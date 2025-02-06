#pragma once

namespace dino::debug_ui {
    bool is_open();
    void set_is_open(bool open);

    void ui_frame_begin();
    void ui_frame_end();

    bool begin(char *name, bool *open);
    void end();

    void text(char *text);
    void label_text(char *label, char *text);

    void same_line();

    bool begin_combo(char *label, char *preview);
    void end_combo();
    bool selectable(char *label, bool *selected);

    bool button(char *label);

    bool begin_main_menu_bar();
    void end_main_menu_bar();

    bool begin_menu(char *label);
    void end_menu();

    bool menu_item(char *label, bool *selected);

    bool collapsing_header(char *label);
    bool tree_node(char *label);
    void tree_pop();

    bool begin_child(char *str_id);
    void end_child();

    bool checkbox(char *label, bool *v);
    bool input_int(char *label, int *v);
    bool input_float(char *label, float *v);

    void set_render_hooks();
}
