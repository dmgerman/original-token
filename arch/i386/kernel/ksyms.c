macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
DECL|variable|arch_symbol_table
r_static
r_struct
id|symbol_table
id|arch_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
multiline_comment|/* platform dependent support */
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
