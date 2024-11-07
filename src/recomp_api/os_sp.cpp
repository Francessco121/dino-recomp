#include "ultramodern/ultramodern.hpp"
#include "librecomp/recomp.h"

// TODO: is this necessary?
uint32_t spStatus = 0;

extern "C" void __osSpSetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    spStatus = ctx->r4;
}

extern "C" void __osSpGetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    ctx->r2 = spStatus;
}
