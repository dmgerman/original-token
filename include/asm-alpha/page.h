macro_line|#ifndef _ALPHA_PAGE_H
DECL|macro|_ALPHA_PAGE_H
mdefine_line|#define _ALPHA_PAGE_H
DECL|macro|invalidate_all
mdefine_line|#define invalidate_all() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-2($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__( &bslash;&n;&t;&quot;lda $16,-1($31)&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;.long 51&quot; &bslash;&n;&t;: : :&quot;$1&quot;, &quot;$16&quot;, &quot;$17&quot;, &quot;$22&quot;,&quot;$23&quot;,&quot;$24&quot;,&quot;$25&quot;)
multiline_comment|/* PAGE_SHIFT determines the page size */
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT&t;&t;&t;13
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;&t;23
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE&t;&t;&t;(1UL &lt;&lt; PAGE_SHIFT)
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
macro_line|#ifdef __KERNEL__
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to mask away the intra-page address bits */
DECL|macro|PAGE_MASK
mdefine_line|#define PAGE_MASK&t;&t;&t;(~(PAGE_SIZE-1))
multiline_comment|/* to mask away the intra-page address bits */
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;&t;(~(PGDIR_SIZE-1))
multiline_comment|/* to align the pointer to the (next) page boundary */
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(addr)&t;&t;(((addr)+PAGE_SIZE-1)&amp;PAGE_MASK)
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;4
multiline_comment|/* to find an entry in a page-table-directory */
multiline_comment|/*&n; * XXXXX This isn&squot;t right: we shouldn&squot;t use the ptbr, but the L2 pointer.&n; * This is just for getting it through the compiler right now&n; */
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) &bslash;&n;((unsigned long *) ((tsk)-&gt;tss.ptbr + ((((unsigned long)(address)) &gt;&gt; 21) &amp; PTR_MASK &amp; ~PAGE_MASK)))
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address)&t;&t;&bslash;&n;  ((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* the no. of pointers that fit on a page */
DECL|macro|PTRS_PER_PAGE
mdefine_line|#define PTRS_PER_PAGE&t;&t;&t;(PAGE_SIZE/sizeof(void*))
multiline_comment|/* to set the page-dir */
multiline_comment|/*&n; * XXXXX This isn&squot;t right: we shouldn&squot;t use the ptbr, but the L2 pointer.&n; * This is just for getting it through the compiler right now&n; */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir) &bslash;&n;do { &bslash;&n;&t;(tsk)-&gt;tss.ptbr = (unsigned long) (pgdir); &bslash;&n;&t;if ((tsk) == current) &bslash;&n;&t;&t;invalidate(); &bslash;&n;} while (0)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ALPHA_PAGE_H */
eof
