multiline_comment|/*****************************************************************************&n;* wanproc.c&t;WAN Router Module. /proc filesystem interface.&n;*&n;*&t;&t;This module is completely hardware-independent and provides&n;*&t;&t;access to the router using Linux /proc filesystem.&n;*&n;* Author:&t;Gene Kozin&t;&lt;genek@compuserve.com&gt;&n;*&n;* Copyright:&t;(c) 1995-1997 Sangoma Technologies Inc.&n;*&n;*&t;&t;This program is free software; you can redistribute it and/or&n;*&t;&t;modify it under the terms of the GNU General Public License&n;*&t;&t;as published by the Free Software Foundation; either version&n;*&t;&t;2 of the License, or (at your option) any later version.&n;* ============================================================================&n;* Jun 29, 1997&t;Alan Cox&t;Merged with 1.0.3 vendor code&n;* Jan 29, 1997&t;Gene Kozin&t;v1.0.1. Implemented /proc read routines&n;* Jan 30, 1997&t;Alan Cox&t;Hacked around for 2.1&n;* Dec 13, 1996&t;Gene Kozin&t;Initial version (based on Sangoma&squot;s WANPIPE)&n;*****************************************************************************/
macro_line|#include &lt;linux/stddef.h&gt;&t;/* offsetof(), etc. */
macro_line|#include &lt;linux/errno.h&gt;&t;/* return codes */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;&t;/* kmalloc(), kfree() */
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* verify_area(), etc. */
macro_line|#include &lt;linux/string.h&gt;&t;/* inline mem*, str* functions */
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* __initfunc et al. */
macro_line|#include &lt;asm/segment.h&gt;&t;/* kernel &lt;-&gt; user copy */
macro_line|#include &lt;asm/byteorder.h&gt;&t;/* htons(), etc. */
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy_to_user */
macro_line|#include &lt;linux/wanrouter.h&gt;&t;/* WAN router API definitions */
multiline_comment|/****** Defines and Macros **************************************************/
macro_line|#ifndef&t;min
DECL|macro|min
mdefine_line|#define min(a,b) (((a)&lt;(b))?(a):(b))
macro_line|#endif
macro_line|#ifndef&t;max
DECL|macro|max
mdefine_line|#define max(a,b) (((a)&gt;(b))?(a):(b))
macro_line|#endif
DECL|macro|PROC_BUFSZ
mdefine_line|#define&t;PROC_BUFSZ&t;4000&t;/* buffer size for printing proc info */
multiline_comment|/****** Data Types **********************************************************/
DECL|struct|wan_stat_entry
r_typedef
r_struct
id|wan_stat_entry
(brace
DECL|member|next
r_struct
id|wan_stat_entry
op_star
id|next
suffix:semicolon
DECL|member|description
r_char
op_star
id|description
suffix:semicolon
multiline_comment|/* description string */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* -&gt; data */
DECL|member|data_type
r_int
id|data_type
suffix:semicolon
multiline_comment|/* data type */
DECL|typedef|wan_stat_entry_t
)brace
id|wan_stat_entry_t
suffix:semicolon
multiline_comment|/****** Function Prototypes *************************************************/
multiline_comment|/* Proc filesystem interface */
r_static
r_int
id|router_proc_perms
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_static
id|ssize_t
id|router_proc_read
c_func
(paren
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
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
multiline_comment|/* Methods for preparing data for reading proc entries */
r_static
r_int
id|config_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
suffix:semicolon
r_static
r_int
id|status_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
suffix:semicolon
r_static
r_int
id|wandev_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
suffix:semicolon
multiline_comment|/* Miscellaneous */
multiline_comment|/*&n; *&t;Global Data&n; */
multiline_comment|/*&n; *&t;Names of the proc directory entries &n; */
DECL|variable|name_root
r_static
r_char
id|name_root
(braket
)braket
op_assign
id|ROUTER_NAME
suffix:semicolon
DECL|variable|name_conf
r_static
r_char
id|name_conf
(braket
)braket
op_assign
l_string|&quot;config&quot;
suffix:semicolon
DECL|variable|name_stat
r_static
r_char
id|name_stat
(braket
)braket
op_assign
l_string|&quot;status&quot;
suffix:semicolon
multiline_comment|/*&n; *&t;Structures for interfacing with the /proc filesystem.&n; *&t;Router creates its own directory /proc/net/router with the folowing&n; *&t;entries:&n; *&t;config&t;&t;device configuration&n; *&t;status&t;&t;global device statistics&n; *&t;&lt;device&gt;&t;entry for each WAN device&n; */
multiline_comment|/*&n; *&t;Generic /proc/net/router/&lt;file&gt; file and inode operations &n; */
DECL|variable|router_fops
r_static
r_struct
id|file_operations
id|router_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek   */
id|router_proc_read
comma
multiline_comment|/* read&t;   */
l_int|NULL
comma
multiline_comment|/* write   */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select  */
l_int|NULL
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|router_inode
r_static
r_struct
id|inode_operations
id|router_inode
op_assign
(brace
op_amp
id|router_fops
comma
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
id|router_proc_perms
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;/proc/net/router/&lt;device&gt; file and inode operations&n; */
DECL|variable|wandev_fops
r_static
r_struct
id|file_operations
id|wandev_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek   */
id|router_proc_read
comma
multiline_comment|/* read&t;   */
l_int|NULL
comma
multiline_comment|/* write   */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select  */
id|wanrouter_ioctl
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|wandev_inode
r_static
r_struct
id|inode_operations
id|wandev_inode
op_assign
(brace
op_amp
id|wandev_fops
comma
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
id|router_proc_perms
)brace
suffix:semicolon
multiline_comment|/*&n; * Proc filesystem derectory entries.&n; */
multiline_comment|/*&n; *&t;/proc/net/router &n; */
DECL|variable|proc_router
r_static
r_struct
id|proc_dir_entry
id|proc_router
op_assign
(brace
l_int|0
comma
multiline_comment|/* .low_ino */
r_sizeof
(paren
id|name_root
)paren
op_minus
l_int|1
comma
multiline_comment|/* .namelen */
id|name_root
comma
multiline_comment|/* .name */
l_int|0555
op_or
id|S_IFDIR
comma
multiline_comment|/* .mode */
l_int|2
comma
multiline_comment|/* .nlink */
l_int|0
comma
multiline_comment|/* .uid */
l_int|0
comma
multiline_comment|/* .gid */
l_int|0
comma
multiline_comment|/* .size */
op_amp
id|proc_dir_inode_operations
comma
multiline_comment|/* .ops */
l_int|NULL
comma
multiline_comment|/* .get_info */
l_int|NULL
comma
multiline_comment|/* .fill_node */
l_int|NULL
comma
multiline_comment|/* .next */
l_int|NULL
comma
multiline_comment|/* .parent */
l_int|NULL
comma
multiline_comment|/* .subdir */
l_int|NULL
comma
multiline_comment|/* .data */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;/proc/net/router/config &n; */
DECL|variable|proc_router_conf
r_static
r_struct
id|proc_dir_entry
id|proc_router_conf
op_assign
(brace
l_int|0
comma
multiline_comment|/* .low_ino */
r_sizeof
(paren
id|name_conf
)paren
op_minus
l_int|1
comma
multiline_comment|/* .namelen */
id|name_conf
comma
multiline_comment|/* .name */
l_int|0444
op_or
id|S_IFREG
comma
multiline_comment|/* .mode */
l_int|1
comma
multiline_comment|/* .nlink */
l_int|0
comma
multiline_comment|/* .uid */
l_int|0
comma
multiline_comment|/* .gid */
l_int|0
comma
multiline_comment|/* .size */
op_amp
id|router_inode
comma
multiline_comment|/* .ops */
op_amp
id|config_get_info
comma
multiline_comment|/* .get_info */
l_int|NULL
comma
multiline_comment|/* .fill_node */
l_int|NULL
comma
multiline_comment|/* .next */
l_int|NULL
comma
multiline_comment|/* .parent */
l_int|NULL
comma
multiline_comment|/* .subdir */
l_int|NULL
comma
multiline_comment|/* .data */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;/proc/net/router/status &n; */
DECL|variable|proc_router_stat
r_static
r_struct
id|proc_dir_entry
id|proc_router_stat
op_assign
(brace
l_int|0
comma
multiline_comment|/* .low_ino */
r_sizeof
(paren
id|name_stat
)paren
op_minus
l_int|1
comma
multiline_comment|/* .namelen */
id|name_stat
comma
multiline_comment|/* .name */
l_int|0444
op_or
id|S_IFREG
comma
multiline_comment|/* .mode */
l_int|1
comma
multiline_comment|/* .nlink */
l_int|0
comma
multiline_comment|/* .uid */
l_int|0
comma
multiline_comment|/* .gid */
l_int|0
comma
multiline_comment|/* .size */
op_amp
id|router_inode
comma
multiline_comment|/* .ops */
id|status_get_info
comma
multiline_comment|/* .get_info */
l_int|NULL
comma
multiline_comment|/* .fill_node */
l_int|NULL
comma
multiline_comment|/* .next */
l_int|NULL
comma
multiline_comment|/* .parent */
l_int|NULL
comma
multiline_comment|/* .subdir */
l_int|NULL
comma
multiline_comment|/* .data */
)brace
suffix:semicolon
multiline_comment|/* Strings */
DECL|variable|conf_hdr
r_static
r_char
id|conf_hdr
(braket
)braket
op_assign
l_string|&quot;Device name    | port |IRQ|DMA|mem.addr|mem.size|&quot;
l_string|&quot;option1|option2|option3|option4&bslash;n&quot;
suffix:semicolon
DECL|variable|stat_hdr
r_static
r_char
id|stat_hdr
(braket
)braket
op_assign
l_string|&quot;Device name    |station|interface|clocking|baud rate| MTU |ndev&quot;
l_string|&quot;|link state&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n; *&t;Interface functions&n; */
multiline_comment|/*&n; *&t;Initialize router proc interface.&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|wanrouter_proc_init
(paren
r_void
)paren
)paren
(brace
r_int
id|err
op_assign
id|proc_register
c_func
(paren
id|proc_net
comma
op_amp
id|proc_router
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
id|proc_register
c_func
(paren
op_amp
id|proc_router
comma
op_amp
id|proc_router_conf
)paren
suffix:semicolon
id|proc_register
c_func
(paren
op_amp
id|proc_router
comma
op_amp
id|proc_router_stat
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Clean up router proc interface.&n; */
DECL|function|wanrouter_proc_cleanup
r_void
id|wanrouter_proc_cleanup
(paren
r_void
)paren
(brace
id|proc_unregister
c_func
(paren
op_amp
id|proc_router
comma
id|proc_router_conf.low_ino
)paren
suffix:semicolon
id|proc_unregister
c_func
(paren
op_amp
id|proc_router
comma
id|proc_router_stat.low_ino
)paren
suffix:semicolon
id|proc_unregister
c_func
(paren
id|proc_net
comma
id|proc_router.low_ino
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Add directory entry for WAN device.&n; */
DECL|function|wanrouter_proc_add
r_int
id|wanrouter_proc_add
(paren
id|wan_device_t
op_star
id|wandev
)paren
(brace
r_if
c_cond
(paren
id|wandev-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|wandev-&gt;dent
comma
l_int|0
comma
r_sizeof
(paren
id|wandev-&gt;dent
)paren
)paren
suffix:semicolon
id|wandev-&gt;dent.namelen
op_assign
id|strlen
c_func
(paren
id|wandev-&gt;name
)paren
suffix:semicolon
id|wandev-&gt;dent.name
op_assign
id|wandev-&gt;name
suffix:semicolon
id|wandev-&gt;dent.mode
op_assign
l_int|0444
op_or
id|S_IFREG
suffix:semicolon
id|wandev-&gt;dent.nlink
op_assign
l_int|1
suffix:semicolon
id|wandev-&gt;dent.ops
op_assign
op_amp
id|wandev_inode
suffix:semicolon
id|wandev-&gt;dent.get_info
op_assign
op_amp
id|wandev_get_info
suffix:semicolon
id|wandev-&gt;dent.data
op_assign
id|wandev
suffix:semicolon
r_return
id|proc_register
c_func
(paren
op_amp
id|proc_router
comma
op_amp
id|wandev-&gt;dent
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Delete directory entry for WAN device.&n; */
DECL|function|wanrouter_proc_delete
r_int
id|wanrouter_proc_delete
c_func
(paren
id|wan_device_t
op_star
id|wandev
)paren
(brace
r_if
c_cond
(paren
id|wandev-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|proc_unregister
c_func
(paren
op_amp
id|proc_router
comma
id|wandev-&gt;dent.low_ino
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****** Proc filesystem entry points ****************************************/
multiline_comment|/*&n; *&t;Verify access rights.&n; */
DECL|function|router_proc_perms
r_static
r_int
id|router_proc_perms
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|op
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Read router proc directory entry.&n; *&t;This is universal routine for reading all entries in /proc/net/router&n; *&t;directory.  Each directory entry contains a pointer to the &squot;method&squot; for&n; *&t;preparing data for that entry.&n; *&t;o verify arguments&n; *&t;o allocate kernel buffer&n; *&t;o call get_info() to prepare data&n; *&t;o copy data to user space&n; *&t;o release kernel buffer&n; *&n; *&t;Return:&t;number of bytes copied to user space (0, if no data)&n; *&t;&t;&lt;0&t;error&n; */
DECL|function|router_proc_read
r_static
id|ssize_t
id|router_proc_read
c_func
(paren
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
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dent
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_int
id|pos
comma
id|offs
comma
id|len
suffix:semicolon
r_if
c_cond
(paren
id|count
op_le
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|dent
op_assign
id|inode-&gt;u.generic_ip
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dent
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|dent-&gt;get_info
op_eq
l_int|NULL
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_assign
id|kmalloc
c_func
(paren
id|PROC_BUFSZ
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOBUFS
suffix:semicolon
id|pos
op_assign
id|dent
op_member_access_from_pointer
id|get_info
c_func
(paren
id|page
comma
id|dent-&gt;data
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|offs
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|offs
OL
id|pos
)paren
(brace
id|len
op_assign
id|min
c_func
(paren
id|pos
op_minus
id|offs
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
(paren
id|page
op_plus
id|offs
)paren
comma
id|len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|file-&gt;f_pos
op_add_assign
id|len
suffix:semicolon
)brace
r_else
id|len
op_assign
l_int|0
suffix:semicolon
id|kfree
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Prepare data for reading &squot;Config&squot; entry.&n; *&t;Return length of data.&n; */
DECL|function|config_get_info
r_static
r_int
id|config_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
(brace
r_int
id|cnt
op_assign
r_sizeof
(paren
id|conf_hdr
)paren
op_minus
l_int|1
suffix:semicolon
id|wan_device_t
op_star
id|wandev
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
id|conf_hdr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|wandev
op_assign
id|router_devlist
suffix:semicolon
id|wandev
op_logical_and
(paren
id|cnt
OL
(paren
id|PROC_BUFSZ
op_minus
l_int|80
)paren
)paren
suffix:semicolon
id|wandev
op_assign
id|wandev-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|wandev-&gt;state
)paren
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-15s|0x%-4X|%3u|%3u|0x%-6lX|0x%-6X|%7u|%7u|%7u|%7u&bslash;n&quot;
comma
id|wandev-&gt;name
comma
id|wandev-&gt;ioport
comma
id|wandev-&gt;irq
comma
id|wandev-&gt;dma
comma
id|wandev-&gt;maddr
comma
id|wandev-&gt;msize
comma
id|wandev-&gt;hw_opt
(braket
l_int|0
)braket
comma
id|wandev-&gt;hw_opt
(braket
l_int|1
)braket
comma
id|wandev-&gt;hw_opt
(braket
l_int|2
)braket
comma
id|wandev-&gt;hw_opt
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
r_return
id|cnt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Prepare data for reading &squot;Status&squot; entry.&n; *&t;Return length of data.&n; */
DECL|function|status_get_info
r_static
r_int
id|status_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
(brace
r_int
id|cnt
op_assign
r_sizeof
(paren
id|stat_hdr
)paren
op_minus
l_int|1
suffix:semicolon
id|wan_device_t
op_star
id|wandev
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
id|stat_hdr
)paren
suffix:semicolon
r_for
c_loop
(paren
id|wandev
op_assign
id|router_devlist
suffix:semicolon
id|wandev
op_logical_and
(paren
id|cnt
OL
(paren
id|PROC_BUFSZ
op_minus
l_int|80
)paren
)paren
suffix:semicolon
id|wandev
op_assign
id|wandev-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|wandev-&gt;state
)paren
r_continue
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-15s|%-7s|%-9s|%-8s|%9u|%5u|%3u |&quot;
comma
id|wandev-&gt;name
comma
id|wandev-&gt;station
ques
c_cond
l_string|&quot; DCE&quot;
suffix:colon
l_string|&quot; DTE&quot;
comma
id|wandev-&gt;interface
ques
c_cond
l_string|&quot; V.35&quot;
suffix:colon
l_string|&quot; RS-232&quot;
comma
id|wandev-&gt;clocking
ques
c_cond
l_string|&quot;internal&quot;
suffix:colon
l_string|&quot;external&quot;
comma
id|wandev-&gt;bps
comma
id|wandev-&gt;mtu
comma
id|wandev-&gt;ndev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|wandev-&gt;state
)paren
(brace
r_case
id|WAN_UNCONFIGURED
suffix:colon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-12s&bslash;n&quot;
comma
l_string|&quot;unconfigured&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAN_DISCONNECTED
suffix:colon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-12s&bslash;n&quot;
comma
l_string|&quot;disconnected&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAN_CONNECTING
suffix:colon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-12s&bslash;n&quot;
comma
l_string|&quot;connecting&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WAN_CONNECTED
suffix:colon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-12s&bslash;n&quot;
comma
l_string|&quot;connected&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%-12s&bslash;n&quot;
comma
l_string|&quot;invalid&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|cnt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Prepare data for reading &lt;device&gt; entry.&n; *&t;Return length of data.&n; *&n; *&t;On entry, the &squot;start&squot; argument will contain a pointer to WAN device&n; *&t;data space.&n; */
DECL|function|wandev_get_info
r_static
r_int
id|wandev_get_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offs
comma
r_int
id|len
comma
r_int
id|dummy
)paren
(brace
id|wan_device_t
op_star
id|wandev
op_assign
(paren
r_void
op_star
)paren
id|start
suffix:semicolon
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|wandev
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|wandev-&gt;magic
op_ne
id|ROUTER_MAGIC
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wandev-&gt;state
)paren
r_return
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;device is not configured!&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Update device statistics */
r_if
c_cond
(paren
id|wandev-&gt;update
)paren
id|wandev
op_member_access_from_pointer
id|update
c_func
(paren
id|wandev
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;total frames received&quot;
comma
id|wandev-&gt;stats.rx_packets
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;receiver overrun errors&quot;
comma
id|wandev-&gt;stats.rx_over_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;CRC errors&quot;
comma
id|wandev-&gt;stats.rx_crc_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;frame length errors&quot;
comma
id|wandev-&gt;stats.rx_length_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;frame format errors&quot;
comma
id|wandev-&gt;stats.rx_frame_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;aborted frames received&quot;
comma
id|wandev-&gt;stats.rx_missed_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;reveived frames dropped&quot;
comma
id|wandev-&gt;stats.rx_dropped
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;other receive errors&quot;
comma
id|wandev-&gt;stats.rx_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;&bslash;n%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;total frames transmitted&quot;
comma
id|wandev-&gt;stats.tx_packets
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;aborted frames transmitted&quot;
comma
id|wandev-&gt;stats.tx_aborted_errors
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;transmit frames dropped&quot;
comma
id|wandev-&gt;stats.tx_dropped
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;transmit collisions&quot;
comma
id|wandev-&gt;stats.collisions
)paren
suffix:semicolon
id|cnt
op_add_assign
id|sprintf
c_func
(paren
op_amp
id|buf
(braket
id|cnt
)braket
comma
l_string|&quot;%30s: %12lu&bslash;n&quot;
comma
l_string|&quot;other transmit errors&quot;
comma
id|wandev-&gt;stats.tx_errors
)paren
suffix:semicolon
r_return
id|cnt
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;End&n; */
eof
