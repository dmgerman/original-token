multiline_comment|/*&n; *  linux/fs/ufs/ufs_super.c&n; *&n; * Copyright (C) 1996&n; * Adrian Rodriguez (adrian@franklins-tower.rutgers.edu)&n; * Laboratory for Computer Science Research Computing Facility&n; * Rutgers, The State University of New Jersey&n; *&n; * Copyright (C) 1996  Eddie C. Dost  (ecd@skynet.be)&n; *&n; */
multiline_comment|/*&n; * Kernel module support added on 96/04/26 by&n; * Stefan Reinauer &lt;stepan@home.culture.mipt.ru&gt;&n; *&n; * Module usage counts added on 96/04/29 by&n; * Gertjan van Wingerde &lt;gertjan@cs.vu.nl&gt;&n; *&n; * Clean swab support on 19970406 by&n; * Francois-Rene Rideau &lt;rideau@ens.fr&gt;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ufs_fs.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;ufs_swab.h&quot;
r_struct
id|super_block
op_star
id|ufs_read_super
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
suffix:semicolon
r_void
id|ufs_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
r_int
id|ufs_statfs
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
id|bufsize
)paren
suffix:semicolon
DECL|variable|ufs_super_ops
r_static
r_struct
id|super_operations
id|ufs_super_ops
op_assign
(brace
id|ufs_read_inode
comma
l_int|NULL
comma
multiline_comment|/* XXX - ufs_write_inode() */
id|ufs_put_inode
comma
l_int|NULL
comma
multiline_comment|/* XXX - ufs_delete_inode() */
l_int|NULL
comma
multiline_comment|/* notify_change() */
id|ufs_put_super
comma
l_int|NULL
comma
multiline_comment|/* XXX - ufs_write_super() */
id|ufs_statfs
comma
l_int|NULL
comma
multiline_comment|/* XXX - ufs_remount() */
)brace
suffix:semicolon
DECL|variable|ufs_fs_type
r_static
r_struct
id|file_system_type
id|ufs_fs_type
op_assign
(brace
l_string|&quot;ufs&quot;
comma
id|FS_REQUIRES_DEV
comma
id|ufs_read_super
comma
l_int|NULL
)brace
suffix:semicolon
r_int
DECL|function|init_ufs_fs
id|init_ufs_fs
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
id|ufs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|init_ufs_fs
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_filesystem
c_func
(paren
op_amp
id|ufs_fs_type
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|error_buf
r_static
r_char
id|error_buf
(braket
l_int|1024
)braket
suffix:semicolon
DECL|function|ufs_warning
r_void
id|ufs_warning
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_const
r_char
op_star
id|function
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
id|va_start
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
(paren
id|error_buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|va_end
(paren
id|args
)paren
suffix:semicolon
id|printk
(paren
id|KERN_WARNING
l_string|&quot;UFS warning (device %s): %s: %s&bslash;n&quot;
comma
id|kdevname
c_func
(paren
id|sb-&gt;s_dev
)paren
comma
id|function
comma
id|error_buf
)paren
suffix:semicolon
)brace
macro_line|#if 0 /* unused */
r_static
r_void
id|ufs_print_super_stuff
c_func
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|ufs_superblock
op_star
id|usb
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fs_sblkno: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_sblkno
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_size: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_ncg: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_ncg
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_bsize: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_bsize
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_frag: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_frag
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_nindir: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_nindir
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_inopb: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_inopb
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_optim: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_optim
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_ncyl: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_ncyl
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_state: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_state
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_magic: 0x%8.8x&bslash;n&quot;
comma
id|usb-&gt;fs_magic
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fs_fsmnt: `%s&squot;&bslash;n&quot;
comma
id|usb-&gt;fs_fsmnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
r_struct
id|super_block
op_star
DECL|function|ufs_read_super
id|ufs_read_super
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
id|ufs_superblock
op_star
id|usb
suffix:semicolon
multiline_comment|/* normalized to local byteorder */
r_struct
id|buffer_head
op_star
id|bh1
comma
op_star
id|bh2
suffix:semicolon
id|__u32
id|bytesex
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* sb-&gt;s_dev and sb-&gt;s_flags are set by our caller&n;&t; * data is the mystery argument to sys_mount()&n;&t; *&n;&t; * Our caller also sets s_dev, s_covered, s_rd_only, s_dirt,&n;&t; *   and s_type when we return.&n;&t; */
id|MOD_INC_USE_COUNT
suffix:semicolon
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* XXX - make everything read only for testing */
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh1
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
id|UFS_SBLOCK
op_div
id|BLOCK_SIZE
comma
id|BLOCK_SIZE
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|bh2
op_assign
id|bread
c_func
(paren
id|sb-&gt;s_dev
comma
(paren
id|UFS_SBLOCK
op_plus
id|BLOCK_SIZE
)paren
op_div
id|BLOCK_SIZE
comma
id|BLOCK_SIZE
)paren
)paren
)paren
(brace
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;ufs_read_super: unable to read superblock&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|ufs_read_super_lose
suffix:semicolon
)brace
multiline_comment|/* XXX - redo this so we can free it later... */
id|usb
op_assign
(paren
r_struct
id|ufs_superblock
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb
op_eq
l_int|NULL
)paren
(brace
id|brelse
c_func
(paren
id|bh1
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh2
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;ufs_read_super: get_free_page() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|ufs_read_super_lose
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|usb
comma
id|bh1-&gt;b_data
comma
id|BLOCK_SIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|usb
op_plus
id|BLOCK_SIZE
comma
id|bh2-&gt;b_data
comma
r_sizeof
(paren
r_struct
id|ufs_superblock
)paren
op_minus
id|BLOCK_SIZE
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
id|bh2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|le32_to_cpup
c_func
(paren
op_amp
id|usb-&gt;fs_magic
)paren
)paren
(brace
r_case
id|UFS_MAGIC
suffix:colon
id|bytesex
op_assign
id|UFS_LITTLE_ENDIAN
suffix:semicolon
id|ufs_superblock_le_to_cpus
c_func
(paren
id|usb
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_CIGAM
suffix:colon
id|bytesex
op_assign
id|UFS_BIG_ENDIAN
suffix:semicolon
id|ufs_superblock_be_to_cpus
c_func
(paren
id|usb
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* usb is now normalized to local byteorder */
r_default
suffix:colon
id|printk
(paren
l_string|&quot;ufs_read_super: bad magic number 0x%8.8x &quot;
l_string|&quot;on dev %d/%d&bslash;n&quot;
comma
id|usb-&gt;fs_magic
comma
id|MAJOR
c_func
(paren
id|sb-&gt;s_dev
)paren
comma
id|MINOR
c_func
(paren
id|sb-&gt;s_dev
)paren
)paren
suffix:semicolon
r_goto
id|ufs_read_super_lose
suffix:semicolon
)brace
multiline_comment|/* We found a UFS filesystem on this device. */
multiline_comment|/* XXX - parse args */
r_if
c_cond
(paren
id|usb-&gt;fs_bsize
op_ne
id|UFS_BSIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs_bsize %d != %d&bslash;n&quot;
comma
id|usb-&gt;fs_bsize
comma
id|UFS_BSIZE
)paren
suffix:semicolon
r_goto
id|ufs_read_super_lose
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usb-&gt;fs_fsize
op_ne
id|UFS_FSIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs_fsize %d != %d&bslash;n&quot;
comma
id|usb-&gt;fs_fsize
comma
id|UFS_FSIZE
)paren
suffix:semicolon
r_goto
id|ufs_read_super_lose
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_UFS_SUPER
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs last mounted on &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|usb-&gt;fs_fsmnt
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|usb-&gt;fs_state
op_eq
id|UFS_FSOK
op_minus
id|usb-&gt;fs_time
)paren
(brace
r_switch
c_cond
(paren
id|usb-&gt;fs_clean
)paren
(brace
r_case
id|UFS_FSCLEAN
suffix:colon
macro_line|#ifdef DEBUG_UFS_SUPER
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs is clean&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|UFS_FSSTABLE
suffix:colon
macro_line|#ifdef DEBUG_UFS_SUPER
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs is stable&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_case
id|UFS_FSACTIVE
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs is active&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UFS_FSBAD
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs is bad&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: can&squot;t grok fs_clean 0x%x&bslash;n&quot;
comma
id|usb-&gt;fs_clean
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: fs needs fsck&bslash;n&quot;
)paren
suffix:semicolon
id|sb-&gt;s_flags
op_or_assign
id|MS_RDONLY
suffix:semicolon
multiline_comment|/* XXX - make it read only or barf if it&squot;s not (/, /usr) */
)brace
multiline_comment|/* XXX - sanity check sb fields */
multiline_comment|/* KRR - Why are we not using fs_bsize for blocksize? */
id|sb-&gt;s_blocksize
op_assign
id|usb-&gt;fs_fsize
suffix:semicolon
id|sb-&gt;s_blocksize_bits
op_assign
id|usb-&gt;fs_fshift
suffix:semicolon
multiline_comment|/* XXX - sb-&gt;s_lock */
id|sb-&gt;s_op
op_assign
op_amp
id|ufs_super_ops
suffix:semicolon
id|sb-&gt;dq_op
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX */
id|sb-&gt;s_magic
op_assign
id|usb-&gt;fs_magic
suffix:semicolon
multiline_comment|/* sb-&gt;s_time */
multiline_comment|/* sb-&gt;s_wait */
multiline_comment|/* XXX - sb-&gt;u.ufs_sb */
id|sb-&gt;u.ufs_sb.s_raw_sb
op_assign
id|usb
suffix:semicolon
multiline_comment|/* XXX - maybe move this to the top */
id|sb-&gt;u.ufs_sb.s_flags
op_assign
id|bytesex
op_or
id|UFS_DEBUG_INITIAL
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_ncg
op_assign
id|usb-&gt;fs_ncg
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_ipg
op_assign
id|usb-&gt;fs_ipg
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_fpg
op_assign
id|usb-&gt;fs_fpg
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_fsize
op_assign
id|usb-&gt;fs_fsize
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_fmask
op_assign
id|usb-&gt;fs_fmask
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_fshift
op_assign
id|usb-&gt;fs_fshift
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_bsize
op_assign
id|usb-&gt;fs_bsize
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_bmask
op_assign
id|usb-&gt;fs_bmask
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_bshift
op_assign
id|usb-&gt;fs_bshift
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_iblkno
op_assign
id|usb-&gt;fs_iblkno
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_dblkno
op_assign
id|usb-&gt;fs_dblkno
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_cgoffset
op_assign
id|usb-&gt;fs_cgoffset
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_cgmask
op_assign
id|usb-&gt;fs_cgmask
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_inopb
op_assign
id|usb-&gt;fs_inopb
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_lshift
op_assign
id|usb-&gt;fs_bshift
op_minus
id|usb-&gt;fs_fshift
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_lmask
op_assign
op_complement
(paren
(paren
id|usb-&gt;fs_fmask
op_minus
id|usb-&gt;fs_bmask
)paren
op_rshift
id|usb-&gt;fs_fshift
)paren
suffix:semicolon
id|sb-&gt;u.ufs_sb.s_fsfrag
op_assign
id|usb-&gt;fs_frag
suffix:semicolon
multiline_comment|/* XXX - rename this later */
id|sb-&gt;s_root
op_assign
id|d_alloc_root
c_func
(paren
id|iget
c_func
(paren
id|sb
comma
id|UFS_ROOTINO
)paren
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_UFS_SUPER
id|printk
c_func
(paren
l_string|&quot;ufs_read_super: inopb %u&bslash;n&quot;
comma
id|sb-&gt;u.ufs_sb.s_inopb
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * XXX - read cg structs?&n;&t; */
id|unlock_super
c_func
(paren
id|sb
)paren
suffix:semicolon
r_return
id|sb
suffix:semicolon
id|ufs_read_super_lose
suffix:colon
multiline_comment|/* XXX - clean up */
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|ufs_put_super
r_void
id|ufs_put_super
(paren
r_struct
id|super_block
op_star
id|sb
)paren
(brace
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_put_super&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX */
)brace
id|lock_super
(paren
id|sb
)paren
suffix:semicolon
multiline_comment|/* XXX - sync fs data, set state to ok, and flush buffers */
id|sb-&gt;s_dev
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX - free allocated kernel memory */
multiline_comment|/* includes freeing usb page */
id|unlock_super
(paren
id|sb
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|ufs_statfs
r_int
id|ufs_statfs
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
r_struct
id|statfs
id|tmp
suffix:semicolon
r_struct
id|statfs
op_star
id|sp
op_assign
op_amp
id|tmp
suffix:semicolon
r_struct
id|ufs_superblock
op_star
id|fsb
op_assign
id|sb-&gt;u.ufs_sb.s_raw_sb
suffix:semicolon
multiline_comment|/* fsb was already normalized during mounting */
r_int
r_int
id|used
comma
id|avail
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;u.ufs_sb.s_flags
op_amp
id|UFS_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ufs_statfs&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* XXX */
)brace
id|sp-&gt;f_type
op_assign
id|sb-&gt;s_magic
suffix:semicolon
id|sp-&gt;f_bsize
op_assign
id|sb-&gt;s_blocksize
suffix:semicolon
id|sp-&gt;f_blocks
op_assign
id|fsb-&gt;fs_dsize
suffix:semicolon
id|sp-&gt;f_bfree
op_assign
id|fsb-&gt;fs_cstotal.cs_nbfree
op_star
id|fsb-&gt;fs_frag
op_plus
id|fsb-&gt;fs_cstotal.cs_nffree
suffix:semicolon
id|avail
op_assign
id|sp-&gt;f_blocks
op_minus
(paren
id|sp-&gt;f_blocks
op_div
l_int|100
)paren
op_star
id|fsb-&gt;fs_minfree
suffix:semicolon
id|used
op_assign
id|sp-&gt;f_blocks
op_minus
id|sp-&gt;f_bfree
suffix:semicolon
r_if
c_cond
(paren
id|avail
OG
id|used
)paren
id|sp-&gt;f_bavail
op_assign
id|avail
op_minus
id|used
suffix:semicolon
r_else
id|sp-&gt;f_bavail
op_assign
l_int|0
suffix:semicolon
id|sp-&gt;f_files
op_assign
id|sb-&gt;u.ufs_sb.s_ncg
op_star
id|sb-&gt;u.ufs_sb.s_ipg
suffix:semicolon
id|sp-&gt;f_ffree
op_assign
id|fsb-&gt;fs_cstotal.cs_nifree
suffix:semicolon
id|sp-&gt;f_fsid.val
(braket
l_int|0
)braket
op_assign
id|fsb-&gt;fs_id
(braket
l_int|0
)braket
suffix:semicolon
id|sp-&gt;f_fsid.val
(braket
l_int|1
)braket
op_assign
id|fsb-&gt;fs_id
(braket
l_int|1
)braket
suffix:semicolon
id|sp-&gt;f_namelen
op_assign
id|UFS_MAXNAMLEN
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
id|buf
comma
id|sp
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
eof
