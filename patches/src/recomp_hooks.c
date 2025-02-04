#include "patches.h"
#include "cheats.h"
#include "debug_ui.h"
#include "common.h"

RECOMP_DECLARE_EVENT(recomp_on_game_tick());
RECOMP_DECLARE_EVENT(recomp_on_dbgui());

void dbg_ui_test();

void game_tick_hook() {
    handle_warp_cheat();

    recomp_on_game_tick();

    recomp_dbgui_ui_frame_begin();
    dbg_ui_test();
    recomp_on_dbgui();
    recomp_dbgui_ui_frame_end();
}

extern void warpPlayer(s32 warpIndex, s32 param2);

struct WarpEntry {
    s32 idx;
    char *name;
};

static struct WarpEntry warpEntries[] = {
    { 2, "2: Ice Mountain" },
    { 5, "5: Warlock Mountain Back" },
};
const u32 WARP_ENTRIES_COUNT = sizeof(warpEntries) / sizeof(struct WarpEntry);
struct WarpEntry *selectedWarpEntry = &warpEntries[0];

static s32 cheatsOpen = FALSE;
static s32 dllsOpen = FALSE;

static void dbg_ui_dlls_window() {
    if (recomp_dbgui_begin("DLLs", &dllsOpen)) {
        s32 loaded_count = 0;
        for (s32 i = 0; i < gLoadedDLLCount; i++) {
            if (gLoadedDLLList[i].id != DLL_NONE) {
                loaded_count++;
            }
        }

        recomp_dbgui_textf("Loaded DLLs (%d):", loaded_count);

        if (recomp_dbgui_begin_child("##dlls")) {
            for (s32 i = 0; i < gLoadedDLLCount; i++) {
                DLLState *dll = &gLoadedDLLList[i];
                DLLFile *file = dll->id == DLL_NONE
                    ? NULL
                    : DLL_EXPORTS_TO_FILE(dll->exports);
                const char *label = dll->id == DLL_NONE
                    ? recomp_sprintf_helper("<empty slot>##%d", i)
                    : recomp_sprintf_helper("%d##%d", dll->id, i);
                if (recomp_dbgui_tree_node(label)) {
                    recomp_dbgui_textf("refCount: %d", dll->refCount);
                    recomp_dbgui_textf("address: %p", file);
                    recomp_dbgui_tree_pop();
                }
            }
            recomp_dbgui_end_child();
        }
    }
    recomp_dbgui_end();
}

static void dbg_ui_cheat_window() {
    if (recomp_dbgui_begin("Cheats", &cheatsOpen)) {
        if (recomp_dbgui_begin_combo("Warp Location", selectedWarpEntry->name)) {
            for (u32 i = 0; i < WARP_ENTRIES_COUNT; i++) {
                struct WarpEntry *entry = &warpEntries[i];
                if (recomp_dbgui_selectable(entry->name, entry == selectedWarpEntry)) {
                    selectedWarpEntry = entry;
                }
            }
            recomp_dbgui_end_combo();
        }

        if (recomp_dbgui_button("Warp")) {
            warpPlayer(selectedWarpEntry->idx, /*fade*/FALSE);
        }
    }
    recomp_dbgui_end();
}

void dbg_ui_test() {
    if (!recomp_dbgui_is_open()) {
        return;
    }

    if (recomp_dbgui_begin_main_menu_bar()) {
        recomp_dbgui_menu_item("Cheats", &cheatsOpen);
        recomp_dbgui_menu_item("DLLs", &dllsOpen);
        recomp_dbgui_end_main_menu_bar();
    }

    if (cheatsOpen) {
        dbg_ui_cheat_window();
    }
    if (dllsOpen) {
        dbg_ui_dlls_window();
    }
}
