macro_line|#ifndef _LINUX_KERNEL_H
DECL|macro|_LINUX_KERNEL_H
mdefine_line|#define _LINUX_KERNEL_H
multiline_comment|/*&n; * &squot;kernel.h&squot; contains some often-used function prototypes etc&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
r_int
id|verify_area
c_func
(paren
r_int
id|type
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|math_error
c_func
(paren
r_void
)paren
suffix:semicolon
r_volatile
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|str
)paren
suffix:semicolon
r_volatile
r_void
id|do_exit
c_func
(paren
r_int
id|error_code
)paren
suffix:semicolon
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
l_string|&quot;C&quot;
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
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_MALLOC
DECL|macro|kmalloc
mdefine_line|#define kmalloc(a,b) deb_kmalloc(__FILE__,__LINE__, a,b)
DECL|macro|kfree_s
mdefine_line|#define kfree_s(a,b) deb_kfree_s(__FILE__,__LINE__,a,b)
r_void
op_star
id|deb_kmalloc
c_func
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|deb_kfree_s
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|deb_kcheck_s
c_func
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|kfree
mdefine_line|#define kfree(a) deb_kfree_s(__FILE__,__LINE__, a,0)
DECL|macro|kcheck
mdefine_line|#define kcheck(a) deb_kcheck_s(__FILE__,__LINE__, a,0)
DECL|macro|kcheck_s
mdefine_line|#define kcheck_s(a,b) deb_kcheck_s(__FILE__,__LINE__, a,b)
macro_line|#else /* !debug */
r_void
op_star
id|kmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|kfree_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|kcheck_s
mdefine_line|#define kcheck_s(a,b) 0
DECL|macro|kfree
mdefine_line|#define kfree(x) kfree_s((x), 0)
DECL|macro|kcheck
mdefine_line|#define kcheck(x) kcheck_s((x), 0)
macro_line|#endif
multiline_comment|/*&n; * This is defined as a macro, but at some point this might become a&n; * real subroutine that sets a flag if it returns true (to do&n; * BSD-style accounting where the process is flagged if it uses root&n; * privs).  The implication of this is that you should do normal&n; * permissions checks first, and check suser() last.&n; */
DECL|macro|suser
mdefine_line|#define suser() (current-&gt;euid == 0)
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
