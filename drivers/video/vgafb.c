multiline_comment|/*&n; *  linux/drivers/video/vgafb.c -- VGA frame buffer device&n; *&n; *&t;Created 28 Mar 1998 by Geert Uytterhoeven&n; *&t;Hardware cursor support added on 14 Apr 1998 by Emmanuel Marty&n; *&n; *  This file is heavily based on vgacon.c. Read about its contributors there.&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
multiline_comment|/* KNOWN PROBLEMS/TO DO ===================================================== *&n; *&n; *&t;- add support for loadable fonts and VESA blanking&n; *&n; *&t;- for now only VGA _text_ mode is supported&n; *&n; * KNOWN PROBLEMS/TO DO ==================================================== */
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
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &quot;fbcon.h&quot;
macro_line|#include &quot;fbcon-vga.h&quot;
DECL|macro|BLANK
mdefine_line|#define BLANK 0x0020
DECL|macro|CAN_LOAD_EGA_FONTS
mdefine_line|#define CAN_LOAD_EGA_FONTS&t;/* undefine if the user must not do this */
DECL|macro|CAN_LOAD_PALETTE
mdefine_line|#define CAN_LOAD_PALETTE&t;/* undefine if the user must not do this */
DECL|macro|dac_reg
mdefine_line|#define dac_reg&t;(0x3c8)
DECL|macro|dac_val
mdefine_line|#define dac_val&t;(0x3c9)
macro_line|#ifdef __powerpc__
DECL|macro|VGA_OFFSET
mdefine_line|#define VGA_OFFSET _ISA_MEM_BASE;
macro_line|#else
DECL|macro|VGA_OFFSET
mdefine_line|#define VGA_OFFSET 0x0
macro_line|#endif
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
l_int|16
)braket
suffix:semicolon
DECL|variable|fb_fix
r_static
r_struct
id|fb_fix_screeninfo
id|fb_fix
op_assign
(brace
(brace
l_int|0
comma
)brace
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
multiline_comment|/* Description of the hardware situation */
DECL|variable|vga_video_type
r_static
r_int
r_char
id|vga_video_type
suffix:semicolon
DECL|variable|vga_video_mem_base
r_static
r_int
r_int
id|vga_video_mem_base
suffix:semicolon
multiline_comment|/* Base of video memory */
DECL|variable|vga_video_mem_term
r_static
r_int
r_int
id|vga_video_mem_term
suffix:semicolon
multiline_comment|/* End of video memory */
DECL|variable|vga_video_port_reg
r_static
id|u16
id|vga_video_port_reg
suffix:semicolon
multiline_comment|/* Video register select port */
DECL|variable|vga_video_port_val
r_static
id|u16
id|vga_video_port_val
suffix:semicolon
multiline_comment|/* Video register value port */
DECL|variable|vga_video_num_columns
r_static
r_int
r_int
id|vga_video_num_columns
suffix:semicolon
multiline_comment|/* Number of text columns */
DECL|variable|vga_video_num_lines
r_static
r_int
r_int
id|vga_video_num_lines
suffix:semicolon
multiline_comment|/* Number of text lines */
DECL|variable|vga_can_do_color
r_static
r_int
id|vga_can_do_color
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;     *  VGA screen access&n;     */
DECL|function|vga_writew
r_static
r_inline
r_void
id|vga_writew
c_func
(paren
id|u16
id|val
comma
id|u16
op_star
id|addr
)paren
(brace
macro_line|#ifdef __powerpc__
id|st_le16
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
macro_line|#else
id|writew
c_func
(paren
id|val
comma
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
macro_line|#endif /* !__powerpc__ */
)brace
DECL|function|vga_readw
r_static
r_inline
id|u16
id|vga_readw
c_func
(paren
id|u16
op_star
id|addr
)paren
(brace
macro_line|#ifdef __powerpc__
r_return
id|ld_le16
c_func
(paren
id|addr
)paren
suffix:semicolon
macro_line|#else
r_return
id|readw
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
macro_line|#endif /* !__powerpc__ */&t;
)brace
multiline_comment|/*&n; * By replacing the four outb_p with two back to back outw, we can reduce&n; * the window of opportunity to see text mislocated to the RHS of the&n; * console during heavy scrolling activity. However there is the remote&n; * possibility that some pre-dinosaur hardware won&squot;t like the back to back&n; * I/O. Since the Xservers get away with it, we should be able to as well.&n; */
DECL|function|write_vga
r_static
r_inline
r_void
id|write_vga
c_func
(paren
r_int
r_char
id|reg
comma
r_int
r_int
id|val
)paren
(brace
macro_line|#ifndef SLOW_VGA
r_int
r_int
id|v1
comma
id|v2
suffix:semicolon
id|v1
op_assign
id|reg
op_plus
(paren
id|val
op_amp
l_int|0xff00
)paren
suffix:semicolon
id|v2
op_assign
id|reg
op_plus
l_int|1
op_plus
(paren
(paren
id|val
op_lshift
l_int|8
)paren
op_amp
l_int|0xff00
)paren
suffix:semicolon
id|outw
c_func
(paren
id|v1
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outw
c_func
(paren
id|v2
comma
id|vga_video_port_reg
)paren
suffix:semicolon
macro_line|#else
id|outb_p
c_func
(paren
id|reg
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|vga_video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg
op_plus
l_int|1
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xff
comma
id|vga_video_port_val
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|vga_set_origin
r_static
r_inline
r_void
id|vga_set_origin
c_func
(paren
r_int
r_int
id|location
)paren
(brace
id|write_vga
c_func
(paren
l_int|12
comma
id|location
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|vga_set_cursor
r_static
r_inline
r_void
id|vga_set_cursor
c_func
(paren
r_int
id|location
)paren
(brace
id|write_vga
c_func
(paren
l_int|14
comma
id|location
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|vga_set_split
r_static
r_void
id|vga_set_split
c_func
(paren
r_int
r_int
id|linenum
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|overflow
comma
id|fontsize
suffix:semicolon
r_if
c_cond
(paren
id|vga_video_type
op_ne
id|VIDEO_TYPE_VGAC
)paren
(brace
r_return
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|overflow
op_assign
id|inb_p
c_func
(paren
id|vga_video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x09
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|fontsize
op_assign
id|inb_p
c_func
(paren
id|vga_video_port_val
)paren
suffix:semicolon
id|overflow
op_and_assign
op_complement
l_int|0x10
suffix:semicolon
id|overflow
op_or_assign
(paren
id|linenum
op_amp
l_int|0x100
)paren
ques
c_cond
l_int|0x10
suffix:colon
l_int|0
suffix:semicolon
id|fontsize
op_and_assign
op_complement
l_int|0x40
suffix:semicolon
id|fontsize
op_or_assign
(paren
id|linenum
op_amp
l_int|0x200
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0
suffix:semicolon
id|linenum
op_and_assign
l_int|0xff
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x18
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|linenum
comma
id|vga_video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|overflow
comma
id|vga_video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x09
comma
id|vga_video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|fontsize
comma
id|vga_video_port_val
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|vga_set_palreg
r_static
r_inline
r_void
id|vga_set_palreg
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
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|regno
comma
id|dac_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|red
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|green
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|blue
comma
id|dac_val
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_static
r_int
id|vgafb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
r_static
r_int
id|vgafb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
suffix:semicolon
r_static
r_int
id|vgafb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_get_cmap
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_set_cmap
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_ioctl
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n;     *  Interface to the low level console driver&n;     */
r_void
id|vgafb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|vgafb_setup
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
id|vgafbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafbcon_updatevar
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|vgafbcon_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n;     *  VGA text console with hardware cursor&n;     */
DECL|variable|fbcon_vgafb
r_static
r_struct
id|display_switch
id|fbcon_vgafb
suffix:semicolon
multiline_comment|/*&n;     *  Internal routines&n;     */
r_static
r_int
id|vgafb_getcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_int
id|vgafb_setcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|do_install_cmap
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|variable|vgafb_ops
r_static
r_struct
id|fb_ops
id|vgafb_ops
op_assign
(brace
id|vgafb_open
comma
id|vgafb_release
comma
id|vgafb_get_fix
comma
id|vgafb_get_var
comma
id|vgafb_set_var
comma
id|vgafb_get_cmap
comma
id|vgafb_set_cmap
comma
id|vgafb_pan_display
comma
id|vgafb_ioctl
)brace
suffix:semicolon
multiline_comment|/*&n;     *  Open/Release the frame buffer device&n;     */
DECL|function|vgafb_open
r_static
r_int
id|vgafb_open
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
multiline_comment|/*&n;     *  Nothing, only a usage count for the moment&n;     */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vgafb_release
r_static
r_int
id|vgafb_release
c_func
(paren
r_struct
id|fb_info
op_star
id|info
comma
r_int
id|user
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the Fixed Part of the Display&n;     */
DECL|function|vgafb_get_fix
r_static
r_int
id|vgafb_get_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
DECL|function|vgafb_get_var
r_static
r_int
id|vgafb_get_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
DECL|function|vgafb_set_var
r_static
r_int
id|vgafb_set_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
op_logical_neg
(paren
id|var-&gt;accel_flags
op_amp
id|FB_ACCELF_TEXT
)paren
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
id|vga_set_origin
c_func
(paren
id|var-&gt;yoffset
op_div
id|video_font_height
op_star
id|fb_fix.line_length
)paren
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
comma
id|info
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Pan or Wrap the Display&n;     *&n;     *  This call looks only at xoffset, yoffset and the FB_VMODE_YWRAP flag&n;     */
DECL|function|vgafb_pan_display
r_static
r_int
id|vgafb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|var-&gt;xoffset
op_logical_or
id|var-&gt;yoffset
op_plus
id|var-&gt;yres
OG
id|var-&gt;yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vga_set_origin
c_func
(paren
id|var-&gt;yoffset
op_div
id|video_font_height
op_star
id|fb_fix.line_length
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Get the Colormap&n;     */
DECL|function|vgafb_get_cmap
r_static
r_int
id|vgafb_get_cmap
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
comma
r_struct
id|fb_info
op_star
id|info
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
id|vgafb_getcolreg
comma
id|info
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
l_int|1
op_lshift
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
DECL|function|vgafb_set_cmap
r_static
r_int
id|vgafb_set_cmap
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|err
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
(brace
multiline_comment|/* current console? */
id|err
op_assign
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
id|vgafb_setcolreg
comma
id|info
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
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
DECL|function|vgafb_ioctl
r_static
r_int
id|vgafb_ioctl
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Move hardware vga cursor&n;     */
DECL|function|fbcon_vgafb_cursor
r_static
r_void
id|fbcon_vgafb_cursor
c_func
(paren
r_struct
id|display
op_star
id|p
comma
r_int
id|mode
comma
r_int
id|x
comma
r_int
id|y
)paren
(brace
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|CM_ERASE
suffix:colon
id|vga_set_cursor
c_func
(paren
id|vga_video_mem_term
op_minus
id|vga_video_mem_base
op_minus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CM_MOVE
suffix:colon
r_case
id|CM_DRAW
suffix:colon
id|vga_set_cursor
c_func
(paren
id|y
op_star
id|p-&gt;next_line
op_plus
(paren
id|x
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|vgafb_init
c_func
(paren
r_void
)paren
)paren
(brace
id|u16
id|saved
suffix:semicolon
id|u16
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|screen_info.orig_video_isVGA
op_eq
id|VIDEO_TYPE_VLFB
)paren
r_return
suffix:semicolon
id|vga_video_num_lines
op_assign
id|ORIG_VIDEO_LINES
suffix:semicolon
id|vga_video_num_columns
op_assign
id|ORIG_VIDEO_COLS
suffix:semicolon
r_if
c_cond
(paren
id|ORIG_VIDEO_MODE
op_eq
l_int|7
)paren
(brace
multiline_comment|/* Is this a monochrome display? */
id|vga_video_mem_base
op_assign
l_int|0xb0000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|vga_video_port_reg
op_assign
l_int|0x3b4
suffix:semicolon
id|vga_video_port_val
op_assign
l_int|0x3b5
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ORIG_VIDEO_EGA_BX
op_amp
l_int|0xff
)paren
op_ne
l_int|0x10
)paren
(brace
id|vga_video_type
op_assign
id|VIDEO_TYPE_EGAM
suffix:semicolon
id|vga_video_mem_term
op_assign
l_int|0xb8000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
l_string|&quot;EGA+&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3b0
comma
l_int|16
comma
l_string|&quot;ega&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|vga_video_type
op_assign
id|VIDEO_TYPE_MDA
suffix:semicolon
id|vga_video_mem_term
op_assign
l_int|0xb1000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
l_string|&quot;*MDA&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3b0
comma
l_int|12
comma
l_string|&quot;mda&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3bf
comma
l_int|1
comma
l_string|&quot;mda&quot;
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* If not, it is color. */
id|vga_can_do_color
op_assign
l_int|1
suffix:semicolon
id|vga_video_mem_base
op_assign
l_int|0xb8000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|vga_video_port_reg
op_assign
l_int|0x3d4
suffix:semicolon
id|vga_video_port_val
op_assign
l_int|0x3d5
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ORIG_VIDEO_EGA_BX
op_amp
l_int|0xff
)paren
op_ne
l_int|0x10
)paren
(brace
r_int
id|i
suffix:semicolon
id|vga_video_mem_term
op_assign
l_int|0xc0000
op_plus
id|VGA_OFFSET
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ORIG_VIDEO_ISVGA
)paren
(brace
id|vga_video_type
op_assign
id|VIDEO_TYPE_EGAC
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
l_string|&quot;EGA&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3c0
comma
l_int|32
comma
l_string|&quot;ega&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|vga_video_type
op_assign
id|VIDEO_TYPE_VGAC
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
l_string|&quot;VGA+&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3c0
comma
l_int|32
comma
l_string|&quot;vga+&quot;
)paren
suffix:semicolon
macro_line|#ifdef VGA_CAN_DO_64KB
multiline_comment|/*&n;&t;&t; * get 64K rather than 32K of video RAM.&n;&t;&t; * This doesn&squot;t actually work on all &quot;VGA&quot;&n;&t;&t; * controllers (it seems like setting MM=01&n;&t;&t; * and COE=1 isn&squot;t necessarily a good idea)&n;&t;&t; */
id|vga_video_mem_base
op_assign
l_int|0xa0000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|vga_video_mem_term
op_assign
l_int|0xb0000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|outb_p
c_func
(paren
l_int|6
comma
l_int|0x3ce
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|6
comma
l_int|0x3cf
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t; * Normalise the palette registers, to point&n;&t;&t; * the 16 screen colours to the first 16&n;&t;&t; * DAC entries.&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|inb_p
c_func
(paren
l_int|0x3da
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|i
comma
l_int|0x3c0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|i
comma
l_int|0x3c0
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0x20
comma
l_int|0x3c0
)paren
suffix:semicolon
multiline_comment|/* now set the DAC registers back to their&n;&t;&t; * default values */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vga_set_palreg
c_func
(paren
id|color_table
(braket
id|i
)braket
comma
id|default_red
(braket
id|i
)braket
comma
id|default_grn
(braket
id|i
)braket
comma
id|default_blu
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|vga_video_type
op_assign
id|VIDEO_TYPE_CGA
suffix:semicolon
id|vga_video_mem_term
op_assign
l_int|0xba000
op_plus
id|VGA_OFFSET
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_fix.id
comma
l_string|&quot;*CGA&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x3d4
comma
l_int|2
comma
l_string|&quot;cga&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *&t;Find out if there is a graphics card present.&n;     *&t;Are there smarter methods around?&n;     */
id|p
op_assign
(paren
id|u16
op_star
)paren
id|vga_video_mem_base
suffix:semicolon
id|saved
op_assign
id|vga_readw
c_func
(paren
id|p
)paren
suffix:semicolon
id|vga_writew
c_func
(paren
l_int|0xAA55
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vga_readw
c_func
(paren
id|p
)paren
op_ne
l_int|0xAA55
)paren
(brace
id|vga_writew
c_func
(paren
id|saved
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vga_writew
c_func
(paren
l_int|0x55AA
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vga_readw
c_func
(paren
id|p
)paren
op_ne
l_int|0x55AA
)paren
(brace
id|vga_writew
c_func
(paren
id|saved
comma
id|p
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vga_writew
c_func
(paren
id|saved
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vga_video_type
op_eq
id|VIDEO_TYPE_VGAC
op_logical_or
id|vga_video_type
op_eq
id|VIDEO_TYPE_EGAC
op_logical_or
id|vga_video_type
op_eq
id|VIDEO_TYPE_EGAM
)paren
(brace
id|video_font_height
op_assign
id|ORIG_VIDEO_POINTS
suffix:semicolon
)brace
r_else
(brace
id|video_font_height
op_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* This may be suboptimal but is a safe bet - go with it */
id|video_scan_lines
op_assign
id|video_font_height
op_star
id|vga_video_num_lines
suffix:semicolon
id|fb_fix.smem_start
op_assign
(paren
r_char
op_star
)paren
id|vga_video_mem_base
suffix:semicolon
id|fb_fix.smem_len
op_assign
id|vga_video_mem_term
op_minus
id|vga_video_mem_base
suffix:semicolon
id|fb_fix.type
op_assign
id|FB_TYPE_TEXT
suffix:semicolon
id|fb_fix.type_aux
op_assign
id|vga_can_do_color
ques
c_cond
id|FB_AUX_TEXT_CGA
suffix:colon
id|FB_AUX_TEXT_MDA
suffix:semicolon
id|fb_fix.visual
op_assign
id|FB_VISUAL_PSEUDOCOLOR
suffix:semicolon
id|fb_fix.xpanstep
op_assign
l_int|0
suffix:semicolon
id|fb_fix.ypanstep
op_assign
id|video_font_height
suffix:semicolon
id|fb_fix.ywrapstep
op_assign
l_int|0
suffix:semicolon
id|fb_fix.line_length
op_assign
l_int|2
op_star
id|vga_video_num_columns
suffix:semicolon
id|fb_fix.mmio_start
op_assign
l_int|NULL
suffix:semicolon
id|fb_fix.mmio_len
op_assign
l_int|0
suffix:semicolon
id|fb_fix.accel
op_assign
id|FB_ACCEL_NONE
suffix:semicolon
id|fb_var.xres
op_assign
id|vga_video_num_columns
op_star
l_int|8
suffix:semicolon
id|fb_var.yres
op_assign
id|vga_video_num_lines
op_star
id|video_font_height
suffix:semicolon
id|fb_var.xres_virtual
op_assign
id|fb_var.xres
suffix:semicolon
multiline_comment|/* the cursor is put at the end of the video memory, hence the -2 */
id|fb_var.yres_virtual
op_assign
(paren
(paren
id|fb_fix.smem_len
op_minus
l_int|2
)paren
op_div
id|fb_fix.line_length
)paren
op_star
id|video_font_height
suffix:semicolon
id|fb_var.xoffset
op_assign
id|fb_var.yoffset
op_assign
l_int|0
suffix:semicolon
id|fb_var.bits_per_pixel
op_assign
id|vga_can_do_color
ques
c_cond
l_int|4
suffix:colon
l_int|1
suffix:semicolon
id|fb_var.grayscale
op_assign
op_logical_neg
id|vga_can_do_color
suffix:semicolon
id|fb_var.red.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.red.length
op_assign
l_int|6
suffix:semicolon
id|fb_var.red.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.green.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.green.length
op_assign
l_int|6
suffix:semicolon
id|fb_var.green.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.blue.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.blue.length
op_assign
l_int|6
suffix:semicolon
id|fb_var.blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|fb_var.transp.offset
op_assign
l_int|0
suffix:semicolon
id|fb_var.transp.length
op_assign
l_int|0
suffix:semicolon
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
id|fb_var.accel_flags
op_assign
id|FB_ACCELF_TEXT
suffix:semicolon
id|fb_var.pixclock
op_assign
l_int|39722
suffix:semicolon
multiline_comment|/* 25.175 MHz */
id|fb_var.left_margin
op_assign
l_int|40
suffix:semicolon
id|fb_var.right_margin
op_assign
l_int|24
suffix:semicolon
id|fb_var.upper_margin
op_assign
l_int|39
suffix:semicolon
id|fb_var.lower_margin
op_assign
l_int|9
suffix:semicolon
id|fb_var.hsync_len
op_assign
l_int|96
suffix:semicolon
id|fb_var.vsync_len
op_assign
l_int|2
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
l_int|NULL
suffix:semicolon
id|disp.cmap.green
op_assign
l_int|NULL
suffix:semicolon
id|disp.cmap.blue
op_assign
l_int|NULL
suffix:semicolon
id|disp.cmap.transp
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef __i386__
id|disp.screen_base
op_assign
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|fb_fix.smem_start
comma
id|fb_fix.smem_len
)paren
suffix:semicolon
macro_line|#else
id|disp.screen_base
op_assign
id|bus_to_virt
c_func
(paren
(paren
r_int
r_int
)paren
id|fb_fix.smem_start
)paren
suffix:semicolon
macro_line|#endif
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
id|fb_fix.ypanstep
suffix:semicolon
id|disp.ywrapstep
op_assign
id|fb_fix.ywrapstep
suffix:semicolon
id|disp.line_length
op_assign
id|fb_fix.line_length
suffix:semicolon
id|disp.can_soft_blank
op_assign
id|vga_can_do_color
suffix:semicolon
id|disp.inverse
op_assign
l_int|0
suffix:semicolon
id|disp.dispsw
op_assign
op_amp
id|fbcon_vgafb
suffix:semicolon
id|strcpy
c_func
(paren
id|fb_info.modename
comma
id|fb_fix.id
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
id|vgafb_ops
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
id|vgafbcon_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|vgafbcon_updatevar
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|vgafbcon_blank
suffix:semicolon
id|vgafb_set_var
c_func
(paren
op_amp
id|fb_var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
OL
l_int|0
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;fb%d: VGA frame buffer device, using %dK of video memory&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_fix.smem_len
op_rshift
l_int|10
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|vgafb_setup
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
)paren
(brace
multiline_comment|/* nothing yet */
)brace
multiline_comment|/*&n;     *  Update the `var&squot; structure (called by fbcon.c)&n;     */
DECL|function|vgafbcon_updatevar
r_static
r_int
id|vgafbcon_updatevar
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|con
op_eq
id|currcon
)paren
(brace
r_struct
id|fb_var_screeninfo
op_star
id|var
op_assign
op_amp
id|fb_display
(braket
id|currcon
)braket
dot
id|var
suffix:semicolon
multiline_comment|/* hardware scrolling */
id|vga_set_origin
c_func
(paren
id|var-&gt;yoffset
op_div
id|video_font_height
op_star
id|fb_fix.line_length
)paren
suffix:semicolon
id|vga_set_split
c_func
(paren
id|var-&gt;yres
op_minus
(paren
(paren
id|var-&gt;vmode
op_amp
id|FB_VMODE_YWRAP
)paren
ques
c_cond
id|var-&gt;yoffset
op_plus
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vgafbcon_switch
r_static
r_int
id|vgafbcon_switch
c_func
(paren
r_int
id|con
comma
r_struct
id|fb_info
op_star
id|info
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
id|vgafb_getcolreg
comma
id|info
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
comma
id|info
)paren
suffix:semicolon
id|vgafbcon_updatevar
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;     *  Blank the display.&n;     */
DECL|function|vgafbcon_blank
r_static
r_void
id|vgafbcon_blank
c_func
(paren
r_int
id|blank
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|blank
)paren
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vga_set_palreg
c_func
(paren
id|i
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|vga_set_palreg
c_func
(paren
id|i
comma
id|palette
(braket
id|i
)braket
dot
id|red
comma
id|palette
(braket
id|i
)braket
dot
id|green
comma
id|palette
(braket
id|i
)braket
dot
id|blue
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;     *  Read a single color register and split it into&n;     *  colors/transparent. Return != 0 for invalid regno.&n;     */
DECL|function|vgafb_getcolreg
r_static
r_int
id|vgafb_getcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|regno
OG
l_int|15
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
DECL|function|vgafb_setcolreg
r_static
r_int
id|vgafb_setcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|regno
OG
l_int|15
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
id|vga_set_palreg
c_func
(paren
id|regno
comma
id|red
comma
id|green
comma
id|blue
)paren
suffix:semicolon
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
comma
r_struct
id|fb_info
op_star
id|info
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
id|vgafb_setcolreg
comma
id|info
)paren
suffix:semicolon
r_else
id|fb_set_cmap
c_func
(paren
id|fb_default_cmap
c_func
(paren
l_int|1
op_lshift
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
id|vgafb_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *  VGA text console with hardware cursor&n;     */
DECL|variable|fbcon_vgafb
r_static
r_struct
id|display_switch
id|fbcon_vgafb
op_assign
(brace
id|fbcon_vga_setup
comma
id|fbcon_vga_bmove
comma
id|fbcon_vga_clear
comma
id|fbcon_vga_putc
comma
id|fbcon_vga_putcs
comma
id|fbcon_vga_revc
comma
id|fbcon_vgafb_cursor
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|vgafb_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_framebuffer
c_func
(paren
op_amp
id|fb_info
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof