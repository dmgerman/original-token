multiline_comment|/* $Id: fsmuld.c,v 1.9 1999/05/28 13:42:12 jj Exp $&n; * arch/sparc/math-emu/fsmuld.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1998 Peter Maydell (pmaydell@chiark.greenend.org.uk)&n; *&n; */
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;double.h&quot;
macro_line|#include &quot;single.h&quot;
DECL|function|FSMULD
r_int
id|FSMULD
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
id|FP_DECL_S
c_func
(paren
id|IN
)paren
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
id|FP_UNPACK_SP
c_func
(paren
id|IN
comma
id|rs1
)paren
suffix:semicolon
id|FP_CONV
c_func
(paren
id|D
comma
id|S
comma
l_int|2
comma
l_int|1
comma
id|A
comma
id|IN
)paren
suffix:semicolon
id|FP_UNPACK_SP
c_func
(paren
id|IN
comma
id|rs2
)paren
suffix:semicolon
id|FP_CONV
c_func
(paren
id|D
comma
id|S
comma
l_int|2
comma
l_int|1
comma
id|B
comma
id|IN
)paren
suffix:semicolon
id|FP_MUL_D
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
