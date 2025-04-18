#include "debug_ui.h"
#include "patches.h"

#include "game/objects/object.h"
#include "sys/camera.h"
#include "sys/gfx/gx.h"
#include "sys/math.h"
#include "variables.h"

#include "../culling.h"
#include "../gfx_patches.h"

extern f32 gFovY;
extern f32 gAspect;
extern u16 gPerspNorm;
extern MtxF gViewProjMtx;
extern MtxF gProjectionMtx;
extern MtxF gViewMtx;
extern f32 gNearPlane;
extern f32 gFarPlane;
extern Viewport gViewports[4];
extern Vp gRSPViewports[20];

extern s32* gCurMtx;
extern s32* gCurVtx;
extern s32* gCurPol;

static s32 gCurGfx_overflowed = FALSE;
static s32 gCurMtx_overflowed = FALSE;
static s32 gCurVtx_overflowed = FALSE;
static s32 gCurPol_overflowed = FALSE;

static void general_tab() {
    recomp_dbgui_textf("gWorldX: %f", gWorldX);
    recomp_dbgui_textf("gWorldZ: %f", gWorldZ);

    u32 gdlSize = (u32)gCurGfx - (u32)gMainGfx[gFrameBufIdx];
    u32 mtxSize = (u32)gCurMtx - (u32)gMainMtx[gFrameBufIdx];
    u32 vtxSize = (u32)gCurVtx - (u32)gMainVtx[gFrameBufIdx];
    u32 polSize = (u32)gCurPol - (u32)gMainPol[gFrameBufIdx];

    if (gdlSize > RECOMP_MAIN_GFX_BUF_SIZE) gCurGfx_overflowed = TRUE;
    if (mtxSize > RECOMP_MAIN_MTX_BUF_SIZE) gCurMtx_overflowed = TRUE;
    if (vtxSize > RECOMP_MAIN_VTX_BUF_SIZE) gCurVtx_overflowed = TRUE;
    if (polSize > RECOMP_MAIN_POL_BUF_SIZE) gCurPol_overflowed = TRUE;

    recomp_dbgui_textf("gCurGfx size: %x/%x\t(%f%%)", gdlSize, RECOMP_MAIN_GFX_BUF_SIZE, (f32)gdlSize / (f32)RECOMP_MAIN_GFX_BUF_SIZE);
    if (gCurGfx_overflowed) recomp_dbgui_textf("WARN: gCurGfx overflowed!!!");
    
    recomp_dbgui_textf("gCurMtx size: %x/%x\t(%f%%)", mtxSize, RECOMP_MAIN_MTX_BUF_SIZE, (f32)mtxSize / (f32)RECOMP_MAIN_MTX_BUF_SIZE);
    if (gCurMtx_overflowed) recomp_dbgui_textf("WARN: gCurMtx overflowed!!!");
    
    recomp_dbgui_textf("gCurVtx size: %x/%x\t(%f%%)", vtxSize, RECOMP_MAIN_VTX_BUF_SIZE, (f32)vtxSize / (f32)RECOMP_MAIN_VTX_BUF_SIZE);
    if (gCurVtx_overflowed) recomp_dbgui_textf("WARN: gCurVtx overflowed!!!");
    
    recomp_dbgui_textf("gCurPol size: %x/%x\t(%f%%)", polSize, RECOMP_MAIN_POL_BUF_SIZE, (f32)polSize / (f32)RECOMP_MAIN_POL_BUF_SIZE);
    if (gCurPol_overflowed) recomp_dbgui_textf("WARN: gCurPol overflowed!!!");
}

