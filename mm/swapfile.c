multiline_comment|/*&n; *  linux/mm/swapfile.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Swap reorganised 29.12.95, Stephen Tweedie&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
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
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt; /* for blk_size */
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/dcache.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/uaccess.h&gt; /* for copy_to/from_user */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|variable|nr_swapfiles
r_int
r_int
id|nr_swapfiles
op_assign
l_int|0
suffix:semicolon
r_static
r_struct
(brace
DECL|member|head
r_int
id|head
suffix:semicolon
multiline_comment|/* head of priority-ordered swapfile list */
DECL|member|next
r_int
id|next
suffix:semicolon
multiline_comment|/* swapfile to be used next */
DECL|variable|swap_list
)brace
id|swap_list
op_assign
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|swap_info
r_struct
id|swap_info_struct
id|swap_info
(braket
id|MAX_SWAPFILES
)braket
suffix:semicolon
DECL|function|scan_swap_map
r_static
r_inline
r_int
id|scan_swap_map
c_func
(paren
r_struct
id|swap_info_struct
op_star
id|si
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
multiline_comment|/* &n;&t; * We try to cluster swap pages by allocating them&n;&t; * sequentially in swap.  Once we&squot;ve allocated&n;&t; * SWAP_CLUSTER_MAX pages this way, however, we resort to&n;&t; * first-free allocation, starting a new cluster.  This&n;&t; * prevents us from scattering swap pages all over the entire&n;&t; * swap partition, so that we reduce overall disk seek times&n;&t; * between swap pages.  -- sct */
r_if
c_cond
(paren
id|si-&gt;cluster_nr
)paren
(brace
r_while
c_loop
(paren
id|si-&gt;cluster_next
op_le
id|si-&gt;highest_bit
)paren
(brace
id|offset
op_assign
id|si-&gt;cluster_next
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|si-&gt;swap_map
(braket
id|offset
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|offset
comma
id|si-&gt;swap_lockmap
)paren
)paren
r_continue
suffix:semicolon
id|si-&gt;cluster_nr
op_decrement
suffix:semicolon
r_goto
id|got_page
suffix:semicolon
)brace
)brace
id|si-&gt;cluster_nr
op_assign
id|SWAP_CLUSTER_MAX
suffix:semicolon
r_for
c_loop
(paren
id|offset
op_assign
id|si-&gt;lowest_bit
suffix:semicolon
id|offset
op_le
id|si-&gt;highest_bit
suffix:semicolon
id|offset
op_increment
)paren
(brace
r_if
c_cond
(paren
id|si-&gt;swap_map
(braket
id|offset
)braket
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|offset
comma
id|si-&gt;swap_lockmap
)paren
)paren
r_continue
suffix:semicolon
id|si-&gt;lowest_bit
op_assign
id|offset
suffix:semicolon
id|got_page
suffix:colon
id|si-&gt;swap_map
(braket
id|offset
)braket
op_assign
l_int|1
suffix:semicolon
id|nr_swap_pages
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_eq
id|si-&gt;highest_bit
)paren
id|si-&gt;highest_bit
op_decrement
suffix:semicolon
id|si-&gt;cluster_next
op_assign
id|offset
suffix:semicolon
r_return
id|offset
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_swap_page
r_int
r_int
id|get_swap_page
c_func
(paren
r_void
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|offset
comma
id|entry
suffix:semicolon
r_int
id|type
comma
id|wrapped
op_assign
l_int|0
suffix:semicolon
id|type
op_assign
id|swap_list.next
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nr_swap_pages
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|p
op_assign
op_amp
id|swap_info
(braket
id|type
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_amp
id|SWP_WRITEOK
)paren
op_eq
id|SWP_WRITEOK
)paren
(brace
id|offset
op_assign
id|scan_swap_map
c_func
(paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|entry
op_assign
id|SWP_ENTRY
c_func
(paren
id|type
comma
id|offset
)paren
suffix:semicolon
id|type
op_assign
id|swap_info
(braket
id|type
)braket
dot
id|next
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_or
id|p-&gt;prio
op_ne
id|swap_info
(braket
id|type
)braket
dot
id|prio
)paren
(brace
id|swap_list.next
op_assign
id|swap_list.head
suffix:semicolon
)brace
r_else
(brace
id|swap_list.next
op_assign
id|type
suffix:semicolon
)brace
r_return
id|entry
suffix:semicolon
)brace
)brace
id|type
op_assign
id|p-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|wrapped
)paren
(brace
r_if
c_cond
(paren
id|type
OL
l_int|0
op_logical_or
id|p-&gt;prio
op_ne
id|swap_info
(braket
id|type
)braket
dot
id|prio
)paren
(brace
id|type
op_assign
id|swap_list.head
suffix:semicolon
id|wrapped
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* out of swap space */
)brace
)brace
)brace
DECL|function|swap_free
r_void
id|swap_free
c_func
(paren
r_int
r_int
id|entry
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|offset
comma
id|type
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
suffix:semicolon
id|type
op_assign
id|SWP_TYPE
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type
op_amp
id|SHM_SWP_TYPE
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|nr_swapfiles
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free nonexistent swap-page&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|swap_info
(braket
id|type
)braket
suffix:semicolon
id|offset
op_assign
id|SWP_OFFSET
c_func
(paren
id|entry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_ge
id|p-&gt;max
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;swap_free: weirdness&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;flags
op_amp
id|SWP_USED
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to free swap from unused swap-device&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|offset
OL
id|p-&gt;lowest_bit
)paren
id|p-&gt;lowest_bit
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|offset
OG
id|p-&gt;highest_bit
)paren
id|p-&gt;highest_bit
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_map
(braket
id|offset
)braket
)paren
id|printk
c_func
(paren
l_string|&quot;swap_free: swap-space map bad (entry %08lx)&bslash;n&quot;
comma
id|entry
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|p-&gt;swap_map
(braket
id|offset
)braket
)paren
id|nr_swap_pages
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;prio
OG
id|swap_info
(braket
id|swap_list.next
)braket
dot
id|prio
)paren
(brace
id|swap_list.next
op_assign
id|swap_list.head
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Trying to stop swapping from a file is fraught with races, so&n; * we repeat quite a bit here when we have to pause. swapoff()&n; * isn&squot;t exactly timing-critical, so who cares (but this is /really/&n; * inefficient, ugh).&n; *&n; * We return 1 after having slept, which makes the process start over&n; * from the beginning for this process..&n; */
DECL|function|unuse_pte
r_static
r_inline
r_int
id|unuse_pte
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
id|pte_t
op_star
id|dir
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|page
)paren
(brace
id|pte_t
id|pte
op_assign
op_star
id|dir
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|pte
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
r_struct
id|page
op_star
id|pg
suffix:semicolon
r_int
r_int
id|page_nr
op_assign
id|MAP_NR
c_func
(paren
id|pte_page
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_int
r_int
id|pg_swap_entry
suffix:semicolon
r_if
c_cond
(paren
id|page_nr
op_ge
id|max_mapnr
)paren
r_return
l_int|0
suffix:semicolon
id|pg
op_assign
id|mem_map
op_plus
id|page_nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pg_swap_entry
op_assign
id|in_swap_cache
c_func
(paren
id|pg
)paren
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|SWP_TYPE
c_func
(paren
id|pg_swap_entry
)paren
op_ne
id|SWP_TYPE
c_func
(paren
id|entry
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|delete_from_swap_cache
c_func
(paren
id|pg
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|dir
comma
id|pte_mkdirty
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pg_swap_entry
op_ne
id|entry
)paren
r_return
l_int|0
suffix:semicolon
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_ne
id|entry
)paren
r_return
l_int|0
suffix:semicolon
id|set_pte
c_func
(paren
id|dir
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
id|flush_tlb_page
c_func
(paren
id|vma
comma
id|address
)paren
suffix:semicolon
op_increment
id|vma-&gt;vm_mm-&gt;rss
suffix:semicolon
id|swap_free
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|unuse_pmd
r_static
r_inline
r_int
id|unuse_pmd
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pmd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|page
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unuse_pmd: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|dir
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|offset
op_add_assign
id|address
op_amp
id|PMD_MASK
suffix:semicolon
id|address
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|unuse_pte
c_func
(paren
id|vma
comma
id|offset
op_plus
id|address
op_minus
id|vma-&gt;vm_start
comma
id|pte
comma
id|entry
comma
id|page
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unuse_pgd
r_static
r_inline
r_int
id|unuse_pgd
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|page
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|offset
comma
id|end
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unuse_pgd: bad pgd (%08lx)&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
id|offset
op_assign
id|address
op_amp
id|PGDIR_MASK
suffix:semicolon
id|address
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|unuse_pmd
c_func
(paren
id|vma
comma
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|offset
comma
id|entry
comma
id|page
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|address
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unuse_vma
r_static
r_int
id|unuse_vma
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
id|pgd_t
op_star
id|pgdir
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|page
)paren
(brace
r_int
r_int
id|start
op_assign
id|vma-&gt;vm_start
comma
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
r_while
c_loop
(paren
id|start
OL
id|end
)paren
(brace
r_if
c_cond
(paren
id|unuse_pgd
c_func
(paren
id|vma
comma
id|pgdir
comma
id|start
comma
id|end
op_minus
id|start
comma
id|entry
comma
id|page
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|start
op_assign
(paren
id|start
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|pgdir
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unuse_process
r_static
r_int
id|unuse_process
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|entry
comma
r_int
r_int
id|page
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/*&n;&t; * Go through process&squot; page directory.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|mm
op_logical_or
id|mm
op_eq
op_amp
id|init_mm
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|vma
op_assign
id|mm-&gt;mmap
suffix:semicolon
id|vma
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
)paren
(brace
id|pgd_t
op_star
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|vma-&gt;vm_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unuse_vma
c_func
(paren
id|vma
comma
id|pgd
comma
id|entry
comma
id|page
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|find_swap_entry
r_static
r_int
r_int
id|find_swap_entry
c_func
(paren
r_int
id|type
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
op_assign
op_amp
id|swap_info
(braket
id|type
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|p-&gt;max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;swap_map
(braket
id|i
)braket
OG
l_int|0
op_logical_and
id|p-&gt;swap_map
(braket
id|i
)braket
op_ne
l_int|0x80
)paren
r_return
id|SWP_ENTRY
c_func
(paren
id|type
comma
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We completely avoid races by reading each swap page in advance,&n; * and then search for the process using it.  All the necessary&n; * page table adjustments can then be made atomically.&n; */
DECL|function|try_to_unuse
r_static
r_int
id|try_to_unuse
c_func
(paren
r_int
r_int
id|type
)paren
(brace
r_int
r_int
id|page
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|entry
suffix:semicolon
multiline_comment|/*&n;&t; * Find all swap entries in use ...&n;&t; */
r_while
c_loop
(paren
(paren
id|entry
op_assign
id|find_swap_entry
c_func
(paren
id|type
)paren
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
(brace
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
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Read in the page, and then free the swap page.&n;&t;&t; */
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
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
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
id|unuse_process
c_func
(paren
id|p-&gt;mm
comma
id|entry
comma
id|page
)paren
)paren
(brace
id|page
op_assign
l_int|0
suffix:semicolon
r_goto
id|unlock
suffix:semicolon
)brace
)brace
id|unlock
suffix:colon
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;try_to_unuse: didn&squot;t find entry %8lx&bslash;n&quot;
comma
id|entry
)paren
suffix:semicolon
id|swap_free
c_func
(paren
id|entry
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|page
)paren
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_swapoff
id|asmlinkage
r_int
id|sys_swapoff
c_func
(paren
r_const
r_char
op_star
id|specialfile
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
r_int
id|i
comma
id|type
comma
id|prev
suffix:semicolon
r_int
id|err
op_assign
op_minus
id|EPERM
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|dentry
op_assign
id|namei
c_func
(paren
id|specialfile
)paren
suffix:semicolon
id|err
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_goto
id|out
suffix:semicolon
id|prev
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|type
op_assign
id|swap_list.head
suffix:semicolon
id|type
op_ge
l_int|0
suffix:semicolon
id|type
op_assign
id|swap_info
(braket
id|type
)braket
dot
id|next
)paren
(brace
id|p
op_assign
id|swap_info
op_plus
id|type
suffix:semicolon
r_if
c_cond
(paren
(paren
id|p-&gt;flags
op_amp
id|SWP_WRITEOK
)paren
op_eq
id|SWP_WRITEOK
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;swap_file
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;swap_file
op_eq
id|dentry
)paren
r_break
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|dentry-&gt;d_inode-&gt;i_mode
)paren
op_logical_and
(paren
id|p-&gt;swap_device
op_eq
id|dentry-&gt;d_inode-&gt;i_rdev
)paren
)paren
r_break
suffix:semicolon
)brace
)brace
id|prev
op_assign
id|type
suffix:semicolon
)brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|type
OL
l_int|0
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
OL
l_int|0
)paren
(brace
id|swap_list.head
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_else
(brace
id|swap_info
(braket
id|prev
)braket
dot
id|next
op_assign
id|p-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type
op_eq
id|swap_list.next
)paren
(brace
multiline_comment|/* just pick something that&squot;s safe... */
id|swap_list.next
op_assign
id|swap_list.head
suffix:semicolon
)brace
id|p-&gt;flags
op_assign
id|SWP_USED
suffix:semicolon
id|err
op_assign
id|try_to_unuse
c_func
(paren
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
multiline_comment|/* re-insert swap space back into swap_list */
r_for
c_loop
(paren
id|prev
op_assign
op_minus
l_int|1
comma
id|i
op_assign
id|swap_list.head
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|prev
op_assign
id|i
comma
id|i
op_assign
id|swap_info
(braket
id|i
)braket
dot
id|next
)paren
r_if
c_cond
(paren
id|p-&gt;prio
op_ge
id|swap_info
(braket
id|i
)braket
dot
id|prio
)paren
r_break
suffix:semicolon
id|p-&gt;next
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|prev
OL
l_int|0
)paren
id|swap_list.head
op_assign
id|swap_list.next
op_assign
id|p
op_minus
id|swap_info
suffix:semicolon
r_else
id|swap_info
(braket
id|prev
)braket
dot
id|next
op_assign
id|p
op_minus
id|swap_info
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_WRITEOK
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;swap_device
)paren
(brace
id|memset
c_func
(paren
op_amp
id|filp
comma
l_int|0
comma
r_sizeof
(paren
id|filp
)paren
)paren
suffix:semicolon
id|filp.f_dentry
op_assign
id|dentry
suffix:semicolon
id|filp.f_mode
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* read write */
multiline_comment|/* open it again to get fops */
r_if
c_cond
(paren
op_logical_neg
id|blkdev_open
c_func
(paren
id|dentry-&gt;d_inode
comma
op_amp
id|filp
)paren
op_logical_and
id|filp.f_op
op_logical_and
id|filp.f_op-&gt;release
)paren
(brace
id|filp.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|dentry-&gt;d_inode
comma
op_amp
id|filp
)paren
suffix:semicolon
id|filp.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|dentry-&gt;d_inode
comma
op_amp
id|filp
)paren
suffix:semicolon
)brace
)brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
id|nr_swap_pages
op_sub_assign
id|p-&gt;pages
suffix:semicolon
id|dput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|vfree
c_func
(paren
id|p-&gt;swap_map
)paren
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|get_swaparea_info
r_int
id|get_swaparea_info
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
suffix:semicolon
r_struct
id|swap_info_struct
op_star
id|ptr
op_assign
id|swap_info
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|len
op_assign
l_int|0
comma
id|usedswap
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;Filename&bslash;t&bslash;t&bslash;tType&bslash;t&bslash;tSize&bslash;tUsed&bslash;tPriority&bslash;n&quot;
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
id|nr_swapfiles
suffix:semicolon
id|i
op_increment
comma
id|ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;flags
op_amp
id|SWP_USED
)paren
(brace
r_char
op_star
id|path
op_assign
id|d_path
c_func
(paren
id|ptr-&gt;swap_file
comma
id|page
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%-31s &quot;
comma
id|path
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr-&gt;swap_device
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;file&bslash;t&bslash;t&quot;
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;partition&bslash;t&quot;
)paren
suffix:semicolon
id|usedswap
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|ptr-&gt;max
suffix:semicolon
op_increment
id|j
)paren
r_switch
c_cond
(paren
id|ptr-&gt;swap_map
(braket
id|j
)braket
)paren
(brace
r_case
l_int|128
suffix:colon
r_case
l_int|0
suffix:colon
r_continue
suffix:semicolon
r_default
suffix:colon
id|usedswap
op_increment
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%d&bslash;t%d&bslash;t%d&bslash;n&quot;
comma
id|ptr-&gt;pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|usedswap
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|ptr-&gt;prio
)paren
suffix:semicolon
)brace
)brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Written 01/25/92 by Simmule Turner, heavily changed by Linus.&n; *&n; * The swapon system call&n; */
DECL|function|sys_swapon
id|asmlinkage
r_int
id|sys_swapon
c_func
(paren
r_const
r_char
op_star
id|specialfile
comma
r_int
id|swap_flags
)paren
(brace
r_struct
id|swap_info_struct
op_star
id|p
suffix:semicolon
r_struct
id|dentry
op_star
id|swap_dentry
suffix:semicolon
r_int
r_int
id|type
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|prev
suffix:semicolon
r_int
id|error
op_assign
op_minus
id|EPERM
suffix:semicolon
r_struct
id|file
id|filp
suffix:semicolon
r_static
r_int
id|least_priority
op_assign
l_int|0
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|filp
comma
l_int|0
comma
r_sizeof
(paren
id|filp
)paren
)paren
suffix:semicolon
id|p
op_assign
id|swap_info
suffix:semicolon
r_for
c_loop
(paren
id|type
op_assign
l_int|0
suffix:semicolon
id|type
OL
id|nr_swapfiles
suffix:semicolon
id|type
op_increment
comma
id|p
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
(paren
id|p-&gt;flags
op_amp
id|SWP_USED
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|MAX_SWAPFILES
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ge
id|nr_swapfiles
)paren
id|nr_swapfiles
op_assign
id|type
op_plus
l_int|1
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_USED
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;lowest_bit
op_assign
l_int|0
suffix:semicolon
id|p-&gt;highest_bit
op_assign
l_int|0
suffix:semicolon
id|p-&gt;cluster_nr
op_assign
l_int|0
suffix:semicolon
id|p-&gt;max
op_assign
l_int|1
suffix:semicolon
id|p-&gt;next
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|swap_flags
op_amp
id|SWAP_FLAG_PREFER
)paren
(brace
id|p-&gt;prio
op_assign
(paren
id|swap_flags
op_amp
id|SWAP_FLAG_PRIO_MASK
)paren
op_rshift
id|SWAP_FLAG_PRIO_SHIFT
suffix:semicolon
)brace
r_else
(brace
id|p-&gt;prio
op_assign
op_decrement
id|least_priority
suffix:semicolon
)brace
id|swap_dentry
op_assign
id|namei
c_func
(paren
id|specialfile
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|swap_dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|swap_dentry
)paren
)paren
r_goto
id|bad_swap_2
suffix:semicolon
id|p-&gt;swap_file
op_assign
id|swap_dentry
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|S_ISBLK
c_func
(paren
id|swap_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
(brace
id|p-&gt;swap_device
op_assign
id|swap_dentry-&gt;d_inode-&gt;i_rdev
suffix:semicolon
id|set_blocksize
c_func
(paren
id|p-&gt;swap_device
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|filp.f_dentry
op_assign
id|swap_dentry
suffix:semicolon
id|filp.f_mode
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* read write */
id|error
op_assign
id|blkdev_open
c_func
(paren
id|swap_dentry-&gt;d_inode
comma
op_amp
id|filp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|bad_swap_2
suffix:semicolon
id|error
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_device
op_logical_or
(paren
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|p-&gt;swap_device
)paren
)braket
op_logical_and
op_logical_neg
id|blk_size
(braket
id|MAJOR
c_func
(paren
id|p-&gt;swap_device
)paren
)braket
(braket
id|MINOR
c_func
(paren
id|p-&gt;swap_device
)paren
)braket
)paren
)paren
r_goto
id|bad_swap
suffix:semicolon
id|error
op_assign
op_minus
id|EBUSY
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
id|nr_swapfiles
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|type
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;swap_device
op_eq
id|swap_info
(braket
id|i
)braket
dot
id|swap_device
)paren
r_goto
id|bad_swap
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|swap_dentry-&gt;d_inode-&gt;i_mode
)paren
)paren
r_goto
id|bad_swap
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
(paren
r_int
r_char
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_lockmap
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to start swapping: out of memory :-)&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|bad_swap
suffix:semicolon
)brace
id|read_swap_page
c_func
(paren
id|SWP_ENTRY
c_func
(paren
id|type
comma
l_int|0
)paren
comma
(paren
r_char
op_star
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
r_if
c_cond
(paren
id|memcmp
c_func
(paren
l_string|&quot;SWAP-SPACE&quot;
comma
id|p-&gt;swap_lockmap
op_plus
id|PAGE_SIZE
op_minus
l_int|10
comma
l_int|10
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to find swap-space signature&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|bad_swap
suffix:semicolon
)brace
id|memset
c_func
(paren
id|p-&gt;swap_lockmap
op_plus
id|PAGE_SIZE
op_minus
l_int|10
comma
l_int|0
comma
l_int|10
)paren
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
id|p-&gt;lowest_bit
op_assign
l_int|0
suffix:semicolon
id|p-&gt;highest_bit
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|8
op_star
id|PAGE_SIZE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|p-&gt;swap_lockmap
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;lowest_bit
)paren
id|p-&gt;lowest_bit
op_assign
id|i
suffix:semicolon
id|p-&gt;highest_bit
op_assign
id|i
suffix:semicolon
id|p-&gt;max
op_assign
id|i
op_plus
l_int|1
suffix:semicolon
id|j
op_increment
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|j
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Empty swap-file&bslash;n&quot;
)paren
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|bad_swap
suffix:semicolon
)brace
id|p-&gt;swap_map
op_assign
(paren
r_int
r_char
op_star
)paren
id|vmalloc
c_func
(paren
id|p-&gt;max
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p-&gt;swap_map
)paren
(brace
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|bad_swap
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|p-&gt;max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|i
comma
id|p-&gt;swap_lockmap
)paren
)paren
id|p-&gt;swap_map
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
r_else
id|p-&gt;swap_map
(braket
id|i
)braket
op_assign
l_int|0x80
suffix:semicolon
)brace
id|p-&gt;swap_map
(braket
l_int|0
)braket
op_assign
l_int|0x80
suffix:semicolon
id|memset
c_func
(paren
id|p-&gt;swap_lockmap
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|p-&gt;flags
op_assign
id|SWP_WRITEOK
suffix:semicolon
id|p-&gt;pages
op_assign
id|j
suffix:semicolon
id|nr_swap_pages
op_add_assign
id|j
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Adding Swap: %dk swap-space (priority %d)&bslash;n&quot;
comma
id|j
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|p-&gt;prio
)paren
suffix:semicolon
multiline_comment|/* insert swap space into swap_list: */
id|prev
op_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|swap_list.head
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_assign
id|swap_info
(braket
id|i
)braket
dot
id|next
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;prio
op_ge
id|swap_info
(braket
id|i
)braket
dot
id|prio
)paren
(brace
r_break
suffix:semicolon
)brace
id|prev
op_assign
id|i
suffix:semicolon
)brace
id|p-&gt;next
op_assign
id|i
suffix:semicolon
r_if
c_cond
(paren
id|prev
OL
l_int|0
)paren
(brace
id|swap_list.head
op_assign
id|swap_list.next
op_assign
id|p
op_minus
id|swap_info
suffix:semicolon
)brace
r_else
(brace
id|swap_info
(braket
id|prev
)braket
dot
id|next
op_assign
id|p
op_minus
id|swap_info
suffix:semicolon
)brace
id|error
op_assign
l_int|0
suffix:semicolon
r_goto
id|out
suffix:semicolon
id|bad_swap
suffix:colon
r_if
c_cond
(paren
id|filp.f_op
op_logical_and
id|filp.f_op-&gt;release
)paren
(brace
id|filp.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|filp.f_dentry-&gt;d_inode
comma
op_amp
id|filp
)paren
suffix:semicolon
)brace
id|bad_swap_2
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
)paren
id|p-&gt;swap_lockmap
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|p-&gt;swap_map
)paren
suffix:semicolon
id|dput
c_func
(paren
id|p-&gt;swap_file
)paren
suffix:semicolon
id|p-&gt;swap_device
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swap_file
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_map
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;swap_lockmap
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
DECL|function|si_swapinfo
r_void
id|si_swapinfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
(brace
r_int
r_int
id|i
comma
id|j
suffix:semicolon
id|val-&gt;freeswap
op_assign
id|val-&gt;totalswap
op_assign
l_int|0
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
id|nr_swapfiles
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|swap_info
(braket
id|i
)braket
dot
id|flags
op_amp
id|SWP_WRITEOK
)paren
op_ne
id|SWP_WRITEOK
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|swap_info
(braket
id|i
)braket
dot
id|max
suffix:semicolon
op_increment
id|j
)paren
r_switch
c_cond
(paren
id|swap_info
(braket
id|i
)braket
dot
id|swap_map
(braket
id|j
)braket
)paren
(brace
r_case
l_int|128
suffix:colon
r_continue
suffix:semicolon
r_case
l_int|0
suffix:colon
op_increment
id|val-&gt;freeswap
suffix:semicolon
r_default
suffix:colon
op_increment
id|val-&gt;totalswap
suffix:semicolon
)brace
)brace
id|val-&gt;freeswap
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;totalswap
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
