multiline_comment|/* &n;        epia.c    (c) 1997  Grant R. Guenther &lt;grant@torque.net&gt;&n;                            Under the terms of the GNU public license.&n;&n;        epia.c is a low-level protocol driver for Shuttle Technologies &n;&t;EPIA parallel to IDE adapter chip.  This device is now obsolete&n;&t;and has been replaced with the EPAT chip, which is supported&n;&t;by epat.c, however, some devices based on EPIA are still&n;&t;available.&n;&n;*/
DECL|macro|EPIA_VERSION
mdefine_line|#define EPIA_VERSION      &quot;1.0&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
multiline_comment|/* mode codes:  0  nybble reads on port 1, 8-bit writes&n;                1  5/3 reads on ports 1 &amp; 2, 8-bit writes&n;                2  8-bit reads and writes&n;                3  8-bit EPP mode&n;&t;&t;4  16-bit EPP&n;&t;&t;5  32-bit EPP&n;*/
DECL|macro|j44
mdefine_line|#define j44(a,b)                (((a&gt;&gt;4)&amp;0x0f)+(b&amp;0xf0))
DECL|macro|j53
mdefine_line|#define j53(a,b)                (((a&gt;&gt;3)&amp;0x1f)+((b&lt;&lt;4)&amp;0xe0))
multiline_comment|/* cont =  0   IDE register file&n;   cont =  1   IDE control registers&n;*/
DECL|variable|cont_map
r_static
r_int
id|cont_map
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0x80
)brace
suffix:semicolon
DECL|function|epia_read_regr
r_static
r_int
id|epia_read_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
)paren
(brace
r_int
id|a
comma
id|b
comma
id|r
suffix:semicolon
id|regr
op_add_assign
id|cont_map
(braket
id|cont
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|r
op_assign
id|regr
op_xor
l_int|0x39
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
id|j44
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
r_case
l_int|1
suffix:colon
id|r
op_assign
id|regr
op_xor
l_int|0x31
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w0
c_func
(paren
id|r
op_amp
l_int|0x37
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|w0
c_func
(paren
id|r
op_or
l_int|0xf0
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
id|j53
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
id|r
op_assign
id|regr
op_xor
l_int|0x29
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0X21
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x23
)paren
suffix:semicolon
id|a
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
id|w3
c_func
(paren
id|regr
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
id|a
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|epia_write_regr
r_static
r_void
id|epia_write_regr
c_func
(paren
id|PIA
op_star
id|pi
comma
r_int
id|cont
comma
r_int
id|regr
comma
r_int
id|val
)paren
(brace
r_int
id|r
suffix:semicolon
id|regr
op_add_assign
id|cont_map
(braket
id|cont
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|r
op_assign
id|regr
op_xor
l_int|0x19
suffix:semicolon
id|w0
c_func
(paren
id|r
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w0
c_func
(paren
id|val
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_case
l_int|4
suffix:colon
r_case
l_int|5
suffix:colon
id|r
op_assign
id|regr
op_xor
l_int|0x40
suffix:semicolon
id|w3
c_func
(paren
id|r
)paren
suffix:semicolon
id|w4
c_func
(paren
id|val
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|macro|WR
mdefine_line|#define WR(r,v)         epia_write_regr(pi,0,r,v)
DECL|macro|RR
mdefine_line|#define RR(r)           (epia_read_regr(pi,0,r))
multiline_comment|/* The use of register 0x84 is entirely unclear - it seems to control&n;   some EPP counters ...  currently we know about 3 different block&n;   sizes:  the standard 512 byte reads and writes, 12 byte writes and &n;   2048 byte reads (the last two being used in the CDrom drivers.&n;*/
DECL|function|epia_connect
r_static
r_void
id|epia_connect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|pi-&gt;saved_r0
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|pi-&gt;saved_r2
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x50
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xc0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x30
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xa0
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pi-&gt;mode
op_ge
l_int|3
)paren
(brace
id|w0
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x82
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x26
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
)brace
id|WR
c_func
(paren
l_int|0x86
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|epia_disconnect
r_static
r_void
id|epia_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0x10
)paren
suffix:semicolon
id|w0
c_func
(paren
id|pi-&gt;saved_r0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|w0
c_func
(paren
id|pi-&gt;saved_r0
)paren
suffix:semicolon
id|w2
c_func
(paren
id|pi-&gt;saved_r2
)paren
suffix:semicolon
)brace
DECL|function|epia_read_block
r_static
r_void
id|epia_read_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|k
comma
id|ph
comma
id|a
comma
id|b
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|w0
c_func
(paren
l_int|0x81
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xc1
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|2
op_plus
id|ph
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|b
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|j44
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|w0
c_func
(paren
l_int|0x91
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x10
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x51
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xd1
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|a
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|r2
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|j53
c_func
(paren
id|a
comma
id|b
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w0
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w0
c_func
(paren
l_int|0x89
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x23
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x21
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|w2
c_func
(paren
l_int|0x24
op_plus
id|ph
)paren
suffix:semicolon
id|buf
(braket
id|k
)braket
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|count
OG
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|3
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
id|buf
(braket
id|k
)braket
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
id|count
OG
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|3
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|2
suffix:semicolon
id|k
op_increment
)paren
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
op_assign
id|r4w
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
id|count
OG
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|3
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x24
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|4
suffix:semicolon
id|k
op_increment
)paren
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
op_assign
id|r4l
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|epia_write_block
r_static
r_void
id|epia_write_block
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|ph
comma
id|k
comma
id|last
comma
id|d
suffix:semicolon
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
r_case
l_int|1
suffix:colon
r_case
l_int|2
suffix:colon
id|w0
c_func
(paren
l_int|0xa1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|ph
op_assign
l_int|0
suffix:semicolon
id|last
op_assign
l_int|0x8000
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
(brace
id|d
op_assign
id|buf
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|d
op_ne
id|last
)paren
(brace
id|last
op_assign
id|d
suffix:semicolon
id|w0
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|4
op_plus
id|ph
)paren
suffix:semicolon
id|ph
op_assign
l_int|1
op_minus
id|ph
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|1
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
suffix:semicolon
id|k
op_increment
)paren
id|w4
c_func
(paren
id|buf
(braket
id|k
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|1
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|2
suffix:semicolon
id|k
op_increment
)paren
id|w4w
c_func
(paren
(paren
(paren
id|u16
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|1
)paren
suffix:semicolon
id|w3
c_func
(paren
l_int|0x40
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|count
op_div
l_int|4
suffix:semicolon
id|k
op_increment
)paren
id|w4l
c_func
(paren
(paren
(paren
id|u32
op_star
)paren
id|buf
)paren
(braket
id|k
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|512
)paren
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|epia_test_proto
r_static
r_int
id|epia_test_proto
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|scratch
comma
r_int
id|verbose
)paren
(brace
r_int
id|j
comma
id|k
comma
id|f
suffix:semicolon
r_int
id|e
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
id|epia_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|WR
c_func
(paren
l_int|6
comma
l_int|0xa0
op_plus
id|j
op_star
l_int|0x10
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|256
suffix:semicolon
id|k
op_increment
)paren
(brace
id|WR
c_func
(paren
l_int|2
comma
id|k
op_xor
l_int|0xaa
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|3
comma
id|k
op_xor
l_int|0x55
)paren
suffix:semicolon
r_if
c_cond
(paren
id|RR
c_func
(paren
l_int|2
)paren
op_ne
(paren
id|k
op_xor
l_int|0xaa
)paren
)paren
id|e
(braket
id|j
)braket
op_increment
suffix:semicolon
)brace
)brace
id|epia_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|f
op_assign
l_int|0
suffix:semicolon
id|epia_connect
c_func
(paren
id|pi
)paren
suffix:semicolon
id|WR
c_func
(paren
l_int|0x84
comma
l_int|8
)paren
suffix:semicolon
id|epia_read_block
c_func
(paren
id|pi
comma
id|scratch
comma
l_int|512
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|256
suffix:semicolon
id|k
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|scratch
(braket
l_int|2
op_star
id|k
)braket
op_amp
l_int|0xff
)paren
op_ne
(paren
(paren
id|k
op_plus
l_int|1
)paren
op_amp
l_int|0xff
)paren
)paren
id|f
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|scratch
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
op_amp
l_int|0xff
)paren
op_ne
(paren
(paren
op_minus
l_int|2
op_minus
id|k
)paren
op_amp
l_int|0xff
)paren
)paren
id|f
op_increment
suffix:semicolon
)brace
id|WR
c_func
(paren
l_int|0x84
comma
l_int|0
)paren
suffix:semicolon
id|epia_disconnect
c_func
(paren
id|pi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verbose
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: epia: port 0x%x, mode %d, test=(%d,%d,%d)&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|pi-&gt;port
comma
id|pi-&gt;mode
comma
id|e
(braket
l_int|0
)braket
comma
id|e
(braket
l_int|1
)braket
comma
id|f
)paren
suffix:semicolon
)brace
r_return
(paren
id|e
(braket
l_int|0
)braket
op_logical_and
id|e
(braket
l_int|1
)braket
)paren
op_logical_or
id|f
suffix:semicolon
)brace
DECL|function|epia_log_adapter
r_static
r_void
id|epia_log_adapter
c_func
(paren
id|PIA
op_star
id|pi
comma
r_char
op_star
id|scratch
comma
r_int
id|verbose
)paren
(brace
r_char
op_star
id|mode_string
(braket
l_int|6
)braket
op_assign
(brace
l_string|&quot;4-bit&quot;
comma
l_string|&quot;5/3&quot;
comma
l_string|&quot;8-bit&quot;
comma
l_string|&quot;EPP-8&quot;
comma
l_string|&quot;EPP-16&quot;
comma
l_string|&quot;EPP-32&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: epia %s, Shuttle EPIA at 0x%x, &quot;
comma
id|pi-&gt;device
comma
id|EPIA_VERSION
comma
id|pi-&gt;port
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mode %d (%s), delay %d&bslash;n&quot;
comma
id|pi-&gt;mode
comma
id|mode_string
(braket
id|pi-&gt;mode
)braket
comma
id|pi-&gt;delay
)paren
suffix:semicolon
)brace
DECL|function|epia_inc_use
r_static
r_void
id|epia_inc_use
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|epia_dec_use
r_static
r_void
id|epia_dec_use
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|epia
r_struct
id|pi_protocol
id|epia
op_assign
(brace
l_string|&quot;epia&quot;
comma
l_int|0
comma
l_int|6
comma
l_int|3
comma
l_int|1
comma
l_int|1
comma
id|epia_write_regr
comma
id|epia_read_regr
comma
id|epia_write_block
comma
id|epia_read_block
comma
id|epia_connect
comma
id|epia_disconnect
comma
l_int|0
comma
l_int|0
comma
id|epia_test_proto
comma
id|epia_log_adapter
comma
id|epia_inc_use
comma
id|epia_dec_use
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|pi_register
c_func
(paren
op_amp
id|epia
)paren
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|pi_unregister
c_func
(paren
op_amp
id|epia
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of epia.c */
eof