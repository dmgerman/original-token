macro_line|#ifndef _PPC_IO_H
DECL|macro|_PPC_IO_H
mdefine_line|#define _PPC_IO_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
multiline_comment|/* from the Carolina Technical Spec -- Cort */
DECL|macro|IBM_ACORN
mdefine_line|#define IBM_ACORN 0x82A
DECL|macro|SIO_CONFIG_RA
mdefine_line|#define SIO_CONFIG_RA&t;0x398
DECL|macro|SIO_CONFIG_RD
mdefine_line|#define SIO_CONFIG_RD&t;0x399
DECL|macro|IBM_HDD_LED
mdefine_line|#define IBM_HDD_LED       0x808
DECL|macro|IBM_EQUIP_PRESENT
mdefine_line|#define IBM_EQUIP_PRESENT 0x80c&t;
DECL|macro|IBM_L2_STATUS
mdefine_line|#define IBM_L2_STATUS     0x80d
DECL|macro|IBM_L2_INVALIDATE
mdefine_line|#define IBM_L2_INVALIDATE 0x814
DECL|macro|IBM_SYS_CTL
mdefine_line|#define IBM_SYS_CTL       0x81c
DECL|macro|SLOW_DOWN_IO
mdefine_line|#define SLOW_DOWN_IO
DECL|macro|PMAC_ISA_IO_BASE
mdefine_line|#define PMAC_ISA_IO_BASE &t;0
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
mdefine_line|#define PREP_ISA_MEM_BASE &t;0xd0000000
multiline_comment|/*#define PREP_ISA_MEM_BASE &t;0xc0000000*/
DECL|macro|PREP_PCI_DRAM_OFFSET
mdefine_line|#define PREP_PCI_DRAM_OFFSET &t;0x80000000
macro_line|#if defined(CONFIG_MACH_SPECIFIC)
macro_line|#ifdef CONFIG_PREP
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;PREP_ISA_IO_BASE
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;PREP_ISA_MEM_BASE
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET PREP_PCI_DRAM_OFFSET
macro_line|#endif /* CONFIG_PREP */
macro_line|#ifdef CONFIG_CHRP
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;CHRP_ISA_IO_BASE
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;CHRP_ISA_MEM_BASE
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET CHRP_PCI_DRAM_OFFSET
macro_line|#endif /* CONFIG_CHRP */
macro_line|#ifdef CONFIG_PMAC
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;PMAC_ISA_IO_BASE
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;PMAC_ISA_MEM_BASE
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET PMAC_PCI_DRAM_OFFSET
macro_line|#endif /* CONFIG_PMAC */
macro_line|#else /* CONFIG_MACH_SPECIFIC */
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE isa_io_base
r_extern
r_int
r_int
id|isa_mem_base
suffix:semicolon
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE isa_mem_base
DECL|macro|PCI_DRAM_OFFSET
macro_line|#undef PCI_DRAM_OFFSET
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET  pci_dram_offset
r_extern
r_int
r_int
id|pci_dram_offset
suffix:semicolon
macro_line|#endif /* CONFIG_MACH_SPECIFIC */
DECL|macro|readb
mdefine_line|#define readb(addr) (*(volatile unsigned char *) (addr))
DECL|macro|readw
mdefine_line|#define readw(addr) ld_le16((volatile unsigned short *)(addr))
DECL|macro|readl
mdefine_line|#define readl(addr) ld_le32((volatile unsigned *)addr)
DECL|macro|writeb
mdefine_line|#define writeb(b,addr) ((*(volatile unsigned char *) (addr)) = (b))
DECL|macro|writew
mdefine_line|#define writew(b,addr) st_le16((volatile unsigned short *)(addr),(b))
DECL|macro|writel
mdefine_line|#define writel(b,addr) st_le32((volatile unsigned *)(addr),(b))
DECL|macro|insb
mdefine_line|#define insb(port, buf, ns)&t;_insb((unsigned char *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|outsb
mdefine_line|#define outsb(port, buf, ns)&t;_outsb((unsigned char *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|insw
mdefine_line|#define insw(port, buf, ns)&t;_insw((unsigned short *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|outsw
mdefine_line|#define outsw(port, buf, ns)&t;_outsw((unsigned short *)((port)+_IO_BASE), (buf), (ns))
DECL|macro|insl
mdefine_line|#define insl(port, buf, nl)&t;_insl((unsigned long *)((port)+_IO_BASE), (buf), (nl))
DECL|macro|outsl
mdefine_line|#define outsl(port, buf, nl)&t;_outsl((unsigned long *)((port)+_IO_BASE), (buf), (nl))
DECL|macro|inb
mdefine_line|#define inb(port)&t;&t;in_8((unsigned char *)((port)+_IO_BASE))
DECL|macro|outb
mdefine_line|#define outb(val, port)&t;&t;out_8((unsigned char *)((port)+_IO_BASE), (val))
DECL|macro|inw
mdefine_line|#define inw(port)&t;&t;in_le16((unsigned short *)((port)+_IO_BASE))
DECL|macro|outw
mdefine_line|#define outw(val, port)&t;&t;out_le16((unsigned short *)((port)+_IO_BASE), (val))
DECL|macro|inl
mdefine_line|#define inl(port)&t;&t;in_le32((unsigned *)((port)+_IO_BASE))
DECL|macro|outl
mdefine_line|#define outl(val, port)&t;&t;out_le32((unsigned *)((port)+_IO_BASE), (val))
DECL|macro|inb_p
mdefine_line|#define inb_p(port)&t;&t;in_8((unsigned char *)((port)+_IO_BASE))
DECL|macro|outb_p
mdefine_line|#define outb_p(val, port)&t;out_8((unsigned char *)((port)+_IO_BASE), (val))
DECL|macro|inw_p
mdefine_line|#define inw_p(port)&t;&t;in_le16((unsigned short *)((port)+_IO_BASE))
DECL|macro|outw_p
mdefine_line|#define outw_p(val, port)&t;out_le16((unsigned short *)((port)+_IO_BASE), (val))
DECL|macro|inl_p
mdefine_line|#define inl_p(port)&t;&t;in_le32(((unsigned *)(port)+_IO_BASE))
DECL|macro|outl_p
mdefine_line|#define outl_p(val, port)&t;out_le32((unsigned *)((port)+_IO_BASE), (val))
r_extern
r_void
id|_insb
c_func
(paren
r_volatile
r_int
r_char
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
r_int
r_char
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
DECL|macro|memset_io
mdefine_line|#define memset_io(a,b,c)&t;memset((a),(b),(c))
DECL|macro|memcpy_fromio
mdefine_line|#define memcpy_fromio(a,b,c)&t;memcpy((a),(b),(c))
DECL|macro|memcpy_toio
mdefine_line|#define memcpy_toio(a,b,c)&t;memcpy((a),(b),(c))
macro_line|#ifdef __KERNEL__
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
)brace
multiline_comment|/*&n; * Map in an area of physical address space, for accessing&n; * I/O devices etc.&n; */
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
r_extern
r_void
id|iounmap
c_func
(paren
r_int
r_int
op_star
id|addr
)paren
suffix:semicolon
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
r_return
(paren
r_int
r_int
)paren
id|address
op_minus
id|KERNELBASE
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
(paren
id|address
op_plus
id|KERNELBASE
)paren
suffix:semicolon
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
id|asm
r_volatile
(paren
l_string|&quot;eieio&quot;
suffix:colon
suffix:colon
)paren
suffix:semicolon
)brace
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
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|eieio
c_func
(paren
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
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|eieio
c_func
(paren
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
id|ret
op_assign
id|ld_le16
c_func
(paren
id|addr
)paren
suffix:semicolon
id|eieio
c_func
(paren
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
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|eieio
c_func
(paren
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
id|st_le16
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
id|eieio
c_func
(paren
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
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|eieio
c_func
(paren
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
id|ret
op_assign
id|ld_le32
c_func
(paren
id|addr
)paren
suffix:semicolon
id|eieio
c_func
(paren
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
id|ret
op_assign
op_star
id|addr
suffix:semicolon
id|eieio
c_func
(paren
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
id|st_le32
c_func
(paren
id|addr
comma
id|val
)paren
suffix:semicolon
id|eieio
c_func
(paren
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
op_star
id|addr
op_assign
id|val
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
