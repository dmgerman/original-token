multiline_comment|/*&n; * $Id: hitfb.c,v 1.1 2000/06/10 21:45:40 yaegashi Exp $&n; * linux/drivers/video/hitfb.c -- Hitachi LCD frame buffer device&n; * (C) 1999 Mihai Spatar&n; * (C) 2000 YAEGASHI Takeshi&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/nubus.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/fb.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/fbcon-cfb16.h&gt;
macro_line|#include &lt;asm/hd64461.h&gt;
DECL|macro|CONFIG_SH_LCD_VIDEOBASE
mdefine_line|#define CONFIG_SH_LCD_VIDEOBASE&t;&t;CONFIG_HD64461_IOBASE+0x2000000
multiline_comment|/* These are for HP Jornada 680/690.&n;   It is desired that they are configurable...  */
DECL|macro|CONFIG_SH_LCD_VIDEOSIZE
mdefine_line|#define CONFIG_SH_LCD_VIDEOSIZE&t;&t;1024*1024
DECL|macro|CONFIG_SH_LCD_HORZ
mdefine_line|#define CONFIG_SH_LCD_HORZ&t;&t;640
DECL|macro|CONFIG_SH_LCD_VERT
mdefine_line|#define CONFIG_SH_LCD_VERT&t;&t;240
DECL|macro|CONFIG_SH_LCD_DEFAULTBPP
mdefine_line|#define CONFIG_SH_LCD_DEFAULTBPP&t;16
DECL|struct|hitfb_info
r_struct
id|hitfb_info
(brace
DECL|member|gen
r_struct
id|fb_info_gen
id|gen
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|hitfb_par
r_struct
id|hitfb_par
(brace
DECL|member|x
DECL|member|y
r_int
id|x
comma
id|y
suffix:semicolon
DECL|member|bpp
r_int
id|bpp
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|fb_info
r_static
r_struct
id|hitfb_info
id|fb_info
suffix:semicolon
DECL|variable|current_par
r_static
r_struct
id|hitfb_par
id|current_par
suffix:semicolon
DECL|variable|current_par_valid
r_static
r_int
id|current_par_valid
op_assign
l_int|0
suffix:semicolon
DECL|variable|disp
r_static
r_struct
id|display
id|disp
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
DECL|variable|fbcon_cmap
)brace
id|fbcon_cmap
suffix:semicolon
DECL|variable|hit_videobase
DECL|variable|hit_videosize
r_int
r_int
id|hit_videobase
comma
id|hit_videosize
suffix:semicolon
DECL|variable|default_var
r_static
r_struct
id|fb_var_screeninfo
id|default_var
suffix:semicolon
r_int
id|hitfb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|hitfb_setup
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
r_static
r_void
id|hitfb_set_par
c_func
(paren
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
r_static
r_void
id|hitfb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
DECL|function|hitfb_detect
r_static
r_void
id|hitfb_detect
c_func
(paren
r_void
)paren
(brace
r_struct
id|hitfb_par
id|par
suffix:semicolon
id|hit_videobase
op_assign
id|CONFIG_SH_LCD_VIDEOBASE
suffix:semicolon
id|hit_videosize
op_assign
id|CONFIG_SH_LCD_VIDEOSIZE
suffix:semicolon
id|par.x
op_assign
id|CONFIG_SH_LCD_HORZ
suffix:semicolon
id|par.y
op_assign
id|CONFIG_SH_LCD_VERT
suffix:semicolon
id|par.bpp
op_assign
id|CONFIG_SH_LCD_DEFAULTBPP
suffix:semicolon
id|hitfb_set_par
c_func
(paren
op_amp
id|par
comma
l_int|NULL
)paren
suffix:semicolon
id|hitfb_encode_var
c_func
(paren
op_amp
id|default_var
comma
op_amp
id|par
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|hitfb_encode_fix
r_static
r_int
id|hitfb_encode_fix
c_func
(paren
r_struct
id|fb_fix_screeninfo
op_star
id|fix
comma
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
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
l_string|&quot;Hitachi HD64461&quot;
)paren
suffix:semicolon
id|fix-&gt;smem_start
op_assign
id|hit_videobase
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|hit_videosize
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;visual
op_assign
id|FB_VISUAL_TRUECOLOR
suffix:semicolon
id|fix-&gt;xpanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|fix-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|par-&gt;bpp
)paren
(brace
r_default
suffix:colon
r_case
l_int|8
suffix:colon
id|fix-&gt;line_length
op_assign
id|par-&gt;x
suffix:semicolon
r_case
l_int|16
suffix:colon
id|fix-&gt;line_length
op_assign
id|par-&gt;x
op_star
l_int|2
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_decode_var
r_static
r_int
id|hitfb_decode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|par-&gt;x
op_assign
id|var-&gt;xres
suffix:semicolon
id|par-&gt;y
op_assign
id|var-&gt;yres
suffix:semicolon
id|par-&gt;bpp
op_assign
id|var-&gt;bits_per_pixel
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_encode_var
r_static
r_void
id|hitfb_encode_var
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|memset
c_func
(paren
id|var
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|var
)paren
)paren
suffix:semicolon
id|var-&gt;xres
op_assign
id|par-&gt;x
suffix:semicolon
id|var-&gt;yres
op_assign
id|par-&gt;y
suffix:semicolon
id|var-&gt;xres_virtual
op_assign
id|var-&gt;xres
suffix:semicolon
id|var-&gt;yres_virtual
op_assign
id|var-&gt;yres
suffix:semicolon
id|var-&gt;xoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
id|par-&gt;bpp
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;nonstd
op_assign
l_int|0
suffix:semicolon
id|var-&gt;activate
op_assign
l_int|0
suffix:semicolon
id|var-&gt;height
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|0
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;left_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;right_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;upper_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;lower_margin
op_assign
l_int|0
suffix:semicolon
id|var-&gt;hsync_len
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vsync_len
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|var-&gt;bits_per_pixel
)paren
(brace
r_case
l_int|8
suffix:colon
id|var-&gt;red.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
multiline_comment|/* RGB 565 */
id|var-&gt;red.offset
op_assign
l_int|11
suffix:semicolon
id|var-&gt;red.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.offset
op_assign
l_int|5
suffix:semicolon
id|var-&gt;green.length
op_assign
l_int|6
suffix:semicolon
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.length
op_assign
l_int|5
suffix:semicolon
id|var-&gt;transp.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.length
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|var-&gt;red.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;green.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.msb_right
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_get_par
r_static
r_void
id|hitfb_get_par
c_func
(paren
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
op_star
id|par
op_assign
id|current_par
suffix:semicolon
)brace
DECL|function|hitfb_set_par
r_static
r_void
id|hitfb_set_par
c_func
(paren
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
multiline_comment|/* Set the hardware according to &squot;par&squot;. */
id|current_par
op_assign
op_star
id|par
suffix:semicolon
id|current_par_valid
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|hitfb_getcolreg
r_static
r_int
id|hitfb_getcolreg
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
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
id|outw
c_func
(paren
id|regno
op_lshift
l_int|8
comma
id|HD64461_CPTRAR
)paren
suffix:semicolon
op_star
id|red
op_assign
id|inw
c_func
(paren
id|HD64461_CPTRDR
)paren
op_lshift
l_int|10
suffix:semicolon
op_star
id|green
op_assign
id|inw
c_func
(paren
id|HD64461_CPTRDR
)paren
op_lshift
l_int|10
suffix:semicolon
op_star
id|blue
op_assign
id|inw
c_func
(paren
id|HD64461_CPTRDR
)paren
op_lshift
l_int|10
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
DECL|function|hitfb_setcolreg
r_static
r_int
id|hitfb_setcolreg
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
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
id|outw
c_func
(paren
id|regno
op_lshift
l_int|8
comma
id|HD64461_CPTWAR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|red
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|green
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
id|outw
c_func
(paren
id|blue
op_rshift
l_int|10
comma
id|HD64461_CPTWDR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regno
OL
l_int|16
)paren
(brace
r_switch
c_cond
(paren
id|current_par.bpp
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|16
suffix:colon
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
r_break
suffix:semicolon
macro_line|#endif
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_pan_display
r_static
r_int
id|hitfb_pan_display
c_func
(paren
r_struct
id|fb_var_screeninfo
op_star
id|var
comma
r_struct
id|hitfb_par
op_star
id|par
comma
r_const
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
DECL|function|hitfb_blank
r_static
r_int
id|hitfb_blank
c_func
(paren
r_int
id|blank_mode
comma
r_const
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_set_disp
r_static
r_void
id|hitfb_set_disp
c_func
(paren
r_const
r_void
op_star
id|par
comma
r_struct
id|display
op_star
id|disp
comma
r_struct
id|fb_info_gen
op_star
id|info
)paren
(brace
id|disp-&gt;screen_base
op_assign
(paren
r_void
op_star
)paren
id|hit_videobase
suffix:semicolon
r_switch
c_cond
(paren
(paren
(paren
r_struct
id|hitfb_par
op_star
)paren
id|par
)paren
op_member_access_from_pointer
id|bpp
)paren
(brace
macro_line|#ifdef FBCON_HAS_CFB8
r_case
l_int|8
suffix:colon
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef FBCON_HAS_CFB16
r_case
l_int|16
suffix:colon
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb16
suffix:semicolon
id|disp-&gt;dispsw_data
op_assign
id|fbcon_cmap.cfb16
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
)brace
)brace
DECL|variable|hitfb_switch
r_struct
id|fbgen_hwswitch
id|hitfb_switch
op_assign
(brace
id|hitfb_detect
comma
id|hitfb_encode_fix
comma
id|hitfb_decode_var
comma
id|hitfb_encode_var
comma
id|hitfb_get_par
comma
id|hitfb_set_par
comma
id|hitfb_getcolreg
comma
id|hitfb_setcolreg
comma
id|hitfb_pan_display
comma
id|hitfb_blank
comma
id|hitfb_set_disp
)brace
suffix:semicolon
DECL|variable|hitfb_ops
r_static
r_struct
id|fb_ops
id|hitfb_ops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|fb_get_fix
suffix:colon
id|fbgen_get_fix
comma
id|fb_get_var
suffix:colon
id|fbgen_get_var
comma
id|fb_set_var
suffix:colon
id|fbgen_set_var
comma
id|fb_get_cmap
suffix:colon
id|fbgen_get_cmap
comma
id|fb_set_cmap
suffix:colon
id|fbgen_set_cmap
comma
id|fb_pan_display
suffix:colon
id|fbgen_pan_display
comma
id|fb_ioctl
suffix:colon
id|fbgen_ioctl
comma
)brace
suffix:semicolon
DECL|function|hitfb_init
r_int
id|__init
id|hitfb_init
c_func
(paren
r_void
)paren
(brace
id|strcpy
c_func
(paren
id|fb_info.gen.info.modename
comma
l_string|&quot;Hitachi HD64461&quot;
)paren
suffix:semicolon
id|fb_info.gen.info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|fb_info.gen.info.flags
op_assign
id|FBINFO_FLAG_DEFAULT
suffix:semicolon
id|fb_info.gen.info.fbops
op_assign
op_amp
id|hitfb_ops
suffix:semicolon
id|fb_info.gen.info.disp
op_assign
op_amp
id|disp
suffix:semicolon
id|fb_info.gen.info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|fb_info.gen.info.switch_con
op_assign
op_amp
id|fbgen_switch
suffix:semicolon
id|fb_info.gen.info.updatevar
op_assign
op_amp
id|fbgen_update_var
suffix:semicolon
id|fb_info.gen.info.blank
op_assign
op_amp
id|fbgen_blank
suffix:semicolon
id|fb_info.gen.parsize
op_assign
r_sizeof
(paren
r_struct
id|hitfb_par
)paren
suffix:semicolon
id|fb_info.gen.fbhw
op_assign
op_amp
id|hitfb_switch
suffix:semicolon
id|fb_info.gen.fbhw
op_member_access_from_pointer
id|detect
c_func
(paren
)paren
suffix:semicolon
id|fbgen_get_var
c_func
(paren
op_amp
id|disp.var
comma
op_minus
l_int|1
comma
op_amp
id|fb_info.gen.info
)paren
suffix:semicolon
id|disp.var.activate
op_assign
id|FB_ACTIVATE_NOW
suffix:semicolon
id|fbgen_do_set_var
c_func
(paren
op_amp
id|disp.var
comma
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|fbgen_set_disp
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
id|fbgen_install_cmap
c_func
(paren
l_int|0
comma
op_amp
id|fb_info.gen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|fb_info.gen.info
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;fb%d: %s frame buffer device&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|fb_info.gen.info.node
)paren
comma
id|fb_info.gen.info.modename
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hitfb_cleanup
r_void
id|hitfb_cleanup
c_func
(paren
r_struct
id|fb_info
op_star
id|info
)paren
(brace
id|unregister_framebuffer
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
DECL|function|hitfb_setup
r_int
id|__init
id|hitfb_setup
c_func
(paren
r_char
op_star
id|options
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|hitfb_init
c_func
(paren
)paren
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
id|hitfb_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
