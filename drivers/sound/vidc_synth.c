multiline_comment|/*&n; * drivers/sound/vidc_synth.c&n; *&n; * Synthesizer routines for the VIDC&n; *&n; * Copyright (C) 1997 Russell King &lt;rmk@arm.uk.linux.org&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;vidc.h&quot;
DECL|variable|vidc_info
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
DECL|variable|vidc_sdev
r_int
id|vidc_sdev
suffix:semicolon
DECL|variable|vidc_synth_volume
r_int
id|vidc_synth_volume
suffix:semicolon
DECL|function|vidc_synth_open
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
DECL|function|vidc_synth_close
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
DECL|variable|vidc_synth_operations
r_static
r_struct
id|synth_operations
id|vidc_synth_operations
op_assign
(brace
op_amp
id|vidc_info
comma
multiline_comment|/* info                 */
l_int|0
comma
multiline_comment|/* midi_dev             */
id|SYNTH_TYPE_SAMPLE
comma
multiline_comment|/* synth_type           */
multiline_comment|/*SAMPLE_TYPE_XXX */
l_int|0
comma
multiline_comment|/* SAMPLE_TYPE GUS */
multiline_comment|/* synth_subtype                */
id|vidc_synth_open
comma
multiline_comment|/* open                 */
id|vidc_synth_close
comma
multiline_comment|/* close                */
l_int|NULL
comma
multiline_comment|/* ioctl                */
l_int|NULL
comma
multiline_comment|/* kill_note            */
l_int|NULL
comma
multiline_comment|/* start_note           */
l_int|NULL
comma
multiline_comment|/* set_instr            */
l_int|NULL
comma
multiline_comment|/* reset                */
l_int|NULL
comma
multiline_comment|/* hw_control           */
l_int|NULL
comma
multiline_comment|/* load_patch           */
l_int|NULL
comma
multiline_comment|/* aftertouch           */
l_int|NULL
comma
multiline_comment|/* controller           */
l_int|NULL
comma
multiline_comment|/* panning              */
l_int|NULL
comma
multiline_comment|/* volume_method        */
l_int|NULL
comma
multiline_comment|/* patchmgr             */
l_int|NULL
comma
multiline_comment|/* bender               */
l_int|NULL
comma
multiline_comment|/* alloc                */
l_int|NULL
comma
multiline_comment|/* setup_voice          */
l_int|NULL
comma
multiline_comment|/* send_sysex           */
multiline_comment|/* alloc                */
multiline_comment|/* chn_info[16]         */
)brace
suffix:semicolon
DECL|function|vidc_synth_get_volume
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
DECL|function|vidc_synth_set_volume
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
DECL|function|vidc_synth_init
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
eof
