multiline_comment|/* &n;   saa7185 - Philips SAA7185B video encoder driver version 0.0.3&n;&n;   Copyright (C) 1998 Dave Perks &lt;dperks@ibm.net&gt;&n;&n;   This program is free software; you can redistribute it and/or modify&n;   it under the terms of the GNU General Public License as published by&n;   the Free Software Foundation; either version 2 of the License, or&n;   (at your option) any later version.&n;&n;   This program is distributed in the hope that it will be useful,&n;   but WITHOUT ANY WARRANTY; without even the implied warranty of&n;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;   GNU General Public License for more details.&n;&n;   You should have received a copy of the GNU General Public License&n;   along with this program; if not, write to the Free Software&n;   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
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
macro_line|#include &lt;linux/video_encoder.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG(x)   x&t;&t;/* Debug driver */
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|struct|saa7185
r_struct
id|saa7185
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
l_int|128
)braket
suffix:semicolon
DECL|member|norm
r_int
id|norm
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
DECL|macro|I2C_SAA7185
mdefine_line|#define   I2C_SAA7185        0x88
DECL|macro|I2C_DELAY
mdefine_line|#define I2C_DELAY   10
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|function|saa7185_write
r_static
r_int
id|saa7185_write
c_func
(paren
r_struct
id|saa7185
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
r_int
r_int
id|flags
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
DECL|function|saa7185_write_block
r_static
r_int
id|saa7185_write_block
c_func
(paren
r_struct
id|saa7185
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
suffix:semicolon
r_int
id|subaddr
suffix:semicolon
r_int
r_int
id|flags
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
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|init_common
r_static
r_const
r_int
r_char
id|init_common
(braket
)braket
op_assign
(brace
l_int|0x3a
comma
l_int|0x0f
comma
multiline_comment|/* CBENB=0, V656=0, VY2C=1, YUV2C=1, MY2C=1, MUV2C=1 */
l_int|0x42
comma
l_int|0x6b
comma
multiline_comment|/* OVLY0=107 */
l_int|0x43
comma
l_int|0x00
comma
multiline_comment|/* OVLU0=0     white */
l_int|0x44
comma
l_int|0x00
comma
multiline_comment|/* OVLV0=0   */
l_int|0x45
comma
l_int|0x22
comma
multiline_comment|/* OVLY1=34  */
l_int|0x46
comma
l_int|0xac
comma
multiline_comment|/* OVLU1=172   yellow */
l_int|0x47
comma
l_int|0x0e
comma
multiline_comment|/* OVLV1=14  */
l_int|0x48
comma
l_int|0x03
comma
multiline_comment|/* OVLY2=3   */
l_int|0x49
comma
l_int|0x1d
comma
multiline_comment|/* OVLU2=29    cyan */
l_int|0x4a
comma
l_int|0xac
comma
multiline_comment|/* OVLV2=172 */
l_int|0x4b
comma
l_int|0xf0
comma
multiline_comment|/* OVLY3=240 */
l_int|0x4c
comma
l_int|0xc8
comma
multiline_comment|/* OVLU3=200   green */
l_int|0x4d
comma
l_int|0xb9
comma
multiline_comment|/* OVLV3=185 */
l_int|0x4e
comma
l_int|0xd4
comma
multiline_comment|/* OVLY4=212 */
l_int|0x4f
comma
l_int|0x38
comma
multiline_comment|/* OVLU4=56    magenta */
l_int|0x50
comma
l_int|0x47
comma
multiline_comment|/* OVLV4=71  */
l_int|0x51
comma
l_int|0xc1
comma
multiline_comment|/* OVLY5=193 */
l_int|0x52
comma
l_int|0xe3
comma
multiline_comment|/* OVLU5=227   red */
l_int|0x53
comma
l_int|0x54
comma
multiline_comment|/* OVLV5=84  */
l_int|0x54
comma
l_int|0xa3
comma
multiline_comment|/* OVLY6=163 */
l_int|0x55
comma
l_int|0x54
comma
multiline_comment|/* OVLU6=84    blue */
l_int|0x56
comma
l_int|0xf2
comma
multiline_comment|/* OVLV6=242 */
l_int|0x57
comma
l_int|0x90
comma
multiline_comment|/* OVLY7=144 */
l_int|0x58
comma
l_int|0x00
comma
multiline_comment|/* OVLU7=0     black */
l_int|0x59
comma
l_int|0x00
comma
multiline_comment|/* OVLV7=0   */
l_int|0x5a
comma
l_int|0x00
comma
multiline_comment|/* CHPS=0    */
l_int|0x5b
comma
l_int|0x76
comma
multiline_comment|/* GAINU=118 */
l_int|0x5c
comma
l_int|0xa5
comma
multiline_comment|/* GAINV=165 */
l_int|0x5d
comma
l_int|0x3c
comma
multiline_comment|/* BLCKL=60  */
l_int|0x5e
comma
l_int|0x3a
comma
multiline_comment|/* BLNNL=58  */
l_int|0x5f
comma
l_int|0x3a
comma
multiline_comment|/* CCRS=0, BLNVB=58 */
l_int|0x60
comma
l_int|0x00
comma
multiline_comment|/* NULL      */
multiline_comment|/* 0x61 - 0x66 set according to norm */
l_int|0x67
comma
l_int|0x00
comma
multiline_comment|/* 0 : caption 1st byte odd  field */
l_int|0x68
comma
l_int|0x00
comma
multiline_comment|/* 0 : caption 2nd byte odd  field */
l_int|0x69
comma
l_int|0x00
comma
multiline_comment|/* 0 : caption 1st byte even field */
l_int|0x6a
comma
l_int|0x00
comma
multiline_comment|/* 0 : caption 2nd byte even field */
l_int|0x6b
comma
l_int|0x91
comma
multiline_comment|/* MODIN=2, PCREF=0, SCCLN=17 */
l_int|0x6c
comma
l_int|0x20
comma
multiline_comment|/* SRCV1=0, TRCV2=1, ORCV1=0, PRCV1=0, CBLF=0, ORCV2=0, PRCV2=0 */
l_int|0x6d
comma
l_int|0x00
comma
multiline_comment|/* SRCM1=0, CCEN=0 */
l_int|0x6e
comma
l_int|0x0e
comma
multiline_comment|/* HTRIG=0x00e, approx. centered, at least for PAL */
l_int|0x6f
comma
l_int|0x00
comma
multiline_comment|/* HTRIG upper bits */
l_int|0x70
comma
l_int|0x20
comma
multiline_comment|/* PHRES=0, SBLN=1, VTRIG=0 */
multiline_comment|/* The following should not be needed */
l_int|0x71
comma
l_int|0x15
comma
multiline_comment|/* BMRQ=0x115 */
l_int|0x72
comma
l_int|0x90
comma
multiline_comment|/* EMRQ=0x690 */
l_int|0x73
comma
l_int|0x61
comma
multiline_comment|/* EMRQ=0x690, BMRQ=0x115 */
l_int|0x74
comma
l_int|0x00
comma
multiline_comment|/* NULL       */
l_int|0x75
comma
l_int|0x00
comma
multiline_comment|/* NULL       */
l_int|0x76
comma
l_int|0x00
comma
multiline_comment|/* NULL       */
l_int|0x77
comma
l_int|0x15
comma
multiline_comment|/* BRCV=0x115 */
l_int|0x78
comma
l_int|0x90
comma
multiline_comment|/* ERCV=0x690 */
l_int|0x79
comma
l_int|0x61
comma
multiline_comment|/* ERCV=0x690, BRCV=0x115 */
multiline_comment|/* Field length controls */
l_int|0x7a
comma
l_int|0x70
comma
multiline_comment|/* FLC=0 */
multiline_comment|/* The following should not be needed if SBLN = 1 */
l_int|0x7b
comma
l_int|0x16
comma
multiline_comment|/* FAL=22 */
l_int|0x7c
comma
l_int|0x35
comma
multiline_comment|/* LAL=244 */
l_int|0x7d
comma
l_int|0x20
comma
multiline_comment|/* LAL=244, FAL=22 */
)brace
suffix:semicolon
DECL|variable|init_pal
r_static
r_const
r_int
r_char
id|init_pal
(braket
)braket
op_assign
(brace
l_int|0x61
comma
l_int|0x1e
comma
multiline_comment|/* FISE=0, PAL=1, SCBW=1, RTCE=1, YGS=1, INPI=0, DOWN=0 */
l_int|0x62
comma
l_int|0xc8
comma
multiline_comment|/* DECTYP=1, BSTA=72 */
l_int|0x63
comma
l_int|0xcb
comma
multiline_comment|/* FSC0 */
l_int|0x64
comma
l_int|0x8a
comma
multiline_comment|/* FSC1 */
l_int|0x65
comma
l_int|0x09
comma
multiline_comment|/* FSC2 */
l_int|0x66
comma
l_int|0x2a
comma
multiline_comment|/* FSC3 */
)brace
suffix:semicolon
DECL|variable|init_ntsc
r_static
r_const
r_int
r_char
id|init_ntsc
(braket
)braket
op_assign
(brace
l_int|0x61
comma
l_int|0x1d
comma
multiline_comment|/* FISE=1, PAL=0, SCBW=1, RTCE=1, YGS=1, INPI=0, DOWN=0 */
l_int|0x62
comma
l_int|0xe6
comma
multiline_comment|/* DECTYP=1, BSTA=102 */
l_int|0x63
comma
l_int|0x1f
comma
multiline_comment|/* FSC0 */
l_int|0x64
comma
l_int|0x7c
comma
multiline_comment|/* FSC1 */
l_int|0x65
comma
l_int|0xf0
comma
multiline_comment|/* FSC2 */
l_int|0x66
comma
l_int|0x21
comma
multiline_comment|/* FSC3 */
)brace
suffix:semicolon
DECL|function|saa7185_attach
r_static
r_int
id|saa7185_attach
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
id|saa7185
op_star
id|encoder
suffix:semicolon
id|device-&gt;data
op_assign
id|encoder
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|saa7185
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|encoder
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
id|encoder
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|saa7185
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|device-&gt;name
comma
l_string|&quot;saa7185&quot;
)paren
suffix:semicolon
id|encoder-&gt;bus
op_assign
id|device-&gt;bus
suffix:semicolon
id|encoder-&gt;addr
op_assign
id|device-&gt;addr
suffix:semicolon
id|encoder-&gt;norm
op_assign
id|VIDEO_MODE_NTSC
suffix:semicolon
id|encoder-&gt;enable
op_assign
l_int|1
suffix:semicolon
id|i
op_assign
id|saa7185_write_block
c_func
(paren
id|encoder
comma
id|init_common
comma
r_sizeof
(paren
id|init_common
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|0
)paren
(brace
id|i
op_assign
id|saa7185_write_block
c_func
(paren
id|encoder
comma
id|init_ntsc
comma
r_sizeof
(paren
id|init_ntsc
)paren
)paren
suffix:semicolon
)brace
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
l_string|&quot;%s_attach: init error %d&bslash;n&quot;
comma
id|device-&gt;name
comma
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|saa7185_detach
r_static
r_int
id|saa7185_detach
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
DECL|function|saa7185_command
r_static
r_int
id|saa7185_command
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
id|saa7185
op_star
id|encoder
op_assign
id|device-&gt;data
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|ENCODER_GET_CAPABILITIES
suffix:colon
(brace
r_struct
id|video_encoder_capability
op_star
id|cap
op_assign
id|arg
suffix:semicolon
id|cap-&gt;flags
op_assign
id|VIDEO_ENCODER_PAL
op_or
id|VIDEO_ENCODER_NTSC
op_or
id|VIDEO_ENCODER_SECAM
op_or
id|VIDEO_ENCODER_CCIR
suffix:semicolon
id|cap-&gt;inputs
op_assign
l_int|1
suffix:semicolon
id|cap-&gt;outputs
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_NORM
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
id|saa7185_write_block
c_func
(paren
id|encoder
comma
id|init_ntsc
comma
r_sizeof
(paren
id|init_ntsc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_PAL
suffix:colon
id|saa7185_write_block
c_func
(paren
id|encoder
comma
id|init_pal
comma
r_sizeof
(paren
id|init_pal
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VIDEO_MODE_SECAM
suffix:colon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|encoder-&gt;norm
op_assign
op_star
id|iarg
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_INPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
macro_line|#if 0
multiline_comment|/* not much choice of inputs */
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
macro_line|#else
multiline_comment|/* RJ: *iarg = 0: input is from SA7111&n;&t;&t;&t;   *iarg = 1: input is from ZR36060 */
r_switch
c_cond
(paren
op_star
id|iarg
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Switch RTCE to 1 */
id|saa7185_write
c_func
(paren
id|encoder
comma
l_int|0x61
comma
(paren
id|encoder-&gt;reg
(braket
l_int|0x61
)braket
op_amp
l_int|0xf7
)paren
op_or
l_int|0x08
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* Switch RTCE to 0 */
id|saa7185_write
c_func
(paren
id|encoder
comma
l_int|0x61
comma
(paren
id|encoder-&gt;reg
(braket
l_int|0x61
)braket
op_amp
l_int|0xf7
)paren
op_or
l_int|0x00
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
macro_line|#endif
)brace
r_break
suffix:semicolon
r_case
id|ENCODER_SET_OUTPUT
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
id|ENCODER_ENABLE_OUTPUT
suffix:colon
(brace
r_int
op_star
id|iarg
op_assign
id|arg
suffix:semicolon
id|encoder-&gt;enable
op_assign
op_logical_neg
op_logical_neg
op_star
id|iarg
suffix:semicolon
id|saa7185_write
c_func
(paren
id|encoder
comma
l_int|0x61
comma
(paren
id|encoder-&gt;reg
(braket
l_int|0x61
)braket
op_amp
l_int|0xbf
)paren
op_or
(paren
id|encoder-&gt;enable
ques
c_cond
l_int|0x00
suffix:colon
l_int|0x40
)paren
)paren
suffix:semicolon
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
DECL|variable|i2c_driver_saa7185
r_struct
id|i2c_driver
id|i2c_driver_saa7185
op_assign
(brace
l_string|&quot;saa7185&quot;
comma
multiline_comment|/* name */
id|I2C_DRIVERID_VIDEOENCODER
comma
multiline_comment|/* ID */
id|I2C_SAA7185
comma
id|I2C_SAA7185
op_plus
l_int|1
comma
id|saa7185_attach
comma
id|saa7185_detach
comma
id|saa7185_command
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
id|saa7185_init
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
id|i2c_driver_saa7185
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
id|i2c_driver_saa7185
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
