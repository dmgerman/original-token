multiline_comment|/*&n; * $Id: b1pcmcia.c,v 1.3 1999/07/09 15:05:41 keil Exp $&n; * &n; * Module for AVM B1/M1/M2 PCMCIA-card.&n; * &n; * (c) Copyright 1999 by Carsten Paeth (calle@calle.in-berlin.de)&n; * &n; * $Log: b1pcmcia.c,v $&n; * Revision 1.3  1999/07/09 15:05:41  keil&n; * compat.h is now isdn_compat.h&n; *&n; * Revision 1.2  1999/07/05 15:09:51  calle&n; * - renamed &quot;appl_release&quot; to &quot;appl_released&quot;.&n; * - version und profile data now cleared on controller reset&n; * - extended /proc interface, to allow driver and controller specific&n; *   informations to include by driver hackers.&n; *&n; * Revision 1.1  1999/07/01 15:26:30  calle&n; * complete new version (I love it):&n; * + new hardware independed &quot;capi_driver&quot; interface that will make it easy to:&n; *   - support other controllers with CAPI-2.0 (i.e. USB Controller)&n; *   - write a CAPI-2.0 for the passive cards&n; *   - support serial link CAPI-2.0 boxes.&n; * + wrote &quot;capi_driver&quot; for all supported cards.&n; * + &quot;capi_driver&quot; (supported cards) now have to be configured with&n; *   make menuconfig, in the past all supported cards where included&n; *   at once.&n; * + new and better informations in /proc/capi/&n; * + new ioctl to switch trace of capi messages per controller&n; *   using &quot;avmcapictrl trace [contr] on|off|....&quot;&n; * + complete testcircle with all supported cards and also the&n; *   PCMCIA cards (now patch for pcmcia-cs-3.0.13 needed) done.&n; *&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/b1pcmcia.h&gt;
macro_line|#include &lt;linux/isdn_compat.h&gt;
macro_line|#include &quot;capicmd.h&quot;
macro_line|#include &quot;capiutil.h&quot;
macro_line|#include &quot;capilli.h&quot;
macro_line|#include &quot;avmcard.h&quot;
DECL|variable|revision
r_static
r_char
op_star
id|revision
op_assign
l_string|&quot;$Revision: 1.3 $&quot;
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth &lt;calle@calle.in-berlin.de&gt;&quot;
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|di
r_static
r_struct
id|capi_driver_interface
op_star
id|di
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_interrupt
r_static
r_void
id|b1pcmcia_interrupt
c_func
(paren
r_int
id|interrupt
comma
r_void
op_star
id|devptr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|avmcard
op_star
id|card
suffix:semicolon
id|card
op_assign
(paren
id|avmcard
op_star
)paren
id|devptr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;b1_interrupt: wrong device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|card-&gt;interrupt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1_interrupt: reentering interrupt hander (%s)&bslash;n&quot;
comma
id|card-&gt;name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|card-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|b1_handle_interrupt
c_func
(paren
id|card
)paren
suffix:semicolon
id|card-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_remove_ctr
r_static
r_void
id|b1pcmcia_remove_ctr
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmcard
op_star
id|card
op_assign
(paren
id|avmcard
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_int
r_int
id|port
op_assign
id|card-&gt;port
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|b1_reset
c_func
(paren
id|port
)paren
suffix:semicolon
id|di
op_member_access_from_pointer
id|detach_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
multiline_comment|/* io addrsses managent by CardServices &n;&t; * release_region(card-&gt;port, AVMB1_PORTLEN);&n;&t; */
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_add_card
r_static
r_int
id|b1pcmcia_add_card
c_func
(paren
r_struct
id|capi_driver
op_star
id|driver
comma
r_int
r_int
id|port
comma
r_int
id|irq
comma
r_enum
id|avmcardtype
id|cardtype
)paren
(brace
id|avmcard
op_star
id|card
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|card
op_assign
(paren
id|avmcard
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
id|avmcard
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;b1pcmcia: no memory.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|card
comma
l_int|0
comma
r_sizeof
(paren
id|avmcard
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cardtype
)paren
(brace
r_case
id|avm_m1
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;m1-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|avm_m2
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;m2-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|card-&gt;name
comma
l_string|&quot;b1pcmcia-%x&quot;
comma
id|port
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|card-&gt;port
op_assign
id|port
suffix:semicolon
id|card-&gt;irq
op_assign
id|irq
suffix:semicolon
id|card-&gt;cardtype
op_assign
id|cardtype
suffix:semicolon
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|b1_detect
c_func
(paren
id|card-&gt;port
comma
id|card-&gt;cardtype
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;b1pcmcia: NO card at 0x%x (%d)&bslash;n&quot;
comma
id|card-&gt;port
comma
id|retval
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|b1_reset
c_func
(paren
id|card-&gt;port
)paren
suffix:semicolon
id|retval
op_assign
id|request_irq
c_func
(paren
id|card-&gt;irq
comma
id|b1pcmcia_interrupt
comma
l_int|0
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1pcmcia: unable to get IRQ %d.&bslash;n&quot;
comma
id|card-&gt;irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|card-&gt;ctrl
op_assign
id|di
op_member_access_from_pointer
id|attach_ctr
c_func
(paren
id|driver
comma
id|card-&gt;name
comma
id|card
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card-&gt;ctrl
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;b1pcmcia: attach controller failed.&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|card-&gt;irq
comma
id|card
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|card
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
id|card-&gt;ctrl-&gt;cnr
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_procinfo
r_static
r_char
op_star
id|b1pcmcia_procinfo
c_func
(paren
r_struct
id|capi_ctr
op_star
id|ctrl
)paren
(brace
id|avmcard
op_star
id|card
op_assign
(paren
id|avmcard
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|card
)paren
r_return
l_string|&quot;&quot;
suffix:semicolon
id|sprintf
c_func
(paren
id|card-&gt;infobuf
comma
l_string|&quot;%s %s 0x%x %d&quot;
comma
id|card-&gt;cardname
(braket
l_int|0
)braket
ques
c_cond
id|card-&gt;cardname
suffix:colon
l_string|&quot;-&quot;
comma
id|card-&gt;version
(braket
id|VER_DRIVER
)braket
ques
c_cond
id|card-&gt;version
(braket
id|VER_DRIVER
)braket
suffix:colon
l_string|&quot;-&quot;
comma
id|card-&gt;port
comma
id|card-&gt;irq
)paren
suffix:semicolon
r_return
id|card-&gt;infobuf
suffix:semicolon
)brace
multiline_comment|/* ------------------------------------------------------------- */
DECL|variable|b1pcmcia_driver
r_static
r_struct
id|capi_driver
id|b1pcmcia_driver
op_assign
(brace
l_string|&quot;b1pcmcia&quot;
comma
l_string|&quot;0.0&quot;
comma
id|b1_load_firmware
comma
id|b1_reset_ctr
comma
id|b1pcmcia_remove_ctr
comma
id|b1_register_appl
comma
id|b1_release_appl
comma
id|b1_send_message
comma
id|b1pcmcia_procinfo
comma
id|b1ctl_read_proc
comma
l_int|0
comma
multiline_comment|/* use standard driver_read_proc */
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
DECL|function|b1pcmcia_addcard_b1
r_int
id|b1pcmcia_addcard_b1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
op_amp
id|b1pcmcia_driver
comma
id|port
comma
id|irq
comma
id|avm_b1pcmcia
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_addcard_m1
r_int
id|b1pcmcia_addcard_m1
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
op_amp
id|b1pcmcia_driver
comma
id|port
comma
id|irq
comma
id|avm_m1
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_addcard_m2
r_int
id|b1pcmcia_addcard_m2
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_return
id|b1pcmcia_add_card
c_func
(paren
op_amp
id|b1pcmcia_driver
comma
id|port
comma
id|irq
comma
id|avm_m2
)paren
suffix:semicolon
)brace
DECL|function|b1pcmcia_delcard
r_int
id|b1pcmcia_delcard
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_struct
id|capi_ctr
op_star
id|ctrl
suffix:semicolon
id|avmcard
op_star
id|card
suffix:semicolon
r_for
c_loop
(paren
id|ctrl
op_assign
id|b1pcmcia_driver.controller
suffix:semicolon
id|ctrl
suffix:semicolon
id|ctrl
op_assign
id|ctrl-&gt;next
)paren
(brace
id|card
op_assign
(paren
id|avmcard
op_star
)paren
(paren
id|ctrl-&gt;driverdata
)paren
suffix:semicolon
r_if
c_cond
(paren
id|card-&gt;port
op_eq
id|port
op_logical_and
id|card-&gt;irq
op_eq
id|irq
)paren
(brace
id|b1pcmcia_remove_ctr
c_func
(paren
id|ctrl
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ESRCH
suffix:semicolon
)brace
DECL|variable|b1pcmcia_addcard_b1
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_b1
)paren
suffix:semicolon
DECL|variable|b1pcmcia_addcard_m1
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_m1
)paren
suffix:semicolon
DECL|variable|b1pcmcia_addcard_m2
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_addcard_m2
)paren
suffix:semicolon
DECL|variable|b1pcmcia_delcard
id|EXPORT_SYMBOL
c_func
(paren
id|b1pcmcia_delcard
)paren
suffix:semicolon
multiline_comment|/* ------------------------------------------------------------- */
macro_line|#ifdef MODULE
DECL|macro|b1pcmcia_init
mdefine_line|#define b1pcmcia_init init_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|function|b1pcmcia_init
r_int
id|b1pcmcia_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|capi_driver
op_star
id|driver
op_assign
op_amp
id|b1pcmcia_driver
suffix:semicolon
r_char
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|revision
comma
l_char|&squot;:&squot;
)paren
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|driver-&gt;revision
comma
id|p
op_plus
l_int|1
comma
r_sizeof
(paren
id|driver-&gt;revision
)paren
)paren
suffix:semicolon
id|p
op_assign
id|strchr
c_func
(paren
id|driver-&gt;revision
comma
l_char|&squot;$&squot;
)paren
suffix:semicolon
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: revision %s&bslash;n&quot;
comma
id|driver-&gt;name
comma
id|driver-&gt;revision
)paren
suffix:semicolon
id|di
op_assign
id|attach_capi_driver
c_func
(paren
id|driver
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|di
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to attach capi_driver&bslash;n&quot;
comma
id|driver-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|detach_capi_driver
c_func
(paren
op_amp
id|b1pcmcia_driver
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
