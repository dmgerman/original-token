multiline_comment|/* Low-level parallel port routines for Archimedes onboard hardware&n; *&n; * Author: Phil Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
multiline_comment|/* This driver is for the parallel port hardware found on Acorn&squot;s old&n; * range of Archimedes machines.  The A5000 and newer systems have PC-style&n; * I/O hardware and should use the parport_pc driver instead.&n; *&n; * The Acorn printer port hardware is very simple.  There is a single 8-bit&n; * write-only latch for the data port and control/status bits are handled&n; * with various auxilliary input and output lines.  The port is not&n; * bidirectional, does not support any modes other than SPP, and has only&n; * a subset of the standard printer control lines connected.&n; */
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/oldlatches.h&gt;
macro_line|#include &lt;asm/arch/irqs.h&gt;
DECL|macro|DATA_LATCH
mdefine_line|#define DATA_LATCH    0x3350010
multiline_comment|/* ARC can&squot;t read from the data latch, so we must use a soft copy. */
DECL|variable|data_copy
r_static
r_int
r_char
id|data_copy
suffix:semicolon
DECL|function|arc_interrupt
r_static
r_void
id|arc_interrupt
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
DECL|function|arc_write_data
r_static
r_void
id|arc_write_data
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
id|data_copy
op_assign
id|data
suffix:semicolon
id|outb
c_func
(paren
id|data
comma
id|DATA_LATCH
)paren
suffix:semicolon
)brace
DECL|function|arc_read_data
r_static
r_int
r_char
id|arc_read_data
c_func
(paren
r_struct
id|parport
op_star
id|p
)paren
(brace
r_return
id|data_copy
suffix:semicolon
)brace
DECL|function|arc_inc_use_count
r_static
r_void
id|arc_inc_use_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|arc_dec_use_count
r_static
r_void
id|arc_dec_use_count
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|function|arc_fill_inode
r_static
r_void
id|arc_fill_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|fill
)paren
(brace
macro_line|#ifdef MODULE
r_if
c_cond
(paren
id|fill
)paren
id|MOD_INC_USE_COUNT
suffix:semicolon
r_else
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|parport_arc_ops
r_static
r_struct
id|parport_operations
id|parport_arc_ops
op_assign
(brace
id|arc_write_data
comma
id|arc_read_data
comma
id|arc_write_control
comma
id|arc_read_control
comma
id|arc_frob_control
comma
l_int|NULL
comma
multiline_comment|/* write_econtrol */
l_int|NULL
comma
multiline_comment|/* read_econtrol */
l_int|NULL
comma
multiline_comment|/* frob_econtrol */
id|arc_write_status
comma
id|arc_read_status
comma
l_int|NULL
comma
multiline_comment|/* write_fifo */
l_int|NULL
comma
multiline_comment|/* read_fifo */
l_int|NULL
comma
multiline_comment|/* change_mode */
id|arc_release_resources
comma
id|arc_claim_resources
comma
l_int|NULL
comma
multiline_comment|/* epp_write_data */
l_int|NULL
comma
multiline_comment|/* epp_read_data */
l_int|NULL
comma
multiline_comment|/* epp_write_addr */
l_int|NULL
comma
multiline_comment|/* epp_read_addr */
l_int|NULL
comma
multiline_comment|/* epp_check_timeout */
l_int|NULL
comma
multiline_comment|/* epp_write_block */
l_int|NULL
comma
multiline_comment|/* epp_read_block */
l_int|NULL
comma
multiline_comment|/* ecp_write_block */
l_int|NULL
comma
multiline_comment|/* epp_write_block */
id|arc_init_state
comma
id|arc_save_state
comma
id|arc_restore_state
comma
id|arc_enable_irq
comma
id|arc_disable_irq
comma
id|arc_interrupt
comma
id|arc_inc_use_count
comma
id|arc_dec_use_count
comma
id|arc_fill_inode
)brace
suffix:semicolon
multiline_comment|/* --- Initialisation code -------------------------------- */
DECL|function|parport_arc_init
r_int
id|parport_arc_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Archimedes hardware provides only one port, at a fixed address */
r_struct
id|parport
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|DATA_LATCH
comma
l_int|4
)paren
)paren
r_return
l_int|0
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
id|base
comma
id|IRQ_PRINTERACK
comma
id|PARPORT_DMA_NONE
comma
op_amp
id|parport_arc_ops
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|p-&gt;modes
op_assign
id|PARPORT_MODE_ARCSPP
suffix:semicolon
id|p-&gt;size
op_assign
l_int|4
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Archimedes on-board port, using irq %d&bslash;n&quot;
comma
id|p-&gt;irq
)paren
suffix:semicolon
id|parport_proc_register
c_func
(paren
id|p
)paren
suffix:semicolon
id|p-&gt;flags
op_or_assign
id|PARPORT_FLAG_COMA
suffix:semicolon
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
r_return
l_int|1
suffix:semicolon
)brace
eof
