macro_line|#ifndef __ALPHA_UNALIGNED_H
DECL|macro|__ALPHA_UNALIGNED_H
mdefine_line|#define __ALPHA_UNALIGNED_H
multiline_comment|/* &n; * The main single-value unaligned transfer routines.&n; */
DECL|macro|get_unaligned
mdefine_line|#define get_unaligned(ptr) &bslash;&n;&t;((__typeof__(*(ptr)))__get_unaligned((ptr), sizeof(*(ptr))))
DECL|macro|put_unaligned
mdefine_line|#define put_unaligned(x,ptr) &bslash;&n;&t;__put_unaligned((unsigned long)(x), (ptr), sizeof(*(ptr)))
multiline_comment|/*&n; * This is a silly but good way to make sure that&n; * the get/put functions are indeed always optimized,&n; * and that we use the correct sizes.&n; */
r_extern
r_void
id|bad_unaligned_access_length
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * EGCS 1.1 knows about arbitrary unaligned loads.  Define some&n; * packed structures to talk about such things with.&n; */
DECL|struct|__una_u64
DECL|member|x
r_struct
id|__una_u64
(brace
id|__u64
id|x
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|__una_u32
DECL|member|x
r_struct
id|__una_u32
(brace
id|__u32
id|x
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|__una_u16
DECL|member|x
r_struct
id|__una_u16
(brace
id|__u16
id|x
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Elemental unaligned loads &n; */
DECL|function|__uldq
r_extern
r_inline
r_int
r_int
id|__uldq
c_func
(paren
r_const
r_int
r_int
op_star
id|r11
)paren
(brace
r_const
r_struct
id|__una_u64
op_star
id|ptr
op_assign
(paren
r_const
r_struct
id|__una_u64
op_star
)paren
id|r11
suffix:semicolon
r_return
id|ptr-&gt;x
suffix:semicolon
)brace
DECL|function|__uldl
r_extern
r_inline
r_int
r_int
id|__uldl
c_func
(paren
r_const
r_int
r_int
op_star
id|r11
)paren
(brace
r_const
r_struct
id|__una_u32
op_star
id|ptr
op_assign
(paren
r_const
r_struct
id|__una_u32
op_star
)paren
id|r11
suffix:semicolon
r_return
id|ptr-&gt;x
suffix:semicolon
)brace
DECL|function|__uldw
r_extern
r_inline
r_int
r_int
id|__uldw
c_func
(paren
r_const
r_int
r_int
op_star
id|r11
)paren
(brace
r_const
r_struct
id|__una_u16
op_star
id|ptr
op_assign
(paren
r_const
r_struct
id|__una_u16
op_star
)paren
id|r11
suffix:semicolon
r_return
id|ptr-&gt;x
suffix:semicolon
)brace
multiline_comment|/*&n; * Elemental unaligned stores &n; */
DECL|function|__ustq
r_extern
r_inline
r_void
id|__ustq
c_func
(paren
r_int
r_int
id|r5
comma
r_int
r_int
op_star
id|r11
)paren
(brace
r_struct
id|__una_u64
op_star
id|ptr
op_assign
(paren
r_struct
id|__una_u64
op_star
)paren
id|r11
suffix:semicolon
id|ptr-&gt;x
op_assign
id|r5
suffix:semicolon
)brace
DECL|function|__ustl
r_extern
r_inline
r_void
id|__ustl
c_func
(paren
r_int
r_int
id|r5
comma
r_int
r_int
op_star
id|r11
)paren
(brace
r_struct
id|__una_u32
op_star
id|ptr
op_assign
(paren
r_struct
id|__una_u32
op_star
)paren
id|r11
suffix:semicolon
id|ptr-&gt;x
op_assign
id|r5
suffix:semicolon
)brace
DECL|function|__ustw
r_extern
r_inline
r_void
id|__ustw
c_func
(paren
r_int
r_int
id|r5
comma
r_int
r_int
op_star
id|r11
)paren
(brace
r_struct
id|__una_u16
op_star
id|ptr
op_assign
(paren
r_struct
id|__una_u16
op_star
)paren
id|r11
suffix:semicolon
id|ptr-&gt;x
op_assign
id|r5
suffix:semicolon
)brace
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
id|__uldw
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|val
op_assign
id|__uldl
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|val
op_assign
id|__uldq
c_func
(paren
(paren
r_const
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_unaligned_access_length
c_func
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
(paren
id|val
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|__ustw
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__ustl
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
suffix:colon
id|__ustq
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|bad_unaligned_access_length
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
