macro_line|#ifndef ASMARM_VGA_H
DECL|macro|ASMARM_VGA_H
mdefine_line|#define ASMARM_VGA_H
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VGA_MAP_MEM
mdefine_line|#define VGA_MAP_MEM(x)&t;(0xe0000000 + (x))
DECL|macro|vga_readb
mdefine_line|#define vga_readb(x)&t;(*(x))
DECL|macro|vga_writeb
mdefine_line|#define vga_writeb(x,y)&t;(*(y) = (x))
macro_line|#endif
eof
