macro_line|#ifndef _LINUX_DIRENT_H
DECL|macro|_LINUX_DIRENT_H
mdefine_line|#define _LINUX_DIRENT_H
DECL|struct|dirent
r_struct
id|dirent
(brace
DECL|member|d_ino
r_int
id|d_ino
suffix:semicolon
DECL|member|d_off
id|__kernel_off_t
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
l_int|256
)braket
suffix:semicolon
multiline_comment|/* We must not include limits.h! */
)brace
suffix:semicolon
macro_line|#endif
eof
