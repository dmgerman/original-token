macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/asm-sparc/irq.h&n; *&n; *&t;Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#include &lt;linux/linkage.h&gt;
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|macro|__STR
mdefine_line|#define __STR(x) #x
DECL|macro|STR
mdefine_line|#define STR(x) __STR(x)
DECL|macro|SAVE_ALL
mdefine_line|#define SAVE_ALL &quot;xx&quot;
DECL|macro|SAVE_MOST
mdefine_line|#define SAVE_MOST &quot;yy&quot;
DECL|macro|RESTORE_MOST
mdefine_line|#define RESTORE_MOST &quot;zz&quot;
DECL|macro|ACK_FIRST
mdefine_line|#define ACK_FIRST(mask) &quot;aa&quot;
DECL|macro|ACK_SECOND
mdefine_line|#define ACK_SECOND(mask) &quot;dummy&quot;
DECL|macro|UNBLK_FIRST
mdefine_line|#define UNBLK_FIRST(mask) &quot;dummy&quot;
DECL|macro|UNBLK_SECOND
mdefine_line|#define UNBLK_SECOND(mask) &quot;dummy&quot;
DECL|macro|IRQ_NAME2
mdefine_line|#define IRQ_NAME2(nr) nr##_interrupt(void)
DECL|macro|IRQ_NAME
mdefine_line|#define IRQ_NAME(nr) IRQ_NAME2(IRQ##nr)
DECL|macro|FAST_IRQ_NAME
mdefine_line|#define FAST_IRQ_NAME(nr) IRQ_NAME2(fast_IRQ##nr)
DECL|macro|BAD_IRQ_NAME
mdefine_line|#define BAD_IRQ_NAME(nr) IRQ_NAME2(bad_IRQ##nr)
DECL|macro|BUILD_IRQ
mdefine_line|#define BUILD_IRQ(chip,nr,mask) &bslash;&n;asmlinkage void IRQ_NAME(nr); &bslash;&n;asmlinkage void FAST_IRQ_NAME(nr); &bslash;&n;asmlinkage void BAD_IRQ_NAME(nr); &bslash;&n;asm code comes here
macro_line|#endif
eof
