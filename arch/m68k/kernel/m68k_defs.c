multiline_comment|/*&n; * This program is used to generate definitions needed by&n; * assembly language modules.&n; *&n; * We use the technique used in the OSF Mach kernel code:&n; * generate asm statements containing #defines,&n; * compile this file to assembler, and then extract the&n; * #defines from the assembly-language output.&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
DECL|macro|DEFINE
mdefine_line|#define DEFINE(sym, val) &bslash;&n;&t;asm volatile(&quot;&bslash;n#define &quot; #sym &quot; %0&quot; : : &quot;i&quot; (val))
DECL|function|main
r_int
id|main
c_func
(paren
r_void
)paren
(brace
id|DEFINE
c_func
(paren
id|TS_TSS
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|tss
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TS_ESP0
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|tss.esp0
)paren
)paren
suffix:semicolon
id|DEFINE
c_func
(paren
id|TS_FPU
comma
m_offsetof
(paren
r_struct
id|task_struct
comma
id|tss.fp
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof