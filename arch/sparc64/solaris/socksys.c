multiline_comment|/* $Id: socksys.c,v 1.11 2000/02/09 22:32:17 davem Exp $&n; * socksys.c: /dev/inet/ stuff for Solaris emulation.&n; *&n; * Copyright (C) 1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; * Copyright (C) 1997, 1998 Patrik Rak (prak3264@ss1000.ms.mff.cuni.cz)&n; * Copyright (C) 1995, 1996 Mike Jagdis (jaggy@purplet.demon.co.uk)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/termios.h&gt;
macro_line|#include &quot;conv.h&quot;
macro_line|#include &quot;socksys.h&quot;
r_extern
id|asmlinkage
r_int
id|sys_ioctl
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|variable|af_inet_protocols
r_static
r_int
id|af_inet_protocols
(braket
)braket
op_assign
(brace
id|IPPROTO_ICMP
comma
id|IPPROTO_ICMP
comma
id|IPPROTO_IGMP
comma
id|IPPROTO_IPIP
comma
id|IPPROTO_TCP
comma
id|IPPROTO_EGP
comma
id|IPPROTO_PUP
comma
id|IPPROTO_UDP
comma
id|IPPROTO_IDP
comma
id|IPPROTO_RAW
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
suffix:semicolon
macro_line|#ifndef DEBUG_SOLARIS_KMALLOC
DECL|macro|mykmalloc
mdefine_line|#define mykmalloc kmalloc
DECL|macro|mykfree
mdefine_line|#define mykfree kfree
macro_line|#else
r_extern
r_void
op_star
id|mykmalloc
c_func
(paren
r_int
id|s
comma
r_int
id|gfp
)paren
suffix:semicolon
r_extern
r_void
id|mykfree
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|sock_poll
r_static
r_int
r_int
(paren
op_star
id|sock_poll
)paren
(paren
r_struct
id|file
op_star
comma
id|poll_table
op_star
)paren
suffix:semicolon
DECL|variable|socksys_file_ops
r_static
r_struct
id|file_operations
id|socksys_file_ops
op_assign
(brace
multiline_comment|/* Currently empty */
)brace
suffix:semicolon
DECL|function|socksys_open
r_static
r_int
id|socksys_open
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
)paren
(brace
r_int
id|family
comma
id|type
comma
id|protocol
comma
id|fd
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
(paren
op_star
id|sys_socket
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
)paren
id|SUNOS
c_func
(paren
l_int|97
)paren
suffix:semicolon
r_struct
id|sol_socket_struct
op_star
id|sock
suffix:semicolon
id|family
op_assign
(paren
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|family
)paren
(brace
r_case
id|AF_UNIX
suffix:colon
id|type
op_assign
id|SOCK_STREAM
suffix:semicolon
id|protocol
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AF_INET
suffix:colon
id|protocol
op_assign
id|af_inet_protocols
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_amp
l_int|0xf
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|protocol
)paren
(brace
r_case
id|IPPROTO_TCP
suffix:colon
id|type
op_assign
id|SOCK_STREAM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|IPPROTO_UDP
suffix:colon
id|type
op_assign
id|SOCK_DGRAM
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|type
op_assign
id|SOCK_RAW
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|type
op_assign
id|SOCK_RAW
suffix:semicolon
id|protocol
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|fd
op_assign
id|sys_socket
c_func
(paren
id|family
comma
id|type
comma
id|protocol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_return
id|fd
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. The following operations are not legal!&n;&t; * Try instead:&n;&t; * d_delete(filp-&gt;f_dentry), then d_instantiate with sock inode&n;&t; */
id|dentry
op_assign
id|filp-&gt;f_dentry
suffix:semicolon
id|filp-&gt;f_dentry
op_assign
id|dget
c_func
(paren
id|fcheck
c_func
(paren
id|fd
)paren
op_member_access_from_pointer
id|f_dentry
)paren
suffix:semicolon
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
id|filp-&gt;f_dentry-&gt;d_inode-&gt;i_flock
op_assign
id|inode-&gt;i_flock
suffix:semicolon
id|filp-&gt;f_dentry-&gt;d_inode-&gt;u.socket_i.file
op_assign
id|filp
suffix:semicolon
id|filp-&gt;f_op
op_assign
op_amp
id|socksys_file_ops
suffix:semicolon
id|sock
op_assign
(paren
r_struct
id|sol_socket_struct
op_star
)paren
id|mykmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sol_socket_struct
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sock
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|SOLDD
c_func
(paren
(paren
l_string|&quot;sock=%016lx(%016lx)&bslash;n&quot;
comma
id|sock
comma
id|filp
)paren
)paren
suffix:semicolon
id|sock-&gt;magic
op_assign
id|SOLARIS_SOCKET_MAGIC
suffix:semicolon
id|sock-&gt;modcount
op_assign
l_int|0
suffix:semicolon
id|sock-&gt;state
op_assign
id|TS_UNBND
suffix:semicolon
id|sock-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|sock-&gt;pfirst
op_assign
id|sock-&gt;plast
op_assign
l_int|NULL
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|sock
suffix:semicolon
id|SOLDD
c_func
(paren
(paren
l_string|&quot;filp-&gt;private_data %016lx&bslash;n&quot;
comma
id|filp-&gt;private_data
)paren
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|socksys_release
r_static
r_int
id|socksys_release
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
)paren
(brace
r_struct
id|sol_socket_struct
op_star
id|sock
suffix:semicolon
r_struct
id|T_primsg
op_star
id|it
suffix:semicolon
multiline_comment|/* XXX: check this */
id|sock
op_assign
(paren
r_struct
id|sol_socket_struct
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
id|SOLDD
c_func
(paren
(paren
l_string|&quot;sock release %016lx(%016lx)&bslash;n&quot;
comma
id|sock
comma
id|filp
)paren
)paren
suffix:semicolon
id|it
op_assign
id|sock-&gt;pfirst
suffix:semicolon
r_while
c_loop
(paren
id|it
)paren
(brace
r_struct
id|T_primsg
op_star
id|next
op_assign
id|it-&gt;next
suffix:semicolon
id|SOLDD
c_func
(paren
(paren
l_string|&quot;socksys_release %016lx-&gt;%016lx&bslash;n&quot;
comma
id|it
comma
id|next
)paren
)paren
suffix:semicolon
id|mykfree
c_func
(paren
(paren
r_char
op_star
)paren
id|it
)paren
suffix:semicolon
id|it
op_assign
id|next
suffix:semicolon
)brace
id|filp-&gt;private_data
op_assign
l_int|NULL
suffix:semicolon
id|SOLDD
c_func
(paren
(paren
l_string|&quot;socksys_release %016lx&bslash;n&quot;
comma
id|sock
)paren
)paren
suffix:semicolon
id|mykfree
c_func
(paren
(paren
r_char
op_star
)paren
id|sock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|socksys_poll
r_static
r_int
r_int
id|socksys_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_struct
id|inode
op_star
id|ino
suffix:semicolon
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
id|filp-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|ino
op_logical_and
id|ino-&gt;i_sock
)paren
(brace
r_struct
id|sol_socket_struct
op_star
id|sock
suffix:semicolon
id|sock
op_assign
(paren
r_struct
id|sol_socket_struct
op_star
)paren
id|filp-&gt;private_data
suffix:semicolon
r_if
c_cond
(paren
id|sock
op_logical_and
id|sock-&gt;pfirst
)paren
(brace
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_if
c_cond
(paren
id|sock-&gt;pfirst-&gt;pri
op_eq
id|MSG_HIPRI
)paren
id|mask
op_or_assign
id|POLLPRI
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sock_poll
)paren
id|mask
op_or_assign
(paren
op_star
id|sock_poll
)paren
(paren
id|filp
comma
id|wait
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|variable|socksys_fops
r_static
r_struct
id|file_operations
id|socksys_fops
op_assign
(brace
id|open
suffix:colon
id|socksys_open
comma
id|release
suffix:colon
id|socksys_release
comma
)brace
suffix:semicolon
r_int
id|__init
DECL|function|init_socksys
id|init_socksys
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
(paren
op_star
id|sys_socket
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
comma
r_int
comma
r_int
)paren
)paren
id|SUNOS
c_func
(paren
l_int|97
)paren
suffix:semicolon
r_int
(paren
op_star
id|sys_close
)paren
(paren
r_int
r_int
)paren
op_assign
(paren
r_int
(paren
op_star
)paren
(paren
r_int
r_int
)paren
)paren
id|SYS
c_func
(paren
id|close
)paren
suffix:semicolon
id|ret
op_assign
id|register_chrdev
(paren
l_int|30
comma
l_string|&quot;socksys&quot;
comma
op_amp
id|socksys_fops
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Couldn&squot;t register socksys character device&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|sys_socket
c_func
(paren
id|AF_INET
comma
id|SOCK_STREAM
comma
id|IPPROTO_TCP
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Couldn&squot;t create socket&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|file
op_assign
id|fcheck
c_func
(paren
id|ret
)paren
suffix:semicolon
multiline_comment|/* N.B. Is this valid? Suppose the f_ops are in a module ... */
id|socksys_file_ops
op_assign
op_star
id|file-&gt;f_op
suffix:semicolon
id|sys_close
c_func
(paren
id|ret
)paren
suffix:semicolon
id|sock_poll
op_assign
id|socksys_file_ops.poll
suffix:semicolon
id|socksys_file_ops.poll
op_assign
id|socksys_poll
suffix:semicolon
id|socksys_file_ops.release
op_assign
id|socksys_release
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cleanup_socksys
id|cleanup_socksys
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|unregister_chrdev
(paren
l_int|30
comma
l_string|&quot;socksys&quot;
)paren
)paren
id|printk
(paren
l_string|&quot;Couldn&squot;t unregister socksys character device&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
