multiline_comment|/*&n; * Definitions for diskquota-operations. When diskquota is configured these&n; * macros expand to the right source-code.&n; *&n; * Author:  Marco van Wieringen &lt;mvw@planets.elm.net&gt;&n; *&n; * Version: $Id: quotaops.h,v 1.2 1998/01/15 16:22:26 ecd Exp $&n; *&n; */
macro_line|#ifndef _LINUX_QUOTAOPS_
DECL|macro|_LINUX_QUOTAOPS_
mdefine_line|#define _LINUX_QUOTAOPS_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_QUOTA)
multiline_comment|/*&n; * declaration of quota_function calls in kernel.&n; */
r_extern
r_void
id|dquot_initialize
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_void
id|dquot_drop
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
r_extern
r_void
id|invalidate_dquots
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|quota_off
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|sync_dquots
c_func
(paren
id|kdev_t
id|dev
comma
r_int
id|type
)paren
suffix:semicolon
r_extern
r_int
id|dquot_alloc_block
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
comma
id|uid_t
id|initiator
comma
r_char
id|warn
)paren
suffix:semicolon
r_extern
r_int
id|dquot_alloc_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
comma
id|uid_t
id|initiator
)paren
suffix:semicolon
r_extern
r_void
id|dquot_free_block
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
)paren
suffix:semicolon
r_extern
r_void
id|dquot_free_inode
c_func
(paren
r_const
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|number
)paren
suffix:semicolon
r_extern
r_int
id|dquot_transfer
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|iattr
comma
r_char
id|direction
comma
id|uid_t
id|initiator
)paren
suffix:semicolon
multiline_comment|/*&n; * Operations supported for diskquotas.&n; */
DECL|macro|DQUOT_INIT
mdefine_line|#define DQUOT_INIT(inode) &bslash;&n;if (inode-&gt;i_sb &amp;&amp; inode-&gt;i_sb-&gt;dq_op) { &bslash;&n;&t;inode-&gt;i_sb-&gt;dq_op-&gt;initialize(inode, -1); &bslash;&n;}
DECL|macro|DQUOT_DROP
mdefine_line|#define DQUOT_DROP(inode) &bslash;&n;if (IS_QUOTAINIT(inode)) { &bslash;&n;&t;if (inode-&gt;i_sb &amp;&amp; inode-&gt;i_sb-&gt;dq_op) &bslash;&n;&t;&t;inode-&gt;i_sb-&gt;dq_op-&gt;drop(inode); &bslash;&n;}
DECL|macro|DQUOT_SAVE_DROP
mdefine_line|#define DQUOT_SAVE_DROP(inode) &bslash;&n;if (IS_QUOTAINIT(inode)) { &bslash;&n;&t;inode-&gt;i_lock = 1; &bslash;&n;&t;if (inode-&gt;i_sb &amp;&amp; inode-&gt;i_sb-&gt;dq_op) &bslash;&n;&t;&t;inode-&gt;i_sb-&gt;dq_op-&gt;drop(inode); &bslash;&n;&t;unlock_inode(inode); &bslash;&n;&t;goto we_slept; &bslash;&n;}
DECL|macro|DQUOT_PREALLOC_BLOCK
mdefine_line|#define DQUOT_PREALLOC_BLOCK(sb, inode, nr) &bslash;&n;if (sb-&gt;dq_op) { &bslash;&n;&t;if (sb-&gt;dq_op-&gt;alloc_block(inode, fs_to_dq_blocks(nr, sb-&gt;s_blocksize), &bslash;&n;&t;                           current-&gt;euid, 0) == NO_QUOTA) &bslash;&n;&t;&t;break; &bslash;&n;}
DECL|macro|DQUOT_ALLOC_BLOCK
mdefine_line|#define DQUOT_ALLOC_BLOCK(sb, inode, nr) &bslash;&n;if (sb-&gt;dq_op) { &bslash;&n;&t;if (sb-&gt;dq_op-&gt;alloc_block(inode, fs_to_dq_blocks(nr, sb-&gt;s_blocksize), &bslash;&n;&t;                           current-&gt;euid, 1) == NO_QUOTA) { &bslash;&n;&t;&t;unlock_super (sb); &bslash;&n;&t;&t;*err = -EDQUOT; &bslash;&n;&t;&t;return 0; &bslash;&n;&t;} &bslash;&n;}
DECL|macro|DQUOT_ALLOC_INODE
mdefine_line|#define DQUOT_ALLOC_INODE(sb, inode) &bslash;&n;if (sb-&gt;dq_op) { &bslash;&n;&t;sb-&gt;dq_op-&gt;initialize (inode, -1); &bslash;&n;&t;if (sb-&gt;dq_op-&gt;alloc_inode (inode, 1, current-&gt;euid)) { &bslash;&n;&t;&t;sb-&gt;dq_op-&gt;drop (inode); &bslash;&n;&t;&t;inode-&gt;i_nlink = 0; &bslash;&n;&t;&t;iput (inode); &bslash;&n;&t;&t;*err = -EDQUOT; &bslash;&n;&t;&t;return NULL; &bslash;&n;&t;} &bslash;&n;&t;inode-&gt;i_flags |= S_QUOTA; &bslash;&n;}
DECL|macro|DQUOT_FREE_BLOCK
mdefine_line|#define DQUOT_FREE_BLOCK(sb, inode, nr) &bslash;&n;if (sb-&gt;dq_op) { &bslash;&n;&t;sb-&gt;dq_op-&gt;free_block(inode, fs_to_dq_blocks(nr, sb-&gt;s_blocksize)); &bslash;&n;}
DECL|macro|DQUOT_FREE_INODE
mdefine_line|#define DQUOT_FREE_INODE(sb, inode) &bslash;&n;if (sb-&gt;dq_op) { &bslash;&n;&t;sb-&gt;dq_op-&gt;free_inode(inode, 1); &bslash;&n;}
DECL|macro|DQUOT_TRANSFER
mdefine_line|#define DQUOT_TRANSFER(dentry, iattr) &bslash;&n;if (dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op) { &bslash;&n;&t;if (IS_QUOTAINIT(dentry-&gt;d_inode) == 0) &bslash;&n;&t;&t;dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op-&gt;initialize(dentry-&gt;d_inode, -1); &bslash;&n;&t;if (dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op-&gt;transfer(dentry-&gt;d_inode, &amp;iattr, 0, current-&gt;euid)) { &bslash;&n;&t;&t;error = -EDQUOT; &bslash;&n;&t;&t;goto out; &bslash;&n;&t;} &bslash;&n;&t;error = notify_change(dentry, &amp;iattr); &bslash;&n;&t;if (error) &bslash;&n;&t;&t;inode-&gt;i_sb-&gt;dq_op-&gt;transfer(dentry-&gt;d_inode, &amp;iattr, 1, current-&gt;euid); &bslash;&n;} else { &bslash;&n;&t;error = notify_change(dentry, &amp;iattr); &bslash;&n;}
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(dev) &bslash;&n;sync_dquots(dev, -1)
DECL|macro|DQUOT_OFF
mdefine_line|#define DQUOT_OFF(dev) &bslash;&n;quota_off(dev, -1)
macro_line|#else
multiline_comment|/*&n; * NO-OP when quota not configured.&n; */
DECL|macro|DQUOT_INIT
mdefine_line|#define DQUOT_INIT(inode)
DECL|macro|DQUOT_DROP
mdefine_line|#define DQUOT_DROP(inode)
DECL|macro|DQUOT_SAVE_DROP
mdefine_line|#define DQUOT_SAVE_DROP(inode)
DECL|macro|DQUOT_PREALLOC_BLOCK
mdefine_line|#define DQUOT_PREALLOC_BLOCK(sb, inode, nr)
DECL|macro|DQUOT_ALLOC_BLOCK
mdefine_line|#define DQUOT_ALLOC_BLOCK(sb, inode, nr)
DECL|macro|DQUOT_ALLOC_INODE
mdefine_line|#define DQUOT_ALLOC_INODE(sb, inode)
DECL|macro|DQUOT_FREE_BLOCK
mdefine_line|#define DQUOT_FREE_BLOCK(sb, inode, nr)
DECL|macro|DQUOT_FREE_INODE
mdefine_line|#define DQUOT_FREE_INODE(sb, inode)
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(dev)
DECL|macro|DQUOT_OFF
mdefine_line|#define DQUOT_OFF(dev)
multiline_comment|/*&n; * Special case expands to a simple notify_change.&n; */
DECL|macro|DQUOT_TRANSFER
mdefine_line|#define DQUOT_TRANSFER(dentry, iattr) &bslash;&n;error = notify_change(dentry, &amp;iattr)
macro_line|#endif /* CONFIG_QUOTA */
macro_line|#endif /* _LINUX_QUOTAOPS_ */
eof
