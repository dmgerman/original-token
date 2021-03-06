multiline_comment|/* ioctl.c -- IOCTL processing for DRM -*- linux-c -*-&n; * Created: Fri Jan  8 09:01:26 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; * &n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
DECL|function|drm_irq_busid
r_int
id|drm_irq_busid
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
id|drm_irq_busid_t
id|p
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|p
comma
(paren
id|drm_irq_busid_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|p
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev
op_assign
id|pci_find_slot
c_func
(paren
id|p.busnum
comma
id|PCI_DEVFN
c_func
(paren
id|p.devnum
comma
id|p.funcnum
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
id|p.irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_else
id|p.irq
op_assign
l_int|0
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d:%d:%d =&gt; IRQ %d&bslash;n&quot;
comma
id|p.busnum
comma
id|p.devnum
comma
id|p.funcnum
comma
id|p.irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_irq_busid_t
op_star
)paren
id|arg
comma
op_amp
id|p
comma
r_sizeof
(paren
id|p
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
DECL|function|drm_getunique
r_int
id|drm_getunique
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
id|drm_unique_t
id|u
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|u
comma
(paren
id|drm_unique_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|u
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
id|u.unique_len
op_ge
id|dev-&gt;unique_len
)paren
(brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|u.unique
comma
id|dev-&gt;unique
comma
id|dev-&gt;unique_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|u.unique_len
op_assign
id|dev-&gt;unique_len
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_unique_t
op_star
)paren
id|arg
comma
op_amp
id|u
comma
r_sizeof
(paren
id|u
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
DECL|function|drm_setunique
r_int
id|drm_setunique
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
id|drm_unique_t
id|u
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;unique_len
op_logical_or
id|dev-&gt;unique
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|u
comma
(paren
id|drm_unique_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|u
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
op_logical_neg
id|u.unique_len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|dev-&gt;unique_len
op_assign
id|u.unique_len
suffix:semicolon
id|dev-&gt;unique
op_assign
id|drm_alloc
c_func
(paren
id|u.unique_len
op_plus
l_int|1
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|dev-&gt;unique
comma
id|u.unique
comma
id|dev-&gt;unique_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|dev-&gt;unique
(braket
id|dev-&gt;unique_len
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|dev-&gt;devname
op_assign
id|drm_alloc
c_func
(paren
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
op_plus
id|strlen
c_func
(paren
id|dev-&gt;unique
)paren
op_plus
l_int|2
comma
id|DRM_MEM_DRIVER
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|dev-&gt;devname
comma
l_string|&quot;%s@%s&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;unique
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
