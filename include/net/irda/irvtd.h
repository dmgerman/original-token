multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irvtd.h&n; * Version:       0.1&n; * Sources:       irlpt.h&n; * &n; *     Copyright (c) 1998, Takahide Higuchi &lt;thiguchi@pluto.dti.ne.jp&gt;,&n; *     All Rights Reserved.&n; *     &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *&n; *     I, Takahide Higuchi, provide no warranty for any of this software.&n; *     This material is provided &quot;AS-IS&quot; and at no charge.&n; *&n; ********************************************************************/
macro_line|#ifndef IRCOMM_H
DECL|macro|IRCOMM_H
mdefine_line|#define IRCOMM_H
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
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
multiline_comment|/*&n; * Serial input interrupt line counters -- external structure&n; * Four lines can interrupt: CTS, DSR, RI, DCD&n; *&n; * this structure must be compatible with serial_icounter_struct defined in&n; * &lt;linux/serial.h&gt;.&n; */
DECL|struct|icounter_struct
r_struct
id|icounter_struct
(brace
DECL|member|cts
DECL|member|dsr
DECL|member|rng
DECL|member|dcd
r_int
id|cts
comma
id|dsr
comma
id|rng
comma
id|dcd
suffix:semicolon
DECL|member|reserved
r_int
id|reserved
(braket
l_int|16
)braket
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/* buffer queue */
DECL|member|rxbuff
r_struct
id|sk_buff_head
id|rxbuff
suffix:semicolon
multiline_comment|/* buffer queue */
DECL|member|comm
r_struct
id|ircomm_cb
op_star
id|comm
suffix:semicolon
multiline_comment|/* ircomm instance */
multiline_comment|/* &n;&t; * These members are used for compatibility with usual serial device.&n;&t; * See linux/serial.h&n;&t; */
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
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
DECL|member|rx_tqueue
r_struct
id|tq_struct
id|rx_tqueue
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|normal_termios
r_struct
id|termios
id|normal_termios
suffix:semicolon
DECL|member|callout_termios
r_struct
id|termios
id|callout_termios
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
DECL|member|icount
r_struct
id|icounter_struct
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
multiline_comment|/* Debug function */
multiline_comment|/* #define CHECK_SKB(skb) check_skb((skb),  __LINE__,__FILE__) */
macro_line|#endif
eof
