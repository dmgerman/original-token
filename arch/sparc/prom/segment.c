multiline_comment|/* $Id: segment.c,v 1.3 1996/09/19 20:27:28 davem Exp $&n; * segment.c:  Prom routine to map segments in other contexts before&n; *             a standalone is completely mapped.  This is for sun4 and&n; *             sun4c architectures only.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;ld [%0], %%g6&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|current_set
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
