multiline_comment|/*&n; * linux/fs/fat/buffer.c&n; *&n; *&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#include &lt;linux/fat_cvf.h&gt;
macro_line|#if 0
macro_line|#  define PRINTK(x) printk x
macro_line|#else
DECL|macro|PRINTK
macro_line|#  define PRINTK(x)
macro_line|#endif
DECL|function|fat_bread
r_struct
id|buffer_head
op_star
id|fat_bread
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;fat_bread: block=0x%x&bslash;n&quot;
comma
id|block
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note that the blocksize is 512, 1024 or 2048, but the first read&n;&t; * is always of size 1024 (or 2048). Doing readahead may be&n;&t; * counterproductive or just plain wrong.&n;&t; */
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_bread
)paren
(brace
r_return
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_bread
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|512
)paren
(brace
id|ret
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|block
comma
l_int|512
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|buffer_head
op_star
id|real
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|1024
)paren
(brace
id|real
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|block
op_rshift
l_int|1
comma
l_int|1024
)paren
suffix:semicolon
)brace
r_else
(brace
id|real
op_assign
id|bread
(paren
id|sb-&gt;s_dev
comma
id|block
op_rshift
l_int|2
comma
l_int|2048
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|real
op_ne
l_int|NULL
)paren
(brace
id|ret
op_assign
(paren
r_struct
id|buffer_head
op_star
)paren
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|buffer_head
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* #Specification: msdos / strategy / special device / dummy blocks&n;&t;&t;&t;&t;&t;Many special device (Scsi optical disk for one) use&n;&t;&t;&t;&t;&t;larger hardware sector size. This allows for higher&n;&t;&t;&t;&t;&t;capacity.&n;&n;&t;&t;&t;&t;&t;Most of the time, the MsDOS file system that sit&n;&t;&t;&t;&t;&t;on this device is totally unaligned. It use logically&n;&t;&t;&t;&t;&t;512 bytes sector size, with logical sector starting&n;&t;&t;&t;&t;&t;in the middle of a hardware block. The bad news is&n;&t;&t;&t;&t;&t;that a hardware sector may hold data own by two&n;&t;&t;&t;&t;&t;different files. This means that the hardware sector&n;&t;&t;&t;&t;&t;must be read, patch and written almost all the time.&n;&n;&t;&t;&t;&t;&t;Needless to say that it kills write performance&n;&t;&t;&t;&t;&t;on all OS.&n;&n;&t;&t;&t;&t;&t;Internally the linux msdos fs is using 512 bytes&n;&t;&t;&t;&t;&t;logical sector. When accessing such a device, we&n;&t;&t;&t;&t;&t;allocate dummy buffer cache blocks, that we stuff&n;&t;&t;&t;&t;&t;with the information of a real one (1k large).&n;&n;&t;&t;&t;&t;&t;This strategy is used to hide this difference to&n;&t;&t;&t;&t;&t;the core of the msdos fs. The slowdown is not&n;&t;&t;&t;&t;&t;hidden though!&n;&t;&t;&t;&t;*/
multiline_comment|/*&n;&t;&t;&t;&t;&t;The memset is there only to catch errors. The msdos&n;&t;&t;&t;&t;&t;fs is only using b_data&n;&t;&t;&t;&t;*/
id|memset
(paren
id|ret
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|ret
)paren
)paren
suffix:semicolon
id|ret-&gt;b_data
op_assign
id|real-&gt;b_data
suffix:semicolon
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|2048
)paren
(brace
r_if
c_cond
(paren
id|block
op_amp
l_int|3
)paren
id|ret-&gt;b_data
op_add_assign
(paren
id|block
op_amp
l_int|3
)paren
op_lshift
l_int|9
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|block
op_amp
l_int|1
)paren
id|ret-&gt;b_data
op_add_assign
l_int|512
suffix:semicolon
)brace
id|ret-&gt;b_next
op_assign
id|real
suffix:semicolon
)brace
r_else
(brace
id|brelse
(paren
id|real
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fat_getblk
r_struct
id|buffer_head
op_star
id|fat_getblk
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
(brace
r_struct
id|buffer_head
op_star
id|ret
op_assign
l_int|NULL
suffix:semicolon
id|PRINTK
c_func
(paren
(paren
l_string|&quot;fat_getblk: block=0x%x&bslash;n&quot;
comma
id|block
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_getblk
)paren
(brace
r_return
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_getblk
c_func
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|512
)paren
(brace
id|ret
op_assign
id|getblk
(paren
id|sb-&gt;s_dev
comma
id|block
comma
l_int|512
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* #Specification: msdos / special device / writing&n;&t;&t;&t;A write is always preceded by a read of the complete block&n;&t;&t;&t;(large hardware sector size). This defeat write performance.&n;&t;&t;&t;There is a possibility to optimize this when writing large&n;&t;&t;&t;chunk by making sure we are filling large block. Volunteer ?&n;&t;&t;*/
id|ret
op_assign
id|fat_bread
(paren
id|sb
comma
id|block
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|fat_brelse
r_void
id|fat_brelse
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_brelse
)paren
(brace
r_return
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_brelse
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|512
)paren
(brace
id|brelse
(paren
id|bh
)paren
suffix:semicolon
)brace
r_else
(brace
id|brelse
(paren
id|bh-&gt;b_next
)paren
suffix:semicolon
multiline_comment|/* We can free the dummy because a new one is allocated at&n;&t;&t;&t;&t;each fat_getblk() and fat_bread().&n;&t;&t;&t;*/
id|kfree
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|fat_mark_buffer_dirty
r_void
id|fat_mark_buffer_dirty
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|dirty_val
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_mark_buffer_dirty
)paren
(brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_mark_buffer_dirty
c_func
(paren
id|sb
comma
id|bh
comma
id|dirty_val
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_ne
l_int|512
)paren
(brace
id|bh
op_assign
id|bh-&gt;b_next
suffix:semicolon
)brace
id|mark_buffer_dirty
(paren
id|bh
comma
id|dirty_val
)paren
suffix:semicolon
)brace
DECL|function|fat_set_uptodate
r_void
id|fat_set_uptodate
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|val
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_set_uptodate
)paren
(brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_set_uptodate
c_func
(paren
id|sb
comma
id|bh
comma
id|val
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_ne
l_int|512
)paren
(brace
id|bh
op_assign
id|bh-&gt;b_next
suffix:semicolon
)brace
id|mark_buffer_uptodate
c_func
(paren
id|bh
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|fat_is_uptodate
r_int
id|fat_is_uptodate
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_is_uptodate
)paren
(brace
r_return
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_is_uptodate
c_func
(paren
id|sb
comma
id|bh
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_ne
l_int|512
)paren
(brace
id|bh
op_assign
id|bh-&gt;b_next
suffix:semicolon
)brace
r_return
id|buffer_uptodate
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|fat_ll_rw_block
r_void
id|fat_ll_rw_block
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|opr
comma
r_int
id|nbreq
comma
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|32
)braket
)paren
(brace
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
)paren
r_if
c_cond
(paren
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format-&gt;cvf_ll_rw_block
)paren
(brace
id|MSDOS_SB
c_func
(paren
id|sb
)paren
op_member_access_from_pointer
id|cvf_format
op_member_access_from_pointer
id|cvf_ll_rw_block
c_func
(paren
id|sb
comma
id|opr
comma
id|nbreq
comma
id|bh
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sb-&gt;s_blocksize
op_eq
l_int|512
)paren
(brace
id|ll_rw_block
c_func
(paren
id|opr
comma
id|nbreq
comma
id|bh
)paren
suffix:semicolon
)brace
r_else
(brace
r_struct
id|buffer_head
op_star
id|tmp
(braket
l_int|32
)braket
suffix:semicolon
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
id|nbreq
suffix:semicolon
id|i
op_increment
)paren
(brace
id|tmp
(braket
id|i
)braket
op_assign
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_next
suffix:semicolon
)brace
id|ll_rw_block
c_func
(paren
id|opr
comma
id|nbreq
comma
id|tmp
)paren
suffix:semicolon
)brace
)brace
eof
