multiline_comment|/*&n; *  linux/include/linux/nfs_fs.h&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  OS-specific nfs filesystem definitions and declarations&n; */
macro_line|#ifndef _LINUX_NFS_FS_H
DECL|macro|_LINUX_NFS_FS_H
mdefine_line|#define _LINUX_NFS_FS_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pagemap.h&gt;
macro_line|#include &lt;linux/sunrpc/debug.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs2.h&gt;
macro_line|#include &lt;linux/nfs3.h&gt;
macro_line|#include &lt;linux/nfs_xdr.h&gt;
multiline_comment|/*&n; * Enable debugging support for nfs client.&n; * Requires RPC_DEBUG.&n; */
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFS_DEBUG
macro_line|# define NFS_DEBUG
macro_line|#endif
multiline_comment|/*&n; * NFS_MAX_DIRCACHE controls the number of simultaneously cached&n; * directory chunks. Each chunk holds the list of nfs_entry&squot;s returned&n; * in a single readdir call in a memory region of size PAGE_SIZE.&n; *&n; * Note that at most server-&gt;rsize bytes of the cache memory are used.&n; */
DECL|macro|NFS_MAX_DIRCACHE
mdefine_line|#define NFS_MAX_DIRCACHE&t;&t;16
DECL|macro|NFS_MAX_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_MAX_FILE_IO_BUFFER_SIZE&t;32768
DECL|macro|NFS_DEF_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_DEF_FILE_IO_BUFFER_SIZE&t;4096
multiline_comment|/*&n; * The upper limit on timeouts for the exponential backoff algorithm.&n; */
DECL|macro|NFS_MAX_RPC_TIMEOUT
mdefine_line|#define NFS_MAX_RPC_TIMEOUT&t;&t;(6*HZ)
DECL|macro|NFS_WRITEBACK_DELAY
mdefine_line|#define NFS_WRITEBACK_DELAY&t;&t;(5*HZ)
DECL|macro|NFS_WRITEBACK_LOCKDELAY
mdefine_line|#define NFS_WRITEBACK_LOCKDELAY&t;&t;(60*HZ)
DECL|macro|NFS_COMMIT_DELAY
mdefine_line|#define NFS_COMMIT_DELAY&t;&t;(5*HZ)
multiline_comment|/*&n; * Size of the lookup cache in units of number of entries cached.&n; * It is better not to make this too large although the optimum&n; * depends on a usage and environment.&n; */
DECL|macro|NFS_LOOKUP_CACHE_SIZE
mdefine_line|#define NFS_LOOKUP_CACHE_SIZE&t;&t;64
multiline_comment|/*&n; * superblock magic number for NFS&n; */
DECL|macro|NFS_SUPER_MAGIC
mdefine_line|#define NFS_SUPER_MAGIC&t;&t;&t;0x6969
DECL|macro|NFS_FH
mdefine_line|#define NFS_FH(dentry)&t;&t;&t;((struct nfs_fh *) ((dentry)-&gt;d_fsdata))
DECL|macro|NFS_DSERVER
mdefine_line|#define NFS_DSERVER(dentry)&t;&t;(&amp;(dentry)-&gt;d_sb-&gt;u.nfs_sb.s_server)
DECL|macro|NFS_SERVER
mdefine_line|#define NFS_SERVER(inode)&t;&t;(&amp;(inode)-&gt;i_sb-&gt;u.nfs_sb.s_server)
DECL|macro|NFS_CLIENT
mdefine_line|#define NFS_CLIENT(inode)&t;&t;(NFS_SERVER(inode)-&gt;client)
DECL|macro|NFS_PROTO
mdefine_line|#define NFS_PROTO(inode)&t;&t;(NFS_SERVER(inode)-&gt;rpc_ops)
DECL|macro|NFS_REQUESTLIST
mdefine_line|#define NFS_REQUESTLIST(inode)&t;&t;(NFS_SERVER(inode)-&gt;rw_requests)
DECL|macro|NFS_ADDR
mdefine_line|#define NFS_ADDR(inode)&t;&t;&t;(RPC_PEERADDR(NFS_CLIENT(inode)))
DECL|macro|NFS_CONGESTED
mdefine_line|#define NFS_CONGESTED(inode)&t;&t;(RPC_CONGESTED(NFS_CLIENT(inode)))
DECL|macro|NFS_COOKIEVERF
mdefine_line|#define NFS_COOKIEVERF(inode)&t;&t;((inode)-&gt;u.nfs_i.cookieverf)
DECL|macro|NFS_READTIME
mdefine_line|#define NFS_READTIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_jiffies)
DECL|macro|NFS_CACHE_CTIME
mdefine_line|#define NFS_CACHE_CTIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_ctime)
DECL|macro|NFS_CACHE_MTIME
mdefine_line|#define NFS_CACHE_MTIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_mtime)
DECL|macro|NFS_CACHE_ATIME
mdefine_line|#define NFS_CACHE_ATIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_atime)
DECL|macro|NFS_CACHE_ISIZE
mdefine_line|#define NFS_CACHE_ISIZE(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_isize)
DECL|macro|NFS_NEXTSCAN
mdefine_line|#define NFS_NEXTSCAN(inode)&t;&t;((inode)-&gt;u.nfs_i.nextscan)
DECL|macro|NFS_CACHEINV
mdefine_line|#define NFS_CACHEINV(inode) &bslash;&n;do { &bslash;&n;&t;NFS_READTIME(inode) = jiffies - NFS_MAXATTRTIMEO(inode) - 1; &bslash;&n;} while (0)
DECL|macro|NFS_ATTRTIMEO
mdefine_line|#define NFS_ATTRTIMEO(inode)&t;&t;((inode)-&gt;u.nfs_i.attrtimeo)
DECL|macro|NFS_MINATTRTIMEO
mdefine_line|#define NFS_MINATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmin &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmin)
DECL|macro|NFS_MAXATTRTIMEO
mdefine_line|#define NFS_MAXATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmax &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmax)
DECL|macro|NFS_ATTRTIMEO_UPDATE
mdefine_line|#define NFS_ATTRTIMEO_UPDATE(inode)&t;((inode)-&gt;u.nfs_i.attrtimeo_timestamp)
DECL|macro|NFS_FLAGS
mdefine_line|#define NFS_FLAGS(inode)&t;&t;((inode)-&gt;u.nfs_i.flags)
DECL|macro|NFS_REVALIDATING
mdefine_line|#define NFS_REVALIDATING(inode)&t;&t;(NFS_FLAGS(inode) &amp; NFS_INO_REVALIDATING)
DECL|macro|NFS_FILEID
mdefine_line|#define NFS_FILEID(inode)&t;&t;((inode)-&gt;u.nfs_i.fileid)
DECL|macro|NFS_FSID
mdefine_line|#define NFS_FSID(inode)&t;&t;&t;((inode)-&gt;u.nfs_i.fsid)
multiline_comment|/* Inode Flags */
DECL|macro|NFS_USE_READDIRPLUS
mdefine_line|#define NFS_USE_READDIRPLUS(inode)&t;((NFS_FLAGS(inode) &amp; NFS_INO_ADVISE_RDPLUS) ? 1 : 0)
DECL|macro|NFS_MONOTONE_COOKIES
mdefine_line|#define NFS_MONOTONE_COOKIES(inode)&t;((NFS_SERVER(inode)-&gt;flags &amp; NFS_NONMONOTONE_COOKIES) ? 0 : 1)
multiline_comment|/*&n; * These are the default flags for swap requests&n; */
DECL|macro|NFS_RPC_SWAPFLAGS
mdefine_line|#define NFS_RPC_SWAPFLAGS&t;&t;(RPC_TASK_SWAPPER|RPC_TASK_ROOTCREDS)
multiline_comment|/* Flags in the RPC client structure */
DECL|macro|NFS_CLNTF_BUFSIZE
mdefine_line|#define NFS_CLNTF_BUFSIZE&t;0x0001&t;/* readdir buffer in longwords */
DECL|macro|NFS_RW_SYNC
mdefine_line|#define NFS_RW_SYNC&t;&t;0x0001&t;/* O_SYNC handling */
DECL|macro|NFS_RW_SWAP
mdefine_line|#define NFS_RW_SWAP&t;&t;0x0002&t;/* This is a swap request */
multiline_comment|/*&n; * When flushing a cluster of dirty pages, there can be different&n; * strategies:&n; */
DECL|macro|FLUSH_AGING
mdefine_line|#define FLUSH_AGING&t;&t;0&t;/* only flush old buffers */
DECL|macro|FLUSH_SYNC
mdefine_line|#define FLUSH_SYNC&t;&t;1&t;/* file being synced, or contention */
DECL|macro|FLUSH_WAIT
mdefine_line|#define FLUSH_WAIT&t;&t;2&t;/* wait for completion */
DECL|macro|FLUSH_STABLE
mdefine_line|#define FLUSH_STABLE&t;&t;4&t;/* commit to stable storage */
r_static
r_inline
DECL|function|page_offset
id|loff_t
id|page_offset
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
(paren
(paren
id|loff_t
)paren
id|page-&gt;index
)paren
op_lshift
id|PAGE_CACHE_SHIFT
suffix:semicolon
)brace
r_static
r_inline
DECL|function|page_index
r_int
r_int
id|page_index
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|page-&gt;index
suffix:semicolon
)brace
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * linux/fs/nfs/inode.c&n; */
r_extern
r_struct
id|super_block
op_star
id|nfs_read_super
c_func
(paren
r_struct
id|super_block
op_star
comma
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|init_nfs_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|nfs_zap_caches
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|nfs_fhget
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|nfs_fh
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_refresh_inode
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|nfs_fattr
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_revalidate
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_release
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|__nfs_revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_notify_change
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/file.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_file_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|nfs_file_operations
suffix:semicolon
r_extern
r_struct
id|address_space_operations
id|nfs_file_aops
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/dir.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|file_operations
id|nfs_dir_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|nfs_dentry_operations
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/symlink.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_symlink_inode_operations
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/locks.c&n; */
r_extern
r_int
id|nfs_lock
c_func
(paren
r_struct
id|file
op_star
comma
r_int
comma
r_struct
id|file_lock
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/write.c&n; */
r_extern
r_int
id|nfs_writepage
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_check_failed_request
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_struct
id|nfs_page
op_star
id|nfs_find_request
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_release_request
c_func
(paren
r_struct
id|nfs_page
op_star
id|req
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_incompatible
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
suffix:semicolon
r_extern
r_int
id|nfs_updatepage
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|page
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Try to write back everything synchronously (but check the&n; * return value!)&n; */
r_extern
r_int
id|nfs_sync_file
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_file
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_flush_timeout
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NFS_V3
r_extern
r_int
id|nfs_commit_file
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|nfs_commit_timeout
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
r_static
r_inline
r_int
DECL|function|nfs_have_writebacks
id|nfs_have_writebacks
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|inode-&gt;u.nfs_i.writeback
)paren
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|nfs_wb_all
id|nfs_wb_all
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|FLUSH_WAIT
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
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back all requests on one page - we do this before reading it.&n; */
r_static
r_inline
r_int
DECL|function|nfs_wb_page
id|nfs_wb_page
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
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
l_int|0
comma
id|page_index
c_func
(paren
id|page
)paren
comma
l_int|1
comma
id|FLUSH_WAIT
op_or
id|FLUSH_STABLE
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
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Write back all pending writes for one user.. &n; */
r_static
r_inline
r_int
DECL|function|nfs_wb_file
id|nfs_wb_file
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_int
id|error
op_assign
id|nfs_sync_file
c_func
(paren
id|inode
comma
id|file
comma
l_int|0
comma
l_int|0
comma
id|FLUSH_WAIT
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
id|error
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * linux/fs/nfs/read.c&n; */
r_extern
r_int
id|nfs_readpage
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|page
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * linux/fs/mount_clnt.c&n; * (Used only by nfsroot module)&n; */
r_extern
r_int
id|nfs_mount
c_func
(paren
r_struct
id|sockaddr_in
op_star
comma
r_char
op_star
comma
r_struct
id|nfs_fh
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs3_mount
c_func
(paren
r_struct
id|sockaddr_in
op_star
comma
r_char
op_star
comma
r_struct
id|nfs_fh
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * inline functions&n; */
r_static
r_inline
r_int
DECL|function|nfs_revalidate_inode
id|nfs_revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|dentry
op_star
id|dentry
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|NFS_READTIME
c_func
(paren
id|inode
)paren
op_plus
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__nfs_revalidate_inode
c_func
(paren
id|server
comma
id|dentry
)paren
suffix:semicolon
)brace
r_static
r_inline
id|loff_t
DECL|function|nfs_size_to_loff_t
id|nfs_size_to_loff_t
c_func
(paren
id|__u64
id|size
)paren
(brace
id|loff_t
id|maxsz
op_assign
(paren
(paren
(paren
id|loff_t
)paren
id|ULONG_MAX
)paren
op_lshift
id|PAGE_CACHE_SHIFT
)paren
op_plus
id|PAGE_CACHE_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|maxsz
)paren
r_return
id|maxsz
suffix:semicolon
r_return
(paren
id|loff_t
)paren
id|size
suffix:semicolon
)brace
r_static
r_inline
id|ino_t
DECL|function|nfs_fileid_to_ino_t
id|nfs_fileid_to_ino_t
c_func
(paren
id|u64
id|fileid
)paren
(brace
id|ino_t
id|ino
op_assign
(paren
id|ino_t
)paren
id|fileid
suffix:semicolon
r_if
c_cond
(paren
r_sizeof
(paren
id|ino_t
)paren
OL
r_sizeof
(paren
id|u64
)paren
)paren
id|ino
op_xor_assign
id|fileid
op_rshift
(paren
r_sizeof
(paren
id|u64
)paren
op_minus
r_sizeof
(paren
id|ino_t
)paren
)paren
op_star
l_int|8
suffix:semicolon
r_return
id|ino
suffix:semicolon
)brace
r_static
r_inline
id|time_t
DECL|function|nfs_time_to_secs
id|nfs_time_to_secs
c_func
(paren
id|__u64
id|time
)paren
(brace
r_return
(paren
id|time_t
)paren
(paren
id|time
op_rshift
l_int|32
)paren
suffix:semicolon
)brace
multiline_comment|/* NFS root */
r_extern
r_void
op_star
id|nfs_root_data
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|nfs_wait_event
mdefine_line|#define nfs_wait_event(clnt, wq, condition)&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __retval = 0;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (clnt-&gt;cl_intr) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;sigset_t oldmask;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;rpc_clnt_sigmask(clnt, &amp;oldmask);&t;&t;&t;&bslash;&n;&t;&t;__retval = wait_event_interruptible(wq, condition);&t;&bslash;&n;&t;&t;rpc_clnt_sigunmask(clnt, &amp;oldmask);&t;&t;&t;&bslash;&n;&t;} else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;wait_event(wq, condition);&t;&t;&t;&t;&bslash;&n;&t;__retval;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * NFS debug flags&n; */
DECL|macro|NFSDBG_VFS
mdefine_line|#define NFSDBG_VFS&t;&t;0x0001
DECL|macro|NFSDBG_DIRCACHE
mdefine_line|#define NFSDBG_DIRCACHE&t;&t;0x0002
DECL|macro|NFSDBG_LOOKUPCACHE
mdefine_line|#define NFSDBG_LOOKUPCACHE&t;0x0004
DECL|macro|NFSDBG_PAGECACHE
mdefine_line|#define NFSDBG_PAGECACHE&t;0x0008
DECL|macro|NFSDBG_PROC
mdefine_line|#define NFSDBG_PROC&t;&t;0x0010
DECL|macro|NFSDBG_XDR
mdefine_line|#define NFSDBG_XDR&t;&t;0x0020
DECL|macro|NFSDBG_FILE
mdefine_line|#define NFSDBG_FILE&t;&t;0x0040
DECL|macro|NFSDBG_ROOT
mdefine_line|#define NFSDBG_ROOT&t;&t;0x0080
DECL|macro|NFSDBG_ALL
mdefine_line|#define NFSDBG_ALL&t;&t;0xFFFF
macro_line|#ifdef __KERNEL__
DECL|macro|ifdebug
macro_line|# undef ifdebug
macro_line|# ifdef NFS_DEBUG
DECL|macro|ifdebug
macro_line|#  define ifdebug(fac)&t;&t;if (nfs_debug &amp; NFSDBG_##fac)
macro_line|# else
DECL|macro|ifdebug
macro_line|#  define ifdebug(fac)&t;&t;if (0)
macro_line|# endif
macro_line|#endif /* __KERNEL */
macro_line|#endif
eof
