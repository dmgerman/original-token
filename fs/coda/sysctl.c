multiline_comment|/*&n; * Sysctl operations for Coda filesystem&n; * Original version: (C) 1996 P. Braam and M. Callahan&n; * Rewritten for Linux 2.1. (C) 1997 Carnegie Mellon University&n; * &n; * Carnegie Mellon encourages users to contribute improvements to&n; * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).&n; */
multiline_comment|/* sysctl entries for Coda! */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_cnode.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
macro_line|#include &lt;linux/coda_sysctl.h&gt;
r_extern
r_int
id|coda_debug
suffix:semicolon
multiline_comment|/* extern int cfsnc_use; */
r_extern
r_int
id|coda_print_entry
suffix:semicolon
multiline_comment|/* extern int cfsnc_flushme; */
r_extern
r_int
id|cfsnc_procsize
suffix:semicolon
multiline_comment|/* extern void cfsnc_flush(void); */
r_void
id|coda_sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|coda_sysctl_clean
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|coda_dointvec
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
suffix:semicolon
DECL|variable|fs_table_header
DECL|variable|coda_table_header
r_struct
id|ctl_table_header
op_star
id|fs_table_header
comma
op_star
id|coda_table_header
suffix:semicolon
DECL|macro|FS_CODA
mdefine_line|#define FS_CODA         1       /* Coda file system */
DECL|macro|CODA_DEBUG
mdefine_line|#define CODA_DEBUG  &t; 1&t; /* control debugging */
DECL|macro|CODA_ENTRY
mdefine_line|#define CODA_ENTRY&t; 2       /* control enter/leave pattern */
DECL|macro|CODA_TIMEOUT
mdefine_line|#define CODA_TIMEOUT    3       /* timeout on upcalls to become intrble */
DECL|macro|CODA_MC
mdefine_line|#define CODA_MC         4       /* use/do not use the access cache */
DECL|macro|CODA_HARD
mdefine_line|#define CODA_HARD       5       /* mount type &quot;hard&quot; or &quot;soft&quot; */
DECL|variable|coda_table
r_static
id|ctl_table
id|coda_table
(braket
)braket
op_assign
(brace
(brace
id|CODA_DEBUG
comma
l_string|&quot;debug&quot;
comma
op_amp
id|coda_debug
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|coda_dointvec
)brace
comma
(brace
id|CODA_ENTRY
comma
l_string|&quot;printentry&quot;
comma
op_amp
id|coda_print_entry
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|coda_dointvec
)brace
comma
(brace
id|CODA_MC
comma
l_string|&quot;accesscache&quot;
comma
op_amp
id|coda_access_cache
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|coda_dointvec
)brace
comma
(brace
id|CODA_TIMEOUT
comma
l_string|&quot;timeout&quot;
comma
op_amp
id|coda_timeout
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|coda_dointvec
)brace
comma
(brace
id|CODA_HARD
comma
l_string|&quot;hard&quot;
comma
op_amp
id|coda_hard
comma
r_sizeof
(paren
r_int
)paren
comma
l_int|0644
comma
l_int|NULL
comma
op_amp
id|coda_dointvec
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|fs_table
r_static
id|ctl_table
id|fs_table
(braket
)braket
op_assign
(brace
(brace
id|FS_CODA
comma
l_string|&quot;coda&quot;
comma
l_int|NULL
comma
l_int|0
comma
l_int|0555
comma
id|coda_table
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|coda_sysctl_init
r_void
id|coda_sysctl_init
c_func
(paren
)paren
(brace
id|fs_table_header
op_assign
id|register_sysctl_table
c_func
(paren
id|fs_table
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&t;coda_table_header = register_sysctl_table(coda_table, 0);*/
)brace
DECL|function|coda_sysctl_clean
r_void
id|coda_sysctl_clean
c_func
(paren
)paren
(brace
multiline_comment|/*unregister_sysctl_table(coda_table_header);*/
id|unregister_sysctl_table
c_func
(paren
id|fs_table_header
)paren
suffix:semicolon
)brace
DECL|function|coda_dointvec
r_int
id|coda_dointvec
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
op_star
id|i
comma
id|vleft
comma
id|first
op_assign
l_int|1
comma
id|len
comma
id|left
comma
id|neg
comma
id|val
suffix:semicolon
DECL|macro|TMPBUFLEN
mdefine_line|#define TMPBUFLEN 20
r_char
id|buf
(braket
id|TMPBUFLEN
)braket
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|table-&gt;data
op_logical_or
op_logical_neg
id|table-&gt;maxlen
op_logical_or
op_logical_neg
op_star
id|lenp
op_logical_or
(paren
id|filp-&gt;f_pos
op_logical_and
op_logical_neg
id|write
)paren
)paren
(brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|i
op_assign
(paren
r_int
op_star
)paren
id|table-&gt;data
suffix:semicolon
id|vleft
op_assign
id|table-&gt;maxlen
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|left
op_assign
op_star
id|lenp
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|left
op_logical_and
id|vleft
op_decrement
suffix:semicolon
id|i
op_increment
comma
id|first
op_assign
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|write
)paren
(brace
r_while
c_loop
(paren
id|left
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|left
op_decrement
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|buffer
)paren
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
r_break
suffix:semicolon
id|neg
op_assign
l_int|0
suffix:semicolon
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|TMPBUFLEN
op_minus
l_int|1
)paren
id|len
op_assign
id|TMPBUFLEN
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|buffer
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
op_eq
l_char|&squot;-&squot;
op_logical_and
id|left
OG
l_int|1
)paren
(brace
id|neg
op_assign
l_int|1
suffix:semicolon
id|left
op_decrement
comma
id|p
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|p
template_param
l_char|&squot;9&squot;
)paren
r_break
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|len
op_assign
id|p
op_minus
id|buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
OL
id|left
)paren
op_logical_and
op_star
id|p
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|neg
)paren
id|val
op_assign
op_minus
id|val
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
id|left
op_sub_assign
id|len
suffix:semicolon
op_star
id|i
op_assign
id|val
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%d&quot;
comma
op_star
id|i
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|left
)paren
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|left
op_sub_assign
id|len
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|write
op_logical_and
op_logical_neg
id|first
op_logical_and
id|left
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|left
op_decrement
comma
id|buffer
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|left
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|left
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|write
op_logical_and
id|first
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|lenp
op_sub_assign
id|left
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
op_star
id|lenp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof