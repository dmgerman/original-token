multiline_comment|/* $Id: fstox.c,v 1.3 1999/05/28 13:45:01 jj Exp $&n; * arch/sparc64/math-emu/fstox.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; *&n; */
DECL|macro|FP_ROUNDMODE
mdefine_line|#define FP_ROUNDMODE FP_RND_ZERO
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;single.h&quot;
DECL|function|FSTOX
r_int
id|FSTOX
c_func
(paren
r_int
op_star
id|rd
comma
r_void
op_star
id|rs2
)paren
(brace
id|FP_DECL_EX
suffix:semicolon
id|FP_DECL_S
c_func
(paren
id|A
)paren
suffix:semicolon
r_int
id|r
suffix:semicolon
id|FP_UNPACK_SP
c_func
(paren
id|A
comma
id|rs2
)paren
suffix:semicolon
id|FP_TO_INT_S
c_func
(paren
id|r
comma
id|A
comma
l_int|64
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|FP_INHIBIT_RESULTS
)paren
op_star
id|rd
op_assign
id|r
suffix:semicolon
id|FP_HANDLE_EXCEPTIONS
suffix:semicolon
)brace
eof
