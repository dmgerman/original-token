macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
id|asmlinkage
r_int
r_int
id|__ashrdi3
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_char
id|m68k_debug_device
(braket
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_ATARI
r_extern
r_void
id|mach_atari_syms_export
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA
r_extern
r_void
id|mach_amiga_syms_export
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
r_extern
r_void
id|mach_mac_syms_export
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
id|memcmp
)paren
comma
id|X
c_func
(paren
id|boot_info
)paren
comma
id|X
c_func
(paren
id|m68k_is040or060
)paren
comma
id|X
c_func
(paren
id|cache_push
)paren
comma
id|X
c_func
(paren
id|cache_clear
)paren
comma
id|X
c_func
(paren
id|mm_vtop
)paren
comma
id|X
c_func
(paren
id|mm_ptov
)paren
comma
id|X
c_func
(paren
id|m68k_debug_device
)paren
comma
multiline_comment|/* The following are special because they&squot;re not called&n;&t;   explicitly (the C compiler generates them).  Fortunately,&n;&t;   their interface isn&squot;t gonna change any time soon now, so&n;&t;   it&squot;s OK to leave it out of version control.  */
id|XNOVERS
c_func
(paren
id|__ashrdi3
)paren
comma
id|XNOVERS
c_func
(paren
id|memcpy
)paren
comma
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
r_switch
c_cond
(paren
id|boot_info.machtype
)paren
(brace
macro_line|#ifdef CONFIG_ATARI
r_case
id|MACH_ATARI
suffix:colon
id|mach_atari_syms_export
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_AMIGA
r_case
id|MACH_AMIGA
suffix:colon
id|mach_amiga_syms_export
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
r_case
id|MACH_MAC
suffix:colon
id|mach_mac_syms_export
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
eof