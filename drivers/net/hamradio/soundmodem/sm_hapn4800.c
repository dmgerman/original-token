multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;sm_hapn4800.c  -- soundcard radio modem driver, 4800 baud HAPN modem&n; *&n; *&t;Copyright (C) 1996  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; *&n; *  This module implements a (hopefully) HAPN (Hamilton Area Packet&n; *  Network) compatible 4800 baud modem.&n; *  The HAPN modem uses kind of &quot;duobinary signalling&quot; (not really,&n; *  duobinary signalling gives ... 0 0 -1 0 1 0 0 ... at the sampling&n; *  instants, whereas HAPN signalling gives ... 0 0 -1 1 0 0 ..., see&n; *  Proakis, Digital Communications).&n; *  The code is untested. It is compatible with itself (i.e. it can decode&n; *  the packets it sent), but I could not test if it is compatible with&n; *  any &quot;real&quot; HAPN modem, since noone uses it in my region of the world.&n; *  Feedback therefore welcome.&n; */
macro_line|#include &quot;sm.h&quot;
macro_line|#include &quot;sm_tbl_hapn4800.h&quot;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|demod_state_hapn48
r_struct
id|demod_state_hapn48
(brace
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|member|bit_pll
r_int
r_int
id|bit_pll
suffix:semicolon
DECL|member|last_bit
r_int
r_char
id|last_bit
suffix:semicolon
DECL|member|last_bit2
r_int
r_char
id|last_bit2
suffix:semicolon
DECL|member|dcd_shreg
r_int
r_int
id|dcd_shreg
suffix:semicolon
DECL|member|dcd_sum0
DECL|member|dcd_sum1
DECL|member|dcd_sum2
r_int
id|dcd_sum0
comma
id|dcd_sum1
comma
id|dcd_sum2
suffix:semicolon
DECL|member|dcd_time
r_int
r_int
id|dcd_time
suffix:semicolon
DECL|member|lvlhi
DECL|member|lvllo
r_int
id|lvlhi
comma
id|lvllo
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_state_hapn48
r_struct
id|mod_state_hapn48
(brace
DECL|member|shreg
r_int
r_int
id|shreg
suffix:semicolon
DECL|member|tx_bit
r_int
r_char
id|tx_bit
suffix:semicolon
DECL|member|tx_seq
r_int
r_int
id|tx_seq
suffix:semicolon
DECL|member|tbl
r_const
r_int
r_char
op_star
id|tbl
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_10_u8
r_static
r_void
id|modulator_hapn4800_10_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_10
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|10
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
op_star
id|st-&gt;tbl
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_10_s16
r_static
r_void
id|modulator_hapn4800_10_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_10
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|10
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
(paren
(paren
op_star
id|st-&gt;tbl
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_8_u8
r_static
r_void
id|modulator_hapn4800_8_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_8
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|8
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
op_star
id|st-&gt;tbl
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_8_s16
r_static
r_void
id|modulator_hapn4800_8_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_8
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|8
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
(paren
(paren
op_star
id|st-&gt;tbl
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_pm10_u8
r_static
r_void
id|modulator_hapn4800_pm10_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_pm10
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|10
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
op_star
id|st-&gt;tbl
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_pm10_s16
r_static
r_void
id|modulator_hapn4800_pm10_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_pm10
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|10
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
(paren
(paren
op_star
id|st-&gt;tbl
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_pm8_u8
r_static
r_void
id|modulator_hapn4800_pm8_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_pm8
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|8
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
op_star
id|st-&gt;tbl
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_hapn4800_pm8_s16
r_static
r_void
id|modulator_hapn4800_pm8_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|mod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;m
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|st-&gt;tx_seq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|st-&gt;shreg
op_le
l_int|1
)paren
id|st-&gt;shreg
op_assign
id|hdlcdrv_getbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
op_or
l_int|0x10000
suffix:semicolon
id|st-&gt;tx_bit
op_assign
(paren
id|st-&gt;tx_bit
op_lshift
l_int|1
)paren
op_or
(paren
id|st-&gt;tx_bit
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;tx_bit
op_xor_assign
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;tbl
op_assign
id|hapn48_txfilt_pm8
op_plus
(paren
id|st-&gt;tx_bit
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;tx_seq
op_ge
l_int|8
)paren
id|st-&gt;tx_seq
op_assign
l_int|0
suffix:semicolon
op_star
id|buf
op_assign
(paren
(paren
op_star
id|st-&gt;tbl
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;tbl
op_add_assign
l_int|0x10
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_hapn4800_10_u8
r_static
r_void
id|demodulator_hapn4800_10_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_static
r_const
r_int
id|pll_corr
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|0x800
comma
l_int|0x800
)brace
suffix:semicolon
r_int
id|curst
comma
id|cursync
suffix:semicolon
r_int
id|inv
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|inv
op_assign
(paren
(paren
r_int
)paren
(paren
id|buf
(braket
op_minus
l_int|2
)braket
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;lvlhi
op_assign
(paren
id|st-&gt;lvlhi
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
id|st-&gt;lvllo
op_assign
(paren
id|st-&gt;lvllo
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
)paren
id|st-&gt;lvlhi
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
)paren
id|st-&gt;lvllo
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_amp
l_int|1
)paren
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x199a
suffix:semicolon
id|curst
op_assign
id|cursync
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
op_minus
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursync
)paren
(brace
id|st-&gt;dcd_shreg
op_or_assign
id|cursync
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
(paren
(paren
id|st-&gt;bit_pll
op_minus
l_int|0x8000u
)paren
op_amp
l_int|0xffffu
)paren
OL
l_int|0x8ccdu
)braket
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
l_int|16
op_star
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x18c6318c
)paren
op_minus
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0xe739ce70
)paren
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|cursync
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|st-&gt;dcd_time
)paren
op_le
l_int|0
)paren
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
(paren
id|st-&gt;dcd_sum0
op_plus
id|st-&gt;dcd_sum1
op_plus
id|st-&gt;dcd_sum2
)paren
OL
l_int|0
)paren
suffix:semicolon
id|st-&gt;dcd_sum2
op_assign
id|st-&gt;dcd_sum1
suffix:semicolon
id|st-&gt;dcd_sum1
op_assign
id|st-&gt;dcd_sum0
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* slight bias */
id|st-&gt;dcd_time
op_assign
l_int|240
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;bit_pll
op_ge
l_int|0x10000
)paren
(brace
id|st-&gt;bit_pll
op_and_assign
l_int|0xffff
suffix:semicolon
id|st-&gt;last_bit2
op_assign
id|st-&gt;last_bit
suffix:semicolon
r_if
c_cond
(paren
id|curst
OL
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|curst
OG
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
(paren
id|st-&gt;last_bit
op_xor
id|st-&gt;last_bit2
op_xor
l_int|1
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
(brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;shreg
op_rshift
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_assign
l_int|0x10000
suffix:semicolon
)brace
id|diag_trigger
c_func
(paren
id|sm
)paren
suffix:semicolon
)brace
id|diag_add_one
c_func
(paren
id|sm
comma
id|inv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_hapn4800_10_s16
r_static
r_void
id|demodulator_hapn4800_10_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_static
r_const
r_int
id|pll_corr
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|0x800
comma
l_int|0x800
)brace
suffix:semicolon
r_int
id|curst
comma
id|cursync
suffix:semicolon
r_int
id|inv
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|inv
op_assign
id|buf
(braket
op_minus
l_int|2
)braket
suffix:semicolon
id|st-&gt;lvlhi
op_assign
(paren
id|st-&gt;lvlhi
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
id|st-&gt;lvllo
op_assign
(paren
id|st-&gt;lvllo
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
)paren
id|st-&gt;lvlhi
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
)paren
id|st-&gt;lvllo
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_amp
l_int|1
)paren
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x199a
suffix:semicolon
id|curst
op_assign
id|cursync
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
op_minus
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursync
)paren
(brace
id|st-&gt;dcd_shreg
op_or_assign
id|cursync
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
(paren
(paren
id|st-&gt;bit_pll
op_minus
l_int|0x8000u
)paren
op_amp
l_int|0xffffu
)paren
OL
l_int|0x8ccdu
)braket
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
l_int|16
op_star
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x18c6318c
)paren
op_minus
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0xe739ce70
)paren
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|cursync
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|st-&gt;dcd_time
)paren
op_le
l_int|0
)paren
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
(paren
id|st-&gt;dcd_sum0
op_plus
id|st-&gt;dcd_sum1
op_plus
id|st-&gt;dcd_sum2
)paren
OL
l_int|0
)paren
suffix:semicolon
id|st-&gt;dcd_sum2
op_assign
id|st-&gt;dcd_sum1
suffix:semicolon
id|st-&gt;dcd_sum1
op_assign
id|st-&gt;dcd_sum0
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* slight bias */
id|st-&gt;dcd_time
op_assign
l_int|240
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;bit_pll
op_ge
l_int|0x10000
)paren
(brace
id|st-&gt;bit_pll
op_and_assign
l_int|0xffff
suffix:semicolon
id|st-&gt;last_bit2
op_assign
id|st-&gt;last_bit
suffix:semicolon
r_if
c_cond
(paren
id|curst
OL
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|curst
OG
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
(paren
id|st-&gt;last_bit
op_xor
id|st-&gt;last_bit2
op_xor
l_int|1
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
(brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;shreg
op_rshift
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_assign
l_int|0x10000
suffix:semicolon
)brace
id|diag_trigger
c_func
(paren
id|sm
)paren
suffix:semicolon
)brace
id|diag_add_one
c_func
(paren
id|sm
comma
id|inv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_hapn4800_8_u8
r_static
r_void
id|demodulator_hapn4800_8_u8
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_static
r_const
r_int
id|pll_corr
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|0x800
comma
l_int|0x800
)brace
suffix:semicolon
r_int
id|curst
comma
id|cursync
suffix:semicolon
r_int
id|inv
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|inv
op_assign
(paren
(paren
r_int
)paren
(paren
id|buf
(braket
op_minus
l_int|2
)braket
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
suffix:semicolon
id|st-&gt;lvlhi
op_assign
(paren
id|st-&gt;lvlhi
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
id|st-&gt;lvllo
op_assign
(paren
id|st-&gt;lvllo
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
)paren
id|st-&gt;lvlhi
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
)paren
id|st-&gt;lvllo
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_amp
l_int|1
)paren
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x2000
suffix:semicolon
id|curst
op_assign
id|cursync
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
op_minus
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursync
)paren
(brace
id|st-&gt;dcd_shreg
op_or_assign
id|cursync
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
(paren
(paren
id|st-&gt;bit_pll
op_minus
l_int|0x8000u
)paren
op_amp
l_int|0xffffu
)paren
OL
l_int|0x9000u
)braket
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
l_int|16
op_star
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x44444444
)paren
op_minus
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0xbbbbbbbb
)paren
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|cursync
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|st-&gt;dcd_time
)paren
op_le
l_int|0
)paren
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
(paren
id|st-&gt;dcd_sum0
op_plus
id|st-&gt;dcd_sum1
op_plus
id|st-&gt;dcd_sum2
)paren
OL
l_int|0
)paren
suffix:semicolon
id|st-&gt;dcd_sum2
op_assign
id|st-&gt;dcd_sum1
suffix:semicolon
id|st-&gt;dcd_sum1
op_assign
id|st-&gt;dcd_sum0
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* slight bias */
id|st-&gt;dcd_time
op_assign
l_int|240
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;bit_pll
op_ge
l_int|0x10000
)paren
(brace
id|st-&gt;bit_pll
op_and_assign
l_int|0xffff
suffix:semicolon
id|st-&gt;last_bit2
op_assign
id|st-&gt;last_bit
suffix:semicolon
r_if
c_cond
(paren
id|curst
OL
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|curst
OG
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
(paren
id|st-&gt;last_bit
op_xor
id|st-&gt;last_bit2
op_xor
l_int|1
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
(brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;shreg
op_rshift
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_assign
l_int|0x10000
suffix:semicolon
)brace
id|diag_trigger
c_func
(paren
id|sm
)paren
suffix:semicolon
)brace
id|diag_add_one
c_func
(paren
id|sm
comma
id|inv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_hapn4800_8_s16
r_static
r_void
id|demodulator_hapn4800_8_s16
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_const
r_int
op_star
id|buf
comma
r_int
r_int
id|buflen
)paren
(brace
r_struct
id|demod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_static
r_const
r_int
id|pll_corr
(braket
l_int|2
)braket
op_assign
(brace
op_minus
l_int|0x800
comma
l_int|0x800
)brace
suffix:semicolon
r_int
id|curst
comma
id|cursync
suffix:semicolon
r_int
id|inv
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|buflen
OG
l_int|0
suffix:semicolon
id|buflen
op_decrement
comma
id|buf
op_increment
)paren
(brace
id|inv
op_assign
id|buf
(braket
op_minus
l_int|2
)braket
suffix:semicolon
id|st-&gt;lvlhi
op_assign
(paren
id|st-&gt;lvlhi
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
id|st-&gt;lvllo
op_assign
(paren
id|st-&gt;lvllo
op_star
l_int|65309
)paren
op_rshift
l_int|16
suffix:semicolon
multiline_comment|/* decay */
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
)paren
id|st-&gt;lvlhi
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
)paren
id|st-&gt;lvllo
op_assign
id|inv
suffix:semicolon
r_if
c_cond
(paren
id|buflen
op_amp
l_int|1
)paren
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x2000
suffix:semicolon
id|curst
op_assign
id|cursync
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|inv
OG
id|st-&gt;lvlhi
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OG
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|inv
OL
id|st-&gt;lvllo
op_rshift
l_int|1
)paren
(brace
id|curst
op_assign
op_minus
l_int|1
suffix:semicolon
id|cursync
op_assign
(paren
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|1
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|3
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|0
)braket
op_logical_and
id|buf
(braket
op_minus
l_int|2
)braket
OL
id|buf
(braket
op_minus
l_int|4
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cursync
)paren
(brace
id|st-&gt;dcd_shreg
op_or_assign
id|cursync
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
(paren
(paren
id|st-&gt;bit_pll
op_minus
l_int|0x8000u
)paren
op_amp
l_int|0xffffu
)paren
OL
l_int|0x9000u
)braket
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
l_int|16
op_star
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x44444444
)paren
op_minus
id|hweight32
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0xbbbbbbbb
)paren
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|cursync
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_decrement
id|st-&gt;dcd_time
)paren
op_le
l_int|0
)paren
(brace
id|hdlcdrv_setdcd
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
(paren
id|st-&gt;dcd_sum0
op_plus
id|st-&gt;dcd_sum1
op_plus
id|st-&gt;dcd_sum2
)paren
OL
l_int|0
)paren
suffix:semicolon
id|st-&gt;dcd_sum2
op_assign
id|st-&gt;dcd_sum1
suffix:semicolon
id|st-&gt;dcd_sum1
op_assign
id|st-&gt;dcd_sum0
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* slight bias */
id|st-&gt;dcd_time
op_assign
l_int|240
suffix:semicolon
)brace
r_if
c_cond
(paren
id|st-&gt;bit_pll
op_ge
l_int|0x10000
)paren
(brace
id|st-&gt;bit_pll
op_and_assign
l_int|0xffff
suffix:semicolon
id|st-&gt;last_bit2
op_assign
id|st-&gt;last_bit
suffix:semicolon
r_if
c_cond
(paren
id|curst
OL
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|curst
OG
l_int|0
)paren
id|st-&gt;last_bit
op_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
(paren
id|st-&gt;last_bit
op_xor
id|st-&gt;last_bit2
op_xor
l_int|1
)paren
op_amp
l_int|1
)paren
op_lshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
(brace
id|hdlcdrv_putbits
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;shreg
op_rshift
l_int|1
)paren
suffix:semicolon
id|st-&gt;shreg
op_assign
l_int|0x10000
suffix:semicolon
)brace
id|diag_trigger
c_func
(paren
id|sm
)paren
suffix:semicolon
)brace
id|diag_add_one
c_func
(paren
id|sm
comma
id|inv
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demod_init_hapn4800
r_static
r_void
id|demod_init_hapn4800
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
r_struct
id|demod_state_hapn48
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_hapn48
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
id|st-&gt;dcd_time
op_assign
l_int|120
suffix:semicolon
id|st-&gt;dcd_sum0
op_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_hapn4800_8_tx
r_const
r_struct
id|modem_tx_info
id|sm_hapn4800_8_tx
op_assign
(brace
l_string|&quot;hapn4800&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_hapn48
)paren
comma
l_int|38400
comma
l_int|4800
comma
id|modulator_hapn4800_8_u8
comma
id|modulator_hapn4800_8_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_hapn4800_8_rx
r_const
r_struct
id|modem_rx_info
id|sm_hapn4800_8_rx
op_assign
(brace
l_string|&quot;hapn4800&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_hapn48
)paren
comma
l_int|38400
comma
l_int|4800
comma
l_int|5
comma
l_int|8
comma
id|demodulator_hapn4800_8_u8
comma
id|demodulator_hapn4800_8_s16
comma
id|demod_init_hapn4800
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_hapn4800_10_tx
r_const
r_struct
id|modem_tx_info
id|sm_hapn4800_10_tx
op_assign
(brace
l_string|&quot;hapn4800&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_hapn48
)paren
comma
l_int|48000
comma
l_int|4800
comma
id|modulator_hapn4800_10_u8
comma
id|modulator_hapn4800_10_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_hapn4800_10_rx
r_const
r_struct
id|modem_rx_info
id|sm_hapn4800_10_rx
op_assign
(brace
l_string|&quot;hapn4800&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_hapn48
)paren
comma
l_int|48000
comma
l_int|4800
comma
l_int|5
comma
l_int|10
comma
id|demodulator_hapn4800_10_u8
comma
id|demodulator_hapn4800_10_s16
comma
id|demod_init_hapn4800
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_hapn4800_pm8_tx
r_const
r_struct
id|modem_tx_info
id|sm_hapn4800_pm8_tx
op_assign
(brace
l_string|&quot;hapn4800pm&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_hapn48
)paren
comma
l_int|38400
comma
l_int|4800
comma
id|modulator_hapn4800_pm8_u8
comma
id|modulator_hapn4800_pm8_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_hapn4800_pm8_rx
r_const
r_struct
id|modem_rx_info
id|sm_hapn4800_pm8_rx
op_assign
(brace
l_string|&quot;hapn4800pm&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_hapn48
)paren
comma
l_int|38400
comma
l_int|4800
comma
l_int|5
comma
l_int|8
comma
id|demodulator_hapn4800_8_u8
comma
id|demodulator_hapn4800_8_s16
comma
id|demod_init_hapn4800
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|sm_hapn4800_pm10_tx
r_const
r_struct
id|modem_tx_info
id|sm_hapn4800_pm10_tx
op_assign
(brace
l_string|&quot;hapn4800pm&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_hapn48
)paren
comma
l_int|48000
comma
l_int|4800
comma
id|modulator_hapn4800_pm10_u8
comma
id|modulator_hapn4800_pm10_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_hapn4800_pm10_rx
r_const
r_struct
id|modem_rx_info
id|sm_hapn4800_pm10_rx
op_assign
(brace
l_string|&quot;hapn4800pm&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_hapn48
)paren
comma
l_int|48000
comma
l_int|4800
comma
l_int|5
comma
l_int|10
comma
id|demodulator_hapn4800_10_u8
comma
id|demodulator_hapn4800_10_s16
comma
id|demod_init_hapn4800
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
eof