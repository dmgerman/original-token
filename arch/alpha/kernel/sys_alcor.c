multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_alcor.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the ALCOR and XLT (XL-300/366/433).&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/* Note mask bit is true for ENABLED irqs.  */
DECL|variable|cached_irq_mask
r_static
r_int
r_int
id|cached_irq_mask
suffix:semicolon
r_static
r_inline
r_void
DECL|function|alcor_update_irq_hw
id|alcor_update_irq_hw
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
op_star
(paren
id|vuip
)paren
id|GRU_INT_MASK
op_assign
id|mask
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|alcor_enable_irq
id|alcor_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|alcor_update_irq_hw
c_func
(paren
id|cached_irq_mask
op_or_assign
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|alcor_disable_irq
id|alcor_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|alcor_update_irq_hw
c_func
(paren
id|cached_irq_mask
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
)paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|alcor_mask_and_ack_irq
id|alcor_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|alcor_disable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* On ALCOR/XLT, need to dismiss interrupt via GRU. */
op_star
(paren
id|vuip
)paren
id|GRU_INT_CLEAR
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|alcor_startup_irq
id|alcor_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|alcor_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|alcor_isa_mask_and_ack_irq
id|alcor_isa_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|i8259a_mask_and_ack_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/* On ALCOR/XLT, need to dismiss interrupt via GRU. */
op_star
(paren
id|vuip
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0x80000000
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|alcor_end_irq
id|alcor_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|alcor_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|alcor_irq_type
r_static
r_struct
id|hw_interrupt_type
id|alcor_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;ALCOR&quot;
comma
id|startup
suffix:colon
id|alcor_startup_irq
comma
id|shutdown
suffix:colon
id|alcor_disable_irq
comma
id|enable
suffix:colon
id|alcor_enable_irq
comma
id|disable
suffix:colon
id|alcor_disable_irq
comma
id|ack
suffix:colon
id|alcor_mask_and_ack_irq
comma
id|end
suffix:colon
id|alcor_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|alcor_device_interrupt
id|alcor_device_interrupt
c_func
(paren
r_int
r_int
id|vector
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary register of the GRU */
id|pld
op_assign
(paren
op_star
(paren
id|vuip
)paren
id|GRU_INT_REQ
)paren
op_amp
id|GRU_INT_REQ_BITS
suffix:semicolon
multiline_comment|/*&n;&t; * Now for every possible bit set, work through them and call&n;&t; * the appropriate interrupt handler.&n;&t; */
r_while
c_loop
(paren
id|pld
)paren
(brace
id|i
op_assign
id|ffz
c_func
(paren
op_complement
id|pld
)paren
suffix:semicolon
id|pld
op_and_assign
id|pld
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* clear least bit set */
r_if
c_cond
(paren
id|i
op_eq
l_int|31
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
id|handle_irq
c_func
(paren
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
)brace
r_static
r_void
id|__init
DECL|function|alcor_init_irq
id|alcor_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|srm_device_interrupt
suffix:semicolon
op_star
(paren
id|vuip
)paren
id|GRU_INT_MASK
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all disabled */
op_star
(paren
id|vuip
)paren
id|GRU_INT_EDGE
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all are level */
op_star
(paren
id|vuip
)paren
id|GRU_INT_HILO
op_assign
l_int|0x80000000U
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ISA only HI */
op_star
(paren
id|vuip
)paren
id|GRU_INT_CLEAR
op_assign
l_int|0
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* all clear */
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|48
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/* On Alcor, at least, lines 20..30 are not connected&n;&t;&t;   and can generate spurrious interrupts if we turn them&n;&t;&t;   on while IRQ probing.  */
r_if
c_cond
(paren
id|i
op_ge
l_int|16
op_plus
l_int|20
op_logical_and
id|i
op_le
l_int|16
op_plus
l_int|30
)paren
r_continue
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
id|IRQ_DISABLED
op_or
id|IRQ_LEVEL
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|alcor_irq_type
suffix:semicolon
)brace
id|i8259a_irq_type.ack
op_assign
id|alcor_isa_mask_and_ack_irq
suffix:semicolon
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|16
op_plus
l_int|31
comma
op_amp
id|isa_cascade_irqaction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ GRU_INT_REQ:&n; * Bit      Meaning&n; * 0        Interrupt Line A from slot 2&n; * 1        Interrupt Line B from slot 2&n; * 2        Interrupt Line C from slot 2&n; * 3        Interrupt Line D from slot 2&n; * 4        Interrupt Line A from slot 1&n; * 5        Interrupt line B from slot 1&n; * 6        Interrupt Line C from slot 1&n; * 7        Interrupt Line D from slot 1&n; * 8        Interrupt Line A from slot 0&n; * 9        Interrupt Line B from slot 0&n; *10        Interrupt Line C from slot 0&n; *11        Interrupt Line D from slot 0&n; *12        Interrupt Line A from slot 4&n; *13        Interrupt Line B from slot 4&n; *14        Interrupt Line C from slot 4&n; *15        Interrupt Line D from slot 4&n; *16        Interrupt Line D from slot 3&n; *17        Interrupt Line D from slot 3&n; *18        Interrupt Line D from slot 3&n; *19        Interrupt Line D from slot 3&n; *20-30     Reserved&n; *31        EISA interrupt&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  6       built-in TULIP (XLT only)&n; *  7       PCI on board slot 0&n; *  8       PCI on board slot 3&n; *  9       PCI on board slot 4&n; * 10       PCEB (PCI-EISA bridge)&n; * 11       PCI on board slot 2&n; * 12       PCI on board slot 1&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
r_static
r_int
id|__init
DECL|function|alcor_map_irq
id|alcor_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_static
r_char
id|irq_tab
(braket
l_int|7
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
multiline_comment|/* note: IDSEL 17 is XLT only */
(brace
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 17,  TULIP  */
(brace
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|11
)brace
comma
multiline_comment|/* IdSel 18,  slot 0 */
(brace
l_int|16
op_plus
l_int|16
comma
l_int|16
op_plus
l_int|16
comma
l_int|16
op_plus
l_int|17
comma
l_int|16
op_plus
l_int|18
comma
l_int|16
op_plus
l_int|19
)brace
comma
multiline_comment|/* IdSel 19,  slot 3 */
(brace
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 20,  slot 4 */
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
)brace
comma
multiline_comment|/* IdSel 21,  PCEB   */
(brace
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|3
)brace
comma
multiline_comment|/* IdSel 22,  slot 2 */
(brace
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|4
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|7
)brace
comma
multiline_comment|/* IdSel 23,  slot 1 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|6
comma
id|max_idsel
op_assign
l_int|12
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
r_static
r_void
DECL|function|alcor_kill_arch
id|alcor_kill_arch
c_func
(paren
r_int
id|mode
)paren
(brace
multiline_comment|/* Who said DEC engineer&squot;s have no sense of humor? ;-)  */
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
op_star
(paren
id|vuip
)paren
id|GRU_RESET
op_assign
l_int|0x0000dead
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The System Vectors&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_ALCOR)
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|alcor_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Alcor&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_CIA_IO
comma
id|DO_CIA_BUS
comma
id|machine_check
suffix:colon
id|cia_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|EISA_DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|CIA_DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|alcor_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|alcor_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|cia_init_pci
comma
id|kill_arch
suffix:colon
id|alcor_kill_arch
comma
id|pci_map_irq
suffix:colon
id|alcor_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
id|sys
suffix:colon
(brace
id|cia
suffix:colon
(brace
id|gru_int_req_bits
suffix:colon
id|ALCOR_GRU_INT_REQ_BITS
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|alcor
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_XLT)
r_struct
id|alpha_machine_vector
id|xlt_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;XLT&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_CIA_IO
comma
id|DO_CIA_BUS
comma
id|machine_check
suffix:colon
id|cia_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|EISA_DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|CIA_DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|alcor_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|alcor_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|cia_init_pci
comma
id|kill_arch
suffix:colon
id|alcor_kill_arch
comma
id|pci_map_irq
suffix:colon
id|alcor_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
id|sys
suffix:colon
(brace
id|cia
suffix:colon
(brace
id|gru_int_req_bits
suffix:colon
id|XLT_GRU_INT_REQ_BITS
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|xlt
)paren
macro_line|#endif
eof
