multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irda_device.h&n; * Version:       &n; * Description:   &n; * Status:        Experimental.&n; * Author:        Haris Zukanovic &lt;haris@stud.cs.uit.no&gt;&n; * Created at:    Tue Apr 14 12:41:42 1998&n; * Modified at:   Thu Dec 10 21:18:25 1998&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; * &n; *     Copyright (c) 1998 Haris Zukanovic, &lt;haris@stud.cs.uit.no&gt;&n; *     Copyright (c) 1998 Dag Brattli, &lt;dagb@cs.uit.no&gt;&n; *     Copyright (c) 1998 Thomas Davis, &lt;ratbert@radiks.net&gt;,&n; *     All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     Neither Haris Zukanovic nor University of Troms&#xfffd; admit liability nor&n; *     provide warranty for any of this software. This material is &n; *     provided &quot;AS-IS&quot; and at no charge.&n; *     &n; ********************************************************************/
macro_line|#ifndef IRDA_DEVICE_H
DECL|macro|IRDA_DEVICE_H
mdefine_line|#define IRDA_DEVICE_H
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/qos.h&gt;
macro_line|#include &lt;net/irda/irqueue.h&gt;
DECL|macro|SIR_MODE
mdefine_line|#define SIR_MODE &t;0x01
DECL|macro|MIR_MODE
mdefine_line|#define MIR_MODE &t;0x02
DECL|macro|FIR_MODE
mdefine_line|#define FIR_MODE &t;0x04
DECL|macro|IO_PIO
mdefine_line|#define IO_PIO   &t;0x08
DECL|macro|IO_DMA
mdefine_line|#define IO_DMA&t;&t;0x10
DECL|macro|IO_XMIT
mdefine_line|#define IO_XMIT 0x01
DECL|macro|IO_RECV
mdefine_line|#define IO_RECV 0x02
multiline_comment|/* Chip specific info */
DECL|struct|chipio_t
r_struct
id|chipio_t
(brace
DECL|member|iobase
DECL|member|iobase2
r_int
id|iobase
comma
id|iobase2
suffix:semicolon
multiline_comment|/* IO base */
DECL|member|io_ext
DECL|member|io_ext2
r_int
id|io_ext
comma
id|io_ext2
suffix:semicolon
multiline_comment|/* Length of iobase */
DECL|member|irq
DECL|member|irq2
r_int
id|irq
comma
id|irq2
suffix:semicolon
multiline_comment|/* Interrupts used */
DECL|member|fifo_size
r_int
id|fifo_size
suffix:semicolon
multiline_comment|/* FIFO size */
DECL|member|dma
DECL|member|dma2
r_int
id|dma
comma
id|dma2
suffix:semicolon
multiline_comment|/* DMA channel used */
DECL|member|irqflags
r_int
id|irqflags
suffix:semicolon
multiline_comment|/* interrupt flags (ie, SA_SHIRQ|SA_INTERRUPT) */
DECL|member|direction
r_int
id|direction
suffix:semicolon
multiline_comment|/* Used by some FIR drivers */
DECL|member|baudrate
r_int
id|baudrate
suffix:semicolon
multiline_comment|/* Currently used baudrate */
DECL|member|dongle_id
r_int
id|dongle_id
suffix:semicolon
multiline_comment|/* Dongle or transceiver currently used */
)brace
suffix:semicolon
multiline_comment|/* Buffer specific info */
DECL|struct|iobuff_t
r_struct
id|iobuff_t
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Receiving state (transmit state not used) */
DECL|member|in_frame
r_int
id|in_frame
suffix:semicolon
multiline_comment|/* True if receiving frame */
DECL|member|data
id|__u8
op_star
id|data
suffix:semicolon
multiline_comment|/* the buffer */
DECL|member|head
id|__u8
op_star
id|head
suffix:semicolon
multiline_comment|/* start of data in buffer */
DECL|member|tail
id|__u8
op_star
id|tail
suffix:semicolon
multiline_comment|/* end of data in buffer */
DECL|member|offset
r_int
id|offset
suffix:semicolon
multiline_comment|/* Usually data + offset = head */
DECL|member|len
r_int
id|len
suffix:semicolon
multiline_comment|/* currently used bytes in buffer */
DECL|member|truesize
r_int
id|truesize
suffix:semicolon
multiline_comment|/* total size of the data area */
DECL|member|fcs
id|__u16
id|fcs
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* Allocation flags (GFP_KERNEL | GFP_DMA ) */
)brace
suffix:semicolon
multiline_comment|/* &n; * This structure contains data that _we_ would have liked to be in the device&n; * structure, but we don&squot;t want to mess it up more than it is already. Better &n; * to keep the data in separate structures! This structure abstracts common &n; * stuff from IrDA port implementations.&n; */
DECL|struct|irda_device
r_struct
id|irda_device
(brace
DECL|member|q
id|QUEUE
id|q
suffix:semicolon
multiline_comment|/* Must be first */
DECL|member|magic
r_int
id|magic
suffix:semicolon
multiline_comment|/* our magic bullet */
DECL|member|name
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|irlap
r_struct
id|irlap_cb
op_star
id|irlap
suffix:semicolon
multiline_comment|/* The link layer we are connected to  */
DECL|member|netdev
r_struct
id|device
id|netdev
suffix:semicolon
multiline_comment|/* Yes! we are some kind of netdevice */
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
multiline_comment|/* &t;int flags; */
DECL|member|priv
r_void
op_star
id|priv
suffix:semicolon
multiline_comment|/* Pointer to low level implementation */
DECL|member|qos
r_struct
id|qos_info
id|qos
suffix:semicolon
multiline_comment|/* QoS capabilities for this device */
DECL|member|io
r_struct
id|chipio_t
id|io
suffix:semicolon
DECL|member|tx_buff
r_struct
id|iobuff_t
id|tx_buff
suffix:semicolon
DECL|member|rx_buff
r_struct
id|iobuff_t
id|rx_buff
suffix:semicolon
DECL|member|media_busy
r_int
id|media_busy
suffix:semicolon
multiline_comment|/* Media busy stuff */
DECL|member|media_busy_timer
r_struct
id|timer_list
id|media_busy_timer
suffix:semicolon
DECL|member|todo_timer
r_struct
id|timer_list
id|todo_timer
suffix:semicolon
DECL|member|hard_xmit
r_int
(paren
op_star
id|hard_xmit
)paren
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
DECL|member|change_speed
r_void
(paren
op_star
id|change_speed
)paren
(paren
r_struct
id|irda_device
op_star
id|driver
comma
r_int
id|baud
)paren
suffix:semicolon
DECL|member|is_receiving
r_int
(paren
op_star
id|is_receiving
)paren
(paren
r_struct
id|irda_device
op_star
)paren
suffix:semicolon
multiline_comment|/* receiving? */
multiline_comment|/* int (*is_tbusy)(struct irda_device *); */
multiline_comment|/* transmitting? */
DECL|member|wait_until_sent
r_void
(paren
op_star
id|wait_until_sent
)paren
(paren
r_struct
id|irda_device
op_star
)paren
suffix:semicolon
DECL|member|new_speed
r_int
id|new_speed
suffix:semicolon
multiline_comment|/* Will be removed in future */
)brace
suffix:semicolon
r_extern
id|hashbin_t
op_star
id|irda_device
suffix:semicolon
multiline_comment|/* Function prototypes */
r_int
id|irda_device_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|irda_device_cleanup
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|irda_device_open
c_func
(paren
r_struct
id|irda_device
op_star
comma
r_char
op_star
id|name
comma
r_void
op_star
id|priv
)paren
suffix:semicolon
r_void
id|irda_device_close
c_func
(paren
r_struct
id|irda_device
op_star
)paren
suffix:semicolon
multiline_comment|/* Interface to be uses by IrLAP */
r_inline
r_void
id|irda_device_set_media_busy
c_func
(paren
r_struct
id|irda_device
op_star
comma
r_int
id|status
)paren
suffix:semicolon
r_inline
r_int
id|irda_device_is_media_busy
c_func
(paren
r_struct
id|irda_device
op_star
)paren
suffix:semicolon
r_inline
r_int
id|irda_device_is_receiving
c_func
(paren
r_struct
id|irda_device
op_star
)paren
suffix:semicolon
r_inline
r_void
id|irda_device_change_speed
c_func
(paren
r_struct
id|irda_device
op_star
comma
r_int
)paren
suffix:semicolon
r_inline
r_struct
id|qos_info
op_star
id|irda_device_get_qos
c_func
(paren
r_struct
id|irda_device
op_star
id|self
)paren
suffix:semicolon
r_int
id|irda_device_txqueue_empty
c_func
(paren
r_struct
id|irda_device
op_star
id|self
)paren
suffix:semicolon
r_int
id|irda_device_setup
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
id|__inline__
r_int
id|irda_get_mtt
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
)paren
suffix:semicolon
r_void
id|setup_dma
c_func
(paren
r_int
id|channel
comma
r_char
op_star
id|buffer
comma
r_int
id|count
comma
r_int
id|mode
)paren
suffix:semicolon
macro_line|#endif
eof
