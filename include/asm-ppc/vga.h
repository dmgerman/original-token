multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#ifndef _LINUX_ASM_VGA_H_
DECL|macro|_LINUX_ASM_VGA_H_
mdefine_line|#define _LINUX_ASM_VGA_H_
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
DECL|macro|VT_BUF_HAVE_RW
mdefine_line|#define VT_BUF_HAVE_RW
DECL|function|scr_writew
r_extern
r_inline
r_void
id|scr_writew
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
multiline_comment|/* If using vgacon (not fbcon) byteswap the writes.&n;&t; * If non-vgacon assume fbcon and don&squot;t byteswap&n;&t; * just like include/linux/vt_buffer.h.&n;&t; * XXX: this is a performance loss so get rid of it&n;&t; *      as soon as fbcon works on prep.&n;&t; * -- Cort&n;&t; */
macro_line|#ifdef CONFIG_FB
r_if
c_cond
(paren
id|conswitchp
op_ne
op_amp
id|vga_con
)paren
(paren
op_star
(paren
id|addr
)paren
op_assign
(paren
id|val
)paren
)paren
suffix:semicolon
r_else
macro_line|#endif /* CONFIG_FB */
id|st_le16
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|scr_readw
r_extern
r_inline
id|u16
id|scr_readw
c_func
(paren
r_const
id|u16
op_star
id|addr
)paren
(brace
macro_line|#ifdef CONFIG_FB
r_if
c_cond
(paren
id|conswitchp
op_ne
op_amp
id|vga_con
)paren
r_return
(paren
op_star
(paren
id|addr
)paren
)paren
suffix:semicolon
r_else
macro_line|#endif /* CONFIG_FB */
r_return
id|ld_le16
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|addr
)paren
suffix:semicolon
)brace
DECL|macro|VT_BUF_HAVE_MEMCPYF
mdefine_line|#define VT_BUF_HAVE_MEMCPYF
DECL|macro|scr_memcpyw_from
mdefine_line|#define scr_memcpyw_from memcpy
DECL|macro|scr_memcpyw_to
mdefine_line|#define scr_memcpyw_to memcpy
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x) (x + _ISA_MEM_BASE)
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x) (*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y) (*(y) = (x))
macro_line|#endif
eof
