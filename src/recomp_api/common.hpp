#pragma once

#include "librecomp/overlays.hpp" // IWYU pragma: export
#include "librecomp/helpers.hpp"

#define REGISTER_EXPORT(name) recomp::overlays::register_base_export(#name, name)

namespace dino::recomp_api {
    // Strings must be copied out of rdram since their character addresses are effectively
    // reversed in rdram compared to normal ram. The returned pointer MUST be freed by the caller.
    char *copy_rdram_str(PTR(char) str, uint8_t* rdram, recomp_context* ctx);
}
