multiline_comment|/*&n; *  linux/mm/page_alloc.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/swapctl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_to/from_user */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|nr_swap_pages
r_int
id|nr_swap_pages
op_assign
l_int|0
suffix:semicolon
DECL|variable|nr_free_pages
r_int
id|nr_free_pages
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Free area management&n; *&n; * The free_area_list arrays point to the queue heads of the free areas&n; * of different sizes&n; */
macro_line|#if CONFIG_AP1000
multiline_comment|/* the AP+ needs to allocate 8MB contiguous, aligned chunks of ram&n;   for the ring buffers */
DECL|macro|NR_MEM_LISTS
mdefine_line|#define NR_MEM_LISTS 12
macro_line|#else
DECL|macro|NR_MEM_LISTS
mdefine_line|#define NR_MEM_LISTS 6
macro_line|#endif
multiline_comment|/* The start of this MUST match the start of &quot;struct page&quot; */
DECL|struct|free_area_struct
r_struct
id|free_area_struct
(brace
DECL|member|next
r_struct
id|page
op_star
id|next
suffix:semicolon
DECL|member|prev
r_struct
id|page
op_star
id|prev
suffix:semicolon
DECL|member|map
r_int
r_int
op_star
id|map
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|memory_head
mdefine_line|#define memory_head(x) ((struct page *)(x))
DECL|variable|free_area
r_static
r_struct
id|free_area_struct
id|free_area
(braket
id|NR_MEM_LISTS
)braket
suffix:semicolon
DECL|function|init_mem_queue
r_static
r_inline
r_void
id|init_mem_queue
c_func
(paren
r_struct
id|free_area_struct
op_star
id|head
)paren
(brace
id|head-&gt;next
op_assign
id|memory_head
c_func
(paren
id|head
)paren
suffix:semicolon
id|head-&gt;prev
op_assign
id|memory_head
c_func
(paren
id|head
)paren
suffix:semicolon
)brace
DECL|function|add_mem_queue
r_static
r_inline
r_void
id|add_mem_queue
c_func
(paren
r_struct
id|free_area_struct
op_star
id|head
comma
r_struct
id|page
op_star
id|entry
)paren
(brace
r_struct
id|page
op_star
id|next
op_assign
id|head-&gt;next
suffix:semicolon
id|entry-&gt;prev
op_assign
id|memory_head
c_func
(paren
id|head
)paren
suffix:semicolon
id|entry-&gt;next
op_assign
id|next
suffix:semicolon
id|next-&gt;prev
op_assign
id|entry
suffix:semicolon
id|head-&gt;next
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|remove_mem_queue
r_static
r_inline
r_void
id|remove_mem_queue
c_func
(paren
r_struct
id|page
op_star
id|entry
)paren
(brace
r_struct
id|page
op_star
id|next
op_assign
id|entry-&gt;next
suffix:semicolon
r_struct
id|page
op_star
id|prev
op_assign
id|entry-&gt;prev
suffix:semicolon
id|next-&gt;prev
op_assign
id|prev
suffix:semicolon
id|prev-&gt;next
op_assign
id|next
suffix:semicolon
)brace
multiline_comment|/*&n; * Free_page() adds the page to the free lists. This is optimized for&n; * fast normal cases (no error jumps taken normally).&n; *&n; * The way to optimize jumps for gcc-2.2.2 is to:&n; *  - select the &quot;normal&quot; case and put it inside the if () { XXX }&n; *  - no else-statements if you can avoid them&n; *&n; * With the above two rules, you get a straight-line execution path&n; * for the normal case, giving better asm-code.&n; *&n; * free_page() may sleep since the page being freed may be a buffer&n; * page or present in the swap cache. It will not sleep, however,&n; * for a freshly allocated page (get_free_page()).&n; */
multiline_comment|/*&n; * Buddy system. Hairy. You really aren&squot;t expected to understand this&n; *&n; * Hint: -mask = 1+~mask&n; */
DECL|function|free_pages_ok
r_static
r_inline
r_void
id|free_pages_ok
c_func
(paren
r_int
r_int
id|map_nr
comma
r_int
r_int
id|order
)paren
(brace
r_struct
id|free_area_struct
op_star
id|area
op_assign
id|free_area
op_plus
id|order
suffix:semicolon
r_int
r_int
id|index
op_assign
id|map_nr
op_rshift
(paren
l_int|1
op_plus
id|order
)paren
suffix:semicolon
r_int
r_int
id|mask
op_assign
(paren
op_complement
l_int|0UL
)paren
op_lshift
id|order
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
DECL|macro|list
mdefine_line|#define list(x) (mem_map+(x))
id|map_nr
op_and_assign
id|mask
suffix:semicolon
id|nr_free_pages
op_sub_assign
id|mask
suffix:semicolon
r_while
c_loop
(paren
id|mask
op_plus
(paren
l_int|1
op_lshift
(paren
id|NR_MEM_LISTS
op_minus
l_int|1
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|change_bit
c_func
(paren
id|index
comma
id|area-&gt;map
)paren
)paren
r_break
suffix:semicolon
id|remove_mem_queue
c_func
(paren
id|list
c_func
(paren
id|map_nr
op_xor
op_minus
id|mask
)paren
)paren
suffix:semicolon
id|mask
op_lshift_assign
l_int|1
suffix:semicolon
id|area
op_increment
suffix:semicolon
id|index
op_rshift_assign
l_int|1
suffix:semicolon
id|map_nr
op_and_assign
id|mask
suffix:semicolon
)brace
id|add_mem_queue
c_func
(paren
id|area
comma
id|list
c_func
(paren
id|map_nr
)paren
)paren
suffix:semicolon
DECL|macro|list
macro_line|#undef list
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|__free_page
r_void
id|__free_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|PageReserved
c_func
(paren
id|page
)paren
op_logical_and
id|atomic_dec_and_test
c_func
(paren
op_amp
id|page-&gt;count
)paren
)paren
(brace
r_int
r_int
id|map_nr
op_assign
id|page-&gt;map_nr
suffix:semicolon
id|delete_from_swap_cache
c_func
(paren
id|map_nr
)paren
suffix:semicolon
id|free_pages_ok
c_func
(paren
id|map_nr
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|free_pages
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
(brace
r_int
r_int
id|map_nr
op_assign
id|MAP_NR
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_nr
OL
id|max_mapnr
)paren
(brace
id|mem_map_t
op_star
id|map
op_assign
id|mem_map
op_plus
id|map_nr
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|map
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|map-&gt;count
)paren
)paren
(brace
id|delete_from_swap_cache
c_func
(paren
id|map_nr
)paren
suffix:semicolon
id|free_pages_ok
c_func
(paren
id|map_nr
comma
id|order
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Some ugly macros to speed up __get_free_pages()..&n; */
DECL|macro|MARK_USED
mdefine_line|#define MARK_USED(index, order, area) &bslash;&n;&t;change_bit((index) &gt;&gt; (1+(order)), (area)-&gt;map)
DECL|macro|CAN_DMA
mdefine_line|#define CAN_DMA(x) (PageDMA(x))
DECL|macro|ADDRESS
mdefine_line|#define ADDRESS(x) (PAGE_OFFSET + ((x) &lt;&lt; PAGE_SHIFT))
DECL|macro|RMQUEUE
mdefine_line|#define RMQUEUE(order, dma) &bslash;&n;do { struct free_area_struct * area = free_area+order; &bslash;&n;     unsigned long new_order = order; &bslash;&n;&t;do { struct page *prev = memory_head(area), *ret; &bslash;&n;&t;&t;while (memory_head(area) != (ret = prev-&gt;next)) { &bslash;&n;&t;&t;&t;if (!dma || CAN_DMA(ret)) { &bslash;&n;&t;&t;&t;&t;unsigned long map_nr = ret-&gt;map_nr; &bslash;&n;&t;&t;&t;&t;(prev-&gt;next = ret-&gt;next)-&gt;prev = prev; &bslash;&n;&t;&t;&t;&t;MARK_USED(map_nr, new_order, area); &bslash;&n;&t;&t;&t;&t;nr_free_pages -= 1 &lt;&lt; order; &bslash;&n;&t;&t;&t;&t;EXPAND(ret, map_nr, order, new_order, area); &bslash;&n;&t;&t;&t;&t;restore_flags(flags); &bslash;&n;&t;&t;&t;&t;return ADDRESS(map_nr); &bslash;&n;&t;&t;&t;} &bslash;&n;&t;&t;&t;prev = ret; &bslash;&n;&t;&t;} &bslash;&n;&t;&t;new_order++; area++; &bslash;&n;&t;} while (new_order &lt; NR_MEM_LISTS); &bslash;&n;} while (0)
DECL|macro|EXPAND
mdefine_line|#define EXPAND(map,index,low,high,area) &bslash;&n;do { unsigned long size = 1 &lt;&lt; high; &bslash;&n;&t;while (high &gt; low) { &bslash;&n;&t;&t;area--; high--; size &gt;&gt;= 1; &bslash;&n;&t;&t;add_mem_queue(area, map); &bslash;&n;&t;&t;MARK_USED(index, high, area); &bslash;&n;&t;&t;index += size; &bslash;&n;&t;&t;map += size; &bslash;&n;&t;} &bslash;&n;&t;atomic_set(&amp;map-&gt;count, 1); &bslash;&n;&t;map-&gt;age = PAGE_INITIAL_AGE; &bslash;&n;} while (0)
DECL|function|__get_free_pages
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
id|order
comma
r_int
id|dma
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|reserved_pages
suffix:semicolon
r_if
c_cond
(paren
id|order
op_ge
id|NR_MEM_LISTS
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
op_logical_and
id|priority
op_ne
id|GFP_ATOMIC
)paren
(brace
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|count
OL
l_int|5
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;gfp called nonatomically from interrupt %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|priority
op_assign
id|GFP_ATOMIC
suffix:semicolon
)brace
)brace
id|reserved_pages
op_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|priority
op_ne
id|GFP_NFS
)paren
id|reserved_pages
op_assign
id|min_free_pages
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|repeat
suffix:colon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priority
op_eq
id|GFP_ATOMIC
)paren
op_logical_or
id|nr_free_pages
OG
id|reserved_pages
)paren
(brace
id|RMQUEUE
c_func
(paren
id|order
comma
id|dma
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priority
op_ne
id|GFP_BUFFER
op_logical_and
id|try_to_free_page
c_func
(paren
id|priority
comma
id|dma
comma
l_int|1
)paren
)paren
r_goto
id|repeat
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Show free area list (used inside shift_scroll-lock stuff)&n; * We also calculate the percentage fragmentation. We do this by counting the&n; * memory on each free list with the exception of the first item on the list.&n; */
DECL|function|show_free_areas
r_void
id|show_free_areas
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|order
comma
id|flags
suffix:semicolon
r_int
r_int
id|total
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free pages:      %6dkB&bslash;n ( &quot;
comma
id|nr_free_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|order
op_assign
l_int|0
suffix:semicolon
id|order
OL
id|NR_MEM_LISTS
suffix:semicolon
id|order
op_increment
)paren
(brace
r_struct
id|page
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|nr
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|free_area
(braket
id|order
)braket
dot
id|next
suffix:semicolon
id|tmp
op_ne
id|memory_head
c_func
(paren
id|free_area
op_plus
id|order
)paren
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;next
)paren
(brace
id|nr
op_increment
suffix:semicolon
)brace
id|total
op_add_assign
id|nr
op_star
(paren
(paren
id|PAGE_SIZE
op_rshift
l_int|10
)paren
op_lshift
id|order
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%lu*%lukB &quot;
comma
id|nr
comma
(paren
r_int
r_int
)paren
(paren
(paren
id|PAGE_SIZE
op_rshift
l_int|10
)paren
op_lshift
id|order
)paren
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;= %lukB)&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
macro_line|#ifdef SWAP_CACHE_INFO
id|show_swap_cache_info
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif&t;
)brace
DECL|macro|LONG_ALIGN
mdefine_line|#define LONG_ALIGN(x) (((x)+(sizeof(long))-1)&amp;~((sizeof(long))-1))
multiline_comment|/*&n; * set up the free-area data structures:&n; *   - mark all pages reserved&n; *   - mark all memory queues empty&n; *   - clear the memory bitmaps&n; */
DECL|function|free_area_init
r_int
r_int
id|free_area_init
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
(brace
id|mem_map_t
op_star
id|p
suffix:semicolon
r_int
r_int
id|mask
op_assign
id|PAGE_MASK
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * select nr of pages we try to keep free for important stuff&n;&t; * with a minimum of 16 pages. This is totally arbitrary&n;&t; */
id|i
op_assign
(paren
id|end_mem
op_minus
id|PAGE_OFFSET
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_plus
l_int|7
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|16
)paren
id|i
op_assign
l_int|16
suffix:semicolon
id|min_free_pages
op_assign
id|i
suffix:semicolon
id|free_pages_low
op_assign
id|i
op_plus
(paren
id|i
op_rshift
l_int|1
)paren
suffix:semicolon
id|free_pages_high
op_assign
id|i
op_plus
id|i
suffix:semicolon
id|start_mem
op_assign
id|init_swap_cache
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
id|mem_map
op_assign
(paren
id|mem_map_t
op_star
)paren
id|start_mem
suffix:semicolon
id|p
op_assign
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|end_mem
)paren
suffix:semicolon
id|start_mem
op_assign
id|LONG_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
id|p
)paren
suffix:semicolon
id|memset
c_func
(paren
id|mem_map
comma
l_int|0
comma
id|start_mem
op_minus
(paren
r_int
r_int
)paren
id|mem_map
)paren
suffix:semicolon
r_do
(brace
op_decrement
id|p
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|p-&gt;count
comma
l_int|0
)paren
suffix:semicolon
id|p-&gt;flags
op_assign
(paren
l_int|1
op_lshift
id|PG_DMA
)paren
op_or
(paren
l_int|1
op_lshift
id|PG_reserved
)paren
suffix:semicolon
id|p-&gt;map_nr
op_assign
id|p
op_minus
id|mem_map
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
OG
id|mem_map
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NR_MEM_LISTS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|bitmap_size
suffix:semicolon
id|init_mem_queue
c_func
(paren
id|free_area
op_plus
id|i
)paren
suffix:semicolon
id|mask
op_add_assign
id|mask
suffix:semicolon
id|end_mem
op_assign
(paren
id|end_mem
op_plus
op_complement
id|mask
)paren
op_amp
id|mask
suffix:semicolon
id|bitmap_size
op_assign
(paren
id|end_mem
op_minus
id|PAGE_OFFSET
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_plus
id|i
)paren
suffix:semicolon
id|bitmap_size
op_assign
(paren
id|bitmap_size
op_plus
l_int|7
)paren
op_rshift
l_int|3
suffix:semicolon
id|bitmap_size
op_assign
id|LONG_ALIGN
c_func
(paren
id|bitmap_size
)paren
suffix:semicolon
id|free_area
(braket
id|i
)braket
dot
id|map
op_assign
(paren
r_int
r_int
op_star
)paren
id|start_mem
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|start_mem
comma
l_int|0
comma
id|bitmap_size
)paren
suffix:semicolon
id|start_mem
op_add_assign
id|bitmap_size
suffix:semicolon
)brace
r_return
id|start_mem
suffix:semicolon
)brace
multiline_comment|/*&n; * The tests may look silly, but it essentially makes sure that&n; * no other process did a swap-in on us just as we were waiting.&n; *&n; * Also, don&squot;t bother to add to the swap cache if this page-in&n; * was due to a write access.&n; */
DECL|function|swap_in
r_void
id|swap_in
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
id|pte_t
op_star
id|page_table
comma
r_int
r_int
id|entry
comma
r_int
id|write_access
)paren
(brace
r_int
r_int
id|page
op_assign
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|page_table
)paren
op_ne
id|entry
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
id|set_pte
c_func
(paren
id|page_table
comma
id|BAD_PAGE
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
id|oom
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|read_swap_page
c_func
(paren
id|entry
comma
(paren
r_char
op_star
)paren
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
op_star
id|page_table
)paren
op_ne
id|entry
)paren
(brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|vma-&gt;vm_mm-&gt;rss
op_increment
suffix:semicolon
id|tsk-&gt;maj_flt
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_access
op_logical_and
id|add_to_swap_cache
c_func
(paren
id|MAP_NR
c_func
(paren
id|page
)paren
comma
id|entry
)paren
)paren
(brace
multiline_comment|/* keep swap page allocated for the moment (swap cache) */
id|set_pte
c_func
(paren
id|page_table
comma
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|page_table
comma
id|pte_mkwrite
c_func
(paren
id|pte_mkdirty
c_func
(paren
id|mk_pte
c_func
(paren
id|page
comma
id|vma-&gt;vm_page_prot
)paren
)paren
)paren
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
