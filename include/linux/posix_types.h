macro_line|#ifndef _LINUX_POSIX_TYPES_H
DECL|macro|_LINUX_POSIX_TYPES_H
mdefine_line|#define _LINUX_POSIX_TYPES_H
multiline_comment|/*&n; * This file is generally used by user-level software, so you need to&n; * be a little careful about namespace pollution etc.  Also, we cannot&n; * assume GCC is being used.&n; */
macro_line|#ifndef NULL
DECL|macro|NULL
macro_line|# define NULL&t;&t;((void *) 0)
macro_line|#endif
multiline_comment|/*&n; * This allows for 1024 file descriptors: if NR_OPEN is ever grown&n; * beyond that you&squot;ll have to change this too. But 1024 fd&squot;s seem to be&n; * enough even for such &quot;real&quot; unices like OSF/1, so hopefully this is&n; * one limit that doesn&squot;t have to be changed [again].&n; *&n; * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in&n; * &lt;sys/time.h&gt; (and thus &lt;linux/time.h&gt;) - but this is a more logical&n; * place for them. Solved by having dummy defines in &lt;sys/time.h&gt;.&n; */
multiline_comment|/*&n; * Those macros may have been defined in &lt;gnu/types.h&gt;. But we always&n; * use the ones here. &n; */
DECL|macro|__NFDBITS
macro_line|#undef __NFDBITS
DECL|macro|__NFDBITS
mdefine_line|#define __NFDBITS&t;(8 * sizeof(unsigned long))
DECL|macro|__FD_SETSIZE
macro_line|#undef __FD_SETSIZE
DECL|macro|__FD_SETSIZE
mdefine_line|#define __FD_SETSIZE&t;1024
DECL|macro|__FDSET_LONGS
macro_line|#undef __FDSET_LONGS
DECL|macro|__FDSET_LONGS
mdefine_line|#define __FDSET_LONGS&t;(__FD_SETSIZE/__NFDBITS)
DECL|macro|__FDELT
macro_line|#undef __FDELT
DECL|macro|__FDELT
mdefine_line|#define&t;__FDELT(d)&t;((d) / __NFDBITS)
DECL|macro|__FDMASK
macro_line|#undef __FDMASK
DECL|macro|__FDMASK
mdefine_line|#define&t;__FDMASK(d)&t;(1UL &lt;&lt; ((d) % __NFDBITS))
DECL|struct|fd_set
r_typedef
r_struct
id|fd_set
(brace
DECL|member|fds_bits
r_int
r_int
id|fds_bits
(braket
id|__FDSET_LONGS
)braket
suffix:semicolon
DECL|typedef|__kernel_fd_set
)brace
id|__kernel_fd_set
suffix:semicolon
macro_line|#include &lt;asm/posix_types.h&gt;
macro_line|#endif /* _LINUX_POSIX_TYPES_H */
eof
