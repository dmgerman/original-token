multiline_comment|/*&n; *  generic_serial.h&n; *&n; *  Copyright (C) 1998 R.E.Wolff@BitWizard.nl&n; *&n; *  written for the SX serial driver.&n; *     Contains the code that should be shared over all the serial drivers.&n; *&n; *  Version 0.1 -- December, 1998.&n; */
macro_line|#ifndef GENERIC_SERIAL_H
DECL|macro|GENERIC_SERIAL_H
mdefine_line|#define GENERIC_SERIAL_H
DECL|struct|real_driver
r_struct
id|real_driver
(brace
DECL|member|disable_tx_interrupts
r_void
(paren
op_star
id|disable_tx_interrupts
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|enable_tx_interrupts
r_void
(paren
op_star
id|enable_tx_interrupts
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|disable_rx_interrupts
r_void
(paren
op_star
id|disable_rx_interrupts
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|enable_rx_interrupts
r_void
(paren
op_star
id|enable_rx_interrupts
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|get_CD
r_int
(paren
op_star
id|get_CD
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|shutdown_port
r_void
(paren
op_star
id|shutdown_port
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|set_real_termios
r_void
(paren
op_star
id|set_real_termios
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|chars_in_buffer
r_int
(paren
op_star
id|chars_in_buffer
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|hungup
r_void
(paren
op_star
id|hungup
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|getserial
r_void
(paren
op_star
id|getserial
)paren
(paren
r_void
op_star
comma
r_struct
id|serial_struct
op_star
id|sp
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|gs_port
r_struct
id|gs_port
(brace
DECL|member|magic
r_int
id|magic
suffix:semicolon
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
multiline_comment|/*  struct semaphore        port_write_sem; */
DECL|member|flags
r_int
id|flags
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
id|wait_queue_head_t
id|open_wait
suffix:semicolon
DECL|member|close_wait
id|wait_queue_head_t
id|close_wait
suffix:semicolon
DECL|member|session
r_int
id|session
suffix:semicolon
DECL|member|pgrp
r_int
id|pgrp
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|member|blocked_open
r_int
id|blocked_open
suffix:semicolon
DECL|member|tty
r_struct
id|tty_struct
op_star
id|tty
suffix:semicolon
DECL|member|event
r_int
id|event
suffix:semicolon
DECL|member|closing_wait
r_int
r_int
id|closing_wait
suffix:semicolon
DECL|member|close_delay
r_int
id|close_delay
suffix:semicolon
DECL|member|rd
r_struct
id|real_driver
op_star
id|rd
suffix:semicolon
DECL|member|wakeup_chars
r_int
id|wakeup_chars
suffix:semicolon
DECL|member|baud_base
r_int
id|baud_base
suffix:semicolon
DECL|member|baud
r_int
id|baud
suffix:semicolon
DECL|member|custom_divisor
r_int
id|custom_divisor
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags */
multiline_comment|/* Warning: serial.h defines some ASYNC_ flags, they say they are &quot;only&quot;&n;   used in serial.c, but they are also used in all other serial drivers. &n;   Make sure they don&squot;t clash with these here... */
DECL|macro|GS_TX_INTEN
mdefine_line|#define GS_TX_INTEN      0x00800000
DECL|macro|GS_RX_INTEN
mdefine_line|#define GS_RX_INTEN      0x00400000
DECL|macro|GS_ACTIVE
mdefine_line|#define GS_ACTIVE        0x00200000
DECL|macro|GS_TYPE_NORMAL
mdefine_line|#define GS_TYPE_NORMAL   1
DECL|macro|GS_TYPE_CALLOUT
mdefine_line|#define GS_TYPE_CALLOUT  2
DECL|macro|GS_DEBUG_FLUSH
mdefine_line|#define GS_DEBUG_FLUSH   0x00000001
DECL|macro|GS_DEBUG_BTR
mdefine_line|#define GS_DEBUG_BTR     0x00000002
DECL|macro|GS_DEBUG_TERMIOS
mdefine_line|#define GS_DEBUG_TERMIOS 0x00000004
DECL|macro|GS_DEBUG_STUFF
mdefine_line|#define GS_DEBUG_STUFF   0x00000008
DECL|macro|GS_DEBUG_CLOSE
mdefine_line|#define GS_DEBUG_CLOSE   0x00000010
r_void
id|gs_put_char
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
r_char
id|ch
)paren
suffix:semicolon
r_int
id|gs_write
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_int
id|from_user
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
r_int
id|gs_write_room
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_int
id|gs_chars_in_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_flush_buffer
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_flush_chars
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_stop
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_start
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_hangup
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
)paren
suffix:semicolon
r_void
id|gs_do_softint
c_func
(paren
r_void
op_star
id|private_
)paren
suffix:semicolon
r_int
id|block_til_ready
c_func
(paren
r_void
op_star
id|port
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_void
id|gs_close
c_func
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|file
op_star
id|filp
)paren
suffix:semicolon
r_void
id|gs_set_termios
(paren
r_struct
id|tty_struct
op_star
id|tty
comma
r_struct
id|termios
op_star
id|old_termios
)paren
suffix:semicolon
r_int
id|gs_init_port
c_func
(paren
r_struct
id|gs_port
op_star
id|port
)paren
suffix:semicolon
r_int
id|gs_setserial
c_func
(paren
r_struct
id|gs_port
op_star
id|port
comma
r_struct
id|serial_struct
op_star
id|sp
)paren
suffix:semicolon
r_void
id|gs_getserial
c_func
(paren
r_struct
id|gs_port
op_star
id|port
comma
r_struct
id|serial_struct
op_star
id|sp
)paren
suffix:semicolon
r_extern
r_int
id|gs_debug
suffix:semicolon
macro_line|#endif
eof
