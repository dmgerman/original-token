multiline_comment|/* $Id: reg.h,v 1.2 1997/06/24 23:19:55 davem Exp $&n; * linux/asm-sparc64/reg.h&n; * Layout of the registers as expected by gdb on the Sparc&n; * we should replace the user.h definitions with those in&n; * this file, we don&squot;t even use the other &n; * -miguel&n; *&n; * The names of the structures, constants and aliases in this file&n; * have the same names as the sunos ones, some programs rely on these&n; * names (gdb for example).&n; *&n; */
macro_line|#ifndef __SPARC64_REG_H
DECL|macro|__SPARC64_REG_H
mdefine_line|#define __SPARC64_REG_H
DECL|struct|regs
r_struct
id|regs
(brace
DECL|member|r_psr
r_int
id|r_psr
suffix:semicolon
DECL|macro|r_ps
mdefine_line|#define r_ps r_psr
DECL|member|r_pc
r_int
id|r_pc
suffix:semicolon
DECL|member|r_npc
r_int
id|r_npc
suffix:semicolon
DECL|member|r_y
r_int
id|r_y
suffix:semicolon
DECL|member|r_g1
r_int
id|r_g1
suffix:semicolon
DECL|member|r_g2
r_int
id|r_g2
suffix:semicolon
DECL|member|r_g3
r_int
id|r_g3
suffix:semicolon
DECL|member|r_g4
r_int
id|r_g4
suffix:semicolon
DECL|member|r_g5
r_int
id|r_g5
suffix:semicolon
DECL|member|r_g6
r_int
id|r_g6
suffix:semicolon
DECL|member|r_g7
r_int
id|r_g7
suffix:semicolon
DECL|member|r_o0
r_int
id|r_o0
suffix:semicolon
DECL|member|r_o1
r_int
id|r_o1
suffix:semicolon
DECL|member|r_o2
r_int
id|r_o2
suffix:semicolon
DECL|member|r_o3
r_int
id|r_o3
suffix:semicolon
DECL|member|r_o4
r_int
id|r_o4
suffix:semicolon
DECL|member|r_o5
r_int
id|r_o5
suffix:semicolon
DECL|member|r_o6
r_int
id|r_o6
suffix:semicolon
DECL|member|r_o7
r_int
id|r_o7
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fpq
r_struct
id|fpq
(brace
DECL|member|addr
r_int
r_int
op_star
id|addr
suffix:semicolon
DECL|member|instr
r_int
id|ing
id|instr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fq
r_struct
id|fq
(brace
r_union
(brace
DECL|member|whole
r_float
id|whole
suffix:semicolon
DECL|member|fpq
r_struct
id|fpq
id|fpq
suffix:semicolon
DECL|member|FQu
)brace
id|FQu
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FPU_REGS_TYPE
mdefine_line|#define FPU_REGS_TYPE unsigned int
DECL|macro|FPU_FSR_TYPE
mdefine_line|#define FPU_FSR_TYPE unsigned
DECL|struct|fp_status
r_struct
id|fp_status
(brace
r_union
(brace
DECL|member|Fpu_regs
id|FPU_REGS_TYPE
id|Fpu_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|Fpu_dregs
r_float
id|Fpu_dregs
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|fpu_fr
)brace
id|fpu_fr
suffix:semicolon
DECL|member|Fpu_fsr
id|FPU_FSR_TYPE
id|Fpu_fsr
suffix:semicolon
DECL|member|Fpu_flags
r_int
id|Fpu_flags
suffix:semicolon
DECL|member|Fpu_extra
r_int
id|Fpu_extra
suffix:semicolon
DECL|member|Fpu_qcnt
r_int
id|Fpu_qcnt
suffix:semicolon
DECL|member|Fpu_q
r_struct
id|fq
id|Fpu_q
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|fpu_regs
mdefine_line|#define fpu_regs  f_fpstatus.fpu_fr.Fpu_regs
DECL|macro|fpu_dregs
mdefine_line|#define fpu_dregs f_fpstatus.fpu_fr.Fpu_dregs
DECL|macro|fpu_fsr
mdefine_line|#define fpu_fsr   f_fpstatus.Fpu_fsr
DECL|macro|fpu_flags
mdefine_line|#define fpu_flags f_fpstatus.Fpu_flags
DECL|macro|fpu_extra
mdefine_line|#define fpu_extra f_fpstatus.Fpu_extra
DECL|macro|fpu_q
mdefine_line|#define fpu_q     f_fpstatus.Fpu_q
DECL|macro|fpu_qcnt
mdefine_line|#define fpu_qcnt  f_fpstatus.Fpu_qcnt
DECL|struct|fpu
r_struct
id|fpu
(brace
DECL|member|f_fpstatus
r_struct
id|fp_status
id|f_fpstatus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|regs64
r_struct
id|regs64
(brace
DECL|member|r_g1
r_int
r_int
id|r_g1
suffix:semicolon
DECL|member|r_g2
r_int
r_int
id|r_g2
suffix:semicolon
DECL|member|r_g3
r_int
r_int
id|r_g3
suffix:semicolon
DECL|member|r_g4
r_int
r_int
id|r_g4
suffix:semicolon
DECL|member|r_g5
r_int
r_int
id|r_g5
suffix:semicolon
DECL|member|r_g6
r_int
r_int
id|r_g6
suffix:semicolon
DECL|member|r_g7
r_int
r_int
id|r_g7
suffix:semicolon
DECL|member|r_o0
r_int
r_int
id|r_o0
suffix:semicolon
DECL|member|r_o1
r_int
r_int
id|r_o1
suffix:semicolon
DECL|member|r_o2
r_int
r_int
id|r_o2
suffix:semicolon
DECL|member|r_o3
r_int
r_int
id|r_o3
suffix:semicolon
DECL|member|r_o4
r_int
r_int
id|r_o4
suffix:semicolon
DECL|member|r_o5
r_int
r_int
id|r_o5
suffix:semicolon
DECL|member|r_o6
r_int
r_int
id|r_o6
suffix:semicolon
DECL|member|r_o7
r_int
r_int
id|r_o7
suffix:semicolon
DECL|member|tstate
r_int
r_int
id|tstate
suffix:semicolon
DECL|member|tpc
r_int
r_int
id|tpc
suffix:semicolon
DECL|member|tnpc
r_int
r_int
id|tnpc
suffix:semicolon
DECL|member|y
r_int
r_int
id|y
suffix:semicolon
DECL|member|fprs
r_int
r_int
id|fprs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|fp_status64
r_struct
id|fp_status64
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|fsr
r_int
r_int
id|fsr
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* __SPARC64_REG_H */
eof
