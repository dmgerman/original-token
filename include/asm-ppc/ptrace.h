macro_line|#ifndef _PPC_PTRACE_H
DECL|macro|_PPC_PTRACE_H
mdefine_line|#define _PPC_PTRACE_H
multiline_comment|/*&n; * This struct defines the way the registers are stored on the&n; * kernel stack during a system call or other kernel entry.&n; * Note: the &quot;_overhead&quot; and &quot;_underhead&quot; spaces are stack locations&n; * used by called routines.  Because of the way the PowerPC ABI&n; * specifies the function prologue/epilogue, registers can be&n; * saved in stack locations which are below the current stack&n; * pointer (_underhead).  If an interrupt occurs during this&n; * [albeit] small time interval, registers which were saved on&n; * the stack could be trashed by the interrupt save code.  The&n; * &quot;_underhead&quot; leaves a hole just in case this happens.  It also&n; * wastes 80 bytes of stack if it doesn&squot;t!  Similarly, the called&n; * routine stores some information &quot;above&quot; the stack pointer before&n; * if gets adjusted.  This is covered by the &quot;_overhead&quot; field&n; * and [thankfully] is not totally wasted.&n; *&n; */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
DECL|member|_overhead
r_int
r_int
id|_overhead
(braket
l_int|14
)braket
suffix:semicolon
multiline_comment|/* Callee&squot;s SP,LR,params */
DECL|member|gpr
r_int
r_int
id|gpr
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|nip
r_int
r_int
id|nip
suffix:semicolon
DECL|member|msr
r_int
r_int
id|msr
suffix:semicolon
DECL|member|ctr
r_int
r_int
id|ctr
suffix:semicolon
DECL|member|link
r_int
r_int
id|link
suffix:semicolon
DECL|member|ccr
r_int
r_int
id|ccr
suffix:semicolon
DECL|member|xer
r_int
r_int
id|xer
suffix:semicolon
DECL|member|dar
r_int
r_int
id|dar
suffix:semicolon
multiline_comment|/* Fault registers */
DECL|member|dsisr
r_int
r_int
id|dsisr
suffix:semicolon
DECL|member|srr1
r_int
r_int
id|srr1
suffix:semicolon
DECL|member|srr0
r_int
r_int
id|srr0
suffix:semicolon
DECL|member|hash1
DECL|member|hash2
r_int
r_int
id|hash1
comma
id|hash2
suffix:semicolon
DECL|member|imiss
DECL|member|dmiss
r_int
r_int
id|imiss
comma
id|dmiss
suffix:semicolon
DECL|member|icmp
DECL|member|dcmp
r_int
r_int
id|icmp
comma
id|dcmp
suffix:semicolon
DECL|member|orig_gpr3
r_int
r_int
id|orig_gpr3
suffix:semicolon
multiline_comment|/* Used for restarting system calls */
DECL|member|result
r_int
r_int
id|result
suffix:semicolon
multiline_comment|/* Result of a system call */
DECL|member|fpcsr
r_float
id|fpcsr
suffix:semicolon
DECL|member|trap
r_int
r_int
id|trap
suffix:semicolon
multiline_comment|/* Reason for being here */
DECL|member|marker
r_int
r_int
id|marker
suffix:semicolon
multiline_comment|/* Should have DEADDEAD */
multiline_comment|/*unsigned long _underhead[20]; */
multiline_comment|/* Callee&squot;s register save area */
DECL|member|edx
r_int
r_int
id|edx
suffix:semicolon
multiline_comment|/* for binfmt_elf.c which wants edx */
)brace
suffix:semicolon
DECL|macro|instruction_pointer
mdefine_line|#define instruction_pointer(regs) ((regs)-&gt;nip)
DECL|macro|user_mode
mdefine_line|#define user_mode(regs) ((regs)-&gt;msr &amp; 0x4000)
macro_line|#ifdef KERNEL
r_extern
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Offsets used by &squot;ptrace&squot; system call interface */
multiline_comment|/* Note: these should correspond to gpr[x]        */
DECL|macro|PT_R0
mdefine_line|#define PT_R0&t;0
DECL|macro|PT_R1
mdefine_line|#define PT_R1&t;1
DECL|macro|PT_R2
mdefine_line|#define PT_R2&t;2
DECL|macro|PT_R3
mdefine_line|#define PT_R3&t;3
DECL|macro|PT_R4
mdefine_line|#define PT_R4&t;4
DECL|macro|PT_R5
mdefine_line|#define PT_R5&t;5
DECL|macro|PT_R6
mdefine_line|#define PT_R6&t;6
DECL|macro|PT_R7
mdefine_line|#define PT_R7&t;7
DECL|macro|PT_R8
mdefine_line|#define PT_R8&t;8
DECL|macro|PT_R9
mdefine_line|#define PT_R9&t;9
DECL|macro|PT_R10
mdefine_line|#define PT_R10&t;10
DECL|macro|PT_R11
mdefine_line|#define PT_R11&t;11
DECL|macro|PT_R12
mdefine_line|#define PT_R12&t;12
DECL|macro|PT_R13
mdefine_line|#define PT_R13&t;13
DECL|macro|PT_R14
mdefine_line|#define PT_R14&t;14
DECL|macro|PT_R15
mdefine_line|#define PT_R15&t;15
DECL|macro|PT_R16
mdefine_line|#define PT_R16&t;16
DECL|macro|PT_R17
mdefine_line|#define PT_R17&t;17
DECL|macro|PT_R18
mdefine_line|#define PT_R18&t;18
DECL|macro|PT_R19
mdefine_line|#define PT_R19&t;19
DECL|macro|PT_R20
mdefine_line|#define PT_R20&t;20
DECL|macro|PT_R21
mdefine_line|#define PT_R21&t;21
DECL|macro|PT_R22
mdefine_line|#define PT_R22&t;22
DECL|macro|PT_R23
mdefine_line|#define PT_R23&t;23
DECL|macro|PT_R24
mdefine_line|#define PT_R24&t;24
DECL|macro|PT_R25
mdefine_line|#define PT_R25&t;25
DECL|macro|PT_R26
mdefine_line|#define PT_R26&t;26
DECL|macro|PT_R27
mdefine_line|#define PT_R27&t;27
DECL|macro|PT_R28
mdefine_line|#define PT_R28&t;28
DECL|macro|PT_R29
mdefine_line|#define PT_R29&t;29
DECL|macro|PT_R30
mdefine_line|#define PT_R30&t;30
DECL|macro|PT_R31
mdefine_line|#define PT_R31&t;31
DECL|macro|PT_NIP
mdefine_line|#define PT_NIP&t;32
DECL|macro|PT_MSR
mdefine_line|#define PT_MSR&t;33
DECL|macro|PT_ORIG_R3
mdefine_line|#define PT_ORIG_R3 34
DECL|macro|PT_CTR
mdefine_line|#define PT_CTR&t;35
DECL|macro|PT_LNK
mdefine_line|#define PT_LNK&t;36
DECL|macro|PT_XER
mdefine_line|#define PT_XER&t;37
DECL|macro|PT_CCR
mdefine_line|#define PT_CCR&t;38
DECL|macro|PT_FPR0
mdefine_line|#define PT_FPR0&t;48
macro_line|#endif
eof
