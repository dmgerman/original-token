macro_line|#ifndef _LINUX_TYPES_H
DECL|macro|_LINUX_TYPES_H
mdefine_line|#define _LINUX_TYPES_H
multiline_comment|/*&n; * This allows for 256 file descriptors: if NR_OPEN is ever grown beyond that&n; * you&squot;ll have to change this too. But 256 fd&squot;s seem to be enough even for such&n; * &quot;real&quot; unices like SunOS, so hopefully this is one limit that doesn&squot;t have&n; * to be changed.&n; *&n; * Note that POSIX wants the FD_CLEAR(fd,fdsetp) defines to be in &lt;sys/time.h&gt;&n; * (and thus &lt;linux/time.h&gt;) - but this is a more logical place for them. Solved&n; * by having dummy defines in &lt;sys/time.h&gt;.&n; */
multiline_comment|/*&n; * Those macros may have been defined in &lt;gnu/types.h&gt;. But we always&n; * use the ones here. &n; */
DECL|macro|__FDSET_LONGS
macro_line|#undef __FDSET_LONGS
DECL|macro|__FDSET_LONGS
mdefine_line|#define __FDSET_LONGS (256/(8*sizeof(unsigned long)))
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
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
macro_line|#if defined(__GNUC__) &amp;&amp; !defined(__STRICT_ANSI__)
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
