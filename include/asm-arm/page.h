macro_line|#ifndef _ASMARM_PAGE_H
DECL|macro|_ASMARM_PAGE_H
mdefine_line|#define _ASMARM_PAGE_H
macro_line|#include &lt;asm/arch/memory.h&gt;
macro_line|#include &lt;asm/proc/page.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|BUG
mdefine_line|#define BUG() do { &bslash;&n;&t;printk(&quot;kernel BUG at %s:%d!&bslash;n&quot;, __FILE__, __LINE__); &bslash;&n;&t;*(int *)0 = 0; &bslash;&n;} while (0)
DECL|macro|PAGE_BUG
mdefine_line|#define PAGE_BUG(page) do { &bslash;&n;&t;BUG(); &bslash;&n;} while (0)
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|get_user_page
mdefine_line|#define get_user_page(vaddr)&t;&t;__get_free_page(GFP_KERNEL)
DECL|macro|free_user_page
mdefine_line|#define free_user_page(page, addr)&t;free_page(addr)
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;&t;memzero((void *)(page), PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#endif
multiline_comment|/* unsigned long __pa(void *x) */
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;__virt_to_phys((unsigned long)(x))
multiline_comment|/* void *__va(unsigned long x) */
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)(__phys_to_virt((unsigned long)(x))))
macro_line|#endif
eof
