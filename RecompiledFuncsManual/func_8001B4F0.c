#include "recomp.h"
#include "disable_warnings.h"

void func_8001B4F0(uint8_t* rdram, recomp_context* ctx) {
    uint64_t hi = 0, lo = 0, result = 0;
    unsigned int rounding_mode = DEFAULT_ROUNDING_MODE;
    int c1cs = 0; 
    // lui         $at, 0x8009
    ctx->r1 = S32(0X8009 << 16);
    // sw          $a0, -0x152C($at)
    MEM_W(-0X152C, ctx->r1) = ctx->r4;
    // lw          $a0, 0x0($a0)
    ctx->r4 = MEM_W(0X0, ctx->r4);
    // addiu       $sp, $sp, -0x28
    ctx->r29 = ADD32(ctx->r29, -0X28);
    // sw          $ra, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r31;
    // sw          $s0, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->r16;
    // sw          $s1, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->r17;
    // sw          $s2, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->r18;
    // sw          $s3, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->r19;
    // sw          $s4, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->r20;
    // sw          $s5, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->r21;
    // sw          $s6, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->r22;
    // sw          $s7, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->r23;
    // addiu       $sp, $sp, -0x38
    ctx->r29 = ADD32(ctx->r29, -0X38);
    // lw          $t9, 0x7C($sp)
    ctx->r25 = MEM_W(0X7C, ctx->r29);
    // lui         $t1, 0x8009
    ctx->r9 = S32(0X8009 << 16);
    // swc1        $f30, 0x2C($sp)
    MEM_W(0X2C, ctx->r29) = ctx->f30.u32l;
    // addiu       $t1, $t1, -0x1524
    ctx->r9 = ADD32(ctx->r9, -0X1524);
    // sw          $a0, -0x1530($at)
    MEM_W(-0X1530, ctx->r1) = ctx->r4;
    // lui         $at, 0x8009
    ctx->r1 = S32(0X8009 << 16);
    // mtc1        $zero, $f30
    ctx->f30.u32l = 0;
    // addiu       $t1, $t1, 0x1C
    ctx->r9 = ADD32(ctx->r9, 0X1C);
    // andi        $s1, $t9, 0x40
    ctx->r17 = ctx->r25 & 0X40;
    // sw          $ra, 0x0($sp)
    MEM_W(0X0, ctx->r29) = ctx->r31;
    // swc1        $f20, 0x4($sp)
    MEM_W(0X4, ctx->r29) = ctx->f20.u32l;
    // swc1        $f21, 0x8($sp)
    MEM_W(0X8, ctx->r29) = ctx->f_odd[(21 - 1) * 2];
    // swc1        $f22, 0xC($sp)
    MEM_W(0XC, ctx->r29) = ctx->f22.u32l;
    // swc1        $f23, 0x10($sp)
    MEM_W(0X10, ctx->r29) = ctx->f_odd[(23 - 1) * 2];
    // swc1        $f24, 0x14($sp)
    MEM_W(0X14, ctx->r29) = ctx->f24.u32l;
    // swc1        $f25, 0x18($sp)
    MEM_W(0X18, ctx->r29) = ctx->f_odd[(25 - 1) * 2];
    // swc1        $f26, 0x1C($sp)
    MEM_W(0X1C, ctx->r29) = ctx->f26.u32l;
    // swc1        $f27, 0x20($sp)
    MEM_W(0X20, ctx->r29) = ctx->f_odd[(27 - 1) * 2];
    // swc1        $f28, 0x24($sp)
    MEM_W(0X24, ctx->r29) = ctx->f28.u32l;
    // swc1        $f29, 0x28($sp)
    MEM_W(0X28, ctx->r29) = ctx->f_odd[(29 - 1) * 2];
    // swc1        $f31, 0x30($sp)
    MEM_W(0X30, ctx->r29) = ctx->f_odd[(31 - 1) * 2];
    // sw          $a3, -0x1528($at)
    MEM_W(-0X1528, ctx->r1) = ctx->r7;
    // bne         $s1, $zero, L_8001B63C
    if (ctx->r17 != 0) {
        // addiu       $t7, $t1, 0x6
        ctx->r15 = ADD32(ctx->r9, 0X6);
        goto L_8001B63C;
    }
    // addiu       $t7, $t1, 0x6
    ctx->r15 = ADD32(ctx->r9, 0X6);
    // lw          $s1, 0x7C($sp)
    ctx->r17 = MEM_W(0X7C, ctx->r29);
    // andi        $s1, $s1, 0x1
    ctx->r17 = ctx->r17 & 0X1;
    // beql        $s1, $zero, L_8001B5A8
    if (ctx->r17 == 0) {
        // mtc1        $t1, $f27
        ctx->f_odd[(27 - 1) * 2] = ctx->r9;
        goto L_8001B5A8;
    }
    goto skip_0;
    // mtc1        $t1, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r9;
    skip_0:
    // or          $t1, $a0, $zero
    ctx->r9 = ctx->r4 | 0;
    // b           L_8001B5D0
    // addiu       $t1, $t1, 0x1C
    ctx->r9 = ADD32(ctx->r9, 0X1C);
    goto L_8001B5D0;
    // addiu       $t1, $t1, 0x1C
    ctx->r9 = ADD32(ctx->r9, 0X1C);
    // mtc1        $t1, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r9;
L_8001B5A8:
    // lw          $a3, 0x34($a2)
    ctx->r7 = MEM_W(0X34, ctx->r6);
    // lw          $t4, 0x2C($a2)
    ctx->r12 = MEM_W(0X2C, ctx->r6);
    // lh          $s4, 0x4C($a2)
    ctx->r20 = MEM_H(0X4C, ctx->r6);
    // lwc1        $f4, 0x4($a2)
    ctx->f4.u32l = MEM_W(0X4, ctx->r6);
    // jal         0x8001BCF0
    // or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    func_8001BCF0(rdram, ctx);
    goto after_0;
    // or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    after_0:
    // lh          $t3, 0x58($a2)
    ctx->r11 = MEM_H(0X58, ctx->r6);
    // mfc1        $t1, $f27
    ctx->r9 = (int32_t)ctx->f_odd[(27 - 1) * 2];
    // blez        $t3, L_8001C1D8
    if (SIGNED(ctx->r11) <= 0) {
        // or          $t8, $t1, $zero
        ctx->r24 = ctx->r9 | 0;
        goto L_8001C1D8;
    }
    // or          $t8, $t1, $zero
    ctx->r24 = ctx->r9 | 0;
L_8001B5D0:
    // lw          $s1, 0x7C($sp)
    ctx->r17 = MEM_W(0X7C, ctx->r29);
    // andi        $s1, $s1, 0x2
    ctx->r17 = ctx->r17 & 0X2;
    // beql        $s1, $zero, L_8001B5F0
    if (ctx->r17 == 0) {
        // mtc1        $t1, $f27
        ctx->f_odd[(27 - 1) * 2] = ctx->r9;
        goto L_8001B5F0;
    }
    goto skip_1;
    // mtc1        $t1, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r9;
    skip_1:
    // or          $t7, $a0, $zero
    ctx->r15 = ctx->r4 | 0;
    // b           L_8001B610
    // addiu       $t7, $t7, 0x22
    ctx->r15 = ADD32(ctx->r15, 0X22);
    goto L_8001B610;
    // addiu       $t7, $t7, 0x22
    ctx->r15 = ADD32(ctx->r15, 0X22);
    // mtc1        $t1, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r9;
L_8001B5F0:
    // lw          $a3, 0x38($a2)
    ctx->r7 = MEM_W(0X38, ctx->r6);
    // lw          $t4, 0x30($a2)
    ctx->r12 = MEM_W(0X30, ctx->r6);
    // lh          $s4, 0x4E($a2)
    ctx->r20 = MEM_H(0X4E, ctx->r6);
    // lwc1        $f4, 0x8($a2)
    ctx->f4.u32l = MEM_W(0X8, ctx->r6);
    // jal         0x8001BCF0
    // or          $t5, $t7, $zero
    ctx->r13 = ctx->r15 | 0;
    func_8001BCF0(rdram, ctx);
    goto after_1;
    // or          $t5, $t7, $zero
    ctx->r13 = ctx->r15 | 0;
    after_1:
    // mfc1        $t1, $f27
    ctx->r9 = (int32_t)ctx->f_odd[(27 - 1) * 2];
    // nop

L_8001B610:
    // lh          $t6, 0x58($a2)
    ctx->r14 = MEM_H(0X58, ctx->r6);
    // lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    // mtc1        $t6, $f20
    ctx->f20.u32l = ctx->r14;
    // or          $t4, $t7, $zero
    ctx->r12 = ctx->r15 | 0;
    // cvt.s.w     $f20, $f20
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    ctx->f20.fl = CVT_S_W(ctx->f20.u32l);
    // mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // jal         0x8001B6F0
    // div.s       $f28, $f20, $f21
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f28.fl = DIV_S(ctx->f20.fl, ctx->f21.fl);
    func_8001B6F0(rdram, ctx);
    goto after_2;
    // div.s       $f28, $f20, $f21
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f28.fl = DIV_S(ctx->f20.fl, ctx->f21.fl);
    after_2:
    // j           L_8001C83C
    // nop

    goto L_8001C83C;
    // nop

L_8001B63C:
    // mtc1        $t1, $f27
    ctx->f_odd[(27 - 1) * 2] = ctx->r9;
    // lw          $a3, 0x34($a2)
    ctx->r7 = MEM_W(0X34, ctx->r6);
    // lw          $t4, 0x2C($a2)
    ctx->r12 = MEM_W(0X2C, ctx->r6);
    // lh          $s4, 0x4C($a2)
    ctx->r20 = MEM_H(0X4C, ctx->r6);
    // lwc1        $f28, 0x4($a2)
    ctx->f28.u32l = MEM_W(0X4, ctx->r6);
    // jal         0x8001BF70
    // or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    func_8001BF70(rdram, ctx);
    goto after_3;
    // or          $t5, $t1, $zero
    ctx->r13 = ctx->r9 | 0;
    after_3:
    // floor.w.s   $f4, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    ctx->f4.u32l = S32(floorf(ctx->f28.fl));
    // lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // mfc1        $t5, $f27
    ctx->r13 = (int32_t)ctx->f_odd[(27 - 1) * 2];
    // cvt.s.w     $f4, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    ctx->f4.fl = CVT_S_W(ctx->f4.u32l);
    // addiu       $s3, $zero, 0x4
    ctx->r19 = ADD32(0, 0X4);
    // or          $t4, $t7, $zero
    ctx->r12 = ctx->r15 | 0;
    // sw          $s3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r19;
    // sub.s       $f28, $f28, $f4
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f28.fl = ctx->f28.fl - ctx->f4.fl;
    // mul.s       $f21, $f21, $f28
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f21.fl = MUL_S(ctx->f21.fl, ctx->f28.fl);
    // cvt.w.s     $f4, $f21
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 21);
    ctx->f4.u32l = CVT_W_S(ctx->f21.fl);
    // mfc1        $t6, $f4
    ctx->r14 = (int32_t)ctx->f4.u32l;
    // jal         0x8001B6F0
    // nop

    func_8001B6F0(rdram, ctx);
    goto after_4;
    // nop

    after_4:
    // lui         $t1, 0x8009
    ctx->r9 = S32(0X8009 << 16);
    // addiu       $t1, $t1, -0x1524
    ctx->r9 = ADD32(ctx->r9, -0X1524);
    // addiu       $t1, $t1, 0x1C
    ctx->r9 = ADD32(ctx->r9, 0X1C);
    // addiu       $t7, $t1, 0x6
    ctx->r15 = ADD32(ctx->r9, 0X6);
    // lw          $a3, 0x38($a2)
    ctx->r7 = MEM_W(0X38, ctx->r6);
    // lw          $t4, 0x30($a2)
    ctx->r12 = MEM_W(0X30, ctx->r6);
    // lh          $s4, 0x4E($a2)
    ctx->r20 = MEM_H(0X4E, ctx->r6);
    // lwc1        $f4, 0x8($a2)
    ctx->f4.u32l = MEM_W(0X8, ctx->r6);
    // jal         0x8001BCF0
    // or          $t5, $t7, $zero
    ctx->r13 = ctx->r15 | 0;
    func_8001BCF0(rdram, ctx);
    goto after_5;
    // or          $t5, $t7, $zero
    ctx->r13 = ctx->r15 | 0;
    after_5:
    // lh          $t6, 0x58($a2)
    ctx->r14 = MEM_H(0X58, ctx->r6);
    // lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // addiu       $s3, $zero, 0x1
    ctx->r19 = ADD32(0, 0X1);
    // mtc1        $t6, $f20
    ctx->f20.u32l = ctx->r14;
    // or          $t5, $a0, $zero
    ctx->r13 = ctx->r4 | 0;
    // sw          $s3, 0x7C($sp)
    MEM_W(0X7C, ctx->r29) = ctx->r19;
    // cvt.s.w     $f20, $f20
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    ctx->f20.fl = CVT_S_W(ctx->f20.u32l);
    // mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // addiu       $t5, $t5, 0x1C
    ctx->r13 = ADD32(ctx->r13, 0X1C);
    // or          $t4, $t7, $zero
    ctx->r12 = ctx->r15 | 0;
    // jal         0x8001B6F0
    // div.s       $f28, $f20, $f21
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f28.fl = DIV_S(ctx->f20.fl, ctx->f21.fl);
    func_8001B6F0(rdram, ctx);
    goto after_6;
    // div.s       $f28, $f20, $f21
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f28.fl = DIV_S(ctx->f20.fl, ctx->f21.fl);
    after_6:
    // j           L_8001C83C
    // nop

    goto L_8001C83C;
    // nop

    // lw          $s3, 0x7C($sp)
    ctx->r19 = MEM_W(0X7C, ctx->r29);
    // or          $t9, $ra, $zero
    ctx->r25 = ctx->r31 | 0;
    // andi        $t2, $s3, 0x20
    ctx->r10 = ctx->r19 & 0X20;
    // beq         $t2, $zero, L_8001B728
    if (ctx->r10 == 0) {
        // nop
    
        goto L_8001B728;
    }
    // nop

    // lui         $t1, 0x8009
    ctx->r9 = S32(0X8009 << 16);
    // lh          $t1, 0x3DC($t1)
    ctx->r9 = MEM_H(0X3DC, ctx->r9);
    // sh          $t1, 0x0($t4)
    MEM_H(0X0, ctx->r12) = ctx->r9;
    // lui         $t1, 0x8009
    ctx->r9 = S32(0X8009 << 16);
    // lh          $t1, 0x3DE($t1)
    ctx->r9 = MEM_H(0X3DE, ctx->r9);
    // sh          $t1, 0x2($t4)
    MEM_H(0X2, ctx->r12) = ctx->r9;
    // lui         $t1, 0x8009
    ctx->r9 = S32(0X8009 << 16);
    // lh          $t1, 0x3E0($t1)
    ctx->r9 = MEM_H(0X3E0, ctx->r9);
    // sh          $t1, 0x4($t4)
    MEM_H(0X4, ctx->r12) = ctx->r9;
L_8001B728:
    // lui         $t0, 0x8009
    ctx->r8 = S32(0X8009 << 16);
    // andi        $t2, $s3, 0xC
    ctx->r10 = ctx->r19 & 0XC;
    // or          $v0, $t5, $zero
    ctx->r2 = ctx->r13 | 0;
    // lw          $t0, -0x1528($t0)
    ctx->r8 = MEM_W(-0X1528, ctx->r8);
    // beq         $t2, $zero, L_8001B754
    if (ctx->r10 == 0) {
        // lw          $t1, 0x70($sp)
        ctx->r9 = MEM_W(0X70, ctx->r29);
        goto L_8001B754;
    }
    // lw          $t1, 0x70($sp)
    ctx->r9 = MEM_W(0X70, ctx->r29);
    // or          $v0, $a0, $zero
    ctx->r2 = ctx->r4 | 0;
    // andi        $t2, $t2, 0x8
    ctx->r10 = ctx->r10 & 0X8;
    // beq         $t2, $zero, L_8001B754
    if (ctx->r10 == 0) {
        // addiu       $v0, $v0, 0x1C
        ctx->r2 = ADD32(ctx->r2, 0X1C);
        goto L_8001B754;
    }
    // addiu       $v0, $v0, 0x1C
    ctx->r2 = ADD32(ctx->r2, 0X1C);
    // addiu       $v0, $v0, 0x6
    ctx->r2 = ADD32(ctx->r2, 0X6);
L_8001B754:
    // lui         $at, 0x3F80
    ctx->r1 = S32(0X3F80 << 16);
    // mtc1        $at, $f31
    ctx->f_odd[(31 - 1) * 2] = ctx->r1;
    // lui         $at, 0x4000
    ctx->r1 = S32(0X4000 << 16);
    // sll         $t2, $t1, 4
    ctx->r10 = S32(ctx->r9) << 4;
    // mtc1        $at, $f29
    ctx->f_odd[(29 - 1) * 2] = ctx->r1;
    // addiu       $s6, $zero, 0x800
    ctx->r22 = ADD32(0, 0X800);
    // addiu       $t3, $zero, 0x7FC
    ctx->r11 = ADD32(0, 0X7FC);
    // addu        $s4, $t2, $t0
    ctx->r20 = ADD32(ctx->r10, ctx->r8);
    // sub.s       $f27, $f31, $f28
    CHECK_FR(ctx, 27);
    CHECK_FR(ctx, 31);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f31.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f27.fl = ctx->f31.fl - ctx->f28.fl;
L_8001B778:
    // lbu         $t2, 0x3($t0)
    ctx->r10 = MEM_BU(0X3, ctx->r8);
    // sll         $s1, $t2, 6
    ctx->r17 = S32(ctx->r10) << 6;
    // addu        $t8, $t4, $s1
    ctx->r24 = ADD32(ctx->r12, ctx->r17);
    // lbu         $t2, 0x2($t0)
    ctx->r10 = MEM_BU(0X2, ctx->r8);
    // sll         $t7, $t2, 6
    ctx->r15 = S32(ctx->r10) << 6;
    // addu        $s0, $t5, $t7
    ctx->r16 = ADD32(ctx->r13, ctx->r15);
    // addu        $v1, $v0, $t7
    ctx->r3 = ADD32(ctx->r2, ctx->r15);
    // andi        $t2, $s3, 0xF
    ctx->r10 = ctx->r19 & 0XF;
    // beq         $t2, $zero, L_8001B7D4
    if (ctx->r10 == 0) {
        // addiu       $t1, $zero, 0x2
        ctx->r9 = ADD32(0, 0X2);
        goto L_8001B7D4;
    }
    // addiu       $t1, $zero, 0x2
    ctx->r9 = ADD32(0, 0X2);
    // lbu         $t2, 0x1($t0)
    ctx->r10 = MEM_BU(0X1, ctx->r8);
    // andi        $t2, $t2, 0x7F
    ctx->r10 = ctx->r10 & 0X7F;
    // sll         $t7, $t2, 6
    ctx->r15 = S32(ctx->r10) << 6;
    // addu        $v1, $v0, $t7
    ctx->r3 = ADD32(ctx->r2, ctx->r15);
    // andi        $t2, $s3, 0x3
    ctx->r10 = ctx->r19 & 0X3;
    // beq         $t2, $zero, L_8001B7D4
    if (ctx->r10 == 0) {
        // nop
    
        goto L_8001B7D4;
    }
    // nop

    // andi        $t2, $t2, 0x1
    ctx->r10 = ctx->r10 & 0X1;
    // beq         $t2, $zero, L_8001B7D0
    if (ctx->r10 == 0) {
        // nop
    
        goto L_8001B7D0;
    }
    // nop

    // b           L_8001B7D4
    // addu        $s0, $t5, $t7
    ctx->r16 = ADD32(ctx->r13, ctx->r15);
    goto L_8001B7D4;
    // addu        $s0, $t5, $t7
    ctx->r16 = ADD32(ctx->r13, ctx->r15);
L_8001B7D0:
    // addu        $t8, $t4, $t7
    ctx->r24 = ADD32(ctx->r12, ctx->r15);
L_8001B7D4:
    // lhu         $t2, 0xC($t8)
    ctx->r10 = MEM_HU(0XC, ctx->r24);
    // bne         $t2, $zero, L_8001B7E4
    if (ctx->r10 != 0) {
        // nop
    
        goto L_8001B7E4;
    }
    // nop

    // ori         $t2, $t2, 0x400
    ctx->r10 = ctx->r10 | 0X400;
L_8001B7E4:
    // lhu         $t7, 0xC($s0)
    ctx->r15 = MEM_HU(0XC, ctx->r16);
    // bne         $t7, $zero, L_8001B7F4
    if (ctx->r15 != 0) {
        // nop
    
        goto L_8001B7F4;
    }
    // nop

    // ori         $t7, $t7, 0x400
    ctx->r15 = ctx->r15 | 0X400;
L_8001B7F4:
    // subu        $t2, $t2, $t7
    ctx->r10 = SUB32(ctx->r10, ctx->r15);
    // mult        $t2, $t6
    result = S64(S32(ctx->r10)) * S64(S32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // mflo        $t2
    ctx->r10 = lo;
    // sra         $t2, $t2, 10
    ctx->r10 = S32(ctx->r10) >> 10;
    // addu        $t2, $t2, $t7
    ctx->r10 = ADD32(ctx->r10, ctx->r15);
    // sh          $t2, 0xC($v1)
    MEM_H(0XC, ctx->r3) = ctx->r10;
    // lh          $t7, 0x18($s0)
    ctx->r15 = MEM_H(0X18, ctx->r16);
    // addiu       $s0, $s0, 0x2
    ctx->r16 = ADD32(ctx->r16, 0X2);
    // andi        $t2, $s3, 0x10
    ctx->r10 = ctx->r19 & 0X10;
    // bne         $t2, $zero, L_8001B838
    if (ctx->r10 != 0) {
        // addiu       $t8, $t8, 0x2
        ctx->r24 = ADD32(ctx->r24, 0X2);
        goto L_8001B838;
    }
    // addiu       $t8, $t8, 0x2
    ctx->r24 = ADD32(ctx->r24, 0X2);
    // lh          $t2, 0x16($t8)
    ctx->r10 = MEM_H(0X16, ctx->r24);
    // subu        $t2, $t2, $t7
    ctx->r10 = SUB32(ctx->r10, ctx->r15);
    // mult        $t2, $t6
    result = S64(S32(ctx->r10)) * S64(S32(ctx->r14)); lo = S32(result >> 0); hi = S32(result >> 32);
    // mflo        $t2
    ctx->r10 = lo;
    // sra         $t2, $t2, 10
    ctx->r10 = S32(ctx->r10) >> 10;
    // addu        $t7, $t7, $t2
    ctx->r15 = ADD32(ctx->r15, ctx->r10);
L_8001B838:
    // sh          $t7, 0x18($v1)
    MEM_H(0X18, ctx->r3) = ctx->r15;
    // addiu       $v1, $v1, 0x2
    ctx->r3 = ADD32(ctx->r3, 0X2);
    // bne         $t1, $zero, L_8001B7D4
    if (ctx->r9 != 0) {
        // addiu       $t1, $t1, -0x1
        ctx->r9 = ADD32(ctx->r9, -0X1);
        goto L_8001B7D4;
    }
    // addiu       $t1, $t1, -0x1
    ctx->r9 = ADD32(ctx->r9, -0X1);
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // bne         $t0, $s4, L_8001B778
    if (ctx->r8 != ctx->r20) {
        // nop
    
        goto L_8001B778;
    }
    // nop

    // lui         $s2, 0x8009
    ctx->r18 = S32(0X8009 << 16);
    // lui         $t0, 0x8009
    ctx->r8 = S32(0X8009 << 16);
    // addiu       $s2, $s2, 0x450
    ctx->r18 = ADD32(ctx->r18, 0X450);
    // lw          $t1, 0x70($sp)
    ctx->r9 = MEM_W(0X70, ctx->r29);
    // lw          $t0, -0x1528($t0)
    ctx->r8 = MEM_W(-0X1528, ctx->r8);
    // lw          $s7, 0x78($sp)
    ctx->r23 = MEM_W(0X78, ctx->r29);
L_8001B86C:
    // lbu         $s0, 0x2($t0)
    ctx->r16 = MEM_BU(0X2, ctx->r8);
    // sll         $s1, $s0, 6
    ctx->r17 = S32(ctx->r16) << 6;
    // addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // lw          $t2, 0x7C($sp)
    ctx->r10 = MEM_W(0X7C, ctx->r29);
    // andi        $t7, $t2, 0x1
    ctx->r15 = ctx->r10 & 0X1;
    // beq         $t7, $zero, L_8001B8B0
    if (ctx->r15 == 0) {
        // nop
    
        goto L_8001B8B0;
    }
    // nop

    // lbu         $s0, 0x1($t0)
    ctx->r16 = MEM_BU(0X1, ctx->r8);
    // andi        $s0, $s0, 0x7F
    ctx->r16 = ctx->r16 & 0X7F;
    // sll         $s1, $s0, 6
    ctx->r17 = S32(ctx->r16) << 6;
    // addu        $t6, $s1, $a0
    ctx->r14 = ADD32(ctx->r17, ctx->r4);
    // addu        $t8, $v0, $s1
    ctx->r24 = ADD32(ctx->r2, ctx->r17);
    // lwc1        $f20, 0x0($t6)
    ctx->f20.u32l = MEM_W(0X0, ctx->r14);
    // lwc1        $f21, 0x4($t6)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X4, ctx->r14);
    // lwc1        $f25, 0x8($t6)
    ctx->f_odd[(25 - 1) * 2] = MEM_W(0X8, ctx->r14);
    // b           L_8001B8D8
    // lwc1        $f26, 0xC($t6)
    ctx->f26.u32l = MEM_W(0XC, ctx->r14);
    goto L_8001B8D8;
    // lwc1        $f26, 0xC($t6)
    ctx->f26.u32l = MEM_W(0XC, ctx->r14);
L_8001B8B0:
    // jal         0x8001BC00
    // addu        $s0, $t5, $s1
    ctx->r16 = ADD32(ctx->r13, ctx->r17);
    func_8001BC00(rdram, ctx);
    goto after_7;
    // addu        $s0, $t5, $s1
    ctx->r16 = ADD32(ctx->r13, ctx->r17);
    after_7:
    // mul.s       $f14, $f7, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f14.fl = MUL_S(ctx->f7.fl, ctx->f18.fl);
    // add.s       $f20, $f10, $f11
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 11);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f11.fl);
    ctx->f20.fl = ctx->f10.fl + ctx->f11.fl;
    // mul.s       $f15, $f8, $f19
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f15.fl = MUL_S(ctx->f8.fl, ctx->f19.fl);
    // sub.s       $f21, $f12, $f13
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 13);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f13.fl);
    ctx->f21.fl = ctx->f12.fl - ctx->f13.fl;
    // mul.s       $f16, $f6, $f19
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f19.fl);
    // add.s       $f25, $f14, $f15
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 15);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f15.fl);
    ctx->f25.fl = ctx->f14.fl + ctx->f15.fl;
    // mul.s       $f17, $f9, $f18
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f9.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f17.fl = MUL_S(ctx->f9.fl, ctx->f18.fl);
    // sub.s       $f26, $f16, $f17
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 17);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f17.fl);
    ctx->f26.fl = ctx->f16.fl - ctx->f17.fl;
L_8001B8D8:
    // lbu         $s0, 0x3($t0)
    ctx->r16 = MEM_BU(0X3, ctx->r8);
    // sll         $s1, $s0, 6
    ctx->r17 = S32(ctx->r16) << 6;
    // lw          $t2, 0x7C($sp)
    ctx->r10 = MEM_W(0X7C, ctx->r29);
    // andi        $t7, $t2, 0x2
    ctx->r15 = ctx->r10 & 0X2;
    // beq         $t7, $zero, L_8001B918
    if (ctx->r15 == 0) {
        // nop
    
        goto L_8001B918;
    }
    // nop

    // lbu         $s0, 0x1($t0)
    ctx->r16 = MEM_BU(0X1, ctx->r8);
    // andi        $s0, $s0, 0x7F
    ctx->r16 = ctx->r16 & 0X7F;
    // sll         $s1, $s0, 6
    ctx->r17 = S32(ctx->r16) << 6;
    // addu        $t6, $s1, $a0
    ctx->r14 = ADD32(ctx->r17, ctx->r4);
    // addiu       $t6, $t6, 0x10
    ctx->r14 = ADD32(ctx->r14, 0X10);
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
    // lwc1        $f5, 0x4($t6)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X4, ctx->r14);
    // lwc1        $f6, 0x8($t6)
    ctx->f6.u32l = MEM_W(0X8, ctx->r14);
    // b           L_8001B940
    // lwc1        $f7, 0xC($t6)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0XC, ctx->r14);
    goto L_8001B940;
    // lwc1        $f7, 0xC($t6)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0XC, ctx->r14);
L_8001B918:
    // jal         0x8001BC00
    // addu        $s0, $t4, $s1
    ctx->r16 = ADD32(ctx->r12, ctx->r17);
    func_8001BC00(rdram, ctx);
    goto after_8;
    // addu        $s0, $t4, $s1
    ctx->r16 = ADD32(ctx->r12, ctx->r17);
    after_8:
    // mul.s       $f14, $f7, $f18
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f14.fl = MUL_S(ctx->f7.fl, ctx->f18.fl);
    // add.s       $f4, $f10, $f11
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 11);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f11.fl);
    ctx->f4.fl = ctx->f10.fl + ctx->f11.fl;
    // mul.s       $f15, $f8, $f19
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f15.fl = MUL_S(ctx->f8.fl, ctx->f19.fl);
    // sub.s       $f5, $f12, $f13
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 13);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f13.fl);
    ctx->f5.fl = ctx->f12.fl - ctx->f13.fl;
    // mul.s       $f16, $f6, $f19
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f19.fl);
    // add.s       $f6, $f14, $f15
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 15);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f15.fl);
    ctx->f6.fl = ctx->f14.fl + ctx->f15.fl;
    // mul.s       $f17, $f9, $f18
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f9.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f17.fl = MUL_S(ctx->f9.fl, ctx->f18.fl);
    // sub.s       $f7, $f16, $f17
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 17);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f17.fl);
    ctx->f7.fl = ctx->f16.fl - ctx->f17.fl;
