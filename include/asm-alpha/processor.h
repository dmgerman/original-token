multiline_comment|/*&n; * include/asm-alpha/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_ALPHA_PROCESSOR_H
DECL|macro|__ASM_ALPHA_PROCESSOR_H
mdefine_line|#define __ASM_ALPHA_PROCESSOR_H
multiline_comment|/*&n; * We have a 8GB user address space to start with: 33 bits of vm&n; * can be handled with just 2 page table levels.&n; *&n; * Eventually, this should be bumped to 40 bits or so..&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE (0x200000000UL)
multiline_comment|/*&n; * Bus types&n; */
DECL|macro|EISA_bus
mdefine_line|#define EISA_bus 1
DECL|macro|EISA_bus__is_a_macro
mdefine_line|#define EISA_bus__is_a_macro /* for versions in ksyms.c */
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * The alpha has no problems with write protection&n; */
DECL|macro|wp_works_ok
mdefine_line|#define wp_works_ok 1
DECL|macro|wp_works_ok__is_a_macro
mdefine_line|#define wp_works_ok__is_a_macro /* for versions in ksyms.c */
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|ksp
r_int
r_int
id|ksp
suffix:semicolon
DECL|member|usp
r_int
r_int
id|usp
suffix:semicolon
DECL|member|ptbr
r_int
r_int
id|ptbr
suffix:semicolon
DECL|member|pcc
r_int
r_int
id|pcc
suffix:semicolon
DECL|member|asn
r_int
r_int
id|asn
suffix:semicolon
DECL|member|unique
r_int
r_int
id|unique
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|res1
DECL|member|res2
r_int
r_int
id|res1
comma
id|res2
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;&t;0, 0, 0, &bslash;&n;}
multiline_comment|/*&n; * These are the &quot;cli()&quot; and &quot;sti()&quot; for software interrupts&n; * They work by increasing/decreasing the &quot;intr_count&quot; value, &n; * and as such can be nested arbitrarily.&n; */
DECL|function|start_bh_atomic
r_extern
r_inline
r_void
id|start_bh_atomic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;addq %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|end_bh_atomic
r_extern
r_inline
r_void
id|end_bh_atomic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|dummy
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n1:&bslash;t&quot;
l_string|&quot;ldq_l %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;subq %0,1,%0&bslash;n&bslash;t&quot;
l_string|&quot;stq_c %0,%1&bslash;n&bslash;t&quot;
l_string|&quot;beq %0,1b&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|dummy
)paren
comma
l_string|&quot;=m&quot;
(paren
id|intr_count
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* __ASM_ALPHA_PROCESSOR_H */
eof
