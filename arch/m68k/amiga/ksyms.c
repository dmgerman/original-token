macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;asm/zorro.h&gt;
DECL|variable|mach_amiga_symbol_table
r_static
r_struct
id|symbol_table
id|mach_amiga_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
multiline_comment|/*&n;   * Add things here when you find the need for it.&n;   */
id|X
c_func
(paren
id|zorro_find
)paren
comma
id|X
c_func
(paren
id|zorro_get_board
)paren
comma
id|X
c_func
(paren
id|zorro_config_board
)paren
comma
id|X
c_func
(paren
id|zorro_unconfig_board
)paren
comma
multiline_comment|/* example&n;  X(something_you_need),&n;  */
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
DECL|function|mach_amiga_syms_export
r_void
id|mach_amiga_syms_export
c_func
(paren
r_void
)paren
(brace
id|register_symtab
c_func
(paren
op_amp
id|mach_amiga_symbol_table
)paren
suffix:semicolon
)brace
eof
