multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/system.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROC_SYSTEM_H
DECL|macro|__ASM_PROC_SYSTEM_H
mdefine_line|#define __ASM_PROC_SYSTEM_H
r_extern
r_const
r_char
id|xchg_str
(braket
)braket
suffix:semicolon
DECL|function|__xchg
r_extern
id|__inline__
r_int
r_int
id|__xchg
c_func
(paren
r_int
r_int
id|x
comma
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
r_switch
c_cond
(paren
id|size
)paren
(brace
r_case
l_int|1
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;swpb %0, %1, [%2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
m_abort
(paren
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
id|__asm__
id|__volatile__
(paren
l_string|&quot;swp %0, %1, [%2]&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|x
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|x
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptr
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|arm_invalidptr
c_func
(paren
id|xchg_str
comma
id|size
)paren
suffix:semicolon
)brace
r_return
id|x
suffix:semicolon
)brace
DECL|macro|set_cr
mdefine_line|#define set_cr(x)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&bslash;&n;&t;&quot;mcr&t;p15, 0, %0, c1, c0&t;@ set CR&quot;&t;&bslash;&n;&t;  : : &quot;r&quot; (x));&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
r_extern
r_int
r_int
id|cr_no_alignment
suffix:semicolon
multiline_comment|/* defined in entry-armv.S */
r_extern
r_int
r_int
id|cr_alignment
suffix:semicolon
multiline_comment|/* defined in entry-armv.S */
multiline_comment|/*&n; * We can wait for an interrupt...&n; */
DECL|macro|proc_idle
mdefine_line|#define proc_idle()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;mcr&t;p15, 0, %0, c15, c8, 2&t;@ proc_idle&quot;&t;&t;&bslash;&n;&t;  : : &quot;r&quot; (0));&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * A couple of speedups for the ARM&n; */
multiline_comment|/*&n; * Save the current interrupt enable state &amp; disable IRQs&n; */
DECL|macro|__save_flags_cli
mdefine_line|#define __save_flags_cli(x)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%1, cpsr&t;&t;@ save_flags_cli&bslash;n&quot;&t;&bslash;&n;&quot;&t;and&t;%0, %1, #192&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;%1, %1, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr, %1&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (x), &quot;=r&quot; (temp)&t;&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Enable IRQs&n; */
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ sti&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Disable IRQs&n; */
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ cli&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #128&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * save current IRQ &amp; FIQ state&n; */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ save_flags&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;and&t;%0, %0, #192&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * restore saved IRQ &amp; FIQ state&n; */
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&t;&t;&t;&bslash;&n;&t;&quot;mrs&t;%0, cpsr&t;&t;@ restore_flags&bslash;n&quot;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #192&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, %1&bslash;n&quot;&t;&t;&t;&t;&t;&bslash;&n;&quot;&t;msr&t;cpsr, %0&quot;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;r&quot; (x)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#ifdef __SMP__
macro_line|#error SMP not supported
macro_line|#else
DECL|macro|cli
mdefine_line|#define cli() __cli()
DECL|macro|sti
mdefine_line|#define sti() __sti()
DECL|macro|save_flags
mdefine_line|#define save_flags(x)&t;&t;__save_flags(x)
DECL|macro|restore_flags
mdefine_line|#define restore_flags(x)&t;__restore_flags(x)
DECL|macro|save_flags_cli
mdefine_line|#define save_flags_cli(x)&t;__save_flags_cli(x)
macro_line|#endif
macro_line|#endif
eof
