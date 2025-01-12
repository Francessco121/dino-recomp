#include "ultramodern/ultramodern.hpp"
#include "recomp.h"
#include "librecomp/helpers.hpp"

#include "dino/game.hpp"

extern "C" void recomp_get_pending_warp(uint8_t* rdram, recomp_context* ctx) {
    _return(ctx, dino::game::get_next_warp());
}

