multiline_comment|/*&n; * Low-level hardware access stuff for Jazz family machines.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mc146818rtc.h&gt;
r_static
r_int
r_char
DECL|function|fd_inb
id|fd_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|c
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_return
id|c
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_outb
id|fd_outb
c_func
(paren
r_int
r_char
id|value
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|port
op_assign
id|value
suffix:semicolon
)brace
multiline_comment|/*&n; * How to access the floppy DMA functions.&n; */
r_static
r_void
DECL|function|fd_enable_dma
id|fd_enable_dma
c_func
(paren
r_void
)paren
(brace
id|vdma_enable
c_func
(paren
id|JAZZ_FLOPPY_DMA
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_disable_dma
id|fd_disable_dma
c_func
(paren
r_void
)paren
(brace
id|vdma_disable
c_func
(paren
id|JAZZ_FLOPPY_DMA
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|fd_request_dma
id|fd_request_dma
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_free_dma
id|fd_free_dma
c_func
(paren
r_void
)paren
(brace
)brace
r_static
r_void
DECL|function|fd_clear_dma_ff
id|fd_clear_dma_ff
c_func
(paren
r_void
)paren
(brace
)brace
r_static
r_void
DECL|function|fd_set_dma_mode
id|fd_set_dma_mode
c_func
(paren
r_char
id|mode
)paren
(brace
id|vdma_set_mode
c_func
(paren
id|JAZZ_FLOPPY_DMA
comma
id|mode
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_set_dma_addr
id|fd_set_dma_addr
c_func
(paren
r_int
r_int
id|a
)paren
(brace
id|vdma_set_addr
c_func
(paren
id|JAZZ_FLOPPY_DMA
comma
id|vdma_phys2log
c_func
(paren
id|PHYSADDR
c_func
(paren
id|a
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_set_dma_count
id|fd_set_dma_count
c_func
(paren
r_int
r_int
id|count
)paren
(brace
id|vdma_set_count
c_func
(paren
id|JAZZ_FLOPPY_DMA
comma
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|fd_get_dma_residue
id|fd_get_dma_residue
c_func
(paren
r_void
)paren
(brace
r_return
id|vdma_get_residue
c_func
(paren
id|JAZZ_FLOPPY_DMA
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|fd_enable_irq
id|fd_enable_irq
c_func
(paren
r_void
)paren
(brace
)brace
r_static
r_void
DECL|function|fd_disable_irq
id|fd_disable_irq
c_func
(paren
r_void
)paren
(brace
)brace
r_void
DECL|function|jazz_fd_cacheflush
id|jazz_fd_cacheflush
c_func
(paren
r_const
r_void
op_star
id|addr
comma
r_int
id|size
)paren
(brace
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_char
DECL|function|rtc_read_data
id|rtc_read_data
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
op_star
(paren
r_char
op_star
)paren
id|JAZZ_RTC_BASE
suffix:semicolon
)brace
r_static
r_void
DECL|function|rtc_write_data
id|rtc_write_data
c_func
(paren
r_int
r_char
id|data
comma
r_int
r_int
id|addr
)paren
(brace
id|outb_p
c_func
(paren
id|addr
comma
id|RTC_PORT
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
op_star
(paren
r_char
op_star
)paren
id|JAZZ_RTC_BASE
op_assign
id|data
suffix:semicolon
)brace
DECL|variable|jazz_feature
r_struct
id|feature
id|jazz_feature
op_assign
(brace
multiline_comment|/*&n;&t; * How to access the floppy controller&squot;s ports&n;&t; */
id|fd_inb
comma
id|fd_outb
comma
multiline_comment|/*&n;&t; * How to access the floppy DMA functions.&n;&t; */
id|fd_enable_dma
comma
id|fd_disable_dma
comma
id|fd_request_dma
comma
id|fd_free_dma
comma
id|fd_clear_dma_ff
comma
id|fd_set_dma_mode
comma
id|fd_set_dma_addr
comma
id|fd_set_dma_count
comma
id|fd_get_dma_residue
comma
id|fd_enable_irq
comma
id|fd_disable_irq
comma
multiline_comment|/*&n;&t; * How to access the RTC functions.&n;&t; */
id|rtc_read_data
comma
id|rtc_write_data
)brace
suffix:semicolon
eof