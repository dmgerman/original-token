multiline_comment|/* $Id: fdtos.c,v 1.4 1999/05/28 13:43:58 jj Exp $&n; * arch/sparc64/math-emu/fdtos.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; *&n; */
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
macro_line|#include &quot;single.h&quot;
DECL|function|FDTOS
r_int
id|FDTOS
c_func
(paren
r_void
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
id|FP_DECL_D
c_func
(paren
id|A
)paren
suffix:semicolon
id|FP_DECL_S
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
id|rs2
)paren
suffix:semicolon
id|FP_CONV
c_func
(paren
id|S
comma
id|D
comma
l_int|1
comma
l_int|1
comma
id|R
comma
id|A
)paren
suffix:semicolon
id|FP_PACK_SP
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
