macro_line|#ifndef _LINUX_MM_H
DECL|macro|_LINUX_MM_H
mdefine_line|#define _LINUX_MM_H
macro_line|#include &lt;linux/page.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
DECL|macro|VERIFY_READ
mdefine_line|#define VERIFY_READ 0
DECL|macro|VERIFY_WRITE
mdefine_line|#define VERIFY_WRITE 1
r_int
id|__verify_write
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|count
)paren
suffix:semicolon
DECL|function|verify_area
r_extern
r_inline
r_int
id|verify_area
c_func
(paren
r_int
id|type
comma
r_void
op_star
id|addr
comma
r_int
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|TASK_SIZE
op_le
(paren
r_int
r_int
)paren
id|addr
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|TASK_SIZE
op_minus
(paren
r_int
r_int
)paren
id|addr
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|wp_works_ok
op_logical_or
id|type
op_eq
id|VERIFY_READ
op_logical_or
op_logical_neg
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|__verify_write
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Linux kernel virtual memory manager primitives.&n; * The idea being to have a &quot;virtual&quot; mm in the same way&n; * we have a virtual fs - giving a cleaner interface to the&n; * mm details, and allowing different kinds of memory mappings&n; * (from shared memory to executable loading to arbitrary&n; * mmap() functions).&n; */
multiline_comment|/*&n; * This struct defines a memory VMM memory area. There is one of these&n; * per VM-area/task.  A VM area is any part of the process virtual memory&n; * space that has a special rule for the page-fault handlers (ie a shared&n; * library, the executable area etc).&n; */
DECL|struct|vm_area_struct
r_struct
id|vm_area_struct
(brace
DECL|member|vm_task
r_struct
id|task_struct
op_star
id|vm_task
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
r_int
r_int
id|vm_page_prot
suffix:semicolon
DECL|member|vm_next
r_struct
id|vm_area_struct
op_star
id|vm_next
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|vm_share
r_struct
id|vm_area_struct
op_star
id|vm_share
suffix:semicolon
multiline_comment|/* linked list */
DECL|member|vm_inode
r_struct
id|inode
op_star
id|vm_inode
suffix:semicolon
DECL|member|vm_offset
r_int
r_int
id|vm_offset
suffix:semicolon
DECL|member|vm_ops
r_struct
id|vm_operations_struct
op_star
id|vm_ops
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * These are the virtual MM functions - opening of an area, closing it (needed to&n; * keep files on disk up-to-date etc), pointer to the functions called when a&n; * no-page or a wp-page exception occurs, and the function which decides on sharing&n; * of pages between different processes.&n; */
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
DECL|member|nopage
r_void
(paren
op_star
id|nopage
)paren
(paren
r_int
id|error_code
comma
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|member|wppage
r_void
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
)paren
suffix:semicolon
DECL|member|share
r_int
(paren
op_star
id|share
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|from
comma
r_struct
id|vm_area_struct
op_star
id|to
comma
r_int
r_int
id|address
)paren
suffix:semicolon
DECL|member|unmap
r_int
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
)brace
suffix:semicolon
r_extern
r_int
r_int
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|__zero_page
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE __zero_page()
r_extern
r_volatile
r_int
id|free_page_ptr
suffix:semicolon
multiline_comment|/* used by malloc and tcp/ip. */
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
r_int
id|free_page_list
suffix:semicolon
r_extern
r_int
id|nr_secondary_pages
suffix:semicolon
r_extern
r_int
r_int
id|secondary_page_list
suffix:semicolon
DECL|macro|MAX_SECONDARY_PAGES
mdefine_line|#define MAX_SECONDARY_PAGES 20
multiline_comment|/*&n; * This is timing-critical - most of the time in getting a new page&n; * goes to clearing the page. If you want a page without the clearing&n; * overhead, just use __get_free_page() directly..&n; */
r_extern
r_int
r_int
id|__get_free_page
c_func
(paren
r_int
id|priority
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
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rep ; stosl&quot;
suffix:colon
multiline_comment|/* no outputs */
"&bslash;"
suffix:colon
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|1024
)paren
comma
l_string|&quot;D&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;di&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
multiline_comment|/* memory.c */
r_extern
r_void
id|free_page
c_func
(paren
r_int
r_int
id|addr
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
r_int
id|mask
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
r_int
id|mask
)paren
suffix:semicolon
r_extern
r_void
id|do_wp_page
c_func
(paren
r_int
r_int
id|error_code
comma
r_int
r_int
id|address
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|user_esp
)paren
suffix:semicolon
r_extern
r_void
id|do_no_page
c_func
(paren
r_int
r_int
id|error_code
comma
r_int
r_int
id|address
comma
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|user_esp
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
id|low_start_mem
comma
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
id|task
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
id|page_nr
)paren
suffix:semicolon
r_extern
r_int
r_int
id|swap_duplicate
c_func
(paren
r_int
r_int
id|page_nr
)paren
suffix:semicolon
r_extern
r_void
id|swap_in
c_func
(paren
r_int
r_int
op_star
id|table_ptr
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
DECL|typedef|map_mergep_fnp
r_typedef
r_int
(paren
op_star
id|map_mergep_fnp
)paren
(paren
r_const
r_struct
id|vm_area_struct
op_star
comma
r_const
r_struct
id|vm_area_struct
op_star
comma
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|merge_segments
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
id|map_mergep_fnp
comma
r_void
op_star
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
r_int
id|ignoff_mergep
c_func
(paren
r_const
r_struct
id|vm_area_struct
op_star
comma
r_const
r_struct
id|vm_area_struct
op_star
comma
r_void
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
DECL|macro|read_swap_page
mdefine_line|#define read_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(READ,(nr),(buf))
DECL|macro|write_swap_page
mdefine_line|#define write_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(WRITE,(nr),(buf))
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__(&quot;movl %%cr3,%%eax&bslash;n&bslash;tmovl %%eax,%%cr3&quot;: : :&quot;ax&quot;)
r_extern
r_int
r_int
id|high_memory
suffix:semicolon
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) ((addr) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_PAGE_RESERVED
mdefine_line|#define MAP_PAGE_RESERVED (1&lt;&lt;15)
r_extern
r_int
r_int
op_star
id|mem_map
suffix:semicolon
DECL|macro|PAGE_PRESENT
mdefine_line|#define PAGE_PRESENT&t;0x001
DECL|macro|PAGE_RW
mdefine_line|#define PAGE_RW&t;&t;0x002
DECL|macro|PAGE_USER
mdefine_line|#define PAGE_USER&t;0x004
DECL|macro|PAGE_PWT
mdefine_line|#define PAGE_PWT&t;0x008&t;/* 486 only - not used currently */
DECL|macro|PAGE_PCD
mdefine_line|#define PAGE_PCD&t;0x010&t;/* 486 only - not used currently */
DECL|macro|PAGE_ACCESSED
mdefine_line|#define PAGE_ACCESSED&t;0x020
DECL|macro|PAGE_DIRTY
mdefine_line|#define PAGE_DIRTY&t;0x040
DECL|macro|PAGE_COW
mdefine_line|#define PAGE_COW&t;0x200&t;/* implemented in software (one of the AVL bits) */
DECL|macro|PAGE_PRIVATE
mdefine_line|#define PAGE_PRIVATE&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED | PAGE_COW)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;(PAGE_PRESENT | PAGE_USER | PAGE_ACCESSED)
DECL|macro|PAGE_TABLE
mdefine_line|#define PAGE_TABLE&t;(PAGE_PRESENT | PAGE_RW | PAGE_USER | PAGE_ACCESSED)
DECL|macro|GFP_BUFFER
mdefine_line|#define GFP_BUFFER&t;0x00
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;0x01
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;0x02
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;0x03
multiline_comment|/* vm_ops not present page codes */
DECL|macro|SHM_SWP_TYPE
mdefine_line|#define SHM_SWP_TYPE 0x41        
r_extern
r_void
id|shm_no_page
(paren
id|ulong
op_star
)paren
suffix:semicolon
macro_line|#endif
eof
