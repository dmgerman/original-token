multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_dp264.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * Code supporting the DP264 (EV6+TSUNAMI).&n; */
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
macro_line|#include &lt;asm/pci.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_tsunami.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq.h&quot;
macro_line|#include &quot;bios32.h&quot;
macro_line|#include &quot;machvec.h&quot;
multiline_comment|/*&n; * HACK ALERT! only CPU#0 is used currently&n; */
r_static
r_void
DECL|function|dp264_update_irq_hw
id|dp264_update_irq_hw
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
comma
r_int
id|unmask_p
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ge
l_int|16
)paren
(brace
r_volatile
r_int
r_int
op_star
id|csr
suffix:semicolon
r_if
c_cond
(paren
id|TSUNAMI_bootcpu
OL
l_int|2
)paren
r_if
c_cond
(paren
op_logical_neg
id|TSUNAMI_bootcpu
)paren
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim0.csr
suffix:semicolon
r_else
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim1.csr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|TSUNAMI_bootcpu
op_eq
l_int|2
)paren
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim2.csr
suffix:semicolon
r_else
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim3.csr
suffix:semicolon
op_star
id|csr
op_assign
op_complement
id|mask
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|csr
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|irq
op_ge
l_int|8
)paren
id|outb
c_func
(paren
id|mask
op_rshift
l_int|8
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* ISA PIC2 */
r_else
id|outb
c_func
(paren
id|mask
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* ISA PIC1 */
)brace
r_static
r_void
DECL|function|dp264_device_interrupt
id|dp264_device_interrupt
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
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;dp264_device_interrupt: NOT IMPLEMENTED YET!! &bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|pld
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the interrupt summary register of TSUNAMI */
id|pld
op_assign
id|TSUNAMI_cchip-&gt;dir0.csr
suffix:semicolon
multiline_comment|/*&n;         * Now for every possible bit set, work through them and call&n;         * the appropriate interrupt handler.&n;         */
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
l_int|55
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
multiline_comment|/* if not timer int */
id|handle_irq
c_func
(paren
l_int|16
op_plus
id|i
comma
l_int|16
op_plus
id|i
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#if 0
id|TSUNAMI_cchip-&gt;dir0.csr
op_assign
l_int|1UL
op_lshift
id|i
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
id|tmp
op_assign
id|TSUNAMI_cchip-&gt;dir0.csr
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
)brace
r_static
r_void
DECL|function|dp264_srm_device_interrupt
id|dp264_srm_device_interrupt
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
id|irq
comma
id|ack
suffix:semicolon
id|ack
op_assign
id|irq
op_assign
(paren
id|vector
op_minus
l_int|0x800
)paren
op_rshift
l_int|4
suffix:semicolon
multiline_comment|/*&n;         * The DP264 SRM console reports PCI interrupts with a vector&n;&t; * 0x100 *higher* than one might expect, as PCI IRQ 0 (ie bit 0)&n;&t; * shows up as IRQ 16, etc, etc. We adjust it down by 16 to have&n;&t; * it line up with the actual bit numbers from the DIM registers,&n;&t; * which is how we manage the interrupts/mask. Sigh...&n;         */
r_if
c_cond
(paren
id|irq
op_ge
l_int|32
)paren
id|ack
op_assign
id|irq
op_assign
id|irq
op_minus
l_int|16
suffix:semicolon
id|handle_irq
c_func
(paren
id|irq
comma
id|ack
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|dp264_init_irq
id|dp264_init_irq
c_func
(paren
r_void
)paren
(brace
r_volatile
r_int
r_int
op_star
id|csr
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|DMA1_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0
comma
id|DMA2_RESET_REG
)paren
suffix:semicolon
id|outb
c_func
(paren
id|DMA_MODE_CASCADE
comma
id|DMA2_MODE_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|alpha_mv.device_interrupt
op_assign
id|dp264_srm_device_interrupt
suffix:semicolon
r_if
c_cond
(paren
id|TSUNAMI_bootcpu
OL
l_int|2
)paren
r_if
c_cond
(paren
op_logical_neg
id|TSUNAMI_bootcpu
)paren
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim0.csr
suffix:semicolon
r_else
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim1.csr
suffix:semicolon
r_else
r_if
c_cond
(paren
id|TSUNAMI_bootcpu
op_eq
l_int|2
)paren
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim2.csr
suffix:semicolon
r_else
id|csr
op_assign
op_amp
id|TSUNAMI_cchip-&gt;dim3.csr
suffix:semicolon
multiline_comment|/* Note invert on MASK bits.  */
op_star
id|csr
op_assign
op_complement
(paren
id|alpha_irq_mask
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
op_star
id|csr
suffix:semicolon
id|enable_irq
c_func
(paren
l_int|55
)paren
suffix:semicolon
multiline_comment|/* Enable CYPRESS interrupt controller (ISA).  */
id|enable_irq
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ TSUNAMI_CSR_DIM0:&n; * Bit      Meaning&n; * 0-17     Unused&n; *18        Interrupt SCSI B (Adaptec 7895 builtin)&n; *19        Interrupt SCSI A (Adaptec 7895 builtin)&n; *20        Interrupt Line D from slot 2 PCI0&n; *21        Interrupt Line C from slot 2 PCI0&n; *22        Interrupt Line B from slot 2 PCI0&n; *23        Interrupt Line A from slot 2 PCI0&n; *24        Interrupt Line D from slot 1 PCI0&n; *25        Interrupt Line C from slot 1 PCI0&n; *26        Interrupt Line B from slot 1 PCI0&n; *27        Interrupt Line A from slot 1 PCI0&n; *28        Interrupt Line D from slot 0 PCI0&n; *29        Interrupt Line C from slot 0 PCI0&n; *30        Interrupt Line B from slot 0 PCI0&n; *31        Interrupt Line A from slot 0 PCI0&n; *&n; *32        Interrupt Line D from slot 3 PCI1&n; *33        Interrupt Line C from slot 3 PCI1&n; *34        Interrupt Line B from slot 3 PCI1&n; *35        Interrupt Line A from slot 3 PCI1&n; *36        Interrupt Line D from slot 2 PCI1&n; *37        Interrupt Line C from slot 2 PCI1&n; *38        Interrupt Line B from slot 2 PCI1&n; *39        Interrupt Line A from slot 2 PCI1&n; *40        Interrupt Line D from slot 1 PCI1&n; *41        Interrupt Line C from slot 1 PCI1&n; *42        Interrupt Line B from slot 1 PCI1&n; *43        Interrupt Line A from slot 1 PCI1&n; *44        Interrupt Line D from slot 0 PCI1&n; *45        Interrupt Line C from slot 0 PCI1&n; *46        Interrupt Line B from slot 0 PCI1&n; *47        Interrupt Line A from slot 0 PCI1&n; *48-52     Unused&n; *53        PCI0 NMI (from Cypress)&n; *54        PCI0 SMI INT (from Cypress)&n; *55        PCI0 ISA Interrupt (from Cypress)&n; *56-60     Unused&n; *61        PCI1 Bus Error&n; *62        PCI0 Bus Error&n; *63        Reserved&n; *&n; * IdSel&t;&n; *   5&t; Cypress Bridge I/O&n; *   6&t; SCSI Adaptec builtin&n; *   7&t; 64 bit PCI option slot 0 (all busses)&n; *   8&t; 64 bit PCI option slot 1 (all busses)&n; *   9&t; 64 bit PCI option slot 2 (all busses)&n; *  10&t; 64 bit PCI option slot 3 (not bus 0)&n; */
r_static
r_int
id|__init
DECL|function|dp264_map_irq
id|dp264_map_irq
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
l_int|6
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
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
multiline_comment|/* IdSel 5 ISA Bridge */
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
multiline_comment|/* IdSel 6 SCSI builtin*/
(brace
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|15
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|12
)brace
comma
multiline_comment|/* IdSel 7 slot 0 */
(brace
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|10
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|8
)brace
comma
multiline_comment|/* IdSel 8 slot 1 */
(brace
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|7
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|4
)brace
comma
multiline_comment|/* IdSel 9 slot 2 */
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
l_int|2
comma
l_int|16
op_plus
l_int|1
comma
l_int|16
op_plus
l_int|0
)brace
multiline_comment|/* IdSel 10 slot 3 */
)brace
suffix:semicolon
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
r_int
id|irq
op_assign
id|COMMON_TABLE_LOOKUP
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
id|irq
op_add_assign
l_int|16
op_star
id|bus2hose
(braket
id|dev-&gt;bus-&gt;number
)braket
op_member_access_from_pointer
id|pci_hose_index
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|dp264_pci_fixup
id|dp264_pci_fixup
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
id|dp264_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|SMC669_Init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|dp264_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;DP264&quot;
comma
id|DO_EV6_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_TSUNAMI_IO
comma
id|DO_TSUNAMI_BUS
comma
id|machine_check
suffix:colon
id|tsunami_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|64
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|64
)paren
comma
id|update_irq_hw
suffix:colon
id|dp264_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|dp264_device_interrupt
comma
id|init_arch
suffix:colon
id|tsunami_init_arch
comma
id|init_irq
suffix:colon
id|dp264_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|dp264_pci_fixup
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
id|dp264
)paren
eof