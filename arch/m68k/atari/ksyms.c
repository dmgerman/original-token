macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#include &lt;asm/atarikb.h&gt;
macro_line|#include &lt;asm/atari_joystick.h&gt;
macro_line|#include &lt;asm/atari_stdma.h&gt;
macro_line|#if 0
macro_line|#include &lt;asm/atari_acsi.h&gt;
macro_line|#endif
DECL|variable|mach_atari_symbol_table
r_static
r_struct
id|symbol_table
id|mach_atari_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
id|X
c_func
(paren
id|is_medusa
)paren
comma
id|X
c_func
(paren
id|atari_register_vme_int
)paren
comma
id|X
c_func
(paren
id|stdma_lock
)paren
comma
id|X
c_func
(paren
id|stdma_release
)paren
comma
id|X
c_func
(paren
id|stdma_others_waiting
)paren
comma
id|X
c_func
(paren
id|stdma_islocked
)paren
comma
id|X
c_func
(paren
id|atari_mouse_buttons
)paren
comma
id|X
c_func
(paren
id|atari_mouse_interrupt_hook
)paren
comma
id|X
c_func
(paren
id|atari_MIDI_interrupt_hook
)paren
comma
id|X
c_func
(paren
id|ikbd_write
)paren
comma
id|X
c_func
(paren
id|ikbd_mouse_y0_top
)paren
comma
id|X
c_func
(paren
id|ikbd_mouse_thresh
)paren
comma
id|X
c_func
(paren
id|ikbd_mouse_rel_pos
)paren
comma
id|X
c_func
(paren
id|ikbd_mouse_disable
)paren
comma
macro_line|#if 0
macro_line|#ifdef CONFIG_ATARI_ACSI
id|X
c_func
(paren
id|acsi_wait_for_IRQ
)paren
comma
id|X
c_func
(paren
id|acsi_wait_for_noIRQ
)paren
comma
id|X
c_func
(paren
id|acsicmd_nodma
)paren
comma
id|X
c_func
(paren
id|acsi_getstatus
)paren
comma
macro_line|#ifdef CONFIG_ATARI_SLM
id|X
c_func
(paren
id|acsi_extstatus
)paren
comma
id|X
c_func
(paren
id|acsi_end_extstatus
)paren
comma
id|X
c_func
(paren
id|acsi_extcmd
)paren
comma
macro_line|#endif
macro_line|#endif
macro_line|#endif /* 0 */
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
DECL|function|mach_atari_syms_export
r_void
id|mach_atari_syms_export
c_func
(paren
r_void
)paren
(brace
id|register_symtab
c_func
(paren
op_amp
id|mach_atari_symbol_table
)paren
suffix:semicolon
)brace
eof