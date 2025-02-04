#include "recomp_funcs.h"
#include "patches.h"
#include "debug_ui.h"

const char *recomp_vsprintf_helper(const char *fmt, va_list args) {
    // 1MB buffer for string formatting... if that's not enough then
    // you have bigger problems...
    static char buffer[1024 * 1024];
    
    vsprintf(buffer, fmt, args);

    return buffer;
}

const char *recomp_sprintf_helper(const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    const char *str = recomp_vsprintf_helper(fmt, args);

    va_end(args);

    return str;
}

// recomp_dbgui_textf

void recomp_dbgui_textf(const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_text(recomp_vsprintf_helper(fmt, args));

    va_end(args);
}

RECOMP_EXPORT void mod_dbgui_textf(const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_text(recomp_vsprintf_helper(fmt, args));

    va_end(args);
}

// recomp_dbgui_label_textf

void recomp_dbgui_label_textf(const char *label, const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_label_text(label, recomp_vsprintf_helper(fmt, args));

    va_end(args);
}

RECOMP_EXPORT void mod_dbgui_label_textf(const char *label, const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    recomp_dbgui_label_text(label, recomp_vsprintf_helper(fmt, args));

    va_end(args);
}

// mod re-exports

RECOMP_EXPORT s32 mod_dbgui_begin(const char *str, s32 *open) {
    return recomp_dbgui_begin(str, open);
}
RECOMP_EXPORT void mod_dbgui_end() {
    recomp_dbgui_end();
}
RECOMP_EXPORT void mod_dbgui_text(const char *text) {
    recomp_dbgui_text(text);
}
RECOMP_EXPORT void mod_dbgui_label_text(const char *label, const char *text) {
    recomp_dbgui_label_text(label, text);
}
RECOMP_EXPORT void mod_dbgui_same_line() {
    recomp_dbgui_same_line();
}
RECOMP_EXPORT s32 mod_dbgui_begin_combo(const char *label, const char *preview) {
    return recomp_dbgui_begin_combo(label, preview);
}
RECOMP_EXPORT void mod_dbgui_end_combo() {
    recomp_dbgui_end_combo();
}
RECOMP_EXPORT s32 mod_dbgui_selectable(const char *label, s32 selected) {
    return recomp_dbgui_selectable(label, selected);
}
RECOMP_EXPORT s32 mod_dbgui_button(const char *label) {
    return recomp_dbgui_button(label);
}
RECOMP_EXPORT s32 mod_dbgui_is_open() {
    return recomp_dbgui_is_open();
}
RECOMP_EXPORT s32 mod_dbgui_begin_main_menu_bar() {
    return recomp_dbgui_begin_main_menu_bar();
}
RECOMP_EXPORT void mod_dbgui_end_main_menu_bar() {
    recomp_dbgui_end_main_menu_bar();
}
RECOMP_EXPORT s32 mod_dbgui_begin_menu(const char *label) {
    return recomp_dbgui_begin_menu(label);
}
RECOMP_EXPORT void mod_dbgui_end_menu() {
    recomp_dbgui_end_menu();
}
RECOMP_EXPORT s32 mod_dbgui_menu_item(const char *label, s32 *selected) {
    return recomp_dbgui_menu_item(label, selected);
}
RECOMP_EXPORT s32 mod_dbgui_collapsing_header(const char *label) {
    return recomp_dbgui_collapsing_header(label);
}
RECOMP_EXPORT s32 mod_dbgui_tree_node(const char *label) {
    return recomp_dbgui_tree_node(label);
}
RECOMP_EXPORT void mod_dbgui_tree_pop() {
    recomp_dbgui_tree_pop();
}
RECOMP_EXPORT s32 mod_dbgui_begin_child(const char *str_id) {
    return recomp_dbgui_begin_child(str_id);
}
RECOMP_EXPORT void mod_dbgui_end_child() {
    recomp_dbgui_end_child();
}
RECOMP_EXPORT s32 mod_dbgui_checkbox(const char *label, s32 *value) {
    return recomp_dbgui_checkbox(label, value);
}
RECOMP_EXPORT s32 mod_dbgui_input_int(const char *label, s32 *value) {
    return recomp_dbgui_input_int(label, value);
}
RECOMP_EXPORT s32 mod_dbgui_input_float(const char *label, f32 *value) {
    return recomp_dbgui_input_float(label, value);
}
