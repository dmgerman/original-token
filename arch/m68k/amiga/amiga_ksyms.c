macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#include &lt;asm/amipcmcia.h&gt;
r_extern
r_volatile
id|u_short
id|amiga_audio_min_period
suffix:semicolon
r_extern
id|u_short
id|amiga_audio_period
suffix:semicolon
multiline_comment|/*&n; * Add things here when you find the need for it.&n; */
DECL|variable|amiga_model
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_model
)paren
suffix:semicolon
DECL|variable|amiga_chipset
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_chipset
)paren
suffix:semicolon
DECL|variable|amiga_hw_present
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_hw_present
)paren
suffix:semicolon
DECL|variable|amiga_eclock
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_eclock
)paren
suffix:semicolon
DECL|variable|amiga_colorclock
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_colorclock
)paren
suffix:semicolon
DECL|variable|amiga_chip_alloc
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_chip_alloc
)paren
suffix:semicolon
DECL|variable|amiga_chip_free
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_chip_free
)paren
suffix:semicolon
DECL|variable|amiga_chip_avail
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_chip_avail
)paren
suffix:semicolon
DECL|variable|amiga_chip_size
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_chip_size
)paren
suffix:semicolon
DECL|variable|amiga_audio_period
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_audio_period
)paren
suffix:semicolon
DECL|variable|amiga_audio_min_period
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_audio_min_period
)paren
suffix:semicolon
DECL|variable|amiga_do_irq
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_do_irq
)paren
suffix:semicolon
DECL|variable|amiga_do_irq_list
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_do_irq_list
)paren
suffix:semicolon
DECL|variable|amiga_intena_vals
id|EXPORT_SYMBOL
c_func
(paren
id|amiga_intena_vals
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_AMIGA_PCMCIA
DECL|variable|pcmcia_reset
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_reset
)paren
suffix:semicolon
DECL|variable|pcmcia_copy_tuple
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_copy_tuple
)paren
suffix:semicolon
DECL|variable|pcmcia_program_voltage
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_program_voltage
)paren
suffix:semicolon
DECL|variable|pcmcia_access_speed
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_access_speed
)paren
suffix:semicolon
DECL|variable|pcmcia_write_enable
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_write_enable
)paren
suffix:semicolon
DECL|variable|pcmcia_write_disable
id|EXPORT_SYMBOL
c_func
(paren
id|pcmcia_write_disable
)paren
suffix:semicolon
macro_line|#endif
eof
