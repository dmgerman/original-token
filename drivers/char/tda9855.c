multiline_comment|/*&n; * For the TDA9855 chip (afaik, only the Diamond DTV2000 has this)&n; * This driver will not complain if used with a TDA9850 or any &n; * other i2c device with the same address.&n; *&n; * Copyright (c) 1999 Steve VanDeBogart (vandebo@uclink.berkeley.edu)&n; * This code is placed under the terms of the GNU General Public License&n; * Based on tda8425.c by Greg Alexander (c) 1998&n; *&n; * TODO:&n; *   Fix channel change bug - sound goes out when changeing channels, mute&n; *                            and unmote to fix.&n; *   Fine tune sound&n; *   Get rest of capabilities into video_audio struct...&n; *&n; *  Revision: 0.1 &n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/i2c.h&gt;
macro_line|#include &lt;linux/i2c-algo-bit.h&gt;
macro_line|#include &quot;bttv.h&quot;
macro_line|#include &quot;audiochip.h&quot;
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* insmod parameter */
multiline_comment|/* Addresses to scan */
DECL|macro|I2C_TDA9855_L
mdefine_line|#define I2C_TDA9855_L        0xb4
DECL|macro|I2C_TDA9855_H
mdefine_line|#define I2C_TDA9855_H        0xb6
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|normal_i2c_range
r_static
r_int
r_int
id|normal_i2c_range
(braket
)braket
op_assign
(brace
id|I2C_TDA9855_L
op_rshift
l_int|1
comma
id|I2C_TDA9855_H
op_rshift
l_int|1
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe
r_static
r_int
r_int
id|probe
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|probe_range
r_static
r_int
r_int
id|probe_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore
r_static
r_int
r_int
id|ignore
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|ignore_range
r_static
r_int
r_int
id|ignore_range
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|force
r_static
r_int
r_int
id|force
(braket
l_int|2
)braket
op_assign
(brace
id|I2C_CLIENT_END
comma
id|I2C_CLIENT_END
)brace
suffix:semicolon
DECL|variable|addr_data
r_static
r_struct
id|i2c_client_address_data
id|addr_data
op_assign
(brace
id|normal_i2c
comma
id|normal_i2c_range
comma
id|probe
comma
id|probe_range
comma
id|ignore
comma
id|ignore_range
comma
id|force
)brace
suffix:semicolon
DECL|struct|tda9855
r_struct
id|tda9855
(brace
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|rvol
DECL|member|lvol
r_int
id|rvol
comma
id|lvol
suffix:semicolon
DECL|member|bass
DECL|member|treble
DECL|member|sub
r_int
id|bass
comma
id|treble
comma
id|sub
suffix:semicolon
DECL|member|c1
DECL|member|c2
DECL|member|c3
r_int
id|c1
comma
id|c2
comma
id|c3
suffix:semicolon
DECL|member|a1
DECL|member|a2
DECL|member|a3
r_int
id|a1
comma
id|a2
comma
id|a3
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
suffix:semicolon
DECL|macro|dprintk
mdefine_line|#define dprintk  if (debug) printk
multiline_comment|/* subaddresses */
DECL|macro|TDA9855_VR
mdefine_line|#define TDA9855_VR&t;0x00 /* Volume, right */
DECL|macro|TDA9855_VL
mdefine_line|#define TDA9855_VL&t;0x01 /* Volume, left */
DECL|macro|TDA9855_BA
mdefine_line|#define TDA9855_BA&t;0x02 /* Bass */
DECL|macro|TDA9855_TR
mdefine_line|#define TDA9855_TR&t;0x03 /* Treble */
DECL|macro|TDA9855_SW
mdefine_line|#define TDA9855_SW&t;0x04 /* Subwoofer - not connected on DTV2000 */
DECL|macro|TDA9855_C1
mdefine_line|#define TDA9855_C1&t;0x05 /* Control 1 */
DECL|macro|TDA9855_C2
mdefine_line|#define TDA9855_C2&t;0x06 /* Control 2 */
DECL|macro|TDA9855_C3
mdefine_line|#define TDA9855_C3&t;0x07 /* Control 3 */
DECL|macro|TDA9855_A1
mdefine_line|#define TDA9855_A1&t;0x08 /* Alignmnet 1*/
DECL|macro|TDA9855_A2
mdefine_line|#define TDA9855_A2&t;0x09 /* Alignmnet 2*/
DECL|macro|TDA9855_A3
mdefine_line|#define TDA9855_A3&t;0x0a /* Alignmnet 3*/
multiline_comment|/* Masks for bits in subaddresses */
multiline_comment|/* VR */
multiline_comment|/* VL */
multiline_comment|/* lower 7 bits control gain from -71dB (0x28) to 16dB (0x7f)&n; * in 1dB steps - mute is 0x27 */
multiline_comment|/* BA */
multiline_comment|/* lower 5 bits control bass gain from -12dB (0x06) to 16.5dB (0x19)&n; * in .5dB steps - 0 is 0x0E */
multiline_comment|/* TR */
multiline_comment|/* 4 bits &lt;&lt; 1 control treble gain from -12dB (0x3) to 12dB (0xb)&n; * in 3dB steps - 0 is 0x7 */
multiline_comment|/* SW */
multiline_comment|/* 4 bits &lt;&lt; 2 control subwoofer/surraound gain from -14db (0x1) to 14db (0xf)&n; * in 3dB steps - mute is 0x0 */
multiline_comment|/* C1 */
DECL|macro|TDA9855_MUTE
mdefine_line|#define TDA9855_MUTE&t;1&lt;&lt;7 /* GMU, Mute at outputs */
DECL|macro|TDA9855_AVL
mdefine_line|#define TDA9855_AVL&t;1&lt;&lt;6 /* AVL, Automatic Volume Level */
DECL|macro|TDA9855_LOUD
mdefine_line|#define TDA9855_LOUD&t;1&lt;&lt;5 /* Loudness, 1==off */
DECL|macro|TDA9855_SUR
mdefine_line|#define TDA9855_SUR&t;1&lt;&lt;3 /* Surround / Subwoofer 1==.5(L-R) 0==.5(L+R) */
multiline_comment|/* Bits 0 to 3 select various combinations&n;                                 * of line in and line out, only the &n;                                 * interesting ones are defined */
DECL|macro|TDA9855_EXT
mdefine_line|#define TDA9855_EXT&t;1&lt;&lt;2 /* Selects inputs LIR and LIL.  Pins 41 &amp; 12 */
DECL|macro|TDA9855_INT
mdefine_line|#define TDA9855_INT&t;0    /* Selects inputs LOR and LOL.  (internal) */
multiline_comment|/* C2 */
DECL|macro|TDA9855_SAP
mdefine_line|#define TDA9855_SAP&t;3&lt;&lt;6 /* Selects SAP output, mute if not received */
DECL|macro|TDA9855_STEREO
mdefine_line|#define TDA9855_STEREO&t;1&lt;&lt;6 /* Selects Stereo ouput, mono if not received */
DECL|macro|TDA9855_MONO
mdefine_line|#define TDA9855_MONO&t;0    /* Forces Mono output */
DECL|macro|TDA9855_TZCM
mdefine_line|#define TDA9855_TZCM&t;1&lt;&lt;5 /* If set, don&squot;t mute till zero crossing */
DECL|macro|TDA9855_VZCM
mdefine_line|#define TDA9855_VZCM&t;1&lt;&lt;4 /* If set, don&squot;t change volume till zero crossing*/
DECL|macro|TDA9855_LMU
mdefine_line|#define TDA9855_LMU&t;1&lt;&lt;3 /* Mute at LOR and LOL */
DECL|macro|TDA9855_LINEAR
mdefine_line|#define TDA9855_LINEAR&t;0    /* Linear Stereo */
DECL|macro|TDA9855_PSEUDO
mdefine_line|#define TDA9855_PSEUDO&t;1    /* Pseudo Stereo */
DECL|macro|TDA9855_SPAT_30
mdefine_line|#define TDA9855_SPAT_30&t;2    /* Spatial Stereo, 30% anti-phase crosstalk */
DECL|macro|TDA9855_SPAT_50
mdefine_line|#define TDA9855_SPAT_50&t;3    /* Spatial Stereo, 52% anti-phase crosstalk */
DECL|macro|TDA9855_E_MONO
mdefine_line|#define TDA9855_E_MONO&t;7    /* Forced mono - mono select elseware, so useless*/
multiline_comment|/* C3 */
multiline_comment|/* lower 4 bits control input gain from -3.5dB (0x0) to 4dB (0xF)&n; * in .5dB steps -  0 is 0x7 */
multiline_comment|/* A1 and A2 (read/write) */
multiline_comment|/* lower 5 bites are wideband and spectral expander alignment&n; * from 0x00 to 0x1f - nominal at 0x0f and 0x10 (read/write) */
DECL|macro|TDA9855_STP
mdefine_line|#define TDA9855_STP&t;1&lt;&lt;5 /* Stereo Pilot/detect (read-only) */
DECL|macro|TDA9855_SAPP
mdefine_line|#define TDA9855_SAPP&t;1&lt;&lt;6 /* SAP Pilot/detect (read-only) */
DECL|macro|TDA9855_STS
mdefine_line|#define TDA9855_STS&t;1&lt;&lt;7 /* Stereo trigger 1= &lt;35mV 0= &lt;30mV (write-only)*/
multiline_comment|/* A3 */
multiline_comment|/* lower 3 bits control timing current for alignment: -30% (0x0), -20% (0x1),&n; * -10% (0x2), nominal (0x3), +10% (0x6), +20% (0x5), +30% (0x4) */
multiline_comment|/* 2 bits &lt;&lt; 5 control AVL attack time: 420ohm (0x0), 730ohm (0x2), &n; * 1200ohm (0x1), 2100ohm (0x3) */
DECL|macro|TDA9855_ADJ
mdefine_line|#define TDA9855_ADJ&t;1&lt;&lt;7 /* Stereo adjust on/off (wideband and spectral) */
multiline_comment|/* Begin code */
DECL|function|tda9855_write
r_static
r_int
id|tda9855_write
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
comma
r_int
id|subaddr
comma
r_int
id|val
)paren
(brace
r_int
r_char
id|buffer
(braket
l_int|2
)braket
suffix:semicolon
id|buffer
(braket
l_int|0
)braket
op_assign
id|subaddr
suffix:semicolon
id|buffer
(braket
l_int|1
)braket
op_assign
id|val
suffix:semicolon
r_if
c_cond
(paren
l_int|2
op_ne
id|i2c_master_send
c_func
(paren
id|client
comma
id|buffer
comma
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda9855: I/O error, trying (write %d 0x%x)&bslash;n&quot;
comma
id|subaddr
comma
id|val
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9855_read
r_static
r_int
id|tda9855_read
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_int
r_char
id|buffer
suffix:semicolon
r_if
c_cond
(paren
l_int|1
op_ne
id|i2c_master_recv
c_func
(paren
id|client
comma
op_amp
id|buffer
comma
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda9855: I/O error, trying (read)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
id|buffer
suffix:semicolon
)brace
DECL|function|tda9855_set
r_static
r_int
id|tda9855_set
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9855
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|16
)braket
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda9855_set(0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x)&bslash;n&quot;
comma
id|t-&gt;rvol
comma
id|t-&gt;lvol
comma
id|t-&gt;bass
comma
id|t-&gt;treble
comma
id|t-&gt;sub
comma
id|t-&gt;c1
comma
id|t-&gt;c2
comma
id|t-&gt;c3
comma
id|t-&gt;a1
comma
id|t-&gt;a2
comma
id|t-&gt;a3
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|TDA9855_VR
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|t-&gt;rvol
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|t-&gt;lvol
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|t-&gt;bass
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|t-&gt;treble
suffix:semicolon
id|buf
(braket
l_int|5
)braket
op_assign
id|t-&gt;sub
suffix:semicolon
id|buf
(braket
l_int|6
)braket
op_assign
id|t-&gt;c1
suffix:semicolon
id|buf
(braket
l_int|7
)braket
op_assign
id|t-&gt;c2
suffix:semicolon
id|buf
(braket
l_int|8
)braket
op_assign
id|t-&gt;c3
suffix:semicolon
id|buf
(braket
l_int|9
)braket
op_assign
id|t-&gt;a1
suffix:semicolon
id|buf
(braket
l_int|10
)braket
op_assign
id|t-&gt;a2
suffix:semicolon
id|buf
(braket
l_int|11
)braket
op_assign
id|t-&gt;a3
suffix:semicolon
r_if
c_cond
(paren
l_int|12
op_ne
id|i2c_master_send
c_func
(paren
id|client
comma
id|buf
comma
l_int|12
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;tda9855: I/O error, trying tda9855_set&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9855_init
r_static
r_void
id|tda9855_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9855
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
id|t-&gt;rvol
op_assign
l_int|0x6f
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;lvol
op_assign
l_int|0x6f
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;bass
op_assign
l_int|0x0e
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;treble
op_assign
(paren
l_int|0x07
op_lshift
l_int|1
)paren
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;sub
op_assign
l_int|0x8
op_lshift
l_int|2
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;c1
op_assign
id|TDA9855_MUTE
op_or
id|TDA9855_AVL
op_or
id|TDA9855_LOUD
op_or
id|TDA9855_INT
suffix:semicolon
multiline_comment|/* Set Mute, AVL, Loudness off, Internal sound */
id|t-&gt;c2
op_assign
id|TDA9855_STEREO
op_or
id|TDA9855_LINEAR
suffix:semicolon
multiline_comment|/* Set Stereo liner mode */
id|t-&gt;c3
op_assign
l_int|0x07
suffix:semicolon
multiline_comment|/* 0dB input gain */
id|t-&gt;a1
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* Select nominal wideband expander */
id|t-&gt;a2
op_assign
l_int|0x10
suffix:semicolon
multiline_comment|/* Select nominal spectral expander and 30mV trigger */
id|t-&gt;a3
op_assign
l_int|0x3
suffix:semicolon
multiline_comment|/* Set: nominal timinig current, 420ohm AVL attack */
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_C1
comma
id|TDA9855_MUTE
)paren
suffix:semicolon
multiline_comment|/* mute */
id|tda9855_set
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
multiline_comment|/* *********************** *&n; * i2c interface functions *&n; * *********************** */
DECL|function|tda9855_attach
r_static
r_int
id|tda9855_attach
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
comma
r_int
id|addr
comma
r_int
r_int
id|flags
comma
r_int
id|kind
)paren
(brace
r_struct
id|tda9855
op_star
id|t
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
id|client
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|client
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|client
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|client
comma
op_amp
id|client_template
comma
r_sizeof
(paren
r_struct
id|i2c_client
)paren
)paren
suffix:semicolon
id|client-&gt;adapter
op_assign
id|adap
suffix:semicolon
id|client-&gt;addr
op_assign
id|addr
suffix:semicolon
id|client-&gt;data
op_assign
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|t
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|t
comma
l_int|0
comma
r_sizeof
op_star
id|t
)paren
suffix:semicolon
id|tda9855_init
c_func
(paren
id|client
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|strcpy
c_func
(paren
id|client-&gt;name
comma
l_string|&quot;TDA9855&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda9855: init&bslash;n&quot;
)paren
suffix:semicolon
id|i2c_attach_client
c_func
(paren
id|client
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9855_probe
r_static
r_int
id|tda9855_probe
c_func
(paren
r_struct
id|i2c_adapter
op_star
id|adap
)paren
(brace
r_if
c_cond
(paren
id|adap-&gt;id
op_eq
(paren
id|I2C_ALGO_BIT
op_or
id|I2C_HW_B_BT848
)paren
)paren
r_return
id|i2c_probe
c_func
(paren
id|adap
comma
op_amp
id|addr_data
comma
id|tda9855_attach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9855_detach
r_static
r_int
id|tda9855_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9855
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
id|tda9855_init
c_func
(paren
id|client
)paren
suffix:semicolon
id|i2c_detach_client
c_func
(paren
id|client
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|t
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|client
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9855_command
r_static
r_int
id|tda9855_command
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
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
id|tda9855
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
macro_line|#if 0
id|__u16
op_star
id|sarg
op_assign
id|arg
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* --- v4l ioctls --- */
multiline_comment|/* take care: bttv does userspace copying, we&squot;ll get a&n;&t;   kernel pointer here... */
r_case
id|VIDIOCGAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|va
op_assign
id|arg
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|va-&gt;flags
op_or_assign
id|VIDEO_AUDIO_VOLUME
op_or
id|VIDEO_AUDIO_BASS
op_or
id|VIDEO_AUDIO_TREBLE
suffix:semicolon
multiline_comment|/* min is 0x27 max is 0x7f, vstep is 2e8 */
id|left
op_assign
(paren
id|t-&gt;lvol
op_minus
l_int|0x27
)paren
op_star
l_int|0x2e8
suffix:semicolon
id|right
op_assign
(paren
id|t-&gt;rvol
op_minus
l_int|0x27
)paren
op_star
l_int|0x2e8
suffix:semicolon
id|va-&gt;volume
op_assign
id|MAX
c_func
(paren
id|left
comma
id|right
)paren
suffix:semicolon
id|va-&gt;balance
op_assign
(paren
l_int|32768
op_star
id|MIN
c_func
(paren
id|left
comma
id|right
)paren
)paren
op_div
(paren
id|va-&gt;volume
ques
c_cond
id|va-&gt;volume
suffix:colon
l_int|1
)paren
suffix:semicolon
id|va-&gt;balance
op_assign
(paren
id|left
OL
id|right
)paren
ques
c_cond
(paren
l_int|65535
op_minus
id|va-&gt;balance
)paren
suffix:colon
id|va-&gt;balance
suffix:semicolon
id|va-&gt;bass
op_assign
(paren
id|t-&gt;bass
op_minus
l_int|0x6
)paren
op_star
l_int|0xccc
suffix:semicolon
multiline_comment|/* min 0x6 max is 0x19 */
id|va-&gt;treble
op_assign
(paren
(paren
id|t-&gt;treble
op_rshift
l_int|1
)paren
op_minus
l_int|0x3
)paren
op_star
l_int|0x1c71
suffix:semicolon
id|va-&gt;mode
op_assign
(paren
(paren
id|TDA9855_STP
op_or
id|TDA9855_SAPP
)paren
op_amp
id|tda9855_read
c_func
(paren
id|client
)paren
)paren
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|va-&gt;mode
)paren
id|va-&gt;mode
op_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|VIDIOCSAUDIO
suffix:colon
(brace
r_struct
id|video_audio
op_star
id|va
op_assign
id|arg
suffix:semicolon
r_int
id|left
comma
id|right
suffix:semicolon
id|left
op_assign
(paren
id|MIN
c_func
(paren
l_int|65536
op_minus
id|va-&gt;balance
comma
l_int|32768
)paren
op_star
id|va-&gt;volume
)paren
op_div
l_int|32768
suffix:semicolon
id|right
op_assign
(paren
id|MIN
c_func
(paren
id|va-&gt;balance
comma
l_int|32768
)paren
op_star
id|va-&gt;volume
)paren
op_div
l_int|32768
suffix:semicolon
id|t-&gt;lvol
op_assign
id|left
op_div
l_int|0x2e8
op_plus
l_int|0x27
suffix:semicolon
id|t-&gt;rvol
op_assign
id|right
op_div
l_int|0x2e8
op_plus
l_int|0x27
suffix:semicolon
id|t-&gt;bass
op_assign
id|va-&gt;bass
op_div
l_int|0xccc
op_plus
l_int|0x6
suffix:semicolon
id|t-&gt;treble
op_assign
(paren
id|va-&gt;treble
op_div
l_int|0x1c71
op_plus
l_int|0x3
)paren
op_lshift
l_int|1
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_VL
comma
id|t-&gt;lvol
)paren
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_VR
comma
id|t-&gt;rvol
)paren
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_BA
comma
id|t-&gt;bass
)paren
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_TR
comma
id|t-&gt;treble
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|va-&gt;mode
)paren
(brace
r_case
id|VIDEO_SOUND_MONO
suffix:colon
id|t-&gt;c2
op_assign
id|TDA9855_MONO
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_SOUND_STEREO
suffix:colon
id|t-&gt;c2
op_assign
id|TDA9855_STEREO
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_SOUND_LANG2
suffix:colon
id|t-&gt;c2
op_assign
id|TDA9855_SAP
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_C2
comma
id|t-&gt;c2
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/* --- old, obsolete interface --- */
r_case
id|AUDC_GET_VOLUME_LEFT
suffix:colon
op_star
id|sarg
op_assign
(paren
id|t-&gt;lvol
op_minus
l_int|0x27
)paren
op_star
l_int|0x2e8
suffix:semicolon
multiline_comment|/* min is 0x27 max is 0x7f, vstep is 2e8 */
r_break
suffix:semicolon
r_case
id|AUDC_GET_VOLUME_RIGHT
suffix:colon
op_star
id|sarg
op_assign
(paren
id|t-&gt;rvol
op_minus
l_int|0x27
)paren
op_star
l_int|0x2e8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SET_VOLUME_LEFT
suffix:colon
id|t-&gt;lvol
op_assign
op_star
id|sarg
op_div
l_int|0x2e8
op_plus
l_int|0x27
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SET_VOLUME_RIGHT
suffix:colon
id|t-&gt;rvol
op_assign
op_star
id|sarg
op_div
l_int|0x2e8
op_plus
l_int|0x27
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_GET_BASS
suffix:colon
op_star
id|sarg
op_assign
(paren
id|t-&gt;bass
op_minus
l_int|0x6
)paren
op_star
l_int|0xccc
suffix:semicolon
multiline_comment|/* min 0x6 max is 0x19 */
r_break
suffix:semicolon
r_case
id|AUDC_SET_BASS
suffix:colon
id|t-&gt;bass
op_assign
op_star
id|sarg
op_div
l_int|0xccc
op_plus
l_int|0x6
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_BA
comma
id|t-&gt;bass
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_GET_TREBLE
suffix:colon
op_star
id|sarg
op_assign
(paren
(paren
id|t-&gt;treble
op_rshift
l_int|1
)paren
op_minus
l_int|0x3
)paren
op_star
l_int|0x1c71
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SET_TREBLE
suffix:colon
id|t-&gt;treble
op_assign
(paren
op_star
id|sarg
op_div
l_int|0x1c71
op_plus
l_int|0x3
)paren
op_lshift
l_int|1
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_TR
comma
id|t-&gt;treble
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_GET_STEREO
suffix:colon
op_star
id|sarg
op_assign
(paren
(paren
id|TDA9855_STP
op_or
id|TDA9855_SAPP
)paren
op_amp
id|tda9855_read
c_func
(paren
id|client
)paren
)paren
op_rshift
l_int|4
suffix:semicolon
r_if
c_cond
(paren
op_star
id|sarg
op_eq
l_int|0
)paren
(brace
op_star
id|sarg
op_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|AUDC_SET_STEREO
suffix:colon
r_if
c_cond
(paren
op_star
id|sarg
op_eq
id|VIDEO_SOUND_MONO
)paren
(brace
id|t-&gt;c2
op_assign
id|TDA9855_MONO
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
)brace
multiline_comment|/* Mask out the sap and stereo bits and set mono */
r_else
r_if
c_cond
(paren
op_star
id|sarg
op_eq
id|VIDEO_SOUND_STEREO
)paren
(brace
id|t-&gt;c2
op_assign
id|TDA9855_STEREO
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
)brace
multiline_comment|/* Mask out the sap and stereo bits and set stereo */
r_else
r_if
c_cond
(paren
op_star
id|sarg
op_eq
id|VIDEO_SOUND_LANG2
)paren
(brace
id|t-&gt;c2
op_assign
id|TDA9855_SAP
op_or
(paren
id|t-&gt;c2
op_amp
l_int|0x3f
)paren
suffix:semicolon
)brace
multiline_comment|/* Mask out the sap and stereo bits and set sap */
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_C2
comma
id|t-&gt;c2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SET_INPUT
suffix:colon
id|dprintk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda9855: SET_INPUT with 0x%04x&bslash;n&quot;
comma
op_star
id|sarg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|sarg
op_amp
(paren
id|AUDIO_MUTE
op_or
id|AUDIO_OFF
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|t-&gt;c1
op_or_assign
id|TDA9855_MUTE
suffix:semicolon
)brace
r_else
id|t-&gt;c1
op_assign
id|t-&gt;c1
op_amp
l_int|0x7f
suffix:semicolon
multiline_comment|/* won&squot;t work --&gt;  (~TDA9855_MUTE); */
r_if
c_cond
(paren
(paren
op_star
id|sarg
op_amp
id|AUDIO_INTERN
)paren
op_eq
id|AUDIO_INTERN
)paren
(brace
id|t-&gt;c1
op_assign
(paren
id|t-&gt;c1
op_amp
op_complement
l_int|0x7
)paren
op_or
id|TDA9855_INT
suffix:semicolon
)brace
multiline_comment|/* 0x7 is a mask for the int/ext */
r_if
c_cond
(paren
(paren
op_star
id|sarg
op_amp
id|AUDIO_EXTERN
)paren
op_eq
id|AUDIO_EXTERN
)paren
(brace
id|t-&gt;c1
op_assign
(paren
id|t-&gt;c1
op_amp
op_complement
l_int|0x7
)paren
op_or
id|TDA9855_EXT
suffix:semicolon
)brace
multiline_comment|/* 0x7 is a mask for the int/ext */
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_C1
comma
id|t-&gt;c1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AUDC_SWITCH_MUTE
suffix:colon
r_if
c_cond
(paren
(paren
id|t-&gt;c1
op_amp
op_complement
id|TDA9855_MUTE
)paren
op_eq
l_int|0
)paren
(brace
id|t-&gt;c1
op_or_assign
id|TDA9855_MUTE
suffix:semicolon
)brace
r_else
id|t-&gt;c1
op_and_assign
op_complement
id|TDA9855_MUTE
suffix:semicolon
id|tda9855_write
c_func
(paren
id|client
comma
id|TDA9855_C1
comma
id|t-&gt;c1
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* TDA9855 unsupported: */
multiline_comment|/*&t;case AUDC_NEWCHANNEL:&n;&t;case AUDC_SET_RADIO:&n;&t;case AUDC_GET_DC:&n;*/
macro_line|#endif
r_default
suffix:colon
(brace
)brace
multiline_comment|/* nothing */
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|driver
r_static
r_struct
id|i2c_driver
id|driver
op_assign
(brace
l_string|&quot;i2c tda9855 driver&quot;
comma
id|I2C_DRIVERID_TDA9855
comma
id|I2C_DF_NOTIFY
comma
id|tda9855_probe
comma
id|tda9855_detach
comma
id|tda9855_command
comma
)brace
suffix:semicolon
DECL|variable|client_template
r_static
r_struct
id|i2c_client
id|client_template
op_assign
(brace
l_string|&quot;(unset)&quot;
comma
multiline_comment|/* name */
op_minus
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
op_amp
id|driver
)brace
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
r_int
id|tda9855_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|i2c_add_driver
c_func
(paren
op_amp
id|driver
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
