DECL|macro|_PAS2_MIXER_C_
mdefine_line|#define _PAS2_MIXER_C_
multiline_comment|/*&n; * sound/pas2_mixer.c&n; *&n; * Mixer routines for the Pro Audio Spectrum cards.&n; */
multiline_comment|/*&n; * Copyright by Hannu Savolainen 1993-1996&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; *&n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIG_PAS)
macro_line|#include &quot;pas.h&quot;
DECL|macro|TRACE
mdefine_line|#define TRACE(what)&t;&t;/* (what) */
r_extern
r_int
id|translat_code
suffix:semicolon
r_extern
r_char
id|pas_model
suffix:semicolon
r_extern
r_int
op_star
id|pas_osp
suffix:semicolon
DECL|variable|rec_devices
r_static
r_int
id|rec_devices
op_assign
(paren
id|SOUND_MASK_MIC
)paren
suffix:semicolon
multiline_comment|/* Default recording source */
DECL|variable|mode_control
r_static
r_int
id|mode_control
op_assign
l_int|0
suffix:semicolon
DECL|macro|POSSIBLE_RECORDING_DEVICES
mdefine_line|#define POSSIBLE_RECORDING_DEVICES&t;(SOUND_MASK_SYNTH | SOUND_MASK_SPEAKER | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_ALTPCM)
DECL|macro|SUPPORTED_MIXER_DEVICES
mdefine_line|#define SUPPORTED_MIXER_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_SPEAKER | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_ALTPCM | SOUND_MASK_IMIX | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_VOLUME | SOUND_MASK_BASS | SOUND_MASK_TREBLE | SOUND_MASK_RECLEV | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_MUTE | SOUND_MASK_ENHANCE | SOUND_MASK_LOUD)
DECL|variable|levels
r_static
r_int
r_int
id|levels
(braket
id|SOUND_MIXER_NRDEVICES
)braket
op_assign
(brace
l_int|0x3232
comma
multiline_comment|/* Master Volume */
l_int|0x3232
comma
multiline_comment|/* Bass */
l_int|0x3232
comma
multiline_comment|/* Treble */
l_int|0x5050
comma
multiline_comment|/* FM */
l_int|0x4b4b
comma
multiline_comment|/* PCM */
l_int|0x3232
comma
multiline_comment|/* PC Speaker */
l_int|0x4b4b
comma
multiline_comment|/* Ext Line */
l_int|0x4b4b
comma
multiline_comment|/* Mic */
l_int|0x4b4b
comma
multiline_comment|/* CD */
l_int|0x6464
comma
multiline_comment|/* Recording monitor */
l_int|0x4b4b
comma
multiline_comment|/* SB PCM */
l_int|0x6464
multiline_comment|/* Recording level */
)brace
suffix:semicolon
r_void
DECL|function|mix_write
id|mix_write
(paren
r_int
r_char
id|data
comma
r_int
id|ioaddr
)paren
(brace
multiline_comment|/*&n;   * The Revision D cards have a problem with their MVA508 interface. The&n;   * kludge-o-rama fix is to make a 16-bit quantity with identical LSB and&n;   * MSBs out of the output byte and to do a 16-bit out to the mixer port -&n;   * 1. We need to do this because it isn&squot;t timing problem but chip access&n;   * sequence problem.&n;   */
r_if
c_cond
(paren
id|pas_model
op_eq
id|PAS_16D
)paren
(brace
id|outw
(paren
id|data
op_or
(paren
id|data
op_lshift
l_int|8
)paren
comma
(paren
id|ioaddr
op_xor
id|translat_code
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|outb
(paren
l_int|0x80
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
id|pas_write
(paren
id|data
comma
id|ioaddr
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|mixer_output
id|mixer_output
(paren
r_int
id|right_vol
comma
r_int
id|left_vol
comma
r_int
id|div
comma
r_int
id|bits
comma
r_int
id|mixer
)paren
multiline_comment|/* Input or output mixer */
(brace
r_int
id|left
op_assign
id|left_vol
op_star
id|div
op_div
l_int|100
suffix:semicolon
r_int
id|right
op_assign
id|right_vol
op_star
id|div
op_div
l_int|100
suffix:semicolon
r_if
c_cond
(paren
id|bits
op_amp
id|P_M_MV508_MIXER
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Select input or output mixer&n;&t;&t;&t;&t; */
id|left
op_or_assign
id|mixer
suffix:semicolon
id|right
op_or_assign
id|mixer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bits
op_eq
id|P_M_MV508_BASS
op_logical_or
id|bits
op_eq
id|P_M_MV508_TREBLE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Bass and treble are mono devices&n;&t;&t;&t;&t; */
id|mix_write
(paren
id|P_M_MV508_ADDRESS
op_or
id|bits
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mix_write
(paren
id|left
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|right_vol
op_assign
id|left_vol
suffix:semicolon
)brace
r_else
(brace
id|mix_write
(paren
id|P_M_MV508_ADDRESS
op_or
id|P_M_MV508_LEFT
op_or
id|bits
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mix_write
(paren
id|left
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mix_write
(paren
id|P_M_MV508_ADDRESS
op_or
id|P_M_MV508_RIGHT
op_or
id|bits
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mix_write
(paren
id|right
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
)brace
r_return
(paren
id|left_vol
op_or
(paren
id|right_vol
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
)brace
r_void
DECL|function|set_mode
id|set_mode
(paren
r_int
id|new_mode
)paren
(brace
id|mix_write
(paren
id|P_M_MV508_ADDRESS
op_or
id|P_M_MV508_MODE
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mix_write
(paren
id|new_mode
comma
id|PARALLEL_MIXER
)paren
suffix:semicolon
id|mode_control
op_assign
id|new_mode
suffix:semicolon
)brace
r_static
r_int
DECL|function|pas_mixer_set
id|pas_mixer_set
(paren
r_int
id|whichDev
comma
r_int
r_int
id|level
)paren
(brace
r_int
id|left
comma
id|right
comma
id|devmask
comma
id|changed
comma
id|i
comma
id|mixer
op_assign
l_int|0
suffix:semicolon
id|TRACE
(paren
id|printk
(paren
l_string|&quot;static int pas_mixer_set(int whichDev = %d, unsigned int level = %X)&bslash;n&quot;
comma
id|whichDev
comma
id|level
)paren
)paren
suffix:semicolon
id|left
op_assign
id|level
op_amp
l_int|0x7f
suffix:semicolon
id|right
op_assign
(paren
id|level
op_amp
l_int|0x7f00
)paren
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|whichDev
OL
id|SOUND_MIXER_NRDEVICES
)paren
r_if
c_cond
(paren
(paren
l_int|1
op_lshift
id|whichDev
)paren
op_amp
id|rec_devices
)paren
id|mixer
op_assign
id|P_M_MV508_INPUTMIX
suffix:semicolon
r_else
id|mixer
op_assign
id|P_M_MV508_OUTPUTMIX
suffix:semicolon
r_switch
c_cond
(paren
id|whichDev
)paren
(brace
r_case
id|SOUND_MIXER_VOLUME
suffix:colon
multiline_comment|/* Master volume (0-63) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|63
comma
id|P_M_MV508_MASTER_A
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;       * Note! Bass and Treble are mono devices. Will use just the left&n;       * channel.&n;       */
r_case
id|SOUND_MIXER_BASS
suffix:colon
multiline_comment|/* Bass (0-12) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|12
comma
id|P_M_MV508_BASS
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_TREBLE
suffix:colon
multiline_comment|/* Treble (0-12) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|12
comma
id|P_M_MV508_TREBLE
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_SYNTH
suffix:colon
multiline_comment|/* Internal synthesizer (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_FM
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_PCM
suffix:colon
multiline_comment|/* PAS PCM (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_PCM
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_ALTPCM
suffix:colon
multiline_comment|/* SB PCM (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_SB
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_SPEAKER
suffix:colon
multiline_comment|/* PC speaker (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_SPEAKER
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_LINE
suffix:colon
multiline_comment|/* External line (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_LINE
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CD
suffix:colon
multiline_comment|/* CD (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_CDROM
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_MIC
suffix:colon
multiline_comment|/* External microphone (0-31) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_MIC
comma
id|mixer
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_IMIX
suffix:colon
multiline_comment|/* Recording monitor (0-31) (Output mixer only) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|31
comma
id|P_M_MV508_MIXER
op_or
id|P_M_MV508_IMIXER
comma
id|P_M_MV508_OUTPUTMIX
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECLEV
suffix:colon
multiline_comment|/* Recording level (0-15) */
id|levels
(braket
id|whichDev
)braket
op_assign
id|mixer_output
(paren
id|right
comma
id|left
comma
l_int|15
comma
id|P_M_MV508_MASTER_B
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_MUTE
suffix:colon
r_return
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_ENHANCE
suffix:colon
id|i
op_assign
l_int|0
suffix:semicolon
id|level
op_and_assign
l_int|0x7f
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|i
op_assign
(paren
id|level
op_div
l_int|20
)paren
op_minus
l_int|1
suffix:semicolon
id|mode_control
op_and_assign
op_complement
id|P_M_MV508_ENHANCE_BITS
suffix:semicolon
id|mode_control
op_or_assign
id|P_M_MV508_ENHANCE_BITS
suffix:semicolon
id|set_mode
(paren
id|mode_control
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|i
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_star
l_int|20
suffix:semicolon
r_return
id|i
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_LOUD
suffix:colon
id|mode_control
op_and_assign
op_complement
id|P_M_MV508_LOUDNESS
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|mode_control
op_or_assign
id|P_M_MV508_LOUDNESS
suffix:semicolon
id|set_mode
(paren
id|mode_control
)paren
suffix:semicolon
r_return
op_logical_neg
op_logical_neg
id|level
suffix:semicolon
multiline_comment|/* 0 or 1 */
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECSRC
suffix:colon
id|devmask
op_assign
id|level
op_amp
id|POSSIBLE_RECORDING_DEVICES
suffix:semicolon
id|changed
op_assign
id|devmask
op_xor
id|rec_devices
suffix:semicolon
id|rec_devices
op_assign
id|devmask
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
id|SOUND_MIXER_NRDEVICES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|changed
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|pas_mixer_set
(paren
id|i
comma
id|levels
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_return
id|rec_devices
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
(paren
id|levels
(braket
id|whichDev
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*****/
r_static
r_void
DECL|function|pas_mixer_reset
id|pas_mixer_reset
(paren
r_void
)paren
(brace
r_int
id|foo
suffix:semicolon
id|TRACE
(paren
id|printk
(paren
l_string|&quot;pas2_mixer.c: void pas_mixer_reset(void)&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|foo
op_assign
l_int|0
suffix:semicolon
id|foo
OL
id|SOUND_MIXER_NRDEVICES
suffix:semicolon
id|foo
op_increment
)paren
id|pas_mixer_set
(paren
id|foo
comma
id|levels
(braket
id|foo
)braket
)paren
suffix:semicolon
id|set_mode
(paren
id|P_M_MV508_LOUDNESS
op_or
id|P_M_MV508_ENHANCE_40
)paren
suffix:semicolon
)brace
r_int
DECL|function|pas_mixer_ioctl
id|pas_mixer_ioctl
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
id|TRACE
(paren
id|printk
(paren
l_string|&quot;pas2_mixer.c: int pas_mixer_ioctl(unsigned int cmd = %X, unsigned int arg = %X)&bslash;n&quot;
comma
id|cmd
comma
id|arg
)paren
)paren
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
id|_IOC_DIR
(paren
id|cmd
)paren
op_amp
id|_IOC_WRITE
)paren
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|pas_mixer_set
(paren
id|cmd
op_amp
l_int|0xff
comma
id|get_fs_long
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
)paren
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t;   * Read parameters&n;&t;&t;&t;&t; */
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
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|rec_devices
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_STEREODEVS
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|SUPPORTED_MIXER_DEVICES
op_amp
op_complement
(paren
id|SOUND_MASK_BASS
op_or
id|SOUND_MASK_TREBLE
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_DEVMASK
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|SUPPORTED_MIXER_DEVICES
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_RECMASK
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|POSSIBLE_RECORDING_DEVICES
op_amp
id|SUPPORTED_MIXER_DEVICES
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_CAPS
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* No special capabilities */
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_MUTE
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* No mute yet */
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_ENHANCE
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode_control
op_amp
id|P_M_MV508_ENHANCE_BITS
)paren
)paren
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
(paren
(paren
id|mode_control
op_amp
id|P_M_MV508_ENHANCE_BITS
)paren
op_plus
l_int|1
)paren
op_star
l_int|20
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SOUND_MIXER_LOUD
suffix:colon
r_if
c_cond
(paren
id|mode_control
op_amp
id|P_M_MV508_LOUDNESS
)paren
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
l_int|1
)paren
suffix:semicolon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
id|snd_ioctl_return
(paren
(paren
r_int
op_star
)paren
id|arg
comma
id|levels
(braket
id|cmd
op_amp
l_int|0xff
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|variable|pas_mixer_operations
r_static
r_struct
id|mixer_operations
id|pas_mixer_operations
op_assign
(brace
l_string|&quot;Pro Audio Spectrum 16&quot;
comma
id|pas_mixer_ioctl
)brace
suffix:semicolon
r_int
DECL|function|pas_init_mixer
id|pas_init_mixer
(paren
r_void
)paren
(brace
id|pas_mixer_reset
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_mixers
OL
id|MAX_MIXER_DEV
)paren
id|mixer_devs
(braket
id|num_mixers
op_increment
)braket
op_assign
op_amp
id|pas_mixer_operations
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
