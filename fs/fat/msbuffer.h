r_struct
id|buffer_head
op_star
id|fat_bread
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
r_struct
id|buffer_head
op_star
id|fat_getblk
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|block
)paren
suffix:semicolon
r_void
id|fat_brelse
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|fat_mark_buffer_dirty
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|dirty_val
)paren
suffix:semicolon
r_void
id|fat_set_uptodate
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
comma
r_int
id|val
)paren
suffix:semicolon
r_int
id|fat_is_uptodate
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_struct
id|buffer_head
op_star
id|bh
)paren
suffix:semicolon
r_void
id|fat_ll_rw_block
(paren
r_struct
id|super_block
op_star
id|sb
comma
r_int
id|opr
comma
r_int
id|nbreq
comma
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|32
)braket
)paren
suffix:semicolon
multiline_comment|/* These macros exist to avoid modifying all the code */
multiline_comment|/* They should be removed one day I guess */
multiline_comment|/* The versioning mechanism of the modules system define those macros */
multiline_comment|/* This remove some warnings */
macro_line|#ifdef brelse
DECL|macro|brelse
macro_line|#undef brelse
macro_line|#endif
macro_line|#ifdef bread
DECL|macro|bread
macro_line|#undef bread
macro_line|#endif
macro_line|#ifdef getblk
DECL|macro|getblk
macro_line|#undef getblk
macro_line|#endif
DECL|macro|brelse
mdefine_line|#define brelse(b)&t;&t;&t;fat_brelse(sb,b)
DECL|macro|bread
mdefine_line|#define bread(d,b,s)&t;&t;&t;fat_bread(sb,b)
DECL|macro|getblk
mdefine_line|#define getblk(d,b,s)&t;&t;&t;fat_getblk(sb,b)
DECL|macro|mark_buffer_dirty
mdefine_line|#define mark_buffer_dirty(b,v)&t;&t;fat_mark_buffer_dirty(sb,b,v)
eof
