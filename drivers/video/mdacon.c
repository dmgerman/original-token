multiline_comment|/*&n; *  linux/drivers/video/mdacon.c -- Low level MDA based console driver&n; *&n; *&t;(c) 1998 Andrew Apted &lt;ajapted@netspace.net.au&gt;&n; *&n; *      including portions (c) 1995-1998 Patrick Caulfield.&n; *&n; *  This file is based on the VGA console driver (vgacon.c):&n; *&t;&n; *&t;Created 28 Sep 1997 by Geert Uytterhoeven&n; *&n; *&t;Rewritten by Martin Mares &lt;mj@ucw.cz&gt;, July 1998&n; *&n; *  and on the old console.c, vga.c and vesa_blank.c drivers:&n; *&n; *&t;Copyright (C) 1991, 1992  Linus Torvalds&n; *&t;&t;&t;    1995  Jay Estabrook&n; *&n; *  This file is subject to the terms and conditions of the GNU General Public&n; *  License.  See the file COPYING in the main directory of this archive for&n; *  more details.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/vt_buffer.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/vga.h&gt;
multiline_comment|/* description of the hardware layout */
DECL|variable|mda_vram_base
r_static
r_int
r_int
id|mda_vram_base
suffix:semicolon
multiline_comment|/* Base of video memory */
DECL|variable|mda_vram_len
r_static
r_int
r_int
id|mda_vram_len
suffix:semicolon
multiline_comment|/* Size of video memory */
DECL|variable|mda_num_columns
r_static
r_int
r_int
id|mda_num_columns
suffix:semicolon
multiline_comment|/* Number of text columns */
DECL|variable|mda_num_lines
r_static
r_int
r_int
id|mda_num_lines
suffix:semicolon
multiline_comment|/* Number of text lines */
DECL|variable|mda_index_port
r_static
r_int
r_int
id|mda_index_port
suffix:semicolon
multiline_comment|/* Register select port */
DECL|variable|mda_value_port
r_static
r_int
r_int
id|mda_value_port
suffix:semicolon
multiline_comment|/* Register value port */
DECL|variable|mda_mode_port
r_static
r_int
r_int
id|mda_mode_port
suffix:semicolon
multiline_comment|/* Mode control port */
DECL|variable|mda_status_port
r_static
r_int
r_int
id|mda_status_port
suffix:semicolon
multiline_comment|/* Status and Config port */
DECL|variable|mda_gfx_port
r_static
r_int
r_int
id|mda_gfx_port
suffix:semicolon
multiline_comment|/* Graphics control port */
multiline_comment|/* current hardware state */
DECL|variable|mda_origin_loc
r_static
r_int
id|mda_origin_loc
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mda_cursor_loc
r_static
r_int
id|mda_cursor_loc
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mda_cursor_size_from
r_static
r_int
id|mda_cursor_size_from
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|mda_cursor_size_to
r_static
r_int
id|mda_cursor_size_to
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|enumerator|TYPE_MDA
DECL|enumerator|TYPE_HERC
DECL|enumerator|TYPE_HERCPLUS
DECL|enumerator|TYPE_HERCCOLOR
DECL|variable|mda_type
r_static
r_enum
(brace
id|TYPE_MDA
comma
id|TYPE_HERC
comma
id|TYPE_HERCPLUS
comma
id|TYPE_HERCCOLOR
)brace
id|mda_type
suffix:semicolon
DECL|variable|mda_type_name
r_static
r_char
op_star
id|mda_type_name
suffix:semicolon
multiline_comment|/* console information */
DECL|variable|mda_first_vc
r_static
r_int
id|mda_first_vc
op_assign
l_int|13
suffix:semicolon
DECL|variable|mda_last_vc
r_static
r_int
id|mda_last_vc
op_assign
l_int|16
suffix:semicolon
DECL|variable|mda_display_fg
r_static
r_struct
id|vc_data
op_star
id|mda_display_fg
op_assign
l_int|NULL
suffix:semicolon
macro_line|#ifdef MODULE_PARM
id|MODULE_PARM
c_func
(paren
id|mda_first_vc
comma
l_string|&quot;1-255i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mda_last_vc
comma
l_string|&quot;1-255i&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* MDA register values&n; */
DECL|macro|MDA_CURSOR_BLINKING
mdefine_line|#define MDA_CURSOR_BLINKING&t;0x00
DECL|macro|MDA_CURSOR_OFF
mdefine_line|#define MDA_CURSOR_OFF&t;&t;0x20
DECL|macro|MDA_CURSOR_SLOWBLINK
mdefine_line|#define MDA_CURSOR_SLOWBLINK&t;0x60
DECL|macro|MDA_MODE_GRAPHICS
mdefine_line|#define MDA_MODE_GRAPHICS&t;0x02
DECL|macro|MDA_MODE_VIDEO_EN
mdefine_line|#define MDA_MODE_VIDEO_EN&t;0x08
DECL|macro|MDA_MODE_BLINK_EN
mdefine_line|#define MDA_MODE_BLINK_EN&t;0x20
DECL|macro|MDA_MODE_GFX_PAGE1
mdefine_line|#define MDA_MODE_GFX_PAGE1&t;0x80
DECL|macro|MDA_STATUS_HSYNC
mdefine_line|#define MDA_STATUS_HSYNC&t;0x01
DECL|macro|MDA_STATUS_VSYNC
mdefine_line|#define MDA_STATUS_VSYNC&t;0x80
DECL|macro|MDA_STATUS_VIDEO
mdefine_line|#define MDA_STATUS_VIDEO&t;0x08
DECL|macro|MDA_CONFIG_COL132
mdefine_line|#define MDA_CONFIG_COL132&t;0x08
DECL|macro|MDA_GFX_MODE_EN
mdefine_line|#define MDA_GFX_MODE_EN&t;&t;0x01
DECL|macro|MDA_GFX_PAGE_EN
mdefine_line|#define MDA_GFX_PAGE_EN&t;&t;0x02
multiline_comment|/*&n; * MDA could easily be classified as &quot;pre-dinosaur hardware&quot;.&n; */
DECL|function|write_mda_b
r_static
r_void
id|write_mda_b
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_char
id|reg
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
id|reg
comma
id|mda_index_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
comma
id|mda_value_port
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|write_mda_w
r_static
r_void
id|write_mda_w
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_char
id|reg
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
id|reg
comma
id|mda_index_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|mda_value_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg
op_plus
l_int|1
comma
id|mda_index_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xff
comma
id|mda_value_port
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|test_mda_b
r_static
r_int
id|test_mda_b
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_char
id|reg
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
id|reg
comma
id|mda_index_port
)paren
suffix:semicolon
id|outb
(paren
id|val
comma
id|mda_value_port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|val
op_assign
(paren
id|inb_p
c_func
(paren
id|mda_value_port
)paren
op_eq
id|val
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|mda_set_origin
r_static
r_inline
r_void
id|mda_set_origin
c_func
(paren
r_int
r_int
id|location
)paren
(brace
r_if
c_cond
(paren
id|mda_origin_loc
op_eq
id|location
)paren
r_return
suffix:semicolon
id|write_mda_w
c_func
(paren
id|location
op_rshift
l_int|1
comma
l_int|0x0c
)paren
suffix:semicolon
id|mda_origin_loc
op_assign
id|location
suffix:semicolon
)brace
DECL|function|mda_set_cursor
r_static
r_inline
r_void
id|mda_set_cursor
c_func
(paren
r_int
r_int
id|location
)paren
(brace
r_if
c_cond
(paren
id|mda_cursor_loc
op_eq
id|location
)paren
r_return
suffix:semicolon
id|write_mda_w
c_func
(paren
id|location
op_rshift
l_int|1
comma
l_int|0x0e
)paren
suffix:semicolon
id|mda_cursor_loc
op_assign
id|location
suffix:semicolon
)brace
DECL|function|mda_set_cursor_size
r_static
r_inline
r_void
id|mda_set_cursor_size
c_func
(paren
r_int
id|from
comma
r_int
id|to
)paren
(brace
r_if
c_cond
(paren
id|mda_cursor_size_from
op_eq
id|from
op_logical_and
id|mda_cursor_size_to
op_eq
id|to
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|from
OG
id|to
)paren
(brace
id|write_mda_b
c_func
(paren
id|MDA_CURSOR_OFF
comma
l_int|0x0a
)paren
suffix:semicolon
multiline_comment|/* disable cursor */
)brace
r_else
(brace
id|write_mda_b
c_func
(paren
id|from
comma
l_int|0x0a
)paren
suffix:semicolon
multiline_comment|/* cursor start */
id|write_mda_b
c_func
(paren
id|to
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* cursor end */
)brace
id|mda_cursor_size_from
op_assign
id|from
suffix:semicolon
id|mda_cursor_size_to
op_assign
id|to
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|mdacon_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
)paren
(brace
multiline_comment|/* command line format: mdacon=&lt;first&gt;,&lt;last&gt; */
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OL
l_int|2
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|1
)braket
template_param
id|MAX_NR_CONSOLES
op_logical_or
id|ints
(braket
l_int|2
)braket
template_param
id|MAX_NR_CONSOLES
)paren
r_return
suffix:semicolon
id|mda_first_vc
op_assign
id|ints
(braket
l_int|1
)braket
op_minus
l_int|1
suffix:semicolon
id|mda_last_vc
op_assign
id|ints
(braket
l_int|2
)braket
op_minus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef MODULE
DECL|function|mda_detect
r_static
r_int
id|mda_detect
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_static
r_int
id|mda_detect
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
r_int
id|count
op_assign
l_int|0
suffix:semicolon
id|u16
op_star
id|p
comma
id|p_save
suffix:semicolon
id|u16
op_star
id|q
comma
id|q_save
suffix:semicolon
multiline_comment|/* do a memory check */
id|p
op_assign
(paren
id|u16
op_star
)paren
id|mda_vram_base
suffix:semicolon
id|q
op_assign
(paren
id|u16
op_star
)paren
(paren
id|mda_vram_base
op_plus
l_int|0x01000
)paren
suffix:semicolon
id|p_save
op_assign
id|scr_readw
c_func
(paren
id|p
)paren
suffix:semicolon
id|q_save
op_assign
id|scr_readw
c_func
(paren
id|q
)paren
suffix:semicolon
id|scr_writew
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
id|scr_readw
c_func
(paren
id|p
)paren
op_eq
l_int|0xAA55
)paren
id|count
op_increment
suffix:semicolon
id|scr_writew
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
id|scr_readw
c_func
(paren
id|p
)paren
op_eq
l_int|0x55AA
)paren
id|count
op_increment
suffix:semicolon
id|scr_writew
c_func
(paren
id|p_save
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ne
l_int|2
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* check if we have 4K or 8K */
id|scr_writew
c_func
(paren
l_int|0xA55A
comma
id|q
)paren
suffix:semicolon
id|scr_writew
c_func
(paren
l_int|0x0000
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scr_readw
c_func
(paren
id|q
)paren
op_eq
l_int|0xA55A
)paren
id|count
op_increment
suffix:semicolon
id|scr_writew
c_func
(paren
l_int|0x5AA5
comma
id|q
)paren
suffix:semicolon
id|scr_writew
c_func
(paren
l_int|0x0000
comma
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scr_readw
c_func
(paren
id|q
)paren
op_eq
l_int|0x5AA5
)paren
id|count
op_increment
suffix:semicolon
id|scr_writew
c_func
(paren
id|p_save
comma
id|p
)paren
suffix:semicolon
id|scr_writew
c_func
(paren
id|q_save
comma
id|q
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_eq
l_int|4
)paren
(brace
id|mda_vram_len
op_assign
l_int|0x02000
suffix:semicolon
)brace
multiline_comment|/* Ok, there is definitely a card registering at the correct&n;&t; * memory location, so now we do an I/O port test.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|test_mda_b
c_func
(paren
l_int|0x66
comma
l_int|0x0f
)paren
)paren
(brace
multiline_comment|/* cursor low register */
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|test_mda_b
c_func
(paren
l_int|0x99
comma
l_int|0x0f
)paren
)paren
(brace
multiline_comment|/* cursor low register */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* See if the card is a Hercules, by checking whether the vsync&n;&t; * bit of the status register is changing.  This test lasts for&n;&t; * approximately 1/10th of a second.&n;&t; */
id|p_save
op_assign
id|q_save
op_assign
id|inb_p
c_func
(paren
id|mda_status_port
)paren
op_amp
id|MDA_STATUS_VSYNC
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
l_int|50000
op_logical_and
id|p_save
op_eq
id|q_save
suffix:semicolon
id|count
op_increment
)paren
(brace
id|q_save
op_assign
id|inb
c_func
(paren
id|mda_status_port
)paren
op_amp
id|MDA_STATUS_VSYNC
suffix:semicolon
id|udelay
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p_save
op_ne
id|q_save
)paren
(brace
r_switch
c_cond
(paren
id|inb_p
c_func
(paren
id|mda_status_port
)paren
op_amp
l_int|0x70
)paren
(brace
r_case
l_int|0x10
suffix:colon
id|mda_type
op_assign
id|TYPE_HERCPLUS
suffix:semicolon
id|mda_type_name
op_assign
l_string|&quot;HerculesPlus&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x50
suffix:colon
id|mda_type
op_assign
id|TYPE_HERCCOLOR
suffix:semicolon
id|mda_type_name
op_assign
l_string|&quot;HerculesColor&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mda_type
op_assign
id|TYPE_HERC
suffix:semicolon
id|mda_type_name
op_assign
l_string|&quot;Hercules&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|mda_initialize
r_static
r_void
id|mda_initialize
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_static
r_void
id|mda_initialize
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
id|write_mda_b
c_func
(paren
l_int|97
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* horizontal total */
id|write_mda_b
c_func
(paren
l_int|80
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* horizontal displayed */
id|write_mda_b
c_func
(paren
l_int|82
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* horizontal sync pos */
id|write_mda_b
c_func
(paren
l_int|15
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* horizontal sync width */
id|write_mda_b
c_func
(paren
l_int|25
comma
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/* vertical total */
id|write_mda_b
c_func
(paren
l_int|6
comma
l_int|0x05
)paren
suffix:semicolon
multiline_comment|/* vertical total adjust */
id|write_mda_b
c_func
(paren
l_int|25
comma
l_int|0x06
)paren
suffix:semicolon
multiline_comment|/* vertical displayed */
id|write_mda_b
c_func
(paren
l_int|25
comma
l_int|0x07
)paren
suffix:semicolon
multiline_comment|/* vertical sync pos */
id|write_mda_b
c_func
(paren
l_int|2
comma
l_int|0x08
)paren
suffix:semicolon
multiline_comment|/* interlace mode */
id|write_mda_b
c_func
(paren
l_int|13
comma
l_int|0x09
)paren
suffix:semicolon
multiline_comment|/* maximum scanline */
id|write_mda_b
c_func
(paren
l_int|12
comma
l_int|0x0a
)paren
suffix:semicolon
multiline_comment|/* cursor start */
id|write_mda_b
c_func
(paren
l_int|13
comma
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* cursor end */
id|write_mda_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/* start address */
id|write_mda_w
c_func
(paren
l_int|0x0000
comma
l_int|0x0e
)paren
suffix:semicolon
multiline_comment|/* cursor location */
id|outb_p
c_func
(paren
id|MDA_MODE_VIDEO_EN
op_or
id|MDA_MODE_BLINK_EN
comma
id|mda_mode_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|mda_status_port
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|mda_gfx_port
)paren
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|mdacon_startup
r_static
r_const
r_char
op_star
id|mdacon_startup
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_static
r_const
r_char
op_star
id|mdacon_startup
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
id|mda_num_columns
op_assign
l_int|80
suffix:semicolon
id|mda_num_lines
op_assign
l_int|25
suffix:semicolon
id|mda_vram_base
op_assign
id|VGA_MAP_MEM
c_func
(paren
l_int|0xb0000
)paren
suffix:semicolon
id|mda_vram_len
op_assign
l_int|0x01000
suffix:semicolon
id|mda_index_port
op_assign
l_int|0x3b4
suffix:semicolon
id|mda_value_port
op_assign
l_int|0x3b5
suffix:semicolon
id|mda_mode_port
op_assign
l_int|0x3b8
suffix:semicolon
id|mda_status_port
op_assign
l_int|0x3ba
suffix:semicolon
id|mda_gfx_port
op_assign
l_int|0x3bf
suffix:semicolon
id|mda_type
op_assign
id|TYPE_MDA
suffix:semicolon
id|mda_type_name
op_assign
l_string|&quot;MDA&quot;
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mda_detect
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;mdacon: MDA card not detected.&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mda_type
op_ne
id|TYPE_MDA
)paren
(brace
id|mda_initialize
c_func
(paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;mdacon: %s with %ldK of memory detected.&bslash;n&quot;
comma
id|mda_type_name
comma
id|mda_vram_len
op_div
l_int|1024
)paren
suffix:semicolon
r_return
l_string|&quot;MDA-2&quot;
suffix:semicolon
)brace
DECL|function|mdacon_init
r_static
r_void
id|mdacon_init
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|init
)paren
(brace
id|c-&gt;vc_complement_mask
op_assign
l_int|0x0800
suffix:semicolon
multiline_comment|/* reverse video */
id|c-&gt;vc_display_fg
op_assign
op_amp
id|mda_display_fg
suffix:semicolon
r_if
c_cond
(paren
id|init
)paren
(brace
id|c-&gt;vc_cols
op_assign
id|mda_num_columns
suffix:semicolon
id|c-&gt;vc_rows
op_assign
id|mda_num_lines
suffix:semicolon
)brace
r_else
(brace
id|vc_resize_con
c_func
(paren
id|mda_num_lines
comma
id|mda_num_columns
comma
id|c-&gt;vc_num
)paren
suffix:semicolon
)brace
multiline_comment|/* make the first MDA console visible */
r_if
c_cond
(paren
id|mda_display_fg
op_eq
l_int|NULL
)paren
id|mda_display_fg
op_assign
id|c
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|mdacon_deinit
r_static
r_void
id|mdacon_deinit
c_func
(paren
r_struct
id|vc_data
op_star
id|c
)paren
(brace
multiline_comment|/* con_set_default_unimap(c-&gt;vc_num); */
r_if
c_cond
(paren
id|mda_display_fg
op_eq
id|c
)paren
id|mda_display_fg
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|function|mda_convert_attr
r_static
r_inline
id|u16
id|mda_convert_attr
c_func
(paren
id|u16
id|ch
)paren
(brace
id|u16
id|attr
op_assign
l_int|0x0700
suffix:semicolon
multiline_comment|/* Underline and reverse-video are mutually exclusive on MDA.&n;&t; * Since reverse-video is used for cursors and selected areas,&n;&t; * it takes precedence. &n;&t; */
r_if
c_cond
(paren
id|ch
op_amp
l_int|0x0800
)paren
id|attr
op_assign
l_int|0x7000
suffix:semicolon
multiline_comment|/* reverse */
r_else
r_if
c_cond
(paren
id|ch
op_amp
l_int|0x0400
)paren
id|attr
op_assign
l_int|0x0100
suffix:semicolon
multiline_comment|/* underline */
r_return
(paren
(paren
id|ch
op_amp
l_int|0x0200
)paren
op_lshift
l_int|2
)paren
op_or
multiline_comment|/* intensity */
(paren
id|ch
op_amp
l_int|0x8000
)paren
op_or
multiline_comment|/* blink */
(paren
id|ch
op_amp
l_int|0x00ff
)paren
op_or
id|attr
suffix:semicolon
)brace
DECL|function|mdacon_build_attr
r_static
id|u8
id|mdacon_build_attr
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
id|u8
id|color
comma
id|u8
id|intensity
comma
id|u8
id|blink
comma
id|u8
id|underline
comma
id|u8
id|reverse
)paren
(brace
multiline_comment|/* The attribute is just a bit vector:&n;&t; *&n;&t; *&t;Bit 0..1 : intensity (0..2)&n;&t; *&t;Bit 2    : underline&n;&t; *&t;Bit 3    : reverse&n;&t; *&t;Bit 7    : blink&n;&t; */
r_return
(paren
id|intensity
op_amp
l_int|3
)paren
op_or
(paren
(paren
id|underline
op_amp
l_int|1
)paren
op_lshift
l_int|2
)paren
op_or
(paren
(paren
id|reverse
op_amp
l_int|1
)paren
op_lshift
l_int|3
)paren
op_or
(paren
(paren
id|blink
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
)brace
DECL|function|mdacon_invert_region
r_static
r_void
id|mdacon_invert_region
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
id|u16
op_star
id|p
comma
r_int
id|count
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
)paren
(brace
id|scr_writew
c_func
(paren
id|scr_readw
c_func
(paren
id|p
)paren
op_xor
l_int|0x0800
comma
id|p
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|macro|MDA_ADDR
mdefine_line|#define MDA_ADDR(x,y)  ((u16 *) mda_vram_base + (y)*mda_num_columns + (x))
DECL|function|mdacon_putc
r_static
r_void
id|mdacon_putc
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|ch
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
id|scr_writew
c_func
(paren
id|mda_convert_attr
c_func
(paren
id|ch
)paren
comma
id|MDA_ADDR
c_func
(paren
id|x
comma
id|y
)paren
)paren
suffix:semicolon
)brace
DECL|function|mdacon_putcs
r_static
r_void
id|mdacon_putcs
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_const
r_int
r_int
op_star
id|s
comma
r_int
id|count
comma
r_int
id|y
comma
r_int
id|x
)paren
(brace
id|u16
op_star
id|dest
op_assign
id|MDA_ADDR
c_func
(paren
id|x
comma
id|y
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
)paren
(brace
id|scr_writew
c_func
(paren
id|mda_convert_attr
c_func
(paren
op_star
id|s
op_increment
)paren
comma
id|dest
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|mdacon_clear
r_static
r_void
id|mdacon_clear
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|y
comma
r_int
id|x
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
id|u16
op_star
id|dest
op_assign
id|MDA_ADDR
c_func
(paren
id|x
comma
id|y
)paren
suffix:semicolon
id|u16
id|eattr
op_assign
id|mda_convert_attr
c_func
(paren
id|c-&gt;vc_video_erase_char
)paren
suffix:semicolon
r_if
c_cond
(paren
id|width
op_le
l_int|0
op_logical_or
id|height
op_le
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|x
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|mda_num_columns
)paren
(brace
id|scr_memsetw
c_func
(paren
id|dest
comma
id|eattr
comma
id|height
op_star
id|width
op_star
l_int|2
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
suffix:semicolon
id|height
OG
l_int|0
suffix:semicolon
id|height
op_decrement
comma
id|dest
op_add_assign
id|mda_num_columns
)paren
id|scr_memsetw
c_func
(paren
id|dest
comma
id|eattr
comma
id|width
op_star
l_int|2
)paren
suffix:semicolon
)brace
)brace
DECL|function|mdacon_bmove
r_static
r_void
id|mdacon_bmove
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|sy
comma
r_int
id|sx
comma
r_int
id|dy
comma
r_int
id|dx
comma
r_int
id|height
comma
r_int
id|width
)paren
(brace
id|u16
op_star
id|src
comma
op_star
id|dest
suffix:semicolon
r_if
c_cond
(paren
id|width
op_le
l_int|0
op_logical_or
id|height
op_le
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|sx
op_eq
l_int|0
op_logical_and
id|dx
op_eq
l_int|0
op_logical_and
id|width
op_eq
id|mda_num_columns
)paren
(brace
id|scr_memmovew
c_func
(paren
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|dy
)paren
comma
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|sy
)paren
comma
id|height
op_star
id|width
op_star
l_int|2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dy
OL
id|sy
op_logical_or
(paren
id|dy
op_eq
id|sy
op_logical_and
id|dx
OL
id|sx
)paren
)paren
(brace
id|src
op_assign
id|MDA_ADDR
c_func
(paren
id|sx
comma
id|sy
)paren
suffix:semicolon
id|dest
op_assign
id|MDA_ADDR
c_func
(paren
id|dx
comma
id|dy
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|height
OG
l_int|0
suffix:semicolon
id|height
op_decrement
)paren
(brace
id|scr_memmovew
c_func
(paren
id|dest
comma
id|src
comma
id|width
op_star
l_int|2
)paren
suffix:semicolon
id|src
op_add_assign
id|mda_num_columns
suffix:semicolon
id|dest
op_add_assign
id|mda_num_columns
suffix:semicolon
)brace
)brace
r_else
(brace
id|src
op_assign
id|MDA_ADDR
c_func
(paren
id|sx
comma
id|sy
op_plus
id|height
op_minus
l_int|1
)paren
suffix:semicolon
id|dest
op_assign
id|MDA_ADDR
c_func
(paren
id|dx
comma
id|dy
op_plus
id|height
op_minus
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|height
OG
l_int|0
suffix:semicolon
id|height
op_decrement
)paren
(brace
id|scr_memmovew
c_func
(paren
id|dest
comma
id|src
comma
id|width
op_star
l_int|2
)paren
suffix:semicolon
id|src
op_sub_assign
id|mda_num_columns
suffix:semicolon
id|dest
op_sub_assign
id|mda_num_columns
suffix:semicolon
)brace
)brace
)brace
DECL|function|mdacon_switch
r_static
r_int
id|mdacon_switch
c_func
(paren
r_struct
id|vc_data
op_star
id|c
)paren
(brace
r_return
l_int|1
suffix:semicolon
multiline_comment|/* redrawing needed */
)brace
DECL|function|mdacon_set_palette
r_static
r_int
id|mdacon_set_palette
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
r_char
op_star
id|table
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|mdacon_blank
r_static
r_int
id|mdacon_blank
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|blank
)paren
(brace
r_if
c_cond
(paren
id|blank
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x00
comma
id|mda_mode_port
)paren
suffix:semicolon
multiline_comment|/* disable video */
)brace
r_else
(brace
id|outb_p
c_func
(paren
id|MDA_MODE_VIDEO_EN
op_or
id|MDA_MODE_BLINK_EN
comma
id|mda_mode_port
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mdacon_font_op
r_static
r_int
id|mdacon_font_op
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_struct
id|console_font_op
op_star
id|op
)paren
(brace
r_return
op_minus
id|ENOSYS
suffix:semicolon
)brace
DECL|function|mdacon_scrolldelta
r_static
r_int
id|mdacon_scrolldelta
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|lines
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mdacon_cursor
r_static
r_void
id|mdacon_cursor
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|CM_ERASE
)paren
(brace
id|mda_set_cursor
c_func
(paren
id|mda_vram_len
op_minus
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|mda_set_cursor
c_func
(paren
id|c-&gt;vc_y
op_star
id|mda_num_columns
op_star
l_int|2
op_plus
id|c-&gt;vc_x
op_star
l_int|2
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;vc_cursor_type
op_amp
l_int|0x0f
)paren
(brace
r_case
id|CUR_LOWER_THIRD
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|10
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_LOWER_HALF
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|7
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_TWO_THIRDS
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|4
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_BLOCK
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|1
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CUR_NONE
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|14
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mda_set_cursor_size
c_func
(paren
l_int|12
comma
l_int|13
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|mdacon_scroll
r_static
r_int
id|mdacon_scroll
c_func
(paren
r_struct
id|vc_data
op_star
id|c
comma
r_int
id|t
comma
r_int
id|b
comma
r_int
id|dir
comma
r_int
id|lines
)paren
(brace
id|u16
id|eattr
op_assign
id|mda_convert_attr
c_func
(paren
id|c-&gt;vc_video_erase_char
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lines
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|lines
OG
id|c-&gt;vc_rows
)paren
multiline_comment|/* maximum realistic size */
id|lines
op_assign
id|c-&gt;vc_rows
suffix:semicolon
r_switch
c_cond
(paren
id|dir
)paren
(brace
r_case
id|SM_UP
suffix:colon
id|scr_memmovew
c_func
(paren
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|t
)paren
comma
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|t
op_plus
id|lines
)paren
comma
(paren
id|b
op_minus
id|t
op_minus
id|lines
)paren
op_star
id|mda_num_columns
op_star
l_int|2
)paren
suffix:semicolon
id|scr_memsetw
c_func
(paren
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|b
op_minus
id|lines
)paren
comma
id|eattr
comma
id|lines
op_star
id|mda_num_columns
op_star
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SM_DOWN
suffix:colon
id|scr_memmovew
c_func
(paren
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|t
op_plus
id|lines
)paren
comma
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|t
)paren
comma
(paren
id|b
op_minus
id|t
op_minus
id|lines
)paren
op_star
id|mda_num_columns
op_star
l_int|2
)paren
suffix:semicolon
id|scr_memsetw
c_func
(paren
id|MDA_ADDR
c_func
(paren
l_int|0
comma
id|t
)paren
comma
id|eattr
comma
id|lines
op_star
id|mda_num_columns
op_star
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  The console `switch&squot; structure for the MDA based console&n; */
DECL|variable|mda_con
r_struct
id|consw
id|mda_con
op_assign
(brace
id|mdacon_startup
comma
multiline_comment|/* con_startup */
id|mdacon_init
comma
multiline_comment|/* con_init */
id|mdacon_deinit
comma
multiline_comment|/* con_deinit */
id|mdacon_clear
comma
multiline_comment|/* con_clear */
id|mdacon_putc
comma
multiline_comment|/* con_putc */
id|mdacon_putcs
comma
multiline_comment|/* con_putcs */
id|mdacon_cursor
comma
multiline_comment|/* con_cursor */
id|mdacon_scroll
comma
multiline_comment|/* con_scroll */
id|mdacon_bmove
comma
multiline_comment|/* con_bmove */
id|mdacon_switch
comma
multiline_comment|/* con_switch */
id|mdacon_blank
comma
multiline_comment|/* con_blank */
id|mdacon_font_op
comma
multiline_comment|/* con_font_op */
id|mdacon_set_palette
comma
multiline_comment|/* con_set_palette */
id|mdacon_scrolldelta
comma
multiline_comment|/* con_scrolldelta */
l_int|NULL
comma
multiline_comment|/* con_set_origin */
l_int|NULL
comma
multiline_comment|/* con_save_screen */
id|mdacon_build_attr
comma
multiline_comment|/* con_build_attr */
id|mdacon_invert_region
comma
multiline_comment|/* con_invert_region */
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|mda_console_init
r_void
id|mda_console_init
c_func
(paren
r_void
)paren
macro_line|#else
id|__initfunc
c_func
(paren
r_void
id|mda_console_init
c_func
(paren
r_void
)paren
)paren
macro_line|#endif
(brace
r_if
c_cond
(paren
id|mda_first_vc
OG
id|mda_last_vc
)paren
r_return
suffix:semicolon
id|take_over_console
c_func
(paren
op_amp
id|mda_con
comma
id|mda_first_vc
comma
id|mda_last_vc
comma
l_int|0
)paren
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
id|mda_console_init
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
id|give_up_console
c_func
(paren
op_amp
id|mda_con
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
