multiline_comment|/*&n; *  linux/fs/ufs/ufs_file.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * $Id: ufs_file.c,v 1.7 1997/01/26 07:14:28 davem Exp $&n; *&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
DECL|variable|ufs_file_operations
r_static
r_struct
id|file_operations
id|ufs_file_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
id|generic_file_read
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
id|generic_file_mmap
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* open */
l_int|NULL
comma
multiline_comment|/* release */
id|file_fsync
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
l_int|NULL
comma
multiline_comment|/* check_media_change */
l_int|NULL
comma
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|ufs_file_inode_operations
r_struct
id|inode_operations
id|ufs_file_inode_operations
op_assign
(brace
op_amp
id|ufs_file_operations
comma
multiline_comment|/* default directory file operations */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
id|generic_readpage
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
id|ufs_bmap
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
comma
multiline_comment|/* permission */
l_int|NULL
comma
multiline_comment|/* smap */
)brace
suffix:semicolon
eof
