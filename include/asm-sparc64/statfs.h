multiline_comment|/* $Id: statfs.h,v 1.2 1997/04/14 17:05:22 jj Exp $ */
macro_line|#ifndef _SPARC64_STATFS_H
DECL|macro|_SPARC64_STATFS_H
mdefine_line|#define _SPARC64_STATFS_H
macro_line|#ifndef __KERNEL_STRICT_NAMES
macro_line|#include &lt;linux/types.h&gt;
DECL|typedef|fsid_t
r_typedef
id|__kernel_fsid_t
id|fsid_t
suffix:semicolon
macro_line|#endif
DECL|struct|statfs32
r_struct
id|statfs32
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
id|__kernel_fsid_t32
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
multiline_comment|/* SunOS ignores this field. */
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
)brace
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
id|__kernel_fsid_t
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