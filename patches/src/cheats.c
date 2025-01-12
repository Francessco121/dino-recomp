#include "patches.h"
#include "patch_helpers.h"
#include "recomp_funcs.h"
#include "common.h"

void func_8004D1D4(s32 warpIndex, s32 param2);

void handle_warp_cheat() {
    s32 pendingWarp = recomp_get_pending_warp();
    if (pendingWarp != -1) {
        func_8004D1D4(pendingWarp, 1);
    }
} 
