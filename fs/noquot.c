multiline_comment|/*&n; *&t;A Non implementation of disk quotas. Chainsawed from dquot.c by&n; *&t;Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;. This saves us memory without&n; *&t;having zillions of #ifdefs (Or if it had been done right one&n; *&t;&n; *&t;QUOTA_OP(inode,func)&n; *&n; *&t;macro.)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mount.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define min(a,b) ((a) &lt; (b)) ? (a) : (b)
macro_line|#endif
DECL|function|sync_dquots
r_int
id|sync_dquots
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Trash the cache for a certain type on a device.&n; */
DECL|function|invalidate_dquots
r_void
id|invalidate_dquots
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
(brace
)brace
multiline_comment|/*&n; * Initialize pointer in an inode to the right dquots.&n; */
DECL|function|dquot_initialize
r_void
id|dquot_initialize
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
)paren
(brace
)brace
DECL|function|dquot_drop
r_void
id|dquot_drop
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
)brace
DECL|function|dquot_init
r_void
id|dquot_init
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/*&n; * Turn quota off on a device. type == -1 ==&gt; quotaoff for all types (umount)&n; */
DECL|function|quota_off
r_int
id|quota_off
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|quota_on
r_int
id|quota_on
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
comma
r_char
op_star
id|path
)paren
(brace
r_return
op_minus
id|ENOPKG
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok this is the systemcall interface, this communicates with&n; * the userlevel programs. Currently this only supports diskquota&n; * calls. Maybe we need to add the process quotas etc in the future.&n; * But we probably better use rlimits for that.&n; */
DECL|function|sys_quotactl
id|asmlinkage
r_int
id|sys_quotactl
c_func
(paren
r_int
id|cmd
comma
r_const
r_char
op_star
id|special
comma
r_int
id|id
comma
id|caddr_t
id|addr
)paren
(brace
r_return
op_minus
id|ENOPKG
suffix:semicolon
)brace
eof
