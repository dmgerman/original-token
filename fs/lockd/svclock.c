multiline_comment|/*&n; * linux/fs/lockd/svclock.c&n; *&n; * Handling of server-side locks, mostly of the blocked variety.&n; * This is the ugliest part of lockd because we tread on very thin ice.&n; * GRANT and CANCEL calls may get stuck, meet in mid-flight, etc.&n; * IMNSHO introducing the grant callback into the NLM protocol was one&n; * of the worst ideas Sun ever had. Except maybe for the idea of doing&n; * NFS file locking at all.&n; *&n; * I&squot;m trying hard to avoid race conditions by protecting most accesses&n; * to a file&squot;s list of blocked locks through a semaphore. The global&n; * list of blocked locks is not protected in this fashion however.&n; * Therefore, some functions (such as the RPC callback for the async grant&n; * call) move blocked locks towards the head of the list *while some other&n; * process might be traversing it*. This should not be a problem in&n; * practice, because this will only cause functions traversing the list&n; * to visit some blocks twice.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/nlm.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
DECL|macro|NLMDBG_FACILITY
mdefine_line|#define NLMDBG_FACILITY&t;&t;NLMDBG_SVCLOCK
r_static
r_void
id|nlmsvc_insert_block
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
comma
r_int
r_int
)paren
suffix:semicolon
r_static
r_int
id|nlmsvc_remove_block
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
)paren
suffix:semicolon
r_static
r_void
id|nlmsvc_grant_callback
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
r_static
r_void
id|nlmsvc_notify_blocked
c_func
(paren
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * The list of blocked locks to retry&n; */
DECL|variable|nlm_blocked
r_static
r_struct
id|nlm_block
op_star
id|nlm_blocked
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Insert a blocked lock into the global list&n; */
r_static
r_void
DECL|function|nlmsvc_insert_block
id|nlmsvc_insert_block
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
comma
r_int
r_int
id|when
)paren
(brace
r_struct
id|nlm_block
op_star
op_star
id|bp
comma
op_star
id|b
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_insert_block(%p, %ld)&bslash;n&quot;
comma
id|block
comma
id|when
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block-&gt;b_queued
)paren
id|nlmsvc_remove_block
c_func
(paren
id|block
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bp
op_assign
op_amp
id|nlm_blocked
suffix:semicolon
(paren
id|b
op_assign
op_star
id|bp
)paren
suffix:semicolon
id|bp
op_assign
op_amp
id|b-&gt;b_next
)paren
r_if
c_cond
(paren
id|when
OL
id|b-&gt;b_when
)paren
r_break
suffix:semicolon
id|block-&gt;b_queued
op_assign
l_int|1
suffix:semicolon
id|block-&gt;b_when
op_assign
id|when
suffix:semicolon
id|block-&gt;b_next
op_assign
id|b
suffix:semicolon
op_star
id|bp
op_assign
id|block
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a block from the global list&n; */
r_static
r_int
DECL|function|nlmsvc_remove_block
id|nlmsvc_remove_block
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
)paren
(brace
r_struct
id|nlm_block
op_star
op_star
id|bp
comma
op_star
id|b
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block-&gt;b_queued
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|bp
op_assign
op_amp
id|nlm_blocked
suffix:semicolon
(paren
id|b
op_assign
op_star
id|bp
)paren
suffix:semicolon
id|bp
op_assign
op_amp
id|b-&gt;b_next
)paren
(brace
r_if
c_cond
(paren
id|b
op_eq
id|block
)paren
(brace
op_star
id|bp
op_assign
id|block-&gt;b_next
suffix:semicolon
id|block-&gt;b_queued
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a block for a given lock and optionally remove it from&n; * the list.&n; */
r_static
r_struct
id|nlm_block
op_star
DECL|function|nlmsvc_lookup_block
id|nlmsvc_lookup_block
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
comma
r_int
id|remove
)paren
(brace
r_struct
id|nlm_block
op_star
op_star
id|head
comma
op_star
id|block
suffix:semicolon
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_lookup_block f=%p pd=%d %ld-%ld ty=%d&bslash;n&quot;
comma
id|file
comma
id|lock-&gt;fl.fl_pid
comma
id|lock-&gt;fl.fl_start
comma
id|lock-&gt;fl.fl_end
comma
id|lock-&gt;fl.fl_type
)paren
suffix:semicolon
r_for
c_loop
(paren
id|head
op_assign
op_amp
id|nlm_blocked
suffix:semicolon
(paren
id|block
op_assign
op_star
id|head
)paren
suffix:semicolon
id|head
op_assign
op_amp
id|block-&gt;b_next
)paren
(brace
id|fl
op_assign
op_amp
id|block-&gt;b_call.a_args.lock.fl
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: check f=%p pd=%d %ld-%ld ty=%d cookie=%x&bslash;n&quot;
comma
id|block-&gt;b_file
comma
id|fl-&gt;fl_pid
comma
id|fl-&gt;fl_start
comma
id|fl-&gt;fl_end
comma
id|fl-&gt;fl_type
comma
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|block-&gt;b_call.a_args.cookie.data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block-&gt;b_file
op_eq
id|file
op_logical_and
id|nlm_compare_locks
c_func
(paren
id|fl
comma
op_amp
id|lock-&gt;fl
)paren
)paren
(brace
r_if
c_cond
(paren
id|remove
)paren
op_star
id|head
op_assign
id|block-&gt;b_next
suffix:semicolon
r_return
id|block
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|nlm_cookie_match
r_static
r_inline
r_int
id|nlm_cookie_match
c_func
(paren
r_struct
id|nlm_cookie
op_star
id|a
comma
r_struct
id|nlm_cookie
op_star
id|b
)paren
(brace
r_if
c_cond
(paren
id|a-&gt;len
op_ne
id|b-&gt;len
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|memcmp
c_func
(paren
id|a-&gt;data
comma
id|b-&gt;data
comma
id|a-&gt;len
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a block with a given NLM cookie.&n; */
r_static
r_inline
r_struct
id|nlm_block
op_star
DECL|function|nlmsvc_find_block
id|nlmsvc_find_block
c_func
(paren
r_struct
id|nlm_cookie
op_star
id|cookie
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
r_for
c_loop
(paren
id|block
op_assign
id|nlm_blocked
suffix:semicolon
id|block
suffix:semicolon
id|block
op_assign
id|block-&gt;b_next
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;cookie: head of blocked queue %p, block %p&bslash;n&quot;
comma
id|nlm_blocked
comma
id|block
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nlm_cookie_match
c_func
(paren
op_amp
id|block-&gt;b_call.a_args.cookie
comma
id|cookie
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|block
suffix:semicolon
)brace
multiline_comment|/*&n; * Create a block and initialize it.&n; *&n; * Note: we explicitly set the cookie of the grant reply to that of&n; * the blocked lock request. The spec explicitly mentions that the client&n; * should _not_ rely on the callback containing the same cookie as the&n; * request, but (as I found out later) that&squot;s because some implementations&n; * do just this. Never mind the standards comittees, they support our&n; * logging industries.&n; */
r_static
r_inline
r_struct
id|nlm_block
op_star
DECL|function|nlmsvc_create_block
id|nlmsvc_create_block
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
comma
r_struct
id|nlm_cookie
op_star
id|cookie
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
r_struct
id|nlm_host
op_star
id|host
suffix:semicolon
r_struct
id|nlm_rqst
op_star
id|call
suffix:semicolon
multiline_comment|/* Create host handle for callback */
id|host
op_assign
id|nlmclnt_lookup_host
c_func
(paren
op_amp
id|rqstp-&gt;rq_addr
comma
id|rqstp-&gt;rq_prot
comma
id|rqstp-&gt;rq_vers
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Allocate memory for block, and initialize arguments */
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
(paren
r_struct
id|nlm_block
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|block
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|failed
suffix:semicolon
id|memset
c_func
(paren
id|block
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|block
)paren
)paren
suffix:semicolon
multiline_comment|/* Set notifier function for VFS, and init args */
id|lock-&gt;fl.fl_notify
op_assign
id|nlmsvc_notify_blocked
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|nlmclnt_setgrantargs
c_func
(paren
op_amp
id|block-&gt;b_call
comma
id|lock
)paren
)paren
r_goto
id|failed_free
suffix:semicolon
id|block-&gt;b_call.a_args.cookie
op_assign
op_star
id|cookie
suffix:semicolon
multiline_comment|/* see above */
id|dprintk
c_func
(paren
l_string|&quot;lockd: created block %p...&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
multiline_comment|/* Create and initialize the block */
id|block-&gt;b_daemon
op_assign
id|rqstp-&gt;rq_server
suffix:semicolon
id|block-&gt;b_host
op_assign
id|host
suffix:semicolon
id|block-&gt;b_file
op_assign
id|file
suffix:semicolon
multiline_comment|/* Add to file&squot;s list of blocks */
id|block-&gt;b_fnext
op_assign
id|file-&gt;f_blocks
suffix:semicolon
id|file-&gt;f_blocks
op_assign
id|block
suffix:semicolon
multiline_comment|/* Set up RPC arguments for callback */
id|call
op_assign
op_amp
id|block-&gt;b_call
suffix:semicolon
id|call-&gt;a_host
op_assign
id|host
suffix:semicolon
id|call-&gt;a_flags
op_assign
id|RPC_TASK_ASYNC
suffix:semicolon
r_return
id|block
suffix:semicolon
id|failed_free
suffix:colon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
id|failed
suffix:colon
id|nlm_release_host
c_func
(paren
id|host
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a block. If the lock was cancelled or the grant callback&n; * failed, unlock is set to 1.&n; * It is the caller&squot;s responsibility to check whether the file&n; * can be closed hereafter.&n; */
r_static
r_void
DECL|function|nlmsvc_delete_block
id|nlmsvc_delete_block
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
comma
r_int
id|unlock
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
op_assign
op_amp
id|block-&gt;b_call.a_args.lock.fl
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
op_assign
id|block-&gt;b_file
suffix:semicolon
r_struct
id|nlm_block
op_star
op_star
id|bp
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: deleting block %p...&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
multiline_comment|/* Remove block from list */
id|nlmsvc_remove_block
c_func
(paren
id|block
)paren
suffix:semicolon
multiline_comment|/* If granted, unlock it, else remove from inode block list */
r_if
c_cond
(paren
id|unlock
op_logical_and
id|block-&gt;b_granted
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: deleting granted lock&bslash;n&quot;
)paren
suffix:semicolon
id|fl-&gt;fl_type
op_assign
id|F_UNLCK
suffix:semicolon
id|posix_lock_file
c_func
(paren
op_amp
id|block-&gt;b_file-&gt;f_file
comma
id|fl
comma
l_int|0
)paren
suffix:semicolon
id|block-&gt;b_granted
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: unblocking blocked lock&bslash;n&quot;
)paren
suffix:semicolon
id|posix_unblock_lock
c_func
(paren
id|fl
)paren
suffix:semicolon
)brace
multiline_comment|/* If the block is in the middle of a GRANT callback,&n;&t; * don&squot;t kill it yet. */
r_if
c_cond
(paren
id|block-&gt;b_incall
)paren
(brace
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|NLM_NEVER
)paren
suffix:semicolon
id|block-&gt;b_done
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Remove block from file&squot;s list of blocks */
r_for
c_loop
(paren
id|bp
op_assign
op_amp
id|file-&gt;f_blocks
suffix:semicolon
op_star
id|bp
suffix:semicolon
id|bp
op_assign
op_amp
(paren
op_star
id|bp
)paren
op_member_access_from_pointer
id|b_fnext
)paren
(brace
r_if
c_cond
(paren
op_star
id|bp
op_eq
id|block
)paren
(brace
op_star
id|bp
op_assign
id|block-&gt;b_fnext
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|block-&gt;b_host
)paren
id|nlm_release_host
c_func
(paren
id|block-&gt;b_host
)paren
suffix:semicolon
id|nlmclnt_freegrantargs
c_func
(paren
op_amp
id|block-&gt;b_call
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Loop over all blocks and perform the action specified.&n; * (NLM_ACT_CHECK handled by nlmsvc_inspect_file).&n; */
r_int
DECL|function|nlmsvc_traverse_blocks
id|nlmsvc_traverse_blocks
c_func
(paren
r_struct
id|nlm_host
op_star
id|host
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_int
id|action
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
comma
op_star
id|next
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_for
c_loop
(paren
id|block
op_assign
id|file-&gt;f_blocks
suffix:semicolon
id|block
suffix:semicolon
id|block
op_assign
id|next
)paren
(brace
id|next
op_assign
id|block-&gt;b_fnext
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_MARK
)paren
id|block-&gt;b_host-&gt;h_inuse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|action
op_eq
id|NLM_ACT_UNLOCK
)paren
(brace
r_if
c_cond
(paren
id|host
op_eq
l_int|NULL
op_logical_or
id|host
op_eq
id|block-&gt;b_host
)paren
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Attempt to establish a lock, and if it can&squot;t be granted, block it&n; * if required.&n; */
id|u32
DECL|function|nlmsvc_lock
id|nlmsvc_lock
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
comma
r_int
id|wait
comma
r_struct
id|nlm_cookie
op_star
id|cookie
)paren
(brace
r_struct
id|file_lock
op_star
id|conflock
suffix:semicolon
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_lock(%04x/%ld, ty=%d, pi=%d, %ld-%ld, bl=%d)&bslash;n&quot;
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_dev
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_ino
comma
id|lock-&gt;fl.fl_type
comma
id|lock-&gt;fl.fl_pid
comma
id|lock-&gt;fl.fl_start
comma
id|lock-&gt;fl.fl_end
comma
id|wait
)paren
suffix:semicolon
multiline_comment|/* Lock file against concurrent access */
id|down
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
multiline_comment|/* Get existing block (in case client is busy-waiting) */
id|block
op_assign
id|nlmsvc_lookup_block
c_func
(paren
id|file
comma
id|lock
comma
l_int|0
)paren
suffix:semicolon
id|lock-&gt;fl.fl_flags
op_or_assign
id|FL_LOCKD
suffix:semicolon
id|again
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|conflock
op_assign
id|posix_test_lock
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
)paren
)paren
)paren
(brace
id|error
op_assign
id|posix_lock_file
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block
)paren
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: posix_lock_file returned %d&bslash;n&quot;
comma
op_minus
id|error
)paren
suffix:semicolon
r_switch
c_cond
(paren
op_minus
id|error
)paren
(brace
r_case
l_int|0
suffix:colon
r_return
id|nlm_granted
suffix:semicolon
r_case
id|EDEADLK
suffix:colon
macro_line|#ifdef CONFIG_LOCKD_V4
r_return
id|nlm4_deadlock
suffix:semicolon
multiline_comment|/* will be downgraded to lck_deined if this&n;&t;&t;&t;&t;&t;       * is a NLMv1,3 request */
macro_line|#else
multiline_comment|/* no applicable NLM status */
macro_line|#endif
r_case
id|EAGAIN
suffix:colon
r_return
id|nlm_lck_denied
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* includes ENOLCK */
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|wait
)paren
(brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
id|nlm_lck_denied
suffix:semicolon
)brace
multiline_comment|/* If we don&squot;t have a block, create and initialize it. Then&n;&t; * retry because we may have slept in kmalloc. */
r_if
c_cond
(paren
id|block
op_eq
l_int|NULL
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: blocking on this lock (allocating).&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|nlmsvc_create_block
c_func
(paren
id|rqstp
comma
id|file
comma
id|lock
comma
id|cookie
)paren
)paren
)paren
r_return
id|nlm_lck_denied_nolocks
suffix:semicolon
r_goto
id|again
suffix:semicolon
)brace
multiline_comment|/* Append to list of blocked */
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|NLM_NEVER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|block-&gt;b_call.a_args.lock.fl.fl_prevblock
)paren
(brace
multiline_comment|/* Now add block to block list of the conflicting lock&n;&t;&t;   if we haven&squot;t done so. */
id|dprintk
c_func
(paren
l_string|&quot;lockd: blocking on this lock.&bslash;n&quot;
)paren
suffix:semicolon
id|posix_block_lock
c_func
(paren
id|conflock
comma
op_amp
id|block-&gt;b_call.a_args.lock.fl
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
id|nlm_lck_blocked
suffix:semicolon
)brace
multiline_comment|/*&n; * Test for presence of a conflicting lock.&n; */
id|u32
DECL|function|nlmsvc_testlock
id|nlmsvc_testlock
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
comma
r_struct
id|nlm_lock
op_star
id|conflock
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_testlock(%04x/%ld, ty=%d, %ld-%ld)&bslash;n&quot;
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_dev
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_ino
comma
id|lock-&gt;fl.fl_type
comma
id|lock-&gt;fl.fl_start
comma
id|lock-&gt;fl.fl_end
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|fl
op_assign
id|posix_test_lock
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: conflicting lock(ty=%d, %ld-%ld)&bslash;n&quot;
comma
id|fl-&gt;fl_type
comma
id|fl-&gt;fl_start
comma
id|fl-&gt;fl_end
)paren
suffix:semicolon
id|conflock-&gt;caller
op_assign
l_string|&quot;somehost&quot;
suffix:semicolon
multiline_comment|/* FIXME */
id|conflock-&gt;oh.len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t return OH info */
id|conflock-&gt;fl
op_assign
op_star
id|fl
suffix:semicolon
r_return
id|nlm_lck_denied
suffix:semicolon
)brace
r_return
id|nlm_granted
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a lock.&n; * This implies a CANCEL call: We send a GRANT_MSG, the client replies&n; * with a GRANT_RES call which gets lost, and calls UNLOCK immediately&n; * afterwards. In this case the block will still be there, and hence&n; * must be removed.&n; */
id|u32
DECL|function|nlmsvc_unlock
id|nlmsvc_unlock
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
)paren
(brace
r_int
id|error
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_unlock(%04x/%ld, pi=%d, %ld-%ld)&bslash;n&quot;
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_dev
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_ino
comma
id|lock-&gt;fl.fl_pid
comma
id|lock-&gt;fl.fl_start
comma
id|lock-&gt;fl.fl_end
)paren
suffix:semicolon
multiline_comment|/* First, cancel any lock that might be there */
id|nlmsvc_cancel_blocked
c_func
(paren
id|file
comma
id|lock
)paren
suffix:semicolon
id|lock-&gt;fl.fl_type
op_assign
id|F_UNLCK
suffix:semicolon
id|error
op_assign
id|posix_lock_file
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|error
OL
l_int|0
)paren
ques
c_cond
id|nlm_lck_denied_nolocks
suffix:colon
id|nlm_granted
suffix:semicolon
)brace
multiline_comment|/*&n; * Cancel a previously blocked request.&n; *&n; * A cancel request always overrides any grant that may currently&n; * be in progress.&n; * The calling procedure must check whether the file can be closed.&n; */
id|u32
DECL|function|nlmsvc_cancel_blocked
id|nlmsvc_cancel_blocked
c_func
(paren
r_struct
id|nlm_file
op_star
id|file
comma
r_struct
id|nlm_lock
op_star
id|lock
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: nlmsvc_cancel(%04x/%ld, pi=%d, %ld-%ld)&bslash;n&quot;
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_dev
comma
id|file-&gt;f_file.f_dentry-&gt;d_inode-&gt;i_ino
comma
id|lock-&gt;fl.fl_pid
comma
id|lock-&gt;fl.fl_start
comma
id|lock-&gt;fl.fl_end
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_assign
id|nlmsvc_lookup_block
c_func
(paren
id|file
comma
id|lock
comma
l_int|1
)paren
)paren
op_ne
l_int|NULL
)paren
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|1
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
id|nlm_granted
suffix:semicolon
)brace
multiline_comment|/*&n; * Unblock a blocked lock request. This is a callback invoked from the&n; * VFS layer when a lock on which we blocked is removed.&n; *&n; * This function doesn&squot;t grant the blocked lock instantly, but rather moves&n; * the block to the head of nlm_blocked where it can be picked up by lockd.&n; */
r_static
r_void
DECL|function|nlmsvc_notify_blocked
id|nlmsvc_notify_blocked
c_func
(paren
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|nlm_block
op_star
op_star
id|bp
comma
op_star
id|block
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: VFS unblock notification for block %p&bslash;n&quot;
comma
id|fl
)paren
suffix:semicolon
id|posix_unblock_lock
c_func
(paren
id|fl
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bp
op_assign
op_amp
id|nlm_blocked
suffix:semicolon
(paren
id|block
op_assign
op_star
id|bp
)paren
suffix:semicolon
id|bp
op_assign
op_amp
id|block-&gt;b_next
)paren
(brace
r_if
c_cond
(paren
id|nlm_compare_locks
c_func
(paren
op_amp
id|block-&gt;b_call.a_args.lock.fl
comma
id|fl
)paren
)paren
(brace
id|svc_wake_up
c_func
(paren
id|block-&gt;b_daemon
)paren
suffix:semicolon
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;lockd: notification for unknown block!&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to claim a lock that was previously blocked.&n; *&n; * Note that we use both the RPC_GRANTED_MSG call _and_ an async&n; * RPC thread when notifying the client. This seems like overkill...&n; * Here&squot;s why:&n; *  -&t;we don&squot;t want to use a synchronous RPC thread, otherwise&n; *&t;we might find ourselves hanging on a dead portmapper.&n; *  -&t;Some lockd implementations (e.g. HP) don&squot;t react to&n; *&t;RPC_GRANTED calls; they seem to insist on RPC_GRANTED_MSG calls.&n; */
r_static
r_void
DECL|function|nlmsvc_grant_blocked
id|nlmsvc_grant_blocked
c_func
(paren
r_struct
id|nlm_block
op_star
id|block
)paren
(brace
r_struct
id|nlm_file
op_star
id|file
op_assign
id|block-&gt;b_file
suffix:semicolon
r_struct
id|nlm_lock
op_star
id|lock
op_assign
op_amp
id|block-&gt;b_call.a_args.lock
suffix:semicolon
r_struct
id|file_lock
op_star
id|conflock
suffix:semicolon
r_int
id|error
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: grant blocked lock %p&bslash;n&quot;
comma
id|block
)paren
suffix:semicolon
multiline_comment|/* First thing is lock the file */
id|down
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
multiline_comment|/* Unlink block request from list */
id|nlmsvc_remove_block
c_func
(paren
id|block
)paren
suffix:semicolon
multiline_comment|/* If b_granted is true this means we&squot;ve been here before.&n;&t; * Just retry the grant callback, possibly refreshing the RPC&n;&t; * binding */
r_if
c_cond
(paren
id|block-&gt;b_granted
)paren
(brace
id|nlm_rebind_host
c_func
(paren
id|block-&gt;b_host
)paren
suffix:semicolon
r_goto
id|callback
suffix:semicolon
)brace
multiline_comment|/* Try the lock operation again */
r_if
c_cond
(paren
(paren
id|conflock
op_assign
id|posix_test_lock
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Bummer, we blocked again */
id|dprintk
c_func
(paren
l_string|&quot;lockd: lock still blocked&bslash;n&quot;
)paren
suffix:semicolon
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|NLM_NEVER
)paren
suffix:semicolon
id|posix_block_lock
c_func
(paren
id|conflock
comma
op_amp
id|lock-&gt;fl
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Alright, no conflicting lock. Now lock it for real. If the&n;&t; * following yields an error, this is most probably due to low&n;&t; * memory. Retry the lock in a few seconds.&n;&t; */
r_if
c_cond
(paren
(paren
id|error
op_assign
id|posix_lock_file
c_func
(paren
op_amp
id|file-&gt;f_file
comma
op_amp
id|lock-&gt;fl
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
id|KERN_WARNING
l_string|&quot;lockd: unexpected error %d in %s!&bslash;n&quot;
comma
op_minus
id|error
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|jiffies
op_plus
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|callback
suffix:colon
multiline_comment|/* Lock was granted by VFS. */
id|dprintk
c_func
(paren
l_string|&quot;lockd: GRANTing blocked lock.&bslash;n&quot;
)paren
suffix:semicolon
id|block-&gt;b_granted
op_assign
l_int|1
suffix:semicolon
id|block-&gt;b_incall
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Schedule next grant callback in 30 seconds */
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|jiffies
op_plus
l_int|30
op_star
id|HZ
)paren
suffix:semicolon
multiline_comment|/* Call the client */
id|nlmclnt_async_call
c_func
(paren
op_amp
id|block-&gt;b_call
comma
id|NLMPROC_GRANTED_MSG
comma
id|nlmsvc_grant_callback
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the callback from the RPC layer when the NLM_GRANTED_MSG&n; * RPC call has succeeded or timed out.&n; * Like all RPC callbacks, it is invoked by the rpciod process, so it&n; * better not sleep. Therefore, we put the blocked lock on the nlm_blocked&n; * chain once more in order to have it removed by lockd itself (which can&n; * then sleep on the file semaphore without disrupting e.g. the nfs client).&n; */
r_static
r_void
DECL|function|nlmsvc_grant_callback
id|nlmsvc_grant_callback
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
id|call
op_assign
(paren
r_struct
id|nlm_rqst
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
r_int
r_int
id|timeout
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;lockd: GRANT_MSG RPC callback&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;callback: looking for cookie %x &bslash;n&quot;
comma
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|call-&gt;a_args.cookie.data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|nlmsvc_find_block
c_func
(paren
op_amp
id|call-&gt;a_args.cookie
)paren
)paren
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;lockd: no block for cookie %x&bslash;n&quot;
comma
op_star
(paren
id|u32
op_star
)paren
(paren
id|call-&gt;a_args.cookie.data
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Technically, we should down the file semaphore here. Since we&n;&t; * move the block towards the head of the queue only, no harm&n;&t; * can be done, though. */
r_if
c_cond
(paren
id|task-&gt;tk_status
OL
l_int|0
)paren
(brace
multiline_comment|/* RPC error: Re-insert for retransmission */
id|timeout
op_assign
id|jiffies
op_plus
l_int|10
op_star
id|HZ
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|block-&gt;b_done
)paren
(brace
multiline_comment|/* Block already removed, kill it for real */
id|timeout
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Call was successful, now wait for client callback */
id|timeout
op_assign
id|jiffies
op_plus
l_int|60
op_star
id|HZ
suffix:semicolon
)brace
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|timeout
)paren
suffix:semicolon
id|svc_wake_up
c_func
(paren
id|block-&gt;b_daemon
)paren
suffix:semicolon
id|block-&gt;b_incall
op_assign
l_int|0
suffix:semicolon
id|nlm_release_host
c_func
(paren
id|call-&gt;a_host
)paren
suffix:semicolon
id|rpc_release_task
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We received a GRANT_RES callback. Try to find the corresponding&n; * block.&n; */
r_void
DECL|function|nlmsvc_grant_reply
id|nlmsvc_grant_reply
c_func
(paren
r_struct
id|nlm_cookie
op_star
id|cookie
comma
id|u32
id|status
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
r_struct
id|nlm_file
op_star
id|file
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|block
op_assign
id|nlmsvc_find_block
c_func
(paren
id|cookie
)paren
)paren
)paren
r_return
suffix:semicolon
id|file
op_assign
id|block-&gt;b_file
suffix:semicolon
id|file-&gt;f_count
op_increment
suffix:semicolon
id|down
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|block
op_assign
id|nlmsvc_find_block
c_func
(paren
id|cookie
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|status
op_eq
id|NLM_LCK_DENIED_GRACE_PERIOD
)paren
(brace
multiline_comment|/* Try again in a couple of seconds */
id|nlmsvc_insert_block
c_func
(paren
id|block
comma
id|jiffies
op_plus
l_int|10
op_star
id|HZ
)paren
suffix:semicolon
id|block
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Lock is now held by client, or has been rejected.&n;&t;&t;&t; * In both cases, the block should be removed. */
id|file-&gt;f_count
op_increment
suffix:semicolon
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|NLM_LCK_GRANTED
)paren
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|0
)paren
suffix:semicolon
r_else
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|block
)paren
id|up
c_func
(paren
op_amp
id|file-&gt;f_sema
)paren
suffix:semicolon
id|nlm_release_file
c_func
(paren
id|file
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Retry all blocked locks that have been notified. This is where lockd&n; * picks up locks that can be granted, or grant notifications that must&n; * be retransmitted.&n; */
r_int
r_int
DECL|function|nlmsvc_retry_blocked
id|nlmsvc_retry_blocked
c_func
(paren
r_void
)paren
(brace
r_struct
id|nlm_block
op_star
id|block
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nlmsvc_retry_blocked(%p, when=%ld)&bslash;n&quot;
comma
id|nlm_blocked
comma
id|nlm_blocked
ques
c_cond
id|nlm_blocked-&gt;b_when
suffix:colon
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|block
op_assign
id|nlm_blocked
)paren
op_logical_and
id|block-&gt;b_when
op_le
id|jiffies
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nlmsvc_retry_blocked(%p, when=%ld, done=%d)&bslash;n&quot;
comma
id|block
comma
id|block-&gt;b_when
comma
id|block-&gt;b_done
)paren
suffix:semicolon
r_if
c_cond
(paren
id|block-&gt;b_done
)paren
id|nlmsvc_delete_block
c_func
(paren
id|block
comma
l_int|0
)paren
suffix:semicolon
r_else
id|nlmsvc_grant_blocked
c_func
(paren
id|block
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|block
op_assign
id|nlm_blocked
)paren
op_logical_and
id|block-&gt;b_when
op_ne
id|NLM_NEVER
)paren
r_return
(paren
id|block-&gt;b_when
op_minus
id|jiffies
)paren
suffix:semicolon
r_return
id|MAX_SCHEDULE_TIMEOUT
suffix:semicolon
)brace
eof
