multiline_comment|/*&n; * linux/include/asm-arm/proc-armo/system.h&n; *&n; * Copyright (C) 1995, 1996 Russell King&n; */
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
macro_line|#include &lt;asm/proc-fns.h&gt;
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
r_return
id|processor.u.armv2
dot
id|_xchg_1
c_func
(paren
id|x
comma
id|ptr
)paren
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
id|processor.u.armv2
dot
id|_xchg_2
c_func
(paren
id|x
comma
id|ptr
)paren
suffix:semicolon
r_case
l_int|4
suffix:colon
r_return
id|processor.u.armv2
dot
id|_xchg_4
c_func
(paren
id|x
comma
id|ptr
)paren
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We need to turn the caches off before calling the reset vector - RiscOS&n; * messes up if we don&squot;t&n; */
DECL|macro|proc_hard_reset
mdefine_line|#define proc_hard_reset()&t;processor._proc_fin()
multiline_comment|/*&n; * This processor does not idle&n; */
DECL|macro|proc_idle
mdefine_line|#define proc_idle()
multiline_comment|/*&n; * A couple of speedups for the ARM&n; */
multiline_comment|/*&n; * Save the current interrupt enable state &amp; disable IRQs&n; */
DECL|macro|__save_flags_cli
mdefine_line|#define __save_flags_cli(x)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%1, %0, #0x08000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;and&t;%0, %0, #0x0c000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;teqp&t;%1, #0&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (x), &quot;=r&quot; (temp)&t;&bslash;&n;&t;  :&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * Enable IRQs&n; */
DECL|macro|__sti
mdefine_line|#define __sti()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #0x08000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;teqp&t;%0, #0&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Disable IRQs&n; */
DECL|macro|__cli
mdefine_line|#define __cli()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, #0x08000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;teqp&t;%0, #0&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&bslash;&n;&t;  :&t;&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;} while(0)
multiline_comment|/*&n; * save current IRQ &amp; FIQ state&n; */
DECL|macro|__save_flags
mdefine_line|#define __save_flags(x)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;and&t;%0, %0, #0x0c000000&bslash;n&quot;&t;&bslash;&n;&t;  : &quot;=r&quot; (x));&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/*&n; * restore saved IRQ &amp; FIQ state&n; */
DECL|macro|__restore_flags
mdefine_line|#define __restore_flags(x)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;bic&t;%0, %0, #0x0c000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;orr&t;%0, %0, %1&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;teqp&t;%0, #0&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&t;&t;&bslash;&n;&t;  : &quot;r&quot; (x)&t;&t;&t;&bslash;&n;&t;  : &quot;memory&quot;);&t;&t;&t;&bslash;&n;&t;} while (0)
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
