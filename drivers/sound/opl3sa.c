multiline_comment|/*&n; * sound/Xopl3sa.c&n; *&n; * Low level driver for Yamaha YMF701B aka OPL3-SA chip&n; * &n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|SB_OK
macro_line|#undef  SB_OK
macro_line|#include &quot;sound_config.h&quot;
macro_line|#ifdef SB_OK
macro_line|#include &quot;sb.h&quot;
DECL|variable|sb_initialized
r_static
r_int
id|sb_initialized
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_OPL3SA1
DECL|variable|kilroy_was_here
r_static
r_int
id|kilroy_was_here
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t detect twice */
DECL|variable|mpu_initialized
r_static
r_int
id|mpu_initialized
op_assign
l_int|0
suffix:semicolon
DECL|variable|opl3sa_osp
r_static
r_int
op_star
id|opl3sa_osp
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
r_char
DECL|function|opl3sa_read
id|opl3sa_read
c_func
(paren
r_int
id|addr
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|tmp
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x1d
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* password */
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|addr
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* address */
id|tmp
op_assign
id|inb
c_func
(paren
l_int|0xf87
)paren
suffix:semicolon
multiline_comment|/* data */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
r_static
r_void
DECL|function|opl3sa_write
id|opl3sa_write
c_func
(paren
r_int
id|addr
comma
r_int
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
l_int|0x1d
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* password */
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|addr
)paren
comma
l_int|0xf86
)paren
suffix:semicolon
multiline_comment|/* address */
id|outb
c_func
(paren
(paren
(paren
r_int
r_char
)paren
id|data
)paren
comma
l_int|0xf87
)paren
suffix:semicolon
multiline_comment|/* data */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|opl3sa_detect
id|opl3sa_detect
c_func
(paren
r_void
)paren
(brace
r_int
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|tmp
op_assign
id|opl3sa_read
c_func
(paren
l_int|0x01
)paren
)paren
op_amp
l_int|0xc4
)paren
op_ne
l_int|0x04
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect error 1 (%x)&bslash;n&quot;
comma
id|opl3sa_read
c_func
(paren
l_int|0x01
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* return 0; */
)brace
multiline_comment|/*&n; * Check that the password feature has any effect&n; */
r_if
c_cond
(paren
id|inb
c_func
(paren
l_int|0xf87
)paren
op_eq
id|tmp
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect failed 2 (%x/%x)&bslash;n&quot;
comma
id|tmp
comma
id|inb
c_func
(paren
l_int|0xf87
)paren
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
(paren
id|opl3sa_read
c_func
(paren
l_int|0x04
)paren
op_amp
l_int|0xe0
)paren
op_rshift
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
l_int|0
op_logical_and
id|tmp
op_ne
l_int|1
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA detect failed 3 (%d)&bslash;n&quot;
comma
id|tmp
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA mode %x detected&bslash;n&quot;
comma
id|tmp
)paren
)paren
suffix:semicolon
id|opl3sa_write
c_func
(paren
l_int|0x01
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable MSS */
id|opl3sa_write
c_func
(paren
l_int|0x02
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable SB */
id|opl3sa_write
c_func
(paren
l_int|0x03
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Disable MPU */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; *    Probe and attach routines for the Windows Sound System mode of&n; *     OPL3-SA&n; */
r_int
DECL|function|probe_opl3sa_wss
id|probe_opl3sa_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
r_char
id|tmp
op_assign
l_int|0x24
suffix:semicolon
multiline_comment|/* WSS enable */
r_if
c_cond
(paren
id|check_region
c_func
(paren
l_int|0xf86
comma
l_int|2
)paren
)paren
multiline_comment|/* Control port is busy */
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;   * Check if the IO port returns valid signature. The original MS Sound&n;&t;   * system returns 0x04 while some cards (OPL3-SA for example)&n;&t;   * return 0x00.&n;&t; */
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|8
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OPL3-SA: MSS I/O port conflict (%x)&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|opl3sa_osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|opl3sa_detect
c_func
(paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OSS: OPL3-SA chip not found&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x530
suffix:colon
id|tmp
op_or_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xe80
suffix:colon
id|tmp
op_or_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf40
suffix:colon
id|tmp
op_or_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x604
suffix:colon
id|tmp
op_or_assign
l_int|0x18
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;OSS: Unsupported OPL3-SA/WSS base %x&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|opl3sa_write
c_func
(paren
l_int|0x01
comma
id|tmp
)paren
suffix:semicolon
multiline_comment|/* WSS setup register */
id|kilroy_was_here
op_assign
l_int|1
suffix:semicolon
id|ret
op_assign
id|probe_ms_sound
c_func
(paren
id|hw_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
id|request_region
c_func
(paren
l_int|0xf86
comma
l_int|2
comma
l_string|&quot;OPL3-SA&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_void
DECL|function|attach_opl3sa_wss
id|attach_opl3sa_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|nm
op_assign
id|num_mixers
suffix:semicolon
id|attach_ms_sound
c_func
(paren
id|hw_config
)paren
suffix:semicolon
r_if
c_cond
(paren
id|num_mixers
OG
id|nm
)paren
multiline_comment|/* A mixer was installed */
(brace
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE1
comma
id|SOUND_MIXER_CD
)paren
suffix:semicolon
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE2
comma
id|SOUND_MIXER_SYNTH
)paren
suffix:semicolon
id|AD1848_REROUTE
c_func
(paren
id|SOUND_MIXER_LINE3
comma
id|SOUND_MIXER_LINE
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|attach_opl3sa_mpu
id|attach_opl3sa_mpu
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if defined(CONFIG_UART401) &amp;&amp; defined(CONFIG_MIDI)
id|hw_config-&gt;name
op_assign
l_string|&quot;OPL3-SA (MPU401)&quot;
suffix:semicolon
id|attach_uart401
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#endif
)brace
r_int
DECL|function|probe_opl3sa_mpu
id|probe_opl3sa_mpu
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if defined(CONFIG_UART401) &amp;&amp; defined(CONFIG_MIDI)
r_int
r_char
id|conf
suffix:semicolon
r_static
r_char
id|irq_bits
(braket
)braket
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
op_minus
l_int|1
comma
l_int|1
comma
op_minus
l_int|1
comma
l_int|2
comma
op_minus
l_int|1
comma
l_int|3
comma
l_int|4
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|kilroy_was_here
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* OPL3-SA has not been detected earlier */
)brace
r_if
c_cond
(paren
id|mpu_initialized
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;OPL3-SA: MPU mode already initialized&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|4
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OPL3-SA: MPU I/O port conflict (%x)&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|hw_config-&gt;irq
OG
l_int|10
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OPL3-SA: Bad MPU IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OPL3-SA: Bad MPU IRQ %d&bslash;n&quot;
comma
id|hw_config-&gt;irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|hw_config-&gt;io_base
)paren
(brace
r_case
l_int|0x330
suffix:colon
id|conf
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x332
suffix:colon
id|conf
op_assign
l_int|0x20
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x334
suffix:colon
id|conf
op_assign
l_int|0x40
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x300
suffix:colon
id|conf
op_assign
l_int|0x60
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Invalid port */
)brace
id|conf
op_or_assign
l_int|0x83
suffix:semicolon
multiline_comment|/* MPU &amp; OPL3 (synth) &amp; game port enable */
id|conf
op_or_assign
id|irq_bits
(braket
id|hw_config-&gt;irq
)braket
op_lshift
l_int|2
suffix:semicolon
id|opl3sa_write
c_func
(paren
l_int|0x03
comma
id|conf
)paren
suffix:semicolon
id|mpu_initialized
op_assign
l_int|1
suffix:semicolon
r_return
id|probe_uart401
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
r_void
DECL|function|unload_opl3sa_wss
id|unload_opl3sa_wss
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|dma2
op_assign
id|hw_config-&gt;dma2
suffix:semicolon
r_if
c_cond
(paren
id|dma2
op_eq
op_minus
l_int|1
)paren
id|dma2
op_assign
id|hw_config-&gt;dma
suffix:semicolon
id|release_region
c_func
(paren
l_int|0xf86
comma
l_int|2
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|4
)paren
suffix:semicolon
id|ad1848_unload
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|4
comma
id|hw_config-&gt;irq
comma
id|hw_config-&gt;dma
comma
id|dma2
comma
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|unload_opl3sa_mpu
id|unload_opl3sa_mpu
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if defined(CONFIG_UART401) &amp;&amp; defined(CONFIG_MIDI)
id|unload_uart401
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#ifdef SB_OK
r_void
DECL|function|unload_opl3sa_sb
id|unload_opl3sa_sb
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#ifdef CONFIG_SBDSP
id|sb_dsp_unload
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#endif
macro_line|#endif
eof