multiline_comment|/*&n; * linux/include/linux/nfsiod.h&n; *&n; * Declarations for asynchronous NFS RPC calls.&n; *&n; */
macro_line|#ifndef _LINUX_NFSIOD_H
DECL|macro|_LINUX_NFSIOD_H
mdefine_line|#define _LINUX_NFSIOD_H
macro_line|#include &lt;linux/rpcsock.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is the callback handler for nfsiod requests.&n; * Note that the callback procedure must NOT sleep.&n; */
r_struct
id|nfsiod_req
suffix:semicolon
DECL|typedef|nfsiod_done_fn_t
r_typedef
r_void
(paren
op_star
id|nfsiod_done_fn_t
)paren
(paren
r_int
id|result
comma
r_struct
id|nfsiod_req
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the nfsiod request struct.&n; */
DECL|struct|nfsiod_req
r_struct
id|nfsiod_req
(brace
DECL|member|rq_next
r_struct
id|nfsiod_req
op_star
id|rq_next
suffix:semicolon
DECL|member|rq_prev
r_struct
id|nfsiod_req
op_star
id|rq_prev
suffix:semicolon
DECL|member|rq_server
r_struct
id|nfs_server
op_star
id|rq_server
suffix:semicolon
DECL|member|rq_wait
r_struct
id|wait_queue
op_star
id|rq_wait
suffix:semicolon
DECL|member|rq_rpcreq
r_struct
id|rpc_ioreq
id|rq_rpcreq
suffix:semicolon
DECL|member|rq_callback
id|nfsiod_done_fn_t
id|rq_callback
suffix:semicolon
DECL|member|rq_cdata
r_void
op_star
id|rq_cdata
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|nfsiod_req
op_star
id|nfsiod_reserve
c_func
(paren
r_struct
id|nfs_server
op_star
comma
id|nfsiod_done_fn_t
)paren
suffix:semicolon
r_void
id|nfsiod_release
c_func
(paren
r_struct
id|nfsiod_req
op_star
)paren
suffix:semicolon
r_int
id|nfsiod_enqueue
c_func
(paren
r_struct
id|nfsiod_req
op_star
)paren
suffix:semicolon
r_int
id|nfsiod
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NFSIOD_H */
eof
