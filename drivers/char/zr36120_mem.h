multiline_comment|/* either kmalloc() or bigphysarea() alloced memory - continuous */
r_void
op_star
id|bmalloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_void
id|bfree
c_func
(paren
r_void
op_star
id|mem
comma
r_int
r_int
id|size
)paren
suffix:semicolon
eof
