multiline_comment|/*&n; * USB hub driver.&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; * (C) Copyright 1999 Johannes Erdfelt&n; * (C) Copyright 1999 Gregory P. Smith&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
singleline_comment|//#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;hub.h&quot;
macro_line|#ifdef __alpha
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
r_extern
r_int
id|__kernel_thread
c_func
(paren
r_int
r_int
comma
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
)paren
suffix:semicolon
DECL|function|kernel_thread
r_static
r_inline
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
r_return
id|__kernel_thread
c_func
(paren
id|flags
op_or
id|CLONE_VM
comma
id|fn
comma
id|arg
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/* Wakes up khubd */
DECL|variable|hub_event_lock
r_static
id|spinlock_t
id|hub_event_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|hub_event_list
)paren
suffix:semicolon
multiline_comment|/* List of hubs needing servicing */
r_static
id|LIST_HEAD
c_func
(paren
id|hub_list
)paren
suffix:semicolon
multiline_comment|/* List containing all of the hubs (for cleanup) */
r_static
id|DECLARE_WAIT_QUEUE_HEAD
c_func
(paren
id|khubd_wait
)paren
suffix:semicolon
DECL|variable|khubd_pid
r_static
r_int
id|khubd_pid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* PID of khubd */
DECL|variable|khubd_running
r_static
r_int
id|khubd_running
op_assign
l_int|0
suffix:semicolon
DECL|function|usb_get_hub_descriptor
r_static
r_int
id|usb_get_hub_descriptor
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|data
comma
r_int
id|size
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_DESCRIPTOR
comma
id|USB_DIR_IN
op_or
id|USB_RT_HUB
comma
id|USB_DT_HUB
op_lshift
l_int|8
comma
l_int|0
comma
id|data
comma
id|size
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|usb_clear_port_feature
r_static
r_int
id|usb_clear_port_feature
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|port
comma
r_int
id|feature
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_CLEAR_FEATURE
comma
id|USB_RT_PORT
comma
id|feature
comma
id|port
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|usb_set_port_feature
r_static
r_int
id|usb_set_port_feature
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|port
comma
r_int
id|feature
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_sndctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_SET_FEATURE
comma
id|USB_RT_PORT
comma
id|feature
comma
id|port
comma
l_int|NULL
comma
l_int|0
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|usb_get_hub_status
r_static
r_int
id|usb_get_hub_status
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_STATUS
comma
id|USB_DIR_IN
op_or
id|USB_RT_HUB
comma
l_int|0
comma
l_int|0
comma
id|data
comma
r_sizeof
(paren
r_struct
id|usb_hub_status
)paren
comma
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|usb_get_port_status
r_static
r_int
id|usb_get_port_status
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
id|port
comma
r_void
op_star
id|data
)paren
(brace
r_return
id|usb_control_msg
c_func
(paren
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
id|USB_REQ_GET_STATUS
comma
id|USB_DIR_IN
op_or
id|USB_RT_PORT
comma
l_int|0
comma
id|port
comma
id|data
comma
r_sizeof
(paren
r_struct
id|usb_hub_status
)paren
comma
id|HZ
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A irq handler returns non-zero to indicate to&n; * the low-level driver that it wants to be re-activated,&n; * or zero to say &quot;I&squot;m done&quot;.&n; */
DECL|function|hub_irq
r_static
r_int
id|hub_irq
c_func
(paren
r_int
id|status
comma
r_void
op_star
id|__buffer
comma
r_int
id|len
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|usb_hub
op_star
id|hub
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
op_minus
id|ENODEV
suffix:colon
multiline_comment|/* Just ignore it */
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
multiline_comment|/* Something happened, let khubd figure it out */
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|khubd_wait
)paren
)paren
(brace
multiline_comment|/* Add the hub to the event queue */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hub-&gt;event_list.next
op_eq
op_amp
id|hub-&gt;event_list
)paren
(brace
id|list_add
c_func
(paren
op_amp
id|hub-&gt;event_list
comma
op_amp
id|hub_event_list
)paren
suffix:semicolon
multiline_comment|/* Wake up khubd */
id|wake_up
c_func
(paren
op_amp
id|khubd_wait
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|usb_hub_configure
r_static
r_int
id|usb_hub_configure
c_func
(paren
r_struct
id|usb_hub
op_star
id|hub
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|hub-&gt;dev
suffix:semicolon
r_int
r_char
id|buffer
(braket
l_int|4
)braket
comma
op_star
id|bitmap
suffix:semicolon
r_struct
id|usb_hub_descriptor
op_star
id|descriptor
suffix:semicolon
r_struct
id|usb_descriptor_header
op_star
id|header
suffix:semicolon
r_struct
id|usb_hub_status
op_star
id|hubsts
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Get the length first */
r_if
c_cond
(paren
id|usb_get_hub_descriptor
c_func
(paren
id|dev
comma
id|buffer
comma
l_int|4
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|header
op_assign
(paren
r_struct
id|usb_descriptor_header
op_star
)paren
id|buffer
suffix:semicolon
id|bitmap
op_assign
id|kmalloc
c_func
(paren
id|header-&gt;bLength
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bitmap
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|usb_get_hub_descriptor
c_func
(paren
id|dev
comma
id|bitmap
comma
id|header-&gt;bLength
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|descriptor
op_assign
(paren
r_struct
id|usb_hub_descriptor
op_star
)paren
id|bitmap
suffix:semicolon
id|hub-&gt;nports
op_assign
id|dev-&gt;maxchild
op_assign
id|descriptor-&gt;bNbrPorts
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: %d port%s detected&bslash;n&quot;
comma
id|hub-&gt;nports
comma
(paren
id|hub-&gt;nports
op_eq
l_int|1
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;s&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|descriptor-&gt;wHubCharacteristics
op_amp
id|HUB_CHAR_LPSM
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: ganged power switching&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: individual port power switching&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x02
suffix:colon
r_case
l_int|0x03
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: unknown reserved power switching mode&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|descriptor-&gt;wHubCharacteristics
op_amp
id|HUB_CHAR_COMPOUND
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: part of a compound device&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: standalone hub&bslash;n&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|descriptor-&gt;wHubCharacteristics
op_amp
id|HUB_CHAR_OCPM
)paren
(brace
r_case
l_int|0x00
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: global over-current protection&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: individual port over-current protection&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x10
suffix:colon
r_case
l_int|0x18
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: no over-current protection&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: power on to power good time: %dms&bslash;n&quot;
comma
id|descriptor-&gt;bPwrOn2PwrGood
op_star
l_int|2
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: hub controller current requirement: %dmA&bslash;n&quot;
comma
id|descriptor-&gt;bHubContrCurrent
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
id|dev-&gt;maxchild
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub:  port %d is%s removable&bslash;n&quot;
comma
id|i
op_plus
l_int|1
comma
id|bitmap
(braket
l_int|7
op_plus
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_div
l_int|8
)paren
)braket
op_amp
(paren
l_int|1
op_lshift
(paren
(paren
id|i
op_plus
l_int|1
)paren
op_mod
l_int|8
)paren
)paren
ques
c_cond
l_string|&quot; not&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|bitmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_get_hub_status
c_func
(paren
id|dev
comma
id|buffer
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|hubsts
op_assign
(paren
r_struct
id|usb_hub_status
op_star
)paren
id|buffer
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: local power source is %s&bslash;n&quot;
comma
(paren
id|le16_to_cpu
c_func
(paren
id|hubsts-&gt;wHubStatus
)paren
op_amp
id|HUB_STATUS_LOCAL_POWER
)paren
ques
c_cond
l_string|&quot;lost (inactive)&quot;
suffix:colon
l_string|&quot;good&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: %sover-current condition exists&bslash;n&quot;
comma
(paren
id|le16_to_cpu
c_func
(paren
id|hubsts-&gt;wHubStatus
)paren
op_amp
id|HUB_STATUS_OVERCURRENT
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
multiline_comment|/* Enable power to the ports */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: enabling power on all ports&bslash;n&quot;
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
id|hub-&gt;nports
suffix:semicolon
id|i
op_increment
)paren
id|usb_set_port_feature
c_func
(paren
id|dev
comma
id|i
op_plus
l_int|1
comma
id|USB_PORT_FEAT_POWER
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hub_probe
r_static
r_void
op_star
id|hub_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|i
)paren
(brace
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|usb_hub
op_star
id|hub
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|interface
op_assign
op_amp
id|dev-&gt;actconfig-&gt;interface
(braket
id|i
)braket
dot
id|altsetting
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Is it a hub? */
r_if
c_cond
(paren
id|interface-&gt;bInterfaceClass
op_ne
id|USB_CLASS_HUB
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Some hubs have a subclass of 1, which AFAICT according to the */
multiline_comment|/*  specs is not defined, but it works */
r_if
c_cond
(paren
(paren
id|interface-&gt;bInterfaceSubClass
op_ne
l_int|0
)paren
op_logical_and
(paren
id|interface-&gt;bInterfaceSubClass
op_ne
l_int|1
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Multiple endpoints? What kind of mutant ninja-hub is this? */
r_if
c_cond
(paren
id|interface-&gt;bNumEndpoints
op_ne
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
id|endpoint
op_assign
op_amp
id|interface-&gt;endpoint
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Output endpoint? Curiousier and curiousier.. */
r_if
c_cond
(paren
op_logical_neg
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
id|USB_DIR_IN
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* If it&squot;s not an interrupt endpoint, we&squot;d better punt! */
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* We found a hub */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;USB hub found&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|hub
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|hub
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t kmalloc hub struct&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hub
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|hub
)paren
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;event_list
)paren
suffix:semicolon
id|hub-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* Record the new hub&squot;s existence */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;hub_list
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|hub-&gt;hub_list
comma
op_amp
id|hub_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usb_hub_configure
c_func
(paren
id|hub
)paren
op_ge
l_int|0
)paren
(brace
id|hub-&gt;irqpipe
op_assign
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
suffix:semicolon
id|ret
op_assign
id|usb_request_irq
c_func
(paren
id|dev
comma
id|hub-&gt;irqpipe
comma
id|hub_irq
comma
id|endpoint-&gt;bInterval
comma
id|hub
comma
op_amp
id|hub-&gt;irq_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
(paren
id|KERN_WARNING
l_string|&quot;hub: usb_request_irq failed (%d)&bslash;n&quot;
comma
id|ret
)paren
suffix:semicolon
multiline_comment|/* free hub, but first clean up its list. */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Delete it and then reset it */
id|list_del
c_func
(paren
op_amp
id|hub-&gt;event_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;event_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hub-&gt;hub_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;hub_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|hub
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Wake up khubd */
id|wake_up
c_func
(paren
op_amp
id|khubd_wait
)paren
suffix:semicolon
)brace
r_return
id|hub
suffix:semicolon
)brace
DECL|function|hub_disconnect
r_static
r_void
id|hub_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|usb_hub
op_star
id|hub
op_assign
id|ptr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* Delete it and then reset it */
id|list_del
c_func
(paren
op_amp
id|hub-&gt;event_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;event_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hub-&gt;hub_list
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|hub-&gt;hub_list
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hub-&gt;irq_handle
)paren
(brace
id|usb_release_irq
c_func
(paren
id|hub-&gt;dev
comma
id|hub-&gt;irq_handle
comma
id|hub-&gt;irqpipe
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the memory */
id|kfree
c_func
(paren
id|hub
)paren
suffix:semicolon
)brace
DECL|function|usb_hub_port_connect_change
r_static
r_void
id|usb_hub_port_connect_change
c_func
(paren
r_struct
id|usb_device
op_star
id|hub
comma
r_int
id|port
)paren
(brace
r_struct
id|usb_device
op_star
id|usb
suffix:semicolon
r_struct
id|usb_port_status
id|portsts
suffix:semicolon
r_int
r_int
id|portstatus
comma
id|portchange
suffix:semicolon
multiline_comment|/* Check status */
r_if
c_cond
(paren
id|usb_get_port_status
c_func
(paren
id|hub
comma
id|port
op_plus
l_int|1
comma
op_amp
id|portsts
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;get_port_status failed&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|portstatus
op_assign
id|le16_to_cpu
c_func
(paren
id|portsts.wPortStatus
)paren
suffix:semicolon
id|portchange
op_assign
id|le16_to_cpu
c_func
(paren
id|portsts.wPortChange
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;hub.c: portstatus %x, change %x&bslash;n&quot;
comma
id|portstatus
comma
id|portchange
)paren
suffix:semicolon
multiline_comment|/* If it&squot;s not in CONNECT and ENABLE state, we&squot;re done */
r_if
c_cond
(paren
(paren
op_logical_neg
(paren
id|portstatus
op_amp
id|USB_PORT_STAT_CONNECTION
)paren
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|portstatus
op_amp
id|USB_PORT_STAT_ENABLE
)paren
)paren
)paren
(brace
multiline_comment|/* Disconnect anything that may have been there */
id|usb_disconnect
c_func
(paren
op_amp
id|hub-&gt;children
(braket
id|port
)braket
)paren
suffix:semicolon
multiline_comment|/* We&squot;re done now, we already disconnected the device */
r_return
suffix:semicolon
)brace
id|wait_ms
c_func
(paren
l_int|500
)paren
suffix:semicolon
multiline_comment|/* Reset the port */
id|usb_set_port_feature
c_func
(paren
id|hub
comma
id|port
op_plus
l_int|1
comma
id|USB_PORT_FEAT_RESET
)paren
suffix:semicolon
id|wait_ms
c_func
(paren
l_int|500
)paren
suffix:semicolon
multiline_comment|/* Allocate a new device struct for it */
id|usb
op_assign
id|usb_alloc_dev
c_func
(paren
id|hub
comma
id|hub-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|usb
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;couldn&squot;t allocate usb_device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|usb-&gt;slow
op_assign
(paren
id|portstatus
op_amp
id|USB_PORT_STAT_LOW_SPEED
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|hub-&gt;children
(braket
id|port
)braket
op_assign
id|usb
suffix:semicolon
multiline_comment|/* Find a new device ID for it */
id|usb_connect
c_func
(paren
id|usb
)paren
suffix:semicolon
multiline_comment|/* Run it through the hoops (find a driver, etc) */
r_if
c_cond
(paren
id|usb_new_device
c_func
(paren
id|usb
)paren
)paren
(brace
multiline_comment|/* Woops, disable the port */
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;hub: disabling port %d&bslash;n&quot;
comma
id|port
op_plus
l_int|1
)paren
suffix:semicolon
id|usb_clear_port_feature
c_func
(paren
id|hub
comma
id|port
op_plus
l_int|1
comma
id|USB_PORT_FEAT_ENABLE
)paren
suffix:semicolon
)brace
)brace
DECL|function|usb_hub_events
r_static
r_void
id|usb_hub_events
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|list_head
op_star
id|tmp
suffix:semicolon
r_struct
id|usb_device
op_star
id|dev
suffix:semicolon
r_struct
id|usb_hub
op_star
id|hub
suffix:semicolon
multiline_comment|/*&n;&t; *  We restart the list everytime to avoid a deadlock with&n;&t; * deleting hubs downstream from this one. This should be&n;&t; * safe since we delete the hub from the event list.&n;&t; * Not the most efficient, but avoids deadlocks.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_empty
c_func
(paren
op_amp
id|hub_event_list
)paren
)paren
r_goto
id|he_unlock
suffix:semicolon
multiline_comment|/* Grab the next entry from the beginning of the list */
id|tmp
op_assign
id|hub_event_list.next
suffix:semicolon
id|hub
op_assign
id|list_entry
c_func
(paren
id|tmp
comma
r_struct
id|usb_hub
comma
id|event_list
)paren
suffix:semicolon
id|dev
op_assign
id|hub-&gt;dev
suffix:semicolon
id|list_del
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
id|tmp
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
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
id|hub-&gt;nports
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|usb_port_status
id|portsts
suffix:semicolon
r_int
r_int
id|portstatus
comma
id|portchange
suffix:semicolon
r_if
c_cond
(paren
id|usb_get_port_status
c_func
(paren
id|dev
comma
id|i
op_plus
l_int|1
comma
op_amp
id|portsts
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;get_port_status failed&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|portstatus
op_assign
id|le16_to_cpu
c_func
(paren
id|portsts.wPortStatus
)paren
suffix:semicolon
id|portchange
op_assign
id|le16_to_cpu
c_func
(paren
id|portsts.wPortChange
)paren
suffix:semicolon
r_if
c_cond
(paren
id|portchange
op_amp
id|USB_PORT_STAT_C_CONNECTION
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: port %d connection change&bslash;n&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|usb_clear_port_feature
c_func
(paren
id|dev
comma
id|i
op_plus
l_int|1
comma
id|USB_PORT_FEAT_C_CONNECTION
)paren
suffix:semicolon
id|usb_hub_port_connect_change
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|portchange
op_amp
id|USB_PORT_STAT_C_ENABLE
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: port %d enable change&bslash;n&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|usb_clear_port_feature
c_func
(paren
id|dev
comma
id|i
op_plus
l_int|1
comma
id|USB_PORT_FEAT_C_ENABLE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|portchange
op_amp
id|USB_PORT_STAT_C_SUSPEND
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: port %d suspend change&bslash;n&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|portchange
op_amp
id|USB_PORT_STAT_C_OVERCURRENT
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: port %d over-current change&bslash;n&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|portchange
op_amp
id|USB_PORT_STAT_C_RESET
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;hub: port %d reset change&bslash;n&quot;
comma
id|i
op_plus
l_int|1
)paren
suffix:semicolon
id|usb_clear_port_feature
c_func
(paren
id|dev
comma
id|i
op_plus
l_int|1
comma
id|USB_PORT_FEAT_C_RESET
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* end for i */
)brace
multiline_comment|/* end while (1) */
id|he_unlock
suffix:colon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|hub_event_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|usb_hub_thread
r_static
r_int
id|usb_hub_thread
c_func
(paren
r_void
op_star
id|__hub
)paren
(brace
multiline_comment|/*&n;&t;MOD_INC_USE_COUNT;&n;*/
id|khubd_running
op_assign
l_int|1
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This thread doesn&squot;t need any user-level access,&n;&t; * so get rid of all our resources&n;&t; */
id|exit_mm
c_func
(paren
id|current
)paren
suffix:semicolon
id|exit_files
c_func
(paren
id|current
)paren
suffix:semicolon
id|exit_fs
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* Setup a nice name */
id|strcpy
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;khubd&quot;
)paren
suffix:semicolon
multiline_comment|/* Send me a signal to get me die (for debugging) */
r_do
(brace
id|usb_hub_events
c_func
(paren
)paren
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|khubd_wait
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;MOD_DEC_USE_COUNT;&n;*/
id|printk
c_func
(paren
l_string|&quot;usb_hub_thread exiting&bslash;n&quot;
)paren
suffix:semicolon
id|khubd_running
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hub_driver
r_static
r_struct
id|usb_driver
id|hub_driver
op_assign
(brace
l_string|&quot;hub&quot;
comma
id|hub_probe
comma
id|hub_disconnect
comma
(brace
l_int|NULL
comma
l_int|NULL
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * This should be a separate module.&n; */
DECL|function|usb_hub_init
r_int
id|usb_hub_init
c_func
(paren
r_void
)paren
(brace
r_int
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|usb_register
c_func
(paren
op_amp
id|hub_driver
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|usb_hub_thread
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGHAND
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ge
l_int|0
)paren
(brace
id|khubd_pid
op_assign
id|pid
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Fall through if kernel_thread failed */
id|usb_deregister
c_func
(paren
op_amp
id|hub_driver
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|usb_hub_cleanup
r_void
id|usb_hub_cleanup
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* Kill the thread */
id|ret
op_assign
id|kill_proc
c_func
(paren
id|khubd_pid
comma
id|SIGTERM
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
(brace
multiline_comment|/* Wait 10 seconds */
r_int
id|count
op_assign
l_int|10
op_star
l_int|100
suffix:semicolon
r_while
c_loop
(paren
id|khubd_running
op_logical_and
op_decrement
id|count
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;hub: giving up on killing khubd&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Hub resources are freed for us by usb_deregister.  It&n;&t; * usb_driver_purge on every device which in turn calls that&n;&t; * devices disconnect function if it is using this driver.&n;&t; * The hub_disconnect function takes care of releasing the&n;&t; * individual hub resources. -greg&n;&t; */
id|usb_deregister
c_func
(paren
op_amp
id|hub_driver
)paren
suffix:semicolon
)brace
multiline_comment|/* usb_hub_cleanup() */
eof
