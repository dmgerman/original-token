macro_line|#ifndef _LINUX_MM_H
DECL|macro|_LINUX_MM_H
mdefine_line|#define _LINUX_MM_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/list.h&gt;
r_extern
r_int
r_int
id|max_mapnr
suffix:semicolon
r_extern
r_int
r_int
id|num_physpages
suffix:semicolon
r_extern
r_void
op_star
id|high_memory
suffix:semicolon
r_extern
r_int
id|page_cluster
suffix:semicolon
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
multiline_comment|/*&n; * Linux kernel virtual memory manager primitives.&n; * The idea being to have a &quot;virtual&quot; mm in the same way&n; * we have a virtual fs - giving a cleaner interface to the&n; * mm details, and allowing different kinds of memory mappings&n; * (from shared memory to executable loading to arbitrary&n; * mmap() functions).&n; */
multiline_comment|/*&n; * This struct defines a memory VMM memory area. There is one of these&n; * per VM-area/task.  A VM area is any part of the process virtual memory&n; * space that has a special rule for the page-fault handlers (ie a shared&n; * library, the executable area etc).&n; */
DECL|struct|vm_area_struct
r_struct
id|vm_area_struct
(brace
DECL|member|vm_mm
r_struct
id|mm_struct
op_star
id|vm_mm
suffix:semicolon
multiline_comment|/* VM area parameters */
DECL|member|vm_start
r_int
r_int
id|vm_start
suffix:semicolon
DECL|member|vm_end
r_int
r_int
id|vm_end
suffix:semicolon
multiline_comment|/* linked list of VM areas per task, sorted by address */
DECL|member|vm_next
r_struct
id|vm_area_struct
op_star
id|vm_next
suffix:semicolon
DECL|member|vm_page_prot
id|pgprot_t
id|vm_page_prot
suffix:semicolon
DECL|member|vm_flags
r_int
r_int
id|vm_flags
suffix:semicolon
multiline_comment|/* AVL tree of VM areas per task, sorted by address */
DECL|member|vm_avl_height
r_int
id|vm_avl_height
suffix:semicolon
DECL|member|vm_avl_left
r_struct
id|vm_area_struct
op_star
id|vm_avl_left
suffix:semicolon
DECL|member|vm_avl_right
r_struct
id|vm_area_struct
op_star
id|vm_avl_right
suffix:semicolon
multiline_comment|/* For areas with inode, the list inode-&gt;i_mmap, for shm areas,&n;&t; * the list of attaches, otherwise unused.&n;&t; */
DECL|member|vm_next_share
r_struct
id|vm_area_struct
op_star
id|vm_next_share
suffix:semicolon
DECL|member|vm_pprev_share
r_struct
id|vm_area_struct
op_star
op_star
id|vm_pprev_share
suffix:semicolon
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
DECL|member|vm_pgoff
r_int
r_int
id|vm_pgoff
suffix:semicolon
multiline_comment|/* offset in PAGE_SIZE units, *not* PAGE_CACHE_SIZE */
DECL|member|vm_file
r_struct
id|file
op_star
id|vm_file
suffix:semicolon
DECL|member|vm_private_data
r_void
op_star
id|vm_private_data
suffix:semicolon
multiline_comment|/* was vm_pte (shared mem) */
)brace
suffix:semicolon
multiline_comment|/*&n; * vm_flags..&n; */
DECL|macro|VM_READ
mdefine_line|#define VM_READ&t;&t;0x0001&t;/* currently active flags */
DECL|macro|VM_WRITE
mdefine_line|#define VM_WRITE&t;0x0002
DECL|macro|VM_EXEC
mdefine_line|#define VM_EXEC&t;&t;0x0004
DECL|macro|VM_SHARED
mdefine_line|#define VM_SHARED&t;0x0008
DECL|macro|VM_MAYREAD
mdefine_line|#define VM_MAYREAD&t;0x0010&t;/* limits for mprotect() etc */
DECL|macro|VM_MAYWRITE
mdefine_line|#define VM_MAYWRITE&t;0x0020
DECL|macro|VM_MAYEXEC
mdefine_line|#define VM_MAYEXEC&t;0x0040
DECL|macro|VM_MAYSHARE
mdefine_line|#define VM_MAYSHARE&t;0x0080
DECL|macro|VM_GROWSDOWN
mdefine_line|#define VM_GROWSDOWN&t;0x0100&t;/* general info on the segment */
DECL|macro|VM_GROWSUP
mdefine_line|#define VM_GROWSUP&t;0x0200
DECL|macro|VM_SHM
mdefine_line|#define VM_SHM&t;&t;0x0400&t;/* shared memory area, don&squot;t swap out */
DECL|macro|VM_DENYWRITE
mdefine_line|#define VM_DENYWRITE&t;0x0800&t;/* ETXTBSY on write attempts.. */
DECL|macro|VM_EXECUTABLE
mdefine_line|#define VM_EXECUTABLE&t;0x1000
DECL|macro|VM_LOCKED
mdefine_line|#define VM_LOCKED&t;0x2000
DECL|macro|VM_IO
mdefine_line|#define VM_IO           0x4000  /* Memory mapped I/O or similar */
DECL|macro|VM_STACK_FLAGS
mdefine_line|#define VM_STACK_FLAGS&t;0x0177
multiline_comment|/*&n; * mapping from the currently active vm_flags protection bits (the&n; * low four bits) to a page protection mask..&n; */
r_extern
id|pgprot_t
id|protection_map
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/*&n; * These are the virtual MM functions - opening of an area, closing and&n; * unmapping it (needed to keep files on disk up-to-date etc), pointer&n; * to the functions called when a no-page or a wp-page exception occurs. &n; */
DECL|struct|vm_operations_struct
r_struct
id|vm_operations_struct
(brace
DECL|member|open
r_void
(paren
op_star
id|open
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
)paren
suffix:semicolon
DECL|member|close
r_void
(paren
op_star
id|close
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
)paren
suffix:semicolon
DECL|member|unmap
r_void
(paren
op_star
id|unmap
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
DECL|member|protect
r_void
(paren
op_star
id|protect
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
comma
r_int
comma
r_int
r_int
id|newprot
)paren
suffix:semicolon
DECL|member|sync
r_int
(paren
op_star
id|sync
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
comma
r_int
comma
r_int
r_int
id|flags
)paren
suffix:semicolon
DECL|member|advise
r_void
(paren
op_star
id|advise
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
comma
r_int
comma
r_int
r_int
id|advise
)paren
suffix:semicolon
DECL|member|nopage
r_struct
id|page
op_star
(paren
op_star
id|nopage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
id|write_access
)paren
suffix:semicolon
DECL|member|wppage
r_struct
id|page
op_star
(paren
op_star
id|wppage
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|member|swapout
r_int
(paren
op_star
id|swapout
)paren
(paren
r_struct
id|page
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * A swap entry has to fit into a &quot;unsigned long&quot;, as&n; * the entry is hidden in the &quot;pg_offset&quot; field of the&n; * swapper address space.&n; */
r_typedef
r_struct
(brace
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|typedef|swp_entry_t
)brace
id|swp_entry_t
suffix:semicolon
multiline_comment|/*&n; * Try to keep the most commonly accessed fields in single cache lines&n; * here (16 bytes or greater).  This ordering should be particularly&n; * beneficial on 32-bit processors.&n; *&n; * The first line is data used in page cache lookup, the second line&n; * is used for linear searches (eg. clock algorithm scans). &n; */
DECL|struct|page
r_typedef
r_struct
id|page
(brace
multiline_comment|/* these must be first (free area handling) */
DECL|member|list
r_struct
id|list_head
id|list
suffix:semicolon
DECL|member|mapping
r_struct
id|address_space
op_star
id|mapping
suffix:semicolon
DECL|member|pg_offset
r_int
r_int
id|pg_offset
suffix:semicolon
DECL|member|next_hash
r_struct
id|page
op_star
id|next_hash
suffix:semicolon
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* atomic flags, some possibly updated asynchronously */
DECL|member|lru
r_struct
id|list_head
id|lru
suffix:semicolon
DECL|member|wait
id|wait_queue_head_t
id|wait
suffix:semicolon
DECL|member|pprev_hash
r_struct
id|page
op_star
op_star
id|pprev_hash
suffix:semicolon
DECL|member|buffers
r_struct
id|buffer_head
op_star
id|buffers
suffix:semicolon
DECL|typedef|mem_map_t
)brace
id|mem_map_t
suffix:semicolon
DECL|macro|get_page
mdefine_line|#define get_page(p)&t;&t;atomic_inc(&amp;(p)-&gt;count)
DECL|macro|put_page
mdefine_line|#define put_page(p)&t;&t;__free_page(p)
DECL|macro|put_page_testzero
mdefine_line|#define put_page_testzero(p) &t;atomic_dec_and_test(&amp;(p)-&gt;count)
DECL|macro|page_count
mdefine_line|#define page_count(p)&t;&t;atomic_read(&amp;(p)-&gt;count)
DECL|macro|set_page_count
mdefine_line|#define set_page_count(p,v) &t;atomic_set(&amp;(p)-&gt;count, v)
multiline_comment|/* Page flag bit values */
DECL|macro|PG_locked
mdefine_line|#define PG_locked&t;&t; 0
DECL|macro|PG_error
mdefine_line|#define PG_error&t;&t; 1
DECL|macro|PG_referenced
mdefine_line|#define PG_referenced&t;&t; 2
DECL|macro|PG_uptodate
mdefine_line|#define PG_uptodate&t;&t; 3
DECL|macro|PG_decr_after
mdefine_line|#define PG_decr_after&t;&t; 5
DECL|macro|PG_DMA
mdefine_line|#define PG_DMA&t;&t;&t; 7
DECL|macro|PG_slab
mdefine_line|#define PG_slab&t;&t;&t; 8
DECL|macro|PG_swap_cache
mdefine_line|#define PG_swap_cache&t;&t; 9
DECL|macro|PG_skip
mdefine_line|#define PG_skip&t;&t;&t;10
DECL|macro|PG_swap_entry
mdefine_line|#define PG_swap_entry&t;&t;11
DECL|macro|PG_highmem
mdefine_line|#define PG_highmem&t;&t;12
multiline_comment|/* bits 21-30 unused */
DECL|macro|PG_reserved
mdefine_line|#define PG_reserved&t;&t;31
multiline_comment|/* Make it prettier to test the above... */
DECL|macro|Page_Uptodate
mdefine_line|#define Page_Uptodate(page)&t;test_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|SetPageUptodate
mdefine_line|#define SetPageUptodate(page)&t;set_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|ClearPageUptodate
mdefine_line|#define ClearPageUptodate(page)&t;clear_bit(PG_uptodate, &amp;(page)-&gt;flags)
DECL|macro|PageLocked
mdefine_line|#define PageLocked(page)&t;test_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|LockPage
mdefine_line|#define LockPage(page)&t;&t;set_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|TryLockPage
mdefine_line|#define TryLockPage(page)&t;test_and_set_bit(PG_locked, &amp;(page)-&gt;flags)
DECL|macro|UnlockPage
mdefine_line|#define UnlockPage(page)&t;do { &bslash;&n;&t;&t;&t;&t;&t;clear_bit(PG_locked, &amp;(page)-&gt;flags); &bslash;&n;&t;&t;&t;&t;&t;wake_up(&amp;page-&gt;wait); &bslash;&n;&t;&t;&t;&t;} while (0)
DECL|macro|PageError
mdefine_line|#define PageError(page)&t;&t;test_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|SetPageError
mdefine_line|#define SetPageError(page)&t;test_and_set_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|ClearPageError
mdefine_line|#define ClearPageError(page)&t;clear_bit(PG_error, &amp;(page)-&gt;flags)
DECL|macro|PageReferenced
mdefine_line|#define PageReferenced(page)&t;test_bit(PG_referenced, &amp;(page)-&gt;flags)
DECL|macro|PageDecrAfter
mdefine_line|#define PageDecrAfter(page)&t;test_bit(PG_decr_after, &amp;(page)-&gt;flags)
DECL|macro|PageDMA
mdefine_line|#define PageDMA(page)&t;&t;test_bit(PG_DMA, &amp;(page)-&gt;flags)
DECL|macro|PageSlab
mdefine_line|#define PageSlab(page)&t;&t;test_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|PageSwapCache
mdefine_line|#define PageSwapCache(page)&t;test_bit(PG_swap_cache, &amp;(page)-&gt;flags)
DECL|macro|PageReserved
mdefine_line|#define PageReserved(page)&t;test_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|PageSetSlab
mdefine_line|#define PageSetSlab(page)&t;set_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|PageSetSwapCache
mdefine_line|#define PageSetSwapCache(page)&t;set_bit(PG_swap_cache, &amp;(page)-&gt;flags)
DECL|macro|PageTestandSetSwapCache
mdefine_line|#define PageTestandSetSwapCache(page)&t;test_and_set_bit(PG_swap_cache, &amp;(page)-&gt;flags)
DECL|macro|PageClearSlab
mdefine_line|#define PageClearSlab(page)&t;&t;clear_bit(PG_slab, &amp;(page)-&gt;flags)
DECL|macro|PageClearSwapCache
mdefine_line|#define PageClearSwapCache(page)&t;clear_bit(PG_swap_cache, &amp;(page)-&gt;flags)
DECL|macro|PageTestandClearSwapCache
mdefine_line|#define PageTestandClearSwapCache(page)&t;test_and_clear_bit(PG_swap_cache, &amp;(page)-&gt;flags)
macro_line|#ifdef CONFIG_HIGHMEM
DECL|macro|PageHighMem
mdefine_line|#define PageHighMem(page)&t;&t;test_bit(PG_highmem, &amp;(page)-&gt;flags)
macro_line|#else
DECL|macro|PageHighMem
mdefine_line|#define PageHighMem(page)&t;&t;0 /* needed to optimize away at compile time */
macro_line|#endif
DECL|macro|SetPageReserved
mdefine_line|#define SetPageReserved(page)&t;&t;set_bit(PG_reserved, &amp;(page)-&gt;flags)
DECL|macro|ClearPageReserved
mdefine_line|#define ClearPageReserved(page)&t;&t;clear_bit(PG_reserved, &amp;(page)-&gt;flags)
multiline_comment|/*&n; * Various page-&gt;flags bits:&n; *&n; * PG_reserved is set for a page which must never be accessed (which&n; * may not even be present).&n; *&n; * PG_DMA is set for those pages which lie in the range of&n; * physical addresses capable of carrying DMA transfers.&n; *&n; * Multiple processes may &quot;see&quot; the same page. E.g. for untouched&n; * mappings of /dev/null, all processes see the same page full of&n; * zeroes, and text pages of executables and shared libraries have&n; * only one copy in memory, at most, normally.&n; *&n; * For the non-reserved pages, page-&gt;count denotes a reference count.&n; *   page-&gt;count == 0 means the page is free.&n; *   page-&gt;count == 1 means the page is used for exactly one purpose&n; *   (e.g. a private data page of one process).&n; *&n; * A page may be used for kmalloc() or anyone else who does a&n; * __get_free_page(). In this case the page-&gt;count is at least 1, and&n; * all other fields are unused but should be 0 or NULL. The&n; * management of this page is the responsibility of the one who uses&n; * it.&n; *&n; * The other pages (we may call them &quot;process pages&quot;) are completely&n; * managed by the Linux memory manager: I/O, buffers, swapping etc.&n; * The following discussion applies only to them.&n; *&n; * A page may belong to an inode&squot;s memory mapping. In this case,&n; * page-&gt;inode is the pointer to the inode, and page-&gt;offset is the&n; * file offset of the page (not necessarily a multiple of PAGE_SIZE).&n; *&n; * A page may have buffers allocated to it. In this case,&n; * page-&gt;buffers is a circular list of these buffer heads. Else,&n; * page-&gt;buffers == NULL.&n; *&n; * For pages belonging to inodes, the page-&gt;count is the number of&n; * attaches, plus 1 if buffers are allocated to the page.&n; *&n; * All pages belonging to an inode make up a doubly linked list&n; * inode-&gt;i_pages, using the fields page-&gt;next and page-&gt;prev. (These&n; * fields are also used for freelist management when page-&gt;count==0.)&n; * There is also a hash table mapping (inode,offset) to the page&n; * in memory if present. The lists for this hash table use the fields&n; * page-&gt;next_hash and page-&gt;pprev_hash.&n; *&n; * All process pages can do I/O:&n; * - inode pages may need to be read from disk,&n; * - inode pages which have been modified and are MAP_SHARED may need&n; *   to be written to disk,&n; * - private pages which have been modified may need to be swapped out&n; *   to swap space and (later) to be read back into memory.&n; * During disk I/O, PG_locked is used. This bit is set before I/O&n; * and reset when I/O completes. page-&gt;wait is a wait queue of all&n; * tasks waiting for the I/O on this page to complete.&n; * PG_uptodate tells whether the page&squot;s contents is valid.&n; * When a read completes, the page becomes uptodate, unless a disk I/O&n; * error happened.&n; *&n; * For choosing which pages to swap out, inode pages carry a&n; * PG_referenced bit, which is set any time the system accesses&n; * that page through the (inode,offset) hash table.&n; *&n; * PG_skip is used on sparc/sparc64 architectures to &quot;skip&quot; certain&n; * parts of the address space.&n; *&n; * PG_error is set to indicate that an I/O error occurred on this page.&n; */
r_extern
id|mem_map_t
op_star
id|mem_map
suffix:semicolon
multiline_comment|/*&n; * This is timing-critical - most of the time in getting a new page&n; * goes to clearing the page. If you want a page without the clearing&n; * overhead, just use __get_free_page() directly..&n; */
r_extern
r_struct
id|page
op_star
id|__get_pages
c_func
(paren
r_int
id|gfp_mask
comma
r_int
r_int
id|order
)paren
suffix:semicolon
DECL|macro|__get_free_page
mdefine_line|#define __get_free_page(gfp_mask) __get_free_pages((gfp_mask),0)
DECL|macro|__get_dma_pages
mdefine_line|#define __get_dma_pages(gfp_mask, order) __get_free_pages((gfp_mask) | GFP_DMA,(order))
r_extern
r_int
r_int
id|FASTCALL
c_func
(paren
id|__get_free_pages
c_func
(paren
r_int
id|gfp_mask
comma
r_int
r_int
id|gfp_order
)paren
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|get_free_highpage
c_func
(paren
r_int
id|gfp_mask
)paren
suffix:semicolon
DECL|function|get_zeroed_page
r_extern
r_inline
r_int
r_int
id|get_zeroed_page
c_func
(paren
r_int
id|gfp_mask
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|page
op_assign
id|__get_free_page
c_func
(paren
id|gfp_mask
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
id|clear_page
c_func
(paren
(paren
r_void
op_star
)paren
id|page
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/*&n; * The old interface name will be removed in 2.5:&n; */
DECL|macro|get_free_page
mdefine_line|#define get_free_page get_zeroed_page
multiline_comment|/* memory.c &amp; swap.c*/
DECL|macro|free_page
mdefine_line|#define free_page(addr) free_pages((addr),0)
r_extern
r_int
id|FASTCALL
c_func
(paren
id|free_pages
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|order
)paren
)paren
suffix:semicolon
r_extern
r_int
id|FASTCALL
c_func
(paren
id|__free_page
c_func
(paren
r_struct
id|page
op_star
)paren
)paren
suffix:semicolon
r_extern
r_void
id|show_free_areas
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|put_dirty_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|clear_page_tables
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|zap_page_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|copy_page_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|dst
comma
r_struct
id|mm_struct
op_star
id|src
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
suffix:semicolon
r_extern
r_int
id|remap_page_range
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_int
id|zeromap_page_range
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|size
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_extern
r_void
id|vmtruncate
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_int
r_int
id|offset
)paren
suffix:semicolon
r_extern
r_int
id|handle_mm_fault
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
r_int
id|write_access
)paren
suffix:semicolon
r_extern
r_int
id|make_pages_present
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_int
id|access_process_vm
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_readdata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|ptrace_writedata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_char
op_star
id|src
comma
r_int
r_int
id|dst
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|pgt_cache_water
(braket
l_int|2
)braket
suffix:semicolon
r_extern
r_int
id|check_pgt_cache
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_area_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mem_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|show_mem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|oom
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_void
id|si_meminfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
suffix:semicolon
r_extern
r_void
id|swapin_readahead
c_func
(paren
id|swp_entry_t
)paren
suffix:semicolon
multiline_comment|/* mmap.c */
r_extern
r_void
id|vma_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|merge_segments
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|insert_vm_struct
c_func
(paren
r_struct
id|mm_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|build_mmap_avl
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|exit_mmap
c_func
(paren
r_struct
id|mm_struct
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|get_unmapped_area
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_mmap
c_func
(paren
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|do_munmap
c_func
(paren
r_int
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|do_brk
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/* filemap.c */
r_extern
r_void
id|remove_inode_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|page_unuse
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
r_extern
r_int
id|shrink_mmap
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|truncate_inode_pages
c_func
(paren
r_struct
id|inode
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|put_cached_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * GFP bitmasks..&n; */
DECL|macro|__GFP_WAIT
mdefine_line|#define __GFP_WAIT&t;0x01
DECL|macro|__GFP_LOW
mdefine_line|#define __GFP_LOW&t;0x02
DECL|macro|__GFP_MED
mdefine_line|#define __GFP_MED&t;0x04
DECL|macro|__GFP_HIGH
mdefine_line|#define __GFP_HIGH&t;0x08
DECL|macro|__GFP_IO
mdefine_line|#define __GFP_IO&t;0x10
DECL|macro|__GFP_SWAP
mdefine_line|#define __GFP_SWAP&t;0x20
macro_line|#ifdef CONFIG_HIGHMEM
DECL|macro|__GFP_HIGHMEM
mdefine_line|#define __GFP_HIGHMEM&t;0x40
macro_line|#else
DECL|macro|__GFP_HIGHMEM
mdefine_line|#define __GFP_HIGHMEM&t;0x0 /* noop */
macro_line|#endif
DECL|macro|__GFP_DMA
mdefine_line|#define __GFP_DMA&t;0x80
DECL|macro|GFP_BUFFER
mdefine_line|#define GFP_BUFFER&t;(__GFP_LOW | __GFP_WAIT)
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;(__GFP_HIGH)
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;(__GFP_LOW | __GFP_WAIT | __GFP_IO)
DECL|macro|GFP_HIGHUSER
mdefine_line|#define GFP_HIGHUSER&t;(GFP_USER | __GFP_HIGHMEM)
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;(__GFP_MED | __GFP_WAIT | __GFP_IO)
DECL|macro|GFP_NFS
mdefine_line|#define GFP_NFS&t;&t;(__GFP_HIGH | __GFP_WAIT | __GFP_IO)
DECL|macro|GFP_KSWAPD
mdefine_line|#define GFP_KSWAPD&t;(__GFP_IO | __GFP_SWAP)
multiline_comment|/* Flag - indicates that the buffer will be suitable for DMA.  Ignored on some&n;   platforms, used as appropriate on others */
DECL|macro|GFP_DMA
mdefine_line|#define GFP_DMA&t;&t;__GFP_DMA
multiline_comment|/* Flag - indicates that the buffer can be taken from high memory which is not&n;   directly addressable by the kernel */
DECL|macro|GFP_HIGHMEM
mdefine_line|#define GFP_HIGHMEM&t;__GFP_HIGHMEM
multiline_comment|/* vma is the first one with  address &lt; vma-&gt;vm_end,&n; * and even  address &lt; vma-&gt;vm_start. Have to extend vma. */
DECL|function|expand_stack
r_static
r_inline
r_int
id|expand_stack
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
)paren
(brace
r_int
r_int
id|grow
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|grow
op_assign
(paren
id|vma-&gt;vm_start
op_minus
id|address
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_minus
id|address
OG
id|current-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
op_logical_or
(paren
(paren
id|vma-&gt;vm_mm-&gt;total_vm
op_plus
id|grow
)paren
op_lshift
id|PAGE_SHIFT
)paren
OG
id|current-&gt;rlim
(braket
id|RLIMIT_AS
)braket
dot
id|rlim_cur
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|address
suffix:semicolon
id|vma-&gt;vm_pgoff
op_sub_assign
id|grow
suffix:semicolon
id|vma-&gt;vm_mm-&gt;total_vm
op_add_assign
id|grow
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_LOCKED
)paren
id|vma-&gt;vm_mm-&gt;locked_vm
op_add_assign
id|grow
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Look up the first VMA which satisfies  addr &lt; vm_end,  NULL if none. */
r_extern
r_struct
id|vm_area_struct
op_star
id|find_vma
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/* Look up the first VMA which intersects the interval start_addr..end_addr-1,&n;   NULL if none.  Assume start_addr &lt; end_addr. */
DECL|function|find_vma_intersection
r_static
r_inline
r_struct
id|vm_area_struct
op_star
id|find_vma_intersection
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start_addr
comma
r_int
r_int
id|end_addr
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|start_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_logical_and
id|end_addr
op_le
id|vma-&gt;vm_start
)paren
id|vma
op_assign
l_int|NULL
suffix:semicolon
r_return
id|vma
suffix:semicolon
)brace
r_extern
r_struct
id|vm_area_struct
op_star
id|find_extend_vma
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|buffer_under_min
mdefine_line|#define buffer_under_min()&t;(atomic_read(&amp;buffermem_pages) * 100 &lt; &bslash;&n;&t;&t;&t;&t;buffer_mem.min_percent * num_physpages)
DECL|macro|pgcache_under_min
mdefine_line|#define pgcache_under_min()&t;(atomic_read(&amp;page_cache_size) * 100 &lt; &bslash;&n;&t;&t;&t;&t;page_cache.min_percent * num_physpages)
DECL|macro|vmlist_access_lock
mdefine_line|#define vmlist_access_lock(mm)&t;&t;spin_lock(&amp;mm-&gt;page_table_lock)
DECL|macro|vmlist_access_unlock
mdefine_line|#define vmlist_access_unlock(mm)&t;spin_unlock(&amp;mm-&gt;page_table_lock)
DECL|macro|vmlist_modify_lock
mdefine_line|#define vmlist_modify_lock(mm)&t;&t;vmlist_access_lock(mm)
DECL|macro|vmlist_modify_unlock
mdefine_line|#define vmlist_modify_unlock(mm)&t;vmlist_access_unlock(mm)
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
