macro_line|#ifndef _LINUX_LOOP_H
DECL|macro|_LINUX_LOOP_H
mdefine_line|#define _LINUX_LOOP_H
macro_line|#include &lt;linux/kdev_t.h&gt;
multiline_comment|/*&n; * include/linux/loop.h&n; *&n; * Written by Theodore Ts&squot;o, 3/29/93.&n; *&n; * Copyright 1993 by Theodore Ts&squot;o.  Redistribution of this file is&n; * permitted under the GNU Public License.&n; */
DECL|macro|LO_NAME_SIZE
mdefine_line|#define LO_NAME_SIZE&t;64
DECL|macro|LO_KEY_SIZE
mdefine_line|#define LO_KEY_SIZE&t;32
macro_line|#ifdef __KERNEL__
DECL|struct|loop_device
r_struct
id|loop_device
(brace
DECL|member|lo_number
r_int
id|lo_number
suffix:semicolon
DECL|member|lo_dentry
r_struct
id|dentry
op_star
id|lo_dentry
suffix:semicolon
DECL|member|lo_refcnt
r_int
id|lo_refcnt
suffix:semicolon
DECL|member|lo_device
id|kdev_t
id|lo_device
suffix:semicolon
DECL|member|lo_offset
r_int
id|lo_offset
suffix:semicolon
DECL|member|lo_encrypt_type
r_int
id|lo_encrypt_type
suffix:semicolon
DECL|member|lo_encrypt_key_size
r_int
id|lo_encrypt_key_size
suffix:semicolon
DECL|member|lo_flags
r_int
id|lo_flags
suffix:semicolon
DECL|member|transfer
r_int
(paren
op_star
id|transfer
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
r_int
id|real_block
)paren
suffix:semicolon
DECL|member|lo_name
r_char
id|lo_name
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key
r_char
id|lo_encrypt_key
(braket
id|LO_KEY_SIZE
)braket
suffix:semicolon
DECL|member|lo_init
id|__u32
id|lo_init
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|lo_key_owner
id|uid_t
id|lo_key_owner
suffix:semicolon
multiline_comment|/* Who set the key */
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
DECL|member|lo_backing_file
r_struct
id|file
op_star
id|lo_backing_file
suffix:semicolon
DECL|member|key_data
r_void
op_star
id|key_data
suffix:semicolon
DECL|member|key_reserved
r_char
id|key_reserved
(braket
l_int|48
)braket
suffix:semicolon
multiline_comment|/* for use by the filter modules */
)brace
suffix:semicolon
DECL|typedef|transfer_proc_t
r_typedef
r_int
(paren
op_star
id|transfer_proc_t
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
r_int
id|real_block
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Loop flags&n; */
DECL|macro|LO_FLAGS_DO_BMAP
mdefine_line|#define LO_FLAGS_DO_BMAP&t;0x00000001
DECL|macro|LO_FLAGS_READ_ONLY
mdefine_line|#define LO_FLAGS_READ_ONLY&t;0x00000002
multiline_comment|/* &n; * Note that this structure gets the wrong offsets when directly used&n; * from a glibc program, because glibc has a 32bit dev_t.&n; * Prevent people from shooting in their own foot.  &n; */
macro_line|#if __GLIBC__ &gt;= 2 &amp;&amp; !defined(dev_t)
macro_line|#error &quot;Wrong dev_t in loop.h&quot;
macro_line|#endif 
multiline_comment|/*&n; *&t;This uses kdev_t because glibc currently has no appropiate&n; *&t;conversion version for the loop ioctls. &n; * &t;The situation is very unpleasant&t;&n; */
DECL|struct|loop_info
r_struct
id|loop_info
(brace
DECL|member|lo_number
r_int
id|lo_number
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_device
id|dev_t
id|lo_device
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_inode
r_int
r_int
id|lo_inode
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_rdevice
id|dev_t
id|lo_rdevice
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_offset
r_int
id|lo_offset
suffix:semicolon
DECL|member|lo_encrypt_type
r_int
id|lo_encrypt_type
suffix:semicolon
DECL|member|lo_encrypt_key_size
r_int
id|lo_encrypt_key_size
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_flags
r_int
id|lo_flags
suffix:semicolon
multiline_comment|/* ioctl r/o */
DECL|member|lo_name
r_char
id|lo_name
(braket
id|LO_NAME_SIZE
)braket
suffix:semicolon
DECL|member|lo_encrypt_key
r_int
r_char
id|lo_encrypt_key
(braket
id|LO_KEY_SIZE
)braket
suffix:semicolon
multiline_comment|/* ioctl w/o */
DECL|member|lo_init
r_int
r_int
id|lo_init
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|reserved
r_char
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Loop filter types&n; */
DECL|macro|LO_CRYPT_NONE
mdefine_line|#define LO_CRYPT_NONE&t;  0
DECL|macro|LO_CRYPT_XOR
mdefine_line|#define LO_CRYPT_XOR&t;  1
DECL|macro|LO_CRYPT_DES
mdefine_line|#define LO_CRYPT_DES&t;  2
DECL|macro|LO_CRYPT_FISH2
mdefine_line|#define LO_CRYPT_FISH2    3    /* Brand new Twofish encryption */
DECL|macro|LO_CRYPT_BLOW
mdefine_line|#define LO_CRYPT_BLOW     4
DECL|macro|LO_CRYPT_CAST128
mdefine_line|#define LO_CRYPT_CAST128  5
DECL|macro|LO_CRYPT_IDEA
mdefine_line|#define LO_CRYPT_IDEA     6
DECL|macro|LO_CRYPT_DUMMY
mdefine_line|#define LO_CRYPT_DUMMY    9
DECL|macro|LO_CRYPT_SKIPJACK
mdefine_line|#define LO_CRYPT_SKIPJACK 10
DECL|macro|MAX_LO_CRYPT
mdefine_line|#define MAX_LO_CRYPT&t;20
macro_line|#ifdef __KERNEL__
multiline_comment|/* Support for loadable transfer modules */
DECL|struct|loop_func_table
r_struct
id|loop_func_table
(brace
DECL|member|number
r_int
id|number
suffix:semicolon
multiline_comment|/* filter type */
DECL|member|transfer
r_int
(paren
op_star
id|transfer
)paren
(paren
r_struct
id|loop_device
op_star
id|lo
comma
r_int
id|cmd
comma
r_char
op_star
id|raw_buf
comma
r_char
op_star
id|loop_buf
comma
r_int
id|size
comma
r_int
id|real_block
)paren
suffix:semicolon
DECL|member|init
r_int
(paren
op_star
id|init
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_struct
id|loop_info
op_star
)paren
suffix:semicolon
multiline_comment|/* release is called from loop_unregister_transfer or clr_fd */
DECL|member|release
r_int
(paren
op_star
id|release
)paren
(paren
r_struct
id|loop_device
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|loop_device
op_star
comma
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* lock and unlock manage the module use counts */
DECL|member|lock
r_void
(paren
op_star
id|lock
)paren
(paren
r_struct
id|loop_device
op_star
)paren
suffix:semicolon
DECL|member|unlock
r_void
(paren
op_star
id|unlock
)paren
(paren
r_struct
id|loop_device
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_int
id|loop_register_transfer
c_func
(paren
r_struct
id|loop_func_table
op_star
id|funcs
)paren
suffix:semicolon
r_int
id|loop_unregister_transfer
c_func
(paren
r_int
id|number
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * IOCTL commands --- we will commandeer 0x4C (&squot;L&squot;)&n; */
DECL|macro|LOOP_SET_FD
mdefine_line|#define LOOP_SET_FD&t;0x4C00
DECL|macro|LOOP_CLR_FD
mdefine_line|#define LOOP_CLR_FD&t;0x4C01
DECL|macro|LOOP_SET_STATUS
mdefine_line|#define LOOP_SET_STATUS&t;0x4C02
DECL|macro|LOOP_GET_STATUS
mdefine_line|#define LOOP_GET_STATUS&t;0x4C03
macro_line|#endif
eof
