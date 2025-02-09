#include <map>
#include <vector>
#include <optional>

#ifdef _WIN32
#include <SDL_video.h>
#else
#include <SDL2/SDL_video.h>
#endif
#include <SDL_events.h>

#include "rt64_render_hooks.h"
#include "rt64_render_interface_builders.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "ultramodern/renderer_context.hpp"
#include "concurrentqueue.h"

#include "vulkan/rt64_vulkan.h"

#include "imgui/backends/imgui_impl_vulkan.h"

#if defined(_WIN32)
#   include "imgui/backends/imgui_impl_dx12.h"
#   include "imgui/backends/imgui_impl_win32.h"
#   include "utf8conv/utf8conv.h"
#endif

#if defined(_WIN32)
#include "d3d12/rt64_d3d12.h"
#endif

#include "dino/debug_ui.hpp"
#include "dino/renderer.hpp"
#include "dino/config.hpp"

struct VulkanContext {
    VkDevice device = VK_NULL_HANDLE;
    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

    ~VulkanContext() {
        if (renderPass != VK_NULL_HANDLE) {
            vkDestroyRenderPass(device, renderPass, nullptr);
        }

        if (descriptorPool != VK_NULL_HANDLE) {
            vkDestroyDescriptorPool(device, descriptorPool, nullptr);
        }
    }
};

// TODO make this not be global
extern SDL_Window* window;

// We must use our own ImGui context to avoid conflicting with the RT64 inspector where possible
static ImGuiContext *dino_imgui_ctx;
static ImGuiContext *prev_ctx;
static std::unique_ptr<RT64::RenderDescriptorSet> descriptor_set;
static std::mutex frame_mutex;
static bool b_is_open = false;
static bool b_in_ui_frame = false;
static moodycamel::ConcurrentQueue<SDL_Event> event_queue{};
static moodycamel::LightweightSemaphore ui_frame_signal;
static std::unique_ptr<VulkanContext> vulkanContext;

static RT64::UserConfiguration::GraphicsAPI get_graphics_api() {
    const ultramodern::renderer::GraphicsConfig &config = ultramodern::renderer::get_graphics_config();

    switch (config.api_option) {
        case ultramodern::renderer::GraphicsApi::D3D12:
            return RT64::UserConfiguration::GraphicsAPI::D3D12;
        case ultramodern::renderer::GraphicsApi::Vulkan:
            return RT64::UserConfiguration::GraphicsAPI::Vulkan;
        case ultramodern::renderer::GraphicsApi::Auto: {
#if defined(_WIN32)
            return RT64::UserConfiguration::GraphicsAPI::D3D12;
#elif defined(__gnu_linux__)
            return RT64::UserConfiguration::GraphicsAPI::Vulkan;
#elif defined(__APPLE__)
            // TODO: Add MoltenVK option for Mac?
            return RT64::UserConfiguration::GraphicsAPI::Vulkan;
#else
            static_assert(false && "Unimplemented")
#endif
        }
        default:
            assert(false && "Unknown Graphics API.");
            return RT64::UserConfiguration::GraphicsAPI::OptionCount;
    }
}

bool dino::debug_ui::is_open() {
    return b_is_open;
}

void dino::debug_ui::set_is_open(bool open) {
    b_is_open = open;
}

bool dino::debug_ui::want_capture_keyboard() {
    // Go directly through our context pointer so we don't have to worry about it being current
    if (dino_imgui_ctx == nullptr) {
        return false;
    }

    return b_is_open && dino_imgui_ctx->IO.WantCaptureKeyboard;
}

void dino::debug_ui::ui_frame_begin() {
    if (!b_is_open) {
        // Still process the event queue but don't send any to ImGui
        SDL_Event event{};
        while (event_queue.try_dequeue(event)) {
            if (dino::config::get_debug_ui_enabled()) {
                if (event.type == SDL_KEYDOWN && 
                        event.key.keysym.sym == SDLK_BACKQUOTE &&
                        !event.key.repeat) {
                    b_is_open = !b_is_open;
                }
            }
        }
    }

    b_in_ui_frame = true;

    frame_mutex.lock();

    prev_ctx = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(dino_imgui_ctx);

    SDL_Event event{};
    while (event_queue.try_dequeue(event)) {
        if (event.type == SDL_KEYDOWN && 
                event.key.keysym.sym == SDLK_BACKQUOTE &&
                !event.key.repeat) {
            b_is_open = !b_is_open;
        }

        ImGui_ImplSDL2_ProcessEvent(&event);
    }
    
    ImGui_ImplSDL2_NewFrame();

    switch (get_graphics_api()) {
        case RT64::UserConfiguration::GraphicsAPI::D3D12: {
#ifdef _WIN32
            ImGui_ImplDX12_NewFrame();
#else
            assert(false && "Unsupported Graphics API.");
            return;
#endif
            break;
        }
        case RT64::UserConfiguration::GraphicsAPI::Vulkan: {
            ImGui_ImplVulkan_NewFrame();
            break;
        }
        default:
            assert(false && "Unknown Graphics API.");
            break;
    }

    ImGui::NewFrame();
}

