multiline_comment|/*&n; * Cnode definitions for Coda.&n; * Original version: (C) 1996 Peter Braam &n; * Rewritten for Linux 2.1: (C) 1997 Carnegie Mellon University&n; *&n; * Carnegie Mellon encourages users of this code to contribute improvements&n; * to the Coda project. Contact Peter Braam &lt;coda@cs.cmu.edu&gt;.&n; */
macro_line|#ifndef&t;_CNODE_H_
DECL|macro|_CNODE_H_
mdefine_line|#define&t;_CNODE_H_
macro_line|#include &lt;linux/coda.h&gt;
DECL|macro|CODA_CNODE_MAGIC
mdefine_line|#define CODA_CNODE_MAGIC        0x47114711
multiline_comment|/* defintion of cnode, which combines ViceFid with inode information */
DECL|struct|cnode
r_struct
id|cnode
(brace
DECL|member|c_vnode
r_struct
id|inode
op_star
id|c_vnode
suffix:semicolon
multiline_comment|/*  inode associated with cnode */
DECL|member|c_fid
id|ViceFid
id|c_fid
suffix:semicolon
multiline_comment|/* Coda identifier */
DECL|member|c_flags
id|u_short
id|c_flags
suffix:semicolon
multiline_comment|/* flags (see below) */
DECL|member|c_magic
r_int
id|c_magic
suffix:semicolon
multiline_comment|/* to verify the data structure */
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
multiline_comment|/* open vnode pointer */
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
)brace
suffix:semicolon
multiline_comment|/* flags */
DECL|macro|C_VATTR
mdefine_line|#define C_VATTR       0x1         /* Validity of vattr in the cnode */
DECL|macro|C_SYMLINK
mdefine_line|#define C_SYMLINK     0x2         /* Validity of symlink pointer in the cnode */
DECL|macro|C_DYING
mdefine_line|#define C_DYING       0x4&t;  /* Set for outstanding cnodes from venus (which died) */
DECL|macro|C_ZAPFID
mdefine_line|#define C_ZAPFID      0x8
DECL|macro|C_ZAPDIR
mdefine_line|#define C_ZAPDIR      0x10
r_void
id|coda_cnode_free
c_func
(paren
r_struct
id|cnode
op_star
)paren
suffix:semicolon
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
multiline_comment|/* inode to cnode */
DECL|function|ITOC
r_static
r_inline
r_struct
id|cnode
op_star
id|ITOC
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
(paren
(paren
r_struct
id|cnode
op_star
)paren
id|inode-&gt;u.generic_ip
)paren
suffix:semicolon
)brace
multiline_comment|/* cnode to inode */
DECL|function|CTOI
r_static
r_inline
r_struct
id|inode
op_star
id|CTOI
c_func
(paren
r_struct
id|cnode
op_star
id|cnode
)paren
(brace
r_return
(paren
id|cnode-&gt;c_vnode
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
eof
