multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa285/io.h&n; *&n; * Copyright (C) 1997,1998 Russell King&n; *&n; * Modifications:&n; *  06-Dec-1997&t;RMK&t;Created.&n; */
macro_line|#ifndef __ASM_ARM_ARCH_IO_H
DECL|macro|__ASM_ARM_ARCH_IO_H
mdefine_line|#define __ASM_ARM_ARCH_IO_H
macro_line|#include &lt;asm/dec21285.h&gt;
multiline_comment|/*&n; * This architecture does not require any delayed IO, and&n; * has the constant-optimised IO&n; */
DECL|macro|ARCH_IO_DELAY
macro_line|#undef&t;ARCH_IO_DELAY
DECL|macro|ARCH_READWRITE
mdefine_line|#define ARCH_READWRITE
multiline_comment|/*&n; * Dynamic IO functions - let the compiler&n; * optimize the expressions&n; */
DECL|macro|DECLARE_DYN_OUT
mdefine_line|#define DECLARE_DYN_OUT(fnsuffix,instr,typ)&t;&t;&t;&t;&bslash;&n;extern __inline__ void&t;&t;&t;&t;&t;&t;&t;&bslash;&n;__out##fnsuffix (unsigned int value, unsigned int port)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str%?&quot; ##instr## &quot;&t;%0, [%1, %2]&t;@ out&quot;###fnsuffix&t;&bslash;&n;&t;: &t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), typ (port));&t;&t;&t;&bslash;&n;}
DECL|macro|DECLARE_DYN_IN
mdefine_line|#define DECLARE_DYN_IN(sz,fnsuffix,instr,typ)&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned sz&t;&t;&t;&t;&t;&t;&bslash;&n;__in##fnsuffix (unsigned int port)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long value;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr%?&quot; ##instr## &quot;&t;%0, [%1, %2]&t;@ in&quot;###fnsuffix&t;&bslash;&n;&t;: &quot;=&amp;r&quot; (value)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), typ (port));&t;&t;&t;&t;&t;&bslash;&n;&t;return (unsigned sz)value;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|function|__ioaddr
r_extern
id|__inline__
r_int
r_int
id|__ioaddr
(paren
r_int
r_int
id|port
)paren
"&bslash;"
(brace
"&bslash;"
r_return
(paren
r_int
r_int
)paren
(paren
id|PCIO_BASE
op_plus
id|port
)paren
suffix:semicolon
"&bslash;"
)brace
DECL|macro|DECLARE_IO
mdefine_line|#define DECLARE_IO(sz,fnsuffix,instr,typ)&t;&bslash;&n;&t;DECLARE_DYN_OUT(fnsuffix,instr,typ)&t;&bslash;&n;&t;DECLARE_DYN_IN(sz,fnsuffix,instr,typ)
id|DECLARE_IO
c_func
(paren
r_char
comma
id|b
comma
l_string|&quot;b&quot;
comma
l_string|&quot;Jr&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|w
comma
l_string|&quot;h&quot;
comma
l_string|&quot;r&quot;
)paren
id|DECLARE_IO
c_func
(paren
r_int
comma
id|l
comma
l_string|&quot;&quot;
comma
l_string|&quot;Jr&quot;
)paren
DECL|macro|DECLARE_IO
macro_line|#undef DECLARE_IO
DECL|macro|DECLARE_DYN_OUT
macro_line|#undef DECLARE_DYN_OUT
DECL|macro|DECLARE_DYN_IN
macro_line|#undef DECLARE_DYN_IN
multiline_comment|/*&n; * Constant address IO functions&n; *&n; * These have to be macros for the &squot;J&squot; constraint to work -&n; * +/-4096 immediate operand.&n; */
DECL|macro|__outbc
mdefine_line|#define __outbc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str%?b&t;%0, [%1, %2]&t;&t;&t;&t;@ outbc&quot;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&bslash;&n;})
DECL|macro|__inbc
mdefine_line|#define __inbc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned char result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr%?b&t;%0, [%1, %2]&t;&t;&t;&t;@ inbc&quot;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outwc
mdefine_line|#define __outwc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str%?h&t;%0, [%1, %2]&t;&t;&t;&t;@ outwc&quot;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port));&t;&t;&t;&bslash;&n;})
DECL|macro|__inwc
mdefine_line|#define __inwc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned short result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr%?h&t;%0, [%1, %2]&t;&t;&t;&t;@ inwc&quot;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;r&quot; (port));&t;&t;&t;&t;&t;&bslash;&n;&t;result &amp; 0xffff;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__outlc
mdefine_line|#define __outlc(value,port)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;str%?&t;%0, [%1, %2]&t;&t;&t;&t;@ outlc&quot;&t;&bslash;&n;&t;:&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (value), &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&bslash;&n;})
DECL|macro|__inlc
mdefine_line|#define __inlc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long result;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;ldr%?&t;%0, [%1, %2]&t;&t;&t;&t;@ inlc&quot;&t;&t;&bslash;&n;&t;: &quot;=r&quot; (result)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;: &quot;r&quot; (PCIO_BASE), &quot;Jr&quot; (port));&t;&t;&t;&t;&bslash;&n;&t;result;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__ioaddrc
mdefine_line|#define __ioaddrc(port)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long addr;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;addr = PCIO_BASE + port;&t;&t;&t;&t;&t;&bslash;&n;&t;addr;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
multiline_comment|/*&n; * Translated address IO functions&n; *&n; * IO address has already been translated to a virtual address&n; */
DECL|macro|outb_t
mdefine_line|#define outb_t(v,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p) = (v))
DECL|macro|inb_t
mdefine_line|#define inb_t(p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned char *)(p))
DECL|macro|outl_t
mdefine_line|#define outl_t(v,p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p) = (v))
DECL|macro|inl_t
mdefine_line|#define inl_t(p)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(*(volatile unsigned long *)(p))
multiline_comment|/*&n; * ioremap support - validate a PCI memory address,&n; * and convert a PCI memory address to a physical&n; * address for the page tables.&n; */
DECL|macro|valid_ioaddr
mdefine_line|#define valid_ioaddr(iomem,size) ((iomem) &lt; 0x80000000 &amp;&amp; (iomem) + (size) &lt;= 0x80000000)
DECL|macro|io_to_phys
mdefine_line|#define io_to_phys(iomem)&t;((iomem) + DC21285_PCI_MEM)
multiline_comment|/*&n; * Fudge up IO addresses by this much.  Once we&squot;re confident that nobody&n; * is using read*() and so on with addresses they didn&squot;t get from ioremap&n; * this can go away.&n; */
DECL|macro|IO_FUDGE_FACTOR
mdefine_line|#define IO_FUDGE_FACTOR&t;&t;PCIMEM_BASE
multiline_comment|/*&n; * ioremap takes a PCI memory address, as specified in&n; * linux/Documentation/IO-mapping.txt&n; */
DECL|macro|ioremap
mdefine_line|#define ioremap(iomem_addr,size)&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _addr = (iomem_addr), _size = (size);&t;&t;&bslash;&n;&t;void *_ret = NULL;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (valid_ioaddr(_addr, _size)) {&t;&t;&t;&t;&bslash;&n;&t;&t;_addr = io_to_phys(_addr);&t;&t;&t;&t;&bslash;&n;&t;&t;_ret = __ioremap(_addr, _size, 0) - IO_FUDGE_FACTOR;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_ret; })
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(iomem_addr,size) ioremap((iomem_addr),(size))
r_extern
r_void
id|iounmap
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
DECL|macro|DECLARE_PCI_WRITE
mdefine_line|#define DECLARE_PCI_WRITE(typ,fnsuffix)&t;&t;&t;&t;&t;&bslash;&n;static inline void write##fnsuffix(unsigned typ val, unsigned int addr)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;*(volatile unsigned typ *)(IO_FUDGE_FACTOR + addr) = val;&t;&bslash;&n;}
DECL|macro|DECLARE_PCI_READ
mdefine_line|#define DECLARE_PCI_READ(typ,fnsuffix)&t;&t;&t;&t;&t;&bslash;&n;static inline unsigned typ read##fnsuffix (unsigned int addr)&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;return *(volatile unsigned typ *)(IO_FUDGE_FACTOR + addr);&t;&bslash;&n;}
DECL|macro|DECLARE_PCI
mdefine_line|#define DECLARE_PCI(typ,fnsuffix)&t;&t;&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_WRITE(typ,fnsuffix)&t;&t;&t;&t;&t;&bslash;&n;&t;DECLARE_PCI_READ(typ,fnsuffix)
id|DECLARE_PCI
c_func
(paren
r_char
comma
id|b
)paren
id|DECLARE_PCI
c_func
(paren
r_int
comma
id|w
)paren
id|DECLARE_PCI
c_func
(paren
r_int
comma
id|l
)paren
DECL|macro|DECLARE_PCI
macro_line|#undef DECLARE_PCI
DECL|macro|DECLARE_PCI_READ
macro_line|#undef DECLARE_PCI_READ
DECL|macro|DECLARE_PCI_WRITE
macro_line|#undef DECLARE_PCI_WRITE
macro_line|#endif
eof