void dino::debug_ui::ui_frame_end() {
    if (!b_is_open && !b_in_ui_frame) return;
    
    ImGui::Render();
    ImGui::SetCurrentContext(prev_ctx);

    frame_mutex.unlock();

    if (ui_frame_signal.availableApprox() == 0) {
        ui_frame_signal.signal();
    }

    b_in_ui_frame = false;
}

static void assert_is_open() {
    assert((!b_is_open || b_in_ui_frame) && "Cannot call debug UI functions while outside of the debug UI frame.");
    // b_is_open can be set false concurrently while in the middle of calling ImGui functions,
    // don't fail the assert and instead let the frame finish.
    assert((b_is_open || b_in_ui_frame) && "Cannot call debug UI functions while the debug UI is closed.");
}

bool dino::debug_ui::begin(const char *name, bool *open) {
    assert_is_open();
    return ImGui::Begin(name, open);
}

void dino::debug_ui::end() {
    assert_is_open();
    ImGui::End();
}

void dino::debug_ui::text(const char *text) {
    assert_is_open();
    ImGui::Text("%s", text);
}

void dino::debug_ui::label_text(const char *label, char *text) {
    assert_is_open();
    ImGui::LabelText(label, "%s", text);
}

void dino::debug_ui::same_line() {
    assert_is_open();
    ImGui::SameLine();
}

bool dino::debug_ui::begin_combo(const char *label, char *preview) {
    assert_is_open();
    return ImGui::BeginCombo(label, preview);
}

void dino::debug_ui::end_combo() {
    assert_is_open();
    ImGui::EndCombo();
}

bool dino::debug_ui::selectable(const char *label, bool *selected) {
    assert_is_open();
    return ImGui::Selectable(label, selected);
}

bool dino::debug_ui::button(const char *label) {
    assert_is_open();
    return ImGui::Button(label);
}

bool dino::debug_ui::begin_main_menu_bar() {
    assert_is_open();
    return ImGui::BeginMainMenuBar();
}

void dino::debug_ui::end_main_menu_bar() {
    assert_is_open();
    ImGui::EndMainMenuBar();
}

bool dino::debug_ui::begin_menu(const char *label) {
    assert_is_open();
    return ImGui::BeginMenu(label);
}

void dino::debug_ui::end_menu() {
    assert_is_open();
    ImGui::EndMenu();
}

bool dino::debug_ui::menu_item(const char *label, bool *selected) {
    assert_is_open();
    return ImGui::MenuItem(label, NULL, selected);
}

bool dino::debug_ui::collapsing_header(const char *label) {
    assert_is_open();
    return ImGui::CollapsingHeader(label);
}

bool dino::debug_ui::tree_node(const char *label) {
    assert_is_open();
    return ImGui::TreeNode(label);
}

void dino::debug_ui::tree_pop() {
    assert_is_open();
    ImGui::TreePop();
}

bool dino::debug_ui::begin_child(const char *str_id) {
    assert_is_open();
    return ImGui::BeginChild(str_id);
}

void dino::debug_ui::end_child() {
    assert_is_open();
    ImGui::EndChild();
}

bool dino::debug_ui::checkbox(const char *label, bool *v) {
    assert_is_open();
    return ImGui::Checkbox(label, v);
}

bool dino::debug_ui::input_int(const char *label, int *v) {
    assert_is_open();
    return ImGui::InputInt(label, v);
}

bool dino::debug_ui::input_float(const char *label, float *v) {
    assert_is_open();
    return ImGui::InputFloat(label, v);
}

bool dino::debug_ui::input_text(const char *label, char *buf, int buf_size) {
    assert_is_open();
    return ImGui::InputText(label, buf, buf_size);
}

void dino::debug_ui::push_str_id(const char *id) {
    assert_is_open();
    ImGui::PushID(id);
}

void dino::debug_ui::pop_id() {
    assert_is_open();
    ImGui::PopID();
}

bool dino::debug_ui::is_item_hovered() {
    assert_is_open();
    return ImGui::IsItemHovered();
}

ImVec2 dino::debug_ui::get_display_size() {
    assert_is_open();
    return ImGui::GetIO().DisplaySize;
}

