multiline_comment|/*&n; * fs/proc/omirr.c  -  online mirror support&n; *&n; * (C) 1997 Thomas Schoebel-Theuer&n; */
macro_line|#ifndef OMIRR_H
DECL|macro|OMIRR_H
mdefine_line|#define OMIRR_H
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/dalloc.h&gt;
r_extern
r_int
id|omirr_print
c_func
(paren
r_struct
id|dentry
op_star
id|ent1
comma
r_struct
id|dentry
op_star
id|ent2
comma
r_struct
id|qstr
op_star
id|suffix
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
r_extern
r_int
id|omirr_printall
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
suffix:semicolon
macro_line|#endif
eof
