multiline_comment|/*&n; * linux/fs/nfs/mount_clnt.c&n; *&n; * MOUNT client to support NFSroot.&n; *&n; * Copyright (C) 1997, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/xprt.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFSDBG_FACILITY
macro_line|# define NFSDBG_FACILITY&t;NFSDBG_ROOT
macro_line|#endif
multiline_comment|/*&n;#define MOUNT_PROGRAM&t;&t;100005&n;#define MOUNT_VERSION&t;&t;1&n;#define MOUNT_MNT&t;&t;1&n;#define MOUNT_UMNT&t;&t;3&n; */
r_static
r_struct
id|rpc_clnt
op_star
id|mnt_create
c_func
(paren
r_char
op_star
comma
r_struct
id|sockaddr_in
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|rpc_program
id|mnt_program
suffix:semicolon
DECL|struct|mnt_fhstatus
r_struct
id|mnt_fhstatus
(brace
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
DECL|member|fh
r_struct
id|nfs_fh
op_star
id|fh
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Obtain an NFS file handle for the given host and path&n; */
r_int
DECL|function|nfs_mount
id|nfs_mount
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|addr
comma
r_char
op_star
id|path
comma
r_struct
id|nfs_fh
op_star
id|fh
)paren
(brace
r_struct
id|rpc_clnt
op_star
id|mnt_clnt
suffix:semicolon
r_struct
id|mnt_fhstatus
id|result
op_assign
(brace
l_int|0
comma
id|fh
)brace
suffix:semicolon
r_char
id|hostname
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS:      nfs_mount(%08lx:%s)&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
comma
id|path
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|hostname
comma
id|in_ntoa
c_func
(paren
id|addr-&gt;sin_addr.s_addr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mnt_clnt
op_assign
id|mnt_create
c_func
(paren
id|hostname
comma
id|addr
)paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|mnt_clnt
comma
id|NFS_MNTPROC_MNT
comma
id|path
comma
op_amp
id|result
comma
l_int|0
)paren
suffix:semicolon
r_return
id|status
OL
l_int|0
ques
c_cond
id|status
suffix:colon
(paren
id|result.status
ques
c_cond
op_minus
id|EACCES
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_struct
id|rpc_clnt
op_star
DECL|function|mnt_create
id|mnt_create
c_func
(paren
r_char
op_star
id|hostname
comma
r_struct
id|sockaddr_in
op_star
id|srvaddr
)paren
(brace
r_struct
id|rpc_xprt
op_star
id|xprt
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|IPPROTO_UDP
comma
id|srvaddr
comma
l_int|NULL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
id|hostname
comma
op_amp
id|mnt_program
comma
id|NFS_MNT_VERSION
comma
id|RPC_AUTH_NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clnt
)paren
(brace
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
)brace
r_else
(brace
id|clnt-&gt;cl_softrtry
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
l_int|1
suffix:semicolon
id|clnt-&gt;cl_oneshot
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|clnt
suffix:semicolon
)brace
multiline_comment|/*&n; * XDR encode/decode functions for MOUNT&n; */
r_static
r_int
DECL|function|xdr_error
id|xdr_error
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
op_minus
id|EIO
suffix:semicolon
)brace
r_static
r_int
DECL|function|xdr_encode_dirpath
id|xdr_encode_dirpath
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
r_const
r_char
op_star
id|path
)paren
(brace
id|p
op_assign
id|xdr_encode_string
c_func
(paren
id|p
comma
id|path
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
r_static
r_int
DECL|function|xdr_decode_fhstatus
id|xdr_decode_fhstatus
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
id|mnt_fhstatus
op_star
id|res
)paren
(brace
r_if
c_cond
(paren
(paren
id|res-&gt;status
op_assign
id|ntohl
c_func
(paren
op_star
id|p
op_increment
)paren
)paren
op_eq
l_int|0
)paren
id|memcpy
c_func
(paren
id|res-&gt;fh
comma
id|p
comma
r_sizeof
(paren
op_star
id|res-&gt;fh
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|MNT_dirpath_sz
mdefine_line|#define MNT_dirpath_sz&t;&t;(1 + 256)
DECL|macro|MNT_fhstatus_sz
mdefine_line|#define MNT_fhstatus_sz&t;&t;(1 + 8)
DECL|variable|mnt_procedures
r_static
r_struct
id|rpc_procinfo
id|mnt_procedures
(braket
l_int|2
)braket
op_assign
(brace
(brace
l_string|&quot;mnt_null&quot;
comma
(paren
id|kxdrproc_t
)paren
id|xdr_error
comma
(paren
id|kxdrproc_t
)paren
id|xdr_error
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_string|&quot;mnt_mount&quot;
comma
(paren
id|kxdrproc_t
)paren
id|xdr_encode_dirpath
comma
(paren
id|kxdrproc_t
)paren
id|xdr_decode_fhstatus
comma
id|MNT_dirpath_sz
comma
id|MNT_fhstatus_sz
)brace
comma
)brace
suffix:semicolon
DECL|variable|mnt_version1
r_static
r_struct
id|rpc_version
id|mnt_version1
op_assign
(brace
l_int|1
comma
l_int|2
comma
id|mnt_procedures
)brace
suffix:semicolon
DECL|variable|mnt_version
r_static
r_struct
id|rpc_version
op_star
id|mnt_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
op_amp
id|mnt_version1
comma
)brace
suffix:semicolon
DECL|variable|mnt_stats
r_static
r_struct
id|rpc_stat
id|mnt_stats
suffix:semicolon
DECL|variable|mnt_program
r_struct
id|rpc_program
id|mnt_program
op_assign
(brace
l_string|&quot;mount&quot;
comma
id|NFS_MNT_PROGRAM
comma
r_sizeof
(paren
id|mnt_version
)paren
op_div
r_sizeof
(paren
id|mnt_version
(braket
l_int|0
)braket
)paren
comma
id|mnt_version
comma
op_amp
id|mnt_stats
comma
)brace
suffix:semicolon
eof
