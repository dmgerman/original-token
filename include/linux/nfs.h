multiline_comment|/*&n; * NFS protocol definitions&n; */
macro_line|#ifndef _LINUX_NFS_H
DECL|macro|_LINUX_NFS_H
mdefine_line|#define _LINUX_NFS_H
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
DECL|macro|NFS_PORT
mdefine_line|#define NFS_PORT&t;2049
DECL|macro|NFS_MAXDATA
mdefine_line|#define NFS_MAXDATA&t;8192
DECL|macro|NFS_MAXPATHLEN
mdefine_line|#define NFS_MAXPATHLEN&t;1024
DECL|macro|NFS_MAXNAMLEN
mdefine_line|#define NFS_MAXNAMLEN&t;255
DECL|macro|NFS_MAXGROUPS
mdefine_line|#define NFS_MAXGROUPS&t;16
DECL|macro|NFS_FHSIZE
mdefine_line|#define NFS_FHSIZE&t;32
DECL|macro|NFS_COOKIESIZE
mdefine_line|#define NFS_COOKIESIZE&t;4
DECL|macro|NFS_FIFO_DEV
mdefine_line|#define NFS_FIFO_DEV&t;(-1)
DECL|macro|NFSMODE_FMT
mdefine_line|#define NFSMODE_FMT&t;0170000
DECL|macro|NFSMODE_DIR
mdefine_line|#define NFSMODE_DIR&t;0040000
DECL|macro|NFSMODE_CHR
mdefine_line|#define NFSMODE_CHR&t;0020000
DECL|macro|NFSMODE_BLK
mdefine_line|#define NFSMODE_BLK&t;0060000
DECL|macro|NFSMODE_REG
mdefine_line|#define NFSMODE_REG&t;0100000
DECL|macro|NFSMODE_LNK
mdefine_line|#define NFSMODE_LNK&t;0120000
DECL|macro|NFSMODE_SOCK
mdefine_line|#define NFSMODE_SOCK&t;0140000
DECL|macro|NFSMODE_FIFO
mdefine_line|#define NFSMODE_FIFO&t;0010000
DECL|enum|nfs_stat
r_enum
id|nfs_stat
(brace
DECL|enumerator|NFS_OK
id|NFS_OK
op_assign
l_int|0
comma
DECL|enumerator|NFSERR_PERM
id|NFSERR_PERM
op_assign
l_int|1
comma
DECL|enumerator|NFSERR_NOENT
id|NFSERR_NOENT
op_assign
l_int|2
comma
DECL|enumerator|NFSERR_IO
id|NFSERR_IO
op_assign
l_int|5
comma
DECL|enumerator|NFSERR_NXIO
id|NFSERR_NXIO
op_assign
l_int|6
comma
DECL|enumerator|NFSERR_EAGAIN
id|NFSERR_EAGAIN
op_assign
l_int|11
comma
DECL|enumerator|NFSERR_ACCES
id|NFSERR_ACCES
op_assign
l_int|13
comma
DECL|enumerator|NFSERR_EXIST
id|NFSERR_EXIST
op_assign
l_int|17
comma
DECL|enumerator|NFSERR_NODEV
id|NFSERR_NODEV
op_assign
l_int|19
comma
DECL|enumerator|NFSERR_NOTDIR
id|NFSERR_NOTDIR
op_assign
l_int|20
comma
DECL|enumerator|NFSERR_ISDIR
id|NFSERR_ISDIR
op_assign
l_int|21
comma
DECL|enumerator|NFSERR_INVAL
id|NFSERR_INVAL
op_assign
l_int|22
comma
multiline_comment|/* that Sun forgot */
DECL|enumerator|NFSERR_FBIG
id|NFSERR_FBIG
op_assign
l_int|27
comma
DECL|enumerator|NFSERR_NOSPC
id|NFSERR_NOSPC
op_assign
l_int|28
comma
DECL|enumerator|NFSERR_ROFS
id|NFSERR_ROFS
op_assign
l_int|30
comma
DECL|enumerator|NFSERR_NAMETOOLONG
id|NFSERR_NAMETOOLONG
op_assign
l_int|63
comma
DECL|enumerator|NFSERR_NOTEMPTY
id|NFSERR_NOTEMPTY
op_assign
l_int|66
comma
DECL|enumerator|NFSERR_DQUOT
id|NFSERR_DQUOT
op_assign
l_int|69
comma
DECL|enumerator|NFSERR_STALE
id|NFSERR_STALE
op_assign
l_int|70
comma
DECL|enumerator|NFSERR_WFLUSH
id|NFSERR_WFLUSH
op_assign
l_int|99
)brace
suffix:semicolon
DECL|enum|nfs_ftype
r_enum
id|nfs_ftype
(brace
DECL|enumerator|NFNON
id|NFNON
op_assign
l_int|0
comma
DECL|enumerator|NFREG
id|NFREG
op_assign
l_int|1
comma
DECL|enumerator|NFDIR
id|NFDIR
op_assign
l_int|2
comma
DECL|enumerator|NFBLK
id|NFBLK
op_assign
l_int|3
comma
DECL|enumerator|NFCHR
id|NFCHR
op_assign
l_int|4
comma
DECL|enumerator|NFLNK
id|NFLNK
op_assign
l_int|5
comma
DECL|enumerator|NFSOCK
id|NFSOCK
op_assign
l_int|6
comma
DECL|enumerator|NFBAD
id|NFBAD
op_assign
l_int|7
comma
DECL|enumerator|NFFIFO
id|NFFIFO
op_assign
l_int|8
)brace
suffix:semicolon
DECL|struct|nfs_fh
r_struct
id|nfs_fh
(brace
DECL|member|data
r_char
id|data
(braket
id|NFS_FHSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFS_PROGRAM
mdefine_line|#define NFS_PROGRAM&t;&t;100003
DECL|macro|NFS_VERSION
mdefine_line|#define NFS_VERSION&t;&t;2
DECL|macro|NFSPROC_NULL
mdefine_line|#define NFSPROC_NULL&t;&t;0
DECL|macro|NFSPROC_GETATTR
mdefine_line|#define NFSPROC_GETATTR&t;&t;1
DECL|macro|NFSPROC_SETATTR
mdefine_line|#define NFSPROC_SETATTR&t;&t;2
DECL|macro|NFSPROC_ROOT
mdefine_line|#define NFSPROC_ROOT&t;&t;3
DECL|macro|NFSPROC_LOOKUP
mdefine_line|#define NFSPROC_LOOKUP&t;&t;4
DECL|macro|NFSPROC_READLINK
mdefine_line|#define NFSPROC_READLINK&t;5
DECL|macro|NFSPROC_READ
mdefine_line|#define NFSPROC_READ&t;&t;6
DECL|macro|NFSPROC_WRITECACHE
mdefine_line|#define NFSPROC_WRITECACHE&t;7
DECL|macro|NFSPROC_WRITE
mdefine_line|#define NFSPROC_WRITE&t;&t;8
DECL|macro|NFSPROC_CREATE
mdefine_line|#define NFSPROC_CREATE&t;&t;9
DECL|macro|NFSPROC_REMOVE
mdefine_line|#define NFSPROC_REMOVE&t;&t;10
DECL|macro|NFSPROC_RENAME
mdefine_line|#define NFSPROC_RENAME&t;&t;11
DECL|macro|NFSPROC_LINK
mdefine_line|#define NFSPROC_LINK&t;&t;12
DECL|macro|NFSPROC_SYMLINK
mdefine_line|#define NFSPROC_SYMLINK&t;&t;13
DECL|macro|NFSPROC_MKDIR
mdefine_line|#define NFSPROC_MKDIR&t;&t;14
DECL|macro|NFSPROC_RMDIR
mdefine_line|#define NFSPROC_RMDIR&t;&t;15
DECL|macro|NFSPROC_READDIR
mdefine_line|#define NFSPROC_READDIR&t;&t;16
DECL|macro|NFSPROC_STATFS
mdefine_line|#define NFSPROC_STATFS&t;&t;17
multiline_comment|/* Mount support for NFSroot */
macro_line|#ifdef __KERNEL__
DECL|macro|NFS_MNT_PROGRAM
mdefine_line|#define NFS_MNT_PROGRAM&t;&t;100005
DECL|macro|NFS_MNT_VERSION
mdefine_line|#define NFS_MNT_VERSION&t;&t;1
DECL|macro|NFS_MNT_PORT
mdefine_line|#define NFS_MNT_PORT&t;&t;627
DECL|macro|NFS_MNTPROC_MNT
mdefine_line|#define NFS_MNTPROC_MNT&t;&t;1
DECL|macro|NFS_MNTPROC_UMNT
mdefine_line|#define NFS_MNTPROC_UMNT&t;3
macro_line|#endif
macro_line|#if defined(__KERNEL__) || defined(NFS_NEED_KERNEL_TYPES)
r_extern
r_struct
id|rpc_program
id|nfs_program
suffix:semicolon
r_extern
r_struct
id|rpc_stat
id|nfs_rpcstat
suffix:semicolon
DECL|struct|nfs_time
r_struct
id|nfs_time
(brace
DECL|member|seconds
id|__u32
id|seconds
suffix:semicolon
DECL|member|useconds
id|__u32
id|useconds
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_fattr
r_struct
id|nfs_fattr
(brace
DECL|member|type
r_enum
id|nfs_ftype
id|type
suffix:semicolon
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|nlink
id|__u32
id|nlink
suffix:semicolon
DECL|member|uid
id|__u32
id|uid
suffix:semicolon
DECL|member|gid
id|__u32
id|gid
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|blocksize
id|__u32
id|blocksize
suffix:semicolon
DECL|member|rdev
id|__u32
id|rdev
suffix:semicolon
DECL|member|blocks
id|__u32
id|blocks
suffix:semicolon
DECL|member|fsid
id|__u32
id|fsid
suffix:semicolon
DECL|member|fileid
id|__u32
id|fileid
suffix:semicolon
DECL|member|atime
r_struct
id|nfs_time
id|atime
suffix:semicolon
DECL|member|mtime
r_struct
id|nfs_time
id|mtime
suffix:semicolon
DECL|member|ctime
r_struct
id|nfs_time
id|ctime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_sattr
r_struct
id|nfs_sattr
(brace
DECL|member|mode
id|__u32
id|mode
suffix:semicolon
DECL|member|uid
id|__u32
id|uid
suffix:semicolon
DECL|member|gid
id|__u32
id|gid
suffix:semicolon
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|atime
r_struct
id|nfs_time
id|atime
suffix:semicolon
DECL|member|mtime
r_struct
id|nfs_time
id|mtime
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_fsinfo
r_struct
id|nfs_fsinfo
(brace
DECL|member|tsize
id|__u32
id|tsize
suffix:semicolon
DECL|member|bsize
id|__u32
id|bsize
suffix:semicolon
DECL|member|blocks
id|__u32
id|blocks
suffix:semicolon
DECL|member|bfree
id|__u32
id|bfree
suffix:semicolon
DECL|member|bavail
id|__u32
id|bavail
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef NFS_NEED_XDR_TYPES
DECL|struct|nfs_sattrargs
r_struct
id|nfs_sattrargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|sattr
r_struct
id|nfs_sattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_diropargs
r_struct
id|nfs_diropargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readargs
r_struct
id|nfs_readargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_writeargs
r_struct
id|nfs_writeargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|offset
id|__u32
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|buffer
r_const
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_createargs
r_struct
id|nfs_createargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|sattr
r_struct
id|nfs_sattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_renameargs
r_struct
id|nfs_renameargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_linkargs
r_struct
id|nfs_linkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|tofh
r_struct
id|nfs_fh
op_star
id|tofh
suffix:semicolon
DECL|member|toname
r_const
r_char
op_star
id|toname
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_symlinkargs
r_struct
id|nfs_symlinkargs
(brace
DECL|member|fromfh
r_struct
id|nfs_fh
op_star
id|fromfh
suffix:semicolon
DECL|member|fromname
r_const
r_char
op_star
id|fromname
suffix:semicolon
DECL|member|topath
r_const
r_char
op_star
id|topath
suffix:semicolon
DECL|member|sattr
r_struct
id|nfs_sattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readdirargs
r_struct
id|nfs_readdirargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|cookie
id|__u32
id|cookie
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|bufsiz
r_int
r_int
id|bufsiz
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_diropok
r_struct
id|nfs_diropok
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readres
r_struct
id|nfs_readres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readlinkres
r_struct
id|nfs_readlinkres
(brace
DECL|member|string
r_char
op_star
op_star
id|string
suffix:semicolon
DECL|member|lenp
r_int
r_int
op_star
id|lenp
suffix:semicolon
DECL|member|maxlen
r_int
r_int
id|maxlen
suffix:semicolon
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_readdirres
r_struct
id|nfs_readdirres
(brace
DECL|member|buffer
r_void
op_star
id|buffer
suffix:semicolon
DECL|member|bufsiz
r_int
r_int
id|bufsiz
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* NFS_NEED_XDR_TYPES */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
