multiline_comment|/*&n; * include/linux/simp.h  -- simple allocator for cached objects&n; *&n; * This is meant as a faster and simpler (not full-featured) replacement&n; * for SLAB, thus the name &quot;simp&quot; :-)&n; *&n; * (C) 1997 Thomas Schoebel-Theuer&n; */
macro_line|#ifndef SIMP_H
DECL|macro|SIMP_H
mdefine_line|#define SIMP_H
multiline_comment|/* used for constructors / destructors */
DECL|typedef|structor
r_typedef
r_void
(paren
op_star
id|structor
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* create an object cache */
multiline_comment|/* positive clearable_offset means the next two pointers at that offset&n; * can be internally used for freelist pointers when the object is&n; * deallocated / not in use;&n; * if there is no space inside the element that can be reused for&n; * this purpose, supply -1. Using positive offsets is essential for&n; * saving space with very small-sized objects.&n; *&n; * Note for big-sized objects in the range of whole pages, use&n; * the fast Linux page allocator instead, directly.&n; */
r_extern
r_struct
id|simp
op_star
id|simp_create
c_func
(paren
r_char
op_star
id|name
comma
r_int
id|size
comma
id|structor
id|first_ctor
comma
id|structor
id|again_ctor
comma
id|structor
id|dtor
)paren
suffix:semicolon
multiline_comment|/* alloc / dealloc routines */
r_extern
r_void
op_star
id|simp_alloc
c_func
(paren
r_struct
id|simp
op_star
id|simp
)paren
suffix:semicolon
r_extern
r_void
id|simp_free
c_func
(paren
r_void
op_star
id|objp
)paren
suffix:semicolon
multiline_comment|/* garbage collection */
r_extern
r_int
id|simp_garbage
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
