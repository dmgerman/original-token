macro_line|#ifndef _SYS_TYPES_H
DECL|macro|_SYS_TYPES_H
mdefine_line|#define _SYS_TYPES_H
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
macro_line|#ifndef _TIME_T
DECL|macro|_TIME_T
mdefine_line|#define _TIME_T
DECL|typedef|time_t
r_typedef
r_int
id|time_t
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
DECL|typedef|u_long
r_typedef
r_int
r_int
id|u_long
suffix:semicolon
DECL|typedef|ushort
r_typedef
r_int
r_int
id|ushort
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
DECL|typedef|fd_set
r_typedef
r_int
r_int
id|fd_set
suffix:semicolon
DECL|member|quot
DECL|member|rem
DECL|typedef|div_t
r_typedef
r_struct
(brace
r_int
id|quot
comma
id|rem
suffix:semicolon
)brace
id|div_t
suffix:semicolon
DECL|member|quot
DECL|member|rem
DECL|typedef|ldiv_t
r_typedef
r_struct
(brace
r_int
id|quot
comma
id|rem
suffix:semicolon
)brace
id|ldiv_t
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
