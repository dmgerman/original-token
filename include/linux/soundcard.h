macro_line|#ifndef SOUNDCARD_H
DECL|macro|SOUNDCARD_H
mdefine_line|#define SOUNDCARD_H
multiline_comment|/*&n; *&t;linux/soundcard.h&n; *&n; *&t;Sound Card driver for Linux&n; *&n; *&t;(C) Hannu Savolainen 1992&n; *&n; */
multiline_comment|/*&n; *&t;Supported card ID numbers&n; */
DECL|macro|SNDCARD_ADLIB
mdefine_line|#define SNDCARD_ADLIB&t;1
DECL|macro|SNDCARD_SB
mdefine_line|#define SNDCARD_SB&t;2
DECL|macro|SNDCARD_PAS
mdefine_line|#define SNDCARD_PAS&t;3
multiline_comment|/*&n; * IOCTL Commands. Suffix 0x4252 is string &quot;SB&quot;.&n; */
DECL|macro|SNDCTL_CONFIGURE
mdefine_line|#define SNDCTL_CONFIGURE&t;&t;&t;&t;0x00014252
DECL|macro|SNDCTL_FM_LOAD_INSTR
mdefine_line|#define SNDCTL_FM_LOAD_INSTR&t;&t;&t;&t;0x01014252
multiline_comment|/* #define SNDCTL_FM_RETURN_INSTR&t;&t;&t;0x01034252&t;*/
DECL|macro|SNDCTL_SEQ_SYNC
mdefine_line|#define SNDCTL_SEQ_SYNC&t;&t;&t;&t;&t;0x01044252
DECL|macro|SNDCTL_SEQ_RESET
mdefine_line|#define SNDCTL_SEQ_RESET&t;&t;&t;&t;0x01054252
DECL|macro|SNDCTL_SYNTH_INFO
mdefine_line|#define SNDCTL_SYNTH_INFO&t;&t;&t;&t;0x01064252
DECL|macro|SNDCTL_SEQ_TESTMIDI
mdefine_line|#define SNDCTL_SEQ_TESTMIDI&t;&t;&t;&t;0x01074252
DECL|macro|SNDCTL_SEQ_PERCMODE
mdefine_line|#define SNDCTL_SEQ_PERCMODE&t;&t;&t;&t;0x01084252
DECL|macro|SNDCTL_DSP_SPEED
mdefine_line|#define SNDCTL_DSP_SPEED&t;&t;&t;&t;0x01114252
DECL|macro|SNDCTL_DSP_STEREO
mdefine_line|#define SNDCTL_DSP_STEREO&t;&t;&t;&t;0x01124252
DECL|macro|SNDCTL_DSP_GETBLKSIZE
mdefine_line|#define SNDCTL_DSP_GETBLKSIZE&t;&t;&t;&t;0x01134252
DECL|macro|SNDCTL_DSP_SYNC
mdefine_line|#define SNDCTL_DSP_SYNC&t;&t;&t;&t;&t;0x01144252
DECL|macro|SNDCTL_DSP_RESET
mdefine_line|#define SNDCTL_DSP_RESET&t;&t;&t;&t;0x01154252
DECL|macro|SNDCTL_DSP_SAMPLESIZE
mdefine_line|#define SNDCTL_DSP_SAMPLESIZE&t;&t;&t;&t;0x01164252
multiline_comment|/* 8, 12 or 16)&t;*/
DECL|macro|SEQ_FMNOTEOFF
mdefine_line|#define SEQ_FMNOTEOFF&t;&t;0
DECL|macro|SEQ_FMNOTEON
mdefine_line|#define SEQ_FMNOTEON&t;&t;1
DECL|macro|SEQ_WAIT
mdefine_line|#define SEQ_WAIT&t;&t;2
DECL|macro|SEQ_FMPGMCHANGE
mdefine_line|#define SEQ_FMPGMCHANGE&t;&t;3
DECL|macro|SEQ_SYNCTIMER
mdefine_line|#define SEQ_SYNCTIMER&t;&t;4
DECL|macro|SEQ_MIDIPUTC
mdefine_line|#define SEQ_MIDIPUTC&t;&t;5
DECL|macro|SEQ_DRUMON
mdefine_line|#define SEQ_DRUMON&t;&t;6&t;/* Play percussive instrument */
DECL|macro|SEQ_DRUMOFF
mdefine_line|#define SEQ_DRUMOFF&t;&t;7
DECL|typedef|sbi_instr_data
r_typedef
r_int
r_char
id|sbi_instr_data
(braket
l_int|16
)braket
suffix:semicolon
DECL|struct|sbi_instrument
r_struct
id|sbi_instrument
(brace
DECL|member|channel
r_int
id|channel
suffix:semicolon
multiline_comment|/*&t;Channel to be programmed &t;*/
DECL|member|operators
id|sbi_instr_data
id|operators
suffix:semicolon
multiline_comment|/*&t;Register settings for operator cells (.SBI format)&t;*/
)brace
suffix:semicolon
DECL|struct|synth_info
r_struct
id|synth_info
(brace
multiline_comment|/* Read only */
DECL|member|synth_type
r_int
id|synth_type
suffix:semicolon
DECL|macro|SYNTH_TYPE_FM
mdefine_line|#define SYNTH_TYPE_FM&t;&t;&t;0
DECL|member|synth_subtype
r_int
id|synth_subtype
suffix:semicolon
DECL|macro|FM_TYPE_ADLIB
mdefine_line|#define FM_TYPE_ADLIB&t;&t;&t;0
DECL|macro|FM_TYPE_OPL3
mdefine_line|#define FM_TYPE_OPL3&t;&t;&t;1
DECL|member|perc_mode
r_int
id|perc_mode
suffix:semicolon
multiline_comment|/* 0=off 1=off */
DECL|member|nr_voices
r_int
id|nr_voices
suffix:semicolon
DECL|member|nr_drums
r_int
id|nr_drums
suffix:semicolon
DECL|member|instr_bank_size
r_int
id|instr_bank_size
suffix:semicolon
DECL|member|dummies
r_int
id|dummies
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* Reserve space */
)brace
suffix:semicolon
multiline_comment|/*&n;&t;Definitions for a &quot;universal&quot; sound driver &n;&t;by Craig metz (cmetz@thor.tjhsst.edu)&n;*/
multiline_comment|/*  &n;&t;IOCTL requests take the general form of a base address plus&n;&t;a device type plus a request type. The base address fills the&n;&t;top three bytes of the request longword and is formed from the &n;&t;letters &squot;SND&squot;. The top nybble of the remaining byte indicates&n;&t;the device type to be interacted with, and the request type&n;&t;indicates what the device needs to do, and bit 3 of the lower&n;&t;nybble distinguishes read and write. &n;&n;&t;IOCTL Calling Form:&n;&n;&t;&t;ioctl(fh, SOUND_call, &amp;parameter);&n;*/
DECL|macro|SOUND_BASE
mdefine_line|#define SOUND_BASE&t;0x534E4400
DECL|macro|SOUND_READ
mdefine_line|#define SOUND_READ&t;0x00000000
DECL|macro|SOUND_WRITE
mdefine_line|#define SOUND_WRITE&t;0x00000008
multiline_comment|/* &n;&t;Mixer control - device type 0 &n;&n;&t;All parameters are of type &quot;unsigned short int&quot; - The LSB is the &n;&t;left value, the MSB is the right value. Both are in percents, 0 &n;&t;being mute and 100 being full power. In the event that the card &n;&t;only supports mono mixer control, the LSB will be the value used.&n;*/
DECL|macro|SOUND_MIXER
mdefine_line|#define SOUND_MIXER&t;&t;0x00
DECL|macro|SOUND_MIXER_TYPE
mdefine_line|#define SOUND_MIXER_TYPE&t;unsigned short int
DECL|macro|SOUND_MIXER_VOLUME
mdefine_line|#define SOUND_MIXER_VOLUME&t;0x0
DECL|macro|SOUND_MIXER_BASS
mdefine_line|#define SOUND_MIXER_BASS&t;0x1
DECL|macro|SOUND_MIXER_TREBLE
mdefine_line|#define SOUND_MIXER_TREBLE&t;0x2
DECL|macro|SOUND_MIXER_MIDI
mdefine_line|#define SOUND_MIXER_MIDI&t;0x3
DECL|macro|SOUND_MIXER_PCM
mdefine_line|#define SOUND_MIXER_PCM&t;&t;0x4
DECL|macro|SOUND_MIXER_SPEAKER
mdefine_line|#define SOUND_MIXER_SPEAKER&t;0x5
DECL|macro|SOUND_MIXER_LINE
mdefine_line|#define SOUND_MIXER_LINE&t;0x6
DECL|macro|SOUND_MIXER_MIC
mdefine_line|#define SOUND_MIXER_MIC&t;&t;0x7
DECL|macro|SOUND_MIXER_READ_VOLUME
mdefine_line|#define SOUND_MIXER_READ_VOLUME&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_VOLUME )
DECL|macro|SOUND_MIXER_READ_BASS
mdefine_line|#define SOUND_MIXER_READ_BASS&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_BASS   )
DECL|macro|SOUND_MIXER_READ_TREBLE
mdefine_line|#define SOUND_MIXER_READ_TREBLE&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_TREBLE )
DECL|macro|SOUND_MIXER_READ_MIDI
mdefine_line|#define SOUND_MIXER_READ_MIDI&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_MIDI   )
DECL|macro|SOUND_MIXER_READ_PCM
mdefine_line|#define SOUND_MIXER_READ_PCM&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_PCM    )
DECL|macro|SOUND_MIXER_READ_SPEAKER
mdefine_line|#define SOUND_MIXER_READ_SPEAKER&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_READ_LINE
mdefine_line|#define SOUND_MIXER_READ_LINE&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_LINE   )
DECL|macro|SOUND_MIXER_READ_MIC
mdefine_line|#define SOUND_MIXER_READ_MIC&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_READ  | SOUND_MIXER_MIC    )
DECL|macro|SOUND_MIXER_WRITE_VOLUME
mdefine_line|#define SOUND_MIXER_WRITE_VOLUME&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_VOLUME )
DECL|macro|SOUND_MIXER_WRITE_BASS
mdefine_line|#define SOUND_MIXER_WRITE_BASS&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_BASS   )
DECL|macro|SOUND_MIXER_WRITE_TREBLE
mdefine_line|#define SOUND_MIXER_WRITE_TREBLE&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_TREBLE )
DECL|macro|SOUND_MIXER_WRITE_MIDI
mdefine_line|#define SOUND_MIXER_WRITE_MIDI&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_MIDI   )
DECL|macro|SOUND_MIXER_WRITE_PCM
mdefine_line|#define SOUND_MIXER_WRITE_PCM&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_PCM    )
DECL|macro|SOUND_MIXER_WRITE_SPEAKER
mdefine_line|#define SOUND_MIXER_WRITE_SPEAKER&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_SPEAKER)
DECL|macro|SOUND_MIXER_WRITE_LINE
mdefine_line|#define SOUND_MIXER_WRITE_LINE&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_LINE   )
DECL|macro|SOUND_MIXER_WRITE_MIC
mdefine_line|#define SOUND_MIXER_WRITE_MIC&t;&t;(SOUND_BASE | SOUND_MIXER | SOUND_WRITE | SOUND_MIXER_MIC    )
multiline_comment|/*&n;&t;PCM control - device type 1&n;&n;&t;All parameters are of type &quot;unsigned short int&quot;.&n;&n;&t;RATE = sampling rate in Hz&n;&t;CHANNELS = number of channels (1 = mono, 2 = stereo)&n;&t;BITS = number of bits/sample/channel (8 = 8 bit, &n;&t;&t;12 = 12 bit, 16 = 16 bit)&n;&t;FILTER = flag (0 = don&squot;t filter, 1 = use best filter)&n;*/
DECL|macro|SOUND_PCM
mdefine_line|#define SOUND_PCM &t;&t;0x10
DECL|macro|SOUND_PCM_TYPE
mdefine_line|#define SOUND_PCM_TYPE&t;&t;unsigned short int
DECL|macro|SOUND_RATE
mdefine_line|#define SOUND_RATE&t;&t;0x0
DECL|macro|SOUND_CHANNELS
mdefine_line|#define SOUND_CHANNELS&t;&t;0x1
DECL|macro|SOUND_BITS
mdefine_line|#define SOUND_BITS&t;&t;0x2
DECL|macro|SOUND_FILTER
mdefine_line|#define SOUND_FILTER&t;&t;0x3
DECL|macro|SOUND_PCM_READ_RATE
mdefine_line|#define SOUND_PCM_READ_RATE&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_READ  | SOUND_RATE    )
DECL|macro|SOUND_PCM_READ_CHANNELS
mdefine_line|#define SOUND_PCM_READ_CHANNELS&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_READ  | SOUND_CHANNELS)
DECL|macro|SOUND_PCM_READ_BITS
mdefine_line|#define SOUND_PCM_READ_BITS&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_READ  | SOUND_BITS    )
DECL|macro|SOUND_PCM_READ_FILTER
mdefine_line|#define SOUND_PCM_READ_FILTER&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_READ  | SOUND_FILTER  )
DECL|macro|SOUND_PCM_WRITE_RATE
mdefine_line|#define SOUND_PCM_WRITE_RATE&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_WRITE | SOUND_RATE    )
DECL|macro|SOUND_PCM_WRITE_CHANNELS
mdefine_line|#define SOUND_PCM_WRITE_CHANNELS&t;(SOUND_BASE | SOUND_PCM | SOUND_WRITE | SOUND_CHANNELS)
DECL|macro|SOUND_PCM_WRITE_BITS
mdefine_line|#define SOUND_PCM_WRITE_BITS&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_WRITE | SOUND_BITS    )
DECL|macro|SOUND_PCM_WRITE_FILTER
mdefine_line|#define SOUND_PCM_WRITE_FILTER&t;&t;(SOUND_BASE | SOUND_PCM | SOUND_WRITE | SOUND_FILTER  )
multiline_comment|/*&n; *&t;The Mixer ioctl calls are compatible with mach386 driver by&n; *&t;  Steve Haehnichen &lt;shaehnic@ucsd.edu&gt;&n; */
DECL|typedef|BYTE
r_typedef
r_int
r_char
id|BYTE
suffix:semicolon
DECL|typedef|FLAG
r_typedef
r_int
r_char
id|FLAG
suffix:semicolon
DECL|struct|stereo_vol
r_struct
id|stereo_vol
(brace
DECL|member|l
id|BYTE
id|l
suffix:semicolon
multiline_comment|/* Left volume */
DECL|member|r
id|BYTE
id|r
suffix:semicolon
multiline_comment|/* Right volume */
)brace
suffix:semicolon
DECL|macro|MIXER_IOCTL_SET_LEVELS
mdefine_line|#define MIXER_IOCTL_SET_LEVELS &t;&t;0x02014252
DECL|macro|MIXER_IOCTL_SET_PARAMS
mdefine_line|#define MIXER_IOCTL_SET_PARAMS &t;&t;0x02024252
DECL|macro|MIXER_IOCTL_READ_LEVELS
mdefine_line|#define MIXER_IOCTL_READ_LEVELS&t;&t;0x02034252
DECL|macro|MIXER_IOCTL_READ_PARAMS
mdefine_line|#define MIXER_IOCTL_READ_PARAMS&t;&t;0x02044252
DECL|macro|MIXER_IOCTL_RESET
mdefine_line|#define MIXER_IOCTL_RESET&t;&t;0x02054252
multiline_comment|/*&n; * Mixer volume levels for MIXER_IOCTL_SET_VOL &amp; MIXER_IOCTL_READ_VOL&n; */
DECL|struct|sb_mixer_levels
r_struct
id|sb_mixer_levels
(brace
DECL|member|master
r_struct
id|stereo_vol
id|master
suffix:semicolon
multiline_comment|/* Master volume */
DECL|member|voc
r_struct
id|stereo_vol
id|voc
suffix:semicolon
multiline_comment|/* DSP Voice volume */
DECL|member|fm
r_struct
id|stereo_vol
id|fm
suffix:semicolon
multiline_comment|/* FM volume */
DECL|member|line
r_struct
id|stereo_vol
id|line
suffix:semicolon
multiline_comment|/* Line-in volume */
DECL|member|cd
r_struct
id|stereo_vol
id|cd
suffix:semicolon
multiline_comment|/* CD audio */
DECL|member|mic
id|BYTE
id|mic
suffix:semicolon
multiline_comment|/* Microphone level */
)brace
suffix:semicolon
multiline_comment|/*&n; * Mixer parameters for MIXER_IOCTL_SET_PARAMS &amp; MIXER_IOCTL_READ_PARAMS&n; */
DECL|struct|sb_mixer_params
r_struct
id|sb_mixer_params
(brace
DECL|member|record_source
id|BYTE
id|record_source
suffix:semicolon
multiline_comment|/* Recording source (See SRC_xxx below) */
DECL|member|hifreq_filter
id|FLAG
id|hifreq_filter
suffix:semicolon
multiline_comment|/* Filter frequency (hi/low) */
DECL|member|filter_input
id|FLAG
id|filter_input
suffix:semicolon
multiline_comment|/* ANFI input filter */
DECL|member|filter_output
id|FLAG
id|filter_output
suffix:semicolon
multiline_comment|/* DNFI output filter */
DECL|member|dsp_stereo
id|FLAG
id|dsp_stereo
suffix:semicolon
multiline_comment|/* 1 if DSP is in Stereo mode */
)brace
suffix:semicolon
DECL|macro|SRC_MIC
mdefine_line|#define SRC_MIC         1&t;/* Select Microphone recording source */
DECL|macro|SRC_CD
mdefine_line|#define SRC_CD          3&t;/* Select CD recording source */
DECL|macro|SRC_LINE
mdefine_line|#define SRC_LINE        7&t;/* Use Line-in for recording source */
multiline_comment|/*&n; *&t;Dynamic configuration mechanism.&n; *&t;(for soundload program)&n; */
DECL|struct|soundcard_config
r_struct
id|soundcard_config
(brace
DECL|member|config_command
r_int
id|config_command
suffix:semicolon
DECL|macro|SNDCONF_RESET
mdefine_line|#define SNDCONF_RESET&t;&t;&t;0
DECL|macro|SNDCONF_START
mdefine_line|#define SNDCONF_START&t;&t;&t;1
DECL|macro|SNDCONF_SETCARD
mdefine_line|#define SNDCONF_SETCARD&t;&t;&t;2
DECL|member|cardtype
r_int
id|cardtype
suffix:semicolon
multiline_comment|/* SNDCARD_ADLIB etc. */
DECL|member|card_subtype
r_int
id|card_subtype
suffix:semicolon
multiline_comment|/* Card dependent number */
DECL|member|config_parms
r_int
id|config_parms
(braket
l_int|100
)braket
suffix:semicolon
multiline_comment|/* Card dependent parameters */
)brace
suffix:semicolon
r_extern
r_int
id|soundcard_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
eof
