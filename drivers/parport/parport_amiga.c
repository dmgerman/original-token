multiline_comment|/* Low-level parallel port routines for the Amiga buildin port&n; *&n; * Author: Joerg Dorchain &lt;dorchain@wirbel.com&gt;&n; *&n; * This is a complete rewrite of the code, but based heaviy upon the old&n; * lp_intern. code.&n; *&n; * The built-in Amiga parallel port provides one port at a fixed address&n; * with 8 bisdirecttional data lines (D0 - D7) and 3 bidirectional status&n; * lines (BUSY, POUT, SEL), 1 output control line /STROBE (raised automatically in&n; * hardware when the data register is accessed), and 1 input control line&n; * /ACK, able to cause an interrupt, but both not directly settable by&n; * software.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DPRINTK
mdefine_line|#define DPRINTK printk
macro_line|#else
DECL|function|DPRINTK
r_static
r_inline
r_int
id|DPRINTK
c_func
(paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|this_port
r_static
r_struct
id|parport
op_star
id|this_port
op_assign
l_int|NULL
suffix:semicolon
DECL|function|amiga_write_data
r_static
r_void
id|amiga_write_data
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|data
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;write_data %c&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
multiline_comment|/* Triggers also /STROBE. This behavior cannot be changed */
id|ciaa.prb
op_assign
id|data
suffix:semicolon
)brace
DECL|function|amiga_read_data
r_static
r_int
r_char
id|amiga_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
multiline_comment|/* Triggers also /STROBE. This behavior cannot be changed */
r_return
id|ciaa.prb
suffix:semicolon
)brace
macro_line|#if 0
r_static
r_int
r_char
id|control_pc_to_amiga
c_func
(paren
r_int
r_char
id|control
)paren
(brace
r_int
r_char
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_DIRECTION
)paren
multiline_comment|/* XXX: What is this? */
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_INTEN
)paren
multiline_comment|/* XXX: What is INTEN? */
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_SELECT
)paren
multiline_comment|/* XXX: What is SELECP? */
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_INIT
)paren
multiline_comment|/* INITP */
multiline_comment|/* reset connected to cpu reset pin */
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_AUTOFD
)paren
multiline_comment|/* AUTOLF */
multiline_comment|/* Not connected */
suffix:semicolon
r_if
c_cond
(paren
id|control
op_amp
id|PARPORT_CONTROL_STROBE
)paren
multiline_comment|/* Strobe */
multiline_comment|/* Handled only directly by hardware */
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|control_amiga_to_pc
r_static
r_int
r_char
id|control_amiga_to_pc
c_func
(paren
r_int
r_char
id|control
)paren
(brace
r_return
id|PARPORT_CONTROL_INTEN
op_or
id|PARPORT_CONTROL_SELECT
op_or
id|PARPORT_CONTROL_AUTOFD
op_or
id|PARPORT_CONTROL_STROBE
suffix:semicolon
multiline_comment|/* fake value: interrupt enable, select in, no reset,&n;&t;no autolf, no strobe - seems to be closest the wiring diagram */
)brace
DECL|function|amiga_write_control
r_static
r_void
id|amiga_write_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|control
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;write_control %02x&bslash;n&quot;
comma
id|control
)paren
suffix:semicolon
multiline_comment|/* No implementation possible */
)brace
DECL|function|amiga_read_control
r_static
r_int
r_char
id|amiga_read_control
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;read_control &bslash;n&quot;
)paren
suffix:semicolon
r_return
id|control_amiga_to_pc
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|amiga_frob_control
r_static
r_int
r_char
id|amiga_frob_control
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|mask
comma
r_int
r_char
id|val
)paren
(brace
r_int
r_char
id|old
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;frob_control mask %02x, value %02x&bslash;n&quot;
comma
id|mask
comma
id|val
)paren
suffix:semicolon
id|old
op_assign
id|amiga_read_control
c_func
(paren
id|p
)paren
suffix:semicolon
id|amiga_write_control
c_func
(paren
id|p
comma
(paren
id|old
op_amp
op_complement
id|mask
)paren
op_xor
id|val
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
DECL|function|status_pc_to_amiga
r_static
r_int
r_char
id|status_pc_to_amiga
c_func
(paren
r_int
r_char
id|status
)paren
(brace
r_int
r_char
id|ret
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_STATUS_BUSY
)paren
multiline_comment|/* Busy */
id|ret
op_and_assign
op_complement
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_STATUS_ACK
)paren
multiline_comment|/* Ack */
multiline_comment|/* handled in hardware */
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_STATUS_PAPEROUT
)paren
multiline_comment|/* PaperOut */
id|ret
op_or_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_STATUS_SELECT
)paren
multiline_comment|/* select */
id|ret
op_or_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|PARPORT_STATUS_ERROR
)paren
multiline_comment|/* error */
multiline_comment|/* not connected */
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|status_amiga_to_pc
r_static
r_int
r_char
id|status_amiga_to_pc
c_func
(paren
r_int
r_char
id|status
)paren
(brace
r_int
r_char
id|ret
op_assign
id|PARPORT_STATUS_BUSY
op_or
id|PARPORT_STATUS_ACK
op_or
id|PARPORT_STATUS_ERROR
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|1
)paren
multiline_comment|/* Busy */
id|ret
op_and_assign
op_complement
id|PARPORT_STATUS_BUSY
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|2
)paren
multiline_comment|/* PaperOut */
id|ret
op_or_assign
id|PARPORT_STATUS_PAPEROUT
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|4
)paren
multiline_comment|/* Selected */
id|ret
op_or_assign
id|PARPORT_STATUS_SELECT
suffix:semicolon
multiline_comment|/* the rest is not connected or handled autonomously in hardware */
r_return
id|ret
suffix:semicolon
)brace
DECL|function|amiga_write_status
r_static
r_void
id|amiga_write_status
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
r_char
id|status
)paren
(brace
id|DPRINTK
c_func
(paren
l_string|&quot;write_status %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
id|ciab.pra
op_or_assign
(paren
id|ciab.pra
op_amp
l_int|0xf8
)paren
op_or
id|status_pc_to_amiga
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
DECL|function|amiga_read_status
r_static
r_int
r_char
id|amiga_read_status
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_int
r_char
id|status
suffix:semicolon
id|status
op_assign
id|status_amiga_to_pc
c_func
(paren
id|ciab.pra
op_amp
l_int|7
)paren
suffix:semicolon
id|DPRINTK
c_func
(paren
l_string|&quot;read_status %02x&bslash;n&quot;
comma
id|status
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
DECL|function|amiga_change_mode
r_static
r_void
id|amiga_change_mode
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_int
id|m
)paren
(brace
multiline_comment|/* XXX: This port only has one mode, and I am&n;&t;not sure about the corresponding PC-style mode*/
)brace
multiline_comment|/* as this ports irq handling is already done, we use a generic funktion */
DECL|function|amiga_interrupt
r_static
r_void
id|amiga_interrupt
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
id|regs
)paren
(brace
id|parport_generic_irq
c_func
(paren
id|irq
comma
(paren
r_struct
id|parport
op_star
)paren
id|dev_id
comma
id|regs
)paren
suffix:semicolon
)brace
DECL|function|amiga_init_state
r_static
r_void
id|amiga_init_state
c_func
(paren
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|s-&gt;u.amiga.data
op_assign
l_int|0
suffix:semicolon
id|s-&gt;u.amiga.datadir
op_assign
l_int|255
suffix:semicolon
id|s-&gt;u.amiga.status
op_assign
l_int|0
suffix:semicolon
id|s-&gt;u.amiga.statusdir
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|amiga_save_state
r_static
r_void
id|amiga_save_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|s-&gt;u.amiga.data
op_assign
id|ciaa.prb
suffix:semicolon
id|s-&gt;u.amiga.datadir
op_assign
id|ciaa.ddrb
suffix:semicolon
id|s-&gt;u.amiga.status
op_assign
id|ciab.pra
op_amp
l_int|7
suffix:semicolon
id|s-&gt;u.amiga.statusdir
op_assign
id|ciab.ddra
op_amp
l_int|7
suffix:semicolon
)brace
DECL|function|amiga_restore_state
r_static
r_void
id|amiga_restore_state
c_func
(paren
r_struct
id|parport
op_star
id|p
comma
r_struct
id|parport_state
op_star
id|s
)paren
(brace
id|ciaa.prb
op_assign
id|s-&gt;u.amiga.data
suffix:semicolon
id|ciaa.ddrb
op_assign
id|s-&gt;u.amiga.datadir
suffix:semicolon
id|ciab.pra
op_or_assign
(paren
id|ciab.pra
op_amp
l_int|0xf8
)paren
op_or
id|s-&gt;u.amiga.status
suffix:semicolon
id|ciab.ddra
op_or_assign
(paren
id|ciab.ddra
op_amp
l_int|0xf8
)paren
op_or
id|s-&gt;u.amiga.statusdir
suffix:semicolon
)brace
DECL|function|amiga_enable_irq
r_static
r_void
id|amiga_enable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
id|enable_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
)paren
suffix:semicolon
)brace
DECL|function|amiga_disable_irq
r_static
r_void
id|amiga_disable_irq
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
id|disable_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
)paren
suffix:semicolon
)brace
DECL|function|amiga_inc_use_count
r_static
r_void
id|amiga_inc_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
DECL|function|amiga_dec_use_count
r_static
r_void
id|amiga_dec_use_count
c_func
(paren
r_void
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|pp_amiga_ops
r_static
r_struct
id|parport_operations
id|pp_amiga_ops
op_assign
(brace
id|amiga_write_data
comma
id|amiga_read_data
comma
id|amiga_write_control
comma
id|amiga_read_control
comma
id|amiga_frob_control
comma
id|amiga_read_status
comma
id|amiga_enable_irq
comma
id|amiga_disable_irq
comma
l_int|NULL
comma
multiline_comment|/* data_forward */
l_int|NULL
comma
multiline_comment|/* data_reverse */
id|amiga_interrupt
comma
id|amiga_init_state
comma
id|amiga_save_state
comma
id|amiga_restore_state
comma
id|amiga_inc_use_count
comma
id|amiga_dec_use_count
comma
id|parport_ieee1284_epp_write_data
comma
id|parport_ieee1284_epp_read_data
comma
multiline_comment|/* impossible? */
id|parport_ieee1284_epp_write_addr
comma
id|parport_ieee1284_epp_read_addr
comma
multiline_comment|/* impossible? */
id|parport_ieee1284_ecp_write_data
comma
id|parport_ieee1284_ecp_read_data
comma
multiline_comment|/* impossible? */
id|parport_ieee1284_ecp_write_addr
comma
id|parport_ieee1284_write_compat
comma
multiline_comment|/* FIXME - need to write amiga one */
id|parport_ieee1284_read_nibble
comma
id|parport_ieee1284_read_byte
comma
multiline_comment|/* impossible? */
)brace
suffix:semicolon
multiline_comment|/* ----------- Initialisation code --------------------------------- */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|parport_amiga_init
c_func
(paren
r_void
)paren
)paren
(brace
r_struct
id|parport
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|AMI_PARALLEL
)paren
)paren
(brace
id|ciaa.ddrb
op_assign
l_int|0xff
suffix:semicolon
id|ciab.ddra
op_and_assign
l_int|0xf8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|p
op_assign
id|parport_register_port
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|ciaa.prb
comma
id|IRQ_AMIGA_CIAA_FLG
comma
id|PARPORT_DMA_NONE
comma
op_amp
id|pp_amiga_ops
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|this_port
op_assign
id|p
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Amiga built-in port using irq&bslash;n&quot;
comma
id|p-&gt;name
)paren
suffix:semicolon
multiline_comment|/* XXX: set operating mode */
id|parport_proc_register
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|amiga_interrupt
comma
l_int|0
comma
id|p-&gt;name
comma
id|p
)paren
)paren
(brace
id|parport_unregister_port
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parport_probe_hook
)paren
(paren
op_star
id|parport_probe_hook
)paren
(paren
id|p
)paren
suffix:semicolon
id|parport_announce_port
(paren
id|p
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Joerg Dorchain&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Parport Driver for Amiga builtin Port&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Amiga builtin Parallel Port&quot;
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
r_return
op_logical_neg
id|parport_amiga_init
c_func
(paren
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
r_if
c_cond
(paren
id|p-&gt;irq
op_ne
id|PARPORT_IRQ_NONE
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|p
)paren
suffix:semicolon
id|parport_proc_unregister
c_func
(paren
id|this_port
)paren
suffix:semicolon
id|parport_unregister_port
c_func
(paren
id|this_port
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
