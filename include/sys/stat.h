macro_line|#ifndef _SYS_STAT_H
DECL|macro|_SYS_STAT_H
mdefine_line|#define _SYS_STAT_H
macro_line|#include &lt;sys/types.h&gt;
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|st_dev
id|dev_t
id|st_dev
suffix:semicolon
DECL|member|st_ino
id|ino_t
id|st_ino
suffix:semicolon
DECL|member|st_mode
id|umode_t
id|st_mode
suffix:semicolon
DECL|member|st_nlink
id|nlink_t
id|st_nlink
suffix:semicolon
DECL|member|st_uid
id|uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|gid_t
id|st_gid
suffix:semicolon
DECL|member|st_rdev
id|dev_t
id|st_rdev
suffix:semicolon
DECL|member|st_size
id|off_t
id|st_size
suffix:semicolon
DECL|member|st_atime
id|time_t
id|st_atime
suffix:semicolon
DECL|member|st_mtime
id|time_t
id|st_mtime
suffix:semicolon
DECL|member|st_ctime
id|time_t
id|st_ctime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|S_IFMT
mdefine_line|#define S_IFMT  00170000
DECL|macro|S_IFREG
mdefine_line|#define S_IFREG  0100000
DECL|macro|S_IFBLK
mdefine_line|#define S_IFBLK  0060000
DECL|macro|S_IFDIR
mdefine_line|#define S_IFDIR  0040000
DECL|macro|S_IFCHR
mdefine_line|#define S_IFCHR  0020000
DECL|macro|S_IFIFO
mdefine_line|#define S_IFIFO  0010000
DECL|macro|S_ISUID
mdefine_line|#define S_ISUID  0004000
DECL|macro|S_ISGID
mdefine_line|#define S_ISGID  0002000
DECL|macro|S_ISVTX
mdefine_line|#define S_ISVTX  0001000
DECL|macro|S_ISREG
mdefine_line|#define S_ISREG(m)&t;(((m) &amp; S_IFMT) == S_IFREG)
DECL|macro|S_ISDIR
mdefine_line|#define S_ISDIR(m)&t;(((m) &amp; S_IFMT) == S_IFDIR)
DECL|macro|S_ISCHR
mdefine_line|#define S_ISCHR(m)&t;(((m) &amp; S_IFMT) == S_IFCHR)
DECL|macro|S_ISBLK
mdefine_line|#define S_ISBLK(m)&t;(((m) &amp; S_IFMT) == S_IFBLK)
DECL|macro|S_ISFIFO
mdefine_line|#define S_ISFIFO(m)&t;(((m) &amp; S_IFMT) == S_IFIFO)
DECL|macro|S_IRWXU
mdefine_line|#define S_IRWXU 00700
DECL|macro|S_IRUSR
mdefine_line|#define S_IRUSR 00400
DECL|macro|S_IWUSR
mdefine_line|#define S_IWUSR 00200
DECL|macro|S_IXUSR
mdefine_line|#define S_IXUSR 00100
DECL|macro|S_IRWXG
mdefine_line|#define S_IRWXG 00070
DECL|macro|S_IRGRP
mdefine_line|#define S_IRGRP 00040
DECL|macro|S_IWGRP
mdefine_line|#define S_IWGRP 00020
DECL|macro|S_IXGRP
mdefine_line|#define S_IXGRP 00010
DECL|macro|S_IRWXO
mdefine_line|#define S_IRWXO 00007
DECL|macro|S_IROTH
mdefine_line|#define S_IROTH 00004
DECL|macro|S_IWOTH
mdefine_line|#define S_IWOTH 00002
DECL|macro|S_IXOTH
mdefine_line|#define S_IXOTH 00001
r_extern
r_int
id|chmod
c_func
(paren
r_const
r_char
op_star
id|_path
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|fstat
c_func
(paren
r_int
id|fildes
comma
r_struct
id|stat
op_star
id|stat_buf
)paren
suffix:semicolon
r_extern
r_int
id|mkdir
c_func
(paren
r_const
r_char
op_star
id|_path
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|mkfifo
c_func
(paren
r_const
r_char
op_star
id|_path
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|stat
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_struct
id|stat
op_star
id|stat_buf
)paren
suffix:semicolon
r_extern
id|mode_t
id|umask
c_func
(paren
id|mode_t
id|mask
)paren
suffix:semicolon
macro_line|#endif
eof
