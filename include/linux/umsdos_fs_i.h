macro_line|#ifndef UMSDOS_FS_I_H
DECL|macro|UMSDOS_FS_I_H
mdefine_line|#define UMSDOS_FS_I_H
macro_line|#ifndef _LINUX_TYPES_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/msdos_fs_i.h&gt;
macro_line|#include &lt;linux/pipe_fs_i.h&gt;
multiline_comment|/* #Specification: strategy / in memory inode&n; * Here is the information specific to the inode of the UMSDOS file&n; * system. This information is added to the end of the standard struct&n; * inode. Each file system has its own extension to struct inode,&n; * so do the umsdos file system.&n; * &n; * The strategy is to have the umsdos_inode_info as a superset of&n; * the msdos_inode_info, since most of the time the job is done&n; * by the msdos fs code.&n; * &n; * So we duplicate the msdos_inode_info, and add our own info at the&n; * end.&n; * &n; * For all file type (and directory) the inode has a reference to:&n; * the directory which hold this entry: i_dir_owner&n; * The EMD file of i_dir_owner: i_emd_owner&n; * The offset in this EMD file of the entry: pos&n; * &n; * For directory, we also have a reference to the inode of its&n; * own EMD file. Also, we have dir_locking_info to help synchronise&n; * file creation and file lookup. This data is sharing space with&n; * the pipe_inode_info not used by directory. See also msdos_fs_i.h&n; * for more information about pipe_inode_info and msdos_inode_info.&n; * &n; * Special file and fifo do have an inode which correspond to an&n; * empty MSDOS file.&n; * &n; * symlink are processed mostly like regular file. The content is the&n; * link.&n; * &n; * fifos add there own extension to the inode. I have reserved some&n; * space for fifos side by side with msdos_inode_info. This is just&n; * to for the show, because msdos_inode_info already include the&n; * pipe_inode_info.&n; * &n; * The UMSDOS specific extension is placed after the union.&n; */
DECL|struct|dir_locking_info
r_struct
id|dir_locking_info
(brace
DECL|member|p
r_struct
id|wait_queue
op_star
id|p
suffix:semicolon
DECL|member|looking
r_int
r_int
id|looking
suffix:semicolon
multiline_comment|/* How many process doing a lookup */
DECL|member|creating
r_int
r_int
id|creating
suffix:semicolon
multiline_comment|/* Is there any creation going on here&n;&t;&t;&t;&t; *  Only one at a time, although one&n;&t;&t;&t;&t; *  may recursively lock, so it is a counter&n;&t;&t;&t;&t; */
DECL|member|pid
r_int
id|pid
suffix:semicolon
multiline_comment|/* pid of the process owning the creation */
multiline_comment|/* lock */
)brace
suffix:semicolon
DECL|struct|umsdos_inode_info
r_struct
id|umsdos_inode_info
(brace
r_union
(brace
DECL|member|msdos_info
r_struct
id|msdos_inode_info
id|msdos_info
suffix:semicolon
DECL|member|pipe_info
r_struct
id|pipe_inode_info
id|pipe_info
suffix:semicolon
DECL|member|dir_info
r_struct
id|dir_locking_info
id|dir_info
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
multiline_comment|/* Simply a filler, never referenced by fs/umsdos/... */
DECL|member|i_dir_owner
r_int
r_int
id|i_dir_owner
suffix:semicolon
multiline_comment|/* Inode of the dir which hold this entry */
DECL|member|i_emd_owner
r_int
r_int
id|i_emd_owner
suffix:semicolon
multiline_comment|/* Inode of the EMD file of i_dir_owner */
DECL|member|pos
id|off_t
id|pos
suffix:semicolon
multiline_comment|/* Entry offset in the emd_owner file */
multiline_comment|/* The rest is used only if this inode describe a directory */
DECL|member|i_emd_dir
r_int
r_int
id|i_emd_dir
suffix:semicolon
multiline_comment|/* Inode of the EMD file of this inode */
)brace
suffix:semicolon
macro_line|#endif
eof
