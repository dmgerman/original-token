multiline_comment|/*&n; *&t;$Id: io_hd64461.c,v 1.1 2000/06/10 21:45:18 yaegashi Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Typical I/O routines for HD64461 system.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hd64461.h&gt;
DECL|function|PORT2ADDR
r_static
id|__inline__
r_int
r_int
id|PORT2ADDR
c_func
(paren
r_int
r_int
id|port
)paren
(brace
multiline_comment|/* 16550A: HD64461 internal */
r_if
c_cond
(paren
l_int|0x3f8
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x3ff
)paren
r_return
id|CONFIG_HD64461_IOBASE
op_plus
l_int|0x8000
op_plus
(paren
(paren
id|port
op_minus
l_int|0x3f8
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|0x2f8
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x2ff
)paren
r_return
id|CONFIG_HD64461_IOBASE
op_plus
l_int|0x7000
op_plus
(paren
(paren
id|port
op_minus
l_int|0x2f8
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_HD64461_ENABLER
multiline_comment|/* NE2000: HD64461 PCMCIA channel 0 (I/O) */
r_if
c_cond
(paren
l_int|0x300
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x31f
)paren
r_return
l_int|0xba000000
op_plus
id|port
suffix:semicolon
multiline_comment|/* ide0: HD64461 PCMCIA channel 1 (memory) */
multiline_comment|/* On HP690, CF in slot 1 is configured as a memory card&n;&t;   device.  See CF+ and CompactFlash Specification for the&n;&t;   detail of CF&squot;s memory mapped addressing. */
r_if
c_cond
(paren
l_int|0x1f0
op_le
id|port
op_logical_and
id|port
op_le
l_int|0x1f7
)paren
r_return
l_int|0xb5000000
op_plus
id|port
suffix:semicolon
r_if
c_cond
(paren
id|port
op_eq
l_int|0x3f6
)paren
r_return
l_int|0xb50001fe
suffix:semicolon
macro_line|#endif
multiline_comment|/* ??? */
r_if
c_cond
(paren
id|port
OL
l_int|0x10000
)paren
r_return
l_int|0xa0000000
op_plus
id|port
suffix:semicolon
multiline_comment|/* HD64461 internal devices (0xb0000000) */
r_if
c_cond
(paren
id|port
OL
l_int|0x20000
)paren
r_return
id|CONFIG_HD64461_IOBASE
op_plus
id|port
op_minus
l_int|0x10000
suffix:semicolon
multiline_comment|/* PCMCIA channel 0, I/O (0xba000000) */
r_if
c_cond
(paren
id|port
OL
l_int|0x30000
)paren
r_return
l_int|0xba000000
op_plus
id|port
op_minus
l_int|0x20000
suffix:semicolon
multiline_comment|/* PCMCIA channel 1, memory (0xb5000000) */
r_if
c_cond
(paren
id|port
OL
l_int|0x40000
)paren
r_return
l_int|0xb5000000
op_plus
id|port
op_minus
l_int|0x30000
suffix:semicolon
multiline_comment|/* Whole physical address space (0xa0000000) */
r_return
l_int|0xa0000000
op_plus
(paren
id|port
op_amp
l_int|0x1fffffff
)paren
suffix:semicolon
)brace
DECL|function|delay
r_static
r_inline
r_void
id|delay
c_func
(paren
r_void
)paren
(brace
id|ctrl_inw
c_func
(paren
l_int|0xa0000000
)paren
suffix:semicolon
)brace
DECL|function|hd64461_inb
r_int
r_int
id|hd64461_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|hd64461_inb_p
r_int
r_int
id|hd64461_inb_p
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_int
r_int
id|v
op_assign
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
r_return
id|v
suffix:semicolon
)brace
DECL|function|hd64461_inw
r_int
r_int
id|hd64461_inw
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|hd64461_inl
r_int
r_int
id|hd64461_inl
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|hd64461_insb
r_void
id|hd64461_insb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_char
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|buf
op_increment
op_assign
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|hd64461_insw
r_void
id|hd64461_insw
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|buf
op_increment
op_assign
id|inw
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|hd64461_insl
r_void
id|hd64461_insl
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
op_star
id|buf
op_increment
op_assign
id|inl
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|hd64461_outb
r_void
id|hd64461_outb
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|hd64461_outb_p
r_void
id|hd64461_outb_p
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_char
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
id|delay
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|hd64461_outw
r_void
id|hd64461_outw
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|hd64461_outl
r_void
id|hd64461_outl
c_func
(paren
r_int
r_int
id|b
comma
r_int
r_int
id|port
)paren
(brace
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PORT2ADDR
c_func
(paren
id|port
)paren
op_assign
id|b
suffix:semicolon
)brace
DECL|function|hd64461_outsb
r_void
id|hd64461_outsb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_char
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|outb
c_func
(paren
op_star
id|buf
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|hd64461_outsw
r_void
id|hd64461_outsw
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|outw
c_func
(paren
op_star
id|buf
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
)brace
DECL|function|hd64461_outsl
r_void
id|hd64461_outsl
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_const
r_int
r_int
op_star
id|buf
op_assign
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
)paren
(brace
id|outl
c_func
(paren
op_star
id|buf
op_increment
comma
id|port
)paren
suffix:semicolon
)brace
)brace
eof
