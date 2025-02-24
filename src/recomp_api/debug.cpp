#include "ultramodern/ultramodern.hpp"
#include "recomp.h"
#include "librecomp/helpers.hpp"
#include "dino/config.hpp"

extern "C" void recomp_puts(uint8_t* rdram, recomp_context* ctx) {
    if (!dino::config::get_debug_stdout_enabled()) {
        return;
    }

    PTR(char) cur_str = _arg<0, PTR(char)>(rdram, ctx);
    u32 length = _arg<1, u32>(rdram, ctx);

    for (u32 i = 0; i < length; i++) {
        fputc(MEM_B(i, (gpr)cur_str), stdout);
    }
}

extern "C" void recomp_eputs(uint8_t* rdram, recomp_context* ctx) {
    PTR(char) cur_str = _arg<0, PTR(char)>(rdram, ctx);
    u32 length = _arg<1, u32>(rdram, ctx);

    for (u32 i = 0; i < length; i++) {
        fputc(MEM_B(i, (gpr)cur_str), stderr);
    }
}

// TODO: probably want to remove these below

float mem_float(uint8_t* rdram, int32_t offset, gpr reg) {
    fpr fp;
    fp.u32l = MEM_W(offset, reg);

    return fp.fl;
}

void print_indent(int indent, std::function<void(void)> callback) {
    for (int i = 0; i < (indent * 2); i++) {
        putchar(' ');
    }
    callback();
}

void print_vec3f(int indent, uint8_t* rdram, gpr vec3Addr) {
    float x = mem_float(rdram, 0x0, vec3Addr);
    float y = mem_float(rdram, 0x4, vec3Addr);
    float z = mem_float(rdram, 0x8, vec3Addr);

    print_indent(indent, [=]() { printf(".x = %f\n", x); });
    print_indent(indent, [=]() { printf(".y = %f\n", y); });
    print_indent(indent, [=]() { printf(".z = %f\n", z); });
}

void print_srt(int indent, uint8_t* rdram, gpr srtAddr) {
    int16_t yaw = MEM_H(0x0, srtAddr);
    int16_t pitch = MEM_H(0x2, srtAddr);
    int16_t roll = MEM_H(0x4, srtAddr);
    int16_t flags = MEM_H(0x6, srtAddr);
    float scale = mem_float(rdram, 0x8, srtAddr);
    gpr translAddr = srtAddr + 0xC;

    print_indent(indent, [=]() { printf(".yaw = %d\n", yaw); });
    print_indent(indent, [=]() { printf(".pitch = %d\n", pitch); });
    print_indent(indent, [=]() { printf(".roll = %d\n", roll); });
    print_indent(indent, [=]() { printf(".flags = %x\n", flags); });
    print_indent(indent, [=]() { printf(".scale = %f\n", scale); });
    print_indent(indent, [=]() { printf(".transl =\n"); });
    print_vec3f(indent + 1, rdram, translAddr);
}

void print_actor(int indent, uint8_t* rdram, gpr actorAddr) {
    gpr srtAddr = actorAddr + 0x0;
    gpr positionMirrorAddr = actorAddr + 0x18;

    print_indent(indent, [=]() { printf(".srt =\n"); });
    print_srt(indent + 1, rdram, srtAddr);
    print_indent(indent, [=]() { printf(".positionMirror =\n"); });
    print_vec3f(indent + 1, rdram, positionMirrorAddr);
}

void print_camera(int indent, uint8_t* rdram, gpr cameraAddr) {
    gpr srtAddr = cameraAddr + 0x0;
    print_indent(indent, [=]() { printf(".srt =\n"); });
    print_srt(indent + 1, rdram, srtAddr);
}

extern "C" void recomp_print_vec3f(uint8_t* rdram, gpr vec3Addr) {
    printf("vec3f(0x%zx) =\n", vec3Addr);
    print_vec3f(1, rdram, vec3Addr);
}

extern "C" void recomp_print_vec3f_regs(uint8_t* rdram, gpr x, gpr y, gpr z) {
    printf("vec3f =\n");
    printf("  .x = %f\n", ((fpr)x).fl);
    printf("  .y = %f\n", ((fpr)y).fl);
    printf("  .z = %f\n", ((fpr)z).fl);
}

extern "C" void recomp_print_srt(uint8_t* rdram, gpr srtAddr) {
    printf("srt(0x%zx) =\n", srtAddr);
    print_srt(1, rdram, srtAddr);
}

extern "C" void recomp_print_actor(uint8_t* rdram, gpr actorAddr) {
    printf("actor(0x%zx) =\n", actorAddr);
    print_actor(1, rdram, actorAddr);
}

extern "C" void recomp_print_camera(uint8_t* rdram, gpr cameraAddr) {
    printf("camera(0x%zx) =\n", cameraAddr);
    print_camera(1, rdram, cameraAddr);
}
