multiline_comment|/*&n; * linux/fs/lockd/clntproc.c&n; *&n; * RPC procedures for the client side NLM implementation&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
macro_line|#include &lt;linux/lockd/sm_inter.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_CLIENT
r_static
r_int
id|nlmclnt_test
c_func
(paren
r_struct
id|nlm_rqst
op_star
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_static
r_int
id|nlmclnt_lock
c_func
(paren
r_struct
id|nlm_rqst
op_star
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_static
r_int
id|nlmclnt_unlock
c_func
(paren
r_struct
id|nlm_rqst
op_star
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
r_static
r_void
id|nlmclnt_unlock_callback
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_static
r_void
id|nlmclnt_cancel_callback
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_static
r_int
id|nlm_stat_to_errno
c_func
(paren
id|u32
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n; * Cookie counter for NLM requests&n; */
DECL|variable|nlm_cookie
r_static
id|u32
id|nlm_cookie
op_assign
l_int|0x1234
suffix:semicolon
DECL|function|nlmclnt_next_cookie
r_static
r_inline
r_void
id|nlmclnt_next_cookie
c_func
(paren
r_struct
id|nlm_cookie
op_star
id|c
)paren
(brace
id|memcpy
c_func
(paren
id|c-&gt;data
comma
op_amp
id|nlm_cookie
comma
l_int|4
)paren
suffix:semicolon
id|memset
c_func
(paren
id|c-&gt;data
op_plus
l_int|4
comma
l_int|0
comma
l_int|4
)paren
suffix:semicolon
id|c-&gt;len
op_assign
l_int|4
suffix:semicolon
id|nlm_cookie
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize arguments for TEST/LOCK/UNLOCK/CANCEL calls&n; */
r_static
r_inline
r_void
DECL|function|nlmclnt_setlockargs
id|nlmclnt_setlockargs
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_args
op_star
id|argp
op_assign
op_amp
id|req-&gt;a_args
suffix:semicolon
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|argp-&gt;lock
suffix:semicolon
id|nlmclnt_next_cookie
c_func
(paren
op_amp
id|argp-&gt;cookie
)paren
suffix:semicolon
id|argp-&gt;state
op_assign
id|nsm_local_state
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|lock-&gt;fh
comma
id|NFS_FH
c_func
(paren
id|fl-&gt;fl_file-&gt;f_dentry
)paren
comma
r_sizeof
(paren
r_struct
id|nfs_fh
)paren
)paren
suffix:semicolon
id|lock-&gt;caller
op_assign
id|system_utsname.nodename
suffix:semicolon
id|lock-&gt;oh.data
op_assign
id|req-&gt;a_owner
suffix:semicolon
id|lock-&gt;oh.len
op_assign
id|sprintf
c_func
(paren
id|req-&gt;a_owner
comma
l_string|&quot;%d@%s&quot;
comma
id|current-&gt;pid
comma
id|system_utsname.nodename
)paren
suffix:semicolon
id|locks_copy_lock
c_func
(paren
op_amp
id|lock-&gt;fl
comma
id|fl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize arguments for GRANTED call. The nlm_rqst structure&n; * has been cleared already.&n; */
r_int
DECL|function|nlmclnt_setgrantargs
id|nlmclnt_setgrantargs
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|call
comma
r_struct
id|nlm_lock
op_star
id|lock
)paren
(brace
id|locks_copy_lock
c_func
(paren
op_amp
id|call-&gt;a_args.lock.fl
comma
op_amp
id|lock-&gt;fl
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|call-&gt;a_args.lock.fh
comma
op_amp
id|lock-&gt;fh
comma
r_sizeof
(paren
id|call-&gt;a_args.lock.fh
)paren
)paren
suffix:semicolon
id|call-&gt;a_args.lock.caller
op_assign
id|system_utsname.nodename
suffix:semicolon
id|call-&gt;a_args.lock.oh.len
op_assign
id|lock-&gt;oh.len
suffix:semicolon
multiline_comment|/* set default data area */
id|call-&gt;a_args.lock.oh.data
op_assign
id|call-&gt;a_owner
suffix:semicolon
r_if
c_cond
(paren
id|lock-&gt;oh.len
OG
id|NLMCLNT_OHSIZE
)paren
(brace
r_void
op_star
id|data
op_assign
id|kmalloc
c_func
(paren
id|lock-&gt;oh.len
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_return
l_int|0
suffix:semicolon
id|call-&gt;a_args.lock.oh.data
op_assign
(paren
id|u8
op_star
)paren
id|data
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|call-&gt;a_args.lock.oh.data
comma
id|lock-&gt;oh.data
comma
id|lock-&gt;oh.len
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|nlmclnt_freegrantargs
id|nlmclnt_freegrantargs
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|call
)paren
(brace
multiline_comment|/*&n;&t; * Check whether we allocated memory for the owner.&n;&t; */
r_if
c_cond
(paren
id|call-&gt;a_args.lock.oh.data
op_ne
(paren
id|u8
op_star
)paren
id|call-&gt;a_owner
)paren
(brace
id|kfree
c_func
(paren
id|call-&gt;a_args.lock.oh.data
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is the main entry point for the NLM client.&n; */
r_int
DECL|function|nlmclnt_proc
id|nlmclnt_proc
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|cmd
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nfs_server
op_star
id|nfssrv
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_rqst
id|reqst
comma
op_star
id|call
op_assign
op_amp
id|reqst
suffix:semicolon
id|sigset_t
id|oldset
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|status
comma
id|proto
comma
id|vers
suffix:semicolon
id|vers
op_assign
(paren
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|version
op_eq
l_int|3
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|version
OG
l_int|3
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;NFSv4 file locking not implemented!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
multiline_comment|/* Retrieve transport protocol from NFS client */
id|proto
op_assign
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|cl_xprt-&gt;prot
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|host
op_assign
id|nlmclnt_lookup_host
c_func
(paren
id|NFS_ADDR
c_func
(paren
id|inode
)paren
comma
id|proto
comma
id|vers
)paren
)paren
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* Create RPC client handle if not there, and copy soft&n;&t; * and intr flags from NFS client. */
r_if
c_cond
(paren
id|host-&gt;h_rpcclnt
op_eq
l_int|NULL
)paren
(brace
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
multiline_comment|/* Bind an rpc client to this host handle (does not&n;&t;&t; * perform a portmapper lookup) */
r_if
c_cond
(paren
op_logical_neg
(paren
id|clnt
op_assign
id|nlm_bind_host
c_func
(paren
id|host
)paren
)paren
)paren
(brace
id|status
op_assign
op_minus
id|ENOLCK
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|clnt-&gt;cl_softrtry
op_assign
id|nfssrv-&gt;client-&gt;cl_softrtry
suffix:semicolon
id|clnt-&gt;cl_intr
op_assign
id|nfssrv-&gt;client-&gt;cl_intr
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
id|nfssrv-&gt;client-&gt;cl_chatty
suffix:semicolon
)brace
multiline_comment|/* Keep the old signal mask */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|oldset
op_assign
id|current-&gt;blocked
suffix:semicolon
multiline_comment|/* If we&squot;re cleaning up locks because the process is exiting,&n;&t; * perform the RPC call asynchronously. */
r_if
c_cond
(paren
(paren
id|cmd
op_eq
id|F_SETLK
op_logical_or
id|cmd
op_eq
id|F_SETLKW
)paren
op_logical_and
id|fl-&gt;fl_type
op_eq
id|F_UNLCK
op_logical_and
(paren
id|current-&gt;flags
op_amp
id|PF_EXITING
)paren
)paren
(brace
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
multiline_comment|/* Mask all signals */
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|call
op_assign
id|nlmclnt_alloc_call
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|call
)paren
(brace
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_restore
suffix:semicolon
)brace
id|call-&gt;a_flags
op_assign
id|RPC_TASK_ASYNC
suffix:semicolon
)brace
r_else
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|memset
c_func
(paren
id|call
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|call
)paren
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|call-&gt;a_args.lock.fl
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|call-&gt;a_res.lock.fl
)paren
suffix:semicolon
)brace
id|call-&gt;a_host
op_assign
id|host
suffix:semicolon
multiline_comment|/* Set up the argument struct */
id|nlmclnt_setlockargs
c_func
(paren
id|call
comma
id|fl
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|F_GETLK
)paren
(brace
id|status
op_assign
id|nlmclnt_test
c_func
(paren
id|call
comma
id|fl
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|cmd
op_eq
id|F_SETLK
op_logical_or
id|cmd
op_eq
id|F_SETLKW
)paren
op_logical_and
id|fl-&gt;fl_type
op_eq
id|F_UNLCK
)paren
(brace
id|status
op_assign
id|nlmclnt_unlock
c_func
(paren
id|call
comma
id|fl
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cmd
op_eq
id|F_SETLK
op_logical_or
id|cmd
op_eq
id|F_SETLKW
)paren
(brace
id|call-&gt;a_args.block
op_assign
(paren
id|cmd
op_eq
id|F_SETLKW
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|status
op_assign
id|nlmclnt_lock
c_func
(paren
id|call
comma
id|fl
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
OL
l_int|0
op_logical_and
(paren
id|call-&gt;a_flags
op_amp
id|RPC_TASK_ASYNC
)paren
)paren
id|kfree
c_func
(paren
id|call
)paren
suffix:semicolon
id|out_restore
suffix:colon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|oldset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|done
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;lockd: clnt proc returns %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Wait while server is in grace period&n; */
r_static
r_inline
r_int
DECL|function|nlmclnt_grace_wait
id|nlmclnt_grace_wait
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;h_reclaiming
)paren
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|host-&gt;h_gracewait
comma
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
r_else
id|interruptible_sleep_on
c_func
(paren
op_amp
id|host-&gt;h_gracewait
)paren
suffix:semicolon
r_return
id|signalled
c_func
(paren
)paren
ques
c_cond
op_minus
id|ERESTARTSYS
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate an NLM RPC call struct&n; */
r_struct
id|nlm_rqst
op_star
DECL|function|nlmclnt_alloc_call
id|nlmclnt_alloc_call
c_func
(paren
r_void
)paren
(brace
r_struct
id|nlm_rqst
op_star
id|call
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|signalled
c_func
(paren
)paren
)paren
(brace
id|call
op_assign
(paren
r_struct
id|nlm_rqst
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nlm_rqst
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|call
)paren
(brace
id|memset
c_func
(paren
id|call
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|call
)paren
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|call-&gt;a_args.lock.fl
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|call-&gt;a_res.lock.fl
)paren
suffix:semicolon
r_return
id|call
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;nlmclnt_alloc_call: failed, waiting for memory&bslash;n&quot;
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic NLM call&n; */
r_int
DECL|function|nlmclnt_call
id|nlmclnt_call
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
id|u32
id|proc
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
op_assign
id|req-&gt;a_host
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_struct
id|nlm_args
op_star
id|argp
op_assign
op_amp
id|req-&gt;a_args
suffix:semicolon
r_struct
id|nlm_res
op_star
id|resp
op_assign
op_amp
id|req-&gt;a_res
suffix:semicolon
r_struct
id|file
op_star
id|filp
op_assign
id|argp-&gt;lock.fl.fl_file
suffix:semicolon
r_struct
id|rpc_message
id|msg
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: call procedure %s on %s&bslash;n&quot;
comma
id|nlm_procname
c_func
(paren
id|proc
)paren
comma
id|host-&gt;h_name
)paren
suffix:semicolon
id|msg.rpc_proc
op_assign
id|proc
suffix:semicolon
id|msg.rpc_argp
op_assign
id|argp
suffix:semicolon
id|msg.rpc_resp
op_assign
id|resp
suffix:semicolon
r_if
c_cond
(paren
id|filp
)paren
id|msg.rpc_cred
op_assign
id|nfs_file_cred
c_func
(paren
id|filp
)paren
suffix:semicolon
r_else
id|msg.rpc_cred
op_assign
l_int|NULL
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|host-&gt;h_reclaiming
op_logical_and
op_logical_neg
id|argp-&gt;reclaim
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|host-&gt;h_gracewait
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* If we have no RPC client yet, create one. */
r_if
c_cond
(paren
(paren
id|clnt
op_assign
id|nlm_bind_host
c_func
(paren
id|host
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* Perform the RPC call. If an error occurs, try again */
r_if
c_cond
(paren
(paren
id|status
op_assign
id|rpc_call_sync
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: rpc_call returned error %d&bslash;n&quot;
comma
op_minus
id|status
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
op_minus
id|EPROTONOSUPPORT
suffix:colon
id|status
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ECONNREFUSED
suffix:colon
r_case
op_minus
id|ETIMEDOUT
suffix:colon
r_case
op_minus
id|ENOTCONN
suffix:colon
id|nlm_rebind_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|status
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ERESTARTSYS
suffix:colon
r_return
id|signalled
(paren
)paren
ques
c_cond
op_minus
id|EINTR
suffix:colon
id|status
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resp-&gt;status
op_eq
id|NLM_LCK_DENIED_GRACE_PERIOD
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: server in grace period&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|argp-&gt;reclaim
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: spurious grace period reject?!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: server returns status %d&bslash;n&quot;
comma
id|resp-&gt;status
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Okay, call complete */
)brace
multiline_comment|/* Back off a little and try again */
id|interruptible_sleep_on_timeout
c_func
(paren
op_amp
id|host-&gt;h_gracewait
comma
l_int|15
op_star
id|HZ
)paren
suffix:semicolon
multiline_comment|/* When the lock requested by F_SETLKW isn&squot;t available,&n;&t;&t;   we will wait until the request can be satisfied. If&n;&t;&t;   a signal is received during wait, we should return&n;&t;&t;   -EINTR. */
r_if
c_cond
(paren
id|signalled
(paren
)paren
)paren
(brace
id|status
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic NLM call, async version.&n; */
r_int
DECL|function|nlmsvc_async_call
id|nlmsvc_async_call
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
id|u32
id|proc
comma
id|rpc_action
id|callback
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
op_assign
id|req-&gt;a_host
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_struct
id|nlm_args
op_star
id|argp
op_assign
op_amp
id|req-&gt;a_args
suffix:semicolon
r_struct
id|nlm_res
op_star
id|resp
op_assign
op_amp
id|req-&gt;a_res
suffix:semicolon
r_struct
id|rpc_message
id|msg
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: call procedure %s on %s (async)&bslash;n&quot;
comma
id|nlm_procname
c_func
(paren
id|proc
)paren
comma
id|host-&gt;h_name
)paren
suffix:semicolon
multiline_comment|/* If we have no RPC client yet, create one. */
r_if
c_cond
(paren
(paren
id|clnt
op_assign
id|nlm_bind_host
c_func
(paren
id|host
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* bootstrap and kick off the async RPC call */
id|msg.rpc_proc
op_assign
id|proc
suffix:semicolon
id|msg.rpc_argp
op_assign
id|argp
suffix:semicolon
id|msg.rpc_resp
op_assign
id|resp
suffix:semicolon
id|msg.rpc_cred
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|rpc_call_async
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
id|RPC_TASK_ASYNC
comma
id|callback
comma
id|req
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nlmclnt_async_call
id|nlmclnt_async_call
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
id|u32
id|proc
comma
id|rpc_action
id|callback
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
op_assign
id|req-&gt;a_host
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_struct
id|nlm_args
op_star
id|argp
op_assign
op_amp
id|req-&gt;a_args
suffix:semicolon
r_struct
id|nlm_res
op_star
id|resp
op_assign
op_amp
id|req-&gt;a_res
suffix:semicolon
r_struct
id|file
op_star
id|file
op_assign
id|argp-&gt;lock.fl.fl_file
suffix:semicolon
r_struct
id|rpc_message
id|msg
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: call procedure %s on %s (async)&bslash;n&quot;
comma
id|nlm_procname
c_func
(paren
id|proc
)paren
comma
id|host-&gt;h_name
)paren
suffix:semicolon
multiline_comment|/* If we have no RPC client yet, create one. */
r_if
c_cond
(paren
(paren
id|clnt
op_assign
id|nlm_bind_host
c_func
(paren
id|host
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
multiline_comment|/* bootstrap and kick off the async RPC call */
id|msg.rpc_proc
op_assign
id|proc
suffix:semicolon
id|msg.rpc_argp
op_assign
id|argp
suffix:semicolon
id|msg.rpc_resp
op_assign
id|resp
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|msg.rpc_cred
op_assign
id|nfs_file_cred
c_func
(paren
id|file
)paren
suffix:semicolon
r_else
id|msg.rpc_cred
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Increment host refcount */
id|nlm_get_host
c_func
(paren
id|host
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call_async
c_func
(paren
id|clnt
comma
op_amp
id|msg
comma
id|RPC_TASK_ASYNC
comma
id|callback
comma
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * TEST for the presence of a conflicting lock&n; */
r_static
r_int
DECL|function|nlmclnt_test
id|nlmclnt_test
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
r_struct
id|file_lock
op_star
id|fl
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
id|nlmclnt_call
c_func
(paren
id|req
comma
id|NLMPROC_TEST
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
id|status
op_assign
id|req-&gt;a_res.status
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|NLM_LCK_GRANTED
)paren
(brace
id|fl-&gt;fl_type
op_assign
id|F_UNLCK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_eq
id|NLM_LCK_DENIED
)paren
(brace
multiline_comment|/*&n;&t;&t; * Report the conflicting lock back to the application.&n;&t;&t; * FIXME: Is it OK to report the pid back as well?&n;&t;&t; */
id|locks_copy_lock
c_func
(paren
id|fl
comma
op_amp
id|req-&gt;a_res.lock.fl
)paren
suffix:semicolon
multiline_comment|/* fl-&gt;fl_pid = 0; */
)brace
r_else
(brace
r_return
id|nlm_stat_to_errno
c_func
(paren
id|req-&gt;a_res.status
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|nlmclnt_insert_lock_callback
r_void
id|nlmclnt_insert_lock_callback
c_func
(paren
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|nlm_get_host
c_func
(paren
id|fl-&gt;fl_u.nfs_fl.host
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
DECL|function|nlmclnt_remove_lock_callback
r_void
id|nlmclnt_remove_lock_callback
c_func
(paren
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_u.nfs_fl.host
)paren
(brace
id|nlm_release_host
c_func
(paren
id|fl-&gt;fl_u.nfs_fl.host
)paren
suffix:semicolon
id|fl-&gt;fl_u.nfs_fl.host
op_assign
l_int|NULL
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * LOCK: Try to create a lock&n; *&n; *&t;&t;&t;Programmer Harassment Alert&n; *&n; * When given a blocking lock request in a sync RPC call, the HPUX lockd&n; * will faithfully return LCK_BLOCKED but never cares to notify us when&n; * the lock could be granted. This way, our local process could hang&n; * around forever waiting for the callback.&n; *&n; *  Solution A:&t;Implement busy-waiting&n; *  Solution B: Use the async version of the call (NLM_LOCK_{MSG,RES})&n; *&n; * For now I am implementing solution A, because I hate the idea of&n; * re-implementing lockd for a third time in two months. The async&n; * calls shouldn&squot;t be too hard to do, however.&n; *&n; * This is one of the lovely things about standards in the NFS area:&n; * they&squot;re so soft and squishy you can&squot;t really blame HP for doing this.&n; */
r_static
r_int
DECL|function|nlmclnt_lock
id|nlmclnt_lock
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_host
op_star
id|host
op_assign
id|req-&gt;a_host
suffix:semicolon
r_struct
id|nlm_res
op_star
id|resp
op_assign
op_amp
id|req-&gt;a_res
suffix:semicolon
r_int
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|host-&gt;h_monitored
op_logical_and
id|nsm_monitor
c_func
(paren
id|host
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: failed to monitor %s&bslash;n&quot;
comma
id|host-&gt;h_name
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
r_do
(brace
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nlmclnt_call
c_func
(paren
id|req
comma
id|NLMPROC_LOCK
)paren
)paren
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|resp-&gt;status
op_ne
id|NLM_LCK_BLOCKED
)paren
r_break
suffix:semicolon
id|status
op_assign
id|nlmclnt_block
c_func
(paren
id|host
comma
id|fl
comma
op_amp
id|resp-&gt;status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
)brace
r_while
c_loop
(paren
id|resp-&gt;status
op_eq
id|NLM_LCK_BLOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;status
op_eq
id|NLM_LCK_GRANTED
)paren
(brace
id|fl-&gt;fl_u.nfs_fl.state
op_assign
id|host-&gt;h_state
suffix:semicolon
id|fl-&gt;fl_u.nfs_fl.flags
op_or_assign
id|NFS_LCK_GRANTED
suffix:semicolon
id|fl-&gt;fl_u.nfs_fl.host
op_assign
id|host
suffix:semicolon
id|fl-&gt;fl_insert
op_assign
id|nlmclnt_insert_lock_callback
suffix:semicolon
id|fl-&gt;fl_remove
op_assign
id|nlmclnt_remove_lock_callback
suffix:semicolon
)brace
r_return
id|nlm_stat_to_errno
c_func
(paren
id|resp-&gt;status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * RECLAIM: Try to reclaim a lock&n; */
r_int
DECL|function|nlmclnt_reclaim
id|nlmclnt_reclaim
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_rqst
id|reqst
comma
op_star
id|req
suffix:semicolon
r_int
id|status
suffix:semicolon
id|req
op_assign
op_amp
id|reqst
suffix:semicolon
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
id|locks_init_lock
c_func
(paren
op_amp
id|req-&gt;a_args.lock.fl
)paren
suffix:semicolon
id|locks_init_lock
c_func
(paren
op_amp
id|req-&gt;a_res.lock.fl
)paren
suffix:semicolon
id|req-&gt;a_host
op_assign
id|host
suffix:semicolon
id|req-&gt;a_flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set up the argument struct */
id|nlmclnt_setlockargs
c_func
(paren
id|req
comma
id|fl
)paren
suffix:semicolon
id|req-&gt;a_args.reclaim
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nlmclnt_call
c_func
(paren
id|req
comma
id|NLMPROC_LOCK
)paren
)paren
op_ge
l_int|0
op_logical_and
id|req-&gt;a_res.status
op_eq
id|NLM_LCK_GRANTED
)paren
r_return
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: failed to reclaim lock for pid %d &quot;
l_string|&quot;(errno %d, status %d)&bslash;n&quot;
comma
id|fl-&gt;fl_pid
comma
id|status
comma
id|req-&gt;a_res.status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME: This is a serious failure. We can&n;&t; *&n;&t; *  a.&t;Ignore the problem&n;&t; *  b.&t;Send the owning process some signal (Linux doesn&squot;t have&n;&t; *&t;SIGLOST, though...)&n;&t; *  c.&t;Retry the operation&n;&t; *&n;&t; * Until someone comes up with a simple implementation&n;&t; * for b or c, I&squot;ll choose option a.&n;&t; */
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
multiline_comment|/*&n; * UNLOCK: remove an existing lock&n; */
r_static
r_int
DECL|function|nlmclnt_unlock
id|nlmclnt_unlock
c_func
(paren
r_struct
id|nlm_rqst
op_star
id|req
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_res
op_star
id|resp
op_assign
op_amp
id|req-&gt;a_res
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* Clean the GRANTED flag now so the lock doesn&squot;t get&n;&t; * reclaimed while we&squot;re stuck in the unlock call. */
id|fl-&gt;fl_u.nfs_fl.flags
op_and_assign
op_complement
id|NFS_LCK_GRANTED
suffix:semicolon
r_if
c_cond
(paren
id|req-&gt;a_flags
op_amp
id|RPC_TASK_ASYNC
)paren
(brace
r_return
id|nlmclnt_async_call
c_func
(paren
id|req
comma
id|NLMPROC_UNLOCK
comma
id|nlmclnt_unlock_callback
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nlmclnt_call
c_func
(paren
id|req
comma
id|NLMPROC_UNLOCK
)paren
)paren
OL
l_int|0
)paren
r_return
id|status
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;status
op_eq
id|NLM_LCK_GRANTED
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|resp-&gt;status
op_ne
id|NLM_LCK_DENIED_NOLOCKS
)paren
id|printk
c_func
(paren
l_string|&quot;lockd: unexpected unlock status: %d&bslash;n&quot;
comma
id|resp-&gt;status
)paren
suffix:semicolon
multiline_comment|/* What to do now? I&squot;m out of my depth... */
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
r_static
r_void
DECL|function|nlmclnt_unlock_callback
id|nlmclnt_unlock_callback
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nlm_rqst
op_star
id|req
op_assign
(paren
r_struct
id|nlm_rqst
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_int
id|status
op_assign
id|req-&gt;a_res.status
suffix:semicolon
r_if
c_cond
(paren
id|RPC_ASSASSINATED
c_func
(paren
id|task
)paren
)paren
r_goto
id|die
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: unlock failed (err = %d)&bslash;n&quot;
comma
op_minus
id|task-&gt;tk_status
)paren
suffix:semicolon
r_goto
id|retry_unlock
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_ne
id|NLM_LCK_GRANTED
op_logical_and
id|status
op_ne
id|NLM_LCK_DENIED_GRACE_PERIOD
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd: unexpected unlock status: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
)brace
id|die
suffix:colon
id|nlm_release_host
c_func
(paren
id|req-&gt;a_host
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
suffix:semicolon
id|retry_unlock
suffix:colon
id|nlm_rebind_host
c_func
(paren
id|req-&gt;a_host
)paren
suffix:semicolon
id|rpc_restart_call
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Cancel a blocked lock request.&n; * We always use an async RPC call for this in order not to hang a&n; * process that has been Ctrl-C&squot;ed.&n; */
r_int
DECL|function|nlmclnt_cancel
id|nlmclnt_cancel
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_rqst
op_star
id|req
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|sigset_t
id|oldset
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* Block all signals while setting up call */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|oldset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|sigfillset
c_func
(paren
op_amp
id|current-&gt;blocked
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|req
op_assign
id|nlmclnt_alloc_call
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|req-&gt;a_host
op_assign
id|host
suffix:semicolon
id|req-&gt;a_flags
op_assign
id|RPC_TASK_ASYNC
suffix:semicolon
id|nlmclnt_setlockargs
c_func
(paren
id|req
comma
id|fl
)paren
suffix:semicolon
id|status
op_assign
id|nlmclnt_async_call
c_func
(paren
id|req
comma
id|NLMPROC_CANCEL
comma
id|nlmclnt_cancel_callback
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
OL
l_int|0
)paren
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|oldset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_void
DECL|function|nlmclnt_cancel_callback
id|nlmclnt_cancel_callback
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nlm_rqst
op_star
id|req
op_assign
(paren
r_struct
id|nlm_rqst
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_if
c_cond
(paren
id|RPC_ASSASSINATED
c_func
(paren
id|task
)paren
)paren
r_goto
id|die
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: CANCEL call error %d, retrying.&bslash;n&quot;
comma
id|task-&gt;tk_status
)paren
suffix:semicolon
r_goto
id|retry_cancel
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: cancel status %d (task %d)&bslash;n&quot;
comma
id|req-&gt;a_res.status
comma
id|task-&gt;tk_pid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|req-&gt;a_res.status
)paren
(brace
r_case
id|NLM_LCK_GRANTED
suffix:colon
r_case
id|NLM_LCK_DENIED_GRACE_PERIOD
suffix:colon
multiline_comment|/* Everything&squot;s good */
r_break
suffix:semicolon
r_case
id|NLM_LCK_DENIED_NOLOCKS
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;lockd: CANCEL failed (server has no locks)&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|retry_cancel
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: weird return %d for CANCEL call&bslash;n&quot;
comma
id|req-&gt;a_res.status
)paren
suffix:semicolon
)brace
id|die
suffix:colon
id|nlm_release_host
c_func
(paren
id|req-&gt;a_host
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
r_return
suffix:semicolon
id|retry_cancel
suffix:colon
id|nlm_rebind_host
c_func
(paren
id|req-&gt;a_host
)paren
suffix:semicolon
id|rpc_restart_call
c_func
(paren
id|task
)paren
suffix:semicolon
id|rpc_delay
c_func
(paren
id|task
comma
l_int|30
op_star
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Convert an NLM status code to a generic kernel errno&n; */
r_static
r_int
DECL|function|nlm_stat_to_errno
id|nlm_stat_to_errno
c_func
(paren
id|u32
id|status
)paren
(brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|NLM_LCK_GRANTED
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|NLM_LCK_DENIED
suffix:colon
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_case
id|NLM_LCK_DENIED_NOLOCKS
suffix:colon
r_case
id|NLM_LCK_DENIED_GRACE_PERIOD
suffix:colon
r_return
op_minus
id|ENOLCK
suffix:semicolon
r_case
id|NLM_LCK_BLOCKED
suffix:colon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: unexpected status NLM_BLOCKED&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;lockd: unexpected server status %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
eof
