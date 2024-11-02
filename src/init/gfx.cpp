#include "ultramodern/ultramodern.hpp"

#include "dino/error.hpp"
#include "dino/init.hpp"
#include "dino/input.hpp"
#include "dino_sdl.hpp"

SDL_Window* window;

ultramodern::gfx_callbacks_t::gfx_data_t dino::init::create_gfx() {
    SDL_SetHint(SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2");
    SDL_SetHint(SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS, "0");
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE, "1");
    SDL_SetHint(SDL_HINT_JOYSTICK_HIDAPI_PS5_RUMBLE, "1");
    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

#if defined(__linux__)
    SDL_SetHint(SDL_HINT_VIDEODRIVER, "x11");
#endif

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) > 0) {
        exit_error("Failed to initialize SDL2: %s\n", SDL_GetError());
    }

    return {};
}

ultramodern::renderer::WindowHandle dino::init::create_window(ultramodern::gfx_callbacks_t::gfx_data_t) {
    window = SDL_CreateWindow("Dinosaur Planet: Recompiled", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 960, SDL_WINDOW_RESIZABLE );
#if defined(__linux__)
    SetImageAsIcon("icons/512.png",window);
    if (ultramodern::renderer::get_graphics_config().wm_option == ultramodern::renderer::WindowMode::Fullscreen) { // TODO: Remove once RT64 gets native fullscreen support on Linux
        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        SDL_SetWindowFullscreen(window,0);
    }
#endif

    if (window == nullptr) {
        exit_error("Failed to create window: %s\n", SDL_GetError());
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(window, &wmInfo);

#if defined(_WIN32)
    return ultramodern::renderer::WindowHandle{ wmInfo.info.win.window, GetCurrentThreadId() };
#elif defined(__ANDROID__)
    static_assert(false && "Unimplemented");
#elif defined(__linux__)
    if (wmInfo.subsystem != SDL_SYSWM_X11) {
        exit_error("Unsupported SDL2 video driver \"%s\". Only X11 is supported on Linux.\n", SDL_GetCurrentVideoDriver());
    }

    return ultramodern::renderer::WindowHandle{ wmInfo.info.x11.display, wmInfo.info.x11.window };
#else
    static_assert(false && "Unimplemented");
#endif
}

void dino::init::update_gfx(void*) {
    dino::input::handle_events();
}