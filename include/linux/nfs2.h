multiline_comment|/*&n; * NFS protocol definitions&n; *&n; * This file contains constants for Version 2 of the protocol.&n; */
macro_line|#ifndef _LINUX_NFS2_H
DECL|macro|_LINUX_NFS2_H
mdefine_line|#define _LINUX_NFS2_H
DECL|macro|NFS2_PORT
mdefine_line|#define NFS2_PORT&t;2049
DECL|macro|NFS2_MAXDATA
mdefine_line|#define NFS2_MAXDATA&t;8192
DECL|macro|NFS2_MAXPATHLEN
mdefine_line|#define NFS2_MAXPATHLEN&t;1024
DECL|macro|NFS2_MAXNAMLEN
mdefine_line|#define NFS2_MAXNAMLEN&t;255
DECL|macro|NFS2_MAXGROUPS
mdefine_line|#define NFS2_MAXGROUPS&t;16
DECL|macro|NFS2_FHSIZE
mdefine_line|#define NFS2_FHSIZE&t;32
DECL|macro|NFS2_COOKIESIZE
mdefine_line|#define NFS2_COOKIESIZE&t;4
DECL|macro|NFS2_FIFO_DEV
mdefine_line|#define NFS2_FIFO_DEV&t;(-1)
DECL|macro|NFS2MODE_FMT
mdefine_line|#define NFS2MODE_FMT&t;0170000
DECL|macro|NFS2MODE_DIR
mdefine_line|#define NFS2MODE_DIR&t;0040000
DECL|macro|NFS2MODE_CHR
mdefine_line|#define NFS2MODE_CHR&t;0020000
DECL|macro|NFS2MODE_BLK
mdefine_line|#define NFS2MODE_BLK&t;0060000
DECL|macro|NFS2MODE_REG
mdefine_line|#define NFS2MODE_REG&t;0100000
DECL|macro|NFS2MODE_LNK
mdefine_line|#define NFS2MODE_LNK&t;0120000
DECL|macro|NFS2MODE_SOCK
mdefine_line|#define NFS2MODE_SOCK&t;0140000
DECL|macro|NFS2MODE_FIFO
mdefine_line|#define NFS2MODE_FIFO&t;0010000
macro_line|#endif
eof
