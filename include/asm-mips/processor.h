multiline_comment|/*&n; * include/asm-mips/processor.h&n; *&n; * Copyright (C) 1994  Waldorf Electronics&n; * written by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_PROCESSOR_H
DECL|macro|__ASM_MIPS_PROCESSOR_H
mdefine_line|#define __ASM_MIPS_PROCESSOR_H
macro_line|#if !defined (__LANGUAGE_ASSEMBLY__)
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/*&n; * System setup and hardware bug flags..&n; */
r_extern
r_char
id|wait_available
suffix:semicolon
multiline_comment|/* only available on R4[26]00 */
r_extern
r_int
r_int
id|intr_count
suffix:semicolon
r_extern
r_int
r_int
id|event
suffix:semicolon
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; * MCA_bus hardcoded to 0 for now.&n; *&n; * This needs to be extended since MIPS systems are being delivered with&n; * numerous different types of bus systems.&n; */
r_extern
r_int
id|EISA_bus
suffix:semicolon
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * MIPS has no problems with write protection&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User space process size: 2GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x80000000UL)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
DECL|macro|NUM_FPU_REGS
mdefine_line|#define NUM_FPU_REGS&t;32
DECL|struct|mips_fpu_hard_struct
r_struct
id|mips_fpu_hard_struct
(brace
DECL|member|fp_regs
r_float
id|fp_regs
(braket
id|NUM_FPU_REGS
)braket
suffix:semicolon
DECL|member|control
r_int
r_int
id|control
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * FIXME: no fpu emulator yet (but who cares anyway?)&n; */
DECL|struct|mips_fpu_soft_struct
r_struct
id|mips_fpu_soft_struct
(brace
DECL|member|dummy
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|union|mips_fpu_union
r_union
id|mips_fpu_union
(brace
DECL|member|hard
r_struct
id|mips_fpu_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|mips_fpu_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_FPU
mdefine_line|#define INIT_FPU { &bslash;&n;&t;{{0,},} &bslash;&n;}
multiline_comment|/*&n; * If you change thread_struct remember to change the #defines below too!&n; */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
multiline_comment|/*&n;         * saved main processor registers&n;         */
DECL|member|reg16
DECL|member|reg17
DECL|member|reg18
DECL|member|reg19
DECL|member|reg20
DECL|member|reg21
DECL|member|reg22
DECL|member|reg23
r_int
r_int
id|reg16
comma
id|reg17
comma
id|reg18
comma
id|reg19
comma
id|reg20
comma
id|reg21
comma
id|reg22
comma
id|reg23
suffix:semicolon
DECL|member|reg28
DECL|member|reg29
DECL|member|reg30
DECL|member|reg31
r_int
r_int
id|reg28
comma
id|reg29
comma
id|reg30
comma
id|reg31
suffix:semicolon
multiline_comment|/*&n;&t; * saved cp0 stuff&n;&t; */
DECL|member|cp0_status
r_int
r_int
id|cp0_status
suffix:semicolon
multiline_comment|/*&n;&t; * saved fpu/fpu emulator stuff&n;&t; */
DECL|member|fpu
r_union
id|mips_fpu_union
id|fpu
suffix:semicolon
multiline_comment|/*&n;&t; * Other stuff associated with the thread&n;&t; */
DECL|member|cp0_badvaddr
r_int
r_int
id|cp0_badvaddr
suffix:semicolon
DECL|member|error_code
r_int
r_int
id|error_code
suffix:semicolon
DECL|member|trap_no
r_int
r_int
id|trap_no
suffix:semicolon
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* Top of kernel stack   */
DECL|member|pg_dir
r_int
r_int
id|pg_dir
suffix:semicolon
multiline_comment|/* L1 page table pointer */
DECL|macro|MF_FIXADE
mdefine_line|#define MF_FIXADE 1
DECL|member|mflags
r_int
r_int
id|mflags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* !defined (__LANGUAGE_ASSEMBLY__) */
multiline_comment|/*&n; * If you change the #defines remember to change thread_struct above too!&n; */
DECL|macro|TOFF_REG16
mdefine_line|#define TOFF_REG16&t;&t;0
DECL|macro|TOFF_REG17
mdefine_line|#define TOFF_REG17&t;&t;(TOFF_REG16+4)
DECL|macro|TOFF_REG18
mdefine_line|#define TOFF_REG18&t;&t;(TOFF_REG17+4)
DECL|macro|TOFF_REG19
mdefine_line|#define TOFF_REG19&t;&t;(TOFF_REG18+4)
DECL|macro|TOFF_REG20
mdefine_line|#define TOFF_REG20&t;&t;(TOFF_REG19+4)
DECL|macro|TOFF_REG21
mdefine_line|#define TOFF_REG21&t;&t;(TOFF_REG20+4)
DECL|macro|TOFF_REG22
mdefine_line|#define TOFF_REG22&t;&t;(TOFF_REG21+4)
DECL|macro|TOFF_REG23
mdefine_line|#define TOFF_REG23&t;&t;(TOFF_REG22+4)
DECL|macro|TOFF_REG28
mdefine_line|#define TOFF_REG28&t;&t;(TOFF_REG23+4)
DECL|macro|TOFF_REG29
mdefine_line|#define TOFF_REG29&t;&t;(TOFF_REG28+4)
DECL|macro|TOFF_REG30
mdefine_line|#define TOFF_REG30&t;&t;(TOFF_REG29+4)
DECL|macro|TOFF_REG31
mdefine_line|#define TOFF_REG31&t;&t;(TOFF_REG30+4)
DECL|macro|TOFF_CP0_STATUS
mdefine_line|#define TOFF_CP0_STATUS&t;&t;(TOFF_REG31+4)
multiline_comment|/*&n; * Pad for 8 byte boundary!&n; */
DECL|macro|TOFF_FPU
mdefine_line|#define TOFF_FPU&t;&t;(((TOFF_CP0_STATUS+4)+(8-1))&amp;~(8-1))
DECL|macro|TOFF_CP0_BADVADDR
mdefine_line|#define TOFF_CP0_BADVADDR&t;(TOFF_FPU+264)
DECL|macro|TOFF_ERROR_CODE
mdefine_line|#define TOFF_ERROR_CODE&t;&t;(TOFF_CP0_BADVADDR+4)
DECL|macro|TOFF_TRAP_NO
mdefine_line|#define TOFF_TRAP_NO&t;&t;(TOFF_ERROR_CODE+4)
DECL|macro|TOFF_KSP
mdefine_line|#define TOFF_KSP&t;&t;(TOFF_TRAP_NO+4)
DECL|macro|TOFF_PG_DIR
mdefine_line|#define TOFF_PG_DIR&t;&t;(TOFF_KSP+4)
DECL|macro|TOFF_MFLAGS
mdefine_line|#define TOFF_MFLAGS&t;&t;(TOFF_PG_DIR+4)
macro_line|#if !defined (__LANGUAGE_ASSEMBLY__)
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KSEG0, KSEG1, PAGE_SHARED, &bslash;&n;                    VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;        /* &bslash;&n;         * saved main processor registers &bslash;&n;         */ &bslash;&n;&t;0, 0, 0, 0, 0, 0, 0, 0, &bslash;&n;&t;            0, 0, 0, 0, &bslash;&n;&t;/* &bslash;&n;&t; * saved cp0 stuff &bslash;&n;&t; */ &bslash;&n;&t;0, &bslash;&n;&t;/* &bslash;&n;&t; * saved fpu/fpu emulator stuff &bslash;&n;&t; */ &bslash;&n;&t;INIT_FPU, &bslash;&n;&t;/* &bslash;&n;&t; * Other stuff associated with the process&bslash;&n;&t; */ &bslash;&n;&t;0, 0, 0, sizeof(init_kernel_stack) + (unsigned long)init_kernel_stack - 8, &bslash;&n;&t;(unsigned long) swapper_pg_dir - PT_OFFSET, 0 &bslash;&n;}
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_extern
r_inline
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;reg29
)paren
(braket
id|EF_CP0_EPC
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Do necessary setup to start up a newly executed thread.&n; */
r_static
id|__inline__
DECL|function|start_thread
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
id|pc
comma
r_int
r_int
id|sp
)paren
(brace
multiline_comment|/*&n;&t; * Pure paranoia; probably not needed.&n;&t; */
id|sys_cacheflush
c_func
(paren
l_int|0
comma
op_complement
l_int|0
comma
id|BCACHE
)paren
suffix:semicolon
id|sync_mem
c_func
(paren
)paren
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|pc
suffix:semicolon
multiline_comment|/*&n;&t; * New thread loses kernel privileges.&n;&t; */
id|regs-&gt;cp0_status
op_assign
(paren
id|regs-&gt;cp0_status
op_amp
op_complement
(paren
id|ST0_CU0
op_or
id|ST0_KSU
)paren
)paren
op_or
id|KSU_USER
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve argument save space for registers a0 - a3.&n;&t;regs-&gt;reg29 = sp - 4 * sizeof(unsigned long);&n;&t; */
id|regs-&gt;reg29
op_assign
id|sp
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * switch_to(n) should switch tasks to task nr n, first&n; * checking that n isn&squot;t the current task, in which case it does nothing.&n; */
id|asmlinkage
r_void
id|resume
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
id|offset
)paren
suffix:semicolon
DECL|macro|switch_to
mdefine_line|#define switch_to(n) &bslash;&n;&t;resume(n, ((int)(&amp;((struct task_struct *)0)-&gt;tss)))
multiline_comment|/*&n; * Does the process account for user or for system time?&n; */
macro_line|#if defined (__R4000__)
DECL|macro|USES_USER_TIME
mdefine_line|#define USES_USER_TIME(regs) (!((regs)-&gt;cp0_status &amp; 0x18))
macro_line|#else /* !defined (__R4000__) */
DECL|macro|USES_USER_TIME
mdefine_line|#define USES_USER_TIME(regs) (!((regs)-&gt;cp0_status &amp; 0x4))
macro_line|#endif /* !defined (__R4000__) */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !defined (__LANGUAGE_ASSEMBLY__) */
multiline_comment|/*&n; * ELF support&n; *&n; * Using EM_MIPS is actually wrong - this one is reserved for big endian&n; * machines only&n; */
DECL|macro|INCOMPATIBLE_MACHINE
mdefine_line|#define INCOMPATIBLE_MACHINE(m) ((m) != EM_MIPS &amp;&amp; (m) != EM_MIPS_RS4_BE)
DECL|macro|ELF_EM_CPU
mdefine_line|#define ELF_EM_CPU EM_MIPS
macro_line|#endif /* __ASM_MIPS_PROCESSOR_H */
eof
