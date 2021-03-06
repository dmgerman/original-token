multiline_comment|/*&n; * linux/net/sunrpc/stats.c&n; *&n; * procfs-based user access to generic RPC statistics. The stats files&n; * reside in /proc/net/rpc.&n; *&n; * The read routines assume that the buffer passed in is just big enough.&n; * If you implement an RPC service that has its own stats routine which&n; * appends the generic RPC stats, make sure you don&squot;t exceed the PAGE_SIZE&n; * limit.&n; *&n; * Copyright (C) 1995, 1996, 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
DECL|macro|RPCDBG_FACILITY
mdefine_line|#define RPCDBG_FACILITY&t;RPCDBG_MISC
DECL|variable|proc_net_rpc
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_net_rpc
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Get RPC client stats&n; */
r_int
DECL|function|rpc_proc_read
id|rpc_proc_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|rpc_stat
op_star
id|statp
op_assign
(paren
r_struct
id|rpc_stat
op_star
)paren
id|data
suffix:semicolon
r_struct
id|rpc_program
op_star
id|prog
op_assign
id|statp-&gt;program
suffix:semicolon
r_struct
id|rpc_version
op_star
id|vers
suffix:semicolon
r_int
id|len
comma
id|i
comma
id|j
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;net %d %d %d %d&bslash;n&quot;
comma
id|statp-&gt;netcnt
comma
id|statp-&gt;netudpcnt
comma
id|statp-&gt;nettcpcnt
comma
id|statp-&gt;nettcpconn
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;rpc %d %d %d&bslash;n&quot;
comma
id|statp-&gt;rpccnt
comma
id|statp-&gt;rpcretrans
comma
id|statp-&gt;rpcauthrefresh
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|prog-&gt;nrvers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vers
op_assign
id|prog-&gt;version
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;proc%d %d&quot;
comma
id|vers-&gt;number
comma
id|vers-&gt;nrprocs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|vers-&gt;nrprocs
suffix:semicolon
id|j
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %d&quot;
comma
id|vers-&gt;procs
(braket
id|j
)braket
dot
id|p_count
)paren
suffix:semicolon
id|buffer
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|offset
)paren
OG
id|count
)paren
r_return
id|count
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Get RPC server stats&n; */
r_int
DECL|function|svc_proc_read
id|svc_proc_read
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|svc_stat
op_star
id|statp
op_assign
(paren
r_struct
id|svc_stat
op_star
)paren
id|data
suffix:semicolon
r_struct
id|svc_program
op_star
id|prog
op_assign
id|statp-&gt;program
suffix:semicolon
r_struct
id|svc_procedure
op_star
id|proc
suffix:semicolon
r_struct
id|svc_version
op_star
id|vers
suffix:semicolon
r_int
id|len
comma
id|i
comma
id|j
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;net %d %d %d %d&bslash;n&quot;
comma
id|statp-&gt;netcnt
comma
id|statp-&gt;netudpcnt
comma
id|statp-&gt;nettcpcnt
comma
id|statp-&gt;nettcpconn
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;rpc %d %d %d %d %d&bslash;n&quot;
comma
id|statp-&gt;rpccnt
comma
id|statp-&gt;rpcbadfmt
op_plus
id|statp-&gt;rpcbadauth
op_plus
id|statp-&gt;rpcbadclnt
comma
id|statp-&gt;rpcbadfmt
comma
id|statp-&gt;rpcbadauth
comma
id|statp-&gt;rpcbadclnt
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|prog-&gt;pg_nvers
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|vers
op_assign
id|prog-&gt;pg_vers
(braket
id|i
)braket
)paren
op_logical_or
op_logical_neg
(paren
id|proc
op_assign
id|vers-&gt;vs_proc
)paren
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;proc%d %d&quot;
comma
id|i
comma
id|vers-&gt;vs_nproc
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|vers-&gt;vs_nproc
suffix:semicolon
id|j
op_increment
comma
id|proc
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %d&quot;
comma
id|proc-&gt;pc_count
)paren
suffix:semicolon
id|buffer
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
op_ge
id|len
)paren
(brace
op_star
id|start
op_assign
id|buffer
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|start
op_assign
id|buffer
op_plus
id|offset
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_sub_assign
id|offset
)paren
OG
id|count
)paren
r_return
id|count
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Register/unregister RPC proc files&n; */
r_static
r_inline
r_struct
id|proc_dir_entry
op_star
DECL|function|do_register
id|do_register
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_void
op_star
id|data
comma
r_int
id|issvc
)paren
(brace
id|rpc_proc_init
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: registering /proc/net/rpc/%s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
r_return
id|create_proc_read_entry
c_func
(paren
id|name
comma
l_int|0
comma
id|proc_net_rpc
comma
id|issvc
ques
c_cond
id|svc_proc_read
suffix:colon
id|rpc_proc_read
comma
id|data
)paren
suffix:semicolon
)brace
r_struct
id|proc_dir_entry
op_star
DECL|function|rpc_proc_register
id|rpc_proc_register
c_func
(paren
r_struct
id|rpc_stat
op_star
id|statp
)paren
(brace
r_return
id|do_register
c_func
(paren
id|statp-&gt;program-&gt;name
comma
id|statp
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|rpc_proc_unregister
id|rpc_proc_unregister
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|name
comma
id|proc_net_rpc
)paren
suffix:semicolon
)brace
r_struct
id|proc_dir_entry
op_star
DECL|function|svc_proc_register
id|svc_proc_register
c_func
(paren
r_struct
id|svc_stat
op_star
id|statp
)paren
(brace
r_return
id|do_register
c_func
(paren
id|statp-&gt;program-&gt;pg_name
comma
id|statp
comma
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|svc_proc_unregister
id|svc_proc_unregister
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|name
comma
id|proc_net_rpc
)paren
suffix:semicolon
)brace
r_void
DECL|function|rpc_proc_init
id|rpc_proc_init
c_func
(paren
r_void
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: registering /proc/net/rpc&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|proc_net_rpc
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|ent
suffix:semicolon
id|ent
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net/rpc&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ent
)paren
(brace
id|ent-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|proc_net_rpc
op_assign
id|ent
suffix:semicolon
)brace
)brace
)brace
r_void
DECL|function|rpc_proc_exit
id|rpc_proc_exit
c_func
(paren
r_void
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: unregistering /proc/net/rpc&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|proc_net_rpc
)paren
(brace
id|proc_net_rpc
op_assign
l_int|NULL
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/rpc&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef MODULE
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef RPC_DEBUG
id|rpc_register_sysctl
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|rpc_proc_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef RPC_DEBUG
id|rpc_unregister_sysctl
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|rpc_proc_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
