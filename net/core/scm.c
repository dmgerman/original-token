multiline_comment|/* scm.c - Socket level control messages processing.&n; *&n; * Author:&t;Alexey Kuznetsov, &lt;kuznet@ms2.inr.ac.ru&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/ip.h&gt;
macro_line|#include &lt;net/protocol.h&gt;
macro_line|#include &lt;net/rarp.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/udp.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/scm.h&gt;
multiline_comment|/*&n; *&t;Only allow a user to send credentials, that they could set with &n; *&t;setu(g)id.&n; */
DECL|function|scm_check_creds
r_static
id|__inline__
r_int
id|scm_check_creds
c_func
(paren
r_struct
id|ucred
op_star
id|creds
)paren
(brace
r_if
c_cond
(paren
id|suser
c_func
(paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|creds-&gt;pid
op_ne
id|current-&gt;pid
op_logical_or
(paren
id|creds-&gt;uid
op_ne
id|current-&gt;uid
op_logical_and
id|creds-&gt;uid
op_ne
id|current-&gt;euid
op_logical_and
id|creds-&gt;uid
op_ne
id|current-&gt;suid
)paren
op_logical_or
(paren
id|creds-&gt;gid
op_ne
id|current-&gt;gid
op_logical_and
id|creds-&gt;gid
op_ne
id|current-&gt;egid
op_logical_and
id|creds-&gt;gid
op_ne
id|current-&gt;sgid
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|scm_fp_copy
r_static
r_int
id|scm_fp_copy
c_func
(paren
r_struct
id|cmsghdr
op_star
id|cmsg
comma
r_struct
id|scm_fp_list
op_star
op_star
id|fplp
)paren
(brace
r_int
id|num
suffix:semicolon
r_struct
id|scm_fp_list
op_star
id|fpl
op_assign
op_star
id|fplp
suffix:semicolon
r_struct
id|file
op_star
op_star
id|fpp
op_assign
op_amp
id|fpl-&gt;fp
(braket
id|fpl-&gt;count
)braket
suffix:semicolon
r_int
op_star
id|fdp
op_assign
(paren
r_int
op_star
)paren
id|cmsg-&gt;cmsg_data
suffix:semicolon
r_int
id|i
suffix:semicolon
id|num
op_assign
(paren
id|cmsg-&gt;cmsg_len
op_minus
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|num
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|num
OG
id|SCM_MAX_FD
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpl
)paren
(brace
id|fpl
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|scm_fp_list
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpl
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
op_star
id|fplp
op_assign
id|fpl
suffix:semicolon
id|fpl-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fpl-&gt;count
op_plus
id|num
OG
id|SCM_MAX_FD
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Verify the descriptors.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|fd
suffix:semicolon
id|fd
op_assign
id|fdp
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
op_logical_or
id|fd
op_ge
id|NR_OPEN
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|fpp
(braket
id|i
)braket
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
)brace
multiline_comment|/* add another reference to these files */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|num
suffix:semicolon
id|i
op_increment
comma
id|fpp
op_increment
)paren
(paren
op_star
id|fpp
)paren
op_member_access_from_pointer
id|f_count
op_increment
suffix:semicolon
id|fpl-&gt;count
op_add_assign
id|num
suffix:semicolon
r_return
id|num
suffix:semicolon
)brace
DECL|function|__scm_destroy
r_void
id|__scm_destroy
c_func
(paren
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|scm_fp_list
op_star
id|fpl
op_assign
id|scm-&gt;fp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpl
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|fpl-&gt;count
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|close_fp
c_func
(paren
id|fpl-&gt;fp
(braket
id|i
)braket
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fpl
)paren
suffix:semicolon
)brace
DECL|function|not_one_bit
r_extern
id|__inline__
r_int
id|not_one_bit
c_func
(paren
r_int
id|val
)paren
(brace
r_return
(paren
id|val
op_minus
l_int|1
)paren
op_amp
id|val
suffix:semicolon
)brace
DECL|function|__scm_send
r_int
id|__scm_send
c_func
(paren
r_struct
id|socket
op_star
id|sock
comma
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|p
)paren
(brace
r_int
id|err
suffix:semicolon
r_struct
id|cmsghdr
id|kcm
comma
op_star
id|cmsg
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_int
id|acc_fd
suffix:semicolon
r_int
id|scm_flags
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|cmsg
op_assign
id|KCMSG_FIRSTHDR
c_func
(paren
id|msg
)paren
suffix:semicolon
id|cmsg
suffix:semicolon
id|cmsg
op_assign
id|KCMSG_NXTHDR
c_func
(paren
id|msg
comma
id|cmsg
)paren
)paren
(brace
r_if
c_cond
(paren
id|kcm.cmsg_level
op_ne
id|SOL_SOCKET
)paren
r_continue
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Temporary hack: no protocols except for AF_UNIX&n;&t;&t; *&t;undestand scm now.&n;&t;&t; */
r_if
c_cond
(paren
id|sock-&gt;ops-&gt;family
op_ne
id|AF_UNIX
)paren
r_goto
id|error
suffix:semicolon
r_switch
c_cond
(paren
id|kcm.cmsg_type
)paren
(brace
r_case
id|SCM_RIGHTS
suffix:colon
id|err
op_assign
id|scm_fp_copy
c_func
(paren
id|cmsg
comma
op_amp
id|p-&gt;fp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_goto
id|error
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCM_CREDENTIALS
suffix:colon
r_if
c_cond
(paren
id|kcm.cmsg_len
OL
r_sizeof
(paren
id|kcm
)paren
op_plus
r_sizeof
(paren
r_struct
id|ucred
)paren
)paren
r_goto
id|error
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|p-&gt;creds
comma
id|cmsg-&gt;cmsg_data
comma
r_sizeof
(paren
r_struct
id|ucred
)paren
)paren
suffix:semicolon
id|err
op_assign
id|scm_check_creds
c_func
(paren
op_amp
id|p-&gt;creds
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|error
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCM_CONNECT
suffix:colon
r_if
c_cond
(paren
id|scm_flags
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
id|kcm.cmsg_len
OL
r_sizeof
(paren
id|kcm
)paren
op_plus
r_sizeof
(paren
r_int
)paren
)paren
r_goto
id|error
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|acc_fd
comma
id|cmsg-&gt;cmsg_data
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|p-&gt;sock
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|acc_fd
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|acc_fd
OL
l_int|0
op_logical_or
id|acc_fd
op_ge
id|NR_OPEN
op_logical_or
(paren
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|acc_fd
)braket
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file-&gt;f_inode
op_logical_or
op_logical_neg
id|file-&gt;f_inode-&gt;i_sock
)paren
r_return
op_minus
id|ENOTSOCK
suffix:semicolon
id|p-&gt;sock
op_assign
op_amp
id|file-&gt;f_inode-&gt;u.socket_i
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;sock-&gt;state
op_ne
id|SS_UNCONNECTED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|scm_flags
op_or_assign
id|MSG_SYN
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|error
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|p-&gt;fp
op_logical_and
op_logical_neg
id|p-&gt;fp-&gt;count
)paren
(brace
id|kfree
c_func
(paren
id|p-&gt;fp
)paren
suffix:semicolon
id|p-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|msg-&gt;msg_flags
op_or_assign
id|scm_flags
suffix:semicolon
id|scm_flags
op_assign
id|msg-&gt;msg_flags
op_amp
id|MSG_CTLFLAGS
suffix:semicolon
r_if
c_cond
(paren
id|not_one_bit
c_func
(paren
id|scm_flags
)paren
)paren
r_goto
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|scm_flags
op_logical_and
id|p-&gt;fp
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|error
suffix:colon
id|scm_destroy
c_func
(paren
id|p
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|put_cmsg
r_void
id|put_cmsg
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_int
id|level
comma
r_int
id|type
comma
r_int
id|len
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|cmsghdr
op_star
id|cm
op_assign
(paren
r_struct
id|cmsghdr
op_star
)paren
id|msg-&gt;msg_control
suffix:semicolon
r_int
id|cmlen
op_assign
r_sizeof
(paren
op_star
id|cm
)paren
op_plus
id|len
suffix:semicolon
r_if
c_cond
(paren
id|cm
op_eq
l_int|NULL
op_logical_or
id|msg-&gt;msg_controllen
OL
r_sizeof
(paren
op_star
id|cm
)paren
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|msg-&gt;msg_controllen
OL
id|cmlen
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
id|cmlen
op_assign
id|msg-&gt;msg_controllen
suffix:semicolon
)brace
id|cm-&gt;cmsg_level
op_assign
id|level
suffix:semicolon
id|cm-&gt;cmsg_type
op_assign
id|type
suffix:semicolon
id|cm-&gt;cmsg_len
op_assign
id|cmlen
suffix:semicolon
id|memcpy
c_func
(paren
id|cm-&gt;cmsg_data
comma
id|data
comma
id|cmlen
op_minus
r_sizeof
(paren
op_star
id|cm
)paren
)paren
suffix:semicolon
id|cmlen
op_assign
id|CMSG_ALIGN
c_func
(paren
id|cmlen
)paren
suffix:semicolon
id|msg-&gt;msg_control
op_add_assign
id|cmlen
suffix:semicolon
id|msg-&gt;msg_controllen
op_sub_assign
id|cmlen
suffix:semicolon
)brace
DECL|function|scm_detach_fds
r_void
id|scm_detach_fds
c_func
(paren
r_struct
id|msghdr
op_star
id|msg
comma
r_struct
id|scm_cookie
op_star
id|scm
)paren
(brace
r_struct
id|cmsghdr
op_star
id|cm
op_assign
(paren
r_struct
id|cmsghdr
op_star
)paren
id|msg-&gt;msg_control
suffix:semicolon
r_int
id|fdmax
op_assign
(paren
id|msg-&gt;msg_controllen
op_minus
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
)paren
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_int
id|fdnum
op_assign
id|scm-&gt;fp-&gt;count
suffix:semicolon
r_int
op_star
id|cmfptr
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|file
op_star
op_star
id|fp
op_assign
id|scm-&gt;fp-&gt;fp
suffix:semicolon
r_if
c_cond
(paren
id|fdnum
OG
id|fdmax
)paren
id|fdmax
op_assign
id|fdnum
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|cmfptr
op_assign
(paren
r_int
op_star
)paren
id|cm-&gt;cmsg_data
suffix:semicolon
id|i
OL
id|fdmax
suffix:semicolon
id|i
op_increment
comma
id|cmfptr
op_increment
)paren
(brace
r_int
id|new_fd
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_fd
OL
l_int|0
)paren
r_break
suffix:semicolon
id|current-&gt;files-&gt;fd
(braket
id|new_fd
)braket
op_assign
id|fp
(braket
id|i
)braket
suffix:semicolon
op_star
id|cmfptr
op_assign
id|new_fd
suffix:semicolon
id|cmfptr
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
OG
l_int|0
)paren
(brace
r_int
id|cmlen
op_assign
id|i
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
r_struct
id|cmsghdr
)paren
suffix:semicolon
id|cm-&gt;cmsg_level
op_assign
id|SOL_SOCKET
suffix:semicolon
id|cm-&gt;cmsg_type
op_assign
id|SCM_RIGHTS
suffix:semicolon
id|cm-&gt;cmsg_len
op_assign
id|cmlen
suffix:semicolon
id|cmlen
op_assign
id|CMSG_ALIGN
c_func
(paren
id|cmlen
)paren
suffix:semicolon
id|msg-&gt;msg_control
op_add_assign
id|cmlen
suffix:semicolon
id|msg-&gt;msg_controllen
op_sub_assign
id|cmlen
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Dump those that don&squot;t fit.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
id|fdnum
suffix:semicolon
id|i
op_increment
)paren
(brace
id|msg-&gt;msg_flags
op_or_assign
id|MSG_CTRUNC
suffix:semicolon
id|close_fp
c_func
(paren
id|fp
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|kfree
(paren
id|scm-&gt;fp
)paren
suffix:semicolon
id|scm-&gt;fp
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|scm_fp_dup
r_struct
id|scm_fp_list
op_star
id|scm_fp_dup
c_func
(paren
r_struct
id|scm_fp_list
op_star
id|fpl
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|scm_fp_list
op_star
id|new_fpl
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpl
)paren
r_return
l_int|NULL
suffix:semicolon
id|new_fpl
op_assign
id|kmalloc
c_func
(paren
id|fpl-&gt;count
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
op_star
id|fpl
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|new_fpl
)paren
r_return
l_int|NULL
suffix:semicolon
id|memcpy
c_func
(paren
id|new_fpl
comma
id|fpl
comma
id|fpl-&gt;count
op_star
r_sizeof
(paren
r_int
)paren
op_plus
r_sizeof
(paren
op_star
id|fpl
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|fpl-&gt;count
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
id|fpl-&gt;fp
(braket
id|i
)braket
op_member_access_from_pointer
id|f_count
op_increment
suffix:semicolon
r_return
id|new_fpl
suffix:semicolon
)brace
eof
