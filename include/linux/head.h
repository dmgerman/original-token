macro_line|#ifndef _LINUX_HEAD_H
DECL|macro|_LINUX_HEAD_H
mdefine_line|#define _LINUX_HEAD_H
DECL|struct|desc_struct
r_typedef
r_struct
id|desc_struct
(brace
DECL|member|a
DECL|member|b
r_int
r_int
id|a
comma
id|b
suffix:semicolon
DECL|typedef|desc_table
)brace
id|desc_table
(braket
l_int|256
)braket
suffix:semicolon
r_extern
r_int
r_int
id|pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|desc_table
id|idt
comma
id|gdt
suffix:semicolon
DECL|macro|GDT_NUL
mdefine_line|#define GDT_NUL 0
DECL|macro|GDT_CODE
mdefine_line|#define GDT_CODE 1
DECL|macro|GDT_DATA
mdefine_line|#define GDT_DATA 2
DECL|macro|GDT_TMP
mdefine_line|#define GDT_TMP 3
DECL|macro|LDT_NUL
mdefine_line|#define LDT_NUL 0
DECL|macro|LDT_CODE
mdefine_line|#define LDT_CODE 1
DECL|macro|LDT_DATA
mdefine_line|#define LDT_DATA 2
macro_line|#endif
eof
