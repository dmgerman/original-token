multiline_comment|/*&n; *  linux/include/linux/nfs_fs.h&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  OS-specific nfs filesystem definitions and declarations&n; */
macro_line|#ifndef _LINUX_NFS_FS_H
DECL|macro|_LINUX_NFS_FS_H
mdefine_line|#define _LINUX_NFS_FS_H
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/sched.h&gt;
macro_line|#include &lt;linux/nfs.h&gt;
macro_line|#include &lt;linux/nfs_mount.h&gt;
multiline_comment|/*&n; * Enable debugging support for nfs client.&n; * Requires RPC_DEBUG.&n; */
macro_line|#ifdef RPC_DEBUG
DECL|macro|NFS_DEBUG
macro_line|# define NFS_DEBUG
macro_line|#endif
multiline_comment|/*&n; * NFS_MAX_DIRCACHE controls the number of simultaneously cached&n; * directory chunks. Each chunk holds the list of nfs_entry&squot;s returned&n; * in a single readdir call in a memory region of size PAGE_SIZE.&n; *&n; * Note that at most server-&gt;rsize bytes of the cache memory are used.&n; */
DECL|macro|NFS_MAX_DIRCACHE
mdefine_line|#define NFS_MAX_DIRCACHE&t;&t;16
DECL|macro|NFS_MAX_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_MAX_FILE_IO_BUFFER_SIZE&t;16384
DECL|macro|NFS_DEF_FILE_IO_BUFFER_SIZE
mdefine_line|#define NFS_DEF_FILE_IO_BUFFER_SIZE&t;4096
multiline_comment|/*&n; * The upper limit on timeouts for the exponential backoff algorithm.&n; */
DECL|macro|NFS_MAX_RPC_TIMEOUT
mdefine_line|#define NFS_MAX_RPC_TIMEOUT&t;&t;(6*HZ)
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
DECL|macro|NFS_ADDR
mdefine_line|#define NFS_ADDR(inode)&t;&t;&t;(RPC_PEERADDR(NFS_CLIENT(inode)))
DECL|macro|NFS_CONGESTED
mdefine_line|#define NFS_CONGESTED(inode)&t;&t;(RPC_CONGESTED(NFS_CLIENT(inode)))
DECL|macro|NFS_READTIME
mdefine_line|#define NFS_READTIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_jiffies)
DECL|macro|NFS_OLDMTIME
mdefine_line|#define NFS_OLDMTIME(inode)&t;&t;((inode)-&gt;u.nfs_i.read_cache_mtime)
DECL|macro|NFS_CACHEINV
mdefine_line|#define NFS_CACHEINV(inode) &bslash;&n;do { &bslash;&n;&t;NFS_READTIME(inode) = jiffies - 1000000; &bslash;&n;&t;NFS_OLDMTIME(inode) = 0; &bslash;&n;} while (0)
DECL|macro|NFS_ATTRTIMEO
mdefine_line|#define NFS_ATTRTIMEO(inode)&t;&t;((inode)-&gt;u.nfs_i.attrtimeo)
DECL|macro|NFS_MINATTRTIMEO
mdefine_line|#define NFS_MINATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmin &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmin)
DECL|macro|NFS_MAXATTRTIMEO
mdefine_line|#define NFS_MAXATTRTIMEO(inode) &bslash;&n;&t;(S_ISDIR(inode-&gt;i_mode)? NFS_SERVER(inode)-&gt;acdirmax &bslash;&n;&t;&t;&t;       : NFS_SERVER(inode)-&gt;acregmax)
DECL|macro|NFS_FLAGS
mdefine_line|#define NFS_FLAGS(inode)&t;&t;((inode)-&gt;u.nfs_i.flags)
DECL|macro|NFS_REVALIDATING
mdefine_line|#define NFS_REVALIDATING(inode)&t;&t;(NFS_FLAGS(inode) &amp; NFS_INO_REVALIDATE)
DECL|macro|NFS_WRITEBACK
mdefine_line|#define NFS_WRITEBACK(inode)&t;&t;((inode)-&gt;u.nfs_i.writeback)
DECL|macro|NFS_COOKIES
mdefine_line|#define NFS_COOKIES(inode)&t;&t;((inode)-&gt;u.nfs_i.cookies)
DECL|macro|NFS_DIREOF
mdefine_line|#define NFS_DIREOF(inode)&t;&t;((inode)-&gt;u.nfs_i.direof)
multiline_comment|/*&n; * These are the default flags for swap requests&n; */
DECL|macro|NFS_RPC_SWAPFLAGS
mdefine_line|#define NFS_RPC_SWAPFLAGS&t;&t;(RPC_TASK_SWAPPER|RPC_TASK_ROOTCREDS)
multiline_comment|/* Flags in the RPC client structure */
DECL|macro|NFS_CLNTF_BUFSIZE
mdefine_line|#define NFS_CLNTF_BUFSIZE&t;0x0001&t;/* readdir buffer in longwords */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This struct describes a file region to be written.&n; * It&squot;s kind of a pity we have to keep all these lists ourselves, rather&n; * than sticking an extra pointer into struct page.&n; */
DECL|struct|nfs_wreq
r_struct
id|nfs_wreq
(brace
DECL|member|wb_list
r_struct
id|rpc_listitem
id|wb_list
suffix:semicolon
multiline_comment|/* linked list of req&squot;s */
DECL|member|wb_task
r_struct
id|rpc_task
id|wb_task
suffix:semicolon
multiline_comment|/* RPC task */
DECL|member|wb_file
r_struct
id|file
op_star
id|wb_file
suffix:semicolon
multiline_comment|/* dentry referenced */
DECL|member|wb_page
r_struct
id|page
op_star
id|wb_page
suffix:semicolon
multiline_comment|/* page to be written */
DECL|member|wb_wait
id|wait_queue_head_t
id|wb_wait
suffix:semicolon
multiline_comment|/* wait for completion */
DECL|member|wb_offset
r_int
r_int
id|wb_offset
suffix:semicolon
multiline_comment|/* offset within page */
DECL|member|wb_bytes
r_int
r_int
id|wb_bytes
suffix:semicolon
multiline_comment|/* dirty range */
DECL|member|wb_count
r_int
r_int
id|wb_count
suffix:semicolon
multiline_comment|/* user count */
DECL|member|wb_status
r_int
id|wb_status
suffix:semicolon
DECL|member|wb_pid
id|pid_t
id|wb_pid
suffix:semicolon
multiline_comment|/* owner process */
DECL|member|wb_flags
r_int
r_int
id|wb_flags
suffix:semicolon
multiline_comment|/* status flags */
DECL|member|wb_args
r_struct
id|nfs_writeargs
id|wb_args
suffix:semicolon
multiline_comment|/* NFS RPC stuff */
DECL|member|wb_fattr
r_struct
id|nfs_fattr
id|wb_fattr
suffix:semicolon
multiline_comment|/* file attributes */
)brace
suffix:semicolon
DECL|macro|WB_NEXT
mdefine_line|#define WB_NEXT(req)&t;&t;((struct nfs_wreq *) ((req)-&gt;wb_list.next))
multiline_comment|/*&n; * Various flags for wb_flags&n; */
DECL|macro|NFS_WRITE_CANCELLED
mdefine_line|#define NFS_WRITE_CANCELLED&t;0x0004&t;/* has been cancelled */
DECL|macro|NFS_WRITE_UNCOMMITTED
mdefine_line|#define NFS_WRITE_UNCOMMITTED&t;0x0008&t;/* written but uncommitted (NFSv3) */
DECL|macro|NFS_WRITE_INVALIDATE
mdefine_line|#define NFS_WRITE_INVALIDATE&t;0x0010&t;/* invalidate after write */
DECL|macro|NFS_WRITE_INPROGRESS
mdefine_line|#define NFS_WRITE_INPROGRESS&t;0x0100&t;/* RPC call in progress */
DECL|macro|NFS_WRITE_COMPLETE
mdefine_line|#define NFS_WRITE_COMPLETE&t;0x0200&t;/* RPC call completed */
DECL|macro|WB_CANCELLED
mdefine_line|#define WB_CANCELLED(req)&t;((req)-&gt;wb_flags &amp; NFS_WRITE_CANCELLED)
DECL|macro|WB_UNCOMMITTED
mdefine_line|#define WB_UNCOMMITTED(req)&t;((req)-&gt;wb_flags &amp; NFS_WRITE_UNCOMMITTED)
DECL|macro|WB_INVALIDATE
mdefine_line|#define WB_INVALIDATE(req)&t;((req)-&gt;wb_flags &amp; NFS_WRITE_INVALIDATE)
DECL|macro|WB_INPROGRESS
mdefine_line|#define WB_INPROGRESS(req)&t;((req)-&gt;wb_flags &amp; NFS_WRITE_INPROGRESS)
DECL|macro|WB_COMPLETE
mdefine_line|#define WB_COMPLETE(req)&t;((req)-&gt;wb_flags &amp; NFS_WRITE_COMPLETE)
multiline_comment|/*&n; * linux/fs/nfs/proc.c&n; */
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
suffix:semicolon
r_extern
r_int
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
id|res
)paren
suffix:semicolon
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
id|_nfs_revalidate_inode
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
multiline_comment|/*&n; * linux/fs/nfs/file.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_file_inode_operations
suffix:semicolon
multiline_comment|/*&n; * linux/fs/nfs/dir.c&n; */
r_extern
r_struct
id|inode_operations
id|nfs_dir_inode_operations
suffix:semicolon
r_extern
r_struct
id|dentry_operations
id|nfs_dentry_operations
suffix:semicolon
r_extern
r_void
id|nfs_flush_dircache
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_void
id|nfs_free_dircache
c_func
(paren
r_struct
id|inode
op_star
)paren
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
id|file
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
multiline_comment|/*&n; * Try to write back everything synchronously (but check the&n; * return value!)&n; */
r_extern
r_int
id|nfs_wb_all
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_extern
r_int
id|nfs_wb_page
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
r_int
id|nfs_wb_file
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
multiline_comment|/*&n; * Invalidate write-backs, possibly trying to write them&n; * back first..&n; */
r_extern
r_void
id|nfs_inval
c_func
(paren
r_struct
id|inode
op_star
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
multiline_comment|/*&n; * linux/fs/nfs/read.c&n; */
r_extern
r_int
id|nfs_readpage
c_func
(paren
r_struct
id|file
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
id|jiffies
op_minus
id|NFS_READTIME
c_func
(paren
id|inode
)paren
OL
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|_nfs_revalidate_inode
c_func
(paren
id|server
comma
id|dentry
)paren
suffix:semicolon
)brace
multiline_comment|/* NFS root */
r_extern
r_int
id|nfs_root_mount
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
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
