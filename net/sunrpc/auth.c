multiline_comment|/*&n; * linux/fs/nfs/rpcauth.c&n; *&n; * Generic RPC authentication API.&n; *&n; * Copyright (C) 1996, Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#ifdef RPC_DEBUG
DECL|macro|RPCDBG_FACILITY
macro_line|# define RPCDBG_FACILITY&t;RPCDBG_AUTH
macro_line|#endif
DECL|macro|RPC_MAXFLAVOR
mdefine_line|#define RPC_MAXFLAVOR&t;8
DECL|variable|auth_flavors
r_static
r_struct
id|rpc_authops
op_star
id|auth_flavors
(braket
id|RPC_MAXFLAVOR
)braket
op_assign
(brace
op_amp
id|authnull_ops
comma
multiline_comment|/* AUTH_NULL */
op_amp
id|authunix_ops
comma
multiline_comment|/* AUTH_UNIX */
l_int|NULL
comma
multiline_comment|/* others can be loadable modules */
)brace
suffix:semicolon
r_int
DECL|function|rpcauth_register
id|rpcauth_register
c_func
(paren
r_struct
id|rpc_authops
op_star
id|ops
)paren
(brace
r_int
r_int
id|flavor
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flavor
op_assign
id|ops-&gt;au_flavor
)paren
op_ge
id|RPC_MAXFLAVOR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|auth_flavors
(braket
id|flavor
)braket
op_ne
l_int|NULL
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* what else? */
id|auth_flavors
(braket
id|flavor
)braket
op_assign
id|ops
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|rpcauth_unregister
id|rpcauth_unregister
c_func
(paren
r_struct
id|rpc_authops
op_star
id|ops
)paren
(brace
r_int
r_int
id|flavor
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flavor
op_assign
id|ops-&gt;au_flavor
)paren
op_ge
id|RPC_MAXFLAVOR
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|auth_flavors
(braket
id|flavor
)braket
op_ne
id|ops
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/* what else? */
id|auth_flavors
(braket
id|flavor
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_struct
id|rpc_auth
op_star
DECL|function|rpcauth_create
id|rpcauth_create
c_func
(paren
r_int
r_int
id|flavor
comma
r_struct
id|rpc_clnt
op_star
id|clnt
)paren
(brace
r_struct
id|rpc_authops
op_star
id|ops
suffix:semicolon
r_if
c_cond
(paren
id|flavor
op_ge
id|RPC_MAXFLAVOR
op_logical_or
op_logical_neg
(paren
id|ops
op_assign
id|auth_flavors
(braket
id|flavor
)braket
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|clnt-&gt;cl_auth
op_assign
id|ops
op_member_access_from_pointer
id|create
c_func
(paren
id|clnt
)paren
suffix:semicolon
r_return
id|clnt-&gt;cl_auth
suffix:semicolon
)brace
r_void
DECL|function|rpcauth_destroy
id|rpcauth_destroy
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
id|auth-&gt;au_ops
op_member_access_from_pointer
id|destroy
c_func
(paren
id|auth
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize RPC credential cache&n; */
r_void
DECL|function|rpcauth_init_credcache
id|rpcauth_init_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
id|memset
c_func
(paren
id|auth-&gt;au_credcache
comma
l_int|0
comma
r_sizeof
(paren
id|auth-&gt;au_credcache
)paren
)paren
suffix:semicolon
id|auth-&gt;au_nextgc
op_assign
id|jiffies
op_plus
(paren
id|auth-&gt;au_expire
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Clear the RPC credential cache&n; */
r_void
DECL|function|rpcauth_free_credcache
id|rpcauth_free_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
r_struct
id|rpc_cred
op_star
op_star
id|q
comma
op_star
id|cred
suffix:semicolon
r_void
(paren
op_star
id|destroy
)paren
(paren
r_struct
id|rpc_cred
op_star
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|destroy
op_assign
id|auth-&gt;au_ops-&gt;crdestroy
)paren
)paren
id|destroy
op_assign
(paren
r_void
(paren
op_star
)paren
(paren
r_struct
id|rpc_cred
op_star
)paren
)paren
id|rpc_free
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
id|RPC_CREDCACHE_NR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|q
op_assign
op_amp
id|auth-&gt;au_credcache
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cred
op_assign
op_star
id|q
)paren
op_ne
l_int|NULL
)paren
(brace
op_star
id|q
op_assign
id|cred-&gt;cr_next
suffix:semicolon
id|destroy
c_func
(paren
id|cred
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Remove stale credentials. Avoid sleeping inside the loop.&n; */
r_static
r_void
DECL|function|rpcauth_gc_credcache
id|rpcauth_gc_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
)paren
(brace
r_struct
id|rpc_cred
op_star
op_star
id|q
comma
op_star
id|cred
comma
op_star
id|free
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|safe
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: gc&squot;ing RPC credentials for auth %p&bslash;n&quot;
comma
id|auth
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
id|RPC_CREDCACHE_NR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|q
op_assign
op_amp
id|auth-&gt;au_credcache
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cred
op_assign
op_star
id|q
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
op_increment
id|safe
OG
l_int|500
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;RPC: rpcauth_gc_credcache looping!&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cred-&gt;cr_count
op_logical_and
id|cred-&gt;cr_expire
OL
id|jiffies
)paren
(brace
op_star
id|q
op_assign
id|cred-&gt;cr_next
suffix:semicolon
id|cred-&gt;cr_next
op_assign
id|free
suffix:semicolon
id|free
op_assign
id|cred
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|cred-&gt;cr_next
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
(paren
id|cred
op_assign
id|free
)paren
op_ne
l_int|NULL
)paren
(brace
id|free
op_assign
id|cred-&gt;cr_next
suffix:semicolon
id|rpc_free
c_func
(paren
id|cred
)paren
suffix:semicolon
)brace
id|auth-&gt;au_nextgc
op_assign
id|jiffies
op_plus
id|auth-&gt;au_expire
suffix:semicolon
)brace
multiline_comment|/*&n; * Insert credential into cache&n; */
r_inline
r_void
DECL|function|rpcauth_insert_credcache
id|rpcauth_insert_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
comma
r_struct
id|rpc_cred
op_star
id|cred
)paren
(brace
r_int
id|nr
suffix:semicolon
id|nr
op_assign
(paren
id|cred-&gt;cr_uid
op_mod
id|RPC_CREDCACHE_NR
)paren
suffix:semicolon
id|cred-&gt;cr_next
op_assign
id|auth-&gt;au_credcache
(braket
id|nr
)braket
suffix:semicolon
id|auth-&gt;au_credcache
(braket
id|nr
)braket
op_assign
id|cred
suffix:semicolon
id|cred-&gt;cr_expire
op_assign
id|jiffies
op_plus
id|auth-&gt;au_expire
suffix:semicolon
id|cred-&gt;cr_count
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * Look up a process&squot; credentials in the authentication cache&n; */
r_static
r_struct
id|rpc_cred
op_star
DECL|function|rpcauth_lookup_credcache
id|rpcauth_lookup_credcache
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
r_struct
id|rpc_cred
op_star
op_star
id|q
comma
op_star
id|cred
op_assign
l_int|NULL
suffix:semicolon
r_int
id|nr
suffix:semicolon
id|nr
op_assign
id|RPC_DO_ROOTOVERRIDE
c_func
(paren
id|task
)paren
ques
c_cond
l_int|0
suffix:colon
(paren
id|current-&gt;uid
op_mod
id|RPC_CREDCACHE_NR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|auth-&gt;au_nextgc
OL
id|jiffies
)paren
id|rpcauth_gc_credcache
c_func
(paren
id|auth
)paren
suffix:semicolon
id|q
op_assign
op_amp
id|auth-&gt;au_credcache
(braket
id|nr
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cred
op_assign
op_star
id|q
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crmatch
c_func
(paren
id|task
comma
id|cred
)paren
)paren
(brace
op_star
id|q
op_assign
id|cred-&gt;cr_next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|cred-&gt;cr_next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cred
)paren
id|cred
op_assign
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crcreate
c_func
(paren
id|task
)paren
suffix:semicolon
id|rpcauth_insert_credcache
c_func
(paren
id|auth
comma
id|cred
)paren
suffix:semicolon
r_return
(paren
r_struct
id|rpc_cred
op_star
)paren
id|cred
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove cred handle from cache&n; */
r_static
r_inline
r_void
DECL|function|rpcauth_remove_credcache
id|rpcauth_remove_credcache
c_func
(paren
r_struct
id|rpc_auth
op_star
id|auth
comma
r_struct
id|rpc_cred
op_star
id|cred
)paren
(brace
r_struct
id|rpc_cred
op_star
op_star
id|q
comma
op_star
id|cr
suffix:semicolon
r_int
id|nr
suffix:semicolon
id|nr
op_assign
(paren
id|cred-&gt;cr_uid
op_mod
id|RPC_CREDCACHE_NR
)paren
suffix:semicolon
id|q
op_assign
op_amp
id|auth-&gt;au_credcache
(braket
id|nr
)braket
suffix:semicolon
r_while
c_loop
(paren
(paren
id|cr
op_assign
op_star
id|q
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|cred
op_eq
id|cr
)paren
(brace
op_star
id|q
op_assign
id|cred-&gt;cr_next
suffix:semicolon
r_return
suffix:semicolon
)brace
id|q
op_assign
op_amp
id|cred-&gt;cr_next
suffix:semicolon
)brace
)brace
r_struct
id|rpc_cred
op_star
DECL|function|rpcauth_lookupcred
id|rpcauth_lookupcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d looking up %s cred&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_auth-&gt;au_ops-&gt;au_name
)paren
suffix:semicolon
r_return
id|task-&gt;tk_cred
op_assign
id|rpcauth_lookup_credcache
c_func
(paren
id|task
)paren
suffix:semicolon
)brace
r_int
DECL|function|rpcauth_matchcred
id|rpcauth_matchcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
r_struct
id|rpc_cred
op_star
id|cred
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d matching %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_return
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crmatch
c_func
(paren
id|task
comma
id|cred
)paren
suffix:semicolon
)brace
r_void
DECL|function|rpcauth_holdcred
id|rpcauth_holdcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d holding %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_cred
)paren
id|task-&gt;tk_cred-&gt;cr_count
op_increment
suffix:semicolon
)brace
r_void
DECL|function|rpcauth_releasecred
id|rpcauth_releasecred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d releasing %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cred
op_assign
id|task-&gt;tk_cred
)paren
op_ne
l_int|NULL
)paren
(brace
id|cred-&gt;cr_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|cred-&gt;cr_flags
op_amp
id|RPCAUTH_CRED_DEAD
)paren
(brace
id|rpcauth_remove_credcache
c_func
(paren
id|auth
comma
id|cred
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cred-&gt;cr_count
)paren
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crdestroy
c_func
(paren
id|cred
)paren
suffix:semicolon
)brace
id|task-&gt;tk_cred
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|u32
op_star
DECL|function|rpcauth_marshcred
id|rpcauth_marshcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d marshaling %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_return
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crmarshal
c_func
(paren
id|task
comma
id|p
comma
id|task-&gt;tk_flags
op_amp
id|RPC_CALL_REALUID
)paren
suffix:semicolon
)brace
id|u32
op_star
DECL|function|rpcauth_checkverf
id|rpcauth_checkverf
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
comma
id|u32
op_star
id|p
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d validating %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_return
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crvalidate
c_func
(paren
id|task
comma
id|p
)paren
suffix:semicolon
)brace
r_int
DECL|function|rpcauth_refreshcred
id|rpcauth_refreshcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|rpc_auth
op_star
id|auth
op_assign
id|task-&gt;tk_auth
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d refreshing %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
id|task-&gt;tk_status
op_assign
id|auth-&gt;au_ops
op_member_access_from_pointer
id|crrefresh
c_func
(paren
id|task
)paren
suffix:semicolon
r_return
id|task-&gt;tk_status
suffix:semicolon
)brace
r_void
DECL|function|rpcauth_invalcred
id|rpcauth_invalcred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;RPC: %4d invalidating %s cred %p&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_auth-&gt;au_ops-&gt;au_name
comma
id|task-&gt;tk_cred
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_cred
)paren
id|task-&gt;tk_cred-&gt;cr_flags
op_and_assign
op_complement
id|RPCAUTH_CRED_UPTODATE
suffix:semicolon
)brace
r_int
DECL|function|rpcauth_uptodatecred
id|rpcauth_uptodatecred
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_return
op_logical_neg
(paren
id|task-&gt;tk_cred
)paren
op_logical_or
(paren
id|task-&gt;tk_cred-&gt;cr_flags
op_amp
id|RPCAUTH_CRED_UPTODATE
)paren
suffix:semicolon
)brace
eof