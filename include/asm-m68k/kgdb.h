multiline_comment|/*&n; *  include/asm-m68k/kgdb.h&n; *&n; *  Copyright (C) 1996 Roman Hodek&n; */
macro_line|#ifndef __ASM_M68k_KGDB_H
DECL|macro|__ASM_M68k_KGDB_H
mdefine_line|#define __ASM_M68k_KGDB_H
multiline_comment|/*&n; * Structure to save all register values in, already in the order gdb wants&n; * it. Note that the upper half of the SR field is recycled for the FORMAT and&n; * VECTOR fields. Hope that doesn&squot;t confuse gdb... That upper half is ignored&n; * on exiting the stub, so gdb can modify it as it likes.&n; */
DECL|macro|GDBREG_A6
mdefine_line|#define GDBREG_A6&t;14
DECL|macro|GDBREG_A7
mdefine_line|#define GDBREG_A7&t;15
DECL|macro|GDBREG_SP
mdefine_line|#define GDBREG_SP&t;15
DECL|macro|GDBREG_SR
mdefine_line|#define GDBREG_SR&t;16
DECL|macro|GDBREG_PC
mdefine_line|#define GDBREG_PC&t;17
DECL|macro|GDBREG_FP0
mdefine_line|#define GDBREG_FP0&t;18
DECL|macro|GDBREG_FP7
mdefine_line|#define GDBREG_FP7&t;25
DECL|macro|GDBREG_FPCR
mdefine_line|#define GDBREG_FPCR&t;26
DECL|macro|GDBREG_FPIAR
mdefine_line|#define GDBREG_FPIAR 28
DECL|macro|GDBOFFA_D6
mdefine_line|#define GDBOFFA_D6&t;(6*4)
DECL|macro|GDBOFFA_A3
mdefine_line|#define GDBOFFA_A3&t;(11*4)
DECL|macro|NUMREGSBYTES
mdefine_line|#define NUMREGSBYTES&t;180
macro_line|#ifndef __ASSEMBLY__
DECL|struct|gdb_regs
r_struct
id|gdb_regs
(brace
DECL|member|regs
r_int
id|regs
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* d0-a7 */
DECL|member|format
r_int
id|format
suffix:colon
l_int|4
suffix:semicolon
multiline_comment|/* frame format specifier */
DECL|member|vector
r_int
id|vector
suffix:colon
l_int|12
suffix:semicolon
multiline_comment|/* vector offset */
DECL|member|sr
r_int
r_int
id|sr
suffix:semicolon
multiline_comment|/* status register */
DECL|member|pc
r_int
r_int
id|pc
suffix:semicolon
multiline_comment|/* program counter */
DECL|member|fpregs
r_int
r_int
id|fpregs
(braket
l_int|8
op_star
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fp0-fp7 */
DECL|member|fpcntl
r_int
r_int
id|fpcntl
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* fpcr, fpsr, fpiar */
)brace
suffix:semicolon
r_extern
r_struct
id|gdb_regs
id|kgdb_registers
suffix:semicolon
r_extern
r_void
id|kgdb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_struct
id|frame
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|enter_kgdb
c_func
(paren
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
r_extern
r_int
id|kgdb_initialized
suffix:semicolon
multiline_comment|/*&n; * This function will generate a breakpoint exception.  It is used at the&n; * beginning of a program to sync up with a debugger and can be used&n; * otherwise as a quick means to stop program execution and &quot;break&quot; into&n; * the debugger.&n; */
DECL|function|breakpoint
r_extern
r_inline
r_void
id|breakpoint
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kgdb_initialized
)paren
multiline_comment|/* if kgdb not inited, do nothing */
r_return
suffix:semicolon
multiline_comment|/* breakpoint instruction is TRAP #15 */
id|__asm__
id|__volatile__
(paren
l_string|&quot;trap #15&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function will report a SIGABORT to gdb.&n; */
DECL|function|kgdb_abort
r_extern
r_inline
r_void
id|kgdb_abort
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|kgdb_initialized
)paren
multiline_comment|/* if kgdb not inited, do nothing */
r_return
suffix:semicolon
multiline_comment|/* TRAP #14 is reported as SIGABORT */
id|__asm__
id|__volatile__
(paren
l_string|&quot;trap #14&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_M68k_KGDB_H */
eof
