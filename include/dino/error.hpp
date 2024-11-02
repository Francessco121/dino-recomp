#pragma once

#include <cassert>

template<typename... Ts>
void exit_error(const char* str, Ts ...args) {
    // TODO pop up an error
    ((void)fprintf(stderr, str, args), ...);
    assert(false);
    std::quick_exit(EXIT_FAILURE);
}
