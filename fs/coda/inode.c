multiline_comment|/*&n; * Super block/filesystem wide operations&n; *&n; * Copryright (C) 1996 Peter J. Braam &lt;braam@maths.ox.ac.uk&gt; and &n; * Michael Callahan &lt;callahan@maths.ox.ac.uk&gt; &n; * &n; * Rewritten for Linux 2.1.  Peter Braam &lt;braam@cs.cmu.edu&gt;&n; * Copyright (C) Carnegie Mellon University&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_fs_i.h&gt;
macro_line|#include &lt;linux/coda_cache.h&gt;
multiline_comment|/* VFS super_block ops */
r_static
r_struct
id|super_block
op_star
id|coda_read_super
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
r_static
r_void
id|coda_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|coda_put_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|coda_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_static
r_void
id|coda_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_static
r_int
id|coda_statfs
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
)paren
suffix:semicolon
multiline_comment|/* exported operations */
DECL|variable|coda_super_operations
r_struct
id|super_operations
id|coda_super_operations
op_assign
(brace
id|read_inode
suffix:colon
id|coda_read_inode
comma
id|put_inode
suffix:colon
id|coda_put_inode
comma
id|delete_inode
suffix:colon
id|coda_delete_inode
comma
id|put_super
suffix:colon
id|coda_put_super
comma
id|statfs
suffix:colon
id|coda_statfs
comma
)brace
suffix:semicolon
DECL|function|coda_read_super
r_static
r_struct
id|super_block
op_star
id|coda_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_void
op_star
id|data
comma
r_int
id|silent
)paren
(brace
r_struct
id|inode
op_star
id|psdev
op_assign
l_int|0
comma
op_star
id|root
op_assign
l_int|0
suffix:semicolon
r_struct
id|coda_sb_info
op_star
id|sbi
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|venus_comm
op_star
id|vc
op_assign
l_int|NULL
suffix:semicolon
id|ViceFid
id|fid
suffix:semicolon
id|kdev_t
id|dev
op_assign
id|sb-&gt;s_dev
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ENTRY
suffix:semicolon
id|vc
op_assign
op_amp
id|coda_upc_comm
suffix:semicolon
id|sbi
op_assign
op_amp
id|coda_super_info
suffix:semicolon
r_if
c_cond
(paren
id|sbi-&gt;sbi_sb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Already mounted&bslash;n&quot;
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sbi-&gt;sbi_sb
op_assign
id|sb
suffix:semicolon
id|sbi-&gt;sbi_psdev
op_assign
id|psdev
suffix:semicolon
id|sbi-&gt;sbi_vcomm
op_assign
id|vc
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
(paren
id|sbi-&gt;sbi_cchead
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
(paren
id|sbi-&gt;sbi_volroothead
)paren
)paren
suffix:semicolon
id|sb-&gt;u.generic_sbp
op_assign
id|sbi
suffix:semicolon
id|sb-&gt;s_blocksize
op_assign
l_int|1024
suffix:semicolon
multiline_comment|/* XXXXX  what do we put here?? */
id|sb-&gt;s_blocksize_bits
op_assign
l_int|10
suffix:semicolon
id|sb-&gt;s_magic
op_assign
id|CODA_SUPER_MAGIC
suffix:semicolon
id|sb-&gt;s_dev
op_assign
id|dev
suffix:semicolon
id|sb-&gt;s_op
op_assign
op_amp
id|coda_super_operations
suffix:semicolon
multiline_comment|/* get root fid from Venus: this needs the root inode */
id|error
op_assign
id|venus_rootfid
c_func
(paren
id|sb
comma
op_amp
id|fid
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
l_string|&quot;coda_read_super: coda_get_rootfid failed with %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: rootfid is %s&bslash;n&quot;
comma
id|coda_f2s
c_func
(paren
op_amp
id|fid
)paren
)paren
suffix:semicolon
multiline_comment|/* make root inode */
id|error
op_assign
id|coda_cnode_make
c_func
(paren
op_amp
id|root
comma
op_amp
id|fid
comma
id|sb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_logical_or
op_logical_neg
id|root
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Failure of coda_cnode_make for root: error %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
r_goto
id|error
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;coda_read_super: rootinode is %ld dev %d&bslash;n&quot;
comma
id|root-&gt;i_ino
comma
id|root-&gt;i_dev
)paren
suffix:semicolon
id|sbi-&gt;sbi_root
op_assign
id|root
suffix:semicolon
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|root
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|error
suffix:colon
id|EXIT
suffix:semicolon
r_if
c_cond
(paren
id|sbi
)paren
(brace
id|sbi-&gt;sbi_vcomm
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;sbi_root
op_assign
l_int|NULL
suffix:semicolon
id|sbi-&gt;sbi_sb
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|root
)paren
(brace
id|iput
c_func
(paren
id|root
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|coda_put_super
r_static
r_void
id|coda_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_struct
id|coda_sb_info
op_star
id|sb_info
suffix:semicolon
id|ENTRY
suffix:semicolon
id|coda_cache_clear_all
c_func
(paren
id|sb
)paren
suffix:semicolon
id|sb_info
op_assign
id|coda_sbp
c_func
(paren
id|sb
)paren
suffix:semicolon
id|coda_super_info.sbi_sb
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Coda: Bye bye.&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sb_info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|sb_info
)paren
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
)brace
multiline_comment|/* all filling in of inodes postponed until lookup */
DECL|function|coda_read_inode
r_static
r_void
id|coda_read_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
id|ENTRY
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|cii-&gt;c_magic
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|coda_put_inode
r_static
r_void
id|coda_put_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
id|ENTRY
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_INODE
comma
l_string|&quot;ino: %ld, count %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
op_eq
l_int|1
)paren
(brace
id|write_inode_now
c_func
(paren
id|inode
)paren
suffix:semicolon
id|inode-&gt;i_nlink
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|coda_delete_inode
r_static
r_void
id|coda_delete_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
)paren
(brace
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|inode
op_star
id|open_inode
suffix:semicolon
id|ENTRY
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot; inode-&gt;ino: %ld, count: %d&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|atomic_read
c_func
(paren
op_amp
id|inode-&gt;i_count
)paren
)paren
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inode-&gt;i_ino
op_eq
id|CTL_INO
op_logical_or
id|cii-&gt;c_magic
op_ne
id|CODA_CNODE_MAGIC
)paren
(brace
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|list_empty
c_func
(paren
op_amp
id|cii-&gt;c_volrootlist
)paren
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|cii-&gt;c_volrootlist
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|cii-&gt;c_volrootlist
)paren
suffix:semicolon
)brace
id|open_inode
op_assign
id|cii-&gt;c_ovp
suffix:semicolon
r_if
c_cond
(paren
id|open_inode
)paren
(brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;DELINO cached file: ino %ld count %d.&bslash;n&quot;
comma
id|open_inode-&gt;i_ino
comma
id|atomic_read
c_func
(paren
op_amp
id|open_inode-&gt;i_count
)paren
)paren
suffix:semicolon
id|cii-&gt;c_ovp
op_assign
l_int|NULL
suffix:semicolon
id|inode-&gt;i_mapping
op_assign
op_amp
id|inode-&gt;i_data
suffix:semicolon
id|iput
c_func
(paren
id|open_inode
)paren
suffix:semicolon
)brace
id|coda_cache_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CDEBUG
c_func
(paren
id|D_DOWNCALL
comma
l_string|&quot;clearing inode: %ld, %x&bslash;n&quot;
comma
id|inode-&gt;i_ino
comma
id|cii-&gt;c_flags
)paren
suffix:semicolon
id|inode-&gt;u.coda_i.c_magic
op_assign
l_int|0
suffix:semicolon
id|clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
)brace
DECL|function|coda_notify_change
r_int
id|coda_notify_change
c_func
(paren
r_struct
id|dentry
op_star
id|de
comma
r_struct
id|iattr
op_star
id|iattr
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|de-&gt;d_inode
suffix:semicolon
r_struct
id|coda_inode_info
op_star
id|cii
suffix:semicolon
r_struct
id|coda_vattr
id|vattr
suffix:semicolon
r_int
id|error
suffix:semicolon
id|ENTRY
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|vattr
comma
l_int|0
comma
r_sizeof
(paren
id|vattr
)paren
)paren
suffix:semicolon
id|cii
op_assign
id|ITOC
c_func
(paren
id|inode
)paren
suffix:semicolon
id|CHECK_CNODE
c_func
(paren
id|cii
)paren
suffix:semicolon
id|coda_iattr_to_vattr
c_func
(paren
id|iattr
comma
op_amp
id|vattr
)paren
suffix:semicolon
id|vattr.va_type
op_assign
id|C_VNON
suffix:semicolon
multiline_comment|/* cannot set type */
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;vattr.va_mode %o&bslash;n&quot;
comma
id|vattr.va_mode
)paren
suffix:semicolon
id|error
op_assign
id|venus_setattr
c_func
(paren
id|inode-&gt;i_sb
comma
op_amp
id|cii-&gt;c_fid
comma
op_amp
id|vattr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
(brace
id|coda_vattr_to_iattr
c_func
(paren
id|inode
comma
op_amp
id|vattr
)paren
suffix:semicolon
id|coda_cache_clear_inode
c_func
(paren
id|inode
)paren
suffix:semicolon
)brace
id|CDEBUG
c_func
(paren
id|D_SUPER
comma
l_string|&quot;inode.i_mode %o, error %d&bslash;n&quot;
comma
id|inode-&gt;i_mode
comma
id|error
)paren
suffix:semicolon
id|EXIT
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|coda_statfs
r_static
r_int
id|coda_statfs
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
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|venus_statfs
c_func
(paren
id|sb
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
multiline_comment|/* fake something like AFS does */
id|buf-&gt;f_blocks
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_files
op_assign
l_int|9000000
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
l_int|9000000
suffix:semicolon
)brace
multiline_comment|/* and fill in the rest */
id|buf-&gt;f_type
op_assign
id|CODA_SUPER_MAGIC
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|1024
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
id|CODA_MAXNAMLEN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* init_coda: used by filesystems.c to register coda */
id|DECLARE_FSTYPE
c_func
(paren
id|coda_fs_type
comma
l_string|&quot;coda&quot;
comma
id|coda_read_super
comma
l_int|0
)paren
suffix:semicolon
DECL|function|init_coda_fs
r_int
id|init_coda_fs
c_func
(paren
r_void
)paren
(brace
r_return
id|register_filesystem
c_func
(paren
op_amp
id|coda_fs_type
)paren
suffix:semicolon
)brace
eof