L_8001B940:
    // mul.s       $f10, $f20, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f10.fl = MUL_S(ctx->f20.fl, ctx->f4.fl);
    // nop

    // mul.s       $f11, $f21, $f5
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f11.fl = MUL_S(ctx->f21.fl, ctx->f5.fl);
    // nop

    // mul.s       $f12, $f25, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f12.fl = MUL_S(ctx->f25.fl, ctx->f6.fl);
    // add.s       $f10, $f10, $f11
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 11);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f11.fl);
    ctx->f10.fl = ctx->f10.fl + ctx->f11.fl;
    // mul.s       $f13, $f26, $f7
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f13.fl = MUL_S(ctx->f26.fl, ctx->f7.fl);
    // add.s       $f10, $f10, $f12
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 12);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f12.fl);
    ctx->f10.fl = ctx->f10.fl + ctx->f12.fl;
    // mul.s       $f20, $f20, $f27
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f27.fl);
    // add.s       $f10, $f10, $f13
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 13);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f13.fl);
    ctx->f10.fl = ctx->f10.fl + ctx->f13.fl;
    // mul.s       $f21, $f21, $f27
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f21.fl = MUL_S(ctx->f21.fl, ctx->f27.fl);
    // c.olt.s     $f10, $f30
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 30);
    c1cs = ctx->f10.fl < ctx->f30.fl;
    // mul.s       $f25, $f25, $f27
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f25.fl = MUL_S(ctx->f25.fl, ctx->f27.fl);
    // bc1f        L_8001B98C
    if (!c1cs) {
        // nop
    
        goto L_8001B98C;
    }
    // nop

    // sub.s       $f4, $f30, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f4.fl = ctx->f30.fl - ctx->f4.fl;
    // sub.s       $f5, $f30, $f5
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f5.fl = ctx->f30.fl - ctx->f5.fl;
    // sub.s       $f6, $f30, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f6.fl = ctx->f30.fl - ctx->f6.fl;
    // sub.s       $f7, $f30, $f7
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f7.fl = ctx->f30.fl - ctx->f7.fl;
L_8001B98C:
    // mul.s       $f26, $f26, $f27
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f26.fl = MUL_S(ctx->f26.fl, ctx->f27.fl);
    // nop

    // mul.s       $f4, $f4, $f28
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f4.fl = MUL_S(ctx->f4.fl, ctx->f28.fl);
    // lb          $s4, 0x1($t0)
    ctx->r20 = MEM_B(0X1, ctx->r8);
    // and         $s4, $s4, $s7
    ctx->r20 = ctx->r20 & ctx->r23;
    // bgez        $s4, L_8001B9B8
    if (SIGNED(ctx->r20) >= 0) {
        // nop
    
        goto L_8001B9B8;
    }
    // nop

    // addiu       $t1, $t1, -0x1
    ctx->r9 = ADD32(ctx->r9, -0X1);
    // bne         $t1, $zero, L_8001B86C
    if (ctx->r9 != 0) {
        // addiu       $t0, $t0, 0x10
        ctx->r8 = ADD32(ctx->r8, 0X10);
        goto L_8001B86C;
    }
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // j           L_8001C5A0
    // andi        $s4, $s4, 0x7F
    ctx->r20 = ctx->r20 & 0X7F;
    goto L_8001C5A0;
L_8001B9B8:
    // andi        $s4, $s4, 0x7F
    ctx->r20 = ctx->r20 & 0X7F;
    // mul.s       $f5, $f5, $f28
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f5.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f5.fl = MUL_S(ctx->f5.fl, ctx->f28.fl);
    // add.s       $f10, $f20, $f4
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f10.fl = ctx->f20.fl + ctx->f4.fl;
    // mul.s       $f6, $f6, $f28
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f28.fl);
    // add.s       $f11, $f21, $f5
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f11.fl = ctx->f21.fl + ctx->f5.fl;
    // mul.s       $f7, $f7, $f28
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 28);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f28.fl);
    ctx->f7.fl = MUL_S(ctx->f7.fl, ctx->f28.fl);
    // add.s       $f12, $f25, $f6
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f12.fl = ctx->f25.fl + ctx->f6.fl;
    // mul.s       $f0, $f11, $f29
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f11.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f0.fl = MUL_S(ctx->f11.fl, ctx->f29.fl);
    // add.s       $f13, $f26, $f7
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f13.fl = ctx->f26.fl + ctx->f7.fl;
    // lw          $t2, 0x7C($sp)
    ctx->r10 = MEM_W(0X7C, ctx->r29);
    // andi        $s1, $t2, 0xC
    ctx->r17 = ctx->r10 & 0XC;
    // beq         $s1, $zero, L_8001BA30
    if (ctx->r17 == 0) {
        // nop
    
        goto L_8001BA30;
    }
    // nop

    // lbu         $s0, 0x1($t0)
    ctx->r16 = MEM_BU(0X1, ctx->r8);
    // andi        $t2, $t2, 0x8
    ctx->r10 = ctx->r10 & 0X8;
    // andi        $s0, $s0, 0x7F
    ctx->r16 = ctx->r16 & 0X7F;
    // sll         $s1, $s0, 6
    ctx->r17 = S32(ctx->r16) << 6;
    // beq         $t2, $zero, L_8001BA08
    if (ctx->r10 == 0) {
        // or          $s0, $a0, $zero
        ctx->r16 = ctx->r4 | 0;
        goto L_8001BA08;
    }
    // or          $s0, $a0, $zero
    ctx->r16 = ctx->r4 | 0;
    // addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
L_8001BA08:
    // addu        $s1, $s1, $s0
    ctx->r17 = ADD32(ctx->r17, ctx->r16);
    // swc1        $f10, 0x0($s1)
    MEM_W(0X0, ctx->r17) = ctx->f10.u32l;
    // swc1        $f11, 0x4($s1)
    MEM_W(0X4, ctx->r17) = ctx->f_odd[(11 - 1) * 2];
    // swc1        $f12, 0x8($s1)
    MEM_W(0X8, ctx->r17) = ctx->f12.u32l;
    // swc1        $f13, 0xC($s1)
    MEM_W(0XC, ctx->r17) = ctx->f_odd[(13 - 1) * 2];
    // addiu       $t1, $t1, -0x1
    ctx->r9 = ADD32(ctx->r9, -0X1);
    // bne         $t1, $zero, L_8001B86C
    if (ctx->r9 != 0) {
        // addiu       $t0, $t0, 0x10
        ctx->r8 = ADD32(ctx->r8, 0X10);
        goto L_8001B86C;
    }
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // jr          $ra
    // nop

    return;
    // nop

L_8001BA30:
    // mul.s       $f1, $f12, $f29
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f1.fl = MUL_S(ctx->f12.fl, ctx->f29.fl);
    // sll         $s4, $s4, 6
    ctx->r20 = S32(ctx->r20) << 6;
    // lui         $t7, 0x8009
    ctx->r15 = S32(0X8009 << 16);
    // lw          $t7, -0x1530($t7)
    ctx->r15 = MEM_W(-0X1530, ctx->r15);
    // addu        $t7, $t7, $s4
    ctx->r15 = ADD32(ctx->r15, ctx->r20);
    // lui         $at, 0x3D00
    ctx->r1 = S32(0X3D00 << 16);
    // mtc1        $at, $f2
    ctx->f2.u32l = ctx->r1;
    // lh          $t6, 0x18($t8)
    ctx->r14 = MEM_H(0X18, ctx->r24);
    // mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // lwc1        $f7, 0x4($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0X4, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f6, $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // add.s       $f3, $f6, $f7
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f3.fl = ctx->f6.fl + ctx->f7.fl;
    // lh          $t6, 0x1A($t8)
    ctx->r14 = MEM_H(0X1A, ctx->r24);
    // mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // lwc1        $f7, 0x8($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0X8, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f8, $f6, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f8.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // add.s       $f8, $f8, $f7
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f8.fl = ctx->f8.fl + ctx->f7.fl;
    // lh          $t6, 0x1C($t8)
    ctx->r14 = MEM_H(0X1C, ctx->r24);
    // mtc1        $t6, $f6
    ctx->f6.u32l = ctx->r14;
    // lwc1        $f7, 0xC($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0XC, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f6, $f6, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f2.fl);
    // lhu         $t2, 0xC($t8)
    ctx->r10 = MEM_HU(0XC, ctx->r24);
    // lhu         $t6, 0xE($t8)
    ctx->r14 = MEM_HU(0XE, ctx->r24);
    // lhu         $s0, 0x10($t8)
    ctx->r16 = MEM_HU(0X10, ctx->r24);
    // swc1        $f3, 0x30($t7)
    MEM_W(0X30, ctx->r15) = ctx->f_odd[(3 - 1) * 2];
    // mul.s       $f2, $f13, $f29
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f13.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f2.fl = MUL_S(ctx->f13.fl, ctx->f29.fl);
    // add.s       $f6, $f6, $f7
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f6.fl = ctx->f6.fl + ctx->f7.fl;
    // mul.s       $f3, $f10, $f0
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f3.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // swc1        $f6, 0x38($t7)
    MEM_W(0X38, ctx->r15) = ctx->f6.u32l;
    // mul.s       $f4, $f10, $f1
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f4.fl = MUL_S(ctx->f10.fl, ctx->f1.fl);
    // swc1        $f8, 0x34($t7)
    MEM_W(0X34, ctx->r15) = ctx->f8.u32l;
    // mul.s       $f5, $f10, $f2
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f5.fl = MUL_S(ctx->f10.fl, ctx->f2.fl);
    // nop

    // mul.s       $f6, $f11, $f0
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f11.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f6.fl = MUL_S(ctx->f11.fl, ctx->f0.fl);
    // nop

    // mul.s       $f7, $f11, $f1
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f11.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f7.fl = MUL_S(ctx->f11.fl, ctx->f1.fl);
    // nop

    // mul.s       $f8, $f11, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f11.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f8.fl = MUL_S(ctx->f11.fl, ctx->f2.fl);
    // add.s       $f20, $f7, $f5
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f20.fl = ctx->f7.fl + ctx->f5.fl;
    // mul.s       $f17, $f13, $f2
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f13.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f17.fl = MUL_S(ctx->f13.fl, ctx->f2.fl);
    // sub.s       $f21, $f8, $f4
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f21.fl = ctx->f8.fl - ctx->f4.fl;
    // mul.s       $f15, $f12, $f1
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f15.fl = MUL_S(ctx->f12.fl, ctx->f1.fl);
    // add.s       $f25, $f8, $f4
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f25.fl = ctx->f8.fl + ctx->f4.fl;
    // mul.s       $f16, $f12, $f2
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f16.fl = MUL_S(ctx->f12.fl, ctx->f2.fl);
    // add.s       $f19, $f15, $f17
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 17);
    NAN_CHECK(ctx->f15.fl); NAN_CHECK(ctx->f17.fl);
    ctx->f19.fl = ctx->f15.fl + ctx->f17.fl;
    // sub.s       $f19, $f31, $f19
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 31);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f31.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f19.fl = ctx->f31.fl - ctx->f19.fl;
    // sub.s       $f26, $f16, $f3
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f26.fl = ctx->f16.fl - ctx->f3.fl;
    // add.s       $f10, $f6, $f15
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 15);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f15.fl);
    ctx->f10.fl = ctx->f6.fl + ctx->f15.fl;
    // sub.s       $f10, $f31, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 31);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f31.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f10.fl = ctx->f31.fl - ctx->f10.fl;
    // add.s       $f4, $f16, $f3
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f4.fl = ctx->f16.fl + ctx->f3.fl;
    // sub.s       $f2, $f7, $f5
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f2.fl = ctx->f7.fl - ctx->f5.fl;
    // add.s       $f3, $f6, $f17
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 17);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f17.fl);
    ctx->f3.fl = ctx->f6.fl + ctx->f17.fl;
    // sub.s       $f3, $f31, $f3
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 31);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f31.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f3.fl = ctx->f31.fl - ctx->f3.fl;
    // lui         $at, 0x3A80
    ctx->r1 = S32(0X3A80 << 16);
    // mtc1        $at, $f1
    ctx->f_odd[(1 - 1) * 2] = ctx->r1;
    // nop

    // bne         $t2, $zero, L_8001BB64
    if (ctx->r10 != 0) {
        // nop
    
        goto L_8001BB64;
    }
    // nop

    // swc1        $f19, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f_odd[(19 - 1) * 2];
    // swc1        $f20, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->f20.u32l;
    // bne         $t6, $zero, L_8001BB98
    if (ctx->r14 != 0) {
        // swc1        $f21, 0x8($t7)
        MEM_W(0X8, ctx->r15) = ctx->f_odd[(21 - 1) * 2];
        goto L_8001BB98;
    }
    // swc1        $f21, 0x8($t7)
    MEM_W(0X8, ctx->r15) = ctx->f_odd[(21 - 1) * 2];
L_8001BB34:
    // swc1        $f2, 0x10($t7)
    MEM_W(0X10, ctx->r15) = ctx->f2.u32l;
    // swc1        $f3, 0x14($t7)
    MEM_W(0X14, ctx->r15) = ctx->f_odd[(3 - 1) * 2];
    // bne         $s0, $zero, L_8001BBCC
    if (ctx->r16 != 0) {
        // swc1        $f4, 0x18($t7)
        MEM_W(0X18, ctx->r15) = ctx->f4.u32l;
        goto L_8001BBCC;
    }
    // swc1        $f4, 0x18($t7)
    MEM_W(0X18, ctx->r15) = ctx->f4.u32l;
L_8001BB44:
    // swc1        $f25, 0x20($t7)
    MEM_W(0X20, ctx->r15) = ctx->f_odd[(25 - 1) * 2];
    // swc1        $f26, 0x24($t7)
    MEM_W(0X24, ctx->r15) = ctx->f26.u32l;
    // swc1        $f10, 0x28($t7)
    MEM_W(0X28, ctx->r15) = ctx->f10.u32l;
L_8001BB50:
    // addiu       $t1, $t1, -0x1
    ctx->r9 = ADD32(ctx->r9, -0X1);
    // bne         $t1, $zero, L_8001B86C
    if (ctx->r9 != 0) {
        // addiu       $t0, $t0, 0x10
        ctx->r8 = ADD32(ctx->r8, 0X10);
        goto L_8001B86C;
    }
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // j           L_8001C5A0
    // nop

    goto L_8001C5A0;
    // nop

L_8001BB64:
    // mtc1        $t2, $f0
    ctx->f0.u32l = ctx->r10;
    // nop

    // cvt.s.w     $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    ctx->f0.fl = CVT_S_W(ctx->f0.u32l);
    // mul.s       $f0, $f0, $f1
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f1.fl);
    // nop

    // mul.s       $f19, $f19, $f0
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f19.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f19.fl = MUL_S(ctx->f19.fl, ctx->f0.fl);
    // nop

    // swc1        $f19, 0x0($t7)
    MEM_W(0X0, ctx->r15) = ctx->f_odd[(19 - 1) * 2];
    // mul.s       $f20, $f20, $f0
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f0.fl);
    // swc1        $f20, 0x4($t7)
    MEM_W(0X4, ctx->r15) = ctx->f20.u32l;
    // mul.s       $f21, $f21, $f0
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f21.fl = MUL_S(ctx->f21.fl, ctx->f0.fl);
    // beq         $t6, $zero, L_8001BB34
    if (ctx->r14 == 0) {
        // swc1        $f21, 0x8($t7)
        MEM_W(0X8, ctx->r15) = ctx->f_odd[(21 - 1) * 2];
        goto L_8001BB34;
    }
    // swc1        $f21, 0x8($t7)
    MEM_W(0X8, ctx->r15) = ctx->f_odd[(21 - 1) * 2];
