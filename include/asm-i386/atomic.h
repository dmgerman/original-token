macro_line|#ifndef __ARCH_I386_ATOMIC__
DECL|macro|__ARCH_I386_ATOMIC__
mdefine_line|#define __ARCH_I386_ATOMIC__
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; */
macro_line|#ifdef __SMP__
DECL|macro|LOCK
mdefine_line|#define LOCK &quot;lock ; &quot;
macro_line|#else
DECL|macro|LOCK
mdefine_line|#define LOCK &quot;&quot;
macro_line|#endif
multiline_comment|/*&n; * Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
DECL|macro|__atomic_fool_gcc
mdefine_line|#define __atomic_fool_gcc(x) (*(volatile struct { int a[100]; } *)x)
macro_line|#ifdef __SMP__
DECL|member|counter
DECL|typedef|atomic_t
r_typedef
r_struct
(brace
r_volatile
r_int
id|counter
suffix:semicolon
)brace
id|atomic_t
suffix:semicolon
macro_line|#else
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
macro_line|#endif
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)&t;{ (i) }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v,i)&t;&t;(((v)-&gt;counter) = (i))
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
id|LOCK
l_string|&quot;addl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;ir&quot;
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
r_static
id|__inline__
r_void
id|atomic_sub
c_func
(paren
r_int
id|i
comma
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
id|LOCK
l_string|&quot;subl %1,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;ir&quot;
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
DECL|function|atomic_sub_and_test
r_static
id|__inline__
r_int
id|atomic_sub_and_test
c_func
(paren
r_int
id|i
comma
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;subl %2,%0; sete %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;ir&quot;
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
r_return
id|c
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
id|LOCK
l_string|&quot;incl %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
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
id|LOCK
l_string|&quot;decl %0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
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
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;decl %0; sete %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
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
r_return
id|c
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_add_negative
r_extern
id|__inline__
r_int
id|atomic_add_negative
c_func
(paren
r_int
id|i
comma
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
id|LOCK
l_string|&quot;addl %2,%0; sets %1&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
comma
l_string|&quot;=qm&quot;
(paren
id|c
)paren
suffix:colon
l_string|&quot;ir&quot;
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
r_return
id|c
suffix:semicolon
)brace
multiline_comment|/* These are x86-specific, used by some header files */
DECL|macro|atomic_clear_mask
mdefine_line|#define atomic_clear_mask(mask, addr) &bslash;&n;__asm__ __volatile__(LOCK &quot;andl %0,%1&quot; &bslash;&n;: : &quot;r&quot; (~(mask)),&quot;m&quot; (__atomic_fool_gcc(addr)) : &quot;memory&quot;)
DECL|macro|atomic_set_mask
mdefine_line|#define atomic_set_mask(mask, addr) &bslash;&n;__asm__ __volatile__(LOCK &quot;orl %0,%1&quot; &bslash;&n;: : &quot;r&quot; (mask),&quot;m&quot; (__atomic_fool_gcc(addr)) : &quot;memory&quot;)
macro_line|#endif
eof
