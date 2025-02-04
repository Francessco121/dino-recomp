#include "debug_ui.h"
#include "builtin_dbgui.h"

static s32 warpCheatOpen = FALSE;
static s32 dllsOpen = FALSE;

void builtin_dbgui() {
    if (recomp_dbgui_begin_main_menu_bar()) {
        if (recomp_dbgui_begin_menu("Debug")) {
            recomp_dbgui_menu_item("DLLs", &dllsOpen);
            recomp_dbgui_end_menu();
        }
        if (recomp_dbgui_begin_menu("Cheats")) {
            recomp_dbgui_menu_item("Warp", &warpCheatOpen);
            recomp_dbgui_end_menu();
        }
        recomp_dbgui_end_main_menu_bar();
    }

    if (dllsOpen) {
        dbgui_dlls_window(&dllsOpen);
    }
    if (warpCheatOpen) {
        dbgui_warp_cheat_window(&warpCheatOpen);
    }
}
