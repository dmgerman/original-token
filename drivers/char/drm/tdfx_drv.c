multiline_comment|/* tdfx_drv.c -- tdfx driver -*- linux-c -*-&n; * Created: Thu Oct  7 10:38:32 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Daryll Strauss &lt;daryll@valinux.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;tdfx_drv.h&quot;
DECL|macro|TDFX_NAME
mdefine_line|#define TDFX_NAME&t; &quot;tdfx&quot;
DECL|macro|TDFX_DESC
mdefine_line|#define TDFX_DESC&t; &quot;3dfx Banshee/Voodoo3+&quot;
DECL|macro|TDFX_DATE
mdefine_line|#define TDFX_DATE&t; &quot;20000928&quot;
DECL|macro|TDFX_MAJOR
mdefine_line|#define TDFX_MAJOR&t; 1
DECL|macro|TDFX_MINOR
mdefine_line|#define TDFX_MINOR&t; 0
DECL|macro|TDFX_PATCHLEVEL
mdefine_line|#define TDFX_PATCHLEVEL  0
DECL|variable|tdfx_device
r_static
id|drm_device_t
id|tdfx_device
suffix:semicolon
DECL|variable|tdfx_res_ctx
id|drm_ctx_t
id|tdfx_res_ctx
suffix:semicolon
DECL|variable|tdfx_fops
r_static
r_struct
id|file_operations
id|tdfx_fops
op_assign
(brace
macro_line|#if LINUX_VERSION_CODE &gt;= 0x020400
multiline_comment|/* This started being used during 2.4.0-test */
id|owner
suffix:colon
id|THIS_MODULE
comma
macro_line|#endif
id|open
suffix:colon
id|tdfx_open
comma
id|flush
suffix:colon
id|drm_flush
comma
id|release
suffix:colon
id|tdfx_release
comma
id|ioctl
suffix:colon
id|tdfx_ioctl
comma
id|mmap
suffix:colon
id|drm_mmap
comma
id|read
suffix:colon
id|drm_read
comma
id|fasync
suffix:colon
id|drm_fasync
comma
id|poll
suffix:colon
id|drm_poll
comma
)brace
suffix:semicolon
DECL|variable|tdfx_misc
r_static
r_struct
id|miscdevice
id|tdfx_misc
op_assign
(brace
id|minor
suffix:colon
id|MISC_DYNAMIC_MINOR
comma
id|name
suffix:colon
id|TDFX_NAME
comma
id|fops
suffix:colon
op_amp
id|tdfx_fops
comma
)brace
suffix:semicolon
DECL|variable|tdfx_ioctls
r_static
id|drm_ioctl_desc_t
id|tdfx_ioctls
(braket
)braket
op_assign
(brace
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_VERSION
)paren
)braket
op_assign
(brace
id|tdfx_version
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_UNIQUE
)paren
)braket
op_assign
(brace
id|drm_getunique
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_MAGIC
)paren
)braket
op_assign
(brace
id|drm_getmagic
comma
l_int|0
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_IRQ_BUSID
)paren
)braket
op_assign
(brace
id|drm_irq_busid
comma
l_int|0
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SET_UNIQUE
)paren
)braket
op_assign
(brace
id|drm_setunique
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_BLOCK
)paren
)braket
op_assign
(brace
id|drm_block
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_UNBLOCK
)paren
)braket
op_assign
(brace
id|drm_unblock
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AUTH_MAGIC
)paren
)braket
op_assign
(brace
id|drm_authmagic
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_MAP
)paren
)braket
op_assign
(brace
id|drm_addmap
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_CTX
)paren
)braket
op_assign
(brace
id|tdfx_addctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RM_CTX
)paren
)braket
op_assign
(brace
id|tdfx_rmctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_MOD_CTX
)paren
)braket
op_assign
(brace
id|tdfx_modctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_GET_CTX
)paren
)braket
op_assign
(brace
id|tdfx_getctx
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_SWITCH_CTX
)paren
)braket
op_assign
(brace
id|tdfx_switchctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_NEW_CTX
)paren
)braket
op_assign
(brace
id|tdfx_newctx
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RES_CTX
)paren
)braket
op_assign
(brace
id|tdfx_resctx
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_ADD_DRAW
)paren
)braket
op_assign
(brace
id|drm_adddraw
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_RM_DRAW
)paren
)braket
op_assign
(brace
id|drm_rmdraw
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_LOCK
)paren
)braket
op_assign
(brace
id|tdfx_lock
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_UNLOCK
)paren
)braket
op_assign
(brace
id|tdfx_unlock
comma
l_int|1
comma
l_int|0
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_FINISH
)paren
)braket
op_assign
(brace
id|drm_finish
comma
l_int|1
comma
l_int|0
)brace
comma
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ACQUIRE
)paren
)braket
op_assign
(brace
id|drm_agp_acquire
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_RELEASE
)paren
)braket
op_assign
(brace
id|drm_agp_release
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ENABLE
)paren
)braket
op_assign
(brace
id|drm_agp_enable
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_INFO
)paren
)braket
op_assign
(brace
id|drm_agp_info
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_ALLOC
)paren
)braket
op_assign
(brace
id|drm_agp_alloc
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_FREE
)paren
)braket
op_assign
(brace
id|drm_agp_free
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_BIND
)paren
)braket
op_assign
(brace
id|drm_agp_unbind
comma
l_int|1
comma
l_int|1
)brace
comma
(braket
id|DRM_IOCTL_NR
c_func
(paren
id|DRM_IOCTL_AGP_UNBIND
)paren
)braket
op_assign
(brace
id|drm_agp_bind
comma
l_int|1
comma
l_int|1
)brace
comma
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|TDFX_IOCTL_COUNT
mdefine_line|#define TDFX_IOCTL_COUNT DRM_ARRAY_SIZE(tdfx_ioctls)
macro_line|#ifdef MODULE
DECL|variable|tdfx
r_static
r_char
op_star
id|tdfx
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;VA Linux Systems, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;tdfx&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tdfx
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
macro_line|#ifndef MODULE
multiline_comment|/* tdfx_options is called by the kernel to parse command-line options&n; * passed via the boot-loader (e.g., LILO).  It calls the insmod option&n; * routine, drm_parse_drm.&n; */
DECL|function|tdfx_options
r_static
r_int
id|__init
id|tdfx_options
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|drm_parse_options
c_func
(paren
id|str
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;tdfx=&quot;
comma
id|tdfx_options
)paren
suffix:semicolon
macro_line|#endif
DECL|function|tdfx_setup
r_static
r_int
id|tdfx_setup
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;vma_count
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;buf_use
op_assign
l_int|0
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;buf_alloc
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_open
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_close
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_ioctl
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_irq
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_ctx
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_locks
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_unlocks
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_contends
comma
l_int|0
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|dev-&gt;total_sleeps
comma
l_int|0
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
id|DRM_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
id|dev-&gt;maplist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;map_count
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;vmalist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;lock.hw_lock
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
)paren
suffix:semicolon
id|dev-&gt;queue_count
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queue_reserved
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queue_slots
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;queuelist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;irq
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;context_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;dma
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;dma_flag
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_context
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_switch
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;last_checked
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;context_wait
)paren
suffix:semicolon
id|dev-&gt;ctx_start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;lck_start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;buf_rp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|dev-&gt;buf_wp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|dev-&gt;buf_end
op_assign
id|dev-&gt;buf
op_plus
id|DRM_BSZ
suffix:semicolon
id|dev-&gt;buf_async
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|dev-&gt;buf_writers
)paren
suffix:semicolon
id|tdfx_res_ctx.handle
op_assign
op_minus
l_int|1
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* The kernel&squot;s context could be created here, but is now created&n;&t;   in drm_dma_enqueue.&t;This is more resource-efficient for&n;&t;   hardware that does not do DMA, but may mean that&n;&t;   drm_select_queue fails between the time the interrupt is&n;&t;   initialized and the time the queues are initialized. */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tdfx_takedown
r_static
r_int
id|tdfx_takedown
c_func
(paren
id|drm_device_t
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
id|drm_magic_entry_t
op_star
id|pt
comma
op_star
id|next
suffix:semicolon
id|drm_map_t
op_star
id|map
suffix:semicolon
id|drm_vma_entry_t
op_star
id|vma
comma
op_star
id|vma_next
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|dev-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;devname
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;devname
comma
id|strlen
c_func
(paren
id|dev-&gt;devname
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;devname
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;unique
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;unique
comma
id|strlen
c_func
(paren
id|dev-&gt;unique
)paren
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|dev-&gt;unique
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;unique_len
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Clear pid list */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|DRM_HASH_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
suffix:semicolon
id|pt
suffix:semicolon
id|pt
op_assign
id|next
)paren
(brace
id|next
op_assign
id|pt-&gt;next
suffix:semicolon
id|drm_free
c_func
(paren
id|pt
comma
r_sizeof
(paren
op_star
id|pt
)paren
comma
id|DRM_MEM_MAGIC
)paren
suffix:semicolon
)brace
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|head
op_assign
id|dev-&gt;magiclist
(braket
id|i
)braket
dot
id|tail
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
multiline_comment|/* Clear AGP information */
r_if
c_cond
(paren
id|dev-&gt;agp
)paren
(brace
id|drm_agp_mem_t
op_star
id|temp
suffix:semicolon
id|drm_agp_mem_t
op_star
id|temp_next
suffix:semicolon
id|temp
op_assign
id|dev-&gt;agp-&gt;memory
suffix:semicolon
r_while
c_loop
(paren
id|temp
op_ne
l_int|NULL
)paren
(brace
id|temp_next
op_assign
id|temp-&gt;next
suffix:semicolon
id|drm_free_agp
c_func
(paren
id|temp-&gt;memory
comma
id|temp-&gt;pages
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|temp
comma
r_sizeof
(paren
op_star
id|temp
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
id|temp
op_assign
id|temp_next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;agp-&gt;acquired
)paren
id|_drm_agp_release
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Clear vma list (only built for debugging) */
r_if
c_cond
(paren
id|dev-&gt;vmalist
)paren
(brace
r_for
c_loop
(paren
id|vma
op_assign
id|dev-&gt;vmalist
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma_next
)paren
(brace
id|vma_next
op_assign
id|vma-&gt;next
suffix:semicolon
id|drm_free
c_func
(paren
id|vma
comma
r_sizeof
(paren
op_star
id|vma
)paren
comma
id|DRM_MEM_VMAS
)paren
suffix:semicolon
)brace
id|dev-&gt;vmalist
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Clear map area and mtrr information */
r_if
c_cond
(paren
id|dev-&gt;maplist
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
id|dev-&gt;map_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|map
op_assign
id|dev-&gt;maplist
(braket
id|i
)braket
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
macro_line|#ifdef CONFIG_MTRR
r_if
c_cond
(paren
id|map-&gt;mtrr
op_ge
l_int|0
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|retcode
op_assign
id|mtrr_del
c_func
(paren
id|map-&gt;mtrr
comma
id|map-&gt;offset
comma
id|map-&gt;size
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;mtrr_del = %d&bslash;n&quot;
comma
id|retcode
)paren
suffix:semicolon
)brace
macro_line|#endif
id|drm_ioremapfree
c_func
(paren
id|map-&gt;handle
comma
id|map-&gt;size
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|_DRM_SHM
suffix:colon
id|drm_free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|map-&gt;handle
comma
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
r_break
suffix:semicolon
r_case
id|_DRM_AGP
suffix:colon
multiline_comment|/* Do nothing here, because this is all&n;                                   handled in the AGP/GART driver. */
r_break
suffix:semicolon
)brace
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
)brace
id|drm_free
c_func
(paren
id|dev-&gt;maplist
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
id|dev-&gt;maplist
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;map_count
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;lock.hw_lock
)paren
(brace
id|dev-&gt;lock.hw_lock
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* SHM removed */
id|dev-&gt;lock.pid
op_assign
l_int|0
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* tdfx_init is called via init_module at module load time, or via&n; * linux/init/main.c (this is not currently supported). */
DECL|function|tdfx_init
r_static
r_int
id|__init
id|tdfx_init
c_func
(paren
r_void
)paren
(brace
r_int
id|retcode
suffix:semicolon
id|drm_device_t
op_star
id|dev
op_assign
op_amp
id|tdfx_device
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|dev
)paren
)paren
suffix:semicolon
id|dev-&gt;count_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|dev-&gt;struct_sem
comma
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef MODULE
id|drm_parse_options
c_func
(paren
id|tdfx
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|misc_register
c_func
(paren
op_amp
id|tdfx_misc
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot register &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|TDFX_NAME
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
id|dev-&gt;device
op_assign
id|MKDEV
c_func
(paren
id|MISC_MAJOR
comma
id|tdfx_misc.minor
)paren
suffix:semicolon
id|dev-&gt;name
op_assign
id|TDFX_NAME
suffix:semicolon
id|drm_mem_init
c_func
(paren
)paren
suffix:semicolon
id|drm_proc_init
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
id|dev-&gt;agp
op_assign
id|drm_agp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
(paren
id|retcode
op_assign
id|drm_ctxbitmap_init
c_func
(paren
id|dev
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot allocate memory for context bitmap.&bslash;n&quot;
)paren
suffix:semicolon
id|drm_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
id|misc_deregister
c_func
(paren
op_amp
id|tdfx_misc
)paren
suffix:semicolon
id|tdfx_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
id|DRM_INFO
c_func
(paren
l_string|&quot;Initialized %s %d.%d.%d %s on minor %d&bslash;n&quot;
comma
id|TDFX_NAME
comma
id|TDFX_MAJOR
comma
id|TDFX_MINOR
comma
id|TDFX_PATCHLEVEL
comma
id|TDFX_DATE
comma
id|tdfx_misc.minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* tdfx_cleanup is called via cleanup_module at module unload time. */
DECL|function|tdfx_cleanup
r_static
r_void
id|__exit
id|tdfx_cleanup
c_func
(paren
r_void
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
op_amp
id|tdfx_device
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|drm_proc_cleanup
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|misc_deregister
c_func
(paren
op_amp
id|tdfx_misc
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot unload module&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|DRM_INFO
c_func
(paren
l_string|&quot;Module unloaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|drm_ctxbitmap_cleanup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|tdfx_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_AGP) || defined(CONFIG_AGP_MODULE)
r_if
c_cond
(paren
id|dev-&gt;agp
)paren
(brace
id|drm_agp_uninit
c_func
(paren
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|dev-&gt;agp
comma
r_sizeof
(paren
op_star
id|dev-&gt;agp
)paren
comma
id|DRM_MEM_AGPLISTS
)paren
suffix:semicolon
id|dev-&gt;agp
op_assign
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|variable|tdfx_init
id|module_init
c_func
(paren
id|tdfx_init
)paren
suffix:semicolon
DECL|variable|tdfx_cleanup
id|module_exit
c_func
(paren
id|tdfx_cleanup
)paren
suffix:semicolon
DECL|function|tdfx_version
r_int
id|tdfx_version
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
id|drm_version_t
id|version
suffix:semicolon
r_int
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|version
comma
(paren
id|drm_version_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|version
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
DECL|macro|DRM_COPY
mdefine_line|#define DRM_COPY(name,value)&t;&t;&t;&t;     &bslash;&n;&t;len = strlen(value);&t;&t;&t;&t;     &bslash;&n;&t;if (len &gt; name##_len) len = name##_len;&t;&t;     &bslash;&n;&t;name##_len = strlen(value);&t;&t;&t;     &bslash;&n;&t;if (len &amp;&amp; name) {&t;&t;&t;&t;     &bslash;&n;&t;&t;if (copy_to_user(name, value, len))&t;     &bslash;&n;&t;&t;&t;return -EFAULT;&t;&t;&t;     &bslash;&n;&t;}
id|version.version_major
op_assign
id|TDFX_MAJOR
suffix:semicolon
id|version.version_minor
op_assign
id|TDFX_MINOR
suffix:semicolon
id|version.version_patchlevel
op_assign
id|TDFX_PATCHLEVEL
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.name
comma
id|TDFX_NAME
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.date
comma
id|TDFX_DATE
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.desc
comma
id|TDFX_DESC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_version_t
op_star
)paren
id|arg
comma
op_amp
id|version
comma
r_sizeof
(paren
id|version
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
DECL|function|tdfx_open
r_int
id|tdfx_open
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
)paren
(brace
id|drm_device_t
op_star
id|dev
op_assign
op_amp
id|tdfx_device
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;open_count = %d&bslash;n&quot;
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|retcode
op_assign
id|drm_open_helper
c_func
(paren
id|inode
comma
id|filp
comma
id|dev
)paren
)paren
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020333
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/* Needed before Linux 2.3.51 */
macro_line|#endif
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_open
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
op_logical_neg
id|dev-&gt;open_count
op_increment
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
id|tdfx_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
)brace
r_return
id|retcode
suffix:semicolon
)brace
DECL|function|tdfx_release
r_int
id|tdfx_release
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
suffix:semicolon
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|dev
op_assign
id|priv-&gt;dev
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;open_count = %d&bslash;n&quot;
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|retcode
op_assign
id|drm_release
c_func
(paren
id|inode
comma
id|filp
)paren
)paren
)paren
(brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020333
id|MOD_DEC_USE_COUNT
suffix:semicolon
multiline_comment|/* Needed before Linux 2.3.51 */
macro_line|#endif
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_close
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
op_logical_neg
op_decrement
id|dev-&gt;open_count
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
op_logical_or
id|dev-&gt;blocked
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Device busy: %d %d&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
comma
id|dev-&gt;blocked
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|tdfx_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|dev-&gt;count_lock
)paren
suffix:semicolon
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
multiline_comment|/* tdfx_ioctl is called whenever a process performs an ioctl on /dev/drm. */
DECL|function|tdfx_ioctl
r_int
id|tdfx_ioctl
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
r_int
id|nr
op_assign
id|DRM_IOCTL_NR
c_func
(paren
id|cmd
)paren
suffix:semicolon
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
r_int
id|retcode
op_assign
l_int|0
suffix:semicolon
id|drm_ioctl_desc_t
op_star
id|ioctl
suffix:semicolon
id|drm_ioctl_t
op_star
id|func
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_ioctl
)paren
suffix:semicolon
op_increment
id|priv-&gt;ioctl_count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, cmd = 0x%02x, nr = 0x%02x, dev 0x%x, auth = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|cmd
comma
id|nr
comma
id|dev-&gt;device
comma
id|priv-&gt;authenticated
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nr
op_ge
id|TDFX_IOCTL_COUNT
)paren
(brace
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
(brace
id|ioctl
op_assign
op_amp
id|tdfx_ioctls
(braket
id|nr
)braket
suffix:semicolon
id|func
op_assign
id|ioctl-&gt;func
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|func
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;no function&bslash;n&quot;
)paren
suffix:semicolon
id|retcode
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|ioctl-&gt;root_only
op_logical_and
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
op_logical_or
(paren
id|ioctl-&gt;auth_needed
op_logical_and
op_logical_neg
id|priv-&gt;authenticated
)paren
)paren
(brace
id|retcode
op_assign
op_minus
id|EACCES
suffix:semicolon
)brace
r_else
(brace
id|retcode
op_assign
(paren
id|func
)paren
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
)brace
)brace
id|atomic_dec
c_func
(paren
op_amp
id|dev-&gt;ioctl_count
)paren
suffix:semicolon
r_return
id|retcode
suffix:semicolon
)brace
DECL|function|tdfx_lock
r_int
id|tdfx_lock
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
id|DECLARE_WAITQUEUE
c_func
(paren
id|entry
comma
id|current
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
id|drm_lock_t
id|lock
suffix:semicolon
macro_line|#if DRM_DMA_HISTOGRAM
id|cycles_t
id|start
suffix:semicolon
id|dev-&gt;lck_start
op_assign
id|start
op_assign
id|get_cycles
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|lock
comma
(paren
id|drm_lock_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|lock
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
id|lock.context
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using kernel context %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|lock.context
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d (pid %d) requests lock (0x%08x), flags = 0x%08x&bslash;n&quot;
comma
id|lock.context
comma
id|current-&gt;pid
comma
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|lock.flags
)paren
suffix:semicolon
macro_line|#if 0
multiline_comment|/* dev-&gt;queue_count == 0 right now for&n;                                   tdfx.  FIXME? */
r_if
c_cond
(paren
id|lock.context
OL
l_int|0
op_logical_or
id|lock.context
op_ge
id|dev-&gt;queue_count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
op_ne
id|lock.context
)paren
(brace
r_int
id|j
op_assign
id|jiffies
op_minus
id|dev-&gt;lock.lock_time
suffix:semicolon
r_if
c_cond
(paren
id|lock.context
op_eq
id|tdfx_res_ctx.handle
op_logical_and
id|j
op_ge
l_int|0
op_logical_and
id|j
OL
id|DRM_LOCK_SLICE
)paren
(brace
multiline_comment|/* Can&squot;t take lock if we just had it and&n;                                   there is contention. */
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d (pid %d) delayed j=%d dev=%d jiffies=%d&bslash;n&quot;
comma
id|lock.context
comma
id|current-&gt;pid
comma
id|j
comma
id|dev-&gt;lock.lock_time
comma
id|jiffies
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|DRM_LOCK_SLICE
op_minus
id|j
)paren
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;jiffies=%d&bslash;n&quot;
comma
id|jiffies
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|add_wait_queue
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;lock.hw_lock
)paren
(brace
multiline_comment|/* Device has been unregistered */
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drm_lock_take
c_func
(paren
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|lock.context
)paren
)paren
(brace
id|dev-&gt;lock.pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|dev-&gt;lock.lock_time
op_assign
id|jiffies
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_locks
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Got lock */
)brace
multiline_comment|/* Contention */
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_sleeps
)paren
suffix:semicolon
macro_line|#if 1
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
macro_line|#endif
id|schedule
c_func
(paren
)paren
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
(brace
id|ret
op_assign
op_minus
id|ERESTARTSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev-&gt;lock.lock_queue
comma
op_amp
id|entry
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|dev-&gt;last_context
op_ne
id|lock.context
op_logical_and
id|lock.context
op_ne
id|tdfx_res_ctx.handle
op_logical_and
id|dev-&gt;last_context
op_ne
id|tdfx_res_ctx.handle
)paren
(brace
id|add_wait_queue
c_func
(paren
op_amp
id|dev-&gt;context_wait
comma
op_amp
id|entry
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
multiline_comment|/* PRE: dev-&gt;last_context != lock.context */
id|tdfx_context_switch
c_func
(paren
id|dev
comma
id|dev-&gt;last_context
comma
id|lock.context
)paren
suffix:semicolon
multiline_comment|/* POST: we will wait for the context&n;                   switch and will dispatch on a later call&n;                   when dev-&gt;last_context == lock.context&n;                   NOTE WE HOLD THE LOCK THROUGHOUT THIS&n;                   TIME! */
id|current-&gt;policy
op_or_assign
id|SCHED_YIELD
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|remove_wait_queue
c_func
(paren
op_amp
id|dev-&gt;context_wait
comma
op_amp
id|entry
)paren
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
(brace
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;last_context
op_ne
id|lock.context
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Context mismatch: %d %d&bslash;n&quot;
comma
id|dev-&gt;last_context
comma
id|lock.context
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
id|sigemptyset
c_func
(paren
op_amp
id|dev-&gt;sigmask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGSTOP
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTSTP
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTTIN
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|dev-&gt;sigmask
comma
id|SIGTTOU
)paren
suffix:semicolon
id|dev-&gt;sigdata.context
op_assign
id|lock.context
suffix:semicolon
id|dev-&gt;sigdata.lock
op_assign
id|dev-&gt;lock.hw_lock
suffix:semicolon
id|block_all_signals
c_func
(paren
id|drm_notifier
comma
op_amp
id|dev-&gt;sigdata
comma
op_amp
id|dev-&gt;sigmask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lock.flags
op_amp
id|_DRM_LOCK_READY
)paren
(brace
multiline_comment|/* Wait for space in DMA/FIFO */
)brace
r_if
c_cond
(paren
id|lock.flags
op_amp
id|_DRM_LOCK_QUIESCENT
)paren
(brace
multiline_comment|/* Make hardware quiescent */
macro_line|#if 0
id|tdfx_quiescent
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020400
r_if
c_cond
(paren
id|lock.context
op_ne
id|tdfx_res_ctx.handle
)paren
(brace
id|current-&gt;counter
op_assign
l_int|5
suffix:semicolon
id|current-&gt;priority
op_assign
id|DEF_PRIORITY
op_div
l_int|4
suffix:semicolon
)brace
macro_line|#endif
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d %s&bslash;n&quot;
comma
id|lock.context
comma
id|ret
ques
c_cond
l_string|&quot;interrupted&quot;
suffix:colon
l_string|&quot;has lock&quot;
)paren
suffix:semicolon
macro_line|#if DRM_DMA_HISTOGRAM
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;histo.lacq
(braket
id|drm_histogram_slot
c_func
(paren
id|get_cycles
c_func
(paren
)paren
op_minus
id|start
)paren
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|tdfx_unlock
r_int
id|tdfx_unlock
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
id|drm_lock_t
id|lock
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|lock
comma
(paren
id|drm_lock_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|lock
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
id|lock.context
op_eq
id|DRM_KERNEL_CONTEXT
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d using kernel context %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|lock.context
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d frees lock (%d holds)&bslash;n&quot;
comma
id|lock.context
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_unlocks
)paren
suffix:semicolon
r_if
c_cond
(paren
id|_DRM_LOCK_IS_CONT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;total_contends
)paren
suffix:semicolon
id|drm_lock_transfer
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|DRM_KERNEL_CONTEXT
)paren
suffix:semicolon
multiline_comment|/* FIXME: Try to send data to card here */
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;context_flag
)paren
(brace
r_if
c_cond
(paren
id|drm_lock_free
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|DRM_KERNEL_CONTEXT
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020400
r_if
c_cond
(paren
id|lock.context
op_ne
id|tdfx_res_ctx.handle
)paren
(brace
id|current-&gt;counter
op_assign
l_int|5
suffix:semicolon
id|current-&gt;priority
op_assign
id|DEF_PRIORITY
suffix:semicolon
)brace
macro_line|#endif
id|unblock_all_signals
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
