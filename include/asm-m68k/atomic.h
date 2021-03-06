macro_line|#ifndef __ARCH_M68K_ATOMIC__
DECL|macro|__ARCH_M68K_ATOMIC__
mdefine_line|#define __ARCH_M68K_ATOMIC__
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
multiline_comment|/*&n; * We do not have SMP m68k systems, so we don&squot;t have to deal with that.&n; */
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_int
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = i)
DECL|function|atomic_add
r_static
id|__inline__
r_void
id|atomic_add
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;addl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;id&quot;
(paren
id|i
)paren
comma
l_string|&quot;0&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
)brace
DECL|function|atomic_sub
r_static
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;subl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;id&quot;
(paren
id|i
)paren
comma
l_string|&quot;0&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc
r_static
id|__inline__
r_void
id|atomic_inc
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;addql #1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec
r_static
id|__inline__
r_void
id|atomic_dec
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;subql #1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_and_test
r_static
id|__inline__
r_int
id|atomic_dec_and_test
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;subql #1,%1; seq %0&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|c
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;1&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
r_return
id|c
op_ne
l_int|0
suffix:semicolon
)brace
DECL|macro|atomic_clear_mask
mdefine_line|#define atomic_clear_mask(mask, v) &bslash;&n;&t;__asm__ __volatile__(&quot;andl %1,%0&quot; : &quot;=m&quot; (*v) : &quot;id&quot; (~(mask)),&quot;0&quot;(*v))
DECL|macro|atomic_set_mask
mdefine_line|#define atomic_set_mask(mask, v) &bslash;&n;&t;__asm__ __volatile__(&quot;orl %1,%0&quot; : &quot;=m&quot; (*v) : &quot;id&quot; (mask),&quot;0&quot;(*v))
macro_line|#endif /* __ARCH_M68K_ATOMIC __ */
eof
