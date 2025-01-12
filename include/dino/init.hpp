#pragma once

#include <cinttypes>
#include <string>

#include "ultramodern/ultramodern.hpp"
#include "librecomp/rsp.hpp"

namespace dino::init {
    // gfx

    ultramodern::gfx_callbacks_t::gfx_data_t create_gfx();
    ultramodern::renderer::WindowHandle create_window(ultramodern::gfx_callbacks_t::gfx_data_t);
    void update_gfx(void*);

    // audio

    void queue_samples(int16_t* audio_data, size_t sample_count);
    size_t get_frames_remaining();
    void set_frequency(uint32_t freq);
    void reset_audio(uint32_t output_freq);

    // rsp

    RspUcodeFunc* get_rsp_microcode(const OSTask* task);

    // threads

    std::string get_game_thread_name(const OSThread* t);

    // overlays

    void register_overlays();

    // patches

    void register_patches();

    // mods

    void register_mods();
}
