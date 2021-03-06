multiline_comment|/*======================================================================&n;&n;    A driver for PCMCIA IDE/ATA disk cards&n;&n;    ide_cs.c 1.26 1999/11/16 02:10:49&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dhinds@pcmcia.sourceforge.org&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;pcmcia/version.h&gt;
macro_line|#include &lt;pcmcia/cs_types.h&gt;
macro_line|#include &lt;pcmcia/cs.h&gt;
macro_line|#include &lt;pcmcia/cistpl.h&gt;
macro_line|#include &lt;pcmcia/ds.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
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
l_string|&quot;ide_cs.c 1.26 1999/11/16 02:10:49 (David Hinds)&quot;
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
multiline_comment|/*====================================================================*/
DECL|variable|ide_major
r_static
r_const
r_char
id|ide_major
(braket
)braket
op_assign
(brace
id|IDE0_MAJOR
comma
id|IDE1_MAJOR
comma
id|IDE2_MAJOR
comma
id|IDE3_MAJOR
comma
macro_line|#ifdef IDE4_MAJOR
id|IDE4_MAJOR
comma
id|IDE5_MAJOR
macro_line|#endif
)brace
suffix:semicolon
DECL|struct|ide_info_t
r_typedef
r_struct
id|ide_info_t
(brace
DECL|member|link
id|dev_link_t
id|link
suffix:semicolon
DECL|member|ndev
r_int
id|ndev
suffix:semicolon
DECL|member|node
id|dev_node_t
id|node
suffix:semicolon
DECL|member|hd
r_int
id|hd
suffix:semicolon
DECL|typedef|ide_info_t
)brace
id|ide_info_t
suffix:semicolon
r_static
r_void
id|ide_config
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
suffix:semicolon
r_static
r_void
id|ide_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|ide_event
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
l_string|&quot;ide_cs&quot;
suffix:semicolon
r_static
id|dev_link_t
op_star
id|ide_attach
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|ide_detach
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
multiline_comment|/*======================================================================&n;&n;    ide_attach() creates an &quot;instance&quot; of the driver, allocating&n;    local data structures for one device.  The device is registered&n;    with Card Services.&n;&n;======================================================================*/
DECL|function|ide_attach
r_static
id|dev_link_t
op_star
id|ide_attach
c_func
(paren
r_void
)paren
(brace
id|ide_info_t
op_star
id|info
suffix:semicolon
id|dev_link_t
op_star
id|link
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
l_string|&quot;ide_attach()&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Create new ide device */
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
id|ide_release
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
id|IO_DATA_PATH_WIDTH_AUTO
suffix:semicolon
id|link-&gt;io.Attributes2
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
l_int|3
suffix:semicolon
id|link-&gt;irq.Attributes
op_assign
id|IRQ_TYPE_EXCLUSIVE
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
id|ide_event
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
id|CS_SUCCESS
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
id|ide_detach
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
multiline_comment|/* ide_attach */
multiline_comment|/*======================================================================&n;&n;    This deletes a driver &quot;instance&quot;.  The device is de-registered&n;    with Card Services.  If it has been released, all local data&n;    structures are freed.  Otherwise, the structures will be freed&n;    when the device is released.&n;&n;======================================================================*/
DECL|function|ide_detach
r_static
r_void
id|ide_detach
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
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ide_detach(0x%p)&bslash;n&quot;
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
id|ide_release
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
id|link-&gt;handle
)paren
(brace
id|ret
op_assign
id|CardServices
c_func
(paren
id|DeregisterClient
comma
id|link-&gt;handle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
id|CS_SUCCESS
)paren
id|cs_error
c_func
(paren
id|link-&gt;handle
comma
id|DeregisterClient
comma
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink, free device structure */
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|link-&gt;priv
)paren
suffix:semicolon
)brace
multiline_comment|/* ide_detach */
multiline_comment|/*======================================================================&n;&n;    ide_config() is scheduled to run after a CARD_INSERTION event&n;    is received, to configure the PCMCIA socket, and to make the&n;    ide device available to the system.&n;&n;======================================================================*/
DECL|macro|CS_CHECK
mdefine_line|#define CS_CHECK(fn, args...) &bslash;&n;while ((last_ret=CardServices(last_fn=(fn), args))!=0) goto cs_failed
DECL|macro|CFG_CHECK
mdefine_line|#define CFG_CHECK(fn, args...) &bslash;&n;if (CardServices(fn, args) != 0) goto next_entry
DECL|function|ide_config
r_void
id|ide_config
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
id|ide_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|tuple_t
id|tuple
suffix:semicolon
id|u_short
id|buf
(braket
l_int|128
)braket
suffix:semicolon
id|cisparse_t
id|parse
suffix:semicolon
id|config_info_t
id|conf
suffix:semicolon
id|cistpl_cftable_entry_t
op_star
id|cfg
op_assign
op_amp
id|parse.cftable_entry
suffix:semicolon
id|cistpl_cftable_entry_t
id|dflt
op_assign
(brace
l_int|0
)brace
suffix:semicolon
r_int
id|i
comma
id|pass
comma
id|last_ret
comma
id|last_fn
comma
id|hd
op_assign
op_minus
l_int|1
comma
id|io_base
comma
id|ctl_base
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ide_config(0x%p)&bslash;n&quot;
comma
id|link
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
id|tuple.TupleOffset
op_assign
l_int|0
suffix:semicolon
id|tuple.TupleDataMax
op_assign
l_int|255
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
multiline_comment|/* Not sure if this is right... look up the current Vcc */
id|CS_CHECK
c_func
(paren
id|GetConfigurationInfo
comma
id|handle
comma
op_amp
id|conf
)paren
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
id|conf.Vcc
suffix:semicolon
id|pass
op_assign
id|io_base
op_assign
id|ctl_base
op_assign
l_int|0
suffix:semicolon
id|tuple.DesiredTuple
op_assign
id|CISTPL_CFTABLE_ENTRY
suffix:semicolon
id|tuple.Attributes
op_assign
l_int|0
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
multiline_comment|/* Check for matching Vcc, unless we&squot;re desperate */
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
(brace
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
(brace
r_if
c_cond
(paren
id|conf.Vcc
op_ne
id|cfg-&gt;vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
r_goto
id|next_entry
suffix:semicolon
)brace
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
(brace
r_if
c_cond
(paren
id|conf.Vcc
op_ne
id|dflt.vcc.param
(braket
id|CISTPL_POWER_VNOM
)braket
op_div
l_int|10000
)paren
r_goto
id|next_entry
suffix:semicolon
)brace
)brace
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
id|link-&gt;conf.ConfigIndex
op_assign
id|cfg-&gt;index
suffix:semicolon
id|link-&gt;io.BasePort1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|base
suffix:semicolon
id|link-&gt;io.IOAddrLines
op_assign
id|io-&gt;flags
op_amp
id|CISTPL_IO_LINES_MASK
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
id|link-&gt;io.Attributes1
op_assign
id|IO_DATA_PATH_WIDTH_8
suffix:semicolon
r_if
c_cond
(paren
id|io-&gt;nwin
op_eq
l_int|2
)paren
(brace
id|link-&gt;io.NumPorts1
op_assign
l_int|8
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
l_int|1
suffix:semicolon
id|CFG_CHECK
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
id|io_base
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|ctl_base
op_assign
id|link-&gt;io.BasePort2
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|io-&gt;nwin
op_eq
l_int|1
)paren
op_logical_and
(paren
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|len
op_ge
l_int|16
)paren
)paren
(brace
id|link-&gt;io.NumPorts1
op_assign
id|io-&gt;win
(braket
l_int|0
)braket
dot
id|len
suffix:semicolon
id|link-&gt;io.NumPorts2
op_assign
l_int|0
suffix:semicolon
id|CFG_CHECK
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
id|io_base
op_assign
id|link-&gt;io.BasePort1
suffix:semicolon
id|ctl_base
op_assign
id|link-&gt;io.BasePort1
op_plus
l_int|0x0e
suffix:semicolon
)brace
r_else
r_goto
id|next_entry
suffix:semicolon
multiline_comment|/* If we&squot;ve got this far, we&squot;re done */
r_break
suffix:semicolon
)brace
id|next_entry
suffix:colon
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
id|pass
)paren
(brace
id|CS_CHECK
c_func
(paren
id|GetNextTuple
comma
id|handle
comma
op_amp
id|tuple
)paren
suffix:semicolon
)brace
r_else
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
op_ne
l_int|0
)paren
(brace
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
id|memset
c_func
(paren
op_amp
id|dflt
comma
l_int|0
comma
r_sizeof
(paren
id|dflt
)paren
)paren
suffix:semicolon
id|pass
op_increment
suffix:semicolon
)brace
)brace
id|CS_CHECK
c_func
(paren
id|RequestIRQ
comma
id|handle
comma
op_amp
id|link-&gt;irq
)paren
suffix:semicolon
id|CS_CHECK
c_func
(paren
id|RequestConfiguration
comma
id|handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
multiline_comment|/* deal with brain dead IDE resource management */
id|release_region
c_func
(paren
id|link-&gt;io.BasePort1
comma
id|link-&gt;io.NumPorts1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts2
)paren
id|release_region
c_func
(paren
id|link-&gt;io.BasePort2
comma
id|link-&gt;io.NumPorts2
)paren
suffix:semicolon
multiline_comment|/* retry registration in case device is still spinning up */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hd
op_assign
id|ide_register
c_func
(paren
id|io_base
comma
id|ctl_base
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hd
op_ge
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;io.NumPorts1
op_eq
l_int|0x20
)paren
(brace
id|hd
op_assign
id|ide_register
c_func
(paren
id|io_base
op_plus
l_int|0x10
comma
id|ctl_base
op_plus
l_int|0x10
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hd
op_ge
l_int|0
)paren
(brace
id|io_base
op_add_assign
l_int|0x10
suffix:semicolon
id|ctl_base
op_add_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|__set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
op_div
l_int|10
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;ide_cs: ide_register() at 0x%03x &amp; 0x%03x&quot;
l_string|&quot;, irq %u failed&bslash;n&quot;
comma
id|io_base
comma
id|ctl_base
comma
id|link-&gt;irq.AssignedIRQ
)paren
suffix:semicolon
r_goto
id|failed
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|info-&gt;ndev
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|info-&gt;node.dev_name
comma
l_string|&quot;hd%c&quot;
comma
l_char|&squot;a&squot;
op_plus
(paren
id|hd
op_star
l_int|2
)paren
)paren
suffix:semicolon
id|info-&gt;node.major
op_assign
id|ide_major
(braket
id|hd
)braket
suffix:semicolon
id|info-&gt;node.minor
op_assign
l_int|0
suffix:semicolon
id|info-&gt;hd
op_assign
id|hd
suffix:semicolon
id|link-&gt;dev
op_assign
op_amp
id|info-&gt;node
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ide_cs: %s: Vcc = %d.%d, Vpp = %d.%d&bslash;n&quot;
comma
id|info-&gt;node.dev_name
comma
id|link-&gt;conf.Vcc
op_div
l_int|10
comma
id|link-&gt;conf.Vcc
op_mod
l_int|10
comma
id|link-&gt;conf.Vpp1
op_div
l_int|10
comma
id|link-&gt;conf.Vpp1
op_mod
l_int|10
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
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
id|ide_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
)brace
multiline_comment|/* ide_config */
multiline_comment|/*======================================================================&n;&n;    After a card is removed, ide_release() will unregister the net&n;    device, and release the PCMCIA configuration.  If the device is&n;    still open, this will be postponed until it is closed.&n;    &n;======================================================================*/
DECL|function|ide_release
r_void
id|ide_release
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
id|ide_info_t
op_star
id|info
op_assign
id|link-&gt;priv
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;ide_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|info-&gt;ndev
)paren
(brace
id|ide_unregister
c_func
(paren
id|info-&gt;hd
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
id|info-&gt;ndev
op_assign
l_int|0
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
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
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
multiline_comment|/* ide_release */
multiline_comment|/*======================================================================&n;&n;    The card status event handler.  Mostly, this schedules other&n;    stuff to run after an event is received.  A CARD_REMOVAL event&n;    also sets some flags to discourage the ide drivers from&n;    talking to the ports.&n;    &n;======================================================================*/
DECL|function|ide_event
r_int
id|ide_event
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
id|DEBUG
c_func
(paren
l_int|1
comma
l_string|&quot;ide_event(0x%06x)&bslash;n&quot;
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
id|ide_config
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
id|CardServices
c_func
(paren
id|ReleaseConfiguration
comma
id|link-&gt;handle
)paren
suffix:semicolon
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
id|DEV_OK
c_func
(paren
id|link
)paren
)paren
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
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ide_event */
multiline_comment|/*====================================================================*/
DECL|function|init_ide_cs
r_static
r_int
id|__init
id|init_ide_cs
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
l_string|&quot;ide_cs: Card Services release &quot;
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
id|ide_attach
comma
op_amp
id|ide_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_ide_cs
r_static
r_void
id|__exit
id|exit_ide_cs
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
l_string|&quot;ide_cs: unloading&bslash;n&quot;
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
id|ide_detach
c_func
(paren
id|dev_list
)paren
suffix:semicolon
)brace
DECL|variable|init_ide_cs
id|module_init
c_func
(paren
id|init_ide_cs
)paren
suffix:semicolon
DECL|variable|exit_ide_cs
id|module_exit
c_func
(paren
id|exit_ide_cs
)paren
suffix:semicolon
eof
