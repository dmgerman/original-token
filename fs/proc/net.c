multiline_comment|/*&n; *  linux/fs/proc/net.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  gjh 3/&squot;93 heim@peanuts.informatik.uni-tuebingen.de (Gerald J. Heim)&n; *            most of this file is stolen from base.c&n; *            it works, but you shouldn&squot;t use it as a guideline&n; *            for new proc-fs entries. once i&squot;ll make it better.&n; * fvk 3/&squot;93  waltje@uwalt.nl.mugnet.org (Fred N. van Kempen)&n; *&t;      cleaned up the whole thing, moved &quot;net&quot; specific code to&n; *&t;      the NET kernel layer (where it belonged in the first place).&n; * Michael K. Johnson (johnsonm@stolaf.edu) 3/93&n; *            Added support from my previous inet.c.  Cleaned things up&n; *            quite a bit, modularized the code.&n; * fvk 4/&squot;93  waltje@uwalt.nl.mugnet.org (Fred N. van Kempen)&n; *&t;      Renamed &quot;route_get_info()&quot; to &quot;rt_get_info()&quot; for consistency.&n; * Alan Cox (gw4pts@gw4pts.ampr.org) 4/94&n; *&t;      Dusted off the code and added IPX. Fixed the 4K limit.&n; * Erik Schoenfelder (schoenfr@ibr.cs.tu-bs.de)&n; *&t;      /proc/net/snmp.&n; * Alan Cox (gw4pts@gw4pts.ampr.org) 1/95&n; *&t;      Added Appletalk slots&n; *&n; *  proc net directory handling functions&n; */
macro_line|#include &lt;linux/autoconf.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
DECL|macro|PROC_BLOCK_SIZE
mdefine_line|#define PROC_BLOCK_SIZE&t;(3*1024)&t;&t;/* 4K page size but our output routines use some slack for overruns */
DECL|function|proc_readnet
r_static
r_int
id|proc_readnet
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|page
suffix:semicolon
r_int
id|bytes
op_assign
id|count
suffix:semicolon
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|start
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dp
op_assign
(paren
r_struct
id|proc_dir_entry
op_star
)paren
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_while
c_loop
(paren
id|bytes
OG
l_int|0
)paren
(brace
r_int
id|length
comma
id|thistime
op_assign
id|bytes
suffix:semicolon
r_if
c_cond
(paren
id|bytes
OG
id|PROC_BLOCK_SIZE
)paren
id|thistime
op_assign
id|PROC_BLOCK_SIZE
suffix:semicolon
id|length
op_assign
id|dp
op_member_access_from_pointer
id|get_info
c_func
(paren
id|page
comma
op_amp
id|start
comma
id|file-&gt;f_pos
comma
id|thistime
comma
(paren
id|file-&gt;f_flags
op_amp
id|O_ACCMODE
)paren
op_eq
id|O_RDWR
)paren
suffix:semicolon
multiline_comment|/*&n; &t;&t; *&t;We have been given a non page aligned block of&n;&t;&t; *&t;the data we asked for + a bit. We have been given&n; &t;&t; *&t;the start pointer and we know the length.. &n;&t;&t; */
r_if
c_cond
(paren
id|length
op_le
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/*&n; &t;&t; *&t;Copy the bytes&n;&t;&t; */
id|memcpy_tofs
c_func
(paren
id|buf
op_plus
id|copied
comma
id|start
comma
id|length
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|length
suffix:semicolon
multiline_comment|/* Move down the file */
id|bytes
op_sub_assign
id|length
suffix:semicolon
id|copied
op_add_assign
id|length
suffix:semicolon
r_if
c_cond
(paren
id|length
OL
id|thistime
)paren
r_break
suffix:semicolon
multiline_comment|/* End of file */
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
)brace
DECL|variable|proc_net_operations
r_static
r_struct
id|file_operations
id|proc_net_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|proc_readnet
comma
multiline_comment|/* read - bad */
l_int|NULL
comma
multiline_comment|/* write - bad */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select - default */
l_int|NULL
comma
multiline_comment|/* ioctl - default */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc directories can do almost nothing..&n; */
DECL|variable|proc_net_inode_operations
r_struct
id|inode_operations
id|proc_net_inode_operations
op_assign
(brace
op_amp
id|proc_net_operations
comma
multiline_comment|/* default net file-ops */
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
l_int|NULL
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
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
