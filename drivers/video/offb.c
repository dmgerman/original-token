multiline_comment|/*&n; *  linux/drivers/video/offb.c -- Open Firmware based frame buffer device&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This driver is partly based on the PowerMac console driver:&n; *&n; *&t;Copyright (C) 1996 Paul Mackerras&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
DECL|macro|arraysize
mdefine_line|#define arraysize(x)&t;(sizeof(x)/sizeof(*(x)))
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|fb_info
id|fb_info
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|variable|palette
r_static
r_struct
(brace
id|u_char
id|red
comma
id|green
comma
id|blue
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|offb_name
r_static
r_char
id|offb_name
(braket
l_int|16
)braket
op_assign
l_string|&quot;OFfb &quot;
suffix:semicolon
DECL|variable|unknown_cmap_adr
r_static
r_volatile
r_int
r_char
op_star
id|unknown_cmap_adr
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|unknown_cmap_data
r_static
r_volatile
r_int
r_char
op_star
id|unknown_cmap_data
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|fb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|fb_var
r_static
r_struct
id|fb_var_screeninfo
id|fb_var
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_void
id|offb_video_setup
c_func
(paren
r_char
op_star
id|options
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_static
r_int
id|offb_open
c_func
(paren
r_int
id|fbidx
)paren
suffix:semicolon
r_static
r_int
id|offb_release
c_func
(paren
r_int
id|fbidx
)paren
suffix:semicolon
r_static
r_int
id|offb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offb_ioctl
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
id|u_int
id|cmd
comma
id|u_long
id|arg
comma
r_int
id|con
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Interface to the low level console driver&n;     */
r_int
r_int
id|offb_init
c_func
(paren
r_int
r_int
id|mem_start
)paren
suffix:semicolon
r_static
r_int
id|offbcon_switch
c_func
(paren
r_int
id|con
)paren
suffix:semicolon
r_static
r_int
id|offbcon_updatevar
c_func
(paren
r_int
id|con
)paren
suffix:semicolon
r_static
r_void
id|offbcon_blank
c_func
(paren
r_int
id|blank
)paren
suffix:semicolon
r_static
r_int
id|offbcon_setcmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|con
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Internal routines&n;     */
r_static
r_int
id|offb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
)paren
suffix:semicolon
r_static
r_int
id|offb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
)paren
suffix:semicolon
r_static
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
)paren
suffix:semicolon
DECL|variable|offb_ops
r_static
r_struct
id|fb_ops
id|offb_ops
op_assign
(brace
id|offb_open
comma
id|offb_release
comma
id|offb_get_fix
comma
id|offb_get_var
comma
id|offb_set_var
comma
id|offb_get_cmap
comma
id|offb_set_cmap
comma
id|offb_pan_display
comma
id|offb_ioctl
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Open/Release the frame buffer device&n;     */
DECL|function|offb_open
r_static
r_int
id|offb_open
c_func
(paren
r_int
id|fbidx
)paren
(brace
multiline_comment|/*                                                                     &n;     *  Nothing, only a usage count for the moment                          &n;     */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|offb_release
r_static
r_int
id|offb_release
c_func
(paren
r_int
id|fbidx
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the Fixed Part of the Display&n;     */
DECL|function|offb_get_fix
r_static
r_int
id|offb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
)paren
(brace
id|memcpy
c_func
(paren
id|fix
comma
op_amp
id|fb_fix
comma
r_sizeof
(paren
id|fb_fix
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the User Defined Part of the Display&n;     */
DECL|function|offb_get_var
r_static
r_int
id|offb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
(brace
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set the User Defined Part of the Display&n;     */
DECL|function|offb_set_var
r_static
r_int
id|offb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
(brace
r_struct
id|display
op_star
id|display
suffix:semicolon
r_int
id|oldbpp
op_assign
op_minus
l_int|1
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ge
l_int|0
)paren
id|display
op_assign
op_amp
id|fb_display
(braket
id|con
)braket
suffix:semicolon
r_else
id|display
op_assign
op_amp
id|disp
suffix:semicolon
multiline_comment|/* used during initialization */
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|fb_var.xres
op_logical_or
id|var-&gt;yres
OG
id|fb_var.yres
op_logical_or
id|var-&gt;xres_virtual
OG
id|fb_var.xres_virtual
op_logical_or
id|var-&gt;yres_virtual
OG
id|fb_var.yres_virtual
op_logical_or
id|var-&gt;bits_per_pixel
OG
id|fb_var.bits_per_pixel
op_logical_or
id|var-&gt;nonstd
op_logical_or
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_MASK
)paren
op_ne
id|FB_VMODE_NONINTERLACED
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|fb_var
comma
r_sizeof
(paren
id|fb_var
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_NOW
)paren
(brace
id|oldbpp
op_assign
id|display-&gt;var.bits_per_pixel
suffix:semicolon
id|display-&gt;var
op_assign
op_star
id|var
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldbpp
op_ne
id|var-&gt;bits_per_pixel
)paren
(brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|display-&gt;cmap
comma
l_int|0
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|do_install_cmap
c_func
(paren
id|con
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Pan or Wrap the Display&n;     *&n;     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag&n;     */
DECL|function|offb_pan_display
r_static
r_int
id|offb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_logical_or
id|var-&gt;yoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the Colormap&n;     */
DECL|function|offb_get_cmap
r_static
r_int
id|offb_get_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
)paren
(brace
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_get_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
id|kspc
comma
id|offb_getcolreg
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
multiline_comment|/* non default colormap? */
id|fb_copy_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set the Colormap&n;     */
DECL|function|offb_set_cmap
r_static
r_int
id|offb_set_cmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|kspc
comma
r_int
id|con
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unknown_cmap_adr
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
(brace
multiline_comment|/* no colormap allocated? */
r_if
c_cond
(paren
(paren
id|err
op_assign
id|fb_alloc_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
l_int|1
op_lshift
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
comma
l_int|0
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
)brace
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
multiline_comment|/* current console? */
r_return
id|fb_set_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
id|kspc
comma
id|offb_setcolreg
)paren
suffix:semicolon
r_else
id|fb_copy_cmap
c_func
(paren
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
id|kspc
ques
c_cond
l_int|0
suffix:colon
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|offb_ioctl
r_static
r_int
id|offb_ioctl
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
id|u_int
id|cmd
comma
id|u_long
id|arg
comma
r_int
id|con
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|offb_init
c_func
(paren
r_int
r_int
id|mem_start
)paren
)paren
(brace
r_struct
id|device_node
op_star
id|dp
suffix:semicolon
r_int
id|i
comma
id|err
comma
op_star
id|pp
comma
id|len
suffix:semicolon
r_int
op_star
id|up
comma
id|address
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prom_display_path
(braket
l_int|0
)braket
)paren
r_return
id|mem_start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|dp
op_assign
id|find_path_device
c_func
(paren
id|prom_display_path
)paren
)paren
)paren
r_return
id|mem_start
suffix:semicolon
id|strncat
c_func
(paren
id|offb_name
comma
id|dp-&gt;name
comma
r_sizeof
(paren
id|offb_name
)paren
)paren
suffix:semicolon
id|offb_name
(braket
r_sizeof
(paren
id|offb_name
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
id|offb_name
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;depth&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
op_logical_and
op_star
id|pp
op_ne
l_int|8
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: can&squot;t use depth = %d&bslash;n&quot;
comma
id|dp-&gt;full_name
comma
op_star
id|pp
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;width&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|fb_var.xres
op_assign
id|fb_var.xres_virtual
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;height&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|fb_var.yres
op_assign
id|fb_var.yres_virtual
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pp
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;linebytes&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|fb_fix.line_length
op_assign
op_star
id|pp
suffix:semicolon
r_else
id|fb_fix.line_length
op_assign
id|fb_var.xres_virtual
suffix:semicolon
id|fb_fix.smem_len
op_assign
id|fb_fix.line_length
op_star
id|fb_var.yres
suffix:semicolon
r_if
c_cond
(paren
(paren
id|up
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dp
comma
l_string|&quot;address&quot;
comma
op_amp
id|len
)paren
)paren
op_ne
l_int|NULL
op_logical_and
id|len
op_eq
r_sizeof
(paren
r_int
)paren
)paren
id|address
op_assign
(paren
id|u_long
)paren
op_star
id|up
suffix:semicolon
r_else
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
id|dp-&gt;n_addrs
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|size
op_ge
id|len
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|dp-&gt;n_addrs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;no framebuffer address found for %s&bslash;n&quot;
comma
id|dp-&gt;full_name
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
id|address
op_assign
(paren
id|u_long
)paren
id|dp-&gt;addrs
(braket
id|i
)braket
dot
id|address
suffix:semicolon
)brace
id|fb_fix.smem_start
op_assign
id|ioremap
c_func
(paren
id|address
comma
id|fb_fix.smem_len
)paren
suffix:semicolon
id|fb_fix.type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fb_fix.type_aux
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* XXX kludge for ati */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;ATY,&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|unknown_cmap_adr
op_assign
id|ioremap
c_func
(paren
id|address
op_plus
l_int|0x7ff000
comma
l_int|0x1000
)paren
op_plus
l_int|0xcc0
suffix:semicolon
id|unknown_cmap_data
op_assign
id|unknown_cmap_adr
op_plus
l_int|1
suffix:semicolon
)brace
id|fb_fix.visual
op_assign
id|unknown_cmap_adr
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_STATIC_PSEUDOCOLOR
suffix:semicolon
id|fb_var.xoffset
op_assign
id|fb_var.yoffset
op_assign
l_int|0
suffix:semicolon
id|fb_var.bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|fb_var.grayscale
op_assign
l_int|0
suffix:semicolon
id|fb_var.red.offset
op_assign
id|fb_var.green.offset
op_assign
id|fb_var.blue.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.red.length
op_assign
id|fb_var.green.length
op_assign
id|fb_var.blue.length
op_assign
l_int|8
suffix:semicolon
id|fb_var.red.msb_right
op_assign
id|fb_var.green.msb_right
op_assign
id|fb_var.blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.transp.offset
op_assign
id|fb_var.transp.length
op_assign
id|fb_var.transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.nonstd
op_assign
l_int|0
suffix:semicolon
id|fb_var.activate
op_assign
l_int|0
suffix:semicolon
id|fb_var.height
op_assign
id|fb_var.width
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_var.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
id|fb_var.pixclock
op_assign
l_int|10000
suffix:semicolon
id|fb_var.left_margin
op_assign
id|fb_var.right_margin
op_assign
l_int|16
suffix:semicolon
id|fb_var.upper_margin
op_assign
id|fb_var.lower_margin
op_assign
l_int|16
suffix:semicolon
id|fb_var.hsync_len
op_assign
id|fb_var.vsync_len
op_assign
l_int|8
suffix:semicolon
id|fb_var.sync
op_assign
l_int|0
suffix:semicolon
id|fb_var.vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|disp.var
op_assign
id|fb_var
suffix:semicolon
id|disp.cmap.start
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.len
op_assign
l_int|0
suffix:semicolon
id|disp.cmap.red
op_assign
id|disp.cmap.green
op_assign
id|disp.cmap.blue
op_assign
id|disp.cmap.transp
op_assign
l_int|NULL
suffix:semicolon
id|disp.screen_base
op_assign
id|fb_fix.smem_start
suffix:semicolon
id|disp.visual
op_assign
id|fb_fix.visual
suffix:semicolon
id|disp.type
op_assign
id|fb_fix.type
suffix:semicolon
id|disp.type_aux
op_assign
id|fb_fix.type_aux
suffix:semicolon
id|disp.ypanstep
op_assign
l_int|0
suffix:semicolon
id|disp.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|disp.line_length
op_assign
id|fb_fix.line_length
suffix:semicolon
id|disp.can_soft_blank
op_assign
l_int|1
suffix:semicolon
id|disp.inverse
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;OFfb &quot;
)paren
suffix:semicolon
id|strncat
c_func
(paren
id|fb_info.modename
comma
id|dp-&gt;full_name
comma
r_sizeof
(paren
id|fb_info.modename
)paren
)paren
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|offb_ops
suffix:semicolon
id|fb_info.fbvar_num
op_assign
l_int|1
suffix:semicolon
id|fb_info.fbvar
op_assign
op_amp
id|fb_var
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|offbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|offbcon_updatevar
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|offbcon_blank
suffix:semicolon
id|fb_info.setcmap
op_assign
op_amp
id|offbcon_setcmap
suffix:semicolon
id|err
op_assign
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
r_return
id|mem_start
suffix:semicolon
id|offb_set_var
c_func
(paren
op_amp
id|fb_var
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Open Firmware frame buffer device on %s&bslash;n&quot;
comma
id|dp-&gt;full_name
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
DECL|function|offbcon_switch
r_static
r_int
id|offbcon_switch
c_func
(paren
r_int
id|con
)paren
(brace
multiline_comment|/* Do we have to save the colormap? */
r_if
c_cond
(paren
id|fb_display
(braket
id|currcon
)braket
dot
id|cmap.len
)paren
id|fb_get_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|currcon
)braket
dot
id|cmap
comma
op_amp
id|fb_display
(braket
id|currcon
)braket
dot
id|var
comma
l_int|1
comma
id|offb_getcolreg
)paren
suffix:semicolon
id|currcon
op_assign
id|con
suffix:semicolon
multiline_comment|/* Install new colormap */
id|do_install_cmap
c_func
(paren
id|con
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Update the `var&squot; structure (called by fbcon.c)&n;     */
DECL|function|offbcon_updatevar
r_static
r_int
id|offbcon_updatevar
c_func
(paren
r_int
id|con
)paren
(brace
multiline_comment|/* Nothing */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Blank the display.&n;     */
DECL|function|offbcon_blank
r_static
r_void
id|offbcon_blank
c_func
(paren
r_int
id|blank
)paren
(brace
multiline_comment|/* Nothing */
)brace
multiline_comment|/*&n;     *  Set the colormap&n;     */
DECL|function|offbcon_setcmap
r_static
r_int
id|offbcon_setcmap
c_func
(paren
r_struct
id|fb_cmap
op_star
id|cmap
comma
r_int
id|con
)paren
(brace
r_return
id|offb_set_cmap
c_func
(paren
id|cmap
comma
l_int|1
comma
id|con
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Read a single color register and split it into&n;     *  colors/transparent. Return != 0 for invalid regno.&n;     */
DECL|function|offb_getcolreg
r_static
r_int
id|offb_getcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
op_star
id|red
comma
id|u_int
op_star
id|green
comma
id|u_int
op_star
id|blue
comma
id|u_int
op_star
id|transp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|unknown_cmap_adr
op_logical_or
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
op_star
id|red
op_assign
id|palette
(braket
id|regno
)braket
dot
id|red
suffix:semicolon
op_star
id|green
op_assign
id|palette
(braket
id|regno
)braket
dot
id|green
suffix:semicolon
op_star
id|blue
op_assign
id|palette
(braket
id|regno
)braket
dot
id|blue
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Set a single color register. The values supplied are already&n;     *  rounded down to the hardware&squot;s capabilities (according to the&n;     *  entries in the var structure). Return != 0 for invalid regno.&n;     */
DECL|function|offb_setcolreg
r_static
r_int
id|offb_setcolreg
c_func
(paren
id|u_int
id|regno
comma
id|u_int
id|red
comma
id|u_int
id|green
comma
id|u_int
id|blue
comma
id|u_int
id|transp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|unknown_cmap_adr
op_logical_or
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
suffix:semicolon
op_star
id|unknown_cmap_adr
op_assign
id|regno
suffix:semicolon
macro_line|#ifdef __powerpc__
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
op_star
id|unknown_cmap_data
op_assign
id|red
suffix:semicolon
macro_line|#ifdef __powerpc__
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
op_star
id|unknown_cmap_data
op_assign
id|green
suffix:semicolon
macro_line|#ifdef __powerpc__
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
op_star
id|unknown_cmap_data
op_assign
id|blue
suffix:semicolon
macro_line|#ifdef __powerpc__
id|eieio
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_install_cmap
r_static
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
)paren
(brace
r_if
c_cond
(paren
id|con
op_ne
id|currcon
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|fb_display
(braket
id|con
)braket
dot
id|cmap.len
)paren
id|fb_set_cmap
c_func
(paren
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|cmap
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
l_int|1
comma
id|offb_setcolreg
)paren
suffix:semicolon
r_else
id|fb_set_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
id|fb_display
(braket
id|con
)braket
dot
id|var.bits_per_pixel
)paren
comma
op_amp
id|fb_display
(braket
id|con
)braket
dot
id|var
comma
l_int|1
comma
id|offb_setcolreg
)paren
suffix:semicolon
)brace
eof
