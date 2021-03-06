multiline_comment|/*&n; *&t;AX.25 release 037&n; *&n; *&t;This code REQUIRES 2.1.15 or higher/ NET3.038&n; *&n; *&t;This module:&n; *&t;&t;This module is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; *&n; *&t;Most of this code is based on the SDL diagrams published in the 7th&n; *&t;ARRL Computer Networking Conference papers. The diagrams have mistakes&n; *&t;in them, but are mostly correct. Before you modify the code could you&n; *&t;read the SDL diagrams as the code is not obvious and probably very&n; *&t;easy to break;&n; *&n; *&t;History&n; *&t;AX.25 036&t;Jonathan(G4KLX)&t;Split from ax25_subr.c.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;net/ax25.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
multiline_comment|/*&n; *&t;The null address is defined as a callsign of all spaces with an&n; *&t;SSID of zero.&n; */
DECL|variable|null_ax25_address
id|ax25_address
id|null_ax25_address
op_assign
(brace
(brace
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x40
comma
l_int|0x00
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;ax25 -&gt; ascii conversion&n; */
DECL|function|ax2asc
r_char
op_star
id|ax2asc
c_func
(paren
id|ax25_address
op_star
id|a
)paren
(brace
r_static
r_char
id|buf
(braket
l_int|11
)braket
suffix:semicolon
r_char
id|c
comma
op_star
id|s
suffix:semicolon
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
comma
id|s
op_assign
id|buf
suffix:semicolon
id|n
OL
l_int|6
suffix:semicolon
id|n
op_increment
)paren
(brace
id|c
op_assign
(paren
id|a-&gt;ax25_call
(braket
id|n
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x7F
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot; &squot;
)paren
op_star
id|s
op_increment
op_assign
id|c
suffix:semicolon
)brace
op_star
id|s
op_increment
op_assign
l_char|&squot;-&squot;
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
(paren
(paren
id|a-&gt;ax25_call
(braket
l_int|6
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|0x0F
)paren
)paren
OG
l_int|9
)paren
(brace
op_star
id|s
op_increment
op_assign
l_char|&squot;1&squot;
suffix:semicolon
id|n
op_sub_assign
l_int|10
suffix:semicolon
)brace
op_star
id|s
op_increment
op_assign
id|n
op_plus
l_char|&squot;0&squot;
suffix:semicolon
op_star
id|s
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|buf
op_eq
l_char|&squot;&bslash;0&squot;
op_logical_or
op_star
id|buf
op_eq
l_char|&squot;-&squot;
)paren
r_return
l_string|&quot;*&quot;
suffix:semicolon
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;ascii -&gt; ax25 conversion&n; */
DECL|function|asc2ax
id|ax25_address
op_star
id|asc2ax
c_func
(paren
r_char
op_star
id|callsign
)paren
(brace
r_static
id|ax25_address
id|addr
suffix:semicolon
r_char
op_star
id|s
suffix:semicolon
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|s
op_assign
id|callsign
comma
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|6
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
op_star
id|s
op_ne
l_char|&squot;-&squot;
)paren
id|addr.ax25_call
(braket
id|n
)braket
op_assign
op_star
id|s
op_increment
suffix:semicolon
r_else
id|addr.ax25_call
(braket
id|n
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|addr.ax25_call
(braket
id|n
)braket
op_lshift_assign
l_int|1
suffix:semicolon
id|addr.ax25_call
(braket
id|n
)braket
op_and_assign
l_int|0xFE
suffix:semicolon
)brace
r_if
c_cond
(paren
op_star
id|s
op_increment
op_eq
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|addr.ax25_call
(braket
l_int|6
)braket
op_assign
l_int|0x00
suffix:semicolon
r_return
op_amp
id|addr
suffix:semicolon
)brace
id|addr.ax25_call
(braket
l_int|6
)braket
op_assign
op_star
id|s
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|addr.ax25_call
(braket
l_int|6
)braket
op_mul_assign
l_int|10
suffix:semicolon
id|addr.ax25_call
(braket
l_int|6
)braket
op_add_assign
op_star
id|s
op_increment
op_minus
l_char|&squot;0&squot;
suffix:semicolon
)brace
id|addr.ax25_call
(braket
l_int|6
)braket
op_lshift_assign
l_int|1
suffix:semicolon
id|addr.ax25_call
(braket
l_int|6
)braket
op_and_assign
l_int|0x1E
suffix:semicolon
r_return
op_amp
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Compare two ax.25 addresses&n; */
DECL|function|ax25cmp
r_int
id|ax25cmp
c_func
(paren
id|ax25_address
op_star
id|a
comma
id|ax25_address
op_star
id|b
)paren
(brace
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|ct
OL
l_int|6
)paren
(brace
r_if
c_cond
(paren
(paren
id|a-&gt;ax25_call
(braket
id|ct
)braket
op_amp
l_int|0xFE
)paren
op_ne
(paren
id|b-&gt;ax25_call
(braket
id|ct
)braket
op_amp
l_int|0xFE
)paren
)paren
multiline_comment|/* Clean off repeater bits */
r_return
l_int|1
suffix:semicolon
id|ct
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|a-&gt;ax25_call
(braket
id|ct
)braket
op_amp
l_int|0x1E
)paren
op_eq
(paren
id|b-&gt;ax25_call
(braket
id|ct
)braket
op_amp
l_int|0x1E
)paren
)paren
multiline_comment|/* SSID without control bit */
r_return
l_int|0
suffix:semicolon
r_return
l_int|2
suffix:semicolon
multiline_comment|/* Partial match */
)brace
multiline_comment|/*&n; *&t;Compare two AX.25 digipeater paths.&n; */
DECL|function|ax25digicmp
r_int
id|ax25digicmp
c_func
(paren
id|ax25_digi
op_star
id|digi1
comma
id|ax25_digi
op_star
id|digi2
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|digi1-&gt;ndigi
op_ne
id|digi2-&gt;ndigi
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|digi1-&gt;lastrepeat
op_ne
id|digi2-&gt;lastrepeat
)paren
r_return
l_int|1
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
id|digi1-&gt;ndigi
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ax25cmp
c_func
(paren
op_amp
id|digi1-&gt;calls
(braket
id|i
)braket
comma
op_amp
id|digi2-&gt;calls
(braket
id|i
)braket
)paren
op_ne
l_int|0
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Given an AX.25 address pull of to, from, digi list, command/response and the start of data&n; *&n; */
DECL|function|ax25_addr_parse
r_int
r_char
op_star
id|ax25_addr_parse
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|len
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|digi
comma
r_int
op_star
id|flags
comma
r_int
op_star
id|dama
)paren
(brace
r_int
id|d
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|14
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_ne
l_int|NULL
)paren
(brace
op_star
id|flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|6
)braket
op_amp
id|AX25_CBIT
)paren
op_star
id|flags
op_assign
id|AX25_COMMAND
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|13
)braket
op_amp
id|AX25_CBIT
)paren
op_star
id|flags
op_assign
id|AX25_RESPONSE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dama
op_ne
l_int|NULL
)paren
op_star
id|dama
op_assign
op_complement
id|buf
(braket
l_int|13
)braket
op_amp
id|AX25_DAMA_FLAG
suffix:semicolon
multiline_comment|/* Copy to, from */
r_if
c_cond
(paren
id|dest
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|dest
comma
id|buf
op_plus
l_int|0
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|src
op_ne
l_int|NULL
)paren
id|memcpy
c_func
(paren
id|src
comma
id|buf
op_plus
l_int|7
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_sub_assign
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
id|digi-&gt;lastrepeat
op_assign
op_minus
l_int|1
suffix:semicolon
id|digi-&gt;ndigi
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
(paren
id|buf
(braket
op_minus
l_int|1
)braket
op_amp
id|AX25_EBIT
)paren
)paren
(brace
r_if
c_cond
(paren
id|d
op_ge
id|AX25_MAX_DIGIS
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Max of 6 digis */
r_if
c_cond
(paren
id|len
OL
l_int|7
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* Short packet */
id|memcpy
c_func
(paren
op_amp
id|digi-&gt;calls
(braket
id|d
)braket
comma
id|buf
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|digi-&gt;ndigi
op_assign
id|d
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
l_int|6
)braket
op_amp
id|AX25_HBIT
)paren
(brace
id|digi-&gt;repeated
(braket
id|d
)braket
op_assign
l_int|1
suffix:semicolon
id|digi-&gt;lastrepeat
op_assign
id|d
suffix:semicolon
)brace
r_else
(brace
id|digi-&gt;repeated
(braket
id|d
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_sub_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|d
op_increment
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Assemble an AX.25 header from the bits&n; */
DECL|function|ax25_addr_build
r_int
id|ax25_addr_build
c_func
(paren
r_int
r_char
op_star
id|buf
comma
id|ax25_address
op_star
id|src
comma
id|ax25_address
op_star
id|dest
comma
id|ax25_digi
op_star
id|d
comma
r_int
id|flag
comma
r_int
id|modulus
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|ct
op_assign
l_int|0
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|dest
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
(paren
id|AX25_EBIT
op_or
id|AX25_CBIT
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_eq
id|AX25_COMMAND
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_CBIT
suffix:semicolon
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|src
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
(paren
id|AX25_EBIT
op_or
id|AX25_CBIT
)paren
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_SSSID_SPARE
suffix:semicolon
r_if
c_cond
(paren
id|modulus
op_eq
id|AX25_MODULUS
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
r_else
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_ESSID_SPARE
suffix:semicolon
r_if
c_cond
(paren
id|flag
op_eq
id|AX25_RESPONSE
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_CBIT
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Fast path the normal digiless path&n;&t; */
r_if
c_cond
(paren
id|d
op_eq
l_int|NULL
op_logical_or
id|d-&gt;ndigi
op_eq
l_int|0
)paren
(brace
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
r_return
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
)brace
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
r_while
c_loop
(paren
id|ct
OL
id|d-&gt;ndigi
)paren
(brace
id|memcpy
c_func
(paren
id|buf
comma
op_amp
id|d-&gt;calls
(braket
id|ct
)braket
comma
id|AX25_ADDR_LEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;repeated
(braket
id|ct
)braket
)paren
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_HBIT
suffix:semicolon
r_else
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_HBIT
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_EBIT
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_or_assign
id|AX25_SSSID_SPARE
suffix:semicolon
id|buf
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|len
op_add_assign
id|AX25_ADDR_LEN
suffix:semicolon
id|ct
op_increment
suffix:semicolon
)brace
id|buf
(braket
op_minus
l_int|1
)braket
op_or_assign
id|AX25_EBIT
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|ax25_addr_size
r_int
id|ax25_addr_size
c_func
(paren
id|ax25_digi
op_star
id|dp
)paren
(brace
r_if
c_cond
(paren
id|dp
op_eq
l_int|NULL
)paren
r_return
l_int|2
op_star
id|AX25_ADDR_LEN
suffix:semicolon
r_return
id|AX25_ADDR_LEN
op_star
(paren
l_int|2
op_plus
id|dp-&gt;ndigi
)paren
suffix:semicolon
)brace
multiline_comment|/* &n; *&t;Reverse Digipeat List. May not pass both parameters as same struct&n; */
DECL|function|ax25_digi_invert
r_void
id|ax25_digi_invert
c_func
(paren
id|ax25_digi
op_star
id|in
comma
id|ax25_digi
op_star
id|out
)paren
(brace
r_int
id|ct
suffix:semicolon
id|out-&gt;ndigi
op_assign
id|in-&gt;ndigi
suffix:semicolon
id|out-&gt;lastrepeat
op_assign
id|in-&gt;ndigi
op_minus
id|in-&gt;lastrepeat
op_minus
l_int|2
suffix:semicolon
multiline_comment|/* Invert the digipeaters */
r_for
c_loop
(paren
id|ct
op_assign
l_int|0
suffix:semicolon
id|ct
OL
id|in-&gt;ndigi
suffix:semicolon
id|ct
op_increment
)paren
(brace
id|out-&gt;calls
(braket
id|ct
)braket
op_assign
id|in-&gt;calls
(braket
id|in-&gt;ndigi
op_minus
id|ct
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ct
op_le
id|out-&gt;lastrepeat
)paren
(brace
id|out-&gt;calls
(braket
id|ct
)braket
dot
id|ax25_call
(braket
l_int|6
)braket
op_or_assign
id|AX25_HBIT
suffix:semicolon
id|out-&gt;repeated
(braket
id|ct
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|out-&gt;calls
(braket
id|ct
)braket
dot
id|ax25_call
(braket
l_int|6
)braket
op_and_assign
op_complement
id|AX25_HBIT
suffix:semicolon
id|out-&gt;repeated
(braket
id|ct
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
eof
