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
multiline_comment|/*&n; * Set/Get values in SMB-byte order&n; */
DECL|macro|ARCH
mdefine_line|#define ARCH i386
macro_line|#if (ARCH == i386)
DECL|macro|BVAL
mdefine_line|#define BVAL(p,off)      (*((byte  *)(((void *)p)+off)))
DECL|macro|WVAL
mdefine_line|#define WVAL(p,off)      (*((word  *)(((void *)p)+off)))
DECL|macro|DVAL
mdefine_line|#define DVAL(p,off)      (*((dword *)(((void *)p)+off)))
DECL|macro|BSET
mdefine_line|#define BSET(p,off,new)  (*((byte  *)(((void *)p)+off))=(new))
DECL|macro|WSET
mdefine_line|#define WSET(p,off,new)  (*((word  *)(((void *)p)+off))=(new))
DECL|macro|DSET
mdefine_line|#define DSET(p,off,new)  (*((dword *)(((void *)p)+off))=(new))
multiline_comment|/* where to find the base of the SMB packet proper */
DECL|macro|smb_base
mdefine_line|#define smb_base(buf) ((byte *)(((byte *)(buf))+4))
macro_line|#else
macro_line|#error &quot;Currently only on 386, sorry&quot;
macro_line|#endif
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
DECL|member|atime
DECL|member|mtime
id|time_t
id|atime
comma
id|mtime
comma
multiline_comment|/* Times, as seen by the server, normalized */
DECL|member|ctime
id|ctime
suffix:semicolon
multiline_comment|/* to UTC. The ugly conversion happens in */
multiline_comment|/* proc.c */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* File size. */
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
DECL|member|path
r_char
op_star
id|path
suffix:semicolon
multiline_comment|/* Complete path, MS-DOS notation, with &squot;&bslash;&squot; */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* Namelength. */
)brace
suffix:semicolon
macro_line|#endif  /* __KERNEL__ */
macro_line|#endif  /* _LINUX_SMB_H */
eof
