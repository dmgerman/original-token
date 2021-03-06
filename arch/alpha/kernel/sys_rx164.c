multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_rx164.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the RX164 (PCA56+POLARIS).&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_polaris.h&gt;
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
multiline_comment|/* Bus 0, Device 0.  Nothing else matters, since we invoke the&n;   POLARIS routines directly.  */
DECL|variable|rx164_system
r_static
r_struct
id|pci_dev
id|rx164_system
suffix:semicolon
r_static
r_inline
r_void
DECL|function|rx164_update_irq_hw
id|rx164_update_irq_hw
c_func
(paren
r_int
r_int
id|mask
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|polaris_write_config_dword
c_func
(paren
op_amp
id|rx164_system
comma
l_int|0x74
comma
id|mask
)paren
suffix:semicolon
id|polaris_read_config_dword
c_func
(paren
op_amp
id|rx164_system
comma
l_int|0x74
comma
op_amp
id|temp
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|rx164_enable_irq
id|rx164_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|rx164_update_irq_hw
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
DECL|function|rx164_disable_irq
id|rx164_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|rx164_update_irq_hw
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
r_int
r_int
DECL|function|rx164_startup_irq
id|rx164_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|rx164_enable_irq
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
DECL|function|rx164_end_irq
id|rx164_end_irq
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
id|rx164_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|rx164_irq_type
r_static
r_struct
id|hw_interrupt_type
id|rx164_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;RX164&quot;
comma
id|startup
suffix:colon
id|rx164_startup_irq
comma
id|shutdown
suffix:colon
id|rx164_disable_irq
comma
id|enable
suffix:colon
id|rx164_enable_irq
comma
id|disable
suffix:colon
id|rx164_disable_irq
comma
id|ack
suffix:colon
id|rx164_disable_irq
comma
id|end
suffix:colon
id|rx164_end_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|rx164_device_interrupt
id|rx164_device_interrupt
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
id|temp
suffix:semicolon
r_int
r_int
id|pld
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary register.  On Polaris, this is&n;&t;   the DIRR register in PCI config space (offset 0x84).  */
id|polaris_read_config_dword
c_func
(paren
op_amp
id|rx164_system
comma
l_int|0x84
comma
op_amp
id|temp
)paren
suffix:semicolon
id|pld
op_assign
id|temp
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
l_int|20
)paren
(brace
id|isa_no_iack_sc_device_interrupt
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
DECL|function|rx164_init_irq
id|rx164_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|rx164_update_irq_hw
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|16
suffix:semicolon
id|i
OL
l_int|40
suffix:semicolon
op_increment
id|i
)paren
(brace
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
id|rx164_irq_type
suffix:semicolon
)brace
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
l_int|20
comma
op_amp
id|isa_cascade_irqaction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The RX164 changed its interrupt routing between pass1 and pass2...&n; *&n; * PASS1:&n; *&n; *      Slot    IDSEL   INTA    INTB    INTC    INTD    &n; *      0       6       5       10      15      20&n; *      1       7       4       9       14      19&n; *      2       5       3       8       13      18&n; *      3       9       2       7       12      17&n; *      4       10      1       6       11      16&n; *&n; * PASS2:&n; *      Slot    IDSEL   INTA    INTB    INTC    INTD    &n; *      0       5       1       7       12      17&n; *      1       6       2       8       13      18&n; *      2       8       3       9       14      19&n; *      3       9       4       10      15      20&n; *      4       10      5       11      16      6&n; *      &n; */
multiline_comment|/*&n; * IdSel       &n; *   5  32 bit PCI option slot 0&n; *   6  64 bit PCI option slot 1&n; *   7  PCI-ISA bridge&n; *   7  64 bit PCI option slot 2&n; *   9  32 bit PCI option slot 3&n; *  10  PCI-PCI bridge&n; * &n; */
r_static
r_int
id|__init
DECL|function|rx164_map_irq
id|rx164_map_irq
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
macro_line|#if 0
r_static
r_char
id|irq_tab_pass1
(braket
l_int|6
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT   INTA  INTB  INTC   INTD */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|18
)brace
comma
multiline_comment|/* IdSel 5,  slot 2 */
(brace
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|20
)brace
comma
multiline_comment|/* IdSel 6,  slot 0 */
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
l_int|9
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|19
)brace
comma
multiline_comment|/* IdSel 7,  slot 1 */
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
multiline_comment|/* IdSel 8, PCI/ISA bridge */
(brace
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|17
)brace
comma
multiline_comment|/* IdSel 9,  slot 3 */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|16
)brace
comma
multiline_comment|/* IdSel 10, slot 4 */
)brace
suffix:semicolon
macro_line|#else
r_static
r_char
id|irq_tab
(braket
l_int|6
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT   INTA  INTB  INTC   INTD */
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
l_int|6
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|16
)brace
comma
multiline_comment|/* IdSel 5,  slot 0 */
(brace
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|17
)brace
comma
multiline_comment|/* IdSel 6,  slot 1 */
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
multiline_comment|/* IdSel 7, PCI/ISA bridge */
(brace
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|8
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|18
)brace
comma
multiline_comment|/* IdSel 8,  slot 2 */
(brace
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|19
)brace
comma
multiline_comment|/* IdSel 9,  slot 3 */
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
l_int|10
comma
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|5
)brace
comma
multiline_comment|/* IdSel 10, PCI-PCI */
)brace
suffix:semicolon
macro_line|#endif
r_const
r_int
id|min_idsel
op_assign
l_int|5
comma
id|max_idsel
op_assign
l_int|10
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
multiline_comment|/* JRP - Need to figure out how to distinguish pass1 from pass2,&n;&t;   and use the correct table.  */
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|rx164_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;RX164&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_POLARIS_IO
comma
id|DO_POLARIS_BUS
comma
id|machine_check
suffix:colon
id|polaris_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|min_io_address
suffix:colon
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|40
comma
id|device_interrupt
suffix:colon
id|rx164_device_interrupt
comma
id|init_arch
suffix:colon
id|polaris_init_arch
comma
id|init_irq
suffix:colon
id|rx164_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|common_init_pci
comma
id|kill_arch
suffix:colon
l_int|NULL
comma
id|pci_map_irq
suffix:colon
id|rx164_map_irq
comma
id|pci_swizzle
suffix:colon
id|common_swizzle
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|rx164
)paren
eof
