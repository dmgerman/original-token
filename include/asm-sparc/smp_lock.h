multiline_comment|/* smp_lock.h: Locking and unlocking the kernel on the Sparc.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef __SPARC_SMPLOCK_H
DECL|macro|__SPARC_SMPLOCK_H
mdefine_line|#define __SPARC_SMPLOCK_H
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/atops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#ifdef __SMP__
multiline_comment|/*&n; *&t;Locking the kernel &n; */
multiline_comment|/* Knock knock... */
DECL|function|lock_kernel
r_extern
id|__inline
r_void
id|lock_kernel
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|proc
op_assign
id|smp_processor_id
c_func
(paren
)paren
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
multiline_comment|/* need this on sparc? */
r_while
c_loop
(paren
id|ldstub
c_func
(paren
op_amp
id|kernel_flag
)paren
)paren
(brace
r_if
c_cond
(paren
id|proc
op_eq
id|active_kernel_processor
)paren
(brace
r_break
suffix:semicolon
)brace
r_do
(brace
macro_line|#ifdef __SMP_PROF__&t;&t;
id|smp_spins
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
op_increment
suffix:semicolon
macro_line|#endif&t;&t;&t;
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|kernel_flag
)paren
(brace
suffix:semicolon
)brace
multiline_comment|/* Don&squot;t lock the bus more than we have to. */
)brace
id|active_kernel_processor
op_assign
id|proc
suffix:semicolon
id|kernel_counter
op_increment
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* I want out... */
DECL|function|unlock_kernel
r_extern
id|__inline
r_void
id|unlock_kernel
c_func
(paren
r_void
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
multiline_comment|/* need this on sparc? */
r_if
c_cond
(paren
id|kernel_counter
op_eq
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Bogus kernel counter.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|kernel_counter
)paren
(brace
id|active_kernel_processor
op_assign
id|NO_PROC_ID
suffix:semicolon
id|kernel_flag
op_assign
id|KLOCK_CLEAR
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(__SPARC_SMPLOCK_H) */
macro_line|#endif /* (__SMP__) */
eof
