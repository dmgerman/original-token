multiline_comment|/*&n; *&t;Interface routines assumed by gc()&n; *&n; *&t;Copyright (C) Barak A. Pearlmutter.&n; *&t;Released under the GPL version 2 or later.&n; *&n; */
DECL|typedef|pobj
r_typedef
r_struct
id|object
op_star
id|pobj
suffix:semicolon
multiline_comment|/* pointer to a guy of the type we gc */
multiline_comment|/*&n; *&t;How to mark and unmark objects&n; */
r_extern
r_void
id|gc_mark
c_func
(paren
id|pobj
)paren
suffix:semicolon
r_extern
r_void
id|gc_unmark
c_func
(paren
id|pobj
)paren
suffix:semicolon
r_extern
r_int
id|gc_marked
c_func
(paren
id|pobj
)paren
suffix:semicolon
multiline_comment|/* &n; *&t;How to count and access an object&squot;s children&n; */
r_extern
r_int
id|n_children
c_func
(paren
id|pobj
)paren
suffix:semicolon
multiline_comment|/* how many children */
r_extern
id|pobj
id|child_n
c_func
(paren
id|pobj
comma
r_int
)paren
suffix:semicolon
multiline_comment|/* child i, numbered 0..n-1 */
multiline_comment|/*&n; *&t;How to access the root set&n; */
r_extern
r_int
id|root_size
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* number of things in root set */
r_extern
id|pobj
id|root_elt
c_func
(paren
r_int
)paren
suffix:semicolon
multiline_comment|/* element i of root set, numbered 0..n-1 */
multiline_comment|/*&n; *&t;How to access the free list&n; */
r_extern
r_void
id|clear_freelist
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|add_to_free_list
c_func
(paren
id|pobj
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;How to iterate through all objects in memory&n; */
r_extern
r_int
id|N_OBJS
suffix:semicolon
r_extern
id|pobj
id|obj_number
c_func
(paren
r_int
)paren
suffix:semicolon
eof
