multiline_comment|/*&n; *  linux/fs/hpfs/super.c&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  mouning, unmounting, error handling&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;hpfs_fn.h&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* Mark the filesystem dirty, so that chkdsk checks it when os/2 booted */
DECL|function|mark_dirty
r_static
r_void
id|mark_dirty
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;s_hpfs_chkdsk
op_logical_and
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|hpfs_spare_block
op_star
id|sb
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sb
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
l_int|17
comma
op_amp
id|bh
comma
l_int|0
)paren
)paren
)paren
(brace
id|sb-&gt;dirty
op_assign
l_int|1
suffix:semicolon
id|sb-&gt;old_wrote
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Mark the filesystem clean (mark it dirty for chkdsk if chkdsk==2 or if there&n;   were errors) */
DECL|function|unmark_dirty
r_static
r_void
id|unmark_dirty
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|hpfs_spare_block
op_star
id|sb
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sb
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
l_int|17
comma
op_amp
id|bh
comma
l_int|0
)paren
)paren
)paren
(brace
id|sb-&gt;dirty
op_assign
id|s-&gt;s_hpfs_chkdsk
OG
l_int|1
op_minus
id|s-&gt;s_hpfs_was_error
suffix:semicolon
id|sb-&gt;old_wrote
op_assign
id|s-&gt;s_hpfs_chkdsk
op_ge
l_int|2
op_logical_and
op_logical_neg
id|s-&gt;s_hpfs_was_error
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Filesystem error... */
DECL|macro|ERR_BUF_SIZE
mdefine_line|#define ERR_BUF_SIZE 1024
DECL|function|hpfs_error
r_void
id|hpfs_error
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_char
op_star
id|m
comma
dot
dot
dot
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
id|va_list
id|l
suffix:semicolon
id|va_start
c_func
(paren
id|l
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
op_assign
id|kmalloc
c_func
(paren
id|ERR_BUF_SIZE
comma
id|GFP_KERNEL
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: No memory for error message &squot;%s&squot;&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|vsprintf
c_func
(paren
id|buf
comma
id|m
comma
id|l
)paren
op_ge
id|ERR_BUF_SIZE
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: Grrrr... Kernel memory corrupted ... going on, but it&squot;ll crash very soon :-(&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HPFS: filesystem error: &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|buf
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|m
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_hpfs_was_error
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;s_hpfs_err
op_eq
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;; crashing the system because you wanted it&bslash;n&quot;
)paren
suffix:semicolon
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;HPFS panic&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_hpfs_err
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
id|printk
c_func
(paren
l_string|&quot;; already mounted read-only&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;; remounting read-only&bslash;n&quot;
)paren
suffix:semicolon
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
id|printk
c_func
(paren
l_string|&quot;; going on - but anything won&squot;t be destroyed because it&squot;s read-only&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;; corrupted filesystem mounted read/write - your computer will explode within 20 seconds ... but you wanted it so!&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf
)paren
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|s-&gt;s_hpfs_was_error
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* &n; * A little trick to detect cycles in many hpfs structures and don&squot;t let the&n; * kernel crash on corrupted filesystem. When first called, set c2 to 0.&n; *&n; * BTW. chkdsk doesn&squot;t detect cycles correctly. When I had 2 lost directories&n; * nested each in other, chkdsk locked up happilly.&n; */
DECL|function|hpfs_stop_cycles
r_int
id|hpfs_stop_cycles
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
id|key
comma
r_int
op_star
id|c1
comma
r_int
op_star
id|c2
comma
r_char
op_star
id|msg
)paren
(brace
r_if
c_cond
(paren
op_star
id|c2
op_logical_and
op_star
id|c1
op_eq
id|key
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;cycle detected on key %08x in %s&quot;
comma
id|key
comma
id|msg
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
(paren
op_star
id|c2
)paren
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
op_star
id|c2
op_minus
l_int|1
)paren
op_amp
op_star
id|c2
)paren
)paren
op_star
id|c1
op_assign
id|key
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_put_super
r_void
id|hpfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|s-&gt;s_hpfs_cp_table
)paren
id|kfree
c_func
(paren
id|s-&gt;s_hpfs_cp_table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_hpfs_bmp_dir
)paren
id|kfree
c_func
(paren
id|s-&gt;s_hpfs_bmp_dir
)paren
suffix:semicolon
id|unmark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
)brace
DECL|function|hpfs_count_one_bitmap
r_int
id|hpfs_count_one_bitmap
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|secno
id|secno
)paren
(brace
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
op_star
id|bits
suffix:semicolon
r_int
id|i
comma
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bits
op_assign
id|hpfs_map_4sectors
c_func
(paren
id|s
comma
id|secno
comma
op_amp
id|qbh
comma
l_int|4
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
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
l_int|2048
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|b
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bits
(braket
id|i
)braket
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
id|bits
(braket
id|i
)braket
suffix:semicolon
id|b
suffix:semicolon
id|b
op_rshift_assign
l_int|1
)paren
id|count
op_add_assign
id|b
op_amp
l_int|1
suffix:semicolon
)brace
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|count_bitmaps
r_static
r_int
id|count_bitmaps
c_func
(paren
r_struct
id|super_block
op_star
id|s
)paren
(brace
r_int
id|n
comma
id|count
comma
id|n_bands
suffix:semicolon
id|n_bands
op_assign
(paren
id|s-&gt;s_hpfs_fs_size
op_plus
l_int|0x3fff
)paren
op_rshift
l_int|14
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|n_bands
suffix:semicolon
id|n
op_increment
)paren
id|count
op_add_assign
id|hpfs_count_one_bitmap
c_func
(paren
id|s
comma
id|s-&gt;s_hpfs_bmp_dir
(braket
id|n
)braket
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|hpfs_statfs
r_int
id|hpfs_statfs
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_struct
id|statfs
op_star
id|buf
)paren
(brace
multiline_comment|/*if (s-&gt;s_hpfs_n_free == -1) {*/
id|s-&gt;s_hpfs_n_free
op_assign
id|count_bitmaps
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;s_hpfs_n_free_dnodes
op_assign
id|hpfs_count_one_bitmap
c_func
(paren
id|s
comma
id|s-&gt;s_hpfs_dmap
)paren
suffix:semicolon
multiline_comment|/*}*/
id|buf-&gt;f_type
op_assign
id|s-&gt;s_magic
suffix:semicolon
id|buf-&gt;f_bsize
op_assign
l_int|512
suffix:semicolon
id|buf-&gt;f_blocks
op_assign
id|s-&gt;s_hpfs_fs_size
suffix:semicolon
id|buf-&gt;f_bfree
op_assign
id|s-&gt;s_hpfs_n_free
suffix:semicolon
id|buf-&gt;f_bavail
op_assign
id|s-&gt;s_hpfs_n_free
suffix:semicolon
id|buf-&gt;f_files
op_assign
id|s-&gt;s_hpfs_dirband_size
op_div
l_int|4
suffix:semicolon
id|buf-&gt;f_ffree
op_assign
id|s-&gt;s_hpfs_n_free_dnodes
suffix:semicolon
id|buf-&gt;f_namelen
op_assign
l_int|254
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Super operations */
DECL|variable|hpfs_sops
r_static
r_struct
id|super_operations
id|hpfs_sops
op_assign
(brace
id|read_inode
suffix:colon
id|hpfs_read_inode
comma
id|delete_inode
suffix:colon
id|hpfs_delete_inode
comma
id|put_super
suffix:colon
id|hpfs_put_super
comma
id|statfs
suffix:colon
id|hpfs_statfs
comma
id|remount_fs
suffix:colon
id|hpfs_remount_fs
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * A tiny parser for option strings, stolen from dosfs.&n; *&n; * Stolen again from read-only hpfs.&n; */
DECL|function|parse_opts
r_int
id|parse_opts
c_func
(paren
r_char
op_star
id|opts
comma
id|uid_t
op_star
id|uid
comma
id|gid_t
op_star
id|gid
comma
id|umode_t
op_star
id|umask
comma
r_int
op_star
id|lowercase
comma
r_int
op_star
id|conv
comma
r_int
op_star
id|eas
comma
r_int
op_star
id|chk
comma
r_int
op_star
id|errs
comma
r_int
op_star
id|chkdsk
comma
r_int
op_star
id|timeshift
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|rhs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opts
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*printk(&quot;Parsing opts: &squot;%s&squot;&bslash;n&quot;,opts);*/
r_for
c_loop
(paren
id|p
op_assign
id|strtok
c_func
(paren
id|opts
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|p
op_ne
l_int|0
suffix:semicolon
id|p
op_assign
id|strtok
c_func
(paren
l_int|0
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
(paren
id|rhs
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot;=&squot;
)paren
)paren
op_ne
l_int|0
)paren
op_star
id|rhs
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;help&quot;
)paren
)paren
r_return
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;uid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rhs
op_logical_or
op_logical_neg
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|uid
op_assign
id|simple_strtoul
c_func
(paren
id|rhs
comma
op_amp
id|rhs
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;gid&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rhs
op_logical_or
op_logical_neg
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|gid
op_assign
id|simple_strtoul
c_func
(paren
id|rhs
comma
op_amp
id|rhs
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;umask&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|rhs
op_logical_or
op_logical_neg
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|umask
op_assign
id|simple_strtoul
c_func
(paren
id|rhs
comma
op_amp
id|rhs
comma
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;timeshift&quot;
)paren
)paren
(brace
r_int
id|m
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rhs
op_logical_or
op_logical_neg
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
op_eq
l_char|&squot;-&squot;
)paren
id|m
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
op_eq
l_char|&squot;+&squot;
op_logical_or
op_star
id|rhs
op_eq
l_char|&squot;-&squot;
)paren
id|rhs
op_increment
suffix:semicolon
op_star
id|timeshift
op_assign
id|simple_strtoul
c_func
(paren
id|rhs
comma
op_amp
id|rhs
comma
l_int|0
)paren
op_star
id|m
suffix:semicolon
r_if
c_cond
(paren
op_star
id|rhs
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;case&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;lower&quot;
)paren
)paren
op_star
id|lowercase
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;asis&quot;
)paren
)paren
op_star
id|lowercase
op_assign
l_int|0
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;conv&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;binary&quot;
)paren
)paren
op_star
id|conv
op_assign
id|CONV_BINARY
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;text&quot;
)paren
)paren
op_star
id|conv
op_assign
id|CONV_TEXT
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;auto&quot;
)paren
)paren
op_star
id|conv
op_assign
id|CONV_AUTO
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;check&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;none&quot;
)paren
)paren
op_star
id|chk
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;normal&quot;
)paren
)paren
op_star
id|chk
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;strict&quot;
)paren
)paren
op_star
id|chk
op_assign
l_int|2
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;errors&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;continue&quot;
)paren
)paren
op_star
id|errs
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;remount-ro&quot;
)paren
)paren
op_star
id|errs
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;panic&quot;
)paren
)paren
op_star
id|errs
op_assign
l_int|2
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;eas&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;no&quot;
)paren
)paren
op_star
id|eas
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;ro&quot;
)paren
)paren
op_star
id|eas
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;rw&quot;
)paren
)paren
op_star
id|eas
op_assign
l_int|2
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|p
comma
l_string|&quot;chkdsk&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;no&quot;
)paren
)paren
op_star
id|chkdsk
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;errors&quot;
)paren
)paren
op_star
id|chkdsk
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|rhs
comma
l_string|&quot;always&quot;
)paren
)paren
op_star
id|chkdsk
op_assign
l_int|2
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|hpfs_help
r_static
r_inline
r_void
id|hpfs_help
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;HPFS filesystem options:&bslash;n&bslash;&n;      help              do not mount and display this text&bslash;n&bslash;&n;      uid=xxx           set uid of files that don&squot;t have uid specified in eas&bslash;n&bslash;&n;      gid=xxx           set gid of files that don&squot;t have gid specified in eas&bslash;n&bslash;&n;      umask=xxx         set mode of files that don&squot;t have mode specified in eas&bslash;n&bslash;&n;      case=lower        lowercase all files&bslash;n&bslash;&n;      case=asis         do not lowercase files (default)&bslash;n&bslash;&n;      conv=binary       do not convert CR/LF -&gt; LF (default)&bslash;n&bslash;&n;      conv=auto         convert only files with known text extensions&bslash;n&bslash;&n;      conv=text         convert all files&bslash;n&bslash;&n;      check=none        no fs checks - kernel may crash on corrupted filesystem&bslash;n&bslash;&n;      check=normal      do some checks - it should not crash (default)&bslash;n&bslash;&n;      check=strict      do extra time-consuming checks, used for debugging&bslash;n&bslash;&n;      errors=continue   continue on errors&bslash;n&bslash;&n;      errors=remount-ro remount read-only if errors found (default)&bslash;n&bslash;&n;      errors=panic      panic on errors&bslash;n&bslash;&n;      chkdsk=no         do not mark fs for chkdsking even if there were errors&bslash;n&bslash;&n;      chkdsk=errors     mark fs dirty if errors found (default)&bslash;n&bslash;&n;      chkdsk=always     always mark fs dirty - used for debugging&bslash;n&bslash;&n;      eas=no            ignore extended attributes&bslash;n&bslash;&n;      eas=ro            read but do not write extended attributes&bslash;n&bslash;&n;      eas=rw            r/w eas =&gt; enables chmod, chown, mknod, ln -s (default)&bslash;n&bslash;&n;      timeshift=nnn&t;add nnn seconds to file times&bslash;n&bslash;&n;&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|hpfs_remount_fs
r_int
id|hpfs_remount_fs
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_int
op_star
id|flags
comma
r_char
op_star
id|data
)paren
(brace
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
id|umode_t
id|umask
suffix:semicolon
r_int
id|lowercase
comma
id|conv
comma
id|eas
comma
id|chk
comma
id|errs
comma
id|chkdsk
comma
id|timeshift
suffix:semicolon
r_int
id|o
suffix:semicolon
op_star
id|flags
op_or_assign
id|MS_NOATIME
suffix:semicolon
id|uid
op_assign
id|s-&gt;s_hpfs_uid
suffix:semicolon
id|gid
op_assign
id|s-&gt;s_hpfs_gid
suffix:semicolon
id|umask
op_assign
l_int|0777
op_amp
op_complement
id|s-&gt;s_hpfs_mode
suffix:semicolon
id|lowercase
op_assign
id|s-&gt;s_hpfs_lowercase
suffix:semicolon
id|conv
op_assign
id|s-&gt;s_hpfs_conv
suffix:semicolon
id|eas
op_assign
id|s-&gt;s_hpfs_eas
suffix:semicolon
id|chk
op_assign
id|s-&gt;s_hpfs_chk
suffix:semicolon
id|chkdsk
op_assign
id|s-&gt;s_hpfs_chkdsk
suffix:semicolon
id|errs
op_assign
id|s-&gt;s_hpfs_err
suffix:semicolon
id|timeshift
op_assign
id|s-&gt;s_hpfs_timeshift
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o
op_assign
id|parse_opts
c_func
(paren
id|data
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|umask
comma
op_amp
id|lowercase
comma
op_amp
id|conv
comma
op_amp
id|eas
comma
op_amp
id|chk
comma
op_amp
id|errs
comma
op_amp
id|chkdsk
comma
op_amp
id|timeshift
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: bad mount options.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o
op_eq
l_int|2
)paren
(brace
id|hpfs_help
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|timeshift
op_ne
id|s-&gt;s_hpfs_timeshift
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: timeshift can&squot;t be changed using remount.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|unmark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
id|s-&gt;s_hpfs_uid
op_assign
id|uid
suffix:semicolon
id|s-&gt;s_hpfs_gid
op_assign
id|gid
suffix:semicolon
id|s-&gt;s_hpfs_mode
op_assign
l_int|0777
op_amp
op_complement
id|umask
suffix:semicolon
id|s-&gt;s_hpfs_lowercase
op_assign
id|lowercase
suffix:semicolon
id|s-&gt;s_hpfs_conv
op_assign
id|conv
suffix:semicolon
id|s-&gt;s_hpfs_eas
op_assign
id|eas
suffix:semicolon
id|s-&gt;s_hpfs_chk
op_assign
id|chk
suffix:semicolon
id|s-&gt;s_hpfs_chkdsk
op_assign
id|chkdsk
suffix:semicolon
id|s-&gt;s_hpfs_err
op_assign
id|errs
suffix:semicolon
id|s-&gt;s_hpfs_timeshift
op_assign
id|timeshift
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|flags
op_amp
id|MS_RDONLY
)paren
)paren
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hpfs_read_super
r_struct
id|super_block
op_star
id|hpfs_read_super
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
r_void
op_star
id|options
comma
r_int
id|silent
)paren
(brace
id|kdev_t
id|dev
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh0
comma
op_star
id|bh1
comma
op_star
id|bh2
suffix:semicolon
r_struct
id|hpfs_boot_block
op_star
id|bootblock
suffix:semicolon
r_struct
id|hpfs_super_block
op_star
id|superblock
suffix:semicolon
r_struct
id|hpfs_spare_block
op_star
id|spareblock
suffix:semicolon
id|uid_t
id|uid
suffix:semicolon
id|gid_t
id|gid
suffix:semicolon
id|umode_t
id|umask
suffix:semicolon
r_int
id|lowercase
comma
id|conv
comma
id|eas
comma
id|chk
comma
id|errs
comma
id|chkdsk
comma
id|timeshift
suffix:semicolon
id|dnode_secno
id|root_dno
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|de
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|quad_buffer_head
id|qbh
suffix:semicolon
r_int
id|o
suffix:semicolon
id|s-&gt;s_hpfs_bmp_dir
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;s_hpfs_cp_table
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;s_hpfs_creation_de_lock
op_assign
id|s-&gt;s_hpfs_rd_inode
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|s-&gt;s_hpfs_creation_de
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|s-&gt;s_hpfs_iget_q
)paren
suffix:semicolon
id|uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|gid
op_assign
id|current-&gt;gid
suffix:semicolon
id|umask
op_assign
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|lowercase
op_assign
l_int|0
suffix:semicolon
id|conv
op_assign
id|CONV_BINARY
suffix:semicolon
id|eas
op_assign
l_int|2
suffix:semicolon
id|chk
op_assign
l_int|1
suffix:semicolon
id|errs
op_assign
l_int|1
suffix:semicolon
id|chkdsk
op_assign
l_int|1
suffix:semicolon
id|timeshift
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|o
op_assign
id|parse_opts
c_func
(paren
id|options
comma
op_amp
id|uid
comma
op_amp
id|gid
comma
op_amp
id|umask
comma
op_amp
id|lowercase
comma
op_amp
id|conv
comma
op_amp
id|eas
comma
op_amp
id|chk
comma
op_amp
id|errs
comma
op_amp
id|chkdsk
comma
op_amp
id|timeshift
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: bad mount options.&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|o
op_eq
l_int|2
)paren
(brace
id|hpfs_help
c_func
(paren
)paren
suffix:semicolon
r_goto
id|bail0
suffix:semicolon
)brace
multiline_comment|/*s-&gt;s_hpfs_mounting = 1;*/
id|dev
op_assign
id|s-&gt;s_dev
suffix:semicolon
id|set_blocksize
c_func
(paren
id|dev
comma
l_int|512
)paren
suffix:semicolon
id|s-&gt;s_hpfs_fs_size
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bootblock
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
l_int|0
comma
op_amp
id|bh0
comma
l_int|0
)paren
)paren
)paren
r_goto
id|bail1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|superblock
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
l_int|16
comma
op_amp
id|bh1
comma
l_int|1
)paren
)paren
)paren
r_goto
id|bail2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|spareblock
op_assign
id|hpfs_map_sector
c_func
(paren
id|s
comma
l_int|17
comma
op_amp
id|bh2
comma
l_int|0
)paren
)paren
)paren
r_goto
id|bail3
suffix:semicolon
multiline_comment|/* Check magics */
r_if
c_cond
(paren
multiline_comment|/*bootblock-&gt;magic != BB_MAGIC&n;&t;    ||*/
id|superblock-&gt;magic
op_ne
id|SB_MAGIC
op_logical_or
id|spareblock-&gt;magic
op_ne
id|SP_MAGIC
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|silent
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: Bad magic ... probably not HPFS&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
multiline_comment|/* Check version */
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
op_logical_and
id|superblock-&gt;funcversion
op_ne
l_int|2
op_logical_and
id|superblock-&gt;funcversion
op_ne
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: Bad version %d,%d. Mount readonly to go around&bslash;n&quot;
comma
(paren
r_int
)paren
id|superblock-&gt;version
comma
(paren
r_int
)paren
id|superblock-&gt;funcversion
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HPFS: please try recent version of HPFS driver at http://artax.karlin.mff.cuni.cz/~mikulas/vyplody/hpfs/index-e.cgi and if it still can&squot;t understand this format, contact author - mikulas@artax.karlin.mff.cuni.cz&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|s-&gt;s_flags
op_or_assign
id|MS_NOATIME
suffix:semicolon
multiline_comment|/* Fill superblock stuff */
id|s-&gt;s_magic
op_assign
id|HPFS_SUPER_MAGIC
suffix:semicolon
id|s-&gt;s_blocksize
op_assign
l_int|512
suffix:semicolon
id|s-&gt;s_blocksize_bits
op_assign
l_int|9
suffix:semicolon
id|s-&gt;s_op
op_assign
op_amp
id|hpfs_sops
suffix:semicolon
id|s-&gt;s_hpfs_root
op_assign
id|superblock-&gt;root
suffix:semicolon
id|s-&gt;s_hpfs_fs_size
op_assign
id|superblock-&gt;n_sectors
suffix:semicolon
id|s-&gt;s_hpfs_bitmaps
op_assign
id|superblock-&gt;bitmaps
suffix:semicolon
id|s-&gt;s_hpfs_dirband_start
op_assign
id|superblock-&gt;dir_band_start
suffix:semicolon
id|s-&gt;s_hpfs_dirband_size
op_assign
id|superblock-&gt;n_dir_band
suffix:semicolon
id|s-&gt;s_hpfs_dmap
op_assign
id|superblock-&gt;dir_band_bitmap
suffix:semicolon
id|s-&gt;s_hpfs_uid
op_assign
id|uid
suffix:semicolon
id|s-&gt;s_hpfs_gid
op_assign
id|gid
suffix:semicolon
id|s-&gt;s_hpfs_mode
op_assign
l_int|0777
op_amp
op_complement
id|umask
suffix:semicolon
id|s-&gt;s_hpfs_n_free
op_assign
op_minus
l_int|1
suffix:semicolon
id|s-&gt;s_hpfs_n_free_dnodes
op_assign
op_minus
l_int|1
suffix:semicolon
id|s-&gt;s_hpfs_lowercase
op_assign
id|lowercase
suffix:semicolon
id|s-&gt;s_hpfs_conv
op_assign
id|conv
suffix:semicolon
id|s-&gt;s_hpfs_eas
op_assign
id|eas
suffix:semicolon
id|s-&gt;s_hpfs_chk
op_assign
id|chk
suffix:semicolon
id|s-&gt;s_hpfs_chkdsk
op_assign
id|chkdsk
suffix:semicolon
id|s-&gt;s_hpfs_err
op_assign
id|errs
suffix:semicolon
id|s-&gt;s_hpfs_timeshift
op_assign
id|timeshift
suffix:semicolon
id|s-&gt;s_hpfs_was_error
op_assign
l_int|0
suffix:semicolon
id|s-&gt;s_hpfs_cp_table
op_assign
l_int|NULL
suffix:semicolon
id|s-&gt;s_hpfs_c_bitmap
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Load bitmap directory */
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_hpfs_bmp_dir
op_assign
id|hpfs_load_bitmap_directory
c_func
(paren
id|s
comma
id|superblock-&gt;bitmaps
)paren
)paren
)paren
r_goto
id|bail4
suffix:semicolon
multiline_comment|/* Check for general fs errors*/
r_if
c_cond
(paren
id|spareblock-&gt;dirty
op_logical_and
op_logical_neg
id|spareblock-&gt;old_wrote
)paren
(brace
r_if
c_cond
(paren
id|errs
op_eq
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: Improperly stopped, not mounted&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;improperly stopped&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_flags
op_amp
id|MS_RDONLY
)paren
)paren
(brace
id|spareblock-&gt;dirty
op_assign
l_int|1
suffix:semicolon
id|spareblock-&gt;old_wrote
op_assign
l_int|0
suffix:semicolon
id|mark_buffer_dirty
c_func
(paren
id|bh2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spareblock-&gt;hotfixes_used
op_logical_or
id|spareblock-&gt;n_spares_used
)paren
(brace
r_if
c_cond
(paren
id|errs
op_ge
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: Hotfixes not supported here, try chkdsk&bslash;n&quot;
)paren
suffix:semicolon
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;hotfixes not supported here, try chkdsk&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errs
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: Proceeding, but your filesystem will be probably corrupted by this driver...&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
l_string|&quot;HPFS: This driver may read bad files or crash when operating on disk with hotfixes.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|spareblock-&gt;n_dnode_spares
op_ne
id|spareblock-&gt;n_dnode_spares_free
)paren
(brace
r_if
c_cond
(paren
id|errs
op_ge
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: Spare dnodes used, try chkdsk&bslash;n&quot;
)paren
suffix:semicolon
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;warning: spare dnodes used, try chkdsk&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errs
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: Proceeding, but your filesystem could be corrupted if you delete files or directories&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chk
)paren
(brace
r_int
id|a
suffix:semicolon
r_if
c_cond
(paren
id|superblock-&gt;dir_band_end
op_minus
id|superblock-&gt;dir_band_start
op_plus
l_int|1
op_ne
id|superblock-&gt;n_dir_band
op_logical_or
id|superblock-&gt;dir_band_end
template_param
l_int|0x4000
)paren
(brace
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;dir band size mismatch: dir_band_start==%08x, dir_band_end==%08x, n_dir_band==%08x&quot;
comma
id|superblock-&gt;dir_band_start
comma
id|superblock-&gt;dir_band_end
comma
id|superblock-&gt;n_dir_band
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|a
op_assign
id|s-&gt;s_hpfs_dirband_size
suffix:semicolon
id|s-&gt;s_hpfs_dirband_size
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|superblock-&gt;dir_band_start
comma
id|superblock-&gt;n_dir_band
comma
l_string|&quot;dir_band&quot;
)paren
op_logical_or
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|superblock-&gt;dir_band_bitmap
comma
l_int|4
comma
l_string|&quot;dir_band_bitmap&quot;
)paren
op_logical_or
id|hpfs_chk_sectors
c_func
(paren
id|s
comma
id|superblock-&gt;bitmaps
comma
l_int|4
comma
l_string|&quot;bitmaps&quot;
)paren
)paren
(brace
id|mark_dirty
c_func
(paren
id|s
)paren
suffix:semicolon
r_goto
id|bail4
suffix:semicolon
)brace
id|s-&gt;s_hpfs_dirband_size
op_assign
id|a
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;HPFS: You really don&squot;t want any checks? You are crazy...&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Load code page table */
r_if
c_cond
(paren
id|spareblock-&gt;n_code_pages
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|s-&gt;s_hpfs_cp_table
op_assign
id|hpfs_load_code_page
c_func
(paren
id|s
comma
id|spareblock-&gt;code_page_dir
)paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;HPFS: Warning: code page support is disabled&bslash;n&quot;
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh0
)paren
suffix:semicolon
id|hpfs_lock_iget
c_func
(paren
id|s
comma
l_int|1
)paren
suffix:semicolon
id|s-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|s
comma
id|s-&gt;s_hpfs_root
)paren
)paren
suffix:semicolon
id|hpfs_unlock_iget
c_func
(paren
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|s-&gt;s_root
op_logical_or
op_logical_neg
id|s-&gt;s_root-&gt;d_inode
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;HPFS: iget failed. Why???&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|bail0
suffix:semicolon
)brace
id|hpfs_set_dentry_operations
c_func
(paren
id|s-&gt;s_root
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * find the root directory&squot;s . pointer &amp; finish filling in the inode&n;&t; */
id|root_dno
op_assign
id|hpfs_fnode_dno
c_func
(paren
id|s
comma
id|s-&gt;s_hpfs_root
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root_dno
)paren
id|de
op_assign
id|map_dirent
c_func
(paren
id|s-&gt;s_root-&gt;d_inode
comma
id|root_dno
comma
l_string|&quot;&bslash;001&bslash;001&quot;
comma
l_int|2
comma
l_int|NULL
comma
op_amp
id|qbh
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_dno
op_logical_or
op_logical_neg
id|de
)paren
id|hpfs_error
c_func
(paren
id|s
comma
l_string|&quot;unable to find root dir&quot;
)paren
suffix:semicolon
r_else
(brace
id|s-&gt;s_root-&gt;d_inode-&gt;i_atime
op_assign
id|local_to_gmt
c_func
(paren
id|s
comma
id|de-&gt;read_date
)paren
suffix:semicolon
id|s-&gt;s_root-&gt;d_inode-&gt;i_mtime
op_assign
id|local_to_gmt
c_func
(paren
id|s
comma
id|de-&gt;write_date
)paren
suffix:semicolon
id|s-&gt;s_root-&gt;d_inode-&gt;i_ctime
op_assign
id|local_to_gmt
c_func
(paren
id|s
comma
id|de-&gt;creation_date
)paren
suffix:semicolon
id|s-&gt;s_root-&gt;d_inode-&gt;i_hpfs_ea_size
op_assign
id|de-&gt;ea_size
suffix:semicolon
id|s-&gt;s_root-&gt;d_inode-&gt;i_hpfs_parent_dir
op_assign
id|s-&gt;s_root-&gt;d_inode-&gt;i_ino
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root-&gt;d_inode-&gt;i_size
op_eq
op_minus
l_int|1
)paren
id|s-&gt;s_root-&gt;d_inode-&gt;i_size
op_assign
l_int|2048
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_root-&gt;d_inode-&gt;i_blocks
op_eq
op_minus
l_int|1
)paren
id|s-&gt;s_root-&gt;d_inode-&gt;i_blocks
op_assign
l_int|5
suffix:semicolon
)brace
r_if
c_cond
(paren
id|de
)paren
id|hpfs_brelse4
c_func
(paren
op_amp
id|qbh
)paren
suffix:semicolon
r_return
id|s
suffix:semicolon
id|bail4
suffix:colon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|bail3
suffix:colon
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|bail2
suffix:colon
id|brelse
c_func
(paren
id|bh0
)paren
suffix:semicolon
id|bail1
suffix:colon
id|bail0
suffix:colon
r_if
c_cond
(paren
id|s-&gt;s_hpfs_bmp_dir
)paren
id|kfree
c_func
(paren
id|s-&gt;s_hpfs_bmp_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s-&gt;s_hpfs_cp_table
)paren
id|kfree
c_func
(paren
id|s-&gt;s_hpfs_cp_table
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|DECLARE_FSTYPE_DEV
c_func
(paren
id|hpfs_fs_type
comma
l_string|&quot;hpfs&quot;
comma
id|hpfs_read_super
)paren
suffix:semicolon
DECL|function|init_hpfs_fs
r_static
r_int
id|__init
id|init_hpfs_fs
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
id|hpfs_fs_type
)paren
suffix:semicolon
)brace
DECL|function|exit_hpfs_fs
r_static
r_void
id|__exit
id|exit_hpfs_fs
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|hpfs_fs_type
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|module_init
c_func
(paren
id|init_hpfs_fs
)paren
id|module_exit
c_func
(paren
id|exit_hpfs_fs
)paren
eof
