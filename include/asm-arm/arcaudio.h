multiline_comment|/* &n; * arcaudio.h&n; *&n; */
macro_line|#ifndef _LINUX_ARCAUDIO_H
DECL|macro|_LINUX_ARCAUDIO_H
mdefine_line|#define _LINUX_ARCAUDIO_H
DECL|macro|ARCAUDIO_MAXCHANNELS
mdefine_line|#define ARCAUDIO_MAXCHANNELS&t;8
DECL|enum|ch_type
r_enum
id|ch_type
(brace
DECL|enumerator|ARCAUDIO_NONE
id|ARCAUDIO_NONE
comma
multiline_comment|/* No sound (muted) */
DECL|enumerator|ARCAUDIO_8BITSIGNED
id|ARCAUDIO_8BITSIGNED
comma
multiline_comment|/* signed 8 bits per samples */
DECL|enumerator|ARCAUDIO_8BITUNSIGNED
id|ARCAUDIO_8BITUNSIGNED
comma
multiline_comment|/* unsigned 8 bits per samples */
DECL|enumerator|ARCAUDIO_16BITSIGNED
id|ARCAUDIO_16BITSIGNED
comma
multiline_comment|/* signed 16 bits per samples (little endian) */
DECL|enumerator|ARCAUDIO_16BITUNSIGNED
id|ARCAUDIO_16BITUNSIGNED
comma
multiline_comment|/* unsigned 16 bits per samples (little endian) */
DECL|enumerator|ARCAUDIO_LOG
id|ARCAUDIO_LOG
multiline_comment|/* Vidc Log */
)brace
suffix:semicolon
multiline_comment|/* &n; * Global information&n; */
DECL|struct|arcaudio
r_struct
id|arcaudio
(brace
DECL|member|sample_rate
r_int
id|sample_rate
suffix:semicolon
multiline_comment|/* sample rate (Hz) */
DECL|member|num_channels
r_int
id|num_channels
suffix:semicolon
multiline_comment|/* number of channels */
DECL|member|volume
r_int
id|volume
suffix:semicolon
multiline_comment|/* overall system volume */
)brace
suffix:semicolon
multiline_comment|/* &n; * Per channel information&n; */
DECL|struct|arcaudio_channel
r_struct
id|arcaudio_channel
(brace
DECL|member|stereo_position
r_int
id|stereo_position
suffix:semicolon
multiline_comment|/* Channel position */
DECL|member|channel_volume
r_int
id|channel_volume
suffix:semicolon
multiline_comment|/* Channel volume */
DECL|member|channel_type
r_enum
id|ch_type
id|channel_type
suffix:semicolon
multiline_comment|/* Type of channel */
DECL|member|buffer_size
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* Size of channel buffer */
)brace
suffix:semicolon
multiline_comment|/* IOCTLS */
DECL|macro|ARCAUDIO_GETINFO
mdefine_line|#define ARCAUDIO_GETINFO&t;0x6101
DECL|macro|ARCAUDIO_SETINFO
mdefine_line|#define ARCAUDIO_SETINFO&t;0x6102
DECL|macro|ARCAUDIO_GETCHANNELINFO
mdefine_line|#define ARCAUDIO_GETCHANNELINFO&t;0x6111
DECL|macro|ARCAUDIO_SETCHANNELINFO
mdefine_line|#define ARCAUDIO_SETCHANNELINFO&t;0x6112
DECL|macro|ARCAUDIO_GETOPTS
mdefine_line|#define ARCAUDIO_GETOPTS&t;0x61f0
DECL|macro|ARCAUDIO_SETOPTS
mdefine_line|#define ARCAUDIO_SETOPTS&t;0x61f1
DECL|macro|ARCAUDIO_OPTSPKR
mdefine_line|#define  ARCAUDIO_OPTSPKR&t;1&lt;&lt;0
macro_line|#endif
eof
