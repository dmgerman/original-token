multiline_comment|/*&n; *  linux/fs/nfs/inode.c&n; *&n; *  Copyright (C) 1992  Rick Sladkey&n; *&n; *  nfs inode and superblock handling functions&n; *&n; *  Modularised by Alan Cox &lt;Alan.Cox@linux.org&gt;, while hacking some&n; *  experimental NFS changes. Modularisation taken straight from SYS5 fs.&n; *&n; *  Change to nfs_read_super() to permit NFS mounts to multi-homed hosts.&n; *  J.S.Peatfield@damtp.cam.ac.uk&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/sunrpc/clnt.h&gt;
macro_line|#include &lt;linux/sunrpc/stats.h&gt;
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|NFSDBG_FACILITY
mdefine_line|#define NFSDBG_FACILITY&t;&t;NFSDBG_VFS
r_static
r_int
id|nfs_notify_change
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|iattr
op_star
)paren
suffix:semicolon
r_static
r_void
id|nfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|nfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|nfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_void
id|nfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_int
id|nfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|statfs
op_star
comma
r_int
id|bufsiz
)paren
suffix:semicolon
DECL|variable|nfs_sops
r_static
r_struct
id|super_operations
id|nfs_sops
op_assign
(brace
id|nfs_read_inode
comma
multiline_comment|/* read inode */
l_int|NULL
comma
multiline_comment|/* write inode */
id|nfs_put_inode
comma
multiline_comment|/* put inode */
id|nfs_delete_inode
comma
multiline_comment|/* delete inode */
id|nfs_notify_change
comma
multiline_comment|/* notify change */
id|nfs_put_super
comma
multiline_comment|/* put superblock */
l_int|NULL
comma
multiline_comment|/* write superblock */
id|nfs_statfs
comma
multiline_comment|/* stat filesystem */
l_int|NULL
)brace
suffix:semicolon
DECL|variable|nfs_rpcstat
r_struct
id|rpc_stat
id|nfs_rpcstat
op_assign
(brace
op_amp
id|nfs_program
)brace
suffix:semicolon
multiline_comment|/*&n; * The &quot;read_inode&quot; function doesn&squot;t actually do anything:&n; * the real data is filled in later in nfs_fhget. Here we&n; * just mark the cache times invalid, and zero out i_mode&n; * (the latter makes &quot;nfs_refresh_inode&quot; do the right thing&n; * wrt pipe inodes)&n; */
r_static
r_void
DECL|function|nfs_read_inode
id|nfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|inode-&gt;i_blksize
op_assign
id|inode-&gt;i_sb-&gt;s_blocksize
suffix:semicolon
id|inode-&gt;i_mode
op_assign
l_int|0
suffix:semicolon
id|inode-&gt;i_op
op_assign
l_int|NULL
suffix:semicolon
id|NFS_CACHEINV
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|nfs_put_inode
id|nfs_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: put_inode(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This should do any silly-rename cleanups once we&n; * get silly-renaming working again..&n; */
r_static
r_void
DECL|function|nfs_delete_inode
id|nfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: delete_inode(%x/%ld)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
r_void
DECL|function|nfs_put_super
id|nfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|nfs_server
op_star
id|server
op_assign
op_amp
id|sb-&gt;u.nfs_sb.s_server
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|rpc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rpc
op_assign
id|server-&gt;client
)paren
op_ne
l_int|NULL
)paren
id|rpc_shutdown_client
c_func
(paren
id|rpc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|server-&gt;flags
op_amp
id|NFS_MOUNT_NONLM
)paren
)paren
id|lockd_down
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release rpc.lockd */
id|rpciod_down
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* release rpciod */
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Compute and set NFS server blocksize&n; */
r_static
r_int
r_int
DECL|function|nfs_block_size
id|nfs_block_size
c_func
(paren
r_int
r_int
id|bsize
comma
r_int
r_char
op_star
id|nrbitsp
)paren
(brace
r_if
c_cond
(paren
id|bsize
OL
l_int|1024
)paren
id|bsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|bsize
op_ge
id|NFS_MAX_FILE_IO_BUFFER_SIZE
)paren
id|bsize
op_assign
id|NFS_MAX_FILE_IO_BUFFER_SIZE
suffix:semicolon
multiline_comment|/* make sure blocksize is a power of two */
r_if
c_cond
(paren
(paren
id|bsize
op_amp
(paren
id|bsize
op_minus
l_int|1
)paren
)paren
op_logical_or
id|nrbitsp
)paren
(brace
r_int
r_int
id|nrbits
suffix:semicolon
r_for
c_loop
(paren
id|nrbits
op_assign
l_int|31
suffix:semicolon
id|nrbits
op_logical_and
op_logical_neg
(paren
id|bsize
op_amp
(paren
l_int|1
op_lshift
id|nrbits
)paren
)paren
suffix:semicolon
id|nrbits
op_decrement
)paren
suffix:semicolon
id|bsize
op_assign
l_int|1
op_lshift
id|nrbits
suffix:semicolon
r_if
c_cond
(paren
id|nrbitsp
)paren
op_star
id|nrbitsp
op_assign
id|nrbits
suffix:semicolon
r_if
c_cond
(paren
id|bsize
OL
id|NFS_DEF_FILE_IO_BUFFER_SIZE
)paren
id|bsize
op_assign
id|NFS_DEF_FILE_IO_BUFFER_SIZE
suffix:semicolon
)brace
r_return
id|bsize
suffix:semicolon
)brace
multiline_comment|/*&n; * The way this works is that the mount process passes a structure&n; * in the data argument which contains the server&squot;s IP address&n; * and the root file handle obtained from the server&squot;s mount&n; * daemon. We stash these away in the private superblock fields.&n; */
r_struct
id|super_block
op_star
DECL|function|nfs_read_super
id|nfs_read_super
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
(brace
r_struct
id|nfs_mount_data
op_star
id|data
op_assign
(paren
r_struct
id|nfs_mount_data
op_star
)paren
id|raw_data
suffix:semicolon
r_struct
id|sockaddr_in
id|srvaddr
suffix:semicolon
r_struct
id|nfs_server
op_star
id|server
suffix:semicolon
r_struct
id|rpc_timeout
id|timeparms
suffix:semicolon
r_struct
id|rpc_xprt
op_star
id|xprt
suffix:semicolon
r_struct
id|rpc_clnt
op_star
id|clnt
suffix:semicolon
r_int
r_int
id|authflavor
suffix:semicolon
r_int
id|tcp
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_read_super: missing data argument&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|data-&gt;version
op_ne
id|NFS_MOUNT_VERSION
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs warning: mount version %s than kernel&bslash;n&quot;
comma
id|data-&gt;version
OL
id|NFS_MOUNT_VERSION
ques
c_cond
l_string|&quot;older&quot;
suffix:colon
l_string|&quot;newer&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;version
OL
l_int|2
)paren
id|data-&gt;namlen
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|data-&gt;version
OL
l_int|3
)paren
id|data-&gt;bsize
op_assign
l_int|0
suffix:semicolon
)brace
id|lock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|server
op_assign
op_amp
id|sb-&gt;u.nfs_sb.s_server
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|NFS_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|nfs_sops
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
id|nfs_block_size
c_func
(paren
id|data-&gt;bsize
comma
op_amp
id|sb-&gt;s_blocksize_bits
)paren
suffix:semicolon
id|server-&gt;rsize
op_assign
id|nfs_block_size
c_func
(paren
id|data-&gt;rsize
comma
l_int|NULL
)paren
suffix:semicolon
id|server-&gt;wsize
op_assign
id|nfs_block_size
c_func
(paren
id|data-&gt;wsize
comma
l_int|NULL
)paren
suffix:semicolon
id|server-&gt;flags
op_assign
id|data-&gt;flags
suffix:semicolon
id|server-&gt;acregmin
op_assign
id|data-&gt;acregmin
op_star
id|HZ
suffix:semicolon
id|server-&gt;acregmax
op_assign
id|data-&gt;acregmax
op_star
id|HZ
suffix:semicolon
id|server-&gt;acdirmin
op_assign
id|data-&gt;acdirmin
op_star
id|HZ
suffix:semicolon
id|server-&gt;acdirmax
op_assign
id|data-&gt;acdirmax
op_star
id|HZ
suffix:semicolon
id|strcpy
c_func
(paren
id|server-&gt;hostname
comma
id|data-&gt;hostname
)paren
suffix:semicolon
id|sb-&gt;u.nfs_sb.s_root
op_assign
id|data-&gt;root
suffix:semicolon
multiline_comment|/* We now require that the mount process passes the remote address */
id|memcpy
c_func
(paren
op_amp
id|srvaddr
comma
op_amp
id|data-&gt;addr
comma
r_sizeof
(paren
id|srvaddr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|srvaddr.sin_addr.s_addr
op_eq
id|INADDR_ANY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: mount program didn&squot;t pass remote address!&bslash;n&quot;
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Which protocol do we use? */
id|tcp
op_assign
(paren
id|data-&gt;flags
op_amp
id|NFS_MOUNT_TCP
)paren
suffix:semicolon
multiline_comment|/* Initialize timeout values */
id|timeparms.to_initval
op_assign
id|data-&gt;timeo
op_star
id|HZ
op_div
l_int|10
suffix:semicolon
id|timeparms.to_retries
op_assign
id|data-&gt;retrans
suffix:semicolon
id|timeparms.to_maxval
op_assign
id|tcp
ques
c_cond
id|RPC_MAX_TCP_TIMEOUT
suffix:colon
id|RPC_MAX_UDP_TIMEOUT
suffix:semicolon
id|timeparms.to_exponential
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Choose authentication flavor */
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|NFS_MOUNT_SECURE
)paren
(brace
id|authflavor
op_assign
id|RPC_AUTH_DES
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data-&gt;flags
op_amp
id|NFS_MOUNT_KERBEROS
)paren
(brace
id|authflavor
op_assign
id|RPC_AUTH_KRB
suffix:semicolon
)brace
r_else
(brace
id|authflavor
op_assign
id|RPC_AUTH_UNIX
suffix:semicolon
)brace
multiline_comment|/* Now create transport and client */
id|xprt
op_assign
id|xprt_create_proto
c_func
(paren
id|tcp
ques
c_cond
id|IPPROTO_TCP
suffix:colon
id|IPPROTO_UDP
comma
op_amp
id|srvaddr
comma
op_amp
id|timeparms
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xprt
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: cannot create RPC transport.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failure
suffix:semicolon
)brace
id|clnt
op_assign
id|rpc_create_client
c_func
(paren
id|xprt
comma
id|server-&gt;hostname
comma
op_amp
id|nfs_program
comma
id|NFS_VERSION
comma
id|authflavor
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clnt
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NFS: cannot create RPC client.&bslash;n&quot;
)paren
suffix:semicolon
id|xprt_destroy
c_func
(paren
id|xprt
)paren
suffix:semicolon
r_goto
id|failure
suffix:semicolon
)brace
id|clnt-&gt;cl_intr
op_assign
(paren
id|data-&gt;flags
op_amp
id|NFS_MOUNT_INTR
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|clnt-&gt;cl_softrtry
op_assign
(paren
id|data-&gt;flags
op_amp
id|NFS_MOUNT_SOFT
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|clnt-&gt;cl_chatty
op_assign
l_int|1
suffix:semicolon
id|server-&gt;client
op_assign
id|clnt
suffix:semicolon
multiline_comment|/* Fire up rpciod if not yet running */
id|rpciod_up
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Unlock super block and try to get root fh attributes */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|nfs_fhget
c_func
(paren
id|sb
comma
op_amp
id|data-&gt;root
comma
l_int|NULL
)paren
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_root
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* We&squot;re airborne */
r_if
c_cond
(paren
op_logical_neg
(paren
id|server-&gt;flags
op_amp
id|NFS_MOUNT_NONLM
)paren
)paren
id|lockd_up
c_func
(paren
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
)brace
multiline_comment|/* Yargs. It didn&squot;t work out. */
id|printk
c_func
(paren
l_string|&quot;nfs_read_super: get root inode failed&bslash;n&quot;
)paren
suffix:semicolon
id|rpc_shutdown_client
c_func
(paren
id|server-&gt;client
)paren
suffix:semicolon
id|rpciod_down
c_func
(paren
)paren
suffix:semicolon
id|failure
suffix:colon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_lock
)paren
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_static
r_int
DECL|function|nfs_statfs
id|nfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|statfs
op_star
id|buf
comma
r_int
id|bufsiz
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|nfs_fsinfo
id|res
suffix:semicolon
r_struct
id|statfs
id|tmp
suffix:semicolon
id|error
op_assign
id|nfs_proc_statfs
c_func
(paren
op_amp
id|sb-&gt;u.nfs_sb.s_server
comma
op_amp
id|sb-&gt;u.nfs_sb.s_root
comma
op_amp
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_statfs: statfs error = %d&bslash;n&quot;
comma
op_minus
id|error
)paren
suffix:semicolon
id|res.bsize
op_assign
id|res.blocks
op_assign
id|res.bfree
op_assign
id|res.bavail
op_assign
l_int|0
suffix:semicolon
)brace
id|tmp.f_type
op_assign
id|NFS_SUPER_MAGIC
suffix:semicolon
id|tmp.f_bsize
op_assign
id|res.bsize
suffix:semicolon
id|tmp.f_blocks
op_assign
id|res.blocks
suffix:semicolon
id|tmp.f_bfree
op_assign
id|res.bfree
suffix:semicolon
id|tmp.f_bavail
op_assign
id|res.bavail
suffix:semicolon
id|tmp.f_files
op_assign
l_int|0
suffix:semicolon
id|tmp.f_ffree
op_assign
l_int|0
suffix:semicolon
id|tmp.f_namelen
op_assign
id|NAME_MAX
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|tmp
comma
id|bufsiz
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is our own version of iget that looks up inodes by file handle&n; * instead of inode number.  We use this technique instead of using&n; * the vfs read_inode function because there is no way to pass the&n; * file handle or current attributes into the read_inode function.&n; * We just have to be careful not to subvert iget&squot;s special handling&n; * of mount points.&n; */
r_struct
id|inode
op_star
DECL|function|nfs_fhget
id|nfs_fhget
c_func
(paren
r_struct
id|super_block
op_star
id|sb
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
id|nfs_fattr
id|newfattr
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|inode
op_star
id|inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_fhget: super block is NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|fattr
)paren
(brace
id|error
op_assign
id|nfs_proc_getattr
c_func
(paren
op_amp
id|sb-&gt;u.nfs_sb.s_server
comma
id|fhandle
comma
op_amp
id|newfattr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_fhget: getattr error = %d&bslash;n&quot;
comma
op_minus
id|error
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|fattr
op_assign
op_amp
id|newfattr
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|inode
op_assign
id|iget
c_func
(paren
id|sb
comma
id|fattr-&gt;fileid
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_fhget: iget failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_eq
id|sb-&gt;s_dev
)paren
(brace
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_ne
id|fattr-&gt;fileid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;nfs_fhget: unexpected inode from iget&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
op_star
id|NFS_FH
c_func
(paren
id|inode
)paren
op_assign
op_star
id|fhandle
suffix:semicolon
id|nfs_refresh_inode
c_func
(paren
id|inode
comma
id|fattr
)paren
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;NFS: fhget(%x/%ld ct=%d)&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|inode-&gt;i_count
)paren
suffix:semicolon
r_return
id|inode
suffix:semicolon
)brace
r_int
DECL|function|nfs_notify_change
id|nfs_notify_change
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|iattr
op_star
id|attr
)paren
(brace
r_struct
id|nfs_sattr
id|sattr
suffix:semicolon
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_int
id|error
suffix:semicolon
id|sattr.mode
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MODE
)paren
id|sattr.mode
op_assign
id|attr-&gt;ia_mode
suffix:semicolon
id|sattr.uid
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_UID
)paren
id|sattr.uid
op_assign
id|attr-&gt;ia_uid
suffix:semicolon
id|sattr.gid
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_GID
)paren
id|sattr.gid
op_assign
id|attr-&gt;ia_gid
suffix:semicolon
id|sattr.size
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_SIZE
)paren
op_logical_and
id|S_ISREG
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
id|sattr.size
op_assign
id|attr-&gt;ia_size
suffix:semicolon
id|sattr.mtime.seconds
op_assign
id|sattr.mtime.useconds
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_MTIME
)paren
(brace
id|sattr.mtime.seconds
op_assign
id|attr-&gt;ia_mtime
suffix:semicolon
id|sattr.mtime.useconds
op_assign
l_int|0
suffix:semicolon
)brace
id|sattr.atime.seconds
op_assign
id|sattr.atime.useconds
op_assign
(paren
id|u32
)paren
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|attr-&gt;ia_valid
op_amp
id|ATTR_ATIME
)paren
(brace
id|sattr.atime.seconds
op_assign
id|attr-&gt;ia_atime
suffix:semicolon
id|sattr.atime.useconds
op_assign
l_int|0
suffix:semicolon
)brace
id|error
op_assign
id|nfs_proc_setattr
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
op_amp
id|sattr
comma
op_amp
id|fattr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|nfs_truncate_dirty_pages
c_func
(paren
id|inode
comma
id|sattr.size
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
)brace
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Externally visible revalidation function&n; */
r_int
DECL|function|nfs_revalidate
id|nfs_revalidate
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_return
id|nfs_revalidate_inode
c_func
(paren
id|NFS_SERVER
c_func
(paren
id|inode
)paren
comma
id|inode
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called whenever some part of NFS notices that&n; * the cached attributes have to be refreshed.&n; *&n; * This is a bit tricky because we have to make sure all dirty pages&n; * have been sent off to the server before calling invalidate_inode_pages.&n; * To make sure no other process adds more write requests while we try&n; * our best to flush them, we make them sleep during the attribute refresh.&n; *&n; * A very similar scenario holds for the dir cache.&n; */
r_int
DECL|function|_nfs_revalidate_inode
id|_nfs_revalidate_inode
c_func
(paren
r_struct
id|nfs_server
op_star
id|server
comma
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|nfs_fattr
id|fattr
suffix:semicolon
r_int
id|status
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
id|dfprintk
c_func
(paren
id|PAGECACHE
comma
l_string|&quot;NFS: revalidating %x/%ld inode&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
id|NFS_READTIME
c_func
(paren
id|inode
)paren
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_assign
id|nfs_proc_getattr
c_func
(paren
id|server
comma
id|NFS_FH
c_func
(paren
id|inode
)paren
comma
op_amp
id|fattr
)paren
)paren
OL
l_int|0
)paren
r_goto
id|done
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
r_if
c_cond
(paren
id|fattr.mtime.seconds
op_ne
id|NFS_OLDMTIME
c_func
(paren
id|inode
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|S_ISDIR
c_func
(paren
id|inode-&gt;i_mode
)paren
)paren
(brace
multiline_comment|/* This sends off all dirty pages off to the server.&n;&t;&t;&t; * Note that this function must not sleep. */
id|nfs_invalidate_pages
c_func
(paren
id|inode
)paren
suffix:semicolon
id|invalidate_inode_pages
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
id|nfs_invalidate_dircache
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|NFS_OLDMTIME
c_func
(paren
id|inode
)paren
op_assign
id|fattr.mtime.seconds
suffix:semicolon
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
op_assign
id|NFS_MINATTRTIMEO
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Update attrtimeo value */
r_if
c_cond
(paren
(paren
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
op_lshift_assign
l_int|1
)paren
OG
id|NFS_MAXATTRTIMEO
c_func
(paren
id|inode
)paren
)paren
id|NFS_ATTRTIMEO
c_func
(paren
id|inode
)paren
op_assign
id|NFS_MAXATTRTIMEO
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|status
op_assign
l_int|0
suffix:semicolon
id|done
suffix:colon
id|dfprintk
c_func
(paren
id|PAGECACHE
comma
l_string|&quot;NFS: inode %x/%ld revalidation complete (status %d).&bslash;n&quot;
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n; * File system information&n; */
DECL|variable|nfs_fs_type
r_static
r_struct
id|file_system_type
id|nfs_fs_type
op_assign
(brace
l_string|&quot;nfs&quot;
comma
l_int|0
multiline_comment|/* FS_NO_DCACHE - this doesn&squot;t work right now*/
comma
id|nfs_read_super
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * Initialize NFS&n; */
r_int
DECL|function|init_nfs_fs
id|init_nfs_fs
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|rpc_proc_register
c_func
(paren
op_amp
id|nfs_rpcstat
)paren
suffix:semicolon
macro_line|#endif
r_return
id|register_filesystem
c_func
(paren
op_amp
id|nfs_fs_type
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Every kernel module contains stuff like this.&n; */
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
multiline_comment|/* Not quite true; I just maintain it */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Olaf Kirch &lt;okir@monad.swb.de&gt;&quot;
)paren
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|init_nfs_fs
c_func
(paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PROC_FS
id|rpc_proc_unregister
c_func
(paren
l_string|&quot;nfs&quot;
)paren
suffix:semicolon
macro_line|#endif
id|unregister_filesystem
c_func
(paren
op_amp
id|nfs_fs_type
)paren
suffix:semicolon
id|nfs_free_dircache
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
