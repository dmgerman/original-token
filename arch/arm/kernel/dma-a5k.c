multiline_comment|/*&n; * arch/arm/kernel/dma-a5k.c&n; *&n; * Copyright (C) 1998 Russell King&n; *&n; * DMA functions specific to A5000 architecture&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/fiq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;dma.h&quot;
DECL|variable|fh
r_static
r_struct
id|fiq_handler
id|fh
op_assign
(brace
l_string|&quot;floppydma&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|arch_request_dma
r_int
id|arch_request_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
comma
r_const
r_char
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|channel
op_eq
id|DMA_VIRTUAL_FLOPPY
)paren
r_return
l_int|0
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|arch_free_dma
r_void
id|arch_free_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
(brace
r_if
c_cond
(paren
id|channel
op_ne
id|DMA_VIRTUAL_FLOPPY
)paren
id|printk
c_func
(paren
l_string|&quot;arch_free_dma: invalid channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
)brace
DECL|function|arch_get_dma_residue
r_int
id|arch_get_dma_residue
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
(brace
r_if
c_cond
(paren
id|channel
op_ne
id|DMA_VIRTUAL_FLOPPY
)paren
id|printk
c_func
(paren
l_string|&quot;arch_dma_count: invalid channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_else
(brace
r_extern
r_int
id|floppy_fiqresidual
c_func
(paren
r_void
)paren
suffix:semicolon
r_return
id|floppy_fiqresidual
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|arch_enable_dma
r_void
id|arch_enable_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
(brace
r_if
c_cond
(paren
id|channel
op_ne
id|DMA_VIRTUAL_FLOPPY
)paren
id|printk
c_func
(paren
l_string|&quot;arch_enable_dma: invalid channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_else
(brace
r_void
op_star
id|fiqhandler_start
suffix:semicolon
r_int
r_int
id|fiqhandler_length
suffix:semicolon
r_extern
r_void
id|floppy_fiqsetup
c_func
(paren
r_int
r_int
id|len
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;dma_mode
op_eq
id|DMA_MODE_READ
)paren
(brace
r_extern
r_int
r_char
id|floppy_fiqin_start
comma
id|floppy_fiqin_end
suffix:semicolon
id|fiqhandler_start
op_assign
op_amp
id|floppy_fiqin_start
suffix:semicolon
id|fiqhandler_length
op_assign
op_amp
id|floppy_fiqin_end
op_minus
op_amp
id|floppy_fiqin_start
suffix:semicolon
)brace
r_else
(brace
r_extern
r_int
r_char
id|floppy_fiqout_start
comma
id|floppy_fiqout_end
suffix:semicolon
id|fiqhandler_start
op_assign
op_amp
id|floppy_fiqout_start
suffix:semicolon
id|fiqhandler_length
op_assign
op_amp
id|floppy_fiqout_end
op_minus
op_amp
id|floppy_fiqout_start
suffix:semicolon
)brace
r_if
c_cond
(paren
id|claim_fiq
c_func
(paren
op_amp
id|fh
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;floppydma: couldn&squot;t claim FIQ.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
(paren
r_void
op_star
)paren
l_int|0x1c
comma
id|fiqhandler_start
comma
id|fiqhandler_length
)paren
suffix:semicolon
id|flush_page_to_ram
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|floppy_fiqsetup
c_func
(paren
id|dma-&gt;buf.length
comma
id|__bus_to_virt
c_func
(paren
id|dma-&gt;buf.address
)paren
comma
(paren
r_int
)paren
id|PCIO_FLOPPYDMABASE
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
id|dma-&gt;dma_irq
)paren
suffix:semicolon
)brace
)brace
DECL|function|arch_disable_dma
r_void
id|arch_disable_dma
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
)paren
(brace
r_if
c_cond
(paren
id|channel
op_ne
id|DMA_VIRTUAL_FLOPPY
)paren
id|printk
c_func
(paren
l_string|&quot;arch_disable_dma: invalid channel %d&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_else
(brace
id|disable_irq
c_func
(paren
id|dma-&gt;dma_irq
)paren
suffix:semicolon
id|release_fiq
c_func
(paren
op_amp
id|fh
)paren
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|arch_dma_init
c_func
(paren
id|dma_t
op_star
id|dma
)paren
)paren
(brace
id|dma
(braket
id|DMA_VIRTUAL_FLOPPY
)braket
dot
id|dma_irq
op_assign
l_int|64
suffix:semicolon
)brace
eof
