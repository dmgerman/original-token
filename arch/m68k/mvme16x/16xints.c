multiline_comment|/*&n; * arch/m68k/mvme16x/16xints.c&n; *&n; * Copyright (C) 1995 Richard Hirst [richard@sleepie.demon.co.uk]&n; *&n; * based on amiints.c -- Amiga Linux interrupt handling code&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file README.legal in the main directory of this archive&n; * for more details.&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
r_static
r_void
id|mvme16x_defhand
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
id|fp
)paren
suffix:semicolon
multiline_comment|/*&n; * This should ideally be 4 elements only, for speed.&n; */
r_static
r_struct
(brace
DECL|member|handler
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|dev_id
r_void
op_star
id|dev_id
suffix:semicolon
DECL|member|devname
r_const
r_char
op_star
id|devname
suffix:semicolon
DECL|member|count
r_int
id|count
suffix:semicolon
DECL|variable|irq_tab
)brace
id|irq_tab
(braket
l_int|192
)braket
suffix:semicolon
multiline_comment|/*&n; * void mvme16x_init_IRQ (void)&n; *&n; * Parameters:&t;None&n; *&n; * Returns:&t;Nothing&n; *&n; * This function is called during kernel startup to initialize&n; * the mvme16x IRQ handling routines.  Should probably ensure&n; * that the base vectors for the VMEChip2 and PCCChip2 are valid.&n; */
DECL|function|mvme16x_init_IRQ
r_void
id|mvme16x_init_IRQ
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|192
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_tab
(braket
id|i
)braket
dot
id|handler
op_assign
id|mvme16x_defhand
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
id|irq_tab
(braket
id|i
)braket
dot
id|count
op_assign
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|mvme16x_request_irq
r_int
id|mvme16x_request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|irq
template_param
l_int|255
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|flags
op_amp
id|IRQ_FLG_STD
)paren
)paren
(brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|flags
op_amp
id|IRQ_FLG_LOCK
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: IRQ %d from %s is not replaceable&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|flags
op_amp
id|IRQ_FLG_REPLACE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: %s can&squot;t replace IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|devname
comma
id|irq
comma
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|devname
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
)brace
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|flags
op_assign
id|flags
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|dev_id
op_assign
id|dev_id
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|devname
op_assign
id|devname
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|mvme16x_free_irq
r_void
id|mvme16x_free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_if
c_cond
(paren
id|irq
template_param
l_int|255
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Incorrect IRQ %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|dev_id
op_ne
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Removing probably wrong IRQ %d from %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|irq
comma
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|devname
)paren
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|handler
op_assign
id|mvme16x_defhand
suffix:semicolon
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|flags
op_assign
id|IRQ_FLG_STD
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|dev_id
op_assign
l_int|NULL
suffix:semicolon
id|irq_tab
(braket
id|irq
op_minus
l_int|64
)braket
dot
id|devname
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|mvme16x_process_int
r_void
id|mvme16x_process_int
(paren
r_int
r_int
id|vec
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_if
c_cond
(paren
id|vec
template_param
l_int|255
)paren
id|printk
(paren
l_string|&quot;mvme16x_process_int: Illegal vector %ld&quot;
comma
id|vec
)paren
suffix:semicolon
r_else
(brace
id|irq_tab
(braket
id|vec
op_minus
l_int|64
)braket
dot
id|count
op_increment
suffix:semicolon
id|irq_tab
(braket
id|vec
op_minus
l_int|64
)braket
dot
id|handler
c_func
(paren
id|vec
comma
id|irq_tab
(braket
id|vec
op_minus
l_int|64
)braket
dot
id|dev_id
comma
id|fp
)paren
suffix:semicolon
)brace
)brace
DECL|function|mvme16x_get_irq_list
r_int
id|mvme16x_get_irq_list
(paren
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
comma
id|len
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|192
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_tab
(braket
id|i
)braket
dot
id|count
)paren
id|len
op_add_assign
id|sprintf
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Vec 0x%02x: %8d  %s&bslash;n&quot;
comma
id|i
op_plus
l_int|64
comma
id|irq_tab
(braket
id|i
)braket
dot
id|count
comma
id|irq_tab
(braket
id|i
)braket
dot
id|devname
ques
c_cond
id|irq_tab
(braket
id|i
)braket
dot
id|devname
suffix:colon
l_string|&quot;free&quot;
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
)brace
DECL|function|mvme16x_defhand
r_static
r_void
id|mvme16x_defhand
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
id|fp
)paren
(brace
id|printk
(paren
l_string|&quot;Unknown interrupt 0x%02x&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|mvme16x_enable_irq
r_void
id|mvme16x_enable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|mvme16x_disable_irq
r_void
id|mvme16x_disable_irq
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
eof
