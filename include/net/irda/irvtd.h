multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irvtd.h&n; * Version:       0.1&n; * Sources:       irlpt.h&n; * &n; *     Copyright (c) 1998, Takahide Higuchi &lt;thiguchi@pluto.dti.ne.jp&gt;,&n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     I, Takahide Higuchi, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRVTD_H
DECL|macro|IRVTD_H
mdefine_line|#define IRVTD_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/ircomm_common.h&gt;
DECL|macro|IRVTD_MAGIC
mdefine_line|#define IRVTD_MAGIC 0xff545943  /* random */
DECL|macro|COMM_MAX_TTY
mdefine_line|#define COMM_MAX_TTY 1
DECL|macro|IRVTD_RX_QUEUE_HIGH
mdefine_line|#define IRVTD_RX_QUEUE_HIGH 10
DECL|macro|IRVTD_RX_QUEUE_LOW
mdefine_line|#define IRVTD_RX_QUEUE_LOW  2
DECL|macro|IRCOMM_MAJOR
mdefine_line|#define IRCOMM_MAJOR  60;  /* Zero means automatic allocation&n;                              60,61,62,and 63 is reserved for experiment */
DECL|macro|IRVTD_MINOR
mdefine_line|#define IRVTD_MINOR 64
DECL|struct|irvtd_cb
r_struct
id|irvtd_cb
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* magic used to detect corruption of the struct */
multiline_comment|/* if daddr is NULL, remote device have not been discovered yet */
DECL|member|tx_disable
r_int
id|tx_disable
suffix:semicolon
DECL|member|rx_disable
r_int
id|rx_disable
suffix:semicolon
DECL|member|txbuff
r_struct
id|sk_buff
op_star
id|txbuff
suffix:semicolon
DECL|member|rxbuff
r_struct
id|sk_buff_head
id|rxbuff
suffix:semicolon
DECL|member|comm
r_struct
id|ircomm_cb
op_star
id|comm
suffix:semicolon
multiline_comment|/* ircomm instance */
multiline_comment|/* &n;&t; * These members are used for compatibility with usual serial device.&n;&t; * See linux/serial.h&n;&t; */
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* open count */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
DECL|member|close_wait
r_struct
id|wait_queue
op_star
id|close_wait
suffix:semicolon
DECL|member|delta_msr_wait
r_struct
id|wait_queue
op_star
id|delta_msr_wait
suffix:semicolon
DECL|member|tx_wait
r_struct
id|wait_queue
op_star
id|tx_wait
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before closing */
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|mcr
r_int
id|mcr
suffix:semicolon
DECL|member|msr
r_int
id|msr
suffix:semicolon
DECL|member|cts_stoptx
r_int
id|cts_stoptx
suffix:semicolon
DECL|member|ttp_stoptx
r_int
id|ttp_stoptx
suffix:semicolon
DECL|member|ttp_stoprx
r_int
id|ttp_stoprx
suffix:semicolon
DECL|member|disconnect_pend
r_int
id|disconnect_pend
suffix:semicolon
DECL|member|icount
r_struct
id|serial_icounter_struct
id|icount
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
