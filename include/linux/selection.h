multiline_comment|/*&n; * selection.h&n; *&n; * Interface between console.c, tty_io.c, vt.c, vc_screen.c and selection.c&n; */
macro_line|#include &lt;linux/config.h&gt;
r_extern
r_int
id|sel_cons
suffix:semicolon
r_extern
r_void
id|clear_selection
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|set_selection
c_func
(paren
r_const
r_int
r_int
id|arg
comma
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|user
)paren
suffix:semicolon
r_extern
r_int
id|paste_selection
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_extern
r_int
id|sel_loadlut
c_func
(paren
r_const
r_int
r_int
id|arg
)paren
suffix:semicolon
r_extern
r_int
id|mouse_reporting
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|mouse_report
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|butt
comma
r_int
id|mrx
comma
r_int
id|mry
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FB_CONSOLE
r_extern
r_int
r_int
id|get_video_num_columns
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_video_num_lines
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_video_size_row
c_func
(paren
r_int
r_int
id|console
)paren
suffix:semicolon
macro_line|#else
DECL|macro|get_video_num_columns
mdefine_line|#define get_video_num_columns(dummy) video_num_columns
DECL|macro|get_video_num_lines
mdefine_line|#define get_video_num_lines(dummy) video_num_lines
DECL|macro|get_video_size_row
mdefine_line|#define get_video_size_row(dummy) video_size_row
r_extern
r_int
r_int
id|video_num_columns
suffix:semicolon
r_extern
r_int
r_int
id|video_num_lines
suffix:semicolon
r_extern
r_int
r_int
id|video_size_row
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_char
id|video_type
suffix:semicolon
r_extern
r_int
r_int
id|video_mem_base
suffix:semicolon
r_extern
r_int
r_int
id|video_mem_term
suffix:semicolon
r_extern
r_int
r_int
id|video_screen_size
suffix:semicolon
r_extern
r_int
r_int
id|video_port_reg
suffix:semicolon
r_extern
r_int
r_int
id|video_port_val
suffix:semicolon
r_extern
r_int
id|console_blanked
suffix:semicolon
r_extern
r_int
id|can_do_color
suffix:semicolon
r_extern
r_int
r_int
id|video_font_height
suffix:semicolon
r_extern
r_int
r_int
id|video_scan_lines
suffix:semicolon
r_extern
r_int
r_int
id|default_font_height
suffix:semicolon
r_extern
r_int
id|video_font_is_default
suffix:semicolon
r_extern
r_int
r_char
id|color_table
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_red
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_grn
(braket
)braket
suffix:semicolon
r_extern
r_int
id|default_blu
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|__real_origin
suffix:semicolon
r_extern
r_int
r_int
id|__origin
suffix:semicolon
r_extern
r_int
r_char
id|has_wrapped
suffix:semicolon
r_extern
r_int
r_int
op_star
id|vc_scrbuf
(braket
id|MAX_NR_CONSOLES
)braket
suffix:semicolon
r_extern
r_void
id|do_unblank_screen
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
op_star
id|screen_pos
c_func
(paren
r_int
id|currcons
comma
r_int
id|w_offset
comma
r_int
id|viewed
)paren
suffix:semicolon
r_extern
r_int
r_int
id|screen_word
c_func
(paren
r_int
id|currcons
comma
r_int
id|offset
comma
r_int
id|viewed
)paren
suffix:semicolon
r_extern
r_int
id|scrw2glyph
c_func
(paren
r_int
r_int
id|scr_word
)paren
suffix:semicolon
r_extern
r_void
id|complement_pos
c_func
(paren
r_int
id|currcons
comma
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_void
id|invert_screen
c_func
(paren
r_int
id|currcons
comma
r_int
id|offset
comma
r_int
id|count
comma
r_int
id|shift
)paren
suffix:semicolon
DECL|macro|reverse_video_char
mdefine_line|#define reverse_video_char(a)&t;(((a) &amp; 0x88) | ((((a) &gt;&gt; 4) | ((a) &lt;&lt; 4)) &amp; 0x77))
DECL|macro|reverse_video_short
mdefine_line|#define reverse_video_short(a)&t;(((a) &amp; 0x88ff) | &bslash;&n;&t;(((a) &amp; 0x7000) &gt;&gt; 4) | (((a) &amp; 0x0700) &lt;&lt; 4))
multiline_comment|/* this latter line used to have masks 0xf000 and 0x0f00, but selection&n;   requires a self-inverse operation; moreover, the old version looks wrong */
r_extern
r_void
id|getconsxy
c_func
(paren
r_int
id|currcons
comma
r_char
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|putconsxy
c_func
(paren
r_int
id|currcons
comma
r_char
op_star
id|p
)paren
suffix:semicolon
multiline_comment|/* how to access screen memory */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_TGA_CONSOLE)
r_extern
r_int
id|tga_blitc
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|video_mem_term
suffix:semicolon
multiline_comment|/*&n; * TGA console screen memory access&n; * &n; * TGA is *not* a character/attribute cell device; font bitmaps must be rendered&n; * to the screen pixels.&n; *&n; * We must test for an Alpha kernel virtual address that falls within&n; *  the &quot;shadow screen&quot; memory. This condition indicates we really want &n; *  to write to the screen, so, we do... :-)&n; *&n; * NOTE also: there&squot;s only *TWO* operations: to put/get a character/attribute.&n; *  All the others needed by VGA support go away, as Not Applicable for TGA.&n; */
DECL|function|scr_writew
r_static
r_inline
r_void
id|scr_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;         * always deposit the char/attr, then see if it was to &quot;screen&quot; mem.&n;&t; * if so, then render the char/attr onto the real screen.&n;         */
op_star
id|addr
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
OL
id|video_mem_term
op_logical_and
(paren
r_int
r_int
)paren
id|addr
op_ge
id|video_mem_base
)paren
(brace
id|tga_blitc
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
)brace
)brace
DECL|function|scr_readw
r_static
r_inline
r_int
r_int
id|scr_readw
c_func
(paren
r_int
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
macro_line|#elif defined(CONFIG_SUN_CONSOLE)
macro_line|#include &lt;linux/vt_kern.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
r_extern
r_int
id|sun_blitc
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|memsetw
c_func
(paren
r_void
op_star
id|s
comma
r_int
r_int
id|c
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|memcpyw
c_func
(paren
r_int
r_int
op_star
id|to
comma
r_int
r_int
op_star
id|from
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_extern
r_int
r_int
id|video_mem_term
suffix:semicolon
multiline_comment|/* Basically the same as the TGA stuff. */
DECL|function|scr_writew
r_static
r_inline
r_void
id|scr_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;         * always deposit the char/attr, then see if it was to &quot;screen&quot; mem.&n;&t; * if so, then render the char/attr onto the real screen.&n;         */
r_if
c_cond
(paren
op_star
id|addr
op_ne
id|val
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|addr
OL
id|video_mem_term
op_logical_and
(paren
r_int
r_int
)paren
id|addr
op_ge
id|video_mem_base
op_logical_and
id|vt_cons
(braket
id|fg_console
)braket
op_member_access_from_pointer
id|vc_mode
op_eq
id|KD_TEXT
)paren
id|sun_blitc
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
)brace
)brace
DECL|function|scr_readw
r_static
r_inline
r_int
r_int
id|scr_readw
c_func
(paren
r_int
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
macro_line|#else /* CONFIG_TGA_CONSOLE  || CONFIG_SUN_CONSOLE */
multiline_comment|/*&n; * normal VGA console access&n; *&n; */
macro_line|#include &lt;asm/io.h&gt; 
multiline_comment|/*&n; * NOTE: &quot;(long) addr &lt; 0&quot; tests for an Alpha kernel virtual address; this&n; *  indicates a VC&squot;s backing store; otherwise, it&squot;s a bus memory address, for&n; *  the VGA&squot;s screen memory, so we do the Alpha &quot;swizzle&quot;... :-)&n; */
DECL|function|scr_writeb
r_static
r_inline
r_void
id|scr_writeb
c_func
(paren
r_int
r_char
id|val
comma
r_int
r_char
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|addr
OL
l_int|0
)paren
op_star
id|addr
op_assign
id|val
suffix:semicolon
r_else
id|writeb
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
)brace
DECL|function|scr_readb
r_static
r_inline
r_int
r_char
id|scr_readb
c_func
(paren
r_int
r_char
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|addr
OL
l_int|0
)paren
r_return
op_star
id|addr
suffix:semicolon
r_return
id|readb
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|scr_writew
r_static
r_inline
r_void
id|scr_writew
c_func
(paren
r_int
r_int
id|val
comma
r_int
r_int
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|addr
OL
l_int|0
)paren
op_star
id|addr
op_assign
id|val
suffix:semicolon
r_else
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
)brace
DECL|function|scr_readw
r_static
r_inline
r_int
r_int
id|scr_readw
c_func
(paren
r_int
r_int
op_star
id|addr
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
id|addr
OL
l_int|0
)paren
r_return
op_star
id|addr
suffix:semicolon
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
)brace
macro_line|#endif /* CONFIG_TGA_CONSOLE */
macro_line|#ifndef CONFIG_SUN_CONSOLE
DECL|function|memsetw
r_static
r_inline
r_void
id|memsetw
c_func
(paren
r_void
op_star
id|s
comma
r_int
r_int
id|c
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|addr
op_assign
(paren
r_int
r_int
op_star
)paren
id|s
suffix:semicolon
id|count
op_div_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|scr_writew
c_func
(paren
id|c
comma
id|addr
op_increment
)paren
suffix:semicolon
)brace
)brace
DECL|function|memcpyw
r_static
r_inline
r_void
id|memcpyw
c_func
(paren
r_int
r_int
op_star
id|to
comma
r_int
r_int
op_star
id|from
comma
r_int
r_int
id|count
)paren
(brace
id|count
op_div_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|count
)paren
(brace
id|count
op_decrement
suffix:semicolon
id|scr_writew
c_func
(paren
id|scr_readw
c_func
(paren
id|from
op_increment
)paren
comma
id|to
op_increment
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_SUN_CONSOLE */
eof