static void camera_tab() {
    recomp_dbgui_textf("gFovY: %f", gFovY);
    recomp_dbgui_textf("gFovY: %f", gFovY);
    recomp_dbgui_textf("gAspect: %f", gAspect);
    recomp_dbgui_textf("gNearPlane: %f", gNearPlane);
    recomp_dbgui_textf("gFarPlane: %f", gFarPlane);
    recomp_dbgui_textf("gPerspNorm: %d", gPerspNorm);

    if (recomp_dbgui_tree_node("gProjectionMtx")) {
        for (int i = 0; i < 4; i++) {
            recomp_dbgui_textf("%f %f %f %f", gProjectionMtx.m[i][0], gProjectionMtx.m[i][1], gProjectionMtx.m[i][2], gProjectionMtx.m[i][3]);
        }

        recomp_dbgui_tree_pop();
    }

    if (recomp_dbgui_tree_node("gViewMtx")) {
        for (int i = 0; i < 4; i++) {
            recomp_dbgui_textf("%f %f %f %f", gViewMtx.m[i][0], gViewMtx.m[i][1], gViewMtx.m[i][2], gViewMtx.m[i][3]);
        }

        recomp_dbgui_tree_pop();
    }

    if (recomp_dbgui_tree_node("gViewProjMtx")) {
        for (int i = 0; i < 4; i++) {
            recomp_dbgui_textf("%f %f %f %f", gViewProjMtx.m[i][0], gViewProjMtx.m[i][1], gViewProjMtx.m[i][2], gViewProjMtx.m[i][3]);
        }

        recomp_dbgui_tree_pop();
    }

    if (recomp_dbgui_tree_node("gViewports")) {
        for (s32 i = 0; i < 4; i++) {
            Viewport *viewport = &gViewports[i];

            if (recomp_dbgui_tree_node(recomp_sprintf_helper("[%d]", i))) {
                recomp_dbgui_textf("x1: %d", viewport->x1);
                recomp_dbgui_textf("y1: %d", viewport->y1);
                recomp_dbgui_textf("x2: %d", viewport->x2);
                recomp_dbgui_textf("y2: %d", viewport->y2);
                recomp_dbgui_textf("posX: %d", viewport->posX);
                recomp_dbgui_textf("posY: %d", viewport->posY);
                recomp_dbgui_textf("width: %d", viewport->width);
                recomp_dbgui_textf("height: %d", viewport->height);
                recomp_dbgui_textf("ulx: %d", viewport->ulx);
                recomp_dbgui_textf("uly: %d", viewport->uly);
                recomp_dbgui_textf("lrx: %d", viewport->lrx);
                recomp_dbgui_textf("lry: %d", viewport->lry);
                recomp_dbgui_textf("flags: %d", viewport->flags);

                recomp_dbgui_tree_pop();
            }
        }

        recomp_dbgui_tree_pop();
    }

    if (recomp_dbgui_tree_node("gRSPViewports")) {
        for (s32 i = 0; i < 28; i++) {
            Vp *viewport = &gRSPViewports[i];

            if (recomp_dbgui_tree_node(recomp_sprintf_helper("[%d]", i))) {
                recomp_dbgui_textf("vscale[0]: %d", viewport->vp.vscale[0]);
                recomp_dbgui_textf("vscale[1]: %d", viewport->vp.vscale[1]);
                recomp_dbgui_textf("vscale[2]: %d", viewport->vp.vscale[2]);
                recomp_dbgui_textf("vscale[3]: %d", viewport->vp.vscale[3]);
                recomp_dbgui_textf("vtrans[0]: %d", viewport->vp.vtrans[0]);
                recomp_dbgui_textf("vtrans[1]: %d", viewport->vp.vtrans[1]);
                recomp_dbgui_textf("vtrans[2]: %d", viewport->vp.vtrans[2]);
                recomp_dbgui_textf("vtrans[3]: %d", viewport->vp.vtrans[3]);

                recomp_dbgui_tree_pop();
            }
        }

        recomp_dbgui_tree_pop();
    }
}

