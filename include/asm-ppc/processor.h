macro_line|#ifndef __ASM_PPC_PROCESSOR_H
DECL|macro|__ASM_PPC_PROCESSOR_H
mdefine_line|#define __ASM_PPC_PROCESSOR_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
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
macro_line|#ifdef CONFIG_APUS
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;MSR_ME|MSR_FE0|MSR_FE1|MSR_IP|MSR_RI
macro_line|#else
DECL|macro|MSR_
mdefine_line|#define MSR_&t;&t;MSR_ME|MSR_FE0|MSR_FE1|MSR_RI
macro_line|#endif
DECL|macro|MSR_KERNEL
mdefine_line|#define MSR_KERNEL      MSR_|MSR_IR|MSR_DR
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;MSR_KERNEL|MSR_PR|MSR_EE
multiline_comment|/* Bit encodings for Hardware Implementation Register (HID0)&n;   on PowerPC 603, 604, etc. processors (not 601). */
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
DECL|macro|HID0_BTCD
mdefine_line|#define HID0_BTCD&t;(1&lt;&lt;1)&t;&t;/* Branch target cache disable */
multiline_comment|/* fpscr settings */
DECL|macro|FPSCR_FX
mdefine_line|#define FPSCR_FX        (1&lt;&lt;31)
DECL|macro|FPSCR_FEX
mdefine_line|#define FPSCR_FEX       (1&lt;&lt;30)
DECL|macro|_MACH_prep
mdefine_line|#define _MACH_prep     1
DECL|macro|_MACH_Pmac
mdefine_line|#define _MACH_Pmac     2 /* pmac or pmac clone (non-chrp) */
DECL|macro|_MACH_chrp
mdefine_line|#define _MACH_chrp     4 /* chrp machine */
DECL|macro|_MACH_mbx
mdefine_line|#define _MACH_mbx      8 /* Motorola MBX board */
DECL|macro|_MACH_apus
mdefine_line|#define _MACH_apus    16 /* amiga with phase5 powerup */
multiline_comment|/* see residual.h for these */
DECL|macro|_PREP_Motorola
mdefine_line|#define _PREP_Motorola 0x01  /* motorola prep */
DECL|macro|_PREP_Firm
mdefine_line|#define _PREP_Firm     0x02  /* firmworks prep */
DECL|macro|_PREP_IBM
mdefine_line|#define _PREP_IBM      0x00  /* ibm prep */
DECL|macro|_PREP_Bull
mdefine_line|#define _PREP_Bull     0x03  /* bull prep */
multiline_comment|/* these are arbitrary */
DECL|macro|_CHRP_Motorola
mdefine_line|#define _CHRP_Motorola 0x04  /* motorola chrp, the cobra */
DECL|macro|_CHRP_IBM
mdefine_line|#define _CHRP_IBM     0x05   /* IBM chrp, the longtrail and longtrail 2 */
DECL|macro|_GLOBAL
mdefine_line|#define _GLOBAL(n)&bslash;&n;&t;.globl n;&bslash;&n;n:
DECL|macro|TBRU
mdefine_line|#define&t;TBRU&t;269&t;/* Time base Upper/Lower (Reading) */
DECL|macro|TBRL
mdefine_line|#define&t;TBRL&t;268
DECL|macro|TBWU
mdefine_line|#define TBWU&t;284&t;/* Time base Upper/Lower (Writing) */
DECL|macro|TBWL
mdefine_line|#define TBWL&t;285
DECL|macro|XER
mdefine_line|#define&t;XER&t;1
DECL|macro|LR
mdefine_line|#define LR&t;8
DECL|macro|CTR
mdefine_line|#define CTR&t;9
DECL|macro|HID0
mdefine_line|#define HID0&t;1008&t;/* Hardware Implementation */
DECL|macro|PVR
mdefine_line|#define PVR&t;287&t;/* Processor Version */
DECL|macro|IBAT0U
mdefine_line|#define IBAT0U&t;528&t;/* Instruction BAT #0 Upper/Lower */
DECL|macro|IBAT0L
mdefine_line|#define IBAT0L&t;529
DECL|macro|IBAT1U
mdefine_line|#define IBAT1U&t;530&t;/* Instruction BAT #1 Upper/Lower */
DECL|macro|IBAT1L
mdefine_line|#define IBAT1L&t;531
DECL|macro|IBAT2U
mdefine_line|#define IBAT2U&t;532&t;/* Instruction BAT #2 Upper/Lower */
DECL|macro|IBAT2L
mdefine_line|#define IBAT2L&t;533
DECL|macro|IBAT3U
mdefine_line|#define IBAT3U&t;534&t;/* Instruction BAT #3 Upper/Lower */
DECL|macro|IBAT3L
mdefine_line|#define IBAT3L&t;535
DECL|macro|DBAT0U
mdefine_line|#define DBAT0U&t;536&t;/* Data BAT #0 Upper/Lower */
DECL|macro|DBAT0L
mdefine_line|#define DBAT0L&t;537
DECL|macro|DBAT1U
mdefine_line|#define DBAT1U&t;538&t;/* Data BAT #1 Upper/Lower */
DECL|macro|DBAT1L
mdefine_line|#define DBAT1L&t;539
DECL|macro|DBAT2U
mdefine_line|#define DBAT2U&t;540&t;/* Data BAT #2 Upper/Lower */
DECL|macro|DBAT2L
mdefine_line|#define DBAT2L&t;541
DECL|macro|DBAT3U
mdefine_line|#define DBAT3U&t;542&t;/* Data BAT #3 Upper/Lower */
DECL|macro|DBAT3L
mdefine_line|#define DBAT3L&t;543
DECL|macro|DMISS
mdefine_line|#define DMISS&t;976&t;/* TLB Lookup/Refresh registers */
DECL|macro|DCMP
mdefine_line|#define DCMP&t;977
DECL|macro|HASH1
mdefine_line|#define HASH1&t;978
DECL|macro|HASH2
mdefine_line|#define HASH2&t;979
DECL|macro|IMISS
mdefine_line|#define IMISS&t;980
DECL|macro|ICMP
mdefine_line|#define ICMP&t;981
DECL|macro|RPA
mdefine_line|#define RPA&t;982
DECL|macro|SDR1
mdefine_line|#define SDR1&t;25&t;/* MMU hash base register */
DECL|macro|DAR
mdefine_line|#define DAR&t;19&t;/* Data Address Register */
DECL|macro|SPR0
mdefine_line|#define SPR0&t;272&t;/* Supervisor Private Registers */
DECL|macro|SPRG0
mdefine_line|#define SPRG0   272
DECL|macro|SPR1
mdefine_line|#define SPR1&t;273
DECL|macro|SPRG1
mdefine_line|#define SPRG1   273
DECL|macro|SPR2
mdefine_line|#define SPR2&t;274
DECL|macro|SPRG2
mdefine_line|#define SPRG2   274
DECL|macro|SPR3
mdefine_line|#define SPR3&t;275
DECL|macro|SPRG3
mdefine_line|#define SPRG3   275
DECL|macro|DSISR
mdefine_line|#define DSISR&t;18
DECL|macro|SRR0
mdefine_line|#define SRR0&t;26&t;/* Saved Registers (exception) */
DECL|macro|SRR1
mdefine_line|#define SRR1&t;27
DECL|macro|IABR
mdefine_line|#define IABR&t;1010&t;/* Instruction Address Breakpoint */
DECL|macro|DEC
mdefine_line|#define DEC&t;22&t;/* Decrementer */
DECL|macro|EAR
mdefine_line|#define EAR&t;282&t;/* External Address Register */
DECL|macro|L2CR
mdefine_line|#define L2CR&t;1017    /* PPC 750 L2 control register */
DECL|macro|THRM1
mdefine_line|#define THRM1&t;1020
DECL|macro|THRM2
mdefine_line|#define THRM2&t;1021
DECL|macro|THRM3
mdefine_line|#define THRM3&t;1022
DECL|macro|THRM1_TIN
mdefine_line|#define THRM1_TIN 0x1
DECL|macro|THRM1_TIV
mdefine_line|#define THRM1_TIV 0x2
DECL|macro|THRM1_THRES
mdefine_line|#define THRM1_THRES (0x7f&lt;&lt;2)
DECL|macro|THRM1_TID
mdefine_line|#define THRM1_TID (1&lt;&lt;29)
DECL|macro|THRM1_TIE
mdefine_line|#define THRM1_TIE (1&lt;&lt;30)
DECL|macro|THRM1_V
mdefine_line|#define THRM1_V   (1&lt;&lt;31)
DECL|macro|THRM3_E
mdefine_line|#define THRM3_E   (1&lt;&lt;31)
multiline_comment|/* Segment Registers */
DECL|macro|SR0
mdefine_line|#define SR0&t;0
DECL|macro|SR1
mdefine_line|#define SR1&t;1
DECL|macro|SR2
mdefine_line|#define SR2&t;2
DECL|macro|SR3
mdefine_line|#define SR3&t;3
DECL|macro|SR4
mdefine_line|#define SR4&t;4
DECL|macro|SR5
mdefine_line|#define SR5&t;5
DECL|macro|SR6
mdefine_line|#define SR6&t;6
DECL|macro|SR7
mdefine_line|#define SR7&t;7
DECL|macro|SR8
mdefine_line|#define SR8&t;8
DECL|macro|SR9
mdefine_line|#define SR9&t;9
DECL|macro|SR10
mdefine_line|#define SR10&t;10
DECL|macro|SR11
mdefine_line|#define SR11&t;11
DECL|macro|SR12
mdefine_line|#define SR12&t;12
DECL|macro|SR13
mdefine_line|#define SR13&t;13
DECL|macro|SR14
mdefine_line|#define SR14&t;14
DECL|macro|SR15
mdefine_line|#define SR15&t;15
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * If we&squot;ve configured for a specific machine set things&n; * up so the compiler can optimize away the other parts.&n; * -- Cort&n; */
macro_line|#ifdef CONFIG_MACH_SPECIFIC
macro_line|#ifdef CONFIG_PREP
DECL|macro|_machine
mdefine_line|#define _machine (_MACH_prep)
DECL|macro|is_prep
mdefine_line|#define is_prep (1)
DECL|macro|is_chrp
mdefine_line|#define is_chrp (0)
DECL|macro|have_of
mdefine_line|#define have_of (0)
macro_line|#endif /* CONFIG_PREP */
macro_line|#ifdef CONFIG_CHRP
DECL|macro|_machine
mdefine_line|#define _machine (_MACH_chrp)
DECL|macro|is_prep
mdefine_line|#define is_prep (0)
DECL|macro|is_chrp
mdefine_line|#define is_chrp (1)
DECL|macro|have_of
mdefine_line|#define have_of (1)
macro_line|#endif /* CONFIG_CHRP */
macro_line|#ifdef CONFIG_PMAC
DECL|macro|_machine
mdefine_line|#define _machine (_MACH_Pmac)
DECL|macro|is_prep
mdefine_line|#define is_prep (0)
DECL|macro|is_chrp
mdefine_line|#define is_chrp (0)
DECL|macro|have_of
mdefine_line|#define have_of (1)
macro_line|#endif /* CONFIG_PMAC */
macro_line|#ifdef CONFIG_MBX
DECL|macro|_machine
mdefine_line|#define _machine (_MACH_mbx)
DECL|macro|is_prep
mdefine_line|#define is_prep (0)
DECL|macro|is_chrp
mdefine_line|#define is_chrp (0)
DECL|macro|have_of
mdefine_line|#define have_of (0)
macro_line|#endif /* CONFIG_MBX */
macro_line|#ifdef CONFIG_APUS
DECL|macro|_machine
mdefine_line|#define _machine (_MACH_apus)
DECL|macro|is_prep
mdefine_line|#define is_prep (0)
DECL|macro|is_chrp
mdefine_line|#define is_chrp (0)
DECL|macro|have_of
mdefine_line|#define have_of (0)
macro_line|#endif /* CONFIG_APUS */
macro_line|#else /* CONFIG_MACH_SPECIFIC */
r_extern
r_int
id|_machine
suffix:semicolon
multiline_comment|/* if we&squot;re a prep machine */
DECL|macro|is_prep
mdefine_line|#define is_prep (_machine == _MACH_prep)
multiline_comment|/* if we&squot;re a chrp machine */
DECL|macro|is_chrp
mdefine_line|#define is_chrp (_machine == _MACH_chrp)
multiline_comment|/* if we have openfirmware */
r_extern
r_int
r_int
id|have_of
suffix:semicolon
macro_line|#endif /* CONFIG_MACH_SPECIFIC */
multiline_comment|/* what kind of prep workstation we are */
r_extern
r_int
id|_prep_type
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
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
id|nip
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
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
multiline_comment|/* Lazy FPU handling on uni-processor */
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
multiline_comment|/*&n; * this is the minimum allowable io space due to the location&n; * of the io areas on prep (first one at 0x80000000) but&n; * as soon as I get around to remapping the io areas with the BATs&n; * to match the mac we can raise this. -- Cort&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x80000000UL)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 8 * 3)
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
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
multiline_comment|/* Base of page-table tree */
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
id|mm_segment_t
id|fs
suffix:semicolon
multiline_comment|/* for get_fs() validation */
DECL|member|last_syscall
r_int
r_int
id|last_syscall
suffix:semicolon
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
DECL|member|fpscr_pad
r_int
r_int
id|fpscr_pad
suffix:semicolon
multiline_comment|/* fpr ... fpscr must be contiguous */
DECL|member|fpscr
r_int
r_int
id|fpscr
suffix:semicolon
multiline_comment|/* Floating point status */
DECL|member|smp_fork_ret
r_int
r_int
id|smp_fork_ret
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_SP
mdefine_line|#define INIT_SP&t;&t;(sizeof(init_stack) + (unsigned long) &amp;init_stack)
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;INIT_SP, /* ksp */ &bslash;&n;&t;(unsigned long *) swapper_pg_dir, /* pg_tables */ &bslash;&n;&t;0, /* wchan */ &bslash;&n;&t;(struct pt_regs *)INIT_SP - 1, /* regs */ &bslash;&n;&t;KERNEL_DS, /*fs*/ &bslash;&n;&t;0, /* last_syscall */ &bslash;&n;&t;{0}, 0, 0, 0 &bslash;&n;}
multiline_comment|/*&n; * Note: the vm_start and vm_end fields here should *not*&n; * be in kernel space.  (Could vm_end == vm_start perhaps?)&n; */
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0, 0x1000, &bslash;&n;&t;&t;      PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC }
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
)brace
DECL|macro|copy_segments
mdefine_line|#define copy_segments(nr, tsk, mm)&t;do { } while (0)
DECL|macro|release_segments
mdefine_line|#define release_segments(mm)&t;&t;do { } while (0)
multiline_comment|/*&n; * NOTE! The task struct and the stack go together&n; */
DECL|macro|alloc_task_struct
mdefine_line|#define alloc_task_struct() &bslash;&n;&t;((struct task_struct *) __get_free_pages(GFP_KERNEL,1))
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
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* ndef ASSEMBLY*/
macro_line|#endif /* __ASM_PPC_PROCESSOR_H */
eof
