multiline_comment|/* $Id: namei.h,v 1.15 1999/06/10 05:23:17 davem Exp $&n; * linux/include/asm-sparc64/namei.h&n; *&n; * Routines to handle famous /usr/gnemul/s*.&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __SPARC64_NAMEI_H
DECL|macro|__SPARC64_NAMEI_H
mdefine_line|#define __SPARC64_NAMEI_H
DECL|macro|SPARC_BSD_EMUL
mdefine_line|#define SPARC_BSD_EMUL &quot;usr/gnemul/sunos/&quot;
DECL|macro|SPARC_SOL_EMUL
mdefine_line|#define SPARC_SOL_EMUL &quot;usr/gnemul/solaris/&quot;
DECL|function|__emul_prefix
r_static
r_inline
r_char
op_star
id|__emul_prefix
c_func
(paren
r_void
)paren
(brace
r_switch
c_cond
(paren
id|current-&gt;personality
)paren
(brace
r_case
id|PER_BSD
suffix:colon
r_return
id|SPARC_BSD_EMUL
suffix:semicolon
r_case
id|PER_SVR4
suffix:colon
r_return
id|SPARC_SOL_EMUL
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif /* __SPARC64_NAMEI_H */
eof
