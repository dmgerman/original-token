multiline_comment|/* $Id$&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Reset an IP27.&n; *&n; * Copyright (C) 1997, 1998, 1999 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/mmzone.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi/sgihpc.h&gt;
macro_line|#include &lt;asm/sgi/sgint23.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/arch.h&gt;
macro_line|#include &lt;asm/sn/gda.h&gt;
macro_line|#include &lt;asm/sn/sn0/hub.h&gt;
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_void
id|machine_halt
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
id|__attribute__
c_func
(paren
(paren
id|noreturn
)paren
)paren
suffix:semicolon
multiline_comment|/* XXX How to pass the reboot command to the firmware??? */
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Reboot started from CPU %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if 0
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|numnodes
suffix:semicolon
id|i
op_increment
)paren
id|REMOTE_HUB_S
c_func
(paren
id|COMPACT_TO_NASID_NODEID
c_func
(paren
id|i
)paren
comma
id|PROMOP_REG
comma
id|PROMOP_RESTART
)paren
suffix:semicolon
macro_line|#else
id|LOCAL_HUB_S
c_func
(paren
id|NI_PORT_RESET
comma
id|NPR_PORTRESET
op_or
id|NPR_LOCALRESET
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* To do ...  */
)brace
DECL|function|ip27_reboot_setup
r_void
id|ip27_reboot_setup
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Nothing to do on IP27.  */
)brace
eof
