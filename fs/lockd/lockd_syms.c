multiline_comment|/*&n; * linux/fs/lockd/lockd_syms.c&n; *&n; * Symbols exported by the lockd module.&n; *&n; * Authors:&t;Olaf Kirch (okir@monad.swb.de)&n; *&n; * Copyright (C) 1997 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#ifdef CONFIG_MODULES
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/uio.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/lockd/lockd.h&gt;
multiline_comment|/* Start/stop the daemon */
DECL|variable|lockd_up
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_up
)paren
suffix:semicolon
DECL|variable|lockd_down
id|EXPORT_SYMBOL
c_func
(paren
id|lockd_down
)paren
suffix:semicolon
multiline_comment|/* NFS client entry */
DECL|variable|nlmclnt_proc
id|EXPORT_SYMBOL
c_func
(paren
id|nlmclnt_proc
)paren
suffix:semicolon
multiline_comment|/* NFS server entry points/hooks */
DECL|variable|nlmsvc_invalidate_client
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_invalidate_client
)paren
suffix:semicolon
DECL|variable|nlmsvc_ops
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_ops
)paren
suffix:semicolon
multiline_comment|/* Configuration at insmod time */
DECL|variable|nlmsvc_grace_period
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_grace_period
)paren
suffix:semicolon
DECL|variable|nlmsvc_timeout
id|EXPORT_SYMBOL
c_func
(paren
id|nlmsvc_timeout
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_LOCKD_V4
multiline_comment|/* NLM4 exported symbols */
DECL|variable|nlm4_rofs
id|EXPORT_SYMBOL
c_func
(paren
id|nlm4_rofs
)paren
suffix:semicolon
DECL|variable|nlm4_stale_fh
id|EXPORT_SYMBOL
c_func
(paren
id|nlm4_stale_fh
)paren
suffix:semicolon
DECL|variable|nlm4_deadlock
id|EXPORT_SYMBOL
c_func
(paren
id|nlm4_deadlock
)paren
suffix:semicolon
DECL|variable|nlm4_failed
id|EXPORT_SYMBOL
c_func
(paren
id|nlm4_failed
)paren
suffix:semicolon
DECL|variable|nlm4_fbig
id|EXPORT_SYMBOL
c_func
(paren
id|nlm4_fbig
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* CONFIG_MODULES */
eof
