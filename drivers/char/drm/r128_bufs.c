multiline_comment|/* r128_bufs.c -- IOCTLs to manage buffers -*- linux-c -*-&n; * Created: Wed Apr 12 16:19:08 2000 by kevin@precisioninsight.com&n; *&n; * Copyright 2000 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors: Kevin E. Martin &lt;martin@valinux.com&gt;&n; *          Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&t;    Jeff Hartmann &lt;jhartmann@valinux.com&gt;&n; * &n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;r128_drv.h&quot;
macro_line|#include &quot;linux/un.h&quot;
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
DECL|function|r128_addbufs_agp
r_int
id|r128_addbufs_agp
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
id|drm_buf_entry_t
op_star
id|entry
suffix:semicolon
id|drm_buf_t
op_star
id|buf
suffix:semicolon
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|agp_offset
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
id|alignment
suffix:semicolon
r_int
id|page_order
suffix:semicolon
r_int
id|total
suffix:semicolon
r_int
id|byte_count
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
id|byte_count
op_assign
l_int|0
suffix:semicolon
id|agp_offset
op_assign
id|dev-&gt;agp-&gt;base
op_plus
id|request.agp_start
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;count:      %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;order:      %d&bslash;n&quot;
comma
id|order
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;size:       %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;agp_offset: %ld&bslash;n&quot;
comma
id|agp_offset
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;alignment:  %d&bslash;n&quot;
comma
id|alignment
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;page_order: %d&bslash;n&quot;
comma
id|page_order
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;total:      %d&bslash;n&quot;
comma
id|total
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
id|entry-&gt;buf_size
op_assign
id|size
suffix:semicolon
id|entry-&gt;page_order
op_assign
id|page_order
suffix:semicolon
id|offset
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
l_int|0
suffix:semicolon
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
id|agp_offset
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
id|buf-&gt;dev_priv_size
op_assign
r_sizeof
(paren
id|drm_r128_buf_priv_t
)paren
suffix:semicolon
id|buf-&gt;dev_private
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
id|drm_r128_buf_priv_t
)paren
comma
id|DRM_MEM_BUFS
)paren
suffix:semicolon
id|memset
c_func
(paren
id|buf-&gt;dev_private
comma
l_int|0
comma
id|buf-&gt;dev_priv_size
)paren
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
id|byte_count
op_add_assign
id|PAGE_SIZE
op_lshift
id|page_order
suffix:semicolon
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;byte_count: %d&bslash;n&quot;
comma
id|byte_count
)paren
suffix:semicolon
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
id|dma-&gt;byte_count
op_add_assign
id|byte_count
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
id|dma-&gt;flags
op_assign
id|_DRM_DMA_USE_AGP
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
macro_line|#endif
DECL|function|r128_addbufs
r_int
id|r128_addbufs
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
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
suffix:semicolon
id|drm_buf_desc_t
id|request
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev_priv
op_logical_or
id|dev_priv-&gt;is_pci
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
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
r_if
c_cond
(paren
id|request.flags
op_amp
id|_DRM_AGP_BUFFER
)paren
r_return
id|r128_addbufs_agp
c_func
(paren
id|inode
comma
id|filp
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_else
macro_line|#endif
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|r128_mapbufs
r_int
id|r128_mapbufs
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
id|drm_r128_private_t
op_star
id|dev_priv
op_assign
id|dev-&gt;dev_private
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
op_logical_or
op_logical_neg
id|dev_priv
op_logical_or
id|dev_priv-&gt;is_pci
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
r_if
c_cond
(paren
id|dma-&gt;flags
op_amp
id|_DRM_DMA_USE_AGP
)paren
(brace
id|drm_map_t
op_star
id|map
suffix:semicolon
id|map
op_assign
id|dev_priv-&gt;agp_vertbufs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|map
)paren
(brace
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|done
suffix:semicolon
)brace
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
id|map-&gt;size
comma
id|PROT_READ
op_or
id|PROT_WRITE
comma
id|MAP_SHARED
comma
(paren
r_int
r_int
)paren
id|map-&gt;offset
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
)brace
r_else
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
)brace
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
