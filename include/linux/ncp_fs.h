multiline_comment|/*&n; *  ncp_fs.h&n; *&n; *  Copyright (C) 1995, 1996 by Volker Lendecke&n; *&n; */
macro_line|#ifndef _LINUX_NCP_FS_H
DECL|macro|_LINUX_NCP_FS_H
mdefine_line|#define _LINUX_NCP_FS_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ncp_mount.h&gt;
macro_line|#include &lt;linux/ncp_fs_sb.h&gt;
macro_line|#include &lt;linux/ncp_fs_i.h&gt;
multiline_comment|/*&n; * ioctl commands&n; */
DECL|struct|ncp_ioctl_request
r_struct
id|ncp_ioctl_request
(brace
DECL|member|function
r_int
r_int
id|function
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|data
r_char
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|ncp_fs_info
r_struct
id|ncp_fs_info
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|addr
r_struct
id|sockaddr_ipx
id|addr
suffix:semicolon
DECL|member|mounted_uid
id|uid_t
id|mounted_uid
suffix:semicolon
DECL|member|connection
r_int
id|connection
suffix:semicolon
multiline_comment|/* Connection number the server assigned us */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* The negotiated buffer size, to be&n;&t;&t;&t;&t;   used for read/write requests! */
DECL|member|volume_number
r_int
id|volume_number
suffix:semicolon
DECL|member|directory_id
id|__u32
id|directory_id
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|NCP_IOC_NCPREQUEST
mdefine_line|#define&t;NCP_IOC_NCPREQUEST&t;&t;_IOR(&squot;n&squot;, 1, struct ncp_ioctl_request)
DECL|macro|NCP_IOC_GETMOUNTUID
mdefine_line|#define&t;NCP_IOC_GETMOUNTUID&t;&t;_IOW(&squot;n&squot;, 2, uid_t)
DECL|macro|NCP_IOC_CONN_LOGGED_IN
mdefine_line|#define NCP_IOC_CONN_LOGGED_IN          _IO(&squot;n&squot;, 3)
DECL|macro|NCP_GET_FS_INFO_VERSION
mdefine_line|#define NCP_GET_FS_INFO_VERSION (1)
DECL|macro|NCP_IOC_GET_FS_INFO
mdefine_line|#define NCP_IOC_GET_FS_INFO             _IOWR(&squot;n&squot;, 4, struct ncp_fs_info)
multiline_comment|/*&n; * The packet size to allocate. One page should be enough.&n; */
DECL|macro|NCP_PACKET_SIZE
mdefine_line|#define NCP_PACKET_SIZE 4070
DECL|macro|NCP_MAXPATHLEN
mdefine_line|#define NCP_MAXPATHLEN 255
DECL|macro|NCP_MAXNAMELEN
mdefine_line|#define NCP_MAXNAMELEN 14
DECL|macro|NCP_MSG_COMMAND
mdefine_line|#define NCP_MSG_COMMAND &quot;/sbin/nwmsg&quot;
macro_line|#ifdef __KERNEL__
multiline_comment|/* The readdir cache size controls how many directory entries are&n; * cached.&n; */
DECL|macro|NCP_READDIR_CACHE_SIZE
mdefine_line|#define NCP_READDIR_CACHE_SIZE        64
DECL|macro|NCP_MAX_RPC_TIMEOUT
mdefine_line|#define NCP_MAX_RPC_TIMEOUT (6*HZ)
multiline_comment|/* Guess, what 0x564c is :-) */
DECL|macro|NCP_SUPER_MAGIC
mdefine_line|#define NCP_SUPER_MAGIC  0x564c
DECL|macro|NCP_SBP
mdefine_line|#define NCP_SBP(sb)          ((struct ncp_server *)((sb)-&gt;u.generic_sbp))
DECL|macro|NCP_INOP
mdefine_line|#define NCP_INOP(inode)      ((struct ncp_inode_info *)((inode)-&gt;u.generic_ip))
DECL|macro|NCP_SERVER
mdefine_line|#define NCP_SERVER(inode)    NCP_SBP((inode)-&gt;i_sb)
DECL|macro|NCP_FINFO
mdefine_line|#define NCP_FINFO(inode)     (&amp;(NCP_INOP(inode)-&gt;finfo))
DECL|macro|NCP_ISTRUCT
mdefine_line|#define NCP_ISTRUCT(inode)   (&amp;(NCP_FINFO(inode)-&gt;i))
macro_line|#ifdef DEBUG_NCP_MALLOC
macro_line|#include &lt;linux/malloc.h&gt;
r_extern
r_int
id|ncp_malloced
suffix:semicolon
r_extern
r_int
id|ncp_current_malloced
suffix:semicolon
r_static
r_inline
r_void
op_star
DECL|function|ncp_kmalloc
id|ncp_kmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
(brace
id|ncp_malloced
op_add_assign
l_int|1
suffix:semicolon
id|ncp_current_malloced
op_add_assign
l_int|1
suffix:semicolon
r_return
id|kmalloc
c_func
(paren
id|size
comma
id|priority
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|ncp_kfree_s
id|ncp_kfree_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
(brace
id|ncp_current_malloced
op_sub_assign
l_int|1
suffix:semicolon
id|kfree_s
c_func
(paren
id|obj
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#else /* DEBUG_NCP_MALLOC */
DECL|macro|ncp_kmalloc
mdefine_line|#define ncp_kmalloc(s,p) kmalloc(s,p)
DECL|macro|ncp_kfree_s
mdefine_line|#define ncp_kfree_s(o,s) kfree_s(o,s)
macro_line|#endif /* DEBUG_NCP_MALLOC */
macro_line|#if DEBUG_NCP &gt; 0
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, args...) printk(format , ## args)
macro_line|#else
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK(format, args...)
macro_line|#endif
macro_line|#if DEBUG_NCP &gt; 1
DECL|macro|DDPRINTK
mdefine_line|#define DDPRINTK(format, args...) printk(format , ## args)
macro_line|#else
DECL|macro|DDPRINTK
mdefine_line|#define DDPRINTK(format, args...)
macro_line|#endif
multiline_comment|/* linux/fs/ncpfs/file.c */
r_extern
r_struct
id|inode_operations
id|ncp_file_inode_operations
suffix:semicolon
r_int
id|ncp_make_open
c_func
(paren
r_struct
id|inode
op_star
id|i
comma
r_int
id|right
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/dir.c */
r_extern
r_struct
id|inode_operations
id|ncp_dir_inode_operations
suffix:semicolon
r_void
id|ncp_free_inode_info
c_func
(paren
r_struct
id|ncp_inode_info
op_star
id|i
)paren
suffix:semicolon
r_void
id|ncp_free_all_inodes
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_init_root
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_conn_logged_in
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_init_dir_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ncp_invalid_dir_cache
c_func
(paren
r_struct
id|inode
op_star
id|ino
)paren
suffix:semicolon
r_struct
id|ncp_inode_info
op_star
id|ncp_find_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
suffix:semicolon
id|ino_t
id|ncp_info_ino
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_struct
id|ncp_inode_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|ncp_free_dir_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|ncp_date_dos2unix
c_func
(paren
id|__u16
id|time
comma
id|__u16
id|date
)paren
suffix:semicolon
r_void
id|ncp_date_unix2dos
c_func
(paren
r_int
id|unix_date
comma
id|__u16
op_star
id|time
comma
id|__u16
op_star
id|date
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/ioctl.c */
r_int
id|ncp_ioctl
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|filp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/inode.c */
r_struct
id|super_block
op_star
id|ncp_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|raw_data
comma
r_int
id|silent
)paren
suffix:semicolon
r_extern
r_int
id|init_ncp_fs
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ncp_trigger_message
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/sock.c */
r_int
id|ncp_request
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
comma
r_int
id|function
)paren
suffix:semicolon
r_int
id|ncp_connect
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_disconnect
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_catch_watchdog
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_dont_catch_watchdog
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_int
id|ncp_catch_message
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_lock_server
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
r_void
id|ncp_unlock_server
c_func
(paren
r_struct
id|ncp_server
op_star
id|server
)paren
suffix:semicolon
multiline_comment|/* linux/fs/ncpfs/mmap.c */
r_int
id|ncp_mmap
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
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_NCP_FS_H */
eof
