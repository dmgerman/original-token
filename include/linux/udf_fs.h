multiline_comment|/*&n; * udf_fs.h&n; *&n; * Included by fs/filesystems.c&n; *&n; * CONTACTS&n; *&t;E-mail regarding any portion of the Linux UDF file system should be&n; *&t;directed to the development team mailing list (run by majordomo):&n; *&t;&t;linux_udf@hootie.lvld.hp.com&n; *&n; * COPYRIGHT&n; *&t;This file is distributed under the terms of the GNU General Public&n; *&t;License (GPL). Copies of the GPL can be obtained from:&n; *&t;&t;ftp://prep.ai.mit.edu/pub/gnu/GPL&n; *&t;Each contributing author retains all rights to their own work.&n; *&n; * HISTORY&n; *&t;July 21, 1997 - Andrew E. Mileski&n; *&t;Written, tested, and released.&n; *&n; * 10/2/98 dgb&t;rearranged all headers&n; * 11/26/98 bf  added byte order macros&n; * 12/5/98 dgb  removed other includes to reduce kernel namespace pollution.&n; *&t;&t;This should only be included by the kernel now!&n; */
macro_line|#if !defined(_LINUX_UDF_FS_H)
DECL|macro|_LINUX_UDF_FS_H
mdefine_line|#define _LINUX_UDF_FS_H
DECL|macro|UDF_PREALLOCATE
mdefine_line|#define UDF_PREALLOCATE
DECL|macro|UDF_DEFAULT_PREALLOC_BLOCKS
mdefine_line|#define UDF_DEFAULT_PREALLOC_BLOCKS&t;&t;8
DECL|macro|UDF_DEFAULT_PREALLOC_DIR_BLOCKS
mdefine_line|#define UDF_DEFAULT_PREALLOC_DIR_BLOCKS&t;0
DECL|macro|UDFFS_DATE
mdefine_line|#define UDFFS_DATE&t;&t;&quot;99/10/29&quot;
DECL|macro|UDFFS_VERSION
mdefine_line|#define UDFFS_VERSION&t;&quot;0.8.9.3&quot;
DECL|macro|UDFFS_DEBUG
mdefine_line|#define UDFFS_DEBUG
macro_line|#ifdef UDFFS_DEBUG
DECL|macro|udf_debug
mdefine_line|#define udf_debug(f, a...) &bslash;&n;&t;{ &bslash;&n;&t;&t;printk (KERN_DEBUG &quot;UDF-fs DEBUG (%s, %d): %s: &quot;, &bslash;&n;&t;&t;&t;__FILE__, __LINE__, __FUNCTION__); &bslash;&n;&t;&t;printk (## f, ## a); &bslash;&n;&t;}
macro_line|#else
DECL|macro|udf_debug
mdefine_line|#define udf_debug(f, a...) /**/
macro_line|#endif
DECL|macro|udf_info
mdefine_line|#define udf_info(f, a...) &bslash;&n;&t;&t;printk (KERN_INFO &quot;UDF-fs INFO &quot; ## f, ## a);
DECL|struct|udf_addr
r_struct
id|udf_addr
(brace
DECL|member|block
id|__u32
id|block
suffix:semicolon
DECL|member|partition
id|__u16
id|partition
suffix:semicolon
DECL|member|error
r_int
id|error
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
suffix:colon
l_int|15
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Prototype for fs/filesystem.c (the only thing really required in this file) */
r_extern
r_int
id|init_udf_fs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* !defined(_LINUX_UDF_FS_H) */
eof
