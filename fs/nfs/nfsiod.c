multiline_comment|/*&n; * linux/fs/nfs/nfsiod.c&n; *&n; * Async NFS RPC call support.&n; *&n; * When a process wants to place an asynchronous RPC call, it reserves&n; * an nfsiod slot, fills in all necessary fields including the callback&n; * handler field, and enqueues the request.&n; *&n; * This will wake up nfsiod, which calls nfs_rpc_doio to collect the&n; * reply. It then dispatches the result to the caller via the callback&n; * function, including result value and request pointer. It then re-inserts&n; * itself into the free list.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/rpcsock.h&gt;
macro_line|#include &lt;linux/nfsiod.h&gt;
DECL|variable|free_list
r_static
r_struct
id|nfsiod_req
op_star
id|free_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|active
r_static
r_int
id|active
op_assign
l_int|0
suffix:semicolon
DECL|macro|DEBUG_NFSIOD
macro_line|#undef DEBUG_NFSIOD
macro_line|#ifdef DEBUG_NFSIOD
DECL|macro|dprintk
mdefine_line|#define dprintk(args...)&t;printk(## args)
macro_line|#else
DECL|macro|dprintk
mdefine_line|#define dprintk(args...)&t;/* nothing */
macro_line|#endif
multiline_comment|/*&n; * Reserve an nfsiod slot and initialize the request struct&n; */
r_struct
id|nfsiod_req
op_star
DECL|function|nfsiod_reserve
id|nfsiod_reserve
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
id|nfsiod_done_fn_t
id|callback
)paren
(brace
r_struct
id|nfsiod_req
op_star
id|req
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|req
op_assign
id|free_list
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod_reserve: no free nfsiods&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|free_list
op_assign
id|req-&gt;rq_next
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|req-&gt;rq_rpcreq
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rpc_ioreq
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rpc_reserve
c_func
(paren
id|server-&gt;rsock
comma
op_amp
id|req-&gt;rq_rpcreq
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod_reserve failed to reserve RPC slot&bslash;n&quot;
)paren
suffix:semicolon
id|req-&gt;rq_next
op_assign
id|free_list
suffix:semicolon
id|free_list
op_assign
id|req
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|req-&gt;rq_server
op_assign
id|server
suffix:semicolon
id|req-&gt;rq_callback
op_assign
id|callback
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
r_void
DECL|function|nfsiod_release
id|nfsiod_release
c_func
(paren
r_struct
id|nfsiod_req
op_star
id|req
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod_release called&bslash;n&quot;
)paren
suffix:semicolon
id|rpc_release
c_func
(paren
id|req-&gt;rq_server-&gt;rsock
comma
op_amp
id|req-&gt;rq_rpcreq
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|req-&gt;rq_rpcreq
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|rpc_ioreq
)paren
)paren
suffix:semicolon
id|req-&gt;rq_next
op_assign
id|free_list
suffix:semicolon
id|free_list
op_assign
id|req
suffix:semicolon
)brace
multiline_comment|/*&n; * Transmit a request and put it on nfsiod&squot;s list of pending requests.&n; */
r_int
DECL|function|nfsiod_enqueue
id|nfsiod_enqueue
c_func
(paren
r_struct
id|nfsiod_req
op_star
id|req
)paren
(brace
r_int
id|result
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BIO: enqueuing request %p&bslash;n&quot;
comma
op_amp
id|req-&gt;rq_rpcreq
)paren
suffix:semicolon
id|result
op_assign
id|rpc_transmit
c_func
(paren
id|req-&gt;rq_server-&gt;rsock
comma
op_amp
id|req-&gt;rq_rpcreq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;BIO: rpc_transmit returned %d&bslash;n&quot;
comma
id|result
)paren
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;BIO: waking up nfsiod (%p)&bslash;n&quot;
comma
id|req-&gt;rq_wait
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the main nfsiod loop.&n; */
r_int
DECL|function|nfsiod
id|nfsiod
c_func
(paren
r_void
)paren
(brace
r_struct
id|nfsiod_req
id|request
comma
op_star
id|req
op_assign
op_amp
id|request
suffix:semicolon
r_int
id|result
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod %d starting&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* Insert request into free list */
id|memset
c_func
(paren
id|req
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|req
)paren
)paren
suffix:semicolon
id|req-&gt;rq_next
op_assign
id|free_list
suffix:semicolon
id|free_list
op_assign
id|req
suffix:semicolon
multiline_comment|/* Wait until user enqueues request */
id|dprintk
c_func
(paren
l_string|&quot;BIO: before: now %d nfsiod&squot;s active&bslash;n&quot;
comma
id|active
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod %d waiting&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|req-&gt;rq_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req-&gt;rq_rpcreq.rq_slot
)paren
r_continue
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BIO: nfsiod %d woken up; calling nfs_rpc_doio.&bslash;n&quot;
comma
id|current-&gt;pid
)paren
suffix:semicolon
id|active
op_increment
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;BIO: before: now %d nfsiod&squot;s active&bslash;n&quot;
comma
id|active
)paren
suffix:semicolon
id|result
op_assign
id|nfs_rpc_doio
c_func
(paren
id|req-&gt;rq_server
comma
op_amp
id|req-&gt;rq_rpcreq
comma
l_int|1
)paren
suffix:semicolon
id|req
op_member_access_from_pointer
id|rq_callback
c_func
(paren
id|result
comma
id|req
)paren
suffix:semicolon
id|active
op_decrement
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
