#pragma once

#include "librecomp/rsp.hpp"

namespace dino::runtime {

RspUcodeFunc* get_rsp_microcode(const OSTask* task);

}