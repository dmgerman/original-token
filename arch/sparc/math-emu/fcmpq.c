macro_line|#include &quot;soft-fp.h&quot;
macro_line|#include &quot;quad.h&quot;
DECL|function|FCMPQ
r_int
id|FCMPQ
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
r_int
id|fsr
suffix:semicolon
id|__FP_UNPACK_Q
c_func
(paren
id|A
comma
id|rs1
)paren
suffix:semicolon
id|__FP_UNPACK_Q
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
op_minus
l_int|1
)paren
id|ret
op_assign
l_int|2
suffix:semicolon
id|fsr
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|rd
suffix:semicolon
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
op_star
(paren
r_int
r_int
op_star
)paren
id|rd
op_assign
id|fsr
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof