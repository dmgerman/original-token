multiline_comment|/*&n; * linux/arch/alpha/kernel/ksyms.c&n; *&n; * Export the alpha-specific functions that are needed for loadable&n; * modules.&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
r_extern
r_void
id|bcopy
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
suffix:semicolon
multiline_comment|/* these are C runtime functions with special calling conventions: */
r_extern
r_void
id|__divl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__reml
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divqu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remqu
(paren
r_void
)paren
suffix:semicolon
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
r_struct
id|pt_regs
op_star
comma
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
id|_inb
)paren
comma
id|X
c_func
(paren
id|_inw
)paren
comma
id|X
c_func
(paren
id|_inl
)paren
comma
id|X
c_func
(paren
id|_outb
)paren
comma
id|X
c_func
(paren
id|_outw
)paren
comma
id|X
c_func
(paren
id|_outl
)paren
comma
id|X
c_func
(paren
id|_readb
)paren
comma
id|X
c_func
(paren
id|_readw
)paren
comma
id|X
c_func
(paren
id|_readl
)paren
comma
id|X
c_func
(paren
id|_writeb
)paren
comma
id|X
c_func
(paren
id|_writew
)paren
comma
id|X
c_func
(paren
id|_writel
)paren
comma
id|X
c_func
(paren
id|__divl
)paren
comma
id|X
c_func
(paren
id|__reml
)paren
comma
id|X
c_func
(paren
id|__divq
)paren
comma
id|X
c_func
(paren
id|__remq
)paren
comma
id|X
c_func
(paren
id|__divlu
)paren
comma
id|X
c_func
(paren
id|__remlu
)paren
comma
id|X
c_func
(paren
id|__divqu
)paren
comma
id|X
c_func
(paren
id|__remqu
)paren
comma
id|X
c_func
(paren
id|insl
)paren
comma
id|X
c_func
(paren
id|insw
)paren
comma
id|X
c_func
(paren
id|outsl
)paren
comma
id|X
c_func
(paren
id|outsw
)paren
comma
id|X
c_func
(paren
id|strcat
)paren
comma
id|X
c_func
(paren
id|strcmp
)paren
comma
id|X
c_func
(paren
id|strcpy
)paren
comma
id|X
c_func
(paren
id|strlen
)paren
comma
id|X
c_func
(paren
id|strncmp
)paren
comma
id|X
c_func
(paren
id|strncpy
)paren
comma
id|X
c_func
(paren
id|strnlen
)paren
comma
id|X
c_func
(paren
id|strstr
)paren
comma
id|X
c_func
(paren
id|strtok
)paren
comma
id|X
c_func
(paren
id|strchr
)paren
comma
id|X
c_func
(paren
id|memcmp
)paren
comma
id|X
c_func
(paren
id|memmove
)paren
comma
id|X
c_func
(paren
id|__memcpy
)paren
comma
id|X
c_func
(paren
id|__constant_c_memset
)paren
comma
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
id|hwrpb
)paren
comma
id|X
c_func
(paren
id|wrusp
)paren
comma
multiline_comment|/*&n;&t; * The following are special because they&squot;re not called&n;&t; * explicitly (the C compiler or assembler generates them in&n;&t; * response to division operations).  Fortunately, their&n;&t; * interface isn&squot;t gonna change any time soon now, so it&squot;s OK&n;&t; * to leave it out of version control.&n;&t; */
DECL|macro|bcopy
macro_line|# undef bcopy
DECL|macro|memcpy
macro_line|# undef memcpy
DECL|macro|memset
macro_line|# undef memset
id|XNOVERS
c_func
(paren
id|__divl
)paren
comma
id|XNOVERS
c_func
(paren
id|__divlu
)paren
comma
id|XNOVERS
c_func
(paren
id|__divq
)paren
comma
id|XNOVERS
c_func
(paren
id|__divqu
)paren
comma
id|XNOVERS
c_func
(paren
id|__reml
)paren
comma
id|XNOVERS
c_func
(paren
id|__remlu
)paren
comma
id|XNOVERS
c_func
(paren
id|__remq
)paren
comma
id|XNOVERS
c_func
(paren
id|__remqu
)paren
comma
id|XNOVERS
c_func
(paren
id|memcpy
)paren
comma
id|XNOVERS
c_func
(paren
id|memset
)paren
comma
multiline_comment|/* these shouldn&squot;t be necessary---they should be versioned: */
id|XNOVERS
c_func
(paren
id|__memcpy
)paren
comma
id|XNOVERS
c_func
(paren
id|__memset
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
)brace
eof
