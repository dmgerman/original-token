multiline_comment|/* Parallel-port routines for ARC onboard hardware.&n; *&n; * Author: Phil Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/arch/oldlatches.h&gt;
DECL|macro|DATA_LATCH
mdefine_line|#define DATA_LATCH    0x3350010
multiline_comment|/* ARC can&squot;t read from the data latch, so we must use a soft copy. */
DECL|variable|data_copy
r_static
r_int
r_int
id|data_copy
suffix:semicolon
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
r_int
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
r_int
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
DECL|variable|arc_ops
r_static
r_struct
id|parport_operations
id|arc_ops
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
id|arc_save_state
comma
id|arc_restore_state
comma
id|arc_enable_irq
comma
id|arc_disable_irq
comma
id|arc_examine_irq
comma
id|arc_inc_use_count
comma
id|arc_dec_use_count
)brace
suffix:semicolon
eof
