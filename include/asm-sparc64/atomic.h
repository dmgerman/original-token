multiline_comment|/* $Id: atomic.h,v 1.13 1997/04/14 06:56:57 davem Exp $&n; * atomic.h: Thankfully the V9 is at least reasonable for this&n; *           stuff.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
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
mdefine_line|#define ATOMIC_INIT&t;{ 0 }
DECL|macro|atomic_read
mdefine_line|#define atomic_read(v)&t;&t;((v)-&gt;counter)
DECL|macro|atomic_set
mdefine_line|#define atomic_set(v, i)&t;(((v)-&gt;counter) = i)
DECL|function|atomic_add
r_extern
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
r_int
r_int
id|temp0
comma
id|temp1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|1
suffix:colon
id|add
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|1
id|cas
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
comma
op_mod
l_int|1
id|cmp
op_mod
l_int|0
comma
op_mod
l_int|1
id|bne
comma
id|a
comma
id|pn
op_mod
op_mod
id|icc
comma
l_int|1
id|b
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|2
suffix:colon
l_string|&quot; &t;: &quot;
op_assign
op_amp
id|r
l_string|&quot; (temp0), &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|temp1
)paren
suffix:colon
l_string|&quot;HIr&quot;
(paren
id|i
)paren
comma
l_string|&quot;r&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
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
r_int
id|i
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
r_int
id|temp0
comma
id|temp1
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|1
suffix:colon
id|sub
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|1
id|cas
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
comma
op_mod
l_int|1
id|cmp
op_mod
l_int|0
comma
op_mod
l_int|1
id|bne
comma
id|a
comma
id|pn
op_mod
op_mod
id|icc
comma
l_int|1
id|b
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|2
suffix:colon
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
l_string|&quot; (temp0), &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|temp1
)paren
suffix:colon
l_string|&quot;HIr&quot;
(paren
id|i
)paren
comma
l_string|&quot;r&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Same as above, but return the result value. */
DECL|function|atomic_add_return
r_extern
id|__inline__
r_int
id|atomic_add_return
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
r_int
r_int
id|temp0
comma
id|oldval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|1
suffix:colon
id|add
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|1
id|cas
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
comma
op_mod
l_int|1
id|cmp
op_mod
l_int|0
comma
op_mod
l_int|1
id|bne
comma
id|a
comma
id|pn
op_mod
op_mod
id|icc
comma
l_int|1
id|b
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|2
suffix:colon
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
l_string|&quot; (temp0), &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|oldval
)paren
suffix:colon
l_string|&quot;HIr&quot;
(paren
id|i
)paren
comma
l_string|&quot;r&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
r_int
)paren
id|oldval
)paren
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|atomic_sub_return
r_extern
id|__inline__
r_int
id|atomic_sub_return
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
r_int
r_int
id|temp0
comma
id|oldval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
"&quot;"
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|1
suffix:colon
id|sub
op_mod
l_int|0
comma
op_mod
l_int|2
comma
op_mod
l_int|1
id|cas
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
comma
op_mod
l_int|1
id|cmp
op_mod
l_int|0
comma
op_mod
l_int|1
id|bne
comma
id|a
comma
id|pn
op_mod
op_mod
id|icc
comma
l_int|1
id|b
id|lduw
(braket
op_mod
l_int|3
)braket
comma
op_mod
l_int|0
l_int|2
suffix:colon
l_string|&quot;&t;: &quot;
op_assign
op_amp
id|r
l_string|&quot; (temp0), &quot;
op_assign
op_amp
id|r
"&quot;"
(paren
id|oldval
)paren
suffix:colon
l_string|&quot;HIr&quot;
(paren
id|i
)paren
comma
l_string|&quot;r&quot;
(paren
id|__atomic_fool_gcc
c_func
(paren
id|v
)paren
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
(paren
r_int
)paren
id|oldval
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
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
