multiline_comment|/* include/asm-sparc/processor.h&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ASM_SPARC_PROCESSOR_H
DECL|macro|__ASM_SPARC_PROCESSOR_H
mdefine_line|#define __ASM_SPARC_PROCESSOR_H
macro_line|#include &lt;linux/sched.h&gt;  /* For intr_count */
macro_line|#include &lt;asm/ptrace.h&gt;   /* For pt_regs declaration */
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * Write Protection works right in supervisor mode on the Sparc&n; */
macro_line|#if 0  /* Let&squot;s try this out ;) */
mdefine_line|#define wp_works_ok 1
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
macro_line|#else
r_extern
r_char
id|wp_works_ok
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * User space process size: 3GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; *&n; * With the way identity mapping works on the sun4c, this is the best&n; * value to use.&n; *&n; * This has to be looked into for a unified sun4c/sun4m task size.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xC000000UL)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
multiline_comment|/* The first four entries here MUST be the first four. This allows me to&n; * do %lo(offset) loads and stores in entry.S. See TRAP_WIN_CLEAN to see&n; * why.&n; */
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
DECL|member|yreg
r_int
r_int
id|yreg
suffix:semicolon
DECL|member|align
r_int
r_int
id|align
suffix:semicolon
multiline_comment|/* to get 8-byte alignment  XXX  */
DECL|member|reg_window
r_int
r_int
id|reg_window
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|pgd_ptr
r_int
r_int
id|pgd_ptr
suffix:semicolon
DECL|member|context
r_int
id|context
suffix:semicolon
multiline_comment|/* The context allocated to this thread */
multiline_comment|/* 8 local registers + 8 in registers * 24 register windows.&n; * Most sparcs I know of only have 7 or 8 windows implemented,&n; * we determine how many at boot time and store that value&n; * in nwindows.&n; */
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
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_task, (PAGE_OFFSET), (0xff000000UL), &bslash;&n;&t;&t;    0x0 , VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;&t;(long) &amp;swapper_pg_dir, -1,  &bslash;&n;        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, &bslash;&n;}
multiline_comment|/* The thread_frame is what needs to be set up in certain circumstances&n; * upon entry to a trap. It is also loaded sometimes during a window&n; * spill if things don&squot;t go right (bad user stack pointer). In reality&n; * it is not per-process per se, it just sits in the kernel stack while&n; * the current process is in a handler then it is basically forgotten&n; * about the next time flow control goes back to that process.&n; */
multiline_comment|/* Sparc stack save area allocated for each save, not very exciting. */
DECL|struct|sparc_save_stack
r_struct
id|sparc_save_stack
(brace
DECL|member|locals
r_int
r_int
id|locals
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|ins
r_int
r_int
id|ins
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|padd
r_int
r_int
id|padd
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g2, 0x20, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* disable traps */
l_string|&quot;ld %0,%%g3&bslash;n&bslash;t&quot;
l_string|&quot;add %%g3,1,%%g3&bslash;n&bslash;t&quot;
l_string|&quot;st %%g3,%0&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g2, 0x0, %%psr&bslash;n&bslash;t&quot;
multiline_comment|/* enable traps */
suffix:colon
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;memory&quot;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %%g2&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g2, 0x20, %%psr&bslash;n&bslash;t&quot;
l_string|&quot;ld %0,%%g3&bslash;n&bslash;t&quot;
l_string|&quot;sub %%g3,1,%%g3&bslash;n&bslash;t&quot;
l_string|&quot;st %%g3,%0&bslash;n&bslash;t&quot;
l_string|&quot;wr %%g2, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
suffix:colon
l_string|&quot;g2&quot;
comma
l_string|&quot;g3&quot;
comma
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
DECL|function|start_thread
r_static
r_inline
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|sp
comma
r_int
r_int
id|fp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_thread called, halting..n&quot;
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_SPARC_PROCESSOR_H */
eof
