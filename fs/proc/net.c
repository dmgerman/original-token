multiline_comment|/*&n; *  linux/fs/proc/net.c&n; *&n; *  Copyright (C) 1991, 1992 Linus Torvalds&n; *&n; *  gjh 3/&squot;93 heim@peanuts.informatik.uni-tuebingen.de (Gerald J. Heim)&n; *            most of this file is stolen from base.c&n; *            it works, but you shouldn&squot;t use it as a guideline&n; *            for new proc-fs entries. once i&squot;ll make it better.&n; * fvk 3/&squot;93  waltje@uwalt.nl.mugnet.org (Fred N. van Kempen)&n; *&t;      cleaned up the whole thing, moved &quot;net&quot; specific code to&n; *&t;      the NET kernel layer (where it belonged in the first place).&n; * Michael K. Johnson (johnsonm@stolaf.edu) 3/93&n; *            Added support from my previous inet.c.  Cleaned things up&n; *            quite a bit, modularized the code.&n; * fvk 4/&squot;93  waltje@uwalt.nl.mugnet.org (Fred N. van Kempen)&n; *&t;      Renamed &quot;route_get_info()&quot; to &quot;rt_get_info()&quot; for consistency.&n; *&n; *  proc net directory handling functions&n; */
macro_line|#include &lt;linux/autoconf.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
multiline_comment|/* forward references */
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
suffix:semicolon
r_static
r_int
id|proc_readnetdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|dirent
op_star
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|proc_lookupnet
c_func
(paren
r_struct
id|inode
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
r_struct
id|inode
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* the get_*_info() functions are in the net code, and are configured&n;   in via the standard mechanism... */
macro_line|#ifdef CONFIG_INET
r_extern
r_int
id|unix_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|tcp_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|udp_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|raw_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|arp_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dev_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|rt_get_info
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_INET */
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
id|proc_readnetdir
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
multiline_comment|/* default net directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookupnet
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
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|variable|net_dir
r_static
r_struct
id|proc_dir_entry
id|net_dir
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
l_int|2
comma
l_string|&quot;..&quot;
)brace
comma
(brace
l_int|8
comma
l_int|1
comma
l_string|&quot;.&quot;
)brace
macro_line|#ifdef CONFIG_INET
comma
(brace
l_int|128
comma
l_int|4
comma
l_string|&quot;unix&quot;
)brace
comma
(brace
l_int|129
comma
l_int|3
comma
l_string|&quot;arp&quot;
)brace
comma
(brace
l_int|130
comma
l_int|5
comma
l_string|&quot;route&quot;
)brace
comma
(brace
l_int|131
comma
l_int|3
comma
l_string|&quot;dev&quot;
)brace
comma
(brace
l_int|132
comma
l_int|3
comma
l_string|&quot;raw&quot;
)brace
comma
(brace
l_int|133
comma
l_int|3
comma
l_string|&quot;tcp&quot;
)brace
comma
(brace
l_int|134
comma
l_int|3
comma
l_string|&quot;udp&quot;
)brace
macro_line|#endif&t;/* CONFIG_INET */
)brace
suffix:semicolon
DECL|macro|NR_NET_DIRENTRY
mdefine_line|#define NR_NET_DIRENTRY ((sizeof (net_dir))/(sizeof (net_dir[0])))
DECL|function|proc_lookupnet
r_static
r_int
id|proc_lookupnet
c_func
(paren
r_struct
id|inode
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_int
id|len
comma
r_struct
id|inode
op_star
op_star
id|result
)paren
(brace
r_int
r_int
id|ino
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dir
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|dir-&gt;i_mode
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|i
op_assign
id|NR_NET_DIRENTRY
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
op_logical_and
op_logical_neg
id|proc_match
c_func
(paren
id|len
comma
id|name
comma
id|net_dir
op_plus
id|i
)paren
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|ino
op_assign
id|net_dir
(braket
id|i
)braket
dot
id|low_ino
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|result
op_assign
id|iget
c_func
(paren
id|dir-&gt;i_sb
comma
id|ino
)paren
)paren
)paren
(brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
op_minus
id|ENOENT
suffix:semicolon
)brace
id|iput
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_readnetdir
r_static
r_int
id|proc_readnetdir
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
id|filp
comma
r_struct
id|dirent
op_star
id|dirent
comma
r_int
id|count
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
op_logical_or
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|filp-&gt;f_pos
)paren
OL
id|NR_NET_DIRENTRY
)paren
(brace
id|de
op_assign
id|net_dir
op_plus
id|filp-&gt;f_pos
suffix:semicolon
id|filp-&gt;f_pos
op_increment
suffix:semicolon
id|i
op_assign
id|de-&gt;namelen
suffix:semicolon
id|ino
op_assign
id|de-&gt;low_ino
suffix:semicolon
id|put_fs_long
c_func
(paren
id|ino
comma
op_amp
id|dirent-&gt;d_ino
)paren
suffix:semicolon
id|put_fs_word
c_func
(paren
id|i
comma
op_amp
id|dirent-&gt;d_reclen
)paren
suffix:semicolon
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
id|j
op_assign
id|i
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|put_fs_byte
c_func
(paren
id|de-&gt;name
(braket
id|i
)braket
comma
id|i
op_plus
id|dirent-&gt;d_name
)paren
suffix:semicolon
r_return
id|j
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
id|length
suffix:semicolon
r_int
id|end
suffix:semicolon
r_int
r_int
id|ino
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
id|ino
op_assign
id|inode-&gt;i_ino
suffix:semicolon
r_switch
c_cond
(paren
id|ino
)paren
(brace
macro_line|#ifdef CONFIG_INET
r_case
l_int|128
suffix:colon
id|length
op_assign
id|unix_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|129
suffix:colon
id|length
op_assign
id|arp_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|130
suffix:colon
id|length
op_assign
id|rt_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|131
suffix:colon
id|length
op_assign
id|dev_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|132
suffix:colon
id|length
op_assign
id|raw_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|133
suffix:colon
id|length
op_assign
id|tcp_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|134
suffix:colon
id|length
op_assign
id|udp_get_info
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif /* CONFIG_INET */
r_default
suffix:colon
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
op_minus
id|EBADF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
id|length
)paren
(brace
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
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_plus
id|file-&gt;f_pos
OG
id|length
)paren
id|count
op_assign
id|length
op_minus
id|file-&gt;f_pos
suffix:semicolon
id|end
op_assign
id|count
op_plus
id|file-&gt;f_pos
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|page
op_plus
id|file-&gt;f_pos
comma
id|count
)paren
suffix:semicolon
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
id|file-&gt;f_pos
op_assign
id|end
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
eof
