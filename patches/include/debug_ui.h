#pragma once

#include "patch_helpers.h"
#include "stdarg.h"

DECLARE_FUNC(void, recomp_dbgui_ui_frame_begin);
DECLARE_FUNC(void, recomp_dbgui_ui_frame_end);
DECLARE_FUNC(s32, recomp_dbgui_begin, const char *str, s32 *open);
DECLARE_FUNC(void, recomp_dbgui_end);
DECLARE_FUNC(void, recomp_dbgui_text, const char *text);
DECLARE_FUNC(void, recomp_dbgui_label_text, const char *label, const char *text);
DECLARE_FUNC(void, recomp_dbgui_same_line);
DECLARE_FUNC(s32, recomp_dbgui_begin_combo, const char *label, const char *preview);
DECLARE_FUNC(void, recomp_dbgui_end_combo);
DECLARE_FUNC(s32, recomp_dbgui_selectable, const char *label, s32 selected);
DECLARE_FUNC(s32, recomp_dbgui_button, const char *label);
DECLARE_FUNC(s32, recomp_dbgui_is_open);
DECLARE_FUNC(s32, recomp_dbgui_begin_main_menu_bar);
DECLARE_FUNC(void, recomp_dbgui_end_main_menu_bar);
DECLARE_FUNC(s32, recomp_dbgui_begin_menu, const char *label);
DECLARE_FUNC(void, recomp_dbgui_end_menu);
DECLARE_FUNC(s32, recomp_dbgui_menu_item, const char *label, s32 *selected);
DECLARE_FUNC(s32, recomp_dbgui_collapsing_header, const char *label);
DECLARE_FUNC(s32, recomp_dbgui_tree_node, const char *label);
DECLARE_FUNC(void, recomp_dbgui_tree_pop);
DECLARE_FUNC(s32, recomp_dbgui_begin_child, const char *str_id);
DECLARE_FUNC(void, recomp_dbgui_end_child);
DECLARE_FUNC(s32, recomp_dbgui_checkbox, const char *label, s32 *value);
DECLARE_FUNC(s32, recomp_dbgui_input_int, const char *label, s32 *value);
DECLARE_FUNC(s32, recomp_dbgui_input_float, const char *label, f32 *value);

const char *recomp_vsprintf_helper(const char *fmt, va_list args);
const char *recomp_sprintf_helper(const char *fmt, ...);

void recomp_dbgui_textf(const char *fmt, ...);
void recomp_dbgui_label_textf(const char *label, const char *fmt, ...);
