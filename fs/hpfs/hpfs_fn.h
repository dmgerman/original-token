multiline_comment|/*&n; *  linux/fs/hpfs/hpfs_fn.h&n; *&n; *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999&n; *&n; *  function headers&n; */
singleline_comment|//#define DBG
singleline_comment|//#define DEBUG_LOCKS
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/hpfs_fs.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &quot;hpfs.h&quot;
DECL|macro|memcpy_tofs
mdefine_line|#define memcpy_tofs memcpy
DECL|macro|memcpy_fromfs
mdefine_line|#define memcpy_fromfs memcpy
DECL|macro|EIOERROR
mdefine_line|#define EIOERROR  EIO
DECL|macro|EFSERROR
mdefine_line|#define EFSERROR  EPERM
DECL|macro|EMEMERROR
mdefine_line|#define EMEMERROR ENOMEM
DECL|macro|ANODE_ALLOC_FWD
mdefine_line|#define ANODE_ALLOC_FWD&t;512
DECL|macro|FNODE_ALLOC_FWD
mdefine_line|#define FNODE_ALLOC_FWD&t;0
DECL|macro|ALLOC_FWD_MIN
mdefine_line|#define ALLOC_FWD_MIN&t;16
DECL|macro|ALLOC_FWD_MAX
mdefine_line|#define ALLOC_FWD_MAX&t;128
DECL|macro|ALLOC_M
mdefine_line|#define ALLOC_M&t;&t;1
DECL|macro|FNODE_RD_AHEAD
mdefine_line|#define FNODE_RD_AHEAD&t;16
DECL|macro|ANODE_RD_AHEAD
mdefine_line|#define ANODE_RD_AHEAD&t;16
DECL|macro|DNODE_RD_AHEAD
mdefine_line|#define DNODE_RD_AHEAD&t;4
DECL|macro|FREE_DNODES_ADD
mdefine_line|#define FREE_DNODES_ADD&t;58
DECL|macro|FREE_DNODES_DEL
mdefine_line|#define FREE_DNODES_DEL&t;29
DECL|macro|CHKCOND
mdefine_line|#define CHKCOND(x,y) if (!(x)) printk y
macro_line|#ifdef DBG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) printk x
macro_line|#else
DECL|macro|PRINTK
macro_line|#undef PRINTK
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x)
macro_line|#endif
DECL|typedef|nonconst
r_typedef
r_void
id|nonconst
suffix:semicolon
multiline_comment|/* What this is for ? */
multiline_comment|/*&n; * local time (HPFS) to GMT (Unix)&n; */
DECL|function|local_to_gmt
r_extern
r_inline
id|time_t
id|local_to_gmt
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|time_t
id|t
)paren
(brace
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_return
id|t
op_plus
id|sys_tz.tz_minuteswest
op_star
l_int|60
op_minus
(paren
id|sys_tz.tz_dsttime
ques
c_cond
l_int|3600
suffix:colon
l_int|0
)paren
op_plus
id|s-&gt;s_hpfs_timeshift
suffix:semicolon
)brace
DECL|function|gmt_to_local
r_extern
r_inline
id|time_t
id|gmt_to_local
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|time_t
id|t
)paren
(brace
r_extern
r_struct
id|timezone
id|sys_tz
suffix:semicolon
r_return
id|t
op_minus
id|sys_tz.tz_minuteswest
op_star
l_int|60
op_plus
(paren
id|sys_tz.tz_dsttime
ques
c_cond
l_int|3600
suffix:colon
l_int|0
)paren
op_minus
id|s-&gt;s_hpfs_timeshift
suffix:semicolon
)brace
multiline_comment|/*&n; * conv= options&n; */
DECL|macro|CONV_BINARY
mdefine_line|#define CONV_BINARY 0&t;&t;&t;/* no conversion */
DECL|macro|CONV_TEXT
mdefine_line|#define CONV_TEXT 1&t;&t;&t;/* crlf-&gt;newline */
DECL|macro|CONV_AUTO
mdefine_line|#define CONV_AUTO 2&t;&t;&t;/* decide based on file contents */
multiline_comment|/* Four 512-byte buffers and the 2k block obtained by concatenating them */
DECL|struct|quad_buffer_head
r_struct
id|quad_buffer_head
(brace
DECL|member|bh
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* The b-tree down pointer from a dir entry */
DECL|function|de_down_pointer
r_extern
r_inline
id|dnode_secno
id|de_down_pointer
(paren
r_struct
id|hpfs_dirent
op_star
id|de
)paren
(brace
id|CHKCOND
c_func
(paren
id|de-&gt;down
comma
(paren
l_string|&quot;HPFS: de_down_pointer: !de-&gt;down&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
op_star
(paren
id|dnode_secno
op_star
)paren
(paren
(paren
r_void
op_star
)paren
id|de
op_plus
id|de-&gt;length
op_minus
l_int|4
)paren
suffix:semicolon
)brace
multiline_comment|/* The first dir entry in a dnode */
DECL|function|dnode_first_de
r_extern
r_inline
r_struct
id|hpfs_dirent
op_star
id|dnode_first_de
(paren
r_struct
id|dnode
op_star
id|dnode
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|dnode-&gt;dirent
suffix:semicolon
)brace
multiline_comment|/* The end+1 of the dir entries */
DECL|function|dnode_end_de
r_extern
r_inline
r_struct
id|hpfs_dirent
op_star
id|dnode_end_de
(paren
r_struct
id|dnode
op_star
id|dnode
)paren
(brace
id|CHKCOND
c_func
(paren
id|dnode-&gt;first_free
op_ge
l_int|0x14
op_logical_and
id|dnode-&gt;first_free
op_le
l_int|0xa00
comma
(paren
l_string|&quot;HPFS: dnode_end_de: dnode-&gt;first_free = %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|dnode-&gt;first_free
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|dnode
op_plus
id|dnode-&gt;first_free
suffix:semicolon
)brace
multiline_comment|/* The dir entry after dir entry de */
DECL|function|de_next_de
r_extern
r_inline
r_struct
id|hpfs_dirent
op_star
id|de_next_de
(paren
r_struct
id|hpfs_dirent
op_star
id|de
)paren
(brace
id|CHKCOND
c_func
(paren
id|de-&gt;length
op_ge
l_int|0x20
op_logical_and
id|de-&gt;length
OL
l_int|0x800
comma
(paren
l_string|&quot;HPFS: de_next_de: de-&gt;length = %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|de-&gt;length
)paren
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|de
op_plus
id|de-&gt;length
suffix:semicolon
)brace
DECL|function|fnode_ea
r_extern
r_inline
r_struct
id|extended_attribute
op_star
id|fnode_ea
c_func
(paren
r_struct
id|fnode
op_star
id|fnode
)paren
(brace
r_return
(paren
r_struct
id|extended_attribute
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|fnode
op_plus
id|fnode-&gt;ea_offs
)paren
suffix:semicolon
)brace
DECL|function|fnode_end_ea
r_extern
r_inline
r_struct
id|extended_attribute
op_star
id|fnode_end_ea
c_func
(paren
r_struct
id|fnode
op_star
id|fnode
)paren
(brace
r_return
(paren
r_struct
id|extended_attribute
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|fnode
op_plus
id|fnode-&gt;ea_offs
op_plus
id|fnode-&gt;ea_size_s
)paren
suffix:semicolon
)brace
DECL|function|next_ea
r_extern
r_inline
r_struct
id|extended_attribute
op_star
id|next_ea
c_func
(paren
r_struct
id|extended_attribute
op_star
id|ea
)paren
(brace
r_return
(paren
r_struct
id|extended_attribute
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ea
op_plus
l_int|5
op_plus
id|ea-&gt;namelen
op_plus
id|ea-&gt;valuelen
)paren
suffix:semicolon
)brace
DECL|function|ea_sec
r_extern
r_inline
id|secno
id|ea_sec
c_func
(paren
r_struct
id|extended_attribute
op_star
id|ea
)paren
(brace
r_return
op_star
(paren
id|secno
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ea
op_plus
l_int|9
op_plus
id|ea-&gt;namelen
)paren
suffix:semicolon
)brace
DECL|function|ea_len
r_extern
r_inline
id|secno
id|ea_len
c_func
(paren
r_struct
id|extended_attribute
op_star
id|ea
)paren
(brace
r_return
op_star
(paren
id|secno
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ea
op_plus
l_int|5
op_plus
id|ea-&gt;namelen
)paren
suffix:semicolon
)brace
DECL|function|ea_data
r_extern
r_inline
r_char
op_star
id|ea_data
c_func
(paren
r_struct
id|extended_attribute
op_star
id|ea
)paren
(brace
r_return
(paren
r_char
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|ea
op_plus
l_int|5
op_plus
id|ea-&gt;namelen
)paren
suffix:semicolon
)brace
DECL|function|de_size
r_extern
r_inline
r_int
id|de_size
c_func
(paren
r_int
id|namelen
comma
id|secno
id|down_ptr
)paren
(brace
r_return
(paren
(paren
l_int|0x1f
op_plus
id|namelen
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
)paren
op_plus
(paren
id|down_ptr
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|copy_de
r_extern
r_inline
r_void
id|copy_de
c_func
(paren
r_struct
id|hpfs_dirent
op_star
id|dst
comma
r_struct
id|hpfs_dirent
op_star
id|src
)paren
(brace
r_int
id|a
op_assign
id|dst-&gt;down
suffix:semicolon
r_int
id|n
op_assign
id|dst-&gt;not_8x3
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dst
op_logical_or
op_logical_neg
id|src
)paren
r_return
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|dst
op_plus
l_int|2
comma
(paren
r_char
op_star
)paren
id|src
op_plus
l_int|2
comma
l_int|28
)paren
suffix:semicolon
id|dst-&gt;down
op_assign
id|a
suffix:semicolon
id|dst-&gt;not_8x3
op_assign
id|n
suffix:semicolon
)brace
DECL|function|tstbits
r_extern
r_inline
r_int
id|tstbits
c_func
(paren
r_int
op_star
id|bmp
comma
r_int
id|b
comma
r_int
id|n
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|b
op_ge
l_int|0x4000
)paren
op_logical_or
(paren
id|b
op_plus
id|n
op_minus
l_int|1
op_ge
l_int|0x4000
)paren
)paren
r_return
id|n
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|bmp
(braket
(paren
id|b
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_rshift
(paren
id|b
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|n
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
multiline_comment|/*b+i &lt; 0x4000 &amp;&amp;*/
op_logical_neg
(paren
(paren
id|bmp
(braket
(paren
(paren
id|b
op_plus
id|i
)paren
op_amp
l_int|0x3fff
)paren
op_rshift
l_int|5
)braket
op_rshift
(paren
(paren
id|b
op_plus
id|i
)paren
op_amp
l_int|0x1f
)paren
)paren
op_amp
l_int|1
)paren
)paren
r_return
id|i
op_plus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* alloc.c */
r_int
id|hpfs_chk_sectors
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
id|secno
id|hpfs_alloc_sector
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_alloc_if_possible_nolock
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
)paren
suffix:semicolon
r_int
id|hpfs_alloc_if_possible
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
)paren
suffix:semicolon
r_void
id|hpfs_free_sectors
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_check_free_dnodes
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_free_dnode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
)paren
suffix:semicolon
r_struct
id|dnode
op_star
id|hpfs_alloc_dnode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
id|dnode_secno
op_star
comma
r_struct
id|quad_buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|fnode
op_star
id|hpfs_alloc_fnode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
id|fnode_secno
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_struct
id|anode
op_star
id|hpfs_alloc_anode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
id|anode_secno
op_star
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
multiline_comment|/* anode.c */
id|secno
id|hpfs_bplus_lookup
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|bplus_header
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
)paren
suffix:semicolon
id|secno
id|hpfs_add_sector_to_btree
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_remove_btree
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|bplus_header
op_star
)paren
suffix:semicolon
r_int
id|hpfs_ea_read
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|hpfs_ea_write
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|hpfs_ea_remove
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_truncate_btree
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_remove_fnode
c_func
(paren
r_struct
id|super_block
op_star
comma
id|fnode_secno
id|fno
)paren
suffix:semicolon
multiline_comment|/* buffer.c */
r_void
id|hpfs_lock_creation
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_void
id|hpfs_unlock_creation
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_void
id|hpfs_lock_iget
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_unlock_iget
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_void
id|hpfs_lock_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_unlock_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_lock_2inodes
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_unlock_2inodes
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_lock_3inodes
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_unlock_3inodes
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
op_star
id|hpfs_map_sector
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
op_star
comma
r_int
)paren
suffix:semicolon
r_void
op_star
id|hpfs_get_sector
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_void
op_star
id|hpfs_map_4sectors
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|quad_buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_void
op_star
id|hpfs_get_4sectors
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
r_void
id|hpfs_brelse4
c_func
(paren
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
r_void
id|hpfs_mark_4buffers_dirty
c_func
(paren
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
multiline_comment|/* dentry.c */
r_void
id|hpfs_set_dentry_operations
c_func
(paren
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* dir.c */
r_int
id|hpfs_dir_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|hpfs_dir_release
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
r_int
id|hpfs_readdir
c_func
(paren
r_struct
id|file
op_star
comma
r_void
op_star
comma
id|filldir_t
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|hpfs_lookup
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* dnode.c */
r_void
id|hpfs_add_pos
c_func
(paren
r_struct
id|inode
op_star
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_void
id|hpfs_del_pos
c_func
(paren
r_struct
id|inode
op_star
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|hpfs_add_de
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|dnode
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
id|secno
)paren
suffix:semicolon
r_void
id|hpfs_delete_de
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|dnode
op_star
comma
r_struct
id|hpfs_dirent
op_star
)paren
suffix:semicolon
r_int
id|hpfs_add_to_dnode
c_func
(paren
r_struct
id|inode
op_star
comma
id|dnode_secno
comma
r_int
r_char
op_star
comma
r_int
comma
r_struct
id|hpfs_dirent
op_star
comma
id|dnode_secno
)paren
suffix:semicolon
r_int
id|hpfs_add_dirent
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_struct
id|hpfs_dirent
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_remove_dirent
c_func
(paren
r_struct
id|inode
op_star
comma
id|dnode_secno
comma
r_struct
id|hpfs_dirent
op_star
comma
r_struct
id|quad_buffer_head
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_count_dnodes
c_func
(paren
r_struct
id|super_block
op_star
comma
id|dnode_secno
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
id|dnode_secno
id|hpfs_de_as_down_as_possible
c_func
(paren
r_struct
id|super_block
op_star
comma
id|dnode_secno
id|dno
)paren
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|map_pos_dirent
c_func
(paren
r_struct
id|inode
op_star
comma
id|loff_t
op_star
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|map_dirent
c_func
(paren
r_struct
id|inode
op_star
comma
id|dnode_secno
comma
r_char
op_star
comma
r_int
comma
id|dnode_secno
op_star
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
r_void
id|hpfs_remove_dtree
c_func
(paren
r_struct
id|super_block
op_star
comma
id|dnode_secno
)paren
suffix:semicolon
r_struct
id|hpfs_dirent
op_star
id|map_fnode_dirent
c_func
(paren
r_struct
id|super_block
op_star
comma
id|fnode_secno
comma
r_struct
id|fnode
op_star
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
multiline_comment|/* ea.c */
r_void
id|hpfs_ea_ext_remove
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_char
op_star
id|hpfs_get_ea
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|fnode
op_star
comma
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|hpfs_set_ea
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|fnode
op_star
comma
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* file.c */
r_int
id|hpfs_file_release
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
r_int
id|hpfs_open
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
r_int
id|hpfs_file_fsync
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
id|secno
id|hpfs_bmap
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_truncate
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
id|ssize_t
id|hpfs_file_read
c_func
(paren
r_struct
id|file
op_star
comma
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
id|ssize_t
id|hpfs_file_write
c_func
(paren
r_struct
id|file
op_star
comma
r_const
r_char
op_star
comma
r_int
comma
id|loff_t
op_star
)paren
suffix:semicolon
r_int
id|hpfs_writepage
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
multiline_comment|/* inode.c */
r_void
id|hpfs_read_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_write_inode_ea
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|fnode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_write_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_write_inode_nolock
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_int
id|hpfs_notify_change
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
r_void
id|hpfs_write_if_changed
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
r_void
id|hpfs_delete_inode
c_func
(paren
r_struct
id|inode
op_star
)paren
suffix:semicolon
multiline_comment|/* map.c */
r_int
op_star
id|hpfs_map_dnode_bitmap
c_func
(paren
r_struct
id|super_block
op_star
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
r_int
op_star
id|hpfs_map_bitmap
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_struct
id|quad_buffer_head
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_char
op_star
id|hpfs_load_code_page
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
)paren
suffix:semicolon
id|secno
op_star
id|hpfs_load_bitmap_directory
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
id|bmp
)paren
suffix:semicolon
r_struct
id|fnode
op_star
id|hpfs_map_fnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|ino_t
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_struct
id|anode
op_star
id|hpfs_map_anode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|anode_secno
comma
r_struct
id|buffer_head
op_star
op_star
)paren
suffix:semicolon
r_struct
id|dnode
op_star
id|hpfs_map_dnode
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|dnode_secno
comma
r_struct
id|quad_buffer_head
op_star
)paren
suffix:semicolon
id|dnode_secno
id|hpfs_fnode_dno
c_func
(paren
r_struct
id|super_block
op_star
id|s
comma
id|ino_t
id|ino
)paren
suffix:semicolon
multiline_comment|/* mmap.c */
r_int
id|hpfs_mmap
c_func
(paren
r_struct
id|file
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* name.c */
r_int
r_char
id|hpfs_upcase
c_func
(paren
r_int
r_char
op_star
comma
r_int
r_char
)paren
suffix:semicolon
r_int
id|hpfs_chk_name
c_func
(paren
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_char
op_star
id|hpfs_translate_name
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_compare_names
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
r_char
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_is_name_long
c_func
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_void
id|hpfs_adjust_length
c_func
(paren
r_int
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_void
id|hpfs_decide_conv
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* namei.c */
r_int
id|hpfs_mkdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_create
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_mknod
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_int
id|hpfs_symlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
r_int
id|hpfs_unlink
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|hpfs_rmdir
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
r_int
id|hpfs_readlink
c_func
(paren
r_struct
id|dentry
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_struct
id|dentry
op_star
id|hpfs_follow_link
c_func
(paren
r_struct
id|dentry
op_star
comma
r_struct
id|dentry
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_int
id|hpfs_rename
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
comma
r_struct
id|inode
op_star
comma
r_struct
id|dentry
op_star
)paren
suffix:semicolon
multiline_comment|/* super.c */
r_void
id|hpfs_error
c_func
(paren
r_struct
id|super_block
op_star
comma
r_char
op_star
comma
dot
dot
dot
)paren
suffix:semicolon
r_int
id|hpfs_stop_cycles
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
comma
r_int
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_int
id|hpfs_remount_fs
c_func
(paren
r_struct
id|super_block
op_star
comma
r_int
op_star
comma
r_char
op_star
)paren
suffix:semicolon
r_void
id|hpfs_put_super
c_func
(paren
r_struct
id|super_block
op_star
)paren
suffix:semicolon
r_int
id|hpfs_count_one_bitmap
c_func
(paren
r_struct
id|super_block
op_star
comma
id|secno
)paren
suffix:semicolon
r_int
id|hpfs_statfs
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
)paren
suffix:semicolon
r_struct
id|super_block
op_star
id|hpfs_read_super
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
eof
