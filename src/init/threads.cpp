#include <string>

#include "ultramodern/ultra64.h"

#include "dino/init.hpp"

std::string dino::init::get_game_thread_name(const OSThread* t) {
    std::string name = "[Game] ";

    switch (t->id) {
        case 0:
            switch (t->priority) {
                case 150:
                    name += "PIMGR";
                    break;

                case 254:
                    name += "VIMGR";
                    break;

                default:
                    name += std::to_string(t->id);
                    break;
            }
            break;

        case 1:
            name += "IDLE";
            break;

        case 2:
            switch (t->priority) {
                case 5:
                    name += "SLOWLY";
                    break;

                case 127:
                    name += "FAULT";
                    break;

                default:
                    name += std::to_string(t->id);
                    break;
            }
            break;

        case 3:
            name += "MAIN";
            break;

        case 4:
            name += "GRAPH";
            break;

        case 5:
            name += "SCHED";
            break;

        case 7:
            name += "PADMGR";
            break;

        case 10:
            name += "AUDIOMGR";
            break;

        case 13:
            name += "FLASHROM";
            break;

        case 18:
            name += "DMAMGR";
            break;

        case 19:
            name += "IRQMGR";
            break;

        default:
            name += std::to_string(t->id);
            break;
    }

    return name;
}
