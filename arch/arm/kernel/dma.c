multiline_comment|/*&n; * linux/arch/arm/kernel/dma.c&n; *&n; * Copyright (C) 1995, 1996 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|KERNEL_ARCH_DMA
mdefine_line|#define KERNEL_ARCH_DMA
macro_line|#include &lt;asm/dma.h&gt;
DECL|variable|dma_address
r_static
r_int
r_int
id|dma_address
(braket
l_int|8
)braket
suffix:semicolon
DECL|variable|dma_count
r_static
r_int
r_int
id|dma_count
(braket
l_int|8
)braket
suffix:semicolon
DECL|variable|dma_direction
r_static
r_char
id|dma_direction
(braket
l_int|8
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_A5K) || defined(CONFIG_ARCH_RPC)
DECL|macro|DMA_PCIO
mdefine_line|#define DMA_PCIO
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_ARC) &amp;&amp; defined(CONFIG_BLK_DEV_FD)
DECL|macro|DMA_OLD
mdefine_line|#define DMA_OLD
macro_line|#endif
DECL|function|enable_dma
r_void
id|enable_dma
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
macro_line|#ifdef DMA_PCIO
r_case
l_int|2
suffix:colon
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
r_switch
c_cond
(paren
id|dma_direction
(braket
id|dmanr
)braket
)paren
(brace
r_case
l_int|1
suffix:colon
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
r_break
suffix:semicolon
)brace
r_case
l_int|0
suffix:colon
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
r_break
suffix:semicolon
)brace
r_default
suffix:colon
id|printk
(paren
l_string|&quot;enable_dma: dma%d not initialised&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
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
(paren
id|dma_count
(braket
id|dmanr
)braket
comma
id|dma_address
(braket
id|dmanr
)braket
comma
(paren
r_int
)paren
id|PCIO_FLOPPYDMABASE
)paren
suffix:semicolon
id|enable_irq
(paren
l_int|64
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef DMA_OLD
r_case
l_int|0
suffix:colon
(brace
multiline_comment|/* Data DMA */
r_switch
c_cond
(paren
id|dma_direction
(braket
id|dmanr
)braket
)paren
(brace
r_case
l_int|1
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
id|dma_count
(braket
id|dmanr
)braket
comma
id|dma_address
(braket
id|dmanr
)braket
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
l_int|0
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
id|dma_count
(braket
id|dmanr
)braket
comma
id|dma_address
(braket
id|dmanr
)braket
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
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|1
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
r_case
id|DMA_0
suffix:colon
r_case
id|DMA_1
suffix:colon
r_case
id|DMA_2
suffix:colon
r_case
id|DMA_3
suffix:colon
r_case
id|DMA_S0
suffix:colon
r_case
id|DMA_S1
suffix:colon
id|arch_enable_dma
(paren
id|dmanr
op_minus
id|DMA_0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;enable_dma: dma %d not supported&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
)brace
)brace
DECL|function|set_dma_mode
r_void
id|set_dma_mode
(paren
r_int
r_int
id|dmanr
comma
r_char
id|mode
)paren
(brace
r_if
c_cond
(paren
id|dmanr
OL
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|mode
op_eq
id|DMA_MODE_READ
)paren
id|dma_direction
(braket
id|dmanr
)braket
op_assign
l_int|1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mode
op_eq
id|DMA_MODE_WRITE
)paren
id|dma_direction
(braket
id|dmanr
)braket
op_assign
l_int|0
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;set_dma_mode: dma%d: invalid mode %02X not supported&bslash;n&quot;
comma
id|dmanr
comma
id|mode
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dmanr
OL
id|MAX_DMA_CHANNELS
)paren
id|arch_set_dma_mode
(paren
id|dmanr
op_minus
id|DMA_0
comma
id|mode
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;set_dma_mode: dma %d not supported&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
)brace
DECL|function|set_dma_addr
r_void
id|set_dma_addr
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|addr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
OL
l_int|8
)paren
id|dma_address
(braket
id|dmanr
)braket
op_assign
(paren
r_int
r_int
)paren
id|addr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dmanr
OL
id|MAX_DMA_CHANNELS
)paren
id|arch_set_dma_addr
(paren
id|dmanr
op_minus
id|DMA_0
comma
id|addr
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;set_dma_addr: dma %d not supported&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
)brace
DECL|function|set_dma_count
r_void
id|set_dma_count
(paren
r_int
r_int
id|dmanr
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|dmanr
OL
l_int|8
)paren
id|dma_count
(braket
id|dmanr
)braket
op_assign
(paren
r_int
r_int
)paren
id|count
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dmanr
OL
id|MAX_DMA_CHANNELS
)paren
id|arch_set_dma_count
(paren
id|dmanr
op_minus
id|DMA_0
comma
id|count
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;set_dma_count: dma %d not supported&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
)brace
DECL|function|get_dma_residue
r_int
id|get_dma_residue
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|dmanr
OL
l_int|8
)paren
(brace
r_switch
c_cond
(paren
id|dmanr
)paren
(brace
macro_line|#if defined(CONFIG_ARCH_A5K) || defined(CONFIG_ARCH_RPC)
r_case
l_int|2
suffix:colon
(brace
r_extern
r_int
id|floppy_fiqresidual
(paren
r_void
)paren
suffix:semicolon
r_return
id|floppy_fiqresidual
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_ARCH_ARC) &amp;&amp; defined(CONFIG_BLK_DEV_FD)
r_case
l_int|0
suffix:colon
(brace
r_extern
r_int
r_int
id|fdc1772_bytestogo
suffix:semicolon
r_return
id|fdc1772_bytestogo
suffix:semicolon
)brace
macro_line|#endif
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|dmanr
OL
id|MAX_DMA_CHANNELS
)paren
r_return
id|arch_dma_count
(paren
id|dmanr
op_minus
id|DMA_0
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
eof