macro_line|#ifndef _LINUX_MM_H
DECL|macro|_LINUX_MM_H
mdefine_line|#define _LINUX_MM_H
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
r_extern
r_int
r_int
id|high_memory
suffix:semicolon
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#ifdef __KERNEL__
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
r_extern
r_int
id|verify_area
c_func
(paren
r_int
comma
r_const
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
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
multiline_comment|/* linked list of VM areas per task, sorted by address */
DECL|member|vm_next
r_struct
id|vm_area_struct
op_star
id|vm_next
suffix:semicolon
multiline_comment|/* for areas with inode, the circular list inode-&gt;i_mmap */
multiline_comment|/* for shm areas, the circular list of attaches */
multiline_comment|/* otherwise unused */
DECL|member|vm_next_share
r_struct
id|vm_area_struct
op_star
id|vm_next_share
suffix:semicolon
DECL|member|vm_prev_share
r_struct
id|vm_area_struct
op_star
id|vm_prev_share
suffix:semicolon
multiline_comment|/* more */
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
DECL|member|vm_offset
r_int
r_int
id|vm_offset
suffix:semicolon
DECL|member|vm_inode
r_struct
id|inode
op_star
id|vm_inode
suffix:semicolon
DECL|member|vm_pte
r_int
r_int
id|vm_pte
suffix:semicolon
multiline_comment|/* shared mem */
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
r_int
r_int
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
r_int
r_int
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
r_int
r_int
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
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
op_star
)paren
suffix:semicolon
DECL|member|swapin
id|pte_t
(paren
op_star
id|swapin
)paren
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Try to keep the most commonly accessed fields in single cache lines&n; * here (16 bytes or greater).  This ordering should be particularly&n; * beneficial on 32-bit processors.&n; *&n; * The first line is data used in linear searches (eg. clock algorithm&n; * scans).  The second line is data used in page searches through the&n; * page-cache.  -- sct &n; */
DECL|struct|page
r_typedef
r_struct
id|page
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|dirty
r_int
id|dirty
suffix:colon
l_int|16
comma
DECL|member|age
id|age
suffix:colon
l_int|8
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
multiline_comment|/* atomic flags, some possibly updated asynchronously */
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
DECL|member|next
r_struct
id|page
op_star
id|next
suffix:semicolon
DECL|member|next_hash
r_struct
id|page
op_star
id|next_hash
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|prev
r_struct
id|page
op_star
id|prev
suffix:semicolon
DECL|member|prev_hash
r_struct
id|page
op_star
id|prev_hash
suffix:semicolon
DECL|member|buffers
r_struct
id|buffer_head
op_star
id|buffers
suffix:semicolon
DECL|member|swap_unlock_entry
r_int
r_int
id|swap_unlock_entry
suffix:semicolon
DECL|member|map_nr
r_int
r_int
id|map_nr
suffix:semicolon
multiline_comment|/* page-&gt;map_nr == page - mem_map */
DECL|typedef|mem_map_t
)brace
id|mem_map_t
suffix:semicolon
multiline_comment|/* Page flag bit values */
DECL|macro|PG_locked
mdefine_line|#define PG_locked&t;&t; 0
DECL|macro|PG_error
mdefine_line|#define PG_error&t;&t; 1
DECL|macro|PG_referenced
mdefine_line|#define PG_referenced&t;&t; 2
DECL|macro|PG_uptodate
mdefine_line|#define PG_uptodate&t;&t; 3
DECL|macro|PG_free_after
mdefine_line|#define PG_free_after&t;&t; 4
DECL|macro|PG_decr_after
mdefine_line|#define PG_decr_after&t;&t; 5
DECL|macro|PG_swap_unlock_after
mdefine_line|#define PG_swap_unlock_after&t; 6
DECL|macro|PG_DMA
mdefine_line|#define PG_DMA&t;&t;&t; 7
DECL|macro|PG_reserved
mdefine_line|#define PG_reserved&t;&t;31
multiline_comment|/* Make it prettier to test the above... */
DECL|macro|PageLocked
mdefine_line|#define PageLocked(page)&t;(test_bit(PG_locked, &amp;(page)-&gt;flags))
DECL|macro|PageError
mdefine_line|#define PageError(page)&t;&t;(test_bit(PG_error, &amp;(page)-&gt;flags))
DECL|macro|PageReferenced
mdefine_line|#define PageReferenced(page)&t;(test_bit(PG_referenced, &amp;(page)-&gt;flags))
DECL|macro|PageDirty
mdefine_line|#define PageDirty(page)&t;&t;(test_bit(PG_dirty, &amp;(page)-&gt;flags))
DECL|macro|PageUptodate
mdefine_line|#define PageUptodate(page)&t;(test_bit(PG_uptodate, &amp;(page)-&gt;flags))
DECL|macro|PageFreeAfter
mdefine_line|#define PageFreeAfter(page)&t;(test_bit(PG_free_after, &amp;(page)-&gt;flags))
DECL|macro|PageDecrAfter
mdefine_line|#define PageDecrAfter(page)&t;(test_bit(PG_decr_after, &amp;(page)-&gt;flags))
DECL|macro|PageSwapUnlockAfter
mdefine_line|#define PageSwapUnlockAfter(page) (test_bit(PG_swap_unlock_after, &amp;(page)-&gt;flags))
DECL|macro|PageDMA
mdefine_line|#define PageDMA(page)&t;&t;(test_bit(PG_DMA, &amp;(page)-&gt;flags))
DECL|macro|PageReserved
mdefine_line|#define PageReserved(page)&t;(test_bit(PG_reserved, &amp;(page)-&gt;flags))
multiline_comment|/*&n; * page-&gt;reserved denotes a page which must never be accessed (which&n; * may not even be present).&n; *&n; * page-&gt;dma is set for those pages which lie in the range of&n; * physical addresses capable of carrying DMA transfers.&n; *&n; * Multiple processes may &quot;see&quot; the same page. E.g. for untouched&n; * mappings of /dev/null, all processes see the same page full of&n; * zeroes, and text pages of executables and shared libraries have&n; * only one copy in memory, at most, normally.&n; *&n; * For the non-reserved pages, page-&gt;count denotes a reference count.&n; *   page-&gt;count == 0 means the page is free.&n; *   page-&gt;count == 1 means the page is used for exactly one purpose&n; *   (e.g. a private data page of one process).&n; *&n; * A page may be used for kmalloc() or anyone else who does a&n; * get_free_page(). In this case the page-&gt;count is at least 1, and&n; * all other fields are unused but should be 0 or NULL. The&n; * managament of this page is the responsibility of the one who uses&n; * it.&n; *&n; * The other pages (we may call them &quot;process pages&quot;) are completely&n; * managed by the Linux memory manager: I/O, buffers, swapping etc.&n; * The following discussion applies only to them.&n; *&n; * A page may belong to an inode&squot;s memory mapping. In this case,&n; * page-&gt;inode is the inode, and page-&gt;offset is the file offset&n; * of the page (not necessarily a multiple of PAGE_SIZE).&n; *&n; * A page may have buffers allocated to it. In this case,&n; * page-&gt;buffers is a circular list of these buffer heads. Else,&n; * page-&gt;buffers == NULL.&n; *&n; * For pages belonging to inodes, the page-&gt;count is the number of&n; * attaches, plus 1 if buffers are allocated to the page.&n; *&n; * All pages belonging to an inode make up a doubly linked list&n; * inode-&gt;i_pages, using the fields page-&gt;next and page-&gt;prev. (These&n; * fields are also used for freelist management when page-&gt;count==0.)&n; * There is also a hash table mapping (inode,offset) to the page&n; * in memory if present. The lists for this hash table use the fields&n; * page-&gt;next_hash and page-&gt;prev_hash.&n; *&n; * All process pages can do I/O:&n; * - inode pages may need to be read from disk,&n; * - inode pages which have been modified and are MAP_SHARED may need&n; *   to be written to disk,&n; * - private pages which have been modified may need to be swapped out&n; *   to swap space and (later) to be read back into memory.&n; * During disk I/O, page-&gt;locked is true. This bit is set before I/O&n; * and reset when I/O completes. page-&gt;wait is a wait queue of all&n; * tasks waiting for the I/O on this page to complete.&n; * page-&gt;uptodate tells whether the page&squot;s contents is valid.&n; * When a read completes, the page becomes uptodate, unless a disk I/O&n; * error happened.&n; * When a write completes, and page-&gt;free_after is true, the page is&n; * freed without any further delay.&n; *&n; * For choosing which pages to swap out, inode pages carry a&n; * page-&gt;referenced bit, which is set any time the system accesses&n; * that page through the (inode,offset) hash table.&n; * There is also the page-&gt;age counter, which implements a linear&n; * decay (why not an exponential decay?), see swapctl.h.&n; */
r_extern
id|mem_map_t
op_star
id|mem_map
suffix:semicolon
multiline_comment|/*&n; * This is timing-critical - most of the time in getting a new page&n; * goes to clearing the page. If you want a page without the clearing&n; * overhead, just use __get_free_page() directly..&n; */
DECL|macro|__get_free_page
mdefine_line|#define __get_free_page(priority) __get_free_pages((priority),0,0)
DECL|macro|__get_dma_pages
mdefine_line|#define __get_dma_pages(priority, order) __get_free_pages((priority),(order),1)
r_extern
r_int
r_int
id|__get_free_pages
c_func
(paren
r_int
id|priority
comma
r_int
r_int
id|gfporder
comma
r_int
id|dma
)paren
suffix:semicolon
DECL|function|get_free_page
r_extern
r_inline
r_int
r_int
id|get_free_page
c_func
(paren
r_int
id|priority
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
id|priority
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/* memory.c &amp; swap.c*/
DECL|macro|free_page
mdefine_line|#define free_page(addr) free_pages((addr),0)
r_extern
r_void
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
r_int
r_int
id|put_dirty_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|page
comma
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_void
id|free_page_tables
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
id|clear_page_tables
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|new_page_tables
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
suffix:semicolon
r_extern
r_int
id|copy_page_tables
c_func
(paren
r_struct
id|task_struct
op_star
id|to
)paren
suffix:semicolon
r_extern
r_int
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
r_void
id|handle_mm_fault
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
comma
r_int
id|write_access
)paren
suffix:semicolon
r_extern
r_void
id|do_wp_page
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
r_void
id|do_no_page
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
r_int
id|paging_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
)paren
suffix:semicolon
r_extern
r_void
id|mem_init
c_func
(paren
r_int
r_int
id|start_mem
comma
r_int
r_int
id|end_mem
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
multiline_comment|/* vmalloc.c */
r_extern
r_void
op_star
id|vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
op_star
id|vremap
c_func
(paren
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|vfree
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|vread
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
id|addr
comma
r_int
id|count
)paren
suffix:semicolon
multiline_comment|/* mmap.c */
r_extern
r_int
r_int
id|do_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|addr
comma
r_int
r_int
id|len
comma
r_int
r_int
id|prot
comma
r_int
r_int
id|flags
comma
r_int
r_int
id|off
)paren
suffix:semicolon
r_extern
r_void
id|merge_segments
c_func
(paren
r_struct
id|task_struct
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
id|task_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|remove_shared_vm_struct
c_func
(paren
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
multiline_comment|/* filemap.c */
r_extern
r_int
r_int
id|page_unuse
c_func
(paren
r_int
r_int
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
DECL|macro|GFP_BUFFER
mdefine_line|#define GFP_BUFFER&t;0x00
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;0x01
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;0x02
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;0x03
DECL|macro|GFP_NOBUFFER
mdefine_line|#define GFP_NOBUFFER&t;0x04
DECL|macro|GFP_NFS
mdefine_line|#define GFP_NFS&t;&t;0x05
multiline_comment|/* Flag - indicates that the buffer will be suitable for DMA.  Ignored on some&n;   platforms, used as appropriate on others */
DECL|macro|GFP_DMA
mdefine_line|#define GFP_DMA&t;&t;0x80
DECL|macro|GFP_LEVEL_MASK
mdefine_line|#define GFP_LEVEL_MASK 0xf
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
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|grow
op_assign
id|vma-&gt;vm_start
op_minus
id|address
suffix:semicolon
id|vma-&gt;vm_start
op_assign
id|address
suffix:semicolon
id|vma-&gt;vm_offset
op_sub_assign
id|grow
suffix:semicolon
id|vma-&gt;vm_mm-&gt;total_vm
op_add_assign
id|grow
op_rshift
id|PAGE_SHIFT
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
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|avl_empty
mdefine_line|#define avl_empty&t;(struct vm_area_struct *) NULL
multiline_comment|/* Look up the first VMA which satisfies  addr &lt; vm_end,  NULL if none. */
DECL|function|find_vma
r_static
r_inline
r_struct
id|vm_area_struct
op_star
id|find_vma
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|addr
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|result
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|task-&gt;mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|tree
op_assign
id|task-&gt;mm-&gt;mmap_avl
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|tree
op_eq
id|avl_empty
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tree-&gt;vm_end
OG
id|addr
)paren
(brace
id|result
op_assign
id|tree
suffix:semicolon
r_if
c_cond
(paren
id|tree-&gt;vm_start
op_le
id|addr
)paren
r_break
suffix:semicolon
id|tree
op_assign
id|tree-&gt;vm_avl_left
suffix:semicolon
)brace
r_else
id|tree
op_assign
id|tree-&gt;vm_avl_right
suffix:semicolon
)brace
)brace
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* Look up the first VMA which intersects the interval start_addr..end_addr-1,&n;   NULL if none.  Assume start_addr &lt; end_addr. */
DECL|function|find_vma_intersection
r_static
r_inline
r_struct
id|vm_area_struct
op_star
id|find_vma_intersection
(paren
r_struct
id|task_struct
op_star
id|task
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
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|task
comma
id|start_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
id|end_addr
op_le
id|vma-&gt;vm_start
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|vma
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
