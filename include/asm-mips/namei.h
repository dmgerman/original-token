multiline_comment|/*&n; * linux/include/asm-mips/namei.h&n; *&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __ASM_MIPS_NAMEI_H
DECL|macro|__ASM_MIPS_NAMEI_H
mdefine_line|#define __ASM_MIPS_NAMEI_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BINFMT_IRIX
multiline_comment|/* Only one at this time. */
DECL|macro|IRIX32_EMUL
mdefine_line|#define IRIX32_EMUL &quot;usr/gnemul/irix/&quot;
r_extern
r_int
id|__namei
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_struct
id|inode
op_star
comma
r_char
op_star
comma
r_struct
id|inode
op_star
op_star
comma
r_struct
id|inode
op_star
op_star
comma
r_struct
id|qstr
op_star
comma
r_struct
id|dentry
op_star
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_static
id|__inline__
r_int
DECL|function|__prefix_namei
id|__prefix_namei
c_func
(paren
r_int
id|retrieve_mode
comma
r_const
r_char
op_star
id|name
comma
r_struct
id|inode
op_star
id|base
comma
r_char
op_star
id|buf
comma
r_struct
id|inode
op_star
op_star
id|res_dir
comma
r_struct
id|inode
op_star
op_star
id|res_inode
comma
r_struct
id|qstr
op_star
id|last_name
comma
r_struct
id|dentry
op_star
op_star
id|last_entry
comma
r_int
op_star
id|last_error
)paren
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_IRIX32
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_while
c_loop
(paren
op_star
id|name
op_eq
l_char|&squot;/&squot;
)paren
id|name
op_increment
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|current-&gt;fs-&gt;root-&gt;i_count
)paren
suffix:semicolon
id|error
op_assign
id|__namei
c_func
(paren
id|NAM_FOLLOW_LINK
comma
id|IRIX32_EMUL
comma
id|current-&gt;fs-&gt;root
comma
id|buf
comma
l_int|NULL
comma
op_amp
id|base
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|error
op_assign
id|__namei
c_func
(paren
id|retrieve_mode
comma
id|name
comma
id|base
comma
id|buf
comma
id|res_dir
comma
id|res_inode
comma
id|last_name
comma
id|last_entry
comma
id|last_error
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else /* !defined(CONFIG_BINFMT_IRIX) */
DECL|macro|__prefix_namei
mdefine_line|#define __prefix_namei(retrieve_mode, name, base, buf, res_dir, res_inode, &bslash;&n;&t;&t;       last_name, last_entry, last_error) 1
macro_line|#endif /* !defined(CONFIG_BINFMT_IRIX) */
macro_line|#endif /* __ASM_MIPS_NAMEI_H */
eof