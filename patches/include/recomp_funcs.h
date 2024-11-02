#pragma once

#include "patch_helpers.h"

DECLARE_FUNC(void, recomp_puts, const char* data, u32 size);
DECLARE_FUNC(void, recomp_load_overlay_by_id, u32 id, void *ram);

