macro_line|#ifndef _LINUX_HEAD_H
DECL|macro|_LINUX_HEAD_H
mdefine_line|#define _LINUX_HEAD_H
DECL|struct|desc_struct
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
)brace
suffix:semicolon
r_extern
r_struct
id|desc_struct
id|idt_table
(braket
)braket
comma
id|gdt_table
(braket
)braket
suffix:semicolon
r_extern
r_struct
id|desc_struct
op_star
id|idt
comma
op_star
id|gdt
suffix:semicolon
DECL|struct|Xgt_desc_struct
r_struct
id|Xgt_desc_struct
(brace
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|idt_descr
mdefine_line|#define idt_descr (*(struct Xgt_desc_struct *)((char *)&amp;idt - 2))
DECL|macro|gdt_descr
mdefine_line|#define gdt_descr (*(struct Xgt_desc_struct *)((char *)&amp;gdt - 2))
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
