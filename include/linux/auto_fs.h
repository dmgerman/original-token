multiline_comment|/* -*- linux-c -*- ------------------------------------------------------- *&n; *   &n; * linux/include/linux/auto_fs.h&n; *&n; *   Copyright 1997 Transmeta Corporation - All Rights Reserved&n; *&n; * This file is part of the Linux kernel and is made available under&n; * the terms of the GNU General Public License, version 2, or at your&n; * option, any later version, incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
macro_line|#ifndef _LINUX_AUTO_FS_H
DECL|macro|_LINUX_AUTO_FS_H
mdefine_line|#define _LINUX_AUTO_FS_H
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/limits.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;asm/types.h&gt;
DECL|macro|AUTOFS_PROTO_VERSION
mdefine_line|#define AUTOFS_PROTO_VERSION 3
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
