macro_line|#ifndef _LINUX_STAT_H
DECL|macro|_LINUX_STAT_H
mdefine_line|#define _LINUX_STAT_H
DECL|struct|old_stat
r_struct
id|old_stat
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|new_stat
r_struct
id|new_stat
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|S_IFMT
mdefine_line|#define S_IFMT  00170000
DECL|macro|S_IFSOCK
mdefine_line|#define S_IFSOCK 0140000
DECL|macro|S_IFLNK
mdefine_line|#define S_IFLNK&t; 0120000
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
DECL|macro|S_ISLNK
mdefine_line|#define S_ISLNK(m)&t;(((m) &amp; S_IFMT) == S_IFLNK)
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
DECL|macro|S_ISSOCK
mdefine_line|#define S_ISSOCK(m)&t;(((m) &amp; S_IFMT) == S_IFSOCK)
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
macro_line|#endif
eof
