multiline_comment|/*======================================================================&n;&n;    A PCMCIA token-ring driver for IBM-based cards&n;&n;    This driver supports the IBM PCMCIA Token-Ring Card.&n;    Written by Steve Kipisz, kipisz@vnet.ibm.com or&n;                             bungy@ibm.net&n;&n;    Written 1995,1996.&n;&n;    This code is based on pcnet_cs.c from David Hinds.&n;    &n;    V2.2.0 February 1999 - Mike Phillips phillim@amtrak.com&n;&n;    Linux V2.2.x presented significant changes to the underlying&n;    ibmtr.c code.  Mainly the code became a lot more organized and&n;    modular.&n;&n;    This caused the old PCMCIA Token Ring driver to give up and go &n;    home early. Instead of just patching the old code to make it &n;    work, the PCMCIA code has been streamlined, updated and possibly&n;    improved.&n;&n;    This code now only contains code required for the Card Services.&n;    All we do here is set the card up enough so that the real ibmtr.c&n;    driver can find it and work with it properly.&n;&n;    i.e. We set up the io port, irq, mmio memory and shared ram memory.&n;    This enables ibmtr_probe in ibmtr.c to find the card and configure it&n;    as though it was a normal ISA and/or PnP card.&n;&n;    There is some confusion with the difference between available shared&n;    ram and the amount actually reserved from memory.  ibmtr.c sets up&n;    several offsets depending upon the actual on-board memory, not the&n;    reserved memory.  We need to get around this to allow the cards to &n;    work with other cards in restricted memory space.  Therefore the &n;    pcmcia_reality_check function.&n;&n;    TODO&n;&t;- Write the suspend / resume functions. &n;&t;- Fix Kernel Oops when removing card before ifconfig down&n;&n;    CHANGES&n;&n;    v2.2.5 April 1999 Mike Phillips (phillim@amtrak.com)&n;    Obscure bug fix, required changed to ibmtr.c not ibmtr_cs.c&n;    &n;    v2.2.7 May 1999 Mike Phillips (phillim@amtrak.com)&n;    Updated to version 2.2.7 to match the first version of the kernel&n;    that the modification to ibmtr.c were incorporated into.&n;    &n;======================================================================*/
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/trdevice.h&gt;
macro_line|#include &lt;linux/ibmtr.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
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
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) if (pc_debug&gt;(n)) printk(KERN_DEBUG args)
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;ibmtr_cs.c 1.10 1996/01/06 05:19:00 (Steve Kipisz)&bslash;n&quot;
l_string|&quot;           2.2.7 1999/05/03 12:00:00 (Mike Phillips)&bslash;n&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...)
macro_line|#endif
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/* Bit map of interrupts to choose from */
DECL|variable|irq_mask
r_static
id|u_int
id|irq_mask
op_assign
l_int|0xdeb8
suffix:semicolon
DECL|variable|irq_list
r_static
r_int
id|irq_list
(braket
l_int|4
)braket
op_assign
(brace
op_minus
l_int|1
)brace
suffix:semicolon
multiline_comment|/* MMIO base address */
DECL|variable|mmiobase
r_static
id|u_long
id|mmiobase
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* SRAM base address */
DECL|variable|srambase
r_static
id|u_long
id|srambase
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* SRAM size 8,16,32,64 */
DECL|variable|sramsize
r_static
id|u_long
id|sramsize
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* Ringspeed 4,16 */
DECL|variable|ringspeed
r_static
r_int
id|ringspeed
op_assign
l_int|16
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq_mask
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq_list
comma
l_string|&quot;1-4i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mmiobase
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|srambase
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|sramsize
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|ringspeed
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
r_static
r_void
id|ibmtr_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|ibmtr_hw_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|ibmtr_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|ibmtr_event
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
DECL|variable|dev_info
r_static
id|dev_info_t
id|dev_info
op_assign
l_string|&quot;ibmtr_cs&quot;
suffix:semicolon
r_static
id|dev_link_t
op_star
id|ibmtr_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|ibmtr_detach
c_func
(paren
id|dev_link_t
op_star
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
r_extern
r_int
id|ibmtr_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
r_char
id|pcmcia_reality_check
c_func
(paren
r_int
r_char
id|gss
)paren
suffix:semicolon
r_extern
r_int
id|trdev_init
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|tok_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|tok_init_card
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
r_char
id|get_sram_size
c_func
(paren
r_struct
id|tok_info
op_star
id|ti
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
DECL|struct|ibmtr_dev_t
r_typedef
r_struct
id|ibmtr_dev_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|dev
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Changed for 2.2.0 */
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|sram_win_handle
id|window_handle_t
id|sram_win_handle
suffix:semicolon
DECL|member|ti
r_struct
id|tok_info
id|ti
suffix:semicolon
DECL|typedef|ibmtr_dev_t
)brace
id|ibmtr_dev_t
suffix:semicolon
multiline_comment|/*======================================================================&n;&n;    This bit of code is used to avoid unregistering network devices&n;    at inappropriate times.  2.2 and later kernels are fairly picky&n;    about when this can happen.&n;    &n;======================================================================*/
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
id|ibmtr_detach
c_func
(paren
id|link
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*====================================================================*/
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
)brace
multiline_comment|/*======================================================================&n;&n;    ibmtr_attach() creates an &quot;instance&quot; of the driver, allocating&n;    local data structures for one device.  The device is registered&n;    with Card Services.&n;&n;======================================================================*/
DECL|function|ibmtr_attach
r_static
id|dev_link_t
op_star
id|ibmtr_attach
c_func
(paren
r_void
)paren
(brace
id|ibmtr_dev_t
op_star
id|info
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|client_reg_t
id|client_reg
suffix:semicolon
r_int
id|i
comma
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ibmtr_attach()&bslash;n&quot;
)paren
suffix:semicolon
id|flush_stale_links
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Create new token-ring device */
id|info
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|info
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|info
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|info
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|info
)paren
)paren
suffix:semicolon
id|link
op_assign
op_amp
id|info-&gt;link
suffix:semicolon
id|link-&gt;priv
op_assign
id|info
suffix:semicolon
id|link-&gt;release.function
op_assign
op_amp
id|ibmtr_release
suffix:semicolon
id|link-&gt;release.data
op_assign
(paren
id|u_long
)paren
id|link
suffix:semicolon
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.NumPorts1
op_assign
l_int|4
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|16
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
op_or
id|IRQ_HANDLE_PRESENT
suffix:semicolon
id|link-&gt;irq.IRQInfo1
op_assign
id|IRQ_INFO2_VALID
op_or
id|IRQ_LEVEL_ID
suffix:semicolon
r_if
c_cond
(paren
id|irq_list
(braket
l_int|0
)braket
op_eq
op_minus
l_int|1
)paren
id|link-&gt;irq.IRQInfo2
op_assign
id|irq_mask
suffix:semicolon
r_else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|link-&gt;irq.IRQInfo2
op_or_assign
l_int|1
op_lshift
id|irq_list
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;irq.Handler
op_assign
op_amp
id|tok_interrupt
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
id|link-&gt;conf.Present
op_assign
id|PRESENT_OPTION
suffix:semicolon
id|dev
op_assign
id|init_trdev
c_func
(paren
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
op_amp
id|info-&gt;ti
suffix:semicolon
id|link-&gt;irq.Instance
op_assign
id|info-&gt;dev
op_assign
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|ibmtr_detach
c_func
(paren
id|link
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|dev-&gt;init
op_assign
op_amp
id|ibmtr_probe
suffix:semicolon
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
id|ibmtr_event
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
id|ibmtr_detach
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
multiline_comment|/* ibmtr_attach */
multiline_comment|/*======================================================================&n;&n;    This deletes a driver &quot;instance&quot;.  The device is de-registered&n;    with Card Services.  If it has been released, all local data&n;    structures are freed.  Otherwise, the structures will be freed&n;    when the device is released.&n;&n;======================================================================*/
DECL|function|ibmtr_detach
r_static
r_void
id|ibmtr_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
r_struct
id|ibmtr_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ibmtr_detach(0x%p)&bslash;n&quot;
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
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
(brace
r_struct
id|tok_info
op_star
id|ti
op_assign
(paren
r_struct
id|tok_info
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
(paren
id|ti-&gt;tr_timer
)paren
)paren
suffix:semicolon
)brace
id|del_timer
c_func
(paren
op_amp
id|link-&gt;release
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
id|ibmtr_release
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
r_if
c_cond
(paren
id|link-&gt;dev
)paren
id|unregister_trdev
c_func
(paren
id|info-&gt;dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|info
)paren
suffix:semicolon
)brace
multiline_comment|/* ibmtr_detach */
multiline_comment|/*======================================================================&n;&n;    ibmtr_config() is scheduled to run after a CARD_INSERTION event&n;    is received, to configure the PCMCIA socket, and to make the&n;    token-ring device available to the system.&n;&n;======================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|function|ibmtr_config
r_static
r_void
id|ibmtr_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|client_handle_t
id|handle
op_assign
id|link-&gt;handle
suffix:semicolon
id|ibmtr_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
r_struct
id|tok_info
op_star
id|ti
op_assign
id|dev-&gt;priv
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|win_req_t
id|req
suffix:semicolon
id|memreq_t
id|mem
suffix:semicolon
r_int
id|i
comma
id|last_ret
comma
id|last_fn
suffix:semicolon
id|u_char
id|buf
(braket
l_int|64
)braket
suffix:semicolon
r_int
r_char
id|Shared_Ram_Base
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ibmtr_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleData
op_assign
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
multiline_comment|/* Configure card */
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
id|link-&gt;conf.ConfigIndex
op_assign
l_int|0x61
suffix:semicolon
multiline_comment|/* Determine if this is PRIMARY or ALTERNATE. */
multiline_comment|/* Try PRIMARY card at 0xA20-0xA23 */
id|link-&gt;io.BasePort1
op_assign
l_int|0xA20
suffix:semicolon
id|i
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
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|CS_SUCCESS
)paren
(brace
id|memcpy
c_func
(paren
id|info-&gt;node.dev_name
comma
l_string|&quot;tr0&bslash;0&quot;
comma
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Couldn&squot;t get 0xA20-0xA23.  Try ALTERNATE at 0xA24-0xA27. */
id|link-&gt;io.BasePort1
op_assign
l_int|0xA24
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestIO
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;io
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|info-&gt;node.dev_name
comma
l_string|&quot;tr1&bslash;0&quot;
comma
l_int|4
)paren
suffix:semicolon
)brace
id|dev-&gt;base_addr
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|link-&gt;handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|dev-&gt;irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|ti-&gt;irq
op_assign
id|link-&gt;irq.AssignedIRQ
suffix:semicolon
id|ti-&gt;global_int_enable
op_assign
id|GLOBAL_INT_ENABLE
op_plus
(paren
(paren
id|dev-&gt;irq
op_eq
l_int|9
)paren
ques
c_cond
l_int|2
suffix:colon
id|dev-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Allocate the MMIO memory window */
id|req.Attributes
op_assign
id|WIN_DATA_WIDTH_16
op_or
id|WIN_MEMORY_TYPE_CM
op_or
id|WIN_ENABLE
suffix:semicolon
id|req.Attributes
op_or_assign
id|WIN_USE_WAIT
op_or
id|WIN_STRICT_ALIGN
suffix:semicolon
id|req.Base
op_assign
id|mmiobase
suffix:semicolon
id|req.Size
op_assign
l_int|0x2000
suffix:semicolon
id|req.AccessSpeed
op_assign
l_int|250
suffix:semicolon
id|link-&gt;win
op_assign
(paren
id|window_handle_t
)paren
id|link-&gt;handle
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestWindow
comma
op_amp
id|link-&gt;win
comma
op_amp
id|req
)paren
suffix:semicolon
id|mem.CardOffset
op_assign
id|req.Base
suffix:semicolon
id|mem.Page
op_assign
l_int|0
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|MapMemPage
comma
id|link-&gt;win
comma
op_amp
id|mem
)paren
suffix:semicolon
id|ti-&gt;mmio
op_assign
(paren
id|u_long
)paren
id|ioremap
c_func
(paren
id|req.Base
comma
id|req.Size
)paren
suffix:semicolon
multiline_comment|/* Allocate the SRAM memory window */
id|req.Attributes
op_assign
id|WIN_DATA_WIDTH_16
op_or
id|WIN_MEMORY_TYPE_CM
op_or
id|WIN_ENABLE
suffix:semicolon
id|req.Attributes
op_or_assign
id|WIN_USE_WAIT
op_or
id|WIN_MAP_BELOW_1MB
suffix:semicolon
id|req.Base
op_assign
id|srambase
suffix:semicolon
id|req.Size
op_assign
id|sramsize
op_star
l_int|1024
suffix:semicolon
id|req.AccessSpeed
op_assign
l_int|250
suffix:semicolon
id|info-&gt;sram_win_handle
op_assign
(paren
id|window_handle_t
)paren
id|link-&gt;handle
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestWindow
comma
op_amp
id|info-&gt;sram_win_handle
comma
op_amp
id|req
)paren
suffix:semicolon
id|mem.CardOffset
op_assign
id|req.Base
suffix:semicolon
id|mem.Page
op_assign
l_int|0
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|MapMemPage
comma
id|info-&gt;sram_win_handle
comma
op_amp
id|mem
)paren
suffix:semicolon
id|Shared_Ram_Base
op_assign
id|req.Base
op_rshift
l_int|12
suffix:semicolon
id|ti-&gt;sram
op_assign
l_int|0
suffix:semicolon
id|ti-&gt;sram_base
op_assign
id|Shared_Ram_Base
suffix:semicolon
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
multiline_comment|/*  Set up the Token-Ring Controller Configuration Register and&n;        turn on the card.  Check the &quot;Local Area Network Credit Card&n;        Adapters Technical Reference&quot;  SC30-3585 for this info.  */
id|ibmtr_hw_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|i
op_assign
id|register_trdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ibmtr_cs: register_trdev() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: port %#3lx, irq %d,&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; mmio %#5lx,&quot;
comma
(paren
id|u_long
)paren
id|ti-&gt;mmio
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot; sram %#5lx,&quot;
comma
(paren
id|u_long
)paren
id|ti-&gt;sram_base
op_lshift
l_int|12
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;&bslash;n&quot;
id|KERN_INFO
l_string|&quot;  hwaddr=&quot;
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
id|TR_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;%02X&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
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
id|failed
suffix:colon
id|ibmtr_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* ibmtr_config */
multiline_comment|/*======================================================================&n;&n;    After a card is removed, ibmtr_release() will unregister the net&n;    device, and release the PCMCIA configuration.  If the device is&n;    still open, this will be postponed until it is closed.&n;&n;======================================================================*/
DECL|function|ibmtr_release
r_static
r_void
id|ibmtr_release
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
id|ibmtr_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ibmtr_release(0x%p)&bslash;n&quot;
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
l_string|&quot;ibmtr_cs: release postponed, &squot;%s&squot; &quot;
l_string|&quot;still open&bslash;n&quot;
comma
id|info-&gt;node.dev_name
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
r_if
c_cond
(paren
id|link-&gt;win
)paren
(brace
r_struct
id|tok_info
op_star
id|ti
op_assign
id|dev-&gt;priv
suffix:semicolon
id|iounmap
c_func
(paren
(paren
r_void
op_star
)paren
id|ti-&gt;mmio
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
id|CardServices
c_func
(paren
id|ReleaseWindow
comma
id|info-&gt;sram_win_handle
)paren
suffix:semicolon
)brace
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
multiline_comment|/* ibmtr_release */
multiline_comment|/*======================================================================&n;&n;    The card status event handler.  Mostly, this schedules other&n;    stuff to run after an event is received.  A CARD_REMOVAL event&n;    also sets some flags to discourage the net drivers from trying&n;    to talk to the card any more.&n;&n;======================================================================*/
DECL|function|ibmtr_event
r_static
r_int
id|ibmtr_event
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
id|ibmtr_dev_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
id|info-&gt;dev
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;ibmtr_event(0x%06x)&bslash;n&quot;
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
id|mod_timer
c_func
(paren
op_amp
id|link-&gt;release
comma
id|jiffies
op_plus
id|HZ
op_div
l_int|20
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
suffix:semicolon
id|ibmtr_config
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
(paren
id|dev-&gt;init
)paren
(paren
id|dev
)paren
suffix:semicolon
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
multiline_comment|/* ibmtr_event */
multiline_comment|/*====================================================================*/
DECL|function|ibmtr_hw_setup
r_static
r_void
id|ibmtr_hw_setup
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|tok_info
op_star
id|ti
op_assign
id|dev-&gt;priv
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Bizarre IBM behavior, there are 16 bits of information we&n;       need to set, but the card only allows us to send 4 bits at a &n;       time.  For each byte sent to base_addr, bits 7-4 tell the&n;       card which part of the 16 bits we are setting, bits 3-0 contain &n;       the actual information */
multiline_comment|/* First nibble provides 4 bits of mmio */
id|i
op_assign
(paren
(paren
r_int
)paren
id|ti-&gt;mmio
op_rshift
l_int|16
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|outb
c_func
(paren
id|i
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* Second nibble provides 3 bits of mmio */
id|i
op_assign
l_int|0x10
op_or
(paren
(paren
(paren
r_int
)paren
id|ti-&gt;mmio
op_rshift
l_int|12
)paren
op_amp
l_int|0x0E
)paren
suffix:semicolon
id|outb
c_func
(paren
id|i
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* Third nibble, hard-coded values */
id|i
op_assign
l_int|0x26
suffix:semicolon
id|outb
c_func
(paren
id|i
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* Fourth nibble sets shared ram page size */
multiline_comment|/* 8 = 00, 16 = 01, 32 = 10, 64 = 11 */
id|i
op_assign
(paren
id|sramsize
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
suffix:semicolon
id|i
op_assign
(paren
(paren
id|i
op_eq
l_int|4
)paren
ques
c_cond
l_int|3
suffix:colon
id|i
)paren
op_lshift
l_int|2
suffix:semicolon
id|i
op_or_assign
l_int|0x30
suffix:semicolon
r_if
c_cond
(paren
id|ringspeed
op_eq
l_int|16
)paren
id|i
op_or_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;base_addr
op_eq
l_int|0xA24
)paren
id|i
op_or_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|i
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
multiline_comment|/* X40 will release the card for use */
id|outb
c_func
(paren
l_int|0x40
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*======================================================================&n;  &n;    A sweet little function that circumvents the problem with&n;    ibmtr.c trying to use more memory than we can allocate for&n;    the PCMCIA card.  ibmtr.c just assumes that if a card has &n;    64K of shared ram, the entire 64K must be mapped into memory,&n;    whereas resources are sometimes a little tight in card services&n;    so we fool ibmtr.c into thinking the card has less memory on&n;    it than it has.&n;    &n;======================================================================*/
DECL|function|pcmcia_reality_check
r_int
r_char
id|pcmcia_reality_check
c_func
(paren
r_int
r_char
id|gss
)paren
(brace
r_return
(paren
id|gss
OL
id|sramsize
)paren
ques
c_cond
id|sramsize
suffix:colon
id|gss
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|init_ibmtr_cs
r_static
r_int
id|__init
id|init_ibmtr_cs
c_func
(paren
r_void
)paren
(brace
id|servinfo_t
id|serv
suffix:semicolon
id|DEBUG
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
l_string|&quot;ibmtr_cs: Card Services release &quot;
l_string|&quot;does not match!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|register_pccard_driver
c_func
(paren
op_amp
id|dev_info
comma
op_amp
id|ibmtr_attach
comma
op_amp
id|ibmtr_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_ibmtr_cs
r_static
r_void
id|__exit
id|exit_ibmtr_cs
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
l_string|&quot;ibmtr_cs: unloading&bslash;n&quot;
)paren
suffix:semicolon
id|unregister_pccard_driver
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
id|ibmtr_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_ibmtr_cs
id|module_init
c_func
(paren
id|init_ibmtr_cs
)paren
suffix:semicolon
DECL|variable|exit_ibmtr_cs
id|module_exit
c_func
(paren
id|exit_ibmtr_cs
)paren
suffix:semicolon
eof
