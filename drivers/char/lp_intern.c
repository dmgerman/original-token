multiline_comment|/*&n; * split into mid and low-level for better support of different hardware&n; * by Joerg Dorchain (dorchain@mpi-sb.mpg.de)&n; *&n; * Amiga printer device by Michael Rausch (linux@uni-koblenz.de);&n; * Atari support added by Andreas Schwab (schwab@ls5.informatik.uni-dortmund.de);&n; * based upon work from&n; *&n; * Copyright (C) 1992 by Jim Weigand and Linus Torvalds&n; * Copyright (C) 1992,1993 by Michael K. Johnson&n; * - Thanks much to Gunter Windau for pointing out to me where the error&n; *   checking ought to be.&n; * Copyright (C) 1993 by Nigel Gamble (added interrupt code)&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifdef CONFIG_AMIGA
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigaints.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/atarihw.h&gt;
macro_line|#include &lt;asm/atariints.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
macro_line|#include &lt;asm/mvme16xhw.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
macro_line|#include&lt;asm/bvme6000hw.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/lp_intern.h&gt;
DECL|variable|minor
r_static
r_int
id|minor
op_assign
op_minus
l_int|1
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|minor
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
r_static
r_void
id|lp_int_out
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_static
r_int
id|lp_int_busy
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
id|lp_int_pout
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_int
id|lp_int_online
c_func
(paren
r_int
)paren
suffix:semicolon
r_static
r_void
DECL|function|lp_int_out
id|lp_int_out
(paren
r_int
id|c
comma
r_int
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|m68k_machtype
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_ne
id|lp_table
(braket
id|dev
)braket
op_member_access_from_pointer
id|wait
)paren
id|wait
op_increment
suffix:semicolon
id|ciaa.prb
op_assign
id|c
suffix:semicolon
)brace
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|15
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|c
suffix:semicolon
id|sound_ym.rd_data_reg_sel
op_assign
l_int|14
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_ne
id|lp_table
(braket
id|dev
)braket
op_member_access_from_pointer
id|wait
)paren
id|wait
op_increment
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_amp
op_complement
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
r_while
c_loop
(paren
id|wait
)paren
id|wait
op_decrement
suffix:semicolon
id|sound_ym.wd_data
op_assign
id|sound_ym.rd_data_reg_sel
op_or
(paren
l_int|1
op_lshift
l_int|5
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_case
id|MACH_MVME16x
suffix:colon
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_ne
id|lp_table
(braket
id|dev
)braket
op_member_access_from_pointer
id|wait
)paren
id|wait
op_increment
suffix:semicolon
id|mvmelp.data
op_assign
id|c
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_case
id|MACH_BVME6000
suffix:colon
(brace
r_int
id|wait
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|wait
op_ne
id|lp_table
(braket
id|dev
)braket
op_member_access_from_pointer
id|wait
)paren
id|wait
op_increment
suffix:semicolon
id|bvmepit.padr
op_assign
id|c
suffix:semicolon
id|bvmepit.pacr
op_or_assign
l_int|0x02
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
)brace
)brace
r_static
r_int
DECL|function|lp_int_busy
id|lp_int_busy
(paren
r_int
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|m68k_machtype
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
r_return
id|ciab.pra
op_amp
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
r_return
id|mfp.par_dt_reg
op_amp
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_case
id|MACH_MVME16x
suffix:colon
r_return
id|mvmelp.isr
op_amp
l_int|1
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_case
id|MACH_BVME6000
suffix:colon
r_return
l_int|0
multiline_comment|/* !(bvmepit.psr &amp; 0x40) */
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|lp_int_pout
id|lp_int_pout
(paren
r_int
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|m68k_machtype
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
r_return
id|ciab.pra
op_amp
l_int|2
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_case
id|MACH_MVME16x
suffix:colon
r_return
id|mvmelp.isr
op_amp
l_int|2
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_case
id|MACH_BVME6000
suffix:colon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
r_static
r_int
DECL|function|lp_int_online
id|lp_int_online
(paren
r_int
id|dev
)paren
(brace
r_switch
c_cond
(paren
id|m68k_machtype
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
r_return
id|ciab.pra
op_amp
l_int|4
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
r_return
op_logical_neg
(paren
id|mfp.par_dt_reg
op_amp
l_int|1
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_case
id|MACH_MVME16x
suffix:colon
r_return
id|mvmelp.isr
op_amp
l_int|4
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_case
id|MACH_BVME6000
suffix:colon
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
)brace
DECL|function|lp_int_interrupt
r_static
r_void
id|lp_int_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|data
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
macro_line|#ifdef CONFIG_MVME16x
r_if
c_cond
(paren
id|MACH_IS_MVME16x
)paren
id|mvmelp.ack_icr
op_or_assign
l_int|0x08
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_if
c_cond
(paren
id|MACH_IS_BVME6000
)paren
id|bvmepit.pacr
op_and_assign
op_complement
l_int|0x02
suffix:semicolon
macro_line|#endif
id|lp_interrupt
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
DECL|function|lp_int_open
r_static
r_int
id|lp_int_open
c_func
(paren
r_int
id|dev
)paren
(brace
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|lp_int_release
r_static
r_void
id|lp_int_release
c_func
(paren
r_int
id|dev
)paren
(brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
)brace
DECL|variable|tab
r_static
r_struct
id|lp_struct
id|tab
op_assign
(brace
l_string|&quot;Builtin parallel port&quot;
comma
multiline_comment|/* name */
l_int|0
comma
multiline_comment|/* irq */
id|lp_int_out
comma
id|lp_int_busy
comma
id|lp_int_pout
comma
id|lp_int_online
comma
l_int|0
comma
l_int|NULL
comma
multiline_comment|/* ioctl */
id|lp_int_open
comma
id|lp_int_release
comma
id|LP_EXIST
comma
id|LP_INIT_CHAR
comma
id|LP_INIT_TIME
comma
id|LP_INIT_WAIT
comma
l_int|NULL
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|lp_internal_init
r_int
id|__init
id|lp_internal_init
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
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
id|lp_irq
)paren
id|tab.irq
op_assign
id|request_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|lp_int_interrupt
comma
l_int|0
comma
l_string|&quot;builtin printer port&quot;
comma
id|lp_int_interrupt
)paren
suffix:semicolon
id|tab.base
op_assign
(paren
r_void
op_star
)paren
op_amp
id|ciaa.prb
suffix:semicolon
multiline_comment|/* dummy, not used */
id|tab.type
op_assign
id|LP_AMIGA
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
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
id|sound_ym.rd_data_reg_sel
op_assign
l_int|7
suffix:semicolon
id|sound_ym.wd_data
op_assign
(paren
id|sound_ym.rd_data_reg_sel
op_amp
l_int|0x3f
)paren
op_or
l_int|0xc0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_irq
)paren
id|tab.irq
op_assign
id|request_irq
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|lp_int_interrupt
comma
id|IRQ_TYPE_SLOW
comma
l_string|&quot;builtin printer port&quot;
comma
id|lp_int_interrupt
)paren
suffix:semicolon
id|tab.base
op_assign
(paren
r_void
op_star
)paren
op_amp
id|sound_ym.wd_data
suffix:semicolon
multiline_comment|/* dummy, not used */
id|tab.type
op_assign
id|LP_ATARI
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
r_if
c_cond
(paren
id|MACH_IS_MAC
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_if
c_cond
(paren
id|MACH_IS_MVME16x
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mvme16x_config
op_amp
id|MVME16x_CONFIG_GOT_LP
)paren
)paren
r_return
op_minus
id|ENODEV
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
id|mvmelp.ack_icr
op_assign
l_int|0x08
suffix:semicolon
id|mvmelp.flt_icr
op_assign
l_int|0x08
suffix:semicolon
id|mvmelp.sel_icr
op_assign
l_int|0x08
suffix:semicolon
id|mvmelp.pe_icr
op_assign
l_int|0x08
suffix:semicolon
id|mvmelp.bsy_icr
op_assign
l_int|0x08
suffix:semicolon
id|mvmelp.cr
op_assign
l_int|0x10
suffix:semicolon
id|mvmelp.ack_icr
op_assign
l_int|0xd9
suffix:semicolon
multiline_comment|/* Int on trailing edge of ACK */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_irq
)paren
id|tab.irq
op_assign
id|request_irq
c_func
(paren
id|MVME167_IRQ_PRN
comma
id|lp_int_interrupt
comma
l_int|0
comma
l_string|&quot;builtin printer port&quot;
comma
id|lp_int_interrupt
)paren
suffix:semicolon
id|tab.base
op_assign
(paren
r_void
op_star
)paren
op_amp
id|mvmelp
suffix:semicolon
multiline_comment|/* dummy, not used */
id|tab.type
op_assign
id|LP_MVME167
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_if
c_cond
(paren
id|MACH_IS_BVME6000
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
id|bvmepit.pgcr
op_assign
l_int|0x0f
suffix:semicolon
id|bvmepit.psrr
op_assign
l_int|0x18
suffix:semicolon
id|bvmepit.paddr
op_assign
l_int|0xff
suffix:semicolon
id|bvmepit.pcdr
op_assign
(paren
id|bvmepit.pcdr
op_amp
l_int|0xfc
)paren
op_or
l_int|0x02
suffix:semicolon
id|bvmepit.pcddr
op_or_assign
l_int|0x03
suffix:semicolon
id|bvmepit.pacr
op_assign
l_int|0x78
suffix:semicolon
id|bvmepit.pbcr
op_assign
l_int|0x00
suffix:semicolon
id|bvmepit.pivr
op_assign
id|BVME_IRQ_PRN
suffix:semicolon
id|bvmepit.pgcr
op_assign
l_int|0x1f
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_irq
)paren
id|tab.irq
op_assign
id|request_irq
c_func
(paren
id|BVME_IRQ_PRN
comma
id|lp_int_interrupt
comma
l_int|0
comma
l_string|&quot;builtin printer port&quot;
comma
id|lp_int_interrupt
)paren
suffix:semicolon
id|tab.base
op_assign
(paren
r_void
op_star
)paren
op_amp
id|bvmepit
suffix:semicolon
multiline_comment|/* dummy, not used */
id|tab.type
op_assign
id|LP_BVME6000
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|minor
op_assign
id|register_parallel
c_func
(paren
op_amp
id|tab
comma
id|minor
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;builtin lp init: cant get a minor&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp_irq
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
id|MACH_IS_AMIGA
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|free_irq
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_if
c_cond
(paren
id|MACH_IS_MVME16x
)paren
id|free_irq
c_func
(paren
id|MVME167_IRQ_PRN
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_if
c_cond
(paren
id|MACH_IS_BVME6000
)paren
id|free_irq
c_func
(paren
id|BVME_IRQ_PRN
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_return
id|lp_internal_init
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
id|lp_irq
)paren
(brace
macro_line|#ifdef CONFIG_AMIGA
r_if
c_cond
(paren
id|MACH_IS_AMIGA
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_CIAA_FLG
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ATARI
r_if
c_cond
(paren
id|MACH_IS_ATARI
)paren
id|free_irq
c_func
(paren
id|IRQ_MFP_BUSY
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MVME16x
r_if
c_cond
(paren
id|MACH_IS_MVME16x
)paren
id|free_irq
c_func
(paren
id|MVME167_IRQ_PRN
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BVME6000
r_if
c_cond
(paren
id|MACH_IS_BVME6000
)paren
id|free_irq
c_func
(paren
id|BVME_IRQ_PRN
comma
id|lp_int_interrupt
)paren
suffix:semicolon
macro_line|#endif
)brace
id|unregister_parallel
c_func
(paren
id|minor
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
