macro_line|#ifndef __ARM_UNALIGNED_H
DECL|macro|__ARM_UNALIGNED_H
mdefine_line|#define __ARM_UNALIGNED_H
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;&t;((__typeof__(*(ptr)))__get_unaligned((ptr), sizeof(*(ptr))))
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(val, ptr) &bslash;&n;&t;__put_unaligned((unsigned long)(val), (ptr), sizeof(*(ptr)))
r_extern
r_void
id|bad_unaligned_access_length
(paren
r_void
)paren
suffix:semicolon
DECL|function|__get_unaligned
r_extern
r_inline
r_int
r_int
id|__get_unaligned
c_func
(paren
r_const
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|val
op_assign
op_star
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|val
op_assign
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_or
(paren
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|val
op_assign
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_or
(paren
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|1
)braket
op_lshift
l_int|8
)paren
op_or
(paren
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|2
)braket
)paren
op_lshift
l_int|16
op_or
(paren
(paren
(paren
r_const
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|3
)braket
op_lshift
l_int|24
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_unaligned_access_length
(paren
)paren
suffix:semicolon
)brace
r_return
id|val
suffix:semicolon
)brace
DECL|function|__put_unaligned
r_extern
r_inline
r_void
id|__put_unaligned
c_func
(paren
r_int
r_int
id|val
comma
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
(paren
r_int
r_char
op_star
)paren
id|ptr
op_assign
id|val
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_assign
id|val
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|1
)braket
op_assign
id|val
op_rshift
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|0
)braket
op_assign
id|val
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|1
)braket
op_assign
id|val
op_rshift
l_int|8
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|2
)braket
op_assign
id|val
op_rshift
l_int|16
suffix:semicolon
(paren
(paren
r_int
r_char
op_star
)paren
id|ptr
)paren
(braket
l_int|3
)braket
op_assign
id|val
op_rshift
l_int|24
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_unaligned_access_length
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof