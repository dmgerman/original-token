multiline_comment|/*&n; * linux/fs/nfsd/export.c&n; *&n; * NFS exporting and validation.&n; *&n; * We maintain a list of clients, each of which has a list of&n; * exports. To export an fs to a given client, you first have&n; * to create the client entry with NFSCTL_ADDCLIENT, which&n; * creates a client control block and adds it to the hash&n; * table. Then, you call NFSCTL_EXPORT for each fs.&n; *&n; * You cannot currently read the export information from the&n; * kernel. It would be nice to have a /proc file though.&n; *&n; * Copyright (C) 1995, 1996 Olaf Kirch, &lt;okir@monad.swb.de&gt;&n; */
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/sunrpc/svc.h&gt;
macro_line|#include &lt;linux/nfsd/nfsd.h&gt;
macro_line|#include &lt;linux/nfsd/nfsfh.h&gt;
macro_line|#include &lt;linux/nfsd/syscall.h&gt;
macro_line|#include &lt;linux/lockd/bind.h&gt;
DECL|macro|NFSDDBG_FACILITY
mdefine_line|#define NFSDDBG_FACILITY&t;NFSDDBG_EXPORT
DECL|macro|NFSD_PARANOIA
mdefine_line|#define NFSD_PARANOIA 1
DECL|typedef|svc_client
r_typedef
r_struct
id|svc_client
id|svc_client
suffix:semicolon
DECL|typedef|svc_export
r_typedef
r_struct
id|svc_export
id|svc_export
suffix:semicolon
r_static
id|svc_export
op_star
id|exp_find
c_func
(paren
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
)paren
suffix:semicolon
r_static
id|svc_export
op_star
id|exp_parent
c_func
(paren
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
)paren
suffix:semicolon
r_static
r_void
id|exp_unexport_all
c_func
(paren
id|svc_client
op_star
id|clp
)paren
suffix:semicolon
r_static
r_void
id|exp_do_unexport
c_func
(paren
id|svc_export
op_star
id|unexp
)paren
suffix:semicolon
r_static
id|svc_client
op_star
id|exp_getclientbyname
c_func
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_static
r_void
id|exp_freeclient
c_func
(paren
id|svc_client
op_star
id|clp
)paren
suffix:semicolon
r_static
r_void
id|exp_unhashclient
c_func
(paren
id|svc_client
op_star
id|clp
)paren
suffix:semicolon
r_static
r_int
id|exp_verify_string
c_func
(paren
r_char
op_star
id|cp
comma
r_int
id|max
)paren
suffix:semicolon
DECL|macro|CLIENT_HASHBITS
mdefine_line|#define CLIENT_HASHBITS&t;&t;6
DECL|macro|CLIENT_HASHMAX
mdefine_line|#define CLIENT_HASHMAX&t;&t;(1 &lt;&lt; CLIENT_HASHBITS)
DECL|macro|CLIENT_HASHMASK
mdefine_line|#define CLIENT_HASHMASK&t;&t;(CLIENT_HASHMAX - 1)
DECL|macro|CLIENT_HASH
mdefine_line|#define CLIENT_HASH(a) &bslash;&n;&t;&t;((((a)&gt;&gt;24) ^ ((a)&gt;&gt;16) ^ ((a)&gt;&gt;8) ^(a)) &amp; CLIENT_HASHMASK)
DECL|macro|EXPORT_HASH
mdefine_line|#define EXPORT_HASH(dev)&t;((dev) &amp; (NFSCLNT_EXPMAX - 1))
DECL|struct|svc_clnthash
r_struct
id|svc_clnthash
(brace
DECL|member|h_next
r_struct
id|svc_clnthash
op_star
id|h_next
suffix:semicolon
DECL|member|h_addr
r_struct
id|in_addr
id|h_addr
suffix:semicolon
DECL|member|h_client
r_struct
id|svc_client
op_star
id|h_client
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|clnt_hash
r_static
r_struct
id|svc_clnthash
op_star
id|clnt_hash
(braket
id|CLIENT_HASHMAX
)braket
suffix:semicolon
DECL|variable|clients
r_static
id|svc_client
op_star
id|clients
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|initialized
r_static
r_int
id|initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|hash_lock
r_static
r_int
id|hash_lock
op_assign
l_int|0
suffix:semicolon
DECL|variable|want_lock
r_static
r_int
id|want_lock
op_assign
l_int|0
suffix:semicolon
DECL|variable|hash_count
r_static
r_int
id|hash_count
op_assign
l_int|0
suffix:semicolon
DECL|variable|hash_wait
r_static
r_struct
id|wait_queue
op_star
id|hash_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|READLOCK
mdefine_line|#define READLOCK&t;&t;0
DECL|macro|WRITELOCK
mdefine_line|#define WRITELOCK&t;&t;1
multiline_comment|/*&n; * Find a client&squot;s export for a device.&n; */
r_static
r_inline
id|svc_export
op_star
DECL|function|exp_find
id|exp_find
c_func
(paren
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
)paren
(brace
id|svc_export
op_star
id|exp
suffix:semicolon
id|exp
op_assign
id|clp-&gt;cl_export
(braket
id|EXPORT_HASH
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|exp
op_logical_and
id|exp-&gt;ex_dev
op_ne
id|dev
)paren
id|exp
op_assign
id|exp-&gt;ex_next
suffix:semicolon
r_return
id|exp
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the client&squot;s export entry matching xdev/xino.&n; */
id|svc_export
op_star
DECL|function|exp_get
id|exp_get
c_func
(paren
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
comma
id|ino_t
id|ino
)paren
(brace
id|svc_export
op_star
id|exp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clp
)paren
r_return
l_int|NULL
suffix:semicolon
id|exp
op_assign
id|exp_find
c_func
(paren
id|clp
comma
id|dev
)paren
suffix:semicolon
r_return
(paren
id|exp
op_logical_and
id|exp-&gt;ex_ino
op_eq
id|ino
)paren
ques
c_cond
id|exp
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether there are any exports for a device.&n; */
r_static
r_int
DECL|function|exp_device_in_use
id|exp_device_in_use
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_struct
id|svc_client
op_star
id|clp
suffix:semicolon
r_for
c_loop
(paren
id|clp
op_assign
id|clients
suffix:semicolon
id|clp
suffix:semicolon
id|clp
op_assign
id|clp-&gt;cl_next
)paren
(brace
r_if
c_cond
(paren
id|exp_find
c_func
(paren
id|clp
comma
id|dev
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Look up the device of the parent fs.&n; */
r_static
r_inline
r_int
DECL|function|nfsd_parentdev
id|nfsd_parentdev
c_func
(paren
id|dev_t
op_star
id|devp
)paren
(brace
r_struct
id|super_block
op_star
id|sb
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sb
op_assign
id|get_super
c_func
(paren
op_star
id|devp
)paren
)paren
op_logical_or
op_logical_neg
id|sb-&gt;s_root-&gt;d_covers
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|devp
op_eq
id|sb-&gt;s_root-&gt;d_covers-&gt;d_inode-&gt;i_dev
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|devp
op_assign
id|sb-&gt;s_root-&gt;d_covers-&gt;d_inode-&gt;i_dev
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Find the parent export entry for a given fs. This function is used&n; * only by the export syscall to keep the export tree consistent.&n; */
r_static
id|svc_export
op_star
DECL|function|exp_parent
id|exp_parent
c_func
(paren
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
)paren
(brace
id|svc_export
op_star
id|exp
suffix:semicolon
id|dev_t
id|xdev
op_assign
id|dev
suffix:semicolon
r_do
(brace
id|exp
op_assign
id|exp_find
c_func
(paren
id|clp
comma
id|xdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exp
)paren
r_return
id|exp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|nfsd_parentdev
c_func
(paren
op_amp
id|xdev
)paren
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Export a file system.&n; */
r_int
DECL|function|exp_export
id|exp_export
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|nxp
)paren
(brace
id|svc_client
op_star
id|clp
suffix:semicolon
id|svc_export
op_star
id|exp
comma
op_star
id|parent
suffix:semicolon
id|svc_export
op_star
op_star
id|head
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
comma
id|err
suffix:semicolon
id|dev_t
id|dev
suffix:semicolon
id|ino_t
id|ino
suffix:semicolon
multiline_comment|/* Consistency check */
r_if
c_cond
(paren
op_logical_neg
id|exp_verify_string
c_func
(paren
id|nxp-&gt;ex_path
comma
id|NFS_MAXPATHLEN
)paren
op_logical_or
op_logical_neg
id|exp_verify_string
c_func
(paren
id|nxp-&gt;ex_client
comma
id|NFSCLNT_IDMAX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;exp_export called for %s:%s (%x/%ld fl %x).&bslash;n&quot;
comma
id|nxp-&gt;ex_client
comma
id|nxp-&gt;ex_path
comma
id|nxp-&gt;ex_dev
comma
id|nxp-&gt;ex_ino
comma
id|nxp-&gt;ex_flags
)paren
suffix:semicolon
id|dev
op_assign
id|nxp-&gt;ex_dev
suffix:semicolon
id|ino
op_assign
id|nxp-&gt;ex_ino
suffix:semicolon
multiline_comment|/* Try to lock the export table for update */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|exp_writelock
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Look up client info */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|exp_getclientbyname
c_func
(paren
id|nxp-&gt;ex_client
)paren
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
multiline_comment|/*&n;&t; * If there&squot;s already an export for this file, assume this&n;&t; * is just a flag update.&n;&t; */
r_if
c_cond
(paren
(paren
id|exp
op_assign
id|exp_find
c_func
(paren
id|clp
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Ensure there&squot;s only one export per FS. */
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
r_if
c_cond
(paren
id|exp-&gt;ex_ino
op_eq
id|ino
)paren
(brace
id|exp-&gt;ex_flags
op_assign
id|nxp-&gt;ex_flags
suffix:semicolon
id|exp-&gt;ex_anon_uid
op_assign
id|nxp-&gt;ex_anon_uid
suffix:semicolon
id|exp-&gt;ex_anon_gid
op_assign
id|nxp-&gt;ex_anon_gid
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
)brace
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/* Look up the dentry */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|dentry
op_assign
id|lookup_dentry
c_func
(paren
id|nxp-&gt;ex_path
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|err
op_assign
op_minus
id|ENOENT
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
r_goto
id|finish
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_ne
id|nxp-&gt;ex_dev
op_logical_or
id|inode-&gt;i_ino
op_ne
id|nxp-&gt;ex_ino
)paren
(brace
multiline_comment|/* I&squot;m just being paranoid... */
r_goto
id|finish
suffix:semicolon
)brace
multiline_comment|/* We currently export only dirs. */
id|err
op_assign
op_minus
id|ENOTDIR
suffix:semicolon
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
r_goto
id|finish
suffix:semicolon
multiline_comment|/* If this is a sub-export, must be root of FS */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|parent
op_assign
id|exp_parent
c_func
(paren
id|clp
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_struct
id|super_block
op_star
id|sb
op_assign
id|inode-&gt;i_sb
suffix:semicolon
r_if
c_cond
(paren
id|inode
op_ne
id|sb-&gt;s_root-&gt;d_inode
)paren
(brace
macro_line|#ifdef NFSD_PARANOIA
id|printk
c_func
(paren
l_string|&quot;exp_export: sub-export %s not root of device %s&bslash;n&quot;
comma
id|nxp-&gt;ex_path
comma
id|kdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
macro_line|#endif
r_goto
id|finish
suffix:semicolon
)brace
)brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|exp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|exp
)paren
comma
id|GFP_USER
)paren
)paren
)paren
r_goto
id|finish
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: created export entry %p for client %p&bslash;n&quot;
comma
id|exp
comma
id|clp
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|exp-&gt;ex_path
comma
id|nxp-&gt;ex_path
)paren
suffix:semicolon
id|exp-&gt;ex_client
op_assign
id|clp
suffix:semicolon
id|exp-&gt;ex_parent
op_assign
id|parent
suffix:semicolon
id|exp-&gt;ex_dentry
op_assign
id|dentry
suffix:semicolon
id|exp-&gt;ex_flags
op_assign
id|nxp-&gt;ex_flags
suffix:semicolon
id|exp-&gt;ex_dev
op_assign
id|dev
suffix:semicolon
id|exp-&gt;ex_ino
op_assign
id|ino
suffix:semicolon
id|exp-&gt;ex_anon_uid
op_assign
id|nxp-&gt;ex_anon_uid
suffix:semicolon
id|exp-&gt;ex_anon_gid
op_assign
id|nxp-&gt;ex_anon_gid
suffix:semicolon
multiline_comment|/* Update parent pointers of all exports */
r_if
c_cond
(paren
id|parent
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NFSCLNT_EXPMAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|svc_export
op_star
id|temp
op_assign
id|clp-&gt;cl_export
(braket
id|i
)braket
suffix:semicolon
r_while
c_loop
(paren
id|temp
)paren
(brace
r_if
c_cond
(paren
id|temp-&gt;ex_parent
op_eq
id|parent
)paren
id|temp-&gt;ex_parent
op_assign
id|exp
suffix:semicolon
id|temp
op_assign
id|temp-&gt;ex_next
suffix:semicolon
)brace
)brace
)brace
id|head
op_assign
id|clp-&gt;cl_export
op_plus
id|EXPORT_HASH
c_func
(paren
id|dev
)paren
suffix:semicolon
id|exp-&gt;ex_next
op_assign
op_star
id|head
suffix:semicolon
op_star
id|head
op_assign
id|exp
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Unlock hashtable */
id|out_unlock
suffix:colon
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
multiline_comment|/* Release the dentry */
id|finish
suffix:colon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
multiline_comment|/*&n; * Unexport a file system. The export entry has already&n; * been removed from the client&squot;s list of exported fs&squot;s.&n; */
r_static
r_void
DECL|function|exp_do_unexport
id|exp_do_unexport
c_func
(paren
id|svc_export
op_star
id|unexp
)paren
(brace
id|svc_export
op_star
id|exp
suffix:semicolon
id|svc_client
op_star
id|clp
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
r_int
id|i
suffix:semicolon
multiline_comment|/* Update parent pointers. */
id|clp
op_assign
id|unexp-&gt;ex_client
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
id|NFSCLNT_EXPMAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|exp
op_assign
id|clp-&gt;cl_export
(braket
id|i
)braket
suffix:semicolon
id|exp
suffix:semicolon
id|exp
op_assign
id|exp-&gt;ex_next
)paren
r_if
c_cond
(paren
id|exp-&gt;ex_parent
op_eq
id|unexp
)paren
id|exp-&gt;ex_parent
op_assign
id|unexp-&gt;ex_parent
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check whether this is the last export for this device,&n;&t; * and if so flush any cached dentries.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|exp_device_in_use
c_func
(paren
id|unexp-&gt;ex_dev
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;exp_do_unexport: %s last use, flushing cache&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|unexp-&gt;ex_dev
)paren
)paren
suffix:semicolon
id|nfsd_fh_flush
c_func
(paren
id|unexp-&gt;ex_dev
)paren
suffix:semicolon
)brace
id|dentry
op_assign
id|unexp-&gt;ex_dentry
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
id|unexp-&gt;ex_dev
op_ne
id|inode-&gt;i_dev
op_logical_or
id|unexp-&gt;ex_ino
op_ne
id|inode-&gt;i_ino
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: bad dentry in unexport!&bslash;n&quot;
)paren
suffix:semicolon
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|unexp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Revoke all exports for a given client.&n; * This may look very awkward, but we have to do it this way in order&n; * to avoid race conditions (aka mind the parent pointer).&n; */
r_static
r_void
DECL|function|exp_unexport_all
id|exp_unexport_all
c_func
(paren
id|svc_client
op_star
id|clp
)paren
(brace
id|svc_export
op_star
id|exp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;unexporting all fs&squot;s for clnt %p&bslash;n&quot;
comma
id|clp
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
id|NFSCLNT_EXPMAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|exp
op_assign
id|clp-&gt;cl_export
(braket
id|i
)braket
suffix:semicolon
id|clp-&gt;cl_export
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|exp
)paren
(brace
id|svc_export
op_star
id|next
op_assign
id|exp-&gt;ex_next
suffix:semicolon
id|exp_do_unexport
c_func
(paren
id|exp
)paren
suffix:semicolon
id|exp
op_assign
id|next
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * unexport syscall.&n; */
r_int
DECL|function|exp_unexport
id|exp_unexport
c_func
(paren
r_struct
id|nfsctl_export
op_star
id|nxp
)paren
(brace
id|svc_client
op_star
id|clp
suffix:semicolon
id|svc_export
op_star
op_star
id|expp
comma
op_star
id|exp
op_assign
l_int|NULL
suffix:semicolon
r_int
id|err
suffix:semicolon
multiline_comment|/* Consistency check */
r_if
c_cond
(paren
op_logical_neg
id|exp_verify_string
c_func
(paren
id|nxp-&gt;ex_client
comma
id|NFSCLNT_IDMAX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|exp_writelock
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
id|clp
op_assign
id|exp_getclientbyname
c_func
(paren
id|nxp-&gt;ex_client
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;exp_unexport: found client %s&bslash;n&quot;
comma
id|nxp-&gt;ex_client
)paren
suffix:semicolon
id|expp
op_assign
id|clp-&gt;cl_export
op_plus
id|EXPORT_HASH
c_func
(paren
id|nxp-&gt;ex_dev
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|exp
op_assign
op_star
id|expp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|exp-&gt;ex_dev
op_eq
id|nxp-&gt;ex_dev
)paren
(brace
r_if
c_cond
(paren
id|exp-&gt;ex_ino
op_ne
id|nxp-&gt;ex_ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;exp_unexport: ino mismatch, %ld not %ld&bslash;n&quot;
comma
id|exp-&gt;ex_ino
comma
id|nxp-&gt;ex_ino
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
op_star
id|expp
op_assign
id|exp-&gt;ex_next
suffix:semicolon
id|exp_do_unexport
c_func
(paren
id|exp
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|expp
op_assign
op_amp
(paren
id|exp-&gt;ex_next
)paren
suffix:semicolon
)brace
)brace
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Obtain the root fh on behalf of a client.&n; * This could be done in user space, but I feel that it adds some safety&n; * since its harder to fool a kernel module than a user space program.&n; */
r_int
DECL|function|exp_rootfh
id|exp_rootfh
c_func
(paren
r_struct
id|svc_client
op_star
id|clp
comma
id|dev_t
id|dev
comma
id|ino_t
id|ino
comma
r_struct
id|knfs_fh
op_star
id|f
)paren
(brace
r_struct
id|svc_export
op_star
id|exp
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|svc_fh
id|fh
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
id|dprintk
c_func
(paren
l_string|&quot;nfsd: exp_rootfh(%s:%x/%ld)&bslash;n&quot;
comma
id|clp-&gt;cl_ident
comma
id|dev
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|exp
op_assign
id|exp_get
c_func
(paren
id|clp
comma
id|dev
comma
id|ino
)paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|dentry
op_assign
id|exp-&gt;ex_dentry
suffix:semicolon
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;exp_rootfh: Aieee, NULL d_inode&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|inode-&gt;i_dev
op_ne
id|dev
op_logical_or
id|inode-&gt;i_ino
op_ne
id|ino
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;exp_rootfh: Aieee, ino/dev mismatch&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;exp_rootfh: arg[dev(%x):ino(%ld)] inode[dev(%x):ino(%ld)]&bslash;n&quot;
comma
id|dev
comma
id|ino
comma
id|inode-&gt;i_dev
comma
id|inode-&gt;i_ino
)paren
suffix:semicolon
)brace
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|fh_compose
c_func
(paren
op_amp
id|fh
comma
id|exp
comma
id|dentry
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|f
comma
op_amp
id|fh.fh_handle
comma
r_sizeof
(paren
r_struct
id|knfs_fh
)paren
)paren
suffix:semicolon
id|fh_put
c_func
(paren
op_amp
id|fh
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Hashtable locking. Write locks are placed only by user processes&n; * wanting to modify export information.&n; */
r_void
DECL|function|exp_readlock
id|exp_readlock
c_func
(paren
r_void
)paren
(brace
r_while
c_loop
(paren
id|hash_lock
op_logical_or
id|want_lock
)paren
id|sleep_on
c_func
(paren
op_amp
id|hash_wait
)paren
suffix:semicolon
id|hash_count
op_increment
suffix:semicolon
)brace
r_int
DECL|function|exp_writelock
id|exp_writelock
c_func
(paren
r_void
)paren
(brace
id|want_lock
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|hash_count
op_logical_or
id|hash_lock
)paren
id|interruptible_sleep_on
c_func
(paren
op_amp
id|hash_wait
)paren
suffix:semicolon
id|want_lock
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
id|hash_lock
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|exp_unlock
id|exp_unlock
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|hash_count
)paren
id|hash_count
op_decrement
suffix:semicolon
r_else
id|hash_lock
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|hash_wait
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a valid client given an inet address. We always move the most&n; * recently used client to the front of the hash chain to speed up&n; * future lookups.&n; * Locking against other processes is the responsibility of the caller.&n; */
r_struct
id|svc_client
op_star
DECL|function|exp_getclient
id|exp_getclient
c_func
(paren
r_struct
id|sockaddr_in
op_star
id|sin
)paren
(brace
r_struct
id|svc_clnthash
op_star
op_star
id|hp
comma
op_star
op_star
id|head
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|addr
op_assign
id|sin-&gt;sin_addr.s_addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
r_return
l_int|NULL
suffix:semicolon
id|head
op_assign
op_amp
id|clnt_hash
(braket
id|CLIENT_HASH
c_func
(paren
id|addr
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
id|hp
op_assign
id|head
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|hp
)paren
op_ne
l_int|NULL
suffix:semicolon
id|hp
op_assign
op_amp
(paren
id|tmp-&gt;h_next
)paren
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;h_addr.s_addr
op_eq
id|addr
)paren
(brace
multiline_comment|/* Move client to the front */
r_if
c_cond
(paren
id|head
op_ne
id|hp
)paren
(brace
op_star
id|hp
op_assign
id|tmp-&gt;h_next
suffix:semicolon
id|tmp-&gt;h_next
op_assign
op_star
id|head
suffix:semicolon
op_star
id|head
op_assign
id|tmp
suffix:semicolon
)brace
r_return
id|tmp-&gt;h_client
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Find a client given its identifier.&n; */
r_static
id|svc_client
op_star
DECL|function|exp_getclientbyname
id|exp_getclientbyname
c_func
(paren
r_char
op_star
id|ident
)paren
(brace
id|svc_client
op_star
id|clp
suffix:semicolon
r_for
c_loop
(paren
id|clp
op_assign
id|clients
suffix:semicolon
id|clp
suffix:semicolon
id|clp
op_assign
id|clp-&gt;cl_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|clp-&gt;cl_ident
comma
id|ident
)paren
)paren
r_return
id|clp
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Add or modify a client.&n; * Change requests may involve the list of host addresses. The list of&n; * exports and possibly existing uid maps are left untouched.&n; */
r_int
DECL|function|exp_addclient
id|exp_addclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|ncp
)paren
(brace
r_struct
id|svc_clnthash
op_star
id|ch
(braket
id|NFSCLNT_ADDRMAX
)braket
suffix:semicolon
id|svc_client
op_star
id|clp
suffix:semicolon
r_int
id|i
comma
id|err
comma
id|change
op_assign
l_int|0
comma
id|ilen
suffix:semicolon
multiline_comment|/* First, consistency check. */
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ilen
op_assign
id|exp_verify_string
c_func
(paren
id|ncp-&gt;cl_ident
comma
id|NFSCLNT_IDMAX
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|ncp-&gt;cl_naddr
OG
id|NFSCLNT_ADDRMAX
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* Lock the hashtable */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|exp_writelock
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* First check if this is a change request for a client. */
r_for
c_loop
(paren
id|clp
op_assign
id|clients
suffix:semicolon
id|clp
suffix:semicolon
id|clp
op_assign
id|clp-&gt;cl_next
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|clp-&gt;cl_ident
comma
id|ncp-&gt;cl_ident
)paren
)paren
r_break
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|clp
)paren
(brace
id|change
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|clp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|clp
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|out_unlock
suffix:semicolon
id|memset
c_func
(paren
id|clp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|clp
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;created client %s (%p)&bslash;n&quot;
comma
id|ncp-&gt;cl_ident
comma
id|clp
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|clp-&gt;cl_ident
comma
id|ncp-&gt;cl_ident
)paren
suffix:semicolon
id|clp-&gt;cl_idlen
op_assign
id|ilen
suffix:semicolon
)brace
multiline_comment|/* Allocate hash buckets */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ncp-&gt;cl_naddr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|ch
(braket
id|i
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|svc_clnthash
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch
(braket
id|i
)braket
)paren
(brace
r_while
c_loop
(paren
id|i
op_decrement
)paren
id|kfree
c_func
(paren
id|ch
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|change
)paren
id|kfree
c_func
(paren
id|clp
)paren
suffix:semicolon
r_goto
id|out_unlock
suffix:semicolon
)brace
)brace
multiline_comment|/* Copy addresses. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ncp-&gt;cl_naddr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|clp-&gt;cl_addr
(braket
id|i
)braket
op_assign
id|ncp-&gt;cl_addrlist
(braket
id|i
)braket
suffix:semicolon
)brace
id|clp-&gt;cl_naddr
op_assign
id|ncp-&gt;cl_naddr
suffix:semicolon
multiline_comment|/* Remove old client hash entries. */
r_if
c_cond
(paren
id|change
)paren
id|exp_unhashclient
c_func
(paren
id|clp
)paren
suffix:semicolon
multiline_comment|/* Insert client into hashtable. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ncp-&gt;cl_naddr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|in_addr
id|addr
op_assign
id|clp-&gt;cl_addr
(braket
id|i
)braket
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|hash
op_assign
id|CLIENT_HASH
c_func
(paren
id|addr.s_addr
)paren
suffix:semicolon
id|ch
(braket
id|i
)braket
op_member_access_from_pointer
id|h_client
op_assign
id|clp
suffix:semicolon
id|ch
(braket
id|i
)braket
op_member_access_from_pointer
id|h_addr
op_assign
id|addr
suffix:semicolon
id|ch
(braket
id|i
)braket
op_member_access_from_pointer
id|h_next
op_assign
id|clnt_hash
(braket
id|hash
)braket
suffix:semicolon
id|clnt_hash
(braket
id|hash
)braket
op_assign
id|ch
(braket
id|i
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|change
)paren
(brace
id|clp-&gt;cl_next
op_assign
id|clients
suffix:semicolon
id|clients
op_assign
id|clp
suffix:semicolon
)brace
id|err
op_assign
l_int|0
suffix:semicolon
id|out_unlock
suffix:colon
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Delete a client given an identifier.&n; */
r_int
DECL|function|exp_delclient
id|exp_delclient
c_func
(paren
r_struct
id|nfsctl_client
op_star
id|ncp
)paren
(brace
id|svc_client
op_star
op_star
id|clpp
comma
op_star
id|clp
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|exp_verify_string
c_func
(paren
id|ncp-&gt;cl_ident
comma
id|NFSCLNT_IDMAX
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Lock the hashtable */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|exp_writelock
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
r_for
c_loop
(paren
id|clpp
op_assign
op_amp
id|clients
suffix:semicolon
(paren
id|clp
op_assign
op_star
id|clpp
)paren
suffix:semicolon
id|clpp
op_assign
op_amp
(paren
id|clp-&gt;cl_next
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|ncp-&gt;cl_ident
comma
id|clp-&gt;cl_ident
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|clp
)paren
(brace
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
op_star
id|clpp
op_assign
id|clp-&gt;cl_next
suffix:semicolon
id|exp_freeclient
c_func
(paren
id|clp
)paren
suffix:semicolon
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Free a client. The caller has already removed it from the client list.&n; */
r_static
r_void
DECL|function|exp_freeclient
id|exp_freeclient
c_func
(paren
id|svc_client
op_star
id|clp
)paren
(brace
id|exp_unhashclient
c_func
(paren
id|clp
)paren
suffix:semicolon
multiline_comment|/* umap_free(&amp;(clp-&gt;cl_umap)); */
id|exp_unexport_all
c_func
(paren
id|clp
)paren
suffix:semicolon
id|nfsd_lockd_unexport
c_func
(paren
id|clp
)paren
suffix:semicolon
id|kfree
(paren
id|clp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Remove client from hashtable. We first collect all hashtable&n; * entries and free them in one go.&n; * The hash table must be writelocked by the caller.&n; */
r_static
r_void
DECL|function|exp_unhashclient
id|exp_unhashclient
c_func
(paren
id|svc_client
op_star
id|clp
)paren
(brace
r_struct
id|svc_clnthash
op_star
op_star
id|hpp
comma
op_star
id|hp
comma
op_star
id|ch
(braket
id|NFSCLNT_ADDRMAX
)braket
suffix:semicolon
r_int
id|i
comma
id|count
comma
id|err
suffix:semicolon
id|again
suffix:colon
id|err
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|count
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CLIENT_HASHMAX
op_logical_and
op_logical_neg
id|err
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hpp
op_assign
id|clnt_hash
op_plus
id|i
suffix:semicolon
r_while
c_loop
(paren
(paren
id|hp
op_assign
op_star
id|hpp
)paren
op_logical_and
op_logical_neg
id|err
)paren
(brace
r_if
c_cond
(paren
id|hp-&gt;h_client
op_eq
id|clp
)paren
(brace
op_star
id|hpp
op_assign
id|hp-&gt;h_next
suffix:semicolon
id|ch
(braket
id|count
op_increment
)braket
op_assign
id|hp
suffix:semicolon
id|err
op_assign
(paren
id|count
op_ge
id|NFSCLNT_ADDRMAX
)paren
suffix:semicolon
)brace
r_else
(brace
id|hpp
op_assign
op_amp
(paren
id|hp-&gt;h_next
)paren
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|count
op_ne
id|clp-&gt;cl_naddr
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;nfsd: bad address count in freeclient!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|again
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
id|count
suffix:semicolon
id|i
op_increment
)paren
id|kfree
(paren
id|ch
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Lockd is shutting down and tells us to unregister all clients&n; */
r_void
DECL|function|exp_nlmdetach
id|exp_nlmdetach
c_func
(paren
r_void
)paren
(brace
r_struct
id|svc_client
op_star
id|clp
suffix:semicolon
r_for
c_loop
(paren
id|clp
op_assign
id|clients
suffix:semicolon
id|clp
suffix:semicolon
id|clp
op_assign
id|clp-&gt;cl_next
)paren
id|nfsd_lockd_unexport
c_func
(paren
id|clp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Verify that string is non-empty and does not exceed max length.&n; */
r_static
r_int
DECL|function|exp_verify_string
id|exp_verify_string
c_func
(paren
r_char
op_star
id|cp
comma
r_int
id|max
)paren
(brace
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
id|i
OL
id|max
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|cp
(braket
id|i
)braket
)paren
r_return
id|i
suffix:semicolon
id|cp
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;nfsd: couldn&squot;t validate string %s&bslash;n&quot;
comma
id|cp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the exports module.&n; */
r_void
DECL|function|nfsd_export_init
id|nfsd_export_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: initializing export module.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initialized
)paren
r_return
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
id|CLIENT_HASHMAX
suffix:semicolon
id|i
op_increment
)paren
id|clnt_hash
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|clients
op_assign
l_int|NULL
suffix:semicolon
id|initialized
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Shutdown the exports module.&n; */
r_void
DECL|function|nfsd_export_shutdown
id|nfsd_export_shutdown
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: shutting down export module.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialized
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|exp_writelock
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Weird: hashtable locked in exp_shutdown&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|CLIENT_HASHMAX
suffix:semicolon
id|i
op_increment
)paren
(brace
r_while
c_loop
(paren
id|clnt_hash
(braket
id|i
)braket
)paren
id|exp_freeclient
c_func
(paren
id|clnt_hash
(braket
id|i
)braket
op_member_access_from_pointer
id|h_client
)paren
suffix:semicolon
)brace
id|exp_unlock
c_func
(paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;nfsd: export shutdown complete.&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof
