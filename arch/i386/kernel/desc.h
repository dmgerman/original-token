macro_line|#ifndef __ARCH_DESC_H
DECL|macro|__ARCH_DESC_H
mdefine_line|#define __ARCH_DESC_H
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
multiline_comment|/*&n; * Entry into gdt where to find first TSS. GDT layout:&n; *   0 - null&n; *   1 - not used&n; *   2 - kernel code segment&n; *   3 - kernel data segment&n; *   4 - user code segment&n; *   5 - user data segment&n; *   6 - not used&n; *   7 - not used&n; *   8 - APM BIOS support&n; *   9 - APM BIOS support&n; *  10 - APM BIOS support&n; *  11 - APM BIOS support&n; *  12 - TSS #0&n; *  13 - LDT #0&n; *  14 - TSS #1&n; *  15 - LDT #1&n; */
DECL|macro|FIRST_TSS_ENTRY
mdefine_line|#define FIRST_TSS_ENTRY 12
DECL|macro|FIRST_LDT_ENTRY
mdefine_line|#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
DECL|macro|_TSS
mdefine_line|#define _TSS(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_TSS_ENTRY&lt;&lt;3))
DECL|macro|_LDT
mdefine_line|#define _LDT(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_LDT_ENTRY&lt;&lt;3))
DECL|macro|load_TR
mdefine_line|#define load_TR(n) __asm__ __volatile__(&quot;ltr %%ax&quot;: /* no output */ :&quot;a&quot; (_TSS(n)))
DECL|macro|load_ldt
mdefine_line|#define load_ldt(n) __asm__ __volatile__(&quot;lldt %%ax&quot;: /* no output */ :&quot;a&quot; (_LDT(n)))
DECL|macro|store_TR
mdefine_line|#define store_TR(n) &bslash;&n;__asm__(&quot;str %%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subl %2,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;shrl $4,%%eax&quot; &bslash;&n;&t;:&quot;=a&quot; (n) &bslash;&n;&t;:&quot;0&quot; (0),&quot;i&quot; (FIRST_TSS_ENTRY&lt;&lt;3))
r_extern
r_void
id|set_intr_gate
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|set_ldt_desc
c_func
(paren
r_int
r_int
id|n
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|set_tss_desc
c_func
(paren
r_int
r_int
id|n
comma
r_void
op_star
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * This is the ldt that every process will get unless we need&n; * something other than this.&n; */
r_extern
r_struct
id|desc_struct
id|default_ldt
suffix:semicolon
macro_line|#endif
eof
