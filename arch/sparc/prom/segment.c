multiline_comment|/* $Id: segment.c,v 1.2 1995/11/25 01:00:14 davem Exp $&n; * segment.c:  Prom routine to map segments in other contexts before&n; *             a standalone is completely mapped.  This is for sun4 and&n; *             sun4c architectures only.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* Set physical segment &squot;segment&squot; at virtual address &squot;vaddr&squot; in&n; * context &squot;ctx&squot;.&n; */
r_void
DECL|function|prom_putsegment
id|prom_putsegment
c_func
(paren
r_int
id|ctx
comma
r_int
r_int
id|vaddr
comma
r_int
id|segment
)paren
(brace
(paren
op_star
(paren
id|romvec-&gt;pv_setctxt
)paren
)paren
(paren
id|ctx
comma
(paren
r_char
op_star
)paren
id|vaddr
comma
id|segment
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
