multiline_comment|/*&n; *&t;SoftDog&t;0.02:&t;A Software Watchdog Device&n; *&n; *&t;(c) Copyright 1995    Alan Cox &lt;alan@lxorguk.ukuu.org.uk&gt;&n; *&n; *&t;Email us for quotes on Linux software and driver development. &n; *&n; *&t;&t;&t;-----------------------&n; *&n; *&t;This program is free software; you can redistribute it and/or&n; *&t;modify it under the terms of the GNU General Public License&n; *&t;as published by the Free Software Foundation; either version&n; *&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;&t;&t;-----------------------&n; *&n; *&t;Software only watchdog driver. Unlike its big brother the WDT501P&n; *&t;driver this won&squot;t always recover a failed machine.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
DECL|macro|WATCHDOG_MINOR
mdefine_line|#define WATCHDOG_MINOR&t;130
DECL|macro|TIMER_MARGIN
mdefine_line|#define TIMER_MARGIN&t;(60*HZ)&t;&t;/* Allow 1 minute */
multiline_comment|/*&n; *&t;Our timer&n; */
DECL|variable|watchdog_ticktock
r_struct
id|timer_list
id|watchdog_ticktock
suffix:semicolon
DECL|variable|timer_alive
r_static
r_int
id|timer_alive
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; *&t;If the timer expires..&n; */
DECL|function|watchdog_fire
r_static
r_void
id|watchdog_fire
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_extern
r_void
id|hard_reset_now
c_func
(paren
r_void
)paren
suffix:semicolon
id|hard_reset_now
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;WATCHDOG: Reboot didn&squot;t ?????&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Allow only one person to hold it open&n; */
DECL|function|softdog_open
r_static
r_int
id|softdog_open
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
multiline_comment|/*&n;&t; *&t;Activate timer&n;&t; */
id|watchdog_ticktock.expires
op_assign
id|jiffies
op_plus
id|TIMER_MARGIN
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
id|timer_alive
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|softdog_release
r_static
r_void
id|softdog_release
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
multiline_comment|/*&n;&t; *&t;Shut off the timer.&n;&t; */
macro_line|#ifndef CONFIG_WATCHDOG_NOWAYOUT&t; 
id|del_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
macro_line|#endif&t;
id|timer_alive
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|softdog_write
r_static
r_int
id|softdog_write
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
id|data
comma
r_int
id|len
)paren
(brace
multiline_comment|/*&n;&t; *&t;Refresh the timer.&n;&t; */
id|del_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
id|watchdog_ticktock.expires
op_assign
id|jiffies
op_plus
id|TIMER_MARGIN
suffix:semicolon
id|add_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The mouse stuff ought to be renamed misc_register etc before 1.4...&n; */
DECL|function|watchdog_init
r_void
id|watchdog_init
c_func
(paren
r_void
)paren
(brace
r_static
r_struct
id|file_operations
id|softdog_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* Seek */
l_int|NULL
comma
multiline_comment|/* Read */
id|softdog_write
comma
multiline_comment|/* Write */
l_int|NULL
comma
multiline_comment|/* Readdir */
l_int|NULL
comma
multiline_comment|/* Select */
l_int|NULL
comma
multiline_comment|/* Ioctl */
l_int|NULL
comma
multiline_comment|/* MMap */
id|softdog_open
comma
id|softdog_release
comma
l_int|NULL
comma
l_int|NULL
multiline_comment|/* Fasync */
)brace
suffix:semicolon
r_static
r_struct
id|miscdevice
id|softdog_mouse
op_assign
initialization_block
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|softdog_mouse
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|watchdog_ticktock
)paren
suffix:semicolon
id|watchdog_ticktock.function
op_assign
id|watchdog_fire
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Software Watchdog Timer: 0.03&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof