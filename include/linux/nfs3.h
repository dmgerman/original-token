multiline_comment|/*&n; * NFSv3 protocol definitions&n; */
macro_line|#ifndef _LINUX_NFS3_H
DECL|macro|_LINUX_NFS3_H
mdefine_line|#define _LINUX_NFS3_H
DECL|macro|NFS3_PORT
mdefine_line|#define NFS3_PORT&t;&t;2049
DECL|macro|NFS3_MAXDATA
mdefine_line|#define NFS3_MAXDATA&t;&t;32768
DECL|macro|NFS3_MAXPATHLEN
mdefine_line|#define NFS3_MAXPATHLEN&t;&t;PATH_MAX
DECL|macro|NFS3_MAXNAMLEN
mdefine_line|#define NFS3_MAXNAMLEN&t;&t;NAME_MAX
DECL|macro|NFS3_MAXGROUPS
mdefine_line|#define NFS3_MAXGROUPS&t;&t;16
DECL|macro|NFS3_FHSIZE
mdefine_line|#define NFS3_FHSIZE&t;&t;64
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
multiline_comment|/* Flags for access() call */
DECL|macro|NFS3_ACCESS_READ
mdefine_line|#define NFS3_ACCESS_READ&t;0x0001
DECL|macro|NFS3_ACCESS_LOOKUP
mdefine_line|#define NFS3_ACCESS_LOOKUP&t;0x0002
DECL|macro|NFS3_ACCESS_MODIFY
mdefine_line|#define NFS3_ACCESS_MODIFY&t;0x0004
DECL|macro|NFS3_ACCESS_EXTEND
mdefine_line|#define NFS3_ACCESS_EXTEND&t;0x0008
DECL|macro|NFS3_ACCESS_DELETE
mdefine_line|#define NFS3_ACCESS_DELETE&t;0x0010
DECL|macro|NFS3_ACCESS_EXECUTE
mdefine_line|#define NFS3_ACCESS_EXECUTE&t;0x0020
multiline_comment|/* Flags for create mode */
DECL|enum|nfs3_createmode
r_enum
id|nfs3_createmode
(brace
DECL|enumerator|NFS3_CREATE_UNCHECKED
id|NFS3_CREATE_UNCHECKED
op_assign
l_int|0
comma
DECL|enumerator|NFS3_CREATE_GUARDED
id|NFS3_CREATE_GUARDED
op_assign
l_int|1
comma
DECL|enumerator|NFS3_CREATE_EXCLUSIVE
id|NFS3_CREATE_EXCLUSIVE
op_assign
l_int|2
)brace
suffix:semicolon
multiline_comment|/* NFSv3 file system properties */
DECL|macro|NFS3_FSF_LINK
mdefine_line|#define NFS3_FSF_LINK&t;&t;0x0001
DECL|macro|NFS3_FSF_SYMLINK
mdefine_line|#define NFS3_FSF_SYMLINK&t;0x0002
DECL|macro|NFS3_FSF_HOMOGENEOUS
mdefine_line|#define NFS3_FSF_HOMOGENEOUS&t;0x0008
DECL|macro|NFS3_FSF_CANSETTIME
mdefine_line|#define NFS3_FSF_CANSETTIME&t;0x0010
multiline_comment|/* Some shorthands. See fs/nfsd/nfs3proc.c */
DECL|macro|NFS3_FSF_DEFAULT
mdefine_line|#define NFS3_FSF_DEFAULT&t;0x001B
DECL|macro|NFS3_FSF_BILLYBOY
mdefine_line|#define NFS3_FSF_BILLYBOY&t;0x0018
DECL|macro|NFS3_FSF_READONLY
mdefine_line|#define NFS3_FSF_READONLY&t;0x0008
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
DECL|macro|NFS3PROC_NULL
mdefine_line|#define NFS3PROC_NULL&t;&t;0
DECL|macro|NFS3PROC_GETATTR
mdefine_line|#define NFS3PROC_GETATTR&t;1
DECL|macro|NFS3PROC_SETATTR
mdefine_line|#define NFS3PROC_SETATTR&t;2
DECL|macro|NFS3PROC_LOOKUP
mdefine_line|#define NFS3PROC_LOOKUP&t;&t;3
DECL|macro|NFS3PROC_ACCESS
mdefine_line|#define NFS3PROC_ACCESS&t;&t;4
DECL|macro|NFS3PROC_READLINK
mdefine_line|#define NFS3PROC_READLINK&t;5
DECL|macro|NFS3PROC_READ
mdefine_line|#define NFS3PROC_READ&t;&t;6
DECL|macro|NFS3PROC_WRITE
mdefine_line|#define NFS3PROC_WRITE&t;&t;7
DECL|macro|NFS3PROC_CREATE
mdefine_line|#define NFS3PROC_CREATE&t;&t;8
DECL|macro|NFS3PROC_MKDIR
mdefine_line|#define NFS3PROC_MKDIR&t;&t;9
DECL|macro|NFS3PROC_SYMLINK
mdefine_line|#define NFS3PROC_SYMLINK&t;10
DECL|macro|NFS3PROC_MKNOD
mdefine_line|#define NFS3PROC_MKNOD&t;&t;11
DECL|macro|NFS3PROC_REMOVE
mdefine_line|#define NFS3PROC_REMOVE&t;&t;12
DECL|macro|NFS3PROC_RMDIR
mdefine_line|#define NFS3PROC_RMDIR&t;&t;13
DECL|macro|NFS3PROC_RENAME
mdefine_line|#define NFS3PROC_RENAME&t;&t;14
DECL|macro|NFS3PROC_LINK
mdefine_line|#define NFS3PROC_LINK&t;&t;15
DECL|macro|NFS3PROC_READDIR
mdefine_line|#define NFS3PROC_READDIR&t;16
DECL|macro|NFS3PROC_READDIRPLUS
mdefine_line|#define NFS3PROC_READDIRPLUS&t;17
DECL|macro|NFS3PROC_FSSTAT
mdefine_line|#define NFS3PROC_FSSTAT&t;&t;18
DECL|macro|NFS3PROC_FSINFO
mdefine_line|#define NFS3PROC_FSINFO&t;&t;19
DECL|macro|NFS3PROC_PATHCONF
mdefine_line|#define NFS3PROC_PATHCONF&t;20
DECL|macro|NFS3PROC_COMMIT
mdefine_line|#define NFS3PROC_COMMIT&t;&t;21
DECL|macro|NFS_MNT3_PROGRAM
mdefine_line|#define NFS_MNT3_PROGRAM&t;100005
DECL|macro|NFS_MNT3_VERSION
mdefine_line|#define NFS_MNT3_VERSION&t;3
DECL|macro|MOUNTPROC3_NULL
mdefine_line|#define MOUNTPROC3_NULL&t;&t;0
DECL|macro|MOUNTPROC3_MNT
mdefine_line|#define MOUNTPROC3_MNT&t;&t;1
DECL|macro|MOUNTPROC3_UMNT
mdefine_line|#define MOUNTPROC3_UMNT&t;&t;3
DECL|macro|MOUNTPROC3_UMNTALL
mdefine_line|#define MOUNTPROC3_UMNTALL&t;4
macro_line|#if defined(__KERNEL__) || defined(NFS_NEED_KERNEL_TYPES)
multiline_comment|/* Number of 32bit words in post_op_attr */
DECL|macro|NFS3_POST_OP_ATTR_WORDS
mdefine_line|#define NFS3_POST_OP_ATTR_WORDS&t;&t;22
macro_line|#ifdef NFS_NEED_NFS3_XDR_TYPES
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
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|guard
r_int
r_int
id|guard
suffix:semicolon
DECL|member|guardtime
id|__u64
id|guardtime
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
DECL|member|len
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_accessargs
r_struct
id|nfs3_accessargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
DECL|member|access
id|__u32
id|access
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
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|createmode
r_enum
id|nfs3_createmode
id|createmode
suffix:semicolon
DECL|member|verifier
id|__u32
id|verifier
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_mkdirargs
r_struct
id|nfs3_mkdirargs
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
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
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
DECL|member|fromlen
r_int
id|fromlen
suffix:semicolon
DECL|member|topath
r_const
r_char
op_star
id|topath
suffix:semicolon
DECL|member|tolen
r_int
id|tolen
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_mknodargs
r_struct
id|nfs3_mknodargs
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
DECL|member|len
r_int
id|len
suffix:semicolon
DECL|member|type
r_enum
id|nfs3_ftype
id|type
suffix:semicolon
DECL|member|sattr
r_struct
id|iattr
op_star
id|sattr
suffix:semicolon
DECL|member|rdev
id|dev_t
id|rdev
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
DECL|member|fromlen
r_int
id|fromlen
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
DECL|member|tolen
r_int
id|tolen
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
DECL|member|tolen
r_int
id|tolen
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
id|__u64
id|cookie
suffix:semicolon
DECL|member|verf
id|__u32
id|verf
(braket
l_int|2
)braket
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
DECL|member|plus
r_int
id|plus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_diropres
r_struct
id|nfs3_diropres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
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
DECL|struct|nfs3_accessres
r_struct
id|nfs3_accessres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|access
id|__u32
id|access
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_readlinkargs
r_struct
id|nfs3_readlinkargs
(brace
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
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
DECL|struct|nfs3_readlinkres
r_struct
id|nfs3_readlinkres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
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
DECL|struct|nfs3_renameres
r_struct
id|nfs3_renameres
(brace
DECL|member|fromattr
r_struct
id|nfs_fattr
op_star
id|fromattr
suffix:semicolon
DECL|member|toattr
r_struct
id|nfs_fattr
op_star
id|toattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_linkres
r_struct
id|nfs3_linkres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs3_readdirres
r_struct
id|nfs3_readdirres
(brace
DECL|member|dir_attr
r_struct
id|nfs_fattr
op_star
id|dir_attr
suffix:semicolon
DECL|member|verf
id|__u32
op_star
id|verf
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
DECL|member|plus
r_int
id|plus
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* NFS_NEED_XDR_TYPES */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NFS3_H */
eof
