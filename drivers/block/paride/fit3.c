multiline_comment|/* &n;        fit3.c        (c) 1998  Grant R. Guenther &lt;grant@torque.net&gt;&n;                          Under the terms of the GNU public license.&n;&n;&t;fit3.c is a low-level protocol driver for newer models &n;        of the Fidelity International Technology parallel port adapter.  &n;&t;This adapter is used in their TransDisk 3000 portable &n;&t;hard-drives, as well as CD-ROM, PD-CD and other devices.&n;&n;&t;The TD-2000 and certain older devices use a different protocol.&n;&t;Try the fit2 protocol module with them.&n;&n;        NB:  The FIT adapters do not appear to support the control &n;&t;registers.  So, we map ALT_STATUS to STATUS and NO-OP writes &n;&t;to the device control register - this means that IDE reset &n;&t;will not work on these devices.&n;&n;*/
DECL|macro|FIT3_VERSION
mdefine_line|#define FIT3_VERSION      &quot;1.0&quot;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;paride.h&quot;
DECL|macro|j44
mdefine_line|#define j44(a,b)                (((a&gt;&gt;3)&amp;0x0f)|((b&lt;&lt;1)&amp;0xf0))
DECL|macro|w7
mdefine_line|#define w7(byte)                {out_p(7,byte);}
DECL|macro|r7
mdefine_line|#define r7()                    (in_p(7) &amp; 0xff)
multiline_comment|/* cont = 0 - access the IDE register file &n;   cont = 1 - access the IDE command set &n;&n;*/
DECL|function|fit3_write_regr
r_static
r_void
id|fit3_write_regr
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
r_if
c_cond
(paren
id|cont
op_eq
l_int|1
)paren
r_return
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
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
l_int|0xd
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
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w4
c_func
(paren
id|val
)paren
suffix:semicolon
id|w4
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|fit3_read_regr
r_static
r_int
id|fit3_read_regr
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
suffix:semicolon
r_if
c_cond
(paren
id|cont
)paren
(brace
r_if
c_cond
(paren
id|regr
op_ne
l_int|6
)paren
r_return
l_int|0xff
suffix:semicolon
id|regr
op_assign
l_int|7
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|pi-&gt;mode
)paren
(brace
r_case
l_int|0
suffix:colon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x10
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
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
l_int|0xd
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
l_int|0xf
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
l_int|0xc
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
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x90
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
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
l_int|0xec
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xee
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xef
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
l_int|0xc
)paren
suffix:semicolon
r_return
id|a
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
id|regr
op_plus
l_int|0x90
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
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
l_int|0xec
)paren
suffix:semicolon
id|a
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|b
op_assign
id|r4
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
DECL|function|fit3_read_block
r_static
r_void
id|fit3_read_block
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
id|a
comma
id|b
comma
id|c
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
id|w2
c_func
(paren
l_int|0xc
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
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
(brace
id|w2
c_func
(paren
l_int|0xd
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
l_int|0xf
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
l_int|0xc
)paren
suffix:semicolon
id|c
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xe
)paren
suffix:semicolon
id|d
op_assign
id|r1
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
l_int|2
op_star
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
id|buf
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
op_assign
id|j44
c_func
(paren
id|c
comma
id|d
)paren
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x90
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
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
l_int|0xec
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xee
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
(brace
id|w2
c_func
(paren
l_int|0xef
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
l_int|0xee
)paren
suffix:semicolon
id|b
op_assign
id|r0
c_func
(paren
)paren
suffix:semicolon
id|buf
(braket
l_int|2
op_star
id|k
)braket
op_assign
id|a
suffix:semicolon
id|buf
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
op_assign
id|b
suffix:semicolon
)brace
id|w2
c_func
(paren
l_int|0xec
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x90
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
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
l_int|0xec
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
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|fit3_write_block
r_static
r_void
id|fit3_write_block
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
id|w2
c_func
(paren
l_int|0xc
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
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
(brace
id|w0
c_func
(paren
id|buf
(braket
l_int|2
op_star
id|k
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xd
)paren
suffix:semicolon
id|w0
c_func
(paren
id|buf
(braket
l_int|2
op_star
id|k
op_plus
l_int|1
)braket
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|w2
c_func
(paren
l_int|0xc
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
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|fit3_connect
r_static
r_void
id|fit3_connect
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
l_int|0xc
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
l_int|0xa
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pi-&gt;mode
op_eq
l_int|2
)paren
(brace
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0x9
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
)brace
)brace
DECL|function|fit3_disconnect
r_static
r_void
id|fit3_disconnect
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|w2
c_func
(paren
l_int|0xc
)paren
suffix:semicolon
id|w0
c_func
(paren
l_int|0xa
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0x8
)paren
suffix:semicolon
id|w2
c_func
(paren
l_int|0xc
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
DECL|function|fit3_log_adapter
r_static
r_void
id|fit3_log_adapter
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
l_int|3
)braket
op_assign
(brace
l_string|&quot;4-bit&quot;
comma
l_string|&quot;8-bit&quot;
comma
l_string|&quot;EPP&quot;
)brace
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: fit3 %s, FIT 3000 adapter at 0x%x, &quot;
l_string|&quot;mode %d (%s), delay %d&bslash;n&quot;
comma
id|pi-&gt;device
comma
id|FIT3_VERSION
comma
id|pi-&gt;port
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
DECL|function|fit3_init_proto
r_static
r_void
id|fit3_init_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|fit3_release_proto
r_static
r_void
id|fit3_release_proto
c_func
(paren
id|PIA
op_star
id|pi
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|fit3
r_struct
id|pi_protocol
id|fit3
op_assign
(brace
l_string|&quot;fit3&quot;
comma
l_int|0
comma
l_int|3
comma
l_int|2
comma
l_int|1
comma
l_int|1
comma
id|fit3_write_regr
comma
id|fit3_read_regr
comma
id|fit3_write_block
comma
id|fit3_read_block
comma
id|fit3_connect
comma
id|fit3_disconnect
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|fit3_log_adapter
comma
id|fit3_init_proto
comma
id|fit3_release_proto
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
id|fit3
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
id|fit3
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* end of fit3.c */
eof