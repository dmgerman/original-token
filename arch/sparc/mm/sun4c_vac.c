multiline_comment|/* $Id: sun4c_vac.c,v 1.5 1995/11/25 00:59:43 davem Exp $&n; * vac.c:   Routines for flushing various amount of the Sparc VAC&n; *          (virtual address cache) on the sun4c.&n; *&n; * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/asi.h&gt;
macro_line|#include &lt;asm/contregs.h&gt;
macro_line|#include &lt;asm/vac-ops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
DECL|variable|sun4c_vacinfo
r_struct
id|sun4c_vac_props
id|sun4c_vacinfo
suffix:semicolon
multiline_comment|/* Invalidate the entire sun4c VAC, it must be off at this point */
r_void
DECL|function|sun4c_flush_all
id|sun4c_flush_all
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|begin
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|sun4c_vacinfo.on
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SUN4C: AIEEE, trying to invalidate vac while&quot;
l_string|&quot; it is on.&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Clear &squot;valid&squot; bit in all cache line tags */
id|begin
op_assign
id|AC_CACHETAGS
suffix:semicolon
id|end
op_assign
(paren
id|AC_CACHETAGS
op_plus
id|sun4c_vacinfo.num_bytes
)paren
suffix:semicolon
r_while
c_loop
(paren
id|begin
OL
id|end
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|begin
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_CONTROL
)paren
)paren
suffix:semicolon
id|begin
op_add_assign
id|sun4c_vacinfo.linesize
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