ImU32 dino::debug_ui::color_float4_to_u32(const ImVec4 &in) {
    return ImGui::ColorConvertFloat4ToU32(in);
}

void dino::debug_ui::foreground_text(const ImVec2 &pos, ImU32 color, const char *text) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddText(pos, color, text);
}

void dino::debug_ui::foreground_line(const ImVec2 &p1, const ImVec2 &p2, ImU32 color, float thickness) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddLine(p1, p2, color, thickness);
}

void dino::debug_ui::foreground_circle(const ImVec2 &center, float radius, ImU32 color, int num_segments, float thickness) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddCircle(center, radius, color, num_segments, thickness);
}

void dino::debug_ui::foreground_circle_filled(const ImVec2 &center, float radius, ImU32 color, int num_segments) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddCircleFilled(center, radius, color, num_segments);
}

void dino::debug_ui::foreground_ellipse(const ImVec2 &center, float radius_x, float radius_y, ImU32 color, float rot, int num_segments, float thickness) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddEllipse(center, radius_x, radius_y, color, rot, num_segments, thickness);
}

void dino::debug_ui::foreground_ellipse_filled(const ImVec2 &center, float radius_x, float radius_y, ImU32 color, float rot, int num_segments) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddEllipseFilled(center, radius_x, radius_y, color, rot, num_segments);
}

void dino::debug_ui::foreground_rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 color, float thickness) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddRect(p_min, p_max, color, 0, 0, thickness);
}

void dino::debug_ui::foreground_rect_filled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 color) {
    assert_is_open();
    ImGui::GetForegroundDrawList()->AddRectFilled(p_min, p_max, color);
}

static int sdl_event_filter(void *userdata, SDL_Event *event) {
    event_queue.enqueue(*event);

    return 1;
}

static void checkVulkanResult(VkResult res) {
    if (res == 0) {
        return;
    }

    fprintf(stderr, "Debug UI ImGui Vulkan Backend failed with error code 0x%X.\n", res);
}

// TODO: why isn't this available in imgui_impl_vulkan.h? do we have an outdated version?
static uint32_t ImGui_ImplVulkanH_SelectQueueFamilyIndex(VkPhysicalDevice physical_device)
{
    uint32_t count;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, nullptr);
    ImVector<VkQueueFamilyProperties> queues_properties;
    queues_properties.resize((int)count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &count, queues_properties.Data);
    for (uint32_t i = 0; i < count; i++)
        if (queues_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            return i;
    return (uint32_t)-1;
}

static void rt64_init_hook(RT64::RenderInterface* _interface, RT64::RenderDevice* device) {
    IMGUI_CHECKVERSION();
    
    ImGuiContext *prev_ctx = ImGui::GetCurrentContext();

    dino_imgui_ctx = ImGui::CreateContext();

    ImGui_ImplSDL2_InitForOther(window);

    switch (get_graphics_api()) {
        case RT64::UserConfiguration::GraphicsAPI::D3D12: {
#ifdef _WIN32
            RT64::D3D12Device *interface_device = static_cast<RT64::D3D12Device *>(device);
            RT64::RenderDescriptorRange descriptor_range(RT64::RenderDescriptorRangeType::TEXTURE, 0, 1);
            descriptor_set = interface_device->createDescriptorSet(RT64::RenderDescriptorSetDesc(&descriptor_range, 1));

            RT64::D3D12DescriptorSet *interface_descriptor_set = static_cast<RT64::D3D12DescriptorSet *>(descriptor_set.get());
            const D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle = interface_device->viewHeapAllocator->getShaderCPUHandleAt(interface_descriptor_set->viewAllocation.offset);
            const D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle = interface_device->viewHeapAllocator->getShaderGPUHandleAt(interface_descriptor_set->viewAllocation.offset);
            ImGui_ImplDX12_Init(interface_device->d3d, 2, DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM, interface_device->viewHeapAllocator->shaderHeap, cpu_handle, gpu_handle);
#else
            assert(false && "Unsupported Graphics API.");
            return;
#endif
            break;
        }
        case RT64::UserConfiguration::GraphicsAPI::Vulkan: {
            RT64::VulkanDevice *interfaceDevice = static_cast<RT64::VulkanDevice *>(device);
            ImGui_ImplVulkan_LoadFunctions([](const char *functionName, void *vulkanInstance) {
                return vkGetInstanceProcAddr(*(reinterpret_cast<VkInstance *>(vulkanInstance)), functionName);
            }, &interfaceDevice->renderInterface->instance);

            std::unordered_map<VkDescriptorType, uint32_t> typeCounts;
            typeCounts[VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER] = 1;

            const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM/*, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM*/ };
            
            vulkanContext = std::make_unique<VulkanContext>();
            vulkanContext->device = interfaceDevice->vk;
            vulkanContext->renderPass = RT64::VulkanGraphicsPipeline::createRenderPass(interfaceDevice, requestSurfaceImageFormat, 
                (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), VK_FORMAT_UNDEFINED, VK_SAMPLE_COUNT_1_BIT);
            vulkanContext->descriptorPool = RT64::VulkanDescriptorSet::createDescriptorPool(interfaceDevice, typeCounts);

            uint32_t queueFamily = ImGui_ImplVulkanH_SelectQueueFamilyIndex(interfaceDevice->physicalDevice);
            IM_ASSERT(queueFamily != (uint32_t)-1);

            VkQueue queue;
            vkGetDeviceQueue(interfaceDevice->vk, queueFamily, 0, &queue);

            ImGui_ImplVulkan_InitInfo initInfo = {};
            initInfo.Instance = interfaceDevice->renderInterface->instance;
            initInfo.PhysicalDevice = interfaceDevice->physicalDevice;
            initInfo.Device = vulkanContext->device;
            initInfo.QueueFamily = queueFamily;
            initInfo.Queue = queue;
            initInfo.DescriptorPool = vulkanContext->descriptorPool;
            initInfo.RenderPass = vulkanContext->renderPass;
            initInfo.Subpass = 0;
            initInfo.MinImageCount = 2;
            initInfo.ImageCount = 2;
            initInfo.CheckVkResultFn = &checkVulkanResult;

            ImGui_ImplVulkan_Init(&initInfo);
            break;
        }
        default:
            assert(false && "Unknown Graphics API.");
            break;
    }

    SDL_AddEventWatch(sdl_event_filter, nullptr);

    ImGui::SetCurrentContext(prev_ctx);
}

