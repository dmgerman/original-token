multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/io.h&n; *&n; * Copyright (C) 1997-1999 Russell King&n; *&n; * Modifications:&n; *  06-12-1997&t;RMK&t;Created.&n; *  07-04-1999&t;RMK&t;Major cleanup&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
multiline_comment|/*&n; * This architecture does not require any delayed IO&n; */
DECL|macro|ARCH_IO_DELAY
macro_line|#undef&t;ARCH_IO_DELAY
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
macro_line|#endif
eof
