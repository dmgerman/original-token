macro_line|#ifndef _ASMARM_PAGE_H
DECL|macro|_ASMARM_PAGE_H
mdefine_line|#define _ASMARM_PAGE_H
macro_line|#include &lt;asm/arch/mmu.h&gt;
macro_line|#include &lt;asm/proc/page.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memzero((void *)(page), PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#endif
multiline_comment|/* unsigned long __pa(void *x) */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;__virt_to_phys((unsigned long)(x))
multiline_comment|/* void *__va(unsigned long x) */
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)(__phys_to_virt((unsigned long)(x))))
macro_line|#endif
eof
