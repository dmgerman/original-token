macro_line|#ifndef __LINUX_UIO_H
DECL|macro|__LINUX_UIO_H
mdefine_line|#define __LINUX_UIO_H
multiline_comment|/*&n; *&t;Berkeley style UIO structures&t;-&t;Alan Cox 1994.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* A word of warning: Our uio structure will clash with the C library one (which is now obsolete). Remove the C&n;   library one from sys/uio.h if you have a very old library set */
DECL|struct|iovec
r_struct
id|iovec
(brace
DECL|member|iov_base
r_void
op_star
id|iov_base
suffix:semicolon
multiline_comment|/* BSD uses caddr_t (same thing in effect) */
DECL|member|iov_len
r_int
id|iov_len
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|UIO_MAXIOV
mdefine_line|#define UIO_MAXIOV&t;16&t;/* Maximum iovec&squot;s in one operation &n;&t;&t;&t;&t;   16 matches BSD */
macro_line|#endif
eof
