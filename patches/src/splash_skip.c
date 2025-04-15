#include "patches.h"

#include "PR/os.h"
#include "PR/sched.h" // TODO: should be in sys/controller.h
#include "sys/controller.h"

static s32 should_skip_splash() {
    return (get_button_presses(0) & A_BUTTON) != 0;
}


#include "recomp/dlls/engine/60_internal.h"

RECOMP_PATCH s32 dll_60_update1() {
    if (data_4 == 1) {
        return 0;
    } else {
        bss_0 += delayFloat;

        // @recomp: Allow skipping
        if (should_skip_splash()) {
            // Fade in background if we haven't shown it yet
            if (bss_0 <= 240.0f) {
                gDLL_28_screen_fade->exports->fade_reversed(30, SCREEN_FADE_BLACK);
            }
            // Let 1 frame render first so the background shows up for the next menu (we render it)
            bss_0 = 720.0f - 0.01f;
            bss_6 = 2;
        }

        if (bss_6 == 0 && bss_0 > 205.0f) {
            gDLL_28_screen_fade->exports->fade(30, SCREEN_FADE_BLACK);
            bss_6 = 1;
        } else if (bss_6 == 1 && bss_0 > 245.0f) {
            gDLL_28_screen_fade->exports->fade_reversed(30, SCREEN_FADE_BLACK);
            bss_6 = 2;
        }

        if (data_0 > 1) {
            bss_8 -= delayFloat;
        }
        if (data_0 > 2) {
            bss_C -= delayFloat;
        }
        if (data_0 > 3) {
            bss_10 -= delayFloat;
        }

        if (bss_0 > 720.0f) {
            bss_4 = 1;
        }

        if (bss_4 != 0) {
            bss_4 = 0;
            bss_0 = 0.0f;
            menu_set(MENU_3);
        }

        return 0;
    } 
}


#include "recomp/dlls/engine/61_internal.h"

RECOMP_PATCH s32 dll_61_update1() {
    s32 delay;

    delay = delayByte;
    if (delay > 3) {
        delay = 3;
    }

    if (bss_1 > 0) {
        bss_1 -= delay;
    }

    // @recomp: Allow skipping
    if (bss_2 != 0 || should_skip_splash()) {
        set_gplay_bitstring(0x44f, 0);
        menu_set(MENU_5);
    }

    data_0 += delayByte;
    if (data_0 > 620) {
        bss_0 = 1;
    }

    if (bss_0 != 0) {
        gDLL_28_screen_fade->exports->fade(30, SCREEN_FADE_BLACK);
        bss_1 = 45;
        bss_2 = 1;
    }

    if (data_4 > 0) {
        bss_4 -= delayFloat;
    }
    if (data_4 > 2) {
        bss_8 -= delayFloat;
    }

    return 0;
}
