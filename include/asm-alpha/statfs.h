macro_line|#ifndef _ALPHA_STATFS_H
DECL|macro|_ALPHA_STATFS_H
mdefine_line|#define _ALPHA_STATFS_H
macro_line|#ifndef _LINUX_TYPES_DONT_EXPORT
macro_line|#include &lt;linux/posix_types.h&gt;
DECL|typedef|fsid_t
r_typedef
id|__kernel_fsid_t
id|fsid_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The OSF/1 statfs structure is much larger, but this should&n; * match the beginning, at least.&n; */
DECL|struct|statfs
r_struct
id|statfs
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_flags
r_int
id|f_flags
suffix:semicolon
DECL|member|f_fsize
r_int
id|f_fsize
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
id|__kernel_fsid_t
id|f_fsid
suffix:semicolon
multiline_comment|/* linux-specific entries start here.. */
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
