multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *   &n; * linux/include/linux/auto_fs.h&n; *&n; *   Copyright 1997 Transmeta Corporation - All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
macro_line|#ifndef _LINUX_AUTO_FS_H
DECL|macro|_LINUX_AUTO_FS_H
mdefine_line|#define _LINUX_AUTO_FS_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|AUTOFS_MIN_PROTO_VERSION
mdefine_line|#define AUTOFS_MIN_PROTO_VERSION 3&t;/* Min version we support */
DECL|macro|AUTOFS_PROTO_VERSION
mdefine_line|#define AUTOFS_PROTO_VERSION 4&t;&t;/* Current version */
multiline_comment|/*&n; * Architectures where both 32- and 64-bit binaries can be executed&n; * on 64-bit kernels need this.  This keeps the structure format&n; * uniform, and makes sure the wait_queue_token isn&squot;t too big to be&n; * passed back down to the kernel.&n; *&n; * This assumes that on these architectures:&n; * mode     32 bit    64 bit&n; * -------------------------&n; * int      32 bit    32 bit&n; * long     32 bit    64 bit&n; *&n; * If so, 32-bit user-space code should be backwards compatible.&n; */
macro_line|#if defined(__sparc__) || defined(__mips__)
DECL|typedef|autofs_wqt_t
r_typedef
r_int
r_int
id|autofs_wqt_t
suffix:semicolon
macro_line|#else
DECL|typedef|autofs_wqt_t
r_typedef
r_int
r_int
id|autofs_wqt_t
suffix:semicolon
macro_line|#endif
DECL|enum|autofs_packet_type
r_enum
id|autofs_packet_type
(brace
DECL|enumerator|autofs_ptype_missing
id|autofs_ptype_missing
comma
multiline_comment|/* Missing entry (mount request) */
DECL|enumerator|autofs_ptype_expire
id|autofs_ptype_expire
comma
multiline_comment|/* Expire entry (umount request) */
DECL|enumerator|autofs_ptype_expire_multi
id|autofs_ptype_expire_multi
comma
multiline_comment|/* Expire entry (umount request) */
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
id|autofs_wqt_t
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
multiline_comment|/* v3 expire (via ioctl) */
DECL|struct|autofs_packet_expire
r_struct
id|autofs_packet_expire
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
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
multiline_comment|/* v4 multi expire (via pipe) */
DECL|struct|autofs_packet_expire_multi
r_struct
id|autofs_packet_expire_multi
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
suffix:semicolon
DECL|member|wait_queue_token
id|autofs_wqt_t
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
DECL|union|autofs_packet_union
r_union
id|autofs_packet_union
(brace
DECL|member|hdr
r_struct
id|autofs_packet_hdr
id|hdr
suffix:semicolon
DECL|member|missing
r_struct
id|autofs_packet_missing
id|missing
suffix:semicolon
DECL|member|expire
r_struct
id|autofs_packet_expire
id|expire
suffix:semicolon
DECL|member|expire_multi
r_struct
id|autofs_packet_expire_multi
id|expire_multi
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|AUTOFS_IOC_READY
mdefine_line|#define AUTOFS_IOC_READY      _IO(0x93,0x60)
DECL|macro|AUTOFS_IOC_FAIL
mdefine_line|#define AUTOFS_IOC_FAIL       _IO(0x93,0x61)
DECL|macro|AUTOFS_IOC_CATATONIC
mdefine_line|#define AUTOFS_IOC_CATATONIC  _IO(0x93,0x62)
DECL|macro|AUTOFS_IOC_PROTOVER
mdefine_line|#define AUTOFS_IOC_PROTOVER   _IOR(0x93,0x63,int)
DECL|macro|AUTOFS_IOC_SETTIMEOUT
mdefine_line|#define AUTOFS_IOC_SETTIMEOUT _IOWR(0x93,0x64,unsigned long)
DECL|macro|AUTOFS_IOC_EXPIRE
mdefine_line|#define AUTOFS_IOC_EXPIRE     _IOR(0x93,0x65,struct autofs_packet_expire)
DECL|macro|AUTOFS_IOC_EXPIRE_MULTI
mdefine_line|#define AUTOFS_IOC_EXPIRE_MULTI _IOW(0x93,0x66,int)
macro_line|#ifdef __KERNEL__
multiline_comment|/* Init function */
r_int
id|init_autofs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_AUTO_FS_H */
eof
