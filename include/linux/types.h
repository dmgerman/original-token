macro_line|#ifndef _LINUX_TYPES_H
DECL|macro|_LINUX_TYPES_H
mdefine_line|#define _LINUX_TYPES_H
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef _SIZE_T
DECL|macro|_SIZE_T
mdefine_line|#define _SIZE_T
DECL|typedef|size_t
r_typedef
r_int
r_int
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _SSIZE_T
DECL|macro|_SSIZE_T
mdefine_line|#define _SSIZE_T
DECL|typedef|ssize_t
r_typedef
r_int
id|ssize_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _TIME_T
DECL|macro|_TIME_T
mdefine_line|#define _TIME_T
DECL|typedef|time_t
r_typedef
r_int
id|time_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _CLOCK_T
DECL|macro|_CLOCK_T
mdefine_line|#define _CLOCK_T
DECL|typedef|clock_t
r_typedef
r_int
id|clock_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _PTRDIFF_T
DECL|macro|_PTRDIFF_T
mdefine_line|#define _PTRDIFF_T
DECL|typedef|ptrdiff_t
r_typedef
r_int
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
DECL|typedef|pid_t
r_typedef
r_int
id|pid_t
suffix:semicolon
DECL|typedef|uid_t
r_typedef
r_int
r_int
id|uid_t
suffix:semicolon
DECL|typedef|gid_t
r_typedef
r_int
r_int
id|gid_t
suffix:semicolon
DECL|typedef|dev_t
r_typedef
r_int
r_int
id|dev_t
suffix:semicolon
DECL|typedef|ino_t
r_typedef
r_int
r_int
id|ino_t
suffix:semicolon
DECL|typedef|mode_t
r_typedef
r_int
r_int
id|mode_t
suffix:semicolon
DECL|typedef|umode_t
r_typedef
r_int
r_int
id|umode_t
suffix:semicolon
DECL|typedef|nlink_t
r_typedef
r_int
r_int
id|nlink_t
suffix:semicolon
DECL|typedef|daddr_t
r_typedef
r_int
id|daddr_t
suffix:semicolon
DECL|typedef|off_t
r_typedef
r_int
id|off_t
suffix:semicolon
macro_line|#ifndef __STRICT_ANSI__
DECL|macro|_LOFF_T
mdefine_line|#define _LOFF_T
DECL|typedef|loff_t
r_typedef
r_int
r_int
id|loff_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* bsd */
DECL|typedef|u_char
r_typedef
r_int
r_char
id|u_char
suffix:semicolon
DECL|typedef|u_short
r_typedef
r_int
r_int
id|u_short
suffix:semicolon
DECL|typedef|u_int
r_typedef
r_int
r_int
id|u_int
suffix:semicolon
DECL|typedef|u_long
r_typedef
r_int
r_int
id|u_long
suffix:semicolon
multiline_comment|/* sysv */
DECL|typedef|unchar
r_typedef
r_int
r_char
id|unchar
suffix:semicolon
DECL|typedef|ushort
r_typedef
r_int
r_int
id|ushort
suffix:semicolon
DECL|typedef|uint
r_typedef
r_int
r_int
id|uint
suffix:semicolon
DECL|typedef|ulong
r_typedef
r_int
r_int
id|ulong
suffix:semicolon
DECL|typedef|caddr_t
r_typedef
r_char
op_star
id|caddr_t
suffix:semicolon
DECL|typedef|cc_t
r_typedef
r_int
r_char
id|cc_t
suffix:semicolon
DECL|typedef|speed_t
r_typedef
r_int
r_int
id|speed_t
suffix:semicolon
DECL|typedef|tcflag_t
r_typedef
r_int
r_int
id|tcflag_t
suffix:semicolon
multiline_comment|/*&n; * This allows for 256 file descriptors: if NR_OPEN is ever grown beyond that&n; * you&squot;ll have to change this too. But 256 fd&squot;s seem to be enough even for such&n; * &quot;real&quot; unices like SunOS, so hopefully this is one limit that doesn&squot;t have&n; * to be changed.&n; *&n; * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in &lt;sys/time.h&gt;&n; * (and thus &lt;linux/time.h&gt;) - but this is a more logical place for them. Solved&n; * by having dummy defines in &lt;sys/time.h&gt;.&n; */
multiline_comment|/*&n; * Those macros may have been defined in &lt;gnu/types.h&gt;. But we always&n; * use the ones here. &n; */
DECL|macro|__FDSET_LONGS
macro_line|#undef __FDSET_LONGS
DECL|macro|__FDSET_LONGS
mdefine_line|#define __FDSET_LONGS 8
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
DECL|typedef|fd_set
)brace
id|fd_set
suffix:semicolon
DECL|macro|__NFDBITS
macro_line|#undef __NFDBITS
DECL|macro|__NFDBITS
mdefine_line|#define __NFDBITS&t;(8 * sizeof(unsigned long))
DECL|macro|__FD_SETSIZE
macro_line|#undef __FD_SETSIZE
DECL|macro|__FD_SETSIZE
mdefine_line|#define __FD_SETSIZE&t;(__FDSET_LONGS*__NFDBITS)
DECL|macro|__FD_SET
macro_line|#undef&t;__FD_SET
DECL|macro|__FD_SET
mdefine_line|#define __FD_SET(fd,fdsetp) &bslash;&n;&t;&t;__asm__ __volatile__(&quot;btsl %1,%0&quot;: &bslash;&n;&t;&t;&t;&quot;=m&quot; (*(fd_set *) (fdsetp)):&quot;r&quot; ((int) (fd)))
DECL|macro|__FD_CLR
macro_line|#undef&t;__FD_CLR
DECL|macro|__FD_CLR
mdefine_line|#define __FD_CLR(fd,fdsetp) &bslash;&n;&t;&t;__asm__ __volatile__(&quot;btrl %1,%0&quot;: &bslash;&n;&t;&t;&t;&quot;=m&quot; (*(fd_set *) (fdsetp)):&quot;r&quot; ((int) (fd)))
DECL|macro|__FD_ISSET
macro_line|#undef&t;__FD_ISSET
DECL|macro|__FD_ISSET
mdefine_line|#define __FD_ISSET(fd,fdsetp) (__extension__ ({ &bslash;&n;&t;&t;unsigned char __result; &bslash;&n;&t;&t;__asm__ __volatile__(&quot;btl %1,%2 ; setb %0&quot; &bslash;&n;&t;&t;&t;:&quot;=q&quot; (__result) :&quot;r&quot; ((int) (fd)), &bslash;&n;&t;&t;&t;&quot;m&quot; (*(fd_set *) (fdsetp))); &bslash;&n;&t;&t;__result; }))
DECL|macro|__FD_ZERO
macro_line|#undef&t;__FD_ZERO
DECL|macro|__FD_ZERO
mdefine_line|#define __FD_ZERO(fdsetp) &bslash;&n;&t;&t;__asm__ __volatile__(&quot;cld ; rep ; stosl&quot; &bslash;&n;&t;&t;&t;:&quot;=m&quot; (*(fd_set *) (fdsetp)) &bslash;&n;&t;&t;&t;:&quot;a&quot; (0), &quot;c&quot; (__FDSET_LONGS), &bslash;&n;&t;&t;&t;&quot;D&quot; ((fd_set *) (fdsetp)) :&quot;cx&quot;,&quot;di&quot;)
DECL|struct|ustat
r_struct
id|ustat
(brace
DECL|member|f_tfree
id|daddr_t
id|f_tfree
suffix:semicolon
DECL|member|f_tinode
id|ino_t
id|f_tinode
suffix:semicolon
DECL|member|f_fname
r_char
id|f_fname
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|f_fpack
r_char
id|f_fpack
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
