#include "culling.h"

#include "PR/ultratypes.h"

s32 recompCullingDisabled = TRUE;

s32 recomp_disable_culling() {
    return recompCullingDisabled;
}