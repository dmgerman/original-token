multiline_comment|/*&n; * linux/fs/nfsd/nfsfh.c&n; *&n; * NFS server filehandle treatment.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_FH
multiline_comment|/*&n; * Perform sanity checks on the dentry in a client&squot;s file handle.&n; */
id|u32
DECL|function|fh_verify
id|fh_verify
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|svc_fh
op_star
id|fhp
comma
r_int
id|type
comma
r_int
id|access
)paren
(brace
r_struct
id|svc_export
op_star
id|exp
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_struct
id|knfs_fh
op_star
id|fh
op_assign
op_amp
id|fhp-&gt;fh_handle
suffix:semicolon
r_if
c_cond
(paren
id|fhp-&gt;fh_dverified
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_lookup(exp %x/%d fh %p)&bslash;n&quot;
comma
id|fh-&gt;fh_xdev
comma
id|fh-&gt;fh_xino
comma
id|fh-&gt;fh_dentry
)paren
suffix:semicolon
multiline_comment|/* Look up the export entry. */
id|exp
op_assign
id|exp_get
c_func
(paren
id|rqstp-&gt;rq_client
comma
id|fh-&gt;fh_xdev
comma
id|fh-&gt;fh_xino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp
)paren
(brace
multiline_comment|/* nfsdstats.fhstale++; */
r_return
id|nfserr_stale
suffix:semicolon
multiline_comment|/* export entry revoked */
)brace
multiline_comment|/* Check if the request originated from a secure port. */
r_if
c_cond
(paren
op_logical_neg
id|rqstp-&gt;rq_secure
op_logical_and
id|EX_SECURE
c_func
(paren
id|exp
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: request from insecure port (%08lx:%d)!&bslash;n&quot;
comma
id|ntohl
c_func
(paren
id|rqstp-&gt;rq_addr.sin_addr.s_addr
)paren
comma
id|ntohs
c_func
(paren
id|rqstp-&gt;rq_addr.sin_port
)paren
)paren
suffix:semicolon
r_return
id|nfserr_perm
suffix:semicolon
)brace
multiline_comment|/* Set user creds if we haven&squot;t done so already. */
id|nfsd_setuser
c_func
(paren
id|rqstp
comma
id|exp
)paren
suffix:semicolon
id|dentry
op_assign
id|fh-&gt;fh_dentry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d_validate
c_func
(paren
id|dentry
comma
id|fh-&gt;fh_dparent
comma
id|fh-&gt;fh_dhash
comma
id|fh-&gt;fh_dlen
)paren
op_logical_or
op_logical_neg
(paren
id|inode
op_assign
id|dentry-&gt;d_inode
)paren
op_logical_or
op_logical_neg
id|inode-&gt;i_nlink
)paren
(brace
multiline_comment|/* Currently we cannot tell the difference between&n;&t;&t; * a bogus pointer and a true unlink between fh&n;&t;&t; * uses.  But who cares about accurate error reporting&n;&t;&t; * to buggy/malicious clients... -DaveM&n;&t;&t; */
multiline_comment|/* nfsdstats.fhstale++; */
r_return
id|nfserr_stale
suffix:semicolon
)brace
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|fhp-&gt;fh_dverified
op_assign
l_int|1
suffix:semicolon
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
multiline_comment|/* Type check. The correct error return for type mismatches&n;&t; * does not seem to be generally agreed upon. SunOS seems to&n;&t; * use EISDIR if file isn&squot;t S_IFREG; a comment in the NFSv3&n;&t; * spec says this is incorrect (implementation notes for the&n;&t; * write call).&n;&t; */
r_if
c_cond
(paren
id|type
OG
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_ne
id|type
)paren
r_return
(paren
id|type
op_eq
id|S_IFDIR
)paren
ques
c_cond
id|nfserr_notdir
suffix:colon
id|nfserr_isdir
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_and
(paren
id|inode-&gt;i_mode
op_amp
id|S_IFMT
)paren
op_eq
op_minus
id|type
)paren
r_return
(paren
id|type
op_eq
op_minus
id|S_IFDIR
)paren
ques
c_cond
id|nfserr_notdir
suffix:colon
id|nfserr_isdir
suffix:semicolon
multiline_comment|/* Finally, check access permissions. */
r_return
id|nfsd_permission
c_func
(paren
id|fhp-&gt;fh_export
comma
id|dentry
comma
id|access
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Compose file handle for NFS reply.&n; */
r_void
DECL|function|fh_compose
id|fh_compose
c_func
(paren
r_struct
id|svc_fh
op_star
id|fhp
comma
r_struct
id|svc_export
op_star
id|exp
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;nfsd: fh_compose(exp %x/%d dentry %p)&bslash;n&quot;
comma
id|exp-&gt;ex_dev
comma
id|exp-&gt;ex_ino
comma
id|dentry
)paren
suffix:semicolon
id|fh_init
c_func
(paren
id|fhp
)paren
suffix:semicolon
multiline_comment|/* initialize empty fh */
id|fhp-&gt;fh_handle.fh_dentry
op_assign
id|dentry
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dparent
op_assign
id|dentry-&gt;d_parent
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dhash
op_assign
id|dentry-&gt;d_name.hash
suffix:semicolon
id|fhp-&gt;fh_handle.fh_dlen
op_assign
id|dentry-&gt;d_name.len
suffix:semicolon
id|fhp-&gt;fh_handle.fh_xdev
op_assign
id|exp-&gt;ex_dev
suffix:semicolon
id|fhp-&gt;fh_handle.fh_xino
op_assign
id|exp-&gt;ex_ino
suffix:semicolon
id|fhp-&gt;fh_export
op_assign
id|exp
suffix:semicolon
multiline_comment|/* We stuck it there, we know it&squot;s good. */
id|fhp-&gt;fh_dverified
op_assign
l_int|1
suffix:semicolon
)brace
eof
