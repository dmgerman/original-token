multiline_comment|/*&n; *&t;include/linux/vt_buffer.h -- Access to VT screen buffer&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; *&t;This is a set of macros and functions which are used in the&n; *&t;console driver and related code to access the screen buffer.&n; *&t;In most cases the console works with simple in-memory buffer,&n; *&t;but when handling hardware text mode consoles, we store&n; *&t;the foreground console directly in video memory.&n; */
macro_line|#ifndef _LINUX_VT_BUFFER_H_
DECL|macro|_LINUX_VT_BUFFER_H_
mdefine_line|#define _LINUX_VT_BUFFER_H_
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_VGA_CONSOLE
macro_line|#if !defined(CONFIG_FB) &amp;&amp; !defined(CONFIG_FB_MODULE)
DECL|macro|VT_BUF_VRAM_ONLY
mdefine_line|#define VT_BUF_VRAM_ONLY
macro_line|#endif
macro_line|#include &lt;asm/vga.h&gt;
macro_line|#endif
macro_line|#ifndef VT_BUF_HAVE_RW
DECL|macro|scr_writew
mdefine_line|#define scr_writew(val, addr) (*(addr) = (val))
DECL|macro|scr_readw
mdefine_line|#define scr_readw(addr) (*(addr))
DECL|macro|scr_memcpyw
mdefine_line|#define scr_memcpyw(d, s, c) memcpy(d, s, c)
DECL|macro|VT_BUF_HAVE_MEMCPYW
mdefine_line|#define VT_BUF_HAVE_MEMCPYW
DECL|macro|scr_memcpyw_from
mdefine_line|#define scr_memcpyw_from(d, s, c) memcpy(d, s, c)
DECL|macro|scr_memcpyw_to
mdefine_line|#define scr_memcpyw_to(d, s, c) memcpy(d, s, c)
DECL|macro|VT_BUF_HAVE_MEMCPYF
mdefine_line|#define VT_BUF_HAVE_MEMCPYF
macro_line|#endif
macro_line|#ifndef VT_BUF_HAVE_MEMSETW
DECL|function|scr_memsetw
r_extern
r_inline
r_void
id|scr_memsetw
c_func
(paren
id|u16
op_star
id|s
comma
id|u16
id|c
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
op_decrement
)paren
id|scr_writew
c_func
(paren
id|c
comma
id|s
op_increment
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef VT_BUF_HAVE_MEMCPYW
DECL|function|scr_memcpyw
r_extern
r_inline
r_void
id|scr_memcpyw
c_func
(paren
id|u16
op_star
id|d
comma
id|u16
op_star
id|s
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
op_decrement
)paren
id|scr_writew
c_func
(paren
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
comma
id|d
op_increment
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef VT_BUF_HAVE_MEMCPYF
DECL|function|scr_memcpyw_from
r_extern
r_inline
r_void
id|scr_memcpyw_from
c_func
(paren
id|u16
op_star
id|d
comma
id|u16
op_star
id|s
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
op_decrement
)paren
op_star
id|d
op_increment
op_assign
id|scr_readw
c_func
(paren
id|s
op_increment
)paren
suffix:semicolon
)brace
DECL|function|scr_memcpyw_to
r_extern
r_inline
r_void
id|scr_memcpyw_to
c_func
(paren
id|u16
op_star
id|d
comma
id|u16
op_star
id|s
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
op_decrement
)paren
id|scr_writew
c_func
(paren
op_star
id|s
op_increment
comma
id|d
op_increment
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|macro|reverse_video_char
mdefine_line|#define reverse_video_char(a)&t;(((a) &amp; 0x88) | ((((a) &gt;&gt; 4) | ((a) &lt;&lt; 4)) &amp; 0x77))
DECL|macro|reverse_video_short
mdefine_line|#define reverse_video_short(a)&t;(((a) &amp; 0x88ff) | &bslash;&n;&t;(((a) &amp; 0x7000) &gt;&gt; 4) | (((a) &amp; 0x0700) &lt;&lt; 4))
multiline_comment|/* this latter line used to have masks 0xf000 and 0x0f00, but selection&n;   requires a self-inverse operation; moreover, the old version looks wrong */
DECL|macro|reverse_video_short_mono
mdefine_line|#define reverse_video_short_mono(a)&t;((a) ^ 0x800)
DECL|macro|complement_video_short
mdefine_line|#define complement_video_short(a)&t;((a) ^ (can_do_color ? 0x7700 : 0x800))
macro_line|#endif
eof
