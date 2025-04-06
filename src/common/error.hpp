#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>

template<typename... Ts>
void exit_error(const char* str, Ts ...args) {
    // TODO pop up an error
    ((void)fprintf(stderr, str, args), ...);
    assert(false);
    std::quick_exit(EXIT_FAILURE);
}
