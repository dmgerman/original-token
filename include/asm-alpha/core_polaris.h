macro_line|#ifndef __ALPHA_POLARIS__H__
DECL|macro|__ALPHA_POLARIS__H__
mdefine_line|#define __ALPHA_POLARIS__H__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/compiler.h&gt;
multiline_comment|/*&n; * POLARIS is the internal name for a core logic chipset which provides&n; * memory controller and PCI access for the 21164PC chip based systems.&n; *&n; * This file is based on:&n; *&n; * Polaris System Controller&n; * Device Functional Specification&n; * 22-Jan-98&n; * Rev. 4.2&n; *&n; */
multiline_comment|/* Polaris memory regions */
DECL|macro|POLARIS_SPARSE_MEM_BASE
mdefine_line|#define&t;&t;POLARIS_SPARSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf800000000)
DECL|macro|POLARIS_DENSE_MEM_BASE
mdefine_line|#define&t;&t;POLARIS_DENSE_MEM_BASE&t;&t;(IDENT_ADDR + 0xf900000000)
DECL|macro|POLARIS_SPARSE_IO_BASE
mdefine_line|#define &t;POLARIS_SPARSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf980000000)
DECL|macro|POLARIS_SPARSE_CONFIG_BASE
mdefine_line|#define&t;&t;POLARIS_SPARSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9c0000000)
DECL|macro|POLARIS_IACK_BASE
mdefine_line|#define&t;&t;POLARIS_IACK_BASE&t;&t;(IDENT_ADDR + 0xf9f8000000)
DECL|macro|POLARIS_DENSE_IO_BASE
mdefine_line|#define&t;&t;POLARIS_DENSE_IO_BASE&t;&t;(IDENT_ADDR + 0xf9fc000000)
DECL|macro|POLARIS_DENSE_CONFIG_BASE
mdefine_line|#define&t;&t;POLARIS_DENSE_CONFIG_BASE&t;(IDENT_ADDR + 0xf9fe000000)
DECL|macro|POLARIS_IACK_SC
mdefine_line|#define&t;&t;POLARIS_IACK_SC&t;&t;&t;POLARIS_IACK_BASE
multiline_comment|/* The Polaris command/status registers live in PCI Config space for&n; * bus 0/device 0.  As such, they may be bytes, words, or doublewords.&n; */
DECL|macro|POLARIS_W_VENID
mdefine_line|#define&t;&t;POLARIS_W_VENID&t;&t;(POLARIS_DENSE_CONFIG_BASE)
DECL|macro|POLARIS_W_DEVID
mdefine_line|#define&t;&t;POLARIS_W_DEVID&t;&t;(POLARIS_DENSE_CONFIG_BASE+2)
DECL|macro|POLARIS_W_CMD
mdefine_line|#define&t;&t;POLARIS_W_CMD&t;&t;(POLARIS_DENSE_CONFIG_BASE+4)
DECL|macro|POLARIS_W_STATUS
mdefine_line|#define&t;&t;POLARIS_W_STATUS&t;(POLARIS_DENSE_CONFIG_BASE+6)
multiline_comment|/* No HAE address.  Polaris has no concept of an HAE, since it&n; * supports transfers of all sizes in dense space.&n; */
DECL|macro|POLARIS_DMA_WIN_BASE_DEFAULT
mdefine_line|#define POLARIS_DMA_WIN_BASE_DEFAULT&t;0x80000000&t;/* fixed, 2G @ 2G */
DECL|macro|POLARIS_DMA_WIN_SIZE_DEFAULT
mdefine_line|#define POLARIS_DMA_WIN_SIZE_DEFAULT&t;0x80000000&t;/* fixed, 2G @ 2G */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM_SETUP)
DECL|macro|POLARIS_DMA_WIN_BASE
mdefine_line|#define POLARIS_DMA_WIN_BASE&t;&t;alpha_mv.dma_win_base
DECL|macro|POLARIS_DMA_WIN_SIZE
mdefine_line|#define POLARIS_DMA_WIN_SIZE&t;&t;alpha_mv.dma_win_size
macro_line|#else
DECL|macro|POLARIS_DMA_WIN_BASE
mdefine_line|#define POLARIS_DMA_WIN_BASE&t;&t;POLARIS_DMA_WIN_BASE_DEFAULT
DECL|macro|POLARIS_DMA_WIN_SIZE
mdefine_line|#define POLARIS_DMA_WIN_SIZE&t;&t;POLARIS_DMA_WIN_SIZE_DEFAULT
macro_line|#endif
multiline_comment|/*&n; * Data structure for handling POLARIS machine checks:&n; */
DECL|struct|el_POLARIS_sysdata_mcheck
r_struct
id|el_POLARIS_sysdata_mcheck
(brace
DECL|member|psc_status
id|u_long
id|psc_status
suffix:semicolon
DECL|member|psc_pcictl0
id|u_long
id|psc_pcictl0
suffix:semicolon
DECL|member|psc_pcictl1
id|u_long
id|psc_pcictl1
suffix:semicolon
DECL|member|psc_pcictl2
id|u_long
id|psc_pcictl2
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE extern inline
DECL|macro|__IO_EXTERN_INLINE
mdefine_line|#define __IO_EXTERN_INLINE
macro_line|#endif
DECL|function|polaris_virt_to_bus
id|__EXTERN_INLINE
r_int
r_int
id|polaris_virt_to_bus
c_func
(paren
r_void
op_star
id|address
)paren
(brace
r_return
id|virt_to_phys
c_func
(paren
id|address
)paren
op_plus
id|POLARIS_DMA_WIN_BASE
suffix:semicolon
)brace
DECL|function|polaris_bus_to_virt
id|__EXTERN_INLINE
r_void
op_star
id|polaris_bus_to_virt
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|phys_to_virt
c_func
(paren
id|address
op_minus
id|POLARIS_DMA_WIN_BASE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * I/O functions:&n; *&n; * POLARIS, the PCI/memory support chipset for the PCA56 (21164PC)&n; * processors, can use either a sparse address  mapping scheme, or the &n; * so-called byte-word PCI address space, to get at PCI memory and I/O.&n; *&n; * However, we will support only the BWX form.&n; */
DECL|macro|vucp
mdefine_line|#define vucp&t;volatile unsigned char *
DECL|macro|vusp
mdefine_line|#define vusp&t;volatile unsigned short *
DECL|macro|vuip
mdefine_line|#define vuip&t;volatile unsigned int  *
DECL|macro|vulp
mdefine_line|#define vulp&t;volatile unsigned long  *
DECL|function|polaris_inb
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_outb
id|__EXTERN_INLINE
r_void
id|polaris_outb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_inw
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_outw
id|__EXTERN_INLINE
r_void
id|polaris_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_inl
id|__EXTERN_INLINE
r_int
r_int
id|polaris_inl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_outl
id|__EXTERN_INLINE
r_void
id|polaris_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_IO_BASE
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Memory functions.  Polaris allows all accesses (byte/word&n; * as well as long/quad) to be done through dense space.&n; *&n; * We will only support DENSE access via BWX insns.&n; */
DECL|function|polaris_readb
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldbu
c_func
(paren
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_readw
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readw
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|__kernel_ldwu
c_func
(paren
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_readl
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readl
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_readq
id|__EXTERN_INLINE
r_int
r_int
id|polaris_readq
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
op_star
(paren
id|vulp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
suffix:semicolon
)brace
DECL|function|polaris_writeb
id|__EXTERN_INLINE
r_void
id|polaris_writeb
c_func
(paren
r_int
r_char
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stb
c_func
(paren
id|b
comma
op_star
(paren
id|vucp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_writew
id|__EXTERN_INLINE
r_void
id|polaris_writew
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
id|__kernel_stw
c_func
(paren
id|b
comma
op_star
(paren
id|vusp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_writel
id|__EXTERN_INLINE
r_void
id|polaris_writel
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vuip
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|polaris_writeq
id|__EXTERN_INLINE
r_void
id|polaris_writeq
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|addr
)paren
(brace
op_star
(paren
id|vulp
)paren
(paren
id|addr
op_plus
id|POLARIS_DENSE_MEM_BASE
)paren
op_assign
id|b
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find the DENSE memory area for a given bus address.  */
DECL|function|polaris_dense_mem
id|__EXTERN_INLINE
r_int
r_int
id|polaris_dense_mem
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|POLARIS_DENSE_MEM_BASE
suffix:semicolon
)brace
DECL|macro|vucp
macro_line|#undef vucp
DECL|macro|vusp
macro_line|#undef vusp
DECL|macro|vuip
macro_line|#undef vuip
DECL|macro|vulp
macro_line|#undef vulp
macro_line|#ifdef __WANT_IO_DEF
DECL|macro|virt_to_bus
mdefine_line|#define virt_to_bus     polaris_virt_to_bus
DECL|macro|bus_to_virt
mdefine_line|#define bus_to_virt     polaris_bus_to_virt
DECL|macro|__inb
mdefine_line|#define __inb           polaris_inb
DECL|macro|__inw
mdefine_line|#define __inw           polaris_inw
DECL|macro|__inl
mdefine_line|#define __inl           polaris_inl
DECL|macro|__outb
mdefine_line|#define __outb          polaris_outb
DECL|macro|__outw
mdefine_line|#define __outw          polaris_outw
DECL|macro|__outl
mdefine_line|#define __outl          polaris_outl
DECL|macro|__readb
mdefine_line|#define __readb         polaris_readb
DECL|macro|__readw
mdefine_line|#define __readw         polaris_readw
DECL|macro|__writeb
mdefine_line|#define __writeb        polaris_writeb
DECL|macro|__writew
mdefine_line|#define __writew        polaris_writew
DECL|macro|__readl
mdefine_line|#define __readl         polaris_readl
DECL|macro|__readq
mdefine_line|#define __readq         polaris_readq
DECL|macro|__writel
mdefine_line|#define __writel        polaris_writel
DECL|macro|__writeq
mdefine_line|#define __writeq        polaris_writeq
DECL|macro|dense_mem
mdefine_line|#define dense_mem       polaris_dense_mem
DECL|macro|inb
mdefine_line|#define inb(port) __inb((port))
DECL|macro|inw
mdefine_line|#define inw(port) __inw((port))
DECL|macro|inl
mdefine_line|#define inl(port) __inl((port))
DECL|macro|outb
mdefine_line|#define outb(v, port) __outb((v),(port))
DECL|macro|outw
mdefine_line|#define outw(v, port) __outw((v),(port))
DECL|macro|outl
mdefine_line|#define outl(v, port) __outl((v),(port))
DECL|macro|readb
mdefine_line|#define readb(a)        __readb((unsigned long)(a))
DECL|macro|readw
mdefine_line|#define readw(a)        __readw((unsigned long)(a))
DECL|macro|readl
mdefine_line|#define readl(a)        __readl((unsigned long)(a))
DECL|macro|readq
mdefine_line|#define readq(a)        __readq((unsigned long)(a))
DECL|macro|writeb
mdefine_line|#define writeb(v,a)     __writeb((v),(unsigned long)(a))
DECL|macro|writew
mdefine_line|#define writew(v,a)     __writew((v),(unsigned long)(a))
DECL|macro|writel
mdefine_line|#define writel(v,a)     __writel((v),(unsigned long)(a))
DECL|macro|writeq
mdefine_line|#define writeq(v,a)     __writeq((v),(unsigned long)(a))
macro_line|#endif /* __WANT_IO_DEF */
macro_line|#ifdef __IO_EXTERN_INLINE
DECL|macro|__EXTERN_INLINE
macro_line|#undef __EXTERN_INLINE
DECL|macro|__IO_EXTERN_INLINE
macro_line|#undef __IO_EXTERN_INLINE
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ALPHA_POLARIS__H__ */
eof
