multiline_comment|/*&n; * sound/gus2_midi.c&n; *&n; * The low level driver for the GUS Midi Interface.&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;gus.h&quot;
macro_line|#include &quot;gus_hw.h&quot;
DECL|variable|midi_busy
DECL|variable|input_opened
r_static
r_int
id|midi_busy
op_assign
l_int|0
comma
id|input_opened
op_assign
l_int|0
suffix:semicolon
DECL|variable|my_dev
r_static
r_int
id|my_dev
suffix:semicolon
DECL|variable|output_used
r_static
r_int
id|output_used
op_assign
l_int|0
suffix:semicolon
DECL|variable|gus_midi_control
r_static
r_volatile
r_int
r_char
id|gus_midi_control
suffix:semicolon
DECL|variable|midi_input_intr
r_static
r_void
(paren
op_star
id|midi_input_intr
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
suffix:semicolon
DECL|variable|tmp_queue
r_static
r_int
r_char
id|tmp_queue
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
id|gus_pnp_flag
suffix:semicolon
DECL|variable|qlen
r_static
r_volatile
r_int
id|qlen
suffix:semicolon
DECL|variable|qhead
DECL|variable|qtail
r_static
r_volatile
r_int
r_char
id|qhead
comma
id|qtail
suffix:semicolon
r_extern
r_int
id|gus_base
comma
id|gus_irq
comma
id|gus_dma
suffix:semicolon
r_extern
r_int
op_star
id|gus_osp
suffix:semicolon
DECL|function|GUS_MIDI_STATUS
r_static
r_int
id|GUS_MIDI_STATUS
c_func
(paren
r_void
)paren
(brace
r_return
id|inb
c_func
(paren
id|u_MidiStatus
)paren
suffix:semicolon
)brace
DECL|function|gus_midi_open
r_static
r_int
id|gus_midi_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
comma
r_void
(paren
op_star
id|input
)paren
(paren
r_int
id|dev
comma
r_int
r_char
id|data
)paren
comma
r_void
(paren
op_star
id|output
)paren
(paren
r_int
id|dev
)paren
)paren
(brace
r_if
c_cond
(paren
id|midi_busy
)paren
(brace
multiline_comment|/*&t;&t;printk(&quot;GUS: Midi busy&bslash;n&quot;);*/
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
id|MIDI_RESET
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
id|gus_delay
c_func
(paren
)paren
suffix:semicolon
id|gus_midi_control
op_assign
l_int|0
suffix:semicolon
id|input_opened
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_eq
id|OPEN_READ
op_logical_or
id|mode
op_eq
id|OPEN_READWRITE
)paren
r_if
c_cond
(paren
op_logical_neg
id|gus_pnp_flag
)paren
(brace
id|gus_midi_control
op_or_assign
id|MIDI_ENABLE_RCV
suffix:semicolon
id|input_opened
op_assign
l_int|1
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
id|gus_midi_control
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
multiline_comment|/* Enable */
id|midi_busy
op_assign
l_int|1
suffix:semicolon
id|qlen
op_assign
id|qhead
op_assign
id|qtail
op_assign
id|output_used
op_assign
l_int|0
suffix:semicolon
id|midi_input_intr
op_assign
id|input
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dump_to_midi
r_static
r_int
id|dump_to_midi
c_func
(paren
r_int
r_char
id|midi_byte
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ok
op_assign
l_int|0
suffix:semicolon
id|output_used
op_assign
l_int|1
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
r_if
c_cond
(paren
id|GUS_MIDI_STATUS
c_func
(paren
)paren
op_amp
id|MIDI_XMIT_EMPTY
)paren
(brace
id|ok
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
(paren
id|midi_byte
)paren
comma
id|u_MidiData
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Enable Midi xmit interrupts (again)&n;&t;&t; */
id|gus_midi_control
op_or_assign
id|MIDI_ENABLE_XMIT
suffix:semicolon
id|outb
c_func
(paren
(paren
id|gus_midi_control
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|ok
suffix:semicolon
)brace
DECL|function|gus_midi_close
r_static
r_void
id|gus_midi_close
c_func
(paren
r_int
id|dev
)paren
(brace
multiline_comment|/*&n;&t; * Reset FIFO pointers, disable intrs&n;&t; */
id|outb
c_func
(paren
(paren
id|MIDI_RESET
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
id|midi_busy
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|gus_midi_out
r_static
r_int
id|gus_midi_out
c_func
(paren
r_int
id|dev
comma
r_int
r_char
id|midi_byte
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/*&n;&t; * Drain the local queue first&n;&t; */
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
r_while
c_loop
(paren
id|qlen
op_logical_and
id|dump_to_midi
c_func
(paren
id|tmp_queue
(braket
id|qhead
)braket
)paren
)paren
(brace
id|qlen
op_decrement
suffix:semicolon
id|qhead
op_increment
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Output the byte if the local queue is empty.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|qlen
)paren
r_if
c_cond
(paren
id|dump_to_midi
c_func
(paren
id|midi_byte
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t;&t; * OK&n;&t;&t;&t;&t;&t; */
multiline_comment|/*&n;&t; *&t;Put to the local queue&n;&t; */
r_if
c_cond
(paren
id|qlen
op_ge
l_int|256
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * Local queue full&n;&t;&t;&t;&t; */
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
id|tmp_queue
(braket
id|qtail
)braket
op_assign
id|midi_byte
suffix:semicolon
id|qlen
op_increment
suffix:semicolon
id|qtail
op_increment
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
DECL|function|gus_midi_start_read
r_static
r_int
id|gus_midi_start_read
c_func
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gus_midi_end_read
r_static
r_int
id|gus_midi_end_read
c_func
(paren
r_int
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gus_midi_kick
r_static
r_void
id|gus_midi_kick
c_func
(paren
r_int
id|dev
)paren
(brace
)brace
DECL|function|gus_midi_buffer_status
r_static
r_int
id|gus_midi_buffer_status
c_func
(paren
r_int
id|dev
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|output_used
)paren
r_return
l_int|0
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
r_if
c_cond
(paren
id|qlen
op_logical_and
id|dump_to_midi
c_func
(paren
id|tmp_queue
(braket
id|qhead
)braket
)paren
)paren
(brace
id|qlen
op_decrement
suffix:semicolon
id|qhead
op_increment
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
(paren
id|qlen
OG
l_int|0
)paren
op_or
op_logical_neg
(paren
id|GUS_MIDI_STATUS
c_func
(paren
)paren
op_amp
id|MIDI_XMIT_EMPTY
)paren
suffix:semicolon
)brace
DECL|macro|MIDI_SYNTH_NAME
mdefine_line|#define MIDI_SYNTH_NAME&t;&quot;Gravis Ultrasound Midi&quot;
DECL|macro|MIDI_SYNTH_CAPS
mdefine_line|#define MIDI_SYNTH_CAPS&t;SYNTH_CAP_INPUT
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|gus_midi_operations
r_static
r_struct
id|midi_operations
id|gus_midi_operations
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|info
suffix:colon
(brace
l_string|&quot;Gravis UltraSound Midi&quot;
comma
l_int|0
comma
l_int|0
comma
id|SNDCARD_GUS
)brace
comma
id|converter
suffix:colon
op_amp
id|std_midi_synth
comma
id|in_info
suffix:colon
(brace
l_int|0
)brace
comma
id|open
suffix:colon
id|gus_midi_open
comma
id|close
suffix:colon
id|gus_midi_close
comma
id|outputc
suffix:colon
id|gus_midi_out
comma
id|start_read
suffix:colon
id|gus_midi_start_read
comma
id|end_read
suffix:colon
id|gus_midi_end_read
comma
id|kick
suffix:colon
id|gus_midi_kick
comma
id|buffer_status
suffix:colon
id|gus_midi_buffer_status
comma
)brace
suffix:semicolon
DECL|function|gus_midi_init
r_void
id|gus_midi_init
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|dev
op_assign
id|sound_alloc_mididev
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gus_midi: Too many midi devices detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|outb
c_func
(paren
(paren
id|MIDI_RESET
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
id|std_midi_synth.midi_dev
op_assign
id|my_dev
op_assign
id|dev
suffix:semicolon
id|hw_config-&gt;slots
(braket
l_int|2
)braket
op_assign
id|dev
suffix:semicolon
id|midi_devs
(braket
id|dev
)braket
op_assign
op_amp
id|gus_midi_operations
suffix:semicolon
id|sequencer_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|gus_midi_interrupt
r_void
id|gus_midi_interrupt
c_func
(paren
r_int
id|dummy
)paren
(brace
r_volatile
r_int
r_char
id|stat
comma
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|timeout
op_assign
l_int|10
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
r_while
c_loop
(paren
id|timeout
op_decrement
OG
l_int|0
op_logical_and
(paren
id|stat
op_assign
id|GUS_MIDI_STATUS
c_func
(paren
)paren
)paren
op_amp
(paren
id|MIDI_RCV_FULL
op_or
id|MIDI_XMIT_EMPTY
)paren
)paren
(brace
r_if
c_cond
(paren
id|stat
op_amp
id|MIDI_RCV_FULL
)paren
(brace
id|data
op_assign
id|inb
c_func
(paren
id|u_MidiData
)paren
suffix:semicolon
r_if
c_cond
(paren
id|input_opened
)paren
id|midi_input_intr
c_func
(paren
id|my_dev
comma
id|data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|stat
op_amp
id|MIDI_XMIT_EMPTY
)paren
(brace
r_while
c_loop
(paren
id|qlen
op_logical_and
id|dump_to_midi
c_func
(paren
id|tmp_queue
(braket
id|qhead
)braket
)paren
)paren
(brace
id|qlen
op_decrement
suffix:semicolon
id|qhead
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|qlen
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;       * Disable Midi output interrupts, since no data in the buffer&n;&t;&t;&t;       */
id|gus_midi_control
op_and_assign
op_complement
id|MIDI_ENABLE_XMIT
suffix:semicolon
id|outb
c_func
(paren
(paren
id|gus_midi_control
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|gus_midi_control
)paren
comma
id|u_MidiControl
)paren
suffix:semicolon
)brace
)brace
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
eof
