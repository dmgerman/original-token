multiline_comment|/* -*- linux-c -*- --------------------------------------------------------- *&n; *&n; * linux/include/linux/auto_fs.h&n; *&n; *  Copyright 1997 Transmeta Corporation -- All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ------------------------------------------------------------------------- */
macro_line|#ifndef _LINUX_AUTO_FS_H
DECL|macro|_LINUX_AUTO_FS_H
mdefine_line|#define _LINUX_AUTO_FS_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|AUTOFS_PROTO_VERSION
mdefine_line|#define AUTOFS_PROTO_VERSION 2
DECL|enum|autofs_packet_type
r_enum
id|autofs_packet_type
(brace
DECL|enumerator|autofs_ptype_missing
id|autofs_ptype_missing
comma
multiline_comment|/* Missing entry (create wait queue) */
multiline_comment|/* ...need more in the future... */
)brace
suffix:semicolon
DECL|struct|autofs_packet_hdr
r_struct
id|autofs_packet_hdr
(brace
DECL|member|proto_version
r_int
id|proto_version
suffix:semicolon
multiline_comment|/* Protocol version */
DECL|member|type
r_enum
id|autofs_packet_type
id|type
suffix:semicolon
multiline_comment|/* Type of packet */
)brace
suffix:semicolon
DECL|struct|autofs_packet_missing
r_struct
id|autofs_packet_missing
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
suffix:semicolon
DECL|member|wait_queue_token
r_int
r_int
id|wait_queue_token
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
id|NAME_MAX
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_IOC_READY
mdefine_line|#define AUTOFS_IOC_READY     _IO(0x93,0x60)
DECL|macro|AUTOFS_IOC_FAIL
mdefine_line|#define AUTOFS_IOC_FAIL      _IO(0x93,0x61)
DECL|macro|AUTOFS_IOC_CATATONIC
mdefine_line|#define AUTOFS_IOC_CATATONIC _IO(0x93,0x62)
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; 0x20100
macro_line|#include &lt;asm/segment.h&gt;
DECL|macro|copy_to_user
mdefine_line|#define copy_to_user&t;memcpy_tofs
DECL|macro|copy_from_user
mdefine_line|#define copy_from_user&t;memcpy_fromfs
macro_line|#else
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|register_symtab
mdefine_line|#define register_symtab(x)&t;do { } while (0)
macro_line|#endif
macro_line|#ifndef DPRINTK
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D) printk D;
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(D)
macro_line|#endif
macro_line|#endif
DECL|macro|AUTOFS_SUPER_MAGIC
mdefine_line|#define AUTOFS_SUPER_MAGIC 0x0187
multiline_comment|/* Structures associated with the root directory hash */
DECL|macro|AUTOFS_HASH_SIZE
mdefine_line|#define AUTOFS_HASH_SIZE 67
DECL|typedef|autofs_hash_t
r_typedef
id|u32
id|autofs_hash_t
suffix:semicolon
multiline_comment|/* Type returned by autofs_hash() */
DECL|struct|autofs_dir_ent
r_struct
id|autofs_dir_ent
(brace
DECL|member|hash
id|autofs_hash_t
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
DECL|member|expiry
id|time_t
id|expiry
suffix:semicolon
multiline_comment|/* Reserved for use in failed-lookup cache */
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
id|autofs_hash_t
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
DECL|struct|autofs_sb_info
r_struct
id|autofs_sb_info
(brace
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
multiline_comment|/* autofs_oz_mode(): do we see the man behind the curtain? */
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
multiline_comment|/* Init function */
r_int
id|init_autofs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Hash operations */
id|autofs_hash_t
id|autofs_hash
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
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
id|autofs_hash_t
comma
r_const
r_char
op_star
comma
r_int
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
id|autofs_hash_t
comma
r_const
r_char
op_star
comma
r_int
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
mdefine_line|#define autofs_say(n,l)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AUTO_FS_H */
eof
