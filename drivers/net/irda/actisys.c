multiline_comment|/*********************************************************************&n; *                &n; * Filename:      actisys.c&n; * Version:       0.3&n; * Description:   Implementation for the ACTiSYS IR-220L and IR-220L+ &n; *                dongles&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Wed Oct 21 20:02:35 1998&n; * Modified at:   Mon Dec 14 11:50:32 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ioctls.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#include &lt;net/irda/irtty.h&gt;
macro_line|#include &lt;net/irda/dongle.h&gt;
r_static
r_void
id|actisys_reset
c_func
(paren
r_struct
id|irda_device
op_star
id|dev
comma
r_int
id|unused
)paren
suffix:semicolon
r_static
r_void
id|actisys_open
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_int
id|type
)paren
suffix:semicolon
r_static
r_void
id|actisys_close
c_func
(paren
r_struct
id|irda_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|actisys_change_speed
c_func
(paren
r_struct
id|irda_device
op_star
id|dev
comma
r_int
id|baudrate
)paren
suffix:semicolon
r_static
r_void
id|actisys_reset
c_func
(paren
r_struct
id|irda_device
op_star
id|dev
comma
r_int
id|unused
)paren
suffix:semicolon
r_static
r_void
id|actisys_init_qos
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_struct
id|qos_info
op_star
id|qos
)paren
suffix:semicolon
multiline_comment|/* These are the baudrates supported */
DECL|variable|baud_rates
r_static
r_int
id|baud_rates
(braket
)braket
op_assign
(brace
l_int|9600
comma
l_int|19200
comma
l_int|57600
comma
l_int|115200
comma
l_int|38400
)brace
suffix:semicolon
DECL|variable|dongle
r_static
r_struct
id|dongle
id|dongle
op_assign
(brace
id|ACTISYS_DONGLE
comma
id|actisys_open
comma
id|actisys_close
comma
id|actisys_reset
comma
id|actisys_change_speed
comma
id|actisys_init_qos
comma
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|actisys_init
c_func
(paren
r_void
)paren
)paren
(brace
id|irtty_register_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
DECL|function|actisys_cleanup
r_void
id|actisys_cleanup
c_func
(paren
r_void
)paren
(brace
id|irtty_unregister_dongle
c_func
(paren
op_amp
id|dongle
)paren
suffix:semicolon
)brace
DECL|function|actisys_open
r_static
r_void
id|actisys_open
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_int
id|type
)paren
(brace
id|strcat
c_func
(paren
id|idev-&gt;name
comma
l_string|&quot; &lt;-&gt; actisys&quot;
)paren
suffix:semicolon
id|idev-&gt;io.dongle_id
op_assign
id|type
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|actisys_close
r_static
r_void
id|actisys_close
c_func
(paren
r_struct
id|irda_device
op_star
id|dev
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; * Function actisys_change_speed (tty, baud)&n; *&n; *    Change speed of the ACTiSYS IR-220L and IR-220L+ type IrDA dongles.  &n; *    To cycle through the available baud rates, pulse RTS low for a few ms.&n; *    To be compatible with the new IR-220L+, we have to reset the dongle &n; *    first since its not possible cycle around anymore and still be &n; *    compatible with both dongles :-(&n; */
DECL|function|actisys_change_speed
r_static
r_void
id|actisys_change_speed
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_int
id|baudrate
)paren
(brace
r_struct
id|irtty_cb
op_star
id|self
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|arg
op_assign
l_int|0
suffix:semicolon
r_struct
id|termios
id|old_termios
suffix:semicolon
r_int
id|cflag
suffix:semicolon
r_int
id|current_baudrate
suffix:semicolon
r_int
id|index
op_assign
l_int|0
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|idev
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|idev-&gt;magic
op_eq
id|IRDA_DEVICE_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irtty_cb
op_star
)paren
id|idev-&gt;priv
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|current_baudrate
op_assign
id|idev-&gt;qos.baud_rate.value
suffix:semicolon
multiline_comment|/* Find the correct baudrate index for the currently used baudrate */
r_while
c_loop
(paren
id|current_baudrate
op_ne
id|baud_rates
(braket
id|index
)braket
)paren
id|index
op_increment
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), index=%d&bslash;n&quot;
comma
id|index
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|self-&gt;tty
)paren
r_return
suffix:semicolon
id|tty
op_assign
id|self-&gt;tty
suffix:semicolon
multiline_comment|/* Cycle through avaiable baudrates until we reach the correct one */
r_while
c_loop
(paren
id|current_baudrate
op_ne
id|baudrate
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), current baudrate = %d&bslash;n&quot;
comma
id|baud_rates
(braket
id|index
)braket
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Clearing RTS&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set DTR, clear RTS */
id|arg
op_assign
id|TIOCM_DTR
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver
dot
id|ioctl
c_func
(paren
id|tty
comma
l_int|NULL
comma
id|TIOCMSET
comma
(paren
r_int
r_int
)paren
op_amp
id|arg
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;Error clearing RTS!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
multiline_comment|/* Wait at a few ms */
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Set DTR, Set RTS */
id|arg
op_assign
id|TIOCM_DTR
op_or
id|TIOCM_RTS
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver
dot
id|ioctl
c_func
(paren
id|tty
comma
l_int|NULL
comma
id|TIOCMSET
comma
(paren
r_int
r_int
)paren
op_amp
id|arg
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;Error setting RTS!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
multiline_comment|/* Wait at a few ms again */
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Go to next baudrate */
r_if
c_cond
(paren
id|idev-&gt;io.dongle_id
op_eq
id|ACTISYS_DONGLE
)paren
id|index
op_assign
(paren
id|index
op_plus
l_int|1
)paren
op_mod
l_int|4
suffix:semicolon
multiline_comment|/* IR-220L */
r_else
id|index
op_assign
(paren
id|index
op_plus
l_int|1
)paren
op_mod
l_int|5
suffix:semicolon
multiline_comment|/* IR-220L+ */
id|current_baudrate
op_assign
id|baud_rates
(braket
id|index
)braket
suffix:semicolon
)brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), current baudrate = %d&bslash;n&quot;
comma
id|baud_rates
(braket
id|index
)braket
)paren
suffix:semicolon
multiline_comment|/* Now change the speed of the serial port */
id|old_termios
op_assign
op_star
(paren
id|tty-&gt;termios
)paren
suffix:semicolon
id|cflag
op_assign
id|tty-&gt;termios-&gt;c_cflag
suffix:semicolon
id|cflag
op_and_assign
op_complement
id|CBAUD
suffix:semicolon
r_switch
c_cond
(paren
id|baudrate
)paren
(brace
r_case
l_int|9600
suffix:colon
r_default
suffix:colon
id|cflag
op_or_assign
id|B9600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|19200
suffix:colon
id|cflag
op_or_assign
id|B19200
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|38400
suffix:colon
id|cflag
op_or_assign
id|B38400
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|57600
suffix:colon
id|cflag
op_or_assign
id|B57600
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|115200
suffix:colon
id|cflag
op_or_assign
id|B115200
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tty-&gt;termios-&gt;c_cflag
op_assign
id|cflag
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Setting the speed of the serial port&bslash;n&quot;
)paren
suffix:semicolon
id|tty-&gt;driver
dot
id|set_termios
c_func
(paren
id|tty
comma
op_amp
id|old_termios
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function actisys_reset (dev)&n; *&n; *      Reset the Actisys type dongle. Warning, this function must only be&n; *      called with a process context!&n; *&n; *    &t;1. Clear DTR for a few ms.&n; *&n; */
DECL|function|actisys_reset
r_static
r_void
id|actisys_reset
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_int
id|unused
)paren
(brace
r_struct
id|irtty_cb
op_star
id|self
suffix:semicolon
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
r_int
id|arg
op_assign
l_int|0
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|4
comma
id|__FUNCTION__
l_string|&quot;()&bslash;n&quot;
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|idev
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|idev-&gt;magic
op_eq
id|IRDA_DEVICE_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|self
op_assign
(paren
r_struct
id|irtty_cb
op_star
)paren
id|idev-&gt;priv
suffix:semicolon
id|ASSERT
c_func
(paren
id|self
op_ne
l_int|NULL
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|self-&gt;magic
op_eq
id|IRTTY_MAGIC
comma
r_return
suffix:semicolon
)paren
suffix:semicolon
id|tty
op_assign
id|self-&gt;tty
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tty
)paren
r_return
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Clearing DTR&bslash;n&quot;
)paren
suffix:semicolon
id|arg
op_assign
id|TIOCM_RTS
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver
dot
id|ioctl
c_func
(paren
id|tty
comma
l_int|NULL
comma
id|TIOCMSET
comma
(paren
r_int
r_int
)paren
op_amp
id|arg
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Ioctl error!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
multiline_comment|/* Sleep 10-20 ms*/
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Setting DTR&bslash;n&quot;
)paren
suffix:semicolon
id|arg
op_assign
id|TIOCM_RTS
op_or
id|TIOCM_DTR
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tty-&gt;driver
dot
id|ioctl
c_func
(paren
id|tty
comma
l_int|NULL
comma
id|TIOCMSET
comma
(paren
r_int
r_int
)paren
op_amp
id|arg
)paren
)paren
(brace
id|DEBUG
c_func
(paren
l_int|0
comma
id|__FUNCTION__
l_string|&quot;(), Ioctl error!&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
id|idev-&gt;qos.baud_rate.value
op_assign
l_int|9600
suffix:semicolon
)brace
multiline_comment|/*&n; * Function actisys_init_qos (qos)&n; *&n; *    Initialize QoS capabilities&n; *&n; */
DECL|function|actisys_init_qos
r_static
r_void
id|actisys_init_qos
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
comma
r_struct
id|qos_info
op_star
id|qos
)paren
(brace
id|qos-&gt;baud_rate.bits
op_and_assign
id|IR_9600
op_or
id|IR_19200
op_or
id|IR_38400
op_or
id|IR_57600
op_or
id|IR_115200
suffix:semicolon
multiline_comment|/* Remove support for 38400 if this is not a 220L+ dongle */
r_if
c_cond
(paren
id|idev-&gt;io.dongle_id
op_eq
id|ACTISYS_DONGLE
)paren
id|qos-&gt;baud_rate.bits
op_and_assign
op_complement
id|IR_38400
suffix:semicolon
id|qos-&gt;min_turn_time.bits
op_and_assign
l_int|0xfe
suffix:semicolon
multiline_comment|/* All except 0 ms */
)brace
macro_line|#ifdef MODULE
multiline_comment|/*&n; * Function init_module (void)&n; *&n; *    Initialize Actisys module&n; *&n; */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|actisys_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Function cleanup_module (void)&n; *&n; *    Cleanup Actisys module&n; *&n; */
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|actisys_cleanup
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
