#include "ultramodern/ultramodern.hpp"
#include "librecomp/recomp.h"

static gpr get_print_arg_val(recomp_context* ctx, int arg) {
    switch (arg) {
        case 0:
            return ctx->r5;
        case 1:
            return ctx->r6;
        case 2:
            return ctx->r7;
        default:
            assert(false);
            return 0;
    }
}

static void handle_print_arg(uint8_t* rdram, recomp_context* ctx, std::vector<char>* printBuffer, int arg, size_t *offset) {
    std::vector<char> widthBuffer;
    char padChar = ' ';
    
    char type = 0;
    int typeI = 0;
    while ((type = MEM_BU((*offset)++, ctx->r4)) != '\0') {
        if (type < '0' || type > '9') {
            break;
        } else {
            if (typeI == 0 && type == '0') {
                padChar = '0';
            } else {
                widthBuffer.push_back(type);
            }
        }
    
        typeI++;
    }

    int width = 0;
    if (widthBuffer.size() > 0) {
        std::string widthStr(widthBuffer.data(), widthBuffer.size());
        width = std::stoi(widthStr);
    }

    gpr argVal = get_print_arg_val(ctx, arg);

    char buf[128];
    switch (type) {
        case 'x':
        {
            int written = sprintf_s(buf, "%x", argVal);
            for (int i = 0; i < (width - written); i++) {
                printBuffer->push_back(padChar);
            }
            for (int i = 0; i < written; i++) {
                printBuffer->push_back(buf[i]);
            }
            break;
        }
        case 'd':
        case 'i':
        {
            int written = sprintf_s(buf, "%d", argVal);
            for (int i = 0; i < (width - written); i++) {
                printBuffer->push_back(padChar);
            }
            for (int i = 0; i < written; i++) {
                printBuffer->push_back(buf[i]);
            }
            break;
        }
        case 'f':
        {
            int written = sprintf_s(buf, "%f", argVal);
            for (int i = 0; i < (width - written); i++) {
                printBuffer->push_back(padChar);
            }
            for (int i = 0; i < written; i++) {
                printBuffer->push_back(buf[i]);
            }
            break;
        }
        case 's':
        {
            char c;
            int strOffset = 0;
            while ((c = MEM_BU(strOffset++, argVal)) != '\0') {
                printBuffer->push_back(c);
            }
            break;
        }
        default:
            assert(false);
    }
}

extern "C" void recomp_dummied_print_func(uint8_t* rdram, recomp_context* ctx) {
    std::vector<char> printBuffer;

    char c = '\0';
    size_t offset = 0;
    int arg = 0;
    while ((c = MEM_BU(offset++, ctx->r4)) != '\0') {
        if (c == '%') {
            handle_print_arg(rdram, ctx, &printBuffer, arg++, &offset);
        } else if (c == '\n') {
            puts(printBuffer.data());
            printBuffer.clear();
        } else {
            printBuffer.push_back(c);
        }
    }

    if (printBuffer.size() > 0) {
        puts(printBuffer.data());
        printBuffer.clear();
    }

    ctx->r2 = 0;
}

extern "C" void recomp_proutSyncPrintf(uint8_t* rdram, recomp_context* ctx) {
    std::vector<char> printBuffer;

    gpr buf = ctx->r5;
    size_t size = ctx->r6;

    for (int i = 0; i < size; i++) {
        printBuffer.push_back(MEM_BU(i, buf));
    }

    if (printBuffer.size() > 0) {
        puts(printBuffer.data());
        printBuffer.clear();
    }

    ctx->r2 = 1;
}

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
