multiline_comment|/*&n; * arch/arm/kernel/dma-arc.c&n; *&n; * Copyright (C) 1998-1999 Dave Gilbert / Russell King&n; *&n; * DMA functions specific to Archimedes architecture&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &quot;dma.h&quot;
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
id|DMA_VIRTUAL_FLOPPY0
op_logical_or
id|channel
op_eq
id|DMA_VIRTUAL_FLOPPY1
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
r_switch
c_cond
(paren
id|channel
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_FD
r_case
id|DMA_VIRTUAL_FLOPPY0
suffix:colon
(brace
multiline_comment|/* Data DMA */
r_switch
c_cond
(paren
id|dma-&gt;dma_mode
)paren
(brace
r_case
id|DMA_MODE_READ
suffix:colon
multiline_comment|/* read */
(brace
r_extern
r_int
r_char
id|fdc1772_dma_read
comma
id|fdc1772_dma_read_end
suffix:semicolon
r_extern
r_void
id|fdc1772_setupdma
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;enable_dma fdc1772 data read&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cliIF
c_func
(paren
)paren
suffix:semicolon
id|memcpy
(paren
(paren
r_void
op_star
)paren
l_int|0x1c
comma
(paren
r_void
op_star
)paren
op_amp
id|fdc1772_dma_read
comma
op_amp
id|fdc1772_dma_read_end
op_minus
op_amp
id|fdc1772_dma_read
)paren
suffix:semicolon
id|fdc1772_setupdma
c_func
(paren
id|dma-&gt;buf.length
comma
id|__bus_to_virt
c_func
(paren
id|dma-&gt;buf.address
)paren
)paren
suffix:semicolon
multiline_comment|/* Sets data pointer up */
id|enable_irq
(paren
l_int|64
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DMA_MODE_WRITE
suffix:colon
multiline_comment|/* write */
(brace
r_extern
r_int
r_char
id|fdc1772_dma_write
comma
id|fdc1772_dma_write_end
suffix:semicolon
r_extern
r_void
id|fdc1772_setupdma
c_func
(paren
r_int
r_int
id|count
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;enable_dma fdc1772 data write&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cliIF
c_func
(paren
)paren
suffix:semicolon
id|memcpy
(paren
(paren
r_void
op_star
)paren
l_int|0x1c
comma
(paren
r_void
op_star
)paren
op_amp
id|fdc1772_dma_write
comma
op_amp
id|fdc1772_dma_write_end
op_minus
op_amp
id|fdc1772_dma_write
)paren
suffix:semicolon
id|fdc1772_setupdma
c_func
(paren
id|dma-&gt;buf.length
comma
id|__bus_to_virt
c_func
(paren
id|dma-&gt;buf.address
)paren
)paren
suffix:semicolon
multiline_comment|/* Sets data pointer up */
id|enable_irq
(paren
l_int|64
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;enable_dma: dma%d not initialised&bslash;n&quot;
comma
id|channel
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DMA_VIRTUAL_FLOPPY1
suffix:colon
(brace
multiline_comment|/* Command end FIQ - actually just sets a flag */
multiline_comment|/* Need to build a branch at the FIQ address */
r_extern
r_void
id|fdc1772_comendhandler
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*printk(&quot;enable_dma fdc1772 command end FIQ&bslash;n&quot;);*/
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cliIF
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0x1c
)paren
op_assign
l_int|0xea000000
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|fdc1772_comendhandler
op_minus
(paren
l_int|0x1c
op_plus
l_int|8
)paren
)paren
op_div
l_int|4
)paren
suffix:semicolon
multiline_comment|/* B fdc1772_comendhandler */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
)brace
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
r_switch
c_cond
(paren
id|channel
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_FD1772
r_case
id|DMA_VIRTUAL_FLOPPY0
suffix:colon
(brace
multiline_comment|/* Data DMA */
r_extern
r_int
r_int
id|fdc1772_bytestogo
suffix:semicolon
multiline_comment|/* 10/1/1999 DAG - I presume its the number of bytes left? */
r_return
id|fdc1772_bytestogo
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_VIRTUAL_FLOPPY1
suffix:colon
(brace
multiline_comment|/* Command completed */
multiline_comment|/* 10/1/1999 DAG - Presume whether there is an outstanding command? */
r_extern
r_int
r_int
id|fdc1772_fdc_int_done
suffix:semicolon
r_return
(paren
id|fdc1772_fdc_int_done
op_eq
l_int|0
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* Explicit! If the int done is 0 then 1 int to go */
)brace
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;dma-arc.c:arch_get_dma_residue called with unknown/unconfigured DMA channel&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
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
id|DMA_VIRTUAL_FLOPPY0
op_logical_and
id|channel
op_ne
id|DMA_VIRTUAL_FLOPPY1
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
id|disable_irq
c_func
(paren
id|dma-&gt;dma_irq
)paren
suffix:semicolon
)brace
DECL|function|arch_set_dma_speed
r_int
id|arch_set_dma_speed
c_func
(paren
id|dmach_t
id|channel
comma
id|dma_t
op_star
id|dma
comma
r_int
id|cycle_ns
)paren
(brace
r_return
l_int|0
suffix:semicolon
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
id|DMA_VIRTUAL_FLOPPY0
)braket
dot
id|dma_irq
op_assign
l_int|64
suffix:semicolon
id|dma
(braket
id|DMA_VIRTUAL_FLOPPY1
)braket
dot
id|dma_irq
op_assign
l_int|65
suffix:semicolon
)brace
eof
