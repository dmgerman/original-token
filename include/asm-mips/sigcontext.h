multiline_comment|/*&n; * include/asm-mips/uaccess.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Ralf Baechle&n; *&n; * $Id: sigcontext.h,v 1.3 1997/06/25 16:57:31 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_SIGCONTEXT_H
DECL|macro|__ASM_MIPS_SIGCONTEXT_H
mdefine_line|#define __ASM_MIPS_SIGCONTEXT_H
multiline_comment|/*&n; * Keep this struct definition in sync with the sigcontext fragment&n; * in arch/mips/tools/offset.c&n; */
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
macro_line|#endif /* __ASM_MIPS_SIGCONTEXT_H */
eof
