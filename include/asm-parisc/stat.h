macro_line|#ifndef _PARISC_STAT_H
DECL|macro|_PARISC_STAT_H
mdefine_line|#define _PARISC_STAT_H
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|stat
r_struct
id|stat
(brace
DECL|member|st_dev
id|dev_t
id|st_dev
suffix:semicolon
multiline_comment|/* dev_t is 32 bits on parisc */
DECL|member|st_ino
id|ino_t
id|st_ino
suffix:semicolon
multiline_comment|/* 32 bits */
DECL|member|st_mode
id|mode_t
id|st_mode
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_nlink
id|nlink_t
id|st_nlink
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_reserved1
r_int
r_int
id|st_reserved1
suffix:semicolon
multiline_comment|/* old st_uid */
DECL|member|st_reserved2
r_int
r_int
id|st_reserved2
suffix:semicolon
multiline_comment|/* old st_gid */
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
DECL|member|st_spare1
r_int
r_int
id|st_spare1
suffix:semicolon
DECL|member|st_mtime
id|time_t
id|st_mtime
suffix:semicolon
DECL|member|st_spare2
r_int
r_int
id|st_spare2
suffix:semicolon
DECL|member|st_ctime
id|time_t
id|st_ctime
suffix:semicolon
DECL|member|st_spare3
r_int
r_int
id|st_spare3
suffix:semicolon
DECL|member|st_blksize
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
multiline_comment|/* ACL stuff */
DECL|member|__unused2
id|dev_t
id|__unused2
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused3
id|ino_t
id|__unused3
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
multiline_comment|/* cnodes */
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
multiline_comment|/* netsite */
DECL|member|st_fstype
r_int
id|st_fstype
suffix:semicolon
DECL|member|st_realdev
id|dev_t
id|st_realdev
suffix:semicolon
DECL|member|st_basemode
r_int
r_int
id|st_basemode
suffix:semicolon
DECL|member|st_spareshort
r_int
r_int
id|st_spareshort
suffix:semicolon
DECL|member|st_uid
id|uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|gid_t
id|st_gid
suffix:semicolon
DECL|member|st_spare4
r_int
r_int
id|st_spare4
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|off64_t
r_typedef
id|__kernel_off64_t
id|off64_t
suffix:semicolon
DECL|struct|hpux_stat64
r_struct
id|hpux_stat64
(brace
DECL|member|st_dev
id|dev_t
id|st_dev
suffix:semicolon
multiline_comment|/* dev_t is 32 bits on parisc */
DECL|member|st_ino
id|ino_t
id|st_ino
suffix:semicolon
multiline_comment|/* 32 bits */
DECL|member|st_mode
id|mode_t
id|st_mode
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_nlink
id|nlink_t
id|st_nlink
suffix:semicolon
multiline_comment|/* 16 bits */
DECL|member|st_reserved1
r_int
r_int
id|st_reserved1
suffix:semicolon
multiline_comment|/* old st_uid */
DECL|member|st_reserved2
r_int
r_int
id|st_reserved2
suffix:semicolon
multiline_comment|/* old st_gid */
DECL|member|st_rdev
id|dev_t
id|st_rdev
suffix:semicolon
DECL|member|st_size
id|off64_t
id|st_size
suffix:semicolon
DECL|member|st_atime
id|time_t
id|st_atime
suffix:semicolon
DECL|member|st_spare1
r_int
r_int
id|st_spare1
suffix:semicolon
DECL|member|st_mtime
id|time_t
id|st_mtime
suffix:semicolon
DECL|member|st_spare2
r_int
r_int
id|st_spare2
suffix:semicolon
DECL|member|st_ctime
id|time_t
id|st_ctime
suffix:semicolon
DECL|member|st_spare3
r_int
r_int
id|st_spare3
suffix:semicolon
DECL|member|st_blksize
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
id|__u64
id|st_blocks
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
multiline_comment|/* ACL stuff */
DECL|member|__unused2
id|dev_t
id|__unused2
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused3
id|ino_t
id|__unused3
suffix:semicolon
multiline_comment|/* network */
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
multiline_comment|/* cnodes */
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
multiline_comment|/* netsite */
DECL|member|st_fstype
r_int
id|st_fstype
suffix:semicolon
DECL|member|st_realdev
id|dev_t
id|st_realdev
suffix:semicolon
DECL|member|st_basemode
r_int
r_int
id|st_basemode
suffix:semicolon
DECL|member|st_spareshort
r_int
r_int
id|st_spareshort
suffix:semicolon
DECL|member|st_uid
id|uid_t
id|st_uid
suffix:semicolon
DECL|member|st_gid
id|gid_t
id|st_gid
suffix:semicolon
DECL|member|st_spare4
r_int
r_int
id|st_spare4
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|stat64
mdefine_line|#define stat64&t;hpux_stat64
macro_line|#endif
eof
