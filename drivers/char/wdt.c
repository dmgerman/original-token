multiline_comment|/*&n; *&t;Industrial Computer Source WDT500/501 driver for Linux 2.1.x&n; *&n; *&t;(c) Copyright 1996 Alan Cox &lt;alan@cymru.net&gt;, All Rights Reserved.&n; *&t;&t;&t;&t;http://www.cymru.net&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&t;&n; *&t;Neither Alan Cox nor CymruNet Ltd. admit liability nor provide &n; *&t;warranty for any of this software. This material is provided &n; *&t;&quot;AS-IS&quot; and at no charge.&t;&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Release 0.06.&n; *&n; *&t;Fixes&n; *&t;&t;Dave Gregorich&t;:&t;Modularisation and minor bugs&n; *&t;&t;Alan Cox&t;:&t;Added the watchdog ioctl() stuff&n; *&t;&t;Alan Cox&t;:&t;Fixed the reboot problem (as noted by&n; *&t;&t;&t;&t;&t;Matt Crocker).&n; *&t;&t;Alan Cox&t;:&t;Added wdt= boot option&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/watchdog.h&gt;
macro_line|#include &quot;wd501p.h&quot;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/notifier.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
DECL|variable|wdt_is_open
r_static
r_int
id|wdt_is_open
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;You must set these - there is no sane way to probe for this board.&n; *&t;You can use wdt=x,y to set these now.&n; */
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x240
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|14
suffix:semicolon
DECL|macro|WD_TIMO
mdefine_line|#define WD_TIMO (100*60)&t;&t;/* 1 minute */
multiline_comment|/*&n; *&t;Setup options&n; */
DECL|function|wdt_setup
r_void
id|wdt_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|0
)paren
(brace
id|io
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ints
(braket
l_int|0
)braket
OG
l_int|1
)paren
(brace
id|irq
op_assign
id|ints
(braket
l_int|2
)braket
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *&t;Programming support&n; */
DECL|function|wdt_ctr_mode
r_static
r_void
id|wdt_ctr_mode
c_func
(paren
r_int
id|ctr
comma
r_int
id|mode
)paren
(brace
id|ctr
op_lshift_assign
l_int|6
suffix:semicolon
id|ctr
op_or_assign
l_int|0x30
suffix:semicolon
id|ctr
op_or_assign
(paren
id|mode
op_lshift
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ctr
comma
id|WDT_CR
)paren
suffix:semicolon
)brace
DECL|function|wdt_ctr_load
r_static
r_void
id|wdt_ctr_load
c_func
(paren
r_int
id|ctr
comma
r_int
id|val
)paren
(brace
id|outb_p
c_func
(paren
id|val
op_amp
l_int|0xFF
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|val
op_rshift
l_int|8
comma
id|WDT_COUNT0
op_plus
id|ctr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kernel methods.&n; */
DECL|function|wdt_status
r_static
r_int
id|wdt_status
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; *&t;Status register to bit flags&n;&t; */
r_int
id|flag
op_assign
l_int|0
suffix:semicolon
r_int
r_char
id|status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
id|status
op_or_assign
id|FEATUREMAP1
suffix:semicolon
id|status
op_and_assign
op_complement
id|FEATUREMAP2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_OVERHEAT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_POWEROVER
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_POWERUNDER
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
(brace
id|flag
op_or_assign
id|WDIOF_FANFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|WDC_SR_ISOI0
)paren
(brace
id|flag
op_or_assign
id|WDIOF_EXTERN1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
id|WDC_SR_ISII1
)paren
(brace
id|flag
op_or_assign
id|WDIOF_EXTERN2
suffix:semicolon
)brace
r_return
id|flag
suffix:semicolon
)brace
DECL|function|wdt_interrupt
r_void
id|wdt_interrupt
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
multiline_comment|/*&n;&t; *&t;Read the status register see what is up and&n;&t; *&t;then printk it.&n;&t; */
r_int
r_char
id|status
op_assign
id|inb_p
c_func
(paren
id|WDT_SR
)paren
suffix:semicolon
id|status
op_or_assign
id|FEATUREMAP1
suffix:semicolon
id|status
op_and_assign
op_complement
id|FEATUREMAP2
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;WDT status %d&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_TGOOD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Overheat alarm.(%d)&bslash;n&quot;
comma
id|inb_p
c_func
(paren
id|WDT_RT
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUOVER
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PSU over voltage.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_PSUUNDR
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;PSU under voltage.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_FANGOOD
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Possible fan fault.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|WDC_SR_WCCR
)paren
)paren
(brace
macro_line|#ifdef SOFTWARE_REBOOT
macro_line|#ifdef ONLY_TESTING
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Would Reboot.&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else&t;&t;
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Initiating system reboot.&bslash;n&quot;
)paren
suffix:semicolon
id|machine_restart
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif&t;&t;
macro_line|#else
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Reset in 5ms.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif&t;&t;
)brace
DECL|function|wdt_llseek
r_static
r_int
r_int
id|wdt_llseek
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
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|function|wdt_ping
r_static
r_void
id|wdt_ping
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Write a watchdog value */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|1
comma
id|WD_TIMO
)paren
suffix:semicolon
multiline_comment|/* Timeout */
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
)brace
DECL|function|wdt_write
r_static
r_int
id|wdt_write
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
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_if
c_cond
(paren
id|count
)paren
(brace
id|wdt_ping
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
multiline_comment|/*&n; *&t;Read reports the temperature in farenheit&n; */
DECL|function|wdt_read
r_static
r_int
id|wdt_read
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
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
id|c
op_assign
id|inb_p
c_func
(paren
id|WDT_RT
)paren
suffix:semicolon
r_int
r_char
id|cp
suffix:semicolon
r_int
id|err
suffix:semicolon
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|TEMP_MINOR
suffix:colon
id|err
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_return
id|err
suffix:semicolon
)brace
id|c
op_mul_assign
l_int|11
suffix:semicolon
id|c
op_div_assign
l_int|15
suffix:semicolon
id|cp
op_assign
id|c
op_plus
l_int|7
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|cp
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|function|wdt_ioctl
r_static
r_int
id|wdt_ioctl
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
id|WDIOF_OVERHEAT
op_or
id|WDIOF_POWERUNDER
op_or
id|WDIOF_POWEROVER
op_or
id|WDIOF_EXTERN1
op_or
id|WDIOF_EXTERN2
op_or
id|WDIOF_FANFAULT
comma
l_int|1
comma
l_string|&quot;WDT500/501&quot;
)brace
suffix:semicolon
id|ident.options
op_and_assign
id|WDT_OPTION_MASK
suffix:semicolon
multiline_comment|/* Mask down to the card we have */
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
r_int
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
(brace
r_return
id|put_user
c_func
(paren
id|wdt_status
c_func
(paren
)paren
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
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
id|wdt_ping
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|wdt_open
r_static
r_int
id|wdt_open
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
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
id|WATCHDOG_MINOR
suffix:colon
r_if
c_cond
(paren
id|wdt_is_open
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *&t;Activate &n;&t;&t;&t; */
id|wdt_is_open
op_assign
l_int|1
suffix:semicolon
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable */
id|wdt_ctr_mode
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|wdt_ctr_mode
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|0
comma
l_int|8948
)paren
suffix:semicolon
multiline_comment|/* count at 100Hz */
id|wdt_ctr_load
c_func
(paren
l_int|1
comma
id|WD_TIMO
)paren
suffix:semicolon
multiline_comment|/* Timeout 120 seconds */
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|65535
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Enable */
r_return
l_int|0
suffix:semicolon
r_case
id|TEMP_MINOR
suffix:colon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|function|wdt_release
r_static
r_void
id|wdt_release
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
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_eq
id|WATCHDOG_MINOR
)paren
(brace
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT&t;
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
multiline_comment|/* Disable counters */
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* 0 length reset pulses now */
macro_line|#endif&t;&t;
id|wdt_is_open
op_assign
l_int|0
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Notifier for system down&n; */
DECL|function|wdt_notify_sys
r_static
r_int
id|wdt_notify_sys
c_func
(paren
r_struct
id|notifier_block
op_star
id|this
comma
r_int
r_int
id|code
comma
r_void
op_star
id|unused
)paren
(brace
r_if
c_cond
(paren
id|code
op_eq
id|SYS_DOWN
op_logical_or
id|code
op_eq
id|SYS_HALT
)paren
(brace
multiline_comment|/* Turn the card off */
id|inb_p
c_func
(paren
id|WDT_DC
)paren
suffix:semicolon
id|wdt_ctr_load
c_func
(paren
l_int|2
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Kernel Interfaces&n; */
DECL|variable|wdt_fops
r_static
r_struct
id|file_operations
id|wdt_fops
op_assign
(brace
id|wdt_llseek
comma
id|wdt_read
comma
id|wdt_write
comma
l_int|NULL
comma
multiline_comment|/* No Readdir */
l_int|NULL
comma
multiline_comment|/* No Select */
id|wdt_ioctl
comma
l_int|NULL
comma
multiline_comment|/* No mmap */
id|wdt_open
comma
id|wdt_release
)brace
suffix:semicolon
DECL|variable|wdt_miscdev
r_static
r_struct
id|miscdevice
id|wdt_miscdev
op_assign
(brace
id|WATCHDOG_MINOR
comma
l_string|&quot;wdt&quot;
comma
op_amp
id|wdt_fops
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501
DECL|variable|temp_miscdev
r_static
r_struct
id|miscdevice
id|temp_miscdev
op_assign
(brace
id|TEMP_MINOR
comma
l_string|&quot;temperature&quot;
comma
op_amp
id|wdt_fops
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;The WDT card needs to learn about soft shutdowns in order to&n; *&t;turn the timebomb registers off. &n; */
DECL|variable|wdt_notifier
r_static
r_struct
id|notifier_block
id|wdt_notifier
op_assign
(brace
id|wdt_notify_sys
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WDT501-P module at %X(Interrupt %d)&bslash;n&quot;
comma
id|io
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|wdt_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;wdt501p&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IRQ %d is not free.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|misc_register
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501&t;
id|misc_register
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
macro_line|#endif&t;
id|request_region
c_func
(paren
id|io
comma
l_int|8
comma
l_string|&quot;wdt501&quot;
)paren
suffix:semicolon
id|notifier_chain_register
c_func
(paren
op_amp
id|boot_notifier_list
comma
op_amp
id|wdt_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501&t;
id|misc_deregister
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
macro_line|#endif&t;
id|notifier_chain_unregister
c_func
(paren
op_amp
id|boot_notifier_list
comma
op_amp
id|wdt_notifier
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|8
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|irq
comma
l_int|NULL
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|wdt_init
r_int
id|wdt_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WDT500/501-P driver at %X(Interrupt %d)&bslash;n&quot;
comma
id|io
comma
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
id|wdt_interrupt
comma
id|SA_INTERRUPT
comma
l_string|&quot;wdt501p&quot;
comma
l_int|NULL
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;IRQ %d is not free.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|misc_register
c_func
(paren
op_amp
id|wdt_miscdev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_WDT_501&t;
id|misc_register
c_func
(paren
op_amp
id|temp_miscdev
)paren
suffix:semicolon
macro_line|#endif&t;
id|request_region
c_func
(paren
id|io
comma
l_int|8
comma
l_string|&quot;wdt501&quot;
)paren
suffix:semicolon
id|notifier_chain_register
c_func
(paren
op_amp
id|boot_notifier_list
comma
op_amp
id|wdt_notifier
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
eof
