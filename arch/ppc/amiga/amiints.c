multiline_comment|/*&n; * linux/arch/m68k/amiga/amiints.c -- Amiga Linux interrupt handling code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file COPYING in the main directory of this archive&n; * for more details.&n; *&n; * 11/07/96: rewritten interrupt handling, irq lists are exists now only for&n; *           this sources where it makes sense (VERTB/PORTS/EXTER) and you must&n; *           be careful that dev_id for this sources is unique since this the&n; *           only possibility to distinguish between different handlers for&n; *           free_irq. irq lists also have different irq flags:&n; *           - IRQ_FLG_FAST: handler is inserted at top of list (after other&n; *                           fast handlers)&n; *           - IRQ_FLG_SLOW: handler is inserted at bottom of list and before&n; *                           they&squot;re executed irq level is set to the previous&n; *                           one, but handlers don&squot;t need to be reentrant, if&n; *                           reentrance occurred, slow handlers will be just&n; *                           called again.&n; *           The whole interrupt handling for CIAs is moved to cia.c&n; *           /Roman Zippel&n; *&n; * 07/08/99: rewamp of the interrupt handling - we now have two types of&n; *           interrupts, normal and fast handlers, fast handlers being&n; *           marked with SA_INTERRUPT and runs with all other interrupts&n; *           disabled. Normal interrupts disable their own source but&n; *           run with all other interrupt sources enabled.&n; *           PORTS and EXTER interrupts are always shared even if the&n; *           drivers do not explicitly mark this when calling&n; *           request_irq which they really should do.&n; *           This is similar to the way interrupts are handled on all&n; *           other architectures and makes a ton of sense besides&n; *           having the advantage of making it easier to share&n; *           drivers.&n; *           /Jes&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amipcmcia.h&gt;
macro_line|#ifdef CONFIG_APUS
macro_line|#include &lt;asm/amigappc.h&gt;
macro_line|#endif
r_extern
r_int
id|cia_request_irq
c_func
(paren
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
r_extern
r_void
id|cia_free_irq
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
r_extern
r_void
id|cia_init_IRQ
c_func
(paren
r_struct
id|ciabase
op_star
id|base
)paren
suffix:semicolon
r_extern
r_int
id|cia_get_irq_list
c_func
(paren
r_struct
id|ciabase
op_star
id|base
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
multiline_comment|/* irq node variables for amiga interrupt sources */
DECL|variable|ami_irq_list
r_static
id|irq_node_t
op_star
id|ami_irq_list
(braket
id|AMI_STD_IRQS
)braket
suffix:semicolon
DECL|variable|ami_intena_vals
r_int
r_int
id|ami_intena_vals
(braket
id|AMI_STD_IRQS
)braket
op_assign
(brace
id|IF_VERTB
comma
id|IF_COPER
comma
id|IF_AUD0
comma
id|IF_AUD1
comma
id|IF_AUD2
comma
id|IF_AUD3
comma
id|IF_BLIT
comma
id|IF_DSKSYN
comma
id|IF_DSKBLK
comma
id|IF_RBF
comma
id|IF_TBE
comma
id|IF_SOFT
comma
id|IF_PORTS
comma
id|IF_EXTER
)brace
suffix:semicolon
DECL|variable|ami_servers
r_static
r_const
r_int
r_char
id|ami_servers
(braket
id|AMI_STD_IRQS
)braket
op_assign
(brace
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|1
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|ami_ablecount
r_static
r_int
id|ami_ablecount
(braket
id|AMI_IRQS
)braket
suffix:semicolon
DECL|function|ami_badint
r_static
r_void
id|ami_badint
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|num_spurious
op_add_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * void amiga_init_IRQ(void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function should be called during kernel startup to initialize&n; * the amiga IRQ handling routines.&n; */
id|__init
DECL|function|amiga_init_IRQ
r_void
id|amiga_init_IRQ
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* initialize handlers */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|AMI_STD_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ami_servers
(braket
id|i
)braket
)paren
(brace
id|ami_irq_list
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|ami_irq_list
(braket
id|i
)braket
op_assign
id|new_irq_node
c_func
(paren
)paren
suffix:semicolon
id|ami_irq_list
(braket
id|i
)braket
op_member_access_from_pointer
id|handler
op_assign
id|ami_badint
suffix:semicolon
id|ami_irq_list
(braket
id|i
)braket
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
id|ami_irq_list
(braket
id|i
)braket
op_member_access_from_pointer
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|ami_irq_list
(braket
id|i
)braket
op_member_access_from_pointer
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|ami_irq_list
(braket
id|i
)braket
op_member_access_from_pointer
id|next
op_assign
l_int|NULL
suffix:semicolon
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
id|AMI_IRQS
suffix:semicolon
id|i
op_increment
)paren
id|ami_ablecount
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off PCMCIA interrupts */
r_if
c_cond
(paren
id|AMIGAHW_PRESENT
c_func
(paren
id|PCMCIA
)paren
)paren
id|pcmcia_disable_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* turn off all interrupts... */
id|custom.intena
op_assign
l_int|0x7fff
suffix:semicolon
id|custom.intreq
op_assign
l_int|0x7fff
suffix:semicolon
macro_line|#ifdef CONFIG_APUS
multiline_comment|/* Clear any inter-CPU interupt requests. Circumvents bug in&n;           Blizzard IPL emulation HW (or so it appears). */
id|APUS_WRITE
c_func
(paren
id|APUS_INT_LVL
comma
id|INTLVL_SETRESET
op_or
id|INTLVL_MASK
)paren
suffix:semicolon
multiline_comment|/* Init IPL emulation. */
id|APUS_WRITE
c_func
(paren
id|APUS_REG_INT
comma
id|REGINT_INTMASTER
op_or
id|REGINT_ENABLEIPL
)paren
suffix:semicolon
id|APUS_WRITE
c_func
(paren
id|APUS_IPL_EMU
comma
id|IPLEMU_DISABLEINT
)paren
suffix:semicolon
id|APUS_WRITE
c_func
(paren
id|APUS_IPL_EMU
comma
id|IPLEMU_SETRESET
op_or
id|IPLEMU_IPLMASK
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* ... and enable the master interrupt bit */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|IF_INTEN
suffix:semicolon
id|cia_init_IRQ
c_func
(paren
op_amp
id|ciaa_base
)paren
suffix:semicolon
id|cia_init_IRQ
c_func
(paren
op_amp
id|ciab_base
)paren
suffix:semicolon
)brace
DECL|function|amiga_insert_irq
r_static
r_inline
r_int
id|amiga_insert_irq
c_func
(paren
id|irq_node_t
op_star
op_star
id|list
comma
id|irq_node_t
op_star
id|node
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_node_t
op_star
id|cur
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node-&gt;dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Warning: dev_id of %s is zero&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|node-&gt;devname
)paren
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
id|cur
op_assign
op_star
id|list
suffix:semicolon
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|SA_SHIRQ
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/*&n;&t;&t; * There should never be more than one&n;&t;&t; */
r_while
c_loop
(paren
id|cur
op_logical_and
id|cur-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
(brace
id|list
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
r_else
(brace
r_while
c_loop
(paren
id|cur
)paren
(brace
id|list
op_assign
op_amp
id|cur-&gt;next
suffix:semicolon
id|cur
op_assign
id|cur-&gt;next
suffix:semicolon
)brace
)brace
id|node-&gt;next
op_assign
id|cur
suffix:semicolon
op_star
id|list
op_assign
id|node
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amiga_delete_irq
r_static
r_inline
r_void
id|amiga_delete_irq
c_func
(paren
id|irq_node_t
op_star
op_star
id|list
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|irq_node_t
op_star
id|node
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
id|node
op_assign
op_star
id|list
suffix:semicolon
id|node
suffix:semicolon
id|list
op_assign
op_amp
id|node-&gt;next
comma
id|node
op_assign
op_star
id|list
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;dev_id
op_eq
id|dev_id
)paren
(brace
op_star
id|list
op_assign
id|node-&gt;next
suffix:semicolon
multiline_comment|/* Mark it as free. */
id|node-&gt;handler
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
l_string|&quot;%s: tried to remove invalid irq&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * amiga_request_irq : add an interrupt service routine for a particular&n; *                     machine specific interrupt source.&n; *                     If the addition was successful, it returns 0.&n; */
DECL|function|amiga_request_irq
r_int
id|amiga_request_irq
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
id|irq_node_t
op_star
id|node
suffix:semicolon
r_int
id|error
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|AMI_IRQS
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Unknown IRQ %d from %s&bslash;n&quot;
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
id|irq
op_ge
id|IRQ_AMIGA_AUTO
)paren
r_return
id|sys_request_irq
c_func
(paren
id|irq
op_minus
id|IRQ_AMIGA_AUTO
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
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_CIAA
)paren
r_return
id|cia_request_irq
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
multiline_comment|/*&n;&t; * IRQ_AMIGA_PORTS &amp; IRQ_AMIGA_EXTER defaults to shared,&n;&t; * we could add a check here for the SA_SHIRQ flag but all drivers&n;&t; * should be aware of sharing anyway.&n;&t; */
r_if
c_cond
(paren
id|ami_servers
(braket
id|irq
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|new_irq_node
c_func
(paren
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|node-&gt;handler
op_assign
id|handler
suffix:semicolon
id|node-&gt;flags
op_assign
id|flags
suffix:semicolon
id|node-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|node-&gt;devname
op_assign
id|devname
suffix:semicolon
id|node-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
id|amiga_insert_irq
c_func
(paren
op_amp
id|ami_irq_list
(braket
id|irq
)braket
comma
id|node
)paren
suffix:semicolon
)brace
r_else
(brace
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|handler
op_assign
id|handler
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|flags
op_assign
id|flags
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|devname
op_assign
id|devname
suffix:semicolon
)brace
multiline_comment|/* enable the interrupt */
r_if
c_cond
(paren
id|irq
OL
id|IRQ_AMIGA_PORTS
op_logical_and
op_logical_neg
id|ami_ablecount
(braket
id|irq
)braket
)paren
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|amiga_free_irq
r_void
id|amiga_free_irq
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
op_ge
id|AMI_IRQS
)paren
(brace
id|printk
(paren
l_string|&quot;%s: Unknown IRQ %d&bslash;n&quot;
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
id|irq
op_ge
id|IRQ_AMIGA_AUTO
)paren
id|sys_free_irq
c_func
(paren
id|irq
op_minus
id|IRQ_AMIGA_AUTO
comma
id|dev_id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_CIAA
)paren
(brace
id|cia_free_irq
c_func
(paren
id|irq
comma
id|dev_id
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ami_servers
(braket
id|irq
)braket
)paren
(brace
id|amiga_delete_irq
c_func
(paren
op_amp
id|ami_irq_list
(braket
id|irq
)braket
comma
id|dev_id
)paren
suffix:semicolon
multiline_comment|/* if server list empty, disable the interrupt */
r_if
c_cond
(paren
op_logical_neg
id|ami_irq_list
(braket
id|irq
)braket
op_logical_and
id|irq
OL
id|IRQ_AMIGA_PORTS
)paren
id|custom.intena
op_assign
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|devname
)paren
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|handler
op_assign
id|ami_badint
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|flags
op_assign
l_int|0
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|custom.intena
op_assign
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Enable/disable a particular machine specific interrupt source.&n; * Note that this may affect other interrupts in case of a shared interrupt.&n; * This function should only be called for a _very_ short time to change some&n; * internal data, that may not be changed by the interrupt at the same time.&n; * ami_(enable|disable)_irq calls may also be nested.&n; */
DECL|function|amiga_enable_irq
r_void
id|amiga_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ge
id|AMI_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Unknown IRQ %d&bslash;n&quot;
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
op_decrement
id|ami_ablecount
(braket
id|irq
)braket
)paren
r_return
suffix:semicolon
multiline_comment|/* No action for auto-vector interrupts */
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_AUTO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Trying to enable auto-vector IRQ %i&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
op_minus
id|IRQ_AMIGA_AUTO
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_CIAA
)paren
(brace
id|cia_set_irq
c_func
(paren
id|irq
comma
l_int|0
)paren
suffix:semicolon
id|cia_able_irq
c_func
(paren
id|irq
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* enable the interrupt */
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
)brace
DECL|function|amiga_disable_irq
r_void
id|amiga_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
id|irq
op_ge
id|AMI_IRQS
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Unknown IRQ %d&bslash;n&quot;
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
id|ami_ablecount
(braket
id|irq
)braket
op_increment
)paren
r_return
suffix:semicolon
multiline_comment|/* No action for auto-vector interrupts */
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_AUTO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Trying to disable auto-vector IRQ %i&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
op_minus
id|IRQ_AMIGA_AUTO
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ge
id|IRQ_AMIGA_CIAA
)paren
(brace
id|cia_able_irq
c_func
(paren
id|irq
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* disable the interrupt */
id|custom.intena
op_assign
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
)brace
DECL|function|amiga_do_irq
r_inline
r_void
id|amiga_do_irq
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|SYS_IRQS
op_plus
id|irq
)braket
op_increment
suffix:semicolon
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|ami_irq_list
(braket
id|irq
)braket
op_member_access_from_pointer
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
DECL|function|amiga_do_irq_list
r_void
id|amiga_do_irq_list
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|fp
comma
r_struct
id|irq_server
op_star
id|server
)paren
(brace
id|irq_node_t
op_star
id|node
comma
op_star
id|slow_nodes
suffix:semicolon
r_int
r_int
id|intena
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|SYS_IRQS
op_plus
id|irq
)braket
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|server-&gt;count
op_increment
)paren
id|server-&gt;reentrance
op_assign
l_int|1
suffix:semicolon
id|intena
op_assign
id|ami_intena_vals
(braket
id|irq
)braket
suffix:semicolon
id|custom.intreq
op_assign
id|intena
suffix:semicolon
multiline_comment|/* serve first fast handlers - there can only be one of these */
id|node
op_assign
id|ami_irq_list
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/*&n;&t; * Timer interrupts show up like this&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|server-&gt;count
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|node
op_logical_and
(paren
id|node-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
(brace
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
id|node
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|node-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|server-&gt;count
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Disable the interrupt source in question and reenable all&n;&t; * other interrupts. No interrupt handler should ever touch&n;&t; * the intena flags directly!&n;&t; */
id|custom.intena
op_assign
id|intena
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|slow_nodes
op_assign
id|node
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|node
suffix:semicolon
id|node
op_assign
id|node-&gt;next
)paren
id|node
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|node-&gt;dev_id
comma
id|fp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|server-&gt;reentrance
)paren
(brace
id|server-&gt;count
op_decrement
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|custom.intena
op_assign
id|IF_SETCLR
op_or
id|intena
suffix:semicolon
r_return
suffix:semicolon
)brace
id|server-&gt;reentrance
op_assign
l_int|0
suffix:semicolon
id|node
op_assign
id|slow_nodes
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The builtin Amiga hardware interrupt handlers.&n; */
DECL|function|ami_int1
r_static
r_void
id|ami_int1
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|ints
op_assign
id|custom.intreqr
op_amp
id|custom.intenar
suffix:semicolon
multiline_comment|/* if serial transmit buffer empty, interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_TBE
)paren
(brace
id|custom.intreq
op_assign
id|IF_TBE
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_TBE
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if floppy disk transfer complete, interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_DSKBLK
)paren
(brace
id|custom.intreq
op_assign
id|IF_DSKBLK
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_DSKBLK
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if software interrupt set, interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_SOFT
)paren
(brace
id|custom.intreq
op_assign
id|IF_SOFT
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_SOFT
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
DECL|function|ami_int3
r_static
r_void
id|ami_int3
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|ints
op_assign
id|custom.intreqr
op_amp
id|custom.intenar
suffix:semicolon
r_static
r_struct
id|irq_server
id|server
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* if a blitter interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_BLIT
)paren
(brace
id|custom.intreq
op_assign
id|IF_BLIT
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_BLIT
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if a copper interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_COPER
)paren
(brace
id|custom.intreq
op_assign
id|IF_COPER
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_COPPER
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if a vertical blank interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_VERTB
)paren
id|amiga_do_irq_list
c_func
(paren
id|IRQ_AMIGA_VERTB
comma
id|fp
comma
op_amp
id|server
)paren
suffix:semicolon
)brace
DECL|function|ami_int4
r_static
r_void
id|ami_int4
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|ints
op_assign
id|custom.intreqr
op_amp
id|custom.intenar
suffix:semicolon
multiline_comment|/* if audio 0 interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_AUD0
)paren
(brace
id|custom.intreq
op_assign
id|IF_AUD0
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_AUD0
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if audio 1 interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_AUD1
)paren
(brace
id|custom.intreq
op_assign
id|IF_AUD1
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_AUD1
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if audio 2 interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_AUD2
)paren
(brace
id|custom.intreq
op_assign
id|IF_AUD2
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_AUD2
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if audio 3 interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_AUD3
)paren
(brace
id|custom.intreq
op_assign
id|IF_AUD3
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_AUD3
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
DECL|function|ami_int5
r_static
r_void
id|ami_int5
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
r_int
id|ints
op_assign
id|custom.intreqr
op_amp
id|custom.intenar
suffix:semicolon
multiline_comment|/* if serial receive buffer full interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_RBF
)paren
(brace
multiline_comment|/* acknowledge of IF_RBF must be done by the serial interrupt */
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_RBF
comma
id|fp
)paren
suffix:semicolon
)brace
multiline_comment|/* if a disk sync interrupt */
r_if
c_cond
(paren
id|ints
op_amp
id|IF_DSKSYN
)paren
(brace
id|custom.intreq
op_assign
id|IF_DSKSYN
suffix:semicolon
id|amiga_do_irq
c_func
(paren
id|IRQ_AMIGA_DSKSYN
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
DECL|function|ami_int7
r_static
r_void
id|ami_int7
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
id|panic
(paren
l_string|&quot;level 7 interrupt received&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_APUS
multiline_comment|/* The PPC irq handling links all handlers requested on the same vector&n;   and executes them in a loop. Having ami_badint at the end of the chain&n;   is a bad idea. */
DECL|variable|amiga_default_handler
r_void
(paren
op_star
id|amiga_default_handler
(braket
id|SYS_IRQS
)braket
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
op_assign
(brace
l_int|NULL
comma
id|ami_int1
comma
l_int|NULL
comma
l_int|NULL
multiline_comment|/* FB expects to replace ami_int3*/
comma
id|ami_int4
comma
id|ami_int5
comma
l_int|NULL
comma
id|ami_int7
)brace
suffix:semicolon
macro_line|#else
DECL|variable|amiga_default_handler
r_void
(paren
op_star
id|amiga_default_handler
(braket
id|SYS_IRQS
)braket
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
op_assign
(brace
id|ami_badint
comma
id|ami_int1
comma
id|ami_badint
comma
id|ami_int3
comma
id|ami_int4
comma
id|ami_int5
comma
id|ami_badint
comma
id|ami_int7
)brace
suffix:semicolon
macro_line|#endif
DECL|function|amiga_get_irq_list
r_int
id|amiga_get_irq_list
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
id|irq_node_t
op_star
id|node
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
id|AMI_STD_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|node
op_assign
id|ami_irq_list
(braket
id|i
)braket
)paren
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
l_string|&quot;ami  %2d: %10u &quot;
comma
id|i
comma
id|kstat.irqs
(braket
l_int|0
)braket
(braket
id|SYS_IRQS
op_plus
id|i
)braket
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|node-&gt;flags
op_amp
id|SA_INTERRUPT
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
l_string|&quot;F &quot;
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
id|node-&gt;devname
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|node
op_assign
id|node-&gt;next
)paren
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
l_string|&quot;                    &quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|node
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|cia_get_irq_list
c_func
(paren
op_amp
id|ciaa_base
comma
id|buf
op_plus
id|len
)paren
suffix:semicolon
id|len
op_add_assign
id|cia_get_irq_list
c_func
(paren
op_amp
id|ciab_base
comma
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
