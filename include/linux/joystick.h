macro_line|#ifndef _LINUX_JOYSTICK_H
DECL|macro|_LINUX_JOYSTICK_H
mdefine_line|#define _LINUX_JOYSTICK_H
multiline_comment|/*&n; * /usr/include/linux/joystick.h  Version 1.2&n; *&n; * Copyright (C) 1996-1999 Vojtech Pavlik&n; *&n; * Sponsored by SuSE&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/types.h&gt;
macro_line|#include &lt;linux/module.h&gt;
multiline_comment|/*&n; * Version&n; */
DECL|macro|JS_VERSION
mdefine_line|#define JS_VERSION&t;&t;0x01020f
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
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,2,0)
macro_line|#error &quot;You need to use at least v2.2 Linux kernel.&quot;
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
macro_line|#include &lt;asm/spinlock.h&gt;
DECL|typedef|wait_queue_head_t
r_typedef
r_struct
id|wait_queue
op_star
id|wait_queue_head_t
suffix:semicolon
DECL|macro|__setup
mdefine_line|#define __setup(a,b)
DECL|macro|BASE_ADDRESS
mdefine_line|#define BASE_ADDRESS(x,i)&t;((x)-&gt;base_address[i])
DECL|macro|DECLARE_WAITQUEUE
mdefine_line|#define DECLARE_WAITQUEUE(x,y)&t;struct wait_queue x = { y, NULL }
DECL|macro|init_waitqueue_head
mdefine_line|#define init_waitqueue_head(x)&t;do { *(x) = NULL; } while (0)
DECL|macro|__set_current_state
mdefine_line|#define __set_current_state(x)&t;current-&gt;state = x
DECL|macro|SETUP_PARAM
mdefine_line|#define SETUP_PARAM&t;&t;char *str, int *ints
DECL|macro|SETUP_PARSE
mdefine_line|#define SETUP_PARSE(x)&t;&t;do {} while (0)
macro_line|#else
macro_line|#include &lt;linux/spinlock.h&gt;
DECL|macro|BASE_ADDRESS
mdefine_line|#define BASE_ADDRESS(x,i)&t;((x)-&gt;resource[i].start)
DECL|macro|SETUP_PARAM
mdefine_line|#define SETUP_PARAM&t;&t;char *str
DECL|macro|SETUP_PARSE
mdefine_line|#define SETUP_PARSE(x)&t;&t;int ints[x]; get_options(str, x, ints)
macro_line|#endif
DECL|macro|PCI_VENDOR_ID_AUREAL
mdefine_line|#define PCI_VENDOR_ID_AUREAL&t;0x12eb
multiline_comment|/*&n; * Parport stuff&n; */
macro_line|#include &lt;linux/parport.h&gt;
DECL|macro|JS_PAR_STATUS_INVERT
mdefine_line|#define JS_PAR_STATUS_INVERT&t;(0x80)
DECL|macro|JS_PAR_CTRL_INVERT
mdefine_line|#define JS_PAR_CTRL_INVERT&t;(0x04)
DECL|macro|JS_PAR_DATA_IN
mdefine_line|#define JS_PAR_DATA_IN(y)&t;parport_read_data(y-&gt;port)
DECL|macro|JS_PAR_DATA_OUT
mdefine_line|#define JS_PAR_DATA_OUT(x,y)&t;parport_write_data(y-&gt;port, x)
DECL|macro|JS_PAR_STATUS
mdefine_line|#define JS_PAR_STATUS(y)&t;parport_read_status(y-&gt;port)
macro_line|#ifndef PARPORT_NEED_GENERIC_OPS
DECL|macro|JS_PAR_CTRL_IN
mdefine_line|#define JS_PAR_CTRL_IN(y)&t;parport_read_control(y-&gt;port)
macro_line|#else
DECL|macro|JS_PAR_CTRL_IN
mdefine_line|#define JS_PAR_CTRL_IN(y)&t;inb(y-&gt;port-&gt;base+2) 
macro_line|#endif
macro_line|#if LINUX_VERSION_CODE &lt; KERNEL_VERSION(2,3,0)
DECL|macro|JS_PAR_CTRL_OUT
mdefine_line|#define JS_PAR_CTRL_OUT(x,y)&t;parport_write_control(y-&gt;port, x)
DECL|macro|JS_PAR_ECTRL_OUT
mdefine_line|#define JS_PAR_ECTRL_OUT(x,y)&t;parport_write_econtrol(y-&gt;port, x)
macro_line|#else
DECL|macro|JS_PAR_CTRL_OUT
mdefine_line|#define JS_PAR_CTRL_OUT(x,y)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((x) &amp; 0x20) parport_data_reverse(y-&gt;port);&t;&bslash;&n;&t;&t;else parport_data_forward(y-&gt;port);&t;&t;&bslash;&n;&t;&t;parport_write_control(y-&gt;port, (x) &amp; ~0x20);&t;&bslash;&n;&t;} while (0)
DECL|macro|JS_PAR_ECTRL_OUT
mdefine_line|#define JS_PAR_ECTRL_OUT(x,y)&t;/*parport sets PS/2 mode on ECR chips */
DECL|macro|PARPORT_MODE_PCPS2
mdefine_line|#define PARPORT_MODE_PCPS2&t;PARPORT_MODE_TRISTATE
DECL|macro|PARPORT_MODE_PCECPPS2
mdefine_line|#define PARPORT_MODE_PCECPPS2&t;PARPORT_MODE_TRISTATE
macro_line|#endif
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
id|wait_queue_head_t
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
DECL|member|fail
r_int
id|fail
suffix:semicolon
DECL|member|total
r_int
id|total
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Sub-module interface&n; */
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
id|js_cr_init
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
id|js_mag_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_pci_init
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
id|js_sball_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_orb_init
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
r_int
id|js_tg_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|js_war_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_JOYSTICK_H */
eof
