multiline_comment|/*&n; *  coda_fs_i.h&n; *&n; *  Copyright (C) 1998 Carnegie Mellon University&n; *&n; */
macro_line|#ifndef _LINUX_CODA_FS_I
DECL|macro|_LINUX_CODA_FS_I
mdefine_line|#define _LINUX_CODA_FS_I
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
DECL|macro|CODA_CNODE_MAGIC
mdefine_line|#define CODA_CNODE_MAGIC        0x47114711
multiline_comment|/*&n; * coda fs inode data&n; */
DECL|struct|coda_inode_info
r_struct
id|coda_inode_info
(brace
DECL|member|c_fid
r_struct
id|ViceFid
id|c_fid
suffix:semicolon
multiline_comment|/* Coda identifier */
DECL|member|c_flags
id|u_short
id|c_flags
suffix:semicolon
multiline_comment|/* flags (see below) */
DECL|member|c_ocount
id|u_short
id|c_ocount
suffix:semicolon
multiline_comment|/* count of openers */
DECL|member|c_owrite
id|u_short
id|c_owrite
suffix:semicolon
multiline_comment|/* count of open for write */
DECL|member|c_mmcount
id|u_short
id|c_mmcount
suffix:semicolon
multiline_comment|/* count of mmappers */
DECL|member|c_ovp
r_struct
id|inode
op_star
id|c_ovp
suffix:semicolon
multiline_comment|/* open inode  pointer */
DECL|member|c_cnhead
r_struct
id|list_head
id|c_cnhead
suffix:semicolon
multiline_comment|/* head of cache entries */
DECL|member|c_volrootlist
r_struct
id|list_head
id|c_volrootlist
suffix:semicolon
multiline_comment|/* list of volroot cnoddes */
DECL|member|c_vnode
r_struct
id|inode
op_star
id|c_vnode
suffix:semicolon
multiline_comment|/*  inode associated with cnode */
DECL|member|c_magic
r_int
id|c_magic
suffix:semicolon
multiline_comment|/* to verify the data structure */
)brace
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|C_VATTR
mdefine_line|#define C_VATTR       0x1         /* Validity of vattr in the cnode */
DECL|macro|C_SYMLINK
mdefine_line|#define C_SYMLINK     0x2         /* Validity of symlink pointer in the cnode */
DECL|macro|C_DYING
mdefine_line|#define C_DYING       0x4&t;  /* Set for outstanding cnodes from venus (which died) */
DECL|macro|C_PURGE
mdefine_line|#define C_PURGE      0x8
DECL|macro|C_ZAPDIR
mdefine_line|#define C_ZAPDIR      0x10
DECL|macro|C_INITED
mdefine_line|#define C_INITED      0x20
r_int
id|coda_cnode_make
c_func
(paren
r_struct
id|inode
op_star
op_star
comma
r_struct
id|ViceFid
op_star
comma
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|coda_cnode_makectl
c_func
(paren
r_struct
id|inode
op_star
op_star
id|inode
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_struct
id|inode
op_star
id|coda_fid_to_inode
c_func
(paren
id|ViceFid
op_star
id|fid
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_void
id|coda_replace_fid
c_func
(paren
r_struct
id|inode
op_star
comma
id|ViceFid
op_star
comma
id|ViceFid
op_star
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
