multiline_comment|/*&n; * kernel/lvm-snap.c&n; *&n; * Copyright (C) 2000 Andrea Arcangeli &lt;andrea@suse.de&gt; SuSE&n; *&n; * LVM snapshot driver is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; * &n; * LVM driver is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with GNU CC; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 59 Temple Place - Suite 330,&n; * Boston, MA 02111-1307, USA. &n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/lvm.h&gt;
DECL|variable|lvm_snap_version
r_static
r_char
op_star
id|lvm_snap_version
id|__attribute__
(paren
(paren
id|unused
)paren
)paren
op_assign
l_string|&quot;LVM 0.8final (15/02/2000)&bslash;n&quot;
suffix:semicolon
r_extern
r_const
r_char
op_star
r_const
id|lvm_name
suffix:semicolon
r_extern
r_int
id|lvm_blocksizes
(braket
)braket
suffix:semicolon
r_void
id|lvm_snapshot_release
c_func
(paren
id|lv_t
op_star
)paren
suffix:semicolon
DECL|macro|hashfn
mdefine_line|#define hashfn(dev,block,mask,chunk_size) &bslash;&n;&t;((HASHDEV(dev)^((block)/(chunk_size))) &amp; (mask))
r_static
r_inline
id|lv_block_exception_t
op_star
DECL|function|lvm_find_exception_table
id|lvm_find_exception_table
c_func
(paren
id|kdev_t
id|org_dev
comma
r_int
r_int
id|org_start
comma
id|lv_t
op_star
id|lv
)paren
(brace
r_struct
id|list_head
op_star
id|hash_table
op_assign
id|lv-&gt;lv_snapshot_hash_table
comma
op_star
id|next
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|lv-&gt;lv_snapshot_hash_mask
suffix:semicolon
r_int
id|chunk_size
op_assign
id|lv-&gt;lv_chunk_size
suffix:semicolon
id|lv_block_exception_t
op_star
id|ret
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|hash_table
op_assign
op_amp
id|hash_table
(braket
id|hashfn
c_func
(paren
id|org_dev
comma
id|org_start
comma
id|mask
comma
id|chunk_size
)paren
)braket
suffix:semicolon
id|ret
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|next
op_assign
id|hash_table-&gt;next
suffix:semicolon
id|next
op_ne
id|hash_table
suffix:semicolon
id|next
op_assign
id|next-&gt;next
)paren
(brace
id|lv_block_exception_t
op_star
id|exception
suffix:semicolon
id|exception
op_assign
id|list_entry
c_func
(paren
id|next
comma
id|lv_block_exception_t
comma
id|hash
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exception-&gt;rsector_org
op_eq
id|org_start
op_logical_and
id|exception-&gt;rdev_org
op_eq
id|org_dev
)paren
(brace
r_if
c_cond
(paren
id|i
)paren
(brace
multiline_comment|/* fun, isn&squot;t it? :) */
id|list_del
c_func
(paren
id|next
)paren
suffix:semicolon
id|list_add
c_func
(paren
id|next
comma
id|hash_table
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|exception
suffix:semicolon
r_break
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|lvm_hash_link
r_static
r_inline
r_void
id|lvm_hash_link
c_func
(paren
id|lv_block_exception_t
op_star
id|exception
comma
id|kdev_t
id|org_dev
comma
r_int
r_int
id|org_start
comma
id|lv_t
op_star
id|lv
)paren
(brace
r_struct
id|list_head
op_star
id|hash_table
op_assign
id|lv-&gt;lv_snapshot_hash_table
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|lv-&gt;lv_snapshot_hash_mask
suffix:semicolon
r_int
id|chunk_size
op_assign
id|lv-&gt;lv_chunk_size
suffix:semicolon
id|hash_table
op_assign
op_amp
id|hash_table
(braket
id|hashfn
c_func
(paren
id|org_dev
comma
id|org_start
comma
id|mask
comma
id|chunk_size
)paren
)braket
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|exception-&gt;hash
comma
id|hash_table
)paren
suffix:semicolon
)brace
DECL|function|lvm_snapshot_remap_block
r_int
id|lvm_snapshot_remap_block
c_func
(paren
id|kdev_t
op_star
id|org_dev
comma
r_int
r_int
op_star
id|org_sector
comma
r_int
r_int
id|pe_start
comma
id|lv_t
op_star
id|lv
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_int
id|pe_off
comma
id|pe_adjustment
comma
id|__org_start
suffix:semicolon
id|kdev_t
id|__org_dev
suffix:semicolon
r_int
id|chunk_size
op_assign
id|lv-&gt;lv_chunk_size
suffix:semicolon
id|lv_block_exception_t
op_star
id|exception
suffix:semicolon
id|pe_off
op_assign
id|pe_start
op_mod
id|chunk_size
suffix:semicolon
id|pe_adjustment
op_assign
(paren
op_star
id|org_sector
op_minus
id|pe_off
)paren
op_mod
id|chunk_size
suffix:semicolon
id|__org_start
op_assign
op_star
id|org_sector
op_minus
id|pe_adjustment
suffix:semicolon
id|__org_dev
op_assign
op_star
id|org_dev
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|exception
op_assign
id|lvm_find_exception_table
c_func
(paren
id|__org_dev
comma
id|__org_start
comma
id|lv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|exception
)paren
(brace
op_star
id|org_dev
op_assign
id|exception-&gt;rdev_new
suffix:semicolon
op_star
id|org_sector
op_assign
id|exception-&gt;rsector_new
op_plus
id|pe_adjustment
suffix:semicolon
id|ret
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|lvm_drop_snapshot
r_static
r_void
id|lvm_drop_snapshot
c_func
(paren
id|lv_t
op_star
id|lv_snap
comma
r_const
r_char
op_star
id|reason
)paren
(brace
id|kdev_t
id|last_dev
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* no exception storage space available for this snapshot&n;&t;   or error on this snapshot --&gt; release it */
id|invalidate_buffers
c_func
(paren
id|lv_snap-&gt;lv_dev
)paren
suffix:semicolon
id|last_dev
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
id|lv_snap-&gt;lv_remap_ptr
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|lv_snap-&gt;lv_block_exception
(braket
id|i
)braket
dot
id|rdev_new
op_ne
id|last_dev
)paren
(brace
id|last_dev
op_assign
id|lv_snap-&gt;lv_block_exception
(braket
id|i
)braket
dot
id|rdev_new
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|last_dev
)paren
suffix:semicolon
)brace
)brace
id|lvm_snapshot_release
c_func
(paren
id|lv_snap
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s -- giving up to snapshot %s on %s due %s&bslash;n&quot;
comma
id|lvm_name
comma
id|lv_snap-&gt;lv_snapshot_org-&gt;lv_name
comma
id|lv_snap-&gt;lv_name
comma
id|reason
)paren
suffix:semicolon
)brace
DECL|function|lvm_snapshot_prepare_blocks
r_static
r_inline
r_void
id|lvm_snapshot_prepare_blocks
c_func
(paren
r_int
r_int
op_star
id|blocks
comma
r_int
r_int
id|start
comma
r_int
id|nr_sectors
comma
r_int
id|blocksize
)paren
(brace
r_int
id|i
comma
id|sectors_per_block
comma
id|nr_blocks
suffix:semicolon
id|sectors_per_block
op_assign
id|blocksize
op_rshift
l_int|9
suffix:semicolon
id|nr_blocks
op_assign
id|nr_sectors
op_div
id|sectors_per_block
suffix:semicolon
id|start
op_div_assign
id|sectors_per_block
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
id|nr_blocks
suffix:semicolon
id|i
op_increment
)paren
id|blocks
(braket
id|i
)braket
op_assign
id|start
op_increment
suffix:semicolon
)brace
DECL|function|get_blksize
r_static
r_inline
r_int
id|get_blksize
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_int
id|correct_size
op_assign
id|BLOCK_SIZE
comma
id|i
comma
id|major
suffix:semicolon
id|major
op_assign
id|MAJOR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|blksize_size
(braket
id|major
)braket
)paren
(brace
id|i
op_assign
id|blksize_size
(braket
id|major
)braket
(braket
id|MINOR
c_func
(paren
id|dev
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|correct_size
op_assign
id|i
suffix:semicolon
)brace
r_return
id|correct_size
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_SNAPSHOT
DECL|function|invalidate_snap_cache
r_static
r_inline
r_void
id|invalidate_snap_cache
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|nr
comma
id|kdev_t
id|dev
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|sectors_per_block
comma
id|i
comma
id|blksize
comma
id|minor
suffix:semicolon
id|minor
op_assign
id|MINOR
c_func
(paren
id|dev
)paren
suffix:semicolon
id|blksize
op_assign
id|lvm_blocksizes
(braket
id|minor
)braket
suffix:semicolon
id|sectors_per_block
op_assign
id|blksize
op_rshift
l_int|9
suffix:semicolon
id|nr
op_div_assign
id|sectors_per_block
suffix:semicolon
id|start
op_div_assign
id|sectors_per_block
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
id|nr
suffix:semicolon
id|i
op_increment
)paren
(brace
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|dev
comma
id|start
op_increment
comma
id|blksize
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
id|bforget
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; * copy on write handler for one snapshot logical volume&n; *&n; * read the original blocks and store it/them on the new one(s).&n; * if there is no exception storage space free any longer --&gt; release snapshot.&n; *&n; * this routine gets called for each _first_ write to a physical chunk.&n; */
DECL|function|lvm_snapshot_COW
r_int
id|lvm_snapshot_COW
c_func
(paren
id|kdev_t
id|org_phys_dev
comma
r_int
r_int
id|org_phys_sector
comma
r_int
r_int
id|org_pe_start
comma
r_int
r_int
id|org_virt_sector
comma
id|lv_t
op_star
id|lv_snap
)paren
(brace
r_const
r_char
op_star
id|reason
suffix:semicolon
r_int
r_int
id|org_start
comma
id|snap_start
comma
id|virt_start
comma
id|pe_off
suffix:semicolon
r_int
id|idx
op_assign
id|lv_snap-&gt;lv_remap_ptr
comma
id|chunk_size
op_assign
id|lv_snap-&gt;lv_chunk_size
suffix:semicolon
id|kdev_t
id|snap_phys_dev
suffix:semicolon
r_struct
id|kiobuf
op_star
id|iobuf
suffix:semicolon
r_int
r_int
id|blocks
(braket
id|KIO_MAX_SECTORS
)braket
suffix:semicolon
r_int
id|blksize_snap
comma
id|blksize_org
comma
id|min_blksize
comma
id|max_blksize
suffix:semicolon
r_int
id|max_sectors
comma
id|nr_sectors
suffix:semicolon
multiline_comment|/* check if we are out of snapshot space */
r_if
c_cond
(paren
id|idx
op_ge
id|lv_snap-&gt;lv_remap_end
)paren
r_goto
id|fail_out_of_space
suffix:semicolon
multiline_comment|/* calculate physical boundaries of source chunk */
id|pe_off
op_assign
id|org_pe_start
op_mod
id|chunk_size
suffix:semicolon
id|org_start
op_assign
id|org_phys_sector
op_minus
(paren
(paren
id|org_phys_sector
op_minus
id|pe_off
)paren
op_mod
id|chunk_size
)paren
suffix:semicolon
id|virt_start
op_assign
id|org_virt_sector
op_minus
(paren
id|org_phys_sector
op_minus
id|org_start
)paren
suffix:semicolon
multiline_comment|/* calculate physical boundaries of destination chunk */
id|snap_phys_dev
op_assign
id|lv_snap-&gt;lv_block_exception
(braket
id|idx
)braket
dot
id|rdev_new
suffix:semicolon
id|snap_start
op_assign
id|lv_snap-&gt;lv_block_exception
(braket
id|idx
)braket
dot
id|rsector_new
suffix:semicolon
macro_line|#ifdef DEBUG_SNAPSHOT
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s -- COW: &quot;
l_string|&quot;org %02d:%02d faulting %lu start %lu, &quot;
l_string|&quot;snap %02d:%02d start %lu, &quot;
l_string|&quot;size %d, pe_start %lu pe_off %lu, virt_sec %lu&bslash;n&quot;
comma
id|lvm_name
comma
id|MAJOR
c_func
(paren
id|org_phys_dev
)paren
comma
id|MINOR
c_func
(paren
id|org_phys_dev
)paren
comma
id|org_phys_sector
comma
id|org_start
comma
id|MAJOR
c_func
(paren
id|snap_phys_dev
)paren
comma
id|MINOR
c_func
(paren
id|snap_phys_dev
)paren
comma
id|snap_start
comma
id|chunk_size
comma
id|org_pe_start
comma
id|pe_off
comma
id|org_virt_sector
)paren
suffix:semicolon
macro_line|#endif
id|iobuf
op_assign
id|lv_snap-&gt;lv_iobuf
suffix:semicolon
id|blksize_org
op_assign
id|get_blksize
c_func
(paren
id|org_phys_dev
)paren
suffix:semicolon
id|blksize_snap
op_assign
id|get_blksize
c_func
(paren
id|snap_phys_dev
)paren
suffix:semicolon
id|max_blksize
op_assign
id|max
c_func
(paren
id|blksize_org
comma
id|blksize_snap
)paren
suffix:semicolon
id|min_blksize
op_assign
id|min
c_func
(paren
id|blksize_org
comma
id|blksize_snap
)paren
suffix:semicolon
id|max_sectors
op_assign
id|KIO_MAX_SECTORS
op_star
(paren
id|min_blksize
op_rshift
l_int|9
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chunk_size
op_mod
(paren
id|max_blksize
op_rshift
l_int|9
)paren
)paren
r_goto
id|fail_blksize
suffix:semicolon
r_while
c_loop
(paren
id|chunk_size
)paren
(brace
id|nr_sectors
op_assign
id|min
c_func
(paren
id|chunk_size
comma
id|max_sectors
)paren
suffix:semicolon
id|chunk_size
op_sub_assign
id|nr_sectors
suffix:semicolon
id|iobuf-&gt;length
op_assign
id|nr_sectors
op_lshift
l_int|9
suffix:semicolon
id|lvm_snapshot_prepare_blocks
c_func
(paren
id|blocks
comma
id|org_start
comma
id|nr_sectors
comma
id|blksize_org
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brw_kiovec
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|iobuf
comma
id|org_phys_dev
comma
id|blocks
comma
id|blksize_org
)paren
op_ne
(paren
id|nr_sectors
op_lshift
l_int|9
)paren
)paren
r_goto
id|fail_raw_read
suffix:semicolon
id|lvm_snapshot_prepare_blocks
c_func
(paren
id|blocks
comma
id|snap_start
comma
id|nr_sectors
comma
id|blksize_snap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|brw_kiovec
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|iobuf
comma
id|snap_phys_dev
comma
id|blocks
comma
id|blksize_snap
)paren
op_ne
(paren
id|nr_sectors
op_lshift
l_int|9
)paren
)paren
r_goto
id|fail_raw_write
suffix:semicolon
)brace
macro_line|#ifdef DEBUG_SNAPSHOT
multiline_comment|/* invalidate the logcial snapshot buffer cache */
id|invalidate_snap_cache
c_func
(paren
id|virt_start
comma
id|lv_snap-&gt;lv_chunk_size
comma
id|lv_snap-&gt;lv_dev
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* the original chunk is now stored on the snapshot volume&n;&t;   so update the execption table */
id|lv_snap-&gt;lv_block_exception
(braket
id|idx
)braket
dot
id|rdev_org
op_assign
id|org_phys_dev
suffix:semicolon
id|lv_snap-&gt;lv_block_exception
(braket
id|idx
)braket
dot
id|rsector_org
op_assign
id|org_start
suffix:semicolon
id|lvm_hash_link
c_func
(paren
id|lv_snap-&gt;lv_block_exception
op_plus
id|idx
comma
id|org_phys_dev
comma
id|org_start
comma
id|lv_snap
)paren
suffix:semicolon
id|lv_snap-&gt;lv_remap_ptr
op_assign
id|idx
op_plus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* slow path */
id|out
suffix:colon
id|lvm_drop_snapshot
c_func
(paren
id|lv_snap
comma
id|reason
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
id|fail_out_of_space
suffix:colon
id|reason
op_assign
l_string|&quot;out of space&quot;
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|fail_raw_read
suffix:colon
id|reason
op_assign
l_string|&quot;read error&quot;
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|fail_raw_write
suffix:colon
id|reason
op_assign
l_string|&quot;write error&quot;
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|fail_blksize
suffix:colon
id|reason
op_assign
l_string|&quot;blocksize error&quot;
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|lvm_snapshot_alloc_iobuf_pages
r_static
r_int
id|lvm_snapshot_alloc_iobuf_pages
c_func
(paren
r_struct
id|kiobuf
op_star
id|iobuf
comma
r_int
id|sectors
)paren
(brace
r_int
id|bytes
comma
id|nr_pages
comma
id|err
comma
id|i
suffix:semicolon
id|bytes
op_assign
id|sectors
op_lshift
l_int|9
suffix:semicolon
id|nr_pages
op_assign
(paren
id|bytes
op_plus
op_complement
id|PAGE_MASK
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|err
op_assign
id|expand_kiobuf
c_func
(paren
id|iobuf
comma
id|nr_pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|iobuf-&gt;locked
op_assign
l_int|1
suffix:semicolon
id|iobuf-&gt;nr_pages
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
id|nr_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|page
op_star
id|page
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,3,27)
id|page
op_assign
id|alloc_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_goto
id|out
suffix:semicolon
macro_line|#else
(brace
r_int
r_int
id|addr
op_assign
id|__get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_goto
id|out
suffix:semicolon
id|iobuf-&gt;pagelist
(braket
id|i
)braket
op_assign
id|addr
suffix:semicolon
id|page
op_assign
id|virt_to_page
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif
id|iobuf-&gt;maplist
(braket
id|i
)braket
op_assign
id|page
suffix:semicolon
multiline_comment|/* the only point to lock the page here is to be allowed&n;&t;&t;   to share unmap_kiobuf() in the fail-path */
macro_line|#ifndef LockPage
DECL|macro|LockPage
mdefine_line|#define LockPage(map) set_bit(PG_locked, &amp;(map)-&gt;flags)
macro_line|#endif
id|LockPage
c_func
(paren
id|page
)paren
suffix:semicolon
id|iobuf-&gt;nr_pages
op_increment
suffix:semicolon
)brace
id|iobuf-&gt;offset
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|calc_max_buckets
r_static
r_int
id|calc_max_buckets
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|mem
suffix:semicolon
id|mem
op_assign
id|num_physpages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|mem
op_div_assign
l_int|100
suffix:semicolon
id|mem
op_mul_assign
l_int|2
suffix:semicolon
id|mem
op_div_assign
r_sizeof
(paren
r_struct
id|list_head
)paren
suffix:semicolon
r_return
id|mem
suffix:semicolon
)brace
DECL|function|lvm_snapshot_alloc_hash_table
r_static
r_int
id|lvm_snapshot_alloc_hash_table
c_func
(paren
id|lv_t
op_star
id|lv
)paren
(brace
r_int
id|err
suffix:semicolon
r_int
r_int
id|buckets
comma
id|max_buckets
comma
id|size
suffix:semicolon
r_struct
id|list_head
op_star
id|hash
suffix:semicolon
id|buckets
op_assign
id|lv-&gt;lv_remap_end
suffix:semicolon
id|max_buckets
op_assign
id|calc_max_buckets
c_func
(paren
)paren
suffix:semicolon
id|buckets
op_assign
id|min
c_func
(paren
id|buckets
comma
id|max_buckets
)paren
suffix:semicolon
r_while
c_loop
(paren
id|buckets
op_amp
(paren
id|buckets
op_minus
l_int|1
)paren
)paren
id|buckets
op_and_assign
(paren
id|buckets
op_minus
l_int|1
)paren
suffix:semicolon
id|size
op_assign
id|buckets
op_star
r_sizeof
(paren
r_struct
id|list_head
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|hash
op_assign
id|vmalloc
c_func
(paren
id|size
)paren
suffix:semicolon
id|lv-&gt;lv_snapshot_hash_table
op_assign
id|hash
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hash
)paren
r_goto
id|out
suffix:semicolon
id|lv-&gt;lv_snapshot_hash_mask
op_assign
id|buckets
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|buckets
op_decrement
)paren
id|INIT_LIST_HEAD
c_func
(paren
id|hash
op_plus
id|buckets
)paren
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
DECL|function|lvm_snapshot_alloc
r_int
id|lvm_snapshot_alloc
c_func
(paren
id|lv_t
op_star
id|lv_snap
)paren
(brace
r_int
id|err
comma
id|blocksize
comma
id|max_sectors
suffix:semicolon
id|err
op_assign
id|alloc_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|lv_snap-&gt;lv_iobuf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out
suffix:semicolon
id|blocksize
op_assign
id|lvm_blocksizes
(braket
id|MINOR
c_func
(paren
id|lv_snap-&gt;lv_dev
)paren
)braket
suffix:semicolon
id|max_sectors
op_assign
id|KIO_MAX_SECTORS
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|9
)paren
suffix:semicolon
id|err
op_assign
id|lvm_snapshot_alloc_iobuf_pages
c_func
(paren
id|lv_snap-&gt;lv_iobuf
comma
id|max_sectors
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_free_kiovec
suffix:semicolon
id|err
op_assign
id|lvm_snapshot_alloc_hash_table
c_func
(paren
id|lv_snap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|out_free_kiovec
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
id|out_free_kiovec
suffix:colon
id|unmap_kiobuf
c_func
(paren
id|lv_snap-&gt;lv_iobuf
)paren
suffix:semicolon
id|free_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|lv_snap-&gt;lv_iobuf
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|lvm_snapshot_release
r_void
id|lvm_snapshot_release
c_func
(paren
id|lv_t
op_star
id|lv
)paren
(brace
r_if
c_cond
(paren
id|lv-&gt;lv_block_exception
)paren
(brace
id|vfree
c_func
(paren
id|lv-&gt;lv_block_exception
)paren
suffix:semicolon
id|lv-&gt;lv_block_exception
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lv-&gt;lv_snapshot_hash_table
)paren
(brace
id|vfree
c_func
(paren
id|lv-&gt;lv_snapshot_hash_table
)paren
suffix:semicolon
id|lv-&gt;lv_snapshot_hash_table
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|lv-&gt;lv_iobuf
)paren
(brace
id|free_kiovec
c_func
(paren
l_int|1
comma
op_amp
id|lv-&gt;lv_iobuf
)paren
suffix:semicolon
id|lv-&gt;lv_iobuf
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
