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
DECL|function|DQUOT_INIT
r_extern
id|__inline__
r_void
id|DQUOT_INIT
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_DROP
r_extern
id|__inline__
r_void
id|DQUOT_DROP
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|IS_QUOTAINIT
c_func
(paren
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_sb
op_logical_and
id|inode-&gt;i_sb-&gt;dq_op
)paren
id|inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|drop
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
)brace
DECL|function|DQUOT_PREALLOC_BLOCK
r_extern
id|__inline__
r_int
id|DQUOT_PREALLOC_BLOCK
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
op_member_access_from_pointer
id|alloc_block
c_func
(paren
id|inode
comma
id|fs_to_dq_blocks
c_func
(paren
id|nr
comma
id|sb-&gt;s_blocksize
)paren
comma
id|current-&gt;euid
comma
l_int|0
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_BLOCK
r_extern
id|__inline__
r_int
id|DQUOT_ALLOC_BLOCK
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
op_member_access_from_pointer
id|alloc_block
c_func
(paren
id|inode
comma
id|fs_to_dq_blocks
c_func
(paren
id|nr
comma
id|sb-&gt;s_blocksize
)paren
comma
id|current-&gt;euid
comma
l_int|1
)paren
op_eq
id|NO_QUOTA
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_ALLOC_INODE
r_extern
id|__inline__
r_int
id|DQUOT_ALLOC_INODE
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
(brace
id|sb-&gt;dq_op-&gt;initialize
(paren
id|inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;dq_op-&gt;alloc_inode
(paren
id|inode
comma
l_int|1
comma
id|current-&gt;euid
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|inode-&gt;i_flags
op_or_assign
id|S_QUOTA
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_BLOCK
r_extern
id|__inline__
r_void
id|DQUOT_FREE_BLOCK
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
comma
r_int
id|nr
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
id|sb-&gt;dq_op
op_member_access_from_pointer
id|free_block
c_func
(paren
id|inode
comma
id|fs_to_dq_blocks
c_func
(paren
id|nr
comma
id|sb-&gt;s_blocksize
)paren
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_FREE_INODE
r_extern
id|__inline__
r_void
id|DQUOT_FREE_INODE
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;dq_op
)paren
id|sb-&gt;dq_op
op_member_access_from_pointer
id|free_inode
c_func
(paren
id|inode
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|DQUOT_TRANSFER
r_extern
id|__inline__
r_int
id|DQUOT_TRANSFER
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_int
id|error
op_assign
op_minus
id|EDQUOT
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op
)paren
(brace
r_if
c_cond
(paren
id|IS_QUOTAINIT
c_func
(paren
id|dentry-&gt;d_inode
)paren
op_eq
l_int|0
)paren
id|dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|initialize
c_func
(paren
id|dentry-&gt;d_inode
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|transfer
c_func
(paren
id|dentry-&gt;d_inode
comma
id|iattr
comma
l_int|0
comma
id|current-&gt;euid
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|notify_change
c_func
(paren
id|dentry
comma
id|iattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|dentry-&gt;d_inode-&gt;i_sb-&gt;dq_op
op_member_access_from_pointer
id|transfer
c_func
(paren
id|dentry-&gt;d_inode
comma
id|iattr
comma
l_int|1
comma
id|current-&gt;euid
)paren
suffix:semicolon
)brace
r_else
(brace
id|error
op_assign
id|notify_change
c_func
(paren
id|dentry
comma
id|iattr
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(dev)&t;sync_dquots(dev, -1)
DECL|macro|DQUOT_OFF
mdefine_line|#define DQUOT_OFF(dev)&t;quota_off(dev, -1)
macro_line|#else
multiline_comment|/*&n; * NO-OP when quota not configured.&n; */
DECL|macro|DQUOT_INIT
mdefine_line|#define DQUOT_INIT(inode)&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_DROP
mdefine_line|#define DQUOT_DROP(inode)&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_PREALLOC_BLOCK
mdefine_line|#define DQUOT_PREALLOC_BLOCK(sb, inode, nr)&t;(0)
DECL|macro|DQUOT_ALLOC_BLOCK
mdefine_line|#define DQUOT_ALLOC_BLOCK(sb, inode, nr)&t;(0)
DECL|macro|DQUOT_ALLOC_INODE
mdefine_line|#define DQUOT_ALLOC_INODE(sb, inode)&t;&t;(0)
DECL|macro|DQUOT_FREE_BLOCK
mdefine_line|#define DQUOT_FREE_BLOCK(sb, inode, nr)&t;&t;do { } while(0)
DECL|macro|DQUOT_FREE_INODE
mdefine_line|#define DQUOT_FREE_INODE(sb, inode)&t;&t;do { } while(0)
DECL|macro|DQUOT_SYNC
mdefine_line|#define DQUOT_SYNC(dev)&t;&t;&t;&t;do { } while(0)
DECL|macro|DQUOT_OFF
mdefine_line|#define DQUOT_OFF(dev)&t;&t;&t;&t;do { } while(0)
multiline_comment|/*&n; * Special case expands to a simple notify_change.&n; */
DECL|macro|DQUOT_TRANSFER
mdefine_line|#define DQUOT_TRANSFER(dentry, iattr) notify_change(dentry, iattr)
macro_line|#endif /* CONFIG_QUOTA */
macro_line|#endif /* _LINUX_QUOTAOPS_ */
eof