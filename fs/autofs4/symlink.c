multiline_comment|/* -*- c -*- --------------------------------------------------------------- *&n; *&n; * linux/fs/autofs/symlink.c&n; *&n; *  Copyright 1997-1998 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#include &quot;autofs_i.h&quot;
DECL|function|autofs4_readlink
r_static
r_int
id|autofs4_readlink
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
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|vfs_readlink
c_func
(paren
id|dentry
comma
id|buffer
comma
id|buflen
comma
id|ino-&gt;u.symlink
)paren
suffix:semicolon
)brace
DECL|function|autofs4_follow_link
r_static
r_int
id|autofs4_follow_link
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|nameidata
op_star
id|nd
)paren
(brace
r_struct
id|autofs_info
op_star
id|ino
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|vfs_follow_link
c_func
(paren
id|nd
comma
id|ino-&gt;u.symlink
)paren
suffix:semicolon
)brace
DECL|variable|autofs4_symlink_inode_operations
r_struct
id|inode_operations
id|autofs4_symlink_inode_operations
op_assign
(brace
id|readlink
suffix:colon
id|autofs4_readlink
comma
id|follow_link
suffix:colon
id|autofs4_follow_link
)brace
suffix:semicolon
eof
