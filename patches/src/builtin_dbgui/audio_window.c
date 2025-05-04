#include "dbgui.h"
#include "../audio.h"

void dbgui_audio_window(s32 *open) {
    if (dbgui_begin("Audio Debug", open)) {
        dbgui_textf("Audio command list size: %x", last_audio_cmdlist_size);
    }
    dbgui_end();
}
