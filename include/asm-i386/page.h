macro_line|#ifndef _I386_PAGE_H
DECL|macro|_I386_PAGE_H
mdefine_line|#define _I386_PAGE_H
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;12
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;(~(PAGE_SIZE-1))
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
DECL|macro|STRICT_MM_TYPECHECKS
mdefine_line|#define STRICT_MM_TYPECHECKS
DECL|macro|clear_page
mdefine_line|#define clear_page(page)&t;memset((void *)(page), 0, PAGE_SIZE)
DECL|macro|copy_page
mdefine_line|#define copy_page(to,from)&t;memcpy((void *)(to), (void *)(from), PAGE_SIZE)
macro_line|#ifdef STRICT_MM_TYPECHECKS
multiline_comment|/*&n; * These are used to make use of C type-checking..&n; */
DECL|member|pte
DECL|typedef|pte_t
r_typedef
r_struct
(brace
r_int
r_int
id|pte
suffix:semicolon
)brace
id|pte_t
suffix:semicolon
DECL|member|pmd
DECL|typedef|pmd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pmd
suffix:semicolon
)brace
id|pmd_t
suffix:semicolon
DECL|member|pgd
DECL|typedef|pgd_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgd
suffix:semicolon
)brace
id|pgd_t
suffix:semicolon
DECL|member|pgprot
DECL|typedef|pgprot_t
r_typedef
r_struct
(brace
r_int
r_int
id|pgprot
suffix:semicolon
)brace
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;((x).pte)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;((x).pmd)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;((x).pgd)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;((x).pgprot)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;((pte_t) { (x) } )
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;((pmd_t) { (x) } )
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;((pgd_t) { (x) } )
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;((pgprot_t) { (x) } )
macro_line|#else
multiline_comment|/*&n; * .. while these make it easier on the compiler&n; */
DECL|typedef|pte_t
r_typedef
r_int
r_int
id|pte_t
suffix:semicolon
DECL|typedef|pmd_t
r_typedef
r_int
r_int
id|pmd_t
suffix:semicolon
DECL|typedef|pgd_t
r_typedef
r_int
r_int
id|pgd_t
suffix:semicolon
DECL|typedef|pgprot_t
r_typedef
r_int
r_int
id|pgprot_t
suffix:semicolon
DECL|macro|pte_val
mdefine_line|#define pte_val(x)&t;(x)
DECL|macro|pmd_val
mdefine_line|#define pmd_val(x)&t;(x)
DECL|macro|pgd_val
mdefine_line|#define pgd_val(x)&t;(x)
DECL|macro|pgprot_val
mdefine_line|#define pgprot_val(x)&t;(x)
DECL|macro|__pte
mdefine_line|#define __pte(x)&t;(x)
DECL|macro|__pmd
mdefine_line|#define __pmd(x)&t;(x)
DECL|macro|__pgd
mdefine_line|#define __pgd(x)&t;(x)
DECL|macro|__pgprot
mdefine_line|#define __pgprot(x)&t;(x)
macro_line|#endif
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/*&n; * This handles the memory map.. We could make this a config&n; * option, but too many people screw it up, and too few need&n; * it.&n; *&n; * A __PAGE_OFFSET of 0xC0000000 means that the kernel has&n; * a virtual address space of one gigabyte, which limits the&n; * amount of physical memory you can use to about 950MB. If&n; * you want to use more physical memory, change this define.&n; *&n; * For example, if you have 2GB worth of physical memory, you&n; * could change this define to 0x70000000, which gives the&n; * kernel slightly more than 2GB of virtual memory (enough to&n; * map all your physical memory + a bit extra for various&n; * io-memory mappings)&n; *&n; * IF YOU CHANGE THIS, PLEASE ALSO CHANGE&n; *&n; *&t;arch/i386/vmlinux.lds&n; *&n; * which has the same constant encoded..&n; */
DECL|macro|__PAGE_OFFSET
mdefine_line|#define __PAGE_OFFSET&t;&t;(0xC0000000)
DECL|macro|PAGE_OFFSET
mdefine_line|#define PAGE_OFFSET&t;&t;((unsigned long)__PAGE_OFFSET)
DECL|macro|__pa
mdefine_line|#define __pa(x)&t;&t;&t;((unsigned long)(x)-PAGE_OFFSET)
DECL|macro|__va
mdefine_line|#define __va(x)&t;&t;&t;((void *)((unsigned long)(x)+PAGE_OFFSET))
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr)&t;&t;(__pa(addr) &gt;&gt; PAGE_SHIFT)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _I386_PAGE_H */
eof
