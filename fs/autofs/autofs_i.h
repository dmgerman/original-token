multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *   &n; * linux/fs/autofs/autofs_i.h&n; *&n; *   Copyright 1997 Transmeta Corporation - All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/* Internal header file for autofs */
macro_line|#include &lt;linux/auto_fs.h&gt;
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
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D) (printk D)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D) ((void)0)
macro_line|#endif
DECL|macro|AUTOFS_SUPER_MAGIC
mdefine_line|#define AUTOFS_SUPER_MAGIC 0x0187
multiline_comment|/*&n; * If the daemon returns a negative response (AUTOFS_IOC_FAIL) then the&n; * kernel will keep the negative response cached for up to the time given&n; * here, although the time can be shorter if the kernel throws the dcache&n; * entry away.  This probably should be settable from user space.&n; */
DECL|macro|AUTOFS_NEGATIVE_TIMEOUT
mdefine_line|#define AUTOFS_NEGATIVE_TIMEOUT (60*HZ)&t;/* 1 minute */
multiline_comment|/* Structures associated with the root directory hash table */
DECL|macro|AUTOFS_HASH_SIZE
mdefine_line|#define AUTOFS_HASH_SIZE 67
DECL|struct|autofs_dir_ent
r_struct
id|autofs_dir_ent
(brace
DECL|member|hash
r_int
id|hash
suffix:semicolon
DECL|member|next
r_struct
id|autofs_dir_ent
op_star
id|next
suffix:semicolon
DECL|member|back
r_struct
id|autofs_dir_ent
op_star
op_star
id|back
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|ino
id|ino_t
id|ino
suffix:semicolon
multiline_comment|/* The following entries are for the expiry system */
DECL|member|last_usage
r_int
r_int
id|last_usage
suffix:semicolon
DECL|member|exp_next
r_struct
id|autofs_dir_ent
op_star
id|exp_next
suffix:semicolon
DECL|member|exp_prev
r_struct
id|autofs_dir_ent
op_star
id|exp_prev
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|autofs_dirhash
r_struct
id|autofs_dirhash
(brace
DECL|member|h
r_struct
id|autofs_dir_ent
op_star
id|h
(braket
id|AUTOFS_HASH_SIZE
)braket
suffix:semicolon
DECL|member|expiry_head
r_struct
id|autofs_dir_ent
id|expiry_head
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|autofs_wait_queue
r_struct
id|autofs_wait_queue
(brace
DECL|member|wait_queue_token
r_int
r_int
id|wait_queue_token
suffix:semicolon
DECL|member|queue
r_struct
id|wait_queue
op_star
id|queue
suffix:semicolon
DECL|member|next
r_struct
id|autofs_wait_queue
op_star
id|next
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
DECL|struct|autofs_symlink
r_struct
id|autofs_symlink
(brace
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
DECL|member|mtime
id|time_t
id|mtime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_MAX_SYMLINKS
mdefine_line|#define AUTOFS_MAX_SYMLINKS 256
DECL|macro|AUTOFS_ROOT_INO
mdefine_line|#define AUTOFS_ROOT_INO      1
DECL|macro|AUTOFS_FIRST_SYMLINK
mdefine_line|#define AUTOFS_FIRST_SYMLINK 2
DECL|macro|AUTOFS_FIRST_DIR_INO
mdefine_line|#define AUTOFS_FIRST_DIR_INO (AUTOFS_FIRST_SYMLINK+AUTOFS_MAX_SYMLINKS)
DECL|macro|AUTOFS_SYMLINK_BITMAP_LEN
mdefine_line|#define AUTOFS_SYMLINK_BITMAP_LEN ((AUTOFS_MAX_SYMLINKS+31)/32)
macro_line|#ifndef END_OF_TIME
DECL|macro|END_OF_TIME
mdefine_line|#define END_OF_TIME ((time_t)((unsigned long)((time_t)(~0UL)) &gt;&gt; 1))
macro_line|#endif
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
DECL|member|exp_timeout
r_int
r_int
id|exp_timeout
suffix:semicolon
DECL|member|next_dir_ino
id|ino_t
id|next_dir_ino
suffix:semicolon
DECL|member|queues
r_struct
id|autofs_wait_queue
op_star
id|queues
suffix:semicolon
multiline_comment|/* Wait queue pointer */
DECL|member|dirhash
r_struct
id|autofs_dirhash
id|dirhash
suffix:semicolon
multiline_comment|/* Root directory hash */
DECL|member|symlink
r_struct
id|autofs_symlink
id|symlink
(braket
id|AUTOFS_MAX_SYMLINKS
)braket
suffix:semicolon
DECL|member|symlink_bitmap
id|u32
id|symlink_bitmap
(braket
id|AUTOFS_SYMLINK_BITMAP_LEN
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* autofs_oz_mode(): do we see the man behind the curtain?  (The&n;   processes which do manipulations for us in user space sees the raw&n;   filesystem without &quot;magic&quot;.) */
DECL|function|autofs_oz_mode
r_static
r_inline
r_int
id|autofs_oz_mode
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
multiline_comment|/* Hash operations */
r_void
id|autofs_initialize_hash
c_func
(paren
r_struct
id|autofs_dirhash
op_star
)paren
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|autofs_hash_lookup
c_func
(paren
r_const
r_struct
id|autofs_dirhash
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_void
id|autofs_hash_insert
c_func
(paren
r_struct
id|autofs_dirhash
op_star
comma
r_struct
id|autofs_dir_ent
op_star
)paren
suffix:semicolon
r_void
id|autofs_hash_delete
c_func
(paren
r_struct
id|autofs_dir_ent
op_star
)paren
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|autofs_hash_enum
c_func
(paren
r_const
r_struct
id|autofs_dirhash
op_star
comma
id|off_t
op_star
)paren
suffix:semicolon
r_void
id|autofs_hash_nuke
c_func
(paren
r_struct
id|autofs_dirhash
op_star
)paren
suffix:semicolon
multiline_comment|/* Expiration-handling functions */
r_void
id|autofs_update_usage
c_func
(paren
r_struct
id|autofs_dirhash
op_star
comma
r_struct
id|autofs_dir_ent
op_star
)paren
suffix:semicolon
r_struct
id|autofs_dir_ent
op_star
id|autofs_expire
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|autofs_sb_info
op_star
)paren
suffix:semicolon
multiline_comment|/* Operations structures */
r_extern
r_struct
id|inode_operations
id|autofs_root_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|autofs_symlink_inode_operations
suffix:semicolon
r_extern
r_struct
id|inode_operations
id|autofs_dir_inode_operations
suffix:semicolon
multiline_comment|/* Initializing function */
r_struct
id|super_block
op_star
id|autofs_read_super
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
multiline_comment|/* Queue management functions */
r_int
id|autofs_wait
c_func
(paren
r_struct
id|autofs_sb_info
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
r_int
id|autofs_wait_release
c_func
(paren
r_struct
id|autofs_sb_info
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|autofs_catatonic_mode
c_func
(paren
r_struct
id|autofs_sb_info
op_star
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
r_void
id|autofs_say
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|len
)paren
suffix:semicolon
macro_line|#else
DECL|macro|autofs_say
mdefine_line|#define autofs_say(n,l) ((void)0)
macro_line|#endif
eof
