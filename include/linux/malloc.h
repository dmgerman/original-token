macro_line|#ifndef _LINUX_MALLOC_H
DECL|macro|_LINUX_MALLOC_H
mdefine_line|#define _LINUX_MALLOC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DEBUG_MALLOC
DECL|macro|kmalloc
mdefine_line|#define kmalloc(a,b) deb_kmalloc(__FILE__,__LINE__,a,b)
DECL|macro|kfree_s
mdefine_line|#define kfree_s(a,b) deb_kfree_s(__FILE__,__LINE__,a,b)
r_void
op_star
id|deb_kmalloc
c_func
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|deb_kfree_s
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
r_void
id|deb_kcheck_s
c_func
(paren
r_const
r_char
op_star
id|deb_file
comma
r_int
r_int
id|deb_line
comma
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|kfree
mdefine_line|#define kfree(a) deb_kfree_s(__FILE__,__LINE__, a,0)
DECL|macro|kcheck
mdefine_line|#define kcheck(a) deb_kcheck_s(__FILE__,__LINE__, a,0)
DECL|macro|kcheck_s
mdefine_line|#define kcheck_s(a,b) deb_kcheck_s(__FILE__,__LINE__, a,b)
macro_line|#else /* !debug */
r_void
op_star
id|kmalloc
c_func
(paren
r_int
r_int
id|size
comma
r_int
id|priority
)paren
suffix:semicolon
r_void
id|kfree_s
c_func
(paren
r_void
op_star
id|obj
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|kcheck_s
mdefine_line|#define kcheck_s(a,b) 0
DECL|macro|kfree
mdefine_line|#define kfree(x) kfree_s((x), 0)
DECL|macro|kcheck
mdefine_line|#define kcheck(x) kcheck_s((x), 0)
macro_line|#endif
macro_line|#endif /* _LINUX_MALLOC_H */
eof
