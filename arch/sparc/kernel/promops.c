multiline_comment|/* promops.c:  Prom node tree operations and Prom Vector initialization&n; *             initialization routines.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;asm/openprom.h&gt;
r_extern
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
multiline_comment|/* This gets called from head.S upon bootup to initialize the&n; * prom vector pointer for the rest of the kernel.&n; */
r_void
DECL|function|init_prom
id|init_prom
c_func
(paren
r_struct
id|linux_romvec
op_star
id|r_ptr
)paren
(brace
id|romvec
op_assign
id|r_ptr
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
