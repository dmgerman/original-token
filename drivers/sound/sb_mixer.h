multiline_comment|/*&n; * sound/sb_mixer.h&n; * &n; * Definitions for the SB Pro and SB16 mixers&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
multiline_comment|/*&n; * Modified:&n; *&t;Hunyue Yau&t;Jan 6 1994&n; *&t;Added defines for the Sound Galaxy NX Pro mixer.&n; *&n; *&t;Rolf Fokkens&t;Dec 20 1998&n; *&t;Added defines for some ES188x chips.&n; *&n; *&t;Rolf Fokkens&t;Dec 27 1998&n; *&t;Moved static stuff to sb_mixer.c&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;legacy.h&quot;
macro_line|#ifdef CONFIG_SBDSP
DECL|macro|SBPRO_RECORDING_DEVICES
mdefine_line|#define SBPRO_RECORDING_DEVICES&t;(SOUND_MASK_LINE | SOUND_MASK_MIC | SOUND_MASK_CD)
multiline_comment|/* Same as SB Pro, unless I find otherwise */
DECL|macro|SGNXPRO_RECORDING_DEVICES
mdefine_line|#define SGNXPRO_RECORDING_DEVICES SBPRO_RECORDING_DEVICES
DECL|macro|SBPRO_MIXER_DEVICES
mdefine_line|#define SBPRO_MIXER_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | SOUND_MASK_VOLUME)
multiline_comment|/* SG NX Pro has treble and bass settings on the mixer. The &squot;speaker&squot;&n; * channel is the COVOX/DisneySoundSource emulation volume control&n; * on the mixer. It does NOT control speaker volume. Should have own&n; * mask eventually?&n; */
DECL|macro|SGNXPRO_MIXER_DEVICES
mdefine_line|#define SGNXPRO_MIXER_DEVICES&t;(SBPRO_MIXER_DEVICES|SOUND_MASK_BASS| &bslash;&n;&t;&t;&t;&t; SOUND_MASK_TREBLE|SOUND_MASK_SPEAKER )
DECL|macro|SB16_RECORDING_DEVICES
mdefine_line|#define SB16_RECORDING_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD)
DECL|macro|SB16_OUTFILTER_DEVICES
mdefine_line|#define SB16_OUTFILTER_DEVICES&t;&t;(SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD)
DECL|macro|ES688_RECORDING_DEVICES
mdefine_line|#define ES688_RECORDING_DEVICES SBPRO_RECORDING_DEVICES
DECL|macro|ES688_MIXER_DEVICES
mdefine_line|#define ES688_MIXER_DEVICES (SBPRO_MIXER_DEVICES|SOUND_MASK_LINE2|SOUND_MASK_SPEAKER)
DECL|macro|ES1688_RECORDING_DEVICES
mdefine_line|#define ES1688_RECORDING_DEVICES ES688_RECORDING_DEVICES
DECL|macro|ES1688_MIXER_DEVICES
mdefine_line|#define ES1688_MIXER_DEVICES (ES688_MIXER_DEVICES|SOUND_MASK_RECLEV)
DECL|macro|ES188X_RECORDING_DEVICES
mdefine_line|#define ES188X_RECORDING_DEVICES&t;(ES1688_RECORDING_DEVICES | SOUND_MASK_LINE2 &bslash;&n;&t;&t;&t;&t;&t; |SOUND_MASK_SYNTH)
DECL|macro|ES188X_MIXER_DEVICES
mdefine_line|#define ES188X_MIXER_DEVICES (ES1688_MIXER_DEVICES)
DECL|macro|SB16_MIXER_DEVICES
mdefine_line|#define SB16_MIXER_DEVICES&t;&t;(SOUND_MASK_SYNTH | SOUND_MASK_PCM | SOUND_MASK_SPEAKER | SOUND_MASK_LINE | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_CD | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_IGAIN | SOUND_MASK_OGAIN | &bslash;&n;&t;&t;&t;&t;&t; SOUND_MASK_VOLUME | SOUND_MASK_BASS | SOUND_MASK_TREBLE | &bslash;&n;&t;&t;&t;&t;&t;SOUND_MASK_IMIX)
multiline_comment|/* These are the only devices that are working at the moment.  Others could&n; * be added once they are identified and a method is found to control them.&n; */
DECL|macro|ALS007_MIXER_DEVICES
mdefine_line|#define ALS007_MIXER_DEVICES&t;(SOUND_MASK_SYNTH | SOUND_MASK_LINE | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_PCM | SOUND_MASK_MIC | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_CD | &bslash;&n;&t;&t;&t;&t; SOUND_MASK_VOLUME)
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
multiline_comment|/*&n; * Additional registers on the SG NX Pro &n; */
DECL|macro|COVOX_VOL
mdefine_line|#define COVOX_VOL&t;0x42
DECL|macro|TREBLE_LVL
mdefine_line|#define TREBLE_LVL&t;0x44
DECL|macro|BASS_LVL
mdefine_line|#define BASS_LVL&t;0x46
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
DECL|macro|SB16_OMASK
mdefine_line|#define SB16_OMASK&t;0x3c
DECL|macro|SB16_IMASK_L
mdefine_line|#define SB16_IMASK_L&t;0x3d
DECL|macro|SB16_IMASK_R
mdefine_line|#define SB16_IMASK_R&t;0x3e
DECL|macro|LEFT_CHN
mdefine_line|#define LEFT_CHN&t;0
DECL|macro|RIGHT_CHN
mdefine_line|#define RIGHT_CHN&t;1
multiline_comment|/*&n; * Mixer registers of ES188x&n; *&n; * These registers specifically take care of recording levels. To make the&n; * mapping from playback devices to recording devices every recording&n; * devices = playback device + ES188X_MIXER_RECDIFF&n; */
DECL|macro|ES188X_MIXER_RECBASE
mdefine_line|#define ES188X_MIXER_RECBASE&t;(SOUND_MIXER_LINE3 + 1)
DECL|macro|ES188X_MIXER_RECDIFF
mdefine_line|#define ES188X_MIXER_RECDIFF&t;(ES188X_MIXER_RECBASE - SOUND_MIXER_SYNTH)
DECL|macro|ES188X_MIXER_RECSYNTH
mdefine_line|#define ES188X_MIXER_RECSYNTH&t;(SOUND_MIXER_SYNTH&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECPCM
mdefine_line|#define ES188X_MIXER_RECPCM&t;(SOUND_MIXER_PCM&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECSPEAKER
mdefine_line|#define ES188X_MIXER_RECSPEAKER&t;(SOUND_MIXER_SPEAKER&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECLINE
mdefine_line|#define ES188X_MIXER_RECLINE&t;(SOUND_MIXER_LINE&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECMIC
mdefine_line|#define ES188X_MIXER_RECMIC&t;(SOUND_MIXER_MIC&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECCD
mdefine_line|#define ES188X_MIXER_RECCD&t;(SOUND_MIXER_CD&t;&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECIMIX
mdefine_line|#define ES188X_MIXER_RECIMIX&t;(SOUND_MIXER_IMIX&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECALTPCM
mdefine_line|#define ES188X_MIXER_RECALTPCM&t;(SOUND_MIXER_ALTPCM&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECRECLEV
mdefine_line|#define ES188X_MIXER_RECRECLEV&t;(SOUND_MIXER_RECLEV&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECIGAIN
mdefine_line|#define ES188X_MIXER_RECIGAIN&t;(SOUND_MIXER_IGAIN&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECOGAIN
mdefine_line|#define ES188X_MIXER_RECOGAIN&t;(SOUND_MIXER_OGAIN&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECLINE1
mdefine_line|#define ES188X_MIXER_RECLINE1&t;(SOUND_MIXER_LINE1&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECLINE2
mdefine_line|#define ES188X_MIXER_RECLINE2&t;(SOUND_MIXER_LINE2&t;+ ES188X_MIXER_RECDIFF)
DECL|macro|ES188X_MIXER_RECLINE3
mdefine_line|#define ES188X_MIXER_RECLINE3&t;(SOUND_MIXER_LINE3&t;+ ES188X_MIXER_RECDIFF)
multiline_comment|/*&n; * Mixer registers of ALS007&n; */
DECL|macro|ALS007_RECORD_SRC
mdefine_line|#define ALS007_RECORD_SRC&t;0x6c
DECL|macro|ALS007_OUTPUT_CTRL1
mdefine_line|#define ALS007_OUTPUT_CTRL1&t;0x3c
DECL|macro|ALS007_OUTPUT_CTRL2
mdefine_line|#define ALS007_OUTPUT_CTRL2&t;0x4c
DECL|macro|MIX_ENT
mdefine_line|#define MIX_ENT(name, reg_l, bit_l, len_l, reg_r, bit_r, len_r)&t;&bslash;&n;&t;{{reg_l, bit_l, len_l}, {reg_r, bit_r, len_r}}
multiline_comment|/*&n; *&t;Recording sources (SB Pro)&n; */
DECL|macro|SRC__MIC
mdefine_line|#define SRC__MIC         1&t;/* Select Microphone recording source */
DECL|macro|SRC__CD
mdefine_line|#define SRC__CD          3&t;/* Select CD recording source */
DECL|macro|SRC__LINE
mdefine_line|#define SRC__LINE        7&t;/* Use Line-in for recording source */
multiline_comment|/*&n; *&t;Recording sources for ALS-007&n; */
DECL|macro|ALS007_MIC
mdefine_line|#define ALS007_MIC&t;4
DECL|macro|ALS007_LINE
mdefine_line|#define ALS007_LINE&t;6
DECL|macro|ALS007_CD
mdefine_line|#define ALS007_CD&t;2
DECL|macro|ALS007_SYNTH
mdefine_line|#define ALS007_SYNTH&t;7
macro_line|#endif
eof
