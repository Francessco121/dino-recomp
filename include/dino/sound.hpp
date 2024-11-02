#pragma once

namespace dino::sound {
    void reset_sound_settings();
    void set_main_volume(int volume);
    int get_main_volume();
    void set_bgm_volume(int volume);
    int get_bgm_volume();
    void set_low_health_beeps_enabled(bool enabled);
    bool get_low_health_beeps_enabled();
}
