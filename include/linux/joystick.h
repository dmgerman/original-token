macro_line|#ifndef _LINUX_JOYSTICK_H
DECL|macro|_LINUX_JOYSTICK_H
mdefine_line|#define _LINUX_JOYSTICK_H
multiline_comment|/*&n; * /usr/include/linux/joystick.h  Version 1.2&n; *&n; * Copyright (C) 1996-1998 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Version&n; */
DECL|macro|JS_VERSION
mdefine_line|#define JS_VERSION&t;&t;0x01020b
multiline_comment|/*&n; * Types and constants for reading from /dev/js&n; */
DECL|macro|JS_EVENT_BUTTON
mdefine_line|#define JS_EVENT_BUTTON&t;&t;0x01&t;/* button pressed/released */
DECL|macro|JS_EVENT_AXIS
mdefine_line|#define JS_EVENT_AXIS&t;&t;0x02&t;/* joystick moved */
DECL|macro|JS_EVENT_INIT
mdefine_line|#define JS_EVENT_INIT&t;&t;0x80&t;/* initial state of device */
DECL|struct|js_event
r_struct
id|js_event
(brace
DECL|member|time
id|__u32
id|time
suffix:semicolon
multiline_comment|/* event timestamp in miliseconds */
DECL|member|value
id|__s16
id|value
suffix:semicolon
multiline_comment|/* value */
DECL|member|type
id|__u8
id|type
suffix:semicolon
multiline_comment|/* event type */
DECL|member|number
id|__u8
id|number
suffix:semicolon
multiline_comment|/* axis/button number */
)brace
suffix:semicolon
multiline_comment|/*&n; * IOCTL commands for joystick driver&n; */
DECL|macro|JSIOCGVERSION
mdefine_line|#define JSIOCGVERSION&t;&t;_IOR(&squot;j&squot;, 0x01, __u32)&t;&t;&t;/* get driver version */
DECL|macro|JSIOCGAXES
mdefine_line|#define JSIOCGAXES&t;&t;_IOR(&squot;j&squot;, 0x11, __u8)&t;&t;&t;/* get number of axes */
DECL|macro|JSIOCGBUTTONS
mdefine_line|#define JSIOCGBUTTONS&t;&t;_IOR(&squot;j&squot;, 0x12, __u8)&t;&t;&t;/* get number of buttons */
DECL|macro|JSIOCGNAME
mdefine_line|#define JSIOCGNAME(len)&t;&t;_IOC(_IOC_READ, &squot;j&squot;, 0x13, len)         /* get identifier string */
DECL|macro|JSIOCSCORR
mdefine_line|#define JSIOCSCORR&t;&t;_IOW(&squot;j&squot;, 0x21, struct js_corr)&t;&t;/* set correction values */
DECL|macro|JSIOCGCORR
mdefine_line|#define JSIOCGCORR&t;&t;_IOR(&squot;j&squot;, 0x22, struct js_corr)&t;&t;/* get correction values */
multiline_comment|/*&n; * Types and constants for get/set correction&n; */
DECL|macro|JS_CORR_NONE
mdefine_line|#define JS_CORR_NONE&t;&t;0x00&t;/* returns raw values */
DECL|macro|JS_CORR_BROKEN
mdefine_line|#define JS_CORR_BROKEN&t;&t;0x01&t;/* broken line */
DECL|struct|js_corr
r_struct
id|js_corr
(brace
DECL|member|coef
id|__s32
id|coef
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|prec
id|__s16
id|prec
suffix:semicolon
DECL|member|type
id|__u16
id|type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * v0.x compatibility definitions&n; */
DECL|macro|JS_RETURN
mdefine_line|#define JS_RETURN&t;&t;sizeof(struct JS_DATA_TYPE)
DECL|macro|JS_TRUE
mdefine_line|#define JS_TRUE&t;&t;&t;1
DECL|macro|JS_FALSE
mdefine_line|#define JS_FALSE&t;&t;0
DECL|macro|JS_X_0
mdefine_line|#define JS_X_0&t;&t;&t;0x01
DECL|macro|JS_Y_0
mdefine_line|#define JS_Y_0&t;&t;&t;0x02
DECL|macro|JS_X_1
mdefine_line|#define JS_X_1&t;&t;&t;0x04
DECL|macro|JS_Y_1
mdefine_line|#define JS_Y_1&t;&t;&t;0x08
DECL|macro|JS_MAX
mdefine_line|#define JS_MAX&t;&t;&t;2
DECL|macro|JS_DEF_TIMEOUT
mdefine_line|#define JS_DEF_TIMEOUT&t;&t;0x1300
DECL|macro|JS_DEF_CORR
mdefine_line|#define JS_DEF_CORR&t;&t;0
DECL|macro|JS_DEF_TIMELIMIT
mdefine_line|#define JS_DEF_TIMELIMIT&t;10L
DECL|macro|JS_SET_CAL
mdefine_line|#define JS_SET_CAL&t;&t;1
DECL|macro|JS_GET_CAL
mdefine_line|#define JS_GET_CAL&t;&t;2
DECL|macro|JS_SET_TIMEOUT
mdefine_line|#define JS_SET_TIMEOUT&t;&t;3
DECL|macro|JS_GET_TIMEOUT
mdefine_line|#define JS_GET_TIMEOUT&t;&t;4
DECL|macro|JS_SET_TIMELIMIT
mdefine_line|#define JS_SET_TIMELIMIT&t;5
DECL|macro|JS_GET_TIMELIMIT
mdefine_line|#define JS_GET_TIMELIMIT&t;6
DECL|macro|JS_GET_ALL
mdefine_line|#define JS_GET_ALL&t;&t;7
DECL|macro|JS_SET_ALL
mdefine_line|#define JS_SET_ALL&t;&t;8
DECL|struct|JS_DATA_TYPE
r_struct
id|JS_DATA_TYPE
(brace
DECL|member|buttons
r_int
id|buttons
suffix:semicolon
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|JS_DATA_SAVE_TYPE
r_struct
id|JS_DATA_SAVE_TYPE
(brace
DECL|member|JS_TIMEOUT
r_int
id|JS_TIMEOUT
suffix:semicolon
DECL|member|BUSY
r_int
id|BUSY
suffix:semicolon
DECL|member|JS_EXPIRETIME
r_int
id|JS_EXPIRETIME
suffix:semicolon
DECL|member|JS_TIMELIMIT
r_int
id|JS_TIMELIMIT
suffix:semicolon
DECL|member|JS_SAVE
r_struct
id|JS_DATA_TYPE
id|JS_SAVE
suffix:semicolon
DECL|member|JS_CORR
r_struct
id|JS_DATA_TYPE
id|JS_CORR
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Internal definitions&n; */
macro_line|#ifdef __KERNEL__
DECL|macro|JS_BUFF_SIZE
mdefine_line|#define JS_BUFF_SIZE&t;&t;64&t;&t;/* output buffer size */
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef KERNEL_VERSION
DECL|macro|KERNEL_VERSION
mdefine_line|#define KERNEL_VERSION(a,b,c) (((a) &lt;&lt; 16) + ((b) &lt;&lt; 8) + (c))
macro_line|#endif
macro_line|#ifndef LINUX_VERSION_CODE
macro_line|#error &quot;You need to use at least 2.0 Linux kernel.&quot;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,0,0)
macro_line|#error &quot;You need to use at least 2.0 Linux kernel.&quot;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|JS_HAS_RDTSC
mdefine_line|#define JS_HAS_RDTSC (current_cpu_data.x86_capability &amp; 0x10)
macro_line|#include &lt;linux/init.h&gt;
macro_line|#else
macro_line|#ifdef MODULE
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,0,35)
DECL|macro|JS_HAS_RDTSC
mdefine_line|#define JS_HAS_RDTSC (x86_capability &amp; 0x10)
macro_line|#else
DECL|macro|JS_HAS_RDTSC
mdefine_line|#define JS_HAS_RDTSC 0
macro_line|#endif
macro_line|#else
DECL|macro|JS_HAS_RDTSC
mdefine_line|#define JS_HAS_RDTSC (x86_capability &amp; 0x10)
macro_line|#endif
DECL|macro|__initdata
mdefine_line|#define __initdata
DECL|macro|__init
mdefine_line|#define __init
DECL|macro|__cli
mdefine_line|#define __cli cli
DECL|macro|__save_flags
mdefine_line|#define __save_flags(flags) save_flags(flags)
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(flags)&t;restore_flags(flags)
DECL|macro|spin_lock_irqsave
mdefine_line|#define spin_lock_irqsave(x, flags) do { cli(); save_flags(flags); } while (0)
DECL|macro|spin_unlock_irqrestore
mdefine_line|#define spin_unlock_irqrestore(x, flags) restore_flags(flags)
DECL|macro|spin_lock_init
mdefine_line|#define spin_lock_init(x) do { } while (0)
DECL|member|something
DECL|typedef|spinlock_t
r_typedef
r_struct
(brace
r_int
id|something
suffix:semicolon
)brace
id|spinlock_t
suffix:semicolon
DECL|macro|SPIN_LOCK_UNLOCKED
mdefine_line|#define SPIN_LOCK_UNLOCKED { 0 }
DECL|macro|MODULE_AUTHOR
mdefine_line|#define MODULE_AUTHOR(x)
DECL|macro|MODULE_PARM
mdefine_line|#define MODULE_PARM(x,y)
DECL|macro|MODULE_SUPPORTED_DEVICE
mdefine_line|#define MODULE_SUPPORTED_DEVICE(x)
DECL|macro|signal_pending
mdefine_line|#define signal_pending(x) (((x)-&gt;signal) &amp; ~((x)-&gt;blocked))
macro_line|#endif
multiline_comment|/*&n; * Parport stuff&n; */
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,0)
DECL|macro|USE_PARPORT
mdefine_line|#define USE_PARPORT
macro_line|#endif
macro_line|#ifdef USE_PARPORT
macro_line|#include &lt;linux/parport.h&gt;
DECL|macro|JS_PAR_STATUS
mdefine_line|#define JS_PAR_STATUS(y)&t;parport_read_status(y-&gt;port)
DECL|macro|JS_PAR_DATA_IN
mdefine_line|#define JS_PAR_DATA_IN(y)&t;parport_read_data(y-&gt;port)
DECL|macro|JS_PAR_DATA_OUT
mdefine_line|#define JS_PAR_DATA_OUT(x,y)&t;parport_write_data(y-&gt;port, x)
DECL|macro|JS_PAR_CTRL_OUT
mdefine_line|#define JS_PAR_CTRL_OUT(x,y)&t;parport_write_control(y-&gt;port, x)
macro_line|#else
DECL|macro|JS_PAR_STATUS
mdefine_line|#define JS_PAR_STATUS(y)&t;inb(y+1)
DECL|macro|JS_PAR_DATA_IN
mdefine_line|#define JS_PAR_DATA_IN(y)&t;inb(y)
DECL|macro|JS_PAR_DATA_OUT
mdefine_line|#define JS_PAR_DATA_OUT(x,y)&t;outb(x,y)
DECL|macro|JS_PAR_CTRL_OUT
mdefine_line|#define JS_PAR_CTRL_OUT(x,y)&t;outb(x,y+2)
macro_line|#endif
DECL|macro|JS_PAR_STATUS_INVERT
mdefine_line|#define JS_PAR_STATUS_INVERT&t;(0x80)
multiline_comment|/*&n; * Internal types&n; */
r_struct
id|js_dev
suffix:semicolon
DECL|typedef|js_read_func
r_typedef
r_int
(paren
op_star
id|js_read_func
)paren
(paren
r_void
op_star
id|info
comma
r_int
op_star
op_star
id|axes
comma
r_int
op_star
op_star
id|buttons
)paren
suffix:semicolon
DECL|typedef|js_time_func
r_typedef
r_int
r_int
(paren
op_star
id|js_time_func
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|js_delta_func
r_typedef
r_int
(paren
op_star
id|js_delta_func
)paren
(paren
r_int
r_int
id|x
comma
r_int
r_int
id|y
)paren
suffix:semicolon
DECL|typedef|js_ops_func
r_typedef
r_int
(paren
op_star
id|js_ops_func
)paren
(paren
r_struct
id|js_dev
op_star
id|dev
)paren
suffix:semicolon
DECL|struct|js_data
r_struct
id|js_data
(brace
DECL|member|axes
r_int
op_star
id|axes
suffix:semicolon
DECL|member|buttons
r_int
op_star
id|buttons
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|js_dev
r_struct
id|js_dev
(brace
DECL|member|next
r_struct
id|js_dev
op_star
id|next
suffix:semicolon
DECL|member|list
r_struct
id|js_list
op_star
id|list
suffix:semicolon
DECL|member|port
r_struct
id|js_port
op_star
id|port
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|cur
r_struct
id|js_data
id|cur
suffix:semicolon
DECL|member|new
r_struct
id|js_data
r_new
suffix:semicolon
DECL|member|corr
r_struct
id|js_corr
op_star
id|corr
suffix:semicolon
DECL|member|buff
r_struct
id|js_event
id|buff
(braket
id|JS_BUFF_SIZE
)braket
suffix:semicolon
DECL|member|open
id|js_ops_func
id|open
suffix:semicolon
DECL|member|close
id|js_ops_func
id|close
suffix:semicolon
DECL|member|ahead
r_int
id|ahead
suffix:semicolon
DECL|member|bhead
r_int
id|bhead
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|num_axes
r_int
id|num_axes
suffix:semicolon
DECL|member|num_buttons
r_int
id|num_buttons
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|js_list
r_struct
id|js_list
(brace
DECL|member|next
r_struct
id|js_list
op_star
id|next
suffix:semicolon
DECL|member|dev
r_struct
id|js_dev
op_star
id|dev
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|startup
r_int
id|startup
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|js_port
r_struct
id|js_port
(brace
DECL|member|next
r_struct
id|js_port
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|js_port
op_star
id|prev
suffix:semicolon
DECL|member|read
id|js_read_func
id|read
suffix:semicolon
DECL|member|devs
r_struct
id|js_dev
op_star
op_star
id|devs
suffix:semicolon
DECL|member|axes
r_int
op_star
op_star
id|axes
suffix:semicolon
DECL|member|buttons
r_int
op_star
op_star
id|buttons
suffix:semicolon
DECL|member|corr
r_struct
id|js_corr
op_star
op_star
id|corr
suffix:semicolon
DECL|member|info
r_void
op_star
id|info
suffix:semicolon
DECL|member|ndevs
r_int
id|ndevs
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Sub-module interface&n; */
r_extern
r_int
r_int
id|js_time_speed
suffix:semicolon
r_extern
id|js_time_func
id|js_get_time
suffix:semicolon
r_extern
id|js_delta_func
id|js_delta
suffix:semicolon
r_extern
r_int
r_int
id|js_time_speed_a
suffix:semicolon
r_extern
id|js_time_func
id|js_get_time_a
suffix:semicolon
r_extern
id|js_delta_func
id|js_delta_a
suffix:semicolon
r_extern
r_struct
id|js_port
op_star
id|js_register_port
c_func
(paren
r_struct
id|js_port
op_star
id|port
comma
r_void
op_star
id|info
comma
r_int
id|devs
comma
r_int
id|infos
comma
id|js_read_func
id|read
)paren
suffix:semicolon
r_extern
r_struct
id|js_port
op_star
id|js_unregister_port
c_func
(paren
r_struct
id|js_port
op_star
id|port
)paren
suffix:semicolon
r_extern
r_int
id|js_register_device
c_func
(paren
r_struct
id|js_port
op_star
id|port
comma
r_int
id|number
comma
r_int
id|axes
comma
r_int
id|buttons
comma
r_char
op_star
id|name
comma
id|js_ops_func
id|open
comma
id|js_ops_func
id|close
)paren
suffix:semicolon
r_extern
r_void
id|js_unregister_device
c_func
(paren
r_struct
id|js_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * Kernel interface&n; */
r_extern
r_int
id|js_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_am_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_an_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_as_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_console_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_db9_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_gr_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_l4_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_lt_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_sw_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_tm_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|js_am_setup
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
suffix:semicolon
r_extern
r_void
id|js_an_setup
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
suffix:semicolon
r_extern
r_void
id|js_as_setup
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
suffix:semicolon
r_extern
r_void
id|js_console_setup
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
suffix:semicolon
r_extern
r_void
id|js_db9_setup
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
suffix:semicolon
r_extern
r_void
id|js_l4_setup
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
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_JOYSTICK_H */
eof
