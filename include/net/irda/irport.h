multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irport.h&n; * Version:       0.1&n; * Description:   Serial driver for IrDA&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sun Aug  3 13:49:59 1997&n; * Modified at:   Thu Jan  7 14:17:31 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1997, 1998 Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRPORT_H
DECL|macro|IRPORT_H
mdefine_line|#define IRPORT_H
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;net/irda/irda_device.h&gt;
DECL|macro|SPEED_DEFAULT
mdefine_line|#define SPEED_DEFAULT 9600
DECL|macro|SPEED_MAX
mdefine_line|#define SPEED_MAX     115200
multiline_comment|/*&n; * These are the supported serial types.&n; */
DECL|macro|PORT_UNKNOWN
mdefine_line|#define PORT_UNKNOWN    0
DECL|macro|PORT_8250
mdefine_line|#define PORT_8250       1
DECL|macro|PORT_16450
mdefine_line|#define PORT_16450      2
DECL|macro|PORT_16550
mdefine_line|#define PORT_16550      3
DECL|macro|PORT_16550A
mdefine_line|#define PORT_16550A     4
DECL|macro|PORT_CIRRUS
mdefine_line|#define PORT_CIRRUS     5
DECL|macro|PORT_16650
mdefine_line|#define PORT_16650      6
DECL|macro|PORT_MAX
mdefine_line|#define PORT_MAX        6  
DECL|macro|FRAME_MAX_SIZE
mdefine_line|#define FRAME_MAX_SIZE 2048
r_void
id|irport_close
c_func
(paren
r_int
id|iobase
)paren
suffix:semicolon
r_int
id|irport_open
c_func
(paren
r_int
id|iobase
)paren
suffix:semicolon
r_int
id|irport_detect
c_func
(paren
r_struct
id|irda_device
op_star
id|idev
)paren
suffix:semicolon
r_void
id|irport_change_speed
c_func
(paren
r_int
id|iobase
comma
r_int
id|speed
)paren
suffix:semicolon
r_void
id|irport_interrupt
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
suffix:semicolon
r_int
id|irport_hard_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
eof
