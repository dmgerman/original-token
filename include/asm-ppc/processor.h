macro_line|#ifndef __ASM_PPC_PROCESSOR_H
DECL|macro|__ASM_PPC_PROCESSOR_H
mdefine_line|#define __ASM_PPC_PROCESSOR_H
multiline_comment|/*&n; * PowerPC machine specifics&n; */
macro_line|#ifndef _PPC_MACHINE_H_
DECL|macro|_PPC_MACHINE_H_
mdefine_line|#define _PPC_MACHINE_H_ 
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
mdefine_line|#define MSR_PR&t;&t;(1&lt;&lt;14)&t;&t;/* Supervisor/User privelege */
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
mdefine_line|#define MSR_&t;&t;MSR_FP|MSR_FE0|MSR_FE1|MSR_ME
DECL|macro|MSR_USER
mdefine_line|#define MSR_USER&t;MSR_|MSR_PR|MSR_EE|MSR_IR|MSR_DR
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
macro_line|#endif
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
id|eip
comma
r_int
r_int
id|esp
)paren
(brace
id|regs-&gt;nip
op_assign
id|eip
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|esp
suffix:semicolon
id|regs-&gt;msr
op_assign
id|MSR_USER
suffix:semicolon
)brace
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
multiline_comment|/*&n; * User space process size: 2GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; *&n; * &quot;this is gonna have to change to 1gig for the sparc&quot; - David S. Miller&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0x80000000UL)
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
DECL|member|segs
r_int
r_int
id|segs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* MMU Segment registers */
DECL|member|last_pc
r_int
r_int
id|last_pc
suffix:semicolon
multiline_comment|/* PC when last entered system */
DECL|member|fpr
r_float
id|fpr
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Complete floating point set */
)brace
suffix:semicolon
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;}
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_mm, 0, 0x40000000, &bslash;&n;&t;&t;      PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC }
multiline_comment|/*&n; * Return saved PC of a blocked thread.  This assumes the frame pointer&n; * is the 6th saved long on the kernel stack and that the saved return&n; * address is the first long in the frame.  This all holds provided the&n; * thread blocked through a call to schedule().&n; */
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
r_int
r_int
id|fp
suffix:semicolon
id|fp
op_assign
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;ksp
)paren
(braket
l_int|6
)braket
suffix:semicolon
r_return
op_star
(paren
r_int
r_int
op_star
)paren
id|fp
suffix:semicolon
)brace
macro_line|#endif
eof