static void rt64_draw_hook(RT64::RenderCommandList* command_list, RT64::RenderFramebuffer* swap_chain_framebuffer) {
    if (!dino::config::get_debug_ui_enabled() && b_is_open) {
        b_is_open = false;
    }

    if (!b_is_open) return;
    
    // TODO: With higher framerate settings, sometimes we end up deadlocked here. This timeout of 1/30th of a second
    // prevents the game from getting locked up while also working as intended on the default framerate option, but
    // shouldn't be necessary and be fixed at some point.
    ui_frame_signal.wait((int64_t)((1.0 / 30.0) * 1000000));
    
    const std::lock_guard<std::mutex> frame_lock(frame_mutex);

    ImGuiContext *prev_ctx = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(dino_imgui_ctx);

    ImDrawData *draw_data = ImGui::GetDrawData();
    if (draw_data != nullptr) {
        switch (get_graphics_api()) {
            case RT64::UserConfiguration::GraphicsAPI::D3D12: {
#ifdef _WIN32
                RT64::D3D12CommandList *interface_command_list = static_cast<RT64::D3D12CommandList *>(command_list);
                interface_command_list->checkDescriptorHeaps();
                ImGui_ImplDX12_RenderDrawData(draw_data, interface_command_list->d3d);
#else
                assert(false && "Unsupported Graphics API.");
#endif
                break;
            }
            case RT64::UserConfiguration::GraphicsAPI::Vulkan: {
                RT64::VulkanCommandList *interface_command_list = static_cast<RT64::VulkanCommandList *>(command_list);
                ImGui_ImplVulkan_RenderDrawData(draw_data, interface_command_list->vk);
                break;
            }
            default:
                assert(false && "Unknown Graphics API.");
                break;
        }
    }

    ImGui::SetCurrentContext(prev_ctx);
}

static void rt64_deinit_hook() {
    ImGuiContext *prev_ctx = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(dino_imgui_ctx);

    switch (get_graphics_api()) {
        case RT64::UserConfiguration::GraphicsAPI::D3D12:
#ifdef _WIN32
            ImGui_ImplDX12_Shutdown();
            descriptor_set.release();
#else
            assert(false && "Unsupported Graphics API.");
            return;
#endif
            break;
        case RT64::UserConfiguration::GraphicsAPI::Vulkan:
            ImGui_ImplVulkan_Shutdown();
            vulkanContext.reset(nullptr);
            break;
        default:
            assert(false && "Unknown Graphics API.");
            break;
    }

    ImGui_ImplSDL2_Shutdown();

    ImGui::DestroyContext(dino_imgui_ctx);
    ImGui::SetCurrentContext(prev_ctx);
}

void dino::debug_ui::set_render_hooks() {
    dino::renderer::add_hook(rt64_init_hook, rt64_draw_hook, rt64_deinit_hook);
}