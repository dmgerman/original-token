macro_line|#ifndef _ALPHA_IRQ_H
DECL|macro|_ALPHA_IRQ_H
mdefine_line|#define _ALPHA_IRQ_H
multiline_comment|/*&n; *&t;linux/include/alpha/irq.h&n; *&n; *&t;(C) 1994 Linus Torvalds&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#if defined(CONFIG_ALPHA_CABRIOLET) || defined(CONFIG_ALPHA_EB66P) || defined(CONFIG_ALPHA_EB164)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;33
macro_line|#elif defined(CONFIG_ALPHA_EB66) || defined(CONFIG_ALPHA_EB64P)
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;32
macro_line|#else
DECL|macro|NR_IRQS
macro_line|# define NR_IRQS&t;16
macro_line|#endif
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
multiline_comment|/*&n; * SAVE_MOST/RESTORE_MOST is used for the faster version of IRQ handlers,&n; * installed by using the SA_INTERRUPT flag. These kinds of IRQ&squot;s don&squot;t&n; * call the routines that do signal handling etc on return, and can have&n; * more relaxed register-saving etc. They are also atomic, and are thus&n; * suited for small, fast interrupts like the serial lines or the harddisk&n; * drivers, which don&squot;t actually need signal handling etc.&n; *&n; * Also note that we actually save only those registers that are used in&n; * C subroutines, so if you do something weird, you&squot;re on your own. &n; */
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