L_8001BB98:
    // mtc1        $t6, $f0
    ctx->f0.u32l = ctx->r14;
    // nop

    // cvt.s.w     $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    ctx->f0.fl = CVT_S_W(ctx->f0.u32l);
    // mul.s       $f0, $f0, $f1
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f1.fl);
    // nop

    // mul.s       $f2, $f2, $f0
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f2.fl = MUL_S(ctx->f2.fl, ctx->f0.fl);
    // nop

    // swc1        $f2, 0x10($t7)
    MEM_W(0X10, ctx->r15) = ctx->f2.u32l;
    // mul.s       $f3, $f3, $f0
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f3.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f3.fl = MUL_S(ctx->f3.fl, ctx->f0.fl);
    // swc1        $f3, 0x14($t7)
    MEM_W(0X14, ctx->r15) = ctx->f_odd[(3 - 1) * 2];
    // mul.s       $f4, $f4, $f0
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f4.fl = MUL_S(ctx->f4.fl, ctx->f0.fl);
    // beq         $s0, $zero, L_8001BB44
    if (ctx->r16 == 0) {
        // swc1        $f4, 0x18($t7)
        MEM_W(0X18, ctx->r15) = ctx->f4.u32l;
        goto L_8001BB44;
    }
    // swc1        $f4, 0x18($t7)
    MEM_W(0X18, ctx->r15) = ctx->f4.u32l;
