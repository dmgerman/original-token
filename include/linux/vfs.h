macro_line|#ifndef _LINUX_VFS_H
DECL|macro|_LINUX_VFS_H
mdefine_line|#define _LINUX_VFS_H
r_typedef
r_struct
(brace
DECL|member|val
r_int
id|val
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|fsid_t
)brace
id|fsid_t
suffix:semicolon
DECL|struct|statfs
r_struct
id|statfs
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|fsid_t
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
