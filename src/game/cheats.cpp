#include <atomic>

std::atomic<int> pendingWarp = -1;

namespace dino::game {
    void set_next_warp(int warpIndex) {
        pendingWarp.store(warpIndex);
    }

    int get_next_warp() {
        return pendingWarp.exchange(-1);
    }
}