L_8001BBCC:
    // mtc1        $s0, $f0
    ctx->f0.u32l = ctx->r16;
    // nop

    // cvt.s.w     $f0, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    ctx->f0.fl = CVT_S_W(ctx->f0.u32l);
    // mul.s       $f0, $f0, $f1
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f0.fl = MUL_S(ctx->f0.fl, ctx->f1.fl);
    // nop

    // mul.s       $f25, $f25, $f0
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f25.fl = MUL_S(ctx->f25.fl, ctx->f0.fl);
    // nop

    // swc1        $f25, 0x20($t7)
    MEM_W(0X20, ctx->r15) = ctx->f_odd[(25 - 1) * 2];
    // mul.s       $f26, $f26, $f0
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f26.fl = MUL_S(ctx->f26.fl, ctx->f0.fl);
    // swc1        $f26, 0x24($t7)
    MEM_W(0X24, ctx->r15) = ctx->f26.u32l;
    // mul.s       $f10, $f10, $f0
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f10.fl = MUL_S(ctx->f10.fl, ctx->f0.fl);
    // j           L_8001BB50
    // swc1        $f10, 0x28($t7)
    MEM_W(0X28, ctx->r15) = ctx->f10.u32l;
    goto L_8001BB50;
    // swc1        $f10, 0x28($t7)
    MEM_W(0X28, ctx->r15) = ctx->f10.u32l;
    // lh          $t7, 0x0($s0)
    ctx->r15 = MEM_H(0X0, ctx->r16);
    // srl         $t2, $t7, 6
    ctx->r10 = S32(U32(ctx->r15) >> 6);
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // and         $s3, $t2, $t3
    ctx->r19 = ctx->r10 & ctx->r11;
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // bltz        $t7, L_8001BC2C
    if (SIGNED(ctx->r15) < 0) {
        // subu        $s3, $s6, $s3
        ctx->r19 = SUB32(ctx->r22, ctx->r19);
        goto L_8001BC2C;
    }
    // subu        $s3, $s6, $s3
    ctx->r19 = SUB32(ctx->r22, ctx->r19);
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // j           L_8001BC3C
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001BC3C;
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
L_8001BC2C:
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // sub.s       $f0, $f30, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f0.fl = ctx->f30.fl - ctx->f0.fl;
L_8001BC3C:
    // lh          $t7, 0x2($s0)
    ctx->r15 = MEM_H(0X2, ctx->r16);
    // srl         $t2, $t7, 6
    ctx->r10 = S32(U32(ctx->r15) >> 6);
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // and         $s3, $t2, $t3
    ctx->r19 = ctx->r10 & ctx->r11;
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // bltz        $t7, L_8001BC68
    if (SIGNED(ctx->r15) < 0) {
        // subu        $s3, $s6, $s3
        ctx->r19 = SUB32(ctx->r22, ctx->r19);
        goto L_8001BC68;
    }
    // subu        $s3, $s6, $s3
    ctx->r19 = SUB32(ctx->r22, ctx->r19);
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // j           L_8001BC78
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001BC78;
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
L_8001BC68:
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // sub.s       $f2, $f30, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f2.fl = ctx->f30.fl - ctx->f2.fl;
L_8001BC78:
    // lh          $t7, 0x4($s0)
    ctx->r15 = MEM_H(0X4, ctx->r16);
    // mul.s       $f6, $f0, $f2
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f6.fl = MUL_S(ctx->f0.fl, ctx->f2.fl);
    // nop

    // srl         $t2, $t7, 6
    ctx->r10 = S32(U32(ctx->r15) >> 6);
    // mul.s       $f7, $f0, $f3
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f7.fl = MUL_S(ctx->f0.fl, ctx->f3.fl);
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // mul.s       $f8, $f1, $f2
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f8.fl = MUL_S(ctx->f1.fl, ctx->f2.fl);
    // nop

    // and         $s3, $t2, $t3
    ctx->r19 = ctx->r10 & ctx->r11;
    // mul.s       $f9, $f1, $f3
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f9.fl = MUL_S(ctx->f1.fl, ctx->f3.fl);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // bltz        $t7, L_8001BCBC
    if (SIGNED(ctx->r15) < 0) {
        // subu        $s3, $s6, $s3
        ctx->r19 = SUB32(ctx->r22, ctx->r19);
        goto L_8001BCBC;
    }
    // subu        $s3, $s6, $s3
    ctx->r19 = SUB32(ctx->r22, ctx->r19);
    // lwc1        $f19, 0x0($t6)
    ctx->f_odd[(19 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // j           L_8001BCCC
    // lwc1        $f18, 0x0($t6)
    ctx->f18.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001BCCC;
    // lwc1        $f18, 0x0($t6)
    ctx->f18.u32l = MEM_W(0X0, ctx->r14);
L_8001BCBC:
    // lwc1        $f18, 0x0($t6)
    ctx->f18.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $s3, $s2
    ctx->r14 = ADD32(ctx->r19, ctx->r18);
    // lwc1        $f19, 0x0($t6)
    ctx->f_odd[(19 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // sub.s       $f18, $f30, $f18
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f18.fl = ctx->f30.fl - ctx->f18.fl;
L_8001BCCC:
    // mul.s       $f10, $f6, $f18
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f10.fl = MUL_S(ctx->f6.fl, ctx->f18.fl);
    // nop

    // mul.s       $f11, $f9, $f19
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f9.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f11.fl = MUL_S(ctx->f9.fl, ctx->f19.fl);
    // nop

    // mul.s       $f12, $f8, $f18
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 18);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f18.fl);
    ctx->f12.fl = MUL_S(ctx->f8.fl, ctx->f18.fl);
    // nop

    // mul.s       $f13, $f7, $f19
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 19);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f19.fl);
    ctx->f13.fl = MUL_S(ctx->f7.fl, ctx->f19.fl);
    // jr          $ra
    // nop

    return;
    // nop

    // floor.w.s   $f6, $f4
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    ctx->f6.u32l = S32(floorf(ctx->f4.fl));
    // lui         $at, 0x4480
    ctx->r1 = S32(0X4480 << 16);
    // lbu         $t6, 0x0($a3)
    ctx->r14 = MEM_BU(0X0, ctx->r7);
    // addu        $s4, $s4, $t4
    ctx->r20 = ADD32(ctx->r20, ctx->r12);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // sll         $s3, $t6, 1
    ctx->r19 = S32(ctx->r14) << 1;
    // addu        $t6, $t6, $s3
    ctx->r14 = ADD32(ctx->r14, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // or          $t0, $t5, $zero
    ctx->r8 = ctx->r13 | 0;
    // sub.s       $f4, $f4, $f6
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f4.fl = ctx->f4.fl - ctx->f6.fl;
    // mtc1        $at, $f5
    ctx->f_odd[(5 - 1) * 2] = ctx->r1;
    // addiu       $t3, $a3, 0x4
    ctx->r11 = ADD32(ctx->r7, 0X4);
    // addiu       $s6, $zero, 0x40
    ctx->r22 = ADD32(0, 0X40);
    // mul.s       $f6, $f4, $f5
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f4.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f6.fl = MUL_S(ctx->f4.fl, ctx->f5.fl);
    // or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // ori         $t2, $zero, 0x3
    ctx->r10 = 0 | 0X3;
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // cvt.w.s     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.u32l = CVT_W_S(ctx->f6.fl);
    // mfc1        $t9, $f6
    ctx->r25 = (int32_t)ctx->f6.u32l;
    // nop

L_8001BD48:
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // beq         $s1, $zero, L_8001BDD0
    if (ctx->r17 == 0) {
        // andi        $s0, $s0, 0xFFF0
        ctx->r16 = ctx->r16 & 0XFFF0;
        goto L_8001BDD0;
    }
    // andi        $s0, $s0, 0xFFF0
    ctx->r16 = ctx->r16 & 0XFFF0;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bnel        $at, $zero, L_8001BD9C
    if (ctx->r1 != 0) {
        // subu        $t8, $s6, $s1
        ctx->r24 = SUB32(ctx->r22, ctx->r17);
        goto L_8001BD9C;
    }
    goto skip_2;
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    skip_2:
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
L_8001BD9C:
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // subu        $t8, $t8, $s5
    ctx->r24 = SUB32(ctx->r24, ctx->r21);
    // sll         $t8, $t8, 21
    ctx->r24 = S32(ctx->r24) << 21;
    // sra         $t8, $t8, 21
    ctx->r24 = S32(ctx->r24) >> 21;
    // mult        $t8, $t9
    result = S64(S32(ctx->r24)) * S64(S32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // mflo        $t8
    ctx->r24 = lo;
    // sra         $t8, $t8, 10
    ctx->r24 = S32(ctx->r24) >> 10;
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // sll         $s5, $s5, 5
    ctx->r21 = S32(ctx->r21) << 5;
    // addu        $s0, $s0, $s5
    ctx->r16 = ADD32(ctx->r16, ctx->r21);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
L_8001BDD0:
    // sh          $s0, 0x0($t5)
    MEM_H(0X0, ctx->r13) = ctx->r16;
    // andi        $s0, $s0, 0x10
    ctx->r16 = ctx->r16 & 0X10;
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // sh          $zero, 0xC($t5)
    MEM_H(0XC, ctx->r13) = 0;
    // bne         $s0, $zero, L_8001BE40
    if (ctx->r16 != 0) {
        // sh          $zero, 0x18($t5)
        MEM_H(0X18, ctx->r13) = 0;
        goto L_8001BE40;
    }
    // sh          $zero, 0x18($t5)
    MEM_H(0X18, ctx->r13) = 0;
L_8001BDE8:
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
L_8001BDEC:
    // bnel        $t2, $zero, L_8001BE00
    if (ctx->r10 != 0) {
        // addiu       $t6, $t6, -0x1
        ctx->r14 = ADD32(ctx->r14, -0X1);
        goto L_8001BE00;
    }
    goto skip_3;
    // addiu       $t6, $t6, -0x1
    ctx->r14 = ADD32(ctx->r14, -0X1);
    skip_3:
    // ori         $t2, $zero, 0x3
    ctx->r10 = 0 | 0X3;
    // addiu       $t5, $t5, 0x3A
    ctx->r13 = ADD32(ctx->r13, 0X3A);
    // addiu       $t6, $t6, -0x1
    ctx->r14 = ADD32(ctx->r14, -0X1);
L_8001BE00:
    // bne         $t6, $zero, L_8001BD48
    if (ctx->r14 != 0) {
        // addiu       $t5, $t5, 0x2
        ctx->r13 = ADD32(ctx->r13, 0X2);
        goto L_8001BD48;
    }
    // addiu       $t5, $t5, 0x2
    ctx->r13 = ADD32(ctx->r13, 0X2);
    // lw          $s3, 0x74($sp)
    ctx->r19 = MEM_W(0X74, ctx->r29);
L_8001BE0C:
    // lhu         $s0, 0x0($s3)
    ctx->r16 = MEM_HU(0X0, ctx->r19);
    // addiu       $at, $zero, 0x1000
    ctx->r1 = ADD32(0, 0X1000);
    // bnel        $s0, $at, L_8001BE28
    if (ctx->r16 != ctx->r1) {
        // addu        $s0, $s0, $t0
        ctx->r16 = ADD32(ctx->r16, ctx->r8);
        goto L_8001BE28;
    }
    goto skip_4;
    // addu        $s0, $s0, $t0
    ctx->r16 = ADD32(ctx->r16, ctx->r8);
    skip_4:
    // jr          $ra
    // nop

    return;
    // nop

    // addu        $s0, $s0, $t0
    ctx->r16 = ADD32(ctx->r16, ctx->r8);
L_8001BE28:
    // lh          $s5, 0x0($s0)
    ctx->r21 = MEM_H(0X0, ctx->r16);
    // lh          $t8, 0x2($s3)
    ctx->r24 = MEM_H(0X2, ctx->r19);
    // addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // j           L_8001BE0C
    // sh          $s5, 0x0($s0)
    MEM_H(0X0, ctx->r16) = ctx->r21;
    goto L_8001BE0C;
    // sh          $s5, 0x0($s0)
    MEM_H(0X0, ctx->r16) = ctx->r21;
L_8001BE40:
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    // andi        $s1, $s0, 0x10
    ctx->r17 = ctx->r16 & 0X10;
    // beql        $s1, $zero, L_8001BEE4
    if (ctx->r17 == 0) {
        // nop
    
        goto L_8001BEE4;
    }
    goto skip_5;
    // nop

    skip_5:
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // beq         $s1, $zero, L_8001BECC
    if (ctx->r17 == 0) {
        // andi        $t1, $s0, 0x20
        ctx->r9 = ctx->r16 & 0X20;
        goto L_8001BECC;
    }
    // andi        $t1, $s0, 0x20
    ctx->r9 = ctx->r16 & 0X20;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bne         $at, $zero, L_8001BE9C
    if (ctx->r1 != 0) {
        // andi        $s0, $s0, 0xFFC0
        ctx->r16 = ctx->r16 & 0XFFC0;
        goto L_8001BE9C;
    }
    // andi        $s0, $s0, 0xFFC0
    ctx->r16 = ctx->r16 & 0XFFC0;
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001BE9C:
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // subu        $t8, $t8, $s5
    ctx->r24 = SUB32(ctx->r24, ctx->r21);
    // mult        $t8, $t9
    result = S64(S32(ctx->r24)) * S64(S32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
    // mflo        $t8
    ctx->r24 = lo;
    // sra         $t8, $t8, 10
    ctx->r24 = S32(ctx->r24) >> 10;
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // sll         $s5, $s5, 1
    ctx->r21 = S32(ctx->r21) << 1;
    // addu        $s0, $s0, $s5
    ctx->r16 = ADD32(ctx->r16, ctx->r21);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
L_8001BECC:
    // sh          $s0, 0xC($t5)
    MEM_H(0XC, ctx->r13) = ctx->r16;
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // bnel        $t1, $zero, L_8001BEE4
    if (ctx->r9 != 0) {
        // lhu         $s0, 0x0($t3)
        ctx->r16 = MEM_HU(0X0, ctx->r11);
        goto L_8001BEE4;
    }
    goto skip_6;
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    skip_6:
    // b           L_8001BDEC
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
    goto L_8001BDEC;
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
L_8001BEE4:
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // beql        $s1, $zero, L_8001BF68
    if (ctx->r17 == 0) {
        // sh          $s0, 0x18($t5)
        MEM_H(0X18, ctx->r13) = ctx->r16;
        goto L_8001BF68;
    }
    goto skip_7;
    // sh          $s0, 0x18($t5)
    MEM_H(0X18, ctx->r13) = ctx->r16;
    skip_7:
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bne         $at, $zero, L_8001BF30
    if (ctx->r1 != 0) {
        // andi        $s0, $s0, 0xFFF0
        ctx->r16 = ctx->r16 & 0XFFF0;
        goto L_8001BF30;
    }
    // andi        $s0, $s0, 0xFFF0
    ctx->r16 = ctx->r16 & 0XFFF0;
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001BF30:
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // subu        $t8, $t8, $s5
    ctx->r24 = SUB32(ctx->r24, ctx->r21);
    // sll         $t8, $t8, 16
    ctx->r24 = S32(ctx->r24) << 16;
    // sra         $t8, $t8, 16
    ctx->r24 = S32(ctx->r24) >> 16;
    // mult        $t8, $t9
    result = S64(S32(ctx->r24)) * S64(S32(ctx->r25)); lo = S32(result >> 0); hi = S32(result >> 32);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
    // mflo        $t8
    ctx->r24 = lo;
    // sra         $t8, $t8, 10
    ctx->r24 = S32(ctx->r24) >> 10;
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // addu        $s0, $s0, $s5
    ctx->r16 = ADD32(ctx->r16, ctx->r21);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
    // sh          $s0, 0x18($t5)
    MEM_H(0X18, ctx->r13) = ctx->r16;
L_8001BF68:
    // b           L_8001BDE8
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    goto L_8001BDE8;
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // lbu         $t6, 0x0($a3)
    ctx->r14 = MEM_BU(0X0, ctx->r7);
    // addu        $s4, $s4, $t4
    ctx->r20 = ADD32(ctx->r20, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // sll         $s3, $t6, 1
    ctx->r19 = S32(ctx->r14) << 1;
    // addu        $t6, $t6, $s3
    ctx->r14 = ADD32(ctx->r14, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // or          $t0, $t5, $zero
    ctx->r8 = ctx->r13 | 0;
    // addiu       $t3, $a3, 0x4
    ctx->r11 = ADD32(ctx->r7, 0X4);
    // addiu       $s6, $zero, 0x40
    ctx->r22 = ADD32(0, 0X40);
    // or          $s2, $zero, $zero
    ctx->r18 = 0 | 0;
    // ori         $t2, $zero, 0x3
    ctx->r10 = 0 | 0X3;
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
L_8001BFA4:
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // bnel        $s1, $zero, L_8001BFC4
    if (ctx->r17 != 0) {
        // addu        $s2, $s2, $s1
        ctx->r18 = ADD32(ctx->r18, ctx->r17);
        goto L_8001BFC4;
    }
    goto skip_8;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    skip_8:
    // sh          $s0, 0x0($t5)
    MEM_H(0X0, ctx->r13) = ctx->r16;
    // b           L_8001C02C
    // sh          $s0, 0x6($t5)
    MEM_H(0X6, ctx->r13) = ctx->r16;
    goto L_8001C02C;
    // sh          $s0, 0x6($t5)
    MEM_H(0X6, ctx->r13) = ctx->r16;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001BFC4:
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bne         $at, $zero, L_8001C000
    if (ctx->r1 != 0) {
        // andi        $s0, $s0, 0xFFF0
        ctx->r16 = ctx->r16 & 0XFFF0;
        goto L_8001C000;
    }
    // andi        $s0, $s0, 0xFFF0
    ctx->r16 = ctx->r16 & 0XFFF0;
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001C000:
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // sll         $s5, $s5, 5
    ctx->r21 = S32(ctx->r21) << 5;
    // sll         $t8, $t8, 5
    ctx->r24 = S32(ctx->r24) << 5;
    // addu        $s5, $s5, $s0
    ctx->r21 = ADD32(ctx->r21, ctx->r16);
    // addu        $t8, $t8, $s0
    ctx->r24 = ADD32(ctx->r24, ctx->r16);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
    // sh          $s5, 0x0($t5)
    MEM_H(0X0, ctx->r13) = ctx->r21;
    // sh          $t8, 0x6($t5)
    MEM_H(0X6, ctx->r13) = ctx->r24;
L_8001C02C:
    // andi        $s0, $s0, 0x10
    ctx->r16 = ctx->r16 & 0X10;
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // sh          $zero, 0xC($t5)
    MEM_H(0XC, ctx->r13) = 0;
    // sh          $zero, 0x12($t5)
    MEM_H(0X12, ctx->r13) = 0;
    // sh          $zero, 0x18($t5)
    MEM_H(0X18, ctx->r13) = 0;
    // bne         $s0, $zero, L_8001C0AC
    if (ctx->r16 != 0) {
        // sh          $zero, 0x1E($t5)
        MEM_H(0X1E, ctx->r13) = 0;
        goto L_8001C0AC;
    }
    // sh          $zero, 0x1E($t5)
    MEM_H(0X1E, ctx->r13) = 0;
L_8001C048:
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
L_8001C04C:
    // bnel        $t2, $zero, L_8001C060
    if (ctx->r10 != 0) {
        // addiu       $t6, $t6, -0x1
        ctx->r14 = ADD32(ctx->r14, -0X1);
        goto L_8001C060;
    }
    goto skip_9;
    // addiu       $t6, $t6, -0x1
    ctx->r14 = ADD32(ctx->r14, -0X1);
    skip_9:
    // ori         $t2, $zero, 0x3
    ctx->r10 = 0 | 0X3;
    // addiu       $t5, $t5, 0x3A
    ctx->r13 = ADD32(ctx->r13, 0X3A);
    // addiu       $t6, $t6, -0x1
    ctx->r14 = ADD32(ctx->r14, -0X1);
L_8001C060:
    // bne         $t6, $zero, L_8001BFA4
    if (ctx->r14 != 0) {
        // addiu       $t5, $t5, 0x2
        ctx->r13 = ADD32(ctx->r13, 0X2);
        goto L_8001BFA4;
    }
    // addiu       $t5, $t5, 0x2
    ctx->r13 = ADD32(ctx->r13, 0X2);
    // lw          $s3, 0x74($sp)
    ctx->r19 = MEM_W(0X74, ctx->r29);
L_8001C06C:
    // lhu         $s0, 0x0($s3)
    ctx->r16 = MEM_HU(0X0, ctx->r19);
    // addiu       $at, $zero, 0x1000
    ctx->r1 = ADD32(0, 0X1000);
    // bnel        $s0, $at, L_8001C088
    if (ctx->r16 != ctx->r1) {
        // addu        $s0, $s0, $t0
        ctx->r16 = ADD32(ctx->r16, ctx->r8);
        goto L_8001C088;
    }
    goto skip_10;
    // addu        $s0, $s0, $t0
    ctx->r16 = ADD32(ctx->r16, ctx->r8);
    skip_10:
    // jr          $ra
    // nop

    return;
    // nop

    // addu        $s0, $s0, $t0
    ctx->r16 = ADD32(ctx->r16, ctx->r8);
L_8001C088:
    // lh          $s5, 0x0($s0)
    ctx->r21 = MEM_H(0X0, ctx->r16);
    // lh          $t8, 0x2($s3)
    ctx->r24 = MEM_H(0X2, ctx->r19);
    // addiu       $s3, $s3, 0x4
    ctx->r19 = ADD32(ctx->r19, 0X4);
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // sh          $s5, 0x0($s0)
    MEM_H(0X0, ctx->r16) = ctx->r21;
    // lh          $s5, 0x6($s0)
    ctx->r21 = MEM_H(0X6, ctx->r16);
    // addu        $s5, $s5, $t8
    ctx->r21 = ADD32(ctx->r21, ctx->r24);
    // j           L_8001C06C
    // sh          $s5, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r21;
    goto L_8001C06C;
    // sh          $s5, 0x6($s0)
    MEM_H(0X6, ctx->r16) = ctx->r21;
L_8001C0AC:
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    // andi        $s1, $s0, 0x10
    ctx->r17 = ctx->r16 & 0X10;
    // beql        $s1, $zero, L_8001C154
    if (ctx->r17 == 0) {
        // nop
    
        goto L_8001C154;
    }
    goto skip_11;
    // nop

    skip_11:
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // bne         $s1, $zero, L_8001C0D4
    if (ctx->r17 != 0) {
        // andi        $t1, $s0, 0x20
        ctx->r9 = ctx->r16 & 0X20;
        goto L_8001C0D4;
    }
    // andi        $t1, $s0, 0x20
    ctx->r9 = ctx->r16 & 0X20;
    // sh          $s0, 0xC($t5)
    MEM_H(0XC, ctx->r13) = ctx->r16;
    // b           L_8001C140
    // sh          $s0, 0x12($t5)
    MEM_H(0X12, ctx->r13) = ctx->r16;
    goto L_8001C140;
    // sh          $s0, 0x12($t5)
    MEM_H(0X12, ctx->r13) = ctx->r16;
L_8001C0D4:
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bne         $at, $zero, L_8001C114
    if (ctx->r1 != 0) {
        // andi        $s0, $s0, 0xFFC0
        ctx->r16 = ctx->r16 & 0XFFC0;
        goto L_8001C114;
    }
    // andi        $s0, $s0, 0xFFC0
    ctx->r16 = ctx->r16 & 0XFFC0;
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001C114:
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // sll         $s5, $s5, 1
    ctx->r21 = S32(ctx->r21) << 1;
    // sll         $t8, $t8, 1
    ctx->r24 = S32(ctx->r24) << 1;
    // addu        $s5, $s5, $s0
    ctx->r21 = ADD32(ctx->r21, ctx->r16);
    // addu        $t8, $t8, $s0
    ctx->r24 = ADD32(ctx->r24, ctx->r16);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
    // sh          $s5, 0xC($t5)
    MEM_H(0XC, ctx->r13) = ctx->r21;
    // sh          $t8, 0x12($t5)
    MEM_H(0X12, ctx->r13) = ctx->r24;
L_8001C140:
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    // bnel        $t1, $zero, L_8001C154
    if (ctx->r9 != 0) {
        // lhu         $s0, 0x0($t3)
        ctx->r16 = MEM_HU(0X0, ctx->r11);
        goto L_8001C154;
    }
    goto skip_12;
    // lhu         $s0, 0x0($t3)
    ctx->r16 = MEM_HU(0X0, ctx->r11);
    skip_12:
    // b           L_8001C04C
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
    goto L_8001C04C;
    // addiu       $t2, $t2, -0x1
    ctx->r10 = ADD32(ctx->r10, -0X1);
L_8001C154:
    // andi        $s1, $s0, 0xF
    ctx->r17 = ctx->r16 & 0XF;
    // bnel        $s1, $zero, L_8001C170
    if (ctx->r17 != 0) {
        // addu        $s2, $s2, $s1
        ctx->r18 = ADD32(ctx->r18, ctx->r17);
        goto L_8001C170;
    }
    goto skip_13;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
    skip_13:
    // sh          $s0, 0x18($t5)
    MEM_H(0X18, ctx->r13) = ctx->r16;
    // b           L_8001C1D0
    // sh          $s0, 0x1E($t5)
    MEM_H(0X1E, ctx->r13) = ctx->r16;
    goto L_8001C1D0;
    // sh          $s0, 0x1E($t5)
    MEM_H(0X1E, ctx->r13) = ctx->r16;
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001C170:
    // slti        $at, $s2, 0x41
    ctx->r1 = SIGNED(ctx->r18) < 0X41 ? 1 : 0;
    // bne         $at, $zero, L_8001C1AC
    if (ctx->r1 != 0) {
        // andi        $s0, $s0, 0xFFF0
        ctx->r16 = ctx->r16 & 0XFFF0;
        goto L_8001C1AC;
    }
    // andi        $s0, $s0, 0xFFF0
    ctx->r16 = ctx->r16 & 0XFFF0;
    // subu        $s2, $s2, $s1
    ctx->r18 = SUB32(ctx->r18, ctx->r17);
    // srl         $s3, $s2, 3
    ctx->r19 = S32(U32(ctx->r18) >> 3);
    // addu        $s4, $s4, $s3
    ctx->r20 = ADD32(ctx->r20, ctx->r19);
    // addu        $t4, $t4, $s3
    ctx->r12 = ADD32(ctx->r12, ctx->r19);
    // ldl         $s3, 0x0($t4)
    ctx->r19 = do_ldl(rdram, ctx->r19, 0X0, ctx->r12);
    // ldl         $s7, 0x0($s4)
    ctx->r23 = do_ldl(rdram, ctx->r23, 0X0, ctx->r20);
    // ldr         $s3, 0x7($t4)
    ctx->r19 = do_ldr(rdram, ctx->r19, 0X7, ctx->r12);
    // ldr         $s7, 0x7($s4)
    ctx->r23 = do_ldr(rdram, ctx->r23, 0X7, ctx->r20);
    // andi        $s2, $s2, 0x7
    ctx->r18 = ctx->r18 & 0X7;
    // dsllv       $s3, $s3, $s2
    ctx->r19 = ctx->r19 << (ctx->r18 & 63);
    // dsllv       $s7, $s7, $s2
    ctx->r23 = ctx->r23 << (ctx->r18 & 63);
    // addu        $s2, $s2, $s1
    ctx->r18 = ADD32(ctx->r18, ctx->r17);
L_8001C1AC:
    // subu        $t8, $s6, $s1
    ctx->r24 = SUB32(ctx->r22, ctx->r17);
    // dsrlv       $s5, $s3, $t8
    ctx->r21 = ctx->r19 >> (ctx->r24 & 63));
    // dsrlv       $t8, $s7, $t8
    ctx->r24 = ctx->r23 >> (ctx->r24 & 63));
    // addu        $s5, $s5, $s0
    ctx->r21 = ADD32(ctx->r21, ctx->r16);
    // addu        $t8, $t8, $s0
    ctx->r24 = ADD32(ctx->r24, ctx->r16);
    // dsllv       $s3, $s3, $s1
    ctx->r19 = ctx->r19 << (ctx->r17 & 63);
    // dsllv       $s7, $s7, $s1
    ctx->r23 = ctx->r23 << (ctx->r17 & 63);
    // sh          $s5, 0x18($t5)
    MEM_H(0X18, ctx->r13) = ctx->r21;
    // sh          $t8, 0x1E($t5)
    MEM_H(0X1E, ctx->r13) = ctx->r24;
L_8001C1D0:
    // b           L_8001C048
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
    goto L_8001C048;
    // addiu       $t3, $t3, 0x2
    ctx->r11 = ADD32(ctx->r11, 0X2);
L_8001C1D8:
    // lui         $t0, 0x8009
    ctx->r8 = S32(0X8009 << 16);
    // lw          $t0, -0x1528($t0)
    ctx->r8 = MEM_W(-0X1528, ctx->r8);
    // lui         $a3, 0x8009
    ctx->r7 = S32(0X8009 << 16);
    // lw          $a3, -0x1530($a3)
    ctx->r7 = MEM_W(-0X1530, ctx->r7);
    // lw          $s0, 0x70($sp)
    ctx->r16 = MEM_W(0X70, ctx->r29);
    // sll         $s0, $s0, 4
    ctx->r16 = S32(ctx->r16) << 4;
    // addu        $s5, $s0, $t0
    ctx->r21 = ADD32(ctx->r16, ctx->r8);
    // lw          $s0, 0x78($sp)
    ctx->r16 = MEM_W(0X78, ctx->r29);
    // ori         $s2, $zero, 0x200
    ctx->r18 = 0 | 0X200;
    // ori         $s3, $zero, 0x400
    ctx->r19 = 0 | 0X400;
    // ori         $s4, $zero, 0x600
    ctx->r20 = 0 | 0X600;
    // lui         $at, 0x3A80
    ctx->r1 = S32(0X3A80 << 16);
    // mtc1        $at, $f21
    ctx->f_odd[(21 - 1) * 2] = ctx->r1;
    // lui         $at, 0x3D00
    ctx->r1 = S32(0X3D00 << 16);
    // mtc1        $at, $f29
    ctx->f_odd[(29 - 1) * 2] = ctx->r1;
    // addiu       $t3, $zero, 0x7FC
    ctx->r11 = ADD32(0, 0X7FC);
    // addiu       $s6, $zero, 0x800
    ctx->r22 = ADD32(0, 0X800);
    // lui         $t5, 0x8009
    ctx->r13 = S32(0X8009 << 16);
    // addiu       $t5, $t5, 0x450
    ctx->r13 = ADD32(ctx->r13, 0X450);
L_8001C224:
    // lb          $t7, 0x1($t0)
    ctx->r15 = MEM_B(0X1, ctx->r8);
    // and         $t7, $t7, $s0
    ctx->r15 = ctx->r15 & ctx->r16;
    // bgez        $t7, L_8001C244
    if (SIGNED(ctx->r15) >= 0) {
        // nop
    
        goto L_8001C244;
    }
    // nop

    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // bne         $t0, $s5, L_8001C224
    if (ctx->r8 != ctx->r21) {
        // nop
    
        goto L_8001C224;
    }
    // nop

    // j           L_8001C5A0
    // sll         $t2, $t7, 6
    ctx->r10 = S32(ctx->r15) << 6;
    goto L_8001C5A0;
L_8001C244:
    // sll         $t2, $t7, 6
    ctx->r10 = S32(ctx->r15) << 6;
    // lbu         $t7, 0x2($t0)
    ctx->r15 = MEM_BU(0X2, ctx->r8);
    // addu        $a0, $t2, $a3
    ctx->r4 = ADD32(ctx->r10, ctx->r7);
    // sll         $t1, $t7, 6
    ctx->r9 = S32(ctx->r15) << 6;
    // addu        $s7, $t8, $t1
    ctx->r23 = ADD32(ctx->r24, ctx->r9);
    // lhu         $t2, 0x0($s7)
    ctx->r10 = MEM_HU(0X0, ctx->r23);
    // srl         $t2, $t2, 5
    ctx->r10 = S32(U32(ctx->r10) >> 5);
    // and         $t7, $t2, $s4
    ctx->r15 = ctx->r10 & ctx->r20;
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // beq         $t7, $s4, L_8001C2A4
    if (ctx->r15 == ctx->r20) {
        // and         $t4, $t2, $t3
        ctx->r12 = ctx->r10 & ctx->r11;
        goto L_8001C2A4;
    }
    // and         $t4, $t2, $t3
    ctx->r12 = ctx->r10 & ctx->r11;
    // beq         $t7, $s3, L_8001C2C0
    if (ctx->r15 == ctx->r19) {
        // addu        $t6, $t4, $t5
        ctx->r14 = ADD32(ctx->r12, ctx->r13);
        goto L_8001C2C0;
    }
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // beq         $t7, $s2, L_8001C290
    if (ctx->r15 == ctx->r18) {
        // subu        $t4, $s6, $t4
        ctx->r12 = SUB32(ctx->r22, ctx->r12);
        goto L_8001C290;
    }
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // j           L_8001C2D8
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001C2D8;
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
L_8001C290:
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C2D8
    // sub.s       $f0, $f30, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f0.fl = ctx->f30.fl - ctx->f0.fl;
    goto L_8001C2D8;
    // sub.s       $f0, $f30, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f0.fl = ctx->f30.fl - ctx->f0.fl;
L_8001C2A4:
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C2D8
    // sub.s       $f1, $f30, $f1
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f1.fl = ctx->f30.fl - ctx->f1.fl;
    goto L_8001C2D8;
    // sub.s       $f1, $f30, $f1
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f1.fl = ctx->f30.fl - ctx->f1.fl;
L_8001C2C0:
    // lwc1        $f1, 0x0($t6)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f0, 0x0($t6)
    ctx->f0.u32l = MEM_W(0X0, ctx->r14);
    // sub.s       $f1, $f30, $f1
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f1.fl = ctx->f30.fl - ctx->f1.fl;
    // sub.s       $f0, $f30, $f0
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f0.fl = ctx->f30.fl - ctx->f0.fl;
L_8001C2D8:
    // lhu         $t2, 0x4($s7)
    ctx->r10 = MEM_HU(0X4, ctx->r23);
    // srl         $t2, $t2, 5
    ctx->r10 = S32(U32(ctx->r10) >> 5);
    // and         $t7, $t2, $s4
    ctx->r15 = ctx->r10 & ctx->r20;
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // beq         $t7, $s4, L_8001C324
    if (ctx->r15 == ctx->r20) {
        // and         $t4, $t2, $t3
        ctx->r12 = ctx->r10 & ctx->r11;
        goto L_8001C324;
    }
    // and         $t4, $t2, $t3
    ctx->r12 = ctx->r10 & ctx->r11;
    // beq         $t7, $s3, L_8001C340
    if (ctx->r15 == ctx->r19) {
        // addu        $t6, $t4, $t5
        ctx->r14 = ADD32(ctx->r12, ctx->r13);
        goto L_8001C340;
    }
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // beq         $t7, $s2, L_8001C310
    if (ctx->r15 == ctx->r18) {
        // subu        $t4, $s6, $t4
        ctx->r12 = SUB32(ctx->r22, ctx->r12);
        goto L_8001C310;
    }
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // lwc1        $f5, 0x0($t6)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // j           L_8001C358
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001C358;
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
L_8001C310:
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f5, 0x0($t6)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C358
    // sub.s       $f4, $f30, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f4.fl = ctx->f30.fl - ctx->f4.fl;
    goto L_8001C358;
    // sub.s       $f4, $f30, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f4.fl = ctx->f30.fl - ctx->f4.fl;
L_8001C324:
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f5, 0x0($t6)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C358
    // sub.s       $f5, $f30, $f5
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f5.fl = ctx->f30.fl - ctx->f5.fl;
    goto L_8001C358;
    // sub.s       $f5, $f30, $f5
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f5.fl = ctx->f30.fl - ctx->f5.fl;
L_8001C340:
    // lwc1        $f5, 0x0($t6)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f4, 0x0($t6)
    ctx->f4.u32l = MEM_W(0X0, ctx->r14);
    // sub.s       $f5, $f30, $f5
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f5.fl = ctx->f30.fl - ctx->f5.fl;
    // sub.s       $f4, $f30, $f4
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f4.fl = ctx->f30.fl - ctx->f4.fl;
L_8001C358:
    // lhu         $t2, 0x2($s7)
    ctx->r10 = MEM_HU(0X2, ctx->r23);
    // srl         $t2, $t2, 5
    ctx->r10 = S32(U32(ctx->r10) >> 5);
    // and         $t7, $t2, $s4
    ctx->r15 = ctx->r10 & ctx->r20;
    // sll         $t2, $t2, 2
    ctx->r10 = S32(ctx->r10) << 2;
    // beq         $t7, $s4, L_8001C3A4
    if (ctx->r15 == ctx->r20) {
        // and         $t4, $t2, $t3
        ctx->r12 = ctx->r10 & ctx->r11;
        goto L_8001C3A4;
    }
    // and         $t4, $t2, $t3
    ctx->r12 = ctx->r10 & ctx->r11;
    // beq         $t7, $s3, L_8001C3C0
    if (ctx->r15 == ctx->r19) {
        // addu        $t6, $t4, $t5
        ctx->r14 = ADD32(ctx->r12, ctx->r13);
        goto L_8001C3C0;
    }
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // beq         $t7, $s2, L_8001C390
    if (ctx->r15 == ctx->r18) {
        // subu        $t4, $s6, $t4
        ctx->r12 = SUB32(ctx->r22, ctx->r12);
        goto L_8001C390;
    }
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // j           L_8001C3D8
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    goto L_8001C3D8;
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
L_8001C390:
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C3D8
    // sub.s       $f2, $f30, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f2.fl = ctx->f30.fl - ctx->f2.fl;
    goto L_8001C3D8;
    // sub.s       $f2, $f30, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f2.fl = ctx->f30.fl - ctx->f2.fl;
L_8001C3A4:
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // j           L_8001C3D8
    // sub.s       $f3, $f30, $f3
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f3.fl = ctx->f30.fl - ctx->f3.fl;
    goto L_8001C3D8;
    // sub.s       $f3, $f30, $f3
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f3.fl = ctx->f30.fl - ctx->f3.fl;
L_8001C3C0:
    // lwc1        $f3, 0x0($t6)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X0, ctx->r14);
    // subu        $t4, $s6, $t4
    ctx->r12 = SUB32(ctx->r22, ctx->r12);
    // addu        $t6, $t4, $t5
    ctx->r14 = ADD32(ctx->r12, ctx->r13);
    // lwc1        $f2, 0x0($t6)
    ctx->f2.u32l = MEM_W(0X0, ctx->r14);
    // sub.s       $f3, $f30, $f3
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f3.fl = ctx->f30.fl - ctx->f3.fl;
    // sub.s       $f2, $f30, $f2
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f2.fl = ctx->f30.fl - ctx->f2.fl;
L_8001C3D8:
    // lh          $t7, 0x18($s7)
    ctx->r15 = MEM_H(0X18, ctx->r23);
    // mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // lwc1        $f7, 0x4($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0X4, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f6, $f6, $f29
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f29.fl);
    // add.s       $f6, $f7, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f6.fl = ctx->f7.fl + ctx->f6.fl;
    // swc1        $f6, 0x30($a0)
    MEM_W(0X30, ctx->r4) = ctx->f6.u32l;
    // lh          $t7, 0x1A($s7)
    ctx->r15 = MEM_H(0X1A, ctx->r23);
    // mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // lwc1        $f7, 0x8($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0X8, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f6, $f6, $f29
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f29.fl);
    // add.s       $f6, $f7, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f6.fl = ctx->f7.fl + ctx->f6.fl;
    // swc1        $f6, 0x34($a0)
    MEM_W(0X34, ctx->r4) = ctx->f6.u32l;
    // lh          $t7, 0x1C($s7)
    ctx->r15 = MEM_H(0X1C, ctx->r23);
    // mtc1        $t7, $f6
    ctx->f6.u32l = ctx->r15;
    // lwc1        $f7, 0xC($t0)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0XC, ctx->r8);
    // cvt.s.w     $f6, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    ctx->f6.fl = CVT_S_W(ctx->f6.u32l);
    // mul.s       $f6, $f6, $f29
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 29);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f29.fl);
    ctx->f6.fl = MUL_S(ctx->f6.fl, ctx->f29.fl);
    // add.s       $f6, $f7, $f6
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f6.fl = ctx->f7.fl + ctx->f6.fl;
    // mul.s       $f7, $f0, $f5
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f7.fl = MUL_S(ctx->f0.fl, ctx->f5.fl);
    // swc1        $f6, 0x38($a0)
    MEM_W(0X38, ctx->r4) = ctx->f6.u32l;
    // mul.s       $f6, $f1, $f5
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f6.fl = MUL_S(ctx->f1.fl, ctx->f5.fl);
    // nop

    // mul.s       $f8, $f1, $f4
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f8.fl = MUL_S(ctx->f1.fl, ctx->f4.fl);
    // nop

    // mul.s       $f9, $f0, $f4
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f9.fl = MUL_S(ctx->f0.fl, ctx->f4.fl);
    // nop

    // mul.s       $f12, $f2, $f4
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f12.fl = MUL_S(ctx->f2.fl, ctx->f4.fl);
    // lhu         $t7, 0xC($s7)
    ctx->r15 = MEM_HU(0XC, ctx->r23);
    // mul.s       $f13, $f2, $f5
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f2.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f13.fl = MUL_S(ctx->f2.fl, ctx->f5.fl);
    // bne         $t7, $zero, L_8001C4D4
    if (ctx->r15 != 0) {
        // nop
    
        goto L_8001C4D4;
    }
    // nop

    // swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    // sub.s       $f14, $f30, $f3
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f14.fl = ctx->f30.fl - ctx->f3.fl;
    // swc1        $f13, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f_odd[(13 - 1) * 2];
