multiline_comment|/*&n; * stats.c&n; * &n; * CODA operation statistics&n; *&n; * (c) March, 1998 Zhanyong Wan &lt;zhanyong.wan@yale.edu&gt;&n; *&n; */
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
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
macro_line|#include &lt;linux/coda_proc.h&gt;
DECL|variable|coda_vfs_stat
r_struct
id|coda_vfs_stats
id|coda_vfs_stat
suffix:semicolon
DECL|variable|coda_permission_stat
r_struct
id|coda_permission_stats
id|coda_permission_stat
suffix:semicolon
DECL|variable|coda_cache_inv_stat
r_struct
id|coda_cache_inv_stats
id|coda_cache_inv_stat
suffix:semicolon
DECL|variable|coda_upcall_stat
r_struct
id|coda_upcall_stats_entry
id|coda_upcall_stat
(braket
id|CFS_NCALLS
)braket
suffix:semicolon
multiline_comment|/* keep this in sync with coda.h! */
DECL|variable|coda_upcall_names
r_char
op_star
id|coda_upcall_names
(braket
)braket
op_assign
(brace
l_string|&quot;totals      &quot;
comma
multiline_comment|/*  0 */
l_string|&quot;noop        &quot;
comma
multiline_comment|/*  1 */
l_string|&quot;root        &quot;
comma
multiline_comment|/*  2 */
l_string|&quot;sync        &quot;
comma
multiline_comment|/*  3 */
l_string|&quot;open        &quot;
comma
multiline_comment|/*  4 */
l_string|&quot;close       &quot;
comma
multiline_comment|/*  5 */
l_string|&quot;ioctl       &quot;
comma
multiline_comment|/*  6 */
l_string|&quot;getattr     &quot;
comma
multiline_comment|/*  7 */
l_string|&quot;setattr     &quot;
comma
multiline_comment|/*  8 */
l_string|&quot;access      &quot;
comma
multiline_comment|/*  9 */
l_string|&quot;lookup      &quot;
comma
multiline_comment|/* 10 */
l_string|&quot;create      &quot;
comma
multiline_comment|/* 11 */
l_string|&quot;remove      &quot;
comma
multiline_comment|/* 12 */
l_string|&quot;link        &quot;
comma
multiline_comment|/* 13 */
l_string|&quot;rename      &quot;
comma
multiline_comment|/* 14 */
l_string|&quot;mkdir       &quot;
comma
multiline_comment|/* 15 */
l_string|&quot;rmdir       &quot;
comma
multiline_comment|/* 16 */
l_string|&quot;readdir     &quot;
comma
multiline_comment|/* 17 */
l_string|&quot;symlink     &quot;
comma
multiline_comment|/* 18 */
l_string|&quot;readlink    &quot;
comma
multiline_comment|/* 19 */
l_string|&quot;fsync       &quot;
comma
multiline_comment|/* 20 */
l_string|&quot;inactive    &quot;
comma
multiline_comment|/* 21 */
l_string|&quot;vget        &quot;
comma
multiline_comment|/* 22 */
l_string|&quot;signal      &quot;
comma
multiline_comment|/* 23 */
l_string|&quot;replace     &quot;
comma
multiline_comment|/* 24 */
l_string|&quot;flush       &quot;
comma
multiline_comment|/* 25 */
l_string|&quot;purgeuser   &quot;
comma
multiline_comment|/* 26 */
l_string|&quot;zapfile     &quot;
comma
multiline_comment|/* 27 */
l_string|&quot;zapdir      &quot;
comma
multiline_comment|/* 28 */
l_string|&quot;zapvnode    &quot;
comma
multiline_comment|/* 28 */
l_string|&quot;purgefid    &quot;
comma
multiline_comment|/* 30 */
l_string|&quot;open_by_path&quot;
multiline_comment|/* 31 */
)brace
suffix:semicolon
DECL|function|reset_coda_vfs_stats
r_void
id|reset_coda_vfs_stats
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|coda_vfs_stat
comma
l_int|0
comma
r_sizeof
(paren
id|coda_vfs_stat
)paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|reset_upcall_entry
c_func
(paren
r_struct
id|coda_upcall_stats_entry
op_star
id|pentry
)paren
(brace
id|pentry-&gt;count
op_assign
l_int|0
suffix:semicolon
id|pentry-&gt;time_sum
op_assign
id|pentry-&gt;time_squared_sum
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|reset_coda_upcall_stats
r_void
id|reset_coda_upcall_stats
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|coda_upcall_stat
comma
l_int|0
comma
r_sizeof
(paren
id|coda_upcall_stat
)paren
)paren
suffix:semicolon
)brace
DECL|function|reset_coda_permission_stats
r_void
id|reset_coda_permission_stats
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|coda_permission_stat
comma
l_int|0
comma
r_sizeof
(paren
id|coda_permission_stat
)paren
)paren
suffix:semicolon
)brace
DECL|function|reset_coda_cache_inv_stats
r_void
id|reset_coda_cache_inv_stats
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|coda_cache_inv_stat
comma
l_int|0
comma
r_sizeof
(paren
id|coda_cache_inv_stat
)paren
)paren
suffix:semicolon
)brace
DECL|function|do_time_stats
r_void
id|do_time_stats
c_func
(paren
r_struct
id|coda_upcall_stats_entry
op_star
id|pentry
comma
r_int
r_int
id|runtime
)paren
(brace
r_int
r_int
id|time
op_assign
id|runtime
op_star
l_int|1000
op_div
id|HZ
suffix:semicolon
multiline_comment|/* time in ms */
id|CDEBUG
c_func
(paren
id|D_SPECIAL
comma
l_string|&quot;time: %ld&bslash;n&quot;
comma
id|time
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pentry-&gt;count
op_eq
l_int|0
)paren
(brace
id|pentry-&gt;time_sum
op_assign
id|pentry-&gt;time_squared_sum
op_assign
l_int|0
suffix:semicolon
)brace
id|pentry-&gt;count
op_increment
suffix:semicolon
id|pentry-&gt;time_sum
op_add_assign
id|time
suffix:semicolon
id|pentry-&gt;time_squared_sum
op_add_assign
id|time
op_star
id|time
suffix:semicolon
)brace
DECL|function|coda_upcall_stats
r_void
id|coda_upcall_stats
c_func
(paren
r_int
id|opcode
comma
r_int
r_int
id|runtime
)paren
(brace
r_struct
id|coda_upcall_stats_entry
op_star
id|pentry
suffix:semicolon
r_if
c_cond
(paren
id|opcode
template_param
id|CFS_NCALLS
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Nasty opcode %d passed to coda_upcall_stats&bslash;n&quot;
comma
id|opcode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pentry
op_assign
op_amp
id|coda_upcall_stat
(braket
id|opcode
)braket
suffix:semicolon
id|do_time_stats
c_func
(paren
id|pentry
comma
id|runtime
)paren
suffix:semicolon
multiline_comment|/* fill in the totals */
id|pentry
op_assign
op_amp
id|coda_upcall_stat
(braket
l_int|0
)braket
suffix:semicolon
id|do_time_stats
c_func
(paren
id|pentry
comma
id|runtime
)paren
suffix:semicolon
)brace
DECL|function|get_time_average
r_int
r_int
id|get_time_average
c_func
(paren
r_const
r_struct
id|coda_upcall_stats_entry
op_star
id|pentry
)paren
(brace
r_return
(paren
id|pentry-&gt;count
op_eq
l_int|0
)paren
ques
c_cond
l_int|0
suffix:colon
id|pentry-&gt;time_sum
op_div
id|pentry-&gt;count
suffix:semicolon
)brace
DECL|function|absolute
r_static
r_inline
r_int
r_int
id|absolute
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_return
id|x
op_ge
l_int|0
ques
c_cond
id|x
suffix:colon
op_minus
id|x
suffix:semicolon
)brace
DECL|function|sqr_root
r_static
r_int
r_int
id|sqr_root
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|y
op_assign
id|x
comma
id|r
suffix:semicolon
r_int
id|n_bit
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|x
OL
l_int|0
)paren
id|x
op_assign
op_minus
id|x
suffix:semicolon
r_while
c_loop
(paren
id|y
)paren
(brace
id|y
op_rshift_assign
l_int|1
suffix:semicolon
id|n_bit
op_increment
suffix:semicolon
)brace
id|r
op_assign
l_int|1
op_lshift
(paren
id|n_bit
op_div
l_int|2
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|r
op_assign
(paren
id|r
op_plus
id|x
op_div
id|r
)paren
op_div
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|r
op_star
id|r
op_le
id|x
op_logical_and
id|x
OL
(paren
id|r
op_plus
l_int|1
)paren
op_star
(paren
id|r
op_plus
l_int|1
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|r
suffix:semicolon
)brace
DECL|function|get_time_std_deviation
r_int
r_int
id|get_time_std_deviation
c_func
(paren
r_const
r_struct
id|coda_upcall_stats_entry
op_star
id|pentry
)paren
(brace
r_int
r_int
id|time_avg
suffix:semicolon
r_if
c_cond
(paren
id|pentry-&gt;count
op_le
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|time_avg
op_assign
id|get_time_average
c_func
(paren
id|pentry
)paren
suffix:semicolon
r_return
id|sqr_root
c_func
(paren
(paren
id|pentry-&gt;time_squared_sum
op_div
id|pentry-&gt;count
)paren
op_minus
id|time_avg
op_star
id|time_avg
)paren
suffix:semicolon
)brace
DECL|function|do_reset_coda_vfs_stats
r_int
id|do_reset_coda_vfs_stats
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
r_if
c_cond
(paren
id|write
)paren
(brace
id|reset_coda_vfs_stats
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_reset_coda_upcall_stats
r_int
id|do_reset_coda_upcall_stats
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
r_if
c_cond
(paren
id|write
)paren
(brace
id|reset_coda_upcall_stats
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_reset_coda_permission_stats
r_int
id|do_reset_coda_permission_stats
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
r_if
c_cond
(paren
id|write
)paren
(brace
id|reset_coda_permission_stats
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_reset_coda_cache_inv_stats
r_int
id|do_reset_coda_cache_inv_stats
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
r_if
c_cond
(paren
id|write
)paren
(brace
id|reset_coda_cache_inv_stats
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|coda_vfs_stats_get_info
r_int
id|coda_vfs_stats_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_struct
id|coda_vfs_stats
op_star
id|ps
op_assign
op_amp
id|coda_vfs_stat
suffix:semicolon
multiline_comment|/* this works as long as we are below 1024 characters! */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Coda VFS statistics&bslash;n&quot;
l_string|&quot;===================&bslash;n&bslash;n&quot;
l_string|&quot;File Operations:&bslash;n&quot;
l_string|&quot;&bslash;tfile_read&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tfile_write&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tfile_mmap&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;topen&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;trelase&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tfsync&bslash;t&bslash;t%9d&bslash;n&bslash;n&quot;
l_string|&quot;Dir Operations:&bslash;n&quot;
l_string|&quot;&bslash;treaddir&bslash;t&bslash;t%9d&bslash;n&bslash;n&quot;
l_string|&quot;Inode Operations&bslash;n&quot;
l_string|&quot;&bslash;tcreate&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tlookup&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tlink&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tunlink&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tsymlink&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tmkdir&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;trmdir&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;trename&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;tpermission&bslash;t%9d&bslash;n&quot;
l_string|&quot;&bslash;treadpage&bslash;t%9d&bslash;n&quot;
comma
multiline_comment|/* file operations */
id|ps-&gt;file_read
comma
id|ps-&gt;file_write
comma
id|ps-&gt;file_mmap
comma
id|ps-&gt;open
comma
id|ps-&gt;release
comma
id|ps-&gt;fsync
comma
multiline_comment|/* dir operations */
id|ps-&gt;readdir
comma
multiline_comment|/* inode operations */
id|ps-&gt;create
comma
id|ps-&gt;lookup
comma
id|ps-&gt;link
comma
id|ps-&gt;unlink
comma
id|ps-&gt;symlink
comma
id|ps-&gt;mkdir
comma
id|ps-&gt;rmdir
comma
id|ps-&gt;rename
comma
id|ps-&gt;permission
comma
id|ps-&gt;readpage
)paren
suffix:semicolon
id|begin
op_assign
id|offset
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|coda_upcall_stats_get_info
r_int
id|coda_upcall_stats_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
id|off_t
id|pos
op_assign
l_int|0
suffix:semicolon
r_char
id|tmpbuf
(braket
l_int|80
)braket
suffix:semicolon
r_int
id|tmplen
op_assign
l_int|0
suffix:semicolon
id|ENTRY
suffix:semicolon
multiline_comment|/* this works as long as we are below 1024 characters! */
r_if
c_cond
(paren
id|offset
OL
l_int|80
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%-79s&bslash;n&quot;
comma
l_string|&quot;Coda upcall statistics&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|160
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-79s&bslash;n&quot;
comma
l_string|&quot;======================&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|240
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-79s&bslash;n&quot;
comma
l_string|&quot;upcall&bslash;t&bslash;t    count&bslash;tavg time(ms)&bslash;tstd deviation(ms)&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
l_int|320
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-79s&bslash;n&quot;
comma
l_string|&quot;------&bslash;t&bslash;t    -----&bslash;t------------&bslash;t-----------------&quot;
)paren
suffix:semicolon
id|pos
op_assign
l_int|320
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CFS_NCALLS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmplen
op_add_assign
id|sprintf
c_func
(paren
id|tmpbuf
comma
l_string|&quot;%s&bslash;t%9d&bslash;t%10ld&bslash;t%10ld&quot;
comma
id|coda_upcall_names
(braket
id|i
)braket
comma
id|coda_upcall_stat
(braket
id|i
)braket
dot
id|count
comma
id|get_time_average
c_func
(paren
op_amp
id|coda_upcall_stat
(braket
id|i
)braket
)paren
comma
id|coda_upcall_stat
(braket
id|i
)braket
dot
id|time_squared_sum
)paren
suffix:semicolon
id|pos
op_add_assign
l_int|80
suffix:semicolon
r_if
c_cond
(paren
id|pos
OL
id|offset
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;%-79s&bslash;n&quot;
comma
id|tmpbuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_ge
id|length
)paren
r_break
suffix:semicolon
)brace
id|begin
op_assign
id|len
op_minus
(paren
id|pos
op_minus
id|offset
)paren
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|coda_permission_stats_get_info
r_int
id|coda_permission_stats_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_struct
id|coda_permission_stats
op_star
id|ps
op_assign
op_amp
id|coda_permission_stat
suffix:semicolon
multiline_comment|/* this works as long as we are below 1024 characters! */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Coda permission statistics&bslash;n&quot;
l_string|&quot;==========================&bslash;n&bslash;n&quot;
l_string|&quot;count&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;hit count&bslash;t%9d&bslash;n&quot;
comma
id|ps-&gt;count
comma
id|ps-&gt;hit_count
)paren
suffix:semicolon
id|begin
op_assign
id|offset
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|coda_cache_inv_stats_get_info
r_int
id|coda_cache_inv_stats_get_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
comma
r_int
id|dummy
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
suffix:semicolon
r_struct
id|coda_cache_inv_stats
op_star
id|ps
op_assign
op_amp
id|coda_cache_inv_stat
suffix:semicolon
multiline_comment|/* this works as long as we are below 1024 characters! */
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Coda cache invalidation statistics&bslash;n&quot;
l_string|&quot;==================================&bslash;n&bslash;n&quot;
l_string|&quot;flush&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;purge user&bslash;t%9d&bslash;n&quot;
l_string|&quot;zap_dir&bslash;t&bslash;t%9d&bslash;n&quot;
l_string|&quot;zap_file&bslash;t%9d&bslash;n&quot;
l_string|&quot;zap_vnode&bslash;t%9d&bslash;n&quot;
l_string|&quot;purge_fid&bslash;t%9d&bslash;n&quot;
l_string|&quot;replace&bslash;t&bslash;t%9d&bslash;n&quot;
comma
id|ps-&gt;flush
comma
id|ps-&gt;purge_user
comma
id|ps-&gt;zap_dir
comma
id|ps-&gt;zap_file
comma
id|ps-&gt;zap_vnode
comma
id|ps-&gt;purge_fid
comma
id|ps-&gt;replace
)paren
suffix:semicolon
id|begin
op_assign
id|offset
suffix:semicolon
op_star
id|start
op_assign
id|buffer
op_plus
id|begin
suffix:semicolon
id|len
op_sub_assign
id|begin
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|length
)paren
id|len
op_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
