multiline_comment|/*&n; *  linux/include/asm-m68k/keyboard.h&n; *&n; *  Created 3 Nov 1996 by Geert Uytterhoeven&n; */
multiline_comment|/*&n; *  This file contains the m68k architecture specific keyboard definitions&n; */
macro_line|#ifndef __M68K_KEYBOARD_H
DECL|macro|__M68K_KEYBOARD_H
mdefine_line|#define __M68K_KEYBOARD_H
macro_line|#ifdef __KERNEL__
DECL|macro|TRANSLATE_SCANCODES
mdefine_line|#define TRANSLATE_SCANCODES&t;&t;0
DECL|macro|USE_MACHDEP_ABSTRACTION
mdefine_line|#define USE_MACHDEP_ABSTRACTION&t;&t;1
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASMm68k_KEYBOARD_H */
eof