L_8001C468:
    // mul.s       $f15, $f8, $f3
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f15.fl = MUL_S(ctx->f8.fl, ctx->f3.fl);
    // swc1        $f14, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f14.u32l;
    // sub.s       $f15, $f15, $f7
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f15.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f15.fl = ctx->f15.fl - ctx->f7.fl;
    // lhu         $t7, 0xE($s7)
    ctx->r15 = MEM_HU(0XE, ctx->r23);
    // mul.s       $f16, $f6, $f3
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f3.fl);
    // bne         $t7, $zero, L_8001C518
    if (ctx->r15 != 0) {
        // nop
    
        goto L_8001C518;
    }
    // nop

    // swc1        $f15, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f_odd[(15 - 1) * 2];
    // add.s       $f16, $f16, $f9
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 9);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f9.fl);
    ctx->f16.fl = ctx->f16.fl + ctx->f9.fl;
    // mul.s       $f17, $f1, $f2
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f17.fl = MUL_S(ctx->f1.fl, ctx->f2.fl);
    // swc1        $f16, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f16.u32l;
L_8001C494:
    // mul.s       $f18, $f9, $f3
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f9.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f18.fl = MUL_S(ctx->f9.fl, ctx->f3.fl);
    // swc1        $f17, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f_odd[(17 - 1) * 2];
    // add.s       $f18, $f18, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f18.fl = ctx->f18.fl + ctx->f6.fl;
    // lhu         $t7, 0x10($s7)
    ctx->r15 = MEM_HU(0X10, ctx->r23);
    // mul.s       $f19, $f7, $f3
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f19.fl = MUL_S(ctx->f7.fl, ctx->f3.fl);
    // bne         $t7, $zero, L_8001C564
    if (ctx->r15 != 0) {
        // nop
    
        goto L_8001C564;
    }
    // nop

    // swc1        $f18, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f18.u32l;
    // sub.s       $f19, $f19, $f8
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f19.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f19.fl = ctx->f19.fl - ctx->f8.fl;
    // mul.s       $f20, $f0, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f20.fl = MUL_S(ctx->f0.fl, ctx->f2.fl);
    // swc1        $f19, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f_odd[(19 - 1) * 2];
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // bne         $t0, $s5, L_8001C224
    if (ctx->r8 != ctx->r21) {
        // swc1        $f20, 0x28($a0)
        MEM_W(0X28, ctx->r4) = ctx->f20.u32l;
        goto L_8001C224;
    }
    // swc1        $f20, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f20.u32l;
    // j           L_8001C5A0
    // nop

    goto L_8001C5A0;
    // nop

