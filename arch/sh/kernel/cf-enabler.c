multiline_comment|/* $Id: cf-enabler.c,v 1.2 1999/12/20 10:14:40 gniibe Exp $&n; *&n; *  linux/drivers/block/cf-enabler.c&n; *&n; *  Copyright (C) 1999  Niibe Yutaka&n; *&n; *  Enable the CF configuration.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
DECL|macro|CF_CIS_BASE
mdefine_line|#define CF_CIS_BASE&t;0xb8000000
multiline_comment|/*&n; * 0xB8000000 : Attribute&n; * 0xB8001000 : Common Memory&n; * 0xBA000000 : I/O&n; */
DECL|function|cf_init
r_int
id|__init
id|cf_init
c_func
(paren
r_void
)paren
(brace
id|outw
c_func
(paren
l_int|0x0042
comma
id|CF_CIS_BASE
op_plus
l_int|0x0200
)paren
suffix:semicolon
id|make_imask_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|disable_irq
c_func
(paren
l_int|14
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|cf_init
id|__initcall
(paren
id|cf_init
)paren
suffix:semicolon
eof
