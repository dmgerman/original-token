multiline_comment|/*&n; *  linux/fs/nfs/proc.c&n; *&n; *  Copyright (C) 1992, 1993, 1994  Rick Sladkey&n; *&n; *  OS-independent nfs remote procedure call functions&n; *&n; *  Tuned by Alan Cox &lt;A.Cox@swansea.ac.uk&gt; for &gt;3K buffers&n; *  so at last we can have decent(ish) throughput off a &n; *  Sun server.&n; *&n; *  Coding optimized and cleaned up by Florian La Roche.&n; *  Note: Error returns are optimized for NFS_OK, which isn&squot;t translated via&n; *  nfs_stat_to_errno(), but happens to be already the right return code.&n; *&n; *  FixMe: We ought to define a sensible small max size for&n; *  things like getattr that are tiny packets and use the&n; *  old get_free_page stuff with it.&n; *&n; *  Also, the code currently doesn&squot;t check the size of the packet, when&n; *  it decodes the packet.&n; *&n; *  Feel free to fix it and mail me the diffs if it worries you.&n; *&n; *  Completely rewritten to support the new RPC call interface;&n; *  rewrote and moved the entire XDR stuff to xdr.c&n; *  --Olaf Kirch June 1996&n; */
DECL|macro|NFS_NEED_XDR_TYPES
mdefine_line|#define NFS_NEED_XDR_TYPES
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#ifdef NFS_DEBUG
DECL|macro|NFSDBG_FACILITY
macro_line|# define NFSDBG_FACILITY&t;NFSDBG_PROC
macro_line|#endif
multiline_comment|/*&n; * One function for each procedure in the NFS protocol.&n; */
r_int
DECL|function|nfs_proc_getattr
id|nfs_proc_getattr
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  getattr&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_GETATTR
comma
id|fhandle
comma
id|fattr
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply getattr&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_setattr
id|nfs_proc_setattr
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_sattrargs
id|arg
op_assign
(brace
id|fhandle
comma
id|sattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  setattr&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_SETATTR
comma
op_amp
id|arg
comma
id|fattr
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply setattr&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_lookup
id|nfs_proc_lookup
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
id|dir
comma
id|name
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
id|fhandle
comma
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  lookup %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_LOOKUP
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply lookup: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_readlink
id|nfs_proc_readlink
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_void
op_star
op_star
id|p0
comma
r_char
op_star
op_star
id|string
comma
r_int
r_int
op_star
id|len
comma
r_int
r_int
id|maxlen
)paren
(brace
r_struct
id|nfs_readlinkres
id|res
op_assign
(brace
id|string
comma
id|len
comma
id|maxlen
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  readlink&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_READLINK
comma
id|fhandle
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply readlink: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
op_star
id|p0
op_assign
id|res.buffer
suffix:semicolon
r_else
r_if
c_cond
(paren
id|res.buffer
)paren
id|kfree
c_func
(paren
id|res.buffer
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_read
id|nfs_proc_read
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_int
id|swap
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
comma
r_void
op_star
id|buffer
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_readargs
id|arg
op_assign
(brace
id|fhandle
comma
id|offset
comma
id|count
comma
id|buffer
)brace
suffix:semicolon
r_struct
id|nfs_readres
id|res
op_assign
(brace
id|fattr
comma
id|count
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  read %d @ %ld&bslash;n&quot;
comma
id|count
comma
id|offset
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_READ
comma
op_amp
id|arg
comma
op_amp
id|res
comma
id|swap
ques
c_cond
id|NFS_RPC_SWAPFLAGS
suffix:colon
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply read: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_write
id|nfs_proc_write
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_int
id|swap
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|count
comma
r_const
r_void
op_star
id|buffer
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_writeargs
id|arg
op_assign
(brace
id|fhandle
comma
id|offset
comma
id|count
comma
id|buffer
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  write %d @ %ld&bslash;n&quot;
comma
id|count
comma
id|offset
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_WRITE
comma
op_amp
id|arg
comma
id|fattr
comma
id|swap
ques
c_cond
(paren
id|RPC_TASK_SWAPPER
op_or
id|RPC_TASK_ROOTCREDS
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply read: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
OL
l_int|0
ques
c_cond
id|status
suffix:colon
id|count
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_create
id|nfs_proc_create
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_createargs
id|arg
op_assign
(brace
id|dir
comma
id|name
comma
id|sattr
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
id|fhandle
comma
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  create %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_CREATE
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply create: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_remove
id|nfs_proc_remove
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
id|dir
comma
id|name
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  remove %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_REMOVE
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply remove: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_rename
id|nfs_proc_rename
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|old_dir
comma
r_const
r_char
op_star
id|old_name
comma
r_struct
id|nfs_fh
op_star
id|new_dir
comma
r_const
r_char
op_star
id|new_name
)paren
(brace
r_struct
id|nfs_renameargs
id|arg
op_assign
(brace
id|old_dir
comma
id|old_name
comma
id|new_dir
comma
id|new_name
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  rename %s -&gt; %s&bslash;n&quot;
comma
id|old_name
comma
id|new_name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_RENAME
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply rename: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_link
id|nfs_proc_link
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|nfs_linkargs
id|arg
op_assign
(brace
id|fhandle
comma
id|dir
comma
id|name
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  link %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_LINK
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply link: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_symlink
id|nfs_proc_symlink
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_const
r_char
op_star
id|path
comma
r_struct
id|nfs_sattr
op_star
id|sattr
)paren
(brace
r_struct
id|nfs_symlinkargs
id|arg
op_assign
(brace
id|dir
comma
id|name
comma
id|path
comma
id|sattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  symlink %s -&gt; %s&bslash;n&quot;
comma
id|name
comma
id|path
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_SYMLINK
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply symlink: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_mkdir
id|nfs_proc_mkdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|nfs_sattr
op_star
id|sattr
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fattr
op_star
id|fattr
)paren
(brace
r_struct
id|nfs_createargs
id|arg
op_assign
(brace
id|dir
comma
id|name
comma
id|sattr
)brace
suffix:semicolon
r_struct
id|nfs_diropok
id|res
op_assign
(brace
id|fhandle
comma
id|fattr
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  mkdir %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_MKDIR
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply mkdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_rmdir
id|nfs_proc_rmdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|dir
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|nfs_diropargs
id|arg
op_assign
(brace
id|dir
comma
id|name
)brace
suffix:semicolon
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  rmdir %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_RMDIR
comma
op_amp
id|arg
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply rmdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * The READDIR implementation is somewhat hackish - we pass a temporary&n; * buffer to the encode function, which installs it in the receive&n; * iovec. The dirent buffer itself is passed in the result struct.&n; */
r_int
DECL|function|nfs_proc_readdir
id|nfs_proc_readdir
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
id|u32
id|cookie
comma
r_int
r_int
id|size
comma
id|__u32
op_star
id|entry
)paren
(brace
r_struct
id|nfs_readdirargs
id|arg
suffix:semicolon
r_struct
id|nfs_readdirres
id|res
suffix:semicolon
r_void
op_star
id|buffer
suffix:semicolon
r_int
r_int
id|buf_size
op_assign
id|PAGE_SIZE
suffix:semicolon
r_int
id|status
suffix:semicolon
multiline_comment|/* First get a temp buffer for the readdir reply */
multiline_comment|/* N.B. does this really need to be cleared? */
id|status
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|buffer
op_assign
(paren
r_void
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the effective size the buffer.  To make sure&n;&t; * that the returned data will fit into the user&squot;s buffer,&n;&t; * we decrease the buffer size as necessary.&n;&t; *&n;&t; * Note: NFS returns three __u32 values for each entry,&n;&t; * and we assume that the data is packed into the user&n;&t; * buffer with the same efficiency. &n;&t; */
r_if
c_cond
(paren
id|size
OL
id|buf_size
)paren
id|buf_size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;rsize
OL
id|buf_size
)paren
id|buf_size
op_assign
id|server-&gt;rsize
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;nfs_proc_readdir: user size=%d, rsize=%d, buf_size=%d&bslash;n&quot;
comma
id|size
comma
id|server-&gt;rsize
comma
id|buf_size
)paren
suffix:semicolon
macro_line|#endif
id|arg.fh
op_assign
id|fhandle
suffix:semicolon
id|arg.cookie
op_assign
id|cookie
suffix:semicolon
id|arg.buffer
op_assign
id|buffer
suffix:semicolon
id|arg.bufsiz
op_assign
id|buf_size
suffix:semicolon
id|res.buffer
op_assign
id|entry
suffix:semicolon
id|res.bufsiz
op_assign
id|size
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  readdir %d&bslash;n&quot;
comma
id|cookie
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_READDIR
comma
op_amp
id|arg
comma
op_amp
id|res
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply readdir: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|buffer
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|status
suffix:semicolon
)brace
r_int
DECL|function|nfs_proc_statfs
id|nfs_proc_statfs
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|nfs_fh
op_star
id|fhandle
comma
r_struct
id|nfs_fsinfo
op_star
id|info
)paren
(brace
r_int
id|status
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS call  statfs&bslash;n&quot;
)paren
suffix:semicolon
id|status
op_assign
id|rpc_call
c_func
(paren
id|server-&gt;client
comma
id|NFSPROC_STATFS
comma
id|fhandle
comma
id|info
comma
l_int|0
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS reply statfs: %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
eof
