multiline_comment|/*&n; * sound/ics2101.c&n; *&n; * Driver for the ICS2101 mixer of GUS v3.7.&n; *&n; *&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; *&n; * Thomas Sailer   : ioctl code reworked (vmalloc/vfree removed)&n; */
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &lt;linux/ultrasound.h&gt;
macro_line|#include &quot;gus.h&quot;
macro_line|#include &quot;gus_hw.h&quot;
DECL|macro|MIX_DEVS
mdefine_line|#define MIX_DEVS&t;(SOUND_MASK_MIC|SOUND_MASK_LINE| &bslash;&n;&t;&t;&t; SOUND_MASK_SYNTH| &bslash;&n;  &t;&t;&t; SOUND_MASK_CD | SOUND_MASK_VOLUME)
r_extern
r_int
op_star
id|gus_osp
suffix:semicolon
r_extern
r_int
id|gus_base
suffix:semicolon
DECL|variable|volumes
r_static
r_int
id|volumes
(braket
id|ICS_MIXDEVS
)braket
suffix:semicolon
DECL|variable|left_fix
r_static
r_int
id|left_fix
(braket
id|ICS_MIXDEVS
)braket
op_assign
(brace
l_int|1
comma
l_int|1
comma
l_int|1
comma
l_int|2
comma
l_int|1
comma
l_int|2
)brace
suffix:semicolon
DECL|variable|right_fix
r_static
r_int
id|right_fix
(braket
id|ICS_MIXDEVS
)braket
op_assign
(brace
l_int|2
comma
l_int|2
comma
l_int|2
comma
l_int|1
comma
l_int|2
comma
l_int|1
)brace
suffix:semicolon
DECL|function|scale_vol
r_static
r_int
id|scale_vol
c_func
(paren
r_int
id|vol
)paren
(brace
multiline_comment|/*&n;&t; *  Experimental volume scaling by Risto Kankkunen.&n;&t; *  This should give smoother volume response than just&n;&t; *  a plain multiplication.&n;&t; */
r_int
id|e
suffix:semicolon
r_if
c_cond
(paren
id|vol
OL
l_int|0
)paren
id|vol
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
l_int|100
)paren
id|vol
op_assign
l_int|100
suffix:semicolon
id|vol
op_assign
(paren
l_int|31
op_star
id|vol
op_plus
l_int|50
)paren
op_div
l_int|100
suffix:semicolon
id|e
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vol
)paren
(brace
r_while
c_loop
(paren
id|vol
OL
l_int|16
)paren
(brace
id|vol
op_lshift_assign
l_int|1
suffix:semicolon
id|e
op_decrement
suffix:semicolon
)brace
id|vol
op_sub_assign
l_int|16
suffix:semicolon
id|e
op_add_assign
l_int|7
suffix:semicolon
)brace
r_return
(paren
(paren
id|e
op_lshift
l_int|4
)paren
op_plus
id|vol
)paren
suffix:semicolon
)brace
DECL|function|write_mix
r_static
r_void
id|write_mix
c_func
(paren
r_int
id|dev
comma
r_int
id|chn
comma
r_int
id|vol
)paren
(brace
r_int
op_star
id|selector
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ctrl_addr
op_assign
id|dev
op_lshift
l_int|3
suffix:semicolon
r_int
id|attn_addr
op_assign
id|dev
op_lshift
l_int|3
suffix:semicolon
id|vol
op_assign
id|scale_vol
c_func
(paren
id|vol
)paren
suffix:semicolon
r_if
c_cond
(paren
id|chn
op_eq
id|CHN_LEFT
)paren
(brace
id|selector
op_assign
id|left_fix
suffix:semicolon
id|ctrl_addr
op_or_assign
l_int|0x00
suffix:semicolon
id|attn_addr
op_or_assign
l_int|0x02
suffix:semicolon
)brace
r_else
(brace
id|selector
op_assign
id|right_fix
suffix:semicolon
id|ctrl_addr
op_or_assign
l_int|0x01
suffix:semicolon
id|attn_addr
op_or_assign
l_int|0x03
suffix:semicolon
)brace
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
id|outb
c_func
(paren
(paren
id|ctrl_addr
)paren
comma
id|u_MixSelect
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|selector
(braket
id|dev
)braket
)paren
comma
id|u_MixData
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|attn_addr
)paren
comma
id|u_MixSelect
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|vol
)paren
comma
id|u_MixData
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_volumes
r_static
r_int
id|set_volumes
c_func
(paren
r_int
id|dev
comma
r_int
id|vol
)paren
(brace
r_int
id|left
op_assign
id|vol
op_amp
l_int|0x00ff
suffix:semicolon
r_int
id|right
op_assign
(paren
id|vol
op_rshift
l_int|8
)paren
op_amp
l_int|0x00ff
suffix:semicolon
r_if
c_cond
(paren
id|left
OL
l_int|0
)paren
id|left
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|left
OG
l_int|100
)paren
id|left
op_assign
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|right
OL
l_int|0
)paren
id|right
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|right
OG
l_int|100
)paren
id|right
op_assign
l_int|100
suffix:semicolon
id|write_mix
c_func
(paren
id|dev
comma
id|CHN_LEFT
comma
id|left
)paren
suffix:semicolon
id|write_mix
c_func
(paren
id|dev
comma
id|CHN_RIGHT
comma
id|right
)paren
suffix:semicolon
id|vol
op_assign
id|left
op_plus
(paren
id|right
op_lshift
l_int|8
)paren
suffix:semicolon
id|volumes
(braket
id|dev
)braket
op_assign
id|vol
suffix:semicolon
r_return
id|vol
suffix:semicolon
)brace
DECL|function|ics2101_mixer_ioctl
r_static
r_int
id|ics2101_mixer_ioctl
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
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|cmd
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
op_eq
l_char|&squot;M&squot;
)paren
(brace
r_if
c_cond
(paren
id|_SIOC_DIR
c_func
(paren
id|cmd
)paren
op_amp
id|_SIOC_WRITE
)paren
(brace
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
op_amp
l_int|0xff
)paren
(brace
r_case
id|SOUND_MIXER_RECSRC
suffix:colon
r_return
id|gus_default_mixer_ioctl
c_func
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_MIC
suffix:colon
id|val
op_assign
id|set_volumes
c_func
(paren
id|DEV_MIC
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CD
suffix:colon
id|val
op_assign
id|set_volumes
c_func
(paren
id|DEV_CD
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_LINE
suffix:colon
id|val
op_assign
id|set_volumes
c_func
(paren
id|DEV_LINE
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_SYNTH
suffix:colon
id|val
op_assign
id|set_volumes
c_func
(paren
id|DEV_GF1
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_VOLUME
suffix:colon
id|val
op_assign
id|set_volumes
c_func
(paren
id|DEV_VOL
comma
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
r_else
(brace
r_switch
c_cond
(paren
id|cmd
op_amp
l_int|0xff
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Return parameters&n;&t;&t;&t;&t; */
r_case
id|SOUND_MIXER_RECSRC
suffix:colon
r_return
id|gus_default_mixer_ioctl
c_func
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_case
id|SOUND_MIXER_DEVMASK
suffix:colon
id|val
op_assign
id|MIX_DEVS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_STEREODEVS
suffix:colon
id|val
op_assign
id|SOUND_MASK_LINE
op_or
id|SOUND_MASK_CD
op_or
id|SOUND_MASK_SYNTH
op_or
id|SOUND_MASK_VOLUME
op_or
id|SOUND_MASK_MIC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECMASK
suffix:colon
id|val
op_assign
id|SOUND_MASK_MIC
op_or
id|SOUND_MASK_LINE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CAPS
suffix:colon
id|val
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_MIC
suffix:colon
id|val
op_assign
id|volumes
(braket
id|DEV_MIC
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_LINE
suffix:colon
id|val
op_assign
id|volumes
(braket
id|DEV_LINE
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CD
suffix:colon
id|val
op_assign
id|volumes
(braket
id|DEV_CD
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_VOLUME
suffix:colon
id|val
op_assign
id|volumes
(braket
id|DEV_VOL
)braket
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_SYNTH
suffix:colon
id|val
op_assign
id|volumes
(braket
id|DEV_GF1
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|ics2101_mixer_operations
r_static
r_struct
id|mixer_operations
id|ics2101_mixer_operations
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|id
suffix:colon
l_string|&quot;ICS2101&quot;
comma
id|name
suffix:colon
l_string|&quot;ICS2101 Multimedia Mixer&quot;
comma
id|ioctl
suffix:colon
id|ics2101_mixer_ioctl
)brace
suffix:semicolon
r_int
DECL|function|ics2101_mixer_init
id|ics2101_mixer_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|n
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|sound_alloc_mixerdev
c_func
(paren
)paren
)paren
op_ne
op_minus
l_int|1
)paren
(brace
id|mixer_devs
(braket
id|n
)braket
op_assign
op_amp
id|ics2101_mixer_operations
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Some GUS v3.7 cards had some channels flipped. Disable&n;&t;&t; * the flipping feature if the model id is other than 5.&n;&t;&t; */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|u_MixSelect
)paren
op_ne
l_int|5
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ICS_MIXDEVS
suffix:semicolon
id|i
op_increment
)paren
id|left_fix
(braket
id|i
)braket
op_assign
l_int|1
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
id|ICS_MIXDEVS
suffix:semicolon
id|i
op_increment
)paren
id|right_fix
(braket
id|i
)braket
op_assign
l_int|2
suffix:semicolon
)brace
id|set_volumes
c_func
(paren
id|DEV_GF1
comma
l_int|0x5a5a
)paren
suffix:semicolon
id|set_volumes
c_func
(paren
id|DEV_CD
comma
l_int|0x5a5a
)paren
suffix:semicolon
id|set_volumes
c_func
(paren
id|DEV_MIC
comma
l_int|0x0000
)paren
suffix:semicolon
id|set_volumes
c_func
(paren
id|DEV_LINE
comma
l_int|0x5a5a
)paren
suffix:semicolon
id|set_volumes
c_func
(paren
id|DEV_VOL
comma
l_int|0x5a5a
)paren
suffix:semicolon
id|set_volumes
c_func
(paren
id|DEV_UNUSED
comma
l_int|0x0000
)paren
suffix:semicolon
)brace
r_return
id|n
suffix:semicolon
)brace
eof
