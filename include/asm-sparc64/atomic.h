multiline_comment|/* $Id: atomic.h,v 1.19 1999/07/03 22:11:17 davem Exp $&n; * atomic.h: Thankfully the V9 is at least reasonable for this&n; *           stuff.&n; *&n; * Copyright (C) 1996, 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ARCH_SPARC64_ATOMIC__
DECL|macro|__ARCH_SPARC64_ATOMIC__
mdefine_line|#define __ARCH_SPARC64_ATOMIC__
multiline_comment|/* Make sure gcc doesn&squot;t try to be clever and move things around&n; * on us. We need to use _exactly_ the address the user gave us,&n; * not some alias that contains the same information.&n; */
DECL|macro|__atomic_fool_gcc
mdefine_line|#define __atomic_fool_gcc(x) ((struct { int a[100]; } *)x)
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
DECL|macro|atomic_add_return
mdefine_line|#define atomic_add_return(__i, __v) &bslash;&n;({&t;register atomic_t *__V asm(&quot;g1&quot;); &bslash;&n;&t;register int __I asm(&quot;g2&quot;); &bslash;&n;&t;__V = (__v); __I = (__i); &bslash;&n;&t;__asm__ __volatile__(&quot;sethi&t;%%hi(__atomic_add), %%g3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;jmpl&t;%%g3 + %%lo(__atomic_add), %%g3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot; nop&bslash;n1:&quot; &bslash;&n;&t;&t;&t;     : &quot;=&amp;r&quot; (__I) &bslash;&n;&t;&t;&t;     : &quot;0&quot; (__I), &quot;r&quot; (__V) &bslash;&n;&t;&t;&t;     : &quot;g3&quot;, &quot;g5&quot;, &quot;g7&quot;, &quot;cc&quot;, &quot;memory&quot;); &bslash;&n;&t;__I; &bslash;&n;})
DECL|macro|atomic_sub_return
mdefine_line|#define atomic_sub_return(__i, __v) &bslash;&n;({&t;register atomic_t *__V asm(&quot;g1&quot;); &bslash;&n;&t;register int __I asm(&quot;g2&quot;); &bslash;&n;&t;__V = (__v); __I = (__i); &bslash;&n;&t;__asm__ __volatile__(&quot;sethi&t;%%hi(__atomic_sub), %%g3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot;jmpl&t;%%g3 + %%lo(__atomic_sub), %%g3&bslash;n&bslash;t&quot; &bslash;&n;&t;&t;&t;     &quot; nop&bslash;n1:&quot; &bslash;&n;&t;&t;&t;     : &quot;=&amp;r&quot; (__I) &bslash;&n;&t;&t;&t;     : &quot;0&quot; (__I), &quot;r&quot; (__V) &bslash;&n;&t;&t;&t;     : &quot;g3&quot;, &quot;g5&quot;, &quot;g7&quot;, &quot;cc&quot;, &quot;memory&quot;); &bslash;&n;&t;__I; &bslash;&n;})
DECL|macro|atomic_add
mdefine_line|#define atomic_add(i, v) atomic_add_return(i, v)
DECL|macro|atomic_sub
mdefine_line|#define atomic_sub(i, v) atomic_sub_return(i, v)
DECL|macro|atomic_dec_return
mdefine_line|#define atomic_dec_return(v) atomic_sub_return(1,(v))
DECL|macro|atomic_inc_return
mdefine_line|#define atomic_inc_return(v) atomic_add_return(1,(v))
DECL|macro|atomic_sub_and_test
mdefine_line|#define atomic_sub_and_test(i,v) (atomic_sub_return((i), (v)) == 0)
DECL|macro|atomic_dec_and_test
mdefine_line|#define atomic_dec_and_test(v) (atomic_sub_return(1, (v)) == 0)
DECL|macro|atomic_inc
mdefine_line|#define atomic_inc(v) atomic_add(1,(v))
DECL|macro|atomic_dec
mdefine_line|#define atomic_dec(v) atomic_sub(1,(v))
macro_line|#endif /* !(__ARCH_SPARC64_ATOMIC__) */
eof
