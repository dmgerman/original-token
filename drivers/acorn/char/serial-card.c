multiline_comment|/*&n; * linux/arch/arm/drivers/char/serial-module.c&n; *&n; * Copyright (c) 1996 Russell King.&n; *&n; * A generic handler of serial expansion cards that use 16550s or&n; * the like.&n; *&n; * Definitions:&n; *  MY_PRODS&t;&t;Product numbers to identify this card by&n; *  MY_MANUS&t;&t;Manufacturer numbers to identify this card by&n; *  MY_NUMPORTS&t;&t;Number of ports per card&n; *  MY_BAUD_BASE&t;Baud base for the card&n; *  MY_INIT&t;&t;Initialisation routine name&n; *  MY_BASE_ADDRESS(ec)&t;Return base address for ports&n; *  MY_PORT_ADDRESS&n; *&t;(port,cardaddr)&t;Return address for port using base address&n; *&t;&t;&t;from above.&n; *&n; * Changelog:&n; *  30-07-1996&t;RMK&t;Created&n; *  22-04-1998&t;RMK&t;Removed old register_pre_init_serial&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/ecard.h&gt;
macro_line|#ifndef NUM_SERIALS
DECL|macro|NUM_SERIALS
mdefine_line|#define NUM_SERIALS&t;MY_NUMPORTS * MAX_ECARDS
macro_line|#endif
macro_line|#ifdef MODULE
DECL|variable|__serial_ports
r_static
r_int
id|__serial_ports
(braket
id|NUM_SERIALS
)braket
suffix:semicolon
DECL|variable|__serial_pcount
r_static
r_int
id|__serial_pcount
suffix:semicolon
DECL|variable|expcard
r_static
r_struct
id|expansion_card
op_star
id|expcard
(braket
id|MAX_ECARDS
)braket
suffix:semicolon
DECL|macro|ADD_ECARD
mdefine_line|#define ADD_ECARD(ec,card) expcard[(card)] = (ec)
DECL|macro|ADD_PORT
mdefine_line|#define ADD_PORT(port) __serial_ports[__serial_pcount++] = (port)
DECL|macro|MY_INIT
macro_line|#undef MY_INIT
DECL|macro|MY_INIT
mdefine_line|#define MY_INIT init_module
macro_line|#else
DECL|macro|ADD_ECARD
mdefine_line|#define ADD_ECARD(ec,card)
DECL|macro|ADD_PORT
mdefine_line|#define ADD_PORT(port)
macro_line|#endif
DECL|variable|serial_cids
r_static
r_const
id|card_ids
id|serial_cids
(braket
)braket
op_assign
(brace
id|MY_CARD_LIST
comma
(brace
l_int|0xffff
comma
l_int|0xffff
)brace
)brace
suffix:semicolon
DECL|function|serial_register_onedev
r_static
r_inline
r_int
id|serial_register_onedev
(paren
r_int
r_int
id|port
comma
r_int
id|irq
)paren
(brace
r_struct
id|serial_struct
id|req
suffix:semicolon
id|req.baud_base
op_assign
id|MY_BAUD_BASE
suffix:semicolon
id|req.irq
op_assign
id|irq
suffix:semicolon
id|req.port
op_assign
id|port
suffix:semicolon
r_return
id|register_serial
c_func
(paren
op_amp
id|req
)paren
suffix:semicolon
)brace
DECL|function|MY_INIT
r_int
id|MY_INIT
(paren
r_void
)paren
(brace
r_int
id|card
op_assign
l_int|0
suffix:semicolon
id|ecard_startfind
(paren
)paren
suffix:semicolon
r_do
(brace
r_struct
id|expansion_card
op_star
id|ec
suffix:semicolon
r_int
r_int
id|cardaddr
suffix:semicolon
r_int
id|port
suffix:semicolon
id|ec
op_assign
id|ecard_find
(paren
l_int|0
comma
id|serial_cids
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
r_break
suffix:semicolon
id|cardaddr
op_assign
id|MY_BASE_ADDRESS
c_func
(paren
id|ec
)paren
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
l_int|0
suffix:semicolon
id|port
OL
id|MY_NUMPORTS
suffix:semicolon
id|port
op_increment
)paren
(brace
r_int
id|line
suffix:semicolon
id|line
op_assign
id|serial_register_onedev
(paren
id|MY_PORT_ADDRESS
c_func
(paren
id|port
comma
id|cardaddr
)paren
comma
id|ec-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|line
OL
l_int|0
)paren
r_break
suffix:semicolon
id|ADD_PORT
c_func
(paren
id|line
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|port
)paren
(brace
id|ecard_claim
(paren
id|ec
)paren
suffix:semicolon
id|ADD_ECARD
c_func
(paren
id|ec
comma
id|card
)paren
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_increment
id|card
OL
id|MAX_ECARDS
)paren
suffix:semicolon
r_return
id|card
ques
c_cond
l_int|0
suffix:colon
op_minus
id|ENODEV
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|__serial_pcount
suffix:semicolon
id|i
op_increment
)paren
id|unregister_serial
(paren
id|__serial_ports
(braket
id|i
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_ECARDS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|expcard
(braket
id|i
)braket
)paren
id|ecard_release
(paren
id|expcard
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
eof