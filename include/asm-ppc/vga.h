multiline_comment|/*&n; *&t;Access to VGA videoram&n; *&n; *&t;(c) 1998 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#ifndef _LINUX_ASM_VGA_H_
DECL|macro|_LINUX_ASM_VGA_H_
mdefine_line|#define _LINUX_ASM_VGA_H_
macro_line|#include &lt;asm/io.h&gt;
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
id|u16
op_star
id|addr
)paren
(brace
r_return
id|ld_le16
c_func
(paren
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
