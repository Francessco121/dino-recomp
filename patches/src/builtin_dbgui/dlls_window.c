#include "debug_ui.h"
#include "sys/dll.h"

void dbgui_dlls_window(s32 *open) {
    if (recomp_dbgui_begin("DLLs", open)) {
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
