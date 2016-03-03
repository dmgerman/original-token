macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_IO_H
DECL|macro|_PPC_IO_H
mdefine_line|#define _PPC_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|SIO_CONFIG_RA
mdefine_line|#define SIO_CONFIG_RA&t;0x398
DECL|macro|SIO_CONFIG_RD
mdefine_line|#define SIO_CONFIG_RD&t;0x399
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
DECL|macro|PMAC_ISA_MEM_BASE
mdefine_line|#define PMAC_ISA_MEM_BASE &t;0
DECL|macro|PMAC_PCI_DRAM_OFFSET
mdefine_line|#define PMAC_PCI_DRAM_OFFSET &t;0
DECL|macro|CHRP_ISA_IO_BASE
mdefine_line|#define CHRP_ISA_IO_BASE &t;0xf8000000
DECL|macro|CHRP_ISA_MEM_BASE
mdefine_line|#define CHRP_ISA_MEM_BASE &t;0xf7000000
DECL|macro|CHRP_PCI_DRAM_OFFSET
mdefine_line|#define CHRP_PCI_DRAM_OFFSET &t;0
DECL|macro|PREP_ISA_IO_BASE
mdefine_line|#define PREP_ISA_IO_BASE &t;0x80000000
DECL|macro|PREP_ISA_MEM_BASE
mdefine_line|#define PREP_ISA_MEM_BASE &t;0xc0000000
DECL|macro|PREP_PCI_DRAM_OFFSET
mdefine_line|#define PREP_PCI_DRAM_OFFSET &t;0x80000000
macro_line|#if defined(CONFIG_4xx)
macro_line|#include &lt;asm/board.h&gt;
macro_line|#elif defined(CONFIG_8xx)
macro_line|#include &lt;asm/mpc8xx.h&gt;
macro_line|#elif defined(CONFIG_8260)
macro_line|#include &lt;asm/mpc8260.h&gt;
macro_line|#else /* 4xx/8xx/8260 */
macro_line|#ifdef CONFIG_APUS
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE 0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE 0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET 0
macro_line|#else /* CONFIG_APUS */
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
r_extern
r_int
r_int
id|isa_mem_base
suffix:semicolon
r_extern
r_int
r_int
id|pci_dram_offset
suffix:semicolon
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;isa_io_base
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;isa_mem_base
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;pci_dram_offset
macro_line|#endif /* CONFIG_APUS */
macro_line|#endif
DECL|macro|readb
mdefine_line|#define readb(addr) in_8((volatile u8 *)(addr))
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) out_8((volatile u8 *)(addr), (b))
macro_line|#if defined(CONFIG_APUS)
DECL|macro|readw
mdefine_line|#define readw(addr) (*(volatile u16 *) (addr))
DECL|macro|readl
mdefine_line|#define readl(addr) (*(volatile u32 *) (addr))
DECL|macro|writew
mdefine_line|#define writew(b,addr) ((*(volatile u16 *) (addr)) = (b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) ((*(volatile u32 *) (addr)) = (b))
macro_line|#else
DECL|macro|readw
mdefine_line|#define readw(addr) in_le16((volatile u16 *)(addr))
DECL|macro|readl
mdefine_line|#define readl(addr) in_le32((volatile u32 *)(addr))
DECL|macro|writew
mdefine_line|#define writew(b,addr) out_le16((volatile u16 *)(addr),(b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) out_le32((volatile u32 *)(addr),(b))
macro_line|#endif
DECL|macro|__raw_readb
mdefine_line|#define __raw_readb(addr)&t;(*(volatile unsigned char *)(addr))
DECL|macro|__raw_readw
mdefine_line|#define __raw_readw(addr)&t;(*(volatile unsigned short *)(addr))
DECL|macro|__raw_readl
mdefine_line|#define __raw_readl(addr)&t;(*(volatile unsigned int *)(addr))
DECL|macro|__raw_writeb
mdefine_line|#define __raw_writeb(v, addr)&t;(*(volatile unsigned char *)(addr) = (v))
DECL|macro|__raw_writew
mdefine_line|#define __raw_writew(v, addr)&t;(*(volatile unsigned short *)(addr) = (v))
DECL|macro|__raw_writel
mdefine_line|#define __raw_writel(v, addr)&t;(*(volatile unsigned int *)(addr) = (v))
multiline_comment|/*&n; * The insw/outsw/insl/outsl macros don&squot;t do byte-swapping.&n; * They are only used in practice for transferring buffers which&n; * are arrays of bytes, and byte-swapping is not appropriate in&n; * that case.  - paulus&n; */
DECL|macro|insb
mdefine_line|#define insb(port, buf, ns)&t;_insb((u8 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|outsb
mdefine_line|#define outsb(port, buf, ns)&t;_outsb((u8 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns)&t;_insw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns)&t;_outsw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|insl
mdefine_line|#define insl(port, buf, nl)&t;_insl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
DECL|macro|outsl
mdefine_line|#define outsl(port, buf, nl)&t;_outsl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
macro_line|#ifdef CONFIG_ALL_PPC
multiline_comment|/*&n; * We have to handle possible machine checks here on powermacs&n; * and potentially some CHRPs -- paulus.&n; */
DECL|macro|__do_in_asm
mdefine_line|#define __do_in_asm(name, op)&t;&t;&t;&t;&bslash;&n;extern __inline__ unsigned int name(unsigned int port)&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int x;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;op &quot; %0,0,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;sync&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;3:&t;li&t;%0,-1&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;b&t;2b&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;.previous&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;1b,3b&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;=&amp;r&quot; (x)&t;&t;&t;&t;&bslash;&n;&t;&t;: &quot;r&quot; (port + _IO_BASE));&t;&t;&bslash;&n;&t;return x;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|__do_out_asm
mdefine_line|#define __do_out_asm(name, op)&t;&t;&t;&t;&bslash;&n;extern __inline__ void name(unsigned int val, unsigned int port) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&t;op &quot; %0,0,%1&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;1:&t;sync&bslash;n&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;2:&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;&t;.align&t;2&bslash;n&quot;&t;&t;&t;&bslash;&n;&t;&t;&quot;&t;.long&t;1b,2b&bslash;n&quot;&t;&t;&bslash;&n;&t;&t;&quot;.previous&quot;&t;&t;&t;&t;&bslash;&n;&t;&t;: : &quot;r&quot; (val), &quot;r&quot; (port + _IO_BASE));&t;&bslash;&n;}
id|__do_in_asm
c_func
(paren
id|inb
comma
l_string|&quot;lbzx&quot;
)paren
id|__do_in_asm
c_func
(paren
id|inw
comma
l_string|&quot;lhbrx&quot;
)paren
id|__do_in_asm
c_func
(paren
id|inl
comma
l_string|&quot;lwbrx&quot;
)paren
id|__do_out_asm
c_func
(paren
id|outb
comma
l_string|&quot;stbx&quot;
)paren
id|__do_out_asm
c_func
(paren
id|outw
comma
l_string|&quot;sthbrx&quot;
)paren
id|__do_out_asm
c_func
(paren
id|outl
comma
l_string|&quot;stwbrx&quot;
)paren
macro_line|#elif defined(CONFIG_APUS)
mdefine_line|#define inb(port)&t;&t;in_8((u8 *)((port)+_IO_BASE))
mdefine_line|#define outb(val, port)&t;&t;out_8((u8 *)((port)+_IO_BASE), (val))
mdefine_line|#define inw(port)&t;&t;in_be16((u16 *)((port)+_IO_BASE))
mdefine_line|#define outw(val, port)&t;&t;out_be16((u16 *)((port)+_IO_BASE), (val))
mdefine_line|#define inl(port)&t;&t;in_be32((u32 *)((port)+_IO_BASE))
mdefine_line|#define outl(val, port)&t;&t;out_be32((u32 *)((port)+_IO_BASE), (val))
macro_line|#else /* not APUS or ALL_PPC */
mdefine_line|#define inb(port)&t;&t;in_8((u8 *)((port)+_IO_BASE))
mdefine_line|#define outb(val, port)&t;&t;out_8((u8 *)((port)+_IO_BASE), (val))
mdefine_line|#define inw(port)&t;&t;in_le16((u16 *)((port)+_IO_BASE))
mdefine_line|#define outw(val, port)&t;&t;out_le16((u16 *)((port)+_IO_BASE), (val))
mdefine_line|#define inl(port)&t;&t;in_le32((u32 *)((port)+_IO_BASE))
mdefine_line|#define outl(val, port)&t;&t;out_le32((u32 *)((port)+_IO_BASE), (val))
macro_line|#endif
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;inb((port))
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)&t;outb((val), (port))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;inw((port))
DECL|macro|outw_p
mdefine_line|#define outw_p(val, port)&t;outw((val), (port))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;inl((port))
DECL|macro|outl_p
mdefine_line|#define outl_p(val, port)&t;outl((val), (port))
r_extern
r_void
id|_insb
c_func
(paren
r_volatile
id|u8
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsb
c_func
(paren
r_volatile
id|u8
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insw
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsw
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insl
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_outsl
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_insw_ns
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_outsw_ns
c_func
(paren
r_volatile
id|u16
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|ns
)paren
suffix:semicolon
r_extern
r_void
id|_insl_ns
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
r_extern
r_void
id|_outsl_ns
c_func
(paren
r_volatile
id|u32
op_star
id|port
comma
r_const
r_void
op_star
id|buf
comma
r_int
id|nl
)paren
suffix:semicolon
multiline_comment|/*&n; * The *_ns versions below don&squot;t do byte-swapping.&n; * Neither do the standard versions now, these are just here&n; * for older code.&n; */
DECL|macro|insw_ns
mdefine_line|#define insw_ns(port, buf, ns)&t;_insw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|outsw_ns
mdefine_line|#define outsw_ns(port, buf, ns)&t;_outsw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|insl_ns
mdefine_line|#define insl_ns(port, buf, nl)&t;_insl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
DECL|macro|outsl_ns
mdefine_line|#define outsl_ns(port, buf, nl)&t;_outsl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT ~0
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)       memset((void *)(a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)   memcpy((a),(void *)(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((void *)(a),(b),(c))
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Map in an area of physical address space, for accessing&n; * I/O devices etc.&n; */
r_extern
r_void
op_star
id|__ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__ioremap_at
c_func
(paren
r_int
r_int
id|phys
comma
r_int
r_int
id|size
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
r_extern
r_void
op_star
id|ioremap
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|macro|ioremap_nocache
mdefine_line|#define ioremap_nocache(addr, size)&t;ioremap((addr), (size))
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
r_extern
r_int
r_int
id|iopa
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_APUS
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
macro_line|#endif
multiline_comment|/*&n; * The PCI bus is inherently Little-Endian.  The PowerPC is being&n; * run Big-Endian.  Thus all values which cross the [PCI] barrier&n; * must be endian-adjusted.  Also, the local DRAM has a different&n; * address from the PCI point of view, thus buffer addresses also&n; * have to be modified [mapped] appropriately.&n; */
DECL|function|virt_to_bus
r_extern
r_inline
r_int
r_int
id|virt_to_bus
c_func
(paren
r_volatile
r_void
op_star
id|address
)paren
(brace
macro_line|#ifndef CONFIG_APUS
r_if
c_cond
(paren
id|address
op_eq
(paren
r_void
op_star
)paren
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|KERNELBASE
op_plus
id|PCI_DRAM_OFFSET
suffix:semicolon
macro_line|#else
r_return
id|iopa
(paren
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|bus_to_virt
r_extern
r_inline
r_void
op_star
id|bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
macro_line|#ifndef CONFIG_APUS
r_if
c_cond
(paren
id|address
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|address
op_minus
id|PCI_DRAM_OFFSET
op_plus
id|KERNELBASE
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
r_void
op_star
)paren
id|mm_ptov
(paren
id|address
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * The PCI bus bridge can translate addresses issued by the processor(s)&n; * into a different address on the PCI bus.  On 32-bit cpus, we assume&n; * this mapping is 1-1, but on 64-bit systems it often isn&squot;t.&n; */
macro_line|#ifndef CONFIG_PPC64BRIDGE
DECL|macro|phys_to_bus
mdefine_line|#define phys_to_bus(x)&t;(x)
DECL|macro|bus_to_phys
mdefine_line|#define bus_to_phys(x)&t;(x)
macro_line|#else
r_extern
r_int
r_int
id|phys_to_bus
c_func
(paren
r_int
r_int
id|pa
)paren
suffix:semicolon
r_extern
r_int
r_int
id|bus_to_phys
c_func
(paren
r_int
r_int
id|ba
comma
r_int
id|busnr
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PPC64BRIDGE */
multiline_comment|/*&n; * Change virtual addresses to physical addresses and vv, for&n; * addresses in the area where the kernel has the RAM mapped.&n; */
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
macro_line|#ifndef CONFIG_APUS
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|KERNELBASE
suffix:semicolon
macro_line|#else
r_return
id|iopa
(paren
(paren
r_int
r_int
)paren
id|address
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#ifndef CONFIG_APUS
r_return
(paren
r_void
op_star
)paren
(paren
id|address
op_plus
id|KERNELBASE
)paren
suffix:semicolon
macro_line|#else
r_return
(paren
r_void
op_star
)paren
id|mm_ptov
(paren
id|address
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n; * Enforce In-order Execution of I/O:&n; * Acts as a barrier to ensure all previous I/O accesses have&n; * completed before any further ones are issued.&n; */
DECL|function|eieio
r_extern
r_inline
r_void
id|eieio
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Enforce in-order execution of data I/O. &n; * No distinction between read/write on PPC; use eieio for all three.&n; */
DECL|macro|iobarrier_rw
mdefine_line|#define iobarrier_rw() eieio()
DECL|macro|iobarrier_r
mdefine_line|#define iobarrier_r()  eieio()
DECL|macro|iobarrier_w
mdefine_line|#define iobarrier_w()  eieio()
multiline_comment|/*&n; * 8, 16 and 32 bit, big and little endian I/O operations, with barrier.&n; */
DECL|function|in_8
r_extern
r_inline
r_int
id|in_8
c_func
(paren
r_volatile
r_int
r_char
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lbz%U1%X1 %0,%1; eieio&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_8
r_extern
r_inline
r_void
id|out_8
c_func
(paren
r_volatile
r_int
r_char
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stb%U0%X0 %1,%0; eieio&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|in_le16
r_extern
r_inline
r_int
id|in_le16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lhbrx %0,0,%1; eieio&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|in_be16
r_extern
r_inline
r_int
id|in_be16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lhz%U1%X1 %0,%1; eieio&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_le16
r_extern
r_inline
r_void
id|out_le16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sthbrx %1,0,%2; eieio&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out_be16
r_extern
r_inline
r_void
id|out_be16
c_func
(paren
r_volatile
r_int
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sth%U0%X0 %1,%0; eieio&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|in_le32
r_extern
r_inline
r_int
id|in_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lwbrx %0,0,%1; eieio&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|in_be32
r_extern
r_inline
r_int
id|in_be32
c_func
(paren
r_volatile
r_int
op_star
id|addr
)paren
(brace
r_int
id|ret
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lwz%U1%X1 %0,%1; eieio&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ret
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|addr
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|out_le32
r_extern
r_inline
r_void
id|out_le32
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stwbrx %1,0,%2; eieio&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
comma
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|out_be32
r_extern
r_inline
r_void
id|out_be32
c_func
(paren
r_volatile
r_int
op_star
id|addr
comma
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;stw%U0%X0 %1,%0; eieio&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|addr
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|check_signature
r_static
r_inline
r_int
id|check_signature
c_func
(paren
r_int
r_int
id|io_addr
comma
r_const
r_int
r_char
op_star
id|signature
comma
r_int
id|length
)paren
(brace
r_int
id|retval
op_assign
l_int|0
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|readb
c_func
(paren
id|io_addr
)paren
op_ne
op_star
id|signature
)paren
r_goto
id|out
suffix:semicolon
id|io_addr
op_increment
suffix:semicolon
id|signature
op_increment
suffix:semicolon
id|length
op_decrement
suffix:semicolon
)brace
r_while
c_loop
(paren
id|length
)paren
suffix:semicolon
id|retval
op_assign
l_int|1
suffix:semicolon
id|out
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Nothing to do */
DECL|macro|dma_cache_inv
mdefine_line|#define dma_cache_inv(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback
mdefine_line|#define dma_cache_wback(_start,_size)&t;&t;do { } while (0)
DECL|macro|dma_cache_wback_inv
mdefine_line|#define dma_cache_wback_inv(_start,_size)&t;do { } while (0)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
eof
