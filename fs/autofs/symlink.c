multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/fs/autofs/symlink.c&n; *&n; *  Copyright 1997 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;autofs_i.h&quot;
DECL|function|autofs_readlink
r_static
r_int
id|autofs_readlink
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_char
op_star
id|buffer
comma
r_int
id|buflen
)paren
(brace
r_struct
id|autofs_symlink
op_star
id|sl
suffix:semicolon
r_int
id|len
suffix:semicolon
id|sl
op_assign
(paren
r_struct
id|autofs_symlink
op_star
)paren
id|dentry-&gt;d_inode-&gt;u.generic_ip
suffix:semicolon
id|len
op_assign
id|sl-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|buflen
)paren
id|len
op_assign
id|buflen
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buffer
comma
id|sl-&gt;data
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|autofs_follow_link
r_static
r_struct
id|dentry
op_star
id|autofs_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|dentry
op_star
id|base
comma
r_int
r_int
id|follow
)paren
(brace
r_struct
id|autofs_symlink
op_star
id|sl
suffix:semicolon
id|sl
op_assign
(paren
r_struct
id|autofs_symlink
op_star
)paren
id|dentry-&gt;d_inode-&gt;u.generic_ip
suffix:semicolon
r_return
id|lookup_dentry
c_func
(paren
id|sl-&gt;data
comma
id|base
comma
id|follow
)paren
suffix:semicolon
)brace
DECL|variable|autofs_symlink_inode_operations
r_struct
id|inode_operations
id|autofs_symlink_inode_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* file operations */
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
id|autofs_readlink
comma
multiline_comment|/* readlink */
id|autofs_follow_link
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
multiline_comment|/* updatepage */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
eof
