multiline_comment|/* $Id: dma.c,v 1.7 1994/12/28 03:35:33 root Exp root $&n; * linux/kernel/dma.c: A DMA channel allocator. Inspired by linux/kernel/irq.c.&n; *&n; * Written by Hennus Bergman, 1992.&n; *&n; * 1994/12/26: Changes by Alex Nash to fix a minor bug in /proc/dma.&n; *   In the previous version the reported device could end up being wrong,&n; *   if a device requested a DMA channel that was already in use.&n; *   [It also happened to remove the sizeof(char *) == sizeof(int)&n; *   assumption introduced because of those /proc/dma patches. -- Hennus]&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* A note on resource allocation:&n; *&n; * All drivers needing DMA channels, should allocate and release them&n; * through the public routines `request_dma()&squot; and `free_dma()&squot;.&n; *&n; * In order to avoid problems, all processes should allocate resources in&n; * the same sequence and release them in the reverse order.&n; *&n; * So, when allocating DMAs and IRQs, first allocate the IRQ, then the DMA.&n; * When releasing them, first release the DMA, then release the IRQ.&n; * If you don&squot;t, you may cause allocation requests to fail unnecessarily.&n; * This doesn&squot;t really matter now, but it will once we get real semaphores&n; * in the kernel.&n; */
DECL|variable|dma_spin_lock
id|spinlock_t
id|dma_spin_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; *&t;If our port doesn&squot;t define this it has no PC like DMA&n; */
macro_line|#ifdef MAX_DMA_CHANNELS
multiline_comment|/* Channel n is busy iff dma_chan_busy[n].lock != 0.&n; * DMA0 used to be reserved for DRAM refresh, but apparently not any more...&n; * DMA4 is reserved for cascading.&n; */
DECL|struct|dma_chan
r_struct
id|dma_chan
(brace
DECL|member|lock
r_int
id|lock
suffix:semicolon
DECL|member|device_id
r_const
r_char
op_star
id|device_id
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|dma_chan_busy
r_static
r_struct
id|dma_chan
id|dma_chan_busy
(braket
id|MAX_DMA_CHANNELS
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_string|&quot;cascade&quot;
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|get_dma_list
r_int
id|get_dma_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DMA_CHANNELS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dma_chan_busy
(braket
id|i
)braket
dot
id|lock
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%2d: %s&bslash;n&quot;
comma
id|i
comma
id|dma_chan_busy
(braket
id|i
)braket
dot
id|device_id
)paren
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/* get_dma_list */
DECL|function|request_dma
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
(brace
r_if
c_cond
(paren
id|dmanr
op_ge
id|MAX_DMA_CHANNELS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|lock
comma
l_int|1
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|device_id
op_assign
id|device_id
suffix:semicolon
multiline_comment|/* old flag was 0, now contains 1 to indicate busy */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* request_dma */
DECL|function|free_dma
r_void
id|free_dma
c_func
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
op_ge
id|MAX_DMA_CHANNELS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|xchg
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
dot
id|lock
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* free_dma */
macro_line|#else
DECL|function|request_dma
r_int
id|request_dma
c_func
(paren
r_int
r_int
id|dmanr
comma
r_const
r_char
op_star
id|device_id
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|free_dma
r_int
id|free_dma
c_func
(paren
r_int
r_int
id|dmanr
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|get_dma_list
r_int
id|get_dma_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
id|strcpy
c_func
(paren
id|buf
comma
l_string|&quot;No DMA&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|7
suffix:semicolon
)brace
macro_line|#endif
eof
