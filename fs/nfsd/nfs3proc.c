multiline_comment|/*&n; * linux/fs/nfsd/nfs3proc.c&n; *&n; * Process version 3 NFS requests.&n; *&n; * Copyright (C) 1996 Olaf Kirch &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/cache.h&gt;
macro_line|#include &lt;linux/nfsd/xdr3.h&gt;
DECL|typedef|svc_rqst
r_typedef
r_struct
id|svc_rqst
id|svc_rqst
suffix:semicolon
DECL|typedef|svc_buf
r_typedef
r_struct
id|svc_buf
id|svc_buf
suffix:semicolon
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;&t;NFSDDBG_PROC
DECL|macro|RETURN
mdefine_line|#define RETURN(st)&t;{ resp-&gt;status = (st); return (st); }
r_static
r_void
DECL|function|svcbuf_reserve
id|svcbuf_reserve
c_func
(paren
r_struct
id|svc_buf
op_star
id|buf
comma
id|u32
op_star
op_star
id|ptr
comma
r_int
op_star
id|len
comma
r_int
id|nr
)paren
(brace
op_star
id|ptr
op_assign
id|buf-&gt;buf
op_plus
id|nr
suffix:semicolon
op_star
id|len
op_assign
id|buf-&gt;buflen
op_minus
id|buf-&gt;len
op_minus
id|nr
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_null
id|nfsd3_proc_null
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_void
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_return
id|nfs_ok
suffix:semicolon
)brace
multiline_comment|/*&n; * Get a file&squot;s attributes&n; */
r_static
r_int
DECL|function|nfsd3_proc_getattr
id|nfsd3_proc_getattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: GETATTR  %x/%ld&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|resp-&gt;fh
op_assign
id|argp-&gt;fh
suffix:semicolon
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
l_int|0
comma
id|MAY_NOP
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set a file&squot;s attributes&n; */
r_static
r_int
DECL|function|nfsd3_proc_setattr
id|nfsd3_proc_setattr
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_sattrargs
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SETATTR  %x/%ld&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|resp-&gt;fh
op_assign
id|argp-&gt;fh
suffix:semicolon
id|nfserr
op_assign
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;attrs
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Look up a path name component&n; */
r_static
r_int
DECL|function|nfsd3_proc_lookup
id|nfsd3_proc_lookup
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_struct
id|nfsd3_lookupres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LOOKUP   %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|resp-&gt;dirfh
op_assign
id|argp-&gt;fh
suffix:semicolon
id|nfserr
op_assign
id|nfsd_lookup
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;dirfh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check file access&n; */
r_static
r_int
DECL|function|nfsd3_proc_access
id|nfsd3_proc_access
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_accessres
op_star
id|resp
)paren
(brace
multiline_comment|/* to be done */
id|resp-&gt;fh
op_assign
id|argp-&gt;fh
suffix:semicolon
r_return
id|nfserr_notsupp
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a symlink.&n; */
r_static
r_int
DECL|function|nfsd3_proc_readlink
id|nfsd3_proc_readlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_readlinkres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|path
suffix:semicolon
r_int
id|dummy
comma
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READLINK %x/%ld&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
multiline_comment|/* Reserve room for status, post_op_attr, and path length */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_resbuf
comma
op_amp
id|path
comma
op_amp
id|dummy
comma
l_int|1
op_plus
l_int|22
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Read the symlink. */
id|resp-&gt;len
op_assign
id|NFS3_MAXPATHLEN
suffix:semicolon
id|nfserr
op_assign
id|nfsd_readlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
(paren
r_char
op_star
)paren
id|path
comma
op_amp
id|resp-&gt;len
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a file.&n; */
r_static
r_int
DECL|function|nfsd3_proc_read
id|nfsd3_proc_read
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_readargs
op_star
id|argp
comma
r_struct
id|nfsd3_readres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|buffer
suffix:semicolon
r_int
id|nfserr
comma
id|avail
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READ %x/%ld %lu bytes at %lu&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
(paren
r_int
r_int
)paren
id|argp-&gt;count
comma
(paren
r_int
r_int
)paren
id|argp-&gt;offset
)paren
suffix:semicolon
multiline_comment|/* Obtain buffer pointer for payload.&n;&t; * 1 (status) + 22 (post_op_attr) + 1 (count) + 1 (eof)&n;&t; * + 1 (xdr opaque byte count) = 26&n;&t; */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_resbuf
comma
op_amp
id|buffer
comma
op_amp
id|avail
comma
l_int|26
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|avail
op_lshift
l_int|2
)paren
OL
id|argp-&gt;count
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;oversized read request from %08lx:%d (%d bytes)&bslash;n&quot;
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
comma
id|argp-&gt;count
)paren
suffix:semicolon
id|argp-&gt;count
op_assign
id|avail
suffix:semicolon
)brace
id|resp-&gt;count
op_assign
id|argp-&gt;count
suffix:semicolon
id|resp-&gt;fh
op_assign
id|argp-&gt;fh
suffix:semicolon
id|nfserr
op_assign
id|nfsd_read
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|argp-&gt;offset
comma
(paren
r_char
op_star
)paren
id|buffer
comma
op_amp
id|resp-&gt;count
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Write data to a file&n; */
r_static
r_int
DECL|function|nfsd3_proc_write
id|nfsd3_proc_write
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_writeargs
op_star
id|argp
comma
r_struct
id|nfsd3_writeres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: WRITE    %x/%ld %d bytes at %ld&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;len
comma
(paren
r_int
r_int
)paren
id|argp-&gt;offset
)paren
suffix:semicolon
id|resp-&gt;fh
op_assign
id|argp-&gt;fh
suffix:semicolon
id|nfserr
op_assign
id|nfsd_write
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
id|argp-&gt;offset
comma
id|argp-&gt;data
comma
id|argp-&gt;len
comma
id|argp-&gt;stable
)paren
suffix:semicolon
id|resp-&gt;committed
op_assign
id|argp-&gt;stable
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * With NFSv3, CREATE processing is a lot easier than with NFSv2.&n; * At least in theory; we&squot;ll see how it fares in practice when the&n; * first reports about SunOS compatibility problems start to pour in...&n; */
r_static
r_int
DECL|function|nfsd3_proc_create
id|nfsd3_proc_create
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_createargs
op_star
id|argp
comma
r_struct
id|nfsd3_createres
op_star
id|resp
)paren
(brace
id|svc_fh
op_star
id|dirfhp
comma
op_star
id|newfhp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|iattr
op_star
id|attr
suffix:semicolon
r_int
id|mode
suffix:semicolon
id|u32
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: CREATE   %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|dirfhp
op_assign
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;dirfh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|newfhp
op_assign
id|fh_init
c_func
(paren
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|attr
op_assign
op_amp
id|argp-&gt;attrs
suffix:semicolon
multiline_comment|/* Get the directory inode */
id|nfserr
op_assign
id|fh_verify
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|S_IFDIR
comma
id|MAY_CREATE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
)paren
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
multiline_comment|/* Unfudge the mode bits */
id|attr-&gt;ia_mode
op_and_assign
op_complement
id|S_IFMT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
)paren
(brace
id|attr-&gt;ia_valid
op_or_assign
id|ATTR_MODE
suffix:semicolon
id|attr-&gt;ia_mode
op_assign
id|S_IFREG
suffix:semicolon
)brace
id|mode
op_assign
id|attr-&gt;ia_mode
op_amp
op_complement
id|S_IFMT
suffix:semicolon
multiline_comment|/* Now create the file and set attributes */
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
id|dirfhp
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
id|attr
comma
id|S_IFREG
comma
l_int|0
comma
id|newfhp
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_remove
id|nfsd3_proc_remove
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_struct
id|nfsd3_attrstat
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: REMOVE   %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|fh_copy
c_func
(paren
op_amp
id|resp-&gt;fh
comma
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
multiline_comment|/* Unlink. -S_IFDIR means file must not be a directory */
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|resp-&gt;fh
comma
op_minus
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_rename
id|nfsd3_proc_rename
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_renameargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RENAME   %x/%ld %s -&gt; %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;fname
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_rename
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;ffh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
op_amp
id|argp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_link
id|nfsd3_proc_link
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_linkargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: LINK     %x/%ld -&gt; %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_link
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;tfh
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;tfh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfsd3_proc_symlink
id|nfsd3_proc_symlink
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_symlinkargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_struct
id|svc_fh
id|newfh
suffix:semicolon
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: SYMLINK  %x/%ld %s -&gt; %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
comma
id|argp-&gt;fname
comma
id|argp-&gt;tname
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|newfh
comma
l_int|0
comma
r_sizeof
(paren
id|newfh
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Create the link, look up new file and set attrs.&n;&t; */
id|nfserr
op_assign
id|nfsd_symlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;ffh
comma
id|argp-&gt;fname
comma
id|argp-&gt;flen
comma
id|argp-&gt;tname
comma
id|argp-&gt;tlen
comma
op_amp
id|newfh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfserr
)paren
id|nfserr
op_assign
id|nfsd_setattr
c_func
(paren
id|rqstp
comma
op_amp
id|newfh
comma
op_amp
id|argp-&gt;attrs
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;ffh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|newfh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Make directory. This operation is not idempotent.&n; */
r_static
r_int
DECL|function|nfsd3_proc_mkdir
id|nfsd3_proc_mkdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_createargs
op_star
id|argp
comma
r_struct
id|nfsd3_diropres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: MKDIR    %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_create
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|argp-&gt;name
comma
id|argp-&gt;len
comma
op_amp
id|argp-&gt;attrs
comma
id|S_IFDIR
comma
l_int|0
comma
op_amp
id|resp-&gt;fh
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove a directory&n; */
r_static
r_int
DECL|function|nfsd3_proc_rmdir
id|nfsd3_proc_rmdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_diropargs
op_star
id|argp
comma
r_void
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: RMDIR    %x/%ld %s&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;name
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_unlink
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
id|S_IFDIR
comma
id|argp-&gt;name
comma
id|argp-&gt;len
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a portion of a directory.&n; */
r_static
r_int
DECL|function|nfsd3_proc_readdir
id|nfsd3_proc_readdir
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd3_readdirargs
op_star
id|argp
comma
r_struct
id|nfsd3_readdirres
op_star
id|resp
)paren
(brace
id|u32
op_star
id|buffer
suffix:semicolon
r_int
id|nfserr
comma
id|count
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: READDIR  %x/%ld %d bytes at %d&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|argp-&gt;count
comma
id|argp-&gt;cookie
)paren
suffix:semicolon
multiline_comment|/* Reserve buffer space for status */
id|svcbuf_reserve
c_func
(paren
op_amp
id|rqstp-&gt;rq_resbuf
comma
op_amp
id|buffer
comma
op_amp
id|count
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Make sure we&squot;ve room for the NULL ptr &amp; eof flag, and shrink to&n;&t; * client read size */
r_if
c_cond
(paren
(paren
id|count
op_sub_assign
l_int|8
)paren
OG
id|argp-&gt;count
)paren
id|count
op_assign
id|argp-&gt;count
suffix:semicolon
multiline_comment|/* Read directory and encode entries on the fly */
id|nfserr
op_assign
id|nfsd_readdir
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
(paren
id|loff_t
)paren
id|argp-&gt;cookie
comma
id|nfssvc_encode_entry
comma
id|buffer
comma
op_amp
id|count
)paren
suffix:semicolon
id|resp-&gt;count
op_assign
id|count
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Get file system info&n; */
r_static
r_int
DECL|function|nfsd3_proc_statfs
id|nfsd3_proc_statfs
c_func
(paren
r_struct
id|svc_rqst
op_star
id|rqstp
comma
r_struct
id|nfsd_fhandle
op_star
id|argp
comma
r_struct
id|nfsd3_statfsres
op_star
id|resp
)paren
(brace
r_int
id|nfserr
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: STATFS   %x/%ld&bslash;n&quot;
comma
id|SVCFH_DEV
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
comma
id|SVCFH_INO
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
)paren
suffix:semicolon
id|nfserr
op_assign
id|nfsd_statfs
c_func
(paren
id|rqstp
comma
op_amp
id|argp-&gt;fh
comma
op_amp
id|resp-&gt;stats
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|argp-&gt;fh
)paren
suffix:semicolon
id|RETURN
c_func
(paren
id|nfserr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * NFSv2 Server procedures.&n; * Only the results of non-idempotent operations are cached.&n; */
DECL|macro|nfsd3_proc_none
mdefine_line|#define nfsd3_proc_none&t;&t;NULL
DECL|macro|nfssvc_encode_void
mdefine_line|#define nfssvc_encode_void&t;NULL
DECL|macro|nfssvc_decode_void
mdefine_line|#define nfssvc_decode_void&t;NULL
DECL|macro|nfssvc_release_void
mdefine_line|#define nfssvc_release_void&t;NULL
DECL|struct|nfsd3_void
DECL|member|dummy
r_struct
id|nfsd3_void
(brace
r_int
id|dummy
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|PROC
mdefine_line|#define PROC(name, argt, rest, relt, cache)&t;&bslash;&n; { (svc_procfunc) nfsd3_proc_##name,&t;&bslash;&n;   (kxdrproc_t) nfssvc_decode_##argt,&t;&bslash;&n;   (kxdrproc_t) nfssvc_encode_##rest,&t;&bslash;&n;   (kxdrproc_t) nfssvc_release_##relt,&t;&bslash;&n;   sizeof(struct nfsd3_##argt),&t;&t;&bslash;&n;   sizeof(struct nfsd3_##rest),&t;&t;&bslash;&n;   0,&t;&t;&t;&t;&t;&bslash;&n;   cache&t;&t;&t;&t;&bslash;&n; }
DECL|variable|nfsd3_procedures2
r_struct
id|svc_procedure
id|nfsd3_procedures2
(braket
l_int|18
)braket
op_assign
(brace
id|PROC
c_func
(paren
id|null
comma
r_void
comma
r_void
comma
r_void
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|getattr
comma
id|fhandle
comma
id|attrstat
comma
id|fhandle
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|setattr
comma
id|sattrargs
comma
id|attrstat
comma
id|fhandle
comma
id|RC_REPLBUFF
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
r_void
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|lookup
comma
id|diropargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|readlink
comma
id|fhandle
comma
id|readlinkres
comma
r_void
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|read
comma
id|readargs
comma
id|readres
comma
id|fhandle
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|none
comma
r_void
comma
r_void
comma
r_void
comma
id|RC_NOCACHE
)paren
comma
id|PROC
c_func
(paren
id|write
comma
id|writeargs
comma
id|attrstat
comma
id|fhandle
comma
id|RC_REPLBUFF
)paren
comma
id|PROC
c_func
(paren
id|create
comma
id|createargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_REPLBUFF
)paren
comma
id|PROC
c_func
(paren
id|remove
comma
id|diropargs
comma
r_void
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|rename
comma
id|renameargs
comma
r_void
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|link
comma
id|linkargs
comma
r_void
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|symlink
comma
id|symlinkargs
comma
r_void
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|mkdir
comma
id|createargs
comma
id|diropres
comma
id|fhandle
comma
id|RC_REPLBUFF
)paren
comma
id|PROC
c_func
(paren
id|rmdir
comma
id|diropargs
comma
r_void
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|readdir
comma
id|readdirargs
comma
id|readdirres
comma
r_void
comma
id|RC_REPLSTAT
)paren
comma
id|PROC
c_func
(paren
id|statfs
comma
id|fhandle
comma
id|statfsres
comma
r_void
comma
id|RC_NOCACHE
)paren
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Map errnos to NFS errnos.&n; */
r_int
DECL|function|nfserrno
id|nfserrno
(paren
r_int
id|errno
)paren
(brace
r_static
r_struct
(brace
r_int
id|nfserr
suffix:semicolon
r_int
id|syserr
suffix:semicolon
)brace
id|nfs_errtbl
(braket
)braket
op_assign
(brace
(brace
id|NFS_OK
comma
l_int|0
)brace
comma
(brace
id|NFSERR_PERM
comma
id|EPERM
)brace
comma
(brace
id|NFSERR_NOENT
comma
id|ENOENT
)brace
comma
(brace
id|NFSERR_IO
comma
id|EIO
)brace
comma
(brace
id|NFSERR_NXIO
comma
id|ENXIO
)brace
comma
(brace
id|NFSERR_ACCES
comma
id|EACCES
)brace
comma
(brace
id|NFSERR_EXIST
comma
id|EEXIST
)brace
comma
(brace
id|NFSERR_NODEV
comma
id|ENODEV
)brace
comma
(brace
id|NFSERR_NOTDIR
comma
id|ENOTDIR
)brace
comma
(brace
id|NFSERR_ISDIR
comma
id|EISDIR
)brace
comma
(brace
id|NFSERR_INVAL
comma
id|EINVAL
)brace
comma
(brace
id|NFSERR_FBIG
comma
id|EFBIG
)brace
comma
(brace
id|NFSERR_NOSPC
comma
id|ENOSPC
)brace
comma
(brace
id|NFSERR_ROFS
comma
id|EROFS
)brace
comma
(brace
id|NFSERR_NAMETOOLONG
comma
id|ENAMETOOLONG
)brace
comma
(brace
id|NFSERR_NOTEMPTY
comma
id|ENOTEMPTY
)brace
comma
macro_line|#ifdef EDQUOT
(brace
id|NFSERR_DQUOT
comma
id|EDQUOT
)brace
comma
macro_line|#endif
(brace
id|NFSERR_STALE
comma
id|ESTALE
)brace
comma
(brace
id|NFSERR_WFLUSH
comma
id|EIO
)brace
comma
(brace
op_minus
l_int|1
comma
id|EIO
)brace
)brace
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|nfs_errtbl
(braket
id|i
)braket
dot
id|nfserr
op_ne
op_minus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|nfs_errtbl
(braket
id|i
)braket
dot
id|syserr
op_eq
id|errno
)paren
r_return
id|htonl
(paren
id|nfs_errtbl
(braket
id|i
)braket
dot
id|nfserr
)paren
suffix:semicolon
)brace
id|printk
(paren
id|KERN_INFO
l_string|&quot;nfsd: non-standard errno: %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
id|nfserr_io
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_void
id|nfsd3_dump
c_func
(paren
r_char
op_star
id|tag
comma
id|u32
op_star
id|buf
comma
r_int
id|len
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;nfsd: %s (%d words)&bslash;n&quot;
comma
id|tag
comma
id|len
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
id|len
op_logical_and
id|i
OL
l_int|32
suffix:semicolon
id|i
op_add_assign
l_int|8
)paren
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot; %08lx %08lx %08lx %08lx&quot;
l_string|&quot; %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|buf
(braket
id|i
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|1
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|2
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|3
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|4
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|5
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|6
)braket
comma
id|buf
(braket
id|i
op_plus
l_int|7
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
