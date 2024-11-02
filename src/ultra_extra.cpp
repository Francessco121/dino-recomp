#include <cassert>

#include "ultramodern/ultramodern.hpp"
#include "librecomp/recomp.h"

extern "C" void __osSpSetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    assert(false);
}
