#include "stdarg.h"

#include "patches.h"
#include "recomp_funcs.h"

extern int _Printf(void*, s32, const char* fmt, ...);

// Hook up game printf to recomp logging
RECOMP_PATCH void* proutSyncPrintf(void* dst, const char* fmt, s32 size) {
    recomp_puts(fmt, size);
    return (void*)1;
}

RECOMP_EXPORT int recomp_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = _Printf(&proutSyncPrintf, NULL, fmt, args);

    va_end(args);

    return ret;
}

// Hook up unused print function
RECOMP_PATCH s32 dummied_print_func(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    recomp_printf(fmt, args);
    recomp_printf("\n");

    va_end(args);

    return 0;
}
