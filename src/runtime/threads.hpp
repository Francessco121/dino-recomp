#pragma once

#include <string>
#include "ultramodern/ultra64.h"

namespace dino::runtime {

std::string get_game_thread_name(const OSThread* t);

}