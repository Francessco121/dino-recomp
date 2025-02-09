#pragma once

#include "patch_helpers.h"
#include "stdarg.h"

#include "PR/ultratypes.h"

typedef struct {
    f32 x, y;
} DbgUiPos;

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
DECLARE_FUNC(s32, recomp_dbgui_is_enabled);
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
DECLARE_FUNC(s32, recomp_dbgui_input_text, const char *label, char *buffer, s32 buffer_size);
DECLARE_FUNC(void, recomp_dbgui_push_str_id, const char *str_id);
DECLARE_FUNC(void, recomp_dbgui_pop_id);
DECLARE_FUNC(s32, recomp_dbgui_is_item_hovered);
DECLARE_FUNC(void, recomp_dbgui_get_display_size, f32 *width, f32 *height);
typedef struct {
    float r;
    float g;
    float b;
    float a;
} DbgUiColor;
DECLARE_FUNC(u32, recomp_dbgui_color_float4_to_u32, const DbgUiColor *color);
DECLARE_FUNC(void, recomp_dbgui_foreground_text, const DbgUiPos *pos, u32 color, const char *text);
typedef struct {
    DbgUiPos p1;
    DbgUiPos p2;
    u32 color;
    float thickness;
} DbgUiLine;
DECLARE_FUNC(void, recomp_dbgui_foreground_line, const DbgUiLine *line);
typedef struct {
    DbgUiPos center;
    float radius;
    u32 color;
    s32 numSegments;
    float thickness;
} DbgUiCircle;
DECLARE_FUNC(void, recomp_dbgui_foreground_circle, const DbgUiCircle *circle);
typedef struct {
    DbgUiPos center;
    float radius;
    u32 color;
    s32 numSegments;
} DbgUiCircleFilled;
DECLARE_FUNC(void, recomp_dbgui_foreground_circle_filled, const DbgUiCircleFilled *circle);
typedef struct {
    DbgUiPos center;
    float radiusX;
    float radiusY;
    u32 color;
    float rotation;
    s32 numSegments;
    float thickness;
} DbgUiEllipse;
DECLARE_FUNC(void, recomp_dbgui_foreground_ellipse, const DbgUiEllipse *ellipse);
typedef struct {
    DbgUiPos center;
    float radiusX;
    float radiusY;
    u32 color;
    float rotation;
    s32 numSegments;
} DbgUiEllipseFilled;
DECLARE_FUNC(void, recomp_dbgui_foreground_ellipse_filled, const DbgUiEllipseFilled *ellipse);
typedef struct {
    DbgUiPos min;
    DbgUiPos max;
    u32 color;
    float thickness;
} DbgUiRect;
DECLARE_FUNC(void, recomp_dbgui_foreground_rect, const DbgUiRect *rect);
typedef struct {
    DbgUiPos min;
    DbgUiPos max;
    u32 color;
} DbgUiRectFilled;
DECLARE_FUNC(void, recomp_dbgui_foreground_rect_filled, const DbgUiRectFilled *rect);

void recomp_dbgui_textf(const char *fmt, ...);
void recomp_dbgui_label_textf(const char *label, const char *fmt, ...);
