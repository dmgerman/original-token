multiline_comment|/*&n; *  types.h&n; *  This file defines four things:&n; *   - generic platform independent fixed-size types (e.g. ntfs_u32)&n; *   - specific fixed-size types (e.g. ntfs_offset_t)&n; *   - macros that read and write those types from and to byte arrays&n; *   - types derived from OS specific ones&n; *&n; *  Copyright (C) 1996 Martin von L&#xfffd;wis&n; */
macro_line|#ifdef NTFS_IN_LINUX_KERNEL
multiline_comment|/* get installed types if we compile the kernel*/
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#endif
macro_line|#if defined(i386) || defined(__i386__)
multiline_comment|/* unsigned integral types */
macro_line|#ifndef NTFS_INTEGRAL_TYPES
DECL|macro|NTFS_INTEGRAL_TYPES
mdefine_line|#define NTFS_INTEGRAL_TYPES
DECL|typedef|ntfs_u8
r_typedef
r_int
r_char
id|ntfs_u8
suffix:semicolon
DECL|typedef|ntfs_u16
r_typedef
r_int
r_int
id|ntfs_u16
suffix:semicolon
DECL|typedef|ntfs_u32
r_typedef
r_int
r_int
id|ntfs_u32
suffix:semicolon
DECL|typedef|ntfs_u64
r_typedef
r_int
r_int
r_int
id|ntfs_u64
suffix:semicolon
macro_line|#endif
multiline_comment|/* unicode character type */
macro_line|#ifndef NTFS_WCHAR_T
DECL|macro|NTFS_WCHAR_T
mdefine_line|#define NTFS_WCHAR_T
DECL|typedef|ntfs_wchar_t
r_typedef
r_int
r_int
id|ntfs_wchar_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* file offset */
macro_line|#ifndef NTFS_OFFSET_T
DECL|macro|NTFS_OFFSET_T
mdefine_line|#define NTFS_OFFSET_T
DECL|typedef|ntfs_offset_t
r_typedef
r_int
r_int
r_int
id|ntfs_offset_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* UTC */
macro_line|#ifndef NTFS_TIME64_T
DECL|macro|NTFS_TIME64_T
mdefine_line|#define NTFS_TIME64_T
DECL|typedef|ntfs_time64_t
r_typedef
r_int
r_int
r_int
id|ntfs_time64_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* This is really unsigned long long. So we support only volumes up to 2 TB */
macro_line|#ifndef NTFS_CLUSTER_T
DECL|macro|NTFS_CLUSTER_T
mdefine_line|#define NTFS_CLUSTER_T
DECL|typedef|ntfs_cluster_t
r_typedef
r_int
r_int
id|ntfs_cluster_t
suffix:semicolon
macro_line|#endif
multiline_comment|/* Macros reading unsigned integers from a byte pointer */
multiline_comment|/* these should work for all little endian machines */
DECL|macro|NTFS_GETU8
mdefine_line|#define NTFS_GETU8(p)      (*(ntfs_u8*)(p))
DECL|macro|NTFS_GETU16
mdefine_line|#define NTFS_GETU16(p)     (*(ntfs_u16*)(p))
DECL|macro|NTFS_GETU24
mdefine_line|#define NTFS_GETU24(p)     (NTFS_GETU32(p) &amp; 0xFFFFFF)
DECL|macro|NTFS_GETU32
mdefine_line|#define NTFS_GETU32(p)     (*(ntfs_u32*)(p))
DECL|macro|NTFS_GETU64
mdefine_line|#define NTFS_GETU64(p)     (*(ntfs_u64*)(p))
multiline_comment|/* Macros writing unsigned integers */
DECL|macro|NTFS_PUTU8
mdefine_line|#define NTFS_PUTU8(p,v)      (*(ntfs_u8*)(p))=(v)
DECL|macro|NTFS_PUTU16
mdefine_line|#define NTFS_PUTU16(p,v)     (*(ntfs_u16*)(p))=(v)
DECL|macro|NTFS_PUTU24
mdefine_line|#define NTFS_PUTU24(p,v)     NTFS_PUTU16(p,(v) &amp; 0xFFFF);&bslash;&n;                             NTFS_PUTU8(((char*)p)+2,(v)&gt;&gt;16)
DECL|macro|NTFS_PUTU32
mdefine_line|#define NTFS_PUTU32(p,v)     (*(ntfs_u32*)(p))=(v)
DECL|macro|NTFS_PUTU64
mdefine_line|#define NTFS_PUTU64(p,v)     (*(ntfs_u64*)(p))=(v)
multiline_comment|/* Macros reading signed integers, returning int */
DECL|macro|NTFS_GETS8
mdefine_line|#define NTFS_GETS8(p)        ((int)(*(char*)(p)))
DECL|macro|NTFS_GETS16
mdefine_line|#define NTFS_GETS16(p)       ((int)(*(short*)(p)))
DECL|macro|NTFS_GETS24
mdefine_line|#define NTFS_GETS24(p)       (NTFS_GETU24(p) &lt; 0x800000 ? (int)NTFS_GETU24(p) : (int)(NTFS_GETU24(p) | 0xFF000000))
DECL|macro|NTFS_PUTS8
mdefine_line|#define NTFS_PUTS8(p,v)      NTFS_PUTU8(p,v)
DECL|macro|NTFS_PUTS16
mdefine_line|#define NTFS_PUTS16(p,v)     NTFS_PUTU16(p,v)
DECL|macro|NTFS_PUTS24
mdefine_line|#define NTFS_PUTS24(p,v)     NTFS_PUTU24(p,v)
DECL|macro|NTFS_PUTS32
mdefine_line|#define NTFS_PUTS32(p,v)     NTFS_PUTU32(p,v)
macro_line|#else
macro_line|#error Put your machine description here
macro_line|#endif
multiline_comment|/* architecture independent macros */
multiline_comment|/* PUTU32 would not clear all bytes */
DECL|macro|NTFS_PUTINUM
mdefine_line|#define NTFS_PUTINUM(p,i)    NTFS_PUTU64(p,i-&gt;i_number);&bslash;&n;                             NTFS_PUTU16(((char*)p)+6,i-&gt;sequence_number)
multiline_comment|/* system dependent types */
macro_line|#ifdef __linux__
multiline_comment|/* We always need kernel types, because glibc makes them of different size */
macro_line|#include &lt;asm/posix_types.h&gt;
multiline_comment|/* Avoid a type redefinition with future include of glibc &lt;stdlib.h&gt; */
DECL|macro|__FD_ZERO
macro_line|#undef __FD_ZERO
DECL|macro|__FD_SET
macro_line|#undef __FD_SET
DECL|macro|__FD_CLR
macro_line|#undef __FD_CLR
DECL|macro|__FD_ISSET
macro_line|#undef __FD_ISSET
macro_line|#ifndef NTMODE_T
DECL|macro|NTMODE_T
mdefine_line|#define NTMODE_T
DECL|typedef|ntmode_t
r_typedef
id|__kernel_mode_t
id|ntmode_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_UID_T
DECL|macro|NTFS_UID_T
mdefine_line|#define NTFS_UID_T
DECL|typedef|ntfs_uid_t
r_typedef
id|__kernel_uid_t
id|ntfs_uid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_GID_T
DECL|macro|NTFS_GID_T
mdefine_line|#define NTFS_GID_T
DECL|typedef|ntfs_gid_t
r_typedef
id|__kernel_gid_t
id|ntfs_gid_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_SIZE_T
DECL|macro|NTFS_SIZE_T
mdefine_line|#define NTFS_SIZE_T
DECL|typedef|ntfs_size_t
r_typedef
id|__kernel_size_t
id|ntfs_size_t
suffix:semicolon
macro_line|#endif
macro_line|#ifndef NTFS_TIME_T
DECL|macro|NTFS_TIME_T
mdefine_line|#define NTFS_TIME_T
DECL|typedef|ntfs_time_t
r_typedef
id|__kernel_time_t
id|ntfs_time_t
suffix:semicolon
macro_line|#endif
macro_line|#else
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/stat.h&gt;
DECL|typedef|ntmode_t
r_typedef
id|mode_t
id|ntmode_t
suffix:semicolon
DECL|typedef|ntfs_uid_t
r_typedef
id|uid_t
id|ntfs_uid_t
suffix:semicolon
DECL|typedef|ntfs_gid_t
r_typedef
id|gid_t
id|ntfs_gid_t
suffix:semicolon
DECL|typedef|ntfs_size_t
r_typedef
r_int
id|ntfs_size_t
suffix:semicolon
DECL|typedef|ntfs_time_t
r_typedef
id|time_t
id|ntfs_time_t
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
