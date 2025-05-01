#include "ultramodern/ultramodern.hpp"
#include "ultramodern/error_handling.hpp"
#include "librecomp/helpers.hpp"
#include "recomp.h"

#include "recomp_ui/recomp_ui.hpp"
#include "common.hpp"

extern "C" void recomp_get_window_resolution(uint8_t* rdram, recomp_context* ctx) {
    int width, height;
    recompui::get_window_size(width, height);

    gpr width_out = _arg<0, PTR(u32)>(rdram, ctx);
    gpr height_out = _arg<1, PTR(u32)>(rdram, ctx);

    MEM_W(0, width_out) = (u32)width;
    MEM_W(0, height_out) = (u32)height;
}

extern "C" void recomp_error_message_box(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) message_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *message = dino::recomp_api::copy_rdram_str(message_ptr, rdram, ctx);

    ultramodern::error_handling::message_box(message);

    free(message);
}

extern "C" void recomp_exit_with_error(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) message_ptr = _arg<0, PTR(char)>(rdram, ctx);

    char *message = dino::recomp_api::copy_rdram_str(message_ptr, rdram, ctx);

    ultramodern::error_handling::message_box(message);

    free(message);

    ultramodern::error_handling::quick_exit(__FILE__, __LINE__, __FUNCTION__);
}

extern "C" void recomp_exit(uint8_t* rdram, recomp_context* ctx) {
    ultramodern::quit();
}

extern "C" void recomp_powf(uint8_t* rdram, recomp_context* ctx) {
    float a = _arg<0, float>(rdram, ctx);
    float b = ctx->f14.fl; //_arg<1, float>(rdram, ctx);

    _return(ctx, std::pow(a, b));
}

extern "C" void recomp_time_us(uint8_t* rdram, recomp_context* ctx) {
    _return(ctx, static_cast<u32>(std::chrono::duration_cast<std::chrono::microseconds>(ultramodern::time_since_start()).count()));
}

namespace dino::recomp_api {
    void register_general_exports() {
        REGISTER_EXPORT(recomp_get_window_resolution);
        REGISTER_EXPORT(recomp_error_message_box);
        REGISTER_EXPORT(recomp_exit_with_error);
        REGISTER_EXPORT(recomp_exit);
        REGISTER_EXPORT(recomp_powf);
        REGISTER_EXPORT(recomp_time_us);
    }
}
