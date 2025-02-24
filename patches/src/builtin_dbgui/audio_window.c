#include "debug_ui.h"
#include "common.h"
#include "../audio.h"

void dbgui_audio_window(s32 *open) {
    if (recomp_dbgui_begin("Audio Debug", open)) {
        recomp_dbgui_textf("Audio command list size: %x", last_audio_cmdlist_size);
    }
    recomp_dbgui_end();
}
