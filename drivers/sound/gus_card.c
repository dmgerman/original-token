multiline_comment|/*&n; * sound/gus_card.c&n; *&n; * Detection routine for the Gravis Ultrasound.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;sound_config.h&quot;
macro_line|#include &quot;soundmodule.h&quot;
macro_line|#if defined(CONFIG_GUS) || defined(MODULE)
macro_line|#include &quot;gus_hw.h&quot;
r_void
id|gusintr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
suffix:semicolon
DECL|variable|gus_base
DECL|variable|gus_irq
DECL|variable|gus_dma
r_int
id|gus_base
op_assign
l_int|0
comma
id|gus_irq
op_assign
l_int|0
comma
id|gus_dma
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|gus_wave_volume
suffix:semicolon
r_extern
r_int
id|gus_pcm_volume
suffix:semicolon
r_extern
r_int
id|have_gus_max
suffix:semicolon
DECL|variable|gus_pnp_flag
r_int
id|gus_pnp_flag
op_assign
l_int|0
suffix:semicolon
DECL|function|attach_gus_card
r_void
id|attach_gus_card
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|snd_set_irq_handler
c_func
(paren
id|hw_config-&gt;irq
comma
id|gusintr
comma
l_string|&quot;Gravis Ultrasound&quot;
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
id|gus_wave_init
c_func
(paren
id|hw_config
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|16
comma
l_string|&quot;GUS&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|0x100
comma
l_int|12
comma
l_string|&quot;GUS&quot;
)paren
suffix:semicolon
multiline_comment|/* 0x10c-&gt; is MAX */
r_if
c_cond
(paren
id|sound_alloc_dma
c_func
(paren
id|hw_config-&gt;dma
comma
l_string|&quot;GUS&quot;
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;gus_card.c: Can&squot;t allocate DMA channel&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_ne
op_minus
l_int|1
op_logical_and
id|hw_config-&gt;dma2
op_ne
id|hw_config-&gt;dma
)paren
r_if
c_cond
(paren
id|sound_alloc_dma
c_func
(paren
id|hw_config-&gt;dma2
comma
l_string|&quot;GUS(2)&quot;
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;gus_card.c: Can&squot;t allocate DMA channel 2&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_MIDI)
id|gus_midi_init
c_func
(paren
id|hw_config
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|probe_gus
r_int
id|probe_gus
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
id|io_addr
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;card_subtype
op_eq
l_int|1
)paren
id|gus_pnp_flag
op_assign
l_int|1
suffix:semicolon
id|irq
op_assign
id|hw_config-&gt;irq
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;card_subtype
op_eq
l_int|0
)paren
multiline_comment|/* GUS/MAX/ACE */
r_if
c_cond
(paren
id|irq
op_ne
l_int|3
op_logical_and
id|irq
op_ne
l_int|5
op_logical_and
id|irq
op_ne
l_int|7
op_logical_and
id|irq
op_ne
l_int|9
op_logical_and
id|irq
op_ne
l_int|11
op_logical_and
id|irq
op_ne
l_int|12
op_logical_and
id|irq
op_ne
l_int|15
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GUS: Unsupported IRQ %d&bslash;n&quot;
comma
id|irq
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
l_int|16
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GUS: I/O range conflict (1)&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|0x100
comma
l_int|16
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;GUS: I/O range conflict (2)&bslash;n&quot;
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|gus_wave_detect
c_func
(paren
id|hw_config-&gt;io_base
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#ifndef EXCLUDE_GUS_IODETECT
multiline_comment|/*&n;&t; * Look at the possible base addresses (0x2X0, X=1, 2, 3, 4, 5, 6)&n;&t; */
r_for
c_loop
(paren
id|io_addr
op_assign
l_int|0x210
suffix:semicolon
id|io_addr
op_le
l_int|0x260
suffix:semicolon
id|io_addr
op_add_assign
l_int|0x10
)paren
r_if
c_cond
(paren
id|io_addr
op_ne
id|hw_config-&gt;io_base
)paren
multiline_comment|/*&n;&t;&t;&t;&t;&t;&t;&t; * Already tested&n;&t;&t;&t;&t;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|check_region
c_func
(paren
id|io_addr
comma
l_int|16
)paren
)paren
r_if
c_cond
(paren
op_logical_neg
id|check_region
c_func
(paren
id|io_addr
op_plus
l_int|0x100
comma
l_int|16
)paren
)paren
r_if
c_cond
(paren
id|gus_wave_detect
c_func
(paren
id|io_addr
)paren
)paren
(brace
id|hw_config-&gt;io_base
op_assign
id|io_addr
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unload_gus
r_void
id|unload_gus
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|DDB
c_func
(paren
id|printk
c_func
(paren
l_string|&quot;unload_gus(%x)&bslash;n&quot;
comma
id|hw_config-&gt;io_base
)paren
)paren
suffix:semicolon
id|gus_wave_unload
c_func
(paren
id|hw_config
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|16
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|hw_config-&gt;io_base
op_plus
l_int|0x100
comma
l_int|12
)paren
suffix:semicolon
multiline_comment|/* 0x10c-&gt; is MAX */
id|snd_release_irq
c_func
(paren
id|hw_config-&gt;irq
)paren
suffix:semicolon
id|sound_free_dma
c_func
(paren
id|hw_config-&gt;dma
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hw_config-&gt;dma2
op_ne
op_minus
l_int|1
op_logical_and
id|hw_config-&gt;dma2
op_ne
id|hw_config-&gt;dma
)paren
id|sound_free_dma
c_func
(paren
id|hw_config-&gt;dma2
)paren
suffix:semicolon
)brace
DECL|function|gusintr
r_void
id|gusintr
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|dummy
)paren
(brace
r_int
r_char
id|src
suffix:semicolon
r_extern
r_int
id|gus_timer_enabled
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_GUSMAX
r_if
c_cond
(paren
id|have_gus_max
)paren
id|adintr
c_func
(paren
id|irq
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|src
op_assign
id|inb
c_func
(paren
id|u_IrqStatus
)paren
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|src
op_amp
id|DMA_TC_IRQ
)paren
(brace
id|guswave_dma_irq
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|src
op_amp
(paren
id|MIDI_TX_IRQ
op_or
id|MIDI_RX_IRQ
)paren
)paren
(brace
macro_line|#if defined(CONFIG_MIDI)
id|gus_midi_interrupt
c_func
(paren
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
id|src
op_amp
(paren
id|GF1_TIMER1_IRQ
op_or
id|GF1_TIMER2_IRQ
)paren
)paren
(brace
macro_line|#if defined(CONFIG_SEQUENCER) || defined(CONFIG_SEQUENCER_MODULE)
r_if
c_cond
(paren
id|gus_timer_enabled
)paren
id|sound_timer_interrupt
c_func
(paren
)paren
suffix:semicolon
id|gus_write8
c_func
(paren
l_int|0x45
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Ack IRQ */
id|gus_timer_command
c_func
(paren
l_int|4
comma
l_int|0x80
)paren
suffix:semicolon
multiline_comment|/* Reset IRQ flags */
macro_line|#else
id|gus_write8
c_func
(paren
l_int|0x45
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Stop timers */
macro_line|#endif
)brace
r_if
c_cond
(paren
id|src
op_amp
(paren
id|WAVETABLE_IRQ
op_or
id|ENVELOPE_IRQ
)paren
)paren
id|gus_voice_irq
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Some extra code for the 16 bit sampling option&n; */
macro_line|#ifdef CONFIG_GUS16
DECL|function|probe_gus_db16
r_int
id|probe_gus_db16
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
r_return
id|ad1848_detect
c_func
(paren
id|hw_config-&gt;io_base
comma
l_int|NULL
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
)brace
DECL|function|attach_gus_db16
r_void
id|attach_gus_db16
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
macro_line|#if defined(CONFIG_GUS) || defined(MODULE)
id|gus_pcm_volume
op_assign
l_int|100
suffix:semicolon
id|gus_wave_volume
op_assign
l_int|90
suffix:semicolon
macro_line|#endif
id|hw_config-&gt;slots
(braket
l_int|3
)braket
op_assign
id|ad1848_init
c_func
(paren
l_string|&quot;GUS 16 bit sampling&quot;
comma
id|hw_config-&gt;io_base
comma
id|hw_config-&gt;irq
comma
id|hw_config-&gt;dma
comma
id|hw_config-&gt;dma
comma
l_int|0
comma
id|hw_config-&gt;osp
)paren
suffix:semicolon
)brace
DECL|function|unload_gus_db16
r_void
id|unload_gus_db16
c_func
(paren
r_struct
id|address_info
op_star
id|hw_config
)paren
(brace
id|ad1848_unload
c_func
(paren
id|hw_config-&gt;io_base
comma
id|hw_config-&gt;irq
comma
id|hw_config-&gt;dma
comma
id|hw_config-&gt;dma
comma
l_int|0
)paren
suffix:semicolon
id|sound_unload_audiodev
c_func
(paren
id|hw_config-&gt;slots
(braket
l_int|3
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef MODULE
DECL|variable|config
r_static
r_struct
id|address_info
id|config
suffix:semicolon
multiline_comment|/*&n; *    Note DMA2 of -1 has the right meaning in the GUS driver as well&n; *      as here. &n; */
DECL|variable|io
r_int
id|io
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|irq
r_int
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|dma
r_int
id|dma
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|dma16
r_int
id|dma16
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Set this for modules that need it */
DECL|variable|type
r_int
id|type
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* 1 for PnP */
DECL|variable|gus16
r_int
id|gus16
op_assign
l_int|0
suffix:semicolon
DECL|variable|db16
r_static
r_int
id|db16
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Has a Gus16 AD1848 on it */
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|dma16
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
id|MODULE_PARM
c_func
(paren
id|gus16
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|db16
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Gravis Ultrasound audio driver Copyright (C) by Hannu Savolainen 1993-1996&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|io
op_eq
op_minus
l_int|1
op_logical_or
id|dma
op_eq
op_minus
l_int|1
op_logical_or
id|irq
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;I/O, IRQ, and DMA are mandatory&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|config.io_base
op_assign
id|io
suffix:semicolon
id|config.irq
op_assign
id|irq
suffix:semicolon
id|config.dma
op_assign
id|dma
suffix:semicolon
id|config.dma2
op_assign
id|dma16
suffix:semicolon
id|config.card_subtype
op_assign
id|type
suffix:semicolon
macro_line|#if defined(CONFIG_GUS16)
r_if
c_cond
(paren
id|probe_gus_db16
c_func
(paren
op_amp
id|config
)paren
op_logical_and
id|gus16
)paren
(brace
id|attach_gus_db16
c_func
(paren
op_amp
id|config
)paren
suffix:semicolon
id|db16
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
id|probe_gus
c_func
(paren
op_amp
id|config
)paren
op_eq
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|attach_gus_card
c_func
(paren
op_amp
id|config
)paren
suffix:semicolon
id|SOUND_LOCK
suffix:semicolon
r_return
l_int|0
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
macro_line|#if defined(CONFIG_GUS16)
r_if
c_cond
(paren
id|db16
)paren
id|unload_gus_db16
c_func
(paren
op_amp
id|config
)paren
suffix:semicolon
macro_line|#endif
id|unload_gus
c_func
(paren
op_amp
id|config
)paren
suffix:semicolon
id|SOUND_LOCK_END
suffix:semicolon
)brace
macro_line|#endif
eof
