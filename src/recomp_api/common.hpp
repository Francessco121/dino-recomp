#pragma once

#include "librecomp/overlays.hpp" // IWYU pragma: export

#define REGISTER_EXPORT(name) recomp::overlays::register_base_export(#name, name)
