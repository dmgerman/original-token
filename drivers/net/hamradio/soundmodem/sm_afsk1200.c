multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;sm_afsk1200.c  -- soundcard radio modem driver, 1200 baud AFSK modem&n; *&n; *&t;Copyright (C) 1996  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; */
macro_line|#include &quot;sm.h&quot;
macro_line|#include &quot;sm_tbl_afsk1200.h&quot;
multiline_comment|/* --------------------------------------------------------------------- */
DECL|struct|demod_state_afsk12
r_struct
id|demod_state_afsk12
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
DECL|member|last_sample
r_int
r_char
id|last_sample
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
DECL|member|last_rxbit
r_int
r_char
id|last_rxbit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mod_state_afsk12
r_struct
id|mod_state_afsk12
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
DECL|member|bit_pll
r_int
r_int
id|bit_pll
suffix:semicolon
DECL|member|dds_inc
r_int
r_int
id|dds_inc
suffix:semicolon
DECL|member|txphase
r_int
r_int
id|txphase
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|dds_inc
r_static
r_const
r_int
id|dds_inc
(braket
l_int|2
)braket
op_assign
(brace
id|AFSK12_TX_FREQ_LO
op_star
l_int|0x10000
op_div
id|AFSK12_SAMPLE_RATE
comma
id|AFSK12_TX_FREQ_HI
op_star
l_int|0x10000
op_div
id|AFSK12_SAMPLE_RATE
)brace
suffix:semicolon
DECL|function|modulator_1200_u8
r_static
r_void
id|modulator_1200_u8
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
id|mod_state_afsk12
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk12
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|st-&gt;txphase
op_increment
)paren
op_amp
l_int|7
)paren
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
op_xor
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
)paren
op_amp
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|st-&gt;dds_inc
op_assign
id|dds_inc
(braket
id|st-&gt;tx_bit
op_amp
l_int|1
)braket
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|OFFSCOS
c_func
(paren
id|st-&gt;bit_pll
)paren
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|st-&gt;dds_inc
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|modulator_1200_s16
r_static
r_void
id|modulator_1200_s16
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
id|mod_state_afsk12
op_star
id|st
op_assign
(paren
r_struct
id|mod_state_afsk12
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
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|st-&gt;txphase
op_increment
)paren
op_amp
l_int|7
)paren
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
op_xor
(paren
op_logical_neg
(paren
id|st-&gt;shreg
op_amp
l_int|1
)paren
)paren
)paren
op_amp
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
)brace
id|st-&gt;dds_inc
op_assign
id|dds_inc
(braket
id|st-&gt;tx_bit
op_amp
l_int|1
)braket
suffix:semicolon
op_star
id|buf
op_increment
op_assign
id|COS
c_func
(paren
id|st-&gt;bit_pll
)paren
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|st-&gt;dds_inc
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|convolution8_u8
r_extern
id|__inline__
r_int
id|convolution8_u8
c_func
(paren
r_const
r_int
r_char
op_star
id|st
comma
r_const
r_int
op_star
id|coeff
comma
r_int
id|csum
)paren
(brace
r_int
id|sum
op_assign
op_minus
l_int|0x80
op_star
id|csum
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
l_int|0
)braket
op_star
id|coeff
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|1
)braket
op_star
id|coeff
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|2
)braket
op_star
id|coeff
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|3
)braket
op_star
id|coeff
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|4
)braket
op_star
id|coeff
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|5
)braket
op_star
id|coeff
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|6
)braket
op_star
id|coeff
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|7
)braket
op_star
id|coeff
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|sum
op_rshift_assign
l_int|7
suffix:semicolon
r_return
id|sum
op_star
id|sum
suffix:semicolon
)brace
DECL|function|convolution8_s16
r_extern
id|__inline__
r_int
id|convolution8_s16
c_func
(paren
r_const
r_int
op_star
id|st
comma
r_const
r_int
op_star
id|coeff
comma
r_int
id|csum
)paren
(brace
r_int
id|sum
op_assign
l_int|0
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
l_int|0
)braket
op_star
id|coeff
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|1
)braket
op_star
id|coeff
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|2
)braket
op_star
id|coeff
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|3
)braket
op_star
id|coeff
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|4
)braket
op_star
id|coeff
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|5
)braket
op_star
id|coeff
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|6
)braket
op_star
id|coeff
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|sum
op_add_assign
(paren
id|st
(braket
op_minus
l_int|7
)braket
op_star
id|coeff
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|sum
op_rshift_assign
l_int|15
suffix:semicolon
r_return
id|sum
op_star
id|sum
suffix:semicolon
)brace
DECL|function|do_filter_1200_u8
r_extern
id|__inline__
r_int
id|do_filter_1200_u8
c_func
(paren
r_const
r_int
r_char
op_star
id|buf
)paren
(brace
r_int
id|sum
op_assign
id|convolution8_u8
c_func
(paren
id|buf
comma
id|afsk12_tx_lo_i
comma
id|SUM_AFSK12_TX_LO_I
)paren
suffix:semicolon
id|sum
op_add_assign
id|convolution8_u8
c_func
(paren
id|buf
comma
id|afsk12_tx_lo_q
comma
id|SUM_AFSK12_TX_LO_Q
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution8_u8
c_func
(paren
id|buf
comma
id|afsk12_tx_hi_i
comma
id|SUM_AFSK12_TX_HI_I
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution8_u8
c_func
(paren
id|buf
comma
id|afsk12_tx_hi_q
comma
id|SUM_AFSK12_TX_HI_Q
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
DECL|function|do_filter_1200_s16
r_extern
id|__inline__
r_int
id|do_filter_1200_s16
c_func
(paren
r_const
r_int
op_star
id|buf
)paren
(brace
r_int
id|sum
op_assign
id|convolution8_s16
c_func
(paren
id|buf
comma
id|afsk12_tx_lo_i
comma
id|SUM_AFSK12_TX_LO_I
)paren
suffix:semicolon
id|sum
op_add_assign
id|convolution8_s16
c_func
(paren
id|buf
comma
id|afsk12_tx_lo_q
comma
id|SUM_AFSK12_TX_LO_Q
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution8_s16
c_func
(paren
id|buf
comma
id|afsk12_tx_hi_i
comma
id|SUM_AFSK12_TX_HI_I
)paren
suffix:semicolon
id|sum
op_sub_assign
id|convolution8_s16
c_func
(paren
id|buf
comma
id|afsk12_tx_hi_q
comma
id|SUM_AFSK12_TX_HI_Q
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|variable|pll_corr
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
l_int|0x1000
comma
l_int|0x1000
)brace
suffix:semicolon
DECL|function|demodulator_1200_u8
r_static
r_void
id|demodulator_1200_u8
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
id|demod_state_afsk12
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk12
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|sum
suffix:semicolon
r_int
r_char
id|newsample
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
id|sum
op_assign
id|do_filter_1200_u8
c_func
(paren
id|buf
)paren
suffix:semicolon
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x2000
suffix:semicolon
id|newsample
op_assign
(paren
id|sum
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;last_sample
op_xor
id|newsample
)paren
(brace
id|st-&gt;last_sample
op_assign
id|newsample
suffix:semicolon
id|st-&gt;dcd_shreg
op_or_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
id|st-&gt;bit_pll
OL
l_int|0x9000
)braket
suffix:semicolon
id|j
op_assign
l_int|4
op_star
id|hweight8
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x38
)paren
op_minus
id|hweight16
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x7c0
)paren
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
id|j
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;last_sample
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
l_int|120
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
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
op_logical_neg
(paren
id|st-&gt;last_rxbit
op_xor
id|st-&gt;last_sample
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|st-&gt;last_rxbit
op_assign
id|st-&gt;last_sample
suffix:semicolon
id|diag_trigger
c_func
(paren
id|sm
)paren
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
)brace
id|diag_add
c_func
(paren
id|sm
comma
(paren
(paren
(paren
r_int
)paren
op_star
id|buf
)paren
op_minus
l_int|0x80
)paren
op_lshift
l_int|8
comma
id|sum
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demodulator_1200_s16
r_static
r_void
id|demodulator_1200_s16
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
id|demod_state_afsk12
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk12
op_star
)paren
(paren
op_amp
id|sm-&gt;d
)paren
suffix:semicolon
r_int
id|j
suffix:semicolon
r_int
id|sum
suffix:semicolon
r_int
r_char
id|newsample
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
id|sum
op_assign
id|do_filter_1200_s16
c_func
(paren
id|buf
)paren
suffix:semicolon
id|st-&gt;dcd_shreg
op_lshift_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
l_int|0x2000
suffix:semicolon
id|newsample
op_assign
(paren
id|sum
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|st-&gt;last_sample
op_xor
id|newsample
)paren
(brace
id|st-&gt;last_sample
op_assign
id|newsample
suffix:semicolon
id|st-&gt;dcd_shreg
op_or_assign
l_int|1
suffix:semicolon
id|st-&gt;bit_pll
op_add_assign
id|pll_corr
(braket
id|st-&gt;bit_pll
OL
l_int|0x9000
)braket
suffix:semicolon
id|j
op_assign
l_int|4
op_star
id|hweight8
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x38
)paren
op_minus
id|hweight16
c_func
(paren
id|st-&gt;dcd_shreg
op_amp
l_int|0x7c0
)paren
suffix:semicolon
id|st-&gt;dcd_sum0
op_add_assign
id|j
suffix:semicolon
)brace
id|hdlcdrv_channelbit
c_func
(paren
op_amp
id|sm-&gt;hdrv
comma
id|st-&gt;last_sample
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
l_int|120
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
id|st-&gt;shreg
op_rshift_assign
l_int|1
suffix:semicolon
id|st-&gt;shreg
op_or_assign
(paren
op_logical_neg
(paren
id|st-&gt;last_rxbit
op_xor
id|st-&gt;last_sample
)paren
)paren
op_lshift
l_int|16
suffix:semicolon
id|st-&gt;last_rxbit
op_assign
id|st-&gt;last_sample
suffix:semicolon
id|diag_trigger
c_func
(paren
id|sm
)paren
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
)brace
id|diag_add
c_func
(paren
id|sm
comma
op_star
id|buf
comma
id|sum
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|demod_init_1200
r_static
r_void
id|demod_init_1200
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
r_struct
id|demod_state_afsk12
op_star
id|st
op_assign
(paren
r_struct
id|demod_state_afsk12
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
DECL|variable|sm_afsk1200_tx
r_const
r_struct
id|modem_tx_info
id|sm_afsk1200_tx
op_assign
(brace
l_string|&quot;afsk1200&quot;
comma
r_sizeof
(paren
r_struct
id|mod_state_afsk12
)paren
comma
id|AFSK12_SAMPLE_RATE
comma
l_int|1200
comma
id|modulator_1200_u8
comma
id|modulator_1200_s16
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|sm_afsk1200_rx
r_const
r_struct
id|modem_rx_info
id|sm_afsk1200_rx
op_assign
(brace
l_string|&quot;afsk1200&quot;
comma
r_sizeof
(paren
r_struct
id|demod_state_afsk12
)paren
comma
id|AFSK12_SAMPLE_RATE
comma
l_int|1200
comma
l_int|8
comma
id|AFSK12_SAMPLE_RATE
op_div
l_int|1200
comma
id|demodulator_1200_u8
comma
id|demodulator_1200_s16
comma
id|demod_init_1200
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------- */
eof