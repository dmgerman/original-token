multiline_comment|/*&n; * consolemap.h&n; *&n; * Interface between console.c, selection.c  and consolemap.c&n; */
DECL|macro|NORM_MAP
mdefine_line|#define NORM_MAP 0
DECL|macro|GRAF_MAP
mdefine_line|#define GRAF_MAP 1
DECL|macro|NULL_MAP
mdefine_line|#define NULL_MAP 2
DECL|macro|USER_MAP
mdefine_line|#define USER_MAP 3
r_extern
r_int
id|hashtable_contents_valid
suffix:semicolon
r_extern
r_int
r_char
id|inverse_translate
c_func
(paren
r_int
r_char
id|c
)paren
suffix:semicolon
r_extern
r_int
r_char
op_star
id|set_translate
c_func
(paren
r_int
id|m
)paren
suffix:semicolon
eof
