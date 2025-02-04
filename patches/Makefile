TARGET = patches.elf

CC      = clang
LD      = ld.lld

BUILD_DIR = build

CFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
			-fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset \
			-Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable -Wno-missing-braces -Wno-unsupported-floating-point-opt
CPPFLAGS := -nostdinc -D_LANGUAGE_C -DMIPS -I include -I dummy_headers -I ../lib/dinosaur-planet/include -I ../lib/dinosaur-planet/src -I ../lib/dino-recomp-syms/include -I../lib/rt64/include
LDFLAGS  := -nostdlib -T patches.ld -T syms.ld -Map $(BUILD_DIR)/patches.map --unresolved-symbols=ignore-all --emit-relocs

C_SRCS := $(wildcard src/*.c)
C_SRCS += $(wildcard src/builtin_dbgui/*.c)
C_OBJS := $(C_SRCS:%.c=$(BUILD_DIR)/%.o)
C_DEPS := $(C_SRCS:%.c=$(BUILD_DIR)/%.d)

$(BUILD_DIR)/$(TARGET): $(C_OBJS) patches.ld syms.ld
	$(LD) $(C_OBJS) $(LDFLAGS) -o $@

$(C_OBJS): $(BUILD_DIR)/%.o : %.c
	mkdir -p ${dir $@}
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
	rm -rf $(BUILD_DIR)

-include $(C_DEPS)

.PHONY: clean
