multiline_comment|/* atomic.h: These really suck for now.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __ARCH_SPARC_ATOMIC__
DECL|macro|__ARCH_SPARC_ATOMIC__
mdefine_line|#define __ARCH_SPARC_ATOMIC__
macro_line|#ifdef __SMP__
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/smp_lock.h&gt;
macro_line|#endif
DECL|typedef|atomic_t
r_typedef
r_int
id|atomic_t
suffix:semicolon
DECL|function|atomic_add
r_static
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
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|v
op_add_assign
id|i
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
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
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|v
op_sub_assign
id|i
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
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
id|flags
comma
id|result
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
op_star
id|v
op_sub_assign
id|i
suffix:semicolon
id|result
op_assign
(paren
op_star
id|v
op_eq
l_int|0
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|atomic_inc
r_static
id|__inline__
r_void
id|atomic_inc
c_func
(paren
id|atomic_t
op_star
id|v
)paren
(brace
id|atomic_add
c_func
(paren
l_int|1
comma
id|v
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
id|atomic_t
op_star
id|v
)paren
(brace
id|atomic_sub
c_func
(paren
l_int|1
comma
id|v
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
id|atomic_t
op_star
id|v
)paren
(brace
r_return
id|atomic_sub_and_test
c_func
(paren
l_int|1
comma
id|v
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__ARCH_SPARC_ATOMIC__) */
eof