multiline_comment|/*&n; *&t;linux/arch/alpha/kernel/sys_jensen.c&n; *&n; *&t;Copyright (C) 1995 Linus Torvalds&n; *&t;Copyright (C) 1998, 1999 Richard Henderson&n; *&n; * Code supporting the Jensen.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|__EXTERN_INLINE
mdefine_line|#define __EXTERN_INLINE inline
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/jensen.h&gt;
DECL|macro|__EXTERN_INLINE
macro_line|#undef  __EXTERN_INLINE
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &quot;proto.h&quot;
macro_line|#include &quot;irq_impl.h&quot;
macro_line|#include &quot;machvec_impl.h&quot;
multiline_comment|/*&n; * Jensen is special: the vector is 0x8X0 for EISA interrupt X, and&n; * 0x9X0 for the local motherboard interrupts..&n; *&n; *&t;0x660 - NMI&n; *&n; *&t;0x800 - IRQ0  interval timer (not used, as we use the RTC timer)&n; *&t;0x810 - IRQ1  line printer (duh..)&n; *&t;0x860 - IRQ6  floppy disk&n; *&t;0x8E0 - IRQ14 SCSI controller&n; *&n; *&t;0x900 - COM1&n; *&t;0x920 - COM2&n; *&t;0x980 - keyboard&n; *&t;0x990 - mouse&n; *&n; * PCI-based systems are more sane: they don&squot;t have the local&n; * interrupts at all, and have only normal PCI interrupts from&n; * devices.  Happily it&squot;s easy enough to do a sane mapping from the&n; * Jensen..  Note that this means that we may have to do a hardware&n; * &quot;ack&quot; to a different interrupt than we report to the rest of the&n; * world.&n; */
r_static
r_void
DECL|function|jensen_local_ack
id|jensen_local_ack
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/* irq1 is supposed to be the keyboard, silly Jensen.  */
r_if
c_cond
(paren
id|irq
op_eq
l_int|7
)paren
id|i8259a_mask_and_ack_irq
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|jensen_local_irq_type
r_static
r_struct
id|hw_interrupt_type
id|jensen_local_irq_type
op_assign
(brace
r_typename
suffix:colon
l_string|&quot;LOCAL&quot;
comma
id|startup
suffix:colon
id|i8259a_startup_irq
comma
id|shutdown
suffix:colon
id|i8259a_disable_irq
comma
id|enable
suffix:colon
id|i8259a_enable_irq
comma
id|disable
suffix:colon
id|i8259a_disable_irq
comma
id|ack
suffix:colon
id|jensen_local_ack
comma
id|end
suffix:colon
id|i8259a_enable_irq
comma
)brace
suffix:semicolon
r_static
r_void
DECL|function|jensen_device_interrupt
id|jensen_device_interrupt
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
suffix:semicolon
r_switch
c_cond
(paren
id|vector
)paren
(brace
r_case
l_int|0x660
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Whee.. NMI received. Probable hardware error&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;61=%02x, 461=%02x&bslash;n&quot;
comma
id|inb
c_func
(paren
l_int|0x61
)paren
comma
id|inb
c_func
(paren
l_int|0x461
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* local device interrupts: */
r_case
l_int|0x900
suffix:colon
id|irq
op_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* com1 -&gt; irq 4 */
r_case
l_int|0x920
suffix:colon
id|irq
op_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* com2 -&gt; irq 3 */
r_case
l_int|0x980
suffix:colon
id|irq
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* kbd -&gt; irq 1 */
r_case
l_int|0x990
suffix:colon
id|irq
op_assign
l_int|9
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* mouse -&gt; irq 9 */
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|vector
OG
l_int|0x900
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unknown local interrupt %lx&bslash;n&quot;
comma
id|vector
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|irq
op_eq
l_int|1
)paren
id|irq
op_assign
l_int|7
suffix:semicolon
r_break
suffix:semicolon
)brace
id|handle_irq
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|jensen_init_irq
id|jensen_init_irq
c_func
(paren
r_void
)paren
(brace
id|init_i8259a_irqs
c_func
(paren
)paren
suffix:semicolon
id|init_rtc_irq
c_func
(paren
)paren
suffix:semicolon
id|irq_desc
(braket
l_int|1
)braket
dot
id|handler
op_assign
op_amp
id|jensen_local_irq_type
suffix:semicolon
id|irq_desc
(braket
l_int|4
)braket
dot
id|handler
op_assign
op_amp
id|jensen_local_irq_type
suffix:semicolon
id|irq_desc
(braket
l_int|3
)braket
dot
id|handler
op_assign
op_amp
id|jensen_local_irq_type
suffix:semicolon
id|irq_desc
(braket
l_int|7
)braket
dot
id|handler
op_assign
op_amp
id|jensen_local_irq_type
suffix:semicolon
id|irq_desc
(braket
l_int|9
)braket
dot
id|handler
op_assign
op_amp
id|jensen_local_irq_type
suffix:semicolon
id|common_init_isa_dma
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_void
id|__init
DECL|function|jensen_init_arch
id|jensen_init_arch
c_func
(paren
r_void
)paren
(brace
id|__direct_map_base
op_assign
l_int|0
suffix:semicolon
id|__direct_map_size
op_assign
l_int|0xffffffff
suffix:semicolon
)brace
r_static
r_void
DECL|function|jensen_machine_check
id|jensen_machine_check
(paren
id|u64
id|vector
comma
id|u64
id|la
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Machine check&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|macro|jensen_pci_tbi
mdefine_line|#define jensen_pci_tbi&t;((void*)0)
multiline_comment|/*&n; * The System Vector&n; */
DECL|variable|__initmv
r_struct
id|alpha_machine_vector
id|jensen_mv
id|__initmv
op_assign
(brace
id|vector_name
suffix:colon
l_string|&quot;Jensen&quot;
comma
id|DO_EV4_MMU
comma
id|IO_LITE
c_func
(paren
id|JENSEN
comma
id|jensen
)paren
comma
id|BUS
c_func
(paren
id|jensen
)paren
comma
id|machine_check
suffix:colon
id|jensen_machine_check
comma
id|max_dma_address
suffix:colon
id|ALPHA_MAX_DMA_ADDRESS
comma
id|rtc_port
suffix:colon
l_int|0x170
comma
id|nr_irqs
suffix:colon
l_int|16
comma
id|device_interrupt
suffix:colon
id|jensen_device_interrupt
comma
id|init_arch
suffix:colon
id|jensen_init_arch
comma
id|init_irq
suffix:colon
id|jensen_init_irq
comma
id|init_rtc
suffix:colon
id|common_init_rtc
comma
id|init_pci
suffix:colon
l_int|NULL
comma
id|kill_arch
suffix:colon
l_int|NULL
comma
)brace
suffix:semicolon
id|ALIAS_MV
c_func
(paren
id|jensen
)paren
eof
