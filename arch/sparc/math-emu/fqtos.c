multiline_comment|/* $Id: fqtos.c,v 1.9 1999/05/28 13:42:10 jj Exp $&n; * arch/sparc/math-emu/fqtos.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1998 Peter Maydell (pmaydell@chiark.greenend.org.uk)&n; *&n; */
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;quad.h&quot;
macro_line|#include &quot;single.h&quot;
DECL|function|FQTOS
r_int
id|FQTOS
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
id|FP_DECL_Q
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
id|FP_UNPACK_QP
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
id|Q
comma
l_int|1
comma
l_int|4
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
