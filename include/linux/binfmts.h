macro_line|#ifndef _LINUX_BINFMTS_H
DECL|macro|_LINUX_BINFMTS_H
mdefine_line|#define _LINUX_BINFMTS_H
macro_line|#include &lt;linux/ptrace.h&gt;
multiline_comment|/*&n; * MAX_ARG_PAGES defines the number of pages allocated for arguments&n; * and envelope for the new program. 32 should suffice, this gives&n; * a maximum env+arg of 128kB w/4KB pages!&n; */
DECL|macro|MAX_ARG_PAGES
mdefine_line|#define MAX_ARG_PAGES 32
multiline_comment|/*&n; * This structure is used to hold the arguments that are used when loading binaries.&n; */
DECL|struct|linux_binprm
r_struct
id|linux_binprm
(brace
DECL|member|buf
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|page
r_int
r_int
id|page
(braket
id|MAX_ARG_PAGES
)braket
suffix:semicolon
DECL|member|p
r_int
r_int
id|p
suffix:semicolon
DECL|member|sh_bang
r_int
id|sh_bang
suffix:semicolon
DECL|member|java
r_int
id|java
suffix:semicolon
multiline_comment|/* Java binary, prevent recursive invocation */
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|e_uid
DECL|member|e_gid
r_int
id|e_uid
comma
id|e_gid
suffix:semicolon
DECL|member|argc
DECL|member|envc
r_int
id|argc
comma
id|envc
suffix:semicolon
DECL|member|filename
r_char
op_star
id|filename
suffix:semicolon
multiline_comment|/* Name of binary */
DECL|member|loader
DECL|member|exec
r_int
r_int
id|loader
comma
id|exec
suffix:semicolon
DECL|member|dont_iput
r_int
id|dont_iput
suffix:semicolon
multiline_comment|/* binfmt handler has put inode */
)brace
suffix:semicolon
multiline_comment|/*&n; * This structure defines the functions that are used to load the binary formats that&n; * linux accepts.&n; */
DECL|struct|linux_binfmt
r_struct
id|linux_binfmt
(brace
DECL|member|next
r_struct
id|linux_binfmt
op_star
id|next
suffix:semicolon
DECL|member|module
r_struct
id|module
op_star
id|module
suffix:semicolon
DECL|member|load_binary
r_int
(paren
op_star
id|load_binary
)paren
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|member|load_shlib
r_int
(paren
op_star
id|load_shlib
)paren
(paren
r_int
id|fd
)paren
suffix:semicolon
DECL|member|core_dump
r_int
(paren
op_star
id|core_dump
)paren
(paren
r_int
id|signr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|register_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
)paren
suffix:semicolon
r_extern
r_int
id|unregister_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
)paren
suffix:semicolon
r_extern
r_int
id|read_exec
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|offset
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
comma
r_int
id|to_kmem
)paren
suffix:semicolon
r_extern
r_int
id|open_inode
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
id|mode
)paren
suffix:semicolon
r_extern
r_int
id|init_elf_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_elf32_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_aout_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_aout32_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_script_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_java_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_em86_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_misc_binfmt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|prepare_binprm
c_func
(paren
r_struct
id|linux_binprm
op_star
)paren
suffix:semicolon
r_extern
r_void
id|remove_arg_zero
c_func
(paren
r_struct
id|linux_binprm
op_star
)paren
suffix:semicolon
r_extern
r_int
id|search_binary_handler
c_func
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|flush_old_exec
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
r_extern
r_int
r_int
id|setup_arg_pages
c_func
(paren
r_int
r_int
id|p
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
r_extern
r_int
r_int
id|copy_strings
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_int
r_int
op_star
id|page
comma
r_int
r_int
id|p
comma
r_int
id|from_kmem
)paren
suffix:semicolon
multiline_comment|/* this eventually goes away */
DECL|macro|change_ldt
mdefine_line|#define change_ldt(a,b) setup_arg_pages(a,b)
macro_line|#endif
eof
