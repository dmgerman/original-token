multiline_comment|/* $Id: parport_share.c,v 1.1.2.4 1997/04/01 18:19:11 phil Exp $&n; * Parallel-port resource manager code.&n; * &n; * Authors: David Campbell &lt;campbell@tirian.che.curtin.edu.au&gt;&n; *          Tim Waugh &lt;tmw20@cam.ac.uk&gt;&n; *&t;    Jose Renau &lt;renau@acm.org&gt;&n; *&n; * based on work by Grant Guenther &lt;grant@torque.net&gt;&n; *              and Philip Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &quot;parport_ll_io.h&quot;
DECL|variable|portlist
DECL|variable|portlist_tail
r_static
r_struct
id|parport
op_star
id|portlist
op_assign
l_int|NULL
comma
op_star
id|portlist_tail
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|portcount
r_static
r_int
id|portcount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* from parport_init.c */
r_extern
r_int
id|initialize_parport
c_func
(paren
r_struct
id|parport
op_star
comma
r_int
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|dma
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* Return a list of all the ports we know about. */
DECL|function|parport_enumerate
r_struct
id|parport
op_star
id|parport_enumerate
c_func
(paren
r_void
)paren
(brace
r_return
id|portlist
suffix:semicolon
)brace
DECL|function|parport_null_intr_func
r_static
r_void
id|parport_null_intr_func
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
id|regs
)paren
(brace
multiline_comment|/* NULL function - Does nothing */
r_return
suffix:semicolon
)brace
DECL|function|parport_register_port
r_struct
id|parport
op_star
id|parport_register_port
c_func
(paren
r_int
r_int
id|base
comma
r_int
id|irq
comma
r_int
id|dma
)paren
(brace
r_struct
id|parport
r_new
comma
op_star
id|tmp
suffix:semicolon
multiline_comment|/* Check for a previously registered port.&n;&t; * NOTE: we will ignore irq and dma if we find a previously&n;&t; * registered device.&n;&t; */
r_for
c_loop
(paren
id|tmp
op_assign
id|portlist
suffix:semicolon
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;base
op_eq
id|base
)paren
r_return
id|tmp
suffix:semicolon
)brace
multiline_comment|/* Has someone grabbed the address yet? */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base
comma
l_int|3
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|initialize_parport
c_func
(paren
op_amp
r_new
comma
id|base
comma
id|irq
comma
id|dma
comma
id|portcount
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
r_new
dot
id|dma
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
r_new
dot
id|dma
comma
r_new
dot
id|name
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unable to claim DMA %d&bslash;n&quot;
comma
r_new
dot
id|name
comma
r_new
dot
id|dma
)paren
suffix:semicolon
id|release_region
c_func
(paren
r_new
dot
id|base
comma
r_new
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
dot
id|modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
r_new
dot
id|base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
r_new
dot
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|parport
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;parport: memory squeeze&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
r_new
dot
id|base
comma
r_new
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
dot
id|modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
r_new
dot
id|base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
r_new
dot
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|tmp
comma
op_amp
r_new
comma
r_sizeof
(paren
r_struct
id|parport
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
dot
id|irq
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
r_new
dot
id|irq
comma
id|parport_null_intr_func
comma
id|SA_INTERRUPT
comma
r_new
dot
id|name
comma
id|tmp
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: unable to claim IRQ %d&bslash;n&quot;
comma
r_new
dot
id|name
comma
r_new
dot
id|irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|release_region
c_func
(paren
r_new
dot
id|base
comma
r_new
dot
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
dot
id|modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
r_new
dot
id|base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
id|kfree
c_func
(paren
r_new
dot
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* Here we chain the entry to our list. */
r_if
c_cond
(paren
id|portlist_tail
)paren
id|portlist_tail-&gt;next
op_assign
id|tmp
suffix:semicolon
id|portlist_tail
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|portlist
)paren
id|portlist
op_assign
id|tmp
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s at 0x%x&quot;
comma
id|tmp-&gt;name
comma
id|tmp-&gt;base
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;irq
op_ge
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;, irq %d&quot;
comma
id|tmp-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;dma
op_ge
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;, dma %d&quot;
comma
id|tmp-&gt;dma
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [&quot;
)paren
suffix:semicolon
(brace
multiline_comment|/* Ugh! */
DECL|macro|printmode
mdefine_line|#define printmode(x) {if(tmp-&gt;modes&amp;PARPORT_MODE_##x){printk(&quot;%s%s&quot;,f?&quot;,&quot;:&quot;&quot;,#x);f++;}}
r_int
id|f
op_assign
l_int|0
suffix:semicolon
id|printmode
c_func
(paren
id|SPP
)paren
suffix:semicolon
id|printmode
c_func
(paren
id|PS2
)paren
suffix:semicolon
id|printmode
c_func
(paren
id|EPP
)paren
suffix:semicolon
id|printmode
c_func
(paren
id|ECP
)paren
suffix:semicolon
id|printmode
c_func
(paren
id|ECPEPP
)paren
suffix:semicolon
id|printmode
c_func
(paren
id|ECPPS2
)paren
suffix:semicolon
DECL|macro|printmode
macro_line|#undef printmode
)brace
id|printk
c_func
(paren
l_string|&quot;]&bslash;n&quot;
)paren
suffix:semicolon
id|portcount
op_increment
suffix:semicolon
multiline_comment|/* Restore device back to default conditions */
r_if
c_cond
(paren
id|tmp-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
id|w_ecr
c_func
(paren
id|tmp
comma
id|tmp-&gt;ecr
)paren
suffix:semicolon
id|w_ctr
c_func
(paren
id|tmp
comma
id|tmp-&gt;ctr
)paren
suffix:semicolon
id|tmp-&gt;probe_info
dot
r_class
op_assign
id|PARPORT_CLASS_LEGACY
suffix:semicolon
multiline_comment|/* assume the worst */
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|parport_destroy
r_void
id|parport_destroy
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
multiline_comment|/* Dangerous to try destroying a port if its friends are nearby. */
r_if
c_cond
(paren
id|port-&gt;devices
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: attempt to release active port&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/* Devices still present */
)brace
multiline_comment|/* No point in further destroying a port that already lies in ruins. */
r_if
c_cond
(paren
id|port-&gt;flags
op_amp
id|PARPORT_FLAG_COMA
)paren
r_return
suffix:semicolon
multiline_comment|/* Now clean out the port entry */
r_if
c_cond
(paren
id|port-&gt;irq
op_ge
l_int|0
)paren
id|free_irq
c_func
(paren
id|port-&gt;irq
comma
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;dma
op_ge
l_int|0
)paren
id|free_dma
c_func
(paren
id|port-&gt;dma
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|port-&gt;base
comma
id|port-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
id|port-&gt;base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
id|port-&gt;flags
op_or_assign
id|PARPORT_FLAG_COMA
suffix:semicolon
)brace
DECL|function|parport_register_device
r_struct
id|ppd
op_star
id|parport_register_device
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_const
r_char
op_star
id|name
comma
id|callback_func
id|pf
comma
id|callback_func
id|kf
comma
id|irq_handler_func
id|irq_func
comma
r_int
id|flags
comma
r_void
op_star
id|handle
)paren
(brace
r_struct
id|ppd
op_star
id|tmp
suffix:semicolon
multiline_comment|/* We only allow one lurker device (eg PLIP) */
r_if
c_cond
(paren
id|flags
op_amp
id|PARPORT_DEV_LURK
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;lurker
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: refused to register second lurker (%s)&bslash;n&quot;
comma
id|port-&gt;name
comma
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pf
op_logical_or
op_logical_neg
id|kf
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: refused to register lurking device (%s) without callbacks&bslash;n&quot;
comma
id|port-&gt;name
comma
id|name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/* We may need to claw back the port hardware. */
r_if
c_cond
(paren
id|port-&gt;flags
op_amp
id|PARPORT_FLAG_COMA
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|port-&gt;base
comma
l_int|3
)paren
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|port-&gt;base
comma
id|port-&gt;size
comma
id|port-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|request_region
c_func
(paren
id|port-&gt;base
op_plus
l_int|0x400
comma
l_int|3
comma
id|port-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;dma
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|port-&gt;dma
comma
id|port-&gt;name
)paren
)paren
(brace
id|release_region
c_func
(paren
id|port-&gt;base
comma
id|port-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
id|port-&gt;base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|port-&gt;irq
op_ne
op_minus
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|port-&gt;irq
comma
id|parport_null_intr_func
comma
id|SA_INTERRUPT
comma
id|port-&gt;name
comma
id|port
)paren
op_ne
l_int|0
)paren
(brace
id|release_region
c_func
(paren
id|port-&gt;base
comma
id|port-&gt;size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
(brace
id|release_region
c_func
(paren
id|port-&gt;base
op_plus
l_int|0x400
comma
l_int|3
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;dma
op_ge
l_int|0
)paren
id|free_dma
c_func
(paren
id|port-&gt;dma
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
)brace
id|port-&gt;flags
op_and_assign
op_complement
id|PARPORT_FLAG_COMA
suffix:semicolon
)brace
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ppd
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|tmp-&gt;name
op_assign
(paren
r_char
op_star
)paren
id|name
suffix:semicolon
id|tmp-&gt;port
op_assign
id|port
suffix:semicolon
id|tmp-&gt;preempt
op_assign
id|pf
suffix:semicolon
id|tmp-&gt;wakeup
op_assign
id|kf
suffix:semicolon
id|tmp
op_member_access_from_pointer
r_private
op_assign
id|handle
suffix:semicolon
id|tmp-&gt;irq_func
op_assign
id|irq_func
suffix:semicolon
id|tmp-&gt;ctr
op_assign
id|port-&gt;ctr
suffix:semicolon
id|tmp-&gt;ecr
op_assign
id|port-&gt;ecr
suffix:semicolon
multiline_comment|/* Chain this onto the list */
id|tmp-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
id|tmp-&gt;next
op_assign
id|port-&gt;devices
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;devices
)paren
id|port-&gt;devices-&gt;prev
op_assign
id|tmp
suffix:semicolon
id|port-&gt;devices
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PARPORT_DEV_LURK
)paren
id|port-&gt;lurker
op_assign
id|tmp
suffix:semicolon
id|inc_parport_count
c_func
(paren
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|parport_unregister_device
r_void
id|parport_unregister_device
c_func
(paren
r_struct
id|ppd
op_star
id|dev
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport_unregister_device: passed NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|port
op_assign
id|dev-&gt;port
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;cad
op_eq
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: refused to unregister currently active device %s&bslash;n&quot;
comma
id|port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;lurker
op_eq
id|dev
)paren
id|port-&gt;lurker
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;next
)paren
id|dev-&gt;next-&gt;prev
op_assign
id|dev-&gt;prev
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;prev
)paren
id|dev-&gt;prev-&gt;next
op_assign
id|dev-&gt;next
suffix:semicolon
r_else
id|port-&gt;devices
op_assign
id|dev-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dec_parport_count
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If there are no more devices, put the port to sleep. */
r_if
c_cond
(paren
op_logical_neg
id|port-&gt;devices
)paren
id|parport_destroy
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|parport_claim
r_int
id|parport_claim
c_func
(paren
r_struct
id|ppd
op_star
id|dev
)paren
(brace
r_struct
id|ppd
op_star
id|pd1
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
op_eq
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: %s already owner&bslash;n&quot;
comma
id|dev-&gt;port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Preempt any current device */
id|pd1
op_assign
id|dev-&gt;port-&gt;cad
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad-&gt;preempt
)paren
(brace
multiline_comment|/* Now try to preempt */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
op_member_access_from_pointer
id|preempt
c_func
(paren
id|dev-&gt;port-&gt;cad
op_member_access_from_pointer
r_private
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
multiline_comment|/* Save control registers */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
id|dev-&gt;port-&gt;cad-&gt;ecr
op_assign
id|dev-&gt;port-&gt;ecr
op_assign
id|r_ecr
c_func
(paren
id|dev-&gt;port
)paren
suffix:semicolon
id|dev-&gt;port-&gt;cad-&gt;ctr
op_assign
id|dev-&gt;port-&gt;ctr
op_assign
id|r_ctr
c_func
(paren
id|dev-&gt;port
)paren
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/* Watch out for bad things */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
op_ne
id|pd1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: death while preempting %s&bslash;n&quot;
comma
id|dev-&gt;port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/* Now we do the change of devices */
id|dev-&gt;port-&gt;cad
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;irq
op_ge
l_int|0
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;port-&gt;irq
comma
id|dev-&gt;port
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|dev-&gt;port-&gt;irq
comma
id|dev-&gt;irq_func
ques
c_cond
id|dev-&gt;irq_func
suffix:colon
id|parport_null_intr_func
comma
id|SA_INTERRUPT
comma
id|dev-&gt;name
comma
id|dev-&gt;port
)paren
suffix:semicolon
)brace
multiline_comment|/* Restore control registers */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
r_if
c_cond
(paren
id|dev-&gt;ecr
op_ne
id|dev-&gt;port-&gt;ecr
)paren
id|w_ecr
c_func
(paren
id|dev-&gt;port
comma
id|dev-&gt;ecr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;ctr
op_ne
id|dev-&gt;port-&gt;ctr
)paren
id|w_ctr
c_func
(paren
id|dev-&gt;port
comma
id|dev-&gt;ctr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parport_release
r_void
id|parport_release
c_func
(paren
r_struct
id|ppd
op_star
id|dev
)paren
(brace
r_struct
id|ppd
op_star
id|pd1
suffix:semicolon
multiline_comment|/* Make sure that dev is the current device */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
op_ne
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: %s tried to release parport when not owner&bslash;n&quot;
comma
id|dev-&gt;port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev-&gt;port-&gt;cad
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Save control registers */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;modes
op_amp
id|PARPORT_MODE_ECR
)paren
id|dev-&gt;ecr
op_assign
id|dev-&gt;port-&gt;ecr
op_assign
id|r_ecr
c_func
(paren
id|dev-&gt;port
)paren
suffix:semicolon
id|dev-&gt;ctr
op_assign
id|dev-&gt;port-&gt;ctr
op_assign
id|r_ctr
c_func
(paren
id|dev-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;irq
op_ge
l_int|0
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;port-&gt;irq
comma
id|dev-&gt;port
)paren
suffix:semicolon
id|request_irq
c_func
(paren
id|dev-&gt;port-&gt;irq
comma
id|parport_null_intr_func
comma
id|SA_INTERRUPT
comma
id|dev-&gt;port-&gt;name
comma
id|dev-&gt;port
)paren
suffix:semicolon
)brace
multiline_comment|/* Walk the list, offering a wakeup callback to everybody other&n;&t; * than the lurker and the device that called us.&n;&t; */
r_for
c_loop
(paren
id|pd1
op_assign
id|dev-&gt;next
suffix:semicolon
id|pd1
suffix:semicolon
id|pd1
op_assign
id|pd1-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pd1-&gt;flags
op_amp
id|PARPORT_DEV_LURK
)paren
)paren
(brace
r_if
c_cond
(paren
id|pd1-&gt;wakeup
)paren
(brace
id|pd1
op_member_access_from_pointer
id|wakeup
c_func
(paren
id|pd1
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
)paren
r_return
suffix:semicolon
)brace
)brace
)brace
r_for
c_loop
(paren
id|pd1
op_assign
id|dev-&gt;port-&gt;devices
suffix:semicolon
id|pd1
op_logical_and
id|pd1
op_ne
id|dev
suffix:semicolon
id|pd1
op_assign
id|pd1-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pd1-&gt;flags
op_amp
id|PARPORT_DEV_LURK
)paren
)paren
(brace
r_if
c_cond
(paren
id|pd1-&gt;wakeup
)paren
(brace
id|pd1
op_member_access_from_pointer
id|wakeup
c_func
(paren
id|pd1
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
)paren
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* Now give the lurker a chance.&n;&t; * There should be a wakeup callback because we checked for it&n;&t; * at registration.&n;&t; */
r_if
c_cond
(paren
id|dev-&gt;port-&gt;lurker
op_logical_and
(paren
id|dev-&gt;port-&gt;lurker
op_ne
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;port-&gt;lurker-&gt;wakeup
)paren
(brace
id|dev-&gt;port-&gt;lurker
op_member_access_from_pointer
id|wakeup
c_func
(paren
id|dev-&gt;port-&gt;lurker
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s (%s): lurker&squot;s wakeup callback went away!&bslash;n&quot;
comma
id|dev-&gt;port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* The following read funktions are an implementation of a status readback&n; * and device id request confirming to IEEE1284-1994.&n; */
multiline_comment|/* Wait for Status line(s) to change in 35 ms - see IEEE1284-1994 page 24 to&n; * 25 for this. After this time we can create a timeout because the&n; * peripheral doesn&squot;t conform to IEEE1284. We want to save CPU time: we are&n; * waiting a maximum time of 500 us busy (this is for speed). If there is&n; * not the right answer in this time, we call schedule and other processes&n; * are able &quot;to eat&quot; the time up to 30ms.  So the maximum load avarage can&squot;t&n; * get above 5% for a read even if the peripheral is really slow. (but your&n; * read gets very slow then - only about 10 characters per second. This&n; * should be tuneable). Thanks to Andreas who pointed me to this and ordered&n; * the documentation.&n; */
DECL|function|parport_wait_peripheral
r_int
id|parport_wait_peripheral
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|result
)paren
(brace
r_int
id|counter
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_do
(brace
id|status
op_assign
id|parport_r_status
c_func
(paren
id|port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|25
)paren
suffix:semicolon
id|counter
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
(paren
id|status
op_amp
id|mask
)paren
op_ne
id|result
)paren
op_logical_and
(paren
id|counter
OL
l_int|20
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|counter
op_eq
l_int|20
)paren
op_logical_and
(paren
(paren
id|status
op_amp
id|mask
)paren
op_ne
id|result
)paren
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
l_int|4
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* wait for 4 scheduler runs (40ms) */
id|status
op_assign
id|parport_r_status
c_func
(paren
id|port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
id|mask
)paren
op_ne
id|result
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* timeout */
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* okay right response from device */
)brace
multiline_comment|/* Test if nibble mode for status readback is okay. Returns the value false&n; * if the printer doesn&squot;t support readback at all. If it supports readbacks&n; * and printer data is available the function returns 1, otherwise 2. The&n; * only valid values for &quot;mode&quot; are 0 and 4. 0 requests normal nibble mode,&n; * 4 is for &quot;request device id using nibble mode&quot;. The request for the&n; * device id is best done in an ioctl (or at bootup time).  There is no&n; * check for an invalid value, the only function using this call at the&n; * moment is lp_read and the ioctl LPGETDEVICEID both fixed calls from&n; * trusted kernel.&n; */
DECL|function|parport_ieee1284_nibble_mode_ok
r_int
id|parport_ieee1284_nibble_mode_ok
c_func
(paren
r_struct
id|parport
op_star
id|port
comma
r_int
r_char
id|mode
)paren
(brace
id|parport_w_data
c_func
(paren
id|port
comma
id|mode
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|parport_w_ctrl
c_func
(paren
id|port
comma
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|8
)paren
suffix:semicolon
multiline_comment|/* SelectIN low */
id|parport_w_ctrl
c_func
(paren
id|port
comma
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_or
l_int|2
)paren
suffix:semicolon
multiline_comment|/* AutoFeed high */
r_if
c_cond
(paren
id|parport_wait_peripheral
c_func
(paren
id|port
comma
l_int|0x78
comma
l_int|0x38
)paren
)paren
(brace
multiline_comment|/* timeout? */
id|parport_w_ctrl
c_func
(paren
id|port
comma
(paren
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|2
)paren
op_or
l_int|8
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* first stage of negotiation failed, &n;                           * no IEEE1284 compliant device on this port &n;                           */
)brace
id|parport_w_ctrl
c_func
(paren
id|port
comma
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_or
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Strobe high */
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Strobe wait */
id|parport_w_ctrl
c_func
(paren
id|port
comma
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Strobe low */
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|parport_w_ctrl
c_func
(paren
id|port
comma
id|parport_r_ctrl
c_func
(paren
id|port
)paren
op_amp
op_complement
l_int|2
)paren
suffix:semicolon
multiline_comment|/* AutoFeed low */
r_return
(paren
id|parport_wait_peripheral
c_func
(paren
id|port
comma
l_int|0x20
comma
l_int|0
)paren
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|1
suffix:semicolon
)brace
eof
