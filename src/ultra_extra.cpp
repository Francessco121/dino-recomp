#include <cassert>
#include <cstring>
#include <cstdio>
#include <string>

#include "ultramodern/ultramodern.hpp"
#include "librecomp/recomp.h"

uint32_t spStatus = 0;

extern "C" void __osSpSetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    spStatus = ctx->r4;
}

extern "C" void __osSpGetStatus_recomp(uint8_t* rdram, recomp_context* ctx) {
    ctx->r2 = spStatus;
}

extern "C" uint32_t recomp_osAiGetLength() {
    return ultramodern::get_remaining_audio_bytes();
}

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

extern "C" void dummied_print_func(uint8_t* rdram, recomp_context* ctx) {
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

extern "C" void proutSyncPrintf(uint8_t* rdram, recomp_context* ctx) {
    std::vector<char> printBuffer;

    gpr buf = ctx->r5;
    size_t size = ctx->r6;

    printf("proutSyncPrintf called");

    for (int i = 0; i < size; i++) {
        printBuffer.push_back(MEM_BU(i, buf));
    }

    if (printBuffer.size() > 0) {
        puts(printBuffer.data());
        printBuffer.clear();
    }

    ctx->r2 = 1;
}
