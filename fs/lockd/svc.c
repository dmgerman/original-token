multiline_comment|/*&n; * linux/fs/lockd/svc.c&n; *&n; * This is the central lockd service.&n; *&n; * FIXME: Separate the lockd NFS server functionality from the lockd NFS&n; * &t;  client functionality. Oh why didn&squot;t Sun create two separate&n; *&t;  services in the first place?&n; *&n; * Authors:&t;Olaf Kirch (okir@monad.swb.de)&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_SVC
DECL|macro|LOCKD_BUFSIZE
mdefine_line|#define LOCKD_BUFSIZE&t;&t;(1024 + NLMSSVC_XDRSIZE)
DECL|macro|BLOCKABLE_SIGS
mdefine_line|#define BLOCKABLE_SIGS&t;&t;(~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
r_extern
r_struct
id|svc_program
id|nlmsvc_program
suffix:semicolon
DECL|variable|nlmsvc_ops
r_struct
id|nlmsvc_binding
op_star
id|nlmsvc_ops
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|nlmsvc_sema
r_static
r_struct
id|semaphore
id|nlmsvc_sema
op_assign
id|MUTEX
suffix:semicolon
DECL|variable|nlmsvc_users
r_static
r_int
r_int
id|nlmsvc_users
op_assign
l_int|0
suffix:semicolon
DECL|variable|nlmsvc_pid
r_static
id|pid_t
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
DECL|variable|nlmsvc_grace_period
r_int
r_int
id|nlmsvc_grace_period
op_assign
l_int|0
suffix:semicolon
DECL|variable|nlmsvc_timeout
r_int
r_int
id|nlmsvc_timeout
op_assign
l_int|0
suffix:semicolon
DECL|variable|lockd_start
r_static
r_struct
id|wait_queue
op_star
id|lockd_start
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|lockd_exit
r_static
r_struct
id|wait_queue
op_star
id|lockd_exit
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Currently the following can be set only at insmod time.&n; * Ideally, they would be accessible through the sysctl interface.&n; */
DECL|variable|nlm_grace_period
r_int
r_int
id|nlm_grace_period
op_assign
l_int|0
suffix:semicolon
DECL|variable|nlm_timeout
r_int
r_int
id|nlm_timeout
op_assign
id|LOCKD_DFLT_TIMEO
suffix:semicolon
multiline_comment|/*&n; * This is the lockd kernel thread&n; */
r_static
r_void
DECL|function|lockd
id|lockd
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
op_assign
id|rqstp-&gt;rq_server
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Lock module and set up kernel thread */
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Let our maker know we&squot;re running.&n;&t; */
id|nlmsvc_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|lockd_start
)paren
suffix:semicolon
id|exit_mm
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;session
op_assign
l_int|1
suffix:semicolon
id|current-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;lockd&quot;
)paren
suffix:semicolon
multiline_comment|/* kick rpciod */
id|rpciod_up
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. current do_fork() doesn&squot;t like NULL task-&gt;files,&n;&t; * so we defer closing files until forking rpciod.&n;&t; */
id|exit_files
c_func
(paren
id|current
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS locking service started (ver &quot;
id|LOCKD_VERSION
l_string|&quot;).&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlm_timeout
)paren
id|nlm_timeout
op_assign
id|LOCKD_DFLT_TIMEO
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
id|nlmsvc_grace_period
op_assign
l_int|10
op_star
id|HZ
suffix:semicolon
macro_line|#else
r_if
c_cond
(paren
id|nlm_grace_period
)paren
(brace
id|nlmsvc_grace_period
op_add_assign
(paren
l_int|1
op_plus
id|nlm_grace_period
op_div
id|nlm_timeout
)paren
op_star
id|nlm_timeout
op_star
id|HZ
suffix:semicolon
)brace
r_else
(brace
id|nlmsvc_grace_period
op_add_assign
l_int|5
op_star
id|nlm_timeout
op_star
id|HZ
suffix:semicolon
)brace
macro_line|#endif
id|nlmsvc_grace_period
op_add_assign
id|jiffies
suffix:semicolon
id|nlmsvc_timeout
op_assign
id|nlm_timeout
op_star
id|HZ
suffix:semicolon
multiline_comment|/*&n;&t; * The main request loop. We don&squot;t terminate until the last&n;&t; * NFS mount or NFS daemon has gone away, and we&squot;ve been sent a&n;&t; * signal, or else another process has taken over our job.&n;&t; */
r_while
c_loop
(paren
(paren
id|nlmsvc_users
op_logical_or
op_logical_neg
id|signalled
c_func
(paren
)paren
)paren
op_logical_and
id|nlmsvc_pid
op_eq
id|current-&gt;pid
)paren
(brace
r_if
c_cond
(paren
id|signalled
c_func
(paren
)paren
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|flush_signals
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Retry any blocked locks that have been notified by&n;&t;&t; * the VFS. Don&squot;t do this during grace period.&n;&t;&t; * (Theoretically, there shouldn&squot;t even be blocked locks&n;&t;&t; * during grace period).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_grace_period
)paren
(brace
id|current-&gt;timeout
op_assign
id|nlmsvc_retry_blocked
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nlmsvc_grace_period
OL
id|jiffies
)paren
id|nlmsvc_grace_period
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Find a socket with data available and call its&n;&t;&t; * recvfrom routine.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|svc_recv
c_func
(paren
id|serv
comma
id|rqstp
)paren
)paren
op_eq
op_minus
id|EAGAIN
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|EINTR
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: terminating on error %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: request from %08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Look up the NFS client handle. The handle is needed for&n;&t;&t; * all but the GRANTED callback RPCs.&n;&t;&t; */
r_if
c_cond
(paren
id|nlmsvc_ops
)paren
(brace
id|nlmsvc_ops
op_member_access_from_pointer
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
id|rqstp-&gt;rq_client
op_assign
id|nlmsvc_ops
op_member_access_from_pointer
id|exp_getclient
c_func
(paren
op_amp
id|rqstp-&gt;rq_addr
)paren
suffix:semicolon
)brace
r_else
(brace
id|rqstp-&gt;rq_client
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Process request with all signals blocked.  */
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|siginitsetinv
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_complement
id|BLOCKABLE_SIGS
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|svc_process
c_func
(paren
id|serv
comma
id|rqstp
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|sigemptyset
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
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
multiline_comment|/* Unlock export hash tables */
r_if
c_cond
(paren
id|nlmsvc_ops
)paren
id|nlmsvc_ops
op_member_access_from_pointer
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check whether there&squot;s a new lockd process before&n;&t; * shutting down the hosts and clearing the slot.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_pid
op_logical_or
id|current-&gt;pid
op_eq
id|nlmsvc_pid
)paren
(brace
id|nlm_shutdown_hosts
c_func
(paren
)paren
suffix:semicolon
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;lockd: new process, skipping host shutdown&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|lockd_exit
)paren
suffix:semicolon
multiline_comment|/* Exit the RPC thread */
id|svc_exit_thread
c_func
(paren
id|rqstp
)paren
suffix:semicolon
multiline_comment|/* release rpciod */
id|rpciod_down
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Release module */
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Make a socket for lockd&n; * FIXME: Move this to net/sunrpc/svc.c so that we can share this with nfsd.&n; */
r_static
r_int
DECL|function|lockd_makesock
id|lockd_makesock
c_func
(paren
r_struct
id|svc_serv
op_star
id|serv
comma
r_int
id|protocol
comma
r_int
r_int
id|port
)paren
(brace
r_struct
id|sockaddr_in
id|sin
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: creating socket proto = %d&bslash;n&quot;
comma
id|protocol
)paren
suffix:semicolon
id|sin.sin_family
op_assign
id|AF_INET
suffix:semicolon
id|sin.sin_addr.s_addr
op_assign
id|INADDR_ANY
suffix:semicolon
id|sin.sin_port
op_assign
id|htons
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
id|svc_create_socket
c_func
(paren
id|serv
comma
id|protocol
comma
op_amp
id|sin
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Bring up the lockd process if it&squot;s not already up.&n; */
r_int
DECL|function|lockd_up
id|lockd_up
c_func
(paren
r_void
)paren
(brace
r_struct
id|svc_serv
op_star
id|serv
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unconditionally increment the user count ... this is&n;&t; * the number of clients who _want_ a lockd process.&n;&t; */
id|nlmsvc_users
op_increment
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether we&squot;re already up and running.&n;&t; */
r_if
c_cond
(paren
id|nlmsvc_pid
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Sanity check: if there&squot;s no pid,&n;&t; * we should be the first user ...&n;&t; */
r_if
c_cond
(paren
id|nlmsvc_users
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;lockd_up: no pid, %d users??&bslash;n&quot;
comma
id|nlmsvc_users
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|serv
op_assign
id|svc_create
c_func
(paren
op_amp
id|nlmsvc_program
comma
l_int|0
comma
id|NLMSVC_XDRSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serv
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd_up: create service failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|lockd_makesock
c_func
(paren
id|serv
comma
id|IPPROTO_UDP
comma
l_int|0
)paren
)paren
OL
l_int|0
op_logical_or
(paren
id|error
op_assign
id|lockd_makesock
c_func
(paren
id|serv
comma
id|IPPROTO_TCP
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd_up: makesock failed, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|destroy_and_out
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create the kernel thread and wait for it to start.&n;&t; */
id|error
op_assign
id|svc_create_thread
c_func
(paren
id|lockd
comma
id|serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd_up: create thread failed, error=%d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|destroy_and_out
suffix:semicolon
)brace
id|sleep_on
c_func
(paren
op_amp
id|lockd_start
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: svc_serv structures have an initial use count of 1,&n;&t; * so we exit through here on both success and failure.&n;&t; */
id|destroy_and_out
suffix:colon
id|svc_destroy
c_func
(paren
id|serv
)paren
suffix:semicolon
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrement the user count and bring down lockd if we&squot;re the last.&n; */
r_void
DECL|function|lockd_down
id|lockd_down
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_users
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|nlmsvc_users
)paren
r_goto
id|out
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;lockd_down: no users! pid=%d&bslash;n&quot;
comma
id|nlmsvc_pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlmsvc_pid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd_down: nothing to do!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|kill_proc
c_func
(paren
id|nlmsvc_pid
comma
id|SIGKILL
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Wait for the lockd process to exit, but since we&squot;re holding&n;&t; * the lockd semaphore, we can&squot;t wait around forever ...&n;&t; */
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
l_int|5
op_star
id|HZ
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|lockd_exit
)paren
suffix:semicolon
id|current-&gt;timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nlmsvc_pid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;lockd_down: lockd failed to exit, clearing pid&bslash;n&quot;
)paren
suffix:semicolon
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
id|up
c_func
(paren
op_amp
id|nlmsvc_sema
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
multiline_comment|/* New module support in 2.1.18 */
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020112
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Olaf Kirch &lt;okir@monad.swb.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NFS file locking service version &quot;
id|LOCKD_VERSION
l_string|&quot;.&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|nlm_grace_period
comma
l_string|&quot;10-240l&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|nlm_timeout
comma
l_string|&quot;3-20l&quot;
)paren
suffix:semicolon
macro_line|#endif
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Init the static variables */
id|nlmsvc_sema
op_assign
id|MUTEX
suffix:semicolon
id|nlmsvc_users
op_assign
l_int|0
suffix:semicolon
id|nlmsvc_pid
op_assign
l_int|0
suffix:semicolon
id|lockd_exit
op_assign
l_int|NULL
suffix:semicolon
id|nlmxdr_init
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
multiline_comment|/* FIXME: delete all NLM clients */
id|nlm_shutdown_hosts
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Define NLM program and procedures&n; */
DECL|variable|nlmsvc_version1
r_static
r_struct
id|svc_version
id|nlmsvc_version1
op_assign
(brace
l_int|1
comma
l_int|16
comma
id|nlmsvc_procedures
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|nlmsvc_version3
r_static
r_struct
id|svc_version
id|nlmsvc_version3
op_assign
(brace
l_int|3
comma
l_int|24
comma
id|nlmsvc_procedures
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NFSD_NFS3
DECL|variable|nlmsvc_version4
r_static
r_struct
id|svc_version
id|nlmsvc_version4
op_assign
(brace
l_int|4
comma
l_int|24
comma
id|nlmsvc_procedures4
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|nlmsvc_version
r_static
r_struct
id|svc_version
op_star
id|nlmsvc_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
op_amp
id|nlmsvc_version1
comma
l_int|NULL
comma
op_amp
id|nlmsvc_version3
comma
macro_line|#ifdef CONFIG_NFSD_NFS3
op_amp
id|nlmsvc_version4
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|variable|nlmsvc_stats
r_static
r_struct
id|svc_stat
id|nlmsvc_stats
suffix:semicolon
DECL|macro|NLM_NRVERS
mdefine_line|#define NLM_NRVERS&t;(sizeof(nlmsvc_version)/sizeof(nlmsvc_version[0]))
DECL|variable|nlmsvc_program
r_struct
id|svc_program
id|nlmsvc_program
op_assign
(brace
id|NLM_PROGRAM
comma
multiline_comment|/* program number */
l_int|1
comma
id|NLM_NRVERS
op_minus
l_int|1
comma
multiline_comment|/* version range */
id|NLM_NRVERS
comma
multiline_comment|/* number of entries in nlmsvc_version */
id|nlmsvc_version
comma
multiline_comment|/* version table */
l_string|&quot;lockd&quot;
comma
multiline_comment|/* service name */
op_amp
id|nlmsvc_stats
comma
multiline_comment|/* stats table */
)brace
suffix:semicolon
eof
