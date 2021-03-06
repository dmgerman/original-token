multiline_comment|/*&n; * framebuffer driver for VBE 2.0 compliant graphic boards&n; *&n; * switching to graphics mode happens at boot time (while&n; * running in real mode, see arch/i386/video.S).&n; *&n; * (c) 1998 Gerd Knorr &lt;kraxel@goldbach.in-berlin.de&gt;&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mtrr.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;video/fbcon-cfb24.h&gt;
macro_line|#include &lt;video/fbcon-cfb32.h&gt;
macro_line|#include &lt;video/fbcon-mac.h&gt;
DECL|macro|dac_reg
mdefine_line|#define dac_reg&t;(0x3c8)
DECL|macro|dac_val
mdefine_line|#define dac_val&t;(0x3c9)
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * card parameters&n; */
multiline_comment|/* card */
DECL|variable|video_base
r_int
r_int
id|video_base
suffix:semicolon
multiline_comment|/* physical addr */
DECL|variable|video_size
r_int
id|video_size
suffix:semicolon
DECL|variable|video_vbase
r_char
op_star
id|video_vbase
suffix:semicolon
multiline_comment|/* mapped */
multiline_comment|/* mode */
DECL|variable|video_bpp
r_static
r_int
id|video_bpp
suffix:semicolon
DECL|variable|video_width
r_static
r_int
id|video_width
suffix:semicolon
DECL|variable|video_height
r_static
r_int
id|video_height
suffix:semicolon
DECL|variable|video_height_virtual
r_static
r_int
id|video_height_virtual
suffix:semicolon
DECL|variable|video_type
r_static
r_int
id|video_type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
DECL|variable|video_visual
r_static
r_int
id|video_visual
suffix:semicolon
DECL|variable|video_linelength
r_static
r_int
id|video_linelength
suffix:semicolon
DECL|variable|video_cmap_len
r_static
r_int
id|video_cmap_len
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|vesafb_defined
r_static
r_struct
id|fb_var_screeninfo
id|vesafb_defined
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* W,H, W, H (virtual) load xres,xres_virtual*/
l_int|0
comma
l_int|0
comma
multiline_comment|/* virtual -&gt; visible no offset */
l_int|8
comma
multiline_comment|/* depth -&gt; load bits_per_pixel */
l_int|0
comma
multiline_comment|/* greyscale ? */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* R */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* G */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* B */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* transparency */
l_int|0
comma
multiline_comment|/* standard pixel format */
id|FB_ACTIVATE_NOW
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|0
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
comma
l_int|0
comma
multiline_comment|/* No sync info */
id|FB_VMODE_NONINTERLACED
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
)brace
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
DECL|member|blue
DECL|member|green
DECL|member|red
DECL|member|pad
DECL|variable|palette
r_static
r_struct
(brace
id|u_short
id|blue
comma
id|green
comma
id|red
comma
id|pad
suffix:semicolon
)brace
id|palette
(braket
l_int|256
)braket
suffix:semicolon
r_static
r_union
(brace
macro_line|#ifdef FBCON_HAS_CFB16
DECL|member|cfb16
id|u16
id|cfb16
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
DECL|member|cfb24
id|u32
id|cfb24
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
DECL|member|cfb32
id|u32
id|cfb32
(braket
l_int|16
)braket
suffix:semicolon
macro_line|#endif
DECL|variable|fbcon_cmap
)brace
id|fbcon_cmap
suffix:semicolon
DECL|variable|inverse
r_static
r_int
id|inverse
op_assign
l_int|0
suffix:semicolon
DECL|variable|mtrr
r_static
r_int
id|mtrr
op_assign
l_int|0
suffix:semicolon
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|variable|pmi_setpal
r_static
r_int
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pmi for palette changes ??? */
DECL|variable|ypan
r_static
r_int
id|ypan
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0..nothing, 1..ypan, 2..ywrap */
DECL|variable|pmi_base
r_static
r_int
r_int
op_star
id|pmi_base
op_assign
l_int|0
suffix:semicolon
DECL|variable|pmi_start
r_static
r_void
(paren
op_star
id|pmi_start
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|pmi_pal
r_static
r_void
(paren
op_star
id|pmi_pal
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|vesafb_sw
r_static
r_struct
id|display_switch
id|vesafb_sw
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|vesafb_pan_display
r_static
r_int
id|vesafb_pan_display
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
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ypan
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;yoffset
OG
id|var-&gt;yres_virtual
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ypan
op_eq
l_int|1
)paren
op_logical_and
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
id|offset
op_assign
(paren
id|var-&gt;yoffset
op_star
id|video_linelength
op_plus
id|var-&gt;xoffset
)paren
op_div
l_int|4
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call *(%%edi)&quot;
suffix:colon
multiline_comment|/* no return value */
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0x4f07
)paren
comma
multiline_comment|/* EAX */
l_string|&quot;b&quot;
(paren
l_int|0
)paren
comma
multiline_comment|/* EBX */
l_string|&quot;c&quot;
(paren
id|offset
)paren
comma
multiline_comment|/* ECX */
l_string|&quot;d&quot;
(paren
id|offset
op_rshift
l_int|16
)paren
comma
multiline_comment|/* EDX */
l_string|&quot;D&quot;
(paren
op_amp
id|pmi_start
)paren
)paren
suffix:semicolon
multiline_comment|/* EDI */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesafb_update_var
r_static
r_int
id|vesafb_update_var
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
op_logical_and
id|ypan
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
r_return
id|vesafb_pan_display
c_func
(paren
id|var
comma
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
DECL|function|vesafb_get_fix
r_static
r_int
id|vesafb_get_fix
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
id|memset
c_func
(paren
id|fix
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;VESA VGA&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|video_base
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|video_size
suffix:semicolon
id|fix-&gt;type
op_assign
id|video_type
suffix:semicolon
id|fix-&gt;visual
op_assign
id|video_visual
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
id|ypan
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
(paren
id|ypan
OG
l_int|1
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|fix-&gt;line_length
op_assign
id|video_linelength
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesafb_get_var
r_static
r_int
id|vesafb_get_var
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
id|con
op_eq
op_minus
l_int|1
)paren
(brace
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|vesafb_defined
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
)paren
)paren
suffix:semicolon
)brace
r_else
op_star
id|var
op_assign
id|fb_display
(braket
id|con
)braket
dot
id|var
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesafb_set_disp
r_static
r_void
id|vesafb_set_disp
c_func
(paren
r_int
id|con
)paren
(brace
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
r_struct
id|display
op_star
id|display
suffix:semicolon
r_struct
id|display_switch
op_star
id|sw
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
id|vesafb_get_fix
c_func
(paren
op_amp
id|fix
comma
id|con
comma
l_int|0
)paren
suffix:semicolon
id|memset
c_func
(paren
id|display
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|display
)paren
)paren
suffix:semicolon
id|display-&gt;screen_base
op_assign
id|video_vbase
suffix:semicolon
id|display-&gt;visual
op_assign
id|fix.visual
suffix:semicolon
id|display-&gt;type
op_assign
id|fix.type
suffix:semicolon
id|display-&gt;type_aux
op_assign
id|fix.type_aux
suffix:semicolon
id|display-&gt;ypanstep
op_assign
id|fix.ypanstep
suffix:semicolon
id|display-&gt;ywrapstep
op_assign
id|fix.ywrapstep
suffix:semicolon
id|display-&gt;line_length
op_assign
id|fix.line_length
suffix:semicolon
id|display-&gt;next_line
op_assign
id|fix.line_length
suffix:semicolon
id|display-&gt;can_soft_blank
op_assign
l_int|0
suffix:semicolon
id|display-&gt;inverse
op_assign
id|inverse
suffix:semicolon
id|vesafb_get_var
c_func
(paren
op_amp
id|display-&gt;var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|video_bpp
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|sw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|15
suffix:colon
r_case
l_int|16
suffix:colon
id|sw
op_assign
op_amp
id|fbcon_cfb16
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb16
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
r_case
l_int|24
suffix:colon
id|sw
op_assign
op_amp
id|fbcon_cfb24
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb24
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
r_case
l_int|32
suffix:colon
id|sw
op_assign
op_amp
id|fbcon_cfb32
suffix:semicolon
id|display-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb32
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
macro_line|#ifdef FBCON_HAS_MAC
id|sw
op_assign
op_amp
id|fbcon_mac
suffix:semicolon
r_break
suffix:semicolon
macro_line|#else
id|sw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
r_return
suffix:semicolon
macro_line|#endif
)brace
id|memcpy
c_func
(paren
op_amp
id|vesafb_sw
comma
id|sw
comma
r_sizeof
(paren
op_star
id|sw
)paren
)paren
suffix:semicolon
id|display-&gt;dispsw
op_assign
op_amp
id|vesafb_sw
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ypan
)paren
(brace
id|display-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|vesafb_sw.bmove
op_assign
id|fbcon_redraw_bmove
suffix:semicolon
)brace
)brace
DECL|function|vesafb_set_var
r_static
r_int
id|vesafb_set_var
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
r_static
r_int
id|first
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|var-&gt;xres
op_ne
id|vesafb_defined.xres
op_logical_or
id|var-&gt;yres
op_ne
id|vesafb_defined.yres
op_logical_or
id|var-&gt;xres_virtual
op_ne
id|vesafb_defined.xres_virtual
op_logical_or
id|var-&gt;yres_virtual
OG
id|video_height_virtual
op_logical_or
id|var-&gt;yres_virtual
OL
id|video_height
op_logical_or
id|var-&gt;xoffset
op_logical_or
id|var-&gt;bits_per_pixel
op_ne
id|vesafb_defined.bits_per_pixel
op_logical_or
id|var-&gt;nonstd
)paren
(brace
r_if
c_cond
(paren
id|first
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Vesafb does not support changing the video mode&bslash;n&quot;
)paren
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|var-&gt;activate
op_amp
id|FB_ACTIVATE_MASK
)paren
op_eq
id|FB_ACTIVATE_TEST
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ypan
)paren
(brace
r_if
c_cond
(paren
id|vesafb_defined.yres_virtual
op_ne
id|var-&gt;yres_virtual
)paren
(brace
id|vesafb_defined.yres_virtual
op_assign
id|var-&gt;yres_virtual
suffix:semicolon
r_if
c_cond
(paren
id|con
op_ne
op_minus
l_int|1
)paren
(brace
id|fb_display
(braket
id|con
)braket
dot
id|var
op_assign
id|vesafb_defined
suffix:semicolon
id|info
op_member_access_from_pointer
id|changevar
c_func
(paren
id|con
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|var-&gt;yoffset
op_ne
id|vesafb_defined.yoffset
)paren
r_return
id|vesafb_pan_display
c_func
(paren
id|var
comma
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|var-&gt;yoffset
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesa_getcolreg
r_static
r_int
id|vesa_getcolreg
c_func
(paren
r_int
id|regno
comma
r_int
op_star
id|red
comma
r_int
op_star
id|green
comma
r_int
op_star
id|blue
comma
r_int
op_star
id|transp
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
(brace
multiline_comment|/*&n;&t; *  Read a single color register and split it into colors/transparent.&n;&t; *  Return != 0 for invalid regno.&n;&t; */
r_if
c_cond
(paren
id|regno
op_ge
id|video_cmap_len
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
op_star
id|transp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef FBCON_HAS_CFB8
DECL|function|vesa_setpalette
r_static
r_void
id|vesa_setpalette
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
)paren
(brace
r_struct
(brace
id|u_char
id|blue
comma
id|green
comma
id|red
comma
id|pad
suffix:semicolon
)brace
id|entry
suffix:semicolon
r_if
c_cond
(paren
id|pmi_setpal
)paren
(brace
id|entry.red
op_assign
id|red
op_rshift
l_int|10
suffix:semicolon
id|entry.green
op_assign
id|green
op_rshift
l_int|10
suffix:semicolon
id|entry.blue
op_assign
id|blue
op_rshift
l_int|10
suffix:semicolon
id|entry.pad
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;call *(%%esi)&quot;
suffix:colon
multiline_comment|/* no return value */
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0x4f09
)paren
comma
multiline_comment|/* EAX */
l_string|&quot;b&quot;
(paren
l_int|0
)paren
comma
multiline_comment|/* EBX */
l_string|&quot;c&quot;
(paren
l_int|1
)paren
comma
multiline_comment|/* ECX */
l_string|&quot;d&quot;
(paren
id|regno
)paren
comma
multiline_comment|/* EDX */
l_string|&quot;D&quot;
(paren
op_amp
id|entry
)paren
comma
multiline_comment|/* EDI */
l_string|&quot;S&quot;
(paren
op_amp
id|pmi_pal
)paren
)paren
suffix:semicolon
multiline_comment|/* ESI */
)brace
r_else
(brace
multiline_comment|/* without protected mode interface, try VGA registers... */
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
op_rshift
l_int|10
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|green
op_rshift
l_int|10
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|blue
op_rshift
l_int|10
comma
id|dac_val
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|vesa_setcolreg
r_static
r_int
id|vesa_setcolreg
c_func
(paren
r_int
id|regno
comma
r_int
id|red
comma
r_int
id|green
comma
r_int
id|blue
comma
r_int
id|transp
comma
r_struct
id|fb_info
op_star
id|fb_info
)paren
(brace
multiline_comment|/*&n;&t; *  Set a single color register. The values supplied are&n;&t; *  already rounded down to the hardware&squot;s capabilities&n;&t; *  (according to the entries in the `var&squot; structure). Return&n;&t; *  != 0 for invalid regno.&n;&t; */
r_if
c_cond
(paren
id|regno
op_ge
id|video_cmap_len
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
r_switch
c_cond
(paren
id|video_bpp
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|vesa_setpalette
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
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|15
suffix:colon
r_case
l_int|16
suffix:colon
r_if
c_cond
(paren
id|vesafb_defined.red.offset
op_eq
l_int|10
)paren
(brace
multiline_comment|/* 1:5:5:5 */
id|fbcon_cmap.cfb16
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf800
)paren
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xf800
)paren
op_rshift
l_int|6
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf800
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 0:5:6:5 */
id|fbcon_cmap.cfb16
(braket
id|regno
)braket
op_assign
(paren
(paren
id|red
op_amp
l_int|0xf800
)paren
)paren
op_or
(paren
(paren
id|green
op_amp
l_int|0xfc00
)paren
op_rshift
l_int|5
)paren
op_or
(paren
(paren
id|blue
op_amp
l_int|0xf800
)paren
op_rshift
l_int|11
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB24
r_case
l_int|24
suffix:colon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|fbcon_cmap.cfb24
(braket
id|regno
)braket
op_assign
(paren
id|red
op_lshift
id|vesafb_defined.red.offset
)paren
op_or
(paren
id|green
op_lshift
id|vesafb_defined.green.offset
)paren
op_or
(paren
id|blue
op_lshift
id|vesafb_defined.blue.offset
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB32
r_case
l_int|32
suffix:colon
id|red
op_rshift_assign
l_int|8
suffix:semicolon
id|green
op_rshift_assign
l_int|8
suffix:semicolon
id|blue
op_rshift_assign
l_int|8
suffix:semicolon
id|fbcon_cmap.cfb32
(braket
id|regno
)braket
op_assign
(paren
id|red
op_lshift
id|vesafb_defined.red.offset
)paren
op_or
(paren
id|green
op_lshift
id|vesafb_defined.green.offset
)paren
op_or
(paren
id|blue
op_lshift
id|vesafb_defined.blue.offset
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
)brace
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
l_int|1
comma
id|vesa_setcolreg
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
id|video_cmap_len
)paren
comma
l_int|1
comma
id|vesa_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
DECL|function|vesafb_get_cmap
r_static
r_int
id|vesafb_get_cmap
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
id|kspc
comma
id|vesa_getcolreg
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
id|video_cmap_len
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
DECL|function|vesafb_set_cmap
r_static
r_int
id|vesafb_set_cmap
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
id|video_cmap_len
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
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
id|kspc
comma
id|vesa_setcolreg
comma
id|info
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
DECL|variable|vesafb_ops
r_static
r_struct
id|fb_ops
id|vesafb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|vesafb_get_fix
comma
id|fb_get_var
suffix:colon
id|vesafb_get_var
comma
id|fb_set_var
suffix:colon
id|vesafb_set_var
comma
id|fb_get_cmap
suffix:colon
id|vesafb_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|vesafb_set_cmap
comma
id|fb_pan_display
suffix:colon
id|vesafb_pan_display
comma
)brace
suffix:semicolon
DECL|function|vesafb_setup
r_int
id|__init
id|vesafb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_char
op_star
id|this_opt
suffix:semicolon
id|fb_info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|options
op_logical_or
op_logical_neg
op_star
id|options
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|this_opt
op_assign
id|strtok
c_func
(paren
id|options
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
id|this_opt
suffix:semicolon
id|this_opt
op_assign
id|strtok
c_func
(paren
l_int|NULL
comma
l_string|&quot;,&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|this_opt
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;inverse&quot;
)paren
)paren
id|inverse
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;redraw&quot;
)paren
)paren
id|ypan
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;ypan&quot;
)paren
)paren
id|ypan
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;ywrap&quot;
)paren
)paren
id|ypan
op_assign
l_int|2
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;vgapal&quot;
)paren
)paren
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;pmipal&quot;
)paren
)paren
id|pmi_setpal
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|this_opt
comma
l_string|&quot;mtrr&quot;
)paren
)paren
id|mtrr
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|this_opt
comma
l_string|&quot;font:&quot;
comma
l_int|5
)paren
)paren
id|strcpy
c_func
(paren
id|fb_info.fontname
comma
id|this_opt
op_plus
l_int|5
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vesafb_switch
r_static
r_int
id|vesafb_switch
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
l_int|1
comma
id|vesa_getcolreg
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
id|vesafb_update_var
c_func
(paren
id|con
comma
id|info
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* 0 unblank, 1 blank, 2 no vsync, 3 no hsync, 4 off */
DECL|function|vesafb_blank
r_static
r_void
id|vesafb_blank
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
multiline_comment|/* Not supported */
)brace
DECL|function|vesafb_init
r_int
id|__init
id|vesafb_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|screen_info.orig_video_isVGA
op_ne
id|VIDEO_TYPE_VLFB
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|video_base
op_assign
id|screen_info.lfb_base
suffix:semicolon
id|video_bpp
op_assign
id|screen_info.lfb_depth
suffix:semicolon
r_if
c_cond
(paren
l_int|15
op_eq
id|video_bpp
)paren
id|video_bpp
op_assign
l_int|16
suffix:semicolon
id|video_width
op_assign
id|screen_info.lfb_width
suffix:semicolon
id|video_height
op_assign
id|screen_info.lfb_height
suffix:semicolon
id|video_linelength
op_assign
id|screen_info.lfb_linelength
suffix:semicolon
id|video_size
op_assign
id|screen_info.lfb_size
op_star
l_int|65536
suffix:semicolon
id|video_visual
op_assign
(paren
id|video_bpp
op_eq
l_int|8
)paren
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|video_base
comma
id|video_size
comma
l_string|&quot;vesafb&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vesafb: abort, cannot reserve video memory at 0x%lx&bslash;n&quot;
comma
id|video_base
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|video_vbase
op_assign
id|ioremap
c_func
(paren
id|video_base
comma
id|video_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|video_vbase
)paren
(brace
id|release_mem_region
c_func
(paren
id|video_base
comma
id|video_size
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vesafb: abort, cannot ioremap video memory 0x%x @ 0x%lx&bslash;n&quot;
comma
id|video_size
comma
id|video_base
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: framebuffer at 0x%lx, mapped to 0x%p, size %dk&bslash;n&quot;
comma
id|video_base
comma
id|video_vbase
comma
id|video_size
op_div
l_int|1024
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: mode is %dx%dx%d, linelength=%d, pages=%d&bslash;n&quot;
comma
id|video_width
comma
id|video_height
comma
id|video_bpp
comma
id|video_linelength
comma
id|screen_info.pages
)paren
suffix:semicolon
r_if
c_cond
(paren
id|screen_info.vesapm_seg
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: protected mode interface info at %04x:%04x&bslash;n&quot;
comma
id|screen_info.vesapm_seg
comma
id|screen_info.vesapm_off
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|screen_info.vesapm_seg
OL
l_int|0xc000
)paren
id|ypan
op_assign
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* not available or some DOS TSR ... */
r_if
c_cond
(paren
id|ypan
op_logical_or
id|pmi_setpal
)paren
(brace
id|pmi_base
op_assign
(paren
r_int
r_int
op_star
)paren
id|bus_to_virt
c_func
(paren
(paren
(paren
r_int
r_int
)paren
id|screen_info.vesapm_seg
op_lshift
l_int|4
)paren
op_plus
id|screen_info.vesapm_off
)paren
suffix:semicolon
id|pmi_start
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|pmi_base
op_plus
id|pmi_base
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|pmi_pal
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|pmi_base
op_plus
id|pmi_base
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: pmi: set display start = %p, set palette = %p&bslash;n&quot;
comma
id|pmi_start
comma
id|pmi_pal
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmi_base
(braket
l_int|3
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: pmi: ports = &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|pmi_base
(braket
l_int|3
)braket
op_div
l_int|2
suffix:semicolon
id|pmi_base
(braket
id|i
)braket
op_ne
l_int|0xffff
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%x &quot;
comma
id|pmi_base
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmi_base
(braket
id|i
)braket
op_ne
l_int|0xffff
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * memory areas not supported (yet?)&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; * Rules are: we have to set up a descriptor for the requested&n;&t;&t;&t;&t; * memory area and pass it in the ES register to the BIOS function.&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: can&squot;t handle memory requests, pmi disabled&bslash;n&quot;
)paren
suffix:semicolon
id|ypan
op_assign
id|pmi_setpal
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|vesafb_defined.xres
op_assign
id|video_width
suffix:semicolon
id|vesafb_defined.yres
op_assign
id|video_height
suffix:semicolon
id|vesafb_defined.xres_virtual
op_assign
id|video_width
suffix:semicolon
id|vesafb_defined.yres_virtual
op_assign
id|video_size
op_div
id|video_linelength
suffix:semicolon
id|vesafb_defined.bits_per_pixel
op_assign
id|video_bpp
suffix:semicolon
r_if
c_cond
(paren
id|ypan
op_logical_and
id|vesafb_defined.yres_virtual
OG
id|video_height
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: scrolling: %s using protected mode interface, yres_virtual=%d&bslash;n&quot;
comma
(paren
id|ypan
OG
l_int|1
)paren
ques
c_cond
l_string|&quot;ywrap&quot;
suffix:colon
l_string|&quot;ypan&quot;
comma
id|vesafb_defined.yres_virtual
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: scrolling: redraw&bslash;n&quot;
)paren
suffix:semicolon
id|vesafb_defined.yres_virtual
op_assign
id|video_height
suffix:semicolon
id|ypan
op_assign
l_int|0
suffix:semicolon
)brace
id|video_height_virtual
op_assign
id|vesafb_defined.yres_virtual
suffix:semicolon
multiline_comment|/* some dummy values for timing to make fbset happy */
id|vesafb_defined.pixclock
op_assign
l_int|10000000
op_div
id|video_width
op_star
l_int|1000
op_div
id|video_height
suffix:semicolon
id|vesafb_defined.left_margin
op_assign
(paren
id|video_width
op_div
l_int|8
)paren
op_amp
l_int|0xf8
suffix:semicolon
id|vesafb_defined.right_margin
op_assign
l_int|32
suffix:semicolon
id|vesafb_defined.upper_margin
op_assign
l_int|16
suffix:semicolon
id|vesafb_defined.lower_margin
op_assign
l_int|4
suffix:semicolon
id|vesafb_defined.hsync_len
op_assign
(paren
id|video_width
op_div
l_int|8
)paren
op_amp
l_int|0xf8
suffix:semicolon
id|vesafb_defined.vsync_len
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|video_bpp
OG
l_int|8
)paren
(brace
id|vesafb_defined.red.offset
op_assign
id|screen_info.red_pos
suffix:semicolon
id|vesafb_defined.red.length
op_assign
id|screen_info.red_size
suffix:semicolon
id|vesafb_defined.green.offset
op_assign
id|screen_info.green_pos
suffix:semicolon
id|vesafb_defined.green.length
op_assign
id|screen_info.green_size
suffix:semicolon
id|vesafb_defined.blue.offset
op_assign
id|screen_info.blue_pos
suffix:semicolon
id|vesafb_defined.blue.length
op_assign
id|screen_info.blue_size
suffix:semicolon
id|vesafb_defined.transp.offset
op_assign
id|screen_info.rsvd_pos
suffix:semicolon
id|vesafb_defined.transp.length
op_assign
id|screen_info.rsvd_size
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;vesafb: directcolor: &quot;
l_string|&quot;size=%d:%d:%d:%d, shift=%d:%d:%d:%d&bslash;n&quot;
comma
id|screen_info.rsvd_size
comma
id|screen_info.red_size
comma
id|screen_info.green_size
comma
id|screen_info.blue_size
comma
id|screen_info.rsvd_pos
comma
id|screen_info.red_pos
comma
id|screen_info.green_pos
comma
id|screen_info.blue_pos
)paren
suffix:semicolon
id|video_cmap_len
op_assign
l_int|16
suffix:semicolon
)brace
r_else
(brace
id|vesafb_defined.red.length
op_assign
l_int|6
suffix:semicolon
id|vesafb_defined.green.length
op_assign
l_int|6
suffix:semicolon
id|vesafb_defined.blue.length
op_assign
l_int|6
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|j
op_assign
id|color_table
(braket
id|i
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|red
op_assign
id|default_red
(braket
id|j
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|green
op_assign
id|default_grn
(braket
id|j
)braket
suffix:semicolon
id|palette
(braket
id|i
)braket
dot
id|blue
op_assign
id|default_blu
(braket
id|j
)braket
suffix:semicolon
)brace
id|video_cmap_len
op_assign
l_int|256
suffix:semicolon
)brace
multiline_comment|/* request failure does not faze us, as vgacon probably has this&n;&t; * region already (FIXME) */
id|request_region
c_func
(paren
l_int|0x3c0
comma
l_int|32
comma
l_string|&quot;vesafb&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mtrr
)paren
(brace
r_int
id|temp_size
op_assign
id|video_size
suffix:semicolon
r_while
c_loop
(paren
id|mtrr_add
c_func
(paren
id|video_base
comma
id|temp_size
comma
id|MTRR_TYPE_WRCOMB
comma
l_int|1
)paren
op_eq
op_minus
id|EINVAL
)paren
(brace
id|temp_size
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
id|strcpy
c_func
(paren
id|fb_info.modename
comma
l_string|&quot;VESA VGA&quot;
)paren
suffix:semicolon
id|fb_info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.fbops
op_assign
op_amp
id|vesafb_ops
suffix:semicolon
id|fb_info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.switch_con
op_assign
op_amp
id|vesafb_switch
suffix:semicolon
id|fb_info.updatevar
op_assign
op_amp
id|vesafb_update_var
suffix:semicolon
id|fb_info.blank
op_assign
op_amp
id|vesafb_blank
suffix:semicolon
id|fb_info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|vesafb_set_disp
c_func
(paren
op_minus
l_int|1
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
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.node
)paren
comma
id|fb_info.modename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
