multiline_comment|/*&n; * Architecture specific parts of the Floppy driver&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995&n; */
macro_line|#ifndef __ASM_I386_FLOPPY_H
DECL|macro|__ASM_I386_FLOPPY_H
mdefine_line|#define __ASM_I386_FLOPPY_H
DECL|macro|fd_inb
mdefine_line|#define fd_inb(port)&t;&t;&t;inb_p(port)
DECL|macro|fd_outb
mdefine_line|#define fd_outb(port,value)&t;&t;outb_p(port,value)
DECL|macro|fd_enable_dma
mdefine_line|#define fd_enable_dma()         enable_dma(FLOPPY_DMA)
DECL|macro|fd_disable_dma
mdefine_line|#define fd_disable_dma()        disable_dma(FLOPPY_DMA)
DECL|macro|fd_request_dma
mdefine_line|#define fd_request_dma()        request_dma(FLOPPY_DMA,&quot;floppy&quot;)
DECL|macro|fd_free_dma
mdefine_line|#define fd_free_dma()           free_dma(FLOPPY_DMA)
DECL|macro|fd_clear_dma_ff
mdefine_line|#define fd_clear_dma_ff()       clear_dma_ff(FLOPPY_DMA)
DECL|macro|fd_set_dma_mode
mdefine_line|#define fd_set_dma_mode(mode)   set_dma_mode(FLOPPY_DMA,mode)
DECL|macro|fd_set_dma_addr
mdefine_line|#define fd_set_dma_addr(addr)   set_dma_addr(FLOPPY_DMA,addr)
DECL|macro|fd_set_dma_count
mdefine_line|#define fd_set_dma_count(count) set_dma_count(FLOPPY_DMA,count)
DECL|macro|fd_enable_irq
mdefine_line|#define fd_enable_irq()         enable_irq(FLOPPY_IRQ)
DECL|macro|fd_disable_irq
mdefine_line|#define fd_disable_irq()        disable_irq(FLOPPY_IRQ)
DECL|macro|fd_cacheflush
mdefine_line|#define fd_cacheflush(addr,size) /* nothing */
DECL|macro|fd_request_irq
mdefine_line|#define fd_request_irq()        request_irq(FLOPPY_IRQ, floppy_interrupt, &bslash;&n;&t;&t;&t;&t;&t;    SA_INTERRUPT|SA_SAMPLE_RANDOM, &bslash;&n;&t;&t;&t;&t;            &quot;floppy&quot;)
DECL|macro|fd_free_irq
mdefine_line|#define fd_free_irq()           free_irq(FLOPPY_IRQ);
DECL|function|virtual_dma_init
id|__inline__
r_void
id|virtual_dma_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do on an i386 */
)brace
DECL|variable|FDC1
r_static
r_int
id|FDC1
op_assign
l_int|0x3f0
suffix:semicolon
DECL|variable|FDC2
r_static
r_int
id|FDC2
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|macro|FLOPPY0_TYPE
mdefine_line|#define FLOPPY0_TYPE&t;((CMOS_READ(0x10) &gt;&gt; 4) &amp; 15)
DECL|macro|FLOPPY1_TYPE
mdefine_line|#define FLOPPY1_TYPE&t;(CMOS_READ(0x10) &amp; 15)
DECL|macro|N_FDC
mdefine_line|#define N_FDC 2
DECL|macro|N_DRIVE
mdefine_line|#define N_DRIVE 8
multiline_comment|/*&n; * The DMA channel used by the floppy controller cannot access data at&n; * addresses &gt;= 16MB&n; *&n; * Went back to the 1MB limit, as some people had problems with the floppy&n; * driver otherwise. It doesn&squot;t matter much for performance anyway, as most&n; * floppy accesses go through the track buffer.&n; */
DECL|macro|CROSS_64KB
mdefine_line|#define CROSS_64KB(a,s) ((unsigned long)(a)/K_64 != ((unsigned long)(a) + (s) - 1) / K_64)
macro_line|#endif /* __ASM_I386_FLOPPY_H */
eof
