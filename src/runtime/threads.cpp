#include "threads.hpp"

#include <string>

#include "ultramodern/ultra64.h"

namespace dino::runtime {

std::string get_game_thread_name(const OSThread* t) {
    std::string name = "[Game] ";

    switch (t->id) {
        case -1:
            name += "EXCEPTION";
            break;
        
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

        case 3:
            name += "MAIN";
            break;

        case 4:
            name += "AUDIO";
            break;

        case 5:
            name += "SCHED";
            break;

        case 98:
            name += "CONTROLLER";
            break;
        
        case 99:
            name += "ASSET";
            break;
        
        case 100:
            name += "CRASH";
            break;

        default:
            name += std::to_string(t->id);
            break;
    }

    return name;
}

}
