macro_line|#ifndef __ASM_SH_BUGS_H
DECL|macro|__ASM_SH_BUGS_H
mdefine_line|#define __ASM_SH_BUGS_H
multiline_comment|/*&n; * This is included by init/main.c to check for architecture-dependent bugs.&n; *&n; * Needs:&n; *&t;void check_bugs(void);&n; */
multiline_comment|/*&n; * I don&squot;t know of any Super-H bugs yet.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|check_bugs
c_func
(paren
r_void
)paren
)paren
(brace
)brace
macro_line|#endif /* __ASM_SH_BUGS_H */
eof
