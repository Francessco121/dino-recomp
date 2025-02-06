#include "ultramodern/ultramodern.hpp"
#include "recomp.h"
#include "librecomp/helpers.hpp"

#include "dino/debug_ui.hpp"
#include "dino/config.hpp"

// Strings must be copied out of rdram since their character addresses are effectively
// reversed in rdram compared to normal ram. The returned pointer MUST be freed by the caller.
static char *copy_str(PTR(char) str, uint8_t* rdram, recomp_context* ctx) {
    u32 len = 0;
    PTR(char) str_ptr = str;
    while (MEM_B(0, (gpr)str_ptr++) != '\0') {
        len++;
    }

    char *copy = (char*)malloc(len + 1);
    for (size_t i = 0; i <= len; i++) {
        copy[i] = MEM_B(i, (gpr)str);
    }

    return copy;
}

extern "C" void recomp_dbgui_is_open(uint8_t* rdram, recomp_context* ctx) {
    _return<s32>(ctx, dino::debug_ui::is_open());
}

extern "C" void recomp_dbgui_is_enabled(uint8_t* rdram, recomp_context* ctx) {
    _return<s32>(ctx, dino::config::get_debug_ui_enabled());
}

extern "C" void recomp_dbgui_ui_frame_begin(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::ui_frame_begin();
}

extern "C" void recomp_dbgui_ui_frame_end(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::ui_frame_end();
}

extern "C" void recomp_dbgui_begin(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) name_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(s32) open_ptr = _arg<1, PTR(s32)>(rdram, ctx);

    char *name = copy_str(name_ptr, rdram, ctx);

    bool expanded = false;
    if ((gpr)open_ptr != 0) {
        bool open = MEM_W(0, (gpr)open_ptr) != 0;
        expanded = dino::debug_ui::begin(name, &open);

        MEM_W(0, (gpr)open_ptr) = open;
    } else {
        expanded = dino::debug_ui::begin(name, nullptr);
    }

    free(name);

    _return<s32>(ctx, expanded);
}

extern "C" void recomp_dbgui_end(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::end();
}

extern "C" void recomp_dbgui_text(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) text_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *text = copy_str(text_ptr, rdram, ctx);

    dino::debug_ui::text(text);

    free(text);
}

extern "C" void recomp_dbgui_label_text(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(char) text_ptr = _arg<1, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);
    char *text = copy_str(text_ptr, rdram, ctx);

    dino::debug_ui::label_text(label, text);

    free(label);
    free(text);
}

extern "C" void recomp_dbgui_same_line(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::same_line();
}

extern "C" void recomp_dbgui_begin_combo(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(char) preview_ptr = _arg<1, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);
    char *preview = copy_str(preview_ptr, rdram, ctx);

    bool open = dino::debug_ui::begin_combo(label, preview);

    free(label);
    free(preview);

    _return<s32>(ctx, open);
}

extern "C" void recomp_dbgui_end_combo(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::end_combo();
}

extern "C" void recomp_dbgui_selectable(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    bool selected = _arg<1, s32>(rdram, ctx) != 0;

    char *label = copy_str(label_ptr, rdram, ctx);

    bool pressed = dino::debug_ui::selectable(label, &selected);

    free(label);

    _return<s32>(ctx, pressed);
}

extern "C" void recomp_dbgui_button(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool pressed = dino::debug_ui::button(label);

    free(label);

    _return<s32>(ctx, pressed);
}

extern "C" void recomp_dbgui_begin_main_menu_bar(uint8_t* rdram, recomp_context* ctx) {
    bool expanded = expanded = dino::debug_ui::begin_main_menu_bar();

    _return<s32>(ctx, expanded);
}

extern "C" void recomp_dbgui_end_main_menu_bar(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::end_main_menu_bar();
}

extern "C" void recomp_dbgui_begin_menu(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool open = dino::debug_ui::begin_menu(label);

    free(label);

    _return<s32>(ctx, open);
}

extern "C" void recomp_dbgui_end_menu(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::end_menu();
}

extern "C" void recomp_dbgui_menu_item(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(s32) selected_ptr = _arg<1, PTR(s32)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool pressed = false;
    if ((gpr)selected_ptr != 0) {
        bool selected = MEM_W(0, (gpr)selected_ptr) != 0;
        pressed = dino::debug_ui::menu_item(label, &selected);

        MEM_W(0, (gpr)selected_ptr) = selected;
    } else {
        pressed = dino::debug_ui::menu_item(label, nullptr);
    }

    free(label);

    _return<s32>(ctx, pressed);
}

extern "C" void recomp_dbgui_collapsing_header(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool open = dino::debug_ui::collapsing_header(label);

    free(label);

    _return<s32>(ctx, open);
}

extern "C" void recomp_dbgui_tree_node(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool open = dino::debug_ui::tree_node(label);

    free(label);

    _return<s32>(ctx, open);
}

extern "C" void recomp_dbgui_tree_pop(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::tree_pop();
}

extern "C" void recomp_dbgui_begin_child(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) str_id_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *str_id = copy_str(str_id_ptr, rdram, ctx);

    bool open = dino::debug_ui::begin_child(str_id);

    free(str_id);

    _return<s32>(ctx, open);
}

extern "C" void recomp_dbgui_end_child(uint8_t* rdram, recomp_context* ctx) {
    dino::debug_ui::end_child();
}

extern "C" void recomp_dbgui_checkbox(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(s32) value_ptr = _arg<1, PTR(s32)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    bool value = MEM_W(0, (gpr)value_ptr) != 0;

    bool pressed = dino::debug_ui::checkbox(label, &value);

    MEM_W(0, (gpr)value_ptr) = value;

    free(label);

    _return<s32>(ctx, pressed);
}

extern "C" void recomp_dbgui_input_int(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(s32) value_ptr = _arg<1, PTR(s32)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    s32 value = MEM_W(0, (gpr)value_ptr);

    bool pressed = dino::debug_ui::input_int(label, &value);

    MEM_W(0, (gpr)value_ptr) = value;

    free(label);

    _return<s32>(ctx, pressed);
}

extern "C" void recomp_dbgui_input_float(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) label_ptr = _arg<0, PTR(char)>(rdram, ctx);
    PTR(s32) value_ptr = _arg<1, PTR(s32)>(rdram, ctx);

    char *label = copy_str(label_ptr, rdram, ctx);

    float value = static_cast<float>(MEM_W(0, (gpr)value_ptr));

    bool pressed = dino::debug_ui::input_float(label, &value);

    MEM_W(0, (gpr)value_ptr) = static_cast<s32>(value);

    free(label);

    _return<s32>(ctx, pressed);
}
