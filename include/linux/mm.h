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
mdefine_line|#define VM_SHM&t;&t;0x0400
DECL|macro|VM_DENYWRITE
mdefine_line|#define VM_DENYWRITE&t;0x0800&t;/* ETXTBSY on write attempts.. */
DECL|macro|VM_EXECUTABLE
mdefine_line|#define VM_EXECUTABLE&t;0x1000
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
r_int
id|page
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
r_extern
id|mem_map_t
op_star
id|mem_map
suffix:semicolon
multiline_comment|/* planning stage.. */
DECL|macro|P_DIRTY
mdefine_line|#define P_DIRTY&t;&t;0x0001
DECL|macro|P_LOCKED
mdefine_line|#define P_LOCKED&t;0x0002
DECL|macro|P_UPTODATE
mdefine_line|#define P_UPTODATE&t;0x0004
DECL|macro|P_RESERVED
mdefine_line|#define P_RESERVED&t;0x8000
DECL|struct|page_info
r_struct
id|page_info
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
DECL|member|inode
r_struct
id|inode
op_star
id|inode
suffix:semicolon
DECL|member|offset
r_int
r_int
id|offset
suffix:semicolon
DECL|member|next_same_inode
r_struct
id|page_info
op_star
id|next_same_inode
suffix:semicolon
DECL|member|prev_same_inode
r_struct
id|page_info
op_star
id|prev_same_inode
suffix:semicolon
DECL|member|next_hash
r_struct
id|page_info
op_star
id|next_hash
suffix:semicolon
DECL|member|prev_hash
r_struct
id|page_info
op_star
id|prev_hash
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* end of planning stage */
multiline_comment|/*&n; * Free area management&n; */
r_extern
r_int
id|nr_swap_pages
suffix:semicolon
r_extern
r_int
id|nr_free_pages
suffix:semicolon
r_extern
r_int
id|min_free_pages
suffix:semicolon
DECL|macro|NR_MEM_LISTS
mdefine_line|#define NR_MEM_LISTS 6
DECL|struct|mem_list
r_struct
id|mem_list
(brace
DECL|member|next
r_struct
id|mem_list
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|mem_list
op_star
id|prev
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|mem_list
id|free_area_list
(braket
id|NR_MEM_LISTS
)braket
suffix:semicolon
r_extern
r_int
r_char
op_star
id|free_area_map
(braket
id|NR_MEM_LISTS
)braket
suffix:semicolon
multiline_comment|/*&n; * This is timing-critical - most of the time in getting a new page&n; * goes to clearing the page. If you want a page without the clearing&n; * overhead, just use __get_free_page() directly..&n; */
DECL|macro|__get_free_page
mdefine_line|#define __get_free_page(priority) __get_free_pages((priority),0,~0UL)
DECL|macro|__get_dma_pages
mdefine_line|#define __get_dma_pages(priority, order) __get_free_pages((priority),(order),MAX_DMA_ADDRESS)
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
r_int
id|max_addr
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
id|clone_page_tables
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
id|unmap_page_range
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|size
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
multiline_comment|/* swap.c */
r_extern
r_void
id|swap_free
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|swap_duplicate
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|swap_in
c_func
(paren
r_struct
id|task_struct
op_star
comma
r_struct
id|vm_area_struct
op_star
comma
id|pte_t
op_star
comma
r_int
r_int
id|id
comma
r_int
id|write_access
)paren
suffix:semicolon
r_extern
r_void
id|si_swapinfo
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
id|rw_swap_page
c_func
(paren
r_int
id|rw
comma
r_int
r_int
id|nr
comma
r_char
op_star
id|buf
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
r_struct
id|vm_area_struct
op_star
id|find_vma
(paren
r_struct
id|task_struct
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_struct
id|vm_area_struct
op_star
id|find_vma_intersection
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
DECL|macro|read_swap_page
mdefine_line|#define read_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(READ,(nr),(buf))
DECL|macro|write_swap_page
mdefine_line|#define write_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(WRITE,(nr),(buf))
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
multiline_comment|/*&n; * vm_ops not present page codes for shared memory.&n; *&n; * Will go away eventually..&n; */
DECL|macro|SHM_SWP_TYPE
mdefine_line|#define SHM_SWP_TYPE 0x40
r_extern
r_void
id|shm_no_page
(paren
id|ulong
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * swap cache stuff (in swap.c)&n; */
DECL|macro|SWAP_CACHE_INFO
mdefine_line|#define SWAP_CACHE_INFO
r_extern
r_int
r_int
op_star
id|swap_cache
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
r_extern
r_int
r_int
id|swap_cache_add_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_add_success
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_del_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_del_success
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_total
suffix:semicolon
r_extern
r_int
r_int
id|swap_cache_find_success
suffix:semicolon
macro_line|#endif
DECL|function|in_swap_cache
r_extern
r_inline
r_int
r_int
id|in_swap_cache
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|swap_cache
(braket
id|MAP_NR
c_func
(paren
id|addr
)paren
)braket
suffix:semicolon
)brace
DECL|function|find_in_swap_cache
r_extern
r_inline
r_int
id|find_in_swap_cache
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_find_total
op_increment
suffix:semicolon
macro_line|#endif
id|entry
op_assign
id|xchg
c_func
(paren
id|swap_cache
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
r_if
c_cond
(paren
id|entry
)paren
id|swap_cache_find_success
op_increment
suffix:semicolon
macro_line|#endif&t;
r_return
id|entry
suffix:semicolon
)brace
DECL|function|delete_from_swap_cache
r_extern
r_inline
r_int
id|delete_from_swap_cache
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_int
r_int
id|entry
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_del_total
op_increment
suffix:semicolon
macro_line|#endif&t;
id|entry
op_assign
id|xchg
c_func
(paren
id|swap_cache
op_plus
id|MAP_NR
c_func
(paren
id|addr
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry
)paren
(brace
macro_line|#ifdef SWAP_CACHE_INFO
id|swap_cache_del_success
op_increment
suffix:semicolon
macro_line|#endif
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
