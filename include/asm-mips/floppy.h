multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995&n; */
macro_line|#ifndef __ASM_MIPS_FLOPPY_H
DECL|macro|__ASM_MIPS_FLOPPY_H
mdefine_line|#define __ASM_MIPS_FLOPPY_H
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/mipsconfig.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;&t;feature-&gt;fd_inb(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(value,port)&t;&t;feature-&gt;fd_outb(value,port)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()&t;&t;&t;feature-&gt;fd_enable_dma()
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()&t;&t;feature-&gt;fd_disable_dma()
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()&t;&t;feature-&gt;fd_request_dma()
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()&t;&t;&t;feature-&gt;fd_free_dma()
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()&t;&t;feature-&gt;fd_clear_dma_ff()
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)&t;&t;feature-&gt;fd_set_dma_mode(mode)
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)&t;&t;feature-&gt;fd_set_dma_addr(virt_to_bus(addr))
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(count)&t;&t;feature-&gt;fd_set_dma_count(count)
DECL|macro|fd_get_dma_residue
mdefine_line|#define fd_get_dma_residue()&t;&t;feature-&gt;fd_get_dma_residue()
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()&t;&t;&t;feature-&gt;fd_enable_irq()
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()&t;&t;feature-&gt;fd_disable_irq()
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr, size)&t;feature-&gt;fd_cacheflush((void *)addr, size)
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()        request_irq(FLOPPY_IRQ, floppy_interrupt, &bslash;&n;&t;&t;&t;&t;&t;    SA_INTERRUPT|SA_SAMPLE_RANDOM, &bslash;&n;&t;&t;&t;&t;            &quot;floppy&quot;, NULL)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()           free_irq(FLOPPY_IRQ, NULL);
DECL|macro|MAX_BUFFER_SECTORS
mdefine_line|#define MAX_BUFFER_SECTORS 24
DECL|function|mips_dma_mem_alloc
r_static
r_int
r_int
id|mips_dma_mem_alloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
op_assign
id|__get_order
c_func
(paren
id|size
)paren
suffix:semicolon
r_int
r_int
id|mem
suffix:semicolon
id|mem
op_assign
id|__get_dma_pages
c_func
(paren
id|GFP_KERNEL
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|boot_info.machtype
op_eq
id|MACH_ACER_PICA_61
op_logical_or
id|boot_info.machtype
op_eq
id|MACH_MIPS_MAGNUM_4000
op_logical_or
id|boot_info.machtype
op_eq
id|MACH_OLIVETTI_M700
)paren
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|mem
)paren
comma
id|size
)paren
suffix:semicolon
r_return
id|mem
suffix:semicolon
)brace
DECL|function|mips_dma_mem_free
r_static
r_void
id|mips_dma_mem_free
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|boot_info.machtype
op_eq
id|MACH_ACER_PICA_61
op_logical_or
id|boot_info.machtype
op_eq
id|MACH_MIPS_MAGNUM_4000
op_logical_or
id|boot_info.machtype
op_eq
id|MACH_OLIVETTI_M700
)paren
id|vdma_free
c_func
(paren
id|PHYSADDR
c_func
(paren
id|addr
)paren
)paren
suffix:semicolon
id|free_pages
c_func
(paren
id|addr
comma
id|__get_order
c_func
(paren
id|size
)paren
)paren
suffix:semicolon
)brace
DECL|macro|fd_dma_mem_alloc
mdefine_line|#define fd_dma_mem_alloc(mem,size) mips_dma_mem_alloc(mem,size)
DECL|macro|fd_dma_mem_free
mdefine_line|#define fd_dma_mem_free(mem) mips_dma_mem_free(mem)
multiline_comment|/*&n; * And on Mips&squot;s the CMOS info fails also ...&n; *&n; * FIXME: This information should come from the ARC configuration tree&n; *        or wherever a particular machine has stored this ...&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE 4&t;&t;/* this is wrong for the Olli M700, but who cares... */
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE 0
DECL|macro|FDC1
mdefine_line|#define FDC1&t;&t;&t;((boot_info.machtype == MACH_ACER_PICA_61 || &bslash;&n;&t;&t;&t;&t;boot_info.machtype == MACH_MIPS_MAGNUM_4000 || &bslash;&n;&t;&t;&t;&t;boot_info.machtype == MACH_OLIVETTI_M700) ? &bslash;&n;&t;&t;&t;&t;0xe0003000 : 0x3f0)
DECL|variable|FDC2
r_static
r_int
id|FDC2
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|N_FDC
mdefine_line|#define N_FDC 1&t;&t;&t;/* do you *really* want a second controller? */
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; *&n; * On MIPSes using vdma, this actually means that *all* transfers go thru&n; * the * track buffer since 0x1000000 is always smaller than KSEG0/1.&n; * Actually this needs to be a bit more complicated since the so much different&n; * hardware available with MIPS CPUs ...&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64)
macro_line|#endif /* __ASM_MIPS_FLOPPY_H */
eof
