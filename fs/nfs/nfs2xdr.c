multiline_comment|/*&n; * linux/fs/nfs/xdr.c&n; *&n; * XDR functions to encode/decode NFS RPC arguments and results.&n; *&n; * Copyright (C) 1992, 1993, 1994  Rick Sladkey&n; * Copyright (C) 1996 Olaf Kirch&n; */
DECL|macro|NFS_NEED_XDR_TYPES
mdefine_line|#define NFS_NEED_XDR_TYPES
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_XDR
DECL|macro|QUADLEN
mdefine_line|#define QUADLEN(len)&t;&t;(((len) + 3) &gt;&gt; 2)
r_static
r_int
id|nfs_stat_to_errno
c_func
(paren
r_int
id|stat
)paren
suffix:semicolon
multiline_comment|/* Mapping from NFS error code to &quot;errno&quot; error code. */
DECL|macro|errno_NFSERR_IO
mdefine_line|#define errno_NFSERR_IO&t;&t;EIO
multiline_comment|/*&n; * Declare the space requirements for NFS arguments and replies as&n; * number of 32bit-words&n; */
DECL|macro|NFS_fhandle_sz
mdefine_line|#define NFS_fhandle_sz&t;&t;8
DECL|macro|NFS_sattr_sz
mdefine_line|#define NFS_sattr_sz&t;&t;8
DECL|macro|NFS_filename_sz
mdefine_line|#define NFS_filename_sz&t;&t;1+(NFS_MAXNAMLEN&gt;&gt;2)
DECL|macro|NFS_path_sz
mdefine_line|#define NFS_path_sz&t;&t;1+(NFS_MAXPATHLEN&gt;&gt;2)
DECL|macro|NFS_fattr_sz
mdefine_line|#define NFS_fattr_sz&t;&t;17
DECL|macro|NFS_info_sz
mdefine_line|#define NFS_info_sz&t;&t;5
DECL|macro|NFS_entry_sz
mdefine_line|#define NFS_entry_sz&t;&t;NFS_filename_sz+3
DECL|macro|NFS_enc_void_sz
mdefine_line|#define NFS_enc_void_sz&t;&t;0
DECL|macro|NFS_diropargs_sz
mdefine_line|#define NFS_diropargs_sz&t;NFS_fhandle_sz+NFS_filename_sz
DECL|macro|NFS_sattrargs_sz
mdefine_line|#define NFS_sattrargs_sz&t;NFS_fhandle_sz+NFS_sattr_sz
DECL|macro|NFS_readargs_sz
mdefine_line|#define NFS_readargs_sz&t;&t;NFS_fhandle_sz+3
DECL|macro|NFS_writeargs_sz
mdefine_line|#define NFS_writeargs_sz&t;NFS_fhandle_sz+4
DECL|macro|NFS_createargs_sz
mdefine_line|#define NFS_createargs_sz&t;NFS_diropargs_sz+NFS_sattr_sz
DECL|macro|NFS_renameargs_sz
mdefine_line|#define NFS_renameargs_sz&t;NFS_diropargs_sz+NFS_diropargs_sz
DECL|macro|NFS_linkargs_sz
mdefine_line|#define NFS_linkargs_sz&t;&t;NFS_fhandle_sz+NFS_diropargs_sz
DECL|macro|NFS_symlinkargs_sz
mdefine_line|#define NFS_symlinkargs_sz&t;NFS_diropargs_sz+NFS_path_sz+NFS_sattr_sz
DECL|macro|NFS_readdirargs_sz
mdefine_line|#define NFS_readdirargs_sz&t;NFS_fhandle_sz+2
DECL|macro|NFS_dec_void_sz
mdefine_line|#define NFS_dec_void_sz&t;&t;0
DECL|macro|NFS_attrstat_sz
mdefine_line|#define NFS_attrstat_sz&t;&t;1+NFS_fattr_sz
DECL|macro|NFS_diropres_sz
mdefine_line|#define NFS_diropres_sz&t;&t;1+NFS_fhandle_sz+NFS_fattr_sz
DECL|macro|NFS_readlinkres_sz
mdefine_line|#define NFS_readlinkres_sz&t;1+NFS_path_sz
DECL|macro|NFS_readres_sz
mdefine_line|#define NFS_readres_sz&t;&t;1+NFS_fattr_sz+1
DECL|macro|NFS_stat_sz
mdefine_line|#define NFS_stat_sz&t;&t;1
DECL|macro|NFS_readdirres_sz
mdefine_line|#define NFS_readdirres_sz&t;1
DECL|macro|NFS_statfsres_sz
mdefine_line|#define NFS_statfsres_sz&t;1+NFS_info_sz
multiline_comment|/*&n; * Common NFS XDR functions as inlines&n; */
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_fhandle
id|xdr_encode_fhandle
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
(brace
op_star
(paren
(paren
r_struct
id|nfs_fh
op_star
)paren
id|p
)paren
op_assign
op_star
id|fhandle
suffix:semicolon
r_return
id|p
op_plus
id|QUADLEN
c_func
(paren
r_sizeof
(paren
op_star
id|fhandle
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_fhandle
id|xdr_decode_fhandle
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fhandle
)paren
(brace
op_star
id|fhandle
op_assign
op_star
(paren
(paren
r_struct
id|nfs_fh
op_star
)paren
id|p
)paren
suffix:semicolon
r_return
id|p
op_plus
id|QUADLEN
c_func
(paren
r_sizeof
(paren
op_star
id|fhandle
)paren
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_string2
id|xdr_decode_string2
c_func
(paren
id|u32
op_star
id|p
comma
r_char
op_star
op_star
id|string
comma
r_int
r_int
op_star
id|len
comma
r_int
r_int
id|maxlen
)paren
(brace
op_star
id|len
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
op_star
id|len
OG
id|maxlen
)paren
r_return
l_int|NULL
suffix:semicolon
op_star
id|string
op_assign
(paren
r_char
op_star
)paren
id|p
suffix:semicolon
r_return
id|p
op_plus
id|QUADLEN
c_func
(paren
op_star
id|len
)paren
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_decode_fattr
id|xdr_decode_fattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
id|fattr-&gt;type
op_assign
(paren
r_enum
id|nfs_ftype
)paren
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;mode
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;nlink
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;uid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;gid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;size
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;blocksize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;rdev
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;blocks
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;fsid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;fileid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;atime.seconds
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;atime.useconds
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;mtime.seconds
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;mtime.useconds
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;ctime.seconds
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|fattr-&gt;ctime.useconds
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
id|p
suffix:semicolon
)brace
r_static
r_inline
id|u32
op_star
DECL|function|xdr_encode_sattr
id|xdr_encode_sattr
c_func
(paren
id|u32
op_star
id|p
comma
r_struct
id|nfs_sattr
op_star
id|sattr
)paren
(brace
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;mode
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;uid
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;gid
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;size
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;atime.seconds
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;atime.useconds
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;mtime.seconds
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|sattr-&gt;mtime.useconds
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * NFS encode functions&n; */
multiline_comment|/*&n; * Encode void argument&n; */
r_static
r_int
DECL|function|nfs_xdr_enc_void
id|nfs_xdr_enc_void
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode file handle argument&n; * GETATTR, READLINK, STATFS&n; */
r_static
r_int
DECL|function|nfs_xdr_fhandle
id|nfs_xdr_fhandle
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_fh
op_star
id|fh
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|fh
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode SETATTR arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_sattrargs
id|nfs_xdr_sattrargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_sattrargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode directory ops argument&n; * LOOKUP, REMOVE, RMDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_diropargs
id|nfs_xdr_diropargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_diropargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;name
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Arguments to a READ call. Since we read data directly into the page&n; * cache, we also set up the reply iovec here so that iov[1] points&n; * exactly to the page wewant to fetch.&n; */
r_static
r_int
DECL|function|nfs_xdr_readargs
id|nfs_xdr_readargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readargs
op_star
id|args
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|req-&gt;rq_task-&gt;tk_auth
suffix:semicolon
r_int
id|replen
comma
id|buflen
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;count
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;count
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
macro_line|#if 1
multiline_comment|/* set up reply iovec */
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
id|buflen
op_assign
id|req-&gt;rq_rvec
(braket
l_int|0
)braket
dot
id|iov_len
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|replen
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
id|args-&gt;buffer
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|args-&gt;count
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|2
)braket
dot
id|iov_base
op_assign
(paren
id|u8
op_star
)paren
id|req-&gt;rq_rvec
(braket
l_int|0
)braket
dot
id|iov_base
op_plus
id|replen
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|2
)braket
dot
id|iov_len
op_assign
id|buflen
op_minus
id|replen
suffix:semicolon
id|req-&gt;rq_rlen
op_assign
id|args-&gt;count
op_plus
id|buflen
suffix:semicolon
id|req-&gt;rq_rnr
op_assign
l_int|3
suffix:semicolon
macro_line|#else
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|replen
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode READ reply&n; */
r_static
r_int
DECL|function|nfs_xdr_readres
id|nfs_xdr_readres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readres
op_star
id|res
)paren
(brace
r_struct
id|iovec
op_star
id|iov
op_assign
id|req-&gt;rq_rvec
suffix:semicolon
r_int
id|status
comma
id|count
comma
id|recvd
comma
id|hdrlen
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      readres OK status %lx&bslash;n&quot;
comma
id|ntohl
c_func
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|res-&gt;fattr
)paren
suffix:semicolon
id|count
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|hdrlen
op_assign
(paren
id|u8
op_star
)paren
id|p
op_minus
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
suffix:semicolon
id|recvd
op_assign
id|req-&gt;rq_rlen
op_minus
id|hdrlen
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ne
id|iov
(braket
l_int|2
)braket
dot
id|iov_base
)paren
(brace
multiline_comment|/* Unexpected reply header size. Punt.&n;&t;&t; * XXX: Move iovec contents to align data on page&n;&t;&t; * boundary and adjust RPC header size guess */
id|printk
c_func
(paren
l_string|&quot;NFS: Odd RPC header size in read reply: %d&bslash;n&quot;
comma
id|hdrlen
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
id|recvd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: server cheating in read reply: &quot;
l_string|&quot;count %d &gt; recvd %d&bslash;n&quot;
comma
id|count
comma
id|recvd
)paren
suffix:semicolon
id|count
op_assign
id|recvd
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;RPC:      readres OK count %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|res-&gt;count
)paren
id|memset
c_func
(paren
(paren
id|u8
op_star
)paren
(paren
id|iov
(braket
l_int|1
)braket
dot
id|iov_base
op_plus
id|count
)paren
comma
l_int|0
comma
id|res-&gt;count
op_minus
id|count
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
multiline_comment|/*&n; * Write arguments. Splice the buffer to be written into the iovec.&n; */
r_static
r_int
DECL|function|nfs_xdr_writeargs
id|nfs_xdr_writeargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_writeargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;offset
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;count
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;count
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
id|req-&gt;rq_svec
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
(paren
r_void
op_star
)paren
id|args-&gt;buffer
suffix:semicolon
id|req-&gt;rq_svec
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|args-&gt;count
suffix:semicolon
id|req-&gt;rq_slen
op_add_assign
id|args-&gt;count
suffix:semicolon
id|req-&gt;rq_snr
op_assign
l_int|2
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode create arguments&n; * CREATE, MKDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_createargs
id|nfs_xdr_createargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_createargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;name
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode RENAME arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_renameargs
id|nfs_xdr_renameargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_renameargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;fromname
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;tofh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;toname
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode LINK arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_linkargs
id|nfs_xdr_linkargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_linkargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;tofh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;toname
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode SYMLINK arguments&n; */
r_static
r_int
DECL|function|nfs_xdr_symlinkargs
id|nfs_xdr_symlinkargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_symlinkargs
op_star
id|args
)paren
(brace
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fromfh
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;fromname
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|args-&gt;topath
)paren
suffix:semicolon
id|p
op_assign
id|xdr_encode_sattr
c_func
(paren
id|p
comma
id|args-&gt;sattr
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Encode arguments to readdir call&n; */
r_static
r_int
DECL|function|nfs_xdr_readdirargs
id|nfs_xdr_readdirargs
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readdirargs
op_star
id|args
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|req-&gt;rq_task-&gt;tk_auth
suffix:semicolon
r_int
id|replen
suffix:semicolon
id|p
op_assign
id|xdr_encode_fhandle
c_func
(paren
id|p
comma
id|args-&gt;fh
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;cookie
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|htonl
c_func
(paren
id|args-&gt;bufsiz
)paren
suffix:semicolon
id|req-&gt;rq_slen
op_assign
id|xdr_adjust_iovec
c_func
(paren
id|req-&gt;rq_svec
comma
id|p
)paren
suffix:semicolon
multiline_comment|/* set up reply iovec */
id|replen
op_assign
(paren
id|RPC_REPHDRSIZE
op_plus
id|auth-&gt;au_rslack
op_plus
id|NFS_readdirres_sz
)paren
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t;dprintk(&quot;RPC: readdirargs: slack is 4 * (%d + %d + %d) = %d&bslash;n&quot;,&n;&t;&t;RPC_REPHDRSIZE, auth-&gt;au_rslack, NFS_readdirres_sz, replen);&n;&t; */
id|req-&gt;rq_rvec
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|replen
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|1
)braket
dot
id|iov_base
op_assign
id|args-&gt;buffer
suffix:semicolon
id|req-&gt;rq_rvec
(braket
l_int|1
)braket
dot
id|iov_len
op_assign
id|args-&gt;bufsiz
suffix:semicolon
id|req-&gt;rq_rlen
op_assign
id|replen
op_plus
id|args-&gt;bufsiz
suffix:semicolon
id|req-&gt;rq_rnr
op_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n;&t;dprintk(&quot;RPC:      readdirargs set up reply vec:&bslash;n&quot;);&n;&t;dprintk(&quot;          rvec[0] = %p/%d&bslash;n&quot;,&n;&t;&t;&t;req-&gt;rq_rvec[0].iov_base,&n;&t;&t;&t;req-&gt;rq_rvec[0].iov_len);&n;&t;dprintk(&quot;          rvec[1] = %p/%d&bslash;n&quot;,&n;&t;&t;&t;req-&gt;rq_rvec[1].iov_base,&n;&t;&t;&t;req-&gt;rq_rvec[1].iov_len);&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode the result of a readdir call. We decode the result in place&n; * to avoid a malloc of NFS_MAXNAMLEN+1 for each file name.&n; * After decoding, the layout in memory looks like this:&n; *&t;entry1 entry2 ... entryN &lt;space&gt; stringN ... string2 string1&n; * Note that the strings are not null-terminated so that the entire number&n; * of entries returned by the server should fit into the buffer.&n; */
r_static
r_int
DECL|function|nfs_xdr_readdirres
id|nfs_xdr_readdirres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readdirres
op_star
id|res
)paren
(brace
r_struct
id|nfs_entry
op_star
id|entry
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
op_assign
id|req-&gt;rq_rvec
suffix:semicolon
r_int
id|status
comma
id|nr
comma
id|len
suffix:semicolon
r_char
op_star
id|string
suffix:semicolon
id|u32
op_star
id|end
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|p
op_ne
(paren
(paren
id|u8
op_star
)paren
id|iov-&gt;iov_base
op_plus
id|iov-&gt;iov_len
)paren
)paren
(brace
multiline_comment|/* Unexpected reply header size. Punt. */
id|printk
c_func
(paren
l_string|&quot;NFS: Odd RPC header size in readdirres reply&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
multiline_comment|/* Get start and end address of XDR data */
id|p
op_assign
(paren
id|u32
op_star
)paren
id|iov
(braket
l_int|1
)braket
dot
id|iov_base
suffix:semicolon
id|end
op_assign
(paren
id|u32
op_star
)paren
(paren
(paren
id|u8
op_star
)paren
id|p
op_plus
id|iov
(braket
l_int|1
)braket
dot
id|iov_len
)paren
suffix:semicolon
multiline_comment|/* Get start and end of dirent buffer */
id|entry
op_assign
(paren
r_struct
id|nfs_entry
op_star
)paren
id|res-&gt;buffer
suffix:semicolon
id|string
op_assign
(paren
r_char
op_star
)paren
id|res-&gt;buffer
op_plus
id|res-&gt;bufsiz
suffix:semicolon
r_for
c_loop
(paren
id|nr
op_assign
l_int|0
suffix:semicolon
op_star
id|p
op_increment
suffix:semicolon
id|nr
op_increment
comma
id|entry
op_increment
)paren
(brace
id|entry-&gt;fileid
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|len
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
(paren
id|p
op_plus
id|QUADLEN
c_func
(paren
id|len
)paren
op_plus
l_int|3
)paren
OG
id|end
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NFS: short packet in readdir reply!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
OG
id|NFS_MAXNAMLEN
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: giant filename in readdir (len %x)!&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
id|errno_NFSERR_IO
suffix:semicolon
)brace
id|string
op_sub_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
(paren
id|entry
op_plus
l_int|1
)paren
OG
(paren
r_void
op_star
)paren
id|string
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NFS: should not happen in %s!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NFS: len = %d, entry+1=%p, string=%p&bslash;n&quot;
comma
id|len
comma
id|entry
op_plus
l_int|1
comma
id|string
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|entry-&gt;name
op_assign
id|string
suffix:semicolon
id|entry-&gt;length
op_assign
id|len
suffix:semicolon
id|memmove
c_func
(paren
id|string
comma
id|p
comma
id|len
)paren
suffix:semicolon
id|p
op_add_assign
id|QUADLEN
c_func
(paren
id|len
)paren
suffix:semicolon
id|entry-&gt;cookie
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|entry-&gt;eof
op_assign
op_logical_neg
id|p
(braket
l_int|0
)braket
op_logical_and
id|p
(braket
l_int|1
)braket
suffix:semicolon
)brace
r_return
id|nr
suffix:semicolon
)brace
multiline_comment|/*&n; * NFS XDR decode functions&n; */
multiline_comment|/*&n; * Decode void reply&n; */
r_static
r_int
DECL|function|nfs_xdr_dec_void
id|nfs_xdr_dec_void
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode simple status reply&n; */
r_static
r_int
DECL|function|nfs_xdr_stat
id|nfs_xdr_stat
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
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
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
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
l_int|0
)paren
id|status
op_assign
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode attrstat reply&n; * GETATTR, SETATTR, WRITE&n; */
r_static
r_int
DECL|function|nfs_xdr_attrstat
id|nfs_xdr_attrstat
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      attrstat status %lx&bslash;n&quot;
comma
id|ntohl
c_func
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|fattr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      attrstat OK type %d mode %o dev %x ino %x&bslash;n&quot;
comma
id|fattr-&gt;type
comma
id|fattr-&gt;mode
comma
id|fattr-&gt;fsid
comma
id|fattr-&gt;fileid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode diropres reply&n; * LOOKUP, CREATE, MKDIR&n; */
r_static
r_int
DECL|function|nfs_xdr_diropres
id|nfs_xdr_diropres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_diropok
op_star
id|res
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      diropres status %lx&bslash;n&quot;
comma
id|ntohl
c_func
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|p
op_assign
id|xdr_decode_fhandle
c_func
(paren
id|p
comma
id|res-&gt;fh
)paren
suffix:semicolon
id|xdr_decode_fattr
c_func
(paren
id|p
comma
id|res-&gt;fattr
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC:      diropres OK type %x mode %o dev %x ino %x&bslash;n&quot;
comma
id|res-&gt;fattr-&gt;type
comma
id|res-&gt;fattr-&gt;mode
comma
id|res-&gt;fattr-&gt;fsid
comma
id|res-&gt;fattr-&gt;fileid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode READLINK reply&n; */
r_static
r_int
DECL|function|nfs_xdr_readlinkres
id|nfs_xdr_readlinkres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_readlinkres
op_star
id|res
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|xdr_decode_string2
c_func
(paren
id|p
comma
id|res-&gt;string
comma
id|res-&gt;lenp
comma
id|res-&gt;maxlen
)paren
suffix:semicolon
multiline_comment|/* Caller takes over the buffer here to avoid extra copy */
id|res-&gt;buffer
op_assign
id|req-&gt;rq_task-&gt;tk_buffer
suffix:semicolon
id|req-&gt;rq_task-&gt;tk_buffer
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Decode STATFS reply&n; */
r_static
r_int
DECL|function|nfs_xdr_statfsres
id|nfs_xdr_statfsres
c_func
(paren
r_struct
id|rpc_rqst
op_star
id|req
comma
id|u32
op_star
id|p
comma
r_struct
id|nfs_fsinfo
op_star
id|res
)paren
(brace
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
)paren
r_return
op_minus
id|nfs_stat_to_errno
c_func
(paren
id|status
)paren
suffix:semicolon
id|res-&gt;tsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bsize
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;blocks
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bfree
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
suffix:semicolon
id|res-&gt;bavail
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to translate between nfs status return values and&n; * the local errno values which may not be the same.&n; */
r_static
r_struct
(brace
DECL|member|stat
r_int
id|stat
suffix:semicolon
DECL|member|errno
r_int
id|errno
suffix:semicolon
DECL|variable|nfs_errtbl
)brace
id|nfs_errtbl
(braket
)braket
op_assign
(brace
(brace
id|NFS_OK
comma
l_int|0
)brace
comma
(brace
id|NFSERR_PERM
comma
id|EPERM
)brace
comma
(brace
id|NFSERR_NOENT
comma
id|ENOENT
)brace
comma
(brace
id|NFSERR_IO
comma
id|errno_NFSERR_IO
)brace
comma
(brace
id|NFSERR_NXIO
comma
id|ENXIO
)brace
comma
(brace
id|NFSERR_EAGAIN
comma
id|EAGAIN
)brace
comma
(brace
id|NFSERR_ACCES
comma
id|EACCES
)brace
comma
(brace
id|NFSERR_EXIST
comma
id|EEXIST
)brace
comma
(brace
id|NFSERR_NODEV
comma
id|ENODEV
)brace
comma
(brace
id|NFSERR_NOTDIR
comma
id|ENOTDIR
)brace
comma
(brace
id|NFSERR_ISDIR
comma
id|EISDIR
)brace
comma
(brace
id|NFSERR_INVAL
comma
id|EINVAL
)brace
comma
(brace
id|NFSERR_FBIG
comma
id|EFBIG
)brace
comma
(brace
id|NFSERR_NOSPC
comma
id|ENOSPC
)brace
comma
(brace
id|NFSERR_ROFS
comma
id|EROFS
)brace
comma
(brace
id|NFSERR_NAMETOOLONG
comma
id|ENAMETOOLONG
)brace
comma
(brace
id|NFSERR_NOTEMPTY
comma
id|ENOTEMPTY
)brace
comma
(brace
id|NFSERR_DQUOT
comma
id|EDQUOT
)brace
comma
(brace
id|NFSERR_STALE
comma
id|ESTALE
)brace
comma
macro_line|#ifdef EWFLUSH
(brace
id|NFSERR_WFLUSH
comma
id|EWFLUSH
)brace
comma
macro_line|#endif
(brace
op_minus
l_int|1
comma
id|EIO
)brace
)brace
suffix:semicolon
r_static
r_int
DECL|function|nfs_stat_to_errno
id|nfs_stat_to_errno
c_func
(paren
r_int
id|stat
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|nfs_errtbl
(braket
id|i
)braket
dot
id|stat
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nfs_errtbl
(braket
id|i
)braket
dot
id|stat
op_eq
id|stat
)paren
r_return
id|nfs_errtbl
(braket
id|i
)braket
dot
id|errno
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;nfs_stat_to_errno: bad nfs status return value: %d&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|nfs_errtbl
(braket
id|i
)braket
dot
id|errno
suffix:semicolon
)brace
macro_line|#ifndef MAX
DECL|macro|MAX
macro_line|# define MAX(a, b)&t;(((a) &gt; (b))? (a) : (b))
macro_line|#endif
DECL|macro|PROC
mdefine_line|#define PROC(proc, argtype, restype)&t;&bslash;&n;    { &quot;nfs_&quot; #proc,&t;&t;&t;&t;&t;&bslash;&n;      (kxdrproc_t) nfs_xdr_##argtype,&t;&t;&t;&bslash;&n;      (kxdrproc_t) nfs_xdr_##restype,&t;&t;&t;&bslash;&n;      MAX(NFS_##argtype##_sz,NFS_##restype##_sz) &lt;&lt; 2&t;&bslash;&n;    }
DECL|variable|nfs_procedures
r_static
r_struct
id|rpc_procinfo
id|nfs_procedures
(braket
l_int|18
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
id|enc_void
comma
id|dec_void
)paren
comma
id|PROC
c_func
(paren
id|getattr
comma
id|fhandle
comma
id|attrstat
)paren
comma
id|PROC
c_func
(paren
id|setattr
comma
id|sattrargs
comma
id|attrstat
)paren
comma
id|PROC
c_func
(paren
id|root
comma
id|enc_void
comma
id|dec_void
)paren
comma
id|PROC
c_func
(paren
id|lookup
comma
id|diropargs
comma
id|diropres
)paren
comma
id|PROC
c_func
(paren
id|readlink
comma
id|fhandle
comma
id|readlinkres
)paren
comma
id|PROC
c_func
(paren
id|read
comma
id|readargs
comma
id|readres
)paren
comma
id|PROC
c_func
(paren
id|writecache
comma
id|enc_void
comma
id|dec_void
)paren
comma
id|PROC
c_func
(paren
id|write
comma
id|writeargs
comma
id|attrstat
)paren
comma
id|PROC
c_func
(paren
id|create
comma
id|createargs
comma
id|diropres
)paren
comma
id|PROC
c_func
(paren
id|remove
comma
id|diropargs
comma
id|stat
)paren
comma
id|PROC
c_func
(paren
id|rename
comma
id|renameargs
comma
id|stat
)paren
comma
id|PROC
c_func
(paren
id|link
comma
id|linkargs
comma
id|stat
)paren
comma
id|PROC
c_func
(paren
id|symlink
comma
id|symlinkargs
comma
id|stat
)paren
comma
id|PROC
c_func
(paren
id|mkdir
comma
id|createargs
comma
id|diropres
)paren
comma
id|PROC
c_func
(paren
id|rmdir
comma
id|diropargs
comma
id|stat
)paren
comma
id|PROC
c_func
(paren
id|readdir
comma
id|readdirargs
comma
id|readdirres
)paren
comma
id|PROC
c_func
(paren
id|statfs
comma
id|fhandle
comma
id|statfsres
)paren
comma
)brace
suffix:semicolon
DECL|variable|nfs_version2
r_static
r_struct
id|rpc_version
id|nfs_version2
op_assign
(brace
l_int|2
comma
r_sizeof
(paren
id|nfs_procedures
)paren
op_div
r_sizeof
(paren
id|nfs_procedures
(braket
l_int|0
)braket
)paren
comma
id|nfs_procedures
)brace
suffix:semicolon
DECL|variable|nfs_version
r_static
r_struct
id|rpc_version
op_star
id|nfs_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|nfs_version2
)brace
suffix:semicolon
DECL|variable|nfs_program
r_struct
id|rpc_program
id|nfs_program
op_assign
(brace
l_string|&quot;nfs&quot;
comma
id|NFS_PROGRAM
comma
r_sizeof
(paren
id|nfs_version
)paren
op_div
r_sizeof
(paren
id|nfs_version
(braket
l_int|0
)braket
)paren
comma
id|nfs_version
comma
op_amp
id|nfs_rpcstat
comma
)brace
suffix:semicolon
eof
