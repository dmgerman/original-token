multiline_comment|/*&n; * sound/cs4232.c&n; *&n; * The low level driver for Crystal CS4232 based cards. The CS4232 is&n; * a PnP compatible chip which contains a CS4231A codec, SB emulation,&n; * a MPU401 compatible MIDI port, joystick and synthesizer and IDE CD-ROM &n; * interfaces. This is just a temporary driver until full PnP support&n; * gets implemented. Just the WSS codec, FM synth and the MIDI ports are&n; * supported. Other interfaces are left uninitialized.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1996&n; *&n; * USS/Lite for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#if defined(CONFIG_CS4232)
DECL|macro|KEY_PORT
mdefine_line|#define KEY_PORT&t;0x279&t;/* Same as LPT1 status port */
DECL|macro|CSN_NUM
mdefine_line|#define CSN_NUM&t;&t;0x99&t;/* Just a random number */
DECL|variable|osp
r_static
r_int
op_star
id|osp
suffix:semicolon
r_static
r_void
DECL|function|CS_OUT
id|CS_OUT
(paren
r_int
r_char
id|a
)paren
(brace
id|outb
(paren
id|a
comma
id|KEY_PORT
)paren
suffix:semicolon
)brace
DECL|macro|CS_OUT2
mdefine_line|#define CS_OUT2(a, b)&t;&t;{CS_OUT(a);CS_OUT(b);}
DECL|macro|CS_OUT3
mdefine_line|#define CS_OUT3(a, b, c)&t;{CS_OUT(a);CS_OUT(b);CS_OUT(c);}
DECL|variable|mpu_base
DECL|variable|mpu_irq
r_static
r_int
id|mpu_base
op_assign
l_int|0
comma
id|mpu_irq
op_assign
l_int|0
suffix:semicolon
DECL|variable|mpu_detected
r_static
r_int
id|mpu_detected
op_assign
l_int|0
suffix:semicolon
r_int
DECL|function|probe_cs4232_mpu
id|probe_cs4232_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/*&n; * Just write down the config values.&n; */
id|mpu_base
op_assign
id|hw_config-&gt;io_base
suffix:semicolon
id|mpu_irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|attach_cs4232_mpu
id|attach_cs4232_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
)brace
DECL|variable|crystal_key
r_static
r_int
r_char
id|crystal_key
(braket
)braket
op_assign
multiline_comment|/* A 32 byte magic key sequence */
(brace
l_int|0x96
comma
l_int|0x35
comma
l_int|0x9a
comma
l_int|0xcd
comma
l_int|0xe6
comma
l_int|0xf3
comma
l_int|0x79
comma
l_int|0xbc
comma
l_int|0x5e
comma
l_int|0xaf
comma
l_int|0x57
comma
l_int|0x2b
comma
l_int|0x15
comma
l_int|0x8a
comma
l_int|0xc5
comma
l_int|0xe2
comma
l_int|0xf1
comma
l_int|0xf8
comma
l_int|0x7c
comma
l_int|0x3e
comma
l_int|0x9f
comma
l_int|0x4f
comma
l_int|0x27
comma
l_int|0x13
comma
l_int|0x09
comma
l_int|0x84
comma
l_int|0x42
comma
l_int|0xa1
comma
l_int|0xd0
comma
l_int|0x68
comma
l_int|0x34
comma
l_int|0x1a
)brace
suffix:semicolon
r_int
DECL|function|probe_cs4232
id|probe_cs4232
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|i
comma
id|n
suffix:semicolon
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_int
id|dma1
op_assign
id|hw_config-&gt;dma
comma
id|dma2
op_assign
id|hw_config-&gt;dma2
suffix:semicolon
r_static
id|wait_handle
op_star
id|cs_sleeper
op_assign
l_int|NULL
suffix:semicolon
r_static
r_volatile
r_struct
id|snd_wait
id|cs_sleep_flag
op_assign
(brace
l_int|0
)brace
suffix:semicolon
id|osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
multiline_comment|/*&n; * Verify that the I/O port range is free.&n; */
r_if
c_cond
(paren
id|check_region
(paren
id|base
comma
l_int|4
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;cs4232.c: I/O port 0x%03x not free&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ad1848_detect
(paren
id|hw_config-&gt;io_base
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* The card is already active */
multiline_comment|/*&n; * This version of the driver doesn&squot;t use the PnP method when configuring&n; * the card but a simplified method defined by Crystal. This means that&n; * just one CS4232 compatible device can exist on the system. Also this&n; * method conflicts with possible PnP support in the OS. For this reason &n; * driver is just a temporary kludge.&n; */
multiline_comment|/*&n; * Repeat initialization few times since it doesn&squot;t always succeed in&n; * first time.&n; */
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|4
suffix:semicolon
id|n
op_increment
)paren
(brace
id|cs_sleep_flag.flags
op_assign
id|WK_NONE
suffix:semicolon
multiline_comment|/*&n; * Wake up the card by sending a 32 byte Crystal key to the key port.&n; */
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
op_increment
)paren
id|CS_OUT
(paren
id|crystal_key
(braket
id|i
)braket
)paren
suffix:semicolon
(brace
r_int
r_int
id|tlimit
suffix:semicolon
r_if
c_cond
(paren
id|HZ
op_div
l_int|10
)paren
id|current_set_timeout
(paren
id|tlimit
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|10
)paren
)paren
suffix:semicolon
r_else
id|tlimit
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|cs_sleep_flag.flags
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|cs_sleeper
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs_sleep_flag.flags
op_amp
id|WK_WAKEUP
)paren
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_ge
id|tlimit
)paren
id|cs_sleep_flag.flags
op_or_assign
id|WK_TIMEOUT
suffix:semicolon
)brace
id|cs_sleep_flag.flags
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Delay */
multiline_comment|/*&n; * Now set the CSN (Card Select Number).&n; */
id|CS_OUT2
(paren
l_int|0x06
comma
id|CSN_NUM
)paren
suffix:semicolon
multiline_comment|/*&n; * Then set some config bytes. First logical device 0 &n; */
id|CS_OUT2
(paren
l_int|0x15
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* Select logical device 0 (WSS/SB/FM) */
id|CS_OUT3
(paren
l_int|0x47
comma
(paren
id|base
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|base
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* WSS base */
r_if
c_cond
(paren
id|check_region
(paren
l_int|0x388
comma
l_int|4
)paren
)paren
multiline_comment|/* Not free */
id|CS_OUT3
(paren
l_int|0x48
comma
l_int|0x00
comma
l_int|0x00
)paren
multiline_comment|/* FM base off */
r_else
id|CS_OUT3
(paren
l_int|0x48
comma
l_int|0x03
comma
l_int|0x88
)paren
suffix:semicolon
multiline_comment|/* FM base 0x388 */
id|CS_OUT3
(paren
l_int|0x42
comma
l_int|0x00
comma
l_int|0x00
)paren
suffix:semicolon
multiline_comment|/* SB base off */
id|CS_OUT2
(paren
l_int|0x22
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* SB+WSS IRQ */
id|CS_OUT2
(paren
l_int|0x2a
comma
id|dma1
)paren
suffix:semicolon
multiline_comment|/* SB+WSS DMA */
r_if
c_cond
(paren
id|dma2
op_ne
op_minus
l_int|1
)paren
id|CS_OUT2
(paren
l_int|0x25
comma
id|dma2
)paren
multiline_comment|/* WSS DMA2 */
r_else
id|CS_OUT2
(paren
l_int|0x25
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* No WSS DMA2 */
id|CS_OUT2
(paren
l_int|0x33
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Activate logical dev 0 */
(brace
r_int
r_int
id|tlimit
suffix:semicolon
r_if
c_cond
(paren
id|HZ
op_div
l_int|10
)paren
id|current_set_timeout
(paren
id|tlimit
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|10
)paren
)paren
suffix:semicolon
r_else
id|tlimit
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|cs_sleep_flag.flags
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|cs_sleeper
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs_sleep_flag.flags
op_amp
id|WK_WAKEUP
)paren
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_ge
id|tlimit
)paren
id|cs_sleep_flag.flags
op_or_assign
id|WK_TIMEOUT
suffix:semicolon
)brace
id|cs_sleep_flag.flags
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Delay */
multiline_comment|/*&n; * Initialize logical device 3 (MPU)&n; */
macro_line|#if (defined(CONFIG_MPU401) || defined(CONFIG_MPU_EMU)) &amp;&amp; defined(CONFIG_MIDI)
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
)paren
(brace
id|CS_OUT2
(paren
l_int|0x15
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Select logical device 3 (MPU) */
id|CS_OUT3
(paren
l_int|0x47
comma
(paren
id|mpu_base
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|mpu_base
op_amp
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* MPU base */
id|CS_OUT2
(paren
l_int|0x22
comma
id|mpu_irq
)paren
suffix:semicolon
multiline_comment|/* MPU IRQ */
id|CS_OUT2
(paren
l_int|0x33
comma
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Activate logical dev 3 */
)brace
macro_line|#endif
multiline_comment|/*&n; * Finally activate the chip&n; */
id|CS_OUT
(paren
l_int|0x79
)paren
suffix:semicolon
(brace
r_int
r_int
id|tlimit
suffix:semicolon
r_if
c_cond
(paren
id|HZ
op_div
l_int|5
)paren
id|current_set_timeout
(paren
id|tlimit
op_assign
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|5
)paren
)paren
suffix:semicolon
r_else
id|tlimit
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|cs_sleep_flag.flags
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|cs_sleeper
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs_sleep_flag.flags
op_amp
id|WK_WAKEUP
)paren
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_ge
id|tlimit
)paren
id|cs_sleep_flag.flags
op_or_assign
id|WK_TIMEOUT
suffix:semicolon
)brace
id|cs_sleep_flag.flags
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Delay */
multiline_comment|/*&n; * Then try to detect the codec part of the chip&n; */
r_if
c_cond
(paren
id|ad1848_detect
(paren
id|hw_config-&gt;io_base
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
)paren
r_return
l_int|1
suffix:semicolon
(brace
r_int
r_int
id|tlimit
suffix:semicolon
r_if
c_cond
(paren
id|HZ
)paren
id|current_set_timeout
(paren
id|tlimit
op_assign
id|jiffies
op_plus
(paren
id|HZ
)paren
)paren
suffix:semicolon
r_else
id|tlimit
op_assign
(paren
r_int
r_int
)paren
op_minus
l_int|1
suffix:semicolon
id|cs_sleep_flag.flags
op_assign
id|WK_SLEEP
suffix:semicolon
id|module_interruptible_sleep_on
(paren
op_amp
id|cs_sleeper
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cs_sleep_flag.flags
op_amp
id|WK_WAKEUP
)paren
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_ge
id|tlimit
)paren
id|cs_sleep_flag.flags
op_or_assign
id|WK_TIMEOUT
suffix:semicolon
)brace
id|cs_sleep_flag.flags
op_and_assign
op_complement
id|WK_SLEEP
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Longer delay */
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|attach_cs4232
id|attach_cs4232
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_int
id|dma1
op_assign
id|hw_config-&gt;dma
comma
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
id|dma1
suffix:semicolon
id|ad1848_init
(paren
l_string|&quot;CS4232&quot;
comma
id|base
comma
id|irq
comma
id|dma1
comma
multiline_comment|/* Playback DMA */
id|dma2
comma
multiline_comment|/* Capture DMA */
l_int|0
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
macro_line|#if (defined(CONFIG_MPU401) || defined(CONFIG_MPU_EMU)) &amp;&amp; defined(CONFIG_MIDI)
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
)paren
(brace
r_static
r_struct
id|address_info
id|hw_config2
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Ensure it&squot;s initialized */
id|hw_config2.io_base
op_assign
id|mpu_base
suffix:semicolon
id|hw_config2.irq
op_assign
id|mpu_irq
suffix:semicolon
id|hw_config2.dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.dma2
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.always_detect
op_assign
l_int|0
suffix:semicolon
id|hw_config2.name
op_assign
l_int|NULL
suffix:semicolon
id|hw_config2.driver_use_1
op_assign
l_int|0
suffix:semicolon
id|hw_config2.driver_use_2
op_assign
l_int|0
suffix:semicolon
id|hw_config2.card_subtype
op_assign
l_int|0
suffix:semicolon
id|hw_config2.osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
r_if
c_cond
(paren
id|probe_mpu401
(paren
op_amp
id|hw_config2
)paren
)paren
(brace
id|mpu_detected
op_assign
l_int|1
suffix:semicolon
id|attach_mpu401
(paren
op_amp
id|hw_config2
)paren
suffix:semicolon
)brace
r_else
(brace
id|mpu_base
op_assign
id|mpu_irq
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
r_void
DECL|function|unload_cs4232
id|unload_cs4232
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|base
op_assign
id|hw_config-&gt;io_base
comma
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_int
id|dma1
op_assign
id|hw_config-&gt;dma
comma
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
id|dma1
suffix:semicolon
id|ad1848_unload
(paren
id|base
comma
id|irq
comma
id|dma1
comma
multiline_comment|/* Playback DMA */
id|dma2
comma
multiline_comment|/* Capture DMA */
l_int|0
)paren
suffix:semicolon
macro_line|#if (defined(CONFIG_MPU401) || defined(CONFIG_MPU_EMU)) &amp;&amp; defined(CONFIG_MIDI)
r_if
c_cond
(paren
id|mpu_base
op_ne
l_int|0
op_logical_and
id|mpu_irq
op_ne
l_int|0
op_logical_and
id|mpu_detected
)paren
(brace
r_static
r_struct
id|address_info
id|hw_config2
op_assign
(brace
l_int|0
)brace
suffix:semicolon
multiline_comment|/* Ensure it&squot;s initialized */
id|hw_config2.io_base
op_assign
id|mpu_base
suffix:semicolon
id|hw_config2.irq
op_assign
id|mpu_irq
suffix:semicolon
id|hw_config2.dma
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.dma2
op_assign
op_minus
l_int|1
suffix:semicolon
id|hw_config2.always_detect
op_assign
l_int|0
suffix:semicolon
id|hw_config2.name
op_assign
l_int|NULL
suffix:semicolon
id|hw_config2.driver_use_1
op_assign
l_int|0
suffix:semicolon
id|hw_config2.driver_use_2
op_assign
l_int|0
suffix:semicolon
id|hw_config2.card_subtype
op_assign
l_int|0
suffix:semicolon
id|hw_config2.osp
op_assign
id|hw_config-&gt;osp
suffix:semicolon
id|unload_mpu401
(paren
op_amp
id|hw_config2
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_void
DECL|function|unload_cs4232_mpu
id|unload_cs4232_mpu
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
multiline_comment|/* Not required. Handled by cs4232_unload */
)brace
macro_line|#endif
eof
