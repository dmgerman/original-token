multiline_comment|/* $Id: namei.h,v 1.12 1998/03/13 17:38:13 jj Exp $&n; * linux/include/asm-sparc64/namei.h&n; *&n; * Routines to handle famous /usr/gnemul/s*.&n; * Included from linux/fs/namei.c&n; */
macro_line|#ifndef __SPARC64_NAMEI_H
DECL|macro|__SPARC64_NAMEI_H
mdefine_line|#define __SPARC64_NAMEI_H
DECL|macro|SPARC_BSD_EMUL
mdefine_line|#define SPARC_BSD_EMUL &quot;usr/gnemul/sunos/&quot;
DECL|macro|SPARC_SOL_EMUL
mdefine_line|#define SPARC_SOL_EMUL &quot;usr/gnemul/solaris/&quot;
r_static
r_inline
r_struct
id|dentry
op_star
DECL|function|__sparc64_lookup_dentry
id|__sparc64_lookup_dentry
c_func
(paren
r_const
r_char
op_star
id|name
comma
r_int
id|follow_link
)paren
(brace
r_struct
id|dentry
op_star
id|base
suffix:semicolon
r_char
op_star
id|emul
suffix:semicolon
r_switch
c_cond
(paren
id|current-&gt;personality
)paren
(brace
macro_line|#if 0
multiline_comment|/* Until we solve, why SunOS apps sometime crash, disable gnemul support for SunOS */
r_case
id|PER_BSD
suffix:colon
id|emul
op_assign
id|SPARC_BSD_EMUL
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif&t;&t;
r_case
id|PER_SVR4
suffix:colon
id|emul
op_assign
id|SPARC_SOL_EMUL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|NULL
suffix:semicolon
)brace
id|base
op_assign
id|lookup_dentry
(paren
id|emul
comma
id|dget
(paren
id|current-&gt;fs-&gt;root
)paren
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
(paren
id|base
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|base
op_assign
id|lookup_dentry
(paren
id|name
comma
id|base
comma
id|follow_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
(paren
id|base
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|base-&gt;d_inode
)paren
(brace
r_struct
id|dentry
op_star
id|fromroot
suffix:semicolon
id|fromroot
op_assign
id|lookup_dentry
(paren
id|name
comma
id|dget
(paren
id|current-&gt;fs-&gt;root
)paren
comma
id|follow_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
(paren
id|fromroot
)paren
)paren
r_return
id|base
suffix:semicolon
r_if
c_cond
(paren
id|fromroot-&gt;d_inode
)paren
(brace
id|dput
c_func
(paren
id|base
)paren
suffix:semicolon
r_return
id|fromroot
suffix:semicolon
)brace
id|dput
c_func
(paren
id|fromroot
)paren
suffix:semicolon
)brace
r_return
id|base
suffix:semicolon
)brace
DECL|macro|__prefix_lookup_dentry
mdefine_line|#define __prefix_lookup_dentry(name, follow_link)&t;&t;&t;&t;&bslash;&n;&t;if (current-&gt;personality) {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;dentry = __sparc64_lookup_dentry (name, follow_link);&t;&t;&bslash;&n;&t;&t;if (dentry) return dentry;&t;&t;&t;&t;&t;&bslash;&n;&t;}
macro_line|#endif /* __SPARC64_NAMEI_H */
eof
