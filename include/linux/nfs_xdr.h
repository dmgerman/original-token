macro_line|#ifndef _LINUX_NFS_XDR_H
DECL|macro|_LINUX_NFS_XDR_H
mdefine_line|#define _LINUX_NFS_XDR_H
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
DECL|struct|nfs_fattr
r_struct
id|nfs_fattr
(brace
DECL|member|valid
r_int
r_int
id|valid
suffix:semicolon
multiline_comment|/* which fields are valid */
DECL|member|pre_size
id|__u64
id|pre_size
suffix:semicolon
multiline_comment|/* pre_op_attr.size&t;  */
DECL|member|pre_mtime
id|__u64
id|pre_mtime
suffix:semicolon
multiline_comment|/* pre_op_attr.mtime&t;  */
DECL|member|pre_ctime
id|__u64
id|pre_ctime
suffix:semicolon
multiline_comment|/* pre_op_attr.ctime&t;  */
DECL|member|type
r_enum
id|nfs_ftype
id|type
suffix:semicolon
multiline_comment|/* always use NFSv2 types */
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
r_union
(brace
r_struct
(brace
DECL|member|blocksize
id|__u32
id|blocksize
suffix:semicolon
DECL|member|blocks
id|__u32
id|blocks
suffix:semicolon
DECL|member|nfs2
)brace
id|nfs2
suffix:semicolon
r_struct
(brace
DECL|member|used
id|__u64
id|used
suffix:semicolon
DECL|member|nfs3
)brace
id|nfs3
suffix:semicolon
DECL|member|du
)brace
id|du
suffix:semicolon
DECL|member|rdev
id|__u32
id|rdev
suffix:semicolon
DECL|member|fsid
id|__u64
id|fsid
suffix:semicolon
DECL|member|fileid
id|__u64
id|fileid
suffix:semicolon
DECL|member|atime
id|__u64
id|atime
suffix:semicolon
DECL|member|mtime
id|__u64
id|mtime
suffix:semicolon
DECL|member|ctime
id|__u64
id|ctime
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NFS_ATTR_WCC
mdefine_line|#define NFS_ATTR_WCC&t;&t;0x0001&t;&t;/* pre-op WCC data    */
DECL|macro|NFS_ATTR_FATTR
mdefine_line|#define NFS_ATTR_FATTR&t;&t;0x0002&t;&t;/* post-op attributes */
DECL|macro|NFS_ATTR_FATTR_V3
mdefine_line|#define NFS_ATTR_FATTR_V3&t;0x0004&t;&t;/* NFSv3 attributes */
multiline_comment|/*&n; * Info on the file system&n; */
DECL|struct|nfs_fsinfo
r_struct
id|nfs_fsinfo
(brace
DECL|member|rtmax
id|__u32
id|rtmax
suffix:semicolon
multiline_comment|/* max.  read transfer size */
DECL|member|rtpref
id|__u32
id|rtpref
suffix:semicolon
multiline_comment|/* pref. read transfer size */
DECL|member|rtmult
id|__u32
id|rtmult
suffix:semicolon
multiline_comment|/* reads should be multiple of this */
DECL|member|wtmax
id|__u32
id|wtmax
suffix:semicolon
multiline_comment|/* max.  write transfer size */
DECL|member|wtpref
id|__u32
id|wtpref
suffix:semicolon
multiline_comment|/* pref. write transfer size */
DECL|member|wtmult
id|__u32
id|wtmult
suffix:semicolon
multiline_comment|/* writes should be multiple of this */
DECL|member|dtpref
id|__u32
id|dtpref
suffix:semicolon
multiline_comment|/* pref. readdir transfer size */
DECL|member|maxfilesize
id|__u64
id|maxfilesize
suffix:semicolon
DECL|member|bsize
id|__u64
id|bsize
suffix:semicolon
multiline_comment|/* block size */
DECL|member|tbytes
id|__u64
id|tbytes
suffix:semicolon
multiline_comment|/* total size in bytes */
DECL|member|fbytes
id|__u64
id|fbytes
suffix:semicolon
multiline_comment|/* # of free bytes */
DECL|member|abytes
id|__u64
id|abytes
suffix:semicolon
multiline_comment|/* # of bytes available to user */
DECL|member|tfiles
id|__u64
id|tfiles
suffix:semicolon
multiline_comment|/* # of files */
DECL|member|ffiles
id|__u64
id|ffiles
suffix:semicolon
multiline_comment|/* # of free files */
DECL|member|afiles
id|__u64
id|afiles
suffix:semicolon
multiline_comment|/* # of files available to user */
DECL|member|linkmax
id|__u32
id|linkmax
suffix:semicolon
multiline_comment|/* max # of hard links */
DECL|member|namelen
id|__u32
id|namelen
suffix:semicolon
multiline_comment|/* max name length */
)brace
suffix:semicolon
multiline_comment|/* Arguments to the read call.&n; * Note that NFS_READ_MAXIOV must be &lt;= (MAX_IOVEC-2) from sunrpc/xprt.h&n; */
DECL|macro|NFS_READ_MAXIOV
mdefine_line|#define NFS_READ_MAXIOV 8
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
id|__u64
id|offset
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
DECL|member|nriov
r_int
r_int
id|nriov
suffix:semicolon
DECL|member|iov
r_struct
id|iovec
id|iov
(braket
id|NFS_READ_MAXIOV
)braket
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
DECL|member|eof
r_int
id|eof
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Arguments to the write call.&n; * Note that NFS_WRITE_MAXIOV must be &lt;= (MAX_IOVEC-2) from sunrpc/xprt.h&n; */
DECL|macro|NFS_WRITE_MAXIOV
mdefine_line|#define NFS_WRITE_MAXIOV        8
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
DECL|member|stable
r_enum
id|nfs3_stable_how
id|stable
suffix:semicolon
DECL|member|nriov
r_int
r_int
id|nriov
suffix:semicolon
DECL|member|iov
r_struct
id|iovec
id|iov
(braket
id|NFS_WRITE_MAXIOV
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|nfs_writeverf
r_struct
id|nfs_writeverf
(brace
DECL|member|committed
r_enum
id|nfs3_stable_how
id|committed
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
DECL|struct|nfs_writeres
r_struct
id|nfs_writeres
(brace
DECL|member|fattr
r_struct
id|nfs_fattr
op_star
id|fattr
suffix:semicolon
DECL|member|verf
r_struct
id|nfs_writeverf
op_star
id|verf
suffix:semicolon
DECL|member|count
id|__u32
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Argument struct for decode_entry function&n; */
DECL|struct|nfs_entry
r_struct
id|nfs_entry
(brace
DECL|member|ino
id|__u64
id|ino
suffix:semicolon
DECL|member|cookie
id|__u64
id|cookie
comma
DECL|member|prev_cookie
id|prev_cookie
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:semicolon
DECL|member|fh
r_struct
id|nfs_fh
id|fh
suffix:semicolon
DECL|member|fattr
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * The following types are for NFSv2 only.&n; */
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
id|iattr
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
DECL|member|len
r_int
r_int
id|len
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
DECL|member|len
r_int
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
DECL|member|fromlen
r_int
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
r_int
id|tolen
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
DECL|member|tolen
r_int
r_int
id|tolen
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
DECL|member|fromlen
r_int
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
DECL|struct|nfs_readlinkargs
r_struct
id|nfs_readlinkargs
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
DECL|struct|nfs_readlinkres
r_struct
id|nfs_readlinkres
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
multiline_comment|/*&n; * RPC procedure vector for NFSv2/NFSv3 demuxing&n; */
DECL|struct|nfs_rpc_ops
r_struct
id|nfs_rpc_ops
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
multiline_comment|/* Protocol version */
DECL|member|getroot
r_int
(paren
op_star
id|getroot
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|getattr
r_int
(paren
op_star
id|getattr
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|setattr
r_int
(paren
op_star
id|setattr
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
DECL|member|lookup
r_int
(paren
op_star
id|lookup
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|access
r_int
(paren
op_star
id|access
)paren
(paren
r_struct
id|inode
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|readlink
r_int
(paren
op_star
id|readlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|read
r_int
(paren
op_star
id|read
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
comma
id|loff_t
comma
r_int
r_int
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|eofp
)paren
suffix:semicolon
DECL|member|write
r_int
(paren
op_star
id|write
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
comma
id|loff_t
comma
r_int
r_int
comma
r_void
op_star
id|buffer
comma
r_struct
id|nfs_writeverf
op_star
id|verfp
)paren
suffix:semicolon
DECL|member|commit
r_int
(paren
op_star
id|commit
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|member|create
r_int
(paren
op_star
id|create
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_int
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|remove
r_int
(paren
op_star
id|remove
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|unlink_setup
r_int
(paren
op_star
id|unlink_setup
)paren
(paren
r_struct
id|rpc_message
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|unlink_done
r_void
(paren
op_star
id|unlink_done
)paren
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|rpc_message
op_star
)paren
suffix:semicolon
DECL|member|rename
r_int
(paren
op_star
id|rename
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|link
r_int
(paren
op_star
id|link
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|symlink
r_int
(paren
op_star
id|symlink
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|mkdir
r_int
(paren
op_star
id|mkdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|rmdir
r_int
(paren
op_star
id|rmdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
)paren
suffix:semicolon
DECL|member|readdir
r_int
(paren
op_star
id|readdir
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|rpc_cred
op_star
comma
id|u64
comma
r_void
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|mknod
r_int
(paren
op_star
id|mknod
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|iattr
op_star
comma
id|dev_t
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
DECL|member|statfs
r_int
(paren
op_star
id|statfs
)paren
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fsinfo
op_star
)paren
suffix:semicolon
DECL|member|decode_dirent
id|u32
op_star
(paren
op_star
id|decode_dirent
)paren
(paren
id|u32
op_star
comma
r_struct
id|nfs_entry
op_star
comma
r_int
id|plus
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * &t;NFS_CALL(getattr, inode, (fattr));&n; * into&n; *&t;NFS_PROTO(inode)-&gt;getattr(fattr);&n; */
DECL|macro|NFS_CALL
mdefine_line|#define NFS_CALL(op, inode, args)&t;NFS_PROTO(inode)-&gt;op args
multiline_comment|/*&n; * Function vectors etc. for the NFS client&n; */
r_extern
r_struct
id|nfs_rpc_ops
id|nfs_v2_clientops
suffix:semicolon
r_extern
r_struct
id|nfs_rpc_ops
id|nfs_v3_clientops
suffix:semicolon
r_extern
r_struct
id|rpc_version
id|nfs_version2
suffix:semicolon
r_extern
r_struct
id|rpc_version
id|nfs_version3
suffix:semicolon
r_extern
r_struct
id|rpc_program
id|nfs_program
suffix:semicolon
macro_line|#endif
eof
