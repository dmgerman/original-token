multiline_comment|/*&n; * sound/sb_mixer.h&n; * &n; * Definitions for the SB Pro and SB16 mixers&n; * &n; * Copyright by Hannu Savolainen 1993&n; * &n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions are&n; * met: 1. Redistributions of source code must retain the above copyright&n; * notice, this list of conditions and the following disclaimer. 2.&n; * Redistributions in binary form must reproduce the above copyright notice,&n; * this list of conditions and the following disclaimer in the documentation&n; * and/or other materials provided with the distribution.&n; * &n; * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS&squot;&squot; AND ANY&n; * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED&n; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE&n; * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR&n; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR&n; * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER&n; * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT&n; * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY&n; * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF&n; * SUCH DAMAGE.&n; * &n; */
DECL|macro|SBPRO_RECORDING_DEVICES
mdefine_line|#define SBPRO_RECORDING_DEVICES&t;(SOUND_MASK_LINE | SOUND_MASK_MIC | SOUND_MASK_CD)
DECL|macro|SBPRO_MIXER_DEVICES
mdefine_line|#define SBPRO_MIXER_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_VOLUME)
DECL|macro|SB16_RECORDING_DEVICES
mdefine_line|#define SB16_RECORDING_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_SPEAKER | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD)
DECL|macro|SB16_MIXER_DEVICES
mdefine_line|#define SB16_MIXER_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_SPEAKER | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_RECLEV | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_VOLUME | SOUND_MASK_BASS | SOUND_MASK_TREBLE)
multiline_comment|/*&n; * Mixer registers&n; * &n; * NOTE!&t;RECORD_SRC == IN_FILTER&n; */
multiline_comment|/* &n; * Mixer registers of SB Pro&n; */
DECL|macro|VOC_VOL
mdefine_line|#define VOC_VOL&t;&t;0x04
DECL|macro|MIC_VOL
mdefine_line|#define MIC_VOL&t;&t;0x0A
DECL|macro|MIC_MIX
mdefine_line|#define MIC_MIX&t;&t;0x0A
DECL|macro|RECORD_SRC
mdefine_line|#define RECORD_SRC&t;0x0C
DECL|macro|IN_FILTER
mdefine_line|#define IN_FILTER&t;0x0C
DECL|macro|OUT_FILTER
mdefine_line|#define OUT_FILTER&t;0x0E
DECL|macro|MASTER_VOL
mdefine_line|#define MASTER_VOL&t;0x22
DECL|macro|FM_VOL
mdefine_line|#define FM_VOL&t;&t;0x26
DECL|macro|CD_VOL
mdefine_line|#define CD_VOL&t;&t;0x28
DECL|macro|LINE_VOL
mdefine_line|#define LINE_VOL&t;0x2E
DECL|macro|IRQ_NR
mdefine_line|#define IRQ_NR&t;&t;0x80
DECL|macro|DMA_NR
mdefine_line|#define DMA_NR&t;&t;0x81
DECL|macro|IRQ_STAT
mdefine_line|#define IRQ_STAT&t;0x82
DECL|macro|OPSW
mdefine_line|#define OPSW&t;&t;0x3c
DECL|macro|FREQ_HI
mdefine_line|#define FREQ_HI         (1 &lt;&lt; 3)/* Use High-frequency ANFI filters */
DECL|macro|FREQ_LOW
mdefine_line|#define FREQ_LOW        0&t;/* Use Low-frequency ANFI filters */
DECL|macro|FILT_ON
mdefine_line|#define FILT_ON         0&t;/* Yes, 0 to turn it on, 1 for off */
DECL|macro|FILT_OFF
mdefine_line|#define FILT_OFF        (1 &lt;&lt; 5)
DECL|macro|MONO_DAC
mdefine_line|#define MONO_DAC&t;0x00
DECL|macro|STEREO_DAC
mdefine_line|#define STEREO_DAC&t;0x02
multiline_comment|/*&n; * Mixer registers of SB16&n; */
DECL|macro|SB16_IMASK_L
mdefine_line|#define SB16_IMASK_L&t;0x3d
DECL|macro|SB16_IMASK_R
mdefine_line|#define SB16_IMASK_R&t;0x3e
DECL|macro|LEFT_CHN
mdefine_line|#define LEFT_CHN&t;0
DECL|macro|RIGHT_CHN
mdefine_line|#define RIGHT_CHN&t;1
DECL|struct|mixer_def
r_struct
id|mixer_def
(brace
DECL|member|name
r_char
id|name
(braket
l_int|20
)braket
suffix:semicolon
DECL|member|regno
r_int
r_int
id|regno
suffix:colon
l_int|8
suffix:semicolon
DECL|member|bitoffs
r_int
r_int
id|bitoffs
suffix:colon
l_int|4
suffix:semicolon
DECL|member|nbits
r_int
r_int
id|nbits
suffix:colon
l_int|4
suffix:semicolon
)brace
suffix:semicolon
DECL|typedef|mixer_tab
r_typedef
r_struct
id|mixer_def
id|mixer_tab
(braket
l_int|32
)braket
(braket
l_int|2
)braket
suffix:semicolon
DECL|typedef|mixer_ent
r_typedef
r_struct
id|mixer_def
id|mixer_ent
suffix:semicolon
DECL|macro|MIX_ENT
mdefine_line|#define MIX_ENT(name, reg_l, bit_l, len_l, reg_r, bit_r, len_r)&t;&bslash;&n;&t;{{#name,reg_l, bit_l, len_l}, {&quot; &quot;, reg_r, bit_r, len_r}}
macro_line|#ifdef __SB_MIXER_C__
DECL|variable|sbpro_mix
id|mixer_tab
id|sbpro_mix
op_assign
(brace
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|0x22
comma
l_int|7
comma
l_int|4
comma
l_int|0x22
comma
l_int|3
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|0x26
comma
l_int|7
comma
l_int|4
comma
l_int|0x26
comma
l_int|3
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|0x04
comma
l_int|7
comma
l_int|4
comma
l_int|0x04
comma
l_int|3
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|0x2e
comma
l_int|7
comma
l_int|4
comma
l_int|0x2e
comma
l_int|3
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|0x0a
comma
l_int|2
comma
l_int|3
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|0x28
comma
l_int|7
comma
l_int|4
comma
l_int|0x28
comma
l_int|3
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IMIX
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
)brace
suffix:semicolon
DECL|variable|sb16_mix
id|mixer_tab
id|sb16_mix
op_assign
(brace
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_VOLUME
comma
l_int|0x30
comma
l_int|7
comma
l_int|5
comma
l_int|0x31
comma
l_int|7
comma
l_int|5
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_BASS
comma
l_int|0x46
comma
l_int|7
comma
l_int|4
comma
l_int|0x47
comma
l_int|7
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_TREBLE
comma
l_int|0x44
comma
l_int|7
comma
l_int|4
comma
l_int|0x45
comma
l_int|7
comma
l_int|4
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SYNTH
comma
l_int|0x34
comma
l_int|7
comma
l_int|5
comma
l_int|0x35
comma
l_int|7
comma
l_int|5
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_PCM
comma
l_int|0x32
comma
l_int|7
comma
l_int|5
comma
l_int|0x33
comma
l_int|7
comma
l_int|5
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_SPEAKER
comma
l_int|0x3b
comma
l_int|7
comma
l_int|2
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_LINE
comma
l_int|0x38
comma
l_int|7
comma
l_int|5
comma
l_int|0x39
comma
l_int|7
comma
l_int|5
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_MIC
comma
l_int|0x3a
comma
l_int|7
comma
l_int|5
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_CD
comma
l_int|0x36
comma
l_int|7
comma
l_int|5
comma
l_int|0x37
comma
l_int|7
comma
l_int|5
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_IMIX
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_ALTPCM
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0
comma
l_int|0
)paren
comma
id|MIX_ENT
c_func
(paren
id|SOUND_MIXER_RECLEV
comma
l_int|0x3f
comma
l_int|7
comma
l_int|2
comma
l_int|0x40
comma
l_int|7
comma
l_int|2
)paren
)brace
suffix:semicolon
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
l_int|0x4b4b
comma
multiline_comment|/* Master Volume */
l_int|0x3232
comma
multiline_comment|/* Bass */
l_int|0x3232
comma
multiline_comment|/* Treble */
l_int|0x4b4b
comma
multiline_comment|/* FM */
l_int|0x4b4b
comma
multiline_comment|/* PCM */
l_int|0x4b4b
comma
multiline_comment|/* PC Speaker */
l_int|0x4b4b
comma
multiline_comment|/* Ext Line */
l_int|0x3232
comma
multiline_comment|/* Mic */
l_int|0x4b4b
comma
multiline_comment|/* CD */
l_int|0x4b4b
comma
multiline_comment|/* Recording monitor */
l_int|0x4b4b
comma
multiline_comment|/* SB PCM */
l_int|0x4b4b
)brace
suffix:semicolon
multiline_comment|/* Recording level */
DECL|variable|sb16_recmasks
r_static
r_int
r_char
id|sb16_recmasks
(braket
id|SOUND_MIXER_NRDEVICES
)braket
op_assign
(brace
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_VOLUME&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_BASS&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_TREBLE&t;*/
l_int|0x60
comma
multiline_comment|/* SOUND_MIXER_SYNTH&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_PCM&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_SPEAKER&t;*/
l_int|0x18
comma
multiline_comment|/* SOUND_MIXER_LINE&t;*/
l_int|0x01
comma
multiline_comment|/* SOUND_MIXER_MIC&t;*/
l_int|0x06
comma
multiline_comment|/* SOUND_MIXER_CD&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_IMIX&t;*/
l_int|0x00
comma
multiline_comment|/* SOUND_MIXER_ALTPCM&t;*/
l_int|0x00
multiline_comment|/* SOUND_MIXER_RECLEV&t;*/
)brace
suffix:semicolon
macro_line|#endif
eof