multiline_comment|/*&n; * linux/fs/nfs/read.c&n; *&n; * Block I/O for NFS&n; *&n; * Partial copy of Linus&squot; read cache modifications to fs/nfs/file.c&n; * modified for async RPC by okir@monad.swb.de&n; *&n; * We do an ugly hack here in order to return proper error codes to the&n; * user program when a read request failed: since generic_file_read&n; * only checks the return value of inode-&gt;i_op-&gt;readpage() which is always 0&n; * for async RPC, we set the error bit of the page to 1 when an error occurs,&n; * and make nfs_readpage transmit requests synchronously when encountering this.&n; * This is only a small problem, though, since we now retry all operations&n; * within the RPC code when root squashing is suspected.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/nfs_page.h&gt;
macro_line|#include &lt;linux/nfs_flushd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_PAGECACHE
DECL|struct|nfs_read_data
r_struct
id|nfs_read_data
(brace
DECL|member|task
r_struct
id|rpc_task
id|task
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|cred
r_struct
id|rpc_cred
op_star
id|cred
suffix:semicolon
DECL|member|args
r_struct
id|nfs_readargs
id|args
suffix:semicolon
multiline_comment|/* XDR argument struct */
DECL|member|res
r_struct
id|nfs_readres
id|res
suffix:semicolon
multiline_comment|/* ... and result struct */
DECL|member|fattr
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
multiline_comment|/* fattr storage */
DECL|member|pages
r_struct
id|list_head
id|pages
suffix:semicolon
multiline_comment|/* Coalesced read requests */
)brace
suffix:semicolon
multiline_comment|/*&n; * Local function declarations&n; */
r_static
r_void
id|nfs_readpage_result
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
suffix:semicolon
multiline_comment|/* Hack for future NFS swap support */
macro_line|#ifndef IS_SWAPFILE
DECL|macro|IS_SWAPFILE
macro_line|# define IS_SWAPFILE(inode)&t;(0)
macro_line|#endif
DECL|variable|nfs_rdata_cachep
r_static
id|kmem_cache_t
op_star
id|nfs_rdata_cachep
suffix:semicolon
DECL|function|nfs_readdata_alloc
r_static
id|__inline__
r_struct
id|nfs_read_data
op_star
id|nfs_readdata_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|nfs_read_data
op_star
id|p
suffix:semicolon
id|p
op_assign
id|kmem_cache_alloc
c_func
(paren
id|nfs_rdata_cachep
comma
id|SLAB_NFS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|p-&gt;pages
)paren
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
DECL|function|nfs_readdata_free
r_static
id|__inline__
r_void
id|nfs_readdata_free
c_func
(paren
r_struct
id|nfs_read_data
op_star
id|p
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|nfs_rdata_cachep
comma
id|p
)paren
suffix:semicolon
)brace
DECL|function|nfs_readdata_release
r_static
r_void
id|nfs_readdata_release
c_func
(paren
r_struct
id|rpc_task
op_star
id|task
)paren
(brace
r_struct
id|nfs_read_data
op_star
id|data
op_assign
(paren
r_struct
id|nfs_read_data
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
id|nfs_readdata_free
c_func
(paren
id|data
)paren
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
id|file
op_star
id|file
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
id|rpc_cred
op_star
id|cred
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
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
r_int
id|eof
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: nfs_readpage_sync(%p)&bslash;n&quot;
comma
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
id|cred
op_assign
id|nfs_file_cred
c_func
(paren
id|file
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This works now because the socket layer never tries to DMA&n;&t; * into this buffer directly.&n;&t; */
id|buffer
op_assign
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
l_string|&quot;NFS: nfs_proc_read(%s, (%x/%Ld), %Ld, %d, %p)&bslash;n&quot;
comma
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|hostname
comma
id|inode-&gt;i_dev
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|inode
)paren
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
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
id|NFS_PROTO
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
id|cred
comma
op_amp
id|fattr
comma
id|flags
comma
id|offset
comma
id|rsize
comma
id|buffer
comma
op_amp
id|eof
)paren
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|fattr
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
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
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PageError
c_func
(paren
id|page
)paren
)paren
id|ClearPageError
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
r_static
r_inline
r_struct
id|nfs_page
op_star
DECL|function|_nfs_find_read
id|_nfs_find_read
c_func
(paren
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
id|list_head
op_star
id|head
comma
op_star
id|next
suffix:semicolon
id|head
op_assign
op_amp
id|inode-&gt;u.nfs_i.read
suffix:semicolon
id|next
op_assign
id|head-&gt;next
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
id|head
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|next
)paren
suffix:semicolon
id|next
op_assign
id|next-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|page_index
c_func
(paren
id|req-&gt;wb_page
)paren
op_ne
id|page_index
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|req-&gt;wb_count
op_increment
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_struct
id|nfs_page
op_star
DECL|function|nfs_find_read
id|nfs_find_read
c_func
(paren
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
id|nfs_page
op_star
id|req
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
id|req
op_assign
id|_nfs_find_read
c_func
(paren
id|inode
comma
id|page
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_return
id|req
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a request to the inode&squot;s asynchronous read list.&n; */
r_static
r_inline
r_void
DECL|function|nfs_mark_request_read
id|nfs_mark_request_read
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|req-&gt;wb_inode
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|req-&gt;wb_list
)paren
)paren
(brace
id|nfs_list_add_request
c_func
(paren
id|req
comma
op_amp
id|inode-&gt;u.nfs_i.read
)paren
suffix:semicolon
id|inode-&gt;u.nfs_i.nread
op_increment
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * NB: the call to inode_schedule_scan() must lie outside the&n;&t; *     spinlock since it can run flushd().&n;&t; */
id|inode_schedule_scan
c_func
(paren
id|inode
comma
id|req-&gt;wb_timeout
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_readpage_async
id|nfs_readpage_async
c_func
(paren
r_struct
id|file
op_star
id|file
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
id|nfs_page
op_star
id|req
comma
op_star
r_new
op_assign
l_int|NULL
suffix:semicolon
r_int
id|result
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|Page_Uptodate
c_func
(paren
id|page
)paren
)paren
r_break
suffix:semicolon
id|req
op_assign
id|nfs_find_read
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
id|req
)paren
(brace
r_if
c_cond
(paren
id|page
op_ne
id|req-&gt;wb_page
)paren
(brace
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_pagein_inode
c_func
(paren
id|inode
comma
id|page_index
c_func
(paren
id|page
)paren
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
)paren
(brace
id|nfs_lock_request
c_func
(paren
r_new
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|wb_timeout
op_assign
id|jiffies
op_plus
id|NFS_READ_DELAY
suffix:semicolon
id|nfs_mark_request_read
c_func
(paren
r_new
)paren
suffix:semicolon
id|nfs_unlock_request
c_func
(paren
r_new
)paren
suffix:semicolon
r_new
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_new
op_assign
id|nfs_create_request
c_func
(paren
id|file
comma
id|inode
comma
id|page
comma
l_int|0
comma
id|PAGE_CACHE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;u.nfs_i.nread
op_ge
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rpages
op_logical_or
id|page_index
c_func
(paren
id|page
)paren
op_eq
(paren
id|inode-&gt;i_size
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_CACHE_SHIFT
)paren
id|nfs_pagein_inode
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
)paren
id|nfs_release_request
c_func
(paren
r_new
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up the NFS read request struct&n; */
r_static
r_void
DECL|function|nfs_read_rpcsetup
id|nfs_read_rpcsetup
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|nfs_read_data
op_star
id|data
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_struct
id|iovec
op_star
id|iov
suffix:semicolon
r_int
r_int
id|count
suffix:semicolon
id|iov
op_assign
id|data-&gt;args.iov
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|head
)paren
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|head-&gt;next
)paren
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_list_add_request
c_func
(paren
id|req
comma
op_amp
id|data-&gt;pages
)paren
suffix:semicolon
id|iov-&gt;iov_base
op_assign
id|kmap
c_func
(paren
id|req-&gt;wb_page
)paren
op_plus
id|req-&gt;wb_offset
suffix:semicolon
id|iov-&gt;iov_len
op_assign
id|req-&gt;wb_bytes
suffix:semicolon
id|count
op_add_assign
id|req-&gt;wb_bytes
suffix:semicolon
id|iov
op_increment
suffix:semicolon
id|data-&gt;args.nriov
op_increment
suffix:semicolon
)brace
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|data-&gt;pages.next
)paren
suffix:semicolon
id|data-&gt;inode
op_assign
id|req-&gt;wb_inode
suffix:semicolon
id|data-&gt;cred
op_assign
id|req-&gt;wb_cred
suffix:semicolon
id|data-&gt;args.fh
op_assign
id|NFS_FH
c_func
(paren
id|req-&gt;wb_inode
)paren
suffix:semicolon
id|data-&gt;args.offset
op_assign
id|page_offset
c_func
(paren
id|req-&gt;wb_page
)paren
op_plus
id|req-&gt;wb_offset
suffix:semicolon
id|data-&gt;args.count
op_assign
id|count
suffix:semicolon
id|data-&gt;res.fattr
op_assign
op_amp
id|data-&gt;fattr
suffix:semicolon
id|data-&gt;res.count
op_assign
id|count
suffix:semicolon
id|data-&gt;res.eof
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|nfs_async_read_error
id|nfs_async_read_error
c_func
(paren
r_struct
id|list_head
op_star
id|head
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|head
)paren
)paren
(brace
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|head-&gt;next
)paren
suffix:semicolon
id|page
op_assign
id|req-&gt;wb_page
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|SetPageError
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
id|nfs_unlock_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|nfs_pagein_one
id|nfs_pagein_one
c_func
(paren
r_struct
id|list_head
op_star
id|head
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|rpc_task
op_star
id|task
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
op_assign
id|NFS_CLIENT
c_func
(paren
id|inode
)paren
suffix:semicolon
r_struct
id|nfs_read_data
op_star
id|data
suffix:semicolon
r_struct
id|rpc_message
id|msg
suffix:semicolon
r_int
id|flags
suffix:semicolon
id|sigset_t
id|oldset
suffix:semicolon
id|data
op_assign
id|nfs_readdata_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
r_goto
id|out_bad
suffix:semicolon
id|task
op_assign
op_amp
id|data-&gt;task
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
id|nfs_read_rpcsetup
c_func
(paren
id|head
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Finalize the task. */
id|rpc_init_task
c_func
(paren
id|task
comma
id|clnt
comma
id|nfs_readpage_result
comma
id|flags
)paren
suffix:semicolon
id|task-&gt;tk_calldata
op_assign
id|data
suffix:semicolon
multiline_comment|/* Release requests */
id|task-&gt;tk_release
op_assign
id|nfs_readdata_release
suffix:semicolon
macro_line|#ifdef CONFIG_NFS_V3
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
macro_line|#else
id|msg.rpc_proc
op_assign
id|NFSPROC_READ
suffix:semicolon
macro_line|#endif
id|msg.rpc_argp
op_assign
op_amp
id|data-&gt;args
suffix:semicolon
id|msg.rpc_resp
op_assign
op_amp
id|data-&gt;res
suffix:semicolon
id|msg.rpc_cred
op_assign
id|data-&gt;cred
suffix:semicolon
multiline_comment|/* Start the async call */
id|dprintk
c_func
(paren
l_string|&quot;NFS: %4d initiated read call (req %x/%Ld count %d nriov %d.&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|inode-&gt;i_dev
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|inode
)paren
comma
id|data-&gt;args.count
comma
id|data-&gt;args.nriov
)paren
suffix:semicolon
id|rpc_clnt_sigmask
c_func
(paren
id|clnt
comma
op_amp
id|oldset
)paren
suffix:semicolon
id|rpc_call_setup
c_func
(paren
id|task
comma
op_amp
id|msg
comma
l_int|0
)paren
suffix:semicolon
id|rpc_execute
c_func
(paren
id|task
)paren
suffix:semicolon
id|rpc_clnt_sigunmask
c_func
(paren
id|clnt
comma
op_amp
id|oldset
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_bad
suffix:colon
id|nfs_async_read_error
c_func
(paren
id|head
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_pagein_list
id|nfs_pagein_list
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|list_head
op_star
id|head
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|one_request
)paren
suffix:semicolon
r_struct
id|nfs_page
op_star
id|req
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pages
op_assign
l_int|0
comma
id|rpages
op_assign
id|NFS_SERVER
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|rpages
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
id|head
)paren
)paren
(brace
id|pages
op_add_assign
id|nfs_coalesce_requests
c_func
(paren
id|head
comma
op_amp
id|one_request
comma
id|rpages
)paren
suffix:semicolon
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|one_request.next
)paren
suffix:semicolon
id|error
op_assign
id|nfs_pagein_one
c_func
(paren
op_amp
id|one_request
comma
id|req-&gt;wb_inode
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
r_if
c_cond
(paren
id|error
op_ge
l_int|0
)paren
r_return
id|pages
suffix:semicolon
id|nfs_async_read_error
c_func
(paren
id|head
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_scan_read_timeout
id|nfs_scan_read_timeout
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|list_head
op_star
id|dst
)paren
(brace
r_int
id|pages
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
id|pages
op_assign
id|nfs_scan_list_timeout
c_func
(paren
op_amp
id|inode-&gt;u.nfs_i.read
comma
id|dst
comma
id|inode
)paren
suffix:semicolon
id|inode-&gt;u.nfs_i.nread
op_sub_assign
id|pages
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;u.nfs_i.nread
op_eq
l_int|0
)paren
op_ne
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;u.nfs_i.read
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NFS: desynchronized value of nfs_i.nread.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_return
id|pages
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_scan_read
id|nfs_scan_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|list_head
op_star
id|dst
comma
r_int
r_int
id|idx_start
comma
r_int
r_int
id|npages
)paren
(brace
r_int
id|res
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
id|res
op_assign
id|nfs_scan_list
c_func
(paren
op_amp
id|inode-&gt;u.nfs_i.read
comma
id|dst
comma
l_int|NULL
comma
id|idx_start
comma
id|npages
)paren
suffix:semicolon
id|inode-&gt;u.nfs_i.nread
op_sub_assign
id|res
suffix:semicolon
r_if
c_cond
(paren
(paren
id|inode-&gt;u.nfs_i.nread
op_eq
l_int|0
)paren
op_ne
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;u.nfs_i.read
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NFS: desynchronized value of nfs_i.nread.&bslash;n&quot;
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|nfs_wreq_lock
)paren
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|nfs_pagein_inode
r_int
id|nfs_pagein_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|idx_start
comma
r_int
r_int
id|npages
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
r_int
id|res
comma
id|error
op_assign
l_int|0
suffix:semicolon
id|res
op_assign
id|nfs_scan_read
c_func
(paren
id|inode
comma
op_amp
id|head
comma
id|idx_start
comma
id|npages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
id|error
op_assign
id|nfs_pagein_list
c_func
(paren
id|inode
comma
op_amp
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_return
id|res
suffix:semicolon
)brace
DECL|function|nfs_pagein_timeout
r_int
id|nfs_pagein_timeout
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|LIST_HEAD
c_func
(paren
id|head
)paren
suffix:semicolon
r_int
id|pages
comma
id|error
op_assign
l_int|0
suffix:semicolon
id|pages
op_assign
id|nfs_scan_read_timeout
c_func
(paren
id|inode
comma
op_amp
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages
)paren
id|error
op_assign
id|nfs_pagein_list
c_func
(paren
id|inode
comma
op_amp
id|head
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
OL
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_return
id|pages
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
id|nfs_read_data
op_star
id|data
op_assign
(paren
r_struct
id|nfs_read_data
op_star
)paren
id|task-&gt;tk_calldata
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|data-&gt;inode
suffix:semicolon
r_int
id|count
op_assign
id|data-&gt;res.count
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;NFS: %4d nfs_readpage_result, (status %d)&bslash;n&quot;
comma
id|task-&gt;tk_pid
comma
id|task-&gt;tk_status
)paren
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
op_amp
id|data-&gt;fattr
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|data-&gt;pages
)paren
)paren
(brace
r_struct
id|nfs_page
op_star
id|req
op_assign
id|nfs_list_entry
c_func
(paren
id|data-&gt;pages.next
)paren
suffix:semicolon
r_struct
id|page
op_star
id|page
op_assign
id|req-&gt;wb_page
suffix:semicolon
id|nfs_list_remove_request
c_func
(paren
id|req
)paren
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;tk_status
op_ge
l_int|0
op_logical_and
id|count
op_ge
l_int|0
)paren
(brace
id|SetPageUptodate
c_func
(paren
id|page
)paren
suffix:semicolon
id|count
op_sub_assign
id|PAGE_CACHE_SIZE
suffix:semicolon
)brace
r_else
id|SetPageError
c_func
(paren
id|page
)paren
suffix:semicolon
id|flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
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
id|dprintk
c_func
(paren
l_string|&quot;NFS: read (%x/%Ld %d@%Ld)&bslash;n&quot;
comma
id|req-&gt;wb_inode-&gt;i_dev
comma
(paren
r_int
r_int
)paren
id|NFS_FILEID
c_func
(paren
id|req-&gt;wb_inode
)paren
comma
id|req-&gt;wb_bytes
comma
(paren
r_int
r_int
)paren
(paren
id|page_offset
c_func
(paren
id|page
)paren
op_plus
id|req-&gt;wb_offset
)paren
)paren
suffix:semicolon
id|nfs_unlock_request
c_func
(paren
id|req
)paren
suffix:semicolon
id|nfs_release_request
c_func
(paren
id|req
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Read a page over NFS.&n; * We read the page synchronously in the following cases:&n; *  -&t;The NFS rsize is smaller than PAGE_CACHE_SIZE. We could kludge our way&n; *&t;around this by creating several consecutive read requests, but&n; *&t;that&squot;s hardly worth it.&n; *  -&t;The error flag is set for this page. This happens only when a&n; *&t;previous async read operation failed.&n; */
r_int
DECL|function|nfs_readpage
id|nfs_readpage
c_func
(paren
r_struct
id|file
op_star
id|file
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
suffix:semicolon
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file
)paren
(brace
r_struct
id|address_space
op_star
id|mapping
op_assign
id|page-&gt;mapping
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mapping
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|inode
op_assign
(paren
r_struct
id|inode
op_star
)paren
id|mapping-&gt;host
suffix:semicolon
)brace
r_else
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
id|BUG
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
id|file
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
id|file
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
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_error
suffix:colon
id|UnlockPage
c_func
(paren
id|page
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|nfs_init_readpagecache
r_int
id|nfs_init_readpagecache
c_func
(paren
r_void
)paren
(brace
id|nfs_rdata_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;nfs_read_data&quot;
comma
r_sizeof
(paren
r_struct
id|nfs_read_data
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nfs_rdata_cachep
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nfs_destroy_readpagecache
r_void
id|nfs_destroy_readpagecache
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|kmem_cache_destroy
c_func
(paren
id|nfs_rdata_cachep
)paren
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;nfs_read_data: not all structures were freed&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
