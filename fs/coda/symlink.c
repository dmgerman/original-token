multiline_comment|/*&n; * Symlink inode operations for Coda filesystem&n; * Original version: (C) 1996 P. Braam and M. Callahan&n; * Rewritten for Linux 2.1. (C) 1997 Carnegie Mellon University&n; * &n; * Carnegie Mellon encourages users to contribute improvements to&n; * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cnode.h&gt;
macro_line|#include &lt;linux/coda_namecache.h&gt;
r_static
r_int
id|coda_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
suffix:semicolon
DECL|variable|coda_symlink_inode_operations
r_struct
id|inode_operations
id|coda_symlink_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* no file-operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
id|coda_readlink
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
l_int|NULL
comma
multiline_comment|/* update page */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|function|coda_readlink
r_static
r_int
id|coda_readlink
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_char
op_star
id|buffer
comma
r_int
id|length
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
id|error
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
r_struct
id|cnode
op_star
id|cp
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cp
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cp
)paren
suffix:semicolon
multiline_comment|/* the maximum length we receive is len */
r_if
c_cond
(paren
id|length
OG
id|CFS_MAXPATHLEN
)paren
id|len
op_assign
id|CFS_MAXPATHLEN
suffix:semicolon
r_else
id|len
op_assign
id|length
suffix:semicolon
id|CODA_ALLOC
c_func
(paren
id|buf
comma
r_char
op_star
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|error
op_assign
id|venus_readlink
c_func
(paren
id|inode-&gt;i_sb
comma
op_amp
(paren
id|cp-&gt;c_fid
)paren
comma
id|buf
comma
op_amp
id|len
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;result %s&bslash;n&quot;
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|copy_to_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|put_user
c_func
(paren
l_char|&squot;&bslash;0&squot;
comma
id|buffer
op_plus
id|len
)paren
suffix:semicolon
id|error
op_assign
id|len
suffix:semicolon
id|CODA_FREE
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|error
suffix:semicolon
)brace
eof
