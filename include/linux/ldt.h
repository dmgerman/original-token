multiline_comment|/*&n; * ldt.h&n; *&n; * Definitions of structures used with the modify_ldt system call.&n; */
macro_line|#ifndef _LINUX_LDT_H
DECL|macro|_LINUX_LDT_H
mdefine_line|#define _LINUX_LDT_H
DECL|struct|modify_ldt_ldt_s
r_struct
id|modify_ldt_ldt_s
(brace
DECL|member|entry_number
r_int
r_int
id|entry_number
suffix:semicolon
DECL|member|base_addr
r_int
r_int
id|base_addr
suffix:semicolon
DECL|member|limit
r_int
r_int
id|limit
suffix:semicolon
DECL|member|seg_32bit
r_int
r_int
id|seg_32bit
suffix:colon
l_int|1
suffix:semicolon
DECL|member|contents
r_int
r_int
id|contents
suffix:colon
l_int|2
suffix:semicolon
DECL|member|read_exec_only
r_int
r_int
id|read_exec_only
suffix:colon
l_int|1
suffix:semicolon
DECL|member|limit_in_pages
r_int
r_int
id|limit_in_pages
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MODIFY_LDT_CONTENTS_DATA
mdefine_line|#define MODIFY_LDT_CONTENTS_DATA&t;0
DECL|macro|MODIFY_LDT_CONTENTS_STACK
mdefine_line|#define MODIFY_LDT_CONTENTS_STACK&t;1
DECL|macro|MODIFY_LDT_CONTENTS_CODE
mdefine_line|#define MODIFY_LDT_CONTENTS_CODE&t;2
r_extern
r_int
id|get_ldt
c_func
(paren
r_void
op_star
id|buffer
)paren
suffix:semicolon
r_extern
r_int
id|set_ldt_entry
c_func
(paren
r_int
id|entry
comma
r_int
r_int
id|base
comma
r_int
r_int
id|limit
comma
r_int
id|seg_32bit_flag
comma
r_int
id|contents
comma
r_int
id|read_only_flag
comma
r_int
id|limit_in_pages_flag
)paren
suffix:semicolon
macro_line|#endif
eof