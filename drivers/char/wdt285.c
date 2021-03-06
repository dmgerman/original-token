multiline_comment|/*&n; *&t;Intel 21285 watchdog driver&n; *&t;Copyright (c) Phil Blundell &lt;pb@nexus.co.uk&gt;, 1998&n; *&n; *&t;based on&n; *&n; *&t;SoftDog&t;0.05:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@redhat.com&gt;, All Rights Reserved.&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/hardware/dec21285.h&gt;
multiline_comment|/*&n; * Define this to stop the watchdog actually rebooting the machine.&n; */
DECL|macro|ONLY_TESTING
macro_line|#undef ONLY_TESTING
DECL|macro|TIMER_MARGIN
mdefine_line|#define TIMER_MARGIN&t;60&t;&t;/* (secs) Default is 1 minute */
DECL|macro|FCLK
mdefine_line|#define FCLK&t;(50*1000*1000)&t;&t;/* 50MHz */
DECL|variable|soft_margin
r_static
r_int
id|soft_margin
op_assign
id|TIMER_MARGIN
suffix:semicolon
multiline_comment|/* in seconds */
DECL|variable|timer_alive
r_static
r_int
id|timer_alive
suffix:semicolon
macro_line|#ifdef ONLY_TESTING
multiline_comment|/*&n; *&t;If the timer expires..&n; */
DECL|function|watchdog_fire
r_static
r_void
id|watchdog_fire
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
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Watchdog: Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_CNTL
op_assign
l_int|0
suffix:semicolon
op_star
id|CSR_TIMER4_CLR
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|watchdog_ping
r_static
r_void
id|watchdog_ping
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
op_star
id|CSR_TIMER4_LOAD
op_assign
id|soft_margin
op_star
(paren
id|FCLK
op_div
l_int|256
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|watchdog_open
r_static
r_int
id|watchdog_open
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_if
c_cond
(paren
id|timer_alive
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Ahead watchdog factor ten, Mr Sulu&n;&t; */
op_star
id|CSR_TIMER4_CLR
op_assign
l_int|0
suffix:semicolon
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
op_star
id|CSR_TIMER4_CNTL
op_assign
id|TIMER_CNTL_ENABLE
op_or
id|TIMER_CNTL_AUTORELOAD
op_or
id|TIMER_CNTL_DIV256
suffix:semicolon
macro_line|#ifdef ONLY_TESTING
id|request_irq
c_func
(paren
id|IRQ_TIMER4
comma
id|watchdog_fire
comma
l_int|0
comma
l_string|&quot;watchdog&quot;
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#else
op_star
id|CSR_SA110_CNTL
op_or_assign
l_int|1
op_lshift
l_int|13
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
id|timer_alive
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|watchdog_release
r_static
r_int
id|watchdog_release
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
macro_line|#ifdef ONLY_TESTING
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|IRQ_TIMER4
comma
l_int|NULL
)paren
suffix:semicolon
id|timer_alive
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
macro_line|#else
multiline_comment|/*&n;&t; *&t;It&squot;s irreversible!&n;&t; */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|watchdog_write
r_static
id|ssize_t
id|watchdog_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|data
comma
r_int
id|len
comma
id|loff_t
op_star
id|ppos
)paren
(brace
multiline_comment|/*  Can&squot;t seek (pwrite) on this device  */
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
r_if
c_cond
(paren
id|len
)paren
(brace
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|watchdog_ioctl
r_static
r_int
id|watchdog_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|i
suffix:semicolon
r_static
r_struct
id|watchdog_info
id|ident
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_string|&quot;Footbridge Watchdog&quot;
)brace
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
r_case
id|WDIOC_GETSUPPORT
suffix:colon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|watchdog_info
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_else
r_return
id|copy_to_user
c_func
(paren
(paren
r_struct
id|watchdog_info
op_star
)paren
id|arg
comma
op_amp
id|ident
comma
r_sizeof
(paren
id|ident
)paren
)paren
suffix:semicolon
r_case
id|WDIOC_GETSTATUS
suffix:colon
r_case
id|WDIOC_GETBOOTSTATUS
suffix:colon
r_return
id|put_user
c_func
(paren
l_int|0
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_case
id|WDIOC_KEEPALIVE
suffix:colon
id|watchdog_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|variable|watchdog_fops
r_static
r_struct
id|file_operations
id|watchdog_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|write
suffix:colon
id|watchdog_write
comma
id|ioctl
suffix:colon
id|watchdog_ioctl
comma
id|open
suffix:colon
id|watchdog_open
comma
id|release
suffix:colon
id|watchdog_release
comma
)brace
suffix:semicolon
DECL|variable|watchdog_miscdev
r_static
r_struct
id|miscdevice
id|watchdog_miscdev
op_assign
(brace
id|WATCHDOG_MINOR
comma
l_string|&quot;watchdog&quot;
comma
op_amp
id|watchdog_fops
)brace
suffix:semicolon
DECL|function|footbridge_watchdog_init
r_static
r_int
id|__init
id|footbridge_watchdog_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_netwinder
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|watchdog_miscdev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Footbridge Watchdog Timer: 0.01, timer margin: %d sec&bslash;n&quot;
comma
id|soft_margin
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_cats
c_func
(paren
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: Watchdog reset may not work on this machine.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|footbridge_watchdog_exit
r_static
r_void
id|__exit
id|footbridge_watchdog_exit
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|watchdog_miscdev
)paren
suffix:semicolon
)brace
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Phil Blundell &lt;pb@nexus.co.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;21285 watchdog driver&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|soft_margin
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|soft_margin
comma
l_string|&quot;Watchdog timeout in seconds&quot;
)paren
suffix:semicolon
DECL|variable|footbridge_watchdog_init
id|module_init
c_func
(paren
id|footbridge_watchdog_init
)paren
suffix:semicolon
DECL|variable|footbridge_watchdog_exit
id|module_exit
c_func
(paren
id|footbridge_watchdog_exit
)paren
suffix:semicolon
eof
