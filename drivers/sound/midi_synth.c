multiline_comment|/*&n; * sound/midi_synth.c&n; *&n; * High level midi sequencer manager for dumb MIDI interfaces.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
multiline_comment|/*&n; * Thomas Sailer   : ioctl code reworked (vmalloc/vfree removed)&n; * Andrew Veliath  : fixed running status in MIDI input state machine&n; */
DECL|macro|USE_SEQ_MACROS
mdefine_line|#define USE_SEQ_MACROS
DECL|macro|USE_SIMPLE_MACROS
mdefine_line|#define USE_SIMPLE_MACROS
macro_line|#include &quot;sound_config.h&quot;
DECL|macro|_MIDI_SYNTH_C_
mdefine_line|#define _MIDI_SYNTH_C_
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|midi2synth
r_static
r_int
id|midi2synth
(braket
id|MAX_MIDI_DEV
)braket
suffix:semicolon
DECL|variable|sysex_state
r_static
r_int
id|sysex_state
(braket
id|MAX_MIDI_DEV
)braket
op_assign
(brace
l_int|0
)brace
suffix:semicolon
DECL|variable|prev_out_status
r_static
r_int
r_char
id|prev_out_status
(braket
id|MAX_MIDI_DEV
)braket
suffix:semicolon
DECL|macro|STORE
mdefine_line|#define STORE(cmd) &bslash;&n;{ &bslash;&n;  int len; &bslash;&n;  unsigned char obuf[8]; &bslash;&n;  cmd; &bslash;&n;  seq_input_event(obuf, len); &bslash;&n;}
DECL|macro|_seqbuf
mdefine_line|#define _seqbuf obuf
DECL|macro|_seqbufptr
mdefine_line|#define _seqbufptr 0
DECL|macro|_SEQ_ADVBUF
mdefine_line|#define _SEQ_ADVBUF(x) len=x
r_void
DECL|function|do_midi_msg
id|do_midi_msg
c_func
(paren
r_int
id|synthno
comma
r_int
r_char
op_star
id|msg
comma
r_int
id|mlen
)paren
(brace
r_switch
c_cond
(paren
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0xf0
)paren
(brace
r_case
l_int|0x90
suffix:colon
r_if
c_cond
(paren
id|msg
(braket
l_int|2
)braket
op_ne
l_int|0
)paren
(brace
id|STORE
c_func
(paren
id|SEQ_START_NOTE
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
comma
id|msg
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|msg
(braket
l_int|2
)braket
op_assign
l_int|64
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|STORE
c_func
(paren
id|SEQ_STOP_NOTE
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
comma
id|msg
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xA0
suffix:colon
id|STORE
c_func
(paren
id|SEQ_KEY_PRESSURE
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
comma
id|msg
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xB0
suffix:colon
id|STORE
c_func
(paren
id|SEQ_CONTROL
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
comma
id|msg
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xC0
suffix:colon
id|STORE
c_func
(paren
id|SEQ_SET_PATCH
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xD0
suffix:colon
id|STORE
c_func
(paren
id|SEQ_CHN_PRESSURE
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
id|msg
(braket
l_int|1
)braket
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xE0
suffix:colon
id|STORE
c_func
(paren
id|SEQ_BENDER
c_func
(paren
id|synthno
comma
id|msg
(braket
l_int|0
)braket
op_amp
l_int|0x0f
comma
(paren
id|msg
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|msg
(braket
l_int|2
)braket
op_amp
l_int|0x7f
)paren
op_lshift
l_int|7
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* printk( &quot;MPU: Unknown midi channel message %02x&bslash;n&quot;,  msg[0]); */
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|midi_outc
id|midi_outc
c_func
(paren
r_int
id|midi_dev
comma
r_int
id|data
)paren
(brace
r_int
id|timeout
suffix:semicolon
r_for
c_loop
(paren
id|timeout
op_assign
l_int|0
suffix:semicolon
id|timeout
OL
l_int|3200
suffix:semicolon
id|timeout
op_increment
)paren
r_if
c_cond
(paren
id|midi_devs
(braket
id|midi_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|midi_dev
comma
(paren
r_int
r_char
)paren
(paren
id|data
op_amp
l_int|0xff
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|data
op_amp
l_int|0x80
)paren
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * Status byte&n;&t;&t;&t;&t;&t;&t; */
id|prev_out_status
(braket
id|midi_dev
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|data
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Store for running status&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
r_return
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Mission complete&n;&t;&t;&t;&t;&t; */
)brace
multiline_comment|/*&n;&t; * Sorry! No space on buffers.&n;&t; */
id|printk
c_func
(paren
l_string|&quot;Midi send timed out&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|prefix_cmd
id|prefix_cmd
c_func
(paren
r_int
id|midi_dev
comma
r_int
r_char
id|status
)paren
(brace
r_if
c_cond
(paren
(paren
r_char
op_star
)paren
id|midi_devs
(braket
id|midi_dev
)braket
op_member_access_from_pointer
id|prefix_cmd
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_return
id|midi_devs
(braket
id|midi_dev
)braket
op_member_access_from_pointer
id|prefix_cmd
c_func
(paren
id|midi_dev
comma
id|status
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|midi_synth_input
id|midi_synth_input
c_func
(paren
r_int
id|orig_dev
comma
r_int
r_char
id|data
)paren
(brace
r_int
id|dev
suffix:semicolon
r_struct
id|midi_input_info
op_star
id|inc
suffix:semicolon
r_static
r_int
r_char
id|len_tab
(braket
)braket
op_assign
multiline_comment|/* # of data bytes following a status&n;&t;&t;&t;&t;&t;&t; */
(brace
l_int|2
comma
multiline_comment|/* 8x */
l_int|2
comma
multiline_comment|/* 9x */
l_int|2
comma
multiline_comment|/* Ax */
l_int|2
comma
multiline_comment|/* Bx */
l_int|1
comma
multiline_comment|/* Cx */
l_int|1
comma
multiline_comment|/* Dx */
l_int|2
comma
multiline_comment|/* Ex */
l_int|0
multiline_comment|/* Fx */
)brace
suffix:semicolon
r_if
c_cond
(paren
id|orig_dev
template_param
id|num_midis
op_logical_or
id|midi_devs
(braket
id|orig_dev
)braket
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|data
op_eq
l_int|0xfe
)paren
multiline_comment|/* Ignore active sensing */
r_return
suffix:semicolon
id|dev
op_assign
id|midi2synth
(braket
id|orig_dev
)braket
suffix:semicolon
id|inc
op_assign
op_amp
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|in_info
suffix:semicolon
r_switch
c_cond
(paren
id|inc-&gt;m_state
)paren
(brace
r_case
id|MST_INIT
suffix:colon
r_if
c_cond
(paren
id|data
op_amp
l_int|0x80
)paren
multiline_comment|/* MIDI status byte */
(brace
r_if
c_cond
(paren
(paren
id|data
op_amp
l_int|0xf0
)paren
op_eq
l_int|0xf0
)paren
multiline_comment|/* Common message */
(brace
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
l_int|0xf0
suffix:colon
multiline_comment|/* Sysex */
id|inc-&gt;m_state
op_assign
id|MST_SYSEX
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Sysex */
r_case
l_int|0xf1
suffix:colon
multiline_comment|/* MTC quarter frame */
r_case
l_int|0xf3
suffix:colon
multiline_comment|/* Song select */
id|inc-&gt;m_state
op_assign
id|MST_DATA
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|1
suffix:semicolon
id|inc-&gt;m_left
op_assign
l_int|1
suffix:semicolon
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf2
suffix:colon
multiline_comment|/* Song position pointer */
id|inc-&gt;m_state
op_assign
id|MST_DATA
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|1
suffix:semicolon
id|inc-&gt;m_left
op_assign
l_int|2
suffix:semicolon
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|data
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|data
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|1
suffix:semicolon
id|do_midi_msg
c_func
(paren
id|dev
comma
id|inc-&gt;m_buf
comma
id|inc-&gt;m_ptr
)paren
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
id|inc-&gt;m_left
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|inc-&gt;m_state
op_assign
id|MST_DATA
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|1
suffix:semicolon
id|inc-&gt;m_left
op_assign
id|len_tab
(braket
(paren
id|data
op_rshift
l_int|4
)paren
op_minus
l_int|8
)braket
suffix:semicolon
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|inc-&gt;m_prev_status
op_assign
id|data
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|inc-&gt;m_prev_status
op_amp
l_int|0x80
)paren
(brace
multiline_comment|/* Data byte (use running status) */
id|inc-&gt;m_ptr
op_assign
l_int|2
suffix:semicolon
id|inc-&gt;m_buf
(braket
l_int|1
)braket
op_assign
id|data
suffix:semicolon
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_assign
id|inc-&gt;m_prev_status
suffix:semicolon
id|inc-&gt;m_left
op_assign
id|len_tab
(braket
(paren
id|inc-&gt;m_buf
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_minus
l_int|8
)braket
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|inc-&gt;m_left
OG
l_int|0
)paren
id|inc-&gt;m_state
op_assign
id|MST_DATA
suffix:semicolon
multiline_comment|/* Not done yet */
r_else
(brace
id|inc-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|do_midi_msg
c_func
(paren
id|dev
comma
id|inc-&gt;m_buf
comma
id|inc-&gt;m_ptr
)paren
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
multiline_comment|/* MST_INIT */
r_case
id|MST_DATA
suffix:colon
id|inc-&gt;m_buf
(braket
id|inc-&gt;m_ptr
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
op_decrement
id|inc-&gt;m_left
op_le
l_int|0
)paren
(brace
id|inc-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|do_midi_msg
c_func
(paren
id|dev
comma
id|inc-&gt;m_buf
comma
id|inc-&gt;m_ptr
)paren
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* MST_DATA */
r_case
id|MST_SYSEX
suffix:colon
r_if
c_cond
(paren
id|data
op_eq
l_int|0xf7
)paren
multiline_comment|/* Sysex end */
(brace
id|inc-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|inc-&gt;m_left
op_assign
l_int|0
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* MST_SYSEX */
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;MIDI%d: Unexpected state %d (%02x)&bslash;n&quot;
comma
id|orig_dev
comma
id|inc-&gt;m_state
comma
(paren
r_int
)paren
id|data
)paren
suffix:semicolon
id|inc-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|leave_sysex
id|leave_sysex
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sysex_state
(braket
id|dev
)braket
)paren
r_return
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|orig_dev
comma
l_int|0xf7
)paren
op_logical_and
id|timeout
OL
l_int|1000
)paren
id|timeout
op_increment
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|midi_synth_output
id|midi_synth_output
c_func
(paren
r_int
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * Currently NOP&n;&t; */
)brace
DECL|function|midi_synth_ioctl
r_int
id|midi_synth_ioctl
c_func
(paren
r_int
id|dev
comma
r_int
r_int
id|cmd
comma
id|caddr_t
id|arg
)paren
(brace
multiline_comment|/*&n;&t; * int orig_dev = synth_devs[dev]-&gt;midi_dev;&n;&t; */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SNDCTL_SYNTH_INFO
suffix:colon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
id|arg
comma
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|info
comma
r_sizeof
(paren
r_struct
id|synth_info
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SNDCTL_SYNTH_MEMAVL
suffix:colon
r_return
l_int|0x7fffffff
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_int
DECL|function|midi_synth_kill_note
id|midi_synth_kill_note
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|note
comma
r_int
id|velocity
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|msg
comma
id|chn
suffix:semicolon
r_if
c_cond
(paren
id|note
template_param
l_int|127
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|velocity
OL
l_int|0
)paren
id|velocity
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|velocity
OG
l_int|127
)paren
id|velocity
op_assign
l_int|127
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|msg
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0xf0
suffix:semicolon
id|chn
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|chn
op_eq
id|channel
op_logical_and
(paren
(paren
id|msg
op_eq
l_int|0x90
op_logical_and
id|velocity
op_eq
l_int|64
)paren
op_logical_or
id|msg
op_eq
l_int|0x80
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Use running status&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
id|note
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|note
)paren
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_eq
l_int|0x90
)paren
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Running status = Note on&n;&t;&t;&t;&t;&t; */
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;   * Note on with velocity 0 == note&n;&t;&t;&t;&t;&t;&t;&t;   * off&n;&t;&t;&t;&t;&t;&t;&t; */
r_else
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|velocity
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|velocity
op_eq
l_int|64
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0x90
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0x90
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Note on&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|note
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * Zero G&n;&t;&t;&t;&t;&t;&t;&t; */
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0x80
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0x80
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Note off&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|note
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|velocity
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|midi_synth_set_instr
id|midi_synth_set_instr
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|instr_no
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_if
c_cond
(paren
id|instr_no
template_param
l_int|127
)paren
id|instr_no
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
l_int|0
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xc0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0xc0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * Program change&n;&t;&t;&t;&t;&t;&t;&t; */
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|instr_no
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_int
DECL|function|midi_synth_start_note
id|midi_synth_start_note
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|note
comma
r_int
id|velocity
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|msg
comma
id|chn
suffix:semicolon
r_if
c_cond
(paren
id|note
template_param
l_int|127
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|velocity
OL
l_int|0
)paren
id|velocity
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|velocity
OG
l_int|127
)paren
id|velocity
op_assign
l_int|127
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|msg
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0xf0
suffix:semicolon
id|chn
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|chn
op_eq
id|channel
op_logical_and
id|msg
op_eq
l_int|0x90
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Use running status&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
id|note
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|note
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|velocity
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0x90
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0x90
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Note on&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|note
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|velocity
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_reset
id|midi_synth_reset
c_func
(paren
r_int
id|dev
)paren
(brace
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_int
DECL|function|midi_synth_open
id|midi_synth_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|err
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|midi_input_info
op_star
id|inc
suffix:semicolon
r_if
c_cond
(paren
id|orig_dev
template_param
id|num_midis
op_logical_or
id|midi_devs
(braket
id|orig_dev
)braket
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|midi2synth
(braket
id|orig_dev
)braket
op_assign
id|dev
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
id|prev_out_status
(braket
id|orig_dev
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|open
c_func
(paren
id|orig_dev
comma
id|mode
comma
id|midi_synth_input
comma
id|midi_synth_output
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|inc
op_assign
op_amp
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|in_info
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|inc-&gt;m_busy
op_assign
l_int|0
suffix:semicolon
id|inc-&gt;m_state
op_assign
id|MST_INIT
suffix:semicolon
id|inc-&gt;m_ptr
op_assign
l_int|0
suffix:semicolon
id|inc-&gt;m_left
op_assign
l_int|0
suffix:semicolon
id|inc-&gt;m_prev_status
op_assign
l_int|0x00
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_close
id|midi_synth_close
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Shut up the synths by sending just single active sensing message.&n;&t; */
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|orig_dev
comma
l_int|0xfe
)paren
suffix:semicolon
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|close
c_func
(paren
id|orig_dev
)paren
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_hw_control
id|midi_synth_hw_control
c_func
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|event
)paren
(brace
)brace
r_int
DECL|function|midi_synth_load_patch
id|midi_synth_load_patch
c_func
(paren
r_int
id|dev
comma
r_int
id|format
comma
r_const
r_char
op_star
id|addr
comma
r_int
id|offs
comma
r_int
id|count
comma
r_int
id|pmgr_flag
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_struct
id|sysex_info
id|sysex
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|left
comma
id|src_offs
comma
id|eox_seen
op_assign
l_int|0
suffix:semicolon
r_int
id|first_byte
op_assign
l_int|1
suffix:semicolon
r_int
id|hdr_size
op_assign
(paren
r_int
r_int
)paren
op_amp
id|sysex.data
(braket
l_int|0
)braket
op_minus
(paren
r_int
r_int
)paren
op_amp
id|sysex
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xf0
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|format
op_ne
id|SYSEX_PATCH
)paren
(brace
multiline_comment|/*&t;&t;  printk(&quot;MIDI Error: Invalid patch format (key) 0x%x&bslash;n&quot;, format);*/
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|hdr_size
)paren
(brace
multiline_comment|/*&t;&t;printk(&quot;MIDI Error: Patch header too short&bslash;n&quot;);*/
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|count
op_sub_assign
id|hdr_size
suffix:semicolon
multiline_comment|/*&n;&t; * Copy the header from user space but ignore the first bytes which have&n;&t; * been transferred already.&n;&t; */
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
(paren
(paren
r_char
op_star
)paren
op_amp
id|sysex
)paren
(braket
id|offs
)braket
comma
op_amp
(paren
id|addr
)paren
(braket
id|offs
)braket
comma
id|hdr_size
op_minus
id|offs
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
OL
id|sysex.len
)paren
(brace
multiline_comment|/*&t;&t;printk(KERN_WARNING &quot;MIDI Warning: Sysex record too short (%d&lt;%d)&bslash;n&quot;, count, (int) sysex.len);*/
id|sysex.len
op_assign
id|count
suffix:semicolon
)brace
id|left
op_assign
id|sysex.len
suffix:semicolon
id|src_offs
op_assign
l_int|0
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
id|left
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|data
suffix:semicolon
id|get_user
c_func
(paren
op_star
(paren
r_int
r_char
op_star
)paren
op_amp
id|data
comma
(paren
r_int
r_char
op_star
)paren
op_amp
(paren
(paren
id|addr
)paren
(braket
id|hdr_size
op_plus
id|i
)braket
)paren
)paren
suffix:semicolon
id|eox_seen
op_assign
(paren
id|i
OG
l_int|0
op_logical_and
id|data
op_amp
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* End of sysex */
r_if
c_cond
(paren
id|eox_seen
op_logical_and
id|data
op_ne
l_int|0xf7
)paren
id|data
op_assign
l_int|0xf7
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|data
op_ne
l_int|0xf0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;midi_synth: Sysex start missing&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_logical_neg
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|orig_dev
comma
(paren
r_int
r_char
)paren
(paren
id|data
op_amp
l_int|0xff
)paren
)paren
op_logical_and
op_logical_neg
id|signal_pending
c_func
(paren
id|current
)paren
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first_byte
op_logical_and
id|data
op_amp
l_int|0x80
)paren
r_return
l_int|0
suffix:semicolon
id|first_byte
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|eox_seen
)paren
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0xf7
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|midi_synth_panning
r_void
id|midi_synth_panning
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|pressure
)paren
(brace
)brace
DECL|function|midi_synth_aftertouch
r_void
id|midi_synth_aftertouch
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|pressure
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|msg
comma
id|chn
suffix:semicolon
r_if
c_cond
(paren
id|pressure
template_param
l_int|127
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|msg
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0xf0
suffix:semicolon
id|chn
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_ne
l_int|0xd0
op_logical_or
id|chn
op_ne
id|channel
)paren
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t; * Test for running status&n;&t;&t;&t;&t;&t;&t; */
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xd0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0xd0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; * Channel pressure&n;&t;&t;&t;&t;&t;&t;&t;&t;&t; */
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
id|pressure
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|pressure
)paren
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_controller
id|midi_synth_controller
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|ctrl_num
comma
r_int
id|value
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|chn
comma
id|msg
suffix:semicolon
r_if
c_cond
(paren
id|ctrl_num
template_param
l_int|127
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|msg
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0xf0
suffix:semicolon
id|chn
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_ne
l_int|0xb0
op_logical_or
id|chn
op_ne
id|channel
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xb0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0xb0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
id|ctrl_num
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|ctrl_num
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|value
op_amp
l_int|0x7f
)paren
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_bender
id|midi_synth_bender
c_func
(paren
r_int
id|dev
comma
r_int
id|channel
comma
r_int
id|value
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
r_int
id|msg
comma
id|prev_chn
suffix:semicolon
r_if
c_cond
(paren
id|channel
template_param
l_int|15
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|value
template_param
l_int|16383
)paren
r_return
suffix:semicolon
id|leave_sysex
c_func
(paren
id|dev
)paren
suffix:semicolon
id|msg
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0xf0
suffix:semicolon
id|prev_chn
op_assign
id|prev_out_status
(braket
id|orig_dev
)braket
op_amp
l_int|0x0f
suffix:semicolon
r_if
c_cond
(paren
id|msg
op_ne
l_int|0xd0
op_logical_or
id|prev_chn
op_ne
id|channel
)paren
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * Test for running status&n;&t;&t;&t;&t;&t;&t;&t; */
(brace
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xe0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
l_int|0xe0
op_or
(paren
id|channel
op_amp
l_int|0x0f
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
id|value
op_amp
l_int|0x7f
)paren
)paren
r_return
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
id|value
op_amp
l_int|0x7f
)paren
suffix:semicolon
id|midi_outc
c_func
(paren
id|orig_dev
comma
(paren
id|value
op_rshift
l_int|7
)paren
op_amp
l_int|0x7f
)paren
suffix:semicolon
)brace
r_void
DECL|function|midi_synth_setup_voice
id|midi_synth_setup_voice
c_func
(paren
r_int
id|dev
comma
r_int
id|voice
comma
r_int
id|channel
)paren
(brace
)brace
r_int
DECL|function|midi_synth_send_sysex
id|midi_synth_send_sysex
c_func
(paren
r_int
id|dev
comma
r_int
r_char
op_star
id|bytes
comma
r_int
id|len
)paren
(brace
r_int
id|orig_dev
op_assign
id|synth_devs
(braket
id|dev
)braket
op_member_access_from_pointer
id|midi_dev
suffix:semicolon
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
id|len
suffix:semicolon
id|i
op_increment
)paren
(brace
r_switch
c_cond
(paren
id|bytes
(braket
id|i
)braket
)paren
(brace
r_case
l_int|0xf0
suffix:colon
multiline_comment|/* Start sysex */
r_if
c_cond
(paren
op_logical_neg
id|prefix_cmd
c_func
(paren
id|orig_dev
comma
l_int|0xf0
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf7
suffix:colon
multiline_comment|/* End sysex */
r_if
c_cond
(paren
op_logical_neg
id|sysex_state
(braket
id|dev
)braket
)paren
multiline_comment|/* Orphan sysex end */
r_return
l_int|0
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sysex_state
(braket
id|dev
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|bytes
(braket
id|i
)braket
op_amp
l_int|0x80
)paren
multiline_comment|/* Error. Another message before sysex end */
(brace
id|bytes
(braket
id|i
)braket
op_assign
l_int|0xf7
suffix:semicolon
multiline_comment|/* Sysex end */
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|orig_dev
comma
id|bytes
(braket
id|i
)braket
)paren
)paren
(brace
multiline_comment|/*&n; * Hardware level buffer is full. Abort the sysex message.&n; */
r_int
id|timeout
op_assign
l_int|0
suffix:semicolon
id|bytes
(braket
id|i
)braket
op_assign
l_int|0xf7
suffix:semicolon
id|sysex_state
(braket
id|dev
)braket
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|midi_devs
(braket
id|orig_dev
)braket
op_member_access_from_pointer
id|outputc
c_func
(paren
id|orig_dev
comma
id|bytes
(braket
id|i
)braket
)paren
op_logical_and
id|timeout
OL
l_int|1000
)paren
id|timeout
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sysex_state
(braket
id|dev
)braket
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