L_8001C4D4:
    // mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // nop

    // cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // mul.s       $f10, $f10, $f21
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f10.fl = MUL_S(ctx->f10.fl, ctx->f21.fl);
    // sub.s       $f14, $f30, $f3
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f14.fl = ctx->f30.fl - ctx->f3.fl;
    // mul.s       $f12, $f12, $f10
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f12.fl = MUL_S(ctx->f12.fl, ctx->f10.fl);
    // nop

    // swc1        $f12, 0x0($a0)
    MEM_W(0X0, ctx->r4) = ctx->f12.u32l;
    // mul.s       $f13, $f13, $f10
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f13.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f13.fl = MUL_S(ctx->f13.fl, ctx->f10.fl);
    // lhu         $t7, 0xE($s7)
    ctx->r15 = MEM_HU(0XE, ctx->r23);
    // mul.s       $f14, $f14, $f10
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f14.fl = MUL_S(ctx->f14.fl, ctx->f10.fl);
    // beq         $t7, $zero, L_8001C468
    if (ctx->r15 == 0) {
        // swc1        $f13, 0x4($a0)
        MEM_W(0X4, ctx->r4) = ctx->f_odd[(13 - 1) * 2];
        goto L_8001C468;
    }
    // swc1        $f13, 0x4($a0)
    MEM_W(0X4, ctx->r4) = ctx->f_odd[(13 - 1) * 2];
    // mul.s       $f15, $f8, $f3
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f8.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f15.fl = MUL_S(ctx->f8.fl, ctx->f3.fl);
    // swc1        $f14, 0x8($a0)
    MEM_W(0X8, ctx->r4) = ctx->f14.u32l;
    // sub.s       $f15, $f15, $f7
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f15.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f15.fl = ctx->f15.fl - ctx->f7.fl;
    // mul.s       $f16, $f6, $f3
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f6.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f16.fl = MUL_S(ctx->f6.fl, ctx->f3.fl);
L_8001C518:
    // mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // nop

    // cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // mul.s       $f10, $f10, $f21
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f10.fl = MUL_S(ctx->f10.fl, ctx->f21.fl);
    // add.s       $f16, $f16, $f9
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 9);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f9.fl);
    ctx->f16.fl = ctx->f16.fl + ctx->f9.fl;
    // mul.s       $f15, $f15, $f10
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f15.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f15.fl = MUL_S(ctx->f15.fl, ctx->f10.fl);
    // nop

    // mul.s       $f17, $f1, $f2
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f1.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f17.fl = MUL_S(ctx->f1.fl, ctx->f2.fl);
    // swc1        $f15, 0x10($a0)
    MEM_W(0X10, ctx->r4) = ctx->f_odd[(15 - 1) * 2];
    // nop

    // mul.s       $f16, $f16, $f10
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f16.fl = MUL_S(ctx->f16.fl, ctx->f10.fl);
    // lhu         $t7, 0x10($s7)
    ctx->r15 = MEM_HU(0X10, ctx->r23);
    // mul.s       $f17, $f17, $f10
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f17.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f17.fl = MUL_S(ctx->f17.fl, ctx->f10.fl);
    // beq         $t7, $zero, L_8001C494
    if (ctx->r15 == 0) {
        // swc1        $f16, 0x14($a0)
        MEM_W(0X14, ctx->r4) = ctx->f16.u32l;
        goto L_8001C494;
    }
    // swc1        $f16, 0x14($a0)
    MEM_W(0X14, ctx->r4) = ctx->f16.u32l;
    // mul.s       $f18, $f9, $f3
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f9.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f18.fl = MUL_S(ctx->f9.fl, ctx->f3.fl);
    // swc1        $f17, 0x18($a0)
    MEM_W(0X18, ctx->r4) = ctx->f_odd[(17 - 1) * 2];
    // add.s       $f18, $f18, $f6
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f18.fl = ctx->f18.fl + ctx->f6.fl;
    // mul.s       $f19, $f7, $f3
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f7.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f19.fl = MUL_S(ctx->f7.fl, ctx->f3.fl);
L_8001C564:
    // mtc1        $t7, $f10
    ctx->f10.u32l = ctx->r15;
    // nop

    // cvt.s.w     $f10, $f10
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    ctx->f10.fl = CVT_S_W(ctx->f10.u32l);
    // mul.s       $f10, $f10, $f21
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 21);
    NAN_CHECK(ctx->f10.fl); NAN_CHECK(ctx->f21.fl);
    ctx->f10.fl = MUL_S(ctx->f10.fl, ctx->f21.fl);
    // sub.s       $f19, $f19, $f8
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f19.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f19.fl = ctx->f19.fl - ctx->f8.fl;
    // mul.s       $f18, $f18, $f10
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f18.fl = MUL_S(ctx->f18.fl, ctx->f10.fl);
    // nop

    // mul.s       $f20, $f0, $f2
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f0.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f20.fl = MUL_S(ctx->f0.fl, ctx->f2.fl);
    // swc1        $f18, 0x20($a0)
    MEM_W(0X20, ctx->r4) = ctx->f18.u32l;
    // mul.s       $f19, $f19, $f10
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f19.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f19.fl = MUL_S(ctx->f19.fl, ctx->f10.fl);
    // swc1        $f19, 0x24($a0)
    MEM_W(0X24, ctx->r4) = ctx->f_odd[(19 - 1) * 2];
    // mul.s       $f20, $f20, $f10
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f20.fl = MUL_S(ctx->f20.fl, ctx->f10.fl);
    // addiu       $t0, $t0, 0x10
    ctx->r8 = ADD32(ctx->r8, 0X10);
    // bne         $t0, $s5, L_8001C224
    if (ctx->r8 != ctx->r21) {
        // swc1        $f20, 0x28($a0)
        MEM_W(0X28, ctx->r4) = ctx->f20.u32l;
        goto L_8001C224;
    }
    // swc1        $f20, 0x28($a0)
    MEM_W(0X28, ctx->r4) = ctx->f20.u32l;
L_8001C5A0:
    // lw          $v0, 0x7C($sp)
    ctx->r2 = MEM_W(0X7C, ctx->r29);
    // andi        $v0, $v0, 0xC
    ctx->r2 = ctx->r2 & 0XC;
    // bne         $v0, $zero, L_8001C83C
    if (ctx->r2 != 0) {
        // or          $v1, $a1, $zero
        ctx->r3 = ctx->r5 | 0;
        goto L_8001C83C;
    }
    // or          $v1, $a1, $zero
    ctx->r3 = ctx->r5 | 0;
    // lui         $v0, 0x8009
    ctx->r2 = S32(0X8009 << 16);
    // addiu       $v0, $v0, 0x3E2
    ctx->r2 = ADD32(ctx->r2, 0X3E2);
    // or          $s1, $v0, $zero
    ctx->r17 = ctx->r2 | 0;
    // lui         $s5, 0x8009
    ctx->r21 = S32(0X8009 << 16);
    // lw          $s5, -0x1530($s5)
    ctx->r21 = MEM_W(-0X1530, ctx->r21);
    // lui         $s0, 0x8009
    ctx->r16 = S32(0X8009 << 16);
    // lw          $s0, -0x1528($s0)
    ctx->r16 = MEM_W(-0X1528, ctx->r16);
    // lw          $t0, 0x78($sp)
    ctx->r8 = MEM_W(0X78, ctx->r29);
    // lb          $s3, 0x1($s0)
    ctx->r19 = MEM_B(0X1, ctx->r16);
    // andi        $s6, $s3, 0x7F
    ctx->r22 = ctx->r19 & 0X7F;
    // and         $s3, $s3, $t0
    ctx->r19 = ctx->r19 & ctx->r8;
    // lw          $s2, 0x70($sp)
    ctx->r18 = MEM_W(0X70, ctx->r29);
    // sll         $s4, $s2, 6
    ctx->r20 = S32(ctx->r18) << 6;
    // addu        $s4, $s4, $s5
    ctx->r20 = ADD32(ctx->r20, ctx->r21);
    // sll         $s4, $s6, 6
    ctx->r20 = S32(ctx->r22) << 6;
    // addu        $s7, $s4, $s5
    ctx->r23 = ADD32(ctx->r20, ctx->r21);
    // bgez        $s3, L_8001C610
    if (SIGNED(ctx->r19) >= 0) {
        // nop
    
        goto L_8001C610;
    }
    // nop

    // addiu       $s6, $zero, -0x5
    ctx->r22 = ADD32(0, -0X5);
    // addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // bne         $s2, $zero, L_8001C618
    if (ctx->r18 != 0) {
        // addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
        goto L_8001C618;
    }
    // addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // j           L_8001C83C
    // nop

    goto L_8001C83C;
    // nop

L_8001C610:
    // j           L_8001C660
    // lwc1        $f21, 0x0($s7)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X0, ctx->r23);
    goto L_8001C660;
    // lwc1        $f21, 0x0($s7)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X0, ctx->r23);
L_8001C618:
    // lb          $s3, 0x1($s0)
    ctx->r19 = MEM_B(0X1, ctx->r16);
    // and         $s3, $s3, $t0
    ctx->r19 = ctx->r19 & ctx->r8;
    // bgez        $s3, L_8001C63C
    if (SIGNED(ctx->r19) >= 0) {
        // nop
    
        goto L_8001C63C;
    }
    // nop

    // addiu       $s6, $zero, -0x1
    ctx->r22 = ADD32(0, -0X1);
    // addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // bne         $s2, $zero, L_8001C618
    if (ctx->r18 != 0) {
        // addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
        goto L_8001C618;
    }
    // addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
    // j           L_8001C83C
    // sll         $s4, $s3, 6
    ctx->r20 = S32(ctx->r19) << 6;
    goto L_8001C83C;
L_8001C63C:
    // sll         $s4, $s3, 6
    ctx->r20 = S32(ctx->r19) << 6;
    // addu        $s7, $s4, $s5
    ctx->r23 = ADD32(ctx->r20, ctx->r21);
    // addu        $s1, $v0, $s3
    ctx->r17 = ADD32(ctx->r2, ctx->r19);
    // lbu         $s4, 0x0($s0)
    ctx->r20 = MEM_BU(0X0, ctx->r16);
    // beq         $s4, $s6, L_8001C694
    if (ctx->r20 == ctx->r22) {
        // or          $s6, $s3, $zero
        ctx->r22 = ctx->r19 | 0;
        goto L_8001C694;
    }
    // or          $s6, $s3, $zero
    ctx->r22 = ctx->r19 | 0;
    // lwc1        $f21, 0x0($s7)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X0, ctx->r23);
    // sll         $v1, $s4, 6
    ctx->r3 = S32(ctx->r20) << 6;
    // addu        $v1, $v1, $s5
    ctx->r3 = ADD32(ctx->r3, ctx->r21);
L_8001C660:
    // lwc1        $f0, 0x0($v1)
    ctx->f0.u32l = MEM_W(0X0, ctx->r3);
    // lwc1        $f1, 0x4($v1)
    ctx->f_odd[(1 - 1) * 2] = MEM_W(0X4, ctx->r3);
    // lwc1        $f2, 0x8($v1)
    ctx->f2.u32l = MEM_W(0X8, ctx->r3);
    // lwc1        $f3, 0x10($v1)
    ctx->f_odd[(3 - 1) * 2] = MEM_W(0X10, ctx->r3);
    // lwc1        $f4, 0x14($v1)
    ctx->f4.u32l = MEM_W(0X14, ctx->r3);
    // lwc1        $f5, 0x18($v1)
    ctx->f_odd[(5 - 1) * 2] = MEM_W(0X18, ctx->r3);
    // lwc1        $f6, 0x20($v1)
    ctx->f6.u32l = MEM_W(0X20, ctx->r3);
    // lwc1        $f7, 0x24($v1)
    ctx->f_odd[(7 - 1) * 2] = MEM_W(0X24, ctx->r3);
    // lwc1        $f8, 0x28($v1)
    ctx->f8.u32l = MEM_W(0X28, ctx->r3);
    // lwc1        $f9, 0x30($v1)
    ctx->f_odd[(9 - 1) * 2] = MEM_W(0X30, ctx->r3);
    // lwc1        $f10, 0x34($v1)
    ctx->f10.u32l = MEM_W(0X34, ctx->r3);
    // j           L_8001C6C8
    // lwc1        $f11, 0x38($v1)
    ctx->f_odd[(11 - 1) * 2] = MEM_W(0X38, ctx->r3);
    goto L_8001C6C8;
    // lwc1        $f11, 0x38($v1)
    ctx->f_odd[(11 - 1) * 2] = MEM_W(0X38, ctx->r3);
L_8001C694:
    // mov.s       $f0, $f12
    CHECK_FR(ctx, 0);
    CHECK_FR(ctx, 12);
    ctx->f0.fl = ctx->f12.fl;
    // mov.s       $f1, $f13
    CHECK_FR(ctx, 1);
    CHECK_FR(ctx, 13);
    ctx->f1.fl = ctx->f13.fl;
    // mov.s       $f2, $f14
    CHECK_FR(ctx, 2);
    CHECK_FR(ctx, 14);
    ctx->f2.fl = ctx->f14.fl;
    // mov.s       $f3, $f15
    CHECK_FR(ctx, 3);
    CHECK_FR(ctx, 15);
    ctx->f3.fl = ctx->f15.fl;
    // mov.s       $f4, $f16
    CHECK_FR(ctx, 4);
    CHECK_FR(ctx, 16);
    ctx->f4.fl = ctx->f16.fl;
    // mov.s       $f5, $f17
    CHECK_FR(ctx, 5);
    CHECK_FR(ctx, 17);
    ctx->f5.fl = ctx->f17.fl;
    // mov.s       $f6, $f18
    CHECK_FR(ctx, 6);
    CHECK_FR(ctx, 18);
    ctx->f6.fl = ctx->f18.fl;
    // mov.s       $f7, $f19
    CHECK_FR(ctx, 7);
    CHECK_FR(ctx, 19);
    ctx->f7.fl = ctx->f19.fl;
    // mov.s       $f8, $f20
    CHECK_FR(ctx, 8);
    CHECK_FR(ctx, 20);
    ctx->f8.fl = ctx->f20.fl;
    // mov.s       $f9, $f21
    CHECK_FR(ctx, 9);
    CHECK_FR(ctx, 21);
    ctx->f9.fl = ctx->f21.fl;
    // mov.s       $f10, $f22
    CHECK_FR(ctx, 10);
    CHECK_FR(ctx, 22);
    ctx->f10.fl = ctx->f22.fl;
    // lwc1        $f21, 0x0($s7)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X0, ctx->r23);
    // mov.s       $f11, $f23
    CHECK_FR(ctx, 11);
    CHECK_FR(ctx, 23);
    ctx->f11.fl = ctx->f23.fl;
