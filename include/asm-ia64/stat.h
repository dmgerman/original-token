macro_line|#ifndef _ASM_IA64_STAT_H
DECL|macro|_ASM_IA64_STAT_H
mdefine_line|#define _ASM_IA64_STAT_H
multiline_comment|/*&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
DECL|struct|stat
r_struct
id|stat
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
DECL|member|__pad1
r_int
r_int
id|__pad1
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
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
id|st_blocks
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _ASM_IA64_STAT_H */
eof
