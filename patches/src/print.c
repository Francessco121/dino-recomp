#include "stdarg.h"

#include "patches.h"
#include "recomp_funcs.h"

extern int _Printf(void*, void*, const char* fmt, va_list args);

// Hook up game printf to recomp logging
RECOMP_PATCH void* proutSyncPrintf(void* dst, const char* buf, s32 size) {
    recomp_puts(buf, size);
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
