multiline_comment|/*&n; * drivers/sound/vidc_synth.c&n; *&n; * Synthesizer routines for the VIDC&n; *&n; * Copyright (C) 1997 Russell King &lt;rmk@arm.uk.linux.org&gt;&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;vidc.h&quot;
macro_line|#if 0
r_static
r_struct
id|synth_info
id|vidc_info
op_assign
(brace
l_string|&quot;VIDCsound&quot;
comma
multiline_comment|/* name                 */
l_int|0
comma
multiline_comment|/* device               */
id|SYNTH_TYPE_SAMPLE
comma
multiline_comment|/* synth_type           */
l_int|0
comma
multiline_comment|/* synth_subtype        */
l_int|0
comma
multiline_comment|/* perc_mode            */
l_int|16
comma
multiline_comment|/* nr_voices            */
l_int|0
comma
multiline_comment|/* nr_drums             */
l_int|0
comma
multiline_comment|/* instr_bank_size      */
l_int|0
comma
multiline_comment|/* capabilities         */
)brace
suffix:semicolon
r_int
id|vidc_sdev
suffix:semicolon
r_int
id|vidc_synth_volume
suffix:semicolon
r_static
r_int
id|vidc_synth_open
c_func
(paren
r_int
id|dev
comma
r_int
id|mode
)paren
(brace
r_if
c_cond
(paren
id|vidc_busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|vidc_busy
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|vidc_synth_close
c_func
(paren
r_int
id|dev
)paren
(brace
id|vidc_busy
op_assign
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|synth_operations
id|vidc_synth_operations
op_assign
(brace
l_string|&quot;VIDC Synth&quot;
comma
multiline_comment|/* name&t;&t;&t;*/
op_amp
id|vidc_info
comma
multiline_comment|/* info &t;&t;*/
l_int|0
comma
multiline_comment|/* midi_dev&t;&t;*/
id|SYNTH_TYPE_SAMPLE
comma
multiline_comment|/* synth_type&t;&t;*/
multiline_comment|/*SAMPLE_TYPE_XXX */
l_int|0
comma
multiline_comment|/* synth_subtype&t;*/
id|vidc_synth_open
comma
multiline_comment|/* open &t;&t;*/
id|vidc_synth_close
comma
multiline_comment|/* close&t;&t;*/
l_int|NULL
comma
multiline_comment|/* ioctl&t;&t;*/
l_int|NULL
comma
multiline_comment|/* kill_note&t;&t;*/
l_int|NULL
comma
multiline_comment|/* start_note&t;&t;*/
l_int|NULL
comma
multiline_comment|/* set_instr&t;&t;*/
l_int|NULL
comma
multiline_comment|/* reset&t;&t;*/
l_int|NULL
comma
multiline_comment|/* hw_control&t;&t;*/
l_int|NULL
comma
multiline_comment|/* load_patch&t;&t;*/
l_int|NULL
comma
multiline_comment|/* aftertouch&t;&t;*/
l_int|NULL
comma
multiline_comment|/* controller&t;&t;*/
l_int|NULL
comma
multiline_comment|/* panning&t;&t;*/
l_int|NULL
comma
multiline_comment|/* volume_method&t;*/
l_int|NULL
comma
multiline_comment|/* bender&t;&t;*/
l_int|NULL
comma
multiline_comment|/* alloc_voice&t;&t;*/
l_int|NULL
comma
multiline_comment|/* setup_voice&t;&t;*/
l_int|NULL
comma
multiline_comment|/* send_sysex&t;&t;*/
multiline_comment|/* alloc&t;&t;*/
multiline_comment|/* chn_info[16] &t;*/
multiline_comment|/* syex_buf&t;&t;*/
multiline_comment|/* syex_ptr&t;&t;*/
)brace
suffix:semicolon
r_int
id|vidc_synth_get_volume
c_func
(paren
r_void
)paren
(brace
r_return
id|vidc_synth_volume
suffix:semicolon
)brace
r_int
id|vidc_synth_set_volume
c_func
(paren
r_int
id|newvol
)paren
(brace
r_return
id|vidc_synth_volume
op_assign
id|newvol
suffix:semicolon
)brace
r_void
id|vidc_synth_init
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|vidc_synth_volume
op_assign
l_int|100
op_or
(paren
l_int|100
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vidc_sdev
op_assign
id|sound_alloc_synthdev
c_func
(paren
)paren
)paren
op_ne
op_minus
l_int|1
)paren
id|synth_devs
(braket
id|vidc_sdev
)braket
op_assign
op_amp
id|vidc_synth_operations
suffix:semicolon
r_else
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;VIDCsound: Too many synthesizers&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
