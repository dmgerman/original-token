multiline_comment|/*&n; * linux/include/linux/sunrpc/sched.h&n; *&n; * Scheduling primitives for kernel Sun RPC.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#ifndef _LINUX_SUNRPC_SCHED_H_
DECL|macro|_LINUX_SUNRPC_SCHED_H_
mdefine_line|#define _LINUX_SUNRPC_SCHED_H_
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/sunrpc/types.h&gt;
multiline_comment|/*&n; * Define this if you want to test the fast scheduler for async calls.&n; * This is still experimental and may not work.&n; */
DECL|macro|CONFIG_RPC_FASTSCHED
macro_line|#undef  CONFIG_RPC_FASTSCHED
multiline_comment|/*&n; * This is the RPC task struct&n; */
DECL|struct|rpc_task
r_struct
id|rpc_task
(brace
DECL|member|tk_prev
r_struct
id|rpc_task
op_star
id|tk_prev
suffix:semicolon
multiline_comment|/* wait queue links */
DECL|member|tk_next
r_struct
id|rpc_task
op_star
id|tk_next
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
DECL|member|tk_magic
r_int
r_int
id|tk_magic
suffix:semicolon
multiline_comment|/* 0xf00baa */
macro_line|#endif
DECL|member|tk_next_task
r_struct
id|rpc_task
op_star
id|tk_next_task
suffix:semicolon
multiline_comment|/* global list of tasks */
DECL|member|tk_prev_task
r_struct
id|rpc_task
op_star
id|tk_prev_task
suffix:semicolon
multiline_comment|/* global list of tasks */
DECL|member|tk_client
r_struct
id|rpc_clnt
op_star
id|tk_client
suffix:semicolon
multiline_comment|/* RPC client */
DECL|member|tk_rqstp
r_struct
id|rpc_rqst
op_star
id|tk_rqstp
suffix:semicolon
multiline_comment|/* RPC request */
DECL|member|tk_cred
r_struct
id|rpc_cred
op_star
id|tk_cred
suffix:semicolon
multiline_comment|/* RPC credentials */
DECL|member|tk_status
r_int
id|tk_status
suffix:semicolon
multiline_comment|/* result of last operation */
DECL|member|tk_rpcwait
r_struct
id|rpc_wait_queue
op_star
id|tk_rpcwait
suffix:semicolon
multiline_comment|/* RPC wait queue we&squot;re on */
multiline_comment|/*&n;&t; * RPC call state&n;&t; */
DECL|member|tk_proc
id|u32
id|tk_proc
suffix:semicolon
multiline_comment|/* procedure number */
DECL|member|tk_buffer
id|u32
op_star
id|tk_buffer
suffix:semicolon
multiline_comment|/* XDR buffer */
DECL|member|tk_argp
r_void
op_star
id|tk_argp
suffix:semicolon
multiline_comment|/* argument storage */
DECL|member|tk_resp
r_void
op_star
id|tk_resp
suffix:semicolon
multiline_comment|/* result storage */
DECL|member|tk_garb_retry
id|u8
id|tk_garb_retry
comma
DECL|member|tk_cred_retry
id|tk_cred_retry
comma
DECL|member|tk_suid_retry
id|tk_suid_retry
suffix:semicolon
multiline_comment|/*&n;&t; * callback&t;to be executed after waking up&n;&t; * action&t;next procedure for async tasks&n;&t; * exit&t;&t;exit async task and report to caller&n;&t; */
DECL|member|tk_callback
r_void
(paren
op_star
id|tk_callback
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_action
r_void
(paren
op_star
id|tk_action
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_exit
r_void
(paren
op_star
id|tk_exit
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
DECL|member|tk_calldata
r_void
op_star
id|tk_calldata
suffix:semicolon
multiline_comment|/*&n;&t; * tk_timer is used for async processing by the RPC scheduling&n;&t; * primitives. You should not access this directly unless&n;&t; * you have a pathological interest in kernel oopses.&n;&t; */
DECL|member|tk_timer
r_struct
id|timer_list
id|tk_timer
suffix:semicolon
multiline_comment|/* kernel timer */
DECL|member|tk_wait
r_struct
id|wait_queue
op_star
id|tk_wait
suffix:semicolon
multiline_comment|/* sync: sleep on this q */
DECL|member|tk_timeout
r_int
r_int
id|tk_timeout
suffix:semicolon
multiline_comment|/* timeout for rpc_sleep() */
DECL|member|tk_flags
r_int
r_int
id|tk_flags
suffix:semicolon
multiline_comment|/* misc flags */
macro_line|#ifdef RPC_DEBUG
DECL|member|tk_pid
r_int
r_int
id|tk_pid
suffix:semicolon
multiline_comment|/* debugging aid */
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|tk_auth
mdefine_line|#define tk_auth&t;&t;&t;tk_client-&gt;cl_auth
DECL|macro|tk_xprt
mdefine_line|#define tk_xprt&t;&t;&t;tk_client-&gt;cl_xprt
DECL|typedef|rpc_action
r_typedef
r_void
(paren
op_star
id|rpc_action
)paren
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * RPC task flags&n; */
DECL|macro|RPC_TASK_RUNNING
mdefine_line|#define RPC_TASK_RUNNING&t;0x0001&t;&t;/* is running */
DECL|macro|RPC_TASK_ASYNC
mdefine_line|#define RPC_TASK_ASYNC&t;&t;0x0002&t;&t;/* is an async task */
DECL|macro|RPC_TASK_CALLBACK
mdefine_line|#define RPC_TASK_CALLBACK&t;0x0004&t;&t;/* invoke callback */
DECL|macro|RPC_TASK_SWAPPER
mdefine_line|#define RPC_TASK_SWAPPER&t;0x0008&t;&t;/* is swapping in/out */
DECL|macro|RPC_TASK_SETUID
mdefine_line|#define RPC_TASK_SETUID&t;&t;0x0010&t;&t;/* is setuid process */
DECL|macro|RPC_TASK_CHILD
mdefine_line|#define RPC_TASK_CHILD&t;&t;0x0020&t;&t;/* is child of other task */
DECL|macro|RPC_CALL_REALUID
mdefine_line|#define RPC_CALL_REALUID&t;0x0040&t;&t;/* try using real uid */
DECL|macro|RPC_CALL_MAJORSEEN
mdefine_line|#define RPC_CALL_MAJORSEEN&t;0x0080&t;&t;/* major timeout seen */
DECL|macro|RPC_TASK_ROOTCREDS
mdefine_line|#define RPC_TASK_ROOTCREDS&t;0x0100&t;&t;/* force root creds */
DECL|macro|RPC_TASK_DYNAMIC
mdefine_line|#define RPC_TASK_DYNAMIC&t;0x0200&t;&t;/* task was kmalloc&squot;ed */
DECL|macro|RPC_TASK_KILLED
mdefine_line|#define RPC_TASK_KILLED&t;&t;0x0400&t;&t;/* task was killed */
DECL|macro|RPC_IS_RUNNING
mdefine_line|#define RPC_IS_RUNNING(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_RUNNING)
DECL|macro|RPC_IS_ASYNC
mdefine_line|#define RPC_IS_ASYNC(t)&t;&t;((t)-&gt;tk_flags &amp; RPC_TASK_ASYNC)
DECL|macro|RPC_IS_SETUID
mdefine_line|#define RPC_IS_SETUID(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_SETUID)
DECL|macro|RPC_IS_CHILD
mdefine_line|#define RPC_IS_CHILD(t)&t;&t;((t)-&gt;tk_flags &amp; RPC_TASK_CHILD)
DECL|macro|RPC_IS_SWAPPER
mdefine_line|#define RPC_IS_SWAPPER(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_SWAPPER)
DECL|macro|RPC_DO_CALLBACK
mdefine_line|#define RPC_DO_CALLBACK(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_CALLBACK)
DECL|macro|RPC_DO_ROOTOVERRIDE
mdefine_line|#define RPC_DO_ROOTOVERRIDE(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_ROOTCREDS)
DECL|macro|RPC_ASSASSINATED
mdefine_line|#define RPC_ASSASSINATED(t)&t;((t)-&gt;tk_flags &amp; RPC_TASK_KILLED)
multiline_comment|/*&n; * RPC synchronization objects&n; */
DECL|struct|rpc_wait_queue
r_struct
id|rpc_wait_queue
(brace
DECL|member|task
r_struct
id|rpc_task
op_star
id|task
suffix:semicolon
macro_line|#ifdef RPC_DEBUG
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifndef RPC_DEBUG
DECL|macro|RPC_INIT_WAITQ
macro_line|# define RPC_INIT_WAITQ(name)&t;((struct rpc_wait_queue) { NULL })
macro_line|#else
DECL|macro|RPC_INIT_WAITQ
macro_line|# define RPC_INIT_WAITQ(name)&t;((struct rpc_wait_queue) { NULL, name })
macro_line|#endif
multiline_comment|/*&n; * Function prototypes&n; */
r_struct
id|rpc_task
op_star
id|rpc_new_task
c_func
(paren
r_struct
id|rpc_clnt
op_star
comma
id|rpc_action
comma
r_int
id|flags
)paren
suffix:semicolon
r_struct
id|rpc_task
op_star
id|rpc_new_child
c_func
(paren
r_struct
id|rpc_clnt
op_star
comma
r_struct
id|rpc_task
op_star
id|parent
)paren
suffix:semicolon
r_void
id|rpc_init_task
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_struct
id|rpc_clnt
op_star
comma
id|rpc_action
id|exitfunc
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|rpc_release_task
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_killall_tasks
c_func
(paren
r_struct
id|rpc_clnt
op_star
)paren
suffix:semicolon
r_void
id|rpc_execute
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_run_child
c_func
(paren
r_struct
id|rpc_task
op_star
id|parent
comma
r_struct
id|rpc_task
op_star
id|child
comma
id|rpc_action
id|action
)paren
suffix:semicolon
r_void
id|rpc_add_wait_queue
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_remove_wait_queue
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_sleep_on
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_struct
id|rpc_task
op_star
comma
id|rpc_action
id|action
comma
id|rpc_action
id|timer
)paren
suffix:semicolon
r_void
id|rpc_cond_wait
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_struct
id|rpc_task
op_star
comma
r_int
r_char
op_star
comma
id|rpc_action
id|action
comma
id|rpc_action
id|timer
)paren
suffix:semicolon
r_void
id|rpc_wake_up_task
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_wake_up
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
)paren
suffix:semicolon
r_struct
id|rpc_task
op_star
id|rpc_wake_up_next
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
)paren
suffix:semicolon
r_void
id|rpc_wake_up_status
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|rpc_add_timer
c_func
(paren
r_struct
id|rpc_task
op_star
comma
id|rpc_action
)paren
suffix:semicolon
r_void
id|rpc_del_timer
c_func
(paren
r_struct
id|rpc_task
op_star
)paren
suffix:semicolon
r_void
id|rpc_delay
c_func
(paren
r_struct
id|rpc_task
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
op_star
id|rpc_allocate
c_func
(paren
r_int
r_int
id|flags
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|rpc_free
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_int
id|rpciod_up
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|rpciod_down
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|__inline__
r_void
op_star
DECL|function|rpc_malloc
id|rpc_malloc
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
r_int
r_int
id|size
)paren
(brace
r_return
id|rpc_allocate
c_func
(paren
id|task-&gt;tk_flags
comma
id|size
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|rpc_exit
id|rpc_exit
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
r_int
id|status
)paren
(brace
id|task-&gt;tk_status
op_assign
id|status
suffix:semicolon
id|task-&gt;tk_action
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef RPC_DEBUG
r_extern
id|__inline__
r_char
op_star
DECL|function|rpc_qname
id|rpc_qname
c_func
(paren
r_struct
id|rpc_wait_queue
op_star
id|q
)paren
(brace
r_return
id|q-&gt;name
ques
c_cond
id|q-&gt;name
suffix:colon
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif /* _LINUX_SUNRPC_SCHED_H_ */
eof
