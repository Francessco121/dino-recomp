#include "rsp.hpp"

#include <cinttypes>

#include "ultramodern/ultra64.h"
#include "librecomp/rsp.hpp"

extern RspUcodeFunc aspMain;

namespace dino::runtime {

RspUcodeFunc* get_rsp_microcode(const OSTask* task) {
    switch (task->t.type) {
    case M_AUDTASK:
        return aspMain;
    default:
        fprintf(stderr, "Unknown task: %" PRIu32 "\n", task->t.type);
        return nullptr;
    }
}

}
