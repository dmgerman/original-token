multiline_comment|/*&n; * Exported symbols for sequencer driver.&n; * __NO_VERSION__ because this is still part of sound.o.&n; */
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
DECL|variable|sequencer_syms_symbol
r_char
id|sequencer_syms_symbol
suffix:semicolon
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;sound_calls.h&quot;
DECL|variable|note_to_freq
id|EXPORT_SYMBOL
c_func
(paren
id|note_to_freq
)paren
suffix:semicolon
DECL|variable|compute_finetune
id|EXPORT_SYMBOL
c_func
(paren
id|compute_finetune
)paren
suffix:semicolon
DECL|variable|seq_copy_to_input
id|EXPORT_SYMBOL
c_func
(paren
id|seq_copy_to_input
)paren
suffix:semicolon
DECL|variable|seq_input_event
id|EXPORT_SYMBOL
c_func
(paren
id|seq_input_event
)paren
suffix:semicolon
DECL|variable|sequencer_init
id|EXPORT_SYMBOL
c_func
(paren
id|sequencer_init
)paren
suffix:semicolon
DECL|variable|sequencer_timer
id|EXPORT_SYMBOL
c_func
(paren
id|sequencer_timer
)paren
suffix:semicolon
DECL|variable|sound_timer_init
id|EXPORT_SYMBOL
c_func
(paren
id|sound_timer_init
)paren
suffix:semicolon
DECL|variable|sound_timer_interrupt
id|EXPORT_SYMBOL
c_func
(paren
id|sound_timer_interrupt
)paren
suffix:semicolon
DECL|variable|sound_timer_syncinterval
id|EXPORT_SYMBOL
c_func
(paren
id|sound_timer_syncinterval
)paren
suffix:semicolon
DECL|variable|reprogram_timer
id|EXPORT_SYMBOL
c_func
(paren
id|reprogram_timer
)paren
suffix:semicolon
macro_line|#include &quot;softoss.h&quot;
DECL|variable|softsynthp
id|EXPORT_SYMBOL
c_func
(paren
id|softsynthp
)paren
suffix:semicolon
multiline_comment|/* Tuning */
DECL|macro|_SEQUENCER_C_
mdefine_line|#define _SEQUENCER_C_
macro_line|#include &quot;tuning.h&quot;
DECL|variable|cent_tuning
id|EXPORT_SYMBOL
c_func
(paren
id|cent_tuning
)paren
suffix:semicolon
DECL|variable|semitone_tuning
id|EXPORT_SYMBOL
c_func
(paren
id|semitone_tuning
)paren
suffix:semicolon
eof
