macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
r_extern
r_int
id|dump_fpu
c_func
(paren
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
DECL|variable|arch_symbol_table
r_static
r_struct
id|symbol_table
id|arch_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
multiline_comment|/* platform dependent support */
id|X
c_func
(paren
id|dump_thread
)paren
comma
id|X
c_func
(paren
id|dump_fpu
)paren
comma
id|X
c_func
(paren
id|ioremap
)paren
comma
id|XNOVERS
c_func
(paren
id|__down_failed
)paren
comma
id|XNOVERS
c_func
(paren
id|__up_wakeup
)paren
comma
macro_line|#ifdef __SMP__
id|X
c_func
(paren
id|apic_reg
)paren
comma
multiline_comment|/* Needed internally for the I386 inlines */
id|X
c_func
(paren
id|cpu_data
)paren
comma
id|X
c_func
(paren
id|syscall_count
)paren
comma
macro_line|#endif
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
DECL|function|arch_syms_export
r_void
id|arch_syms_export
c_func
(paren
r_void
)paren
(brace
id|register_symtab
c_func
(paren
op_amp
id|arch_symbol_table
)paren
suffix:semicolon
)brace
eof
