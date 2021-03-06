multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/cache.h&n; *&n; *  Copyright (C) 1999-2000 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Cache handling for 26-bit ARM processors.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(mm,start,end)&t;&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(start,end)&t;do { } while (0)
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)      do { } while (0)
DECL|macro|clean_cache_entry
mdefine_line|#define clean_cache_entry(_start)&t;&t;do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;&t;do { } while (0)
multiline_comment|/* DAG: ARM3 will flush cache on MEMC updates anyway? so don&squot;t bother */
DECL|macro|clean_cache_area
mdefine_line|#define clean_cache_area(_start,_size) do { } while (0)
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; */
DECL|macro|flush_tlb_all
mdefine_line|#define flush_tlb_all()&t;&t;&t;&t;memc_update_all()
DECL|macro|flush_tlb_mm
mdefine_line|#define flush_tlb_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_tlb_range
mdefine_line|#define flush_tlb_range(mm, start, end)&t;&t;do { (void)(start); (void)(end); } while (0)
DECL|macro|flush_tlb_page
mdefine_line|#define flush_tlb_page(vma, vmaddr)&t;&t;do { } while (0)
multiline_comment|/*&n; * The following handle the weird MEMC chip&n; */
DECL|function|memc_update_all
r_extern
id|__inline__
r_void
id|memc_update_all
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|cpu_memc_update_all
c_func
(paren
id|init_mm.pgd
)paren
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;mm
)paren
r_continue
suffix:semicolon
id|cpu_memc_update_all
c_func
(paren
id|p-&gt;mm-&gt;pgd
)paren
suffix:semicolon
)brace
id|processor
dot
id|_set_pgd
c_func
(paren
id|current-&gt;active_mm-&gt;pgd
)paren
suffix:semicolon
)brace
DECL|function|memc_update_mm
r_extern
id|__inline__
r_void
id|memc_update_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|cpu_memc_update_all
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|processor
dot
id|_set_pgd
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|memc_update_addr
id|memc_update_addr
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pte_t
id|pte
comma
r_int
r_int
id|vaddr
)paren
(brace
id|cpu_memc_update_entry
c_func
(paren
id|mm-&gt;pgd
comma
id|pte_val
c_func
(paren
id|pte
)paren
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|processor
dot
id|_set_pgd
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
)brace
r_extern
id|__inline__
r_void
DECL|function|memc_clear
id|memc_clear
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|page
op_star
id|page
)paren
(brace
id|cpu_memc_update_entry
c_func
(paren
id|mm-&gt;pgd
comma
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
op_eq
id|current-&gt;active_mm
)paren
id|processor
dot
id|_set_pgd
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
)brace
eof
