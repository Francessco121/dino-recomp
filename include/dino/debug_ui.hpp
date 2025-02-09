#pragma once

#include "imgui.h"

namespace dino::debug_ui {
    bool is_open();
    void set_is_open(bool open);
    
    bool want_capture_keyboard();

    void ui_frame_begin();
    void ui_frame_end();

    bool begin(const char *name, bool *open);
    void end();

    void text(const char *text);
    void label_text(const char *label, char *text);

    void same_line();

    bool begin_combo(const char *label, char *preview);
    void end_combo();
    bool selectable(const char *label, bool *selected);

    bool button(const char *label);

    bool begin_main_menu_bar();
    void end_main_menu_bar();

    bool begin_menu(const char *label);
    void end_menu();

    bool menu_item(const char *label, bool *selected);

    bool collapsing_header(const char *label);
    bool tree_node(const char *label);
    void tree_pop();

    bool begin_child(const char *str_id);
    void end_child();

    bool checkbox(const char *label, bool *v);
    bool input_int(const char *label, int *v);
    bool input_float(const char *label, float *v);
    bool input_text(const char *label, char *buf, int buf_size);

    void push_str_id(const char *id);
    void pop_id();

    bool is_item_hovered();

    ImVec2 get_display_size();

    ImU32 color_float4_to_u32(const ImVec4 &in);

    void foreground_text(const ImVec2 &pos, ImU32 color, const char *text);
    void foreground_line(const ImVec2 &p1, const ImVec2 &p2, ImU32 color, float thickness);
    void foreground_circle(const ImVec2 &center, float radius, ImU32 color, int num_segments, float thickness);
    void foreground_circle_filled(const ImVec2 &center, float radius, ImU32 color, int num_segments);
    void foreground_ellipse(const ImVec2 &center, float radius_x, float radius_y, ImU32 color, float rot, int num_segments, float thickness);
    void foreground_ellipse_filled(const ImVec2 &center, float radius_x, float radius_y, ImU32 color, float rot, int num_segments);
    void foreground_rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 color, float thickness);
    void foreground_rect_filled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 color);

    void set_render_hooks();
}
