multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/system.h&n; *&n; * Copyright (c) 1996 Russell King and Dave Gilbert&n; */
macro_line|#ifndef __ASM_ARCH_SYSTEM_H
DECL|macro|__ASM_ARCH_SYSTEM_H
mdefine_line|#define __ASM_ARCH_SYSTEM_H
DECL|macro|cliIF
mdefine_line|#define cliIF()&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;  unsigned long temp;&t;&t;&bslash;&n;&t;  __asm__ __volatile__(&t;&t;&bslash;&n;&quot;&t;mov&t;%0, pc&bslash;n&quot;&t;&t;&bslash;&n;&quot;&t;orr %0, %0, #0x0c000000&bslash;n&quot;&t;&bslash;&n;&quot;&t;teqp&t;%0, #0&bslash;n&quot;&t;&t;&bslash;&n;&t;  : &quot;=r&quot; (temp)&t;&bslash;&n;    : );&t;&bslash;&n;  } while(0)
DECL|function|arch_hard_reset
r_extern
id|__inline__
r_void
id|arch_hard_reset
(paren
r_void
)paren
(brace
r_extern
r_void
id|ecard_reset
(paren
r_int
id|card
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reset all expansion cards.&n;&t; */
id|ecard_reset
(paren
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * copy branch instruction to reset location and call it&n;&t; */
op_star
(paren
r_int
r_int
op_star
)paren
l_int|0
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
l_int|0x03800000
suffix:semicolon
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
l_int|0
)paren
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If that didn&squot;t work, loop endlessly&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
