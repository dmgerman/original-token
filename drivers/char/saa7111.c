multiline_comment|/* &n;   saa7111 - Philips SAA7111A video decoder driver version 0.0.3&n;&n;   Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/wrapper.h&gt;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/i2c-old.h&gt;
macro_line|#include &lt;linux/video_decoder.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)&t;&t;/* Debug driver */
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|saa7111
r_struct
id|saa7111
(brace
DECL|member|bus
r_struct
id|i2c_bus
op_star
id|bus
suffix:semicolon
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|reg
r_int
r_char
id|reg
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|norm
r_int
id|norm
suffix:semicolon
DECL|member|input
r_int
id|input
suffix:semicolon
DECL|member|enable
r_int
id|enable
suffix:semicolon
DECL|member|bright
r_int
id|bright
suffix:semicolon
DECL|member|contrast
r_int
id|contrast
suffix:semicolon
DECL|member|hue
r_int
id|hue
suffix:semicolon
DECL|member|sat
r_int
id|sat
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|I2C_SAA7111
mdefine_line|#define   I2C_SAA7111        0x48
DECL|macro|I2C_DELAY
mdefine_line|#define   I2C_DELAY   10
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|saa7111_write
r_static
r_int
id|saa7111_write
c_func
(paren
r_struct
id|saa7111
op_star
id|dev
comma
r_int
r_char
id|subaddr
comma
r_int
r_char
id|data
)paren
(brace
r_int
id|ack
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|subaddr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|data
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
id|data
suffix:semicolon
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_return
id|ack
suffix:semicolon
)brace
DECL|function|saa7111_write_block
r_static
r_int
id|saa7111_write_block
c_func
(paren
r_struct
id|saa7111
op_star
id|dev
comma
r_int
r_const
r_char
op_star
id|data
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|ack
op_assign
l_int|0
suffix:semicolon
r_int
id|subaddr
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
)paren
(brace
id|LOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|subaddr
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|1
op_logical_and
op_star
id|data
op_eq
op_increment
id|subaddr
)paren
(brace
id|data
op_increment
suffix:semicolon
id|ack
op_assign
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
(paren
id|dev-&gt;reg
(braket
id|subaddr
)braket
op_assign
op_star
id|data
op_increment
)paren
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|len
op_sub_assign
l_int|2
suffix:semicolon
)brace
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
)brace
r_return
id|ack
suffix:semicolon
)brace
DECL|function|saa7111_read
r_static
r_int
id|saa7111_read
c_func
(paren
r_struct
id|saa7111
op_star
id|dev
comma
r_int
r_char
id|subaddr
)paren
(brace
r_int
id|data
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|subaddr
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|i2c_start
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|i2c_sendbyte
c_func
(paren
id|dev-&gt;bus
comma
id|dev-&gt;addr
op_or
l_int|1
comma
id|I2C_DELAY
)paren
suffix:semicolon
id|data
op_assign
id|i2c_readbyte
c_func
(paren
id|dev-&gt;bus
comma
l_int|1
)paren
suffix:semicolon
id|i2c_stop
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
id|UNLOCK_I2C_BUS
c_func
(paren
id|dev-&gt;bus
)paren
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|saa7111_attach
r_static
r_int
id|saa7111_attach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|saa7111
op_star
id|decoder
suffix:semicolon
r_static
r_const
r_int
r_char
id|init
(braket
)braket
op_assign
(brace
l_int|0x00
comma
l_int|0x00
comma
multiline_comment|/* 00 - ID byte */
l_int|0x01
comma
l_int|0x00
comma
multiline_comment|/* 01 - reserved */
multiline_comment|/*front end */
l_int|0x02
comma
l_int|0xd0
comma
multiline_comment|/* 02 - FUSE=3, GUDL=2, MODE=0 */
l_int|0x03
comma
l_int|0x23
comma
multiline_comment|/* 03 - HLNRS=0, VBSL=1, WPOFF=0, HOLDG=0, GAFIX=0, GAI1=256, GAI2=256 */
l_int|0x04
comma
l_int|0x00
comma
multiline_comment|/* 04 - GAI1=256 */
l_int|0x05
comma
l_int|0x00
comma
multiline_comment|/* 05 - GAI2=256 */
multiline_comment|/* decoder */
l_int|0x06
comma
l_int|0xf6
comma
multiline_comment|/* 06 - HSB at  13(50Hz) /  17(60Hz) pixels after end of last line */
l_int|0x07
comma
l_int|0xdd
comma
multiline_comment|/* 07 - HSS at 113(50Hz) / 117(60Hz) pixels after end of last line */
l_int|0x08
comma
l_int|0xc8
comma
multiline_comment|/* 08 - AUFD=1, FSEL=1, EXFIL=0, VTRC=1, HPLL=0, VNOI=0 */
l_int|0x09
comma
l_int|0x01
comma
multiline_comment|/* 09 - BYPS=0, PREF=0, BPSS=0, VBLB=0, UPTCV=0, APER=1 */
l_int|0x0a
comma
l_int|0x80
comma
multiline_comment|/* 0a - BRIG=128 */
l_int|0x0b
comma
l_int|0x47
comma
multiline_comment|/* 0b - CONT=1.109 */
l_int|0x0c
comma
l_int|0x40
comma
multiline_comment|/* 0c - SATN=1.0 */
l_int|0x0d
comma
l_int|0x00
comma
multiline_comment|/* 0d - HUE=0 */
l_int|0x0e
comma
l_int|0x01
comma
multiline_comment|/* 0e - CDTO=0, CSTD=0, DCCF=0, FCTC=0, CHBW=1 */
l_int|0x0f
comma
l_int|0x00
comma
multiline_comment|/* 0f - reserved */
l_int|0x10
comma
l_int|0x48
comma
multiline_comment|/* 10 - OFTS=1, HDEL=0, VRLN=1, YDEL=0 */
l_int|0x11
comma
l_int|0x1c
comma
multiline_comment|/* 11 - GPSW=0, CM99=0, FECO=0, COMPO=1, OEYC=1, OEHV=1, VIPB=0, COLO=0 */
l_int|0x12
comma
l_int|0x00
comma
multiline_comment|/* 12 - output control 2 */
l_int|0x13
comma
l_int|0x00
comma
multiline_comment|/* 13 - output control 3 */
l_int|0x14
comma
l_int|0x00
comma
multiline_comment|/* 14 - reserved */
l_int|0x15
comma
l_int|0x00
comma
multiline_comment|/* 15 - VBI */
l_int|0x16
comma
l_int|0x00
comma
multiline_comment|/* 16 - VBI */
l_int|0x17
comma
l_int|0x00
comma
multiline_comment|/* 17 - VBI */
)brace
suffix:semicolon
id|device-&gt;data
op_assign
id|decoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|saa7111
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decoder
op_eq
l_int|NULL
)paren
(brace
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|MOD_INC_USE_COUNT
suffix:semicolon
id|memset
c_func
(paren
id|decoder
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|saa7111
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|device-&gt;name
comma
l_string|&quot;saa7111&quot;
)paren
suffix:semicolon
id|decoder-&gt;bus
op_assign
id|device-&gt;bus
suffix:semicolon
id|decoder-&gt;addr
op_assign
id|device-&gt;addr
suffix:semicolon
id|decoder-&gt;norm
op_assign
id|VIDEO_MODE_NTSC
suffix:semicolon
id|decoder-&gt;input
op_assign
l_int|0
suffix:semicolon
id|decoder-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|decoder-&gt;bright
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;contrast
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;hue
op_assign
l_int|32768
suffix:semicolon
id|decoder-&gt;sat
op_assign
l_int|32768
suffix:semicolon
id|i
op_assign
id|saa7111_write_block
c_func
(paren
id|decoder
comma
id|init
comma
r_sizeof
(paren
id|init
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s_attach: init status %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|i
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s_attach: chip version %x&bslash;n&quot;
comma
id|device-&gt;name
comma
id|saa7111_read
c_func
(paren
id|decoder
comma
l_int|0x00
)paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7111_detach
r_static
r_int
id|saa7111_detach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
id|kfree
c_func
(paren
id|device-&gt;data
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7111_command
r_static
r_int
id|saa7111_command
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
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
id|saa7111
op_star
id|decoder
op_assign
id|device-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
macro_line|#if defined(DECODER_DUMP)
r_case
id|DECODER_DUMP
suffix:colon
(brace
r_int
id|i
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
l_int|32
suffix:semicolon
id|i
op_add_assign
l_int|16
)paren
(brace
r_int
id|j
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;KERN_DEBUG %s: %03x&quot;
comma
id|device-&gt;name
comma
id|i
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|16
suffix:semicolon
op_increment
id|j
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|saa7111_read
c_func
(paren
id|decoder
comma
id|i
op_plus
id|j
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* defined(DECODER_DUMP) */
r_case
id|DECODER_GET_CAPABILITIES
suffix:colon
(brace
r_struct
id|video_decoder_capability
op_star
id|cap
op_assign
id|arg
suffix:semicolon
id|cap-&gt;flags
op_assign
id|VIDEO_DECODER_PAL
op_or
id|VIDEO_DECODER_NTSC
op_or
id|VIDEO_DECODER_AUTO
op_or
id|VIDEO_DECODER_CCIR
suffix:semicolon
id|cap-&gt;inputs
op_assign
l_int|8
suffix:semicolon
id|cap-&gt;outputs
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_GET_STATUS
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_int
id|status
suffix:semicolon
r_int
id|res
suffix:semicolon
id|status
op_assign
id|saa7111_read
c_func
(paren
id|decoder
comma
l_int|0x1f
)paren
suffix:semicolon
id|res
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|6
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_GOOD
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|decoder-&gt;norm
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_NTSC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|res
op_or_assign
id|DECODER_STATUS_PAL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_case
id|VIDEO_MODE_AUTO
suffix:colon
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|5
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_NTSC
suffix:semicolon
)brace
r_else
(brace
id|res
op_or_assign
id|DECODER_STATUS_PAL
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
l_int|0
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|res
op_or_assign
id|DECODER_STATUS_COLOR
suffix:semicolon
)brace
op_star
id|iarg
op_assign
id|res
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_NORM
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_switch
c_cond
(paren
op_star
id|iarg
)paren
(brace
r_case
id|VIDEO_MODE_NTSC
suffix:colon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x08
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x08
)braket
op_amp
l_int|0x3f
)paren
op_or
l_int|0x40
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x08
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x08
)braket
op_amp
l_int|0x3f
)paren
op_or
l_int|0x00
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_AUTO
suffix:colon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x08
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x08
)braket
op_amp
l_int|0x3f
)paren
op_or
l_int|0x80
)paren
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
id|decoder-&gt;norm
op_assign
op_star
id|iarg
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_INPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
op_star
id|iarg
template_param
l_int|7
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
id|decoder-&gt;input
op_ne
op_star
id|iarg
)paren
(brace
id|decoder-&gt;input
op_assign
op_star
id|iarg
suffix:semicolon
multiline_comment|/* select mode */
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x02
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x02
)braket
op_amp
l_int|0xf8
)paren
op_or
id|decoder-&gt;input
)paren
suffix:semicolon
multiline_comment|/* bypass chrominance trap for modes 4..7 */
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x09
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x09
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|decoder-&gt;input
OG
l_int|3
)paren
ques
c_cond
l_int|0x80
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
multiline_comment|/* not much choice of outputs */
r_if
c_cond
(paren
op_star
id|iarg
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_ENABLE_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
r_int
id|enable
op_assign
(paren
op_star
id|iarg
op_ne
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;enable
op_ne
id|enable
)paren
(brace
id|decoder-&gt;enable
op_assign
id|enable
suffix:semicolon
singleline_comment|// RJ: If output should be disabled (for playing videos), we also need a open PLL.
singleline_comment|//     The input is set to 0 (where no input source is connected), although this
singleline_comment|//     is not necessary.
singleline_comment|//
singleline_comment|//     If output should be enabled, we have to reverse the above.
r_if
c_cond
(paren
id|decoder-&gt;enable
)paren
(brace
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x02
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x02
)braket
op_amp
l_int|0xf8
)paren
op_or
id|decoder-&gt;input
)paren
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x08
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x08
)braket
op_amp
l_int|0xfb
)paren
)paren
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x11
)braket
op_amp
l_int|0xf3
)paren
op_or
l_int|0x0c
)paren
suffix:semicolon
)brace
r_else
(brace
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x02
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x02
)braket
op_amp
l_int|0xf8
)paren
)paren
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x08
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x08
)braket
op_amp
l_int|0xfb
)paren
op_or
l_int|0x04
)paren
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x11
comma
(paren
id|decoder-&gt;reg
(braket
l_int|0x11
)braket
op_amp
l_int|0xf3
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
r_break
suffix:semicolon
r_case
id|DECODER_SET_PICTURE
suffix:colon
(brace
r_struct
id|video_picture
op_star
id|pic
op_assign
id|arg
suffix:semicolon
r_if
c_cond
(paren
id|decoder-&gt;bright
op_ne
id|pic-&gt;brightness
)paren
(brace
multiline_comment|/* We want 0 to 255 we get 0-65535 */
id|decoder-&gt;bright
op_assign
id|pic-&gt;brightness
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x0a
comma
id|decoder-&gt;bright
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;contrast
op_ne
id|pic-&gt;contrast
)paren
(brace
multiline_comment|/* We want 0 to 127 we get 0-65535 */
id|decoder-&gt;contrast
op_assign
id|pic-&gt;contrast
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x0b
comma
id|decoder-&gt;contrast
op_rshift
l_int|9
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;sat
op_ne
id|pic-&gt;colour
)paren
(brace
multiline_comment|/* We want 0 to 127 we get 0-65535 */
id|decoder-&gt;sat
op_assign
id|pic-&gt;colour
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x0c
comma
id|decoder-&gt;sat
op_rshift
l_int|9
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|decoder-&gt;hue
op_ne
id|pic-&gt;hue
)paren
(brace
multiline_comment|/* We want -128 to 127 we get 0-65535 */
id|decoder-&gt;hue
op_assign
id|pic-&gt;hue
suffix:semicolon
id|saa7111_write
c_func
(paren
id|decoder
comma
l_int|0x0d
comma
(paren
id|decoder-&gt;hue
op_minus
l_int|32768
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
)brace
)brace
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|i2c_driver_saa7111
r_struct
id|i2c_driver
id|i2c_driver_saa7111
op_assign
(brace
l_string|&quot;saa7111&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEODECODER
comma
multiline_comment|/* ID */
id|I2C_SAA7111
comma
id|I2C_SAA7111
op_plus
l_int|1
comma
id|saa7111_attach
comma
id|saa7111_detach
comma
id|saa7111_command
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
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
id|saa7111_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_return
id|i2c_register_driver
c_func
(paren
op_amp
id|i2c_driver_saa7111
)paren
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
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_saa7111
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
