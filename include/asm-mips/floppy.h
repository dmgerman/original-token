multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996, 1997 Ralf Baechle&n; *&n; * $Id: floppy.h,v 1.14 1998/05/01 01:35:52 ralf Exp $&n; */
macro_line|#ifndef __ASM_MIPS_FLOPPY_H
DECL|macro|__ASM_MIPS_FLOPPY_H
mdefine_line|#define __ASM_MIPS_FLOPPY_H
macro_line|#include &lt;linux/config.h&gt;
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
mdefine_line|#define fd_enable_dma(channel)&t;&t;feature-&gt;fd_enable_dma(channel)
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma(channel)&t;&t;feature-&gt;fd_disable_dma(channel)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma(channel)&t;&t;feature-&gt;fd_request_dma(channel)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma(channel)&t;&t;feature-&gt;fd_free_dma(channel)
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff(channel)&t;feature-&gt;fd_clear_dma_ff(channel)
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(channel, mode)&t;feature-&gt;fd_set_dma_mode(channel, mode)
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(channel, addr)&t;feature-&gt;fd_set_dma_addr(channel, &bslash;&n;&t;&t;&t;&t;&t;         virt_to_bus(addr))
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(channel,count)&t;feature-&gt;fd_set_dma_count(channel,count)
DECL|macro|fd_get_dma_residue
mdefine_line|#define fd_get_dma_residue(channel)&t;feature-&gt;fd_get_dma_residue(channel)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq(irq)&t;&t;feature-&gt;fd_enable_irq(irq)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq(irq)&t;&t;feature-&gt;fd_disable_irq(irq)
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq(irq)&t;&t;request_irq(irq, floppy_interrupt, &bslash;&n;&t;&t;&t;&t;&t;&t;    SA_INTERRUPT &bslash;&n;&t;&t;&t;&t;&t;            | SA_SAMPLE_RANDOM, &bslash;&n;&t;&t;&t;&t;                    &quot;floppy&quot;, NULL)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq(irq)&t;&t;free_irq(irq, NULL);
DECL|macro|MAX_BUFFER_SECTORS
mdefine_line|#define MAX_BUFFER_SECTORS 24
multiline_comment|/* Pure 2^n version of get_order */
DECL|function|__get_order
r_extern
r_inline
r_int
id|__get_order
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_int
id|order
suffix:semicolon
id|size
op_assign
(paren
id|size
op_minus
l_int|1
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_minus
l_int|1
)paren
suffix:semicolon
id|order
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
(brace
id|size
op_rshift_assign
l_int|1
suffix:semicolon
id|order
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|size
)paren
suffix:semicolon
r_return
id|order
suffix:semicolon
)brace
DECL|function|mips_dma_mem_alloc
r_extern
r_inline
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
macro_line|#ifdef CONFIG_MIPS_JAZZ
r_if
c_cond
(paren
id|mips_machgroup
op_eq
id|MACH_GROUP_JAZZ
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
macro_line|#endif
r_return
id|mem
suffix:semicolon
)brace
DECL|function|mips_dma_mem_free
r_extern
r_inline
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
macro_line|#ifdef CONFIG_MIPS_JAZZ
r_if
c_cond
(paren
id|mips_machgroup
op_eq
id|MACH_GROUP_JAZZ
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
macro_line|#endif
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
mdefine_line|#define fd_dma_mem_alloc(size) mips_dma_mem_alloc(size)
DECL|macro|fd_dma_mem_free
mdefine_line|#define fd_dma_mem_free(mem,size) mips_dma_mem_free(mem,size)
multiline_comment|/*&n; * And on Mips&squot;s the CMOS info fails also ...&n; *&n; * FIXME: This information should come from the ARC configuration tree&n; *        or whereever a particular machine has stored this ...&n; */
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE 4&t;&t;/* this is wrong for the Olli M700, but who cares... */
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE 0
DECL|macro|FDC1
mdefine_line|#define FDC1&t;&t;&t;((mips_machgroup == MACH_GROUP_JAZZ) ? &bslash;&n;&t;&t;&t;&t;JAZZ_FDC_BASE : 0x3f0)
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
DECL|macro|FLOPPY_MOTOR_MASK
mdefine_line|#define FLOPPY_MOTOR_MASK 0xf0
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; *&n; * On MIPSes using vdma, this actually means that *all* transfers go thru&n; * the * track buffer since 0x1000000 is always smaller than KSEG0/1.&n; * Actually this needs to be a bit more complicated since the so much different&n; * hardware available with MIPS CPUs ...&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64)
macro_line|#endif /* __ASM_MIPS_FLOPPY_H */
eof
