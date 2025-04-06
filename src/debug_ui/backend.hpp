#pragma once

#include "imgui.h"

namespace dino::debug_ui::backend {

extern ImGuiContext *dino_imgui_ctx;
extern bool b_is_open;
extern bool b_in_ui_frame;

void begin();
void end();
void set_render_hooks();

}
