multiline_comment|/* $Id: irq.h,v 1.6 1997/08/07 08:06:40 davem Exp $&n; * irq.h: IRQ registers on the 64-bit Sparc.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_IRQ_H
DECL|macro|_SPARC64_IRQ_H
mdefine_line|#define _SPARC64_IRQ_H
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/* Sparc64 extensions to the interrupt registry flags.  Mostly this is&n; * for passing along what bus type the device is on and also the true&n; * format of the dev_id cookie, see below.&n; */
DECL|macro|SA_BUSMASK
mdefine_line|#define SA_BUSMASK&t;0x0f000
DECL|macro|SA_SBUS
mdefine_line|#define SA_SBUS&t;&t;0x01000
DECL|macro|SA_PCI
mdefine_line|#define SA_PCI&t;&t;0x02000
DECL|macro|SA_FHC
mdefine_line|#define SA_FHC&t;&t;0x03000
DECL|macro|SA_EBUS
mdefine_line|#define SA_EBUS&t;&t;0x04000
DECL|macro|SA_BUS
mdefine_line|#define SA_BUS(mask)&t;((mask) &amp; SA_BUSMASK)
DECL|struct|devid_cookie
r_struct
id|devid_cookie
(brace
multiline_comment|/* Caller specifies these. */
DECL|member|real_dev_id
r_void
op_star
id|real_dev_id
suffix:semicolon
multiline_comment|/* What dev_id would usually contain. */
DECL|member|imap
r_int
r_int
op_star
id|imap
suffix:semicolon
multiline_comment|/* Anonymous IMAP register */
DECL|member|iclr
r_int
r_int
op_star
id|iclr
suffix:semicolon
multiline_comment|/* Anonymous ICLR register */
DECL|member|pil
r_int
id|pil
suffix:semicolon
multiline_comment|/* Anonymous PIL */
DECL|member|bus_cookie
r_void
op_star
id|bus_cookie
suffix:semicolon
multiline_comment|/* SYSIO regs, PSYCHO regs, etc. */
multiline_comment|/* Return values. */
DECL|member|ret_ino
r_int
r_int
id|ret_ino
suffix:semicolon
DECL|member|ret_pil
r_int
r_int
id|ret_pil
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|SA_DCOOKIE
mdefine_line|#define SA_DCOOKIE&t;0x10000
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS    15
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|init_timers
c_func
(paren
r_void
(paren
op_star
id|lvl10_irq
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
)paren
suffix:semicolon
macro_line|#ifdef __SMP__
r_extern
r_void
id|set_cpu_int
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|clear_cpu_int
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|set_irq_udt
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
id|request_fast_irq
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
id|__const__
r_char
op_star
id|devname
)paren
suffix:semicolon
DECL|function|set_softint
r_extern
id|__inline__
r_void
id|set_softint
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr&t;%0, 0x0, %%set_softint&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|bits
)paren
)paren
suffix:semicolon
)brace
DECL|function|clear_softint
r_extern
id|__inline__
r_void
id|clear_softint
c_func
(paren
r_int
r_int
id|bits
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wr&t;%0, 0x0, %%clear_softint&quot;
suffix:colon
multiline_comment|/* No outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|bits
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_softint
r_extern
id|__inline__
r_int
r_int
id|get_softint
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd&t;%%softint, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|retval
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
macro_line|#endif
eof
