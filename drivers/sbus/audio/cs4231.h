multiline_comment|/*&n; * drivers/sbus/audio/cs4231.h&n; *&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; * Copyright (C) 1997 Derrick J. Brashear (shadow@dementia.org)&n; */
macro_line|#ifndef _CS4231_H_
DECL|macro|_CS4231_H_
mdefine_line|#define _CS4231_H_
macro_line|#include &lt;linux/types.h&gt;
DECL|struct|cs4231_regs
r_struct
id|cs4231_regs
(brace
DECL|member|iar
id|u_char
id|iar
suffix:semicolon
multiline_comment|/* Index Address Register */
DECL|member|pad0
id|u_char
id|pad0
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|idr
id|u_char
id|idr
suffix:semicolon
multiline_comment|/* Indexed Data Register */
DECL|member|pad1
id|u_char
id|pad1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|statr
id|u_char
id|statr
suffix:semicolon
multiline_comment|/* Status Register */
DECL|member|pad2
id|u_char
id|pad2
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|piodr
id|u_char
id|piodr
suffix:semicolon
multiline_comment|/* PIO Data Register I/O */
DECL|member|pad3
id|u_char
id|pad3
(braket
l_int|3
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cs4231_dma
r_struct
id|cs4231_dma
(brace
DECL|member|dmacsr
id|u_long
id|dmacsr
suffix:semicolon
multiline_comment|/* APC CSR */
DECL|member|dmapad
id|u_long
id|dmapad
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|dmacva
id|u_long
id|dmacva
suffix:semicolon
multiline_comment|/* Capture Virtual Address */
DECL|member|dmacc
id|u_long
id|dmacc
suffix:semicolon
multiline_comment|/* Capture Count */
DECL|member|dmacnva
id|u_long
id|dmacnva
suffix:semicolon
multiline_comment|/* Capture Next VAddress */
DECL|member|dmacnc
id|u_long
id|dmacnc
suffix:semicolon
multiline_comment|/* Capture Next Count */
DECL|member|dmapva
id|u_long
id|dmapva
suffix:semicolon
multiline_comment|/* Playback Virtual Address */
DECL|member|dmapc
id|u_long
id|dmapc
suffix:semicolon
multiline_comment|/* Playback Count */
DECL|member|dmapnva
id|u_long
id|dmapnva
suffix:semicolon
multiline_comment|/* Playback Next VAddress */
DECL|member|dmapnc
id|u_long
id|dmapnc
suffix:semicolon
multiline_comment|/* Playback Next Count */
)brace
suffix:semicolon
DECL|struct|cs4231_chip
r_struct
id|cs4231_chip
(brace
DECL|member|pioregs
r_struct
id|cs4231_regs
id|pioregs
suffix:semicolon
DECL|member|dmaregs
r_struct
id|cs4231_dma
id|dmaregs
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|cs4231_stream_info
r_struct
id|cs4231_stream_info
(brace
DECL|member|sample_rate
r_int
r_int
id|sample_rate
suffix:semicolon
multiline_comment|/* samples per second */
DECL|member|channels
r_int
r_int
id|channels
suffix:semicolon
multiline_comment|/* number of interleaved channels */
DECL|member|precision
r_int
r_int
id|precision
suffix:semicolon
multiline_comment|/* bit-width of each sample */
DECL|member|encoding
r_int
r_int
id|encoding
suffix:semicolon
multiline_comment|/* data encoding method */
DECL|member|gain
r_int
r_int
id|gain
suffix:semicolon
multiline_comment|/* gain level: 0 - 255 */
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|CS_TIMEOUT
mdefine_line|#define CS_TIMEOUT      9000000
DECL|macro|GAIN_SET
mdefine_line|#define GAIN_SET(var, gain)     ((var &amp; ~(0x3f)) | gain)
DECL|macro|RECGAIN_SET
mdefine_line|#define RECGAIN_SET(var, gain)  ((var &amp; ~(0x1f)) | gain)
DECL|macro|IAR_AUTOCAL_BEGIN
mdefine_line|#define IAR_AUTOCAL_BEGIN       0x40
DECL|macro|IAR_AUTOCAL_END
mdefine_line|#define IAR_AUTOCAL_END         ~(0x40)
DECL|macro|IAR_NOT_READY
mdefine_line|#define IAR_NOT_READY            0x80    /* 80h not ready CODEC state */
DECL|macro|MIC_ENABLE
mdefine_line|#define MIC_ENABLE(var)         ((var &amp; 0x2f) | 0x80)
DECL|macro|LINE_ENABLE
mdefine_line|#define LINE_ENABLE(var)        (var &amp; 0x2f)
DECL|macro|CDROM_ENABLE
mdefine_line|#define CDROM_ENABLE(var)       ((var &amp; 0x2f) | 0x40)
DECL|macro|OUTCR_MUTE
mdefine_line|#define OUTCR_MUTE              0x80
DECL|macro|OUTCR_UNMUTE
mdefine_line|#define OUTCR_UNMUTE            ~0x80
multiline_comment|/* 8 */
DECL|macro|DEFAULT_DATA_FMAT
mdefine_line|#define DEFAULT_DATA_FMAT               0x20
multiline_comment|/* 10 */
DECL|macro|PINCR_LINE_MUTE
mdefine_line|#define PINCR_LINE_MUTE         0x40
DECL|macro|PINCR_HDPH_MUTE
mdefine_line|#define PINCR_HDPH_MUTE         0x80
multiline_comment|/* 11 */
DECL|macro|AUTOCAL_IN_PROGRESS
mdefine_line|#define AUTOCAL_IN_PROGRESS      0x20
multiline_comment|/* 12 */
DECL|macro|MISC_IR_MODE2
mdefine_line|#define MISC_IR_MODE2           0x40
multiline_comment|/* 13 */
DECL|macro|LOOPB_ON
mdefine_line|#define LOOPB_ON                0x01
DECL|macro|LOOPB_OFF
mdefine_line|#define LOOPB_OFF               0x00
multiline_comment|/* 16 */
DECL|macro|OLB_ENABLE
mdefine_line|#define OLB_ENABLE              0x80
multiline_comment|/* 17 */
DECL|macro|HPF_ON
mdefine_line|#define HPF_ON                  0x01
DECL|macro|XTALE_ON
mdefine_line|#define XTALE_ON                0x20
DECL|macro|MONO_IOCR_MUTE
mdefine_line|#define MONO_IOCR_MUTE       0x40;
multiline_comment|/* 30 */
DECL|macro|CS4231A
mdefine_line|#define CS4231A         0x20
DECL|macro|APC_CODEC_PDN
mdefine_line|#define APC_CODEC_PDN   0x20            
DECL|macro|APC_RESET
mdefine_line|#define APC_RESET       0x01            
DECL|macro|CS4231_DEFAULT_PLAYGAIN
mdefine_line|#define CS4231_DEFAULT_PLAYGAIN     (132)
DECL|macro|CS4231_DEFAULT_RECGAIN
mdefine_line|#define CS4231_DEFAULT_RECGAIN      (126)
DECL|macro|CS4231_MIN_ATEN
mdefine_line|#define CS4231_MIN_ATEN     (0)
DECL|macro|CS4231_MAX_ATEN
mdefine_line|#define CS4231_MAX_ATEN     (31)
DECL|macro|CS4231_MAX_DEV_ATEN
mdefine_line|#define CS4231_MAX_DEV_ATEN (63)
DECL|macro|CS4231_MIN_GAIN
mdefine_line|#define CS4231_MIN_GAIN     (0)
DECL|macro|CS4231_MAX_GAIN
mdefine_line|#define CS4231_MAX_GAIN     (15)
DECL|macro|CS4231_MON_MIN_ATEN
mdefine_line|#define CS4231_MON_MIN_ATEN         (0)
DECL|macro|CS4231_MON_MAX_ATEN
mdefine_line|#define CS4231_MON_MAX_ATEN         (63)
DECL|macro|CS4231_PRECISION
mdefine_line|#define CS4231_PRECISION    (8)             /* Bits per sample unit */
DECL|macro|CS4231_CHANNELS
mdefine_line|#define CS4231_CHANNELS     (1)             /* Channels per sample frame */
DECL|macro|CS4231_RATE
mdefine_line|#define CS4231_RATE   (8000)          
DECL|macro|AUDIO_ENCODING_NONE
mdefine_line|#define AUDIO_ENCODING_NONE     (0) /* no encoding assigned */
DECL|macro|AUDIO_ENCODING_ULAW
mdefine_line|#define AUDIO_ENCODING_ULAW     (1) /* u-law encoding */
DECL|macro|AUDIO_ENCODING_ALAW
mdefine_line|#define AUDIO_ENCODING_ALAW     (2) /* A-law encoding */
DECL|macro|AUDIO_ENCODING_LINEAR
mdefine_line|#define AUDIO_ENCODING_LINEAR   (3) /* Linear PCM encoding */
DECL|macro|AUDIO_ENCODING_DVI
mdefine_line|#define AUDIO_ENCODING_DVI      (104) /* DVI ADPCM */
DECL|macro|AUDIO_ENCODING_LINEAR8
mdefine_line|#define AUDIO_ENCODING_LINEAR8  (105) /* 8 bit UNSIGNED */
DECL|macro|AUDIO_LEFT_BALANCE
mdefine_line|#define AUDIO_LEFT_BALANCE      (0)
DECL|macro|AUDIO_MID_BALANCE
mdefine_line|#define AUDIO_MID_BALANCE       (32)
DECL|macro|AUDIO_RIGHT_BALANCE
mdefine_line|#define AUDIO_RIGHT_BALANCE     (64)
DECL|macro|AUDIO_BALANCE_SHIFT
mdefine_line|#define AUDIO_BALANCE_SHIFT     (3)
DECL|macro|AUDIO_SPEAKER
mdefine_line|#define AUDIO_SPEAKER           0x01
DECL|macro|AUDIO_HEADPHONE
mdefine_line|#define AUDIO_HEADPHONE         0x02
DECL|macro|AUDIO_LINE_OUT
mdefine_line|#define AUDIO_LINE_OUT          0x04
DECL|macro|AUDIO_MICROPHONE
mdefine_line|#define AUDIO_MICROPHONE        0x01
DECL|macro|AUDIO_LINE_IN
mdefine_line|#define AUDIO_LINE_IN           0x02
DECL|macro|AUDIO_INTERNAL_CD_IN
mdefine_line|#define AUDIO_INTERNAL_CD_IN    0x04
DECL|macro|AUDIO_MAX_GAIN
mdefine_line|#define AUDIO_MAX_GAIN  (255)
macro_line|#endif
eof
