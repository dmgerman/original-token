multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irkbd.h&n; * Version:       0.2&n; * Description:   IrDA Keyboard/Mouse driver (Tekram IR-660)&n; * Status:        Experimental.&n; * Author:        Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * Created at:    Mon Mar  1 00:24:19 1999&n; * Modified at:   Thu Mar 11 14:54:00 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1999 Dag Brattli, All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Dag Brattli nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRKBD_H
DECL|macro|IRKBD_H
mdefine_line|#define IRKBD_H
multiline_comment|/* Some commands */
DECL|macro|IRKBD_CMD_INIT_KBD
mdefine_line|#define IRKBD_CMD_INIT_KBD   0xfe
DECL|macro|IRKBD_CMD_INIT_MOUSE
mdefine_line|#define IRKBD_CMD_INIT_MOUSE 0xff
DECL|macro|IRKBD_CMD_ENABLE
mdefine_line|#define IRKBD_CMD_ENABLE     0x41
DECL|macro|IRKBD_CMD_LED
mdefine_line|#define IRKBD_CMD_LED        0x31
DECL|macro|IRKBD_CMD_KDB_SPEED
mdefine_line|#define IRKBD_CMD_KDB_SPEED  0x33
multiline_comment|/* Some responses */
DECL|macro|IRKBD_RSP_KBDOK
mdefine_line|#define IRKBD_RSP_KBDOK      0x11
DECL|macro|IRKBD_RSP_KBDERR
mdefine_line|#define IRKBD_RSP_KBDERR     0x12
DECL|macro|IRKBD_RSP_MSOK
mdefine_line|#define IRKBD_RSP_MSOK       0x21
DECL|macro|IRKBD_RSP_MSERR
mdefine_line|#define IRKBD_RSP_MSERR      0x22
DECL|macro|IRKBD_RSP_LEDOK
mdefine_line|#define IRKBD_RSP_LEDOK      0x31
DECL|macro|IRKBD_RSP_KBDSPEEDOK
mdefine_line|#define IRKBD_RSP_KBDSPEEDOK 0x33
DECL|macro|IRKBD_RSP_RSPN41
mdefine_line|#define IRKBD_RSP_RSPN41     0x41
DECL|macro|IRKBD_RATE
mdefine_line|#define IRKBD_RATE       2 /* Polling rate, should be 15 ms */
DECL|macro|IRKBD_TIMEOUT
mdefine_line|#define IRKBD_TIMEOUT  100 /* 1000 ms */
DECL|macro|SUBFRAME_MASK
mdefine_line|#define SUBFRAME_MASK     0xc0
DECL|macro|SUBFRAME_MOUSE
mdefine_line|#define SUBFRAME_MOUSE    0x80
DECL|macro|SUBFRAME_KEYBOARD
mdefine_line|#define SUBFRAME_KEYBOARD 0x40
DECL|macro|SUBFRAME_RESPONSE
mdefine_line|#define SUBFRAME_RESPONSE 0x00
DECL|macro|IRKBD_MAX_HEADER
mdefine_line|#define IRKBD_MAX_HEADER (TTP_HEADER+LMP_HEADER+LAP_HEADER)
DECL|macro|IRKBD_BUF_SIZE
mdefine_line|#define IRKBD_BUF_SIZE 4096 /* Must be power of 2! */
r_enum
(brace
DECL|enumerator|IRKBD_IDLE
id|IRKBD_IDLE
comma
multiline_comment|/* Not connected */
DECL|enumerator|IRKBD_INIT_KBD
id|IRKBD_INIT_KBD
comma
multiline_comment|/* Initializing keyboard */
DECL|enumerator|IRKBD_INIT_MOUSE
id|IRKBD_INIT_MOUSE
comma
multiline_comment|/* Initializing mouse */
DECL|enumerator|IRKBD_POLLING
id|IRKBD_POLLING
comma
multiline_comment|/* Polling device */
)brace
suffix:semicolon
multiline_comment|/* Main structure */
DECL|struct|irkbd_cb
r_struct
id|irkbd_cb
(brace
DECL|member|dev
r_struct
id|miscdevice
id|dev
suffix:semicolon
DECL|member|devname
r_char
id|devname
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/* name of the registered device */
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* Open count */
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
DECL|member|tsap
r_struct
id|tsap_cb
op_star
id|tsap
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
DECL|member|scancodes
id|__u8
id|scancodes
(braket
id|IRKBD_BUF_SIZE
)braket
suffix:semicolon
multiline_comment|/* Buffer for mouse events */
DECL|member|head
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
id|tail
suffix:semicolon
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
DECL|member|async
r_struct
id|fasync_struct
op_star
id|async
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* IRKBD_H */
eof
