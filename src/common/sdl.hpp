#pragma once

#define SDL_MAIN_HANDLED
#ifdef _WIN32
#include "SDL.h" // IWYU pragma: export
#include "SDL_syswm.h" // IWYU pragma: export
#else
#include "SDL2/SDL.h" // IWYU pragma: export
#include "SDL2/SDL_syswm.h" // IWYU pragma: export
#endif
