macro_line|#ifndef _ASM_SEGMENT_H
DECL|macro|_ASM_SEGMENT_H
mdefine_line|#define _ASM_SEGMENT_H
macro_line|#include &lt;linux/string.h&gt;
multiline_comment|/*&n; * Uh, these should become the main single-value transfer routines..&n; * They automatically use the right size if we just have the right&n; * pointer type..&n; *&n; * As the alpha uses the same address space for kernel and user&n; * data, we can just do these as direct assignments.&n; */
DECL|macro|put_user
mdefine_line|#define put_user(x,ptr)&t;do { (*(ptr)=(x)); } while (0)
DECL|macro|get_user
mdefine_line|#define get_user(ptr)&t;(*(ptr))
multiline_comment|/*&n; * These are deprecated..&n; *&n; * Use &quot;put_user()&quot; and &quot;get_user()&quot; with the proper pointer types instead.&n; */
DECL|macro|get_fs_byte
mdefine_line|#define get_fs_byte(addr) get_user((unsigned char *)(addr))
DECL|macro|get_fs_word
mdefine_line|#define get_fs_word(addr) get_user((unsigned short *)(addr))
DECL|macro|get_fs_long
mdefine_line|#define get_fs_long(addr) get_user((unsigned int *)(addr))
DECL|macro|get_fs_quad
mdefine_line|#define get_fs_quad(addr) get_user((unsigned long *)(addr))
DECL|macro|put_fs_byte
mdefine_line|#define put_fs_byte(x,addr) put_user((x),(char *)(addr))
DECL|macro|put_fs_word
mdefine_line|#define put_fs_word(x,addr) put_user((x),(short *)(addr))
DECL|macro|put_fs_long
mdefine_line|#define put_fs_long(x,addr) put_user((x),(int *)(addr))
DECL|macro|put_fs_quad
mdefine_line|#define put_fs_quad(x,addr) put_user((x),(long *)(addr))
DECL|macro|memcpy_fromfs
mdefine_line|#define memcpy_fromfs(to,from,n) memcpy((to),(from),(n))
DECL|macro|memcpy_tofs
mdefine_line|#define memcpy_tofs(to,from,n) memcpy((to),(from),(n))
multiline_comment|/*&n; * The fs value determines whether argument validity checking should be&n; * performed or not.  If get_fs() == USER_DS, checking is performed, with&n; * get_fs() == KERNEL_DS, checking is bypassed.&n; *&n; * For historical reasons, these macros are grossly misnamed.&n; */
DECL|macro|KERNEL_DS
mdefine_line|#define KERNEL_DS&t;0
DECL|macro|USER_DS
mdefine_line|#define USER_DS&t;&t;1
DECL|macro|get_fs
mdefine_line|#define get_fs()  (current-&gt;tss.flags &amp; 0x1)
DECL|macro|set_fs
mdefine_line|#define set_fs(x) (current-&gt;tss.flags = (current-&gt;tss.flags &amp; ~0x1) | ((x) &amp; 0x1))
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
macro_line|#endif /* _ASM_SEGMENT_H */
eof
