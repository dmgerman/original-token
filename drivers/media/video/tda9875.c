multiline_comment|/*&n; * For the TDA9875 chip&n; * (The TDA9875 is used on the Diamond DTV2000 french version &n; * Other cards probably use these chips as well.)&n; * This driver will not complain if used with any &n; * other i2c device with the same address.&n; *&n; * Copyright (c) 2000 Guillaume Delvit based on Gerd Knorr source and&n; * Eric Sandeen &n; * This code is placed under the terms of the GNU General Public License&n; * Based on tda9855.c by Steve VanDeBogart (vandebo@uclink.berkeley.edu)&n; * Which was based on tda8425.c by Greg Alexander (c) 1998&n; *&n; * OPTIONS:&n; * debug   - set to 1 if you&squot;d like to see debug messages&n; * &n; *  Revision: 0.1 - original version&n; */
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
macro_line|#include &quot;id.h&quot;
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
DECL|variable|normal_i2c
r_static
r_int
r_int
id|normal_i2c
(braket
)braket
op_assign
(brace
id|I2C_TDA9875
op_rshift
l_int|1
comma
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
multiline_comment|/* This is a superset of the TDA9875 */
DECL|struct|tda9875
r_struct
id|tda9875
(brace
DECL|member|mode
r_int
id|mode
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
r_int
id|bass
comma
id|treble
suffix:semicolon
DECL|member|c
r_struct
id|i2c_client
id|c
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
multiline_comment|/* The TDA9875 is made by Philips Semiconductor&n; * http://www.semiconductors.philips.com&n; * TDA9875: I2C-bus controlled DSP audio processor, FM demodulator&n; *&n; */
multiline_comment|/* subaddresses for TDA9875 */
DECL|macro|TDA9875_MUT
mdefine_line|#define TDA9875_MUT         0x12  /*General mute  (value --&gt; 0b11001100*/
DECL|macro|TDA9875_CFG
mdefine_line|#define TDA9875_CFG         0x01  /* Config register (value --&gt; 0b00000000 */
DECL|macro|TDA9875_DACOS
mdefine_line|#define TDA9875_DACOS       0x13  /*DAC i/o select (ADC) 0b0000100*/
DECL|macro|TDA9875_LOSR
mdefine_line|#define TDA9875_LOSR        0x16  /*Line output select regirter 0b0100 0001*/
DECL|macro|TDA9875_CH1V
mdefine_line|#define TDA9875_CH1V        0x0c  /*Chanel 1 volume (mute)*/
DECL|macro|TDA9875_CH2V
mdefine_line|#define TDA9875_CH2V        0x0d  /*Chanel 2 volume (mute)*/
DECL|macro|TDA9875_SC1
mdefine_line|#define TDA9875_SC1         0x14  /*SCART 1 in (mono)*/
DECL|macro|TDA9875_SC2
mdefine_line|#define TDA9875_SC2         0x15  /*SCART 2 in (mono)*/
DECL|macro|TDA9875_ADCIS
mdefine_line|#define TDA9875_ADCIS       0x17  /*ADC input select (mono) 0b0110 000*/
DECL|macro|TDA9875_AER
mdefine_line|#define TDA9875_AER         0x19  /*Audio effect (AVL+Pseudo) 0b0000 0110*/
DECL|macro|TDA9875_MCS
mdefine_line|#define TDA9875_MCS         0x18  /*Main channel select (DAC) 0b0000100*/
DECL|macro|TDA9875_MVL
mdefine_line|#define TDA9875_MVL         0x1a  /* Main volume gauche */
DECL|macro|TDA9875_MVR
mdefine_line|#define TDA9875_MVR         0x1b  /* Main volume droite */
DECL|macro|TDA9875_MBA
mdefine_line|#define TDA9875_MBA         0x1d  /* Main Basse */
DECL|macro|TDA9875_MTR
mdefine_line|#define TDA9875_MTR         0x1e  /* Main treble */
DECL|macro|TDA9875_ACS
mdefine_line|#define TDA9875_ACS         0x1f  /* Auxilary channel select (FM) 0b0000000*/
DECL|macro|TDA9875_AVL
mdefine_line|#define TDA9875_AVL         0x20  /* Auxilary volume gauche */
DECL|macro|TDA9875_AVR
mdefine_line|#define TDA9875_AVR         0x21  /* Auxilary volume droite */
DECL|macro|TDA9875_ABA
mdefine_line|#define TDA9875_ABA         0x22  /* Auxilary Basse */
DECL|macro|TDA9875_ATR
mdefine_line|#define TDA9875_ATR         0x23  /* Auxilary treble */
DECL|macro|TDA9875_MSR
mdefine_line|#define TDA9875_MSR         0x02  /* Monitor select register */
DECL|macro|TDA9875_C1MSB
mdefine_line|#define TDA9875_C1MSB       0x03  /* Carrier 1 (FM) frequency register MSB */
DECL|macro|TDA9875_C1MIB
mdefine_line|#define TDA9875_C1MIB       0x04  /* Carrier 1 (FM) frequency register (16-8]b */
DECL|macro|TDA9875_C1LSB
mdefine_line|#define TDA9875_C1LSB       0x05  /* Carrier 1 (FM) frequency register LSB */
DECL|macro|TDA9875_C2MSB
mdefine_line|#define TDA9875_C2MSB       0x06  /* Carrier 2 (nicam) frequency register MSB */
DECL|macro|TDA9875_C2MIB
mdefine_line|#define TDA9875_C2MIB       0x07  /* Carrier 2 (nicam) frequency register (16-8]b */
DECL|macro|TDA9875_C2LSB
mdefine_line|#define TDA9875_C2LSB       0x08  /* Carrier 2 (nicam) frequency register LSB */
DECL|macro|TDA9875_DCR
mdefine_line|#define TDA9875_DCR         0x09  /* Demodulateur configuration regirter*/
DECL|macro|TDA9875_DEEM
mdefine_line|#define TDA9875_DEEM        0x0a  /* FM de-emphasis regirter*/
DECL|macro|TDA9875_FMAT
mdefine_line|#define TDA9875_FMAT        0x0b  /* FM Matrix regirter*/
multiline_comment|/* values */
DECL|macro|TDA9875_MUTE_ON
mdefine_line|#define TDA9875_MUTE_ON&t;    0xff /* general mute */
DECL|macro|TDA9875_MUTE_OFF
mdefine_line|#define TDA9875_MUTE_OFF    0xcc /* general no mute */
multiline_comment|/* Begin code */
DECL|function|tda9875_write
r_static
r_int
id|tda9875_write
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
r_char
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
id|dprintk
c_func
(paren
l_string|&quot;In tda9875_write&bslash;n&quot;
)paren
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;Writing %d 0x%x&bslash;n&quot;
comma
id|subaddr
comma
id|val
)paren
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
l_string|&quot;tda9875: I/O error, trying (write %d 0x%x)&bslash;n&quot;
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
macro_line|#if 0
r_static
r_int
id|tda9875_read
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
id|dprintk
c_func
(paren
l_string|&quot;In tda9875_read&bslash;n&quot;
)paren
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
l_string|&quot;tda9875: I/O error, trying (read)&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
l_string|&quot;Read 0x%02x&bslash;n&quot;
comma
id|buffer
)paren
suffix:semicolon
r_return
id|buffer
suffix:semicolon
)brace
macro_line|#endif
DECL|function|tda9875_set
r_static
r_void
id|tda9875_set
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9875
op_star
id|tda
op_assign
id|client-&gt;data
suffix:semicolon
r_int
r_char
id|a
suffix:semicolon
id|dprintk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;tda9875_set(%04x,%04x,%04x,%04x)&bslash;n&quot;
comma
id|tda-&gt;lvol
comma
id|tda-&gt;rvol
comma
id|tda-&gt;bass
comma
id|tda-&gt;treble
)paren
suffix:semicolon
id|a
op_assign
id|tda-&gt;lvol
op_amp
l_int|0xff
suffix:semicolon
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MVL
comma
id|a
)paren
suffix:semicolon
id|a
op_assign
id|tda-&gt;rvol
op_amp
l_int|0xff
suffix:semicolon
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MVR
comma
id|a
)paren
suffix:semicolon
id|a
op_assign
id|tda-&gt;bass
op_amp
l_int|0xff
suffix:semicolon
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MBA
comma
id|a
)paren
suffix:semicolon
id|a
op_assign
id|tda-&gt;treble
op_amp
l_int|0xff
suffix:semicolon
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MTR
comma
id|a
)paren
suffix:semicolon
)brace
DECL|function|do_tda9875_init
r_static
r_void
id|do_tda9875_init
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9875
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;In tda9875_init&bslash;n&quot;
)paren
suffix:semicolon
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_CFG
comma
l_int|0xd0
)paren
suffix:semicolon
multiline_comment|/*reg de config 0 (reset)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MSR
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Monitor 0b00000XXX*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C1MSB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car1(FM) MSB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C1MIB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car1(FM) MIB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C1LSB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car1(FM) LSB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C2MSB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car2(NICAM) MSB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C2MIB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car2(NICAM) MIB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_C2LSB
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Car2(NICAM) LSB XMHz*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_DCR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*Demod config 0x00*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_DEEM
comma
l_int|0x44
)paren
suffix:semicolon
multiline_comment|/*DE-Emph 0b0100 0100*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_FMAT
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*FM Matrix reg 0x00*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_SC1
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* SCART 1 (SC1)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_SC2
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* SCART 2 (sc2)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_CH1V
comma
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* Chanel volume 1 mute*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_CH2V
comma
l_int|0x10
)paren
suffix:semicolon
multiline_comment|/* Chanel volume 2 mute */
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_DACOS
comma
l_int|0x02
)paren
suffix:semicolon
multiline_comment|/* sig DAC i/o(in:nicam)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_ADCIS
comma
l_int|0x6f
)paren
suffix:semicolon
multiline_comment|/* sig ADC input(in:mono)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_LOSR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* line out (in:mono)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_AER
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/*06 Effect (AVL+PSEUDO) */
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MCS
comma
l_int|0x44
)paren
suffix:semicolon
multiline_comment|/* Main ch select (DAC) */
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MVL
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Vol Main left 10dB */
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MVR
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Vol Main right 10dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MBA
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Main Bass Main 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MTR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Main Treble Main 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_ACS
comma
l_int|0x44
)paren
suffix:semicolon
multiline_comment|/* Aux chan select (dac)*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_AVL
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Vol Aux left 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_AVR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Vol Aux right 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_ABA
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Aux Bass Main 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_ATR
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Aux Aigus Main 0dB*/
id|tda9875_write
c_func
(paren
id|client
comma
id|TDA9875_MUT
comma
l_int|0xcc
)paren
suffix:semicolon
multiline_comment|/* General mute  */
id|t-&gt;mode
op_assign
id|AUDIO_UNMUTE
suffix:semicolon
id|t-&gt;lvol
op_assign
id|t-&gt;rvol
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;bass
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0dB */
id|t-&gt;treble
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 0dB */
id|tda9875_set
c_func
(paren
id|client
)paren
suffix:semicolon
)brace
multiline_comment|/* *********************** *&n; * i2c interface functions *&n; * *********************** */
DECL|function|tda9875_attach
r_static
r_int
id|tda9875_attach
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
id|tda9875
op_star
id|t
suffix:semicolon
r_struct
id|i2c_client
op_star
id|client
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;In tda9875_attach&bslash;n&quot;
)paren
suffix:semicolon
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
id|client
op_assign
op_amp
id|t-&gt;c
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
suffix:semicolon
id|do_tda9875_init
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
l_string|&quot;TDA9875&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;tda9875: init&bslash;n&quot;
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
DECL|function|tda9875_probe
r_static
r_int
id|tda9875_probe
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
id|tda9875_attach
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9875_detach
r_static
r_int
id|tda9875_detach
c_func
(paren
r_struct
id|i2c_client
op_star
id|client
)paren
(brace
r_struct
id|tda9875
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
id|do_tda9875_init
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tda9875_command
r_static
r_int
id|tda9875_command
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
id|tda9875
op_star
id|t
op_assign
id|client-&gt;data
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;In tda9875_command...&bslash;n&quot;
)paren
suffix:semicolon
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
id|dprintk
c_func
(paren
l_string|&quot;VIDIOCGAUDIO&bslash;n&quot;
)paren
suffix:semicolon
id|va-&gt;flags
op_or_assign
id|VIDEO_AUDIO_VOLUME
op_or
id|VIDEO_AUDIO_BASS
op_or
id|VIDEO_AUDIO_TREBLE
suffix:semicolon
multiline_comment|/* min is -84 max is 24 */
id|left
op_assign
(paren
id|t-&gt;lvol
op_plus
l_int|84
)paren
op_star
l_int|606
suffix:semicolon
id|right
op_assign
(paren
id|t-&gt;rvol
op_plus
l_int|84
)paren
op_star
l_int|606
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
op_plus
l_int|12
)paren
op_star
l_int|2427
suffix:semicolon
multiline_comment|/* min -12 max +15 */
id|va-&gt;treble
op_assign
(paren
id|t-&gt;treble
op_plus
l_int|12
)paren
op_star
l_int|2730
suffix:semicolon
multiline_comment|/* min -12 max +12 */
id|va-&gt;mode
op_or_assign
id|VIDEO_SOUND_MONO
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* VIDIOCGAUDIO case */
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
id|dprintk
c_func
(paren
l_string|&quot;VIDEOCSAUDIO...&bslash;n&quot;
)paren
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
(paren
(paren
id|left
op_div
l_int|606
)paren
op_minus
l_int|84
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;lvol
OG
l_int|24
)paren
id|t-&gt;lvol
op_assign
l_int|24
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;lvol
OL
op_minus
l_int|84
)paren
id|t-&gt;lvol
op_assign
op_minus
l_int|84
op_amp
l_int|0xff
suffix:semicolon
id|t-&gt;rvol
op_assign
(paren
(paren
id|right
op_div
l_int|606
)paren
op_minus
l_int|84
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;rvol
OG
l_int|24
)paren
id|t-&gt;rvol
op_assign
l_int|24
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;rvol
OL
op_minus
l_int|84
)paren
id|t-&gt;rvol
op_assign
op_minus
l_int|84
op_amp
l_int|0xff
suffix:semicolon
id|t-&gt;bass
op_assign
(paren
(paren
id|va-&gt;bass
op_div
l_int|2400
)paren
op_minus
l_int|12
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;bass
OG
l_int|15
)paren
id|t-&gt;bass
op_assign
l_int|15
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;bass
OL
op_minus
l_int|12
)paren
id|t-&gt;bass
op_assign
op_minus
l_int|12
op_amp
l_int|0xff
suffix:semicolon
id|t-&gt;treble
op_assign
(paren
(paren
id|va-&gt;treble
op_div
l_int|2700
)paren
op_minus
l_int|12
)paren
op_amp
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;treble
OG
l_int|12
)paren
id|t-&gt;treble
op_assign
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;treble
OL
op_minus
l_int|12
)paren
id|t-&gt;treble
op_assign
op_minus
l_int|12
op_amp
l_int|0xff
suffix:semicolon
singleline_comment|//printk(&quot;tda9875 bal:%04x vol:%04x bass:%04x treble:%04x&bslash;n&quot;,va-&gt;balance,va-&gt;volume,va-&gt;bass,va-&gt;treble);
id|tda9875_set
c_func
(paren
id|client
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* end of VIDEOCSAUDIO case */
r_default
suffix:colon
multiline_comment|/* Not VIDEOCGAUDIO or VIDEOCSAUDIO */
multiline_comment|/* nothing */
id|dprintk
c_func
(paren
l_string|&quot;Default&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* end of (cmd) switch */
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
l_string|&quot;i2c tda9875 driver&quot;
comma
id|I2C_DRIVERID_TDA9875
comma
multiline_comment|/* Get new one for TDA9875 */
id|I2C_DF_NOTIFY
comma
id|tda9875_probe
comma
id|tda9875_detach
comma
id|tda9875_command
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
id|tda9875_init
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
id|i2c_del_driver
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
