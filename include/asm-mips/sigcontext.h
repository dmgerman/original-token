macro_line|#ifndef __ASM_MIPS_SIGCONTEXT_H
DECL|macro|__ASM_MIPS_SIGCONTEXT_H
mdefine_line|#define __ASM_MIPS_SIGCONTEXT_H
macro_line|#ifdef __LANGUAGE_ASSEMBLY__
DECL|macro|SC_REGMASK
mdefine_line|#define SC_REGMASK&t;0
DECL|macro|SC_STATUS
mdefine_line|#define SC_STATUS&t;4
DECL|macro|SC_PC
mdefine_line|#define SC_PC&t;&t;8
DECL|macro|SC_REGS
mdefine_line|#define SC_REGS&t;&t;16
DECL|macro|SC_FPREGS
mdefine_line|#define SC_FPREGS&t;272
DECL|macro|SC_OWNEDFP
mdefine_line|#define SC_OWNEDFP&t;528
DECL|macro|SC_FPC_CSR
mdefine_line|#define SC_FPC_CSR&t;532
DECL|macro|SC_FPC_EIR
mdefine_line|#define SC_FPC_EIR&t;536
DECL|macro|SC_SSFLAGS
mdefine_line|#define SC_SSFLAGS&t;540
DECL|macro|SC_MDHI
mdefine_line|#define SC_MDHI&t;&t;544
DECL|macro|SC_MDLO
mdefine_line|#define SC_MDLO&t;&t;552
macro_line|#endif
macro_line|#if defined(__LANGUAGE_C__) || &bslash;&n;    defined(_LANGUAGE_C) || &bslash;&n;    defined(__LANGUAGE_C_PLUS_PLUS__) || &bslash;&n;    defined(__LANGUAGE_OBJECTIVE_C__)
multiline_comment|/*&n; * Whenever this structure is changed you must update the offsets in&n; * arch/mips/mips&lt;isa&gt;/fp-context.S.&n; */
DECL|struct|sigcontext
r_struct
id|sigcontext
(brace
DECL|member|sc_regmask
r_int
r_int
id|sc_regmask
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_status
r_int
r_int
id|sc_status
suffix:semicolon
DECL|member|sc_pc
r_int
r_int
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_regs
r_int
r_int
r_int
id|sc_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpregs
r_int
r_int
r_int
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_ownedfp
r_int
r_int
id|sc_ownedfp
suffix:semicolon
DECL|member|sc_fpc_csr
r_int
r_int
id|sc_fpc_csr
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_fpc_eir
r_int
r_int
id|sc_fpc_eir
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_ssflags
r_int
r_int
id|sc_ssflags
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_mdhi
r_int
r_int
r_int
id|sc_mdhi
suffix:semicolon
DECL|member|sc_mdlo
r_int
r_int
r_int
id|sc_mdlo
suffix:semicolon
DECL|member|sc_cause
r_int
r_int
id|sc_cause
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_badvaddr
r_int
r_int
id|sc_badvaddr
suffix:semicolon
multiline_comment|/* Unused */
DECL|member|sc_sigset
id|sigset_t
id|sc_sigset
suffix:semicolon
DECL|member|__pad0
r_int
r_int
id|__pad0
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* pad for constant size */
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ASM_MIPS_SIGCONTEXT_H */
eof
