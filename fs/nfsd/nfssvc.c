multiline_comment|/*&n; * linux/fs/nfsd/nfssvc.c&n; *&n; * Central processing for nfsd.&n; *&n; * Authors:&t;Olaf Kirch (okir@monad.swb.de)&n; *&n; * Copyright (C) 1995, 1996, 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
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
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/sunrpc/svcsock.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/stats.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;NFSDDBG_SVC
DECL|macro|NFSD_BUFSIZE
mdefine_line|#define NFSD_BUFSIZE&t;&t;(1024 + NFSSVC_MAXBLKSIZE)
DECL|macro|ALLOWED_SIGS
mdefine_line|#define ALLOWED_SIGS&t;(sigmask(SIGKILL))
DECL|macro|SHUTDOWN_SIGS
mdefine_line|#define SHUTDOWN_SIGS&t;(sigmask(SIGKILL) | sigmask(SIGINT) | sigmask(SIGQUIT))
r_extern
r_struct
id|svc_program
id|nfsd_program
suffix:semicolon
r_static
r_void
id|nfsd
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
)paren
suffix:semicolon
DECL|variable|nfssvc_boot
r_struct
id|timeval
id|nfssvc_boot
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|nfsd_serv
r_static
r_struct
id|svc_serv
op_star
id|nfsd_serv
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|nfsd_busy
r_static
r_int
id|nfsd_busy
op_assign
l_int|0
suffix:semicolon
DECL|variable|nfsd_last_call
r_static
r_int
r_int
id|nfsd_last_call
suffix:semicolon
DECL|struct|nfsd_list
r_struct
id|nfsd_list
(brace
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|nfsd_list
r_struct
id|list_head
id|nfsd_list
op_assign
id|LIST_HEAD_INIT
c_func
(paren
id|nfsd_list
)paren
suffix:semicolon
multiline_comment|/*&n; * Maximum number of nfsd processes&n; */
DECL|macro|NFSD_MAXSERVS
mdefine_line|#define&t;NFSD_MAXSERVS&t;&t;128
r_int
DECL|function|nfsd_svc
id|nfsd_svc
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|nrservs
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|none_left
suffix:semicolon
r_struct
id|list_head
op_star
id|victim
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: creating service&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|nrservs
op_le
l_int|0
)paren
id|nrservs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nrservs
OG
id|NFSD_MAXSERVS
)paren
id|nrservs
op_assign
id|NFSD_MAXSERVS
suffix:semicolon
multiline_comment|/* Readahead param cache - will no-op if it already exists */
id|error
op_assign
id|nfsd_racache_init
c_func
(paren
l_int|2
op_star
id|nrservs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nfsd_serv
)paren
(brace
id|nfsd_serv
op_assign
id|svc_create
c_func
(paren
op_amp
id|nfsd_program
comma
id|NFSD_BUFSIZE
comma
id|NFSSVC_XDRSIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfsd_serv
op_eq
l_int|NULL
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|svc_makesock
c_func
(paren
id|nfsd_serv
comma
id|IPPROTO_UDP
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|failure
suffix:semicolon
macro_line|#if 0&t;/* Don&squot;t even pretend that TCP works. It doesn&squot;t. */
id|error
op_assign
id|svc_makesock
c_func
(paren
id|nfsd_serv
comma
id|IPPROTO_TCP
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_goto
id|failure
suffix:semicolon
macro_line|#endif
id|get_fast_time
c_func
(paren
op_amp
id|nfssvc_boot
)paren
suffix:semicolon
multiline_comment|/* record boot time */
)brace
r_else
id|nfsd_serv-&gt;sv_nrthreads
op_increment
suffix:semicolon
id|nrservs
op_sub_assign
(paren
id|nfsd_serv-&gt;sv_nrthreads
op_minus
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
id|nrservs
OG
l_int|0
)paren
(brace
id|nrservs
op_decrement
suffix:semicolon
id|error
op_assign
id|svc_create_thread
c_func
(paren
id|nfsd
comma
id|nfsd_serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_break
suffix:semicolon
)brace
id|victim
op_assign
id|nfsd_list.next
suffix:semicolon
r_while
c_loop
(paren
id|nrservs
OL
l_int|0
op_logical_and
id|victim
op_ne
op_amp
id|nfsd_list
)paren
(brace
r_struct
id|nfsd_list
op_star
id|nl
op_assign
id|list_entry
c_func
(paren
id|victim
comma
r_struct
id|nfsd_list
comma
id|list
)paren
suffix:semicolon
id|victim
op_assign
id|victim-&gt;next
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGKILL
comma
id|nl-&gt;task
comma
l_int|1
)paren
suffix:semicolon
id|nrservs
op_increment
suffix:semicolon
)brace
id|failure
suffix:colon
id|none_left
op_assign
(paren
id|nfsd_serv-&gt;sv_nrthreads
op_eq
l_int|1
)paren
suffix:semicolon
id|svc_destroy
c_func
(paren
id|nfsd_serv
)paren
suffix:semicolon
multiline_comment|/* Release server */
r_if
c_cond
(paren
id|none_left
)paren
(brace
id|nfsd_serv
op_assign
l_int|NULL
suffix:semicolon
id|nfsd_racache_shutdown
c_func
(paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
r_static
r_void
r_inline
DECL|function|update_thread_usage
id|update_thread_usage
c_func
(paren
r_int
id|busy_threads
)paren
(brace
r_int
r_int
id|prev_call
suffix:semicolon
r_int
r_int
id|diff
suffix:semicolon
r_int
id|decile
suffix:semicolon
id|prev_call
op_assign
id|nfsd_last_call
suffix:semicolon
id|nfsd_last_call
op_assign
id|jiffies
suffix:semicolon
id|decile
op_assign
id|busy_threads
op_star
l_int|10
op_div
id|nfsdstats.th_cnt
suffix:semicolon
r_if
c_cond
(paren
id|decile
OG
l_int|0
op_logical_and
id|decile
op_le
l_int|10
)paren
(brace
id|diff
op_assign
id|nfsd_last_call
op_minus
id|prev_call
suffix:semicolon
r_if
c_cond
(paren
(paren
id|nfsdstats.th_usage
(braket
id|decile
op_minus
l_int|1
)braket
op_add_assign
id|diff
)paren
op_ge
id|NFSD_USAGE_WRAP
)paren
id|nfsdstats.th_usage
(braket
id|decile
op_minus
l_int|1
)braket
op_sub_assign
id|NFSD_USAGE_WRAP
suffix:semicolon
r_if
c_cond
(paren
id|decile
op_eq
l_int|10
)paren
id|nfsdstats.th_fullcnt
op_increment
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is the NFS server kernel thread&n; */
r_static
r_void
DECL|function|nfsd
id|nfsd
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
suffix:semicolon
r_struct
id|nfsd_list
id|me
suffix:semicolon
multiline_comment|/* Lock module and set up kernel thread */
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_kernel
c_func
(paren
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
l_string|&quot;nfsd&quot;
)paren
suffix:semicolon
id|current-&gt;fs-&gt;umask
op_assign
l_int|0
suffix:semicolon
id|current-&gt;rlim
(braket
id|RLIMIT_FSIZE
)braket
dot
id|rlim_cur
op_assign
id|RLIM_INFINITY
suffix:semicolon
id|nfsdstats.th_cnt
op_increment
suffix:semicolon
multiline_comment|/* Let svc_process check client&squot;s authentication. */
id|rqstp-&gt;rq_auth
op_assign
l_int|1
suffix:semicolon
id|lockd_up
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* start lockd */
id|me.task
op_assign
id|current
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|me.list
comma
op_amp
id|nfsd_list
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The main request loop&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* Block all but the shutdown signals */
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
id|SHUTDOWN_SIGS
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
multiline_comment|/*&n;&t;&t; * Find a socket with data available and call its&n;&t;&t; * recvfrom routine.&n;&t;&t; */
r_while
c_loop
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
comma
id|MAX_SCHEDULE_TIMEOUT
)paren
)paren
op_eq
op_minus
id|EAGAIN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_break
suffix:semicolon
id|update_thread_usage
c_func
(paren
id|nfsd_busy
)paren
suffix:semicolon
id|nfsd_busy
op_increment
suffix:semicolon
multiline_comment|/* Lock the export hash tables for reading. */
id|exp_readlock
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Validate the client&squot;s address. This will also defeat&n;&t;&t; * port probes on port 2049 by unauthorized clients.&n;&t;&t; */
id|rqstp-&gt;rq_client
op_assign
id|exp_getclient
c_func
(paren
op_amp
id|rqstp-&gt;rq_addr
)paren
suffix:semicolon
multiline_comment|/* Process request with signals blocked.  */
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
id|ALLOWED_SIGS
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
multiline_comment|/* Unlock export hash tables */
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
id|update_thread_usage
c_func
(paren
id|nfsd_busy
)paren
suffix:semicolon
id|nfsd_busy
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
op_ne
op_minus
id|EINTR
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: terminating on error %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
r_int
id|signo
suffix:semicolon
r_for
c_loop
(paren
id|signo
op_assign
l_int|1
suffix:semicolon
id|signo
op_le
id|_NSIG
suffix:semicolon
id|signo
op_increment
)paren
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|signo
)paren
op_logical_and
op_logical_neg
id|sigismember
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|signo
)paren
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: terminating on signal %d&bslash;n&quot;
comma
id|signo
)paren
suffix:semicolon
)brace
multiline_comment|/* Release lockd */
id|lockd_down
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Check if this is last thread */
r_if
c_cond
(paren
id|serv-&gt;sv_nrthreads
op_eq
l_int|1
)paren
(brace
id|nfsd_serv
op_assign
l_int|NULL
suffix:semicolon
id|nfsd_racache_shutdown
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release read-ahead cache */
)brace
id|list_del
c_func
(paren
op_amp
id|me.list
)paren
suffix:semicolon
id|nfsdstats.th_cnt
op_decrement
suffix:semicolon
multiline_comment|/* Release the thread */
id|svc_exit_thread
c_func
(paren
id|rqstp
)paren
suffix:semicolon
multiline_comment|/* Release module */
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd_dispatch
id|nfsd_dispatch
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
id|u32
op_star
id|statp
)paren
(brace
r_struct
id|svc_procedure
op_star
id|proc
suffix:semicolon
id|kxdrproc_t
id|xdr
suffix:semicolon
id|u32
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd_dispatch: vers %d proc %d&bslash;n&quot;
comma
id|rqstp-&gt;rq_vers
comma
id|rqstp-&gt;rq_proc
)paren
suffix:semicolon
id|proc
op_assign
id|rqstp-&gt;rq_procinfo
suffix:semicolon
multiline_comment|/* Check whether we have this call in the cache. */
r_switch
c_cond
(paren
id|nfsd_cache_lookup
c_func
(paren
id|rqstp
comma
id|proc-&gt;pc_cachetype
)paren
)paren
(brace
r_case
id|RC_INTR
suffix:colon
r_case
id|RC_DROPIT
suffix:colon
r_return
l_int|0
suffix:semicolon
r_case
id|RC_REPLY
suffix:colon
r_return
l_int|1
suffix:semicolon
r_case
id|RC_DOIT
suffix:colon
multiline_comment|/* do it */
)brace
multiline_comment|/* Decode arguments */
id|xdr
op_assign
id|proc-&gt;pc_decode
suffix:semicolon
r_if
c_cond
(paren
id|xdr
op_logical_and
op_logical_neg
id|xdr
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_argbuf.buf
comma
id|rqstp-&gt;rq_argp
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: failed to decode arguments!&bslash;n&quot;
)paren
suffix:semicolon
id|nfsd_cache_update
c_func
(paren
id|rqstp
comma
id|RC_NOCACHE
comma
l_int|NULL
)paren
suffix:semicolon
op_star
id|statp
op_assign
id|rpc_garbage_args
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Now call the procedure handler, and encode NFS status. */
id|nfserr
op_assign
id|proc
op_member_access_from_pointer
id|pc_func
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_argp
comma
id|rqstp-&gt;rq_resp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rqstp-&gt;rq_proc
op_ne
l_int|0
)paren
id|svc_putlong
c_func
(paren
op_amp
id|rqstp-&gt;rq_resbuf
comma
id|nfserr
)paren
suffix:semicolon
multiline_comment|/* Encode result.&n;&t; * For NFSv2, additional info is never returned in case of an error.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|nfserr
op_logical_and
id|rqstp-&gt;rq_vers
op_eq
l_int|2
)paren
)paren
(brace
id|xdr
op_assign
id|proc-&gt;pc_encode
suffix:semicolon
r_if
c_cond
(paren
id|xdr
op_logical_and
op_logical_neg
id|xdr
c_func
(paren
id|rqstp
comma
id|rqstp-&gt;rq_resbuf.buf
comma
id|rqstp-&gt;rq_resp
)paren
)paren
(brace
multiline_comment|/* Failed to encode result. Release cache entry */
id|dprintk
c_func
(paren
l_string|&quot;nfsd: failed to encode result!&bslash;n&quot;
)paren
suffix:semicolon
id|nfsd_cache_update
c_func
(paren
id|rqstp
comma
id|RC_NOCACHE
comma
l_int|NULL
)paren
suffix:semicolon
op_star
id|statp
op_assign
id|rpc_system_err
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
multiline_comment|/* Store reply in cache. */
id|nfsd_cache_update
c_func
(paren
id|rqstp
comma
id|proc-&gt;pc_cachetype
comma
id|statp
op_plus
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|nfsd_version2
r_static
r_struct
id|svc_version
id|nfsd_version2
op_assign
(brace
l_int|2
comma
l_int|18
comma
id|nfsd_procedures2
comma
id|nfsd_dispatch
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_NFSD_V3
DECL|variable|nfsd_version3
r_static
r_struct
id|svc_version
id|nfsd_version3
op_assign
(brace
l_int|3
comma
l_int|22
comma
id|nfsd_procedures3
comma
id|nfsd_dispatch
)brace
suffix:semicolon
macro_line|#endif
DECL|variable|nfsd_version
r_static
r_struct
id|svc_version
op_star
id|nfsd_version
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|nfsd_version2
comma
macro_line|#ifdef CONFIG_NFSD_V3
op_amp
id|nfsd_version3
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|NFSD_NRVERS
mdefine_line|#define NFSD_NRVERS&t;&t;(sizeof(nfsd_version)/sizeof(nfsd_version[0]))
DECL|variable|nfsd_program
r_struct
id|svc_program
id|nfsd_program
op_assign
(brace
id|NFS_PROGRAM
comma
multiline_comment|/* program number */
l_int|2
comma
id|NFSD_NRVERS
op_minus
l_int|1
comma
multiline_comment|/* version range */
id|NFSD_NRVERS
comma
multiline_comment|/* nr of entries in nfsd_version */
id|nfsd_version
comma
multiline_comment|/* version table */
l_string|&quot;nfsd&quot;
comma
multiline_comment|/* program name */
op_amp
id|nfsd_svcstats
comma
multiline_comment|/* version table */
)brace
suffix:semicolon
eof
