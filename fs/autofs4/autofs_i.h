multiline_comment|/* -*- c -*- ------------------------------------------------------------- *&n; *   &n; * linux/fs/autofs/autofs_i.h&n; *&n; *   Copyright 1997-1998 Transmeta Corporation - All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/* Internal header file for autofs */
macro_line|#include &lt;linux/auto_fs4.h&gt;
macro_line|#include &lt;linux/list.h&gt;
multiline_comment|/* This is the range of ioctl() numbers we claim as ours */
DECL|macro|AUTOFS_IOC_FIRST
mdefine_line|#define AUTOFS_IOC_FIRST     AUTOFS_IOC_READY
DECL|macro|AUTOFS_IOC_COUNT
mdefine_line|#define AUTOFS_IOC_COUNT     32
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/* #define DEBUG */
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D) do{ printk(&quot;pid %d: &quot;, current-&gt;pid); printk D; } while(0)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D) do {} while(0)
macro_line|#endif
DECL|macro|AUTOFS_SUPER_MAGIC
mdefine_line|#define AUTOFS_SUPER_MAGIC 0x0187
multiline_comment|/*&n; * If the daemon returns a negative response (AUTOFS_IOC_FAIL) then the&n; * kernel will keep the negative response cached for up to the time given&n; * here, although the time can be shorter if the kernel throws the dcache&n; * entry away.  This probably should be settable from user space.&n; */
DECL|macro|AUTOFS_NEGATIVE_TIMEOUT
mdefine_line|#define AUTOFS_NEGATIVE_TIMEOUT (60*HZ)&t;/* 1 minute */
multiline_comment|/* Unified info structure.  This is pointed to by both the dentry and&n;   inode structures.  Each file in the filesystem has an instance of this&n;   structure.  It holds a reference to the dentry, so dentries are never&n;   flushed while the file exists.  All name lookups are dealt with at the&n;   dentry level, although the filesystem can interfere in the validation&n;   process.  Readdir is implemented by traversing the dentry lists. */
DECL|struct|autofs_info
r_struct
id|autofs_info
(brace
DECL|member|dentry
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|sbi
r_struct
id|autofs_sb_info
op_star
id|sbi
suffix:semicolon
DECL|member|last_used
r_int
r_int
id|last_used
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|free
r_void
(paren
op_star
id|free
)paren
(paren
r_struct
id|autofs_info
op_star
)paren
suffix:semicolon
r_union
(brace
DECL|member|symlink
r_const
r_char
op_star
id|symlink
suffix:semicolon
DECL|member|u
)brace
id|u
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_INF_EXPIRING
mdefine_line|#define AUTOFS_INF_EXPIRING&t;(1&lt;&lt;0) /* dentry is in the process of expiring */
DECL|struct|autofs_wait_queue
r_struct
id|autofs_wait_queue
(brace
DECL|member|queue
id|wait_queue_head_t
id|queue
suffix:semicolon
DECL|member|next
r_struct
id|autofs_wait_queue
op_star
id|next
suffix:semicolon
DECL|member|wait_queue_token
id|autofs_wqt_t
id|wait_queue_token
suffix:semicolon
multiline_comment|/* We use the following to see what we are waiting for */
DECL|member|hash
r_int
id|hash
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* This is for status reporting upon return */
DECL|member|status
r_int
id|status
suffix:semicolon
DECL|member|wait_ctr
r_int
id|wait_ctr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_SBI_MAGIC
mdefine_line|#define AUTOFS_SBI_MAGIC 0x6d4a556d
DECL|struct|autofs_sb_info
r_struct
id|autofs_sb_info
(brace
DECL|member|magic
id|u32
id|magic
suffix:semicolon
DECL|member|pipe
r_struct
id|file
op_star
id|pipe
suffix:semicolon
DECL|member|oz_pgrp
id|pid_t
id|oz_pgrp
suffix:semicolon
DECL|member|catatonic
r_int
id|catatonic
suffix:semicolon
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|exp_timeout
r_int
r_int
id|exp_timeout
suffix:semicolon
DECL|member|sb
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
DECL|member|queues
r_struct
id|autofs_wait_queue
op_star
id|queues
suffix:semicolon
multiline_comment|/* Wait queue pointer */
)brace
suffix:semicolon
DECL|function|autofs4_sbi
r_static
r_inline
r_struct
id|autofs_sb_info
op_star
id|autofs4_sbi
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_return
(paren
r_struct
id|autofs_sb_info
op_star
)paren
(paren
id|sb-&gt;u.generic_sbp
)paren
suffix:semicolon
)brace
DECL|function|autofs4_dentry_ino
r_static
r_inline
r_struct
id|autofs_info
op_star
id|autofs4_dentry_ino
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_return
(paren
r_struct
id|autofs_info
op_star
)paren
(paren
id|dentry-&gt;d_fsdata
)paren
suffix:semicolon
)brace
multiline_comment|/* autofs4_oz_mode(): do we see the man behind the curtain?  (The&n;   processes which do manipulations for us in user space sees the raw&n;   filesystem without &quot;magic&quot;.) */
DECL|function|autofs4_oz_mode
r_static
r_inline
r_int
id|autofs4_oz_mode
c_func
(paren
r_struct
id|autofs_sb_info
op_star
id|sbi
)paren
(brace
r_return
id|sbi-&gt;catatonic
op_logical_or
id|current-&gt;pgrp
op_eq
id|sbi-&gt;oz_pgrp
suffix:semicolon
)brace
multiline_comment|/* Does a dentry have some pending activity? */
DECL|function|autofs4_ispending
r_static
r_inline
r_int
id|autofs4_ispending
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|autofs_info
op_star
id|inf
op_assign
id|autofs4_dentry_ino
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
(paren
id|dentry-&gt;d_flags
op_amp
id|DCACHE_AUTOFS_PENDING
)paren
op_logical_or
(paren
id|inf
op_ne
l_int|NULL
op_logical_and
id|inf-&gt;flags
op_amp
id|AUTOFS_INF_EXPIRING
)paren
suffix:semicolon
)brace
r_struct
id|inode
op_star
id|autofs4_get_inode
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|autofs_info
op_star
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|autofs4_init_inf
c_func
(paren
r_struct
id|autofs_sb_info
op_star
comma
id|mode_t
id|mode
)paren
suffix:semicolon
r_void
id|autofs4_free_ino
c_func
(paren
r_struct
id|autofs_info
op_star
)paren
suffix:semicolon
multiline_comment|/* Expiration */
r_int
id|is_autofs4_dentry
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|autofs4_expire_run
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|autofs_sb_info
op_star
comma
r_struct
id|autofs_packet_expire
op_star
)paren
suffix:semicolon
r_int
id|autofs4_expire_multi
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|autofs_sb_info
op_star
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/* Operations structures */
r_extern
r_struct
id|inode_operations
id|autofs4_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|autofs4_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|autofs4_root_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|autofs4_dir_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|autofs4_root_operations
suffix:semicolon
multiline_comment|/* Initializing function */
r_struct
id|super_block
op_star
id|autofs4_read_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|autofs_info
op_star
id|autofs4_init_ino
c_func
(paren
r_struct
id|autofs_info
op_star
comma
r_struct
id|autofs_sb_info
op_star
id|sbi
comma
id|mode_t
id|mode
)paren
suffix:semicolon
multiline_comment|/* Queue management functions */
DECL|enum|autofs_notify
r_enum
id|autofs_notify
(brace
DECL|enumerator|NFY_NONE
id|NFY_NONE
comma
DECL|enumerator|NFY_MOUNT
id|NFY_MOUNT
comma
DECL|enumerator|NFY_EXPIRE
id|NFY_EXPIRE
)brace
suffix:semicolon
r_int
id|autofs4_wait
c_func
(paren
r_struct
id|autofs_sb_info
op_star
comma
r_struct
id|qstr
op_star
comma
r_enum
id|autofs_notify
)paren
suffix:semicolon
r_int
id|autofs4_wait_release
c_func
(paren
r_struct
id|autofs_sb_info
op_star
comma
id|autofs_wqt_t
comma
r_int
)paren
suffix:semicolon
r_void
id|autofs4_catatonic_mode
c_func
(paren
r_struct
id|autofs_sb_info
op_star
)paren
suffix:semicolon
eof
