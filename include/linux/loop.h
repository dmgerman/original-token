macro_line|#ifndef _LINUX_LOOP_H
DECL|macro|_LINUX_LOOP_H
mdefine_line|#define _LINUX_LOOP_H
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
macro_line|#ifdef DES_AVAILABLE
DECL|member|lo_des_key
id|des_key_schedule
id|lo_des_key
suffix:semicolon
DECL|member|lo_des_init
r_int
r_int
id|lo_des_init
(braket
l_int|2
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef IDEA_AVAILABLE
DECL|member|lo_idea_en_key
id|idea_key
id|lo_idea_en_key
suffix:semicolon
DECL|member|lo_idea_de_key
id|idea_key
id|lo_idea_de_key
suffix:semicolon
macro_line|#endif
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
)paren
suffix:semicolon
multiline_comment|/*&n; * Loop flags&n; */
DECL|macro|LO_FLAGS_DO_BMAP
mdefine_line|#define LO_FLAGS_DO_BMAP&t;0x00000001
DECL|macro|LO_FLAGS_READ_ONLY
mdefine_line|#define LO_FLAGS_READ_ONLY&t;0x00000002
macro_line|#endif /* __KERNEL__ */
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
multiline_comment|/*&n; * Loop encryption types --- LO_CRYPT_IDEA isn&squot;t supported yet&n; */
DECL|macro|LO_CRYPT_NONE
mdefine_line|#define LO_CRYPT_NONE&t;0
DECL|macro|LO_CRYPT_XOR
mdefine_line|#define LO_CRYPT_XOR&t;1
DECL|macro|LO_CRYPT_DES
mdefine_line|#define LO_CRYPT_DES&t;2
DECL|macro|LO_CRYPT_IDEA
mdefine_line|#define LO_CRYPT_IDEA&t;3
DECL|macro|MAX_LO_CRYPT
mdefine_line|#define MAX_LO_CRYPT&t;4
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
