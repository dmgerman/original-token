multiline_comment|/* $Id: fdivd.c,v 1.4 1999/05/28 13:43:36 jj Exp $&n; * arch/sparc64/math-emu/fdivd.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; *&n; */
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
DECL|function|FDIVD
r_int
id|FDIVD
c_func
(paren
r_void
op_star
id|rd
comma
r_void
op_star
id|rs2
comma
r_void
op_star
id|rs1
)paren
(brace
id|FP_DECL_EX
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|A
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|B
)paren
suffix:semicolon
id|FP_DECL_D
c_func
(paren
id|R
)paren
suffix:semicolon
id|FP_UNPACK_DP
c_func
(paren
id|A
comma
id|rs1
)paren
suffix:semicolon
id|FP_UNPACK_DP
c_func
(paren
id|B
comma
id|rs2
)paren
suffix:semicolon
id|FP_DIV_D
c_func
(paren
id|R
comma
id|A
comma
id|B
)paren
suffix:semicolon
id|FP_PACK_DP
c_func
(paren
id|rd
comma
id|R
)paren
suffix:semicolon
id|FP_HANDLE_EXCEPTIONS
suffix:semicolon
)brace
eof