static void video_tab() {
    u32 res = get_some_resolution_encoded();
    u32 width = RESOLUTION_WIDTH(res);
    u32 height = RESOLUTION_HEIGHT(res);

    u32 otherRes = get_some_resolution_encoded();
    u32 otherWidth = RESOLUTION_WIDTH(otherRes);
    u32 otherHeight = RESOLUTION_HEIGHT(otherRes);

    recomp_dbgui_textf("Resolution: %dx%d", width, height);
    recomp_dbgui_textf("Other resolution: %dx%d", otherWidth, otherHeight);
    recomp_dbgui_textf("gDisplayHertz: %d", gDisplayHertz);
    recomp_dbgui_textf("delayByte: %d", delayByte);
    recomp_dbgui_textf("delayFloat: %f", delayFloat);
    recomp_dbgui_textf("framerate divisor: %d", D_800BCE34);
    recomp_dbgui_textf("osViBlack timer: %d", D_800BCE14);
    recomp_dbgui_textf("aspectRatioFloat: %f", aspectRatioFloat);
    recomp_dbgui_textf("gHStartMod: %d", gHStartMod);
    recomp_dbgui_textf("gVScaleMod: %d", gVScaleMod);
    recomp_dbgui_textf("osTvType: %d", osTvType);
    recomp_dbgui_textf("gVideoMode: %d", gVideoMode);
    if (recomp_dbgui_tree_node("gOSViModeCustom")) {
        recomp_dbgui_textf("type: %d", gOSViModeCustom.type);
        recomp_dbgui_textf("comRegs.ctrl: %d", gOSViModeCustom.comRegs.ctrl);
        recomp_dbgui_textf("comRegs.width: %d", gOSViModeCustom.comRegs.width);
        recomp_dbgui_textf("comRegs.burst: %d", gOSViModeCustom.comRegs.burst);
        recomp_dbgui_textf("comRegs.vSync: %d", gOSViModeCustom.comRegs.vSync);
        recomp_dbgui_textf("comRegs.hSync: %d", gOSViModeCustom.comRegs.hSync);
        recomp_dbgui_textf("comRegs.leap: %d", gOSViModeCustom.comRegs.leap);
        recomp_dbgui_textf("comRegs.hStart: %d", gOSViModeCustom.comRegs.hStart);
        recomp_dbgui_textf("comRegs.xScale: %d", gOSViModeCustom.comRegs.xScale);
        recomp_dbgui_textf("comRegs.vCurrent: %d", gOSViModeCustom.comRegs.vCurrent);
        recomp_dbgui_textf("fldRegs[0].origin: %d", gOSViModeCustom.fldRegs[0].origin);
        recomp_dbgui_textf("fldRegs[0].yScale: %d", gOSViModeCustom.fldRegs[0].yScale);
        recomp_dbgui_textf("fldRegs[0].vStart: %d", gOSViModeCustom.fldRegs[0].vStart);
        recomp_dbgui_textf("fldRegs[0].vBurst: %d", gOSViModeCustom.fldRegs[0].vBurst);
        recomp_dbgui_textf("fldRegs[0].vIntr: %d", gOSViModeCustom.fldRegs[0].vIntr);
        recomp_dbgui_textf("fldRegs[1].origin: %d", gOSViModeCustom.fldRegs[1].origin);
        recomp_dbgui_textf("fldRegs[1].yScale: %d", gOSViModeCustom.fldRegs[1].yScale);
        recomp_dbgui_textf("fldRegs[1].vStart: %d", gOSViModeCustom.fldRegs[1].vStart);
        recomp_dbgui_textf("fldRegs[1].vBurst: %d", gOSViModeCustom.fldRegs[1].vBurst);
        recomp_dbgui_textf("fldRegs[1].vIntr: %d", gOSViModeCustom.fldRegs[1].vIntr);
        
        recomp_dbgui_tree_pop();
    }
}

static void enhancements_tab() {
    recomp_dbgui_checkbox("Disable culling (widescreen support)", &recompCullingDisabled);
    recomp_dbgui_checkbox("30 FPS SnowBike race", &snowbike30FPS);
}

void dbgui_graphics_window(s32 *open) {
    if (recomp_dbgui_begin("Graphics Debug", open)) {
        if (recomp_dbgui_begin_tab_bar("tabs")) {
            if (recomp_dbgui_begin_tab_item("General", NULL)) {
                general_tab();
                recomp_dbgui_end_tab_item();
            }

            if (recomp_dbgui_begin_tab_item("Camera", NULL)) {
                camera_tab();
                recomp_dbgui_end_tab_item();
            }

            if (recomp_dbgui_begin_tab_item("Video", NULL)) {
                video_tab();
                recomp_dbgui_end_tab_item();
            }

            if (recomp_dbgui_begin_tab_item("Enhancements", NULL)) {
                enhancements_tab();
                recomp_dbgui_end_tab_item();
            }
            
            recomp_dbgui_end_tab_bar();
        }
    }
    recomp_dbgui_end();
}
