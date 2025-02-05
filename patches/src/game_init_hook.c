#include "patches.h"

RECOMP_DECLARE_EVENT(recomp_on_game_init());

void game_init_hook() {
    recomp_on_game_init();
}