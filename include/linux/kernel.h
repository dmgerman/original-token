macro_line|#ifndef _LINUX_KERNEL_H
DECL|macro|_LINUX_KERNEL_H
mdefine_line|#define _LINUX_KERNEL_H
multiline_comment|/*&n; * &squot;kernel.h&squot; contains some often-used function prototypes etc&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
DECL|macro|INT_MAX
mdefine_line|#define INT_MAX&t;&t;((int)(~0U&gt;&gt;1))
DECL|macro|UINT_MAX
mdefine_line|#define UINT_MAX&t;(~0U)
DECL|macro|LONG_MAX
mdefine_line|#define LONG_MAX&t;((long)(~0UL&gt;&gt;1))
DECL|macro|ULONG_MAX
mdefine_line|#define ULONG_MAX&t;(~0UL)
DECL|macro|STACK_MAGIC
mdefine_line|#define STACK_MAGIC&t;0xdeadbeef
DECL|macro|KERN_EMERG
mdefine_line|#define&t;KERN_EMERG&t;&quot;&lt;0&gt;&quot;&t;/* system is unusable&t;&t;&t;*/
DECL|macro|KERN_ALERT
mdefine_line|#define&t;KERN_ALERT&t;&quot;&lt;1&gt;&quot;&t;/* action must be taken immediately&t;*/
DECL|macro|KERN_CRIT
mdefine_line|#define&t;KERN_CRIT&t;&quot;&lt;2&gt;&quot;&t;/* critical conditions&t;&t;&t;*/
DECL|macro|KERN_ERR
mdefine_line|#define&t;KERN_ERR&t;&quot;&lt;3&gt;&quot;&t;/* error conditions&t;&t;&t;*/
DECL|macro|KERN_WARNING
mdefine_line|#define&t;KERN_WARNING&t;&quot;&lt;4&gt;&quot;&t;/* warning conditions&t;&t;&t;*/
DECL|macro|KERN_NOTICE
mdefine_line|#define&t;KERN_NOTICE&t;&quot;&lt;5&gt;&quot;&t;/* normal but significant condition&t;*/
DECL|macro|KERN_INFO
mdefine_line|#define&t;KERN_INFO&t;&quot;&lt;6&gt;&quot;&t;/* informational&t;&t;&t;*/
DECL|macro|KERN_DEBUG
mdefine_line|#define&t;KERN_DEBUG&t;&quot;&lt;7&gt;&quot;&t;/* debug-level messages&t;&t;&t;*/
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 5)
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    __volatile__
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  /**/
DECL|macro|NORET_AND
macro_line|# define NORET_AND     /**/
macro_line|#else
DECL|macro|NORET_TYPE
macro_line|# define NORET_TYPE    /**/
DECL|macro|ATTRIB_NORET
macro_line|# define ATTRIB_NORET  __attribute__((noreturn))
DECL|macro|NORET_AND
macro_line|# define NORET_AND     noreturn,
macro_line|#endif
r_extern
r_void
id|math_error
c_func
(paren
r_void
)paren
suffix:semicolon
id|NORET_TYPE
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|NORET_AND
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
id|NORET_TYPE
r_void
id|do_exit
c_func
(paren
r_int
id|error_code
)paren
id|ATTRIB_NORET
suffix:semicolon
r_extern
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
comma
r_char
op_star
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
id|buf
comma
r_const
r_char
op_star
comma
id|va_list
)paren
suffix:semicolon
r_extern
r_int
id|session_of_pgrp
c_func
(paren
r_int
id|pgrp
)paren
suffix:semicolon
r_extern
r_int
id|kill_proc
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|kill_pg
c_func
(paren
r_int
id|pgrp
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
r_extern
r_int
id|kill_sl
c_func
(paren
r_int
id|sess
comma
r_int
id|sig
comma
r_int
id|priv
)paren
suffix:semicolon
id|asmlinkage
r_int
id|printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
id|__attribute__
(paren
(paren
id|format
(paren
id|printf
comma
l_int|1
comma
l_int|2
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n; * This is defined as a macro, but at some point this might become a&n; * real subroutine that sets a flag if it returns true (to do&n; * BSD-style accounting where the process is flagged if it uses root&n; * privs).  The implication of this is that you should do normal&n; * permissions checks first, and check suser() last.&n; *&n; * &quot;suser()&quot; checks against the effective user id, while &quot;fsuser()&quot;&n; * is used for file permission checking and checks against the fsuid..&n; */
DECL|macro|suser
mdefine_line|#define suser() (current-&gt;euid == 0)
DECL|macro|fsuser
mdefine_line|#define fsuser() (current-&gt;fsuid == 0)
macro_line|#endif /* __KERNEL__ */
DECL|macro|SI_LOAD_SHIFT
mdefine_line|#define SI_LOAD_SHIFT&t;16
DECL|struct|sysinfo
r_struct
id|sysinfo
(brace
DECL|member|uptime
r_int
id|uptime
suffix:semicolon
multiline_comment|/* Seconds since boot */
DECL|member|loads
r_int
r_int
id|loads
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* 1, 5, and 15 minute load averages */
DECL|member|totalram
r_int
r_int
id|totalram
suffix:semicolon
multiline_comment|/* Total usable main memory size */
DECL|member|freeram
r_int
r_int
id|freeram
suffix:semicolon
multiline_comment|/* Available memory size */
DECL|member|sharedram
r_int
r_int
id|sharedram
suffix:semicolon
multiline_comment|/* Amount of shared memory */
DECL|member|bufferram
r_int
r_int
id|bufferram
suffix:semicolon
multiline_comment|/* Memory used by buffers */
DECL|member|totalswap
r_int
r_int
id|totalswap
suffix:semicolon
multiline_comment|/* Total swap space size */
DECL|member|freeswap
r_int
r_int
id|freeswap
suffix:semicolon
multiline_comment|/* swap space still available */
DECL|member|procs
r_int
r_int
id|procs
suffix:semicolon
multiline_comment|/* Number of current processes */
DECL|member|_f
r_char
id|_f
(braket
l_int|22
)braket
suffix:semicolon
multiline_comment|/* Pads structure to 64 bytes */
)brace
suffix:semicolon
macro_line|#endif
eof
