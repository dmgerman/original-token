multiline_comment|/*&n; * Low-level hardware access stuff for Deskstation rPC44/Tyne&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Ralf Baechle&n; *&n; * $Id: hw-access.c,v 1.2 1997/08/08 18:11:57 miguel Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kbdcntrlr.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
r_extern
r_int
id|FLOPPY_IRQ
suffix:semicolon
r_extern
r_int
id|FLOPPY_DMA
suffix:semicolon
id|asmlinkage
r_extern
r_void
id|deskstation_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * How to access the FDC&squot;s registers.&n; */
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
r_return
id|inb_p
c_func
(paren
id|port
)paren
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
id|outb_p
c_func
(paren
id|value
comma
id|port
)paren
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
id|enable_dma
c_func
(paren
id|FLOPPY_DMA
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
id|disable_dma
c_func
(paren
id|FLOPPY_DMA
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
id|request_dma
c_func
(paren
id|FLOPPY_DMA
comma
l_string|&quot;floppy&quot;
)paren
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
id|free_dma
c_func
(paren
id|FLOPPY_DMA
)paren
suffix:semicolon
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
id|clear_dma_ff
c_func
(paren
id|FLOPPY_DMA
)paren
suffix:semicolon
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
id|set_dma_mode
c_func
(paren
id|FLOPPY_DMA
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
id|addr
)paren
(brace
id|set_dma_addr
c_func
(paren
id|FLOPPY_DMA
comma
id|addr
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
id|set_dma_count
c_func
(paren
id|FLOPPY_DMA
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
id|get_dma_residue
c_func
(paren
id|FLOPPY_DMA
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
id|enable_irq
c_func
(paren
id|FLOPPY_IRQ
)paren
suffix:semicolon
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
id|disable_irq
c_func
(paren
id|FLOPPY_IRQ
)paren
suffix:semicolon
)brace
r_void
DECL|function|deskstation_fd_cacheflush
id|deskstation_fd_cacheflush
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
multiline_comment|/*&n; * RTC stuff&n; */
r_static
r_int
r_char
op_star
DECL|function|rtc_read_data
id|rtc_read_data
c_func
(paren
)paren
(brace
r_return
l_int|0
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
)paren
(brace
)brace
multiline_comment|/*&n; * KLUDGE&n; */
r_static
r_int
r_int
DECL|function|vdma_alloc
id|vdma_alloc
c_func
(paren
r_int
r_int
id|paddr
comma
r_int
r_int
id|size
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DESKSTATION_TYNE
DECL|variable|deskstation_tyne_feature
r_struct
id|feature
id|deskstation_tyne_feature
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
macro_line|#endif
macro_line|#ifdef CONFIG_DESKSTATION_RPC44
DECL|variable|deskstation_rpc44_feature
r_struct
id|feature
id|deskstation_rpc44_feature
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
macro_line|#endif
DECL|function|dtc_read_input
r_static
r_int
r_char
id|dtc_read_input
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|dtc_write_output
r_static
r_void
id|dtc_write_output
c_func
(paren
r_int
r_char
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|KBD_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|dtc_write_command
r_static
r_void
id|dtc_write_command
c_func
(paren
r_int
r_char
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|KBD_CNTL_REG
)paren
suffix:semicolon
)brace
DECL|function|dtc_read_status
r_static
r_int
r_char
id|dtc_read_status
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|KBD_STATUS_REG
)paren
suffix:semicolon
)brace
DECL|function|dtc_rm200_keyboard_setup
r_static
r_void
id|dtc_rm200_keyboard_setup
c_func
(paren
r_void
)paren
(brace
id|kbd_read_input
op_assign
id|dtc_read_input
suffix:semicolon
id|kbd_write_output
op_assign
id|dtc_write_output
suffix:semicolon
id|kbd_write_command
op_assign
id|dtc_write_command
suffix:semicolon
id|kbd_read_status
op_assign
id|dtc_read_status
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x60
comma
l_int|16
comma
l_string|&quot;keyboard&quot;
)paren
suffix:semicolon
)brace
eof
