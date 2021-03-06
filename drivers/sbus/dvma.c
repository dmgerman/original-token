multiline_comment|/* dvma.c:  Routines that are used to access DMA on the Sparc SBus.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
DECL|variable|dma_chain
r_struct
id|sbus_dma
op_star
id|dma_chain
suffix:semicolon
multiline_comment|/* Print out the current values in the DMA control registers */
DECL|function|dump_dma_regs
r_extern
id|__inline__
r_void
id|dump_dma_regs
c_func
(paren
r_int
r_int
id|dregs
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA CONTROL&lt;%08x&gt; ADDR&lt;%08x&gt; CNT&lt;%08x&gt; TEST&lt;%08x&gt;&bslash;n&quot;
comma
id|sbus_readl
c_func
(paren
id|dregs
op_plus
id|DMA_CSR
)paren
comma
id|sbus_readl
c_func
(paren
id|dregs
op_plus
id|DMA_ADDR
)paren
comma
id|sbus_readl
c_func
(paren
id|dregs
op_plus
id|DMA_COUNT
)paren
comma
id|sbus_readl
c_func
(paren
id|dregs
op_plus
id|DMA_TEST
)paren
)paren
suffix:semicolon
)brace
DECL|function|init_one_dvma
r_void
id|__init
id|init_one_dvma
c_func
(paren
r_struct
id|sbus_dma
op_star
id|dma
comma
r_int
id|num_dma
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;dma%d: &quot;
comma
id|num_dma
)paren
suffix:semicolon
id|dma-&gt;next
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;running
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No transfers going on as of yet */
id|dma-&gt;allocated
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No one has allocated us yet */
r_switch
c_cond
(paren
id|sbus_readl
c_func
(paren
id|dma-&gt;regs
op_plus
id|DMA_CSR
)paren
op_amp
id|DMA_DEVICE_ID
)paren
(brace
r_case
id|DMA_VERS0
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmarev0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Revision 0 &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_ESCV1
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmaesc1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ESC Revision 1 &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_VERS1
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmarev1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Revision 1 &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_VERS2
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmarev2
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Revision 2 &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_VERHME
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmahme
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;HME DVMA gate array &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|DMA_VERSPLUS
suffix:colon
id|dma-&gt;revision
op_assign
id|dvmarevplus
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Revision 1 PLUS &quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;unknown dma version %08x&quot;
comma
id|sbus_readl
c_func
(paren
id|dma-&gt;regs
op_plus
id|DMA_CSR
)paren
op_amp
id|DMA_DEVICE_ID
)paren
suffix:semicolon
id|dma-&gt;allocated
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if 0 /* Clutters up the screen */
id|dump_dma_regs
c_func
(paren
id|dma-&gt;regs
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Probe this SBus DMA module(s) */
DECL|function|dvma_init
r_void
id|__init
id|dvma_init
c_func
(paren
r_struct
id|sbus_bus
op_star
id|sbus
)paren
(brace
r_struct
id|sbus_dev
op_star
id|this_dev
suffix:semicolon
r_struct
id|sbus_dma
op_star
id|dma
suffix:semicolon
r_struct
id|sbus_dma
op_star
id|dchain
suffix:semicolon
r_static
r_int
id|num_dma
op_assign
l_int|0
suffix:semicolon
id|for_each_sbusdev
c_func
(paren
id|this_dev
comma
id|sbus
)paren
(brace
r_char
op_star
id|name
op_assign
id|this_dev-&gt;prom_name
suffix:semicolon
r_int
id|hme
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;SUNW,fas&quot;
)paren
)paren
(brace
id|hme
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;dma&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;ledma&quot;
)paren
op_logical_and
id|strcmp
c_func
(paren
id|name
comma
l_string|&quot;espdma&quot;
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/* Found one... */
id|dma
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dma
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|dma-&gt;sdev
op_assign
id|this_dev
suffix:semicolon
multiline_comment|/* Put at end of dma chain */
id|dchain
op_assign
id|dma_chain
suffix:semicolon
r_if
c_cond
(paren
id|dchain
)paren
(brace
r_while
c_loop
(paren
id|dchain-&gt;next
)paren
(brace
id|dchain
op_assign
id|dchain-&gt;next
suffix:semicolon
)brace
id|dchain-&gt;next
op_assign
id|dma
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* We&squot;re the first in line */
id|dma_chain
op_assign
id|dma
suffix:semicolon
)brace
id|dma-&gt;regs
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|dma-&gt;sdev-&gt;resource
(braket
l_int|0
)braket
comma
l_int|0
comma
id|dma-&gt;sdev-&gt;resource
(braket
l_int|0
)braket
dot
id|end
op_minus
id|dma-&gt;sdev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
op_plus
l_int|1
comma
l_string|&quot;dma&quot;
)paren
suffix:semicolon
id|dma-&gt;node
op_assign
id|dma-&gt;sdev-&gt;prom_node
suffix:semicolon
id|init_one_dvma
c_func
(paren
id|dma
comma
id|num_dma
op_increment
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SUN4
macro_line|#include &lt;asm/sun4paddr.h&gt;
DECL|function|sun4_dvma_init
r_void
id|__init
id|sun4_dvma_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_dma
op_star
id|dma
suffix:semicolon
r_struct
id|sbus_dma
op_star
id|dchain
suffix:semicolon
r_struct
id|resource
id|r
suffix:semicolon
r_if
c_cond
(paren
id|sun4_dma_physaddr
)paren
(brace
id|dma
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sbus_dma
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/* No SBUS */
id|dma-&gt;sdev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Only one DMA device */
id|dma_chain
op_assign
id|dma
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
r_sizeof
(paren
id|r
)paren
)paren
suffix:semicolon
id|r.start
op_assign
id|sun4_dma_physaddr
suffix:semicolon
id|dma-&gt;regs
op_assign
id|sbus_ioremap
c_func
(paren
op_amp
id|r
comma
l_int|0
comma
id|PAGE_SIZE
comma
l_string|&quot;dma&quot;
)paren
suffix:semicolon
multiline_comment|/* No prom node */
id|dma-&gt;node
op_assign
l_int|0x0
suffix:semicolon
id|init_one_dvma
c_func
(paren
id|dma
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
id|dma_chain
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
