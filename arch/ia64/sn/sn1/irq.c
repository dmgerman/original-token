multiline_comment|/*&n; * Platform dependent support for SGI SN1&n; *&n; * Copyright (C) 2000   Silicon Graphics&n; * Copyright (C) 2000   Jack Steiner (steiner@sgi.com)&n; * Copyright (C) 2000   Alan Mayer (ajm@sgi.com)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/current.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/sn/sgi.h&gt;
macro_line|#include &lt;asm/sn/iograph.h&gt;
macro_line|#include &lt;asm/sn/invent.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;asm/sn/hcl.h&gt;
macro_line|#include &lt;asm/sn/types.h&gt;
macro_line|#include &lt;asm/sn/pci/bridge.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio.h&gt;
macro_line|#include &lt;asm/sn/pci/pciio_private.h&gt;
macro_line|#include &lt;asm/sn/sn_cpuid.h&gt;
macro_line|#include &lt;asm/sn/sn1/bedrock.h&gt;
macro_line|#include &lt;asm/sn/intr.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn1/addrs.h&gt;
macro_line|#include &lt;asm/sn/iobus.h&gt;
macro_line|#include &lt;asm/sn/sn1/arch.h&gt;
macro_line|#include &lt;asm/sn/synergy.h&gt;
r_int
id|bit_pos_to_irq
c_func
(paren
r_int
id|bit
)paren
suffix:semicolon
r_int
id|irq_to_bit_pos
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
id|add_interrupt_randomness
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
r_void
op_star
id|kmalloc
c_func
(paren
r_int
id|size
comma
r_int
id|flags
)paren
suffix:semicolon
r_void
id|kfree
c_func
(paren
r_const
r_void
op_star
)paren
suffix:semicolon
r_int
id|sgi_pci_intr_support
(paren
r_int
r_int
comma
id|device_desc_t
op_star
comma
id|devfs_handle_t
op_star
comma
id|pciio_intr_line_t
op_star
comma
id|devfs_handle_t
op_star
)paren
suffix:semicolon
id|pciio_intr_t
id|pciio_intr_alloc
c_func
(paren
id|devfs_handle_t
comma
id|device_desc_t
comma
id|pciio_intr_line_t
comma
id|devfs_handle_t
)paren
suffix:semicolon
r_int
id|request_irq
c_func
(paren
r_int
r_int
comma
r_void
(paren
op_star
)paren
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
comma
r_int
r_int
comma
r_const
r_char
op_star
comma
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* This should be dynamically allocated, at least part of it. */
multiline_comment|/* For the time being, though, we&squot;ll statically allocate it */
multiline_comment|/* because kmalloc hasn&squot;t been initiallized at the time this */
multiline_comment|/* array is initiallized.  One way to do it would be to statically */
multiline_comment|/* allocate the data for node 0, then let other nodes, as they */
multiline_comment|/* need it, dynamically allocate their own data space. */
DECL|variable|sn1_node_actions
r_struct
id|sn1_cnode_action_list
op_star
id|sn1_node_actions
(braket
id|MAX_COMPACT_NODES
)braket
suffix:semicolon
DECL|variable|sn1_actions
r_struct
id|sn1_cnode_action_list
id|sn1_actions
(braket
id|MAX_COMPACT_NODES
)braket
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
id|numnodes
suffix:semicolon
r_static
r_int
r_int
DECL|function|sn1_startup_irq
id|sn1_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|sn1_shutdown_irq
id|sn1_shutdown_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_disable_irq
id|sn1_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_enable_irq
id|sn1_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_ack_irq
id|sn1_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_end_irq
id|sn1_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_set_affinity_irq
id|sn1_set_affinity_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|mask
)paren
(brace
)brace
r_static
r_void
DECL|function|sn1_handle_irq
id|sn1_handle_irq
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|bit
comma
id|cnode
suffix:semicolon
r_struct
id|sn1_cnode_action_list
op_star
id|alp
suffix:semicolon
r_struct
id|sn1_intr_action
op_star
id|ap
suffix:semicolon
r_void
(paren
op_star
id|handler
)paren
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
r_int
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
r_int
id|cpuid
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|bit
op_assign
id|irq_to_bit_pos
c_func
(paren
id|irq
)paren
suffix:semicolon
id|LOCAL_HUB_CLR_INTR
c_func
(paren
id|bit
)paren
suffix:semicolon
id|cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|alp
op_assign
id|sn1_node_actions
(braket
id|cnode
)braket
suffix:semicolon
id|ap
op_assign
id|alp
(braket
id|irq
)braket
dot
id|action_list
suffix:semicolon
r_if
c_cond
(paren
id|ap
op_eq
l_int|NULL
)paren
(brace
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
id|ap
)paren
(brace
id|flags
op_or_assign
id|ap-&gt;flags
suffix:semicolon
id|handler
op_assign
id|ap-&gt;handler
suffix:semicolon
(paren
op_star
id|handler
)paren
(paren
id|irq
comma
id|ap-&gt;intr_arg
comma
id|regs
)paren
suffix:semicolon
id|ap
op_assign
id|ap-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
op_ne
l_int|0
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|irq_type_sn1
r_struct
id|hw_interrupt_type
id|irq_type_sn1
op_assign
(brace
l_string|&quot;sn1_irq&quot;
comma
id|sn1_startup_irq
comma
id|sn1_shutdown_irq
comma
id|sn1_enable_irq
comma
id|sn1_disable_irq
comma
id|sn1_ack_irq
comma
id|sn1_end_irq
comma
id|sn1_set_affinity_irq
)brace
suffix:semicolon
DECL|variable|sn1_irqaction
r_struct
id|irqaction
id|sn1_irqaction
op_assign
(brace
id|sn1_handle_irq
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
r_void
DECL|function|sn1_irq_init
id|sn1_irq_init
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|NR_IRQS
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_eq
op_amp
id|no_irq_type
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|irq_type_sn1
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|71
op_logical_and
id|i
op_le
l_int|181
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
op_amp
id|sn1_irqaction
suffix:semicolon
)brace
)brace
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
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sn1_node_actions
(braket
id|i
)braket
op_assign
id|sn1_actions
(braket
id|i
)braket
suffix:semicolon
id|memset
c_func
(paren
id|sn1_node_actions
(braket
id|i
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sn1_cnode_action_list
)paren
op_star
(paren
id|IA64_MAX_VECTORED_IRQ
op_plus
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|IA64_MAX_VECTORED_IRQ
op_plus
l_int|1
suffix:semicolon
id|j
op_increment
)paren
(brace
id|spin_lock_init
c_func
(paren
op_amp
id|sn1_node_actions
(braket
id|i
)braket
(braket
id|j
)braket
dot
id|action_list_lock
)paren
suffix:semicolon
)brace
)brace
)brace
r_int
DECL|function|sn1_request_irq
id|sn1_request_irq
(paren
r_int
r_int
id|requested_irq
comma
r_void
(paren
op_star
id|handler
)paren
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
comma
r_int
r_int
id|irqflags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
id|devfs_handle_t
id|curr_dev
suffix:semicolon
id|devfs_handle_t
id|dev
suffix:semicolon
id|pciio_intr_t
id|intr_handle
suffix:semicolon
id|pciio_intr_line_t
id|line
suffix:semicolon
id|device_desc_t
id|dev_desc
suffix:semicolon
r_int
id|cpuid
comma
id|bit
comma
id|cnode
suffix:semicolon
r_struct
id|sn1_intr_action
op_star
id|ap
comma
op_star
id|new_ap
suffix:semicolon
r_struct
id|sn1_cnode_action_list
op_star
id|alp
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_if
c_cond
(paren
(paren
id|requested_irq
op_amp
l_int|0xff
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|ret
suffix:semicolon
id|sgi_pci_intr_support
c_func
(paren
id|requested_irq
comma
op_amp
id|dev_desc
comma
op_amp
id|dev
comma
op_amp
id|line
comma
op_amp
id|curr_dev
)paren
suffix:semicolon
id|intr_handle
op_assign
id|pciio_intr_alloc
c_func
(paren
id|curr_dev
comma
l_int|NULL
comma
id|line
comma
id|curr_dev
)paren
suffix:semicolon
id|bit
op_assign
id|intr_handle-&gt;pi_irq
suffix:semicolon
id|cpuid
op_assign
id|intr_handle-&gt;pi_cpu
suffix:semicolon
id|irq
op_assign
id|bit_pos_to_irq
c_func
(paren
id|bit
)paren
suffix:semicolon
id|cnode
op_assign
id|cpuid_to_cnodeid
c_func
(paren
id|cpuid
)paren
suffix:semicolon
id|new_ap
op_assign
(paren
r_struct
id|sn1_intr_action
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sn1_intr_action
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
id|new_ap-&gt;handler
op_assign
id|handler
suffix:semicolon
id|new_ap-&gt;intr_arg
op_assign
id|dev_id
suffix:semicolon
id|new_ap-&gt;flags
op_assign
id|irqflags
suffix:semicolon
id|new_ap-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|alp
op_assign
id|sn1_node_actions
(braket
id|cnode
)braket
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|alp
(braket
id|irq
)braket
dot
id|action_list_lock
)paren
suffix:semicolon
id|ap
op_assign
id|alp
(braket
id|irq
)braket
dot
id|action_list
suffix:semicolon
multiline_comment|/* check action list for &quot;share&quot; consistency */
r_while
c_loop
(paren
id|ap
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|ap-&gt;flags
op_amp
id|irqflags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|alp
(braket
id|irq
)braket
dot
id|action_list_lock
)paren
suffix:semicolon
)brace
id|ap
op_assign
id|ap-&gt;next
suffix:semicolon
)brace
id|ap
op_assign
id|alp
(braket
id|irq
)braket
dot
id|action_list
suffix:semicolon
r_if
c_cond
(paren
id|ap
)paren
(brace
r_while
c_loop
(paren
id|ap-&gt;next
)paren
(brace
id|ap
op_assign
id|ap-&gt;next
suffix:semicolon
)brace
id|ap-&gt;next
op_assign
id|new_ap
suffix:semicolon
)brace
r_else
(brace
id|alp
(braket
id|irq
)braket
dot
id|action_list
op_assign
id|new_ap
suffix:semicolon
)brace
id|ret
op_assign
id|pciio_intr_connect
c_func
(paren
id|intr_handle
comma
(paren
id|intr_func_t
)paren
id|handler
comma
id|dev_id
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
multiline_comment|/* connect failed, undo what we did. */
id|new_ap
op_assign
id|alp
(braket
id|irq
)braket
dot
id|action_list
suffix:semicolon
r_if
c_cond
(paren
id|new_ap
op_eq
id|ap
)paren
(brace
id|alp
(braket
id|irq
)braket
dot
id|action_list
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
r_else
(brace
r_while
c_loop
(paren
id|new_ap-&gt;next
op_logical_and
id|new_ap-&gt;next
op_ne
id|ap
)paren
(brace
id|new_ap
op_assign
id|new_ap-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_ap-&gt;next
op_eq
id|ap
)paren
(brace
id|new_ap-&gt;next
op_assign
id|ap-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|alp
(braket
id|irq
)braket
dot
id|action_list_lock
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_else
(brace
r_return
id|request_irq
c_func
(paren
id|requested_irq
comma
id|handler
comma
id|irqflags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
)brace
macro_line|#if !defined(CONFIG_IA64_SGI_IO)
r_void
DECL|function|sn1_pci_fixup
id|sn1_pci_fixup
c_func
(paren
r_int
id|arg
)paren
(brace
)brace
macro_line|#endif
r_int
DECL|function|bit_pos_to_irq
id|bit_pos_to_irq
c_func
(paren
r_int
id|bit
)paren
(brace
DECL|macro|BIT_TO_IRQ
mdefine_line|#define BIT_TO_IRQ 64
r_return
id|bit
op_plus
id|BIT_TO_IRQ
suffix:semicolon
)brace
r_int
DECL|function|irq_to_bit_pos
id|irq_to_bit_pos
c_func
(paren
r_int
id|irq
)paren
(brace
DECL|macro|IRQ_TO_BIT
mdefine_line|#define IRQ_TO_BIT 64
r_return
id|irq
op_minus
id|IRQ_TO_BIT
suffix:semicolon
)brace
eof
