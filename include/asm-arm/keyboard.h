multiline_comment|/*&n; * linux/include/asm-arm/keyboard.h&n; *&n; * Keyboard driver definitions for ARM&n; *&n; * (C) 1998 Russell King&n; */
macro_line|#ifndef __ASM_ARM_KEYBOARD_H
DECL|macro|__ASM_ARM_KEYBOARD_H
mdefine_line|#define __ASM_ARM_KEYBOARD_H
multiline_comment|/*&n; * We provide a unified keyboard interface when in VC_MEDIUMRAW&n; * mode.  This means that all keycodes must be common between&n; * all supported keyboards.  This unfortunately puts us at odds&n; * with the PC keyboard interface chip... but we can&squot;t do anything&n; * about that now.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/arch/keyboard.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_ARM_KEYBOARD_H */
eof
