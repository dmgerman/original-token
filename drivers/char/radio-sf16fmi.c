multiline_comment|/* SF16FMI radio driver for Linux radio support&n; * heavily based on rtrack driver...&n; * (c) 1997 M. Kirkwood&n; * (c) 1998 Petr Vandrovec, vandrove@vc.cvut.cz&n; *&n; * Fitted to new interface by Alan Cox &lt;alan.cox@linux.org&gt;&n; *&n; * Notes on the hardware&n; *&n; *  Frequency control is done digitally -- ie out(port,encodefreq(95.8));&n; *  No volume control - only mute/unmute - you have to use line volume&n; *  control on SB-part of SF16FMI&n; *  &n; */
macro_line|#include &lt;linux/module.h&gt;&t;/* Modules &t;&t;&t;*/
macro_line|#include &lt;linux/init.h&gt;&t;&t;/* Initdata&t;&t;&t;*/
macro_line|#include &lt;linux/ioport.h&gt;&t;/* check_region, request_region&t;*/
macro_line|#include &lt;linux/delay.h&gt;&t;/* udelay&t;&t;&t;*/
macro_line|#include &lt;asm/io.h&gt;&t;&t;/* outb, outb_p&t;&t;&t;*/
macro_line|#include &lt;asm/uaccess.h&gt;&t;/* copy to/from user&t;&t;*/
macro_line|#include &lt;linux/videodev.h&gt;&t;/* kernel radio structs&t;&t;*/
macro_line|#include &lt;linux/config.h&gt;&t;/* CONFIG_RADIO_SF16MI_PORT &t;*/
macro_line|#include &quot;rsf16fmi.h&quot;
DECL|struct|fmi_device
r_struct
id|fmi_device
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
)brace
suffix:semicolon
macro_line|#ifndef CONFIG_RADIO_SF16FMI_PORT
DECL|macro|CONFIG_RADIO_SF16FMI_PORT
mdefine_line|#define CONFIG_RADIO_SF16FMI_PORT -1
macro_line|#endif
DECL|variable|io
r_static
r_int
id|io
op_assign
id|CONFIG_RADIO_SF16FMI_PORT
suffix:semicolon
DECL|variable|users
r_static
r_int
id|users
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* local things */
DECL|macro|RSF16_ENCODE
mdefine_line|#define RSF16_ENCODE(x)&t;((x*(1000/4)+10700)/50)
DECL|function|outbits
r_static
r_void
id|outbits
c_func
(paren
r_int
id|bits
comma
r_int
id|data
comma
r_int
id|port
)paren
(brace
r_while
c_loop
(paren
id|bits
op_decrement
)paren
(brace
r_if
c_cond
(paren
id|data
op_amp
l_int|1
)paren
(brace
id|outb
c_func
(paren
l_int|5
comma
id|port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|7
comma
id|port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
l_int|1
comma
id|port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|3
comma
id|port
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|6
)paren
suffix:semicolon
)brace
id|data
op_rshift_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|fmi_mute
r_static
r_void
id|fmi_mute
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0x00
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|fmi_unmute
r_static
r_void
id|fmi_unmute
c_func
(paren
r_int
id|port
)paren
(brace
id|outb
c_func
(paren
l_int|0x08
comma
id|port
)paren
suffix:semicolon
)brace
multiline_comment|/* FREQ is in 1/16ths of a MHz so this is probably wrong atm */
DECL|function|fmi_setfreq
r_static
r_int
id|fmi_setfreq
c_func
(paren
r_struct
id|fmi_device
op_star
id|dev
comma
r_int
r_int
id|freq
)paren
(brace
r_int
id|myport
op_assign
id|dev-&gt;port
suffix:semicolon
id|outbits
c_func
(paren
l_int|16
comma
id|RSF16_ENCODE
c_func
(paren
id|freq
)paren
comma
id|myport
)paren
suffix:semicolon
id|outbits
c_func
(paren
l_int|8
comma
l_int|0xC0
comma
id|myport
)paren
suffix:semicolon
multiline_comment|/* we should wait here... */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fmi_getsigstr
r_static
r_int
id|fmi_getsigstr
c_func
(paren
r_struct
id|fmi_device
op_star
id|dev
)paren
(brace
r_int
id|val
suffix:semicolon
r_int
id|res
suffix:semicolon
r_int
id|myport
op_assign
id|dev-&gt;port
suffix:semicolon
id|val
op_assign
id|dev-&gt;curvol
ques
c_cond
l_int|0x08
suffix:colon
l_int|0x00
suffix:semicolon
multiline_comment|/* unmute/mute */
id|outb
c_func
(paren
id|val
comma
id|myport
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
op_or
l_int|0x10
comma
id|myport
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|140000
)paren
suffix:semicolon
id|res
op_assign
(paren
r_int
)paren
id|inb
c_func
(paren
id|myport
op_plus
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|val
comma
id|myport
)paren
suffix:semicolon
r_return
(paren
id|res
op_amp
l_int|2
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
)brace
DECL|function|fmi_ioctl
r_static
r_int
id|fmi_ioctl
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
id|fmi_device
op_star
id|fmi
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
r_int
)paren
(paren
l_float|87.5
op_star
l_int|16
)paren
suffix:semicolon
id|v.rangehigh
op_assign
(paren
r_int
)paren
(paren
l_float|108.0
op_star
l_int|16
)paren
suffix:semicolon
id|v.flags
op_assign
l_int|0
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_MODE_AUTO
suffix:semicolon
id|v.signal
op_assign
l_int|0xFFFF
op_star
id|fmi_getsigstr
c_func
(paren
id|fmi
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
id|fmi-&gt;curfreq
comma
r_sizeof
(paren
id|fmi-&gt;curfreq
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
id|fmi-&gt;curfreq
comma
id|arg
comma
r_sizeof
(paren
id|fmi-&gt;curfreq
)paren
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|fmi_setfreq
c_func
(paren
id|fmi
comma
id|fmi-&gt;curfreq
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
suffix:semicolon
id|v.mode
op_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
id|v.volume
op_assign
id|fmi-&gt;curvol
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
id|fmi-&gt;curvol
op_assign
id|v.volume
suffix:semicolon
r_if
c_cond
(paren
id|v.flags
op_amp
id|VIDEO_AUDIO_MUTE
)paren
(brace
id|fmi_mute
c_func
(paren
id|fmi-&gt;port
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fmi-&gt;curvol
)paren
(brace
id|fmi_unmute
c_func
(paren
id|fmi-&gt;port
)paren
suffix:semicolon
)brace
r_else
id|fmi_mute
c_func
(paren
id|fmi-&gt;port
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
DECL|function|fmi_open
r_static
r_int
id|fmi_open
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
DECL|function|fmi_close
r_static
r_void
id|fmi_close
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
DECL|variable|fmi_unit
r_static
r_struct
id|fmi_device
id|fmi_unit
suffix:semicolon
DECL|variable|fmi_radio
r_static
r_struct
id|video_device
id|fmi_radio
op_assign
(brace
l_string|&quot;SF16FMI radio&quot;
comma
id|VID_TYPE_TUNER
comma
id|VID_HARDWARE_SF16MI
comma
id|fmi_open
comma
id|fmi_close
comma
l_int|NULL
comma
multiline_comment|/* Can&squot;t read  (no capture ability) */
l_int|NULL
comma
multiline_comment|/* Can&squot;t write */
id|fmi_ioctl
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|fmi_init
c_func
(paren
r_struct
id|video_init
op_star
id|v
)paren
)paren
(brace
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
l_string|&quot;fmi: port 0x%x already in use&bslash;n&quot;
comma
id|io
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|fmi_unit.port
op_assign
id|io
suffix:semicolon
id|fmi_radio.priv
op_assign
op_amp
id|fmi_unit
suffix:semicolon
r_if
c_cond
(paren
id|video_register_device
c_func
(paren
op_amp
id|fmi_radio
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
l_string|&quot;fmi&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;SF16FMI radio card driver.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;(c) 1998 Petr Vandrovec, vandrove@vc.cvut.cz.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* mute card - prevents noisy bootups */
id|fmi_mute
c_func
(paren
id|io
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Petr Vandrovec, vandrove@vc.cvut.cz and M. Kirkwood&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;A driver for the SF16MI radio.&quot;
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
l_string|&quot;I/O address of the SF16MI card (0x284 or 0x384)&quot;
)paren
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
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
r_return
id|fmi_init
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|video_unregister_device
c_func
(paren
op_amp
id|fmi_radio
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
macro_line|#endif
eof
