multiline_comment|/*&n; * include/linux/serial.h&n; *&n; * Copyright (C) 1992 by Theodore Ts&squot;o.&n; * &n; * Redistribution of this file is permitted under the terms of the GNU &n; * Public License (GPL)&n; */
macro_line|#ifndef _LINUX_SERIAL_H
DECL|macro|_LINUX_SERIAL_H
mdefine_line|#define _LINUX_SERIAL_H
DECL|struct|serial_struct
r_struct
id|serial_struct
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|close_delay
r_int
r_int
id|close_delay
suffix:semicolon
DECL|member|reserved_char
r_char
id|reserved_char
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
multiline_comment|/* time to wait before rcvr shutdown */
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
multiline_comment|/* time to wait after rcvr shutdown */
DECL|member|reserved
r_int
id|reserved
(braket
l_int|4
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * For the close wait times, 0 means wait forever for serial port to&n; * flush its output.  65535 means don&squot;t wait at all.&n; */
DECL|macro|ASYNC_CLOSING_WAIT_INF
mdefine_line|#define ASYNC_CLOSING_WAIT_INF&t;0
DECL|macro|ASYNC_CLOSING_WAIT_NONE
mdefine_line|#define ASYNC_CLOSING_WAIT_NONE&t;65535
multiline_comment|/*&n; * These are the supported serial types.&n; */
DECL|macro|PORT_UNKNOWN
mdefine_line|#define PORT_UNKNOWN&t;0
DECL|macro|PORT_8250
mdefine_line|#define PORT_8250&t;1
DECL|macro|PORT_16450
mdefine_line|#define PORT_16450&t;2
DECL|macro|PORT_16550
mdefine_line|#define PORT_16550&t;3
DECL|macro|PORT_16550A
mdefine_line|#define PORT_16550A&t;4
DECL|macro|PORT_CIRRUS
mdefine_line|#define PORT_CIRRUS     5&t;/* Hey!  Who put this there? */
DECL|macro|PORT_16650
mdefine_line|#define PORT_16650&t;6
DECL|macro|PORT_MAX
mdefine_line|#define PORT_MAX&t;6
multiline_comment|/*&n; * Definitions for async_struct (and serial_struct) flags field&n; */
DECL|macro|ASYNC_HUP_NOTIFY
mdefine_line|#define ASYNC_HUP_NOTIFY 0x0001 /* Notify getty on hangups and closes &n;&t;&t;&t;&t;   on the callout port */
DECL|macro|ASYNC_FOURPORT
mdefine_line|#define ASYNC_FOURPORT  0x0002&t;/* Set OU1, OUT2 per AST Fourport settings */
DECL|macro|ASYNC_SAK
mdefine_line|#define ASYNC_SAK&t;0x0004&t;/* Secure Attention Key (Orange book) */
DECL|macro|ASYNC_SPLIT_TERMIOS
mdefine_line|#define ASYNC_SPLIT_TERMIOS 0x0008 /* Separate termios for dialin/callout */
DECL|macro|ASYNC_SPD_MASK
mdefine_line|#define ASYNC_SPD_MASK&t;0x0030
DECL|macro|ASYNC_SPD_HI
mdefine_line|#define ASYNC_SPD_HI&t;0x0010&t;/* Use 56000 instead of 38400 bps */
DECL|macro|ASYNC_SPD_VHI
mdefine_line|#define ASYNC_SPD_VHI&t;0x0020  /* Use 115200 instead of 38400 bps */
DECL|macro|ASYNC_SPD_CUST
mdefine_line|#define ASYNC_SPD_CUST&t;0x0030  /* Use user-specified divisor */
DECL|macro|ASYNC_SKIP_TEST
mdefine_line|#define ASYNC_SKIP_TEST&t;0x0040 /* Skip UART test during autoconfiguration */
DECL|macro|ASYNC_AUTO_IRQ
mdefine_line|#define ASYNC_AUTO_IRQ  0x0080 /* Do automatic IRQ during autoconfiguration */
DECL|macro|ASYNC_SESSION_LOCKOUT
mdefine_line|#define ASYNC_SESSION_LOCKOUT 0x0100 /* Lock out cua opens based on session */
DECL|macro|ASYNC_PGRP_LOCKOUT
mdefine_line|#define ASYNC_PGRP_LOCKOUT    0x0200 /* Lock out cua opens based on pgrp */
DECL|macro|ASYNC_CALLOUT_NOHUP
mdefine_line|#define ASYNC_CALLOUT_NOHUP   0x0400 /* Don&squot;t do hangups for cua device */
DECL|macro|ASYNC_FLAGS
mdefine_line|#define ASYNC_FLAGS&t;0x0FFF&t;/* Possible legal async flags */
DECL|macro|ASYNC_USR_MASK
mdefine_line|#define ASYNC_USR_MASK 0x0430&t;/* Legal flags that non-privileged&n;&t;&t;&t;&t; * users can set or reset */
multiline_comment|/* Internal flags used only by kernel/chr_drv/serial.c */
DECL|macro|ASYNC_INITIALIZED
mdefine_line|#define ASYNC_INITIALIZED&t;0x80000000 /* Serial port was initialized */
DECL|macro|ASYNC_CALLOUT_ACTIVE
mdefine_line|#define ASYNC_CALLOUT_ACTIVE&t;0x40000000 /* Call out device is active */
DECL|macro|ASYNC_NORMAL_ACTIVE
mdefine_line|#define ASYNC_NORMAL_ACTIVE&t;0x20000000 /* Normal device is active */
DECL|macro|ASYNC_BOOT_AUTOCONF
mdefine_line|#define ASYNC_BOOT_AUTOCONF&t;0x10000000 /* Autoconfigure port on bootup */
DECL|macro|ASYNC_CLOSING
mdefine_line|#define ASYNC_CLOSING&t;&t;0x08000000 /* Serial port is closing */
DECL|macro|ASYNC_CTS_FLOW
mdefine_line|#define ASYNC_CTS_FLOW&t;&t;0x04000000 /* Do CTS flow control */
DECL|macro|ASYNC_CHECK_CD
mdefine_line|#define ASYNC_CHECK_CD&t;&t;0x02000000 /* i.e., CLOCAL */
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * This is our internal structure for each serial port&squot;s state.&n; * &n; * Many fields are paralleled by the structure used by the serial_struct&n; * structure.&n; *&n; * For definitions of the flags field, see tty.h&n; */
DECL|struct|async_struct
r_struct
id|async_struct
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
id|irq
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* defined in tty.h */
DECL|member|hub6
r_int
id|hub6
suffix:semicolon
multiline_comment|/* HUB6 plus one */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* UART type */
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|read_status_mask
r_int
id|read_status_mask
suffix:semicolon
DECL|member|ignore_status_mask
r_int
id|ignore_status_mask
suffix:semicolon
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
DECL|member|xmit_fifo_size
r_int
id|xmit_fifo_size
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
DECL|member|x_char
r_int
id|x_char
suffix:semicolon
multiline_comment|/* xon/xoff character */
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|closing_wait2
r_int
r_int
id|closing_wait2
suffix:semicolon
DECL|member|IER
r_int
id|IER
suffix:semicolon
multiline_comment|/* Interrupt Enable Register */
DECL|member|MCR
r_int
id|MCR
suffix:semicolon
multiline_comment|/* Modem control register */
DECL|member|MCR_noint
r_int
id|MCR_noint
suffix:semicolon
multiline_comment|/* MCR with interrupts off */
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|last_active
r_int
r_int
id|last_active
suffix:semicolon
DECL|member|line
r_int
id|line
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
multiline_comment|/* # of fd on device */
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
multiline_comment|/* # of blocked opens */
DECL|member|session
r_int
id|session
suffix:semicolon
multiline_comment|/* Session of opening process */
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
multiline_comment|/* pgrp of opening process */
DECL|member|xmit_buf
r_int
r_char
op_star
id|xmit_buf
suffix:semicolon
DECL|member|xmit_head
r_int
id|xmit_head
suffix:semicolon
DECL|member|xmit_tail
r_int
id|xmit_tail
suffix:semicolon
DECL|member|xmit_cnt
r_int
id|xmit_cnt
suffix:semicolon
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
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
DECL|member|next_port
r_struct
id|async_struct
op_star
id|next_port
suffix:semicolon
multiline_comment|/* For the linked list */
DECL|member|prev_port
r_struct
id|async_struct
op_star
id|prev_port
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SERIAL_MAGIC
mdefine_line|#define SERIAL_MAGIC 0x5301
multiline_comment|/*&n; * The size of the serial xmit buffer is 1 page, or 4096 bytes&n; */
DECL|macro|SERIAL_XMIT_SIZE
mdefine_line|#define SERIAL_XMIT_SIZE 4096
multiline_comment|/*&n; * Events are used to schedule things to happen at timer-interrupt&n; * time, instead of at rs interrupt time.&n; */
DECL|macro|RS_EVENT_WRITE_WAKEUP
mdefine_line|#define RS_EVENT_WRITE_WAKEUP&t;0
DECL|macro|RS_EVENT_HANGUP
mdefine_line|#define RS_EVENT_HANGUP&t;&t;1
multiline_comment|/* Export to allow PCMCIA to use this - Dave Hinds */
r_extern
r_int
id|register_serial
c_func
(paren
r_struct
id|serial_struct
op_star
id|req
)paren
suffix:semicolon
r_extern
r_void
id|unregister_serial
c_func
(paren
r_int
id|line
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SERIAL_H */
eof
