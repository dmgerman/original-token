macro_line|#ifndef _SYS_WAIT_H
DECL|macro|_SYS_WAIT_H
mdefine_line|#define _SYS_WAIT_H
macro_line|#include &lt;sys/types.h&gt;
DECL|macro|_LOW
mdefine_line|#define _LOW(v)&t;&t;( (v) &amp; 0377)
DECL|macro|_HIGH
mdefine_line|#define _HIGH(v)&t;( ((v) &gt;&gt; 8) &amp; 0377)
multiline_comment|/* options for waitpid, WUNTRACED not supported */
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;1
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;2
DECL|macro|WIFEXITED
mdefine_line|#define WIFEXITED(s)&t;(!((s)&amp;0xFF)
DECL|macro|WIFSTOPPED
mdefine_line|#define WIFSTOPPED(s)&t;(((s)&amp;0xFF)==0x7F)
DECL|macro|WEXITSTATUS
mdefine_line|#define WEXITSTATUS(s)&t;(((s)&gt;&gt;8)&amp;0xFF)
DECL|macro|WTERMSIG
mdefine_line|#define WTERMSIG(s)&t;((s)&amp;0x7F)
DECL|macro|WSTOPSIG
mdefine_line|#define WSTOPSIG(s)&t;(((s)&gt;&gt;8)&amp;0xFF)
DECL|macro|WIFSIGNALED
mdefine_line|#define WIFSIGNALED(s)&t;(((unsigned int)(s)-1 &amp; 0xFFFF) &lt; 0xFF)
id|pid_t
id|wait
c_func
(paren
r_int
op_star
id|stat_loc
)paren
suffix:semicolon
id|pid_t
id|waitpid
c_func
(paren
id|pid_t
id|pid
comma
r_int
op_star
id|stat_loc
comma
r_int
id|options
)paren
suffix:semicolon
macro_line|#endif
eof
