multiline_comment|/*&n; *  linux/drivers/char/g364.c&n; *&n; *  Copyright (C) 1996  Wayne Hodgen&n; *&n; *  Based on and using chunks of Jay Estabrooks tga.c&n; *&n; * This module exports the console io support for Inmos&squot;s G364 controller&n; * used in Mips Magnums and clones. Based on the hardware desc for the&n; * Olivetti M700-10 ie. an Inmos G364 based card in a dedicated video slot,&n; * 2MB dual ported VRAM with a 64 bit data path, 256 color lookup table,&n; * palette of 16.7M and a user definable 64x64 hardware cursor.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/tty_flip.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kbd_kern.h&gt;
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/consolemap.h&gt;
macro_line|#include &lt;linux/selection.h&gt;
macro_line|#include &lt;linux/console_struct.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/types.h&gt;
r_extern
r_void
id|register_console
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|console_print
c_func
(paren
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|variable|video_res_x
r_int
id|video_res_x
suffix:semicolon
multiline_comment|/* &n; * Various defines for the G364&n; */
DECL|macro|G364_MEM_BASE
mdefine_line|#define G364_MEM_BASE   0xe4400000
DECL|macro|G364_PORT_BASE
mdefine_line|#define G364_PORT_BASE  0xe4000000
DECL|macro|ID_REG
mdefine_line|#define ID_REG &t;&t;0xe4000000  &t;/* Read only */
DECL|macro|BOOT_REG
mdefine_line|#define BOOT_REG &t;0xe4080000
DECL|macro|TIMING_REG
mdefine_line|#define TIMING_REG &t;0xe4080108 &t;/* to 0x080170 - DON&squot;T TOUCH! */
DECL|macro|MASK_REG
mdefine_line|#define MASK_REG &t;0xe4080200
DECL|macro|CTLA_REG
mdefine_line|#define CTLA_REG &t;0xe4080300
DECL|macro|CURS_TOGGLE
mdefine_line|#define CURS_TOGGLE &t;0x800000
DECL|macro|BIT_PER_PIX
mdefine_line|#define BIT_PER_PIX&t;0x700000&t;/* bits 22 to 20 of Control A */
DECL|macro|DELAY_SAMPLE
mdefine_line|#define DELAY_SAMPLE    0x080000
DECL|macro|PORT_INTER
mdefine_line|#define PORT_INTER&t;0x040000
DECL|macro|PIX_PIPE_DEL
mdefine_line|#define PIX_PIPE_DEL&t;0x030000&t;/* bits 17 and 16 of Control A */
DECL|macro|PIX_PIPE_DEL2
mdefine_line|#define PIX_PIPE_DEL2&t;0x008000&t;/* same as above - don&squot;t ask me why */
DECL|macro|TR_CYCLE_TOG
mdefine_line|#define TR_CYCLE_TOG&t;0x004000
DECL|macro|VRAM_ADR_INC
mdefine_line|#define VRAM_ADR_INC&t;0x003000&t;/* bits 13 and 12 of Control A */
DECL|macro|BLANK_OFF
mdefine_line|#define BLANK_OFF&t;0x000800
DECL|macro|FORCE_BLANK
mdefine_line|#define FORCE_BLANK&t;0x000400
DECL|macro|BLK_FUN_SWTCH
mdefine_line|#define BLK_FUN_SWTCH&t;0x000200
DECL|macro|BLANK_IO
mdefine_line|#define BLANK_IO&t;0x000100
DECL|macro|BLANK_LEVEL
mdefine_line|#define BLANK_LEVEL&t;0x000080
DECL|macro|A_VID_FORM
mdefine_line|#define A_VID_FORM&t;0x000040
DECL|macro|D_SYNC_FORM
mdefine_line|#define D_SYNC_FORM&t;0x000020
DECL|macro|FRAME_FLY_PAT
mdefine_line|#define FRAME_FLY_PAT&t;0x000010
DECL|macro|OP_MODE
mdefine_line|#define OP_MODE&t;&t;0x000008
DECL|macro|INTL_STAND
mdefine_line|#define INTL_STAND&t;0x000004
DECL|macro|SCRN_FORM
mdefine_line|#define SCRN_FORM&t;0x000002
DECL|macro|ENABLE_VTG
mdefine_line|#define ENABLE_VTG&t;0x000001&t;
DECL|macro|TOP_REG
mdefine_line|#define TOP_REG &t;0xe4080400
DECL|macro|CURS_PAL_REG
mdefine_line|#define CURS_PAL_REG &t;0xe4080508 &t;/* to 0x080518 */
DECL|macro|CHKSUM_REG
mdefine_line|#define CHKSUM_REG &t;0xe4080600 &t;/* to 0x080610 - unused */
DECL|macro|CURS_POS_REG
mdefine_line|#define CURS_POS_REG &t;0xe4080638
DECL|macro|CLR_PAL_REG
mdefine_line|#define CLR_PAL_REG &t;0xe4080800&t;/* to 0x080ff8 */
DECL|macro|CURS_PAT_REG
mdefine_line|#define CURS_PAT_REG &t;0xe4081000&t;/* to 0x081ff8 */
DECL|macro|MON_ID_REG
mdefine_line|#define MON_ID_REG &t;0xe4100000 &t;/* unused */
DECL|macro|RESET_REG
mdefine_line|#define RESET_REG &t;0xe4180000  &t;/* Write only */
multiline_comment|/*&n; * built-in font management constants&n; *&n; * NOTE: the built-in font is 8x16, and the video resolution&n; * is either 1280x1024 @ 60Hz or 1024x768 @ 60 or 78Hz.&n; */
DECL|macro|FONTSIZE_X
mdefine_line|#define FONTSIZE_X &t;8 &t;/*  8 pixels wide */
DECL|macro|FONTSIZE_Y
mdefine_line|#define FONTSIZE_Y &t;16 &t;/* 16 pixels high */
DECL|variable|g364_font
r_int
r_char
id|g364_font
(braket
)braket
op_assign
(brace
macro_line|#include &quot;g364.fnt&quot;
)brace
suffix:semicolon
DECL|variable|g364_cursor
id|u32
id|g364_cursor
(braket
l_int|256
)braket
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
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffff0000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffff0000
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0xffff0000
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
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_REMOTE_DEBUG
multiline_comment|/* #define DEBUG_G364 */
r_extern
r_int
id|putDebugChar
c_func
(paren
r_char
id|c
)paren
suffix:semicolon
r_void
DECL|function|putDebugString
id|putDebugString
c_func
(paren
r_char
op_star
id|d_str
)paren
(brace
r_while
c_loop
(paren
op_star
id|d_str
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|putDebugChar
c_func
(paren
op_star
id|d_str
)paren
suffix:semicolon
id|d_str
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
op_decrement
id|d_str
op_ne
l_char|&squot;&bslash;n&squot;
)paren
id|putDebugChar
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif
r_void
id|g364_clear_screen
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|cursor_initialised
r_int
id|cursor_initialised
op_assign
l_int|0
suffix:semicolon
r_int
r_int
DECL|function|con_type_init
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
(brace
id|can_do_color
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;        * fake the screen memory with some CPU memory&n;        */
id|video_mem_base
op_assign
id|kmem_start
suffix:semicolon
id|kmem_start
op_add_assign
id|video_screen_size
suffix:semicolon
id|video_mem_term
op_assign
id|kmem_start
suffix:semicolon
id|video_type
op_assign
id|VIDEO_TYPE_MIPS_G364
suffix:semicolon
id|video_res_x
op_assign
id|video_num_columns
op_star
id|FONTSIZE_X
suffix:semicolon
op_star
id|display_desc
op_assign
l_string|&quot;G364&quot;
suffix:semicolon
r_return
id|kmem_start
suffix:semicolon
)brace
DECL|function|con_type_init_finish
id|con_type_init_finish
c_func
(paren
r_void
)paren
(brace
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
multiline_comment|/*&n;   * should not be called, but if so, do nothing...&n;   */
)brace
multiline_comment|/*&n; * Hide the cursor from view, during blanking, usually...&n; */
r_void
DECL|function|hide_cursor
id|hide_cursor
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&t;*(unsigned int *) CTLA_REG &amp;= ~CURS_TOGGLE; */
)brace
r_void
DECL|function|init_g364_cursor
id|init_g364_cursor
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|CURS_PAL_REG
suffix:semicolon
op_star
id|ptr
op_or_assign
l_int|0x00ffffff
suffix:semicolon
id|ptr
(braket
l_int|2
)braket
op_or_assign
l_int|0x00ffffff
suffix:semicolon
id|ptr
(braket
l_int|4
)braket
op_or_assign
l_int|0x00ffffff
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|CURS_PAT_REG
comma
op_amp
id|g364_cursor
comma
l_int|1024
)paren
suffix:semicolon
id|cursor_initialised
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Set the cursor on.&n; */
r_void
DECL|function|set_cursor
id|set_cursor
c_func
(paren
r_int
id|currcons
)paren
(brace
multiline_comment|/*&n;&t;if (!cursor_initialised)&n;&t;&t;init_g364_cursor();&n;&n;&t;if (console_blanked)&n;&t;&t;return;&n;&n;&t;*(unsigned int *) CTLA_REG |= CURS_TOGGLE;&n;*/
)brace
multiline_comment|/*&n; * NOTE: get_scrmem() and set_scrmem() are here only because&n; * the VGA version of set_scrmem() has some direct VGA references.&n; */
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
)brace
multiline_comment|/*&n; * Fill out later&n; */
r_void
DECL|function|set_palette
id|set_palette
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
r_volatile
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_volatile
r_int
r_int
op_star
)paren
id|CLR_PAL_REG
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
comma
id|ptr
op_add_assign
l_int|2
)paren
(brace
id|j
op_assign
id|color_table
(braket
id|i
)braket
suffix:semicolon
op_star
id|ptr
op_assign
(paren
(paren
id|default_red
(braket
id|j
)braket
op_lshift
l_int|16
)paren
op_or
(paren
id|default_grn
(braket
id|j
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|default_blu
(braket
id|j
)braket
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * NOTE:&n; * this is here, and not in console.c, because the VGA version&n; * tests the controller type to see if color can be done. We *KNOW*&n; * that we can do color on the G364.&n; *&n; */
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
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
l_int|16
op_star
l_int|3
)paren
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
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
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
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
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
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
)paren
r_goto
id|fault
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
l_int|16
op_star
l_int|3
)paren
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
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
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
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
)paren
r_goto
id|fault
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
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
)paren
r_goto
id|fault
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
id|fault
suffix:colon
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
multiline_comment|/*&n; * Adjust the screen to fit a font of a certain height&n; *&n; * Returns &lt; 0 for error, 0 if nothing changed, and the number&n; * of lines on the adjusted console if changed.&n; *&n; * for now, we only support the built-in font...&n; */
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * PIO_FONT support.&n; *&n; * for now, we will use/allow *only* our built-in font...&n; */
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
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * print a character to a graphics console.&n; */
r_void
DECL|function|g364_blitc
id|g364_blitc
c_func
(paren
r_int
r_int
id|charattr
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|row
comma
id|col
comma
id|temp
suffix:semicolon
r_register
r_int
r_int
r_int
op_star
id|dst
comma
op_star
id|font_row
suffix:semicolon
r_register
r_int
id|i
suffix:semicolon
r_char
id|c
suffix:semicolon
multiline_comment|/*&n;   * calculate (row,col) from addr and video_mem_base&n;   */
id|temp
op_assign
(paren
id|addr
op_minus
id|video_mem_base
)paren
op_rshift
l_int|1
suffix:semicolon
id|col
op_assign
id|temp
op_mod
l_int|128
suffix:semicolon
id|row
op_assign
(paren
id|temp
op_minus
id|col
)paren
op_div
l_int|128
suffix:semicolon
multiline_comment|/*&n;   * calculate destination address&n;   */
id|dst
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
(paren
id|G364_MEM_BASE
op_plus
(paren
id|row
op_star
id|video_res_x
op_star
id|FONTSIZE_Y
)paren
op_plus
(paren
id|col
op_star
id|FONTSIZE_X
)paren
)paren
suffix:semicolon
id|c
op_assign
id|charattr
op_amp
l_int|0x00ff
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_int|0x20
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
id|FONTSIZE_Y
suffix:semicolon
id|i
op_increment
comma
id|dst
op_add_assign
id|video_num_columns
)paren
op_star
id|dst
op_assign
l_int|0x00000000
suffix:semicolon
)brace
r_else
(brace
id|font_row
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
op_amp
id|g364_font
(braket
(paren
id|c
op_lshift
l_int|7
)paren
)braket
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
id|FONTSIZE_Y
suffix:semicolon
id|i
op_increment
comma
id|font_row
op_increment
comma
id|dst
op_add_assign
id|video_num_columns
)paren
op_star
id|dst
op_assign
op_star
id|font_row
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * print a character to a graphics console. Colour version, slower!&n; */
r_void
DECL|function|g364_blitc_colour
id|g364_blitc_colour
c_func
(paren
r_int
r_int
id|charattr
comma
r_int
r_int
id|addr
)paren
(brace
r_int
id|row
comma
id|col
comma
id|temp
comma
id|c
comma
id|attrib
suffix:semicolon
r_register
r_int
r_int
id|fgmask
comma
id|bgmask
suffix:semicolon
r_register
r_int
r_int
r_int
op_star
id|dst
comma
op_star
id|font_row
suffix:semicolon
r_register
r_int
id|i
comma
id|stride
suffix:semicolon
id|c
op_assign
id|charattr
op_amp
l_int|0x00ff
suffix:semicolon
id|attrib
op_assign
(paren
id|charattr
op_rshift
l_int|8
)paren
op_amp
l_int|0x00ff
suffix:semicolon
multiline_comment|/*&n;   * extract foreground and background indices&n;   * NOTE: we always treat blink/underline bits as color for now...&n;   */
id|fgmask
op_assign
id|attrib
op_amp
l_int|0x0f
suffix:semicolon
id|bgmask
op_assign
(paren
id|attrib
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
suffix:semicolon
multiline_comment|/* i = (c &amp; 0xff) &lt;&lt; 7;  NOTE: assumption of 128 bytes per character bitmap */
multiline_comment|/*&n;   * calculate (row,col) from addr and video_mem_base&n;   */
id|temp
op_assign
(paren
id|addr
op_minus
id|video_mem_base
)paren
op_rshift
l_int|1
suffix:semicolon
id|col
op_assign
id|temp
op_mod
l_int|128
suffix:semicolon
id|row
op_assign
(paren
id|temp
op_minus
id|col
)paren
op_div
l_int|128
suffix:semicolon
id|stride
op_assign
id|video_res_x
op_div
l_int|8
suffix:semicolon
multiline_comment|/*&n;   * calculate destination address&n;   */
id|dst
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
(paren
id|G364_MEM_BASE
op_plus
(paren
id|row
op_star
id|video_res_x
op_star
id|FONTSIZE_Y
)paren
op_plus
(paren
id|col
op_star
id|FONTSIZE_X
)paren
)paren
suffix:semicolon
id|font_row
op_assign
(paren
r_int
r_int
r_int
op_star
)paren
op_amp
id|g364_font
(braket
(paren
(paren
id|c
op_amp
l_int|0xff
)paren
op_lshift
l_int|7
)paren
)braket
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
id|FONTSIZE_Y
suffix:semicolon
id|i
op_increment
comma
id|font_row
op_increment
comma
id|dst
op_add_assign
id|stride
)paren
(brace
op_star
id|dst
op_assign
op_star
id|font_row
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * dummy routines for the VESA blanking code, which is VGA only,&n; * so we don&squot;t have to carry that stuff around for the G364...&n; */
r_void
DECL|function|vesa_powerdown
id|vesa_powerdown
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|vesa_blank
id|vesa_blank
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|vesa_unblank
id|vesa_unblank
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|set_vesa_blanking
id|set_vesa_blanking
c_func
(paren
r_const
r_int
r_int
id|arg
)paren
(brace
)brace
eof
