#pragma once

#include "recomp.h"

#define MEM_F32(offset, reg) \
    (*(float*)(rdram + ((((reg) + (offset))) - 0xFFFFFFFF80000000)))
