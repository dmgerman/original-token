multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_takara.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * Code supporting the TAKARA.&n; */
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
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq.h&quot;
macro_line|#include &quot;bios32.h&quot;
macro_line|#include &quot;machvec.h&quot;
multiline_comment|/*&n; * WARNING WARNING WARNING&n; *&n; * This port is missing an update_irq_hw implementation.&n; */
r_static
r_void
DECL|function|takara_device_interrupt
id|takara_device_interrupt
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
id|flags
suffix:semicolon
r_int
id|intstatus
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The PALcode will have passed us vectors 0x800 or 0x810,&n;&t; * which are fairly arbitrary values and serve only to tell&n;&t; * us whether an interrupt has come in on IRQ0 or IRQ1. If&n;&t; * it&squot;s IRQ1 it&squot;s a PCI interrupt; if it&squot;s IRQ0, it&squot;s&n;&t; * probably ISA, but PCI interrupts can come through IRQ0&n;&t; * as well if the interrupt controller isn&squot;t in accelerated&n;&t; * mode.&n;&t; *&n;&t; * OTOH, the accelerator thing doesn&squot;t seem to be working&n;&t; * overly well, so what we&squot;ll do instead is try directly&n;&t; * examining the Master Interrupt Register to see if it&squot;s a&n;&t; * PCI interrupt, and if _not_ then we&squot;ll pass it on to the&n;&t; * ISA handler.&n;&t; */
id|intstatus
op_assign
id|inw
c_func
(paren
l_int|0x500
)paren
op_amp
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
)paren
(brace
multiline_comment|/*&n;&t;&t; * This is a PCI interrupt. Check each bit and&n;&t;&t; * despatch an interrupt if it&squot;s set.&n;&t;&t; */
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|8
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|4
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|2
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intstatus
op_amp
l_int|1
)paren
id|handle_irq
c_func
(paren
l_int|16
op_plus
l_int|0
comma
l_int|16
op_plus
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
id|isa_device_interrupt
(paren
id|vector
comma
id|regs
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|takara_init_irq
id|takara_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ctlreg
suffix:semicolon
id|STANDARD_INIT_IRQ_PROLOG
suffix:semicolon
id|ctlreg
op_assign
id|inl
c_func
(paren
l_int|0x500
)paren
suffix:semicolon
id|ctlreg
op_and_assign
op_complement
l_int|0x8000
suffix:semicolon
multiline_comment|/* return to non-accelerated mode */
id|outw
c_func
(paren
id|ctlreg
op_rshift
l_int|16
comma
l_int|0x502
)paren
suffix:semicolon
id|outw
c_func
(paren
id|ctlreg
op_amp
l_int|0xFFFF
comma
l_int|0x500
)paren
suffix:semicolon
id|ctlreg
op_assign
l_int|0x05107c00
suffix:semicolon
multiline_comment|/* enable the PCI interrupt register */
id|outw
c_func
(paren
id|ctlreg
op_rshift
l_int|16
comma
l_int|0x502
)paren
suffix:semicolon
id|outw
c_func
(paren
id|ctlreg
op_amp
l_int|0xFFFF
comma
l_int|0x500
)paren
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The Takara has PCI devices 1, 2, and 3 configured to slots 20,&n; * 19, and 18 respectively, in the default configuration. They can&n; * also be jumpered to slots 8, 7, and 6 respectively, which is fun&n; * because the SIO ISA bridge can also be slot 7. However, the SIO&n; * doesn&squot;t explicitly generate PCI-type interrupts, so we can&n; * assign it whatever the hell IRQ we like and it doesn&squot;t matter.&n; */
r_static
r_int
id|__init
DECL|function|takara_map_irq
id|takara_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|slot
comma
r_int
id|pin
)paren
(brace
r_static
r_char
id|irq_tab
(braket
l_int|15
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
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
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
)brace
comma
multiline_comment|/* slot  6 == device 3 */
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
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
)brace
comma
multiline_comment|/* slot  7 == device 2 */
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
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
)brace
comma
multiline_comment|/* slot  8 == device 1 */
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
multiline_comment|/* slot  9 == nothing */
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
multiline_comment|/* slot 10 == nothing */
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
multiline_comment|/* slot 11 == nothing */
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
multiline_comment|/* slot 12 == nothing */
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
multiline_comment|/* slot 13 == nothing */
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
multiline_comment|/* slot 14 == nothing */
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
multiline_comment|/* slot 15 == nothing */
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
multiline_comment|/* slot 16 == nothing */
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
multiline_comment|/* slot 17 == nothing */
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
l_int|3
comma
l_int|16
op_plus
l_int|3
comma
l_int|16
op_plus
l_int|3
)brace
comma
multiline_comment|/* slot 18 == device 3 */
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
l_int|2
comma
l_int|16
op_plus
l_int|2
comma
l_int|16
op_plus
l_int|2
)brace
comma
multiline_comment|/* slot 19 == device 2 */
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
l_int|1
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|1
)brace
comma
multiline_comment|/* slot 20 == device 1 */
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
l_int|20
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
id|__init
DECL|function|takara_pci_fixup
id|takara_pci_fixup
c_func
(paren
r_void
)paren
(brace
id|layout_all_busses
c_func
(paren
id|DEFAULT_IO_BASE
comma
id|DEFAULT_MEM_BASE
)paren
suffix:semicolon
id|common_pci_fixup
c_func
(paren
id|takara_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|enable_ide
c_func
(paren
l_int|0x26e
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|takara_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Takara&quot;
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
id|nr_irqs
suffix:colon
l_int|20
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|20
)paren
comma
id|update_irq_hw
suffix:colon
l_int|NULL
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|takara_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|takara_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|takara_pci_fixup
comma
id|kill_arch
suffix:colon
id|generic_kill_arch
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|takara
)paren
eof
