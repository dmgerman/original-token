multiline_comment|/* $Header: /sys/linux-0.97/kernel/RCS/dma.c,v 1.4 1992/09/18 02:54:14 root Exp $&n; * linux/kernel/dma.c: A DMA channel allocator. Inspired by linux/kernel/irq.c.&n; * Written by Hennus Bergman, 1992. &n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
multiline_comment|/* A note on resource allocation:&n; *&n; * All drivers needing DMA channels, should allocate and release them&n; * through the public routines `request_dma()&squot; and `free_dma()&squot;.&n; *&n; * In order to avoid problems, all processes should allocate resources in&n; * the same sequence and release them in the reverse order.&n; * &n; * So, when allocating DMAs and IRQs, first allocate the IRQ, then the DMA.&n; * When releasing them, first release the DMA, then release the IRQ.&n; * If you don&squot;t, you may cause allocation requests to fail unnecessarily.&n; * This doesn&squot;t really matter now, but it will once we get real semaphores&n; * in the kernel.&n; */
multiline_comment|/* Channel n is busy iff dma_chan_busy[n] != 0.&n; * DMA0 is reserved for DRAM refresh, I think.&n; * DMA4 is reserved for cascading (?).&n; */
DECL|variable|dma_chan_busy
r_static
r_volatile
r_int
r_int
id|dma_chan_busy
(braket
id|MAX_DMA_CHANNELS
)braket
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Atomically swap memory location [32 bits] with `newval&squot;.&n; * This avoid the cli()/sti() junk and related problems.&n; * [And it&squot;s faster too :-)]&n; * Maybe this should be in include/asm/mutex.h and be used for&n; * implementing kernel-semaphores as well.&n; */
DECL|function|mutex_atomic_swap
r_static
r_int
r_int
id|__inline__
id|mutex_atomic_swap
c_func
(paren
r_volatile
r_int
r_int
op_star
id|p
comma
r_int
r_int
id|newval
)paren
(brace
r_int
r_int
id|semval
op_assign
id|newval
suffix:semicolon
multiline_comment|/* If one of the operands for the XCHG instructions is a memory ref,&n;&t; * it makes the swap an uninterruptible RMW cycle.&n;&t; *&n;&t; * One operand must be in memory, the other in a register, otherwise&n;&t; * the swap may not be atomic.&n;&t; */
id|asm
id|__volatile__
(paren
l_string|&quot;xchgl %2, %0&bslash;n&quot;
suffix:colon
multiline_comment|/* outputs: semval   */
l_string|&quot;=r&quot;
(paren
id|semval
)paren
suffix:colon
multiline_comment|/* inputs: newval, p */
l_string|&quot;0&quot;
(paren
id|semval
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
)paren
suffix:semicolon
multiline_comment|/* p is a var, containing an address */
r_return
id|semval
suffix:semicolon
)brace
multiline_comment|/* mutex_atomic_swap */
DECL|function|request_dma
r_int
id|request_dma
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
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|mutex_atomic_swap
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
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
r_else
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
id|mutex_atomic_swap
c_func
(paren
op_amp
id|dma_chan_busy
(braket
id|dmanr
)braket
comma
l_int|0
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Trying to free free DMA%d&bslash;n&quot;
comma
id|dmanr
)paren
suffix:semicolon
)brace
multiline_comment|/* free_dma */
eof