L_8001C6C8:
    // lwc1        $f22, 0x4($s7)
    ctx->f22.u32l = MEM_W(0X4, ctx->r23);
    // mul.s       $f24, $f21, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f24.fl = MUL_S(ctx->f21.fl, ctx->f0.fl);
    // lwc1        $f30, 0x8($s7)
    ctx->f30.u32l = MEM_W(0X8, ctx->r23);
    // mul.s       $f26, $f21, $f1
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f26.fl = MUL_S(ctx->f21.fl, ctx->f1.fl);
    // lwc1        $f28, 0x10($s7)
    ctx->f28.u32l = MEM_W(0X10, ctx->r23);
    // mul.s       $f25, $f22, $f3
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f25.fl = MUL_S(ctx->f22.fl, ctx->f3.fl);
    // lwc1        $f29, 0x14($s7)
    ctx->f_odd[(29 - 1) * 2] = MEM_W(0X14, ctx->r23);
    // mul.s       $f27, $f22, $f4
    CHECK_FR(ctx, 27);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f27.fl = MUL_S(ctx->f22.fl, ctx->f4.fl);
    // add.s       $f12, $f24, $f25
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f12.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f24, $f30, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f24.fl = MUL_S(ctx->f30.fl, ctx->f6.fl);
    // nop

    // mul.s       $f25, $f30, $f7
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f7.fl);
    // add.s       $f12, $f12, $f24
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 12);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f12.fl); NAN_CHECK(ctx->f24.fl);
    ctx->f12.fl = ctx->f12.fl + ctx->f24.fl;
    // mul.s       $f24, $f21, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f24.fl = MUL_S(ctx->f21.fl, ctx->f2.fl);
    // swc1        $f12, 0x0($s7)
    MEM_W(0X0, ctx->r23) = ctx->f12.u32l;
    // add.s       $f13, $f25, $f26
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f26.fl);
    ctx->f13.fl = ctx->f25.fl + ctx->f26.fl;
    // mul.s       $f25, $f22, $f5
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f25.fl = MUL_S(ctx->f22.fl, ctx->f5.fl);
    // add.s       $f13, $f13, $f27
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 13);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f13.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f13.fl = ctx->f13.fl + ctx->f27.fl;
    // add.s       $f14, $f24, $f25
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f14.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f25, $f30, $f8
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f8.fl);
    // add.s       $f14, $f14, $f25
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 14);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f14.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f14.fl = ctx->f14.fl + ctx->f25.fl;
    // swc1        $f13, 0x4($s7)
    MEM_W(0X4, ctx->r23) = ctx->f_odd[(13 - 1) * 2];
    // mul.s       $f24, $f28, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f24.fl = MUL_S(ctx->f28.fl, ctx->f0.fl);
    // lwc1        $f30, 0x18($s7)
    ctx->f30.u32l = MEM_W(0X18, ctx->r23);
    // mul.s       $f26, $f28, $f1
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f26.fl = MUL_S(ctx->f28.fl, ctx->f1.fl);
    // lwc1        $f21, 0x20($s7)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X20, ctx->r23);
    // mul.s       $f25, $f29, $f3
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f25.fl = MUL_S(ctx->f29.fl, ctx->f3.fl);
    // lwc1        $f22, 0x24($s7)
    ctx->f22.u32l = MEM_W(0X24, ctx->r23);
    // mul.s       $f27, $f29, $f4
    CHECK_FR(ctx, 27);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f27.fl = MUL_S(ctx->f29.fl, ctx->f4.fl);
    // add.s       $f15, $f24, $f25
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f15.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f24, $f30, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f24.fl = MUL_S(ctx->f30.fl, ctx->f6.fl);
    // swc1        $f14, 0x8($s7)
    MEM_W(0X8, ctx->r23) = ctx->f14.u32l;
    // mul.s       $f25, $f30, $f7
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f7.fl);
    // add.s       $f15, $f15, $f24
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 15);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f15.fl); NAN_CHECK(ctx->f24.fl);
    ctx->f15.fl = ctx->f15.fl + ctx->f24.fl;
    // mul.s       $f24, $f28, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f24.fl = MUL_S(ctx->f28.fl, ctx->f2.fl);
    // swc1        $f15, 0x10($s7)
    MEM_W(0X10, ctx->r23) = ctx->f_odd[(15 - 1) * 2];
    // add.s       $f16, $f25, $f26
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f26.fl);
    ctx->f16.fl = ctx->f25.fl + ctx->f26.fl;
    // mul.s       $f25, $f29, $f5
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f25.fl = MUL_S(ctx->f29.fl, ctx->f5.fl);
    // add.s       $f16, $f16, $f27
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 16);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f16.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f16.fl = ctx->f16.fl + ctx->f27.fl;
    // add.s       $f17, $f24, $f25
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f17.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f25, $f30, $f8
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f8.fl);
    // add.s       $f17, $f17, $f25
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 17);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f17.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f17.fl = ctx->f17.fl + ctx->f25.fl;
    // swc1        $f16, 0x14($s7)
    MEM_W(0X14, ctx->r23) = ctx->f16.u32l;
    // mul.s       $f24, $f21, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f24.fl = MUL_S(ctx->f21.fl, ctx->f0.fl);
    // lwc1        $f30, 0x28($s7)
    ctx->f30.u32l = MEM_W(0X28, ctx->r23);
    // mul.s       $f26, $f21, $f1
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f26.fl = MUL_S(ctx->f21.fl, ctx->f1.fl);
    // lwc1        $f28, 0x30($s7)
    ctx->f28.u32l = MEM_W(0X30, ctx->r23);
    // mul.s       $f25, $f22, $f3
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f25.fl = MUL_S(ctx->f22.fl, ctx->f3.fl);
    // lwc1        $f29, 0x34($s7)
    ctx->f_odd[(29 - 1) * 2] = MEM_W(0X34, ctx->r23);
    // mul.s       $f27, $f22, $f4
    CHECK_FR(ctx, 27);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f27.fl = MUL_S(ctx->f22.fl, ctx->f4.fl);
    // add.s       $f18, $f24, $f25
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f18.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f24, $f30, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f24.fl = MUL_S(ctx->f30.fl, ctx->f6.fl);
    // swc1        $f17, 0x18($s7)
    MEM_W(0X18, ctx->r23) = ctx->f_odd[(17 - 1) * 2];
    // mul.s       $f25, $f30, $f7
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f7.fl);
    // add.s       $f18, $f18, $f24
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 18);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f18.fl); NAN_CHECK(ctx->f24.fl);
    ctx->f18.fl = ctx->f18.fl + ctx->f24.fl;
    // mul.s       $f24, $f21, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f24.fl = MUL_S(ctx->f21.fl, ctx->f2.fl);
    // add.s       $f19, $f25, $f26
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 26);
    NAN_CHECK(ctx->f25.fl); NAN_CHECK(ctx->f26.fl);
    ctx->f19.fl = ctx->f25.fl + ctx->f26.fl;
    // mul.s       $f25, $f22, $f5
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f25.fl = MUL_S(ctx->f22.fl, ctx->f5.fl);
    // add.s       $f19, $f19, $f27
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 19);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f19.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f19.fl = ctx->f19.fl + ctx->f27.fl;
    // swc1        $f18, 0x20($s7)
    MEM_W(0X20, ctx->r23) = ctx->f18.u32l;
    // add.s       $f20, $f24, $f25
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f20.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f25, $f30, $f8
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f8.fl);
    // add.s       $f20, $f20, $f25
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 20);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f20.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f20.fl = ctx->f20.fl + ctx->f25.fl;
    // swc1        $f19, 0x24($s7)
    MEM_W(0X24, ctx->r23) = ctx->f_odd[(19 - 1) * 2];
    // mul.s       $f24, $f28, $f0
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f24.fl = MUL_S(ctx->f28.fl, ctx->f0.fl);
    // lwc1        $f30, 0x38($s7)
    ctx->f30.u32l = MEM_W(0X38, ctx->r23);
    // mul.s       $f26, $f28, $f1
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 1);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f1.fl);
    ctx->f26.fl = MUL_S(ctx->f28.fl, ctx->f1.fl);
    // add.s       $f24, $f24, $f9
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 9);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f9.fl);
    ctx->f24.fl = ctx->f24.fl + ctx->f9.fl;
    // mul.s       $f25, $f29, $f3
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 3);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f3.fl);
    ctx->f25.fl = MUL_S(ctx->f29.fl, ctx->f3.fl);
    // add.s       $f26, $f26, $f10
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 10);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f10.fl);
    ctx->f26.fl = ctx->f26.fl + ctx->f10.fl;
    // mul.s       $f27, $f29, $f4
    CHECK_FR(ctx, 27);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 4);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f4.fl);
    ctx->f27.fl = MUL_S(ctx->f29.fl, ctx->f4.fl);
    // add.s       $f21, $f24, $f25
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f21.fl = ctx->f24.fl + ctx->f25.fl;
    // add.s       $f22, $f26, $f27
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 26);
    CHECK_FR(ctx, 27);
    NAN_CHECK(ctx->f26.fl); NAN_CHECK(ctx->f27.fl);
    ctx->f22.fl = ctx->f26.fl + ctx->f27.fl;
    // mul.s       $f24, $f30, $f6
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 6);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f6.fl);
    ctx->f24.fl = MUL_S(ctx->f30.fl, ctx->f6.fl);
    // swc1        $f20, 0x28($s7)
    MEM_W(0X28, ctx->r23) = ctx->f20.u32l;
    // mul.s       $f25, $f30, $f7
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 7);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f7.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f7.fl);
    // add.s       $f21, $f21, $f24
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 21);
    CHECK_FR(ctx, 24);
    NAN_CHECK(ctx->f21.fl); NAN_CHECK(ctx->f24.fl);
    ctx->f21.fl = ctx->f21.fl + ctx->f24.fl;
    // mul.s       $f24, $f28, $f2
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 28);
    CHECK_FR(ctx, 2);
    NAN_CHECK(ctx->f28.fl); NAN_CHECK(ctx->f2.fl);
    ctx->f24.fl = MUL_S(ctx->f28.fl, ctx->f2.fl);
    // swc1        $f21, 0x30($s7)
    MEM_W(0X30, ctx->r23) = ctx->f_odd[(21 - 1) * 2];
    // add.s       $f22, $f22, $f25
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f22.fl = ctx->f22.fl + ctx->f25.fl;
    // add.s       $f24, $f24, $f11
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 11);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f11.fl);
    ctx->f24.fl = ctx->f24.fl + ctx->f11.fl;
    // mul.s       $f25, $f29, $f5
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 29);
    CHECK_FR(ctx, 5);
    NAN_CHECK(ctx->f29.fl); NAN_CHECK(ctx->f5.fl);
    ctx->f25.fl = MUL_S(ctx->f29.fl, ctx->f5.fl);
    // swc1        $f22, 0x34($s7)
    MEM_W(0X34, ctx->r23) = ctx->f22.u32l;
    // add.s       $f23, $f24, $f25
    CHECK_FR(ctx, 23);
    CHECK_FR(ctx, 24);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f24.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f23.fl = ctx->f24.fl + ctx->f25.fl;
    // mul.s       $f25, $f30, $f8
    CHECK_FR(ctx, 25);
    CHECK_FR(ctx, 30);
    CHECK_FR(ctx, 8);
    NAN_CHECK(ctx->f30.fl); NAN_CHECK(ctx->f8.fl);
    ctx->f25.fl = MUL_S(ctx->f30.fl, ctx->f8.fl);
    // add.s       $f23, $f23, $f25
    CHECK_FR(ctx, 23);
    CHECK_FR(ctx, 23);
    CHECK_FR(ctx, 25);
    NAN_CHECK(ctx->f23.fl); NAN_CHECK(ctx->f25.fl);
    ctx->f23.fl = ctx->f23.fl + ctx->f25.fl;
    // swc1        $f23, 0x38($s7)
    MEM_W(0X38, ctx->r23) = ctx->f_odd[(23 - 1) * 2];
    // lbu         $s3, 0x0($s1)
    ctx->r19 = MEM_BU(0X0, ctx->r17);
    // addiu       $s2, $s2, -0x1
    ctx->r18 = ADD32(ctx->r18, -0X1);
    // bne         $s3, $zero, L_8001C8A0
    if (ctx->r19 != 0) {
        // sll         $s3, $s3, 2
        ctx->r19 = S32(ctx->r19) << 2;
        goto L_8001C8A0;
    }
    // sll         $s3, $s3, 2
    ctx->r19 = S32(ctx->r19) << 2;
L_8001C834:
    // bne         $s2, $zero, L_8001C618
    if (ctx->r18 != 0) {
        // addiu       $s0, $s0, 0x10
        ctx->r16 = ADD32(ctx->r16, 0X10);
        goto L_8001C618;
    }
    // addiu       $s0, $s0, 0x10
    ctx->r16 = ADD32(ctx->r16, 0X10);
L_8001C83C:
    // lw          $ra, 0x0($sp)
    ctx->r31 = MEM_W(0X0, ctx->r29);
    // lwc1        $f20, 0x4($sp)
    ctx->f20.u32l = MEM_W(0X4, ctx->r29);
    // lwc1        $f21, 0x8($sp)
    ctx->f_odd[(21 - 1) * 2] = MEM_W(0X8, ctx->r29);
    // lwc1        $f22, 0xC($sp)
    ctx->f22.u32l = MEM_W(0XC, ctx->r29);
    // lwc1        $f23, 0x10($sp)
    ctx->f_odd[(23 - 1) * 2] = MEM_W(0X10, ctx->r29);
    // lwc1        $f24, 0x14($sp)
    ctx->f24.u32l = MEM_W(0X14, ctx->r29);
    // lwc1        $f25, 0x18($sp)
    ctx->f_odd[(25 - 1) * 2] = MEM_W(0X18, ctx->r29);
    // lwc1        $f26, 0x1C($sp)
    ctx->f26.u32l = MEM_W(0X1C, ctx->r29);
    // lwc1        $f27, 0x20($sp)
    ctx->f_odd[(27 - 1) * 2] = MEM_W(0X20, ctx->r29);
    // lwc1        $f28, 0x24($sp)
    ctx->f28.u32l = MEM_W(0X24, ctx->r29);
    // lwc1        $f29, 0x28($sp)
    ctx->f_odd[(29 - 1) * 2] = MEM_W(0X28, ctx->r29);
    // lwc1        $f30, 0x2C($sp)
    ctx->f30.u32l = MEM_W(0X2C, ctx->r29);
    // lwc1        $f31, 0x30($sp)
    ctx->f_odd[(31 - 1) * 2] = MEM_W(0X30, ctx->r29);
    // addiu       $sp, $sp, 0x38
    ctx->r29 = ADD32(ctx->r29, 0X38);
    // lw          $ra, 0x0($sp)
    ctx->r31 = MEM_W(0X0, ctx->r29);
    // lw          $s0, 0x4($sp)
    ctx->r16 = MEM_W(0X4, ctx->r29);
    // lw          $s1, 0x8($sp)
    ctx->r17 = MEM_W(0X8, ctx->r29);
    // lw          $s2, 0xC($sp)
    ctx->r18 = MEM_W(0XC, ctx->r29);
    // lw          $s3, 0x10($sp)
    ctx->r19 = MEM_W(0X10, ctx->r29);
    // lw          $s4, 0x14($sp)
    ctx->r20 = MEM_W(0X14, ctx->r29);
    // lw          $s5, 0x18($sp)
    ctx->r21 = MEM_W(0X18, ctx->r29);
    // lw          $s6, 0x1C($sp)
    ctx->r22 = MEM_W(0X1C, ctx->r29);
    // lw          $s7, 0x20($sp)
    ctx->r23 = MEM_W(0X20, ctx->r29);
    // jr          $ra
    // addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
    return;
    // addiu       $sp, $sp, 0x28
    ctx->r29 = ADD32(ctx->r29, 0X28);
L_8001C8A0:
    // lui         $s1, 0x8009
    ctx->r17 = S32(0X8009 << 16);
    // addiu       $s1, $s1, 0x444
    ctx->r17 = ADD32(ctx->r17, 0X444);
    // addu        $s1, $s1, $s3
    ctx->r17 = ADD32(ctx->r17, ctx->r19);
    // lw          $s1, 0x0($s1)
    ctx->r17 = MEM_W(0X0, ctx->r17);
    // nop

    // nop

    // lui         $at, 0x41F0
    ctx->r1 = S32(0X41F0 << 16);
    // lwc1        $f22, 0x34($s7)
    ctx->f22.u32l = MEM_W(0X34, ctx->r23);
    // mtc1        $at, $f0
    ctx->f0.u32l = ctx->r1;
    // nop

    // add.s       $f22, $f22, $f0
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 22);
    CHECK_FR(ctx, 0);
    NAN_CHECK(ctx->f22.fl); NAN_CHECK(ctx->f0.fl);
    ctx->f22.fl = ctx->f22.fl + ctx->f0.fl;
    // j           L_8001C834
    // swc1        $f22, 0x34($s7)
    MEM_W(0X34, ctx->r23) = ctx->f22.u32l;
    goto L_8001C834;
    // swc1        $f22, 0x34($s7)
    MEM_W(0X34, ctx->r23) = ctx->f22.u32l;
;}
