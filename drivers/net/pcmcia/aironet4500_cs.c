multiline_comment|/*&n; *&t; Aironet 4500 Pcmcia driver&n; *&n; *&t;&t;Elmer Joandi, Januar 1999&n; *&t;Copyright Elmer Joandi, all rights restricted&n; *&t;&n; *&n; *&t;Revision 0.1 ,started  30.12.1998&n; *&n; *&n; */
DECL|variable|awc_version
r_static
r_const
r_char
op_star
id|awc_version
op_assign
l_string|&quot;aironet4500_cs.c v0.1 1/1/99 Elmer Joandi, elmer@ylenurme.ee.&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &lt;pcmcia/ciscode.h&gt;
macro_line|#if LINUX_VERSION_CODE &lt; 0x20300
macro_line|#ifdef MODULE
macro_line|#include &lt;pcmcia/k_compat.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &quot;../aironet4500.h&quot;
DECL|variable|irq_mask
r_static
id|u_int
id|irq_mask
op_assign
l_int|0x5eF8
suffix:semicolon
DECL|variable|awc_ports
r_static
r_int
id|awc_ports
(braket
)braket
op_assign
(brace
l_int|0x140
comma
l_int|0x100
comma
l_int|0xc0
comma
l_int|0x80
)brace
suffix:semicolon
macro_line|#if LINUX_VERSION_CODE &gt; 0x20100
id|MODULE_PARM
c_func
(paren
id|irq_mask
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|macro|RUN_AT
mdefine_line|#define RUN_AT(x)               (jiffies+(x))
macro_line|#ifdef PCMCIA_DEBUG
DECL|variable|pc_debug
r_static
r_int
id|pc_debug
op_assign
id|PCMCIA_DEBUG
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|pc_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|macro|PC_DEBUG
mdefine_line|#define PC_DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args)
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;aironet4500_cs.c v0.1 1/1/99 Elmer Joandi, elmer@ylenurme.ee.&bslash;n&quot;
suffix:semicolon
macro_line|#else
DECL|macro|PC_DEBUG
mdefine_line|#define PC_DEBUG(n, args...)
macro_line|#endif
multiline_comment|/* Index of functions. */
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;aironet4500_cs&quot;
suffix:semicolon
r_static
id|dev_link_t
op_star
id|awc_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|awc_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
r_static
r_void
id|awc_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|awc_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
suffix:semicolon
DECL|variable|dev_list
r_static
id|dev_link_t
op_star
id|dev_list
op_assign
l_int|NULL
suffix:semicolon
DECL|function|cs_error
r_static
r_void
id|cs_error
c_func
(paren
id|client_handle_t
id|handle
comma
r_int
id|func
comma
r_int
id|ret
)paren
(brace
macro_line|#if CS_RELEASE_CODE &lt; 0x2911
id|CardServices
c_func
(paren
id|ReportError
comma
id|dev_info
comma
(paren
r_void
op_star
)paren
id|func
comma
(paren
r_void
op_star
)paren
id|ret
)paren
suffix:semicolon
macro_line|#else
id|error_info_t
id|err
op_assign
(brace
id|func
comma
id|ret
)brace
suffix:semicolon
id|CardServices
c_func
(paren
id|ReportError
comma
id|handle
comma
op_amp
id|err
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|CFG_CHECK
mdefine_line|#define CFG_CHECK(fn, args...) if (CardServices(fn, args) != 0) goto next_entry
DECL|function|flush_stale_links
r_static
r_void
id|flush_stale_links
c_func
(paren
r_void
)paren
(brace
id|dev_link_t
op_star
id|link
comma
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
id|link
op_assign
id|dev_list
suffix:semicolon
id|link
suffix:semicolon
id|link
op_assign
id|next
)paren
(brace
id|next
op_assign
id|link-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_LINK
)paren
id|awc_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   We never need to do anything when a awc device is &quot;initialized&quot;&n;   by the net software, because we only register already-found cards.&n;*/
DECL|function|awc_pcmcia_init
r_static
r_int
id|awc_pcmcia_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_return
id|awc_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|awc_pcmcia_open
r_static
r_int
id|awc_pcmcia_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|status
suffix:semicolon
r_for
c_loop
(paren
id|link
op_assign
id|dev_list
suffix:semicolon
id|link
suffix:semicolon
id|link
op_assign
id|link-&gt;next
)paren
r_if
c_cond
(paren
id|link-&gt;priv
op_eq
id|dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|DEV_OK
c_func
(paren
id|link
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|status
op_assign
id|awc_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|status
)paren
id|link-&gt;open
op_increment
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|awc_pcmcia_close
r_static
r_int
id|awc_pcmcia_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
singleline_comment|//&t;int ioaddr = dev-&gt;base_addr;
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_for
c_loop
(paren
id|link
op_assign
id|dev_list
suffix:semicolon
id|link
suffix:semicolon
id|link
op_assign
id|link-&gt;next
)paren
r_if
c_cond
(paren
id|link-&gt;priv
op_eq
id|dev
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|link
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|PC_DEBUG
c_func
(paren
l_int|2
comma
l_string|&quot;%s: closing device.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|link-&gt;open
op_decrement
suffix:semicolon
id|ret
op_assign
id|awc_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_CONFIG
)paren
(brace
id|link-&gt;release.expires
op_assign
id|RUN_AT
c_func
(paren
id|HZ
op_div
l_int|20
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_RELEASE_PENDING
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|link-&gt;release
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n;&t;awc_attach() creates an &quot;instance&quot; of the driver, allocating&n;&t;local data structures for one device.  The device is registered&n;&t;with Card Services.&n;*/
DECL|function|awc_attach
r_static
id|dev_link_t
op_star
id|awc_attach
c_func
(paren
r_void
)paren
(brace
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|PC_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;awc_attach()&bslash;n&quot;
)paren
suffix:semicolon
id|flush_stale_links
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Create the PC card device object. */
id|link
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|link
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|dev_node_t
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|link-&gt;dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dev_node_t
)paren
)paren
suffix:semicolon
id|link-&gt;release.function
op_assign
op_amp
id|awc_release
suffix:semicolon
id|link-&gt;release.data
op_assign
(paren
id|u_long
)paren
id|link
suffix:semicolon
singleline_comment|//&t;link-&gt;io.NumPorts1 = 32;
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_16
suffix:semicolon
singleline_comment|//&t;link-&gt;io.IOAddrLines = 5;
id|link-&gt;irq.Attributes
op_assign
id|IRQ_HANDLE_PRESENT
suffix:semicolon
singleline_comment|// |IRQ_TYPE_EXCLUSIVE  ;
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
suffix:semicolon
id|link-&gt;irq.IRQInfo2
op_assign
id|irq_mask
suffix:semicolon
id|link-&gt;irq.Handler
op_assign
op_amp
id|awc_interrupt
suffix:semicolon
id|link-&gt;conf.Attributes
op_assign
id|CONF_ENABLE_IRQ
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|50
suffix:semicolon
id|link-&gt;conf.IntType
op_assign
id|INT_MEMORY_AND_IO
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
l_int|1
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|PRESENT_OPTION
suffix:semicolon
multiline_comment|/* Create the network device object. */
id|dev
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_device
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|memset
c_func
(paren
id|dev
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
singleline_comment|//&t;dev =  init_etherdev(0, sizeof(struct awc_private) );
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
id|KERN_CRIT
l_string|&quot;out of mem on dev alloc &bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|awc_private
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;priv
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;out of mem on dev priv alloc &bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|awc_private
)paren
)paren
suffix:semicolon
singleline_comment|//&t;link-&gt;dev-&gt;minor = dev-&gt;minor;
singleline_comment|//&t;link-&gt;dev-&gt;major = dev-&gt;major;
multiline_comment|/* The 4500-specific entries in the device structure. */
singleline_comment|//&t;dev-&gt;tx_queue_len = tx_queue_len;
id|dev-&gt;hard_start_xmit
op_assign
op_amp
id|awc_start_xmit
suffix:semicolon
singleline_comment|//&t;dev-&gt;set_config = &t;&t;&amp;awc_config_misiganes,aga mitte awc_config;
id|dev-&gt;get_stats
op_assign
op_amp
id|awc_get_stats
suffix:semicolon
singleline_comment|//&t;dev-&gt;set_multicast_list = &t;&amp;awc_set_multicast_list;
id|strcpy
c_func
(paren
id|dev-&gt;name
comma
(paren
(paren
r_struct
id|awc_private
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|node.dev_name
)paren
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;init
op_assign
op_amp
id|awc_pcmcia_init
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|awc_pcmcia_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|awc_pcmcia_close
suffix:semicolon
id|link-&gt;priv
op_assign
id|dev
suffix:semicolon
macro_line|#if CS_RELEASE_CODE &gt; 0x2911
id|link-&gt;irq.Instance
op_assign
id|dev
suffix:semicolon
macro_line|#endif
multiline_comment|/* Register with Card Services */
id|link-&gt;next
op_assign
id|dev_list
suffix:semicolon
id|dev_list
op_assign
id|link
suffix:semicolon
id|client_reg.dev_info
op_assign
op_amp
id|dev_info
suffix:semicolon
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|awc_event
suffix:semicolon
id|client_reg.Version
op_assign
l_int|0x0210
suffix:semicolon
id|client_reg.event_callback_args.client_data
op_assign
id|link
suffix:semicolon
id|ret
op_assign
id|CardServices
c_func
(paren
id|RegisterClient
comma
op_amp
id|link-&gt;handle
comma
op_amp
id|client_reg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|0
)paren
(brace
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|RegisterClient
comma
id|ret
)paren
suffix:semicolon
id|awc_detach
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|link
suffix:semicolon
)brace
multiline_comment|/* awc_attach */
multiline_comment|/*&n;&n;&t;This deletes a driver &quot;instance&quot;.  The device is de-registered&n;&t;with Card Services.  If it has been released, all local data&n;&t;structures are freed.  Otherwise, the structures will be freed&n;&t;when the device is released.&n;&n;*/
DECL|function|awc_detach
r_static
r_void
id|awc_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;awc_detach(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
multiline_comment|/* Locate device structure */
r_for
c_loop
(paren
id|linkp
op_assign
op_amp
id|dev_list
suffix:semicolon
op_star
id|linkp
suffix:semicolon
id|linkp
op_assign
op_amp
(paren
op_star
id|linkp
)paren
op_member_access_from_pointer
id|next
)paren
r_if
c_cond
(paren
op_star
id|linkp
op_eq
id|link
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_star
id|linkp
op_eq
l_int|NULL
)paren
r_return
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
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_RELEASE_PENDING
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|link-&gt;release
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_RELEASE_PENDING
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|awc_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_CONFIG
)paren
(brace
id|link-&gt;state
op_or_assign
id|DEV_STALE_LINK
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|link-&gt;handle
)paren
id|CardServices
c_func
(paren
id|DeregisterClient
comma
id|link-&gt;handle
)paren
suffix:semicolon
multiline_comment|/* Unlink device structure, free bits */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|i
OL
id|MAX_AWCS
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|aironet4500_devices
(braket
id|i
)braket
)paren
(brace
id|i
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|aironet4500_devices
(braket
id|i
)braket
op_eq
id|link-&gt;priv
)paren
(brace
r_if
c_cond
(paren
id|awc_proc_unset_fun
)paren
id|awc_proc_unset_fun
c_func
(paren
id|i
)paren
suffix:semicolon
id|aironet4500_devices
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;priv
)paren
(brace
singleline_comment|//struct net_device *dev = link-&gt;priv;
singleline_comment|// dam dam damn mif (dev-&gt;priv)
singleline_comment|//&t;kfree_s(dev-&gt;priv, sizeof(struct awc_private));
id|kfree_s
c_func
(paren
id|link-&gt;priv
comma
r_sizeof
(paren
r_struct
id|net_device
)paren
)paren
suffix:semicolon
)brace
id|kfree_s
c_func
(paren
id|link-&gt;dev
comma
r_sizeof
(paren
r_struct
id|dev_node_t
)paren
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|link
comma
r_sizeof
(paren
r_struct
id|dev_link_t
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* awc_detach */
multiline_comment|/*&n;&n;&t;awc_pcmcia_config() is scheduled to run after a CARD_INSERTION event&n;&t;is received, to configure the PCMCIA socket, and to make the&n;&t;ethernet device available to the system.&n;&n;*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|function|awc_pcmcia_config
r_static
r_void
id|awc_pcmcia_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|client_handle_t
id|handle
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|awc_private
op_star
id|lp
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
r_int
id|ii
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|u_short
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|last_fn
comma
id|last_ret
comma
id|i
op_assign
l_int|0
suffix:semicolon
singleline_comment|//&t;int ioaddr;
id|u16
op_star
id|phys_addr
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|phys_addr
op_assign
(paren
id|u16
op_star
)paren
id|dev-&gt;dev_addr
suffix:semicolon
id|PC_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;awc_pcmcia_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CONFIG
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|tuple.TupleData
op_assign
(paren
id|cisdata_t
op_star
)paren
id|buf
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|64
suffix:semicolon
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
id|link-&gt;conf.ConfigBase
op_assign
id|parse.config.base
suffix:semicolon
id|link-&gt;conf.Present
op_assign
id|parse.config.rmask
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|GetFirstTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|cistpl_cftable_entry_t
id|dflt
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cfg
op_assign
op_amp
(paren
id|parse.cftable_entry
)paren
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|GetTupleData
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
id|CFG_CHECK
c_func
(paren
id|ParseTuple
comma
id|handle
comma
op_amp
id|tuple
comma
op_amp
id|parse
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cfg-&gt;flags
op_amp
id|CISTPL_CFTABLE_DEFAULT
)paren
id|dflt
op_assign
op_star
id|cfg
suffix:semicolon
r_if
c_cond
(paren
id|cfg-&gt;index
op_eq
l_int|0
)paren
r_goto
id|next_entry
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
id|cfg-&gt;index
suffix:semicolon
multiline_comment|/* Use power settings for Vcc and Vpp if present */
multiline_comment|/*  Note that the CIS values need to be rescaled */
r_if
c_cond
(paren
id|cfg-&gt;vcc.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vcc
op_assign
id|cfg-&gt;vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dflt.vcc.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vcc
op_assign
id|dflt.vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
r_if
c_cond
(paren
id|cfg-&gt;vpp1.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vpp1
op_assign
id|link-&gt;conf.Vpp2
op_assign
id|cfg-&gt;vpp1.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dflt.vpp1.present
op_amp
(paren
l_int|1
op_lshift
id|CISTPL_POWER_VNOM
)paren
)paren
id|link-&gt;conf.Vpp1
op_assign
id|link-&gt;conf.Vpp2
op_assign
id|dflt.vpp1.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
suffix:semicolon
multiline_comment|/* Do we need to allocate an interrupt? */
r_if
c_cond
(paren
id|cfg-&gt;irq.IRQInfo1
op_logical_or
id|dflt.irq.IRQInfo1
)paren
id|link-&gt;conf.Attributes
op_or_assign
id|CONF_ENABLE_IRQ
suffix:semicolon
multiline_comment|/* IO window settings */
id|link-&gt;io.NumPorts1
op_assign
id|link-&gt;io.NumPorts2
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cfg-&gt;io.nwin
OG
l_int|0
)paren
op_logical_or
(paren
id|dflt.io.nwin
OG
l_int|0
)paren
)paren
(brace
id|cistpl_io_t
op_star
id|io
op_assign
(paren
id|cfg-&gt;io.nwin
)paren
ques
c_cond
op_amp
id|cfg-&gt;io
suffix:colon
op_amp
id|dflt.io
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|io-&gt;flags
op_amp
id|CISTPL_IO_8BIT
)paren
)paren
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_16
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|io-&gt;flags
op_amp
id|CISTPL_IO_16BIT
)paren
)paren
(brace
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;8-bit IO not supported on this aironet 4500 driver &bslash;n&quot;
)paren
suffix:semicolon
)brace
id|link-&gt;io.BasePort1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;nwin
OG
l_int|1
)paren
(brace
id|link-&gt;io.Attributes2
op_assign
id|link-&gt;io.Attributes1
suffix:semicolon
id|link-&gt;io.BasePort2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
id|io-&gt;win
(braket
l_int|1
)braket
dot
id|len
suffix:semicolon
)brace
)brace
id|ii
op_assign
l_int|0
suffix:semicolon
id|last_fn
op_assign
id|RequestIO
suffix:semicolon
r_while
c_loop
(paren
(paren
id|last_ret
op_assign
id|CardServices
c_func
(paren
id|RequestIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|ii
OG
l_int|4
)paren
r_goto
id|cs_failed
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|awc_ports
(braket
id|ii
)braket
suffix:semicolon
id|ii
op_increment
suffix:semicolon
)brace
suffix:semicolon
r_break
suffix:semicolon
id|next_entry
suffix:colon
r_if
c_cond
(paren
id|CardServices
c_func
(paren
id|GetNextTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;conf.Attributes
op_amp
id|CONF_ENABLE_IRQ
)paren
(brace
id|ii
op_assign
l_int|0
suffix:semicolon
id|last_fn
op_assign
id|RequestIRQ
suffix:semicolon
r_while
c_loop
(paren
(paren
id|last_ret
op_assign
id|CardServices
c_func
(paren
id|RequestIRQ
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
)paren
)paren
(brace
id|ii
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|irq_mask
op_amp
(paren
l_int|1
op_lshift
id|ii
)paren
)paren
op_logical_and
id|ii
OL
l_int|15
)paren
id|ii
op_increment
suffix:semicolon
id|link-&gt;irq.IRQInfo2
op_assign
l_int|1
op_lshift
id|ii
suffix:semicolon
r_if
c_cond
(paren
id|ii
OG
l_int|15
)paren
(brace
r_goto
id|cs_failed
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;trying irq %d , mask %x &bslash;n&quot;
comma
id|ii
comma
id|link-&gt;irq.IRQInfo2
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
id|CS_CHECK
c_func
(paren
id|RequestConfiguration
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|awc_private_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|retval
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;awc_cs: register_netdev() failed for dev %x retval %x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dev
comma
id|retval
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
r_if
c_cond
(paren
id|awc_pcmcia_init
c_func
(paren
id|dev
)paren
)paren
(brace
r_goto
id|failed
suffix:semicolon
)brace
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|aironet4500_devices
(braket
id|i
)braket
op_logical_and
id|i
OL
id|MAX_AWCS
op_minus
l_int|1
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aironet4500_devices
(braket
id|i
)braket
)paren
(brace
id|aironet4500_devices
(braket
id|i
)braket
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|awc_proc_set_fun
)paren
id|awc_proc_set_fun
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|awc_private
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;pcmcia config complete on port %x &bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
suffix:semicolon
id|cs_failed
suffix:colon
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|last_fn
comma
id|last_ret
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|failed
suffix:colon
id|awc_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* awc_pcmcia_config */
multiline_comment|/*&n;&t;After a card is removed, awc_release() will unregister the net&n;&t;device, and release the PCMCIA configuration.  If the device is&n;&t;still open, this will be postponed until it is closed.&n;&n;*/
DECL|function|awc_release
r_static
r_void
id|awc_release
c_func
(paren
id|u_long
id|arg
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
(paren
id|dev_link_t
op_star
)paren
id|arg
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;awc_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;open
)paren
(brace
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;awc_cs: release postponed, &squot;%s&squot; still open&bslash;n&quot;
comma
id|link-&gt;dev-&gt;dev_name
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_STALE_CONFIG
suffix:semicolon
r_return
suffix:semicolon
)brace
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseIRQ
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseWindow
comma
id|link-&gt;win
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;dev
)paren
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
singleline_comment|// link-&gt;dev = NULL;
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_STALE_LINK
)paren
id|awc_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* awc_release */
multiline_comment|/*&n;&n;&t;The card status event handler.  Mostly, this schedules other&n;&t;stuff to run after an event is received.  A CARD_REMOVAL event&n;&t;also sets some flags to discourage the net drivers from trying&n;&t;to talk to the card any more.&n;*/
DECL|function|awc_event
r_static
r_int
id|awc_event
c_func
(paren
id|event_t
id|event
comma
r_int
id|priority
comma
id|event_callback_args_t
op_star
id|args
)paren
(brace
id|dev_link_t
op_star
id|link
op_assign
id|args-&gt;client_data
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|PC_DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;awc_event(0x%06x)&bslash;n&quot;
comma
id|event
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|CS_EVENT_CARD_REMOVAL
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_PRESENT
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|link-&gt;release.expires
op_assign
id|RUN_AT
c_func
(paren
id|HZ
op_div
l_int|20
)paren
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|link-&gt;release
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CS_EVENT_CARD_INSERTION
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_PRESENT
op_or
id|DEV_CONFIG_PENDING
suffix:semicolon
id|awc_pcmcia_config
c_func
(paren
id|link
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_SUSPEND
suffix:colon
id|link-&gt;state
op_or_assign
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_RESET_PHYSICAL
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
r_if
c_cond
(paren
id|link-&gt;open
)paren
id|netif_device_detach
c_func
(paren
id|dev
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|CS_EVENT_PM_RESUME
suffix:colon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_SUSPEND
suffix:semicolon
multiline_comment|/* Fall through... */
r_case
id|CS_EVENT_CARD_RESET
suffix:colon
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
id|CardServices
c_func
(paren
id|RequestConfiguration
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;open
)paren
(brace
singleline_comment|// awc_reset(dev);
id|netif_device_attach
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* awc_event */
DECL|function|aironet_cs_init
r_static
r_int
id|aironet_cs_init
c_func
(paren
r_void
)paren
(brace
id|servinfo_t
id|serv
suffix:semicolon
multiline_comment|/* Always emit the version, before any failure. */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s&quot;
comma
id|awc_version
)paren
suffix:semicolon
id|PC_DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
id|CardServices
c_func
(paren
id|GetCardServicesInfo
comma
op_amp
id|serv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serv.Revision
op_ne
id|CS_RELEASE_CODE
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;awc_cs: Card Services release &quot;
l_string|&quot;does not match!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|register_pcmcia_driver
c_func
(paren
op_amp
id|dev_info
comma
op_amp
id|awc_attach
comma
op_amp
id|awc_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|aironet_cs_exit
r_static
r_void
id|aironet_cs_exit
c_func
(paren
r_void
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;awc_cs: unloading %c &quot;
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|unregister_pcmcia_driver
c_func
(paren
op_amp
id|dev_info
)paren
suffix:semicolon
r_while
c_loop
(paren
id|dev_list
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|dev_list-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|awc_release
c_func
(paren
(paren
id|u_long
)paren
id|dev_list
)paren
suffix:semicolon
id|awc_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
singleline_comment|//&t;while (dev_list != NULL)
singleline_comment|//&t;&t;awc_detach(dev_list);
)brace
DECL|variable|aironet_cs_init
id|module_init
c_func
(paren
id|aironet_cs_init
)paren
suffix:semicolon
DECL|variable|aironet_cs_init
id|module_exit
c_func
(paren
id|aironet_cs_init
)paren
suffix:semicolon
eof
