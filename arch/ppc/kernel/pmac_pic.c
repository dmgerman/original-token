macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/openpic.h&gt;
macro_line|#include &lt;asm/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &quot;pmac_pic.h&quot;
DECL|struct|pmac_irq_hw
multiline_comment|/* pmac */
r_struct
id|pmac_irq_hw
(brace
DECL|member|flag
r_int
r_int
id|flag
suffix:semicolon
DECL|member|enable
r_int
r_int
id|enable
suffix:semicolon
DECL|member|ack
r_int
r_int
id|ack
suffix:semicolon
DECL|member|level
r_int
r_int
id|level
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* XXX these addresses should be obtained from the device tree */
DECL|variable|pmac_irq_hw
r_static
r_volatile
r_struct
id|pmac_irq_hw
op_star
id|pmac_irq_hw
(braket
l_int|4
)braket
op_assign
(brace
(paren
r_struct
id|pmac_irq_hw
op_star
)paren
l_int|0xf3000020
comma
(paren
r_struct
id|pmac_irq_hw
op_star
)paren
l_int|0xf3000010
comma
(paren
r_struct
id|pmac_irq_hw
op_star
)paren
l_int|0xf4000020
comma
(paren
r_struct
id|pmac_irq_hw
op_star
)paren
l_int|0xf4000010
comma
)brace
suffix:semicolon
DECL|variable|max_irqs
r_static
r_int
id|max_irqs
suffix:semicolon
DECL|variable|max_real_irqs
r_static
r_int
id|max_real_irqs
suffix:semicolon
DECL|variable|has_openpic
r_static
r_int
id|has_openpic
op_assign
l_int|0
suffix:semicolon
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 10000000
DECL|macro|GATWICK_IRQ_POOL_SIZE
mdefine_line|#define GATWICK_IRQ_POOL_SIZE        10
DECL|variable|gatwick_int_pool
r_static
r_struct
id|interrupt_info
id|gatwick_int_pool
(braket
id|GATWICK_IRQ_POOL_SIZE
)braket
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_read_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
op_star
id|val
)paren
suffix:semicolon
r_extern
r_int
id|pmac_pcibios_write_config_word
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev_fn
comma
r_int
r_char
id|offset
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|function|pmac_openpic_mask_irq
r_static
r_void
id|pmac_openpic_mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|openpic_disable_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|function|pmac_openpic_unmask_irq
r_static
r_void
id|pmac_openpic_unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|openpic_enable_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|variable|pmac_open_pic
r_struct
id|hw_interrupt_type
id|pmac_open_pic
op_assign
(brace
l_string|&quot; OpenPIC  &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|pmac_openpic_unmask_irq
comma
id|pmac_openpic_mask_irq
comma
id|pmac_openpic_mask_irq
comma
l_int|0
)brace
suffix:semicolon
DECL|function|pmac_mask_and_ack_irq
r_static
r_void
id|__pmac
id|pmac_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|bit
op_assign
l_int|1UL
op_lshift
(paren
id|irq_nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_int
id|i
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|irq_nr
op_ge
id|max_irqs
)paren
r_return
suffix:semicolon
id|clear_bit
c_func
(paren
id|irq_nr
comma
id|ppc_cached_irq_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_clear_bit
c_func
(paren
id|irq_nr
comma
id|ppc_lost_interrupts
)paren
)paren
id|atomic_dec
c_func
(paren
op_amp
id|ppc_n_lost_interrupts
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|ack
comma
id|bit
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|enable
comma
id|ppc_cached_irq_mask
(braket
id|i
)braket
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|ack
comma
id|bit
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* make sure ack gets to controller before we enable&n;                   interrupts */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|in_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
)paren
op_amp
id|bit
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|pmac_set_irq_mask
r_static
r_void
id|__pmac
id|pmac_set_irq_mask
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_int
r_int
id|bit
op_assign
l_int|1UL
op_lshift
(paren
id|irq_nr
op_amp
l_int|0x1f
)paren
suffix:semicolon
r_int
id|i
op_assign
id|irq_nr
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|irq_nr
op_ge
id|max_irqs
)paren
r_return
suffix:semicolon
multiline_comment|/* enable unmasked interrupts */
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|enable
comma
id|ppc_cached_irq_mask
(braket
id|i
)braket
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* make sure mask gets to controller before we&n;                   return to user */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|in_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|enable
)paren
op_amp
id|bit
)paren
op_ne
(paren
id|ppc_cached_irq_mask
(braket
id|i
)braket
op_amp
id|bit
)paren
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/*&n;         * Unfortunately, setting the bit in the enable register&n;         * when the device interrupt is already on *doesn&squot;t* set&n;         * the bit in the flag register or request another interrupt.&n;         */
r_if
c_cond
(paren
(paren
id|bit
op_amp
id|ppc_cached_irq_mask
(braket
id|i
)braket
)paren
op_logical_and
(paren
id|ld_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|level
)paren
op_amp
id|bit
)paren
op_logical_and
op_logical_neg
(paren
id|ld_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
)paren
op_amp
id|bit
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|irq_nr
comma
id|ppc_lost_interrupts
)paren
)paren
id|atomic_inc
c_func
(paren
op_amp
id|ppc_n_lost_interrupts
)paren
suffix:semicolon
)brace
)brace
DECL|function|pmac_mask_irq
r_static
r_void
id|__pmac
id|pmac_mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|clear_bit
c_func
(paren
id|irq_nr
comma
id|ppc_cached_irq_mask
)paren
suffix:semicolon
id|pmac_set_irq_mask
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pmac_unmask_irq
r_static
r_void
id|__pmac
id|pmac_unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
id|set_bit
c_func
(paren
id|irq_nr
comma
id|ppc_cached_irq_mask
)paren
suffix:semicolon
id|pmac_set_irq_mask
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|variable|pmac_pic
r_struct
id|hw_interrupt_type
id|pmac_pic
op_assign
(brace
l_string|&quot; PMAC-PIC &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|pmac_unmask_irq
comma
id|pmac_mask_irq
comma
id|pmac_mask_and_ack_irq
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gatwick_pic
r_struct
id|hw_interrupt_type
id|gatwick_pic
op_assign
(brace
l_string|&quot; GATWICK  &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|pmac_unmask_irq
comma
id|pmac_mask_irq
comma
id|pmac_mask_and_ack_irq
comma
l_int|0
)brace
suffix:semicolon
DECL|function|gatwick_action
r_static
r_void
id|gatwick_action
c_func
(paren
r_int
id|cpl
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
id|irq
comma
id|bits
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
id|max_irqs
op_minus
l_int|1
suffix:semicolon
id|irq
OG
id|max_real_irqs
suffix:semicolon
id|irq
op_sub_assign
l_int|32
)paren
(brace
r_int
id|i
op_assign
id|irq
op_rshift
l_int|5
suffix:semicolon
id|bits
op_assign
id|ld_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
)paren
op_or
id|ppc_lost_interrupts
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|irq
op_sub_assign
id|cntlzw
c_func
(paren
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* The previous version of this code allowed for this case, we&n;&t; * don&squot;t.  Put this here to check for it.&n;&t; * -- Cort&n;&t; */
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_ne
op_amp
id|gatwick_pic
)paren
id|printk
c_func
(paren
l_string|&quot;gatwick irq not from gatwick pic&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|irq
)paren
suffix:semicolon
)brace
r_int
DECL|function|pmac_get_irq
id|pmac_get_irq
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
r_int
id|bits
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __SMP__
multiline_comment|/* IPI&squot;s are a hack on the powersurge -- Cort */
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_ne
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_XMON
r_static
r_int
id|xmon_2nd
suffix:semicolon
r_if
c_cond
(paren
id|xmon_2nd
)paren
id|xmon
c_func
(paren
id|regs
)paren
suffix:semicolon
macro_line|#endif
id|smp_message_recv
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* ignore, already handled */
)brace
(brace
r_int
r_int
id|loops
op_assign
id|MAXCOUNT
suffix:semicolon
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
op_amp
id|global_irq_lock
)paren
)paren
(brace
r_if
c_cond
(paren
id|smp_processor_id
c_func
(paren
)paren
op_eq
id|global_irq_holder
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;uh oh, interrupt while we hold global irq lock!&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loops
op_decrement
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;do_IRQ waiting for irq lock (holder=%d)&bslash;n&quot;
comma
id|global_irq_holder
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|xmon
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
)brace
macro_line|#endif /* __SMP__ */
multiline_comment|/* Yeah, I know, this could be a separate do_IRQ function */
r_if
c_cond
(paren
id|has_openpic
)paren
(brace
id|irq
op_assign
id|openpic_irq
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
id|OPENPIC_VEC_SPURIOUS
)paren
multiline_comment|/* We get those when doing polled ADB requests,&n;&t;&t;&t; * using -2 is a temp hack to disable the printk&n;&t;&t;&t; */
id|irq
op_assign
op_minus
l_int|2
suffix:semicolon
multiline_comment|/*-1; */
r_else
id|openpic_eoi
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|irq
op_assign
id|max_real_irqs
op_minus
l_int|1
suffix:semicolon
id|irq
OG
l_int|0
suffix:semicolon
id|irq
op_sub_assign
l_int|32
)paren
(brace
r_int
id|i
op_assign
id|irq
op_rshift
l_int|5
suffix:semicolon
id|bits
op_assign
id|ld_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|flag
)paren
op_or
id|ppc_lost_interrupts
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|irq
op_sub_assign
id|cntlzw
c_func
(paren
id|bits
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/* This routine will fix some missing interrupt values in the device tree&n; * on the gatwick mac-io controller used by some PowerBooks&n; */
r_static
r_void
id|__init
DECL|function|pmac_fix_gatwick_interrupts
id|pmac_fix_gatwick_interrupts
c_func
(paren
r_struct
id|device_node
op_star
id|gw
comma
r_int
id|irq_base
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_int
id|count
suffix:semicolon
id|memset
c_func
(paren
id|gatwick_int_pool
comma
l_int|0
comma
r_sizeof
(paren
id|gatwick_int_pool
)paren
)paren
suffix:semicolon
id|node
op_assign
id|gw-&gt;child
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|node
)paren
(brace
multiline_comment|/* Fix SCC */
r_if
c_cond
(paren
id|strcasecmp
c_func
(paren
id|node-&gt;name
comma
l_string|&quot;escc&quot;
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|node-&gt;child
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;child-&gt;n_intrs
OL
l_int|3
)paren
(brace
id|node-&gt;child-&gt;intrs
op_assign
op_amp
id|gatwick_int_pool
(braket
id|count
)braket
suffix:semicolon
id|count
op_add_assign
l_int|3
suffix:semicolon
)brace
id|node-&gt;child-&gt;n_intrs
op_assign
l_int|3
suffix:semicolon
id|node-&gt;child-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|15
op_plus
id|irq_base
suffix:semicolon
id|node-&gt;child-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
op_assign
l_int|4
op_plus
id|irq_base
suffix:semicolon
id|node-&gt;child-&gt;intrs
(braket
l_int|2
)braket
dot
id|line
op_assign
l_int|5
op_plus
id|irq_base
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: fixed SCC on second controller (%d,%d,%d)&bslash;n&quot;
comma
id|node-&gt;child-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
comma
id|node-&gt;child-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
comma
id|node-&gt;child-&gt;intrs
(braket
l_int|2
)braket
dot
id|line
)paren
suffix:semicolon
)brace
multiline_comment|/* Fix media-bay &amp; left SWIM */
r_if
c_cond
(paren
id|strcasecmp
c_func
(paren
id|node-&gt;name
comma
l_string|&quot;media-bay&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_struct
id|device_node
op_star
id|ya_node
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;n_intrs
op_eq
l_int|0
)paren
id|node-&gt;intrs
op_assign
op_amp
id|gatwick_int_pool
(braket
id|count
op_increment
)braket
suffix:semicolon
id|node-&gt;n_intrs
op_assign
l_int|1
suffix:semicolon
id|node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|29
op_plus
id|irq_base
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: fixed media-bay on second controller (%d)&bslash;n&quot;
comma
id|node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
)paren
suffix:semicolon
id|ya_node
op_assign
id|node-&gt;child
suffix:semicolon
r_while
c_loop
(paren
id|ya_node
)paren
(brace
r_if
c_cond
(paren
id|strcasecmp
c_func
(paren
id|ya_node-&gt;name
comma
l_string|&quot;floppy&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ya_node-&gt;n_intrs
OL
l_int|2
)paren
(brace
id|ya_node-&gt;intrs
op_assign
op_amp
id|gatwick_int_pool
(braket
id|count
)braket
suffix:semicolon
id|count
op_add_assign
l_int|2
suffix:semicolon
)brace
id|ya_node-&gt;n_intrs
op_assign
l_int|2
suffix:semicolon
id|ya_node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|19
op_plus
id|irq_base
suffix:semicolon
id|ya_node-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
op_assign
l_int|1
op_plus
id|irq_base
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: fixed floppy on second controller (%d,%d)&bslash;n&quot;
comma
id|ya_node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
comma
id|ya_node-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcasecmp
c_func
(paren
id|ya_node-&gt;name
comma
l_string|&quot;ata4&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|ya_node-&gt;n_intrs
OL
l_int|2
)paren
(brace
id|ya_node-&gt;intrs
op_assign
op_amp
id|gatwick_int_pool
(braket
id|count
)braket
suffix:semicolon
id|count
op_add_assign
l_int|2
suffix:semicolon
)brace
id|ya_node-&gt;n_intrs
op_assign
l_int|2
suffix:semicolon
id|ya_node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|14
op_plus
id|irq_base
suffix:semicolon
id|ya_node-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
op_assign
l_int|3
op_plus
id|irq_base
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: fixed ide on second controller (%d,%d)&bslash;n&quot;
comma
id|ya_node-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
comma
id|ya_node-&gt;intrs
(braket
l_int|1
)braket
dot
id|line
)paren
suffix:semicolon
)brace
id|ya_node
op_assign
id|ya_node-&gt;sibling
suffix:semicolon
)brace
)brace
id|node
op_assign
id|node-&gt;sibling
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OG
l_int|10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING !! Gatwick interrupt pool overflow&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  GATWICK_IRQ_POOL_SIZE = %d&bslash;n&quot;
comma
id|GATWICK_IRQ_POOL_SIZE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;              requested = %d&bslash;n&quot;
comma
id|count
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The PowerBook 3400/2400/3500 can have a combo ethernet/modem&n; * card which includes an ohare chip that acts as a second interrupt&n; * controller.  If we find this second ohare, set it up and fix the&n; * interrupt value in the device tree for the ethernet chip.&n; */
DECL|function|enable_second_ohare
r_static
r_void
id|__init
id|enable_second_ohare
c_func
(paren
r_void
)paren
(brace
r_int
r_char
id|bus
comma
id|devfn
suffix:semicolon
r_int
r_int
id|cmd
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|second_irq
suffix:semicolon
r_struct
id|device_node
op_star
id|irqctrler
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci106b,7&quot;
)paren
suffix:semicolon
r_struct
id|device_node
op_star
id|ether
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler
op_eq
l_int|NULL
op_logical_or
id|irqctrler-&gt;n_addrs
op_le
l_int|0
)paren
r_return
suffix:semicolon
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x40
)paren
suffix:semicolon
id|pmac_irq_hw
(braket
l_int|1
)braket
op_assign
(paren
r_volatile
r_struct
id|pmac_irq_hw
op_star
)paren
(paren
id|addr
op_plus
l_int|0x20
)paren
suffix:semicolon
id|max_irqs
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|pci_device_loc
c_func
(paren
id|irqctrler
comma
op_amp
id|bus
comma
op_amp
id|devfn
)paren
op_eq
l_int|0
)paren
(brace
id|pmac_pcibios_read_config_word
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
op_or
id|PCI_COMMAND_MASTER
suffix:semicolon
id|cmd
op_and_assign
op_complement
id|PCI_COMMAND_IO
suffix:semicolon
id|pmac_pcibios_write_config_word
c_func
(paren
id|bus
comma
id|devfn
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
id|second_irq
op_assign
id|irqctrler-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: secondary controller on irq %d&bslash;n&quot;
comma
id|second_irq
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|second_irq
comma
id|gatwick_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;interrupt cascade&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Fix interrupt for the modem/ethernet combo controller. The number&n;&t;   in the device tree (27) is bogus (correct for the ethernet-only&n;&t;   board but not the combo ethernet/modem board).&n;&t;   The real interrupt is 28 on the second controller -&gt; 28+32 = 60.&n;&t;*/
id|ether
op_assign
id|find_devices
c_func
(paren
l_string|&quot;pci1011,14&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ether
op_logical_and
id|ether-&gt;n_intrs
OG
l_int|0
)paren
(brace
id|ether-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|60
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: Fixed ethernet IRQ to %d&bslash;n&quot;
comma
id|ether-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|pmac_pic_init
id|pmac_pic_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|device_node
op_star
id|irqctrler
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
r_int
id|second_irq
op_assign
op_minus
l_int|999
suffix:semicolon
multiline_comment|/* We first try to detect Apple&squot;s new Core99 chipset, since mac-io&n;&t; * is quite different on those machines and contains an IBM MPIC2.&n;&t; */
id|irqctrler
op_assign
id|find_type_devices
c_func
(paren
l_string|&quot;open-pic&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler
op_ne
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PowerMac using OpenPIC irq controller&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler-&gt;n_addrs
OG
l_int|0
)paren
(brace
macro_line|#ifdef CONFIG_XMON
r_struct
id|device_node
op_star
id|pswitch
suffix:semicolon
macro_line|#endif /* CONFIG_XMON */&t;
id|OpenPIC
op_assign
(paren
r_volatile
r_struct
id|OpenPIC
op_star
)paren
id|ioremap
c_func
(paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|size
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|pmac_open_pic
suffix:semicolon
id|openpic_init
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|has_openpic
op_assign
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|pswitch
op_assign
id|find_devices
c_func
(paren
l_string|&quot;programmer-switch&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pswitch
op_logical_and
id|pswitch-&gt;n_intrs
)paren
id|request_irq
c_func
(paren
id|pswitch-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
comma
id|xmon_irq
comma
l_int|0
comma
l_string|&quot;NMI - XMON&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_XMON */
r_return
suffix:semicolon
)brace
id|irqctrler
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * G3 powermacs and 1999 G3 PowerBooks have 64 interrupts,&n;&t; * 1998 G3 Series PowerBooks have 128, &n;&t; * other powermacs have 32.&n;&t; * The combo ethernet/modem card for the Powerstar powerbooks&n;&t; * (2400/3400/3500, ohare based) has a second ohare chip&n;&t; * effectively making a total of 64.&n;&t; */
id|max_irqs
op_assign
id|max_real_irqs
op_assign
l_int|32
suffix:semicolon
id|irqctrler
op_assign
id|find_devices
c_func
(paren
l_string|&quot;mac-io&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler
)paren
(brace
id|max_real_irqs
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler-&gt;next
)paren
id|max_irqs
op_assign
l_int|128
suffix:semicolon
r_else
id|max_irqs
op_assign
l_int|64
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_real_irqs
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|pmac_pic
suffix:semicolon
multiline_comment|/* get addresses of first controller */
r_if
c_cond
(paren
id|irqctrler
)paren
(brace
r_if
c_cond
(paren
id|irqctrler-&gt;n_addrs
OG
l_int|0
)paren
(brace
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x40
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|2
suffix:semicolon
op_increment
id|i
)paren
id|pmac_irq_hw
(braket
id|i
)braket
op_assign
(paren
r_volatile
r_struct
id|pmac_irq_hw
op_star
)paren
(paren
id|addr
op_plus
(paren
l_int|2
op_minus
id|i
)paren
op_star
l_int|0x10
)paren
suffix:semicolon
)brace
multiline_comment|/* get addresses of second controller */
id|irqctrler
op_assign
id|irqctrler-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|irqctrler
op_logical_and
id|irqctrler-&gt;n_addrs
OG
l_int|0
)paren
(brace
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|irqctrler-&gt;addrs
(braket
l_int|0
)braket
dot
id|address
comma
l_int|0x40
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
op_increment
id|i
)paren
id|pmac_irq_hw
(braket
id|i
)braket
op_assign
(paren
r_volatile
r_struct
id|pmac_irq_hw
op_star
)paren
(paren
id|addr
op_plus
(paren
l_int|4
op_minus
id|i
)paren
op_star
l_int|0x10
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* older powermacs have a GC (grand central) or ohare at&n;&t;&t;   f3000000, with interrupt control registers at f3000020. */
id|addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
l_int|0xf3000000
comma
l_int|0x40
)paren
suffix:semicolon
id|pmac_irq_hw
(braket
l_int|0
)braket
op_assign
(paren
r_volatile
r_struct
id|pmac_irq_hw
op_star
)paren
(paren
id|addr
op_plus
l_int|0x20
)paren
suffix:semicolon
)brace
multiline_comment|/* PowerBooks 3400 and 3500 can have a second controller in a second&n;&t;   ohare chip, on the combo ethernet/modem card */
r_if
c_cond
(paren
id|machine_is_compatible
c_func
(paren
l_string|&quot;AAPL,3400/2400&quot;
)paren
op_logical_or
id|machine_is_compatible
c_func
(paren
l_string|&quot;AAPL,3500&quot;
)paren
)paren
id|enable_second_ohare
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* disable all interrupts in all controllers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_star
l_int|32
OL
id|max_irqs
suffix:semicolon
op_increment
id|i
)paren
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
id|i
)braket
op_member_access_from_pointer
id|enable
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* get interrupt line of secondary interrupt controller */
r_if
c_cond
(paren
id|irqctrler
)paren
(brace
id|second_irq
op_assign
id|irqctrler-&gt;intrs
(braket
l_int|0
)braket
dot
id|line
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;irq: secondary controller on irq %d&bslash;n&quot;
comma
(paren
r_int
)paren
id|second_irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|irqctrler
comma
l_string|&quot;gatwick&quot;
)paren
)paren
id|pmac_fix_gatwick_interrupts
c_func
(paren
id|irqctrler
comma
id|max_real_irqs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|max_real_irqs
suffix:semicolon
id|i
OL
id|max_irqs
suffix:semicolon
id|i
op_increment
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|gatwick_pic
suffix:semicolon
id|request_irq
c_func
(paren
id|second_irq
comma
id|gatwick_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;gatwick cascade&quot;
comma
l_int|0
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;System has %d possible interrupts&bslash;n&quot;
comma
id|max_irqs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_irqs
op_ne
id|max_real_irqs
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%d interrupts on main controller&bslash;n&quot;
comma
id|max_real_irqs
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_XMON
id|request_irq
c_func
(paren
l_int|20
comma
id|xmon_irq
comma
l_int|0
comma
l_string|&quot;NMI - XMON&quot;
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif&t;/* CONFIG_XMON */
)brace
macro_line|#ifdef CONFIG_PMAC_PBOOK
multiline_comment|/*&n; * These procedures are used in implementing sleep on the powerbooks.&n; * sleep_save_intrs() saves the states of all interrupt enables&n; * and disables all interupts except for the nominated one.&n; * sleep_restore_intrs() restores the states of all interrupt enables.&n; */
DECL|variable|sleep_save_mask
r_int
r_int
id|sleep_save_mask
(braket
l_int|2
)braket
suffix:semicolon
r_void
DECL|function|sleep_save_intrs
id|sleep_save_intrs
c_func
(paren
r_int
id|viaint
)paren
(brace
id|sleep_save_mask
(braket
l_int|0
)braket
op_assign
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
suffix:semicolon
id|sleep_save_mask
(braket
l_int|1
)braket
op_assign
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
suffix:semicolon
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|set_bit
c_func
(paren
id|viaint
comma
id|ppc_cached_irq_mask
)paren
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|0
)braket
op_member_access_from_pointer
id|enable
comma
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_real_irqs
OG
l_int|32
)paren
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|1
)braket
op_member_access_from_pointer
id|enable
comma
id|ppc_cached_irq_mask
(braket
l_int|1
)braket
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flag
)paren
suffix:semicolon
r_do
(brace
multiline_comment|/* make sure mask gets to controller before we&n;                   return to user */
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|in_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|0
)braket
op_member_access_from_pointer
id|enable
)paren
op_ne
id|ppc_cached_irq_mask
(braket
l_int|0
)braket
)paren
(brace
suffix:semicolon
)brace
)brace
r_void
DECL|function|sleep_restore_intrs
id|sleep_restore_intrs
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|0
)braket
op_member_access_from_pointer
id|enable
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_real_irqs
OG
l_int|32
)paren
id|out_le32
c_func
(paren
op_amp
id|pmac_irq_hw
(braket
l_int|1
)braket
op_member_access_from_pointer
id|enable
comma
l_int|0
)paren
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|max_real_irqs
suffix:semicolon
op_increment
id|i
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|sleep_save_mask
)paren
)paren
id|pmac_unmask_irq
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PMAC_PBOOK */
eof
