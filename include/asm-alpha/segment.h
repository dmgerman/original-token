macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
macro_line|#include &lt;linux/string.h&gt;
DECL|function|get_user_byte
r_static
r_inline
r_int
r_char
id|get_user_byte
c_func
(paren
r_const
r_char
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user_byte((char *)(addr))
DECL|function|get_user_word
r_static
r_inline
r_int
r_int
id|get_user_word
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user_word((short *)(addr))
DECL|function|get_user_long
r_static
r_inline
r_int
r_int
id|get_user_long
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user_long((int *)(addr))
DECL|function|get_user_quad
r_static
r_inline
r_int
r_int
id|get_user_quad
c_func
(paren
r_const
r_int
op_star
id|addr
)paren
(brace
r_return
op_star
id|addr
suffix:semicolon
)brace
DECL|macro|get_fs_quad
mdefine_line|#define get_fs_quad(addr) get_user_quad((long *)(addr))
DECL|function|put_user_byte
r_static
r_inline
r_void
id|put_user_byte
c_func
(paren
r_char
id|val
comma
r_char
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user_byte((x),(char *)(addr))
DECL|function|put_user_word
r_static
r_inline
r_void
id|put_user_word
c_func
(paren
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user_word((x),(short *)(addr))
DECL|function|put_user_long
r_static
r_inline
r_void
id|put_user_long
c_func
(paren
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user_long((x),(int *)(addr))
DECL|function|put_user_quad
r_static
r_inline
r_void
id|put_user_quad
c_func
(paren
r_int
r_int
id|val
comma
r_int
op_star
id|addr
)paren
(brace
op_star
id|addr
op_assign
id|val
suffix:semicolon
)brace
DECL|macro|put_fs_quad
mdefine_line|#define put_fs_quad(x,addr) put_user_quad((x),(long *)(addr))
DECL|macro|memcpy_fromfs
mdefine_line|#define memcpy_fromfs(to, from, n) memcpy((to),(from),(n))
DECL|macro|memcpy_tofs
mdefine_line|#define memcpy_tofs(to, from, n) memcpy((to),(from),(n))
multiline_comment|/*&n; * For segmented arhictectures, these are used to specify which segment&n; * to use for the above functions.&n; *&n; * The alpha is not segmented, so these are just dummies.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS 0
DECL|macro|USER_DS
mdefine_line|#define USER_DS 1
DECL|function|get_fs
r_static
r_inline
r_int
r_int
id|get_fs
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_ds
r_static
r_inline
r_int
r_int
id|get_ds
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|set_fs
r_static
r_inline
r_void
id|set_fs
c_func
(paren
r_int
r_int
id|val
)paren
(brace
)brace
macro_line|#endif /* _ASM_SEGMENT_H */
eof
