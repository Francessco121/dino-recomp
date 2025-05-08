#include "culling.h"
#include "recomp_funcs.h"

#include "PR/ultratypes.h"

s32 recompCullingDisabled = TRUE;

s32 recomp_disable_culling() {
    return recomp_get_aspect_ratio() != RECOMP_ASPECT_ORIGINAL && recompCullingDisabled;
}