macro_line|#ifndef __ARCH_S390_ATOMIC__
DECL|macro|__ARCH_S390_ATOMIC__
mdefine_line|#define __ARCH_S390_ATOMIC__
multiline_comment|/*&n; *  include/asm-s390/atomic.h&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow&n; *&n; *  Derived from &quot;include/asm-i386/bitops.h&quot;&n; *    Copyright (C) 1992, Linus Torvalds&n; *&n; */
multiline_comment|/*&n; * Atomic operations that C can&squot;t guarantee us.  Useful for&n; * resource counting etc..&n; * S390 uses &squot;Compare And Swap&squot; for atomicity in SMP enviroment&n; */
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
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|4
)paren
)paren
)paren
suffix:semicolon
DECL|macro|ATOMIC_INIT
mdefine_line|#define ATOMIC_INIT(i)  { (i) }
DECL|macro|atomic_eieio
mdefine_line|#define atomic_eieio()          __asm__ __volatile__ (&quot;BCR 15,0&quot;)
DECL|function|atomic_read
r_static
id|__inline__
r_int
id|atomic_read
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;bcr      15,0&bslash;n&bslash;t&quot;
l_string|&quot;l        %0,%1&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|retval
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|v
)paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|atomic_set
r_static
id|__inline__
r_void
id|atomic_set
c_func
(paren
id|atomic_t
op_star
id|v
comma
r_int
id|i
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;st  %1,%0&bslash;n&bslash;t&quot;
l_string|&quot;bcr 15,0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;d&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
)brace
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   ar    1,%1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_add_return
r_static
id|__inline__
r_int
id|atomic_add_return
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
id|newval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ar    %1,%2&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|newval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|newval
suffix:semicolon
)brace
DECL|function|atomic_add_negative
r_static
id|__inline__
r_int
id|atomic_add_negative
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
id|newval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ar    %1,%2&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&bslash;n&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|newval
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|newval
OL
l_int|0
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   sr    1,%1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|i
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   ahi   1,1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_inc_return
r_static
id|__inline__
r_int
id|atomic_inc_return
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ahi   %1,1&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|i
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|atomic_inc_and_test
r_static
id|__inline__
r_int
id|atomic_inc_and_test
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ahi   %1,1&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|i
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|i
op_ne
l_int|0
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   ahi   1,-1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_dec_return
r_static
id|__inline__
r_int
id|atomic_dec_return
c_func
(paren
r_volatile
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ahi   %1,-1&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|i
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|i
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
id|i
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    %1,0&bslash;n&quot;
l_string|&quot;   ahi   %1,-1&bslash;n&quot;
l_string|&quot;   cs    0,%1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|i
)paren
suffix:colon
suffix:colon
l_string|&quot;0&quot;
)paren
suffix:semicolon
r_return
id|i
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|atomic_clear_mask
r_static
id|__inline__
r_void
id|atomic_clear_mask
c_func
(paren
r_int
r_int
id|mask
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   nr    1,%1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
op_complement
(paren
id|mask
)paren
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
DECL|function|atomic_set_mask
r_static
id|__inline__
r_void
id|atomic_set_mask
c_func
(paren
r_int
r_int
id|mask
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
l_string|&quot;   l     0,%0&bslash;n&quot;
l_string|&quot;0: lr    1,0&bslash;n&quot;
l_string|&quot;   or    1,%1&bslash;n&quot;
l_string|&quot;   cs    0,1,%0&bslash;n&quot;
l_string|&quot;   jl    0b&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|mask
)paren
suffix:colon
l_string|&quot;0&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;  returns 0  if expected_oldval==value in *v ( swap was successful )&n;  returns 1  if unsuccessful.&n;*/
r_static
id|__inline__
r_int
DECL|function|atomic_compare_and_swap
id|atomic_compare_and_swap
c_func
(paren
r_int
id|expected_oldval
comma
r_int
id|new_val
comma
id|atomic_t
op_star
id|v
)paren
(brace
r_int
id|retval
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;  cs   %2,%3,%1&bslash;n&quot;
l_string|&quot;  ipm  %0&bslash;n&quot;
l_string|&quot;  srl  %0,28&bslash;n&quot;
l_string|&quot;0:&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|retval
)paren
comma
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|expected_oldval
)paren
comma
l_string|&quot;d&quot;
(paren
id|new_val
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n;  Spin till *v = expected_oldval then swap with newval.&n; */
r_static
id|__inline__
r_void
DECL|function|atomic_compare_and_swap_spin
id|atomic_compare_and_swap_spin
c_func
(paren
r_int
id|expected_oldval
comma
r_int
id|new_val
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
l_string|&quot;0: lr  1,%1&bslash;n&quot;
l_string|&quot;   cs  1,%2,%0&bslash;n&quot;
l_string|&quot;   jl  0b&bslash;n&quot;
suffix:colon
l_string|&quot;+m&quot;
(paren
op_star
id|v
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|expected_oldval
)paren
comma
l_string|&quot;d&quot;
(paren
id|new_val
)paren
suffix:colon
l_string|&quot;memory&quot;
comma
l_string|&quot;cc&quot;
comma
l_string|&quot;1&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif                                 /* __ARCH_S390_ATOMIC __            */
eof
