multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_cabriolet.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * Code supporting the Cabriolet (AlphaPC64), EB66+, and EB164,&n; * PC164 and LX164.&n; */
macro_line|#include &lt;linux/config.h&gt;
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
macro_line|#include &lt;asm/core_apecs.h&gt;
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &lt;asm/core_lca.h&gt;
macro_line|#include &lt;asm/core_pyxis.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq.h&quot;
macro_line|#include &quot;bios32.h&quot;
macro_line|#include &quot;machvec.h&quot;
r_static
r_void
DECL|function|cabriolet_update_irq_hw
id|cabriolet_update_irq_hw
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
id|outl
c_func
(paren
id|alpha_irq_mask
op_rshift
l_int|16
comma
l_int|0x804
)paren
suffix:semicolon
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
r_else
id|outb
c_func
(paren
id|mask
comma
l_int|0x21
)paren
suffix:semicolon
)brace
multiline_comment|/* Under SRM console, we must use the CSERVE PALcode routine to manage&n;   the interrupt mask for us.  Otherwise, the kernel/HW get out of&n;   sync with what the PALcode thinks it needs to deliver/ignore.  */
r_static
r_void
DECL|function|cabriolet_srm_update_irq_hw
id|cabriolet_srm_update_irq_hw
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
id|unmaskp
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
r_if
c_cond
(paren
id|unmaskp
)paren
id|cserve_ena
c_func
(paren
id|irq
op_minus
l_int|16
)paren
suffix:semicolon
r_else
id|cserve_dis
c_func
(paren
id|irq
op_minus
l_int|16
)paren
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
r_else
id|outb
c_func
(paren
id|mask
comma
l_int|0x21
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|cabriolet_device_interrupt
id|cabriolet_device_interrupt
c_func
(paren
r_int
r_int
id|v
comma
r_struct
id|pt_regs
op_star
id|r
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
r_int
r_int
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Read the interrupt summary registers */
id|pld
op_assign
id|inb
c_func
(paren
l_int|0x804
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x805
)paren
op_lshift
l_int|8
)paren
op_or
(paren
id|inb
c_func
(paren
l_int|0x806
)paren
op_lshift
l_int|16
)paren
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
l_int|4
)paren
(brace
id|isa_device_interrupt
c_func
(paren
id|v
comma
id|r
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
l_int|16
op_plus
id|i
comma
id|r
)paren
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|cabriolet_init_irq
id|cabriolet_init_irq
c_func
(paren
r_void
)paren
(brace
id|STANDARD_INIT_IRQ_PROLOG
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
)paren
(brace
id|alpha_mv.update_irq_hw
op_assign
id|cabriolet_srm_update_irq_hw
suffix:semicolon
id|alpha_mv.device_interrupt
op_assign
id|srm_device_interrupt
suffix:semicolon
)brace
r_else
(brace
id|outl
c_func
(paren
id|alpha_irq_mask
op_rshift
l_int|16
comma
l_int|0x804
)paren
suffix:semicolon
)brace
id|enable_irq
c_func
(paren
l_int|16
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/* enable SIO cascade */
id|enable_irq
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* enable cascade */
)brace
multiline_comment|/*&n; * The EB66+ is very similar to the EB66 except that it does not have&n; * the on-board NCR and Tulip chips.  In the code below, I have used&n; * slot number to refer to the id select line and *not* the slot&n; * number used in the EB66+ documentation.  However, in the table,&n; * I&squot;ve given the slot number, the id select line and the Jxx number&n; * that&squot;s printed on the board.  The interrupt pins from the PCI slots&n; * are wired into 3 interrupt summary registers at 0x804, 0x805 and&n; * 0x806 ISA.&n; *&n; * In the table, -1 means don&squot;t assign an IRQ number.  This is usually&n; * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.&n; */
r_static
r_inline
r_int
id|__init
DECL|function|eb66p_map_irq
id|eb66p_map_irq
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
l_int|5
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
multiline_comment|/*INT  INTA  INTB  INTC   INTD */
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
l_int|5
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 6,  slot 0, J25 */
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
l_int|10
comma
l_int|16
op_plus
l_int|14
)brace
comma
multiline_comment|/* IdSel 7,  slot 1, J26 */
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
multiline_comment|/* IdSel 8,  SIO         */
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
l_int|11
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 9,  slot 2, J27 */
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
l_int|12
comma
l_int|16
op_plus
l_int|6
)brace
multiline_comment|/* IdSel 10, slot 3, J28 */
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
l_int|10
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
r_inline
r_void
id|__init
DECL|function|eb66p_pci_fixup
id|eb66p_pci_fixup
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
id|APECS_AND_LCA_DEFAULT_MEM_BASE
)paren
suffix:semicolon
id|common_pci_fixup
c_func
(paren
id|eb66p_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|enable_ide
c_func
(paren
l_int|0x398
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The AlphaPC64 is very similar to the EB66+ except that its slots&n; * are numbered differently.  In the code below, I have used slot&n; * number to refer to the id select line and *not* the slot number&n; * used in the AlphaPC64 documentation.  However, in the table, I&squot;ve&n; * given the slot number, the id select line and the Jxx number that&squot;s&n; * printed on the board.  The interrupt pins from the PCI slots are&n; * wired into 3 interrupt summary registers at 0x804, 0x805 and 0x806&n; * ISA.&n; *&n; * In the table, -1 means don&squot;t assign an IRQ number.  This is usually&n; * because it is the Saturn IO (SIO) PCI/ISA Bridge Chip.&n; */
r_static
r_inline
r_int
id|__init
DECL|function|cabriolet_map_irq
id|cabriolet_map_irq
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
l_int|5
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
multiline_comment|/*INT   INTA  INTB  INTC   INTD */
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
l_int|11
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel 5,  slot 2, J21 */
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
l_int|5
comma
l_int|16
op_plus
l_int|9
comma
l_int|16
op_plus
l_int|13
)brace
comma
multiline_comment|/* IdSel 6,  slot 0, J19 */
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
l_int|10
comma
l_int|16
op_plus
l_int|14
)brace
comma
multiline_comment|/* IdSel 7,  slot 1, J20 */
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
multiline_comment|/* IdSel 8,  SIO         */
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
l_int|12
comma
l_int|16
op_plus
l_int|16
)brace
multiline_comment|/* IdSel 9,  slot 3, J22 */
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
l_int|9
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
r_inline
r_void
id|__init
DECL|function|cabriolet_pci_fixup
id|cabriolet_pci_fixup
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
id|APECS_AND_LCA_DEFAULT_MEM_BASE
)paren
suffix:semicolon
id|common_pci_fixup
c_func
(paren
id|cabriolet_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|enable_ide
c_func
(paren
l_int|0x398
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
id|__init
DECL|function|eb164_pci_fixup
id|eb164_pci_fixup
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
id|cabriolet_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|enable_ide
c_func
(paren
l_int|0x398
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The PC164 and LX164 have 19 PCI interrupts, four from each of the four&n; * PCI slots, the SIO, PCI/IDE, and USB.&n; * &n; * Each of the interrupts can be individually masked. This is&n; * accomplished by setting the appropriate bit in the mask register.&n; * A bit is set by writing a &quot;1&quot; to the desired position in the mask&n; * register and cleared by writing a &quot;0&quot;. There are 3 mask registers&n; * located at ISA address 804h, 805h and 806h.&n; * &n; * An I/O read at ISA address 804h, 805h, 806h will return the&n; * state of the 11 PCI interrupts and not the state of the MASKED&n; * interrupts.&n; * &n; * Note: A write to I/O 804h, 805h, and 806h the mask register will be&n; * updated.&n; * &n; * &n; * &t;&t;&t;&t;ISA DATA&lt;7:0&gt;&n; * ISA     +--------------------------------------------------------------+&n; * ADDRESS |   7   |   6   |   5   |   4   |   3   |   2  |   1   |   0   |&n; *         +==============================================================+&n; * 0x804   | INTB0 |  USB  |  IDE  |  SIO  | INTA3 |INTA2 | INTA1 | INTA0 |&n; *         +--------------------------------------------------------------+&n; * 0x805   | INTD0 | INTC3 | INTC2 | INTC1 | INTC0 |INTB3 | INTB2 | INTB1 |&n; *         +--------------------------------------------------------------+&n; * 0x806   | Rsrv  | Rsrv  | Rsrv  | Rsrv  | Rsrv  |INTD3 | INTD2 | INTD1 |&n; *         +--------------------------------------------------------------+&n; *         * Rsrv = reserved bits&n; *         Note: The mask register is write-only.&n; * &n; * IdSel&t;&n; *   5&t; 32 bit PCI option slot 2&n; *   6&t; 64 bit PCI option slot 0&n; *   7&t; 64 bit PCI option slot 1&n; *   8&t; Saturn I/O&n; *   9&t; 32 bit PCI option slot 3&n; *  10&t; USB&n; *  11&t; IDE&n; * &n; */
r_static
r_inline
r_int
id|__init
DECL|function|alphapc164_map_irq
id|alphapc164_map_irq
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
l_int|7
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
multiline_comment|/*INT   INTA  INTB   INTC   INTD */
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
l_int|9
comma
l_int|16
op_plus
l_int|13
comma
l_int|16
op_plus
l_int|17
)brace
comma
multiline_comment|/* IdSel  5, slot 2, J20 */
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
l_int|7
comma
l_int|16
op_plus
l_int|11
comma
l_int|16
op_plus
l_int|15
)brace
comma
multiline_comment|/* IdSel  6, slot 0, J29 */
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
l_int|8
comma
l_int|16
op_plus
l_int|12
comma
l_int|16
op_plus
l_int|16
)brace
comma
multiline_comment|/* IdSel  7, slot 1, J26 */
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
multiline_comment|/* IdSel  8, SIO */
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
l_int|10
comma
l_int|16
op_plus
l_int|14
comma
l_int|16
op_plus
l_int|18
)brace
comma
multiline_comment|/* IdSel  9, slot 3, J19 */
(brace
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
comma
l_int|16
op_plus
l_int|6
)brace
comma
multiline_comment|/* IdSel 10, USB */
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
l_int|5
comma
l_int|16
op_plus
l_int|5
comma
l_int|16
op_plus
l_int|5
)brace
multiline_comment|/* IdSel 11, IDE */
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
l_int|11
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
r_inline
r_void
id|__init
DECL|function|alphapc164_pci_fixup
id|alphapc164_pci_fixup
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
id|alphapc164_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
id|SMC93x_Init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_CABRIOLET)
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|cabriolet_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Cabriolet&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_APECS_IO
comma
id|DO_APECS_BUS
comma
id|machine_check
suffix:colon
id|apecs_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|35
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|35
)paren
comma
id|update_irq_hw
suffix:colon
id|cabriolet_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|cabriolet_device_interrupt
comma
id|init_arch
suffix:colon
id|apecs_init_arch
comma
id|init_irq
suffix:colon
id|cabriolet_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|cabriolet_pci_fixup
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
id|cabriolet
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB164)
r_struct
id|alpha_machine_vector
id|eb164_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;EB164&quot;
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
l_int|35
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|35
)paren
comma
id|update_irq_hw
suffix:colon
id|cabriolet_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|cabriolet_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|cabriolet_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|eb164_pci_fixup
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
id|eb164
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_EB66P)
r_struct
id|alpha_machine_vector
id|eb66p_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;EB66+&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_LCA_IO
comma
id|DO_LCA_BUS
comma
id|machine_check
suffix:colon
id|lca_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|35
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|35
)paren
comma
id|update_irq_hw
suffix:colon
id|cabriolet_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|cabriolet_device_interrupt
comma
id|init_arch
suffix:colon
id|lca_init_arch
comma
id|init_irq
suffix:colon
id|cabriolet_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|eb66p_pci_fixup
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
id|eb66p
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_LX164)
r_struct
id|alpha_machine_vector
id|lx164_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;LX164&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_PYXIS_IO
comma
id|DO_PYXIS_BUS
comma
id|machine_check
suffix:colon
id|pyxis_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|35
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|35
)paren
comma
id|update_irq_hw
suffix:colon
id|cabriolet_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|cabriolet_device_interrupt
comma
id|init_arch
suffix:colon
id|pyxis_init_arch
comma
id|init_irq
suffix:colon
id|cabriolet_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|alphapc164_pci_fixup
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
id|lx164
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_PC164)
r_struct
id|alpha_machine_vector
id|pc164_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;PC164&quot;
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
l_int|35
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|35
)paren
comma
id|update_irq_hw
suffix:colon
id|cabriolet_update_irq_hw
comma
id|ack_irq
suffix:colon
id|generic_ack_irq
comma
id|device_interrupt
suffix:colon
id|cabriolet_device_interrupt
comma
id|init_arch
suffix:colon
id|cia_init_arch
comma
id|init_irq
suffix:colon
id|cabriolet_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|alphapc164_pci_fixup
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
id|pc164
)paren
macro_line|#endif
eof
