macro_line|#ifndef _MSDOS_FS_I
DECL|macro|_MSDOS_FS_I
mdefine_line|#define _MSDOS_FS_I
macro_line|#ifndef _LINUX_CONFIG_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#endif
macro_line|#ifndef _LINUX_PIPE_FS_I_H
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
macro_line|#endif
multiline_comment|/*&n; * MS-DOS file system inode data in memory&n; */
DECL|struct|msdos_inode_info
r_struct
id|msdos_inode_info
(brace
multiline_comment|/*&n;&t;&t;UMSDOS manage special file and fifo as normal empty&n;&t;&t;msdos file. fifo inode processing conflict with msdos&n;&t;&t;processing. So I insert the pipe_inode_info so the&n;&t;&t;information does not overlap. This increases the size of&n;&t;&t;the msdos_inode_info, but the clear winner here is&n;&t;&t;the ext2_inode_info. So it does not change anything to&n;&t;&t;the total size of a struct inode.&n;&n;&t;&t;I have not put it conditionnal. With the advent of loadable&n;&t;&t;file system drivers, it would be very easy to compile&n;&t;&t;a MsDOS FS driver unaware of UMSDOS and then later to&n;&t;&t;load a (then incompatible) UMSDOS FS driver.&n;&t;*/
DECL|member|reserved
r_struct
id|pipe_inode_info
id|reserved
suffix:semicolon
DECL|member|i_start
r_int
id|i_start
suffix:semicolon
multiline_comment|/* first cluster or 0 */
DECL|member|i_attrs
r_int
id|i_attrs
suffix:semicolon
multiline_comment|/* unused attribute bits */
DECL|member|i_busy
r_int
id|i_busy
suffix:semicolon
multiline_comment|/* file is either deleted but still open, or&n;&t;&t;&t;   inconsistent (mkdir) */
DECL|member|i_depend
r_struct
id|inode
op_star
id|i_depend
suffix:semicolon
multiline_comment|/* pointer to inode that depends on the&n;&t;&t;&t;&t;   current inode */
DECL|member|i_old
r_struct
id|inode
op_star
id|i_old
suffix:semicolon
multiline_comment|/* pointer to the old inode this inode&n;&t;&t;&t;&t;   depends on */
DECL|member|i_binary
r_int
id|i_binary
suffix:semicolon
multiline_comment|/* file contains non-text data */
)brace
suffix:semicolon
macro_line|#endif
eof
