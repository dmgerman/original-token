multiline_comment|/*&n; *  linux/mm/vmalloc.c&n; *&n; *  Copyright (C) 1993  Linus Torvalds&n; */
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|struct|vm_struct
r_struct
id|vm_struct
(brace
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|addr
r_void
op_star
id|addr
suffix:semicolon
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
DECL|member|next
r_struct
id|vm_struct
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|vmlist
r_static
r_struct
id|vm_struct
op_star
id|vmlist
op_assign
l_int|NULL
suffix:semicolon
DECL|function|set_pgdir
r_static
r_inline
r_void
id|set_pgdir
c_func
(paren
r_int
r_int
id|address
comma
id|pgd_t
id|entry
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|for_each_task
c_func
(paren
id|p
)paren
op_star
id|pgd_offset
c_func
(paren
id|p-&gt;mm
comma
id|address
)paren
op_assign
id|entry
suffix:semicolon
)brace
DECL|function|free_area_pte
r_static
r_inline
r_void
id|free_area_pte
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
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
id|pmd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;free_area_pte: bad pmd (%08lx)&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|address
)paren
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
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|pte_t
id|page
op_assign
op_star
id|pte
suffix:semicolon
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|page
)paren
)paren
(brace
id|free_page
c_func
(paren
id|pte_page
c_func
(paren
id|page
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Whee.. Swapped out page in kernel page table&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|free_area_pmd
r_static
r_inline
r_void
id|free_area_pmd
c_func
(paren
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
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
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
l_string|&quot;free_area_pmd: bad pgd (%08lx)&bslash;n&quot;
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
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|free_area_pte
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
)paren
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
)brace
DECL|function|free_area_pages
r_static
r_void
id|free_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|free_area_pmd
c_func
(paren
id|dir
comma
id|address
comma
id|end
op_minus
id|address
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
id|invalidate
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|alloc_area_pte
r_static
r_inline
r_int
id|alloc_area_pte
c_func
(paren
id|pte_t
op_star
id|pte
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|end
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
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;alloc_area_pte: page already exists&bslash;n&quot;
)paren
suffix:semicolon
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
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte
c_func
(paren
id|page
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_area_pmd
r_static
r_inline
r_int
id|alloc_area_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
(brace
r_int
r_int
id|end
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
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|alloc_area_pte
c_func
(paren
id|pte
comma
id|address
comma
id|end
op_minus
id|address
)paren
)paren
r_return
op_minus
id|ENOMEM
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_area_pages
r_static
r_int
id|alloc_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc_kernel
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|alloc_area_pmd
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_pgdir
c_func
(paren
id|address
comma
op_star
id|dir
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
id|invalidate
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|remap_area_pte
r_static
r_inline
r_void
id|remap_area_pte
c_func
(paren
id|pte_t
op_star
id|pte
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
)paren
(brace
r_int
r_int
id|end
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
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;remap_area_pte: page already exists&bslash;n&quot;
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|mk_pte
c_func
(paren
id|offset
comma
id|PAGE_KERNEL
)paren
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|offset
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
)brace
DECL|function|remap_area_pmd
r_static
r_inline
r_int
id|remap_area_pmd
c_func
(paren
id|pmd_t
op_star
id|pmd
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
)paren
(brace
r_int
r_int
id|end
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
id|offset
op_sub_assign
id|address
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|remap_area_pte
c_func
(paren
id|pte
comma
id|address
comma
id|end
op_minus
id|address
comma
id|address
op_plus
id|offset
)paren
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
DECL|function|remap_area_pages
r_static
r_int
id|remap_area_pages
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|size
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|address
op_plus
id|size
suffix:semicolon
id|offset
op_sub_assign
id|address
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
op_amp
id|init_mm
comma
id|address
)paren
suffix:semicolon
r_while
c_loop
(paren
id|address
OL
id|end
)paren
(brace
id|pmd_t
op_star
id|pmd
op_assign
id|pmd_alloc_kernel
c_func
(paren
id|dir
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pmd
c_func
(paren
id|pmd
comma
id|address
comma
id|end
op_minus
id|address
comma
id|offset
op_plus
id|address
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|set_pgdir
c_func
(paren
id|address
comma
op_star
id|dir
)paren
suffix:semicolon
id|address
op_assign
(paren
id|address
op_plus
id|PGDIR_SIZE
)paren
op_amp
id|PGDIR_MASK
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
id|invalidate
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_vm_area
r_static
r_struct
id|vm_struct
op_star
id|get_vm_area
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
comma
op_star
id|area
suffix:semicolon
id|area
op_assign
(paren
r_struct
id|vm_struct
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|area
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
id|VMALLOC_START
suffix:semicolon
id|area-&gt;size
op_assign
id|size
op_plus
id|PAGE_SIZE
suffix:semicolon
id|area-&gt;next
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|vmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|size
op_plus
(paren
r_int
r_int
)paren
id|addr
OL
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
r_break
suffix:semicolon
id|addr
op_assign
(paren
r_void
op_star
)paren
(paren
id|tmp-&gt;size
op_plus
(paren
r_int
r_int
)paren
id|tmp-&gt;addr
)paren
suffix:semicolon
)brace
id|area-&gt;addr
op_assign
id|addr
suffix:semicolon
id|area-&gt;next
op_assign
op_star
id|p
suffix:semicolon
op_star
id|p
op_assign
id|area
suffix:semicolon
r_return
id|area
suffix:semicolon
)brace
DECL|function|vfree
r_void
id|vfree
c_func
(paren
r_void
op_star
id|addr
)paren
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
(paren
r_int
r_int
)paren
id|addr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Trying to vfree() bad address (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|vmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;addr
op_eq
id|addr
)paren
(brace
op_star
id|p
op_assign
id|tmp-&gt;next
suffix:semicolon
id|free_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|tmp-&gt;addr
)paren
comma
id|tmp-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to vfree() nonexistent vm area (%p)&bslash;n&quot;
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|vmalloc
r_void
op_star
id|vmalloc
c_func
(paren
r_int
r_int
id|size
)paren
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
OG
(paren
id|MAP_NR
c_func
(paren
id|high_memory
)paren
op_lshift
id|PAGE_SHIFT
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|area-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|alloc_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|addr
)paren
comma
id|size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Remap an arbitrary physical address space into the kernel virtual&n; * address space. Needed when the kernel wants to access high addresses&n; * directly.&n; */
DECL|function|vremap
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
(brace
r_void
op_star
id|addr
suffix:semicolon
r_struct
id|vm_struct
op_star
id|area
suffix:semicolon
r_if
c_cond
(paren
id|offset
OL
id|high_memory
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
l_int|NULL
suffix:semicolon
id|size
op_assign
id|PAGE_ALIGN
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
op_logical_or
id|size
OG
id|offset
op_plus
id|size
)paren
r_return
l_int|NULL
suffix:semicolon
id|area
op_assign
id|get_vm_area
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|area
)paren
r_return
l_int|NULL
suffix:semicolon
id|addr
op_assign
id|area-&gt;addr
suffix:semicolon
r_if
c_cond
(paren
id|remap_area_pages
c_func
(paren
id|VMALLOC_VMADDR
c_func
(paren
id|addr
)paren
comma
id|offset
comma
id|size
)paren
)paren
(brace
id|vfree
c_func
(paren
id|addr
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
DECL|function|vread
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
(brace
r_struct
id|vm_struct
op_star
op_star
id|p
comma
op_star
id|tmp
suffix:semicolon
r_char
op_star
id|vaddr
comma
op_star
id|buf_start
op_assign
id|buf
suffix:semicolon
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|vmlist
suffix:semicolon
(paren
id|tmp
op_assign
op_star
id|p
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|tmp-&gt;next
)paren
(brace
id|vaddr
op_assign
(paren
r_char
op_star
)paren
id|tmp-&gt;addr
suffix:semicolon
r_while
c_loop
(paren
id|addr
OL
id|vaddr
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
id|put_user
c_func
(paren
l_char|&squot;&bslash;0&squot;
comma
id|buf
op_increment
)paren
comma
id|addr
op_increment
comma
id|count
op_decrement
suffix:semicolon
)brace
id|n
op_assign
id|tmp-&gt;size
op_minus
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|addr
OG
id|vaddr
)paren
id|n
op_sub_assign
id|addr
op_minus
id|vaddr
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|n
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
r_goto
id|finished
suffix:semicolon
id|put_user
c_func
(paren
op_star
id|addr
op_increment
comma
id|buf
op_increment
)paren
comma
id|count
op_decrement
suffix:semicolon
)brace
)brace
id|finished
suffix:colon
r_return
id|buf
op_minus
id|buf_start
suffix:semicolon
)brace
eof
