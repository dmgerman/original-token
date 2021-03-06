multiline_comment|/* auth.c -- IOCTLs for authentication -*- linux-c -*-&n; * Created: Tue Feb  2 08:37:54 1999 by faith@precisioninsight.com&n; *&n; * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.&n; * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.&n; * All Rights Reserved.&n; *&n; * Permission is hereby granted, free of charge, to any person obtaining a&n; * copy of this software and associated documentation files (the &quot;Software&quot;),&n; * to deal in the Software without restriction, including without limitation&n; * the rights to use, copy, modify, merge, publish, distribute, sublicense,&n; * and/or sell copies of the Software, and to permit persons to whom the&n; * Software is furnished to do so, subject to the following conditions:&n; * &n; * The above copyright notice and this permission notice (including the next&n; * paragraph) shall be included in all copies or substantial portions of the&n; * Software.&n; * &n; * THE SOFTWARE IS PROVIDED &quot;AS IS&quot;, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR&n; * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,&n; * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL&n; * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR&n; * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,&n; * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER&n; * DEALINGS IN THE SOFTWARE.&n; *&n; * Authors:&n; *    Rickard E. (Rik) Faith &lt;faith@valinux.com&gt;&n; *&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &quot;drmP.h&quot;
DECL|function|drm_hash_magic
r_static
r_int
id|drm_hash_magic
c_func
(paren
id|drm_magic_t
id|magic
)paren
(brace
r_return
id|magic
op_amp
(paren
id|DRM_HASH_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|drm_find_file
r_static
id|drm_file_t
op_star
id|drm_find_file
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_magic_t
id|magic
)paren
(brace
id|drm_file_t
op_star
id|retval
op_assign
l_int|NULL
suffix:semicolon
id|drm_magic_entry_t
op_star
id|pt
suffix:semicolon
r_int
id|hash
op_assign
id|drm_hash_magic
c_func
(paren
id|magic
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|head
suffix:semicolon
id|pt
suffix:semicolon
id|pt
op_assign
id|pt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|pt-&gt;magic
op_eq
id|magic
)paren
(brace
id|retval
op_assign
id|pt-&gt;priv
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|up
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|drm_add_magic
r_int
id|drm_add_magic
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_file_t
op_star
id|priv
comma
id|drm_magic_t
id|magic
)paren
(brace
r_int
id|hash
suffix:semicolon
id|drm_magic_entry_t
op_star
id|entry
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|magic
)paren
suffix:semicolon
id|hash
op_assign
id|drm_hash_magic
c_func
(paren
id|magic
)paren
suffix:semicolon
id|entry
op_assign
id|drm_alloc
c_func
(paren
r_sizeof
(paren
op_star
id|entry
)paren
comma
id|DRM_MEM_MAGIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|entry-&gt;magic
op_assign
id|magic
suffix:semicolon
id|entry-&gt;priv
op_assign
id|priv
suffix:semicolon
id|entry-&gt;next
op_assign
l_int|NULL
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
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail
)paren
(brace
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail-&gt;next
op_assign
id|entry
suffix:semicolon
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail
op_assign
id|entry
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|head
op_assign
id|entry
suffix:semicolon
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail
op_assign
id|entry
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
DECL|function|drm_remove_magic
r_int
id|drm_remove_magic
c_func
(paren
id|drm_device_t
op_star
id|dev
comma
id|drm_magic_t
id|magic
)paren
(brace
id|drm_magic_entry_t
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|drm_magic_entry_t
op_star
id|pt
suffix:semicolon
r_int
id|hash
suffix:semicolon
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%d&bslash;n&quot;
comma
id|magic
)paren
suffix:semicolon
id|hash
op_assign
id|drm_hash_magic
c_func
(paren
id|magic
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|dev-&gt;struct_sem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pt
op_assign
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|head
suffix:semicolon
id|pt
suffix:semicolon
id|prev
op_assign
id|pt
comma
id|pt
op_assign
id|pt-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|pt-&gt;magic
op_eq
id|magic
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|head
op_eq
id|pt
)paren
(brace
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|head
op_assign
id|pt-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail
op_eq
id|pt
)paren
(brace
id|dev-&gt;magiclist
(braket
id|hash
)braket
dot
id|tail
op_assign
id|prev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|prev-&gt;next
op_assign
id|pt-&gt;next
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
)brace
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|drm_getmagic
r_int
id|drm_getmagic
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
r_static
id|drm_magic_t
id|sequence
op_assign
l_int|0
suffix:semicolon
r_static
id|spinlock_t
id|lock
op_assign
id|SPIN_LOCK_UNLOCKED
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
id|drm_auth_t
id|auth
suffix:semicolon
multiline_comment|/* Find unique magic */
r_if
c_cond
(paren
id|priv-&gt;magic
)paren
(brace
id|auth.magic
op_assign
id|priv-&gt;magic
suffix:semicolon
)brace
r_else
(brace
r_do
(brace
id|spin_lock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sequence
)paren
op_increment
id|sequence
suffix:semicolon
multiline_comment|/* reserve 0 */
id|auth.magic
op_assign
id|sequence
op_increment
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|drm_find_file
c_func
(paren
id|dev
comma
id|auth.magic
)paren
)paren
suffix:semicolon
id|priv-&gt;magic
op_assign
id|auth.magic
suffix:semicolon
id|drm_add_magic
c_func
(paren
id|dev
comma
id|priv
comma
id|auth.magic
)paren
suffix:semicolon
)brace
id|DRM_DEBUG
c_func
(paren
l_string|&quot;%u&bslash;n&quot;
comma
id|auth.magic
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
(paren
id|drm_auth_t
op_star
)paren
id|arg
comma
op_amp
id|auth
comma
r_sizeof
(paren
id|auth
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
DECL|function|drm_authmagic
r_int
id|drm_authmagic
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
id|drm_auth_t
id|auth
suffix:semicolon
id|drm_file_t
op_star
id|file
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|auth
comma
(paren
id|drm_auth_t
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|auth
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
l_string|&quot;%u&bslash;n&quot;
comma
id|auth.magic
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|file
op_assign
id|drm_find_file
c_func
(paren
id|dev
comma
id|auth.magic
)paren
)paren
)paren
(brace
id|file-&gt;authenticated
op_assign
l_int|1
suffix:semicolon
id|drm_remove_magic
c_func
(paren
id|dev
comma
id|auth.magic
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
eof
