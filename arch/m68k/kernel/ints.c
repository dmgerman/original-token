multiline_comment|/*&n; * ints.c -- 680x0 Linux general interrupt handling code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; *&n; * 07/03/96: Timer initialization, and thus mach_sched_init(),&n; *           removed from request_irq() and moved to init_time().&n; *           We should therefore consider renaming our add_isr() and&n; *           remove_isr() to request_irq() and free_irq()&n; *           respectively, so they are compliant with the other&n; *           architectures.                                     /Jes&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
multiline_comment|/* list is accessed 0-6 for IRQs 1-7 */
DECL|variable|isr_list
r_static
id|isr_node_t
op_star
id|isr_list
(braket
l_int|7
)braket
suffix:semicolon
multiline_comment|/* The number of spurious interrupts */
DECL|variable|num_spurious
r_volatile
r_int
r_int
id|num_spurious
suffix:semicolon
multiline_comment|/*&n;unsigned long interrupt_stack[PAGE_SIZE/sizeof(long)];&n;*/
multiline_comment|/*&n; * void init_IRQ(void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function should be called during kernel startup to initialize&n; * the IRQ handling routines.&n; */
DECL|function|init_IRQ
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Setup interrupt stack pointer */
multiline_comment|/*&n;    asm (&quot;movec %0,%/isp&quot;&n;&t; : : &quot;r&quot; (interrupt_stack + sizeof (interrupt_stack) / sizeof (long)));&n;&t; */
id|mach_init_INTS
(paren
)paren
suffix:semicolon
)brace
DECL|function|insert_isr
r_void
id|insert_isr
(paren
id|isr_node_t
op_star
op_star
id|listp
comma
id|isr_node_t
op_star
id|node
)paren
(brace
r_int
r_int
id|spl
suffix:semicolon
id|isr_node_t
op_star
id|cur
suffix:semicolon
id|save_flags
c_func
(paren
id|spl
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|cur
op_assign
op_star
id|listp
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_logical_and
id|cur-&gt;pri
op_le
id|node-&gt;pri
)paren
(brace
id|listp
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
id|node-&gt;next
op_assign
id|cur
suffix:semicolon
op_star
id|listp
op_assign
id|node
suffix:semicolon
id|restore_flags
c_func
(paren
id|spl
)paren
suffix:semicolon
)brace
DECL|function|delete_isr
r_void
id|delete_isr
(paren
id|isr_node_t
op_star
op_star
id|listp
comma
id|isrfunc
id|isr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|isr_node_t
op_star
id|np
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
op_star
id|listp
suffix:semicolon
id|np
suffix:semicolon
id|listp
op_assign
op_amp
id|np-&gt;next
comma
id|np
op_assign
op_star
id|listp
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;isr
op_eq
id|isr
)paren
(brace
op_star
id|listp
op_assign
id|np-&gt;next
suffix:semicolon
multiline_comment|/* Mark it as free. */
id|np-&gt;isr
op_assign
l_int|NULL
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;delete_isr: isr %p not found on list!&bslash;n&quot;
comma
id|isr
)paren
suffix:semicolon
)brace
DECL|macro|NUM_ISR_NODES
mdefine_line|#define NUM_ISR_NODES 100
DECL|variable|nodes
r_static
id|isr_node_t
id|nodes
(braket
id|NUM_ISR_NODES
)braket
suffix:semicolon
DECL|function|new_isr_node
id|isr_node_t
op_star
id|new_isr_node
c_func
(paren
r_void
)paren
(brace
id|isr_node_t
op_star
id|np
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|nodes
suffix:semicolon
id|np
OL
op_amp
id|nodes
(braket
id|NUM_ISR_NODES
)braket
suffix:semicolon
id|np
op_increment
)paren
r_if
c_cond
(paren
id|np-&gt;isr
op_eq
l_int|NULL
)paren
r_return
id|np
suffix:semicolon
id|printk
(paren
l_string|&quot;new_isr_node: out of nodes&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|add_isr
r_int
id|add_isr
(paren
r_int
r_int
id|source
comma
id|isrfunc
id|isr
comma
r_int
id|pri
comma
r_void
op_star
id|data
comma
r_char
op_star
id|name
)paren
(brace
id|isr_node_t
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|source
op_amp
id|IRQ_MACHSPEC
)paren
(brace
r_return
id|mach_add_isr
(paren
id|source
comma
id|isr
comma
id|pri
comma
id|data
comma
id|name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|source
template_param
id|IRQ7
)paren
id|panic
(paren
l_string|&quot;add_isr: Incorrect IRQ source %ld from %s&bslash;n&quot;
comma
id|source
comma
id|name
)paren
suffix:semicolon
id|p
op_assign
id|new_isr_node
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|p-&gt;isr
op_assign
id|isr
suffix:semicolon
id|p-&gt;pri
op_assign
id|pri
suffix:semicolon
id|p-&gt;data
op_assign
id|data
suffix:semicolon
id|p-&gt;name
op_assign
id|name
suffix:semicolon
id|p-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|insert_isr
(paren
op_amp
id|isr_list
(braket
id|source
op_minus
l_int|1
)braket
comma
id|p
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|remove_isr
r_int
id|remove_isr
(paren
r_int
r_int
id|source
comma
id|isrfunc
id|isr
)paren
(brace
r_if
c_cond
(paren
id|source
op_amp
id|IRQ_MACHSPEC
)paren
r_return
id|mach_remove_isr
(paren
id|source
comma
id|isr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|source
template_param
id|IRQ7
)paren
(brace
id|printk
(paren
l_string|&quot;remove_isr: Incorrect IRQ source %ld&bslash;n&quot;
comma
id|source
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|delete_isr
(paren
op_amp
id|isr_list
(braket
id|source
op_minus
l_int|1
)braket
comma
id|isr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|call_isr_list
r_void
id|call_isr_list
c_func
(paren
r_int
id|irq
comma
id|isr_node_t
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_while
c_loop
(paren
id|p
)paren
(brace
id|p-&gt;isr
(paren
id|irq
comma
id|fp
comma
id|p-&gt;data
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|process_int
id|asmlinkage
r_void
id|process_int
c_func
(paren
r_int
id|vec
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|level
suffix:semicolon
r_if
c_cond
(paren
id|vec
op_ge
id|VECOFF
c_func
(paren
id|VEC_INT1
)paren
op_logical_and
id|vec
op_le
id|VECOFF
c_func
(paren
id|VEC_INT7
)paren
)paren
id|level
op_assign
(paren
id|vec
op_minus
id|VECOFF
c_func
(paren
id|VEC_SPUR
)paren
)paren
op_rshift
l_int|2
suffix:semicolon
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
id|regs
)paren
suffix:semicolon
r_else
id|panic
c_func
(paren
l_string|&quot;Can&squot;t process interrupt vector 0x%03x&bslash;n&quot;
comma
id|vec
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|kstat.interrupts
(braket
id|level
)braket
op_increment
suffix:semicolon
id|call_isr_list
(paren
id|level
comma
id|isr_list
(braket
id|level
op_minus
l_int|1
)braket
comma
id|regs
)paren
suffix:semicolon
)brace
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
op_minus
id|EINVAL
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
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_if
c_cond
(paren
(paren
id|irq_nr
op_amp
id|IRQ_MACHSPEC
)paren
op_logical_and
id|mach_enable_irq
)paren
id|mach_enable_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
)brace
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq_nr
)paren
(brace
r_if
c_cond
(paren
(paren
id|irq_nr
op_amp
id|IRQ_MACHSPEC
)paren
op_logical_and
id|mach_disable_irq
)paren
id|mach_disable_irq
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
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
id|isr_node_t
op_star
id|p
suffix:semicolon
multiline_comment|/* autovector interrupts */
r_for
c_loop
(paren
id|i
op_assign
id|IRQ1
suffix:semicolon
id|i
op_le
id|IRQ7
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|isr_list
(braket
id|i
op_minus
l_int|1
)braket
)paren
r_continue
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
l_string|&quot;auto %2d: %8d &quot;
comma
id|i
comma
id|kstat.interrupts
(braket
id|i
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|isr_list
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|p
suffix:semicolon
id|p
op_assign
id|p-&gt;next
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
l_string|&quot;%s&bslash;n&quot;
comma
id|p-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;next
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
l_string|&quot;                  &quot;
)paren
suffix:semicolon
)brace
)brace
id|len
op_assign
id|mach_get_irq_list
c_func
(paren
id|buf
comma
id|len
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
eof