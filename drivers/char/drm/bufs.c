multiline_comment|/* bufs.c -- IOCTLs to manage buffers -*- linux-c -*-&n; * Created: Tue Feb  2 08:37:54 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999, 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;linux/un.h&quot;
multiline_comment|/* Compute order.  Can be made faster. */
DECL|function|drm_order
r_int
id|drm_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|order
op_assign
l_int|0
comma
id|tmp
op_assign
id|size
suffix:semicolon
id|tmp
op_rshift_assign
l_int|1
suffix:semicolon
op_increment
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|size
op_amp
op_complement
(paren
l_int|1
op_lshift
id|order
)paren
)paren
op_increment
id|order
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
DECL|function|drm_addmap
r_int
id|drm_addmap
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_mode
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* Require read/write */
id|map
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|map
comma
(paren
id|drm_map_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
op_star
id|map
)paren
)paren
)paren
(brace
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;offset = 0x%08lx, size = 0x%08lx, type = %d&bslash;n&quot;
comma
id|map-&gt;offset
comma
id|map-&gt;size
comma
id|map-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|map-&gt;offset
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
)paren
op_logical_or
(paren
id|map-&gt;size
op_amp
(paren
op_complement
id|PAGE_MASK
)paren
)paren
)paren
(brace
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|map-&gt;mtrr
op_assign
op_minus
l_int|1
suffix:semicolon
id|map-&gt;handle
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|map-&gt;type
)paren
(brace
r_case
id|_DRM_REGISTERS
suffix:colon
r_case
id|_DRM_FRAME_BUFFER
suffix:colon
macro_line|#ifndef __sparc__
r_if
c_cond
(paren
id|map-&gt;offset
op_plus
id|map-&gt;size
OL
id|map-&gt;offset
op_logical_or
id|map-&gt;offset
OL
id|virt_to_phys
c_func
(paren
id|high_memory
)paren
)paren
(brace
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MTRR
r_if
c_cond
(paren
id|map-&gt;type
op_eq
id|_DRM_FRAME_BUFFER
op_logical_or
(paren
id|map-&gt;flags
op_amp
id|_DRM_WRITE_COMBINING
)paren
)paren
(brace
id|map-&gt;mtrr
op_assign
id|mtrr_add
c_func
(paren
id|map-&gt;offset
comma
id|map-&gt;size
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
id|map-&gt;handle
op_assign
id|drm_ioremap
c_func
(paren
id|map-&gt;offset
comma
id|map-&gt;size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SHM
suffix:colon
id|map-&gt;handle
op_assign
(paren
r_void
op_star
)paren
id|drm_alloc_pages
c_func
(paren
id|drm_order
c_func
(paren
id|map-&gt;size
)paren
op_minus
id|PAGE_SHIFT
comma
id|DRM_MEM_SAREA
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%ld %d %p&bslash;n&quot;
comma
id|map-&gt;size
comma
id|drm_order
c_func
(paren
id|map-&gt;size
)paren
comma
id|map-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map-&gt;handle
)paren
(brace
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|map-&gt;offset
op_assign
(paren
r_int
r_int
)paren
id|map-&gt;handle
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;flags
op_amp
id|_DRM_CONTAINS_LOCK
)paren
(brace
id|dev-&gt;lock.hw_lock
op_assign
id|map-&gt;handle
suffix:semicolon
multiline_comment|/* Pointer to lock */
)brace
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
r_case
id|_DRM_AGP
suffix:colon
id|map-&gt;offset
op_assign
id|map-&gt;offset
op_plus
id|dev-&gt;agp-&gt;base
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|drm_free
c_func
(paren
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;maplist
)paren
(brace
op_increment
id|dev-&gt;map_count
suffix:semicolon
id|dev-&gt;maplist
op_assign
id|drm_realloc
c_func
(paren
id|dev-&gt;maplist
comma
(paren
id|dev-&gt;map_count
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
comma
id|dev-&gt;map_count
op_star
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;map_count
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;maplist
op_assign
id|drm_alloc
c_func
(paren
id|dev-&gt;map_count
op_star
r_sizeof
(paren
op_star
id|dev-&gt;maplist
)paren
comma
id|DRM_MEM_MAPS
)paren
suffix:semicolon
)brace
id|dev-&gt;maplist
(braket
id|dev-&gt;map_count
op_minus
l_int|1
)braket
op_assign
id|map
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_map_t
op_star
)paren
id|arg
comma
id|map
comma
r_sizeof
(paren
op_star
id|map
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|map-&gt;type
op_ne
id|_DRM_SHM
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
(paren
(paren
id|drm_map_t
op_star
)paren
id|arg
)paren
op_member_access_from_pointer
id|handle
comma
op_amp
id|map-&gt;offset
comma
r_sizeof
(paren
id|map-&gt;offset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_addbufs
r_int
id|drm_addbufs
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|drm_buf_desc_t
id|request
suffix:semicolon
r_int
id|count
suffix:semicolon
r_int
id|order
suffix:semicolon
r_int
id|size
suffix:semicolon
r_int
id|total
suffix:semicolon
r_int
id|page_order
suffix:semicolon
id|drm_buf_entry_t
op_star
id|entry
suffix:semicolon
r_int
r_int
id|page
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
r_int
id|alignment
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|byte_count
suffix:semicolon
r_int
id|page_count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_buf_desc_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|count
op_assign
id|request.count
suffix:semicolon
id|order
op_assign
id|drm_order
c_func
(paren
id|request.size
)paren
suffix:semicolon
id|size
op_assign
l_int|1
op_lshift
id|order
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;count = %d, size = %d (%d), order = %d, queue_count = %d&bslash;n&quot;
comma
id|request.count
comma
id|request.size
comma
id|size
comma
id|order
comma
id|dev-&gt;queue_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|order
template_param
id|DRM_MAX_ORDER
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;queue_count
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* Not while in use */
id|alignment
op_assign
(paren
id|request.flags
op_amp
id|_DRM_PAGE_ALIGN
)paren
ques
c_cond
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:colon
id|size
suffix:semicolon
id|page_order
op_assign
id|order
op_minus
id|PAGE_SHIFT
OG
l_int|0
ques
c_cond
id|order
op_minus
id|PAGE_SHIFT
suffix:colon
l_int|0
suffix:semicolon
id|total
op_assign
id|PAGE_SIZE
op_lshift
id|page_order
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_use
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|entry
op_assign
op_amp
id|dma-&gt;bufs
(braket
id|order
)braket
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;buf_count
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* May only call once for each order */
)brace
id|entry-&gt;buflist
op_assign
id|drm_alloc
c_func
(paren
id|count
op_star
r_sizeof
(paren
op_star
id|entry-&gt;buflist
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;buflist
)paren
(brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|entry-&gt;buflist
comma
l_int|0
comma
id|count
op_star
r_sizeof
(paren
op_star
id|entry-&gt;buflist
)paren
)paren
suffix:semicolon
id|entry-&gt;seglist
op_assign
id|drm_alloc
c_func
(paren
id|count
op_star
r_sizeof
(paren
op_star
id|entry-&gt;seglist
)paren
comma
id|DRM_MEM_SEGS
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry-&gt;seglist
)paren
(brace
id|drm_free
c_func
(paren
id|entry-&gt;buflist
comma
id|count
op_star
r_sizeof
(paren
op_star
id|entry-&gt;buflist
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|entry-&gt;seglist
comma
l_int|0
comma
id|count
op_star
r_sizeof
(paren
op_star
id|entry-&gt;seglist
)paren
)paren
suffix:semicolon
id|dma-&gt;pagelist
op_assign
id|drm_realloc
c_func
(paren
id|dma-&gt;pagelist
comma
id|dma-&gt;page_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;pagelist
)paren
comma
(paren
id|dma-&gt;page_count
op_plus
(paren
id|count
op_lshift
id|page_order
)paren
)paren
op_star
r_sizeof
(paren
op_star
id|dma-&gt;pagelist
)paren
comma
id|DRM_MEM_PAGES
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pagelist: %d entries&bslash;n&quot;
comma
id|dma-&gt;page_count
op_plus
(paren
id|count
op_lshift
id|page_order
)paren
)paren
suffix:semicolon
id|entry-&gt;buf_size
op_assign
id|size
suffix:semicolon
id|entry-&gt;page_order
op_assign
id|page_order
suffix:semicolon
id|byte_count
op_assign
l_int|0
suffix:semicolon
id|page_count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|entry-&gt;buf_count
OL
id|count
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_assign
id|drm_alloc_pages
c_func
(paren
id|page_order
comma
id|DRM_MEM_DMA
)paren
)paren
)paren
r_break
suffix:semicolon
id|entry-&gt;seglist
(braket
id|entry-&gt;seg_count
op_increment
)braket
op_assign
id|page
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
(paren
l_int|1
op_lshift
id|page_order
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;page %d @ 0x%08lx&bslash;n&quot;
comma
id|dma-&gt;page_count
op_plus
id|page_count
comma
id|page
op_plus
id|PAGE_SIZE
op_star
id|i
)paren
suffix:semicolon
id|dma-&gt;pagelist
(braket
id|dma-&gt;page_count
op_plus
id|page_count
op_increment
)braket
op_assign
id|page
op_plus
id|PAGE_SIZE
op_star
id|i
suffix:semicolon
)brace
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
id|offset
op_plus
id|size
op_le
id|total
op_logical_and
id|entry-&gt;buf_count
OL
id|count
suffix:semicolon
id|offset
op_add_assign
id|alignment
comma
op_increment
id|entry-&gt;buf_count
)paren
(brace
id|buf
op_assign
op_amp
id|entry-&gt;buflist
(braket
id|entry-&gt;buf_count
)braket
suffix:semicolon
id|buf-&gt;idx
op_assign
id|dma-&gt;buf_count
op_plus
id|entry-&gt;buf_count
suffix:semicolon
id|buf-&gt;total
op_assign
id|alignment
suffix:semicolon
id|buf-&gt;order
op_assign
id|order
suffix:semicolon
id|buf-&gt;used
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;offset
op_assign
(paren
id|dma-&gt;byte_count
op_plus
id|byte_count
op_plus
id|offset
)paren
suffix:semicolon
id|buf-&gt;address
op_assign
(paren
r_void
op_star
)paren
(paren
id|page
op_plus
id|offset
)paren
suffix:semicolon
id|buf-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|buf-&gt;waiting
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|buf-&gt;dma_wait
)paren
suffix:semicolon
id|buf-&gt;pid
op_assign
l_int|0
suffix:semicolon
macro_line|#if DRM_DMA_HISTOGRAM
id|buf-&gt;time_queued
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;time_dispatched
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;time_completed
op_assign
l_int|0
suffix:semicolon
id|buf-&gt;time_freed
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|DRM_DEBUG
c_func
(paren
l_string|&quot;buffer %d @ %p&bslash;n&quot;
comma
id|entry-&gt;buf_count
comma
id|buf-&gt;address
)paren
suffix:semicolon
)brace
id|byte_count
op_add_assign
id|PAGE_SIZE
op_lshift
id|page_order
suffix:semicolon
)brace
id|dma-&gt;buflist
op_assign
id|drm_realloc
c_func
(paren
id|dma-&gt;buflist
comma
id|dma-&gt;buf_count
op_star
r_sizeof
(paren
op_star
id|dma-&gt;buflist
)paren
comma
(paren
id|dma-&gt;buf_count
op_plus
id|entry-&gt;buf_count
)paren
op_star
r_sizeof
(paren
op_star
id|dma-&gt;buflist
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|dma-&gt;buf_count
suffix:semicolon
id|i
OL
id|dma-&gt;buf_count
op_plus
id|entry-&gt;buf_count
suffix:semicolon
id|i
op_increment
)paren
id|dma-&gt;buflist
(braket
id|i
)braket
op_assign
op_amp
id|entry-&gt;buflist
(braket
id|i
op_minus
id|dma-&gt;buf_count
)braket
suffix:semicolon
id|dma-&gt;buf_count
op_add_assign
id|entry-&gt;buf_count
suffix:semicolon
id|dma-&gt;seg_count
op_add_assign
id|entry-&gt;seg_count
suffix:semicolon
id|dma-&gt;page_count
op_add_assign
id|entry-&gt;seg_count
op_lshift
id|page_order
suffix:semicolon
id|dma-&gt;byte_count
op_add_assign
id|PAGE_SIZE
op_star
(paren
id|entry-&gt;seg_count
op_lshift
id|page_order
)paren
suffix:semicolon
id|drm_freelist_create
c_func
(paren
op_amp
id|entry-&gt;freelist
comma
id|entry-&gt;buf_count
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
id|entry-&gt;buf_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|drm_freelist_put
c_func
(paren
id|dev
comma
op_amp
id|entry-&gt;freelist
comma
op_amp
id|entry-&gt;buflist
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|request.count
op_assign
id|entry-&gt;buf_count
suffix:semicolon
id|request.size
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_buf_desc_t
op_star
)paren
id|arg
comma
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_infobufs
r_int
id|drm_infobufs
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|drm_buf_info_t
id|request
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|count
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
op_increment
id|dev-&gt;buf_use
suffix:semicolon
multiline_comment|/* Can&squot;t allocate more after this call */
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_buf_info_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
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
id|DRM_MAX_ORDER
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
)paren
op_increment
id|count
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;count = %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request.count
op_ge
id|count
)paren
(brace
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
id|DRM_MAX_ORDER
op_plus
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|count
)braket
dot
id|count
comma
op_amp
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
comma
r_sizeof
(paren
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|buf_count
)paren
)paren
op_logical_or
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|count
)braket
dot
id|size
comma
op_amp
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_size
comma
r_sizeof
(paren
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|buf_size
)paren
)paren
op_logical_or
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|count
)braket
dot
id|low_mark
comma
op_amp
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|freelist.low_mark
comma
r_sizeof
(paren
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|freelist.low_mark
)paren
)paren
op_logical_or
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|count
)braket
dot
id|high_mark
comma
op_amp
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|freelist.high_mark
comma
r_sizeof
(paren
id|dma-&gt;bufs
(braket
l_int|0
)braket
dot
id|freelist.high_mark
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d %d %d %d %d&bslash;n&quot;
comma
id|i
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_count
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|buf_size
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|freelist.low_mark
comma
id|dma-&gt;bufs
(braket
id|i
)braket
dot
id|freelist.high_mark
)paren
suffix:semicolon
op_increment
id|count
suffix:semicolon
)brace
)brace
)brace
id|request.count
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_buf_info_t
op_star
)paren
id|arg
comma
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_markbufs
r_int
id|drm_markbufs
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|drm_buf_desc_t
id|request
suffix:semicolon
r_int
id|order
suffix:semicolon
id|drm_buf_entry_t
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_buf_desc_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d, %d, %d&bslash;n&quot;
comma
id|request.size
comma
id|request.low_mark
comma
id|request.high_mark
)paren
suffix:semicolon
id|order
op_assign
id|drm_order
c_func
(paren
id|request.size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|order
template_param
id|DRM_MAX_ORDER
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|entry
op_assign
op_amp
id|dma-&gt;bufs
(braket
id|order
)braket
suffix:semicolon
r_if
c_cond
(paren
id|request.low_mark
template_param
id|entry-&gt;buf_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|request.high_mark
template_param
id|entry-&gt;buf_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|entry-&gt;freelist.low_mark
op_assign
id|request.low_mark
suffix:semicolon
id|entry-&gt;freelist.high_mark
op_assign
id|request.high_mark
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_freebufs
r_int
id|drm_freebufs
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
id|drm_buf_free_t
id|request
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|idx
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_buf_free_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|request.count
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
id|request.count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|idx
comma
op_amp
id|request.list
(braket
id|i
)braket
comma
r_sizeof
(paren
id|idx
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|idx
OL
l_int|0
op_logical_or
id|idx
op_ge
id|dma-&gt;buf_count
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Index %d (of %d max)&bslash;n&quot;
comma
id|idx
comma
id|dma-&gt;buf_count
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|buf
op_assign
id|dma-&gt;buflist
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;pid
op_ne
id|current-&gt;pid
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d freeing buffer owned by %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|buf-&gt;pid
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|drm_free_buffer
c_func
(paren
id|dev
comma
id|buf
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_mapbufs
r_int
id|drm_mapbufs
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
(brace
id|drm_file_t
op_star
id|priv
op_assign
id|filp-&gt;private_data
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|drm_device_dma_t
op_star
id|dma
op_assign
id|dev-&gt;dma
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
r_const
r_int
id|zero
op_assign
l_int|0
suffix:semicolon
r_int
r_int
r_virtual
suffix:semicolon
r_int
r_int
id|address
suffix:semicolon
id|drm_buf_map_t
id|request
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
)paren
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
op_increment
id|dev-&gt;buf_use
suffix:semicolon
multiline_comment|/* Can&squot;t allocate more after this call */
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|request
comma
(paren
id|drm_buf_map_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|request.count
op_ge
id|dma-&gt;buf_count
)paren
(brace
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_virtual
op_assign
id|do_mmap
c_func
(paren
id|filp
comma
l_int|0
comma
id|dma-&gt;byte_count
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_SHARED
comma
l_int|0
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
r_virtual
OG
op_minus
l_int|1024UL
)paren
(brace
multiline_comment|/* Real error */
id|retcode
op_assign
(paren
r_int
r_int
)paren
r_virtual
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|request
dot
r_virtual
op_assign
(paren
r_void
op_star
)paren
r_virtual
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
id|dma-&gt;buf_count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|i
)braket
dot
id|idx
comma
op_amp
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|idx
comma
r_sizeof
(paren
id|request.list
(braket
l_int|0
)braket
dot
id|idx
)paren
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|i
)braket
dot
id|total
comma
op_amp
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|total
comma
r_sizeof
(paren
id|request.list
(braket
l_int|0
)braket
dot
id|total
)paren
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|i
)braket
dot
id|used
comma
op_amp
id|zero
comma
r_sizeof
(paren
id|zero
)paren
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
id|address
op_assign
r_virtual
op_plus
id|dma-&gt;buflist
(braket
id|i
)braket
op_member_access_from_pointer
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|request.list
(braket
id|i
)braket
dot
id|address
comma
op_amp
id|address
comma
r_sizeof
(paren
id|address
)paren
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EFAULT
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
)brace
)brace
id|done
suffix:colon
id|request.count
op_assign
id|dma-&gt;buf_count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d buffers, retcode = %d&bslash;n&quot;
comma
id|request.count
comma
id|retcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_buf_map_t
op_star
)paren
id|arg
comma
op_amp
id|request
comma
r_sizeof
(paren
id|request
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
eof
