multiline_comment|/* radiotrack (radioreveal) driver for Linux radio support&n; * (c) 1997 M. Kirkwood&n; * Coverted to new API by Alan Cox &lt;Alan.Cox@linux.org&gt;&n; * Various bugfixes and enhancements by Russell Kroll &lt;rkroll@exploits.org&gt;&n; *&n; * History:&n; * 1999-02-24&t;Russell Kroll &lt;rkroll@exploits.org&gt;&n; * &t;&t;Fine tuning/VIDEO_TUNER_LOW&n; *&t;&t;Frequency range expanded to start at 87 MHz&n; *&n; * TODO: Allow for more than one of these foolish entities :-)&n; *&n; * Notes on the hardware (reverse engineered from other peoples&squot;&n; * reverse engineering of AIMS&squot; code :-)&n; *&n; *  Frequency control is done digitally -- ie out(port,encodefreq(95.8));&n; *&n; *  The signal strength query is unsurprisingly inaccurate.  And it seems&n; *  to indicate that (on my card, at least) the frequency setting isn&squot;t&n; *  too great.  (I have to tune up .025MHz from what the freq should be&n; *  to get a report that the thing is tuned.)&n; *&n; *  Volume control is (ugh) analogue:&n; *   out(port, start_increasing_volume);&n; *   wait(a_wee_while);&n; *   out(port, stop_changing_the_volume);&n; *  &n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules &t;&t;&t;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata&t;&t;&t;*/
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region&t;*/
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay&t;&t;&t;*/
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p&t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user&t;&t;*/
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs&t;&t;*/
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_RTRACK_PORT &t;*/
macro_line|#include &lt;asm/semaphore.h&gt;&t;/* Lock for the I/O &t;&t;*/
macro_line|#ifndef CONFIG_RADIO_RTRACK_PORT
DECL|macro|CONFIG_RADIO_RTRACK_PORT
mdefine_line|#define CONFIG_RADIO_RTRACK_PORT -1
macro_line|#endif
DECL|variable|io
r_static
r_int
id|io
op_assign
id|CONFIG_RADIO_RTRACK_PORT
suffix:semicolon
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
suffix:semicolon
DECL|variable|lock
r_static
r_struct
id|semaphore
id|lock
suffix:semicolon
DECL|struct|rt_device
r_struct
id|rt_device
(brace
DECL|member|port
r_int
id|port
suffix:semicolon
DECL|member|curvol
r_int
id|curvol
suffix:semicolon
DECL|member|curfreq
r_int
r_int
id|curfreq
suffix:semicolon
DECL|member|muted
r_int
id|muted
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* local things */
DECL|function|sleep_delay
r_static
r_void
id|sleep_delay
c_func
(paren
r_int
id|n
)paren
(brace
multiline_comment|/* Sleep nicely for &squot;n&squot; uS */
r_int
id|d
op_assign
id|n
op_div
(paren
l_int|1000000
op_div
id|HZ
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|d
)paren
(brace
id|udelay
c_func
(paren
id|n
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Yield CPU time */
r_int
r_int
id|x
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
(paren
id|jiffies
op_minus
id|x
)paren
op_le
id|d
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|rt_decvol
r_static
r_void
id|rt_decvol
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x58
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume down + sigstr + on&t;*/
id|sleep_delay
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xd8
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady + sigstr + on&t;*/
)brace
DECL|function|rt_incvol
r_static
r_void
id|rt_incvol
c_func
(paren
r_void
)paren
(brace
id|outb
c_func
(paren
l_int|0x98
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume up + sigstr + on&t;*/
id|sleep_delay
c_func
(paren
l_int|100000
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xd8
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady + sigstr + on&t;*/
)brace
DECL|function|rt_mute
r_static
r_void
id|rt_mute
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
id|dev-&gt;muted
op_assign
l_int|1
suffix:semicolon
id|down
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xd0
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady, off&t;&t;*/
id|up
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
)brace
DECL|function|rt_setvol
r_static
r_int
id|rt_setvol
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
comma
r_int
id|vol
)paren
(brace
r_int
id|i
suffix:semicolon
id|down
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vol
op_eq
id|dev-&gt;curvol
)paren
(brace
multiline_comment|/* requested volume = current */
r_if
c_cond
(paren
id|dev-&gt;muted
)paren
(brace
multiline_comment|/* user is unmuting the card  */
id|dev-&gt;muted
op_assign
l_int|0
suffix:semicolon
id|outb
(paren
l_int|0xd8
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* enable card */
)brace
id|up
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vol
op_eq
l_int|0
)paren
(brace
multiline_comment|/* volume = 0 means mute the card */
id|outb
c_func
(paren
l_int|0x48
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume down but still &quot;on&quot;&t;*/
id|sleep_delay
c_func
(paren
l_int|2000000
)paren
suffix:semicolon
multiline_comment|/* make sure it&squot;s totally down&t;*/
id|outb
c_func
(paren
l_int|0xd0
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady, off&t;&t;*/
id|dev-&gt;curvol
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* track the volume state!&t;*/
id|up
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|dev-&gt;muted
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vol
OG
id|dev-&gt;curvol
)paren
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;curvol
suffix:semicolon
id|i
OL
id|vol
suffix:semicolon
id|i
op_increment
)paren
(brace
id|rt_incvol
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_for
c_loop
(paren
id|i
op_assign
id|dev-&gt;curvol
suffix:semicolon
id|i
OG
id|vol
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|rt_decvol
c_func
(paren
)paren
suffix:semicolon
)brace
id|dev-&gt;curvol
op_assign
id|vol
suffix:semicolon
id|up
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* the 128+64 on these outb&squot;s is to keep the volume stable while tuning &n; * without them, the volume _will_ creep up with each frequency change&n; * and bit 4 (+16) is to keep the signal strength meter enabled&n; */
DECL|function|send_0_byte
r_void
id|send_0_byte
c_func
(paren
r_int
id|port
comma
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev-&gt;curvol
op_eq
l_int|0
)paren
op_logical_or
(paren
id|dev-&gt;muted
)paren
)paren
(brace
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* wr-enable + data low */
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|2
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* clock */
)brace
r_else
(brace
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|8
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* on + wr-enable + data low */
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|8
op_plus
l_int|2
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* clock */
)brace
id|sleep_delay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|send_1_byte
r_void
id|send_1_byte
c_func
(paren
r_int
id|port
comma
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev-&gt;curvol
op_eq
l_int|0
)paren
op_logical_or
(paren
id|dev-&gt;muted
)paren
)paren
(brace
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|4
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* wr-enable+data high */
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|4
op_plus
l_int|2
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* clock */
)brace
r_else
(brace
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|8
op_plus
l_int|4
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* on+wr-enable+data high */
id|outb_p
c_func
(paren
l_int|128
op_plus
l_int|64
op_plus
l_int|16
op_plus
l_int|8
op_plus
l_int|4
op_plus
l_int|2
op_plus
l_int|1
comma
id|port
)paren
suffix:semicolon
multiline_comment|/* clock */
)brace
id|sleep_delay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
)brace
DECL|function|rt_setfreq
r_static
r_int
id|rt_setfreq
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
comma
r_int
r_int
id|freq
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* adapted from radio-aztech.c */
multiline_comment|/* now uses VIDEO_TUNER_LOW for fine tuning */
id|freq
op_add_assign
l_int|171200
suffix:semicolon
multiline_comment|/* Add 10.7 MHz IF &t;&t;*/
id|freq
op_div_assign
l_int|800
suffix:semicolon
multiline_comment|/* Convert to 50 kHz units&t;*/
id|down
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
multiline_comment|/* Stop other ops interfering */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/*  0: LSB of frequency&t;&t;*/
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|13
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/*   : frequency bits (1-13)&t;*/
r_if
c_cond
(paren
id|freq
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|send_1_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
r_else
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 14: test bit - always 0    */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 15: test bit - always 0    */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 16: band data 0 - always 0 */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 17: band data 1 - always 0 */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 18: band data 2 - always 0 */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 19: time base - always 0   */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 20: spacing (0 = 25 kHz)   */
id|send_1_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 21: spacing (1 = 25 kHz)   */
id|send_0_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 22: spacing (0 = 25 kHz)   */
id|send_1_byte
(paren
id|io
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* 23: AM/FM (FM = 1, always) */
r_if
c_cond
(paren
(paren
id|dev-&gt;curvol
op_eq
l_int|0
)paren
op_logical_or
(paren
id|dev-&gt;muted
)paren
)paren
id|outb
(paren
l_int|0xd0
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady + sigstr */
r_else
id|outb
(paren
l_int|0xd8
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume steady + sigstr + on */
id|up
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_getsigstr
r_static
r_int
id|rt_getsigstr
c_func
(paren
r_struct
id|rt_device
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
)paren
op_amp
l_int|2
)paren
multiline_comment|/* bit set = no signal present&t;*/
r_return
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* signal present&t;&t;*/
)brace
DECL|function|rt_ioctl
r_static
r_int
id|rt_ioctl
c_func
(paren
r_struct
id|video_device
op_star
id|dev
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_struct
id|rt_device
op_star
id|rt
op_assign
id|dev-&gt;priv
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|VIDIOCGCAP
suffix:colon
(brace
r_struct
id|video_capability
id|v
suffix:semicolon
id|v.type
op_assign
id|VID_TYPE_TUNER
suffix:semicolon
id|v.channels
op_assign
l_int|1
suffix:semicolon
id|v.audios
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* No we don&squot;t do pictures */
id|v.maxwidth
op_assign
l_int|0
suffix:semicolon
id|v.maxheight
op_assign
l_int|0
suffix:semicolon
id|v.minwidth
op_assign
l_int|0
suffix:semicolon
id|v.minheight
op_assign
l_int|0
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;RadioTrack&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGTUNER
suffix:colon
(brace
r_struct
id|video_tuner
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
)paren
(brace
multiline_comment|/* Only 1 tuner */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|v.rangelow
op_assign
(paren
l_int|87
op_star
l_int|16000
)paren
suffix:semicolon
id|v.rangehigh
op_assign
(paren
l_int|108
op_star
l_int|16000
)paren
suffix:semicolon
id|v.flags
op_assign
id|VIDEO_TUNER_LOW
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;FM&quot;
)paren
suffix:semicolon
id|v.signal
op_assign
l_int|0xFFFF
op_star
id|rt_getsigstr
c_func
(paren
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSTUNER
suffix:colon
(brace
r_struct
id|video_tuner
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.tuner
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/* Only 1 tuner so no setting needed ! */
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCGFREQ
suffix:colon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|rt-&gt;curfreq
comma
r_sizeof
(paren
id|rt-&gt;curfreq
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|VIDIOCSFREQ
suffix:colon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rt-&gt;curfreq
comma
id|arg
comma
r_sizeof
(paren
id|rt-&gt;curfreq
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|rt_setfreq
c_func
(paren
id|rt
comma
id|rt-&gt;curfreq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
id|v
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|v
comma
l_int|0
comma
r_sizeof
(paren
id|v
)paren
)paren
suffix:semicolon
id|v.flags
op_or_assign
id|VIDEO_AUDIO_MUTABLE
op_or
id|VIDEO_AUDIO_VOLUME
suffix:semicolon
id|v.volume
op_assign
id|rt-&gt;curvol
op_star
l_int|6554
suffix:semicolon
id|v.step
op_assign
l_int|6554
suffix:semicolon
id|strcpy
c_func
(paren
id|v.name
comma
l_string|&quot;Radio&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|arg
comma
op_amp
id|v
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
id|v
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|v
comma
id|arg
comma
r_sizeof
(paren
id|v
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.audio
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|v.flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
id|rt_mute
c_func
(paren
id|rt
)paren
suffix:semicolon
)brace
r_else
id|rt_setvol
c_func
(paren
id|rt
comma
id|v.volume
op_div
l_int|6554
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|ENOIOCTLCMD
suffix:semicolon
)brace
)brace
DECL|function|rt_open
r_static
r_int
id|rt_open
c_func
(paren
r_struct
id|video_device
op_star
id|dev
comma
r_int
id|flags
)paren
(brace
r_if
c_cond
(paren
id|users
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|users
op_increment
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rt_close
r_static
r_void
id|rt_close
c_func
(paren
r_struct
id|video_device
op_star
id|dev
)paren
(brace
id|users
op_decrement
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|rtrack_unit
r_static
r_struct
id|rt_device
id|rtrack_unit
suffix:semicolon
DECL|variable|rtrack_radio
r_static
r_struct
id|video_device
id|rtrack_radio
op_assign
(brace
l_string|&quot;RadioTrack radio&quot;
comma
id|VID_TYPE_TUNER
comma
id|VID_HARDWARE_RTRACK
comma
id|rt_open
comma
id|rt_close
comma
l_int|NULL
comma
multiline_comment|/* Can&squot;t read  (no capture ability) */
l_int|NULL
comma
multiline_comment|/* Can&squot;t write */
l_int|NULL
comma
multiline_comment|/* No poll */
id|rt_ioctl
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|rtrack_init
r_static
r_int
id|__init
id|rtrack_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|io
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;You must set an I/O address with io=0x???&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|io
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtrack: port 0x%x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|rtrack_radio.priv
op_assign
op_amp
id|rtrack_unit
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|rtrack_radio
comma
id|VFL_TYPE_RADIO
)paren
op_eq
op_minus
l_int|1
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|request_region
c_func
(paren
id|io
comma
l_int|2
comma
l_string|&quot;rtrack&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;AIMSlab RadioTrack/RadioReveal card driver.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Set up the I/O locking */
id|init_MUTEX
c_func
(paren
op_amp
id|lock
)paren
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
multiline_comment|/* this ensures that the volume is all the way down  */
id|outb
c_func
(paren
l_int|0x48
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* volume down but still &quot;on&quot;&t;*/
id|sleep_delay
c_func
(paren
l_int|2000000
)paren
suffix:semicolon
multiline_comment|/* make sure it&squot;s totally down&t;*/
id|outb
c_func
(paren
l_int|0xc0
comma
id|io
)paren
suffix:semicolon
multiline_comment|/* steady volume, mute card&t;*/
id|rtrack_unit.curvol
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;M.Kirkwood&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the RadioTrack/RadioReveal radio card.&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM_DESC
c_func
(paren
id|io
comma
l_string|&quot;I/O address of the RadioTrack card (0x20f or 0x30f)&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|cleanup_rtrack_module
r_static
r_void
id|__exit
id|cleanup_rtrack_module
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|rtrack_radio
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|2
)paren
suffix:semicolon
)brace
DECL|variable|rtrack_init
id|module_init
c_func
(paren
id|rtrack_init
)paren
suffix:semicolon
DECL|variable|cleanup_rtrack_module
id|module_exit
c_func
(paren
id|cleanup_rtrack_module
)paren
suffix:semicolon
eof
