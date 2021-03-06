multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_sx164.c&n; *&n; *&t;Copyright (C) 1995 David A Rusling&n; *&t;Copyright (C) 1996 Jay A Estabrook&n; *&t;Copyright (C) 1998, 1999, 2000 Richard Henderson&n; *&n; * Code supporting the SX164 (PCA56+PYXIS).&n; */
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
macro_line|#include &lt;asm/core_cia.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;pci_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
r_static
r_void
id|__init
DECL|function|sx164_init_irq
id|sx164_init_irq
c_func
(paren
r_void
)paren
(brace
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
id|outb
c_func
(paren
l_int|0
comma
id|DMA2_MASK_REG
)paren
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
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Not interested in the bogus interrupts (0,3,4,5,40-47),&n;&t;   NMI (1), or HALT (2).  */
r_if
c_cond
(paren
id|alpha_using_srm
)paren
id|init_srm_irqs
c_func
(paren
l_int|40
comma
l_int|0x3f0000
)paren
suffix:semicolon
r_else
id|init_pyxis_irqs
c_func
(paren
l_int|0xff00003f0000
)paren
suffix:semicolon
id|setup_irq
c_func
(paren
l_int|16
op_plus
l_int|6
comma
op_amp
id|timer_cascade_irqaction
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * PCI Fixup configuration.&n; *&n; * Summary @ PYXIS_INT_REQ:&n; * Bit      Meaning&n; * 0        RSVD&n; * 1        NMI&n; * 2        Halt/Reset switch&n; * 3        MBZ&n; * 4        RAZ&n; * 5        RAZ&n; * 6        Interval timer (RTC)&n; * 7        PCI-ISA Bridge&n; * 8        Interrupt Line A from slot 3&n; * 9        Interrupt Line A from slot 2&n; *10        Interrupt Line A from slot 1&n; *11        Interrupt Line A from slot 0&n; *12        Interrupt Line B from slot 3&n; *13        Interrupt Line B from slot 2&n; *14        Interrupt Line B from slot 1&n; *15        Interrupt line B from slot 0&n; *16        Interrupt Line C from slot 3&n; *17        Interrupt Line C from slot 2&n; *18        Interrupt Line C from slot 1&n; *19        Interrupt Line C from slot 0&n; *20        Interrupt Line D from slot 3&n; *21        Interrupt Line D from slot 2&n; *22        Interrupt Line D from slot 1&n; *23        Interrupt Line D from slot 0&n; *&n; * IdSel       &n; *   5  32 bit PCI option slot 2&n; *   6  64 bit PCI option slot 0&n; *   7  64 bit PCI option slot 1&n; *   8  Cypress I/O&n; *   9  32 bit PCI option slot 3&n; */
r_static
r_int
id|__init
DECL|function|sx164_map_irq
id|sx164_map_irq
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
l_int|5
)braket
(braket
l_int|5
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*INT    INTA   INTB   INTC   INTD */
(brace
l_int|16
op_plus
l_int|9
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
comma
l_int|16
op_plus
l_int|21
)brace
comma
multiline_comment|/* IdSel 5 slot 2 J17 */
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
l_int|15
comma
l_int|16
op_plus
l_int|19
comma
l_int|16
op_plus
l_int|23
)brace
comma
multiline_comment|/* IdSel 6 slot 0 J19 */
(brace
l_int|16
op_plus
l_int|10
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
comma
l_int|16
op_plus
l_int|22
)brace
comma
multiline_comment|/* IdSel 7 slot 1 J18 */
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
multiline_comment|/* IdSel 8 SIO        */
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
l_int|12
comma
l_int|16
op_plus
l_int|16
comma
l_int|16
op_plus
l_int|20
)brace
multiline_comment|/* IdSel 9 slot 3 J15 */
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
r_void
id|__init
DECL|function|sx164_init_pci
id|sx164_init_pci
c_func
(paren
r_void
)paren
(brace
id|cia_init_pci
c_func
(paren
)paren
suffix:semicolon
id|SMC669_Init
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|sx164_init_arch
id|sx164_init_arch
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * OSF palcode v1.23 forgets to enable PCA56 Motion Video&n;&t; * Instructions. Let&squot;s enable it.&n;&t; * We have to check palcode revision because CSERVE interface&n;&t; * is subject to change without notice. For example, it&n;&t; * has been changed completely since v1.16 (found in MILO&n;&t; * distribution). -ink&n;&t; */
r_struct
id|percpu_struct
op_star
id|cpu
op_assign
(paren
r_struct
id|percpu_struct
op_star
)paren
(paren
(paren
r_char
op_star
)paren
id|hwrpb
op_plus
id|hwrpb-&gt;processor_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alpha_using_srm
op_logical_and
(paren
id|cpu-&gt;pal_revision
op_amp
l_int|0xffff
)paren
op_eq
l_int|0x117
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lda&t;$16,8($31)&bslash;n&quot;
l_string|&quot;call_pal 9&bslash;n&quot;
multiline_comment|/* Allow PALRES insns in kernel mode */
l_string|&quot;.long  0x64000118&bslash;n&bslash;n&quot;
multiline_comment|/* hw_mfpr $0,icsr */
l_string|&quot;ldah&t;$16,(1&lt;&lt;(19-16))($31)&bslash;n&quot;
l_string|&quot;or&t;$0,$16,$0&bslash;n&quot;
multiline_comment|/* set MVE bit */
l_string|&quot;.long  0x74000118&bslash;n&quot;
multiline_comment|/* hw_mtpr $0,icsr */
l_string|&quot;lda&t;$16,9($31)&bslash;n&quot;
l_string|&quot;call_pal 9&quot;
multiline_comment|/* Disable PALRES insns */
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;$0&quot;
comma
l_string|&quot;$16&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCA56 MVI set enabled&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|pyxis_init_arch
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|sx164_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;SX164&quot;
comma
id|DO_EV5_MMU
comma
id|DO_DEFAULT_RTC
comma
id|DO_PYXIS_IO
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
id|DEFAULT_IO_BASE
comma
id|min_mem_address
suffix:colon
id|DEFAULT_MEM_BASE
comma
id|nr_irqs
suffix:colon
l_int|48
comma
id|device_interrupt
suffix:colon
id|pyxis_device_interrupt
comma
id|init_arch
suffix:colon
id|sx164_init_arch
comma
id|init_irq
suffix:colon
id|sx164_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
id|sx164_init_pci
comma
id|kill_arch
suffix:colon
l_int|NULL
comma
id|pci_map_irq
suffix:colon
id|sx164_map_irq
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
id|sx164
)paren
eof
