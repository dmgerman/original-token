multiline_comment|/*&n; *  linux/drivers/char/vga.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&t;&t;&t;1995  Jay Estabrook&n; */
multiline_comment|/*&n; *&t;vga.c&n; *&n; * This module exports the console low-level io support for VGA&n; *&n; *     &squot;int con_get_font(char *data)&squot;&n; *     &squot;int con_set_font(char *data, int ch512)&squot;&n; *     &squot;int con_adjust_height(int fontheight)&squot;&n; *&n; *     &squot;int con_get_cmap(char *)&squot;&n; *     &squot;int con_set_cmap(char *)&squot;&n; *&n; *     &squot;int reset_palette(int currcons)&squot;&n; *     &squot;void set_palette(void)&squot;&n; *&n; * User definable mapping table and font loading by Eugene G. Crosser,&n; * &lt;crosser@pccross.msk.su&gt;&n; *&n; * Improved loadable font/UTF-8 support by H. Peter Anvin &n; * Feb-Sep 1995 &lt;peter.anvin@linux.org&gt;&n; *&n; * Colour palette handling, by Simon Tatham&n; * 17-Jun-95 &lt;sgt20@cam.ac.uk&gt;&n; *&n; * if 512 char mode is already enabled don&squot;t re-enable it,&n; * because it causes screen to flicker, by Mitja Horvat&n; * 5-May-96 &lt;mitja.horvat@guest.arnes.si&gt;&n; *&n; * Use 2 outw instead of 4 outb_p to reduce erroneous text &n; * flashing on RHS of screen during heavy console scrolling .&n; * Oct 1996, Paul Gortmaker.&n; *&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &quot;kbd_kern.h&quot;
macro_line|#include &quot;vt_kern.h&quot;
macro_line|#include &quot;consolemap.h&quot;
macro_line|#include &quot;selection.h&quot;
macro_line|#include &quot;console_struct.h&quot;
DECL|macro|CAN_LOAD_EGA_FONTS
mdefine_line|#define CAN_LOAD_EGA_FONTS    /* undefine if the user must not do this */
DECL|macro|CAN_LOAD_PALETTE
mdefine_line|#define CAN_LOAD_PALETTE      /* undefine if the user must not do this */
DECL|macro|dac_reg
mdefine_line|#define dac_reg (0x3c8)
DECL|macro|dac_val
mdefine_line|#define dac_val (0x3c9)
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
id|video_port_reg
)paren
suffix:semicolon
id|outw
c_func
(paren
id|v2
comma
id|video_port_reg
)paren
suffix:semicolon
macro_line|#else
id|outb_p
c_func
(paren
id|reg
comma
id|video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|reg
op_plus
l_int|1
comma
id|video_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xff
comma
id|video_port_val
)paren
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|set_palette
id|set_palette
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
id|video_type
op_ne
id|VIDEO_TYPE_VGAC
op_logical_or
id|console_blanked
op_logical_or
id|vt_cons
(braket
id|fg_console
)braket
op_member_access_from_pointer
id|vc_mode
op_eq
id|KD_GRAPHICS
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|j
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
id|outb_p
(paren
id|color_table
(braket
id|i
)braket
comma
id|dac_reg
)paren
suffix:semicolon
id|outb_p
(paren
id|vc_cons
(braket
id|fg_console
)braket
dot
id|d-&gt;vc_palette
(braket
id|j
op_increment
)braket
op_rshift
l_int|2
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
(paren
id|vc_cons
(braket
id|fg_console
)braket
dot
id|d-&gt;vc_palette
(braket
id|j
op_increment
)braket
op_rshift
l_int|2
comma
id|dac_val
)paren
suffix:semicolon
id|outb_p
(paren
id|vc_cons
(braket
id|fg_console
)braket
dot
id|d-&gt;vc_palette
(braket
id|j
op_increment
)braket
op_rshift
l_int|2
comma
id|dac_val
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|__set_origin
id|__set_origin
c_func
(paren
r_int
r_int
id|offset
)paren
(brace
id|clear_selection
c_func
(paren
)paren
suffix:semicolon
id|__origin
op_assign
id|offset
suffix:semicolon
id|write_vga
c_func
(paren
l_int|12
comma
id|offset
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Put the cursor just beyond the end of the display adaptor memory.&n; */
r_void
DECL|function|hide_cursor
id|hide_cursor
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This is inefficient, we could just put the cursor at 0xffff,&n;     but perhaps the delays due to the inefficiency are useful for&n;     some hardware... */
id|write_vga
c_func
(paren
l_int|14
comma
(paren
id|video_mem_term
op_minus
id|video_mem_base
op_minus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|set_cursor
id|set_cursor
c_func
(paren
r_int
id|currcons
)paren
(brace
r_if
c_cond
(paren
id|currcons
op_ne
id|fg_console
op_logical_or
id|console_blanked
op_logical_or
id|vcmode
op_eq
id|KD_GRAPHICS
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|__real_origin
op_ne
id|__origin
)paren
id|__set_origin
c_func
(paren
id|__real_origin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|deccm
)paren
(brace
id|write_vga
c_func
(paren
l_int|14
comma
(paren
id|pos
op_minus
id|video_mem_base
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|hide_cursor
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
r_int
id|con_type_init
c_func
(paren
r_int
r_int
id|kmem_start
comma
r_const
r_char
op_star
op_star
id|display_desc
)paren
)paren
(brace
r_if
c_cond
(paren
id|ORIG_VIDEO_MODE
op_eq
l_int|7
)paren
multiline_comment|/* Is this a monochrome display? */
(brace
id|video_mem_base
op_assign
l_int|0xb0000
suffix:semicolon
id|video_port_reg
op_assign
l_int|0x3b4
suffix:semicolon
id|video_port_val
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
id|video_type
op_assign
id|VIDEO_TYPE_EGAM
suffix:semicolon
id|video_mem_term
op_assign
l_int|0xb8000
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;EGA+&quot;
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
id|video_type
op_assign
id|VIDEO_TYPE_MDA
suffix:semicolon
id|video_mem_term
op_assign
l_int|0xb2000
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;*MDA&quot;
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
multiline_comment|/* If not, it is color. */
(brace
id|can_do_color
op_assign
l_int|1
suffix:semicolon
id|video_mem_base
op_assign
l_int|0xb8000
suffix:semicolon
id|video_port_reg
op_assign
l_int|0x3d4
suffix:semicolon
id|video_port_val
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
id|video_mem_term
op_assign
l_int|0xc0000
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ORIG_VIDEO_ISVGA
)paren
(brace
id|video_type
op_assign
id|VIDEO_TYPE_EGAC
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;EGA&quot;
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
id|video_type
op_assign
id|VIDEO_TYPE_VGAC
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;VGA+&quot;
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
multiline_comment|/*&n;&t;&t;&t;&t; * get 64K rather than 32K of video RAM.&n;&t;&t;&t;&t; * This doesn&squot;t actually work on all &quot;VGA&quot;&n;&t;&t;&t;&t; * controllers (it seems like setting MM=01&n;&t;&t;&t;&t; * and COE=1 isn&squot;t necessarily a good idea)&n;&t;&t;&t;&t; */
id|video_mem_base
op_assign
l_int|0xa0000
suffix:semicolon
id|video_mem_term
op_assign
l_int|0xb0000
suffix:semicolon
id|outb_p
(paren
l_int|6
comma
l_int|0x3ce
)paren
suffix:semicolon
id|outb_p
(paren
l_int|6
comma
l_int|0x3cf
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;&t;&t;&t; * Normalise the palette registers, to point&n;&t;&t;&t;&t; * the 16 screen colours to the first 16&n;&t;&t;&t;&t; * DAC entries.&n;&t;&t;&t;&t; */
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
(paren
l_int|0x3da
)paren
suffix:semicolon
id|outb_p
(paren
id|i
comma
l_int|0x3c0
)paren
suffix:semicolon
id|outb_p
(paren
id|i
comma
l_int|0x3c0
)paren
suffix:semicolon
)brace
id|outb_p
(paren
l_int|0x20
comma
l_int|0x3c0
)paren
suffix:semicolon
multiline_comment|/* now set the DAC registers back to their&n;&t;&t;&t;&t; * default values */
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
id|outb_p
(paren
id|color_table
(braket
id|i
)braket
comma
l_int|0x3c8
)paren
suffix:semicolon
id|outb_p
(paren
id|default_red
(braket
id|i
)braket
comma
l_int|0x3c9
)paren
suffix:semicolon
id|outb_p
(paren
id|default_grn
(braket
id|i
)braket
comma
l_int|0x3c9
)paren
suffix:semicolon
id|outb_p
(paren
id|default_blu
(braket
id|i
)braket
comma
l_int|0x3c9
)paren
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
id|video_type
op_assign
id|VIDEO_TYPE_CGA
suffix:semicolon
id|video_mem_term
op_assign
l_int|0xba000
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;*CGA&quot;
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
r_return
id|kmem_start
suffix:semicolon
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|con_type_init_finish
c_func
(paren
r_void
)paren
)paren
(brace
)brace
r_void
DECL|function|get_scrmem
id|get_scrmem
c_func
(paren
r_int
id|currcons
)paren
(brace
id|memcpyw
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|vc_scrbuf
(braket
id|currcons
)braket
comma
(paren
r_int
r_int
op_star
)paren
id|origin
comma
id|video_screen_size
)paren
suffix:semicolon
id|origin
op_assign
id|video_mem_start
op_assign
(paren
r_int
r_int
)paren
id|vc_scrbuf
(braket
id|currcons
)braket
suffix:semicolon
id|scr_end
op_assign
id|video_mem_end
op_assign
id|video_mem_start
op_plus
id|video_screen_size
suffix:semicolon
id|pos
op_assign
id|origin
op_plus
id|y
op_star
id|video_size_row
op_plus
(paren
id|x
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
r_void
DECL|function|set_scrmem
id|set_scrmem
c_func
(paren
r_int
id|currcons
comma
r_int
id|offset
)paren
(brace
macro_line|#ifdef CONFIG_HGA
multiline_comment|/* This works with XFree86 1.2, 1.3 and 2.0&n;     This code could be extended and made more generally useful if we could&n;     determine the actual video mode. It appears that this should be&n;     possible on a genuine Hercules card, but I (WM) haven&squot;t been able to&n;     read from any of the required registers on my clone card.&n;     */
multiline_comment|/* This code should work with Hercules and MDA cards. */
r_if
c_cond
(paren
id|video_type
op_eq
id|VIDEO_TYPE_MDA
)paren
(brace
r_if
c_cond
(paren
id|vcmode
op_eq
id|KD_TEXT
)paren
(brace
multiline_comment|/* Ensure that the card is in text mode. */
r_int
id|i
suffix:semicolon
r_static
r_char
id|herc_txt_tbl
(braket
l_int|12
)braket
op_assign
(brace
l_int|0x61
comma
l_int|0x50
comma
l_int|0x52
comma
l_int|0x0f
comma
l_int|0x19
comma
l_int|6
comma
l_int|0x19
comma
l_int|0x19
comma
l_int|2
comma
l_int|0x0d
comma
l_int|0x0b
comma
l_int|0x0c
)brace
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0x3bf
)paren
suffix:semicolon
multiline_comment|/* Back to power-on defaults */
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0x3b8
)paren
suffix:semicolon
multiline_comment|/* Blank the screen, select page 0, etc */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|12
suffix:semicolon
id|i
op_increment
)paren
(brace
id|outb_p
c_func
(paren
id|i
comma
l_int|0x3b4
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|herc_txt_tbl
(braket
id|i
)braket
comma
l_int|0x3b5
)paren
suffix:semicolon
)brace
)brace
DECL|macro|HGA_BLINKER_ON
mdefine_line|#define HGA_BLINKER_ON 0x20
DECL|macro|HGA_SCREEN_ON
mdefine_line|#define HGA_SCREEN_ON  8
multiline_comment|/* Make sure that the hardware is not blanked */
id|outb_p
c_func
(paren
id|HGA_BLINKER_ON
op_or
id|HGA_SCREEN_ON
comma
l_int|0x3b8
)paren
suffix:semicolon
)brace
macro_line|#endif CONFIG_HGA
r_if
c_cond
(paren
id|video_mem_term
op_minus
id|video_mem_base
OL
id|offset
op_plus
id|video_screen_size
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* strange ... */
id|memcpyw
c_func
(paren
(paren
r_int
r_int
op_star
)paren
(paren
id|video_mem_base
op_plus
id|offset
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|origin
comma
id|video_screen_size
)paren
suffix:semicolon
id|video_mem_start
op_assign
id|video_mem_base
suffix:semicolon
id|video_mem_end
op_assign
id|video_mem_term
suffix:semicolon
id|origin
op_assign
id|video_mem_base
op_plus
id|offset
suffix:semicolon
id|scr_end
op_assign
id|origin
op_plus
id|video_screen_size
suffix:semicolon
id|pos
op_assign
id|origin
op_plus
id|y
op_star
id|video_size_row
op_plus
(paren
id|x
op_lshift
l_int|1
)paren
suffix:semicolon
id|has_wrapped
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * PIO_FONT support.&n; *&n; * The font loading code goes back to the codepage package by&n; * Joel Hoffman (joel@wam.umd.edu). (He reports that the original&n; * reference is: &quot;From: p. 307 of _Programmer&squot;s Guide to PC &amp; PS/2&n; * Video Systems_ by Richard Wilton. 1987.  Microsoft Press&quot;.)&n; *&n; * Change for certain monochrome monitors by Yury Shevchuck&n; * (sizif@botik.yaroslavl.su).&n; */
DECL|macro|colourmap
mdefine_line|#define colourmap ((char *)0xa0000)
multiline_comment|/* Pauline Middelink &lt;middelin@polyware.iaf.nl&gt; reports that we&n;   should use 0xA0000 for the bwmap as well.. */
DECL|macro|blackwmap
mdefine_line|#define blackwmap ((char *)0xa0000)
DECL|macro|cmapsz
mdefine_line|#define cmapsz 8192
DECL|macro|attrib_port
mdefine_line|#define attrib_port (0x3c0)
DECL|macro|seq_port_reg
mdefine_line|#define seq_port_reg (0x3c4)
DECL|macro|seq_port_val
mdefine_line|#define seq_port_val (0x3c5)
DECL|macro|gr_port_reg
mdefine_line|#define gr_port_reg (0x3ce)
DECL|macro|gr_port_val
mdefine_line|#define gr_port_val (0x3cf)
r_int
DECL|function|set_get_font
id|set_get_font
c_func
(paren
r_char
op_star
id|arg
comma
r_int
id|set
comma
r_int
id|ch512
)paren
(brace
macro_line|#ifdef CAN_LOAD_EGA_FONTS
r_static
r_int
id|ch512enabled
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|charmap
suffix:semicolon
r_int
id|beg
suffix:semicolon
r_int
r_int
id|video_port_status
op_assign
id|video_port_reg
op_plus
l_int|6
suffix:semicolon
r_int
id|font_select
op_assign
l_int|0x00
suffix:semicolon
multiline_comment|/* no use to &quot;load&quot; CGA... */
r_if
c_cond
(paren
id|video_type
op_eq
id|VIDEO_TYPE_EGAC
op_logical_or
id|video_type
op_eq
id|VIDEO_TYPE_VGAC
)paren
(brace
id|charmap
op_assign
id|colourmap
suffix:semicolon
id|beg
op_assign
l_int|0x0e
suffix:semicolon
macro_line|#ifdef VGA_CAN_DO_64KB
r_if
c_cond
(paren
id|video_type
op_eq
id|VIDEO_TYPE_VGAC
)paren
id|beg
op_assign
l_int|0x06
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
id|video_type
op_eq
id|VIDEO_TYPE_EGAM
)paren
(brace
id|charmap
op_assign
id|blackwmap
suffix:semicolon
id|beg
op_assign
l_int|0x0a
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
id|i
op_assign
id|verify_area
c_func
(paren
id|set
ques
c_cond
id|VERIFY_READ
suffix:colon
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
id|ch512
ques
c_cond
l_int|2
op_star
id|cmapsz
suffix:colon
id|cmapsz
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
r_else
id|ch512
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Default font is always 256 */
macro_line|#ifdef BROKEN_GRAPHICS_PROGRAMS
multiline_comment|/*&n;&t; * All fonts are loaded in slot 0 (0:1 for 512 ch)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Return to default font not supported */
id|video_font_is_default
op_assign
l_int|0
suffix:semicolon
id|font_select
op_assign
id|ch512
ques
c_cond
l_int|0x04
suffix:colon
l_int|0x00
suffix:semicolon
macro_line|#else&t;
multiline_comment|/*&n;&t; * The default font is kept in slot 0 and is never touched.&n;&t; * A custom font is loaded in slot 2 (256 ch) or 2:3 (512 ch)&n;&t; */
r_if
c_cond
(paren
id|set
)paren
(brace
id|video_font_is_default
op_assign
op_logical_neg
id|arg
suffix:semicolon
id|font_select
op_assign
id|arg
ques
c_cond
(paren
id|ch512
ques
c_cond
l_int|0x0e
suffix:colon
l_int|0x0a
)paren
suffix:colon
l_int|0x00
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|video_font_is_default
)paren
id|charmap
op_add_assign
l_int|4
op_star
id|cmapsz
suffix:semicolon
macro_line|#endif
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|seq_port_reg
)paren
suffix:semicolon
multiline_comment|/* First, the sequencer */
id|outb_p
c_func
(paren
l_int|0x01
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* Synchronous reset */
id|outb_p
c_func
(paren
l_int|0x02
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x04
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* CPU writes only to map 2 */
id|outb_p
c_func
(paren
l_int|0x04
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x07
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* Sequential addressing */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x03
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* Clear synchronous reset */
id|outb_p
c_func
(paren
l_int|0x04
comma
id|gr_port_reg
)paren
suffix:semicolon
multiline_comment|/* Now, the graphics controller */
id|outb_p
c_func
(paren
l_int|0x02
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* select map 2 */
id|outb_p
c_func
(paren
l_int|0x05
comma
id|gr_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* disable odd-even addressing */
id|outb_p
c_func
(paren
l_int|0x06
comma
id|gr_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* map start at A000:0000 */
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
r_if
c_cond
(paren
id|set
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
id|cmapsz
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
id|arg
op_plus
id|i
)paren
suffix:semicolon
id|scr_writeb
c_func
(paren
id|c
comma
id|charmap
op_plus
id|i
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
id|cmapsz
suffix:semicolon
id|i
op_increment
)paren
id|put_user
c_func
(paren
id|scr_readb
c_func
(paren
id|charmap
op_plus
id|i
)paren
comma
id|arg
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * In 512-character mode, the character map is not contiguous if&n;&t; * we want to remain EGA compatible -- which we do&n;&t; */
r_if
c_cond
(paren
id|ch512
)paren
(brace
id|charmap
op_add_assign
l_int|2
op_star
id|cmapsz
suffix:semicolon
id|arg
op_add_assign
id|cmapsz
suffix:semicolon
r_if
c_cond
(paren
id|set
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
id|cmapsz
suffix:semicolon
id|i
op_increment
)paren
(brace
r_char
id|c
suffix:semicolon
id|get_user
c_func
(paren
id|c
comma
id|arg
op_plus
id|i
)paren
suffix:semicolon
id|scr_writeb
c_func
(paren
id|c
comma
id|charmap
op_plus
id|i
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
id|cmapsz
suffix:semicolon
id|i
op_increment
)paren
id|put_user
c_func
(paren
id|scr_readb
c_func
(paren
id|charmap
op_plus
id|i
)paren
comma
id|arg
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|seq_port_reg
)paren
suffix:semicolon
multiline_comment|/* First, the sequencer */
id|outb_p
c_func
(paren
l_int|0x01
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* Synchronous reset */
id|outb_p
c_func
(paren
l_int|0x02
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x03
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* CPU writes to maps 0 and 1 */
id|outb_p
c_func
(paren
l_int|0x04
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x03
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* odd-even addressing */
r_if
c_cond
(paren
id|set
)paren
(brace
id|outb_p
c_func
(paren
l_int|0x03
comma
id|seq_port_reg
)paren
suffix:semicolon
multiline_comment|/* Character Map Select */
id|outb_p
c_func
(paren
id|font_select
comma
id|seq_port_val
)paren
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0x00
comma
id|seq_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x03
comma
id|seq_port_val
)paren
suffix:semicolon
multiline_comment|/* clear synchronous reset */
id|outb_p
c_func
(paren
l_int|0x04
comma
id|gr_port_reg
)paren
suffix:semicolon
multiline_comment|/* Now, the graphics controller */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* select map 0 for CPU */
id|outb_p
c_func
(paren
l_int|0x05
comma
id|gr_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x10
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* enable even-odd addressing */
id|outb_p
c_func
(paren
l_int|0x06
comma
id|gr_port_reg
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|beg
comma
id|gr_port_val
)paren
suffix:semicolon
multiline_comment|/* map starts at b800:0 or b000:0 */
multiline_comment|/* if 512 char mode is already enabled don&squot;t re-enable it. */
r_if
c_cond
(paren
(paren
id|set
)paren
op_logical_and
(paren
id|ch512
op_ne
id|ch512enabled
)paren
)paren
multiline_comment|/* attribute controller */
(brace
id|ch512enabled
op_assign
id|ch512
suffix:semicolon
multiline_comment|/* 256-char: enable intensity bit&n;&t;       512-char: disable intensity bit */
id|inb_p
c_func
(paren
id|video_port_status
)paren
suffix:semicolon
multiline_comment|/* clear address flip-flop */
id|outb_p
(paren
l_int|0x12
comma
id|attrib_port
)paren
suffix:semicolon
multiline_comment|/* color plane enable register */
id|outb_p
(paren
id|ch512
ques
c_cond
l_int|0x07
suffix:colon
l_int|0x0f
comma
id|attrib_port
)paren
suffix:semicolon
multiline_comment|/* Wilton (1987) mentions the following; I don&squot;t know what&n;&t;       it means, but it works, and it appears necessary */
id|inb_p
c_func
(paren
id|video_port_status
)paren
suffix:semicolon
id|outb_p
(paren
l_int|0x20
comma
id|attrib_port
)paren
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Adjust the screen to fit a font of a certain height&n; *&n; * Returns &lt; 0 for error, 0 if nothing changed, and the number&n; * of lines on the adjusted console if changed.&n; */
r_int
DECL|function|con_adjust_height
id|con_adjust_height
c_func
(paren
r_int
r_int
id|fontheight
)paren
(brace
r_int
id|rows
comma
id|maxscan
suffix:semicolon
r_int
r_char
id|ovr
comma
id|vde
comma
id|fsr
comma
id|curs
comma
id|cure
suffix:semicolon
r_if
c_cond
(paren
id|fontheight
OG
l_int|32
op_logical_or
(paren
id|video_type
op_ne
id|VIDEO_TYPE_VGAC
op_logical_and
id|video_type
op_ne
id|VIDEO_TYPE_EGAC
op_logical_and
id|video_type
op_ne
id|VIDEO_TYPE_EGAM
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fontheight
op_eq
id|video_font_height
op_logical_or
id|fontheight
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|video_font_height
op_assign
id|fontheight
suffix:semicolon
id|rows
op_assign
id|video_scan_lines
op_div
id|fontheight
suffix:semicolon
multiline_comment|/* Number of video rows we end up with */
id|maxscan
op_assign
id|rows
op_star
id|fontheight
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Scan lines to actually display-1 */
multiline_comment|/* Reprogram the CRTC for the new font size&n;&t;   Note: the attempt to read the overflow register will fail&n;&t;   on an EGA, but using 0xff for the previous value appears to&n;&t;   be OK for EGA text modes in the range 257-512 scan lines, so I&n;&t;   guess we don&squot;t need to worry about it.&n;&n;&t;   The same applies for the spill bits in the font size and cursor&n;&t;   registers; they are write-only on EGA, but it appears that they&n;&t;   are all don&squot;t care bits on EGA, so I guess it doesn&squot;t matter. */
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
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* CRTC overflow register */
id|ovr
op_assign
id|inb_p
c_func
(paren
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x09
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Font size register */
id|fsr
op_assign
id|inb_p
c_func
(paren
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0a
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Cursor start */
id|curs
op_assign
id|inb_p
c_func
(paren
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0b
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Cursor end */
id|cure
op_assign
id|inb_p
c_func
(paren
id|video_port_val
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|vde
op_assign
id|maxscan
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* Vertical display end reg */
id|ovr
op_assign
(paren
id|ovr
op_amp
l_int|0xbd
)paren
op_plus
multiline_comment|/* Overflow register */
(paren
(paren
id|maxscan
op_amp
l_int|0x100
)paren
op_rshift
l_int|7
)paren
op_plus
(paren
(paren
id|maxscan
op_amp
l_int|0x200
)paren
op_rshift
l_int|3
)paren
suffix:semicolon
id|fsr
op_assign
(paren
id|fsr
op_amp
l_int|0xe0
)paren
op_plus
(paren
id|fontheight
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*  Font size register */
id|curs
op_assign
(paren
id|curs
op_amp
l_int|0xc0
)paren
op_plus
id|fontheight
op_minus
(paren
id|fontheight
OL
l_int|10
ques
c_cond
l_int|2
suffix:colon
l_int|3
)paren
suffix:semicolon
id|cure
op_assign
(paren
id|cure
op_amp
l_int|0xe0
)paren
op_plus
id|fontheight
op_minus
(paren
id|fontheight
OL
l_int|10
ques
c_cond
l_int|1
suffix:colon
l_int|2
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
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* CRTC overflow register */
id|outb_p
c_func
(paren
id|ovr
comma
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x09
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Font size */
id|outb_p
c_func
(paren
id|fsr
comma
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0a
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Cursor start */
id|outb_p
c_func
(paren
id|curs
comma
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x0b
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Cursor end */
id|outb_p
c_func
(paren
id|cure
comma
id|video_port_val
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x12
comma
id|video_port_reg
)paren
suffix:semicolon
multiline_comment|/* Vertical display limit */
id|outb_p
c_func
(paren
id|vde
comma
id|video_port_val
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rows
op_eq
id|video_num_lines
)paren
(brace
multiline_comment|/* Change didn&squot;t affect number of lines -- no need to scare&n;&t;     the rest of the world */
r_return
l_int|0
suffix:semicolon
)brace
id|vc_resize
c_func
(paren
id|rows
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Adjust console size */
r_return
id|rows
suffix:semicolon
)brace
r_int
DECL|function|set_get_cmap
id|set_get_cmap
c_func
(paren
r_int
r_char
op_star
id|arg
comma
r_int
id|set
)paren
(brace
macro_line|#ifdef CAN_LOAD_PALETTE
r_int
id|i
suffix:semicolon
multiline_comment|/* no use to set colourmaps in less than colour VGA */
r_if
c_cond
(paren
id|video_type
op_ne
id|VIDEO_TYPE_VGAC
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|set
ques
c_cond
id|VERIFY_READ
suffix:colon
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
l_int|16
op_star
l_int|3
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
r_if
c_cond
(paren
id|set
)paren
(brace
id|get_user
c_func
(paren
id|default_red
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|default_grn
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|default_blu
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
)brace
r_else
(brace
id|put_user
(paren
id|default_red
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
id|put_user
(paren
id|default_grn
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
id|put_user
(paren
id|default_blu
(braket
id|i
)braket
comma
id|arg
op_increment
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|set
)paren
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
id|MAX_NR_CONSOLES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|vc_cons_allocated
c_func
(paren
id|i
)paren
)paren
(brace
r_int
id|j
comma
id|k
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|k
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
id|j
op_increment
)paren
(brace
id|vc_cons
(braket
id|i
)braket
dot
id|d-&gt;vc_palette
(braket
id|k
op_increment
)braket
op_assign
id|default_red
(braket
id|j
)braket
suffix:semicolon
id|vc_cons
(braket
id|i
)braket
dot
id|d-&gt;vc_palette
(braket
id|k
op_increment
)braket
op_assign
id|default_grn
(braket
id|j
)braket
suffix:semicolon
id|vc_cons
(braket
id|i
)braket
dot
id|d-&gt;vc_palette
(braket
id|k
op_increment
)braket
op_assign
id|default_blu
(braket
id|j
)braket
suffix:semicolon
)brace
)brace
id|set_palette
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|EINVAL
suffix:semicolon
macro_line|#endif
)brace
eof
