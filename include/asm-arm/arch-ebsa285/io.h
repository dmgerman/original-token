multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/io.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/dec21285.h&gt;
multiline_comment|/*&n; * This architecture does not require any delayed IO, and&n; * has the constant-optimised IO&n; */
DECL|macro|ARCH_IO_DELAY
macro_line|#undef&t;ARCH_IO_DELAY
DECL|macro|ARCH_READWRITE
mdefine_line|#define ARCH_READWRITE
DECL|macro|__pci_io_addr
mdefine_line|#define __pci_io_addr(x)&t;(PCIO_BASE + (unsigned int)(x))
DECL|macro|__inb
mdefine_line|#define __inb(p)&t;&t;(*(volatile unsigned char *)__pci_io_addr(p))
DECL|macro|__inl
mdefine_line|#define __inl(p)&t;&t;(*(volatile unsigned long *)__pci_io_addr(p))
DECL|function|__inw
r_extern
id|__inline__
r_int
r_int
id|__inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|value
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ldr%?h&t;%0, [%1, %2]&t;@ inw&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|value
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|PCIO_BASE
)paren
comma
l_string|&quot;r&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
r_return
id|value
suffix:semicolon
)brace
DECL|macro|__outb
mdefine_line|#define __outb(v,p)&t;&t;(*(volatile unsigned char *)__pci_io_addr(p) = (v))
DECL|macro|__outl
mdefine_line|#define __outl(v,p)&t;&t;(*(volatile unsigned long *)__pci_io_addr(p) = (v))
DECL|function|__outw
r_extern
id|__inline__
r_void
id|__outw
c_func
(paren
r_int
r_int
id|value
comma
r_int
r_int
id|port
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;str%?h&t;%0, [%1, %2]&t;@ outw&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|value
)paren
comma
l_string|&quot;r&quot;
(paren
id|PCIO_BASE
)paren
comma
l_string|&quot;r&quot;
(paren
id|port
)paren
)paren
suffix:semicolon
)brace
DECL|macro|__ioaddr
mdefine_line|#define __ioaddr(p)&t;__pci_io_addr(p)
multiline_comment|/*&n; * ioremap support - validate a PCI memory address,&n; * and convert a PCI memory address to a physical&n; * address for the page tables.&n; */
DECL|macro|valid_ioaddr
mdefine_line|#define valid_ioaddr(iomem,size) ((iomem) &lt; 0x80000000 &amp;&amp; (iomem) + (size) &lt;= 0x80000000)
DECL|macro|io_to_phys
mdefine_line|#define io_to_phys(iomem)&t; ((iomem) + DC21285_PCI_MEM)
multiline_comment|/*&n; * Fudge up IO addresses by this much.  Once we&squot;re confident that nobody&n; * is using read*() and so on with addresses they didn&squot;t get from ioremap&n; * this can go away.&n; */
DECL|macro|IO_FUDGE_FACTOR
mdefine_line|#define IO_FUDGE_FACTOR&t;&t;PCIMEM_BASE
DECL|macro|__pci_mem_addr
mdefine_line|#define __pci_mem_addr(x)&t;((void *)(IO_FUDGE_FACTOR + (unsigned long)(x)))
multiline_comment|/*&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt&n; */
DECL|macro|ioremap
mdefine_line|#define ioremap(iomem_addr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _addr = (iomem_addr), _size = (size);&t;&t;&bslash;&n;&t;void *_ret = NULL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (valid_ioaddr(_addr, _size)) {&t;&t;&t;&t;&bslash;&n;&t;&t;_addr = io_to_phys(_addr);&t;&t;&t;&t;&bslash;&n;&t;&t;_ret = __ioremap(_addr, _size, 0) - IO_FUDGE_FACTOR;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_ret; })
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(iomem_addr,size) ioremap((iomem_addr),(size))
DECL|macro|iounmap
mdefine_line|#define iounmap(_addr)&t;do { __iounmap(__pci_mem_addr((_addr))); } while (0)
DECL|macro|readb
mdefine_line|#define readb(addr)&t;(*(volatile unsigned char *)__pci_mem_addr(addr))
DECL|macro|readw
mdefine_line|#define readw(addr)&t;(*(volatile unsigned short *)__pci_mem_addr(addr))
DECL|macro|readl
mdefine_line|#define readl(addr)&t;(*(volatile unsigned long *)__pci_mem_addr(addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr)&t;(*(volatile unsigned char *)__pci_mem_addr(addr) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr)&t;(*(volatile unsigned short *)__pci_mem_addr(addr) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr)&t;(*(volatile unsigned long *)__pci_mem_addr(addr) = (b))
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset(__pci_mem_addr(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),__pci_mem_addr(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy(__pci_mem_addr(a),(b),(c))
DECL|macro|eth_io_copy_and_sum
mdefine_line|#define eth_io_copy_and_sum(a,b,c,d) eth_copy_and_sum((a),__pci_mem_addr(b),(c),(d))
macro_line|#endif
eof
