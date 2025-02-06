#include "recomp_funcs.h"
#include "patches.h"
#include "debug_ui.h"

RECOMP_EXPORT void recomp_dbgui_textf(const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_text(recomp_vsprintf_helper(fmt, args));

    va_end(args);
}

RECOMP_EXPORT void recomp_dbgui_label_textf(const char *label, const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_label_text(label, recomp_vsprintf_helper(fmt, args));

    va_end(args);
}
