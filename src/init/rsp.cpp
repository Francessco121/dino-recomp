#include <cinttypes>

#include "ultramodern/ultra64.h"
#include "ultramodern/ultramodern.hpp"
#include "librecomp/rsp.hpp"

#include "dino/init.hpp"

//extern RspUcodeFunc njpgdspMain;
//extern RspUcodeFunc aspMain;

RspExitReason njpgdspMain_stub(uint8_t *rdram) {
    return RspExitReason::Broke;
}

RspExitReason aspMain_stub(uint8_t *rdram) {
    return RspExitReason::Broke;
}

RspUcodeFunc* dino::init::get_rsp_microcode(const OSTask* task) {
    switch (task->t.type) {
    case M_AUDTASK:
        return aspMain_stub;
       //return aspMain;

    case M_NJPEGTASK:
        return njpgdspMain_stub;
       //return njpgdspMain;

    default:
        fprintf(stderr, "Unknown task: %" PRIu32 "\n", task->t.type);
        return nullptr;
    }
}
