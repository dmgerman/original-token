multiline_comment|/*&n; *  Name                         : qnx4_fs_i.h&n; *  Author                       : Richard Frowijn&n; *  Function                     : qnx4 inode definitions&n; *  Version                      : 1.0&n; *  Last modified                : 25-05-1998&n; * &n; *  History                      : 23-03-1998 created&n; * &n; */
macro_line|#ifndef _QNX4_FS_I
DECL|macro|_QNX4_FS_I
mdefine_line|#define _QNX4_FS_I
macro_line|#include &lt;linux/qnxtypes.h&gt;
multiline_comment|/*&n; * qnx4 fs inode entry &n; */
DECL|struct|qnx4_inode_info
r_struct
id|qnx4_inode_info
(brace
DECL|member|i_reserved
r_char
id|i_reserved
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* 16 */
DECL|member|i_size
id|off_t
id|i_size
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_first_xtnt
id|_xtnt_t
id|i_first_xtnt
suffix:semicolon
multiline_comment|/*  8 */
DECL|member|i_xblk
r_int
id|i_xblk
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_ftime
id|time_t
id|i_ftime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_mtime
id|time_t
id|i_mtime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_atime
id|time_t
id|i_atime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_ctime
id|time_t
id|i_ctime
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_num_xtnts
id|_nxtnt_t
id|i_num_xtnts
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_mode
id|mode_t
id|i_mode
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_uid
id|muid_t
id|i_uid
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_gid
id|mgid_t
id|i_gid
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_nlink
id|nlink_t
id|i_nlink
suffix:semicolon
multiline_comment|/*  2 */
DECL|member|i_zero
r_char
id|i_zero
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/*  4 */
DECL|member|i_type
id|_ftype_t
id|i_type
suffix:semicolon
multiline_comment|/*  1 */
DECL|member|i_status
r_int
r_char
id|i_status
suffix:semicolon
multiline_comment|/*  1 */
)brace
suffix:semicolon
macro_line|#endif
eof
