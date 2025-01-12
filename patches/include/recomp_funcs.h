#pragma once

#include "patch_helpers.h"

DECLARE_FUNC(void, recomp_puts, const char* data, u32 size);
DECLARE_FUNC(s32, recomp_get_pending_warp);
