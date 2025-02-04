#include "patches.h"
#include "cheats.h"
#include "debug_ui.h"
#include "builtin_dbgui.h"

RECOMP_DECLARE_EVENT(recomp_on_game_tick());
RECOMP_DECLARE_EVENT(recomp_on_dbgui());

static void dbgui();

void game_tick_hook() {
    handle_warp_cheat();

    recomp_on_game_tick();

    dbgui();
}

static void dbgui() {
    recomp_dbgui_ui_frame_begin();
    
    if (recomp_dbgui_is_open()) {
        builtin_dbgui();
        recomp_on_dbgui();

        if (recomp_dbgui_begin_main_menu_bar()) {
            recomp_dbgui_text("| Press ` to close debug UI.");
            recomp_dbgui_end_main_menu_bar();
        }
    }

    recomp_dbgui_ui_frame_end();
}
