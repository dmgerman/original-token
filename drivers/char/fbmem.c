multiline_comment|/*&n; *  linux/drivers/char/fbmem.c&n; *&n; *  Copyright (C) 1994 Martin Schaller&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
DECL|macro|FB_MAJOR
mdefine_line|#define FB_MAJOR&t;29
DECL|macro|FB_MODES_SHIFT
mdefine_line|#define FB_MODES_SHIFT    5&t;/* 32 modes per framebuffer */
DECL|macro|FB_NUM_MINORS
mdefine_line|#define FB_NUM_MINORS &t;256&t;/* 256 Minors&t;&t;    */
DECL|macro|FB_MAX
mdefine_line|#define FB_MAX&t;&t;(FB_NUM_MINORS / (1 &lt;&lt; FB_MODES_SHIFT))
DECL|macro|GET_INODE
mdefine_line|#define GET_INODE(i) MKDEV(FB_MAJOR, (i) &lt;&lt; FB_MODES_SHIFT)
DECL|macro|GET_FB_IDX
mdefine_line|#define GET_FB_IDX(node) (MINOR(node) &gt;&gt; FB_MODES_SHIFT)
DECL|macro|GET_FB_VAR_IDX
mdefine_line|#define GET_FB_VAR_IDX(node) (MINOR(node) &amp; ((1 &lt;&lt; FB_MODES_SHIFT)-1)) 
DECL|variable|registered_fb
r_struct
id|fb_ops
op_star
id|registered_fb
(braket
id|FB_MAX
)braket
suffix:semicolon
DECL|variable|registered_fb_var
r_struct
id|fb_var_screeninfo
op_star
id|registered_fb_var
(braket
id|FB_MAX
)braket
suffix:semicolon
DECL|variable|registered_fb_var_num
r_int
id|registered_fb_var_num
(braket
id|FB_MAX
)braket
suffix:semicolon
DECL|variable|fb_curr_open
r_int
id|fb_curr_open
(braket
id|FB_MAX
)braket
suffix:semicolon
DECL|variable|fb_open_count
r_int
id|fb_open_count
(braket
id|FB_MAX
)braket
suffix:semicolon
DECL|function|PROC_CONSOLE
r_static
r_inline
r_int
id|PROC_CONSOLE
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;tty
)paren
r_return
id|fg_console
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;tty-&gt;driver.type
op_ne
id|TTY_DRIVER_TYPE_CONSOLE
)paren
multiline_comment|/* XXX Should report error here? */
r_return
id|fg_console
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|current-&gt;tty-&gt;device
)paren
OL
l_int|1
)paren
r_return
id|fg_console
suffix:semicolon
r_return
id|MINOR
c_func
(paren
id|current-&gt;tty-&gt;device
)paren
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_int
DECL|function|fb_read
id|fb_read
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
id|file
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_struct
id|fb_ops
op_star
id|fb
op_assign
id|registered_fb
(braket
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_char
op_star
id|base_addr
suffix:semicolon
r_int
id|copy_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|fb
op_member_access_from_pointer
id|fb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
id|base_addr
op_assign
(paren
r_char
op_star
)paren
id|fix.smem_start
suffix:semicolon
id|copy_size
op_assign
(paren
id|count
op_plus
id|p
op_le
id|fix.smem_len
ques
c_cond
id|count
suffix:colon
id|fix.smem_len
op_minus
id|p
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
id|base_addr
op_plus
id|p
comma
id|copy_size
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|copy_size
suffix:semicolon
r_return
id|copy_size
suffix:semicolon
)brace
r_static
r_int
DECL|function|fb_write
id|fb_write
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
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_struct
id|fb_ops
op_star
id|fb
op_assign
id|registered_fb
(braket
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_char
op_star
id|base_addr
suffix:semicolon
r_int
id|copy_size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|fb
op_member_access_from_pointer
id|fb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
id|base_addr
op_assign
(paren
r_char
op_star
)paren
id|fix.smem_start
suffix:semicolon
id|copy_size
op_assign
(paren
id|count
op_plus
id|p
op_le
id|fix.smem_len
ques
c_cond
id|count
suffix:colon
id|fix.smem_len
op_minus
id|p
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
id|base_addr
op_plus
id|p
comma
id|buf
comma
id|copy_size
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|copy_size
suffix:semicolon
r_return
id|copy_size
suffix:semicolon
)brace
r_static
r_int
DECL|function|fb_ioctl
id|fb_ioctl
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
id|file
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
r_struct
id|fb_ops
op_star
id|fb
op_assign
id|registered_fb
(braket
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|fb_cmap
id|cmap
suffix:semicolon
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_int
id|i
comma
id|fbidx
comma
id|vidx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|FBIOGET_VSCREENINFO
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|fbidx
op_assign
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|vidx
op_assign
id|GET_FB_VAR_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vidx
)paren
multiline_comment|/* ask device driver for current */
id|i
op_assign
id|fb
op_member_access_from_pointer
id|fb_get_var
c_func
(paren
op_amp
id|var
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
r_else
id|var
op_assign
id|registered_fb_var
(braket
id|fbidx
)braket
(braket
id|vidx
op_minus
l_int|1
)braket
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|var
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
r_case
id|FBIOPUT_VSCREENINFO
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|var
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
id|i
op_assign
id|fb
op_member_access_from_pointer
id|fb_set_var
c_func
(paren
op_amp
id|var
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|var
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
id|fbidx
op_assign
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|vidx
op_assign
id|GET_FB_VAR_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_and
id|vidx
)paren
id|registered_fb_var
(braket
id|fbidx
)braket
(braket
id|vidx
op_minus
l_int|1
)braket
op_assign
id|var
suffix:semicolon
r_return
id|i
suffix:semicolon
r_case
id|FBIOGET_FSCREENINFO
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|fb
op_member_access_from_pointer
id|fb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|fix
comma
r_sizeof
(paren
id|fix
)paren
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
r_case
id|FBIOPUTCMAP
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_cmap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|cmap
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|cmap
)paren
)paren
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|cmap.red
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|cmap.green
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|cmap.blue
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cmap.transp
)paren
(brace
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|cmap.transp
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
)brace
r_return
(paren
id|fb
op_member_access_from_pointer
id|fb_set_cmap
c_func
(paren
op_amp
id|cmap
comma
l_int|0
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_case
id|FBIOGETCMAP
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_cmap
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|cmap
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|cmap
)paren
)paren
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|cmap.red
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|cmap.green
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|cmap.blue
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_if
c_cond
(paren
id|cmap.transp
)paren
(brace
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|cmap.transp
comma
id|cmap.len
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
)brace
r_return
(paren
id|fb
op_member_access_from_pointer
id|fb_get_cmap
c_func
(paren
op_amp
id|cmap
comma
l_int|0
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
r_case
id|FBIOPAN_DISPLAY
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|var
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
id|i
op_assign
id|fb
op_member_access_from_pointer
id|fb_pan_display
c_func
(paren
op_amp
id|var
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|var
comma
r_sizeof
(paren
id|var
)paren
)paren
suffix:semicolon
id|fbidx
op_assign
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|vidx
op_assign
id|GET_FB_VAR_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_and
id|vidx
)paren
id|registered_fb_var
(braket
id|fbidx
)braket
(braket
id|vidx
op_minus
l_int|1
)braket
op_assign
id|var
suffix:semicolon
r_return
id|i
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|fb
op_member_access_from_pointer
id|fb_ioctl
c_func
(paren
id|inode
comma
id|file
comma
id|cmd
comma
id|arg
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|fb_mmap
id|fb_mmap
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
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_struct
id|fb_ops
op_star
id|fb
op_assign
id|registered_fb
(braket
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
suffix:semicolon
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|fb
op_member_access_from_pointer
id|fb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
op_plus
id|vma-&gt;vm_offset
)paren
OG
id|fix.smem_len
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vma-&gt;vm_offset
op_add_assign
id|__pa
c_func
(paren
id|fix.smem_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_and_assign
id|_CACHEMASK040
suffix:semicolon
multiline_comment|/* Use write-through cache mode */
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_or_assign
id|_PAGE_NOCACHE_S
suffix:semicolon
)brace
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|vma-&gt;vm_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|fb_open
id|fb_open
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
id|file
)paren
(brace
r_int
id|fbidx
op_assign
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|vidx
op_assign
id|GET_FB_VAR_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|fb_ops
op_star
id|fb
op_assign
id|registered_fb
(braket
id|fbidx
)braket
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vidx
)paren
multiline_comment|/* fb?current always succeeds */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vidx
OG
id|registered_fb_var_num
(braket
id|fbidx
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fb_curr_open
(braket
id|fbidx
)braket
op_logical_and
id|fb_curr_open
(braket
id|fbidx
)braket
op_ne
id|vidx
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_mode
op_amp
l_int|2
)paren
multiline_comment|/* only set parameters if opened writeable */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb
op_member_access_from_pointer
id|fb_set_var
c_func
(paren
id|registered_fb_var
(braket
id|fbidx
)braket
op_plus
id|vidx
op_minus
l_int|1
comma
id|PROC_CONSOLE
c_func
(paren
)paren
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|fb_curr_open
(braket
id|fbidx
)braket
op_assign
id|vidx
suffix:semicolon
id|fb_open_count
(braket
id|fbidx
)braket
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|fb_release
id|fb_release
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
id|file
)paren
(brace
r_int
id|fbidx
op_assign
id|GET_FB_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|vidx
op_assign
id|GET_FB_VAR_IDX
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vidx
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_decrement
id|fb_open_count
(braket
id|fbidx
)braket
)paren
)paren
id|fb_curr_open
(braket
id|fbidx
)braket
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|fb_fops
r_static
r_struct
id|file_operations
id|fb_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek&t;*/
id|fb_read
comma
multiline_comment|/* read&t;&t;*/
id|fb_write
comma
multiline_comment|/* write&t;*/
l_int|NULL
comma
multiline_comment|/* readdir &t;*/
l_int|NULL
comma
multiline_comment|/* poll &t;*/
id|fb_ioctl
comma
multiline_comment|/* ioctl &t;*/
id|fb_mmap
comma
multiline_comment|/* mmap&t;&t;*/
id|fb_open
comma
multiline_comment|/* open &t;*/
id|fb_release
comma
multiline_comment|/* release &t;*/
l_int|NULL
multiline_comment|/* fsync &t;*/
)brace
suffix:semicolon
r_int
DECL|function|register_framebuffer
id|register_framebuffer
c_func
(paren
r_char
op_star
id|id
comma
r_int
op_star
id|node
comma
r_struct
id|fb_ops
op_star
id|fbops
comma
r_int
id|fbvar_num
comma
r_struct
id|fb_var_screeninfo
op_star
id|fbvar
)paren
(brace
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
id|FB_MAX
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|registered_fb
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|FB_MAX
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|registered_fb
(braket
id|i
)braket
op_assign
id|fbops
suffix:semicolon
id|registered_fb_var
(braket
id|i
)braket
op_assign
id|fbvar
suffix:semicolon
id|registered_fb_var_num
(braket
id|i
)braket
op_assign
id|fbvar_num
suffix:semicolon
op_star
id|node
op_assign
id|GET_INODE
c_func
(paren
id|i
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|unregister_framebuffer
id|unregister_framebuffer
c_func
(paren
r_int
id|node
)paren
(brace
r_int
id|i
op_assign
id|GET_FB_IDX
c_func
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|registered_fb
(braket
id|i
)braket
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|registered_fb
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|registered_fb_var
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|fbmem_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|FB_MAJOR
comma
l_string|&quot;fb&quot;
comma
op_amp
id|fb_fops
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for fb devs&bslash;n&quot;
comma
id|FB_MAJOR
)paren
suffix:semicolon
)brace
eof
