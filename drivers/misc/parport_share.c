multiline_comment|/* $Id: parport_share.c,v 1.15 1998/01/11 12:06:17 philip Exp $&n; * Parallel-port resource manager code.&n; * &n; * Authors: David Campbell &lt;campbell@tirian.che.curtin.edu.au&gt;&n; *          Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *          Jose Renau &lt;renau@acm.org&gt;&n; *          Philip Blundell &lt;philb@gnu.org&gt;&n; *&t;    Andrea Arcangeli&n; *&n; * based on work by Grant Guenther &lt;grant@torque.net&gt;&n; *          and Philip Blundell&n; */
DECL|macro|PARPORT_DEBUG_SHARING
macro_line|#undef PARPORT_DEBUG_SHARING&t;&t;/* undef for production */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/spinlock.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#ifdef CONFIG_KMOD
macro_line|#include &lt;linux/kmod.h&gt;
macro_line|#endif
DECL|macro|PARPORT_PARANOID
macro_line|#undef PARPORT_PARANOID
DECL|macro|PARPORT_DEFAULT_TIMESLICE
mdefine_line|#define PARPORT_DEFAULT_TIMESLICE&t;(HZ/5)
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
DECL|variable|parportlist_lock
id|spinlock_t
id|parportlist_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|driver_chain
r_static
r_struct
id|parport_driver
op_star
id|driver_chain
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|driverlist_lock
id|spinlock_t
id|driverlist_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|call_driver_chain
r_static
r_void
id|call_driver_chain
(paren
r_int
id|attach
comma
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|parport_driver
op_star
id|drv
suffix:semicolon
r_for
c_loop
(paren
id|drv
op_assign
id|driver_chain
suffix:semicolon
id|drv
suffix:semicolon
id|drv
op_assign
id|drv-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|attach
)paren
id|drv-&gt;attach
(paren
id|port
)paren
suffix:semicolon
r_else
id|drv-&gt;detach
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|parport_register_driver
r_int
id|parport_register_driver
(paren
r_struct
id|parport_driver
op_star
id|drv
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
id|spin_lock
(paren
op_amp
id|driverlist_lock
)paren
suffix:semicolon
id|drv-&gt;next
op_assign
id|driver_chain
suffix:semicolon
id|driver_chain
op_assign
id|drv
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|driverlist_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
id|portlist
suffix:semicolon
id|port
suffix:semicolon
id|port
op_assign
id|port-&gt;next
)paren
id|drv-&gt;attach
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parport_unregister_driver
r_void
id|parport_unregister_driver
(paren
r_struct
id|parport_driver
op_star
id|arg
)paren
(brace
r_struct
id|parport_driver
op_star
id|drv
op_assign
id|driver_chain
comma
op_star
id|olddrv
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
id|drv
)paren
(brace
r_if
c_cond
(paren
id|drv
op_eq
id|arg
)paren
(brace
id|spin_lock
(paren
op_amp
id|driverlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|olddrv
)paren
id|olddrv-&gt;next
op_assign
id|drv-&gt;next
suffix:semicolon
r_else
id|driver_chain
op_assign
id|drv-&gt;next
suffix:semicolon
id|spin_unlock
(paren
op_amp
id|driverlist_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|olddrv
op_assign
id|drv
suffix:semicolon
id|drv
op_assign
id|drv-&gt;next
suffix:semicolon
)brace
)brace
DECL|variable|parport_probe_hook
r_void
(paren
op_star
id|parport_probe_hook
)paren
(paren
r_struct
id|parport
op_star
id|port
)paren
op_assign
l_int|NULL
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
macro_line|#ifdef CONFIG_KMOD
r_if
c_cond
(paren
id|portlist
op_eq
l_int|NULL
)paren
(brace
id|request_module
c_func
(paren
l_string|&quot;parport_lowlevel&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PNP_PARPORT_MODULE
id|request_module
c_func
(paren
l_string|&quot;parport_probe&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_PNP_PARPORT_MODULE */
)brace
macro_line|#endif /* CONFIG_KMOD */
r_return
id|portlist
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
comma
r_struct
id|parport_operations
op_star
id|ops
)paren
(brace
r_struct
id|parport
op_star
id|tmp
suffix:semicolon
r_int
id|portnum
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Check for a previously registered port.&n;&t;   NOTE: we will ignore irq and dma if we find a previously&n;&t;   registered device.  */
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
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Search for the lowest free parport number. */
r_for
c_loop
(paren
id|portnum
op_assign
l_int|0
suffix:semicolon
suffix:semicolon
id|portnum
op_increment
)paren
(brace
r_struct
id|parport
op_star
id|itr
op_assign
id|portlist
suffix:semicolon
r_while
c_loop
(paren
id|itr
)paren
(brace
r_if
c_cond
(paren
id|itr-&gt;number
op_eq
id|portnum
)paren
multiline_comment|/* No good, already used. */
r_break
suffix:semicolon
r_else
id|itr
op_assign
id|itr-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|itr
op_eq
l_int|NULL
)paren
multiline_comment|/* Got to the end of the list. */
r_break
suffix:semicolon
)brace
multiline_comment|/* Init our structure */
id|memset
c_func
(paren
id|tmp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|parport
)paren
)paren
suffix:semicolon
id|tmp-&gt;base
op_assign
id|base
suffix:semicolon
id|tmp-&gt;irq
op_assign
id|irq
suffix:semicolon
id|tmp-&gt;dma
op_assign
id|dma
suffix:semicolon
id|tmp-&gt;modes
op_assign
l_int|0
suffix:semicolon
id|tmp-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|tmp-&gt;devices
op_assign
id|tmp-&gt;cad
op_assign
l_int|NULL
suffix:semicolon
id|tmp-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|tmp-&gt;ops
op_assign
id|ops
suffix:semicolon
id|tmp-&gt;number
op_assign
id|portnum
suffix:semicolon
id|memset
(paren
op_amp
id|tmp-&gt;probe_info
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|parport_device_info
)paren
)paren
suffix:semicolon
id|tmp-&gt;cad_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|tmp-&gt;waitlist_lock
)paren
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|tmp-&gt;pardevice_lock
)paren
suffix:semicolon
id|name
op_assign
id|kmalloc
c_func
(paren
l_int|15
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parport: memory squeeze&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;parport%d&quot;
comma
id|portnum
)paren
suffix:semicolon
id|tmp-&gt;name
op_assign
id|name
suffix:semicolon
multiline_comment|/*&n;&t; * Chain the entry to our list.&n;&t; *&n;&t; * This function must not run from an irq handler so we don&squot; t need&n;&t; * to clear irq on the local CPU. -arca&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|parportlist_lock
)paren
suffix:semicolon
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
id|spin_unlock
c_func
(paren
op_amp
id|parportlist_lock
)paren
suffix:semicolon
id|tmp-&gt;probe_info
dot
r_class
op_assign
id|PARPORT_CLASS_LEGACY
suffix:semicolon
multiline_comment|/* assume the worst */
id|tmp-&gt;waithead
op_assign
id|tmp-&gt;waittail
op_assign
l_int|NULL
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
DECL|function|parport_announce_port
r_void
id|parport_announce_port
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
multiline_comment|/* Let drivers know that a new port has arrived. */
id|call_driver_chain
(paren
l_int|1
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|parport_unregister_port
r_void
id|parport_unregister_port
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_struct
id|parport
op_star
id|p
suffix:semicolon
multiline_comment|/* Spread the word. */
id|call_driver_chain
(paren
l_int|0
comma
id|port
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|parportlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|portlist
op_eq
id|port
)paren
(brace
r_if
c_cond
(paren
(paren
id|portlist
op_assign
id|port-&gt;next
)paren
op_eq
l_int|NULL
)paren
id|portlist_tail
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
r_for
c_loop
(paren
id|p
op_assign
id|portlist
suffix:semicolon
(paren
id|p
op_ne
l_int|NULL
)paren
op_logical_and
(paren
id|p-&gt;next
op_ne
id|port
)paren
suffix:semicolon
id|p
op_assign
id|p-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
(paren
id|p-&gt;next
op_assign
id|port-&gt;next
)paren
op_eq
l_int|NULL
)paren
id|portlist_tail
op_assign
id|p
suffix:semicolon
)brace
r_else
id|printk
(paren
id|KERN_WARNING
l_string|&quot;%s not found in port list!&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|parportlist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;probe_info.class_name
)paren
id|kfree
(paren
id|port-&gt;probe_info.class_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;probe_info.mfr
)paren
id|kfree
(paren
id|port-&gt;probe_info.mfr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;probe_info.model
)paren
id|kfree
(paren
id|port-&gt;probe_info.model
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;probe_info.cmdset
)paren
id|kfree
(paren
id|port-&gt;probe_info.cmdset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;probe_info.description
)paren
id|kfree
(paren
id|port-&gt;probe_info.description
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port-&gt;name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|parport_quiesce
r_void
id|parport_quiesce
c_func
(paren
r_struct
id|parport
op_star
id|port
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;devices
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: attempt to quiesce active port.&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port-&gt;flags
op_amp
id|PARPORT_FLAG_COMA
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: attempt to quiesce comatose port.&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|port-&gt;ops
op_member_access_from_pointer
id|release_resources
c_func
(paren
id|port
)paren
suffix:semicolon
id|port-&gt;flags
op_or_assign
id|PARPORT_FLAG_COMA
suffix:semicolon
)brace
DECL|function|parport_register_device
r_struct
id|pardevice
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
r_int
(paren
op_star
id|pf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|kf
)paren
(paren
r_void
op_star
)paren
comma
r_void
(paren
op_star
id|irq_func
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
id|flags
comma
r_void
op_star
id|handle
)paren
(brace
r_struct
id|pardevice
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;flags
op_amp
id|PARPORT_FLAG_EXCL
)paren
(brace
multiline_comment|/* An exclusive device is registered. */
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: no more devices allowed&bslash;n&quot;
comma
id|port-&gt;name
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
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
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|pardevice
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: memory squeeze, couldn&squot;t register %s.&bslash;n&quot;
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
id|tmp-&gt;state
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|parport_state
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;state
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: memory squeeze, couldn&squot;t register %s.&bslash;n&quot;
comma
id|port-&gt;name
comma
id|name
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
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
id|port-&gt;ops
op_member_access_from_pointer
id|claim_resources
c_func
(paren
id|port
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: unable to get hardware to register %s.&bslash;n&quot;
comma
id|port-&gt;name
comma
id|name
)paren
suffix:semicolon
id|kfree
(paren
id|tmp-&gt;state
)paren
suffix:semicolon
id|kfree
(paren
id|tmp
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|port-&gt;flags
op_and_assign
op_complement
id|PARPORT_FLAG_COMA
suffix:semicolon
)brace
id|tmp-&gt;name
op_assign
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
id|tmp-&gt;flags
op_assign
id|flags
suffix:semicolon
id|tmp-&gt;irq_func
op_assign
id|irq_func
suffix:semicolon
id|port-&gt;ops
op_member_access_from_pointer
id|init_state
c_func
(paren
id|tmp-&gt;state
)paren
suffix:semicolon
id|tmp-&gt;waiting
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Chain this onto the list */
id|tmp-&gt;prev
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * This function must not run from an irq handler so we don&squot; t need&n;&t; * to clear irq on the local CPU. -arca&n;&t; */
id|spin_lock
c_func
(paren
op_amp
id|port-&gt;pardevice_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PARPORT_DEV_EXCL
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;devices
)paren
(brace
id|spin_unlock
(paren
op_amp
id|port-&gt;pardevice_lock
)paren
suffix:semicolon
id|kfree
(paren
id|tmp-&gt;state
)paren
suffix:semicolon
id|kfree
(paren
id|tmp
)paren
suffix:semicolon
id|printk
(paren
id|KERN_DEBUG
l_string|&quot;%s: cannot grant exclusive access for &quot;
l_string|&quot;device %s&bslash;n&quot;
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
id|port-&gt;flags
op_or_assign
id|PARPORT_FLAG_EXCL
suffix:semicolon
)brace
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
id|spin_unlock
c_func
(paren
op_amp
id|port-&gt;pardevice_lock
)paren
suffix:semicolon
id|inc_parport_count
c_func
(paren
)paren
suffix:semicolon
id|port-&gt;ops
op_member_access_from_pointer
id|inc_use_count
c_func
(paren
)paren
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|tmp-&gt;wait_q
)paren
suffix:semicolon
id|tmp-&gt;timeslice
op_assign
id|PARPORT_DEFAULT_TIMESLICE
suffix:semicolon
id|tmp-&gt;waitnext
op_assign
id|tmp-&gt;waitprev
op_assign
l_int|NULL
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
id|pardevice
op_star
id|dev
)paren
(brace
r_struct
id|parport
op_star
id|port
suffix:semicolon
macro_line|#ifdef PARPORT_PARANOID
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
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
macro_line|#endif
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
id|KERN_WARNING
l_string|&quot;%s: refused to unregister &quot;
l_string|&quot;currently active device %s.&bslash;n&quot;
comma
id|port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|port-&gt;pardevice_lock
)paren
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
r_if
c_cond
(paren
id|dev-&gt;flags
op_amp
id|PARPORT_DEV_EXCL
)paren
id|port-&gt;flags
op_and_assign
op_complement
id|PARPORT_FLAG_EXCL
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|port-&gt;pardevice_lock
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;state
)paren
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
id|port-&gt;ops
op_member_access_from_pointer
id|dec_use_count
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
id|parport_quiesce
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
id|pardevice
op_star
id|dev
)paren
(brace
r_struct
id|pardevice
op_star
id|oldcad
suffix:semicolon
r_struct
id|parport
op_star
id|port
op_assign
id|dev-&gt;port
suffix:semicolon
r_int
r_int
id|flags
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
id|try_again
suffix:colon
multiline_comment|/* Preempt any current device */
r_if
c_cond
(paren
(paren
id|oldcad
op_assign
id|port-&gt;cad
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|oldcad-&gt;preempt
)paren
(brace
r_if
c_cond
(paren
id|oldcad
op_member_access_from_pointer
id|preempt
c_func
(paren
id|oldcad
op_member_access_from_pointer
r_private
)paren
)paren
r_goto
id|blocked
suffix:semicolon
id|port-&gt;ops
op_member_access_from_pointer
id|save_state
c_func
(paren
id|port
comma
id|dev-&gt;state
)paren
suffix:semicolon
)brace
r_else
r_goto
id|blocked
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;cad
op_ne
id|oldcad
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: %s released port when preempted!&bslash;n&quot;
comma
id|port-&gt;name
comma
id|oldcad-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;cad
)paren
r_goto
id|blocked
suffix:semicolon
)brace
)brace
multiline_comment|/* Can&squot;t fail from now on, so mark ourselves as no longer waiting.  */
r_if
c_cond
(paren
id|dev-&gt;waiting
op_amp
l_int|1
)paren
(brace
id|dev-&gt;waiting
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Take ourselves out of the wait list again.  */
id|spin_lock_irqsave
(paren
op_amp
id|port-&gt;waitlist_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;waitprev
)paren
id|dev-&gt;waitprev-&gt;waitnext
op_assign
id|dev-&gt;waitnext
suffix:semicolon
r_else
id|port-&gt;waithead
op_assign
id|dev-&gt;waitnext
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;waitnext
)paren
id|dev-&gt;waitnext-&gt;waitprev
op_assign
id|dev-&gt;waitprev
suffix:semicolon
r_else
id|port-&gt;waittail
op_assign
id|dev-&gt;waitprev
suffix:semicolon
id|spin_unlock_irqrestore
(paren
op_amp
id|port-&gt;waitlist_lock
comma
id|flags
)paren
suffix:semicolon
id|dev-&gt;waitprev
op_assign
id|dev-&gt;waitnext
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|oldcad
op_logical_and
id|port-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
op_logical_and
op_logical_neg
id|oldcad-&gt;irq_func
)paren
multiline_comment|/*&n;&t;&t; * If there was an irq pending it should hopefully happen&n;&t;&t; * before return from enable_irq(). -arca&n;&t;&t; */
id|enable_irq
c_func
(paren
id|port-&gt;irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Avoid running irq handlers if the pardevice doesn&squot; t use it. -arca&n;&t; */
r_if
c_cond
(paren
id|port-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
op_logical_and
op_logical_neg
id|dev-&gt;irq_func
)paren
id|disable_irq
c_func
(paren
id|port-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Now we do the change of devices */
id|write_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;cad_lock
comma
id|flags
)paren
suffix:semicolon
id|port-&gt;cad
op_assign
id|dev
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;cad_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Restore control registers */
id|port-&gt;ops
op_member_access_from_pointer
id|restore_state
c_func
(paren
id|port
comma
id|dev-&gt;state
)paren
suffix:semicolon
id|dev-&gt;time
op_assign
id|jiffies
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|blocked
suffix:colon
multiline_comment|/* If this is the first time we tried to claim the port, register an&n;&t;   interest.  This is only allowed for devices sleeping in&n;&t;   parport_claim_or_block(), or those with a wakeup function.  */
r_if
c_cond
(paren
id|dev-&gt;waiting
op_amp
l_int|2
op_logical_or
id|dev-&gt;wakeup
)paren
(brace
id|spin_lock_irqsave
(paren
op_amp
id|port-&gt;waitlist_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;cad
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* The port got released in the meantime. */
id|spin_unlock_irqrestore
(paren
op_amp
id|port-&gt;waitlist_lock
comma
id|flags
)paren
suffix:semicolon
r_goto
id|try_again
suffix:semicolon
)brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
op_amp
id|dev-&gt;waiting
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* First add ourselves to the end of the wait list. */
id|dev-&gt;waitnext
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;waitprev
op_assign
id|port-&gt;waittail
suffix:semicolon
r_if
c_cond
(paren
id|port-&gt;waittail
)paren
(brace
id|port-&gt;waittail-&gt;waitnext
op_assign
id|dev
suffix:semicolon
id|port-&gt;waittail
op_assign
id|dev
suffix:semicolon
)brace
r_else
id|port-&gt;waithead
op_assign
id|port-&gt;waittail
op_assign
id|dev
suffix:semicolon
)brace
id|spin_unlock_irqrestore
(paren
op_amp
id|port-&gt;waitlist_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
DECL|function|parport_claim_or_block
r_int
id|parport_claim_or_block
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
(brace
r_int
id|r
suffix:semicolon
multiline_comment|/* Signal to parport_claim() that we can wait even without a&n;&t;   wakeup function.  */
id|dev-&gt;waiting
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* Try to claim the port.  If this fails, we need to sleep.  */
id|r
op_assign
id|parport_claim
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|r
op_eq
op_minus
id|EAGAIN
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
macro_line|#ifdef PARPORT_DEBUG_SHARING
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: parport_claim() returned -EAGAIN&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
id|save_flags
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* If dev-&gt;waiting is clear now, an interrupt&n;&t;&t;   gave us the port and we would deadlock if we slept.  */
r_if
c_cond
(paren
id|dev-&gt;waiting
)paren
(brace
id|sleep_on
c_func
(paren
op_amp
id|dev-&gt;wait_q
)paren
suffix:semicolon
id|r
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|r
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef PARPORT_DEBUG_SHARING
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: didn&squot;t sleep in parport_claim_or_block()&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
macro_line|#endif
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
macro_line|#ifdef PARPORT_DEBUG_SHARING
r_if
c_cond
(paren
id|dev-&gt;port-&gt;cad
op_ne
id|dev
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s: exiting parport_claim_or_block but %s owns port!&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;port-&gt;cad
ques
c_cond
id|dev-&gt;port-&gt;cad-&gt;name
suffix:colon
l_string|&quot;nobody&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
id|dev-&gt;waiting
op_assign
l_int|0
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
DECL|function|parport_release
r_void
id|parport_release
c_func
(paren
r_struct
id|pardevice
op_star
id|dev
)paren
(brace
r_struct
id|parport
op_star
id|port
op_assign
id|dev-&gt;port
suffix:semicolon
r_struct
id|pardevice
op_star
id|pd
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Make sure that dev is the current device */
r_if
c_cond
(paren
id|port-&gt;cad
op_ne
id|dev
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: %s tried to release parport &quot;
l_string|&quot;when not owner&bslash;n&quot;
comma
id|port-&gt;name
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|write_lock_irqsave
c_func
(paren
op_amp
id|port-&gt;cad_lock
comma
id|flags
)paren
suffix:semicolon
id|port-&gt;cad
op_assign
l_int|NULL
suffix:semicolon
id|write_unlock_irqrestore
c_func
(paren
op_amp
id|port-&gt;cad_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reenable irq and so discard the eventually pending irq while&n;&t; * cad is NULL. -arca&n;&t; */
r_if
c_cond
(paren
id|port-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
op_logical_and
op_logical_neg
id|dev-&gt;irq_func
)paren
id|enable_irq
c_func
(paren
id|port-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Save control registers */
id|port-&gt;ops
op_member_access_from_pointer
id|save_state
c_func
(paren
id|port
comma
id|dev-&gt;state
)paren
suffix:semicolon
multiline_comment|/* If anybody is waiting, find out who&squot;s been there longest and&n;&t;   then wake them up. (Note: no locking required) */
r_for
c_loop
(paren
id|pd
op_assign
id|port-&gt;waithead
suffix:semicolon
id|pd
suffix:semicolon
id|pd
op_assign
id|pd-&gt;waitnext
)paren
(brace
r_if
c_cond
(paren
id|pd-&gt;waiting
op_amp
l_int|2
)paren
(brace
multiline_comment|/* sleeping in claim_or_block */
id|parport_claim
c_func
(paren
id|pd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|pd-&gt;wait_q
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|pd-&gt;wait_q
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pd-&gt;wakeup
)paren
(brace
id|pd
op_member_access_from_pointer
id|wakeup
c_func
(paren
id|pd
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
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: don&squot;t know how to wake %s&bslash;n&quot;
comma
id|port-&gt;name
comma
id|pd-&gt;name
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Nobody was waiting, so walk the list to see if anyone is&n;&t;   interested in being woken up.  */
r_for
c_loop
(paren
id|pd
op_assign
id|port-&gt;devices
suffix:semicolon
(paren
id|port-&gt;cad
op_eq
l_int|NULL
)paren
op_logical_and
id|pd
suffix:semicolon
id|pd
op_assign
id|pd-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|pd-&gt;wakeup
op_logical_and
id|pd
op_ne
id|dev
)paren
id|pd
op_member_access_from_pointer
id|wakeup
c_func
(paren
id|pd
op_member_access_from_pointer
r_private
)paren
suffix:semicolon
)brace
)brace
DECL|function|parport_parse_params
r_static
r_int
id|parport_parse_params
(paren
r_int
id|nports
comma
r_const
r_char
op_star
id|str
(braket
)braket
comma
r_int
id|val
(braket
)braket
comma
r_int
id|automatic
comma
r_int
id|none
)paren
(brace
r_int
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
id|nports
op_logical_and
id|str
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
(braket
id|i
)braket
comma
l_string|&quot;auto&quot;
comma
l_int|4
)paren
)paren
id|val
(braket
id|i
)braket
op_assign
id|automatic
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
(braket
id|i
)braket
comma
l_string|&quot;none&quot;
comma
l_int|4
)paren
)paren
id|val
(braket
id|i
)braket
op_assign
id|none
suffix:semicolon
r_else
(brace
r_char
op_star
id|ep
suffix:semicolon
r_int
r_int
id|r
op_assign
id|simple_strtoul
c_func
(paren
id|str
(braket
id|i
)braket
comma
op_amp
id|ep
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ep
op_ne
id|str
(braket
id|i
)braket
)paren
id|val
(braket
id|i
)braket
op_assign
id|r
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;parport: bad specifier `%s&squot;&bslash;n&quot;
comma
id|str
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parport_parse_irqs
r_int
id|parport_parse_irqs
c_func
(paren
r_int
id|nports
comma
r_const
r_char
op_star
id|irqstr
(braket
)braket
comma
r_int
id|irqval
(braket
)braket
)paren
(brace
r_return
id|parport_parse_params
(paren
id|nports
comma
id|irqstr
comma
id|irqval
comma
id|PARPORT_IRQ_AUTO
comma
id|PARPORT_IRQ_NONE
)paren
suffix:semicolon
)brace
DECL|function|parport_parse_dmas
r_int
id|parport_parse_dmas
c_func
(paren
r_int
id|nports
comma
r_const
r_char
op_star
id|dmastr
(braket
)braket
comma
r_int
id|dmaval
(braket
)braket
)paren
(brace
r_return
id|parport_parse_params
(paren
id|nports
comma
id|dmastr
comma
id|dmaval
comma
id|PARPORT_DMA_AUTO
comma
id|PARPORT_DMA_NONE
)paren
suffix:semicolon
)brace
eof
