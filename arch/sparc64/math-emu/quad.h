multiline_comment|/*&n; * Definitions for IEEE Quad Precision&n; */
macro_line|#if _FP_W_TYPE_SIZE &lt; 64
macro_line|#error &quot;Only stud muffins allowed, schmuck.&quot;
macro_line|#endif
DECL|macro|_FP_FRACTBITS_Q
mdefine_line|#define _FP_FRACTBITS_Q&t;&t;(2*_FP_W_TYPE_SIZE)
DECL|macro|_FP_FRACBITS_Q
mdefine_line|#define _FP_FRACBITS_Q&t;&t;113
DECL|macro|_FP_FRACXBITS_Q
mdefine_line|#define _FP_FRACXBITS_Q&t;&t;(_FP_FRACTBITS_Q - _FP_FRACBITS_Q)
DECL|macro|_FP_WFRACBITS_Q
mdefine_line|#define _FP_WFRACBITS_Q&t;&t;(_FP_WORKBITS + _FP_FRACBITS_Q)
DECL|macro|_FP_WFRACXBITS_Q
mdefine_line|#define _FP_WFRACXBITS_Q&t;(_FP_FRACTBITS_Q - _FP_WFRACBITS_Q)
DECL|macro|_FP_EXPBITS_Q
mdefine_line|#define _FP_EXPBITS_Q&t;&t;15
DECL|macro|_FP_EXPBIAS_Q
mdefine_line|#define _FP_EXPBIAS_Q&t;&t;16383
DECL|macro|_FP_EXPMAX_Q
mdefine_line|#define _FP_EXPMAX_Q&t;&t;32767
DECL|macro|_FP_QNANBIT_Q
mdefine_line|#define _FP_QNANBIT_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_Q-2) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_IMPLBIT_Q
mdefine_line|#define _FP_IMPLBIT_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_FRACBITS_Q-1) % _FP_W_TYPE_SIZE)
DECL|macro|_FP_OVERFLOW_Q
mdefine_line|#define _FP_OVERFLOW_Q&t;&t;&bslash;&n;&t;((_FP_W_TYPE)1 &lt;&lt; (_FP_WFRACBITS_Q % _FP_W_TYPE_SIZE))
DECL|union|_FP_UNION_Q
r_union
id|_FP_UNION_Q
(brace
DECL|member|flt
r_int
r_float
id|flt
multiline_comment|/* __attribute__((mode(TF))) */
suffix:semicolon
r_struct
(brace
macro_line|#if __BYTE_ORDER == __BIG_ENDIAN
DECL|member|sign
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
DECL|member|exp
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_Q
suffix:semicolon
DECL|member|frac1
r_int
r_int
id|frac1
suffix:colon
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
id|_FP_W_TYPE_SIZE
suffix:semicolon
DECL|member|frac0
r_int
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
macro_line|#else
r_int
r_int
id|frac0
suffix:colon
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
r_int
id|frac1
suffix:colon
id|_FP_FRACBITS_Q
op_minus
(paren
id|_FP_IMPLBIT_Q
op_ne
l_int|0
)paren
op_minus
id|_FP_W_TYPE_SIZE
suffix:semicolon
r_int
id|exp
suffix:colon
id|_FP_EXPBITS_Q
suffix:semicolon
r_int
id|sign
suffix:colon
l_int|1
suffix:semicolon
macro_line|#endif
DECL|member|bits
)brace
id|bits
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|FP_DECL_Q
mdefine_line|#define FP_DECL_Q(X)&t;&t;_FP_DECL(2,X)
DECL|macro|FP_UNPACK_RAW_Q
mdefine_line|#define FP_UNPACK_RAW_Q(X,val)&t;_FP_UNPACK_RAW_2(Q,X,val)
DECL|macro|FP_PACK_RAW_Q
mdefine_line|#define FP_PACK_RAW_Q(val,X)&t;_FP_PACK_RAW_2(Q,val,X)
DECL|macro|FP_UNPACK_Q
mdefine_line|#define FP_UNPACK_Q(X,val)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_UNPACK_RAW_2(Q,X,val);&t;&t;&bslash;&n;    _FP_UNPACK_CANONICAL(Q,2,X);&t;&bslash;&n;  } while (0)
DECL|macro|FP_PACK_Q
mdefine_line|#define FP_PACK_Q(val,X)&t;&t;&bslash;&n;  do {&t;&t;&t;&t;&t;&bslash;&n;    _FP_PACK_CANONICAL(Q,2,X);&t;&t;&bslash;&n;    _FP_PACK_RAW_2(Q,val,X);&t;&t;&bslash;&n;  } while (0)
DECL|macro|FP_NEG_Q
mdefine_line|#define FP_NEG_Q(R,X)&t;&t;_FP_NEG(Q,2,R,X)
DECL|macro|FP_ADD_Q
mdefine_line|#define FP_ADD_Q(R,X,Y)&t;&t;_FP_ADD(Q,2,R,X,Y)
DECL|macro|FP_SUB_Q
mdefine_line|#define FP_SUB_Q(R,X,Y)&t;&t;_FP_SUB(Q,2,R,X,Y)
DECL|macro|FP_MUL_Q
mdefine_line|#define FP_MUL_Q(R,X,Y)&t;&t;_FP_MUL(Q,2,R,X,Y)
DECL|macro|FP_DIV_Q
mdefine_line|#define FP_DIV_Q(R,X,Y)&t;&t;_FP_DIV(Q,2,R,X,Y)
DECL|macro|FP_SQRT_Q
mdefine_line|#define FP_SQRT_Q(R,X)&t;&t;_FP_SQRT(Q,2,R,X)
DECL|macro|FP_CMP_Q
mdefine_line|#define FP_CMP_Q(r,X,Y,un)&t;_FP_CMP(Q,2,r,X,Y,un)
DECL|macro|FP_CMP_EQ_Q
mdefine_line|#define FP_CMP_EQ_Q(r,X,Y)&t;_FP_CMP_EQ(Q,2,r,X,Y)
DECL|macro|FP_TO_INT_Q
mdefine_line|#define FP_TO_INT_Q(r,X,rsz,rsg)  _FP_TO_INT(Q,2,r,X,rsz,rsg)
DECL|macro|FP_FROM_INT_Q
mdefine_line|#define FP_FROM_INT_Q(X,r,rs,rt)  _FP_FROM_INT(Q,2,X,r,rs,rt)
eof
