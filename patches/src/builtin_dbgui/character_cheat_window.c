#include "debug_ui.h"
#include "common.h"

static s32 infinite_health = FALSE;
static s32 infinite_mana = FALSE;

void dbgui_character_cheat_window(s32 *open) {
    GplayStruct10 *char_stats = gDLL_29_gplay->exports->func_ED4();

    if (recomp_dbgui_begin("Character Cheats", open)) {
        recomp_dbgui_checkbox("Infinite Health", &infinite_health);
        recomp_dbgui_checkbox("Infinite Mana", &infinite_mana);

        s32 hp = char_stats->hp;
        if (recomp_dbgui_input_int("Health", &hp)) {
            char_stats->hp = (u8)hp;
        }
        s32 hpMax = char_stats->hpMax;
        if (recomp_dbgui_input_int("Max Health", &hpMax)) {
            char_stats->hpMax = (u8)hpMax;
        }
        s32 mana = char_stats->mana;
        if (recomp_dbgui_input_int("Mana", &mana)) {
            char_stats->mana = (s16)mana;
        }
        s32 manaMax = char_stats->manaMax;
        if (recomp_dbgui_input_int("Max Mana", &manaMax)) {
            char_stats->manaMax = (s16)manaMax;
        }
        s32 scarabs = char_stats->scarabs;
        if (recomp_dbgui_input_int("Scarabs", &scarabs)) {
            char_stats->scarabs = (s16)scarabs;
        }
    }
    recomp_dbgui_end();
}

void dbgui_character_cheat_game_tick() {
    if (!recomp_dbgui_is_enabled()) {
        infinite_health = FALSE;
        infinite_mana = FALSE;
        return;
    }
    
    GplayStruct10 *char_stats = gDLL_29_gplay->exports->func_ED4();

    if (infinite_health) {
        char_stats->hp = char_stats->hpMax;
    }
    if (infinite_mana) {
        char_stats->mana = char_stats->manaMax;
    }
}
