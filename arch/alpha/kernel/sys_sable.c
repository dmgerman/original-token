multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_sable.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998 Richard Henderson&n; *&n; * Code supporting the Sable and Sable-Gamma systems.&n; */
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
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/core_t2.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq.h&quot;
macro_line|#include &quot;bios32.h&quot;
macro_line|#include &quot;machvec.h&quot;
multiline_comment|/*&n; *   For SABLE, which is really baroque, we manage 40 IRQ&squot;s, but the&n; *   hardware really only supports 24, not via normal ISA PIC,&n; *   but cascaded custom 8259&squot;s, etc.&n; *&t; 0-7  (char at 536)&n; *&t; 8-15 (char at 53a)&n; *&t;16-23 (char at 53c)&n; */
multiline_comment|/* Note that the vector reported by the SRM PALcode corresponds to the&n;   interrupt mask bits, but we have to manage via more normal IRQs.  */
r_static
r_struct
(brace
DECL|member|irq_to_mask
r_char
id|irq_to_mask
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|mask_to_irq
r_char
id|mask_to_irq
(braket
l_int|40
)braket
suffix:semicolon
DECL|member|shadow_mask
r_int
r_int
id|shadow_mask
suffix:semicolon
DECL|variable|sable_irq_swizzle
)brace
id|sable_irq_swizzle
op_assign
(brace
(brace
op_minus
l_int|1
comma
l_int|6
comma
op_minus
l_int|1
comma
l_int|8
comma
l_int|15
comma
l_int|12
comma
l_int|7
comma
l_int|9
comma
multiline_comment|/* pseudo PIC  0-7  */
op_minus
l_int|1
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|3
comma
op_minus
l_int|1
comma
l_int|21
comma
l_int|22
comma
multiline_comment|/* pseudo PIC  8-15 */
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
comma
op_minus
l_int|1
comma
multiline_comment|/* pseudo EISA 0-7  */
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
comma
op_minus
l_int|1
comma
multiline_comment|/* pseudo EISA 8-15 */
l_int|2
comma
l_int|1
comma
l_int|0
comma
l_int|4
comma
l_int|5
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
multiline_comment|/* pseudo PCI */
)brace
comma
(brace
l_int|34
comma
l_int|33
comma
l_int|32
comma
l_int|12
comma
l_int|35
comma
l_int|36
comma
l_int|1
comma
l_int|6
comma
multiline_comment|/* mask 0-7  */
l_int|3
comma
l_int|7
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|5
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|4
comma
multiline_comment|/* mask 8-15  */
l_int|9
comma
l_int|10
comma
l_int|11
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|14
comma
l_int|15
comma
op_minus
l_int|1
comma
multiline_comment|/* mask 16-23  */
)brace
comma
l_int|0
)brace
suffix:semicolon
r_static
r_void
DECL|function|sable_update_irq_hw
id|sable_update_irq_hw
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|unused_mask
comma
r_int
id|unmask_p
)paren
(brace
r_int
r_int
id|bit
comma
id|mask
suffix:semicolon
multiline_comment|/* The &quot;irq&quot; argument is really the irq, but we need it to&n;&t;   be the mask bit number.  Convert it now.  */
id|irq
op_assign
id|sable_irq_swizzle.irq_to_mask
(braket
id|irq
)braket
suffix:semicolon
id|bit
op_assign
l_int|1UL
op_lshift
id|irq
suffix:semicolon
id|mask
op_assign
id|sable_irq_swizzle.shadow_mask
op_or
id|bit
suffix:semicolon
r_if
c_cond
(paren
id|unmask_p
)paren
id|mask
op_and_assign
op_complement
id|bit
suffix:semicolon
id|sable_irq_swizzle.shadow_mask
op_assign
id|mask
suffix:semicolon
multiline_comment|/* The &quot;irq&quot; argument is now really the mask bit number.  */
r_if
c_cond
(paren
id|irq
op_le
l_int|7
)paren
id|outb
c_func
(paren
id|mask
comma
l_int|0x537
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|irq
op_le
l_int|15
)paren
id|outb
c_func
(paren
id|mask
op_rshift
l_int|8
comma
l_int|0x53b
)paren
suffix:semicolon
r_else
id|outb
c_func
(paren
id|mask
op_rshift
l_int|16
comma
l_int|0x53d
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|sable_ack_irq
id|sable_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/* Note that the &quot;irq&quot; here is really the mask bit number */
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|7
suffix:colon
id|outb
c_func
(paren
l_int|0xE0
op_or
(paren
id|irq
op_minus
l_int|0
)paren
comma
l_int|0x536
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE0
op_or
l_int|1
comma
l_int|0x534
)paren
suffix:semicolon
multiline_comment|/* slave 0 */
r_break
suffix:semicolon
r_case
l_int|8
dot
dot
dot
l_int|15
suffix:colon
id|outb
c_func
(paren
l_int|0xE0
op_or
(paren
id|irq
op_minus
l_int|8
)paren
comma
l_int|0x53a
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE0
op_or
l_int|3
comma
l_int|0x534
)paren
suffix:semicolon
multiline_comment|/* slave 1 */
r_break
suffix:semicolon
r_case
l_int|16
dot
dot
dot
l_int|24
suffix:colon
id|outb
c_func
(paren
l_int|0xE0
op_or
(paren
id|irq
op_minus
l_int|16
)paren
comma
l_int|0x53c
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xE0
op_or
l_int|4
comma
l_int|0x534
)paren
suffix:semicolon
multiline_comment|/* slave 2 */
r_break
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|sable_srm_device_interrupt
id|sable_srm_device_interrupt
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
multiline_comment|/* Note that the vector reported by the SRM PALcode corresponds&n;&t;   to the interrupt mask bits, but we have to manage via more&n;&t;   normal IRQs.  */
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
id|irq
op_assign
id|sable_irq_swizzle.mask_to_irq
(braket
(paren
id|ack
)paren
)braket
suffix:semicolon
macro_line|#if 0
r_if
c_cond
(paren
id|irq
op_eq
l_int|5
op_logical_or
id|irq
op_eq
l_int|9
op_logical_or
id|irq
op_eq
l_int|10
op_logical_or
id|irq
op_eq
l_int|11
op_logical_or
id|irq
op_eq
l_int|14
op_logical_or
id|irq
op_eq
l_int|15
)paren
id|printk
c_func
(paren
l_string|&quot;srm_device_interrupt: vector=0x%lx  ack=0x%x&quot;
l_string|&quot;  irq=0x%x&bslash;n&quot;
comma
id|vector
comma
id|ack
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
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
DECL|function|sable_init_irq
id|sable_init_irq
c_func
(paren
r_void
)paren
(brace
id|STANDARD_INIT_IRQ_PROLOG
suffix:semicolon
id|outb
c_func
(paren
id|alpha_irq_mask
comma
l_int|0x537
)paren
suffix:semicolon
multiline_comment|/* slave 0 */
id|outb
c_func
(paren
id|alpha_irq_mask
op_rshift
l_int|8
comma
l_int|0x53b
)paren
suffix:semicolon
multiline_comment|/* slave 1 */
id|outb
c_func
(paren
id|alpha_irq_mask
op_rshift
l_int|16
comma
l_int|0x53d
)paren
suffix:semicolon
multiline_comment|/* slave 2 */
id|outb
c_func
(paren
l_int|0x44
comma
l_int|0x535
)paren
suffix:semicolon
multiline_comment|/* enable cascades in master */
)brace
multiline_comment|/*&n; * PCI Fixup configuration for ALPHA SABLE (2100) - 2100A is different ??&n; *&n; * Summary Registers (536/53a/53c):&n; * Bit      Meaning&n; *-----------------&n; * 0        PCI slot 0&n; * 1        NCR810 (builtin)&n; * 2        TULIP (builtin)&n; * 3        mouse&n; * 4        PCI slot 1&n; * 5        PCI slot 2&n; * 6        keyboard&n; * 7        floppy&n; * 8        COM2&n; * 9        parallel port&n; *10        EISA irq 3&n; *11        EISA irq 4&n; *12        EISA irq 5&n; *13        EISA irq 6&n; *14        EISA irq 7&n; *15        COM1&n; *16        EISA irq 9&n; *17        EISA irq 10&n; *18        EISA irq 11&n; *19        EISA irq 12&n; *20        EISA irq 13&n; *21        EISA irq 14&n; *22        NC&n; *23        IIC&n; *&n; * The device to slot mapping looks like:&n; *&n; * Slot     Device&n; *  0       TULIP&n; *  1       SCSI&n; *  2       PCI-EISA bridge&n; *  3       none&n; *  4       none&n; *  5       none&n; *  6       PCI on board slot 0&n; *  7       PCI on board slot 1&n; *  8       PCI on board slot 2&n; *   &n; *&n; * This two layered interrupt approach means that we allocate IRQ 16 and &n; * above for PCI interrupts.  The IRQ relates to which bit the interrupt&n; * comes in on.  This makes interrupt processing much easier.&n; */
multiline_comment|/*&n; * NOTE: the IRQ assignments below are arbitrary, but need to be consistent&n; * with the values in the irq swizzling tables above.&n; */
r_static
r_int
id|__init
DECL|function|sable_map_irq
id|sable_map_irq
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
l_int|9
)braket
(braket
l_int|5
)braket
id|__initlocaldata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
comma
l_int|32
op_plus
l_int|0
)brace
comma
multiline_comment|/* IdSel 0,  TULIP  */
(brace
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
comma
l_int|32
op_plus
l_int|1
)brace
comma
multiline_comment|/* IdSel 1,  SCSI   */
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
multiline_comment|/* IdSel 2,  SIO   */
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
multiline_comment|/* IdSel 3,  none   */
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
multiline_comment|/* IdSel 4,  none   */
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
multiline_comment|/* IdSel 5,  none   */
(brace
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
comma
l_int|32
op_plus
l_int|2
)brace
comma
multiline_comment|/* IdSel 6,  slot 0 */
(brace
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
comma
l_int|32
op_plus
l_int|3
)brace
comma
multiline_comment|/* IdSel 7,  slot 1 */
(brace
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
comma
l_int|32
op_plus
l_int|4
)brace
comma
multiline_comment|/* IdSel 8,  slot 2 */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|0
comma
id|max_idsel
op_assign
l_int|8
comma
id|irqs_per_slot
op_assign
l_int|5
suffix:semicolon
r_return
id|COMMON_TABLE_LOOKUP
suffix:semicolon
)brace
r_void
id|__init
DECL|function|sable_pci_fixup
id|sable_pci_fixup
c_func
(paren
r_void
)paren
(brace
id|layout_all_busses
c_func
(paren
id|EISA_DEFAULT_IO_BASE
comma
id|DEFAULT_MEM_BASE
)paren
suffix:semicolon
id|common_pci_fixup
c_func
(paren
id|sable_map_irq
comma
id|common_swizzle
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vectors&n; *&n; * In order that T2_HAE_ADDRESS should be a constant, we play&n; * these games with GAMMA_BIAS.&n; */
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || !defined(CONFIG_ALPHA_GAMMA)
DECL|macro|GAMMA_BIAS
macro_line|#undef GAMMA_BIAS
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS 0
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|sable_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Sable&quot;
comma
id|DO_EV4_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_T2_IO
comma
id|DO_T2_BUS
comma
id|machine_check
suffix:colon
id|t2_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|40
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|40
)paren
comma
id|update_irq_hw
suffix:colon
id|sable_update_irq_hw
comma
id|ack_irq
suffix:colon
id|sable_ack_irq
comma
id|device_interrupt
suffix:colon
id|sable_srm_device_interrupt
comma
id|init_arch
suffix:colon
id|t2_init_arch
comma
id|init_irq
suffix:colon
id|sable_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|sable_pci_fixup
comma
id|kill_arch
suffix:colon
id|generic_kill_arch
comma
id|sys
suffix:colon
(brace
id|t2
suffix:colon
(brace
id|gamma_bias
suffix:colon
l_int|0
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|sable
)paren
macro_line|#endif
macro_line|#if defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_GAMMA)
DECL|macro|GAMMA_BIAS
macro_line|#undef GAMMA_BIAS
DECL|macro|GAMMA_BIAS
mdefine_line|#define GAMMA_BIAS _GAMMA_BIAS
r_struct
id|alpha_machine_vector
id|sable_gamma_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Sable-Gamma&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_T2_IO
comma
id|DO_T2_BUS
comma
id|machine_check
suffix:colon
id|t2_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|nr_irqs
suffix:colon
l_int|40
comma
id|irq_probe_mask
suffix:colon
id|_PROBE_MASK
c_func
(paren
l_int|40
)paren
comma
id|update_irq_hw
suffix:colon
id|sable_update_irq_hw
comma
id|ack_irq
suffix:colon
id|sable_ack_irq
comma
id|device_interrupt
suffix:colon
id|sable_srm_device_interrupt
comma
id|init_arch
suffix:colon
id|t2_init_arch
comma
id|init_irq
suffix:colon
id|sable_init_irq
comma
id|init_pit
suffix:colon
id|generic_init_pit
comma
id|pci_fixup
suffix:colon
id|sable_pci_fixup
comma
id|kill_arch
suffix:colon
id|generic_kill_arch
comma
id|sys
suffix:colon
(brace
id|t2
suffix:colon
(brace
id|gamma_bias
suffix:colon
id|_GAMMA_BIAS
)brace
)brace
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|sable_gamma
)paren
macro_line|#endif
eof