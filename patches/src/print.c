// #include "stdarg.h"

// #include "patches.h"
// #include "recomp_funcs.h"

// void* proutSyncPrintf(void* dst, const char* fmt, size_t size) {
//     recomp_puts(fmt, size);
//     return (void*)1;
// }

// int recomp_printf(const char* fmt, ...) {
//     va_list args;
//     va_start(args, fmt);

//     int ret = _Printf(&proutSyncPrintf, NULL, fmt, args);

//     va_end(args);

//     return ret;
// }
