#include "debug_ui.h"
#include "builtin_dbgui.h"

static s32 dllsOpen = FALSE;
static s32 audioOpen = FALSE;
static s32 graphicsOpen = FALSE;
static s32 memoryOpen = FALSE;
static s32 warpCheatOpen = FALSE;
static s32 charCheatOpen = FALSE;

void builtin_dbgui() {
    if (recomp_dbgui_begin_main_menu_bar()) {
        if (recomp_dbgui_begin_menu("Debug")) {
            recomp_dbgui_menu_item("DLLs", &dllsOpen);
            recomp_dbgui_menu_item("Audio", &audioOpen);
            recomp_dbgui_menu_item("Graphics", &graphicsOpen);
            recomp_dbgui_menu_item("Memory", &memoryOpen);
            recomp_dbgui_end_menu();
        }
        if (recomp_dbgui_begin_menu("Cheats")) {
            recomp_dbgui_menu_item("Warp", &warpCheatOpen);
            recomp_dbgui_menu_item("Character", &charCheatOpen);
            recomp_dbgui_end_menu();
        }
        recomp_dbgui_end_main_menu_bar();
    }

    if (dllsOpen) {
        dbgui_dlls_window(&dllsOpen);
    }
    if (audioOpen) {
        dbgui_audio_window(&audioOpen);
    }
    if (warpCheatOpen) {
        dbgui_warp_cheat_window(&warpCheatOpen);
    }
    if (charCheatOpen) {
        dbgui_character_cheat_window(&charCheatOpen);
    }
    if (graphicsOpen) {
        dbgui_graphics_window(&graphicsOpen);
    }
    if (memoryOpen) {
        dbgui_memory_window(&memoryOpen);
    }
}

void builtin_dbgui_game_tick() {
    dbgui_character_cheat_game_tick();
}
