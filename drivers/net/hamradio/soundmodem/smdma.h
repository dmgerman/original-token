multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&t;smdma.h  --  soundcard radio modem driver dma buffer routines.&n; *&n; *&t;Copyright (C) 1996  Thomas Sailer (sailer@ife.ee.ethz.ch)&n; *&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2 of the License, or&n; *&t;(at your option) any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; *  Please note that the GPL allows you to use the driver, NOT the radio.&n; *  In order to use the radio, you need a license from the communications&n; *  authority of your country.&n; *&n; */
macro_line|#ifndef _SMDMA_H
DECL|macro|_SMDMA_H
mdefine_line|#define _SMDMA_H
multiline_comment|/* ---------------------------------------------------------------------- */
macro_line|#include &quot;sm.h&quot;
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|macro|DMA_MODE_AUTOINIT
mdefine_line|#define DMA_MODE_AUTOINIT      0x10
DECL|macro|NUM_FRAGMENTS
mdefine_line|#define NUM_FRAGMENTS          4
multiline_comment|/*&n; * NOTE: make sure that hdlcdrv_hdlcbuffer contains enough space&n; * for the modulator to fill the whole DMA buffer without underrun&n; * at the highest possible baud rate, otherwise the TX state machine will&n; * not work correctly. That is (9k6 FSK): HDLCDRV_HDLCBUFFER &gt; 6*NUM_FRAGMENTS&n; */
multiline_comment|/* --------------------------------------------------------------------- */
multiline_comment|/*&n; * ===================== DMA buffer management ===========================&n; */
multiline_comment|/*&n; * returns the number of samples per fragment&n; */
DECL|function|dma_setup
r_extern
id|__inline__
r_int
r_int
id|dma_setup
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
id|send
comma
r_int
r_int
id|dmanr
)paren
(brace
r_if
c_cond
(paren
id|send
)paren
(brace
id|disable_dma
c_func
(paren
id|dmanr
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|dmanr
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|dmanr
comma
id|DMA_MODE_WRITE
op_or
id|DMA_MODE_AUTOINIT
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|dmanr
comma
id|virt_to_bus
c_func
(paren
id|sm-&gt;dma.obuf
)paren
)paren
suffix:semicolon
id|set_dma_count
c_func
(paren
id|dmanr
comma
id|sm-&gt;dma.ofragsz
op_star
id|NUM_FRAGMENTS
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|dmanr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.o16bit
)paren
r_return
id|sm-&gt;dma.ofragsz
op_div
l_int|2
suffix:semicolon
r_return
id|sm-&gt;dma.ofragsz
suffix:semicolon
)brace
r_else
(brace
id|disable_dma
c_func
(paren
id|dmanr
)paren
suffix:semicolon
id|clear_dma_ff
c_func
(paren
id|dmanr
)paren
suffix:semicolon
id|set_dma_mode
c_func
(paren
id|dmanr
comma
id|DMA_MODE_READ
op_or
id|DMA_MODE_AUTOINIT
)paren
suffix:semicolon
id|set_dma_addr
c_func
(paren
id|dmanr
comma
id|virt_to_bus
c_func
(paren
id|sm-&gt;dma.ibuf
)paren
)paren
suffix:semicolon
id|set_dma_count
c_func
(paren
id|dmanr
comma
id|sm-&gt;dma.ifragsz
op_star
id|NUM_FRAGMENTS
)paren
suffix:semicolon
id|enable_dma
c_func
(paren
id|dmanr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.i16bit
)paren
r_return
id|sm-&gt;dma.ifragsz
op_div
l_int|2
suffix:semicolon
r_return
id|sm-&gt;dma.ifragsz
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|dma_ptr
r_extern
id|__inline__
r_int
r_int
id|dma_ptr
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
id|send
comma
r_int
r_int
id|dmanr
comma
r_int
r_int
op_star
id|curfrag
)paren
(brace
r_int
r_int
id|dmaptr
comma
id|sz
comma
id|frg
comma
id|offs
suffix:semicolon
id|dmaptr
op_assign
id|get_dma_residue
c_func
(paren
id|dmanr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|send
)paren
(brace
id|sz
op_assign
id|sm-&gt;dma.ofragsz
op_star
id|NUM_FRAGMENTS
suffix:semicolon
r_if
c_cond
(paren
id|dmaptr
op_eq
l_int|0
op_logical_or
id|dmaptr
OG
id|sz
)paren
id|dmaptr
op_assign
id|sz
suffix:semicolon
id|dmaptr
op_decrement
suffix:semicolon
id|frg
op_assign
id|dmaptr
op_div
id|sm-&gt;dma.ofragsz
suffix:semicolon
id|offs
op_assign
(paren
id|dmaptr
op_mod
id|sm-&gt;dma.ofragsz
)paren
op_plus
l_int|1
suffix:semicolon
op_star
id|curfrag
op_assign
id|NUM_FRAGMENTS
op_minus
l_int|1
op_minus
id|frg
suffix:semicolon
macro_line|#ifdef SM_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|sm-&gt;debug_vals.dma_residue
op_logical_or
id|offs
OL
id|sm-&gt;debug_vals.dma_residue
)paren
id|sm-&gt;debug_vals.dma_residue
op_assign
id|offs
suffix:semicolon
macro_line|#endif /* SM_DEBUG */
r_if
c_cond
(paren
id|sm-&gt;dma.o16bit
)paren
r_return
id|offs
op_div
l_int|2
suffix:semicolon
r_return
id|offs
suffix:semicolon
)brace
r_else
(brace
id|sz
op_assign
id|sm-&gt;dma.ifragsz
op_star
id|NUM_FRAGMENTS
suffix:semicolon
r_if
c_cond
(paren
id|dmaptr
op_eq
l_int|0
op_logical_or
id|dmaptr
OG
id|sz
)paren
id|dmaptr
op_assign
id|sz
suffix:semicolon
id|dmaptr
op_decrement
suffix:semicolon
id|frg
op_assign
id|dmaptr
op_div
id|sm-&gt;dma.ifragsz
suffix:semicolon
id|offs
op_assign
(paren
id|dmaptr
op_mod
id|sm-&gt;dma.ifragsz
)paren
op_plus
l_int|1
suffix:semicolon
op_star
id|curfrag
op_assign
id|NUM_FRAGMENTS
op_minus
l_int|1
op_minus
id|frg
suffix:semicolon
macro_line|#ifdef SM_DEBUG
r_if
c_cond
(paren
op_logical_neg
id|sm-&gt;debug_vals.dma_residue
op_logical_or
id|offs
OL
id|sm-&gt;debug_vals.dma_residue
)paren
id|sm-&gt;debug_vals.dma_residue
op_assign
id|offs
suffix:semicolon
macro_line|#endif /* SM_DEBUG */
r_if
c_cond
(paren
id|sm-&gt;dma.i16bit
)paren
r_return
id|offs
op_div
l_int|2
suffix:semicolon
r_return
id|offs
suffix:semicolon
)brace
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|dma_end_transmit
r_extern
id|__inline__
r_int
id|dma_end_transmit
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_int
id|curfrag
)paren
(brace
r_int
r_int
id|diff
op_assign
(paren
id|NUM_FRAGMENTS
op_plus
id|curfrag
op_minus
id|sm-&gt;dma.ofragptr
)paren
op_mod
id|NUM_FRAGMENTS
suffix:semicolon
id|sm-&gt;dma.ofragptr
op_assign
id|curfrag
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.ptt_cnt
op_le
l_int|0
)paren
(brace
id|sm-&gt;dma.ptt_cnt
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|sm-&gt;dma.ptt_cnt
op_sub_assign
id|diff
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.ptt_cnt
op_le
l_int|0
)paren
(brace
id|sm-&gt;dma.ptt_cnt
op_assign
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_transmit
r_extern
id|__inline__
r_void
id|dma_transmit
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
id|sm-&gt;dma.ptt_cnt
OL
id|NUM_FRAGMENTS
op_logical_and
id|hdlcdrv_ptt
c_func
(paren
op_amp
id|sm-&gt;hdrv
)paren
)paren
(brace
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|sm-&gt;dma.obuf
op_plus
id|sm-&gt;dma.ofragsz
op_star
(paren
(paren
id|sm-&gt;dma.ofragptr
op_plus
id|sm-&gt;dma.ptt_cnt
)paren
op_mod
id|NUM_FRAGMENTS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.o16bit
)paren
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.mod_cyc
comma
id|sm-&gt;mode_tx
op_member_access_from_pointer
id|modulator_s16
c_func
(paren
id|sm
comma
id|p
comma
id|sm-&gt;dma.ofragsz
op_div
l_int|2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.mod_cyc
comma
id|sm-&gt;mode_tx
op_member_access_from_pointer
id|modulator_u8
c_func
(paren
id|sm
comma
id|p
comma
id|sm-&gt;dma.ofragsz
)paren
)paren
suffix:semicolon
)brace
id|sm-&gt;dma.ptt_cnt
op_increment
suffix:semicolon
)brace
)brace
DECL|function|dma_init_transmit
r_extern
id|__inline__
r_void
id|dma_init_transmit
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
id|sm-&gt;dma.ofragptr
op_assign
l_int|0
suffix:semicolon
id|sm-&gt;dma.ptt_cnt
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|dma_start_transmit
r_extern
id|__inline__
r_void
id|dma_start_transmit
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
id|sm-&gt;dma.ofragptr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sm-&gt;dma.o16bit
)paren
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.mod_cyc
comma
id|sm-&gt;mode_tx
op_member_access_from_pointer
id|modulator_s16
c_func
(paren
id|sm
comma
id|sm-&gt;dma.obuf
comma
id|sm-&gt;dma.ofragsz
op_div
l_int|2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.mod_cyc
comma
id|sm-&gt;mode_tx
op_member_access_from_pointer
id|modulator_u8
c_func
(paren
id|sm
comma
id|sm-&gt;dma.obuf
comma
id|sm-&gt;dma.ofragsz
)paren
)paren
suffix:semicolon
)brace
id|sm-&gt;dma.ptt_cnt
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|dma_clear_transmit
r_extern
id|__inline__
r_void
id|dma_clear_transmit
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
id|sm-&gt;dma.ptt_cnt
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|sm-&gt;dma.obuf
comma
(paren
id|sm-&gt;dma.o16bit
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|0x80
comma
id|sm-&gt;dma.ofragsz
op_star
id|NUM_FRAGMENTS
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
DECL|function|dma_receive
r_extern
id|__inline__
r_void
id|dma_receive
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
comma
r_int
r_int
id|curfrag
)paren
(brace
r_void
op_star
id|p
suffix:semicolon
r_while
c_loop
(paren
id|sm-&gt;dma.ifragptr
op_ne
id|curfrag
)paren
(brace
r_if
c_cond
(paren
id|sm-&gt;dma.ifragptr
)paren
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|sm-&gt;dma.ibuf
op_plus
id|sm-&gt;dma.ifragsz
op_star
id|sm-&gt;dma.ifragptr
suffix:semicolon
r_else
(brace
id|p
op_assign
(paren
r_int
r_char
op_star
)paren
id|sm-&gt;dma.ibuf
op_plus
id|NUM_FRAGMENTS
op_star
id|sm-&gt;dma.ifragsz
suffix:semicolon
id|memcpy
c_func
(paren
id|p
comma
id|sm-&gt;dma.ibuf
comma
id|sm-&gt;dma.ifragsz
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sm-&gt;dma.o16bit
)paren
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.demod_cyc
comma
id|sm-&gt;mode_rx
op_member_access_from_pointer
id|demodulator_s16
c_func
(paren
id|sm
comma
id|p
comma
id|sm-&gt;dma.ifragsz
op_div
l_int|2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|time_exec
c_func
(paren
id|sm-&gt;debug_vals.demod_cyc
comma
id|sm-&gt;mode_rx
op_member_access_from_pointer
id|demodulator_u8
c_func
(paren
id|sm
comma
id|p
comma
id|sm-&gt;dma.ifragsz
)paren
)paren
suffix:semicolon
)brace
id|sm-&gt;dma.ifragptr
op_assign
(paren
id|sm-&gt;dma.ifragptr
op_plus
l_int|1
)paren
op_mod
id|NUM_FRAGMENTS
suffix:semicolon
)brace
)brace
DECL|function|dma_init_receive
r_extern
id|__inline__
r_void
id|dma_init_receive
c_func
(paren
r_struct
id|sm_state
op_star
id|sm
)paren
(brace
id|sm-&gt;dma.ifragptr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------- */
macro_line|#endif /* _SMDMA_H */
eof
