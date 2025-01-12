#include "ultramodern/ultramodern.hpp"
#include "recomp.h"

// With the way func_8001B4F0 is recompiled, we need to track whether the function
// already ran it's return routine and prevent it from being ran more than once.
thread_local bool func_8001B4F0_returned = false;

extern "C" void recomp_on_func_8001B4F0_entry() {
    func_8001B4F0_returned = false;
}

extern "C" bool recomp_did_func_8001B4F0_return() {
    return func_8001B4F0_returned;
}

extern "C" void recomp_on_func_8001B4F0_ret() {
    assert(func_8001B4F0_returned == false);
    func_8001B4F0_returned = true;
}
