multiline_comment|/*&n; * linux/fs/nfs/read.c&n; *&n; * Block I/O for NFS&n; *&n; * Partial copy of Linus&squot; read cache modifications to fs/nfs/file.c&n; * modified for async RPC by okir@monad.swb.de&n; *&n; * We do an ugly hack here in order to return proper error codes to the&n; * user program when a read request failed: since generic_file_read&n; * only checks the return value of inode-&gt;i_op-&gt;readpage() which is always 0&n; * for async RPC, we set the error bit of the page to 1 when an error occurs,&n; * and make nfs_readpage transmit requests synchronously when encountering this.&n; * This is only a small problem, though, since we now retry all operations&n; * within the RPC code when root squashing is suspected.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_PAGECACHE
DECL|struct|nfs_rreq
r_struct
id|nfs_rreq
(brace
DECL|member|ra_inode
r_struct
id|inode
op_star
id|ra_inode
suffix:semicolon
multiline_comment|/* inode from which to read */
DECL|member|ra_page
r_struct
id|page
op_star
id|ra_page
suffix:semicolon
multiline_comment|/* page to be read */
DECL|member|ra_args
r_struct
id|nfs_readargs
id|ra_args
suffix:semicolon
multiline_comment|/* XDR argument struct */
DECL|member|ra_res
r_struct
id|nfs_readres
id|ra_res
suffix:semicolon
multiline_comment|/* ... and result struct */
DECL|member|ra_fattr
r_struct
id|nfs_fattr
id|ra_fattr
suffix:semicolon
multiline_comment|/* fattr storage */
)brace
suffix:semicolon
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
multiline_comment|/*&n; * Set up the NFS read request struct&n; */
r_static
r_inline
r_void
DECL|function|nfs_readreq_setup
id|nfs_readreq_setup
c_func
(paren
r_struct
id|nfs_rreq
op_star
id|req
comma
r_struct
id|nfs_fh
op_star
id|fh
comma
id|loff_t
id|offset
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|rsize
)paren
(brace
id|req-&gt;ra_args.fh
op_assign
id|fh
suffix:semicolon
id|req-&gt;ra_args.offset
op_assign
id|offset
suffix:semicolon
id|req-&gt;ra_args.count
op_assign
id|rsize
suffix:semicolon
id|req-&gt;ra_args.iov
(braket
l_int|0
)braket
dot
id|iov_base
op_assign
(paren
r_void
op_star
)paren
id|buffer
suffix:semicolon
id|req-&gt;ra_args.iov
(braket
l_int|0
)braket
dot
id|iov_len
op_assign
id|rsize
suffix:semicolon
id|req-&gt;ra_args.nriov
op_assign
l_int|1
suffix:semicolon
id|req-&gt;ra_fattr.valid
op_assign
l_int|0
suffix:semicolon
id|req-&gt;ra_res.fattr
op_assign
op_amp
id|req-&gt;ra_fattr
suffix:semicolon
id|req-&gt;ra_res.count
op_assign
id|rsize
suffix:semicolon
id|req-&gt;ra_res.eof
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page synchronously.&n; */
r_static
r_int
DECL|function|nfs_readpage_sync
id|nfs_readpage_sync
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|nfs_rreq
id|rqst
suffix:semicolon
r_struct
id|rpc_message
id|msg
suffix:semicolon
id|loff_t
id|offset
op_assign
id|page_offset
c_func
(paren
id|page
)paren
suffix:semicolon
r_char
op_star
id|buffer
suffix:semicolon
r_int
id|rsize
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
suffix:semicolon
r_int
id|result
comma
id|refresh
op_assign
l_int|0
suffix:semicolon
r_int
id|count
op_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
r_int
id|flags
op_assign
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
ques
c_cond
id|NFS_RPC_SWAPFLAGS
suffix:colon
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage_sync(%p)&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This works now because the socket layer never tries to DMA&n;&t; * into this buffer directly.&n;&t; */
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|count
OL
id|rsize
)paren
id|rsize
op_assign
id|count
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_proc_read(%s, (%s/%s), %Ld, %d, %p)&bslash;n&quot;
comma
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|hostname
comma
id|dentry-&gt;d_parent-&gt;d_name.name
comma
id|dentry-&gt;d_name.name
comma
(paren
r_int
r_int
)paren
id|offset
comma
id|rsize
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Set up arguments and perform rpc call */
id|nfs_readreq_setup
c_func
(paren
op_amp
id|rqst
comma
id|NFS_FH
c_func
(paren
id|dentry
)paren
comma
id|offset
comma
id|buffer
comma
id|rsize
)paren
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|msg.rpc_proc
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
id|NFS3PROC_READ
suffix:colon
id|NFSPROC_READ
suffix:semicolon
id|msg.rpc_argp
op_assign
op_amp
id|rqst.ra_args
suffix:semicolon
id|msg.rpc_resp
op_assign
op_amp
id|rqst.ra_res
suffix:semicolon
id|msg.rpc_cred
op_assign
l_int|NULL
suffix:semicolon
id|result
op_assign
id|rpc_call_sync
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
op_amp
id|msg
comma
id|flags
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|rqst.ra_fattr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Even if we had a partial success we can&squot;t mark the page&n;&t;&t; * cache valid.&n;&t;&t; */
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|result
op_eq
op_minus
id|EISDIR
)paren
id|result
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|io_error
suffix:semicolon
)brace
id|refresh
op_assign
l_int|1
suffix:semicolon
id|count
op_sub_assign
id|result
suffix:semicolon
id|offset
op_add_assign
id|result
suffix:semicolon
id|buffer
op_add_assign
id|result
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|rsize
)paren
multiline_comment|/* NFSv2ism */
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
id|count
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|io_error
suffix:colon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the callback from RPC telling us whether a reply was&n; * received or some error occurred (timeout or socket shutdown).&n; */
r_static
r_void
DECL|function|nfs_readpage_result
id|nfs_readpage_result
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs_rreq
op_star
id|req
op_assign
(paren
r_struct
id|nfs_rreq
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|req-&gt;ra_page
suffix:semicolon
r_char
op_star
id|address
op_assign
id|req-&gt;ra_args.iov
(braket
l_int|0
)braket
dot
id|iov_base
suffix:semicolon
r_int
id|result
op_assign
id|task-&gt;tk_status
suffix:semicolon
r_static
r_int
id|succ
op_assign
l_int|0
comma
id|fail
op_assign
l_int|0
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: %4d received callback for page %p, result %d&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|address
comma
id|result
)paren
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|req-&gt;ra_inode
comma
op_amp
id|req-&gt;ra_fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
op_ge
l_int|0
)paren
(brace
id|result
op_assign
id|req-&gt;ra_res.count
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
id|PAGE_CACHE_SIZE
)paren
id|memset
c_func
(paren
id|address
op_plus
id|result
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
op_minus
id|result
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|succ
op_increment
suffix:semicolon
)brace
r_else
(brace
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|fail
op_increment
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: %d successful reads, %d failures&bslash;n&quot;
comma
id|succ
comma
id|fail
)paren
suffix:semicolon
)brace
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfs_readpage_async
id|nfs_readpage_async
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|rpc_message
id|msg
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
r_struct
id|nfs_rreq
op_star
id|req
suffix:semicolon
r_int
id|result
op_assign
op_minus
l_int|1
comma
id|flags
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage_async(%p)&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|NFS_CONGESTED
c_func
(paren
id|inode
)paren
)paren
r_goto
id|out_defer
suffix:semicolon
multiline_comment|/* N.B. Do we need to test? Never called for swapfile inode */
id|flags
op_assign
id|RPC_TASK_ASYNC
op_or
(paren
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
ques
c_cond
id|NFS_RPC_SWAPFLAGS
suffix:colon
l_int|0
)paren
suffix:semicolon
id|req
op_assign
(paren
r_struct
id|nfs_rreq
op_star
)paren
id|rpc_allocate
c_func
(paren
id|flags
comma
r_sizeof
(paren
op_star
id|req
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|req
)paren
r_goto
id|out_defer
suffix:semicolon
id|address
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/* Initialize request */
multiline_comment|/* N.B. Will the dentry remain valid for life of request? */
id|nfs_readreq_setup
c_func
(paren
id|req
comma
id|NFS_FH
c_func
(paren
id|dentry
)paren
comma
id|page_offset
c_func
(paren
id|page
)paren
comma
(paren
r_void
op_star
)paren
id|address
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
id|req-&gt;ra_inode
op_assign
id|inode
suffix:semicolon
id|req-&gt;ra_page
op_assign
id|page
suffix:semicolon
multiline_comment|/* count has been incremented by caller */
multiline_comment|/* Start the async call */
id|dprintk
c_func
(paren
l_string|&quot;NFS: executing async READ request.&bslash;n&quot;
)paren
suffix:semicolon
id|msg.rpc_proc
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
id|NFS3PROC_READ
suffix:colon
id|NFSPROC_READ
suffix:semicolon
id|msg.rpc_argp
op_assign
op_amp
id|req-&gt;ra_args
suffix:semicolon
id|msg.rpc_resp
op_assign
op_amp
id|req-&gt;ra_res
suffix:semicolon
id|msg.rpc_cred
op_assign
l_int|NULL
suffix:semicolon
id|result
op_assign
id|rpc_call_async
c_func
(paren
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
comma
op_amp
id|msg
comma
id|flags
comma
id|nfs_readpage_result
comma
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
r_goto
id|out_free
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|result
suffix:semicolon
id|out_defer
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFS: deferring async READ request.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|out_free
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;NFS: failed to enqueue async READ request.&bslash;n&quot;
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|req
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/*&n; * Read a page over NFS.&n; * We read the page synchronously in the following cases:&n; *  -&t;The file is a swap file. Swap-ins are always sync operations,&n; *&t;so there&squot;s no need bothering to make async reads 100% fail-safe.&n; *  -&t;The NFS rsize is smaller than PAGE_CACHE_SIZE. We could kludge our way&n; *&t;around this by creating several consecutive read requests, but&n; *&t;that&squot;s hardly worth it.&n; *  -&t;The error flag is set for this page. This happens only when a&n; *&t;previous async read operation failed.&n; *  -&t;The server is congested.&n; */
r_int
DECL|function|nfs_readpage
id|nfs_readpage
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_struct
id|page
op_star
id|page
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|error
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage (%p %ld@%lu)&bslash;n&quot;
comma
id|page
comma
id|PAGE_CACHE_SIZE
comma
id|page-&gt;index
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|page
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Try to flush any pending writes to the file..&n;&t; *&n;&t; * NOTE! Because we own the page lock, there cannot&n;&t; * be any new pending writes generated at this point&n;&t; * for this page (other pages can be written to).&n;&t; */
id|error
op_assign
id|nfs_wb_page
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_error
suffix:semicolon
id|error
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
op_logical_and
op_logical_neg
id|PageError
c_func
(paren
id|page
)paren
op_logical_and
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rsize
op_ge
id|PAGE_CACHE_SIZE
)paren
id|error
op_assign
id|nfs_readpage_async
c_func
(paren
id|dentry
comma
id|inode
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|nfs_readpage_sync
c_func
(paren
id|dentry
comma
id|inode
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
op_logical_and
id|IS_SWAPFILE
c_func
(paren
id|inode
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Aiee.. nfs swap-in of page failed!&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|out_free
suffix:semicolon
id|out_error
suffix:colon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|out_free
suffix:colon
id|page_cache_release
c_func
(paren
id|page
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
eof
