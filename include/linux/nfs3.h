multiline_comment|/*&n; * NFSv3 protocol definitions&n; */
macro_line|#ifndef _LINUX_NFS3_H
DECL|macro|_LINUX_NFS3_H
mdefine_line|#define _LINUX_NFS3_H
macro_line|#include &lt;linux/sunrpc/msg_prot.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
DECL|macro|NFS3_PORT
mdefine_line|#define NFS3_PORT&t;&t;2049
DECL|macro|NFS3_MAXDATA
mdefine_line|#define NFS3_MAXDATA&t;&t;8192
DECL|macro|NFS3_MAXPATHLEN
mdefine_line|#define NFS3_MAXPATHLEN&t;&t;PATH_MAX
DECL|macro|NFS3_MAXNAMLEN
mdefine_line|#define NFS3_MAXNAMLEN&t;&t;NAME_MAX
DECL|macro|NFS3_MAXGROUPS
mdefine_line|#define NFS3_MAXGROUPS&t;&t;16
DECL|macro|NFS3_FHSIZE
mdefine_line|#define NFS3_FHSIZE&t;&t;NFS_FHSIZE
DECL|macro|NFS3_COOKIESIZE
mdefine_line|#define NFS3_COOKIESIZE&t;&t;4
DECL|macro|NFS3_FIFO_DEV
mdefine_line|#define NFS3_FIFO_DEV&t;&t;(-1)
DECL|macro|NFS3MODE_FMT
mdefine_line|#define NFS3MODE_FMT&t;&t;0170000
DECL|macro|NFS3MODE_DIR
mdefine_line|#define NFS3MODE_DIR&t;&t;0040000
DECL|macro|NFS3MODE_CHR
mdefine_line|#define NFS3MODE_CHR&t;&t;0020000
DECL|macro|NFS3MODE_BLK
mdefine_line|#define NFS3MODE_BLK&t;&t;0060000
DECL|macro|NFS3MODE_REG
mdefine_line|#define NFS3MODE_REG&t;&t;0100000
DECL|macro|NFS3MODE_LNK
mdefine_line|#define NFS3MODE_LNK&t;&t;0120000
DECL|macro|NFS3MODE_SOCK
mdefine_line|#define NFS3MODE_SOCK&t;&t;0140000
DECL|macro|NFS3MODE_FIFO
mdefine_line|#define NFS3MODE_FIFO&t;&t;0010000
DECL|enum|nfs3_stat
r_enum
id|nfs3_stat
(brace
DECL|enumerator|NFS3_OK
id|NFS3_OK
op_assign
l_int|0
comma
DECL|enumerator|NFS3ERR_PERM
id|NFS3ERR_PERM
op_assign
l_int|1
comma
DECL|enumerator|NFS3ERR_NOENT
id|NFS3ERR_NOENT
op_assign
l_int|2
comma
DECL|enumerator|NFS3ERR_IO
id|NFS3ERR_IO
op_assign
l_int|5
comma
DECL|enumerator|NFS3ERR_NXIO
id|NFS3ERR_NXIO
op_assign
l_int|6
comma
DECL|enumerator|NFS3ERR_EAGAIN
id|NFS3ERR_EAGAIN
op_assign
l_int|11
comma
DECL|enumerator|NFS3ERR_ACCES
id|NFS3ERR_ACCES
op_assign
l_int|13
comma
DECL|enumerator|NFS3ERR_EXIST
id|NFS3ERR_EXIST
op_assign
l_int|17
comma
DECL|enumerator|NFS3ERR_XDEV
id|NFS3ERR_XDEV
op_assign
l_int|18
comma
multiline_comment|/* new in NFSv3 */
DECL|enumerator|NFS3ERR_NODEV
id|NFS3ERR_NODEV
op_assign
l_int|19
comma
DECL|enumerator|NFS3ERR_NOTDIR
id|NFS3ERR_NOTDIR
op_assign
l_int|20
comma
DECL|enumerator|NFS3ERR_ISDIR
id|NFS3ERR_ISDIR
op_assign
l_int|21
comma
DECL|enumerator|NFS3ERR_INVAL
id|NFS3ERR_INVAL
op_assign
l_int|22
comma
multiline_comment|/* new in NFSv3 */
DECL|enumerator|NFS3ERR_FBIG
id|NFS3ERR_FBIG
op_assign
l_int|27
comma
DECL|enumerator|NFS3ERR_NOSPC
id|NFS3ERR_NOSPC
op_assign
l_int|28
comma
DECL|enumerator|NFS3ERR_ROFS
id|NFS3ERR_ROFS
op_assign
l_int|30
comma
DECL|enumerator|NFS3ERR_MLINK
id|NFS3ERR_MLINK
op_assign
l_int|31
comma
multiline_comment|/* new in NFSv3 */
DECL|enumerator|NFS3ERR_NAMETOOLONG
id|NFS3ERR_NAMETOOLONG
op_assign
l_int|63
comma
DECL|enumerator|NFS3ERR_NOTEMPTY
id|NFS3ERR_NOTEMPTY
op_assign
l_int|66
comma
DECL|enumerator|NFS3ERR_DQUOT
id|NFS3ERR_DQUOT
op_assign
l_int|69
comma
DECL|enumerator|NFS3ERR_STALE
id|NFS3ERR_STALE
op_assign
l_int|70
comma
DECL|enumerator|NFS3ERR_REMOTE
id|NFS3ERR_REMOTE
op_assign
l_int|71
comma
multiline_comment|/* new in NFSv3 */
DECL|enumerator|NFS3ERR_BADHANDLE
id|NFS3ERR_BADHANDLE
op_assign
l_int|10001
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_NOT_SYNC
id|NFS3ERR_NOT_SYNC
op_assign
l_int|10002
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_BAD_COOKIE
id|NFS3ERR_BAD_COOKIE
op_assign
l_int|10003
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_NOTSUPP
id|NFS3ERR_NOTSUPP
op_assign
l_int|10004
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_TOOSMALL
id|NFS3ERR_TOOSMALL
op_assign
l_int|10005
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_SERVERFAULT
id|NFS3ERR_SERVERFAULT
op_assign
l_int|10006
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_BADTYPE
id|NFS3ERR_BADTYPE
op_assign
l_int|10007
comma
multiline_comment|/* ditto */
DECL|enumerator|NFS3ERR_JUKEBOX
id|NFS3ERR_JUKEBOX
op_assign
l_int|10008
comma
multiline_comment|/* ditto */
)brace
suffix:semicolon
DECL|enum|nfs3_ftype
r_enum
id|nfs3_ftype
(brace
DECL|enumerator|NF3NON
id|NF3NON
op_assign
l_int|0
comma
DECL|enumerator|NF3REG
id|NF3REG
op_assign
l_int|1
comma
DECL|enumerator|NF3DIR
id|NF3DIR
op_assign
l_int|2
comma
DECL|enumerator|NF3BLK
id|NF3BLK
op_assign
l_int|3
comma
DECL|enumerator|NF3CHR
id|NF3CHR
op_assign
l_int|4
comma
DECL|enumerator|NF3LNK
id|NF3LNK
op_assign
l_int|5
comma
DECL|enumerator|NF3SOCK
id|NF3SOCK
op_assign
l_int|6
comma
DECL|enumerator|NF3FIFO
id|NF3FIFO
op_assign
l_int|7
comma
multiline_comment|/* changed from NFSv2 (was 8) */
DECL|enumerator|NF3BAD
id|NF3BAD
op_assign
l_int|8
)brace
suffix:semicolon
DECL|macro|NFS3_VERSION
mdefine_line|#define NFS3_VERSION&t;&t;3
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
macro_line|#if defined(__KERNEL__) || defined(NFS_NEED_KERNEL_TYPES)
DECL|struct|nfs3_fh
r_struct
id|nfs3_fh
(brace
DECL|member|size
id|__u32
id|size
suffix:semicolon
DECL|member|data
id|__u8
id|data
(braket
id|NFS3_FHSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_fattr
r_struct
id|nfs3_fattr
(brace
DECL|member|type
r_enum
id|nfs3_ftype
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
id|__u64
id|size
suffix:semicolon
DECL|member|used
id|__u64
id|used
suffix:semicolon
DECL|member|rdev_maj
id|__u32
id|rdev_maj
suffix:semicolon
DECL|member|rdev_min
id|__u32
id|rdev_min
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
DECL|struct|nfs3_wcc_attr
r_struct
id|nfs3_wcc_attr
(brace
DECL|member|size
id|__u64
id|size
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
DECL|struct|nfs3_wcc_data
r_struct
id|nfs3_wcc_data
(brace
DECL|member|before
r_struct
id|nfs3_wcc_attr
id|before
suffix:semicolon
DECL|member|after
r_struct
id|nfs3_wcc_attr
id|after
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_sattr
r_struct
id|nfs3_sattr
(brace
DECL|member|valid
id|__u32
id|valid
suffix:semicolon
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
id|__u64
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
DECL|struct|nfs3_entry
r_struct
id|nfs3_entry
(brace
DECL|member|fileid
id|__u32
id|fileid
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|cookie
id|__u32
id|cookie
suffix:semicolon
DECL|member|eof
id|__u32
id|eof
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_fsinfo
r_struct
id|nfs3_fsinfo
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
DECL|struct|nfs3_sattrargs
r_struct
id|nfs3_sattrargs
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
DECL|struct|nfs3_diropargs
r_struct
id|nfs3_diropargs
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
DECL|struct|nfs3_readargs
r_struct
id|nfs3_readargs
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
DECL|struct|nfs3_writeargs
r_struct
id|nfs3_writeargs
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
DECL|struct|nfs3_createargs
r_struct
id|nfs3_createargs
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
DECL|struct|nfs3_renameargs
r_struct
id|nfs3_renameargs
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
DECL|struct|nfs3_linkargs
r_struct
id|nfs3_linkargs
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
DECL|struct|nfs3_symlinkargs
r_struct
id|nfs3_symlinkargs
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
DECL|struct|nfs3_readdirargs
r_struct
id|nfs3_readdirargs
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
DECL|struct|nfs3_diropok
r_struct
id|nfs3_diropok
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
DECL|struct|nfs3_readres
r_struct
id|nfs3_readres
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
DECL|struct|nfs3_readlinkres
r_struct
id|nfs3_readlinkres
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
DECL|struct|nfs3_readdirres
r_struct
id|nfs3_readdirres
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
multiline_comment|/*&n; * The following are for NFSv3&n; */
DECL|struct|nfs3_fh
r_struct
id|nfs3_fh
(brace
DECL|member|size
id|__u32
id|size
suffix:semicolon
id|__u8
id|data
(braket
id|NFS3_FHSIZE
)braket
)brace
suffix:semicolon
DECL|struct|nfs3_wcc_attr
r_struct
id|nfs3_wcc_attr
(brace
DECL|member|size
id|__u64
id|size
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
macro_line|#endif /* NFS_NEED_XDR_TYPES */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof