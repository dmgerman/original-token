multiline_comment|/*======================================================================&n;&n;    CardBus device enabler&n;&n;    cb_enabler.c 1.31 2000/06/12 21:29:36&n;&n;    The contents of this file are subject to the Mozilla Public&n;    License Version 1.1 (the &quot;License&quot;); you may not use this file&n;    except in compliance with the License. You may obtain a copy of&n;    the License at http://www.mozilla.org/MPL/&n;&n;    Software distributed under the License is distributed on an &quot;AS&n;    IS&quot; basis, WITHOUT WARRANTY OF ANY KIND, either express or&n;    implied. See the License for the specific language governing&n;    rights and limitations under the License.&n;&n;    The initial developer of the original code is David A. Hinds&n;    &lt;dahinds@users.sourceforge.net&gt;.  Portions created by David A. Hinds&n;    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.&n;&n;    Alternatively, the contents of this file may be used under the&n;    terms of the GNU Public License version 2 (the &quot;GPL&quot;), in which&n;    case the provisions of the GPL are applicable instead of the&n;    above.  If you wish to allow the use of your version of this file&n;    only under the terms of the GPL and not to allow others to use&n;    your version of this file under the MPL, indicate your decision&n;    by deleting the provisions above and replace them with the notice&n;    and other provisions required by the GPL.  If you do not delete&n;    the provisions above, a recipient may use your version of this&n;    file under either the MPL or the GPL.&n;    &n;    The general idea:&n;&n;    A client driver registers using register_driver().  This module&n;    then creates a Card Services pseudo-client and registers it, and&n;    configures the socket if this is the first client.  It then&n;    invokes the appropriate PCI client routines in response to Card&n;    Services events.  &n;&n;======================================================================*/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
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
l_string|&quot;cb_enabler.c 1.31 2000/06/12 21:29:36 (David Hinds)&quot;
suffix:semicolon
macro_line|#else
DECL|macro|DEBUG
mdefine_line|#define DEBUG(n, args...) do { } while (0)
macro_line|#endif
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;David Hinds &lt;dahinds@users.sourceforge.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;CardBus stub enabler module&quot;
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
multiline_comment|/* Parameters that can be set with &squot;insmod&squot; */
multiline_comment|/*====================================================================*/
DECL|struct|driver_info_t
r_typedef
r_struct
id|driver_info_t
(brace
DECL|member|attach
id|dev_link_t
op_star
(paren
op_star
id|attach
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|dev_info
id|dev_info_t
id|dev_info
suffix:semicolon
DECL|member|ops
id|driver_operations
op_star
id|ops
suffix:semicolon
DECL|member|dev_list
id|dev_link_t
op_star
id|dev_list
suffix:semicolon
DECL|typedef|driver_info_t
)brace
id|driver_info_t
suffix:semicolon
r_static
id|dev_link_t
op_star
id|cb_attach
c_func
(paren
r_int
id|n
)paren
suffix:semicolon
DECL|macro|MK_ENTRY
mdefine_line|#define MK_ENTRY(fn, n) &bslash;&n;static dev_link_t *fn(void) { return cb_attach(n); }
DECL|macro|MAX_DRIVER
mdefine_line|#define MAX_DRIVER&t;4
id|MK_ENTRY
c_func
(paren
id|attach_0
comma
l_int|0
)paren
suffix:semicolon
id|MK_ENTRY
c_func
(paren
id|attach_1
comma
l_int|1
)paren
suffix:semicolon
id|MK_ENTRY
c_func
(paren
id|attach_2
comma
l_int|2
)paren
suffix:semicolon
id|MK_ENTRY
c_func
(paren
id|attach_3
comma
l_int|3
)paren
suffix:semicolon
DECL|variable|driver
r_static
id|driver_info_t
id|driver
(braket
l_int|4
)braket
op_assign
(brace
(brace
id|attach_0
)brace
comma
(brace
id|attach_1
)brace
comma
(brace
id|attach_2
)brace
comma
(brace
id|attach_3
)brace
)brace
suffix:semicolon
DECL|struct|bus_info_t
r_typedef
r_struct
id|bus_info_t
(brace
DECL|member|bus
id|u_char
id|bus
suffix:semicolon
DECL|member|flags
DECL|member|ncfg
DECL|member|nuse
r_int
id|flags
comma
id|ncfg
comma
id|nuse
suffix:semicolon
DECL|member|owner
id|dev_link_t
op_star
id|owner
suffix:semicolon
DECL|typedef|bus_info_t
)brace
id|bus_info_t
suffix:semicolon
DECL|macro|DID_REQUEST
mdefine_line|#define DID_REQUEST&t;1
DECL|macro|DID_CONFIG
mdefine_line|#define DID_CONFIG&t;2
r_static
r_void
id|cb_release
c_func
(paren
id|u_long
id|arg
)paren
suffix:semicolon
r_static
r_int
id|cb_event
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
r_static
r_void
id|cb_detach
c_func
(paren
id|dev_link_t
op_star
)paren
suffix:semicolon
DECL|variable|bus_table
r_static
id|bus_info_t
id|bus_table
(braket
id|MAX_DRIVER
)braket
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
id|pcmcia_report_error
c_func
(paren
id|handle
comma
op_amp
id|err
)paren
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|cb_attach
r_struct
id|dev_link_t
op_star
id|cb_attach
c_func
(paren
r_int
id|n
)paren
(brace
id|client_reg_t
id|client_reg
suffix:semicolon
id|dev_link_t
op_star
id|link
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cb_attach(%d)&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|link
)paren
r_return
l_int|NULL
suffix:semicolon
id|MOD_INC_USE_COUNT
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
id|link-&gt;conf.IntType
op_assign
id|INT_CARDBUS
suffix:semicolon
id|link-&gt;conf.Vcc
op_assign
l_int|33
suffix:semicolon
multiline_comment|/* Insert into instance chain for this driver */
id|link-&gt;priv
op_assign
op_amp
id|driver
(braket
id|n
)braket
suffix:semicolon
id|link-&gt;next
op_assign
id|driver
(braket
id|n
)braket
dot
id|dev_list
suffix:semicolon
id|driver
(braket
id|n
)braket
dot
id|dev_list
op_assign
id|link
suffix:semicolon
multiline_comment|/* Register with Card Services */
id|client_reg.dev_info
op_assign
op_amp
id|driver
(braket
id|n
)braket
dot
id|dev_info
suffix:semicolon
id|client_reg.Attributes
op_assign
id|INFO_IO_CLIENT
op_or
id|INFO_CARD_SHARE
suffix:semicolon
id|client_reg.event_handler
op_assign
op_amp
id|cb_event
suffix:semicolon
id|client_reg.EventMask
op_assign
id|CS_EVENT_RESET_PHYSICAL
op_or
id|CS_EVENT_RESET_REQUEST
op_or
id|CS_EVENT_CARD_RESET
op_or
id|CS_EVENT_CARD_INSERTION
op_or
id|CS_EVENT_CARD_REMOVAL
op_or
id|CS_EVENT_PM_SUSPEND
op_or
id|CS_EVENT_PM_RESUME
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
id|pcmcia_register_client
c_func
(paren
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
id|cb_detach
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
multiline_comment|/*====================================================================*/
DECL|function|cb_detach
r_static
r_void
id|cb_detach
c_func
(paren
id|dev_link_t
op_star
id|link
)paren
(brace
id|driver_info_t
op_star
id|dev
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev_link_t
op_star
op_star
id|linkp
suffix:semicolon
id|bus_info_t
op_star
id|b
op_assign
(paren
r_void
op_star
)paren
id|link-&gt;win
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cb_detach(0x%p)&bslash;n&quot;
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
id|dev-&gt;dev_list
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
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
id|cb_release
c_func
(paren
(paren
id|u_long
)paren
id|link
)paren
suffix:semicolon
multiline_comment|/* Don&squot;t drop Card Services connection if we are the bus owner */
r_if
c_cond
(paren
id|b
op_logical_and
(paren
id|b-&gt;flags
op_ne
l_int|0
)paren
op_logical_and
(paren
id|link
op_eq
id|b-&gt;owner
)paren
)paren
(brace
id|link-&gt;state
op_or_assign
id|DEV_STALE_LINK
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;handle
)paren
id|pcmcia_deregister_client
c_func
(paren
id|link-&gt;handle
)paren
suffix:semicolon
op_star
id|linkp
op_assign
id|link-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|link
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|cb_config
r_static
r_void
id|cb_config
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
id|driver_info_t
op_star
id|drv
op_assign
id|link-&gt;priv
suffix:semicolon
id|dev_locator_t
id|loc
suffix:semicolon
id|bus_info_t
op_star
id|b
suffix:semicolon
id|config_info_t
id|config
suffix:semicolon
id|u_char
id|bus
comma
id|devfn
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cb_config(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
id|link-&gt;state
op_or_assign
id|DEV_CONFIG
suffix:semicolon
multiline_comment|/* Get PCI bus info */
id|pcmcia_get_configuration_info
c_func
(paren
id|handle
comma
op_amp
id|config
)paren
suffix:semicolon
id|bus
op_assign
id|config.Option
suffix:semicolon
id|devfn
op_assign
id|config.Function
suffix:semicolon
multiline_comment|/* Is this a new bus? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DRIVER
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bus
op_eq
id|bus_table
(braket
id|i
)braket
dot
id|bus
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MAX_DRIVER
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
id|MAX_DRIVER
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|bus_table
(braket
id|i
)braket
dot
id|bus
op_eq
l_int|0
)paren
r_break
suffix:semicolon
id|b
op_assign
op_amp
id|bus_table
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;win
op_assign
(paren
r_void
op_star
)paren
id|b
suffix:semicolon
id|b-&gt;bus
op_assign
id|bus
suffix:semicolon
id|b-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|b-&gt;ncfg
op_assign
id|b-&gt;nuse
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Special hook: CS know what to do... */
id|i
op_assign
id|pcmcia_request_io
c_func
(paren
id|handle
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|handle
comma
id|RequestIO
comma
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;flags
op_or_assign
id|DID_REQUEST
suffix:semicolon
id|b-&gt;owner
op_assign
id|link
suffix:semicolon
id|i
op_assign
id|pcmcia_request_configuration
c_func
(paren
id|handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
id|CS_SUCCESS
)paren
(brace
id|cs_error
c_func
(paren
id|handle
comma
id|RequestConfiguration
comma
id|i
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|b-&gt;flags
op_or_assign
id|DID_CONFIG
suffix:semicolon
)brace
r_else
(brace
id|b
op_assign
op_amp
id|bus_table
(braket
id|i
)braket
suffix:semicolon
id|link-&gt;win
op_assign
(paren
r_void
op_star
)paren
id|b
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;flags
op_amp
id|DID_CONFIG
)paren
(brace
id|b-&gt;ncfg
op_increment
suffix:semicolon
id|b-&gt;nuse
op_increment
suffix:semicolon
)brace
)brace
id|loc.bus
op_assign
id|LOC_PCI
suffix:semicolon
id|loc.b.pci.bus
op_assign
id|bus
suffix:semicolon
id|loc.b.pci.devfn
op_assign
id|devfn
suffix:semicolon
id|link-&gt;dev
op_assign
id|drv-&gt;ops
op_member_access_from_pointer
id|attach
c_func
(paren
op_amp
id|loc
)paren
suffix:semicolon
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG_PENDING
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|cb_release
r_static
r_void
id|cb_release
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
id|driver_info_t
op_star
id|drv
op_assign
id|link-&gt;priv
suffix:semicolon
id|bus_info_t
op_star
id|b
op_assign
(paren
r_void
op_star
)paren
id|link-&gt;win
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cb_release(0x%p)&bslash;n&quot;
comma
id|link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|link-&gt;dev
op_ne
l_int|NULL
)paren
(brace
id|drv-&gt;ops
op_member_access_from_pointer
id|detach
c_func
(paren
id|link-&gt;dev
)paren
suffix:semicolon
id|link-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_CONFIG
)paren
(brace
multiline_comment|/* If we&squot;re suspended, config was already released */
r_if
c_cond
(paren
id|link-&gt;state
op_amp
id|DEV_SUSPEND
)paren
id|b-&gt;flags
op_and_assign
op_complement
id|DID_CONFIG
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|b-&gt;flags
op_amp
id|DID_CONFIG
)paren
op_logical_and
(paren
op_decrement
id|b-&gt;ncfg
op_eq
l_int|0
)paren
)paren
(brace
id|pcmcia_release_configuration
c_func
(paren
id|b-&gt;owner-&gt;handle
)paren
suffix:semicolon
id|b-&gt;flags
op_and_assign
op_complement
id|DID_CONFIG
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|b-&gt;flags
op_amp
id|DID_REQUEST
)paren
op_logical_and
(paren
op_decrement
id|b-&gt;nuse
op_eq
l_int|0
)paren
)paren
(brace
id|pcmcia_release_io
c_func
(paren
id|b-&gt;owner-&gt;handle
comma
l_int|NULL
)paren
suffix:semicolon
id|b-&gt;flags
op_and_assign
op_complement
id|DID_REQUEST
suffix:semicolon
)brace
r_if
c_cond
(paren
id|b-&gt;flags
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|b-&gt;owner
op_logical_and
(paren
id|b-&gt;owner-&gt;state
op_amp
id|DEV_STALE_LINK
)paren
)paren
id|cb_detach
c_func
(paren
id|b-&gt;owner
)paren
suffix:semicolon
id|b-&gt;bus
op_assign
l_int|0
suffix:semicolon
id|b-&gt;owner
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
id|link-&gt;state
op_and_assign
op_complement
id|DEV_CONFIG
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|cb_event
r_static
r_int
id|cb_event
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
id|driver_info_t
op_star
id|drv
op_assign
id|link-&gt;priv
suffix:semicolon
id|bus_info_t
op_star
id|b
op_assign
(paren
r_void
op_star
)paren
id|link-&gt;win
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;cb_event(0x%06x)&bslash;n&quot;
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
id|cb_release
c_func
(paren
(paren
id|u_long
)paren
id|link
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
id|cb_config
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
id|drv-&gt;ops-&gt;suspend
op_ne
l_int|NULL
)paren
id|drv-&gt;ops
op_member_access_from_pointer
id|suspend
c_func
(paren
id|link-&gt;dev
)paren
suffix:semicolon
id|b-&gt;ncfg
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;ncfg
op_eq
l_int|0
)paren
id|pcmcia_release_configuration
c_func
(paren
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
id|b-&gt;ncfg
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|b-&gt;ncfg
op_eq
l_int|1
)paren
id|pcmcia_request_configuration
c_func
(paren
id|link-&gt;handle
comma
op_amp
id|link-&gt;conf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|drv-&gt;ops-&gt;resume
op_ne
l_int|NULL
)paren
id|drv-&gt;ops
op_member_access_from_pointer
id|resume
c_func
(paren
id|link-&gt;dev
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*====================================================================*/
DECL|function|register_driver
r_int
id|register_driver
c_func
(paren
r_struct
id|driver_operations
op_star
id|ops
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;register_driver(&squot;%s&squot;)&bslash;n&quot;
comma
id|ops-&gt;name
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
id|MAX_DRIVER
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|driver
(braket
id|i
)braket
dot
id|ops
op_eq
l_int|NULL
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|MAX_DRIVER
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|driver
(braket
id|i
)braket
dot
id|ops
op_assign
id|ops
suffix:semicolon
id|strcpy
c_func
(paren
id|driver
(braket
id|i
)braket
dot
id|dev_info
comma
id|ops-&gt;name
)paren
suffix:semicolon
id|register_pccard_driver
c_func
(paren
op_amp
id|driver
(braket
id|i
)braket
dot
id|dev_info
comma
id|driver
(braket
id|i
)braket
dot
id|attach
comma
op_amp
id|cb_detach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unregister_driver
r_void
id|unregister_driver
c_func
(paren
r_struct
id|driver_operations
op_star
id|ops
)paren
(brace
r_int
id|i
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
l_string|&quot;unregister_driver(&squot;%s&squot;)&bslash;n&quot;
comma
id|ops-&gt;name
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
id|MAX_DRIVER
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|driver
(braket
id|i
)braket
dot
id|ops
op_eq
id|ops
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|MAX_DRIVER
)paren
(brace
id|unregister_pccard_driver
c_func
(paren
op_amp
id|driver
(braket
id|i
)braket
dot
id|dev_info
)paren
suffix:semicolon
id|driver
(braket
id|i
)braket
dot
id|ops
op_assign
l_int|NULL
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
)brace
multiline_comment|/*====================================================================*/
DECL|variable|register_driver
id|EXPORT_SYMBOL
c_func
(paren
id|register_driver
)paren
suffix:semicolon
DECL|variable|unregister_driver
id|EXPORT_SYMBOL
c_func
(paren
id|unregister_driver
)paren
suffix:semicolon
DECL|function|init_cb_enabler
r_static
r_int
id|__init
id|init_cb_enabler
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
id|pcmcia_get_card_services_info
c_func
(paren
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
l_string|&quot;cb_enabler: Card Services release &quot;
l_string|&quot;does not match!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|exit_cb_enabler
r_static
r_void
id|__exit
id|exit_cb_enabler
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
l_string|&quot;cb_enabler: unloading&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|variable|init_cb_enabler
id|module_init
c_func
(paren
id|init_cb_enabler
)paren
suffix:semicolon
DECL|variable|exit_cb_enabler
id|module_exit
c_func
(paren
id|exit_cb_enabler
)paren
suffix:semicolon
multiline_comment|/*====================================================================*/
eof
