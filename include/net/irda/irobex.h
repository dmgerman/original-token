multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irobex.h&n; * Version:       0.8&n; * Description:   &n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Sat Jul  4 22:43:57 1998&n; * Modified at:   Thu Mar 11 16:11:54 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IROBEX_H
DECL|macro|IROBEX_H
mdefine_line|#define IROBEX_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;net/irda/timer.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
DECL|macro|LOW_THRESHOLD
mdefine_line|#define LOW_THRESHOLD      4
DECL|macro|HIGH_THRESHOLD
mdefine_line|#define HIGH_THRESHOLD     8
DECL|macro|IROBEX_MAX_QUEUE
mdefine_line|#define IROBEX_MAX_QUEUE  12
multiline_comment|/* Small structure to be used by the IOCTL call */
DECL|struct|irobex_ioc_t
r_struct
id|irobex_ioc_t
(brace
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|IROBEX_IOC_MAGIC
mdefine_line|#define IROBEX_IOC_MAGIC &squot;k&squot;
DECL|macro|IROBEX_IOCSCONNECT
mdefine_line|#define IROBEX_IOCSCONNECT    _IOW(IROBEX_IOC_MAGIC, 1, 4)
DECL|macro|IROBEX_IOCSDISCONNECT
mdefine_line|#define IROBEX_IOCSDISCONNECT _IOW(IROBEX_IOC_MAGIC, 2, 4)
DECL|macro|IROBEX_IOC_MAXNR
mdefine_line|#define IROBEX_IOC_MAXNR 2
DECL|macro|IROBEX_MAX_HEADER
mdefine_line|#define IROBEX_MAX_HEADER (TTP_HEADER+LMP_HEADER+LAP_HEADER)
r_typedef
r_enum
(brace
DECL|enumerator|OBEX_IDLE
id|OBEX_IDLE
comma
multiline_comment|/* Doing nothing */
DECL|enumerator|OBEX_DISCOVER
id|OBEX_DISCOVER
comma
multiline_comment|/* Trying to discovery remote device */
DECL|enumerator|OBEX_QUERY
id|OBEX_QUERY
comma
multiline_comment|/* Querying remote LM-IAS */
DECL|enumerator|OBEX_CONN
id|OBEX_CONN
comma
multiline_comment|/* Trying to connect to remote device */
DECL|enumerator|OBEX_DATA
id|OBEX_DATA
comma
multiline_comment|/* Data transfer ready */
DECL|typedef|OBEX_STATE
)brace
id|OBEX_STATE
suffix:semicolon
DECL|struct|irobex_cb
r_struct
id|irobex_cb
(brace
DECL|member|queue
id|QUEUE
id|queue
suffix:semicolon
multiline_comment|/* Must be first! */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic used to detect corruption of the struct */
DECL|member|state
id|OBEX_STATE
id|state
suffix:semicolon
multiline_comment|/* Current state */
DECL|member|saddr
id|__u32
id|saddr
suffix:semicolon
multiline_comment|/* my local address */
DECL|member|daddr
id|__u32
id|daddr
suffix:semicolon
multiline_comment|/* peer address */
DECL|member|time_discovered
r_int
r_int
id|time_discovered
suffix:semicolon
DECL|member|ckey
id|__u32
id|ckey
suffix:semicolon
multiline_comment|/* IrLMP client handle */
DECL|member|skey
id|__u32
id|skey
suffix:semicolon
multiline_comment|/* IrLMP service handle */
DECL|member|devname
r_char
id|devname
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* name of the registered device */
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
suffix:semicolon
DECL|member|eof
r_int
id|eof
suffix:semicolon
DECL|member|dtsap_sel
id|__u8
id|dtsap_sel
suffix:semicolon
multiline_comment|/* remote TSAP address */
DECL|member|stsap_sel
id|__u8
id|stsap_sel
suffix:semicolon
multiline_comment|/* local TSAP address */
DECL|member|irlap_data_size
r_int
id|irlap_data_size
suffix:semicolon
DECL|member|dev
r_struct
id|miscdevice
id|dev
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* open count */
DECL|member|rx_queue
r_struct
id|sk_buff_head
id|rx_queue
suffix:semicolon
multiline_comment|/* Receive queue */
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
DECL|member|async
r_struct
id|fasync_struct
op_star
id|async
suffix:semicolon
DECL|member|watchdog_timer
r_struct
id|timer_list
id|watchdog_timer
suffix:semicolon
DECL|member|tx_flow
id|LOCAL_FLOW
id|tx_flow
suffix:semicolon
DECL|member|rx_flow
id|LOCAL_FLOW
id|rx_flow
suffix:semicolon
)brace
suffix:semicolon
r_int
id|irobex_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irobex_watchdog_timer_expired
c_func
(paren
r_int
r_int
id|data
)paren
suffix:semicolon
DECL|function|irobex_start_watchdog_timer
r_inline
r_void
id|irobex_start_watchdog_timer
c_func
(paren
r_struct
id|irobex_cb
op_star
id|self
comma
r_int
id|timeout
)paren
(brace
id|irda_start_timer
c_func
(paren
op_amp
id|self-&gt;watchdog_timer
comma
id|timeout
comma
(paren
r_int
r_int
)paren
id|self
comma
id|irobex_watchdog_timer_expired
)paren
suffix:semicolon
)brace
r_extern
r_struct
id|irobex_cb
op_star
id|irobex
suffix:semicolon
macro_line|#endif
eof
