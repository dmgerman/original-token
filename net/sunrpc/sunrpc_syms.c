multiline_comment|/*&n; * linux/net/sunrpc/sunrpc_syms.c&n; *&n; * Symbols exported by the sunrpc module.&n; *&n; * Copyright (C) 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/sunrpc/auth.h&gt;
multiline_comment|/* RPC scheduler */
DECL|variable|rpc_allocate
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_allocate
)paren
suffix:semicolon
DECL|variable|rpc_free
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_free
)paren
suffix:semicolon
DECL|variable|rpc_execute
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_execute
)paren
suffix:semicolon
DECL|variable|rpc_init_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_init_task
)paren
suffix:semicolon
DECL|variable|rpc_release_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_release_task
)paren
suffix:semicolon
DECL|variable|rpc_sleep_on
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_sleep_on
)paren
suffix:semicolon
DECL|variable|rpc_wake_up_next
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up_next
)paren
suffix:semicolon
DECL|variable|rpc_wake_up_task
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_wake_up_task
)paren
suffix:semicolon
DECL|variable|rpc_new_child
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_new_child
)paren
suffix:semicolon
DECL|variable|rpc_run_child
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_run_child
)paren
suffix:semicolon
DECL|variable|rpciod_down
id|EXPORT_SYMBOL
c_func
(paren
id|rpciod_down
)paren
suffix:semicolon
DECL|variable|rpciod_up
id|EXPORT_SYMBOL
c_func
(paren
id|rpciod_up
)paren
suffix:semicolon
multiline_comment|/* RPC client functions */
DECL|variable|rpc_create_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_create_client
)paren
suffix:semicolon
DECL|variable|rpc_destroy_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_destroy_client
)paren
suffix:semicolon
DECL|variable|rpc_shutdown_client
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_shutdown_client
)paren
suffix:semicolon
DECL|variable|rpc_do_call
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_do_call
)paren
suffix:semicolon
DECL|variable|rpc_call_setup
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_call_setup
)paren
suffix:semicolon
DECL|variable|rpc_delay
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_delay
)paren
suffix:semicolon
DECL|variable|rpc_restart_call
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_restart_call
)paren
suffix:semicolon
multiline_comment|/* Client transport */
DECL|variable|xprt_create_proto
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_create_proto
)paren
suffix:semicolon
DECL|variable|xprt_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_destroy
)paren
suffix:semicolon
DECL|variable|xprt_set_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|xprt_set_timeout
)paren
suffix:semicolon
multiline_comment|/* Client credential cache */
DECL|variable|rpcauth_register
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_register
)paren
suffix:semicolon
DECL|variable|rpcauth_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_unregister
)paren
suffix:semicolon
DECL|variable|rpcauth_init_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_init_credcache
)paren
suffix:semicolon
DECL|variable|rpcauth_free_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_free_credcache
)paren
suffix:semicolon
DECL|variable|rpcauth_insert_credcache
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_insert_credcache
)paren
suffix:semicolon
DECL|variable|rpcauth_lookupcred
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_lookupcred
)paren
suffix:semicolon
DECL|variable|rpcauth_matchcred
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_matchcred
)paren
suffix:semicolon
DECL|variable|rpcauth_releasecred
id|EXPORT_SYMBOL
c_func
(paren
id|rpcauth_releasecred
)paren
suffix:semicolon
multiline_comment|/* RPC server stuff */
DECL|variable|svc_create
id|EXPORT_SYMBOL
c_func
(paren
id|svc_create
)paren
suffix:semicolon
DECL|variable|svc_create_socket
id|EXPORT_SYMBOL
c_func
(paren
id|svc_create_socket
)paren
suffix:semicolon
DECL|variable|svc_create_thread
id|EXPORT_SYMBOL
c_func
(paren
id|svc_create_thread
)paren
suffix:semicolon
DECL|variable|svc_exit_thread
id|EXPORT_SYMBOL
c_func
(paren
id|svc_exit_thread
)paren
suffix:semicolon
DECL|variable|svc_destroy
id|EXPORT_SYMBOL
c_func
(paren
id|svc_destroy
)paren
suffix:semicolon
DECL|variable|svc_drop
id|EXPORT_SYMBOL
c_func
(paren
id|svc_drop
)paren
suffix:semicolon
DECL|variable|svc_process
id|EXPORT_SYMBOL
c_func
(paren
id|svc_process
)paren
suffix:semicolon
DECL|variable|svc_recv
id|EXPORT_SYMBOL
c_func
(paren
id|svc_recv
)paren
suffix:semicolon
DECL|variable|svc_wake_up
id|EXPORT_SYMBOL
c_func
(paren
id|svc_wake_up
)paren
suffix:semicolon
multiline_comment|/* RPC statistics */
macro_line|#ifdef CONFIG_PROC_FS
DECL|variable|rpc_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_register
)paren
suffix:semicolon
DECL|variable|rpc_register_sysctl
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_register_sysctl
)paren
suffix:semicolon
DECL|variable|rpc_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_unregister
)paren
suffix:semicolon
DECL|variable|rpc_proc_init
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_init
)paren
suffix:semicolon
DECL|variable|rpc_proc_read
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_proc_read
)paren
suffix:semicolon
DECL|variable|svc_proc_register
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_register
)paren
suffix:semicolon
DECL|variable|svc_proc_unregister
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_unregister
)paren
suffix:semicolon
DECL|variable|svc_proc_read
id|EXPORT_SYMBOL
c_func
(paren
id|svc_proc_read
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Generic XDR */
DECL|variable|xdr_encode_string
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_string
)paren
suffix:semicolon
DECL|variable|xdr_decode_string
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_decode_string
)paren
suffix:semicolon
DECL|variable|xdr_decode_netobj
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_decode_netobj
)paren
suffix:semicolon
DECL|variable|xdr_encode_netobj
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_encode_netobj
)paren
suffix:semicolon
DECL|variable|xdr_zero
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_zero
)paren
suffix:semicolon
DECL|variable|xdr_one
id|EXPORT_SYMBOL
c_func
(paren
id|xdr_one
)paren
suffix:semicolon
multiline_comment|/* RPC errors */
DECL|variable|rpc_success
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_success
)paren
suffix:semicolon
DECL|variable|rpc_garbage_args
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_garbage_args
)paren
suffix:semicolon
DECL|variable|rpc_system_err
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_system_err
)paren
suffix:semicolon
multiline_comment|/* Debugging symbols */
DECL|variable|rpc_debug
id|EXPORT_SYMBOL
c_func
(paren
id|rpc_debug
)paren
suffix:semicolon
DECL|variable|nfs_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nfs_debug
)paren
suffix:semicolon
DECL|variable|nfsd_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nfsd_debug
)paren
suffix:semicolon
DECL|variable|nlm_debug
id|EXPORT_SYMBOL
c_func
(paren
id|nlm_debug
)paren
suffix:semicolon
eof
