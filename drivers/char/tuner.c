macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &quot;i2c.h&quot;
macro_line|#include &lt;linux/videodev.h&gt;
macro_line|#include &quot;tuner.h&quot;
DECL|variable|debug
r_static
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* insmod parameter */
DECL|variable|type
r_static
r_int
id|type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* tuner type */
DECL|macro|dprintk
mdefine_line|#define dprintk     if (debug) printk
id|MODULE_PARM
c_func
(paren
id|debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|type
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|struct|tuner
r_struct
id|tuner
(brace
DECL|member|bus
r_struct
id|i2c_bus
op_star
id|bus
suffix:semicolon
multiline_comment|/* where is our chip */
DECL|member|addr
r_int
id|addr
suffix:semicolon
DECL|member|type
r_int
id|type
suffix:semicolon
multiline_comment|/* chip type */
DECL|member|freq
r_int
id|freq
suffix:semicolon
multiline_comment|/* keep track of the current settings */
DECL|member|radio
r_int
id|radio
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|struct|tunertype
r_struct
id|tunertype
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|Vendor
r_int
r_char
id|Vendor
suffix:semicolon
DECL|member|Type
r_int
r_char
id|Type
suffix:semicolon
DECL|member|thresh1
r_int
r_int
id|thresh1
suffix:semicolon
multiline_comment|/* frequency Range for UHF,VHF-L, VHF_H */
DECL|member|thresh2
r_int
r_int
id|thresh2
suffix:semicolon
DECL|member|VHF_L
r_int
r_char
id|VHF_L
suffix:semicolon
DECL|member|VHF_H
r_int
r_char
id|VHF_H
suffix:semicolon
DECL|member|UHF
r_int
r_char
id|UHF
suffix:semicolon
DECL|member|config
r_int
r_char
id|config
suffix:semicolon
DECL|member|I2C
r_int
r_char
id|I2C
suffix:semicolon
DECL|member|IFPCoff
r_int
r_int
id|IFPCoff
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;The floats in the tuner struct are computed at compile time&n; *&t;by gcc and cast back to integers. Thus we don&squot;t violate the&n; *&t;&quot;no float in kernel&quot; rule.&n; */
DECL|variable|tuners
r_static
r_struct
id|tunertype
id|tuners
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Temic PAL&quot;
comma
id|TEMIC
comma
id|PAL
comma
l_int|16
op_star
l_float|140.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x01
comma
l_int|0x8e
comma
l_int|0xc2
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips PAL_I&quot;
comma
id|Philips
comma
id|PAL_I
comma
l_int|16
op_star
l_float|140.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|0xc0
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Philips NTSC&quot;
comma
id|Philips
comma
id|NTSC
comma
l_int|16
op_star
l_float|157.25
comma
l_int|16
op_star
l_float|451.25
comma
l_int|0xA0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|0xc0
comma
l_int|732
)brace
comma
(brace
l_string|&quot;Philips SECAM&quot;
comma
id|Philips
comma
id|SECAM
comma
l_int|16
op_star
l_float|168.25
comma
l_int|16
op_star
l_float|447.25
comma
l_int|0xA7
comma
l_int|0x97
comma
l_int|0x37
comma
l_int|0x8e
comma
l_int|0xc0
comma
l_int|623
)brace
comma
(brace
l_string|&quot;NoTuner&quot;
comma
id|NoTuner
comma
id|NOTUNER
comma
l_int|0
comma
l_int|0
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|000
)brace
comma
(brace
l_string|&quot;Philips PAL&quot;
comma
id|Philips
comma
id|PAL
comma
l_int|16
op_star
l_float|168.25
comma
l_int|16
op_star
l_float|447.25
comma
l_int|0xA0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|0xc0
comma
l_int|623
)brace
comma
(brace
l_string|&quot;Temic NTSC&quot;
comma
id|TEMIC
comma
id|NTSC
comma
l_int|16
op_star
l_float|157.25
comma
l_int|16
op_star
l_float|463.25
comma
l_int|0x02
comma
l_int|0x04
comma
l_int|0x01
comma
l_int|0x8e
comma
l_int|0xc2
comma
l_int|732
)brace
comma
(brace
l_string|&quot;TEMIC PAL_I&quot;
comma
id|TEMIC
comma
id|PAL_I
comma
l_int|16
op_star
l_float|170.00
comma
l_int|16
op_star
l_float|450.00
comma
l_int|0xa0
comma
l_int|0x90
comma
l_int|0x30
comma
l_int|0x8e
comma
l_int|0xc2
comma
l_int|623
)brace
comma
)brace
suffix:semicolon
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tuner_getstatus
r_static
r_int
id|tuner_getstatus
(paren
r_struct
id|tuner
op_star
id|t
)paren
(brace
r_return
id|i2c_read
c_func
(paren
id|t-&gt;bus
comma
id|t-&gt;addr
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|macro|TUNER_POR
mdefine_line|#define TUNER_POR       0x80
DECL|macro|TUNER_FL
mdefine_line|#define TUNER_FL        0x40
DECL|macro|TUNER_AFC
mdefine_line|#define TUNER_AFC       0x07
DECL|function|tuner_islocked
r_static
r_int
id|tuner_islocked
(paren
r_struct
id|tuner
op_star
id|t
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|t
)paren
op_amp
id|TUNER_FL
)paren
suffix:semicolon
)brace
DECL|function|tuner_afcstatus
r_static
r_int
id|tuner_afcstatus
(paren
r_struct
id|tuner
op_star
id|t
)paren
(brace
r_return
(paren
id|tuner_getstatus
(paren
id|t
)paren
op_amp
id|TUNER_AFC
)paren
op_minus
l_int|2
suffix:semicolon
)brace
DECL|function|set_tv_freq
r_static
r_void
id|set_tv_freq
c_func
(paren
r_struct
id|tuner
op_star
id|t
comma
r_int
id|freq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|config
suffix:semicolon
id|u16
id|div
suffix:semicolon
r_struct
id|tunertype
op_star
id|tun
op_assign
op_amp
id|tuners
(braket
id|t-&gt;type
)braket
suffix:semicolon
r_if
c_cond
(paren
id|freq
OL
id|tun-&gt;thresh1
)paren
id|config
op_assign
id|tun-&gt;VHF_L
suffix:semicolon
r_else
r_if
c_cond
(paren
id|freq
OL
id|tun-&gt;thresh2
)paren
id|config
op_assign
id|tun-&gt;VHF_H
suffix:semicolon
r_else
id|config
op_assign
id|tun-&gt;UHF
suffix:semicolon
id|div
op_assign
id|freq
op_plus
(paren
r_int
)paren
(paren
l_int|16
op_star
l_float|38.9
)paren
suffix:semicolon
id|div
op_and_assign
l_int|0x7fff
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_write
c_func
(paren
id|t-&gt;bus
comma
id|t-&gt;addr
comma
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
comma
id|div
op_amp
l_int|0xff
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error #1&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|i2c_write
c_func
(paren
id|t-&gt;bus
comma
id|t-&gt;addr
comma
id|tun-&gt;config
comma
id|config
comma
l_int|1
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error #2&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|UNLOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
)brace
DECL|function|set_radio_freq
r_static
r_void
id|set_radio_freq
c_func
(paren
r_struct
id|tuner
op_star
id|t
comma
r_int
id|freq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|config
suffix:semicolon
id|u16
id|div
suffix:semicolon
r_struct
id|tunertype
op_star
id|tun
op_assign
op_amp
id|tuners
(braket
id|type
)braket
suffix:semicolon
id|config
op_assign
l_int|0xa5
suffix:semicolon
id|div
op_assign
id|freq
op_plus
(paren
r_int
)paren
(paren
l_int|16
op_star
l_float|10.7
)paren
suffix:semicolon
id|div
op_and_assign
l_int|0x7fff
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i2c_write
c_func
(paren
id|t-&gt;bus
comma
id|t-&gt;addr
comma
(paren
id|div
op_rshift
l_int|8
)paren
op_amp
l_int|0x7f
comma
id|div
op_amp
l_int|0xff
comma
l_int|1
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error #1&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|i2c_write
c_func
(paren
id|t-&gt;bus
comma
id|t-&gt;addr
comma
id|tun-&gt;config
comma
id|config
comma
l_int|1
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;tuner: i2c i/o error #2&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debug
)paren
(brace
id|UNLOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|current-&gt;timeout
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|LOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tuner_islocked
(paren
id|t
)paren
)paren
id|printk
(paren
l_string|&quot;tuner: PLL locked&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|printk
(paren
l_string|&quot;tuner: PLL not locked&bslash;n&quot;
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;tuner: AFC: %d&bslash;n&quot;
comma
id|tuner_afcstatus
(paren
id|t
)paren
)paren
suffix:semicolon
)brace
id|UNLOCK_I2C_BUS
c_func
(paren
id|t-&gt;bus
)paren
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
DECL|function|tuner_attach
r_static
r_int
id|tuner_attach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_struct
id|tuner
op_star
id|t
suffix:semicolon
multiline_comment|/*&n;&t; *&t;For now we only try and attach these tuners to the BT848&n;&t; *&t;bus. This same module will however work different species&n;&t; *&t;of card using these chips. Just change the constraints&n;&t; *&t;(i2c doesn&squot;t have a totally clash free &squot;address&squot; space)&n;&t; */
r_if
c_cond
(paren
id|device-&gt;bus-&gt;id
op_ne
id|I2C_BUSID_BT848
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|device-&gt;data
op_assign
id|t
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tuner
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
l_int|NULL
op_eq
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
(paren
r_struct
id|tuner
)paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|device-&gt;name
comma
l_string|&quot;tuner&quot;
)paren
suffix:semicolon
id|t-&gt;bus
op_assign
id|device-&gt;bus
suffix:semicolon
id|t-&gt;addr
op_assign
id|device-&gt;addr
suffix:semicolon
id|t-&gt;type
op_assign
id|type
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tuner: type is %d (%s)&bslash;n&quot;
comma
id|t-&gt;type
comma
id|tuners
(braket
id|t-&gt;type
)braket
dot
id|name
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tuner_detach
r_static
r_int
id|tuner_detach
c_func
(paren
r_struct
id|i2c_device
op_star
id|device
)paren
(brace
r_struct
id|tuner
op_star
id|t
op_assign
(paren
r_struct
id|tuner
op_star
)paren
id|device-&gt;data
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
DECL|function|tuner_command
r_static
r_int
id|tuner_command
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
id|tuner
op_star
id|t
op_assign
(paren
r_struct
id|tuner
op_star
)paren
id|device-&gt;data
suffix:semicolon
r_int
op_star
id|iarg
op_assign
(paren
r_int
op_star
)paren
id|arg
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|TUNER_SET_TYPE
suffix:colon
id|t-&gt;type
op_assign
op_star
id|iarg
suffix:semicolon
id|dprintk
c_func
(paren
l_string|&quot;tuner: type set to %d (%s)&bslash;n&quot;
comma
id|t-&gt;type
comma
id|tuners
(braket
id|t-&gt;type
)braket
dot
id|name
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNER_SET_TVFREQ
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;tuner: tv freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_tv_freq
c_func
(paren
id|t
comma
op_star
id|iarg
)paren
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|0
suffix:semicolon
id|t-&gt;freq
op_assign
op_star
id|iarg
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TUNER_SET_RADIOFREQ
suffix:colon
id|dprintk
c_func
(paren
l_string|&quot;tuner: radio freq set to %d.%02d&bslash;n&quot;
comma
(paren
op_star
id|iarg
)paren
op_div
l_int|16
comma
(paren
op_star
id|iarg
)paren
op_mod
l_int|16
op_star
l_int|100
op_div
l_int|16
)paren
suffix:semicolon
id|set_radio_freq
c_func
(paren
id|t
comma
op_star
id|iarg
)paren
suffix:semicolon
id|t-&gt;radio
op_assign
l_int|1
suffix:semicolon
id|t-&gt;freq
op_assign
op_star
id|iarg
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
DECL|variable|i2c_driver_tuner
r_struct
id|i2c_driver
id|i2c_driver_tuner
op_assign
(brace
l_string|&quot;tuner&quot;
comma
multiline_comment|/* name       */
id|I2C_DRIVERID_TUNER
comma
multiline_comment|/* ID         */
l_int|0xc0
comma
l_int|0xce
comma
multiline_comment|/* addr range */
id|tuner_attach
comma
id|tuner_detach
comma
id|tuner_command
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
id|i2c_tuner_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
id|i2c_register_driver
c_func
(paren
op_amp
id|i2c_driver_tuner
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
id|i2c_unregister_driver
c_func
(paren
op_amp
id|i2c_driver_tuner
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-basic-offset: 8&n; * End:&n; */
eof
