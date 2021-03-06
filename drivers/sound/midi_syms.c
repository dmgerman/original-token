multiline_comment|/*&n; * Exported symbols for midi driver.&n; * __NO_VERSION__ because this is still part of sound.o.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
DECL|variable|midi_syms_symbol
r_char
id|midi_syms_symbol
suffix:semicolon
macro_line|#include &quot;sound_config.h&quot;
DECL|macro|_MIDI_SYNTH_C_
mdefine_line|#define _MIDI_SYNTH_C_
macro_line|#include &quot;midi_synth.h&quot;
DECL|variable|do_midi_msg
id|EXPORT_SYMBOL
c_func
(paren
id|do_midi_msg
)paren
suffix:semicolon
DECL|variable|midi_synth_open
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_open
)paren
suffix:semicolon
DECL|variable|midi_synth_close
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_close
)paren
suffix:semicolon
DECL|variable|midi_synth_ioctl
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_ioctl
)paren
suffix:semicolon
DECL|variable|midi_synth_kill_note
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_kill_note
)paren
suffix:semicolon
DECL|variable|midi_synth_start_note
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_start_note
)paren
suffix:semicolon
DECL|variable|midi_synth_set_instr
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_set_instr
)paren
suffix:semicolon
DECL|variable|midi_synth_reset
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_reset
)paren
suffix:semicolon
DECL|variable|midi_synth_hw_control
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_hw_control
)paren
suffix:semicolon
DECL|variable|midi_synth_aftertouch
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_aftertouch
)paren
suffix:semicolon
DECL|variable|midi_synth_controller
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_controller
)paren
suffix:semicolon
DECL|variable|midi_synth_panning
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_panning
)paren
suffix:semicolon
DECL|variable|midi_synth_setup_voice
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_setup_voice
)paren
suffix:semicolon
DECL|variable|midi_synth_send_sysex
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_send_sysex
)paren
suffix:semicolon
DECL|variable|midi_synth_bender
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_bender
)paren
suffix:semicolon
DECL|variable|midi_synth_load_patch
id|EXPORT_SYMBOL
c_func
(paren
id|midi_synth_load_patch
)paren
suffix:semicolon
DECL|variable|MIDIbuf_avail
id|EXPORT_SYMBOL
c_func
(paren
id|MIDIbuf_avail
)paren
suffix:semicolon
eof
