multiline_comment|/* include/asm-sparc/processor.h&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC_PROCESSOR_H
DECL|macro|__ASM_SPARC_PROCESSOR_H
mdefine_line|#define __ASM_SPARC_PROCESSOR_H
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 1
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
multiline_comment|/*&n; * Write Protection works right in supervisor mode on the Sparc&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
multiline_comment|/*&n; * User space process size: 3GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; *&n; * &quot;this is gonna have to change to 1gig for the sparc&quot; - David S. Miller&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xc0000000UL)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
multiline_comment|/* The first five entries here MUST be the first four. This allows me to&n; * do %lo(offset) loads and stores in entry.S. See TRAP_WIN_CLEAN to see&n; * why.&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|uwindows
r_int
r_int
id|uwindows
suffix:semicolon
multiline_comment|/* how many user windows are in the set */
DECL|member|wim
r_int
r_int
id|wim
suffix:semicolon
multiline_comment|/* user&squot;s window invalid mask */
DECL|member|w_saved
r_int
r_int
id|w_saved
suffix:semicolon
multiline_comment|/* how many windows saved in reg_window[] */
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* kernel stack pointer */
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
multiline_comment|/* user&squot;s sp, throw reg windows here */
DECL|member|psr
r_int
r_int
id|psr
suffix:semicolon
multiline_comment|/* save for condition codes */
DECL|member|reg_window
r_int
r_int
id|reg_window
(braket
l_int|16
op_star
l_int|24
)braket
suffix:semicolon
DECL|member|cr3
r_int
r_int
id|cr3
suffix:semicolon
multiline_comment|/* why changed from ptbr? */
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|npc
r_int
r_int
id|npc
suffix:semicolon
multiline_comment|/* next program counter */
multiline_comment|/* 8 local registers + 8 in registers * 24 register windows.&n; * Most sparcs I know of only have 8 windows implemented,&n; * we determine how many at boot time and store that value&n; * in nwindows.&n; */
DECL|member|globl_regs
r_int
r_int
id|globl_regs
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* global regs need to be saved too */
DECL|member|yreg
r_int
r_int
id|yreg
suffix:semicolon
DECL|member|float_regs
r_int
r_int
id|float_regs
(braket
l_int|64
)braket
suffix:semicolon
multiline_comment|/* V8 and below have 32, V9 has 64 */
)brace
suffix:semicolon
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0, 0, 0, 0, 0, 0, &bslash;&n;        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        { 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;        0, &bslash;&n;        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;}
multiline_comment|/* The thread_frame is what needs to be set up in certain circumstances&n; * upon entry to a trap. It is also loaded sometimes during a window&n; * spill if things don&squot;t go right (bad user stack pointer). In reality&n; * it is not per-process per se, it just sits in the kernel stack while&n; * the current process is in a handler then it is basically forgotten&n; * about.&n; */
DECL|struct|thread_frame
r_struct
id|thread_frame
(brace
DECL|member|thr_psr
r_int
r_int
id|thr_psr
suffix:semicolon
DECL|member|thr_pc
r_int
r_int
id|thr_pc
suffix:semicolon
DECL|member|thr_npc
r_int
r_int
id|thr_npc
suffix:semicolon
DECL|member|thr_y
r_int
r_int
id|thr_y
suffix:semicolon
DECL|member|thr_globals
r_int
r_int
id|thr_globals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|thr_outs
r_int
r_int
id|thr_outs
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * These are the &quot;cli()&quot; and &quot;sti()&quot; for software interrupts&n; * They work by increasing/decreasing the &quot;intr_count&quot; value, &n; * and as such can be nested arbitrarily.&n; */
DECL|function|start_bh_atomic
r_extern
r_inline
r_void
id|start_bh_atomic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|dummy
comma
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %2&bslash;n&bslash;t&quot;
l_string|&quot;wr %2, 0x20, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* disable traps */
l_string|&quot;ld %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;add %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;st %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;wr %2, 0x0, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* enable traps */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|psr
op_assign
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|end_bh_atomic
r_extern
r_inline
r_void
id|end_bh_atomic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|dummy
comma
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %2&bslash;n&bslash;t&quot;
l_string|&quot;wr %2, 0x20, %%psr&bslash;n&bslash;t&quot;
l_string|&quot;ld %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;sub %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;st %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;wr %2, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;r&quot;
(paren
id|psr
op_assign
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPARC_PROCESSOR_H */
eof
