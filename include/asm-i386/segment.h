macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
DECL|macro|KERNEL_CS
mdefine_line|#define KERNEL_CS&t;0x10
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0x18
DECL|macro|USER_CS
mdefine_line|#define USER_CS&t;&t;0x23
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;0x2B
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;do { (*(ptr)=(x)); } while (0)
DECL|macro|get_user
mdefine_line|#define get_user(ptr)&t;(*(ptr))
multiline_comment|/*&n; * These are deprecated..&n; *&n; * Use &quot;put_user()&quot; and &quot;get_user()&quot; with the proper pointer types instead.&n; */
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user((const unsigned char *)(addr))
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user((const unsigned short *)(addr))
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user((const unsigned int *)(addr))
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user((x),(unsigned char *)(addr))
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user((x),(unsigned short *)(addr))
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user((x),(unsigned int *)(addr))
DECL|function|memcpy_fromfs
r_static
r_inline
r_void
id|memcpy_fromfs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
DECL|function|memcpy_tofs
r_static
r_inline
r_void
id|memcpy_tofs
c_func
(paren
r_void
op_star
id|to
comma
r_const
r_void
op_star
id|from
comma
r_int
r_int
id|n
)paren
(brace
id|memcpy
c_func
(paren
id|to
comma
id|from
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; * &n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|get_fs
mdefine_line|#define get_fs()&t;(current-&gt;tss.segment)
DECL|macro|set_fs
mdefine_line|#define set_fs(x)&t;(current-&gt;tss.segment = (x))
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
id|KERNEL_DS
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _ASM_SEGMENT_H */
eof
