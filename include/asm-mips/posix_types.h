multiline_comment|/*&n; * POSIX types&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ARCH_MIPS_POSIX_TYPES_H
DECL|macro|__ARCH_MIPS_POSIX_TYPES_H
mdefine_line|#define __ARCH_MIPS_POSIX_TYPES_H
DECL|macro|__need_size_t
mdefine_line|#define __need_size_t
DECL|macro|__need_ptrdiff_t
mdefine_line|#define __need_ptrdiff_t
macro_line|#include &lt;stddef.h&gt;
multiline_comment|/*&n; * This file is generally used by user-level software, so you need to&n; * be a little careful about namespace pollution etc.  Also, we cannot&n; * assume GCC is being used.&n; */
DECL|typedef|__kernel_dev_t
r_typedef
r_int
r_int
id|__kernel_dev_t
suffix:semicolon
DECL|typedef|__kernel_ino_t
r_typedef
r_int
r_int
id|__kernel_ino_t
suffix:semicolon
DECL|typedef|__kernel_mode_t
r_typedef
r_int
r_int
id|__kernel_mode_t
suffix:semicolon
DECL|typedef|__kernel_nlink_t
r_typedef
r_int
r_int
id|__kernel_nlink_t
suffix:semicolon
DECL|typedef|__kernel_off_t
r_typedef
r_int
id|__kernel_off_t
suffix:semicolon
DECL|typedef|__kernel_pid_t
r_typedef
r_int
id|__kernel_pid_t
suffix:semicolon
DECL|typedef|__kernel_ipc_pid_t
r_typedef
r_int
id|__kernel_ipc_pid_t
suffix:semicolon
DECL|typedef|__kernel_uid_t
r_typedef
r_int
id|__kernel_uid_t
suffix:semicolon
DECL|typedef|__kernel_gid_t
r_typedef
r_int
id|__kernel_gid_t
suffix:semicolon
DECL|typedef|__kernel_size_t
r_typedef
id|__SIZE_TYPE__
id|__kernel_size_t
suffix:semicolon
DECL|typedef|__kernel_ssize_t
r_typedef
id|__SSIZE_TYPE__
id|__kernel_ssize_t
suffix:semicolon
DECL|typedef|__kernel_ptrdiff_t
r_typedef
r_int
id|__kernel_ptrdiff_t
suffix:semicolon
DECL|typedef|__kernel_time_t
r_typedef
r_int
id|__kernel_time_t
suffix:semicolon
DECL|typedef|__kernel_clock_t
r_typedef
r_int
id|__kernel_clock_t
suffix:semicolon
DECL|typedef|__kernel_daddr_t
r_typedef
r_int
id|__kernel_daddr_t
suffix:semicolon
DECL|typedef|__kernel_caddr_t
r_typedef
r_char
op_star
id|__kernel_caddr_t
suffix:semicolon
multiline_comment|/* typedef unsigned long&t;__kernel_sigset_t;  anybody using this type? */
macro_line|#ifdef __GNUC__
DECL|typedef|__kernel_loff_t
r_typedef
r_int
r_int
id|__kernel_loff_t
suffix:semicolon
macro_line|#endif
r_typedef
r_struct
(brace
DECL|member|val
r_int
id|val
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|__kernel_fsid_t
)brace
id|__kernel_fsid_t
suffix:semicolon
DECL|macro|__FD_SET
macro_line|#undef __FD_SET
DECL|function|__FD_SET
r_static
id|__inline__
r_void
id|__FD_SET
c_func
(paren
r_int
r_int
id|__fd
comma
id|__kernel_fd_set
op_star
id|__fdsetp
)paren
(brace
r_int
r_int
id|__tmp
op_assign
id|__fd
op_div
id|__NFDBITS
suffix:semicolon
r_int
r_int
id|__rem
op_assign
id|__fd
op_mod
id|__NFDBITS
suffix:semicolon
id|__fdsetp-&gt;fds_bits
(braket
id|__tmp
)braket
op_or_assign
(paren
l_int|1UL
op_lshift
id|__rem
)paren
suffix:semicolon
)brace
DECL|macro|__FD_CLR
macro_line|#undef __FD_CLR
DECL|function|__FD_CLR
r_static
id|__inline__
r_void
id|__FD_CLR
c_func
(paren
r_int
r_int
id|__fd
comma
id|__kernel_fd_set
op_star
id|__fdsetp
)paren
(brace
r_int
r_int
id|__tmp
op_assign
id|__fd
op_div
id|__NFDBITS
suffix:semicolon
r_int
r_int
id|__rem
op_assign
id|__fd
op_mod
id|__NFDBITS
suffix:semicolon
id|__fdsetp-&gt;fds_bits
(braket
id|__tmp
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|__rem
)paren
suffix:semicolon
)brace
DECL|macro|__FD_ISSET
macro_line|#undef __FD_ISSET
DECL|function|__FD_ISSET
r_static
id|__inline__
r_int
id|__FD_ISSET
c_func
(paren
r_int
r_int
id|__fd
comma
r_const
id|__kernel_fd_set
op_star
id|__p
)paren
(brace
r_int
r_int
id|__tmp
op_assign
id|__fd
op_div
id|__NFDBITS
suffix:semicolon
r_int
r_int
id|__rem
op_assign
id|__fd
op_mod
id|__NFDBITS
suffix:semicolon
r_return
(paren
id|__p-&gt;fds_bits
(braket
id|__tmp
)braket
op_amp
(paren
l_int|1UL
op_lshift
id|__rem
)paren
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This will unroll the loop for the normal constant case (8 ints,&n; * for a 256-bit fd_set)&n; */
DECL|macro|__FD_ZERO
macro_line|#undef __FD_ZERO
DECL|function|__FD_ZERO
r_static
id|__inline__
r_void
id|__FD_ZERO
c_func
(paren
id|__kernel_fd_set
op_star
id|__p
)paren
(brace
r_int
r_int
op_star
id|__tmp
op_assign
id|__p-&gt;fds_bits
suffix:semicolon
r_int
id|__i
suffix:semicolon
r_if
c_cond
(paren
id|__builtin_constant_p
c_func
(paren
id|__FDSET_LONGS
)paren
)paren
(brace
r_switch
c_cond
(paren
id|__FDSET_LONGS
)paren
(brace
r_case
l_int|16
suffix:colon
id|__tmp
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|8
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|10
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|11
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|12
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|14
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|15
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__tmp
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__tmp
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|__tmp
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|__i
op_assign
id|__FDSET_LONGS
suffix:semicolon
r_while
c_loop
(paren
id|__i
)paren
(brace
id|__i
op_decrement
suffix:semicolon
op_star
id|__tmp
op_assign
l_int|0
suffix:semicolon
id|__tmp
op_increment
suffix:semicolon
)brace
)brace
macro_line|#endif /* __ARCH_MIPS_POSIX_TYPES_H */
eof
