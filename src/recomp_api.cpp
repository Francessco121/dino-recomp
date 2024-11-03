// #include <stdio.h>
// #include <array>
// #include <cmath>

// #include "librecomp/recomp.h"
// #include "librecomp/helpers.hpp"
// #include "ultramodern/ultramodern.hpp"

// extern "C" void load_overlay_by_id(uint32_t id, uint32_t ram_addr);

// extern "C" void recomp_puts(uint8_t* rdram, recomp_context* ctx) {
//     PTR(char) cur_str = _arg<0, PTR(char)>(rdram, ctx);
//     u32 length = _arg<1, u32>(rdram, ctx);

//     for (u32 i = 0; i < length; i++) {
//         fputc(MEM_B(i, (gpr)cur_str), stdout);
//     }
// }

// extern "C" void recomp_load_overlay_by_id(uint8_t * rdram, recomp_context * ctx) {
//     u32 id = _arg<0, u32>(rdram, ctx);
//     PTR(void) ram = _arg<1, PTR(void)>(rdram, ctx);

//     load_overlay_by_id(id, ram);
// }
