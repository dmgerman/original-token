macro_line|#ifndef _SYS_DIRENT_H
DECL|macro|_SYS_DIRENT_H
mdefine_line|#define _SYS_DIRENT_H
macro_line|#include &lt;limits.h&gt;
macro_line|#include &lt;sys/types.h&gt;
DECL|struct|dirent
r_struct
id|dirent
(brace
DECL|member|d_ino
r_int
id|d_ino
suffix:semicolon
DECL|member|d_off
id|off_t
id|d_off
suffix:semicolon
DECL|member|d_reclen
r_int
r_int
id|d_reclen
suffix:semicolon
DECL|member|d_name
r_char
id|d_name
(braket
id|NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
