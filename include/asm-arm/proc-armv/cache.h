multiline_comment|/*&n; * Cache flushing...&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cpu_flush_cache_all()
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(_mm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;mm)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_cache_all();&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(_mm,_start,_end)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;mm)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_cache_area((_start), (_end), 1);&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(_vma,_vmaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;mm)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_cache_area((_vmaddr),&t;&t;&t;&bslash;&n;&t;&t;&t;&t;(_vmaddr) + PAGE_SIZE,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|clean_cache_range
mdefine_line|#define clean_cache_range(_start,_end)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long _s, _sz;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_s = (unsigned long)_start;&t;&t;&t;&t;&bslash;&n;&t;&t;_sz = (unsigned long)_end - _s;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_clean_cache_area(_s, _sz);&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|clean_cache_area
mdefine_line|#define clean_cache_area(_start,_size)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long _s;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;_s = (unsigned long)_start;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_clean_cache_area(_s, _size);&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(_start,_end)&t;&t;&t;&t;&t;&bslash;&n;&t;cpu_flush_icache_area((_start), (_end) - (_start))
multiline_comment|/*&n; * We don&squot;t have a MEMC chip...&n; */
DECL|macro|memc_update_all
mdefine_line|#define memc_update_all()&t;&t;do { } while (0)
DECL|macro|memc_update_mm
mdefine_line|#define memc_update_mm(mm)&t;&t;do { } while (0)
DECL|macro|memc_update_addr
mdefine_line|#define memc_update_addr(mm,pte,log)&t;do { } while (0)
DECL|macro|memc_clear
mdefine_line|#define memc_clear(mm,physaddr)&t;&t;do { } while (0)
multiline_comment|/*&n; * This flushes back any buffered write data.  We have to clean the entries&n; * in the cache for this page.  This does not invalidate either I or D caches.&n; */
DECL|function|flush_page_to_ram
r_static
id|__inline__
r_void
id|flush_page_to_ram
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|cpu_flush_ram_page
c_func
(paren
id|page_address
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; *&n; * We drain the write buffer in here to ensure that the page tables in ram&n; * are really up to date.  It is more efficient to do this here...&n; */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;cpu_flush_tlb_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(_mm)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;mm)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_tlb_all();&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(_mm,_start,_end)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;mm)&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_tlb_area((_start), (_end), 1);&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(_vma,_vmaddr)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;mm)&t;&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_flush_tlb_page((_vmaddr),&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t; ((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&t;&bslash;&n;&t;} while (0)
eof
