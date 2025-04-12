#include "recomp.h"

extern "C" void __osSpSetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    // Ignore sp set status calls
    //
    // Most of these calls are avoided by how librecomp implements libultra,
    // but Dinosaur Planet's scheduler makes a few calls directly to this
    // during crash handling code, which we can just ignore.
}

extern "C" void __osSpGetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    // This is just here for completeness, the game makes no direct calls to
    // this function. Assert here for sanity's sake.
    assert(false);
}
