macro_line|#ifndef _MM_H
DECL|macro|_MM_H
mdefine_line|#define _MM_H
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE 4096
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;signal.h&gt;
r_extern
r_int
r_int
id|swap_device
suffix:semicolon
r_extern
r_struct
id|inode
op_star
id|swap_file
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
DECL|macro|read_swap_page
mdefine_line|#define read_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(READ,(nr),(buf))
DECL|macro|write_swap_page
mdefine_line|#define write_swap_page(nr,buf) &bslash;&n;&t;rw_swap_page(WRITE,(nr),(buf))
r_extern
r_int
r_int
id|get_free_page
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
r_void
id|swap_free
c_func
(paren
r_int
id|page_nr
)paren
suffix:semicolon
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
DECL|function|oom
r_extern
r_inline
r_volatile
r_void
id|oom
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;out of memory&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|macro|invalidate
mdefine_line|#define invalidate() &bslash;&n;__asm__(&quot;movl %%eax,%%cr3&quot;::&quot;a&quot; (0))
multiline_comment|/* these are not to be changed without changing head.s etc */
DECL|macro|LOW_MEM
mdefine_line|#define LOW_MEM 0x100000
r_extern
r_int
r_int
id|HIGH_MEMORY
suffix:semicolon
DECL|macro|PAGING_MEMORY
mdefine_line|#define PAGING_MEMORY (15*1024*1024)
DECL|macro|PAGING_PAGES
mdefine_line|#define PAGING_PAGES (PAGING_MEMORY&gt;&gt;12)
DECL|macro|MAP_NR
mdefine_line|#define MAP_NR(addr) (((addr)-LOW_MEM)&gt;&gt;12)
DECL|macro|USED
mdefine_line|#define USED 100
r_extern
r_int
r_char
id|mem_map
(braket
id|PAGING_PAGES
)braket
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
macro_line|#endif
eof
