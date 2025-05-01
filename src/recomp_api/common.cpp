#include "common.hpp"

namespace dino::recomp_api {
    char *copy_rdram_str(PTR(char) str, uint8_t* rdram, recomp_context* ctx) {
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
}
