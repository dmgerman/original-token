macro_line|#ifndef __ARCH_I386_ATOMIC__
DECL|macro|__ARCH_I386_ATOMIC__
mdefine_line|#define __ARCH_I386_ATOMIC__
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
multiline_comment|/*&n; * Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
DECL|macro|__atomic_fool_gcc
mdefine_line|#define __atomic_fool_gcc(x) (*(struct { int a[100]; } *)x)
DECL|typedef|atomic_t
r_typedef
r_int
id|atomic_t
suffix:semicolon
DECL|function|atomic_add
r_extern
id|__inline__
r_void
id|atomic_add
c_func
(paren
id|atomic_t
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldl_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;addl %0,%2,%0&bslash;n&bslash;t&quot;
l_string|&quot;stl_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|atomic_sub
r_extern
id|__inline__
r_void
id|atomic_sub
c_func
(paren
id|atomic_t
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldl_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;subl %0,%2,%0&bslash;n&bslash;t&quot;
l_string|&quot;stl_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
l_string|&quot;2:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|i
)paren
comma
l_string|&quot;m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
macro_line|#endif
eof
