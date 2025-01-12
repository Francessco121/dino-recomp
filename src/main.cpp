// TODO: trim unused includes
#include <cstdio>
#include <cassert>
#include <unordered_map>
#include <vector>
#include <array>
#include <filesystem>
#include <numeric>
#include <stdexcept>
#include <cinttypes>

#include "nfd.h"
#include "ultramodern/ultra64.h"
#include "ultramodern/ultramodern.hpp"
#include "librecomp/game.hpp"
#include "librecomp/overlays.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "dino/error.hpp"
#include "dino/init.hpp"
#include "dino/input.hpp"
#include "dino/renderer.hpp"
#include "dino/config.hpp"
#include "dino_sdl.hpp"
#include "recomp_ui.h"

const std::string version_string = "1.0.0";

extern "C" void recomp_entrypoint(uint8_t * rdram, recomp_context * ctx);
gpr get_entrypoint_address();

void dino_thread_create_callback(uint8_t * rdram, recomp_context * ctx) {
    // Dinosaur Planet modifies osCreateThread to enable MIPS3 float mode
    ctx->mips3_float_mode = true;
    ctx->f_odd = &ctx->f1.u32l;
}

// array of supported GameEntry objects
std::vector<recomp::GameEntry> supported_games = {
    {
        .rom_hash = 0xB231A00966BE1430,
        .internal_name = "DINO PLANET",
        .game_id = u8"baserom",
        .mod_game_id = "dino-planet",
        .save_type = recomp::SaveType::Flashram,
        .is_enabled = true,
        .entrypoint_address = get_entrypoint_address(),
        .entrypoint = recomp_entrypoint,
        .thread_create_callback = dino_thread_create_callback,
    },
};

int main(int argc, char** argv) {
    recomp::Version project_version{};
    if (!recomp::Version::from_string(version_string, project_version)) {
        ultramodern::error_handling::message_box(("Invalid version string: " + version_string).c_str());
        return EXIT_FAILURE;
    }

#ifdef _WIN32
    // Set up console output to accept UTF-8 on windows
    SetConsoleOutputCP(CP_UTF8);

    // Initialize native file dialogs.
    NFD_Init();

    // Change to a font that supports Japanese characters
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 16;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"NSimSun");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
#endif

#ifdef _WIN32
    // Force wasapi on Windows, as there seems to be some issue with sample queueing with directsound currently.
    SDL_setenv("SDL_AUDIODRIVER", "wasapi", true);
#endif

    // Initialize SDL audio and set the output frequency.
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    dino::init::reset_audio(48000);

    // Source controller mappings file
    if (SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt") < 0) {
        fprintf(stderr, "Failed to load controller mappings: %s\n", SDL_GetError());
    }

    recomp::register_config_path(dino::config::get_app_folder_path());
    
    // Register supported games
    for (const auto& game : supported_games) {
        recomp::register_game(game);
    }

    dino::init::register_overlays();
    dino::init::register_patches();

    dino::config::load_config();

    recomp::rsp::callbacks_t rsp_callbacks{
        .get_rsp_microcode = dino::init::get_rsp_microcode,
    };

    ultramodern::renderer::callbacks_t renderer_callbacks{
        .create_render_context = dino::renderer::create_render_context,
    };

    ultramodern::gfx_callbacks_t gfx_callbacks{
        .create_gfx = dino::init::create_gfx,
        .create_window = dino::init::create_window,
        .update_gfx = dino::init::update_gfx,
    };

    ultramodern::audio_callbacks_t audio_callbacks{
        .queue_samples = dino::init::queue_samples,
        .get_frames_remaining = dino::init::get_frames_remaining,
        .set_frequency = dino::init::set_frequency,
    };

    ultramodern::input::callbacks_t input_callbacks{
        .poll_input = dino::input::poll_inputs,
        .get_input = dino::input::get_n64_input,
        .set_rumble = dino::input::set_rumble,
        .get_connected_device_info = dino::input::get_connected_device_info,
    };

    ultramodern::events::callbacks_t thread_callbacks{
        .vi_callback = dino::input::update_rumble,
        .gfx_init_callback = recompui::update_supported_options,
    };

    ultramodern::error_handling::callbacks_t error_handling_callbacks{
        .message_box = recompui::message_box,
    };

    ultramodern::threads::callbacks_t threads_callbacks{
        .get_game_thread_name = dino::init::get_game_thread_name,
    };

    dino::init::register_mods();

    recomp::start(
        project_version,
        {},
        rsp_callbacks,
        renderer_callbacks,
        audio_callbacks,
        input_callbacks,
        gfx_callbacks,
        thread_callbacks,
        error_handling_callbacks,
        threads_callbacks
    );

    NFD_Quit();

    return EXIT_SUCCESS;
}
