multiline_comment|/*&n; * Baboon Custom IC Managment&n; *&n; * The Baboon custom IC controls the IDE, PCMCIA and media bay on the&n; * PowerBook 190. It multiplexes multiple interrupt sources onto the&n; * Nubus slot $C interrupt.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt; 
macro_line|#include &lt;asm/macintosh.h&gt; 
macro_line|#include &lt;asm/macints.h&gt; 
macro_line|#include &lt;asm/mac_baboon.h&gt;
multiline_comment|/* #define DEBUG_BABOON /**/
multiline_comment|/* #define DEBUG_IRQS /**/
DECL|variable|baboon_present
DECL|variable|baboon_active
r_int
id|baboon_present
comma
id|baboon_active
suffix:semicolon
DECL|variable|baboon
r_volatile
r_struct
id|baboon
op_star
id|baboon
suffix:semicolon
r_void
id|baboon_irq
c_func
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|macide_ack_intr
c_func
(paren
id|ide_hwif_t
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Baboon initialization.&n; */
DECL|function|baboon_init
r_void
id|__init
id|baboon_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|macintosh_config-&gt;ident
op_ne
id|MAC_MODEL_PB190
)paren
(brace
id|baboon
op_assign
l_int|NULL
suffix:semicolon
id|baboon_present
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
id|baboon
op_assign
(paren
r_struct
id|baboon
op_star
)paren
id|BABOON_BASE
suffix:semicolon
id|baboon_present
op_assign
l_int|1
suffix:semicolon
id|baboon_active
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Baboon detected at %p&bslash;n&quot;
comma
id|baboon
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register the Baboon interrupt dispatcher on nubus slot $C.&n; */
DECL|function|baboon_register_interrupts
r_void
id|__init
id|baboon_register_interrupts
c_func
(paren
r_void
)paren
(brace
id|request_irq
c_func
(paren
id|IRQ_NUBUS_C
comma
id|baboon_irq
comma
id|IRQ_FLG_LOCK
op_or
id|IRQ_FLG_FAST
comma
l_string|&quot;baboon&quot;
comma
(paren
r_void
op_star
)paren
id|baboon
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Baboon interrupt handler. This works a lot like a VIA.&n; */
DECL|function|baboon_irq
r_void
id|baboon_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq_bit
comma
id|i
suffix:semicolon
r_int
r_char
id|events
suffix:semicolon
macro_line|#ifdef DEBUG_IRQS
id|printk
c_func
(paren
l_string|&quot;baboon_irq: mb_control %02X mb_ifr %02X mb_status %02X active %02X&bslash;n&quot;
comma
(paren
id|uint
)paren
id|baboon-&gt;mb_control
comma
(paren
id|uint
)paren
id|baboon-&gt;mb_ifr
comma
(paren
id|uint
)paren
id|baboon-&gt;mb_status
comma
id|baboon_active
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|events
op_assign
id|baboon-&gt;mb_ifr
op_amp
l_int|0x07
)paren
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|irq_bit
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
id|i
op_increment
comma
id|irq_bit
op_lshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|events
op_amp
id|irq_bit
multiline_comment|/* &amp; baboon_active*/
)paren
(brace
id|baboon_active
op_and_assign
op_complement
id|irq_bit
suffix:semicolon
id|mac_do_irq_list
c_func
(paren
id|IRQ_BABOON_0
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
id|baboon_active
op_or_assign
id|irq_bit
suffix:semicolon
id|baboon-&gt;mb_ifr
op_and_assign
op_complement
id|irq_bit
suffix:semicolon
)brace
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|baboon-&gt;mb_ifr
op_amp
l_int|0x02
)paren
id|macide_ack_intr
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* for now we need to smash all interrupts */
id|baboon-&gt;mb_ifr
op_and_assign
op_complement
id|events
suffix:semicolon
macro_line|#endif
)brace
DECL|function|baboon_irq_enable
r_void
id|baboon_irq_enable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;baboon_irq_enable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|baboon_active
op_or_assign
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|baboon_irq_disable
r_void
id|baboon_irq_disable
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_IRQUSE
id|printk
c_func
(paren
l_string|&quot;baboon_irq_disable(%d)&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
id|baboon_active
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|baboon_irq_clear
r_void
id|baboon_irq_clear
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
id|baboon-&gt;mb_ifr
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
DECL|function|baboon_irq_pending
r_int
id|baboon_irq_pending
c_func
(paren
r_int
id|irq
)paren
(brace
r_int
id|irq_idx
op_assign
id|IRQ_IDX
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
id|baboon-&gt;mb_ifr
op_amp
(paren
l_int|1
op_lshift
id|irq_idx
)paren
suffix:semicolon
)brace
eof
