#pragma once

#include "rt64_render_hooks.h"

namespace dino::renderer {

void add_hook(RT64::RenderHookInit *init, RT64::RenderHookDraw *draw, RT64::RenderHookDeinit *deinit);
    
}
