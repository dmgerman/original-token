macro_line|#ifndef _LINUX_TYPES_H
DECL|macro|_LINUX_TYPES_H
mdefine_line|#define _LINUX_TYPES_H
macro_line|#include &lt;linux/posix_types.h&gt;
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef __KERNEL_STRICT_NAMES
DECL|typedef|fd_set
r_typedef
id|__kernel_fd_set
id|fd_set
suffix:semicolon
DECL|typedef|dev_t
r_typedef
id|__kernel_dev_t
id|dev_t
suffix:semicolon
DECL|typedef|ino_t
r_typedef
id|__kernel_ino_t
id|ino_t
suffix:semicolon
DECL|typedef|mode_t
r_typedef
id|__kernel_mode_t
id|mode_t
suffix:semicolon
DECL|typedef|nlink_t
r_typedef
id|__kernel_nlink_t
id|nlink_t
suffix:semicolon
DECL|typedef|off_t
r_typedef
id|__kernel_off_t
id|off_t
suffix:semicolon
DECL|typedef|pid_t
r_typedef
id|__kernel_pid_t
id|pid_t
suffix:semicolon
DECL|typedef|uid_t
r_typedef
id|__kernel_uid_t
id|uid_t
suffix:semicolon
DECL|typedef|gid_t
r_typedef
id|__kernel_gid_t
id|gid_t
suffix:semicolon
DECL|typedef|daddr_t
r_typedef
id|__kernel_daddr_t
id|daddr_t
suffix:semicolon
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
DECL|typedef|loff_t
r_typedef
id|__kernel_loff_t
id|loff_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The following typedefs are also protected by individual ifdefs for&n; * historical reasons:&n; */
macro_line|#ifndef _SIZE_T
DECL|macro|_SIZE_T
mdefine_line|#define _SIZE_T
DECL|typedef|size_t
r_typedef
id|__kernel_size_t
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _SSIZE_T
DECL|macro|_SSIZE_T
mdefine_line|#define _SSIZE_T
DECL|typedef|ssize_t
r_typedef
id|__kernel_ssize_t
id|ssize_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _PTRDIFF_T
DECL|macro|_PTRDIFF_T
mdefine_line|#define _PTRDIFF_T
DECL|typedef|ptrdiff_t
r_typedef
id|__kernel_ptrdiff_t
r_int
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _TIME_T
DECL|macro|_TIME_T
mdefine_line|#define _TIME_T
DECL|typedef|time_t
r_typedef
id|__kernel_time_t
id|time_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _CLOCK_T
DECL|macro|_CLOCK_T
mdefine_line|#define _CLOCK_T
DECL|typedef|clock_t
r_typedef
id|__kernel_clock_t
id|clock_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef _CADDR_T
DECL|macro|_CADDR_T
mdefine_line|#define _CADDR_T
DECL|typedef|caddr_t
r_typedef
id|__kernel_caddr_t
id|caddr_t
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
macro_line|#endif /* __KERNEL_STRICT_NAMES */
multiline_comment|/*&n; * Below are truly Linux-specific types that should never collide with&n; * any application/library that wants linux/types.h.&n; */
DECL|struct|ustat
r_struct
id|ustat
(brace
DECL|member|f_tfree
id|__kernel_daddr_t
id|f_tfree
suffix:semicolon
DECL|member|f_tinode
id|__kernel_ino_t
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
macro_line|#endif /* _LINUX_TYPES_H */
eof
