multiline_comment|/* $Id: fcmpeq.c,v 1.5 1999/05/28 13:43:29 jj Exp $&n; * arch/sparc64/math-emu/fcmpeq.c&n; *&n; * Copyright (C) 1997, 1999 Jakub Jelinek (jj@ultra.linux.cz)&n; * Copyright (C) 1999 David S. Miller (davem@redhat.com)&n; *&n; */
macro_line|#include &quot;sfp-util.h&quot;
macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;quad.h&quot;
DECL|function|FCMPEQ
r_int
id|FCMPEQ
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
id|FP_DECL_Q
c_func
(paren
id|A
)paren
suffix:semicolon
id|FP_DECL_Q
c_func
(paren
id|B
)paren
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_int
id|fccno
op_assign
(paren
r_int
)paren
id|rd
suffix:semicolon
r_int
r_int
id|fsr
suffix:semicolon
id|FP_UNPACK_RAW_QP
c_func
(paren
id|A
comma
id|rs1
)paren
suffix:semicolon
id|FP_UNPACK_RAW_QP
c_func
(paren
id|B
comma
id|rs2
)paren
suffix:semicolon
id|FP_CMP_Q
c_func
(paren
id|ret
comma
id|B
comma
id|A
comma
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
l_int|3
)paren
id|FP_SET_EXCEPTION
c_func
(paren
id|FP_EX_INVALID
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|FP_INHIBIT_RESULTS
)paren
(brace
id|rd
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
)paren
id|rd
)paren
op_amp
op_complement
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
op_minus
l_int|1
)paren
id|ret
op_assign
l_int|2
suffix:semicolon
id|fsr
op_assign
id|current-&gt;tss.xfsr
(braket
l_int|0
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|fccno
)paren
(brace
r_case
l_int|0
suffix:colon
id|fsr
op_and_assign
op_complement
l_int|0xc00
suffix:semicolon
id|fsr
op_or_assign
(paren
id|ret
op_lshift
l_int|10
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|fsr
op_and_assign
op_complement
l_int|0x300000000UL
suffix:semicolon
id|fsr
op_or_assign
(paren
id|ret
op_lshift
l_int|32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|fsr
op_and_assign
op_complement
l_int|0xc00000000UL
suffix:semicolon
id|fsr
op_or_assign
(paren
id|ret
op_lshift
l_int|34
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|fsr
op_and_assign
op_complement
l_int|0x3000000000UL
suffix:semicolon
id|fsr
op_or_assign
(paren
id|ret
op_lshift
l_int|36
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|current-&gt;tss.xfsr
(braket
l_int|0
)braket
op_assign
id|fsr
suffix:semicolon
)brace
id|FP_HANDLE_EXCEPTIONS
suffix:semicolon
)brace
eof
