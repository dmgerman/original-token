multiline_comment|/*&n; *  linux/drivers/video/offb.c -- Open Firmware based frame buffer device&n; *&n; *&t;Copyright (C) 1997 Geert Uytterhoeven&n; *&n; *  This driver is partly based on the PowerMac console driver:&n; *&n; *&t;Copyright (C) 1996 Paul Mackerras&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License. See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_FB_COMPAT_XPMAC
macro_line|#include &lt;asm/vc_ioctl.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;video/fbcon.h&gt;
macro_line|#include &lt;video/fbcon-cfb8.h&gt;
macro_line|#include &lt;video/macmodes.h&gt;
DECL|variable|currcon
r_static
r_int
id|currcon
op_assign
l_int|0
suffix:semicolon
DECL|struct|fb_info_offb
r_struct
id|fb_info_offb
(brace
DECL|member|info
r_struct
id|fb_info
id|info
suffix:semicolon
DECL|member|fix
r_struct
id|fb_fix_screeninfo
id|fix
suffix:semicolon
DECL|member|var
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
DECL|member|disp
r_struct
id|display
id|disp
suffix:semicolon
DECL|member|red
DECL|member|green
DECL|member|blue
DECL|member|pad
DECL|member|palette
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
DECL|member|cmap_adr
r_volatile
r_int
r_char
op_star
id|cmap_adr
suffix:semicolon
DECL|member|cmap_data
r_volatile
r_int
r_char
op_star
id|cmap_data
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __powerpc__
DECL|macro|mach_eieio
mdefine_line|#define mach_eieio()&t;eieio()
macro_line|#else
DECL|macro|mach_eieio
mdefine_line|#define mach_eieio()&t;do {} while (0)
macro_line|#endif
DECL|variable|ofonly
r_static
r_int
id|ofonly
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;     *  Interface used by the world&n;     */
r_void
id|offb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|offb_setup
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
id|offb_release
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FB_COMPAT_XPMAC
r_int
id|console_getmode
c_func
(paren
r_struct
id|vc_mode
op_star
)paren
suffix:semicolon
r_int
id|console_setmode
c_func
(paren
r_struct
id|vc_mode
op_star
comma
r_int
)paren
suffix:semicolon
r_int
id|console_setcmap
c_func
(paren
r_int
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
comma
r_int
r_char
op_star
)paren
suffix:semicolon
r_int
id|console_powermode
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|variable|console_fb_info
r_struct
id|fb_info
op_star
id|console_fb_info
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|display_info
r_struct
id|vc_mode
id|display_info
suffix:semicolon
macro_line|#endif /* CONFIG_FB_COMPAT_XPMAC */
multiline_comment|/*&n;     *  Interface to the low level console driver&n;     */
r_static
r_int
id|offbcon_switch
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
id|offbcon_updatevar
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
id|offbcon_blank
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
comma
r_struct
id|fb_info
op_star
id|info
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
DECL|function|offb_release
r_static
r_int
id|offb_release
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
id|memcpy
c_func
(paren
id|fix
comma
op_amp
id|info2-&gt;fix
comma
r_sizeof
(paren
r_struct
id|fb_fix_screeninfo
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
id|memcpy
c_func
(paren
id|var
comma
op_amp
id|info2-&gt;var
comma
r_sizeof
(paren
r_struct
id|fb_var_screeninfo
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
r_int
id|oldbpp
op_assign
l_int|0
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
id|activate
op_assign
id|var-&gt;activate
suffix:semicolon
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
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
id|info2-&gt;disp
suffix:semicolon
multiline_comment|/* used during initialization */
r_if
c_cond
(paren
id|var-&gt;xres
OG
id|info2-&gt;var.xres
op_logical_or
id|var-&gt;yres
OG
id|info2-&gt;var.yres
op_logical_or
id|var-&gt;xres_virtual
OG
id|info2-&gt;var.xres_virtual
op_logical_or
id|var-&gt;yres_virtual
OG
id|info2-&gt;var.yres_virtual
op_logical_or
id|var-&gt;bits_per_pixel
OG
id|info2-&gt;var.bits_per_pixel
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
id|info2-&gt;var
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
(paren
id|activate
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
id|offb_getcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info2-&gt;cmap_adr
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
id|kspc
comma
id|offb_setcolreg
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
macro_line|#ifdef CONFIG_FB_ATY
r_extern
r_void
id|atyfb_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_ATY */
macro_line|#ifdef CONFIG_FB_S3TRIO
r_extern
r_void
id|s3triofb_init_of
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_S3TRIO */
macro_line|#ifdef CONFIG_FB_IMSTT
r_extern
r_void
id|imsttfb_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_FB_CT65550
r_extern
r_void
id|chips_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_CT65550 */
macro_line|#ifdef CONFIG_FB_CONTROL
r_extern
r_void
id|control_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_CONTROL */
macro_line|#ifdef CONFIG_FB_VALKYRIE
r_extern
r_void
id|valkyrie_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_VALKYRIE */
macro_line|#ifdef CONFIG_FB_PLATINUM
r_extern
r_void
id|platinum_of_init
c_func
(paren
r_struct
id|device_node
op_star
id|dp
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_FB_PLATINUM */
multiline_comment|/*&n;     *  Initialisation&n;     */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|offb_init
c_func
(paren
r_void
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
op_star
id|pp
suffix:semicolon
r_int
r_int
id|dpy
comma
id|len
suffix:semicolon
r_int
op_star
id|up
comma
id|address
suffix:semicolon
r_struct
id|fb_fix_screeninfo
op_star
id|fix
suffix:semicolon
r_struct
id|fb_var_screeninfo
op_star
id|var
suffix:semicolon
r_struct
id|display
op_star
id|disp
suffix:semicolon
r_struct
id|fb_info_offb
op_star
id|info
suffix:semicolon
r_for
c_loop
(paren
id|dpy
op_assign
l_int|0
suffix:semicolon
id|dpy
OL
id|prom_num_displays
suffix:semicolon
id|dpy
op_increment
)paren
(brace
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
id|prom_display_paths
(braket
id|dpy
)braket
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ofonly
)paren
(brace
macro_line|#ifdef CONFIG_FB_ATY
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;ATY&quot;
comma
l_int|3
)paren
)paren
(brace
id|atyfb_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_ATY */
macro_line|#ifdef CONFIG_FB_S3TRIO
r_if
c_cond
(paren
id|s3triofb_init_of
c_func
(paren
id|dp
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif /* CONFIG_FB_S3TRIO */
macro_line|#ifdef CONFIG_FB_IMSTT
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;IMS,tt128mb&quot;
comma
l_int|11
)paren
)paren
(brace
id|imsttfb_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_FB_CT65550
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;chips65550&quot;
)paren
)paren
(brace
id|chips_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_CT65550 */
macro_line|#ifdef CONFIG_FB_CONTROL
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;control&quot;
)paren
)paren
(brace
id|control_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_CONTROL */
macro_line|#ifdef CONFIG_FB_VALKYRIE
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;valkyrie&quot;
)paren
)paren
(brace
id|valkyrie_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_VALKYRIE */
macro_line|#ifdef CONFIG_FB_PLATINUM
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;platinum&quot;
comma
l_int|8
)paren
)paren
(brace
id|platinum_of_init
c_func
(paren
id|dp
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_PLATINUM */
)brace
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|fb_info_offb
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|fix
op_assign
op_amp
id|info-&gt;fix
suffix:semicolon
id|var
op_assign
op_amp
id|info-&gt;var
suffix:semicolon
id|disp
op_assign
op_amp
id|info-&gt;disp
suffix:semicolon
id|strcpy
c_func
(paren
id|fix-&gt;id
comma
l_string|&quot;OFfb &quot;
)paren
suffix:semicolon
id|strncat
c_func
(paren
id|fix-&gt;id
comma
id|dp-&gt;name
comma
r_sizeof
(paren
id|fix-&gt;id
)paren
)paren
suffix:semicolon
id|fix-&gt;id
(braket
r_sizeof
(paren
id|fix-&gt;id
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
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
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_continue
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
id|var-&gt;xres
op_assign
id|var-&gt;xres_virtual
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
id|var-&gt;yres
op_assign
id|var-&gt;yres_virtual
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
id|fix-&gt;line_length
op_assign
op_star
id|pp
suffix:semicolon
r_else
id|fix-&gt;line_length
op_assign
id|var-&gt;xres_virtual
suffix:semicolon
id|fix-&gt;smem_len
op_assign
id|fix-&gt;line_length
op_star
id|var-&gt;yres
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
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_continue
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
multiline_comment|/* kludge for valkyrie */
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|dp-&gt;name
comma
l_string|&quot;valkyrie&quot;
)paren
op_eq
l_int|0
)paren
id|address
op_add_assign
l_int|0x1000
suffix:semicolon
)brace
id|fix-&gt;smem_start
op_assign
(paren
r_char
op_star
)paren
id|address
suffix:semicolon
id|fix-&gt;type
op_assign
id|FB_TYPE_PACKED_PIXELS
suffix:semicolon
id|fix-&gt;type_aux
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
id|info-&gt;cmap_adr
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
id|info-&gt;cmap_data
op_assign
id|info-&gt;cmap_adr
op_plus
l_int|1
suffix:semicolon
)brace
id|fix-&gt;visual
op_assign
id|info-&gt;cmap_adr
ques
c_cond
id|FB_VISUAL_PSEUDOCOLOR
suffix:colon
id|FB_VISUAL_STATIC_PSEUDOCOLOR
suffix:semicolon
id|var-&gt;xoffset
op_assign
id|var-&gt;yoffset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;bits_per_pixel
op_assign
l_int|8
suffix:semicolon
id|var-&gt;grayscale
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.offset
op_assign
id|var-&gt;green.offset
op_assign
id|var-&gt;blue.offset
op_assign
l_int|0
suffix:semicolon
id|var-&gt;red.length
op_assign
id|var-&gt;green.length
op_assign
id|var-&gt;blue.length
op_assign
l_int|8
suffix:semicolon
id|var-&gt;red.msb_right
op_assign
id|var-&gt;green.msb_right
op_assign
id|var-&gt;blue.msb_right
op_assign
l_int|0
suffix:semicolon
id|var-&gt;transp.offset
op_assign
id|var-&gt;transp.length
op_assign
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
id|var-&gt;width
op_assign
op_minus
l_int|1
suffix:semicolon
id|var-&gt;pixclock
op_assign
l_int|10000
suffix:semicolon
id|var-&gt;left_margin
op_assign
id|var-&gt;right_margin
op_assign
l_int|16
suffix:semicolon
id|var-&gt;upper_margin
op_assign
id|var-&gt;lower_margin
op_assign
l_int|16
suffix:semicolon
id|var-&gt;hsync_len
op_assign
id|var-&gt;vsync_len
op_assign
l_int|8
suffix:semicolon
id|var-&gt;sync
op_assign
l_int|0
suffix:semicolon
id|var-&gt;vmode
op_assign
id|FB_VMODE_NONINTERLACED
suffix:semicolon
id|disp-&gt;var
op_assign
op_star
id|var
suffix:semicolon
id|disp-&gt;cmap.start
op_assign
l_int|0
suffix:semicolon
id|disp-&gt;cmap.len
op_assign
l_int|0
suffix:semicolon
id|disp-&gt;cmap.red
op_assign
l_int|NULL
suffix:semicolon
id|disp-&gt;cmap.green
op_assign
l_int|NULL
suffix:semicolon
id|disp-&gt;cmap.blue
op_assign
l_int|NULL
suffix:semicolon
id|disp-&gt;cmap.transp
op_assign
l_int|NULL
suffix:semicolon
id|disp-&gt;screen_base
op_assign
id|ioremap
c_func
(paren
id|address
comma
id|fix-&gt;smem_len
)paren
suffix:semicolon
id|disp-&gt;visual
op_assign
id|fix-&gt;visual
suffix:semicolon
id|disp-&gt;type
op_assign
id|fix-&gt;type
suffix:semicolon
id|disp-&gt;type_aux
op_assign
id|fix-&gt;type_aux
suffix:semicolon
id|disp-&gt;ypanstep
op_assign
l_int|0
suffix:semicolon
id|disp-&gt;ywrapstep
op_assign
l_int|0
suffix:semicolon
id|disp-&gt;line_length
op_assign
id|fix-&gt;line_length
suffix:semicolon
id|disp-&gt;can_soft_blank
op_assign
id|info-&gt;cmap_adr
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|disp-&gt;inverse
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef FBCON_HAS_CFB8
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_cfb8
suffix:semicolon
macro_line|#else
id|disp-&gt;dispsw
op_assign
op_amp
id|fbcon_dummy
suffix:semicolon
macro_line|#endif
id|disp-&gt;scrollmode
op_assign
id|SCROLL_YREDRAW
suffix:semicolon
id|strcpy
c_func
(paren
id|info-&gt;info.modename
comma
l_string|&quot;OFfb &quot;
)paren
suffix:semicolon
id|strncat
c_func
(paren
id|info-&gt;info.modename
comma
id|dp-&gt;full_name
comma
r_sizeof
(paren
id|info-&gt;info.modename
)paren
)paren
suffix:semicolon
id|info-&gt;info.node
op_assign
op_minus
l_int|1
suffix:semicolon
id|info-&gt;info.fbops
op_assign
op_amp
id|offb_ops
suffix:semicolon
id|info-&gt;info.disp
op_assign
id|disp
suffix:semicolon
id|info-&gt;info.fontname
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|info-&gt;info.changevar
op_assign
l_int|NULL
suffix:semicolon
id|info-&gt;info.switch_con
op_assign
op_amp
id|offbcon_switch
suffix:semicolon
id|info-&gt;info.updatevar
op_assign
op_amp
id|offbcon_updatevar
suffix:semicolon
id|info-&gt;info.blank
op_assign
op_amp
id|offbcon_blank
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
r_int
id|j
op_assign
id|color_table
(braket
id|i
)braket
suffix:semicolon
id|info-&gt;palette
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
id|info-&gt;palette
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
id|info-&gt;palette
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
id|offb_set_var
c_func
(paren
id|var
comma
op_minus
l_int|1
comma
op_amp
id|info-&gt;info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|register_framebuffer
c_func
(paren
op_amp
id|info-&gt;info
)paren
OL
l_int|0
)paren
(brace
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;fb%d: Open Firmware frame buffer device on %s&bslash;n&quot;
comma
id|GET_FB_IDX
c_func
(paren
id|info-&gt;info.node
)paren
comma
id|dp-&gt;full_name
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FB_COMPAT_XPMAC
r_if
c_cond
(paren
op_logical_neg
id|console_fb_info
)paren
(brace
id|display_info.height
op_assign
id|var-&gt;yres
suffix:semicolon
id|display_info.width
op_assign
id|var-&gt;xres
suffix:semicolon
id|display_info.depth
op_assign
l_int|8
suffix:semicolon
id|display_info.pitch
op_assign
id|fix-&gt;line_length
suffix:semicolon
id|display_info.mode
op_assign
l_int|0
suffix:semicolon
id|strncpy
c_func
(paren
id|display_info.name
comma
id|dp-&gt;name
comma
r_sizeof
(paren
id|display_info.name
)paren
)paren
suffix:semicolon
id|display_info.fb_address
op_assign
id|address
suffix:semicolon
id|display_info.cmap_adr_address
op_assign
l_int|0
suffix:semicolon
id|display_info.cmap_data_address
op_assign
l_int|0
suffix:semicolon
id|display_info.disp_reg_address
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
id|display_info.disp_reg_address
op_assign
id|address
op_plus
l_int|0x7ffc00
suffix:semicolon
id|display_info.cmap_adr_address
op_assign
id|address
op_plus
l_int|0x7ffcc0
suffix:semicolon
id|display_info.cmap_data_address
op_assign
id|address
op_plus
l_int|0x7ffcc1
suffix:semicolon
)brace
id|console_fb_info
op_assign
op_amp
id|info-&gt;info
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_COMPAT_XPMAC) */
)brace
)brace
multiline_comment|/*&n;     *  Setup: parse used options&n;     */
DECL|function|offb_setup
r_void
id|offb_setup
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
(brace
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
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|options
comma
l_string|&quot;ofonly&quot;
)paren
)paren
id|ofonly
op_assign
l_int|1
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
id|offb_getcolreg
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
comma
r_struct
id|fb_info
op_star
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info2-&gt;cmap_adr
)paren
r_return
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
l_int|256
suffix:semicolon
id|i
op_increment
)paren
(brace
op_star
id|info2-&gt;cmap_adr
op_assign
id|i
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|3
suffix:semicolon
id|j
op_increment
)paren
(brace
op_star
id|info2-&gt;cmap_data
op_assign
l_int|0
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|do_install_cmap
c_func
(paren
id|currcon
comma
id|info
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info2-&gt;cmap_adr
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
(paren
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|red
op_lshift
l_int|8
)paren
op_or
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|red
suffix:semicolon
op_star
id|green
op_assign
(paren
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|green
op_lshift
l_int|8
)paren
op_or
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|green
suffix:semicolon
op_star
id|blue
op_assign
(paren
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|blue
op_lshift
l_int|8
)paren
op_or
id|info2-&gt;palette
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
comma
r_struct
id|fb_info
op_star
id|info
)paren
(brace
r_struct
id|fb_info_offb
op_star
id|info2
op_assign
(paren
r_struct
id|fb_info_offb
op_star
)paren
id|info
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info2-&gt;cmap_adr
op_logical_or
id|regno
OG
l_int|255
)paren
r_return
l_int|1
suffix:semicolon
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
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|red
op_assign
id|red
suffix:semicolon
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|green
op_assign
id|green
suffix:semicolon
id|info2-&gt;palette
(braket
id|regno
)braket
dot
id|blue
op_assign
id|blue
suffix:semicolon
op_star
id|info2-&gt;cmap_adr
op_assign
id|regno
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|info2-&gt;cmap_data
op_assign
id|red
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|info2-&gt;cmap_data
op_assign
id|green
suffix:semicolon
id|mach_eieio
c_func
(paren
)paren
suffix:semicolon
op_star
id|info2-&gt;cmap_data
op_assign
id|blue
suffix:semicolon
id|mach_eieio
c_func
(paren
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
l_int|1
comma
id|offb_setcolreg
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
l_int|1
comma
id|offb_setcolreg
comma
id|info
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_FB_COMPAT_XPMAC
multiline_comment|/*&n;     *  Backward compatibility mode for Xpmac&n;     */
DECL|function|console_getmode
r_int
id|console_getmode
c_func
(paren
r_struct
id|vc_mode
op_star
id|mode
)paren
(brace
op_star
id|mode
op_assign
id|display_info
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|console_setmode
r_int
id|console_setmode
c_func
(paren
r_struct
id|vc_mode
op_star
id|mode
comma
r_int
id|doit
)paren
(brace
r_struct
id|fb_var_screeninfo
id|var
suffix:semicolon
r_int
id|cmode
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|console_fb_info
)paren
r_return
op_minus
id|EOPNOTSUPP
suffix:semicolon
r_switch
c_cond
(paren
id|mode-&gt;depth
)paren
(brace
r_case
l_int|8
suffix:colon
r_case
l_int|0
suffix:colon
multiline_comment|/* default */
id|cmode
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* CMODE_8 */
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|cmode
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* CMODE_16 */
r_break
suffix:semicolon
r_case
l_int|24
suffix:colon
r_case
l_int|32
suffix:colon
id|cmode
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* CMODE_32 */
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|err
op_assign
id|mac_vmode_to_var
c_func
(paren
id|mode-&gt;mode
comma
id|cmode
comma
op_amp
id|var
)paren
)paren
)paren
r_return
id|err
suffix:semicolon
id|var.activate
op_assign
id|doit
ques
c_cond
id|FB_ACTIVATE_NOW
suffix:colon
id|FB_ACTIVATE_TEST
suffix:semicolon
id|err
op_assign
id|console_fb_info-&gt;fbops
op_member_access_from_pointer
id|fb_set_var
c_func
(paren
op_amp
id|var
comma
id|fg_console
comma
id|console_fb_info
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|variable|palette_red
r_static
id|u16
id|palette_red
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|palette_green
r_static
id|u16
id|palette_green
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|palette_blue
r_static
id|u16
id|palette_blue
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|palette_cmap
r_static
r_struct
id|fb_cmap
id|palette_cmap
op_assign
(brace
l_int|0
comma
l_int|16
comma
id|palette_red
comma
id|palette_green
comma
id|palette_blue
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|console_setcmap
r_int
id|console_setcmap
c_func
(paren
r_int
id|n_entries
comma
r_int
r_char
op_star
id|red
comma
r_int
r_char
op_star
id|green
comma
r_int
r_char
op_star
id|blue
)paren
(brace
r_int
id|i
comma
id|j
comma
id|n
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|console_fb_info
)paren
r_return
op_minus
id|EOPNOTSUPP
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
id|n_entries
suffix:semicolon
id|i
op_add_assign
id|n
)paren
(brace
id|n
op_assign
id|n_entries
op_minus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
l_int|16
)paren
id|n
op_assign
l_int|16
suffix:semicolon
id|palette_cmap.start
op_assign
id|i
suffix:semicolon
id|palette_cmap.len
op_assign
id|n
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|n
suffix:semicolon
id|j
op_increment
)paren
(brace
id|palette_cmap.red
(braket
id|j
)braket
op_assign
(paren
id|red
(braket
id|i
op_plus
id|j
)braket
op_lshift
l_int|8
)paren
op_or
id|red
(braket
id|i
op_plus
id|j
)braket
suffix:semicolon
id|palette_cmap.green
(braket
id|j
)braket
op_assign
(paren
id|green
(braket
id|i
op_plus
id|j
)braket
op_lshift
l_int|8
)paren
op_or
id|green
(braket
id|i
op_plus
id|j
)braket
suffix:semicolon
id|palette_cmap.blue
(braket
id|j
)braket
op_assign
(paren
id|blue
(braket
id|i
op_plus
id|j
)braket
op_lshift
l_int|8
)paren
op_or
id|blue
(braket
id|i
op_plus
id|j
)braket
suffix:semicolon
)brace
id|err
op_assign
id|console_fb_info-&gt;fbops
op_member_access_from_pointer
id|fb_set_cmap
c_func
(paren
op_amp
id|palette_cmap
comma
l_int|1
comma
id|fg_console
comma
id|console_fb_info
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|console_powermode
r_int
id|console_powermode
c_func
(paren
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|VC_POWERMODE_INQUIRY
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mode
template_param
id|VESA_POWERDOWN
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Not supported */
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_FB_COMPAT_XPMAC */
eof
