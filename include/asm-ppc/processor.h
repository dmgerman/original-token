macro_line|#ifndef __ASM_PPC_PROCESSOR_H
DECL|macro|__ASM_PPC_PROCESSOR_H
mdefine_line|#define __ASM_PPC_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Bit encodings for Machine State Register (MSR) */
DECL|macro|MSR_POW
mdefine_line|#define MSR_POW&t;&t;(1&lt;&lt;18)&t;&t;/* Enable Power Management */
DECL|macro|MSR_TGPR
mdefine_line|#define MSR_TGPR&t;(1&lt;&lt;17)&t;&t;/* TLB Update registers in use */
DECL|macro|MSR_ILE
mdefine_line|#define MSR_ILE&t;&t;(1&lt;&lt;16)&t;&t;/* Interrupt Little-Endian enable */
DECL|macro|MSR_EE
mdefine_line|#define MSR_EE&t;&t;(1&lt;&lt;15)&t;&t;/* External Interrupt enable */
DECL|macro|MSR_PR
mdefine_line|#define MSR_PR&t;&t;(1&lt;&lt;14)&t;&t;/* Supervisor/User privilege */
DECL|macro|MSR_FP
mdefine_line|#define MSR_FP&t;&t;(1&lt;&lt;13)&t;&t;/* Floating Point enable */
DECL|macro|MSR_ME
mdefine_line|#define MSR_ME&t;&t;(1&lt;&lt;12)&t;&t;/* Machine Check enable */
DECL|macro|MSR_FE0
mdefine_line|#define MSR_FE0&t;&t;(1&lt;&lt;11)&t;&t;/* Floating Exception mode 0 */
DECL|macro|MSR_SE
mdefine_line|#define MSR_SE&t;&t;(1&lt;&lt;10)&t;&t;/* Single Step */
DECL|macro|MSR_BE
mdefine_line|#define MSR_BE&t;&t;(1&lt;&lt;9)&t;&t;/* Branch Trace */
DECL|macro|MSR_FE1
mdefine_line|#define MSR_FE1&t;&t;(1&lt;&lt;8)&t;&t;/* Floating Exception mode 1 */
DECL|macro|MSR_IP
mdefine_line|#define MSR_IP&t;&t;(1&lt;&lt;6)&t;&t;/* Exception prefix 0x000/0xFFF */
DECL|macro|MSR_IR
mdefine_line|#define MSR_IR&t;&t;(1&lt;&lt;5)&t;&t;/* Instruction MMU enable */
DECL|macro|MSR_DR
mdefine_line|#define MSR_DR&t;&t;(1&lt;&lt;4)&t;&t;/* Data MMU enable */
DECL|macro|MSR_RI
mdefine_line|#define MSR_RI&t;&t;(1&lt;&lt;1)&t;&t;/* Recoverable Exception */
DECL|macro|MSR_LE
mdefine_line|#define MSR_LE&t;&t;(1&lt;&lt;0)&t;&t;/* Little-Endian enable */
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;MSR_FE0|MSR_FE1|MSR_ME
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL      MSR_|MSR_IR|MSR_DR
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;MSR_FE0|MSR_FE1|MSR_ME|MSR_PR|MSR_EE|MSR_IR|MSR_DR
multiline_comment|/* Bit encodings for Hardware Implementation Register (HID0) */
DECL|macro|HID0_EMCP
mdefine_line|#define HID0_EMCP&t;(1&lt;&lt;31)&t;&t;/* Enable Machine Check pin */
DECL|macro|HID0_EBA
mdefine_line|#define HID0_EBA&t;(1&lt;&lt;29)&t;&t;/* Enable Bus Address Parity */
DECL|macro|HID0_EBD
mdefine_line|#define HID0_EBD&t;(1&lt;&lt;28)&t;&t;/* Enable Bus Data Parity */
DECL|macro|HID0_SBCLK
mdefine_line|#define HID0_SBCLK&t;(1&lt;&lt;27)
DECL|macro|HID0_EICE
mdefine_line|#define HID0_EICE&t;(1&lt;&lt;26)
DECL|macro|HID0_ECLK
mdefine_line|#define HID0_ECLK&t;(1&lt;&lt;25)
DECL|macro|HID0_PAR
mdefine_line|#define HID0_PAR&t;(1&lt;&lt;24)
DECL|macro|HID0_DOZE
mdefine_line|#define HID0_DOZE&t;(1&lt;&lt;23)
DECL|macro|HID0_NAP
mdefine_line|#define HID0_NAP&t;(1&lt;&lt;22)
DECL|macro|HID0_SLEEP
mdefine_line|#define HID0_SLEEP&t;(1&lt;&lt;21)
DECL|macro|HID0_DPM
mdefine_line|#define HID0_DPM&t;(1&lt;&lt;20)
DECL|macro|HID0_ICE
mdefine_line|#define HID0_ICE&t;(1&lt;&lt;15)&t;&t;/* Instruction Cache Enable */
DECL|macro|HID0_DCE
mdefine_line|#define HID0_DCE&t;(1&lt;&lt;14)&t;&t;/* Data Cache Enable */
DECL|macro|HID0_ILOCK
mdefine_line|#define HID0_ILOCK&t;(1&lt;&lt;13)&t;&t;/* Instruction Cache Lock */
DECL|macro|HID0_DLOCK
mdefine_line|#define HID0_DLOCK&t;(1&lt;&lt;12)&t;&t;/* Data Cache Lock */
DECL|macro|HID0_ICFI
mdefine_line|#define HID0_ICFI&t;(1&lt;&lt;11)&t;&t;/* Instruction Cache Flash Invalidate */
DECL|macro|HID0_DCI
mdefine_line|#define HID0_DCI&t;(1&lt;&lt;10)&t;&t;/* Data Cache Invalidate */
DECL|macro|HID0_SIED
mdefine_line|#define HID0_SIED&t;(1&lt;&lt;7)&t;&t;/* Serial Instruction Execution [Disable] */
DECL|macro|HID0_BHTE
mdefine_line|#define HID0_BHTE&t;(1&lt;&lt;2)&t;&t;/* Branch History Table Enable */
multiline_comment|/* fpscr settings */
DECL|macro|FPSCR_FX
mdefine_line|#define FPSCR_FX        (1&lt;&lt;31)
DECL|macro|FPSCR_FEX
mdefine_line|#define FPSCR_FEX       (1&lt;&lt;30)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * PowerPC machine specifics&n; */
r_extern
r_inline
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 0
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * Write Protection works right in supervisor mode on the PowerPC&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x80000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
multiline_comment|/* Kernel stack pointer */
DECL|member|pg_tables
r_int
r_int
op_star
id|pg_tables
suffix:semicolon
multiline_comment|/* MMU information */
macro_line|#ifdef CONFIG_PMAC
DECL|member|last_pc
r_int
r_int
id|last_pc
suffix:semicolon
multiline_comment|/* PC when last entered system */
DECL|member|user_stack
r_int
r_int
id|user_stack
suffix:semicolon
multiline_comment|/* [User] Stack when entered kernel */
macro_line|#endif  
DECL|member|fpscr_pad
r_int
r_int
id|fpscr_pad
suffix:semicolon
multiline_comment|/* (so we can save fpscr with stfd) */
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* fp status reg */
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
DECL|member|fp_used
r_int
r_int
id|fp_used
suffix:semicolon
DECL|member|wchan
r_int
r_int
id|wchan
suffix:semicolon
multiline_comment|/* Event task is sleeping on */
DECL|member|regs
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* Pointer to saved register state */
DECL|member|fs
r_int
r_int
id|fs
suffix:semicolon
multiline_comment|/* for get_fs() validation */
DECL|member|last_syscall
r_int
r_int
id|last_syscall
suffix:semicolon
DECL|member|pad
r_int
r_int
id|pad
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* pad to 16-byte boundry */
)brace
suffix:semicolon
multiline_comment|/* Points to the thread_struct of the thread (if any) which&n;   currently owns the FPU. */
DECL|macro|fpu_tss
mdefine_line|#define fpu_tss (&amp;(last_task_used_math-&gt;tss))
macro_line|#ifdef CONFIG_PMAC
DECL|macro|LAZY_TSS_FPR_INIT
mdefine_line|#define LAZY_TSS_FPR_INIT 0,0,0,0,{0},
macro_line|#endif
macro_line|#ifdef CONFIG_PREP
DECL|macro|LAZY_TSS_FPR_INIT
mdefine_line|#define LAZY_TSS_FPR_INIT 0,0,{0},
macro_line|#endif
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;sizeof(init_stack) + (long) &amp;init_stack, /* ksp */ &bslash;&n;&t;(long *)swapper_pg_dir, /* pg_tables */ &bslash;&n;&t;LAZY_TSS_FPR_INIT &bslash;&n;&t;0, /*fp_used*/ 0, /*wchan*/ &bslash;&n;&t;sizeof(init_stack) + (long)&amp;init_stack - &bslash;&n;&t;&t;sizeof(struct pt_regs), /* regs */ &bslash;&n;&t;KERNEL_DS /*fs*/, 0 /*last_syscall*/ &bslash;&n;}
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, KERNELBASE/*0*/, 0xffffffff/*0x40000000*/, &bslash;&n;&t;&t;      PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC }
multiline_comment|/*&n; * Return saved PC of a blocked thread. For now, this is the &quot;user&quot; PC&n; */
DECL|function|thread_saved_pc
r_static
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
id|t-&gt;regs
)paren
ques
c_cond
id|t-&gt;regs-&gt;nip
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/*return (t-&gt;last_pc);*/
)brace
r_extern
r_int
id|_machine
suffix:semicolon
DECL|macro|_MACH_Motorola
mdefine_line|#define _MACH_Motorola 0
DECL|macro|_MACH_IBM
mdefine_line|#define _MACH_IBM      1
DECL|macro|_MACH_Be
mdefine_line|#define _MACH_Be       2
DECL|macro|_MACH_Pmac
mdefine_line|#define _MACH_Pmac     3
multiline_comment|/*&n; * NOTE! The task struct and the stack go together&n; */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;&t;((struct task_struct *) __get_free_pages(GFP_KERNEL,1,0))
DECL|macro|free_task_struct
mdefine_line|#define free_task_struct(p)&t;free_pages((unsigned long)(p),1)
multiline_comment|/* in process.c - for early bootup debug -- Cort */
r_int
id|ll_printk
c_func
(paren
r_const
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_void
id|ll_puts
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* ndef ASSEMBLY*/
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __ASM_PPC_PROCESSOR_H */
eof
