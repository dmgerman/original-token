macro_line|#ifndef _M68K_IO_H
DECL|macro|_M68K_IO_H
mdefine_line|#define _M68K_IO_H
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * readX/writeX() are used to access memory mapped devices. On some&n; * architectures the memory mapped IO stuff needs to be accessed&n; * differently. On the m68k architecture, we just read/write the&n; * memory location directly.&n; */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile unsigned short *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile unsigned int *) (addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile unsigned short *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile unsigned int *) (addr)) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
DECL|macro|inb_p
mdefine_line|#define inb_p(addr) readb(addr)
DECL|macro|inb
mdefine_line|#define inb(addr) readb(addr)
DECL|macro|outb
mdefine_line|#define outb(x,addr) ((void) writeb(x,addr))
DECL|macro|outb_p
mdefine_line|#define outb_p(x,addr) outb(x,addr)
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv.&n; */
r_extern
r_int
r_int
id|mm_vtop
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
r_extern
r_int
r_int
id|mm_ptov
c_func
(paren
r_int
r_int
id|addr
)paren
id|__attribute__
(paren
(paren
r_const
)paren
)paren
suffix:semicolon
DECL|function|virt_to_phys
r_extern
r_inline
r_int
r_int
id|virt_to_phys
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
r_return
id|mm_vtop
c_func
(paren
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
)brace
DECL|function|phys_to_virt
r_extern
r_inline
r_void
op_star
id|phys_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
(paren
r_void
op_star
)paren
id|mm_ptov
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * IO bus memory addresses are 1:1 with the physical address&n; */
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus virt_to_phys
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt phys_to_virt
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _M68K_IO_H */
eof
