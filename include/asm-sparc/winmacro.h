multiline_comment|/* $Id: winmacro.h,v 1.11 1995/11/25 02:33:23 davem Exp $&n; * winmacro.h: Window loading-unloading macros.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_WINMACRO_H
DECL|macro|_SPARC_WINMACRO_H
mdefine_line|#define _SPARC_WINMACRO_H
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/psr.h&gt;
multiline_comment|/* These are just handy. */
DECL|macro|_SV
mdefine_line|#define _SV&t;save&t;%sp, -REGWIN_SZ, %sp
DECL|macro|_RS
mdefine_line|#define _RS     restore 
DECL|macro|FLUSH_ALL_KERNEL_WINDOWS
mdefine_line|#define FLUSH_ALL_KERNEL_WINDOWS &bslash;&n;&t;_SV; _SV; _SV; _SV; _SV; _SV; _SV; &bslash;&n;&t;_RS; _RS; _RS; _RS; _RS; _RS; _RS;
multiline_comment|/* Store the register window onto the 8-byte aligned area starting&n; * at %reg.  It might be %sp, it might not, we don&squot;t care.&n; */
DECL|macro|STORE_WINDOW
mdefine_line|#define STORE_WINDOW(reg) &bslash;&n;&t;std&t;%l0, [%reg + RW_L0]; &bslash;&n;&t;std&t;%l2, [%reg + RW_L2]; &bslash;&n;&t;std&t;%l4, [%reg + RW_L4]; &bslash;&n;&t;std&t;%l6, [%reg + RW_L6]; &bslash;&n;&t;std&t;%i0, [%reg + RW_I0]; &bslash;&n;&t;std&t;%i2, [%reg + RW_I2]; &bslash;&n;&t;std&t;%i4, [%reg + RW_I4]; &bslash;&n;&t;std&t;%i6, [%reg + RW_I6];
multiline_comment|/* Load a register window from the area beginning at %reg. */
DECL|macro|LOAD_WINDOW
mdefine_line|#define LOAD_WINDOW(reg) &bslash;&n;&t;ldd&t;[%reg + RW_L0], %l0; &bslash;&n;&t;ldd&t;[%reg + RW_L2], %l2; &bslash;&n;&t;ldd&t;[%reg + RW_L4], %l4; &bslash;&n;&t;ldd&t;[%reg + RW_L6], %l6; &bslash;&n;&t;ldd&t;[%reg + RW_I0], %i0; &bslash;&n;&t;ldd&t;[%reg + RW_I2], %i2; &bslash;&n;&t;ldd&t;[%reg + RW_I4], %i4; &bslash;&n;&t;ldd&t;[%reg + RW_I6], %i6;
multiline_comment|/* Loading and storing struct pt_reg trap frames. */
DECL|macro|LOAD_PT_INS
mdefine_line|#define LOAD_PT_INS(base_reg) &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_I0], %i0; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_I2], %i2; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_I4], %i4; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_I6], %i6;
DECL|macro|LOAD_PT_GLOBALS
mdefine_line|#define LOAD_PT_GLOBALS(base_reg) &bslash;&n;        ld      [%base_reg + STACKFRAME_SZ + PT_G1], %g1; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_G2], %g2; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_G4], %g4; &bslash;&n;        ldd     [%base_reg + STACKFRAME_SZ + PT_G6], %g6;
DECL|macro|LOAD_PT_YREG
mdefine_line|#define LOAD_PT_YREG(base_reg, scratch) &bslash;&n;        ld      [%base_reg + STACKFRAME_SZ + PT_Y], %scratch; &bslash;&n;        wr      %scratch, 0x0, %y;
DECL|macro|LOAD_PT_PRIV
mdefine_line|#define LOAD_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc) &bslash;&n;        ld      [%base_reg + STACKFRAME_SZ + PT_PSR], %pt_psr; &bslash;&n;        ld      [%base_reg + STACKFRAME_SZ + PT_PC], %pt_pc; &bslash;&n;        ld      [%base_reg + STACKFRAME_SZ + PT_NPC], %pt_npc;
DECL|macro|LOAD_PT_ALL
mdefine_line|#define LOAD_PT_ALL(base_reg, pt_psr, pt_pc, pt_npc, scratch) &bslash;&n;        LOAD_PT_YREG(base_reg, scratch) &bslash;&n;        LOAD_PT_INS(base_reg) &bslash;&n;        LOAD_PT_GLOBALS(base_reg) &bslash;&n;        LOAD_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc)
DECL|macro|STORE_PT_INS
mdefine_line|#define STORE_PT_INS(base_reg) &bslash;&n;        std     %i0, [%base_reg + STACKFRAME_SZ + PT_I0]; &bslash;&n;        std     %i2, [%base_reg + STACKFRAME_SZ + PT_I2]; &bslash;&n;        std     %i4, [%base_reg + STACKFRAME_SZ + PT_I4]; &bslash;&n;        std     %i6, [%base_reg + STACKFRAME_SZ + PT_I6];
DECL|macro|STORE_PT_GLOBALS
mdefine_line|#define STORE_PT_GLOBALS(base_reg) &bslash;&n;        st      %g1, [%base_reg + STACKFRAME_SZ + PT_G1]; &bslash;&n;        std     %g2, [%base_reg + STACKFRAME_SZ + PT_G2]; &bslash;&n;        std     %g4, [%base_reg + STACKFRAME_SZ + PT_G4]; &bslash;&n;        std     %g6, [%base_reg + STACKFRAME_SZ + PT_G6];
DECL|macro|STORE_PT_YREG
mdefine_line|#define STORE_PT_YREG(base_reg, scratch) &bslash;&n;        rd      %y, %scratch; &bslash;&n;        st      %scratch, [%base_reg + STACKFRAME_SZ + PT_Y];
DECL|macro|STORE_PT_PRIV
mdefine_line|#define STORE_PT_PRIV(base_reg, pt_psr, pt_pc, pt_npc, pt_wim) &bslash;&n;        st      %pt_psr, [%base_reg + STACKFRAME_SZ + PT_PSR]; &bslash;&n;        st      %pt_pc, [%base_reg + STACKFRAME_SZ + PT_PC]; &bslash;&n;        st      %pt_npc, [%base_reg + STACKFRAME_SZ + PT_NPC]; &bslash;&n;        st      %pt_wim, [%base_reg + STACKFRAME_SZ + PT_WIM];
DECL|macro|STORE_PT_ALL
mdefine_line|#define STORE_PT_ALL(base_reg, reg_psr, reg_pc, reg_npc, reg_wim, g_scratch) &bslash;&n;        STORE_PT_PRIV(base_reg, reg_psr, reg_pc, reg_npc, reg_wim) &bslash;&n;        STORE_PT_GLOBALS(base_reg) &bslash;&n;        STORE_PT_YREG(base_reg, g_scratch) &bslash;&n;        STORE_PT_INS(base_reg)
DECL|macro|SAVE_BOLIXED_USER_STACK
mdefine_line|#define SAVE_BOLIXED_USER_STACK(cur_reg, scratch) &bslash;&n;        ld       [%cur_reg + THREAD_W_SAVED], %scratch; &bslash;&n;        sll      %scratch, 2, %scratch; &bslash;&n;        add      %scratch, %cur_reg, %scratch; &bslash;&n;        st       %sp, [%scratch + THREAD_STACK_PTRS]; &bslash;&n;        sub      %scratch, %cur_reg, %scratch; &bslash;&n;        sll      %scratch, 4, %scratch; &bslash;&n;        add      %scratch, %cur_reg, %scratch; &bslash;&n;        STORE_WINDOW(scratch + THREAD_REG_WINDOW); &bslash;&n;        sub      %scratch, %cur_reg, %scratch; &bslash;&n;        srl      %scratch, 6, %scratch; &bslash;&n;        add      %scratch, 1, %scratch; &bslash;&n;        st       %scratch, [%cur_reg + THREAD_W_SAVED];
multiline_comment|/* For now on a uniprocessor this is ok. */
DECL|macro|LOAD_CURRENT
mdefine_line|#define LOAD_CURRENT(dest_reg) &bslash;&n;        sethi    %hi(C_LABEL(current_set)), %dest_reg; &bslash;&n;        ld       [%dest_reg + %lo(C_LABEL(current_set))], %dest_reg;
macro_line|#endif /* !(_SPARC_WINMACRO_H) */
eof