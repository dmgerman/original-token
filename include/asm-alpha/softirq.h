macro_line|#ifndef _ALPHA_SOFTIRQ_H
DECL|macro|_ALPHA_SOFTIRQ_H
mdefine_line|#define _ALPHA_SOFTIRQ_H
multiline_comment|/*&n; * Software interrupts..&n; */
DECL|macro|get_active_bhs
mdefine_line|#define get_active_bhs()&t;(bh_mask &amp; bh_active)
DECL|function|clear_active_bhs
r_static
r_inline
r_void
id|clear_active_bhs
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
r_int
id|temp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;1:&t;ldq_l %0,%1&bslash;n&quot;
l_string|&quot;&t;and %0,%2,%0&bslash;n&quot;
l_string|&quot;&t;stq_c %0,%1&bslash;n&quot;
l_string|&quot;&t;beq %0,2f&bslash;n&quot;
l_string|&quot;.text 2&bslash;n&quot;
l_string|&quot;2:&t;br 1b&bslash;n&quot;
l_string|&quot;.text&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|temp
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_active
)paren
suffix:colon
l_string|&quot;Ir&quot;
(paren
id|x
)paren
comma
l_string|&quot;m&quot;
(paren
id|bh_active
)paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef __SMP__
multiline_comment|/* These are for the irq&squot;s testing the lock */
DECL|macro|softirq_trylock
mdefine_line|#define softirq_trylock()&t;(intr_count ? 0 : ((intr_count=1),1))
DECL|macro|softirq_endlock
mdefine_line|#define softirq_endlock()&t;(intr_count = 0)
macro_line|#else
macro_line|#error FIXME
macro_line|#endif /* __SMP__ */
macro_line|#endif /* _ALPHA_SOFTIRQ_H */
eof
