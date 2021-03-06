multiline_comment|/* fops.c -- File operations for DRM -*- linux-c -*-&n; * Created: Mon Jan  4 08:58:31 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *    Daryll Strauss &lt;daryll@valinux.com&gt;&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
macro_line|#include &lt;linux/poll.h&gt;
multiline_comment|/* drm_open is called whenever a process opens /dev/drm. */
DECL|function|drm_open_helper
r_int
id|drm_open_helper
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
id|drm_device_t
op_star
id|dev
)paren
(brace
id|kdev_t
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|drm_file_t
op_star
id|priv
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_EXCL
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/* No exclusive opens */
r_if
c_cond
(paren
op_logical_neg
id|drm_cpu_valid
c_func
(paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, minor = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|minor
)paren
suffix:semicolon
id|priv
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|priv
)paren
)paren
suffix:semicolon
id|filp-&gt;private_data
op_assign
id|priv
suffix:semicolon
id|priv-&gt;uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|priv-&gt;pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|priv-&gt;minor
op_assign
id|minor
suffix:semicolon
id|priv-&gt;dev
op_assign
id|dev
suffix:semicolon
id|priv-&gt;ioctl_count
op_assign
l_int|0
suffix:semicolon
id|priv-&gt;authenticated
op_assign
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
suffix:semicolon
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
op_logical_neg
id|dev-&gt;file_last
)paren
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;file_first
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
suffix:semicolon
)brace
r_else
(brace
id|priv-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|priv-&gt;prev
op_assign
id|dev-&gt;file_last
suffix:semicolon
id|dev-&gt;file_last-&gt;next
op_assign
id|priv
suffix:semicolon
id|dev-&gt;file_last
op_assign
id|priv
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
DECL|function|drm_flush
r_int
id|drm_flush
c_func
(paren
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
op_assign
id|priv-&gt;dev
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, device = 0x%x, open_count = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|dev-&gt;device
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* drm_release is called whenever a process closes /dev/drm*.  Linux calls&n;   this only if any mappings have been closed. */
DECL|function|drm_release
r_int
id|drm_release
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
op_assign
id|priv-&gt;dev
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;pid = %d, device = 0x%x, open_count = %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|dev-&gt;device
comma
id|dev-&gt;open_count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;lock.hw_lock
op_logical_and
id|_DRM_LOCK_IS_HELD
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
op_logical_and
id|dev-&gt;lock.pid
op_eq
id|current-&gt;pid
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Process %d dead, freeing lock for context %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
suffix:semicolon
id|drm_lock_free
c_func
(paren
id|dev
comma
op_amp
id|dev-&gt;lock.hw_lock-&gt;lock
comma
id|_DRM_LOCKING_CONTEXT
c_func
(paren
id|dev-&gt;lock.hw_lock-&gt;lock
)paren
)paren
suffix:semicolon
multiline_comment|/* FIXME: may require heavy-handed reset of&n;                                   hardware at this point, possibly&n;                                   processed via a callback to the X&n;                                   server. */
)brace
id|drm_reclaim_buffers
c_func
(paren
id|dev
comma
id|priv-&gt;pid
)paren
suffix:semicolon
id|drm_fasync
c_func
(paren
op_minus
l_int|1
comma
id|filp
comma
l_int|0
)paren
suffix:semicolon
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
id|priv-&gt;prev
)paren
id|priv-&gt;prev-&gt;next
op_assign
id|priv-&gt;next
suffix:semicolon
r_else
id|dev-&gt;file_first
op_assign
id|priv-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;next
)paren
id|priv-&gt;next-&gt;prev
op_assign
id|priv-&gt;prev
suffix:semicolon
r_else
id|dev-&gt;file_last
op_assign
id|priv-&gt;prev
suffix:semicolon
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
id|drm_free
c_func
(paren
id|priv
comma
r_sizeof
(paren
op_star
id|priv
)paren
comma
id|DRM_MEM_FILES
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_fasync
r_int
id|drm_fasync
c_func
(paren
r_int
id|fd
comma
r_struct
id|file
op_star
id|filp
comma
r_int
id|on
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
r_int
id|retcode
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;fd = %d, device = 0x%x&bslash;n&quot;
comma
id|fd
comma
id|dev-&gt;device
)paren
suffix:semicolon
id|retcode
op_assign
id|fasync_helper
c_func
(paren
id|fd
comma
id|filp
comma
id|on
comma
op_amp
id|dev-&gt;buf_async
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retcode
OL
l_int|0
)paren
r_return
id|retcode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* The drm_read and drm_write_string code (especially that which manages&n;   the circular buffer), is based on Alessandro Rubini&squot;s LINUX DEVICE&n;   DRIVERS (Cambridge: O&squot;Reilly, 1998), pages 111-113. */
DECL|function|drm_read
id|ssize_t
id|drm_read
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|off
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
r_int
id|left
suffix:semicolon
r_int
id|avail
suffix:semicolon
r_int
id|send
suffix:semicolon
r_int
id|cur
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%p, %p&bslash;n&quot;
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_wp
)paren
(brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  sleeping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|dev-&gt;buf_readers
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
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  interrupted&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;  awake&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
id|avail
op_assign
id|DRM_BSZ
op_minus
id|left
suffix:semicolon
id|send
op_assign
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
OG
id|dev-&gt;buf_rp
)paren
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_wp
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_else
(brace
id|cur
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|dev-&gt;buf_rp
comma
id|cur
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;buf_rp
op_add_assign
id|cur
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_rp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_rp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|cur
suffix:semicolon
)brace
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_writers
)paren
suffix:semicolon
r_return
id|DRM_MIN
c_func
(paren
id|avail
comma
id|count
)paren
suffix:semicolon
suffix:semicolon
)brace
DECL|function|drm_write_string
r_int
id|drm_write_string
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|left
op_assign
(paren
id|dev-&gt;buf_rp
op_plus
id|DRM_BSZ
op_minus
id|dev-&gt;buf_wp
)paren
op_mod
id|DRM_BSZ
suffix:semicolon
r_int
id|send
op_assign
id|strlen
c_func
(paren
id|s
)paren
suffix:semicolon
r_int
id|count
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d left, %d to send (%p, %p)&bslash;n&quot;
comma
id|left
comma
id|send
comma
id|dev-&gt;buf_rp
comma
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|left
op_eq
l_int|1
op_logical_or
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
(brace
id|DRM_ERROR
c_func
(paren
l_string|&quot;Buffer not empty (%d left, wp = %p, rp = %p)&bslash;n&quot;
comma
id|left
comma
id|dev-&gt;buf_wp
comma
id|dev-&gt;buf_rp
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|send
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ge
id|dev-&gt;buf_rp
)paren
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_end
op_minus
id|dev-&gt;buf_wp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
id|left
)paren
op_decrement
id|count
suffix:semicolon
multiline_comment|/* Leave a hole */
)brace
r_else
(brace
id|count
op_assign
id|DRM_MIN
c_func
(paren
id|send
comma
id|dev-&gt;buf_rp
op_minus
id|dev-&gt;buf_wp
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|strncpy
c_func
(paren
id|dev-&gt;buf_wp
comma
id|s
comma
id|count
)paren
suffix:semicolon
id|dev-&gt;buf_wp
op_add_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_eq
id|dev-&gt;buf_end
)paren
id|dev-&gt;buf_wp
op_assign
id|dev-&gt;buf
suffix:semicolon
id|send
op_sub_assign
id|count
suffix:semicolon
)brace
macro_line|#if LINUX_VERSION_CODE &lt; 0x020315 &amp;&amp; !defined(KILLFASYNCHASTHREEPARAMETERS)
multiline_comment|/* The extra parameter to kill_fasync was added in 2.3.21, and is&n;           _not_ present in _stock_ 2.2.14 and 2.2.15.  However, some&n;           distributions patch 2.2.x kernels to add this parameter.  The&n;           Makefile.linux attempts to detect this addition and defines&n;           KILLFASYNCHASTHREEPARAMETERS if three parameters are found. */
r_if
c_cond
(paren
id|dev-&gt;buf_async
)paren
id|kill_fasync
c_func
(paren
id|dev-&gt;buf_async
comma
id|SIGIO
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Parameter added in 2.3.21. */
macro_line|#if LINUX_VERSION_CODE &lt; 0x020400
r_if
c_cond
(paren
id|dev-&gt;buf_async
)paren
id|kill_fasync
c_func
(paren
id|dev-&gt;buf_async
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/* Type of first parameter changed in&n;                                   Linux 2.4.0-test2... */
r_if
c_cond
(paren
id|dev-&gt;buf_async
)paren
id|kill_fasync
c_func
(paren
op_amp
id|dev-&gt;buf_async
comma
id|SIGIO
comma
id|POLL_IN
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
id|DRM_DEBUG
c_func
(paren
l_string|&quot;waking&bslash;n&quot;
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|dev-&gt;buf_readers
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|drm_poll
r_int
r_int
id|drm_poll
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|poll_table_struct
op_star
id|wait
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
id|poll_wait
c_func
(paren
id|filp
comma
op_amp
id|dev-&gt;buf_readers
comma
id|wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;buf_wp
op_ne
id|dev-&gt;buf_rp
)paren
r_return
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
