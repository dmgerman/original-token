multiline_comment|/*&n; *  smb.h&n; *&n; *  Copyright (C) 1995 by Paal-Kr. Engstad and Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_SMB_H
DECL|macro|_LINUX_SMB_H
mdefine_line|#define _LINUX_SMB_H
DECL|macro|SMB_PORT
mdefine_line|#define SMB_PORT 139
DECL|macro|SMB_MAXNAMELEN
mdefine_line|#define SMB_MAXNAMELEN 255
DECL|macro|SMB_MAXPATHLEN
mdefine_line|#define SMB_MAXPATHLEN 1024
DECL|macro|SMB_DEF_MAX_XMIT
mdefine_line|#define SMB_DEF_MAX_XMIT 32768
multiline_comment|/* Allocate max. 1 page */
DECL|macro|TRANS2_MAX_TRANSFER
mdefine_line|#define TRANS2_MAX_TRANSFER (4096-17)
macro_line|#include &lt;asm/types.h&gt;
macro_line|#ifdef __KERNEL__
DECL|typedef|byte
r_typedef
id|u8
id|byte
suffix:semicolon
DECL|typedef|word
r_typedef
id|u16
id|word
suffix:semicolon
DECL|typedef|dword
r_typedef
id|u32
id|dword
suffix:semicolon
macro_line|#else
DECL|typedef|byte
r_typedef
r_int
r_char
id|byte
suffix:semicolon
DECL|typedef|word
r_typedef
r_int
r_int
id|word
suffix:semicolon
DECL|typedef|dword
r_typedef
r_int
r_int
id|dword
suffix:semicolon
macro_line|#endif
multiline_comment|/* The following macros have been taken directly from Samba. Thanks,&n;   Andrew! */
DECL|macro|CAREFUL_ALIGNMENT
macro_line|#undef CAREFUL_ALIGNMENT
multiline_comment|/* we know that the 386 can handle misalignment and has the &quot;right&quot; &n;   byteorder */
macro_line|#if defined(__i386__)
DECL|macro|CAREFUL_ALIGNMENT
mdefine_line|#define CAREFUL_ALIGNMENT 0
macro_line|#endif
macro_line|#ifndef CAREFUL_ALIGNMENT
DECL|macro|CAREFUL_ALIGNMENT
mdefine_line|#define CAREFUL_ALIGNMENT 1
macro_line|#endif
DECL|macro|BVAL
mdefine_line|#define BVAL(buf,pos) (((u8 *)(buf))[pos])
DECL|macro|PVAL
mdefine_line|#define PVAL(buf,pos) ((unsigned)BVAL(buf,pos))
DECL|macro|BSET
mdefine_line|#define BSET(buf,pos,val) (BVAL(buf,pos) = (val))
macro_line|#if CAREFUL_ALIGNMENT
DECL|macro|WVAL
mdefine_line|#define WVAL(buf,pos) (PVAL(buf,pos)|PVAL(buf,(pos)+1)&lt;&lt;8)
DECL|macro|DVAL
mdefine_line|#define DVAL(buf,pos) (WVAL(buf,pos)|WVAL(buf,(pos)+2)&lt;&lt;16)
DECL|macro|SSVALX
mdefine_line|#define SSVALX(buf,pos,val) (BVAL(buf,pos)=(val)&amp;0xFF,BVAL(buf,pos+1)=(val)&gt;&gt;8)
DECL|macro|SIVALX
mdefine_line|#define SIVALX(buf,pos,val) (SSVALX(buf,pos,val&amp;0xFFFF),SSVALX(buf,pos+2,val&gt;&gt;16))
DECL|macro|WSET
mdefine_line|#define WSET(buf,pos,val) { word __val = (val); &bslash;&n;&t;SSVALX((buf),(pos),((word)(__val))); }
DECL|macro|DSET
mdefine_line|#define DSET(buf,pos,val) { dword __val = (val); &bslash;&n;&t;SIVALX((buf),(pos),((dword)(__val))); }
macro_line|#else
multiline_comment|/* this handles things for architectures like the 386 that can handle&n;   alignment errors */
multiline_comment|/*&n;   WARNING: This section is dependent on the length of word and dword&n;   being correct &n;*/
DECL|macro|WVAL
mdefine_line|#define WVAL(buf,pos) (*(word *)((char *)(buf) + (pos)))
DECL|macro|DVAL
mdefine_line|#define DVAL(buf,pos) (*(dword *)((char *)(buf) + (pos)))
DECL|macro|WSET
mdefine_line|#define WSET(buf,pos,val) WVAL(buf,pos)=((word)(val))
DECL|macro|DSET
mdefine_line|#define DSET(buf,pos,val) DVAL(buf,pos)=((dword)(val))
macro_line|#endif
multiline_comment|/* where to find the base of the SMB packet proper */
DECL|macro|smb_base
mdefine_line|#define smb_base(buf) ((byte *)(((byte *)(buf))+4))
DECL|macro|LANMAN1
mdefine_line|#define LANMAN1
DECL|macro|LANMAN2
mdefine_line|#define LANMAN2
DECL|macro|NT1
mdefine_line|#define NT1
DECL|enum|smb_protocol
r_enum
id|smb_protocol
(brace
DECL|enumerator|PROTOCOL_NONE
id|PROTOCOL_NONE
comma
DECL|enumerator|PROTOCOL_CORE
id|PROTOCOL_CORE
comma
DECL|enumerator|PROTOCOL_COREPLUS
id|PROTOCOL_COREPLUS
comma
DECL|enumerator|PROTOCOL_LANMAN1
id|PROTOCOL_LANMAN1
comma
DECL|enumerator|PROTOCOL_LANMAN2
id|PROTOCOL_LANMAN2
comma
DECL|enumerator|PROTOCOL_NT1
id|PROTOCOL_NT1
)brace
suffix:semicolon
DECL|enum|smb_case_hndl
r_enum
id|smb_case_hndl
(brace
DECL|enumerator|CASE_DEFAULT
id|CASE_DEFAULT
comma
DECL|enumerator|CASE_LOWER
id|CASE_LOWER
comma
DECL|enumerator|CASE_UPPER
id|CASE_UPPER
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|enum|smb_conn_state
r_enum
id|smb_conn_state
(brace
DECL|enumerator|CONN_VALID
id|CONN_VALID
comma
multiline_comment|/* everything&squot;s fine */
DECL|enumerator|CONN_INVALID
id|CONN_INVALID
comma
multiline_comment|/* Something went wrong, but did not&n;                                   try to reconnect yet. */
DECL|enumerator|CONN_RETRIED
id|CONN_RETRIED
multiline_comment|/* Tried a reconnection, but was refused */
)brace
suffix:semicolon
DECL|struct|smb_dskattr
r_struct
id|smb_dskattr
(brace
DECL|member|total
id|word
id|total
suffix:semicolon
DECL|member|allocblocks
id|word
id|allocblocks
suffix:semicolon
DECL|member|blocksize
id|word
id|blocksize
suffix:semicolon
DECL|member|free
id|word
id|free
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Contains all relevant data on a SMB networked file.&n; */
DECL|struct|smb_dirent
r_struct
id|smb_dirent
(brace
DECL|member|f_ino
r_int
r_int
id|f_ino
suffix:semicolon
DECL|member|f_mode
id|umode_t
id|f_mode
suffix:semicolon
DECL|member|f_nlink
id|nlink_t
id|f_nlink
suffix:semicolon
DECL|member|f_uid
id|uid_t
id|f_uid
suffix:semicolon
DECL|member|f_gid
id|gid_t
id|f_gid
suffix:semicolon
DECL|member|f_rdev
id|kdev_t
id|f_rdev
suffix:semicolon
DECL|member|f_size
id|off_t
id|f_size
suffix:semicolon
DECL|member|f_atime
id|time_t
id|f_atime
suffix:semicolon
DECL|member|f_mtime
id|time_t
id|f_mtime
suffix:semicolon
DECL|member|f_ctime
id|time_t
id|f_ctime
suffix:semicolon
DECL|member|f_blksize
r_int
r_int
id|f_blksize
suffix:semicolon
DECL|member|f_blocks
r_int
r_int
id|f_blocks
suffix:semicolon
DECL|member|opened
r_int
id|opened
suffix:semicolon
multiline_comment|/* is it open on the fileserver? */
DECL|member|fileid
id|word
id|fileid
suffix:semicolon
multiline_comment|/* What id to handle a file with? */
DECL|member|attr
id|word
id|attr
suffix:semicolon
multiline_comment|/* Attribute fields, DOS value */
DECL|member|access
r_int
r_int
id|access
suffix:semicolon
multiline_comment|/* Access bits. */
DECL|member|f_pos
r_int
r_int
id|f_pos
suffix:semicolon
multiline_comment|/* File position. (For readdir.) */
DECL|member|name
r_int
r_char
id|name
(braket
id|SMB_MAXNAMELEN
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* namelength */
)brace
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif  /* _LINUX_SMB_H */
eof
