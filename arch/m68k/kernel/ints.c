multiline_comment|/*&n; * linux/arch/m68k/kernel/ints.c -- Linux/m68k general interrupt handling code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * 07/03/96: Timer initialization, and thus mach_sched_init(),&n; *           removed from request_irq() and moved to init_time().&n; *           We should therefore consider renaming our add_isr() and&n; *           remove_isr() to request_irq() and free_irq()&n; *           respectively, so they are compliant with the other&n; *           architectures.                                     /Jes&n; * 11/07/96: Changed all add_/remove_isr() to request_/free_irq() calls.&n; *           Removed irq list support, if any machine needs an irq server&n; *           it must implement this itself (as it&squot;s already done), instead&n; *           only default handler are used with mach_default_handler.&n; *           request_irq got some flags different from other architectures:&n; *           - IRQ_FLG_REPLACE : Replace an existing handler (the default one&n; *                               can be replaced without this flag)&n; *           - IRQ_FLG_LOCK : handler can&squot;t be replaced&n; *           There are other machine depending flags, see there&n; *           If you want to replace a default handler you should know what&n; *           you&squot;re doing, since it might handle different other irq sources&n; *           which must be served                               /Roman Zippel&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* table for system interrupt handlers */
DECL|variable|irq_list
r_static
id|irq_handler_t
id|irq_list
(braket
id|SYS_IRQS
)braket
suffix:semicolon
DECL|variable|default_names
r_static
r_const
r_char
op_star
id|default_names
(braket
id|SYS_IRQS
)braket
op_assign
(brace
l_string|&quot;spurious int&quot;
comma
l_string|&quot;int1 handler&quot;
comma
l_string|&quot;int2 handler&quot;
comma
l_string|&quot;int3 handler&quot;
comma
l_string|&quot;int4 handler&quot;
comma
l_string|&quot;int5 handler&quot;
comma
l_string|&quot;int6 handler&quot;
comma
l_string|&quot;int7 handler&quot;
)brace
suffix:semicolon
multiline_comment|/* The number of spurious interrupts */
DECL|variable|num_spurious
r_volatile
r_int
r_int
id|num_spurious
suffix:semicolon
DECL|macro|NUM_IRQ_NODES
mdefine_line|#define NUM_IRQ_NODES 100
DECL|variable|nodes
r_static
id|irq_node_t
id|nodes
(braket
id|NUM_IRQ_NODES
)braket
suffix:semicolon
DECL|variable|local_irq_count
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|local_bh_count
r_int
r_int
id|local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_static
r_void
id|dummy_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|dummy_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_int
id|dummy_request_irq
c_func
(paren
r_int
r_int
id|irq
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
id|flags
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
suffix:semicolon
r_static
r_void
id|dummy_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
suffix:semicolon
DECL|variable|enable_irq
r_void
(paren
op_star
id|enable_irq
)paren
(paren
r_int
r_int
)paren
op_assign
id|dummy_enable_irq
suffix:semicolon
DECL|variable|disable_irq
r_void
(paren
op_star
id|disable_irq
)paren
(paren
r_int
r_int
)paren
op_assign
id|dummy_disable_irq
suffix:semicolon
DECL|variable|mach_request_irq
r_int
(paren
op_star
id|mach_request_irq
)paren
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
op_assign
id|dummy_request_irq
suffix:semicolon
DECL|variable|mach_free_irq
r_void
(paren
op_star
id|mach_free_irq
)paren
(paren
r_int
r_int
comma
r_void
op_star
)paren
op_assign
id|dummy_free_irq
suffix:semicolon
multiline_comment|/*&n; * void init_IRQ(void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function should be called during kernel startup to initialize&n; * the IRQ handling routines.&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|i
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
id|SYS_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mach_default_handler
)paren
id|irq_list
(braket
id|i
)braket
dot
id|handler
op_assign
(paren
op_star
id|mach_default_handler
)paren
(braket
id|i
)braket
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_list
(braket
id|i
)braket
dot
id|devname
op_assign
id|default_names
(braket
id|i
)braket
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
id|NUM_IRQ_NODES
suffix:semicolon
id|i
op_increment
)paren
id|nodes
(braket
id|i
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|mach_init_IRQ
(paren
)paren
suffix:semicolon
)brace
DECL|function|new_irq_node
id|irq_node_t
op_star
id|new_irq_node
c_func
(paren
r_void
)paren
(brace
id|irq_node_t
op_star
id|node
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|nodes
comma
id|i
op_assign
id|NUM_IRQ_NODES
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|node
op_increment
comma
id|i
op_decrement
)paren
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;handler
)paren
r_return
id|node
suffix:semicolon
id|printk
(paren
l_string|&quot;new_irq_node: out of nodes&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * We will keep these functions until I have convinced Linus to move&n; * the declaration of them from include/linux/sched.h to&n; * include/asm/irq.h.&n; */
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
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
id|flags
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
r_return
id|mach_request_irq
c_func
(paren
id|irq
comma
id|handler
comma
id|flags
comma
id|devname
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|mach_free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
)brace
DECL|function|sys_request_irq
r_int
id|sys_request_irq
c_func
(paren
r_int
r_int
id|irq
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
id|flags
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
r_if
c_cond
(paren
id|irq
template_param
id|IRQ7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_STD
)paren
)paren
(brace
r_if
c_cond
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IRQ %d from %s is not replaceable&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|IRQ_FLG_REPLACE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: %s can&squot;t replace IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|devname
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
id|devname
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_free_irq
r_void
id|sys_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|irq
template_param
id|IRQ7
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_list
(braket
id|irq
)braket
dot
id|devname
)paren
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|handler
op_assign
(paren
op_star
id|mach_default_handler
)paren
(braket
id|irq
)braket
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_list
(braket
id|irq
)braket
dot
id|devname
op_assign
id|default_names
(braket
id|irq
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * Do we need these probe functions on the m68k?&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|probe_irq_off
r_int
id|probe_irq_off
(paren
r_int
r_int
id|irqs
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_enable_irq
r_static
r_void
id|dummy_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;calling uninitialized enable_irq()&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|dummy_disable_irq
r_static
r_void
id|dummy_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;calling uninitialized disable_irq()&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|dummy_request_irq
r_static
r_int
id|dummy_request_irq
c_func
(paren
r_int
r_int
id|irq
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
id|flags
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
id|printk
c_func
(paren
l_string|&quot;calling uninitialized request_irq()&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dummy_free_irq
r_static
r_void
id|dummy_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;calling uninitialized disable_irq()&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|process_int
id|asmlinkage
r_void
id|process_int
c_func
(paren
r_int
r_int
id|vec
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|vec
op_ge
id|VEC_INT1
op_logical_and
id|vec
op_le
id|VEC_INT7
op_logical_and
op_logical_neg
id|MACH_IS_BVME6000
)paren
(brace
id|vec
op_sub_assign
id|VEC_SPUR
suffix:semicolon
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|vec
)braket
op_increment
suffix:semicolon
id|irq_list
(braket
id|vec
)braket
dot
id|handler
c_func
(paren
id|vec
comma
id|irq_list
(braket
id|vec
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|mach_process_int
)paren
id|mach_process_int
c_func
(paren
id|vec
comma
id|fp
)paren
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;Can&squot;t process interrupt vector %ld&bslash;n&quot;
comma
id|vec
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
DECL|function|get_irq_list
r_int
id|get_irq_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* autovector interrupts */
r_if
c_cond
(paren
id|mach_default_handler
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|SYS_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;auto %2d: %10u &quot;
comma
id|i
comma
id|i
ques
c_cond
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|i
)braket
suffix:colon
id|num_spurious
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
id|i
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;L &quot;
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;  &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|irq_list
(braket
id|i
)braket
dot
id|devname
)paren
suffix:semicolon
)brace
)brace
id|len
op_add_assign
id|mach_get_irq_list
c_func
(paren
id|buf
op_plus
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof
