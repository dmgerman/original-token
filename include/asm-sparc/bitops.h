macro_line|#ifndef _SPARC_BITOPS_H
DECL|macro|_SPARC_BITOPS_H
mdefine_line|#define _SPARC_BITOPS_H
multiline_comment|/*&n; * Copyright 1994, David S. Miller (davem@caip.rutgers.edu).&n; */
multiline_comment|/* Set bit &squot;nr&squot; in 32-bit quantity at address &squot;addr&squot; where bit &squot;0&squot;&n; * is in the highest of the four bytes and bit &squot;31&squot; is the high bit&n; * within the first byte. Sparc is BIG-Endian. Unless noted otherwise&n; * all bit-ops return 0 is bit previously clear and != 0 otherwise.&n; */
DECL|function|set_bit
r_extern
id|__inline__
r_int
r_int
id|set_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %g0, %g0, %o2&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, %g0, %o3&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, %o0, %o4&bslash;n&bslash;t&quot;
l_string|&quot;srl %o4, 0x5, %o4&bslash;n&bslash;t&quot;
l_string|&quot;add %o1, %o4, %o1&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, 0x1, %o5&quot;
l_string|&quot;or %g0, 0x1f, %o6&quot;
l_string|&quot;and %o6, %o5, %o6&quot;
l_string|&quot;sll %o5, %o6, %o2&quot;
l_string|&quot;ld [%o1], %o5&bslash;n&bslash;t&quot;
l_string|&quot;and %o5, %o2, %o0&quot;
l_string|&quot;or %o5, %o2, %o5&quot;
l_string|&quot;st %o5, [%o1]&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
multiline_comment|/* confuse gcc :-) */
)brace
DECL|function|clear_bit
r_extern
id|__inline__
r_int
r_int
id|clear_bit
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %g0, %g0, %o2&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, %g0, %o3&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, %o0, %o4&bslash;n&bslash;t&quot;
l_string|&quot;srl %o4, 0x5, %o4&bslash;n&bslash;t&quot;
l_string|&quot;add %o1, %o4, %o1&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, 0x1, %o5&quot;
l_string|&quot;or %g0, 0x1f, %o6&quot;
l_string|&quot;and %o6, %o5, %o6&quot;
l_string|&quot;sll %o5, %o6, %o2&quot;
l_string|&quot;ld [%o1], %o5&bslash;n&bslash;t&quot;
l_string|&quot;and %o5, %o2, %o0&bslash;n&bslash;t&quot;
l_string|&quot;xnor %g0, %o2, %o2&bslash;n&bslash;t&quot;
l_string|&quot;and %o5, %o2, %o5&bslash;n&bslash;t&quot;
l_string|&quot;st %o5, [%o1]&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
multiline_comment|/* confuse gcc ;-) */
)brace
DECL|function|test_bit
r_extern
id|__inline__
r_int
r_int
id|test_bit
c_func
(paren
r_int
id|nr
comma
r_int
op_star
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;or %g0, %o0, %o3&bslash;n&bslash;t&quot;
l_string|&quot;srl %o3, 0x5, %o3&bslash;n&bslash;t&quot;
l_string|&quot;add %o1, %o3, %o1&bslash;n&bslash;t&quot;
l_string|&quot;and %o0, 0x1f, %o0&bslash;n&bslash;t&quot;
l_string|&quot;or %g0, 0x1, %o2&bslash;n&bslash;t&quot;
l_string|&quot;sll %o2, %o0, %o0&quot;
l_string|&quot;ld [%o1], %o2&bslash;n&bslash;t&quot;
l_string|&quot;and %o0, %o2, %o0&bslash;n&bslash;t&quot;
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
multiline_comment|/* confuse gcc :&gt; */
)brace
macro_line|#endif /* defined(_SPARC_BITOPS_H) */
eof
