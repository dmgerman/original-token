multiline_comment|/*&n; * linux/fs/nfsd/xdr.c&n; *&n; * XDR support for nfsd&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/sunrpc/xdr.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_XDR
DECL|variable|nfs_ok
DECL|variable|nfserr_perm
DECL|variable|nfserr_noent
DECL|variable|nfserr_io
DECL|variable|nfserr_nxio
id|u32
id|nfs_ok
comma
id|nfserr_perm
comma
id|nfserr_noent
comma
id|nfserr_io
comma
id|nfserr_nxio
comma
DECL|variable|nfserr_acces
DECL|variable|nfserr_exist
DECL|variable|nfserr_nodev
DECL|variable|nfserr_notdir
id|nfserr_acces
comma
id|nfserr_exist
comma
id|nfserr_nodev
comma
id|nfserr_notdir
comma
DECL|variable|nfserr_isdir
DECL|variable|nfserr_fbig
DECL|variable|nfserr_nospc
DECL|variable|nfserr_rofs
id|nfserr_isdir
comma
id|nfserr_fbig
comma
id|nfserr_nospc
comma
id|nfserr_rofs
comma
DECL|variable|nfserr_nametoolong
DECL|variable|nfserr_dquot
DECL|variable|nfserr_stale
id|nfserr_nametoolong
comma
id|nfserr_dquot
comma
id|nfserr_stale
suffix:semicolon
macro_line|#ifdef NFSD_OPTIMIZE_SPACE
DECL|macro|inline
macro_line|# define inline
macro_line|#endif
multiline_comment|/*&n; * Mapping of S_IF* types to NFS file types&n; */
DECL|variable|nfs_ftypes
r_static
id|u32
id|nfs_ftypes
(braket
)braket
op_assign
(brace
id|NFNON
comma
id|NFFIFO
comma
id|NFCHR
comma
id|NFBAD
comma
id|NFDIR
comma
id|NFBAD
comma
id|NFBLK
comma
id|NFBAD
comma
id|NFREG
comma
id|NFBAD
comma
id|NFLNK
comma
id|NFBAD
comma
id|NFSOCK
comma
id|NFBAD
comma
id|NFLNK
comma
id|NFBAD
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialization of NFS status variables&n; */
r_void
DECL|function|nfsd_xdr_init
id|nfsd_xdr_init
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|inited
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inited
)paren
r_return
suffix:semicolon
id|nfs_ok
op_assign
id|htonl
c_func
(paren
id|NFS_OK
)paren
suffix:semicolon
id|nfserr_perm
op_assign
id|htonl
c_func
(paren
id|NFSERR_PERM
)paren
suffix:semicolon
id|nfserr_noent
op_assign
id|htonl
c_func
(paren
id|NFSERR_NOENT
)paren
suffix:semicolon
id|nfserr_io
op_assign
id|htonl
c_func
(paren
id|NFSERR_IO
)paren
suffix:semicolon
id|nfserr_nxio
op_assign
id|htonl
c_func
(paren
id|NFSERR_NXIO
)paren
suffix:semicolon
id|nfserr_acces
op_assign
id|htonl
c_func
(paren
id|NFSERR_ACCES
)paren
suffix:semicolon
id|nfserr_exist
op_assign
id|htonl
c_func
(paren
id|NFSERR_EXIST
)paren
suffix:semicolon
id|nfserr_nodev
op_assign
id|htonl
c_func
(paren
id|NFSERR_NODEV
)paren
suffix:semicolon
id|nfserr_notdir
op_assign
id|htonl
c_func
(paren
id|NFSERR_NOTDIR
)paren
suffix:semicolon
id|nfserr_isdir
op_assign
id|htonl
c_func
(paren
id|NFSERR_ISDIR
)paren
suffix:semicolon
id|nfserr_fbig
op_assign
id|htonl
c_func
(paren
id|NFSERR_FBIG
)paren
suffix:semicolon
id|nfserr_nospc
op_assign
id|htonl
c_func
(paren
id|NFSERR_NOSPC
)paren
suffix:semicolon
id|nfserr_rofs
op_assign
id|htonl
c_func
(paren
id|NFSERR_ROFS
)paren
suffix:semicolon
id|nfserr_nametoolong
op_assign
id|htonl
c_func
(paren
id|NFSERR_NAMETOOLONG
)paren
suffix:semicolon
id|nfserr_dquot
op_assign
id|htonl
c_func
(paren
id|NFSERR_DQUOT
)paren
suffix:semicolon
id|nfserr_stale
op_assign
id|htonl
c_func
(paren
id|NFSERR_STALE
)paren
suffix:semicolon
id|inited
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR functions for basic NFS types&n; */
r_static
r_inline
id|u32
op_star
DECL|function|decode_fh
id|decode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
id|fh_init
c_func
(paren
id|fhp
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|fhp-&gt;fh_handle
comma
id|p
comma
r_sizeof
(paren
r_struct
id|knfs_fh
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: Look up export pointer here and verify&n;&t; * Sun Secure RPC if requested */
r_return
id|p
op_plus
(paren
r_sizeof
(paren
r_struct
id|knfs_fh
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|encode_fh
id|encode_fh
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
id|memcpy
c_func
(paren
id|p
comma
op_amp
id|fhp-&gt;fh_handle
comma
r_sizeof
(paren
r_struct
id|knfs_fh
)paren
)paren
suffix:semicolon
r_return
id|p
op_plus
(paren
r_sizeof
(paren
r_struct
id|knfs_fh
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode a file name and make sure that the path contains&n; * no slashes or null bytes.&n; */
r_static
r_inline
id|u32
op_star
DECL|function|decode_filename
id|decode_filename
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|namp
comma
r_int
op_star
id|lenp
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|xdr_decode_string
c_func
(paren
id|p
comma
id|namp
comma
id|lenp
comma
id|NFS_MAXNAMLEN
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|name
op_assign
op_star
id|namp
suffix:semicolon
id|i
OL
op_star
id|lenp
suffix:semicolon
id|i
op_increment
comma
id|name
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|name
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|name
op_eq
l_char|&squot;/&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|name
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|decode_pathname
id|decode_pathname
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|namp
comma
r_int
op_star
id|lenp
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|xdr_decode_string
c_func
(paren
id|p
comma
id|namp
comma
id|lenp
comma
id|NFS_MAXPATHLEN
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|name
op_assign
op_star
id|namp
suffix:semicolon
id|i
OL
op_star
id|lenp
suffix:semicolon
id|i
op_increment
comma
id|name
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|name
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
op_star
id|name
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|decode_sattr
id|decode_sattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|iattr
op_star
id|iap
)paren
(brace
id|u32
id|tmp
comma
id|tmp1
suffix:semicolon
id|iap-&gt;ia_valid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Sun client bug compatibility check: some sun clients seem to&n;&t; * put 0xffff in the mode field when they mean 0xffffffff.&n;&t; * Quoting the 4.4BSD nfs server code: Nah nah nah nah na nah.&n;&t; */
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp
op_ne
l_int|0xffff
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|iap-&gt;ia_mode
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_UID
suffix:semicolon
id|iap-&gt;ia_uid
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_GID
suffix:semicolon
id|iap-&gt;ia_gid
op_assign
id|tmp
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_SIZE
suffix:semicolon
id|iap-&gt;ia_size
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|tmp1
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp1
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_ATIME
op_or
id|ATTR_ATIME_SET
suffix:semicolon
id|iap-&gt;ia_atime
op_assign
id|tmp
suffix:semicolon
)brace
id|tmp
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|tmp1
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
op_logical_and
id|tmp1
op_ne
(paren
id|u32
)paren
op_minus
l_int|1
)paren
(brace
id|iap-&gt;ia_valid
op_or_assign
id|ATTR_MTIME
op_or
id|ATTR_MTIME_SET
suffix:semicolon
id|iap-&gt;ia_mtime
op_assign
id|tmp
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|encode_fattr
id|encode_fattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|nfs_ftypes
(braket
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_rshift
l_int|12
)braket
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_mode
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_nlink
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|nfsd_ruid
c_func
(paren
id|rqstp
comma
id|inode-&gt;i_uid
)paren
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|nfsd_rgid
c_func
(paren
id|rqstp
comma
id|inode-&gt;i_gid
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|S_ISLNK
c_func
(paren
id|inode-&gt;i_mode
)paren
op_logical_and
id|inode-&gt;i_size
OG
id|NFS_MAXPATHLEN
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|NFS_MAXPATHLEN
)paren
suffix:semicolon
)brace
r_else
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_size
)paren
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_blksize
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_blocks
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_dev
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_ino
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_atime
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_mtime
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|inode-&gt;i_ctime
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Check buffer bounds after decoding arguments&n; */
r_static
r_inline
r_int
DECL|function|xdr_argsize_check
id|xdr_argsize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_argbuf
suffix:semicolon
r_return
id|p
op_minus
id|buf-&gt;base
op_le
id|buf-&gt;buflen
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|xdr_ressize_check
id|xdr_ressize_check
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|svc_buf
op_star
id|buf
op_assign
op_amp
id|rqstp-&gt;rq_resbuf
suffix:semicolon
id|buf-&gt;len
op_assign
id|p
op_minus
id|buf-&gt;base
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: ressize_check p %p base %p len %d&bslash;n&quot;
comma
id|p
comma
id|buf-&gt;base
comma
id|buf-&gt;buflen
)paren
suffix:semicolon
r_return
(paren
id|buf-&gt;len
op_le
id|buf-&gt;buflen
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR decode functions&n; */
r_int
DECL|function|nfssvc_decode_void
id|nfssvc_decode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_fhandle
id|nfssvc_decode_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|svc_fh
op_star
id|fhp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
id|fhp
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_sattrargs
id|nfssvc_decode_sattrargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_sattrargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_diropargs
id|nfssvc_decode_diropargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_diropargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;name
comma
op_amp
id|args-&gt;len
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_readargs
id|nfssvc_decode_readargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|args-&gt;offset
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;totalsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_writeargs
id|nfssvc_decode_writeargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_writeargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|p
op_increment
suffix:semicolon
multiline_comment|/* beginoffset */
id|args-&gt;offset
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
multiline_comment|/* offset */
id|p
op_increment
suffix:semicolon
multiline_comment|/* totalcount */
id|args-&gt;len
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;data
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|args-&gt;len
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_createargs
id|nfssvc_decode_createargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_createargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;name
comma
op_amp
id|args-&gt;len
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_renameargs
id|nfssvc_decode_renameargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_renameargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fname
comma
op_amp
id|args-&gt;flen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tfh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_linkargs
id|nfssvc_decode_linkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_linkargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tfh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_symlinkargs
id|nfssvc_decode_symlinkargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_symlinkargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;ffh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_filename
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fname
comma
op_amp
id|args-&gt;flen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_pathname
c_func
(paren
id|p
comma
op_amp
id|args-&gt;tname
comma
op_amp
id|args-&gt;tlen
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|decode_sattr
c_func
(paren
id|p
comma
op_amp
id|args-&gt;attrs
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_decode_readdirargs
id|nfssvc_decode_readdirargs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readdirargs
op_star
id|args
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|decode_fh
c_func
(paren
id|p
comma
op_amp
id|args-&gt;fh
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|args-&gt;cookie
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|args-&gt;count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
r_return
id|xdr_argsize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode functions&n; */
r_int
DECL|function|nfssvc_encode_void
id|nfssvc_encode_void
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_void
op_star
id|dummy
)paren
(brace
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_attrstat
id|nfssvc_encode_attrstat
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_attrstat
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
id|resp-&gt;fh.fh_inode
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_diropres
id|nfssvc_encode_diropres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_diropres
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|encode_fh
c_func
(paren
id|p
comma
op_amp
id|resp-&gt;fh
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
id|resp-&gt;fh.fh_inode
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readlinkres
id|nfssvc_encode_readlinkres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readlinkres
op_star
id|resp
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|resp-&gt;len
)paren
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;len
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readres
id|nfssvc_encode_readres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readres
op_star
id|resp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|encode_fattr
c_func
(paren
id|rqstp
comma
id|p
comma
id|resp-&gt;fh.fh_inode
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_readdirres
id|nfssvc_encode_readdirres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_readdirres
op_star
id|resp
)paren
(brace
id|p
op_add_assign
id|XDR_QUADLEN
c_func
(paren
id|resp-&gt;count
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_statfsres
id|nfssvc_encode_statfsres
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_statfsres
op_star
id|resp
)paren
(brace
r_struct
id|statfs
op_star
id|stat
op_assign
op_amp
id|resp-&gt;stats
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
l_int|8
op_star
l_int|1024
)paren
suffix:semicolon
multiline_comment|/* max transfer size */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bsize
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_blocks
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bfree
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|stat-&gt;f_bavail
)paren
suffix:semicolon
r_return
id|xdr_ressize_check
c_func
(paren
id|rqstp
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|nfssvc_encode_entry
id|nfssvc_encode_entry
c_func
(paren
r_struct
id|readdir_cd
op_star
id|cd
comma
r_const
r_char
op_star
id|name
comma
r_int
id|namlen
comma
id|off_t
id|offset
comma
id|ino_t
id|ino
)paren
(brace
id|u32
op_star
id|p
op_assign
id|cd-&gt;buffer
suffix:semicolon
r_int
id|buflen
comma
id|slen
suffix:semicolon
multiline_comment|/*&n;&t;dprintk(&quot;nfsd: entry(%.*s off %ld ino %ld)&bslash;n&quot;,&n;&t;&t;&t;namlen, name, offset, ino);&n;&t; */
r_if
c_cond
(paren
id|offset
OG
op_complement
(paren
(paren
id|u32
)paren
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|cd-&gt;offset
)paren
op_star
id|cd-&gt;offset
op_assign
id|htonl
c_func
(paren
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|namlen
OG
id|NFS2_MAXNAMLEN
)paren
id|namlen
op_assign
id|NFS2_MAXNAMLEN
suffix:semicolon
multiline_comment|/* truncate filename */
id|slen
op_assign
id|XDR_QUADLEN
c_func
(paren
id|namlen
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buflen
op_assign
id|cd-&gt;buflen
op_minus
id|slen
op_minus
l_int|4
)paren
OL
l_int|0
)paren
(brace
id|cd-&gt;eob
op_assign
l_int|1
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|p
op_increment
op_assign
id|xdr_one
suffix:semicolon
multiline_comment|/* mark entry present */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|ino
)paren
suffix:semicolon
multiline_comment|/* file id */
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
(paren
id|u32
)paren
id|namlen
)paren
suffix:semicolon
multiline_comment|/* name length &amp; name */
id|memcpy
c_func
(paren
id|p
comma
id|name
comma
id|namlen
)paren
suffix:semicolon
id|p
op_add_assign
id|slen
suffix:semicolon
id|cd-&gt;offset
op_assign
id|p
suffix:semicolon
multiline_comment|/* remember pointer */
op_star
id|p
op_increment
op_assign
op_complement
(paren
id|u32
)paren
l_int|0
suffix:semicolon
multiline_comment|/* offset of next entry */
id|cd-&gt;buflen
op_assign
id|buflen
suffix:semicolon
id|cd-&gt;buffer
op_assign
id|p
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR release functions&n; */
r_int
DECL|function|nfssvc_release_fhandle
id|nfssvc_release_fhandle
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|p
comma
r_struct
id|nfsd_fhandle
op_star
id|resp
)paren
(brace
id|fh_put
c_func
(paren
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof