multiline_comment|/*&n; * drivers/sbus/audio/audio.h&n; *&n; * Sparc Audio Midlayer&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@noc.rutgers.edu)&n; */
macro_line|#ifndef _AUDIO_H_
DECL|macro|_AUDIO_H_
mdefine_line|#define _AUDIO_H_
multiline_comment|/*&n; *&t;SunOS/Solaris /dev/audio interface&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
multiline_comment|/*&n; * This structure contains state information for audio device IO streams.&n; */
DECL|struct|audio_prinfo
r_typedef
r_struct
id|audio_prinfo
(brace
multiline_comment|/*&n;&t; * The following values describe the audio data encoding.&n;&t; */
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
multiline_comment|/*&n;&t; * The following values control audio device configuration&n;&t; */
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
multiline_comment|/* selected I/O port (see below) */
DECL|member|avail_ports
r_int
r_int
id|avail_ports
suffix:semicolon
multiline_comment|/* available I/O ports (see below) */
DECL|member|_xxx
r_int
r_int
id|_xxx
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|member|buffer_size
r_int
r_int
id|buffer_size
suffix:semicolon
multiline_comment|/* I/O buffer size */
multiline_comment|/*&n;&t; * The following values describe driver state&n;&t; */
DECL|member|samples
r_int
r_int
id|samples
suffix:semicolon
multiline_comment|/* number of samples converted */
DECL|member|eof
r_int
r_int
id|eof
suffix:semicolon
multiline_comment|/* End Of File counter (play only) */
DECL|member|pause
r_int
r_char
id|pause
suffix:semicolon
multiline_comment|/* non-zero for pause, zero to resume */
DECL|member|error
r_int
r_char
id|error
suffix:semicolon
multiline_comment|/* non-zero if overflow/underflow */
DECL|member|waiting
r_int
r_char
id|waiting
suffix:semicolon
multiline_comment|/* non-zero if a process wants access */
DECL|member|balance
r_int
r_char
id|balance
suffix:semicolon
multiline_comment|/* stereo channel balance */
DECL|member|minordev
r_int
r_int
id|minordev
suffix:semicolon
multiline_comment|/*&n;&t; * The following values are read-only state flags&n;&t; */
DECL|member|open
r_int
r_char
id|open
suffix:semicolon
multiline_comment|/* non-zero if open access permitted */
DECL|member|active
r_int
r_char
id|active
suffix:semicolon
multiline_comment|/* non-zero if I/O is active */
DECL|typedef|audio_prinfo_t
)brace
id|audio_prinfo_t
suffix:semicolon
multiline_comment|/*&n; * This structure describes the current state of the audio device.&n; */
DECL|struct|audio_info
r_typedef
r_struct
id|audio_info
(brace
multiline_comment|/*&n;&t; * Per-stream information&n;&t; */
DECL|member|play
id|audio_prinfo_t
id|play
suffix:semicolon
multiline_comment|/* output status information */
DECL|member|record
id|audio_prinfo_t
id|record
suffix:semicolon
multiline_comment|/* input status information */
multiline_comment|/*&n;&t; * Per-unit/channel information&n;&t; */
DECL|member|monitor_gain
r_int
r_int
id|monitor_gain
suffix:semicolon
multiline_comment|/* input to output mix: 0 - 255 */
DECL|member|output_muted
r_int
r_char
id|output_muted
suffix:semicolon
multiline_comment|/* non-zero if output is muted */
DECL|member|_xxx
r_int
r_char
id|_xxx
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|member|_yyy
r_int
r_int
id|_yyy
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* Reserved for future use */
DECL|typedef|audio_info_t
)brace
id|audio_info_t
suffix:semicolon
multiline_comment|/*&n; * Audio encoding types&n; */
DECL|macro|AUDIO_ENCODING_NONE
mdefine_line|#define&t;AUDIO_ENCODING_NONE&t;(0)&t;/* no encoding assigned&t;*/
DECL|macro|AUDIO_ENCODING_ULAW
mdefine_line|#define&t;AUDIO_ENCODING_ULAW&t;(1)&t;/* u-law encoding&t;*/
DECL|macro|AUDIO_ENCODING_ALAW
mdefine_line|#define&t;AUDIO_ENCODING_ALAW&t;(2)&t;/* A-law encoding&t;*/
DECL|macro|AUDIO_ENCODING_LINEAR
mdefine_line|#define&t;AUDIO_ENCODING_LINEAR&t;(3)&t;/* Linear PCM encoding&t;*/
DECL|macro|AUDIO_ENCODING_DVI
mdefine_line|#define&t;AUDIO_ENCODING_DVI&t;(104)&t;/* DVI ADPCM&t;&t;*/
DECL|macro|AUDIO_ENCODING_LINEAR8
mdefine_line|#define&t;AUDIO_ENCODING_LINEAR8&t;(105)&t;/* 8 bit UNSIGNED&t;*/
multiline_comment|/*&n; * These ranges apply to record, play, and monitor gain values&n; */
DECL|macro|AUDIO_MIN_GAIN
mdefine_line|#define&t;AUDIO_MIN_GAIN&t;(0)&t;/* minimum gain value */
DECL|macro|AUDIO_MAX_GAIN
mdefine_line|#define&t;AUDIO_MAX_GAIN&t;(255)&t;/* maximum gain value */
multiline_comment|/*&n; * These values apply to the balance field to adjust channel gain values&n; */
DECL|macro|AUDIO_LEFT_BALANCE
mdefine_line|#define&t;AUDIO_LEFT_BALANCE&t;(0)&t;/* left channel only&t;*/
DECL|macro|AUDIO_MID_BALANCE
mdefine_line|#define&t;AUDIO_MID_BALANCE&t;(32)&t;/* equal left/right channel */
DECL|macro|AUDIO_RIGHT_BALANCE
mdefine_line|#define&t;AUDIO_RIGHT_BALANCE&t;(64)&t;/* right channel only&t;*/
DECL|macro|AUDIO_BALANCE_SHIFT
mdefine_line|#define&t;AUDIO_BALANCE_SHIFT&t;(3)
multiline_comment|/*&n; * Generic minimum/maximum limits for number of channels, both modes&n; */
DECL|macro|AUDIO_MIN_PLAY_CHANNELS
mdefine_line|#define&t;AUDIO_MIN_PLAY_CHANNELS&t;(1)
DECL|macro|AUDIO_MAX_PLAY_CHANNELS
mdefine_line|#define&t;AUDIO_MAX_PLAY_CHANNELS&t;(4)
DECL|macro|AUDIO_MIN_REC_CHANNELS
mdefine_line|#define&t;AUDIO_MIN_REC_CHANNELS&t;(1)
DECL|macro|AUDIO_MAX_REC_CHANNELS
mdefine_line|#define&t;AUDIO_MAX_REC_CHANNELS&t;(4)
multiline_comment|/*&n; * Generic minimum/maximum limits for sample precision&n; */
DECL|macro|AUDIO_MIN_PLAY_PRECISION
mdefine_line|#define&t;AUDIO_MIN_PLAY_PRECISION&t;(8)
DECL|macro|AUDIO_MAX_PLAY_PRECISION
mdefine_line|#define&t;AUDIO_MAX_PLAY_PRECISION&t;(32)
DECL|macro|AUDIO_MIN_REC_PRECISION
mdefine_line|#define&t;AUDIO_MIN_REC_PRECISION&t;&t;(8)
DECL|macro|AUDIO_MAX_REC_PRECISION
mdefine_line|#define&t;AUDIO_MAX_REC_PRECISION&t;&t;(32)
multiline_comment|/*&n; * Define some convenient names for typical audio ports&n; */
multiline_comment|/*&n; * output ports (several may be enabled simultaneously)&n; */
DECL|macro|AUDIO_SPEAKER
mdefine_line|#define&t;AUDIO_SPEAKER&t;&t;0x01&t;/* output to built-in speaker */
DECL|macro|AUDIO_HEADPHONE
mdefine_line|#define&t;AUDIO_HEADPHONE&t;&t;0x02&t;/* output to headphone jack */
DECL|macro|AUDIO_LINE_OUT
mdefine_line|#define&t;AUDIO_LINE_OUT&t;&t;0x04&t;/* output to line out&t; */
multiline_comment|/*&n; * input ports (usually only one at a time)&n; */
DECL|macro|AUDIO_MICROPHONE
mdefine_line|#define&t;AUDIO_MICROPHONE&t;0x01&t;/* input from microphone */
DECL|macro|AUDIO_LINE_IN
mdefine_line|#define&t;AUDIO_LINE_IN&t;&t;0x02&t;/* input from line in&t; */
DECL|macro|AUDIO_CD
mdefine_line|#define&t;AUDIO_CD&t;&t;0x04&t;/* input from on-board CD inputs */
DECL|macro|AUDIO_INTERNAL_CD_IN
mdefine_line|#define&t;AUDIO_INTERNAL_CD_IN&t;AUDIO_CD&t;/* input from internal CDROM */
multiline_comment|/*&n; * This macro initializes an audio_info structure to &squot;harmless&squot; values.&n; * Note that (~0) might not be a harmless value for a flag that was&n; * a signed int.&n; */
DECL|macro|AUDIO_INITINFO
mdefine_line|#define&t;AUDIO_INITINFO(i)&t;{&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned int&t;*__x__;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (__x__ = (unsigned int *)(i);&t;&t;&t;&t;&bslash;&n;&t;    (char *) __x__ &lt; (((char *)(i)) + sizeof (audio_info_t));&t;&bslash;&n;&t;    *__x__++ = ~0);&t;&t;&t;&t;&t;&t;&bslash;&n;}
multiline_comment|/*&n; * Parameter for the AUDIO_GETDEV ioctl to determine current&n; * audio devices.&n; */
DECL|macro|MAX_AUDIO_DEV_LEN
mdefine_line|#define&t;MAX_AUDIO_DEV_LEN&t;(16)
DECL|struct|audio_device
r_typedef
r_struct
id|audio_device
(brace
DECL|member|name
r_char
id|name
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|member|version
r_char
id|version
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|member|config
r_char
id|config
(braket
id|MAX_AUDIO_DEV_LEN
)braket
suffix:semicolon
DECL|typedef|audio_device_t
)brace
id|audio_device_t
suffix:semicolon
multiline_comment|/*&n; * Ioctl calls for the audio device.&n; */
multiline_comment|/*&n; * AUDIO_GETINFO retrieves the current state of the audio device.&n; *&n; * AUDIO_SETINFO copies all fields of the audio_info structure whose&n; * values are not set to the initialized value (-1) to the device state.&n; * It performs an implicit AUDIO_GETINFO to return the new state of the&n; * device.  Note that the record.samples and play.samples fields are set&n; * to the last value before the AUDIO_SETINFO took effect.  This allows&n; * an application to reset the counters while atomically retrieving the&n; * last value.&n; *&n; * AUDIO_DRAIN suspends the calling process until the write buffers are&n; * empty.&n; *&n; * AUDIO_GETDEV returns a structure of type audio_device_t which contains&n; * three strings.  The string &quot;name&quot; is a short identifying string (for&n; * example, the SBus Fcode name string), the string &quot;version&quot; identifies&n; * the current version of the device, and the &quot;config&quot; string identifies&n; * the specific configuration of the audio stream.  All fields are&n; * device-dependent -- see the device specific manual pages for details.&n; */
DECL|macro|AUDIO_GETINFO
mdefine_line|#define&t;AUDIO_GETINFO&t;_IOR(&squot;A&squot;, 1, audio_info_t)
DECL|macro|AUDIO_SETINFO
mdefine_line|#define&t;AUDIO_SETINFO&t;_IOWR(&squot;A&squot;, 2, audio_info_t)
DECL|macro|AUDIO_DRAIN
mdefine_line|#define&t;AUDIO_DRAIN&t;_IO(&squot;A&squot;, 3)
DECL|macro|AUDIO_GETDEV
mdefine_line|#define&t;AUDIO_GETDEV&t;_IOR(&squot;A&squot;, 4, audio_device_t)
multiline_comment|/*&n; * The following ioctl sets the audio device into an internal loopback mode,&n; * if the hardware supports this.  The argument is TRUE to set loopback,&n; * FALSE to reset to normal operation.  If the hardware does not support&n; * internal loopback, the ioctl should fail with EINVAL.&n; */
DECL|macro|AUDIO_DIAG_LOOPBACK
mdefine_line|#define&t;AUDIO_DIAG_LOOPBACK&t;_IOW(&squot;A&squot;, 101, int)
macro_line|#ifdef notneeded
multiline_comment|/*&n; * Structure sent up as a M_PROTO message on trace streams&n; */
DECL|typedef|audtrace_hdr_t
r_typedef
r_struct
id|audtrace_hdr
id|audtrace_hdr_t
suffix:semicolon
DECL|struct|audtrace_hdr
r_struct
id|audtrace_hdr
(brace
DECL|member|seq
r_int
r_int
id|seq
suffix:semicolon
multiline_comment|/* Sequence number (per-aud_stream) */
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* device-dependent */
DECL|member|timestamp
r_struct
id|timeval
id|timestamp
suffix:semicolon
DECL|member|_f
r_char
id|_f
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* filler */
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *&t;Linux kernel internal implementation.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
DECL|macro|SDF_OPEN_WRITE
mdefine_line|#define&t;SDF_OPEN_WRITE&t;0x00000001
DECL|macro|SDF_OPEN_READ
mdefine_line|#define&t;SDF_OPEN_READ&t;0x00000002
DECL|struct|sparcaudio_driver
r_struct
id|sparcaudio_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|ops
r_struct
id|sparcaudio_operations
op_star
id|ops
suffix:semicolon
DECL|member|private
r_void
op_star
r_private
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* Processes blocked on open() sit here. */
DECL|member|open_wait
r_struct
id|wait_queue
op_star
id|open_wait
suffix:semicolon
multiline_comment|/* Task queue for this driver&squot;s bottom half. */
DECL|member|tqueue
r_struct
id|tq_struct
id|tqueue
suffix:semicolon
multiline_comment|/* Support for a circular queue of output buffers. */
DECL|member|output_buffers
id|__u8
op_star
op_star
id|output_buffers
suffix:semicolon
DECL|member|output_sizes
r_int
op_star
id|output_sizes
suffix:semicolon
DECL|member|num_output_buffers
DECL|member|output_front
DECL|member|output_rear
r_int
id|num_output_buffers
comma
id|output_front
comma
id|output_rear
suffix:semicolon
DECL|member|output_count
DECL|member|output_active
r_int
id|output_count
comma
id|output_active
suffix:semicolon
DECL|member|output_write_wait
DECL|member|output_drain_wait
r_struct
id|wait_queue
op_star
id|output_write_wait
comma
op_star
id|output_drain_wait
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sparcaudio_operations
r_struct
id|sparcaudio_operations
(brace
DECL|member|open
r_int
(paren
op_star
id|open
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
DECL|member|release
r_void
(paren
op_star
id|release
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
DECL|member|ioctl
r_int
(paren
op_star
id|ioctl
)paren
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* Ask driver to begin playing a buffer. */
DECL|member|start_output
r_void
(paren
op_star
id|start_output
)paren
(paren
r_struct
id|sparcaudio_driver
op_star
comma
id|__u8
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Ask driver to stop playing a buffer. */
DECL|member|stop_output
r_void
(paren
op_star
id|stop_output
)paren
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* Ask driver to begin recording into a buffer. */
DECL|member|start_input
r_void
(paren
op_star
id|start_input
)paren
(paren
r_struct
id|sparcaudio_driver
op_star
comma
id|__u8
op_star
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* Ask driver to stop recording. */
DECL|member|stop_input
r_void
(paren
op_star
id|stop_input
)paren
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
multiline_comment|/* Return driver name/version to caller. (/dev/audio specific) */
DECL|member|sunaudio_getdev
r_void
(paren
op_star
id|sunaudio_getdev
)paren
(paren
r_struct
id|sparcaudio_driver
op_star
comma
id|audio_device_t
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_sparcaudio_driver
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_sparcaudio_driver
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sparcaudio_output_done
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
r_extern
r_void
id|sparcaudio_input_done
c_func
(paren
r_struct
id|sparcaudio_driver
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sparcaudio_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|amd7930_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|cs4231_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof