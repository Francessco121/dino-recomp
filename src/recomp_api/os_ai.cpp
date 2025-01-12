#include "ultramodern/ultramodern.hpp"
#include "recomp.h"

// osAiGetLength got inlined, we replace it with a call to this
extern "C" uint32_t recomp_osAiGetLength() {
    return ultramodern::get_remaining_audio_bytes();
}
