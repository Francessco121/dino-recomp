#include "patches.h"
#include "cheats.h"

RECOMP_DECLARE_EVENT(recomp_on_game_tick());

void game_tick_hook() {
    handle_warp_cheat();

    recomp_on_game_tick();
}
