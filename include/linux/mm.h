macro_line|#ifndef _LINUX_MM_H
DECL|macro|_LINUX_MM_H
mdefine_line|#define _LINUX_MM_H
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE 4096
DECL|macro|PAGE_SHIFT
mdefine_line|#define PAGE_SHIFT 12
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
multiline_comment|/*&n; * BAD_PAGE is the page that is used for page faults when linux&n; * is out-of-memory. Older versions of linux just did a&n; * do_exit(), but using this instead means there is less risk&n; * for a process dying in kernel mode, possibly leaving a inode&n; * unused etc..&n; *&n; * BAD_PAGETABLE is the accompanying page-table: it is initialized&n; * to point to BAD_PAGE entries.&n; */
DECL|function|__bad_page
r_extern
r_int
r_int
r_inline
id|__bad_page
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|empty_bad_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld ; rep ; stosl&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|empty_bad_page
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|1024
)paren
suffix:colon
l_string|&quot;di&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|empty_bad_page
suffix:semicolon
)brace
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|function|__bad_pagetable
r_extern
r_int
r_int
r_inline
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
r_extern
r_char
id|empty_bad_page_table
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;cld ; rep ; stosl&quot;
op_scope_resolution
l_string|&quot;a&quot;
(paren
l_int|7
op_plus
id|BAD_PAGE
)paren
comma
l_string|&quot;D&quot;
(paren
(paren
r_int
)paren
id|empty_bad_page_table
)paren
comma
l_string|&quot;c&quot;
(paren
l_int|1024
)paren
suffix:colon
l_string|&quot;di&quot;
comma
l_string|&quot;cx&quot;
)paren
suffix:semicolon
r_return
(paren
r_int
r_int
)paren
id|empty_bad_page_table
suffix:semicolon
)brace
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
r_extern
r_volatile
r_int
id|free_page_ptr
suffix:semicolon
multiline_comment|/* used by malloc and tcp/ip. */
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
mdefine_line|#define MAX_SECONDARY_PAGES 10
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
DECL|macro|read_swap_page
mdefine_line|#define read_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(READ,(nr),(buf))
DECL|macro|write_swap_page
mdefine_line|#define write_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(WRITE,(nr),(buf))
multiline_comment|/* memory.c */
r_extern
r_int
r_int
id|get_free_page
c_func
(paren
r_int
id|priority
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
id|free_page
c_func
(paren
r_int
r_int
id|addr
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
r_new
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
id|permiss
)paren
suffix:semicolon
r_extern
r_void
id|write_verify
c_func
(paren
r_int
r_int
id|address
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
id|do_page_fault
c_func
(paren
r_int
r_int
op_star
id|esp
comma
r_int
r_int
id|error_code
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
id|malloc_grab_pages
c_func
(paren
r_void
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
r_void
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
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__ __volatile__(&quot;movl %%cr3,%%eax&bslash;n&bslash;tmovl %%eax,%%cr3&quot;:::&quot;ax&quot;)
r_extern
r_int
r_int
id|high_memory
suffix:semicolon
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) ((addr) &gt;&gt; PAGE_SHIFT)
DECL|macro|MAP_PAGE_RESERVED
mdefine_line|#define MAP_PAGE_RESERVED (1&lt;&lt;15)
DECL|macro|USED
mdefine_line|#define USED 100
r_extern
r_int
r_int
op_star
id|mem_map
suffix:semicolon
DECL|macro|PAGE_DIRTY
mdefine_line|#define PAGE_DIRTY&t;0x40
DECL|macro|PAGE_ACCESSED
mdefine_line|#define PAGE_ACCESSED&t;0x20
DECL|macro|PAGE_USER
mdefine_line|#define PAGE_USER&t;0x04
DECL|macro|PAGE_RW
mdefine_line|#define PAGE_RW&t;&t;0x02
DECL|macro|PAGE_PRESENT
mdefine_line|#define PAGE_PRESENT&t;0x01
DECL|macro|GFP_BUFFER
mdefine_line|#define GFP_BUFFER&t;0x00
DECL|macro|GFP_ATOMIC
mdefine_line|#define GFP_ATOMIC&t;0x01
DECL|macro|GFP_USER
mdefine_line|#define GFP_USER&t;0x02
DECL|macro|GFP_KERNEL
mdefine_line|#define GFP_KERNEL&t;0x03
macro_line|#endif
eof
