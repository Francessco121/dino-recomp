#include "gfx_patches.h"

#include "patches.h"

#include "sys/gfx/gx.h"
#include "sys/memory.h"

RECOMP_PATCH void alloc_frame_buffers(void)
{   
    // @recomp: Use larger buffer sizes

    // in default.dol these have names as well.
    // alloc graphic display list command buffers. ("main:gfx" in default.dol)
    gMainGfx[0] = (s32)malloc(RECOMP_MAIN_GFX_BUF_SIZE * 2, ALLOC_TAG_LISTS_COL, NULL);
    gMainGfx[1] = gMainGfx[0] + RECOMP_MAIN_GFX_BUF_SIZE;

    // matrix buffers ("main:mtx")
    gMainMtx[0] = (s32)malloc(RECOMP_MAIN_MTX_BUF_SIZE * 2, ALLOC_TAG_LISTS_COL, NULL);
    gMainMtx[1] = gMainMtx[0] + RECOMP_MAIN_MTX_BUF_SIZE;

    // polygon buffers? ("main:pol")
    gMainPol[0] = (s32)malloc(RECOMP_MAIN_POL_BUF_SIZE * 2, ALLOC_TAG_LISTS_COL, NULL);
    gMainPol[1] = gMainPol[0] + RECOMP_MAIN_POL_BUF_SIZE;

    // vertex buffers ("main:vtx")
    gMainVtx[0] = (s32)malloc(RECOMP_MAIN_VTX_BUF_SIZE * 2, ALLOC_TAG_LISTS_COL, NULL);
    gMainVtx[1] = gMainVtx[0] + RECOMP_MAIN_VTX_BUF_SIZE;
}
