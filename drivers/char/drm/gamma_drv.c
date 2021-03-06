multiline_comment|/* gamma.c -- 3dlabs GMX 2000 driver -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; *&n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; *&n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &quot;gamma_drv.h&quot;
macro_line|#ifndef PCI_DEVICE_ID_3DLABS_GAMMA
DECL|macro|PCI_DEVICE_ID_3DLABS_GAMMA
mdefine_line|#define PCI_DEVICE_ID_3DLABS_GAMMA 0x0008
macro_line|#endif
macro_line|#ifndef PCI_DEVICE_ID_3DLABS_MX
DECL|macro|PCI_DEVICE_ID_3DLABS_MX
mdefine_line|#define PCI_DEVICE_ID_3DLABS_MX 0x0006
macro_line|#endif
DECL|macro|GAMMA_NAME
mdefine_line|#define GAMMA_NAME&t; &quot;gamma&quot;
DECL|macro|GAMMA_DESC
mdefine_line|#define GAMMA_DESC&t; &quot;3dlabs GMX 2000&quot;
DECL|macro|GAMMA_DATE
mdefine_line|#define GAMMA_DATE&t; &quot;20000910&quot;
DECL|macro|GAMMA_MAJOR
mdefine_line|#define GAMMA_MAJOR&t; 1
DECL|macro|GAMMA_MINOR
mdefine_line|#define GAMMA_MINOR&t; 0
DECL|macro|GAMMA_PATCHLEVEL
mdefine_line|#define GAMMA_PATCHLEVEL 0
DECL|variable|gamma_device
r_static
id|drm_device_t
id|gamma_device
suffix:semicolon
DECL|variable|gamma_fops
r_static
r_struct
id|file_operations
id|gamma_fops
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
id|gamma_open
comma
id|flush
suffix:colon
id|drm_flush
comma
id|release
suffix:colon
id|gamma_release
comma
id|ioctl
suffix:colon
id|gamma_ioctl
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
DECL|variable|gamma_misc
r_static
r_struct
id|miscdevice
id|gamma_misc
op_assign
(brace
id|minor
suffix:colon
id|MISC_DYNAMIC_MINOR
comma
id|name
suffix:colon
id|GAMMA_NAME
comma
id|fops
suffix:colon
op_amp
id|gamma_fops
comma
)brace
suffix:semicolon
DECL|variable|gamma_ioctls
r_static
id|drm_ioctl_desc_t
id|gamma_ioctls
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
id|gamma_version
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
id|DRM_IOCTL_CONTROL
)paren
)braket
op_assign
(brace
id|gamma_control
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
id|DRM_IOCTL_ADD_BUFS
)paren
)braket
op_assign
(brace
id|drm_addbufs
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
id|DRM_IOCTL_MARK_BUFS
)paren
)braket
op_assign
(brace
id|drm_markbufs
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
id|DRM_IOCTL_INFO_BUFS
)paren
)braket
op_assign
(brace
id|drm_infobufs
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
id|DRM_IOCTL_MAP_BUFS
)paren
)braket
op_assign
(brace
id|drm_mapbufs
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
id|DRM_IOCTL_FREE_BUFS
)paren
)braket
op_assign
(brace
id|drm_freebufs
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
id|DRM_IOCTL_ADD_CTX
)paren
)braket
op_assign
(brace
id|drm_addctx
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
id|drm_rmctx
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
id|drm_modctx
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
id|drm_getctx
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
id|drm_switchctx
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
id|drm_newctx
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
id|drm_resctx
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
id|DRM_IOCTL_DMA
)paren
)braket
op_assign
(brace
id|gamma_dma
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
id|DRM_IOCTL_LOCK
)paren
)braket
op_assign
(brace
id|gamma_lock
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
id|gamma_unlock
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
)brace
suffix:semicolon
DECL|macro|GAMMA_IOCTL_COUNT
mdefine_line|#define GAMMA_IOCTL_COUNT DRM_ARRAY_SIZE(gamma_ioctls)
macro_line|#ifdef MODULE
DECL|variable|gamma
r_static
r_char
op_star
id|gamma
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
DECL|variable|devices
r_static
r_int
id|devices
op_assign
l_int|0
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;VA Linux Systems, Inc.&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;3dlabs GMX 2000&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|gamma
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|devices
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|devices
comma
l_string|&quot;devices=x, where x is the number of MX chips on card&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifndef MODULE
multiline_comment|/* gamma_options is called by the kernel to parse command-line options&n; * passed via the boot-loader (e.g., LILO).  It calls the insmod option&n; * routine, drm_parse_options.&n; */
DECL|function|gamma_options
r_static
r_int
id|__init
id|gamma_options
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
l_string|&quot;gamma=&quot;
comma
id|gamma_options
)paren
suffix:semicolon
macro_line|#endif
DECL|function|gamma_setup
r_static
r_int
id|gamma_setup
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
id|drm_dma_setup
c_func
(paren
id|dev
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
macro_line|#if DRM_DMA_HISTO
id|memset
c_func
(paren
op_amp
id|dev-&gt;histo
comma
l_int|0
comma
r_sizeof
(paren
id|dev-&gt;histo
)paren
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|gamma_takedown
r_static
r_int
id|gamma_takedown
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
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|gamma_irq_uninstall
c_func
(paren
id|dev
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
id|dev-&gt;queuelist
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
id|dev-&gt;queue_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|drm_waitlist_destroy
c_func
(paren
op_amp
id|dev-&gt;queuelist
(braket
id|i
)braket
op_member_access_from_pointer
id|waitlist
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;queuelist
(braket
id|i
)braket
)paren
(brace
id|drm_free
c_func
(paren
id|dev-&gt;queuelist
(braket
id|i
)braket
comma
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
(braket
l_int|0
)braket
)paren
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
id|dev-&gt;queuelist
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|drm_free
c_func
(paren
id|dev-&gt;queuelist
comma
id|dev-&gt;queue_slots
op_star
r_sizeof
(paren
op_star
id|dev-&gt;queuelist
)paren
comma
id|DRM_MEM_QUEUES
)paren
suffix:semicolon
id|dev-&gt;queuelist
op_assign
l_int|NULL
suffix:semicolon
)brace
id|drm_dma_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;queue_count
op_assign
l_int|0
suffix:semicolon
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
DECL|function|gamma_found
r_int
id|gamma_found
c_func
(paren
r_void
)paren
(brace
r_return
id|devices
suffix:semicolon
)brace
DECL|function|gamma_find_devices
r_int
id|gamma_find_devices
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|d
op_assign
l_int|NULL
comma
op_star
id|one
op_assign
l_int|NULL
comma
op_star
id|two
op_assign
l_int|NULL
suffix:semicolon
id|d
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_3DLABS
comma
id|PCI_DEVICE_ID_3DLABS_GAMMA
comma
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
r_return
l_int|0
suffix:semicolon
id|one
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_3DLABS
comma
id|PCI_DEVICE_ID_3DLABS_MX
comma
id|d
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|one
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Make sure it&squot;s on the same card, if not - no MX&squot;s found */
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|d-&gt;devfn
)paren
op_ne
id|PCI_SLOT
c_func
(paren
id|one-&gt;devfn
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|two
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_3DLABS
comma
id|PCI_DEVICE_ID_3DLABS_MX
comma
id|one
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|two
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Make sure it&squot;s on the same card, if not - only 1 MX found */
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|d-&gt;devfn
)paren
op_ne
id|PCI_SLOT
c_func
(paren
id|two-&gt;devfn
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* Two MX&squot;s found - we don&squot;t currently support more than 2 */
r_return
l_int|2
suffix:semicolon
)brace
multiline_comment|/* gamma_init is called via init_module at module load time, or via&n; * linux/init/main.c (this is not currently supported). */
DECL|function|gamma_init
r_static
r_int
id|__init
id|gamma_init
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
id|gamma_device
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
id|gamma
)paren
suffix:semicolon
macro_line|#endif
id|devices
op_assign
id|gamma_find_devices
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|devices
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
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
id|gamma_misc
)paren
)paren
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Cannot register &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|GAMMA_NAME
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
id|gamma_misc.minor
)paren
suffix:semicolon
id|dev-&gt;name
op_assign
id|GAMMA_NAME
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
id|DRM_INFO
c_func
(paren
l_string|&quot;Initialized %s %d.%d.%d %s on minor %d with %d MX devices&bslash;n&quot;
comma
id|GAMMA_NAME
comma
id|GAMMA_MAJOR
comma
id|GAMMA_MINOR
comma
id|GAMMA_PATCHLEVEL
comma
id|GAMMA_DATE
comma
id|gamma_misc.minor
comma
id|devices
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* gamma_cleanup is called via cleanup_module at module unload time. */
DECL|function|gamma_cleanup
r_static
r_void
id|__exit
id|gamma_cleanup
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
id|gamma_device
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
id|gamma_misc
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
id|gamma_takedown
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|gamma_init
id|module_init
c_func
(paren
id|gamma_init
)paren
suffix:semicolon
DECL|variable|gamma_cleanup
id|module_exit
c_func
(paren
id|gamma_cleanup
)paren
suffix:semicolon
DECL|function|gamma_version
r_int
id|gamma_version
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
id|GAMMA_MAJOR
suffix:semicolon
id|version.version_minor
op_assign
id|GAMMA_MINOR
suffix:semicolon
id|version.version_patchlevel
op_assign
id|GAMMA_PATCHLEVEL
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.name
comma
id|GAMMA_NAME
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.date
comma
id|GAMMA_DATE
)paren
suffix:semicolon
id|DRM_COPY
c_func
(paren
id|version.desc
comma
id|GAMMA_DESC
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
DECL|function|gamma_open
r_int
id|gamma_open
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
id|gamma_device
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
id|gamma_setup
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
DECL|function|gamma_release
r_int
id|gamma_release
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
id|gamma_takedown
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
multiline_comment|/* drm_ioctl is called whenever a process performs an ioctl on /dev/drm. */
DECL|function|gamma_ioctl
r_int
id|gamma_ioctl
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
id|GAMMA_IOCTL_COUNT
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
id|gamma_ioctls
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
DECL|function|gamma_unlock
r_int
id|gamma_unlock
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
id|gamma_dma_schedule
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
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
macro_line|#if DRM_DMA_HISTOGRAM
id|atomic_inc
c_func
(paren
op_amp
id|dev-&gt;histo.lhld
(braket
id|drm_histogram_slot
c_func
(paren
id|get_cycles
c_func
(paren
)paren
op_minus
id|dev-&gt;lck_start
)paren
)braket
)paren
suffix:semicolon
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
