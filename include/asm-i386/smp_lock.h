macro_line|#ifndef __I386_SMPLOCK_H
DECL|macro|__I386_SMPLOCK_H
mdefine_line|#define __I386_SMPLOCK_H
macro_line|#ifdef __SMP__
multiline_comment|/*&n; *&t;Locking the kernel &n; */
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
multiline_comment|/* set_bit works atomic in SMP machines */
r_while
c_loop
(paren
id|set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|kernel_flag
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;We just start another level if we have the lock &n;&t;&t; */
r_if
c_cond
(paren
id|proc
op_eq
id|active_kernel_processor
)paren
r_break
suffix:semicolon
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
multiline_comment|/*&n;&t;&t;&t; *&t;Doing test_bit here doesn&squot;t lock the bus &n;&t;&t;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|proc
comma
(paren
r_void
op_star
)paren
op_amp
id|smp_invalidate_needed
)paren
)paren
r_if
c_cond
(paren
id|clear_bit
c_func
(paren
id|proc
comma
(paren
r_void
op_star
)paren
op_amp
id|smp_invalidate_needed
)paren
)paren
id|local_invalidate
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|test_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|kernel_flag
)paren
)paren
(brace
suffix:semicolon
)brace
)brace
multiline_comment|/* &n;&t; *&t;We got the lock, so tell the world we are here and increment&n;&t; *&t;the level counter &n;&t; */
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
multiline_comment|/*&n;&t; *&t;If it&squot;s the last level we have in the kernel, then&n;&t; *&t;free the lock &n;&t; */
r_if
c_cond
(paren
id|kernel_counter
op_eq
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;Kernel counter wrong.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* FIXME: Why is kernel_counter sometimes 0 here? */
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
id|clear_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|kernel_flag
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
