#include "stdarg.h"

#include "patches.h"
#include "recomp_funcs.h"

extern int _Printf(void*, void*, const char* fmt, va_list args);

// Hook up game printf to recomp logging
RECOMP_PATCH void* proutSyncPrintf(void* dst, const char* buf, s32 size) {
    recomp_puts(buf, size);
    return (void*)1;
}

void* proutSyncEPrintf(void* dst, const char* buf, s32 size) {
    recomp_eputs(buf, size);
    return (void*)1;
}

RECOMP_EXPORT int recomp_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = _Printf(&proutSyncPrintf, NULL, fmt, args);

    va_end(args);

    return ret;
}

RECOMP_EXPORT int recomp_vprintf(const char* fmt, va_list args) {
    return _Printf(&proutSyncPrintf, NULL, fmt, args);
}

RECOMP_EXPORT int recomp_eprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = _Printf(&proutSyncEPrintf, NULL, fmt, args);

    va_end(args);

    return ret;
}

RECOMP_EXPORT int recomp_veprintf(const char* fmt, va_list args) {
    return _Printf(&proutSyncEPrintf, NULL, fmt, args);
}

// Hook up unused print function
RECOMP_PATCH s32 dummied_print_func(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int ret = _Printf(&proutSyncPrintf, NULL, fmt, args);
    recomp_puts("\n", 1);

    va_end(args);

    return 0;
}

static void *proutSprintf(void *dst, const char *buf, s32 size) {
    bcopy(buf, dst, size);
	return (void*)((char*)dst + size);
}

RECOMP_EXPORT int sprintf(char *s, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	
    int ret = _Printf(&proutSprintf, (void*)s, fmt, args);
	if (0 <= ret) {
		s[ret] = '\0';
    }
	
    va_end(args);
	
    return (ret);
}

RECOMP_EXPORT int vsprintf(char *s, const char *fmt, va_list args) {
    int ret = _Printf(&proutSprintf, (void*)s, fmt, args);
	if (0 <= ret) {
		s[ret] = '\0';
    }
	
    return (ret);
}

RECOMP_EXPORT const char *recomp_vsprintf_helper(const char *fmt, va_list args) {
    // 1MB buffer for string formatting... if that's not enough then
    // you have bigger problems...
    static char buffer[1024 * 1024];
    
    vsprintf(buffer, fmt, args);

    return buffer;
}

RECOMP_EXPORT const char *recomp_sprintf_helper(const char *fmt, ...) {
    va_list args;
	va_start(args, fmt);

    const char *str = recomp_vsprintf_helper(fmt, args);

    va_end(args);

    return str;
}
