multiline_comment|/*&n; *  arch/ppc/mm/init.c&n; *&n; *  Copyright (C) 1991, 1992, 1993, 1994  Linus Torvalds&n; *  Ported to PPC by Gary Thomas&n; *  Modified by Cort Dougan (cort@cs.nmt.edu)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_void
id|die_if_kernel
c_func
(paren
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|show_net_buffers
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|flush_hash_table
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|HASHSTATS
macro_line|#undef HASHSTATS
DECL|variable|_SDR1
r_int
r_int
id|_SDR1
suffix:semicolon
multiline_comment|/* Hardware SDR1 image */
DECL|variable|Hash
id|PTE
op_star
id|Hash
suffix:semicolon
DECL|variable|Hash_size
DECL|variable|Hash_mask
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
DECL|variable|end_of_DRAM
r_int
r_int
op_star
id|end_of_DRAM
suffix:semicolon
DECL|variable|cache_is_copyback
r_int
id|cache_is_copyback
op_assign
l_int|1
suffix:semicolon
DECL|variable|kernel_pages_are_copyback
r_int
id|kernel_pages_are_copyback
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Note: these need to be in &squot;data&squot; so they live over the boot */
DECL|variable|BeBox_IO_page
r_int
r_char
op_star
id|BeBox_IO_page
op_assign
l_int|0
suffix:semicolon
DECL|variable|isBeBox
r_int
r_int
id|isBeBox
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#ifdef HASHSTATS
r_extern
r_int
r_int
op_star
id|hashhits
suffix:semicolon
macro_line|#endif
DECL|function|__bad_pagetable
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;__bad_pagetable&quot;
)paren
suffix:semicolon
)brace
DECL|function|__bad_page
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;__bad_page&quot;
)paren
suffix:semicolon
)brace
DECL|function|show_mem
r_void
id|show_mem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|free
op_assign
l_int|0
comma
id|total
op_assign
l_int|0
comma
id|reserved
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
id|PTE
op_star
id|ptr
suffix:semicolon
r_int
r_int
id|full
op_assign
l_int|0
comma
id|overflow
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ti
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Mem-info:&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free swap:       %6dkB&bslash;n&quot;
comma
id|nr_swap_pages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
id|i
op_assign
id|MAP_NR
c_func
(paren
id|high_memory
)paren
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
id|total
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
id|reserved
op_increment
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
id|free
op_increment
suffix:semicolon
r_else
id|shared
op_add_assign
id|mem_map
(braket
id|i
)braket
dot
id|count
op_minus
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%lu pages of RAM&bslash;n&quot;
comma
id|total
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%lu free pages&bslash;n&quot;
comma
id|free
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%lu reserved pages&bslash;n&quot;
comma
id|reserved
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%lu pages shared&bslash;n&quot;
comma
id|shared
)paren
suffix:semicolon
id|show_buffers
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_NET
id|show_net_buffers
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef HASHSTATS
id|printk
c_func
(paren
l_string|&quot;Hash Hits %u entries (buckets)&bslash;n&quot;
comma
(paren
id|Hash_size
op_div
r_sizeof
(paren
r_struct
id|_PTE
)paren
)paren
op_div
l_int|8
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
(paren
id|Hash_size
op_div
r_sizeof
(paren
r_struct
id|_PTE
)paren
)paren
op_div
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|hashhits
(braket
id|i
)braket
op_ge
l_int|20
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[%lu] &bslash;t %lu&bslash;n&quot;
comma
id|i
comma
id|hashhits
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_for
c_loop
(paren
id|ptr
op_assign
id|Hash
suffix:semicolon
id|ptr
op_le
id|Hash
op_plus
id|Hash_size
suffix:semicolon
id|ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;v
)paren
(brace
id|full
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ptr-&gt;h
op_eq
l_int|1
)paren
id|overflow
op_increment
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;Hash Table: %dkB Buckets: %dk PTEs: %d/%d (%%%d full) %d overflowed&bslash;n&quot;
comma
id|Hash_size
op_rshift
l_int|10
comma
(paren
id|Hash_size
op_div
(paren
r_sizeof
(paren
id|PTE
)paren
op_star
l_int|8
)paren
)paren
op_rshift
l_int|10
comma
id|full
comma
id|Hash_size
op_div
r_sizeof
(paren
id|PTE
)paren
comma
(paren
id|full
op_star
l_int|100
)paren
op_div
(paren
id|Hash_size
op_div
r_sizeof
(paren
id|PTE
)paren
)paren
comma
id|overflow
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; Task  context    vsid0&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ti
op_assign
l_int|0
suffix:semicolon
id|ti
OL
id|NR_TASKS
suffix:semicolon
id|ti
op_increment
)paren
suffix:semicolon
(brace
r_if
c_cond
(paren
id|task
(braket
id|ti
)braket
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%5d %8x %8x&bslash;n&quot;
comma
id|task
(braket
id|ti
)braket
op_member_access_from_pointer
id|pid
comma
id|task
(braket
id|ti
)braket
op_member_access_from_pointer
id|mm-&gt;context
comma
(paren
(paren
id|SEGREG
op_star
)paren
id|task
(braket
id|ti
)braket
op_member_access_from_pointer
id|tss.segs
)paren
(braket
l_int|0
)braket
dot
id|vsid
)paren
suffix:semicolon
)brace
)brace
)brace
r_extern
r_int
r_int
id|free_area_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|function|paging_init
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
(brace
r_return
id|free_area_init
c_func
(paren
id|start_mem
comma
id|end_mem
)paren
suffix:semicolon
)brace
DECL|function|mem_init
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
(brace
r_int
id|codepages
op_assign
l_int|0
suffix:semicolon
r_int
id|datapages
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|tmp
suffix:semicolon
r_extern
r_int
id|etext
suffix:semicolon
id|end_mem
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|high_memory
op_assign
(paren
r_void
op_star
)paren
id|end_mem
suffix:semicolon
id|max_mapnr
op_assign
id|MAP_NR
c_func
(paren
id|end_mem
)paren
suffix:semicolon
multiline_comment|/* clear the zero-page */
id|memset
c_func
(paren
id|empty_zero_page
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
multiline_comment|/* mark usable pages in the mem_map[] */
id|start_mem
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start_mem
)paren
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|KERNELBASE
suffix:semicolon
id|tmp
OL
(paren
r_int
)paren
id|high_memory
suffix:semicolon
id|tmp
op_add_assign
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|tmp
OL
id|start_mem
)paren
(brace
id|set_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|etext
)paren
(brace
id|codepages
op_increment
suffix:semicolon
)brace
r_else
(brace
id|datapages
op_increment
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
id|clear_bit
c_func
(paren
id|PG_reserved
comma
op_amp
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|flags
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|tmp
)paren
)braket
dot
id|count
op_assign
l_int|1
suffix:semicolon
id|free_page
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|tmp
op_assign
id|nr_free_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Memory: %luk/%luk available (%dk kernel code, %dk data)&bslash;n&quot;
comma
id|tmp
op_rshift
l_int|10
comma
(paren
(paren
r_int
)paren
id|high_memory
op_minus
(paren
r_int
)paren
id|KERNELBASE
)paren
op_rshift
l_int|10
comma
id|codepages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
comma
id|datapages
op_lshift
(paren
id|PAGE_SHIFT
op_minus
l_int|10
)paren
)paren
suffix:semicolon
multiline_comment|/*&t;invalidate();*/
r_return
suffix:semicolon
)brace
DECL|function|si_meminfo
r_void
id|si_meminfo
c_func
(paren
r_struct
id|sysinfo
op_star
id|val
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
(paren
(paren
r_int
)paren
id|high_memory
op_amp
l_int|0x00FFFFFF
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;totalram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;sharedram
op_assign
l_int|0
suffix:semicolon
id|val-&gt;freeram
op_assign
id|nr_free_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;bufferram
op_assign
id|buffermem
suffix:semicolon
r_while
c_loop
(paren
id|i
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|PageReserved
c_func
(paren
id|mem_map
op_plus
id|i
)paren
)paren
r_continue
suffix:semicolon
id|val-&gt;totalram
op_increment
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_map
(braket
id|i
)braket
dot
id|count
)paren
r_continue
suffix:semicolon
id|val-&gt;sharedram
op_add_assign
id|mem_map
(braket
id|i
)braket
dot
id|count
op_minus
l_int|1
suffix:semicolon
)brace
id|val-&gt;totalram
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
id|val-&gt;sharedram
op_lshift_assign
id|PAGE_SHIFT
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|BAT0
id|BAT
id|BAT0
op_assign
(brace
(brace
l_int|0x80000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs -- supervisor mode valid */
l_int|1
comma
multiline_comment|/* vp -- user mode valid */
)brace
comma
(brace
l_int|0x80000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* write-through */
l_int|1
comma
multiline_comment|/* cache-inhibited */
l_int|0
comma
multiline_comment|/* memory coherence */
l_int|1
comma
multiline_comment|/* guarded */
id|BPP_RW
multiline_comment|/* protection */
)brace
)brace
suffix:semicolon
DECL|variable|BAT1
id|BAT
id|BAT1
op_assign
(brace
(brace
l_int|0xC0000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0xC0000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|1
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|BAT2
id|BAT
id|BAT2
op_assign
(brace
(brace
l_int|0x90000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* this gets set to amount of phys ram */
l_int|1
comma
multiline_comment|/* vs */
l_int|0
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|0
comma
multiline_comment|/* w */
l_int|0
comma
multiline_comment|/* i */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|BAT3
id|BAT
id|BAT3
op_assign
(brace
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|0
comma
multiline_comment|/* vs */
l_int|0
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|1
comma
multiline_comment|/* i (cache disabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
DECL|variable|TMP_BAT2
id|BAT
id|TMP_BAT2
op_assign
(brace
multiline_comment|/* 0x9XXXXXXX -&gt; 0x0XXXXXXX */
(brace
l_int|0x90000000
op_rshift
l_int|17
comma
multiline_comment|/* bepi */
id|BL_256M
comma
multiline_comment|/* bl */
l_int|1
comma
multiline_comment|/* vs */
l_int|1
comma
multiline_comment|/* vp */
)brace
comma
(brace
l_int|0x00000000
op_rshift
l_int|17
comma
multiline_comment|/* brpn */
l_int|1
comma
multiline_comment|/* w */
l_int|0
comma
multiline_comment|/* i (cache enabled) */
l_int|0
comma
multiline_comment|/* m */
l_int|0
comma
multiline_comment|/* g */
id|BPP_RW
multiline_comment|/* pp */
)brace
)brace
suffix:semicolon
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL 0
macro_line|#endif
multiline_comment|/*&n; * This code is called to create a minimal mapped environment.&n; * It is called with the MMU on, but with only a BAT register&n; * set up to cover the code/data.  After this routine runs,&n; * the BAT mapping is withdrawn and all mappings must be complete.&n; */
r_extern
r_char
id|_start
(braket
)braket
comma
id|_end
(braket
)braket
suffix:semicolon
DECL|function|MMU_init
r_void
id|MMU_init
c_func
(paren
r_void
)paren
(brace
r_extern
id|RESIDUAL
id|res
suffix:semicolon
r_extern
r_int
r_int
id|resptr
suffix:semicolon
r_int
id|i
comma
id|p
suffix:semicolon
id|SEGREG
op_star
id|segs
suffix:semicolon
multiline_comment|/* copy residual data */
r_if
c_cond
(paren
id|resptr
)paren
id|memcpy
c_func
(paren
op_amp
id|res
comma
(paren
r_void
op_star
)paren
(paren
id|resptr
op_plus
id|KERNELBASE
)paren
comma
r_sizeof
(paren
id|RESIDUAL
)paren
)paren
suffix:semicolon
r_else
id|bzero
c_func
(paren
op_amp
id|res
comma
r_sizeof
(paren
id|RESIDUAL
)paren
)paren
suffix:semicolon
multiline_comment|/* clearing bss probably clears this but... */
id|end_of_DRAM
op_assign
(paren
r_int
r_int
op_star
)paren
id|find_end_of_memory
c_func
(paren
)paren
suffix:semicolon
id|_SDR1
op_assign
(paren
(paren
r_int
r_int
)paren
id|Hash
op_minus
id|KERNELBASE
)paren
op_or
id|Hash_mask
suffix:semicolon
macro_line|#if 0&t;
id|printk
c_func
(paren
l_string|&quot;Hash      %08x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|Hash
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hash_mask %08x&bslash;n&quot;
comma
id|Hash_mask
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hash_size %08x&bslash;n&quot;
comma
id|Hash_size
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SDR1      %08x&bslash;n&quot;
comma
id|_SDR1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Segment registers */
id|segs
op_assign
(paren
id|SEGREG
op_star
)paren
id|init_task.tss.segs
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
id|segs
(braket
id|i
)braket
dot
id|ks
op_assign
l_int|0
suffix:semicolon
id|segs
(braket
id|i
)braket
dot
id|kp
op_assign
l_int|1
suffix:semicolon
macro_line|#if 1
r_if
c_cond
(paren
id|i
OL
l_int|8
)paren
id|segs
(braket
id|i
)braket
dot
id|vsid
op_assign
id|i
op_plus
l_int|10000
suffix:semicolon
r_else
macro_line|#else
r_if
c_cond
(paren
id|i
OL
l_int|8
)paren
id|segs
(braket
id|i
)braket
dot
id|vsid
op_assign
id|i
op_lshift
l_int|5
suffix:semicolon
macro_line|#endif&t;&t;  
id|segs
(braket
id|i
)braket
dot
id|vsid
op_assign
id|i
suffix:semicolon
)brace
multiline_comment|/* Hard map in any special local resources */
r_if
c_cond
(paren
id|isBeBox
(braket
l_int|0
)braket
)paren
(brace
multiline_comment|/* Map in one page for the BeBox motherboard I/O */
id|end_of_DRAM
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|end_of_DRAM
op_minus
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#if 0&t;&t;
id|BeBox_IO_page
op_assign
(paren
r_int
r_char
op_star
)paren
l_int|0x7FFFF000
suffix:semicolon
macro_line|#endif
id|BeBox_IO_page
op_assign
(paren
r_int
r_char
op_star
)paren
id|end_of_DRAM
suffix:semicolon
id|MMU_disable_cache_for_page
c_func
(paren
op_amp
id|init_task.tss
comma
id|BeBox_IO_page
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Insert(create) a hardware page table entry&n; */
DECL|function|MMU_hash_page
r_int
r_inline
id|MMU_hash_page
c_func
(paren
r_struct
id|thread_struct
op_star
id|tss
comma
r_int
r_int
id|va
comma
id|pte
op_star
id|pg
)paren
(brace
r_int
id|hash
comma
id|page_index
comma
id|segment
comma
id|i
comma
id|h
comma
id|_h
comma
id|api
comma
id|vsid
comma
id|perms
suffix:semicolon
id|PTE
op_star
id|_pte
comma
op_star
id|empty
comma
op_star
id|slot
suffix:semicolon
id|PTE
op_star
id|slot0
comma
op_star
id|slot1
suffix:semicolon
r_extern
r_char
id|_etext
suffix:semicolon
id|page_index
op_assign
(paren
(paren
r_int
)paren
id|va
op_amp
l_int|0x0FFFF000
)paren
op_rshift
l_int|12
suffix:semicolon
id|segment
op_assign
(paren
r_int
r_int
)paren
id|va
op_rshift
l_int|28
suffix:semicolon
id|api
op_assign
id|page_index
op_rshift
l_int|10
suffix:semicolon
id|vsid
op_assign
(paren
(paren
id|SEGREG
op_star
)paren
id|tss-&gt;segs
)paren
(braket
id|segment
)braket
dot
id|vsid
suffix:semicolon
id|empty
op_assign
id|slot
op_assign
(paren
id|PTE
op_star
)paren
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|va
op_le
id|_etext
)paren
op_logical_and
(paren
id|va
op_ge
id|KERNELBASE
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MMU_hash_page: called on kernel page mapped with bats va %x&bslash;n&quot;
comma
id|va
)paren
suffix:semicolon
)brace
multiline_comment|/* check first hash bucket */
id|h
op_assign
l_int|0
suffix:semicolon
id|hash
op_assign
id|page_index
op_xor
id|vsid
suffix:semicolon
id|hash
op_and_assign
l_int|0x3FF
op_or
(paren
id|Hash_mask
op_lshift
l_int|10
)paren
suffix:semicolon
id|hash
op_mul_assign
l_int|8
suffix:semicolon
multiline_comment|/* 8 entries in each bucket */
id|_pte
op_assign
op_amp
id|Hash
(braket
id|hash
)braket
suffix:semicolon
id|slot0
op_assign
id|_pte
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
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|_pte
op_increment
)paren
(brace
r_if
c_cond
(paren
id|_pte-&gt;v
op_logical_and
id|_pte-&gt;vsid
op_eq
id|vsid
op_logical_and
id|_pte-&gt;h
op_eq
id|h
op_logical_and
id|_pte-&gt;api
op_eq
id|api
)paren
(brace
id|slot
op_assign
id|_pte
suffix:semicolon
r_goto
id|found_it
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|empty
op_eq
l_int|NULL
)paren
op_logical_and
(paren
op_logical_neg
id|_pte-&gt;v
)paren
)paren
(brace
id|empty
op_assign
id|_pte
suffix:semicolon
id|_h
op_assign
id|h
suffix:semicolon
)brace
)brace
multiline_comment|/* check second hash bucket */
id|h
op_assign
l_int|1
suffix:semicolon
id|hash
op_assign
id|page_index
op_xor
id|vsid
suffix:semicolon
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
id|hash
op_and_assign
l_int|0x3FF
op_or
(paren
id|Hash_mask
op_lshift
l_int|10
)paren
suffix:semicolon
id|hash
op_mul_assign
l_int|8
suffix:semicolon
multiline_comment|/* 8 entries in each bucket */
id|_pte
op_assign
op_amp
id|Hash
(braket
id|hash
)braket
suffix:semicolon
id|slot1
op_assign
id|_pte
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
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|_pte
op_increment
)paren
(brace
r_if
c_cond
(paren
id|_pte-&gt;v
op_logical_and
id|_pte-&gt;vsid
op_eq
id|vsid
op_logical_and
id|_pte-&gt;h
op_eq
id|h
op_logical_and
id|_pte-&gt;api
op_eq
id|api
)paren
(brace
id|slot
op_assign
id|_pte
suffix:semicolon
r_goto
id|found_it
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|empty
op_eq
l_int|NULL
)paren
op_logical_and
(paren
op_logical_neg
id|_pte-&gt;v
)paren
)paren
(brace
id|empty
op_assign
id|_pte
suffix:semicolon
id|_h
op_assign
id|h
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|empty
op_eq
(paren
id|PTE
op_star
)paren
l_int|NULL
)paren
(brace
macro_line|#if 1
id|printk
c_func
(paren
l_string|&quot;Both hash buckets full! va %x vsid %x current %s (%d)&bslash;n&quot;
comma
id|va
comma
id|vsid
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
macro_line|#endif
id|slot
op_assign
id|slot1
suffix:semicolon
id|h
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|slot
op_assign
id|empty
suffix:semicolon
id|h
op_assign
id|_h
suffix:semicolon
)brace
id|found_it
suffix:colon
macro_line|#ifdef HASHSTATS
id|hashhits
(braket
id|hash
)braket
op_increment
suffix:semicolon
macro_line|#endif
id|_tlbie
c_func
(paren
id|va
)paren
suffix:semicolon
multiline_comment|/* Clear TLB */
multiline_comment|/* Fill in table */
id|slot-&gt;v
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;vsid
op_assign
id|vsid
suffix:semicolon
id|slot-&gt;h
op_assign
id|h
suffix:semicolon
id|slot-&gt;api
op_assign
id|api
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|pg-&gt;page_num
op_lshift
l_int|12
)paren
op_amp
l_int|0xF0000000
)paren
op_eq
id|KERNELBASE
)paren
(brace
id|slot-&gt;rpn
op_assign
id|pg-&gt;page_num
op_minus
(paren
id|KERNELBASE
op_rshift
l_int|12
)paren
suffix:semicolon
)brace
r_else
(brace
id|slot-&gt;rpn
op_assign
id|pg-&gt;page_num
suffix:semicolon
)brace
id|slot-&gt;r
op_assign
l_int|0
suffix:semicolon
id|slot-&gt;c
op_assign
l_int|0
suffix:semicolon
id|slot-&gt;i
op_assign
l_int|0
suffix:semicolon
id|slot-&gt;g
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cache_is_copyback
)paren
(brace
r_if
c_cond
(paren
id|kernel_pages_are_copyback
op_logical_or
(paren
id|pg-&gt;flags
op_amp
id|_PAGE_USER
)paren
op_logical_or
(paren
id|va
OL
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
)paren
(brace
multiline_comment|/* All User &amp; Kernel TEXT pages are copy-back */
id|slot-&gt;w
op_assign
l_int|0
suffix:semicolon
id|slot-&gt;m
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Kernel DATA pages are write-thru */
id|slot-&gt;w
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;m
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|slot-&gt;w
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;m
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pg-&gt;flags
op_amp
id|_PAGE_USER
)paren
(brace
r_if
c_cond
(paren
id|pg-&gt;flags
op_amp
id|_PAGE_RW
)paren
(brace
multiline_comment|/* Read/write page */
id|perms
op_assign
id|PP_RWRW
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Read only page */
id|perms
op_assign
id|PP_RWRX
suffix:semicolon
id|perms
op_assign
id|PP_RXRX
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Kernel pages */
id|perms
op_assign
id|PP_RWRW
suffix:semicolon
id|perms
op_assign
id|PP_RWXX
suffix:semicolon
)brace
id|slot-&gt;pp
op_assign
id|perms
suffix:semicolon
r_return
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Disable cache for a particular page&n; */
DECL|function|MMU_disable_cache_for_page
id|MMU_disable_cache_for_page
c_func
(paren
r_struct
id|thread_struct
op_star
id|tss
comma
r_int
r_int
id|va
)paren
(brace
r_int
id|hash
comma
id|page_index
comma
id|segment
comma
id|i
comma
id|h
comma
id|_h
comma
id|api
comma
id|vsid
comma
id|perms
suffix:semicolon
id|PTE
op_star
id|_pte
comma
op_star
id|empty
comma
op_star
id|slot
suffix:semicolon
id|PTE
op_star
id|slot0
comma
op_star
id|slot1
suffix:semicolon
r_extern
r_char
id|_etext
suffix:semicolon
id|page_index
op_assign
(paren
(paren
r_int
)paren
id|va
op_amp
l_int|0x0FFFF000
)paren
op_rshift
l_int|12
suffix:semicolon
id|segment
op_assign
(paren
r_int
r_int
)paren
id|va
op_rshift
l_int|28
suffix:semicolon
id|api
op_assign
id|page_index
op_rshift
l_int|10
suffix:semicolon
id|vsid
op_assign
(paren
(paren
id|SEGREG
op_star
)paren
id|tss-&gt;segs
)paren
(braket
id|segment
)braket
dot
id|vsid
suffix:semicolon
id|empty
op_assign
id|slot
op_assign
(paren
id|PTE
op_star
)paren
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|_h
op_assign
l_int|0
suffix:semicolon
id|_h
OL
l_int|2
suffix:semicolon
id|_h
op_increment
)paren
(brace
id|hash
op_assign
id|page_index
op_xor
id|vsid
suffix:semicolon
r_if
c_cond
(paren
id|_h
)paren
(brace
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
multiline_comment|/* Secondary hash uses ones-complement */
)brace
id|hash
op_and_assign
l_int|0x3FF
op_or
(paren
id|Hash_mask
op_lshift
l_int|10
)paren
suffix:semicolon
id|hash
op_mul_assign
l_int|8
suffix:semicolon
multiline_comment|/* Eight entries / hash bucket */
id|_pte
op_assign
op_amp
id|Hash
(braket
id|hash
)braket
suffix:semicolon
multiline_comment|/* Save slot addresses in case we have to purge */
r_if
c_cond
(paren
id|_h
)paren
(brace
id|slot1
op_assign
id|_pte
suffix:semicolon
)brace
r_else
(brace
id|slot0
op_assign
id|_pte
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|_pte
op_increment
)paren
(brace
r_if
c_cond
(paren
id|_pte-&gt;v
op_logical_and
id|_pte-&gt;vsid
op_eq
id|vsid
op_logical_and
id|_pte-&gt;h
op_eq
id|_h
op_logical_and
id|_pte-&gt;api
op_eq
id|api
)paren
(brace
multiline_comment|/* Found it! */
id|h
op_assign
id|_h
suffix:semicolon
id|slot
op_assign
id|_pte
suffix:semicolon
r_goto
id|found_it
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|empty
op_eq
(paren
id|PTE
op_star
)paren
l_int|NULL
)paren
op_logical_and
op_logical_neg
id|_pte-&gt;v
)paren
(brace
id|h
op_assign
id|_h
suffix:semicolon
id|empty
op_assign
id|_pte
suffix:semicolon
)brace
)brace
)brace
id|found_it
suffix:colon
id|_tlbie
c_func
(paren
id|va
)paren
suffix:semicolon
multiline_comment|/* Clear TLB */
id|slot-&gt;i
op_assign
l_int|1
suffix:semicolon
id|slot-&gt;m
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * invalidate a hardware hash table pte&n; */
DECL|function|MMU_invalidate_page
r_inline
r_void
id|MMU_invalidate_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|va
)paren
(brace
r_int
id|hash
comma
id|page_index
comma
id|segment
comma
id|i
comma
id|h
comma
id|_h
comma
id|api
comma
id|vsid
comma
id|perms
suffix:semicolon
id|PTE
op_star
id|_pte
comma
op_star
id|slot
suffix:semicolon
r_int
id|flags
op_assign
l_int|0
suffix:semicolon
id|page_index
op_assign
(paren
(paren
r_int
)paren
id|va
op_amp
l_int|0x0FFFF000
)paren
op_rshift
l_int|12
suffix:semicolon
id|segment
op_assign
(paren
r_int
r_int
)paren
id|va
op_rshift
l_int|28
suffix:semicolon
id|api
op_assign
id|page_index
op_rshift
l_int|10
suffix:semicolon
id|vsid
op_assign
id|mm-&gt;context
op_or
id|segment
suffix:semicolon
r_for
c_loop
(paren
id|_h
op_assign
l_int|0
suffix:semicolon
id|_h
OL
l_int|2
suffix:semicolon
id|_h
op_increment
)paren
(brace
id|hash
op_assign
id|page_index
op_xor
id|vsid
suffix:semicolon
r_if
c_cond
(paren
id|_h
)paren
(brace
id|hash
op_assign
op_complement
id|hash
suffix:semicolon
multiline_comment|/* Secondary hash uses ones-complement */
)brace
id|hash
op_and_assign
l_int|0x3FF
op_or
(paren
id|Hash_mask
op_lshift
l_int|10
)paren
suffix:semicolon
id|hash
op_mul_assign
l_int|8
suffix:semicolon
multiline_comment|/* Eight entries / hash bucket */
id|_pte
op_assign
op_amp
id|Hash
(braket
id|hash
)braket
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
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|_pte
op_increment
)paren
(brace
r_if
c_cond
(paren
id|_pte-&gt;v
op_logical_and
id|_pte-&gt;vsid
op_eq
id|vsid
op_logical_and
id|_pte-&gt;h
op_eq
id|_h
op_logical_and
id|_pte-&gt;api
op_eq
id|api
)paren
(brace
multiline_comment|/* Found it! */
id|_tlbie
c_func
(paren
id|va
)paren
suffix:semicolon
multiline_comment|/* Clear TLB */
r_if
c_cond
(paren
id|_pte-&gt;r
)paren
id|flags
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_if
c_cond
(paren
id|_pte-&gt;c
)paren
id|flags
op_or_assign
id|_PAGE_DIRTY
suffix:semicolon
id|_pte-&gt;v
op_assign
l_int|0
suffix:semicolon
r_return
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
)brace
id|_tlbie
c_func
(paren
id|va
)paren
suffix:semicolon
r_return
(paren
id|flags
)paren
suffix:semicolon
)brace
r_inline
r_void
DECL|function|flush_cache_all
id|flush_cache_all
c_func
(paren
r_void
)paren
(brace
)brace
r_inline
r_void
DECL|function|flush_cache_mm
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
)brace
r_inline
r_void
DECL|function|flush_cache_page
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
id|va
)paren
(brace
)brace
r_inline
r_void
DECL|function|flush_cache_range
id|flush_cache_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|va_start
comma
r_int
r_int
id|va_end
)paren
(brace
)brace
r_inline
r_void
DECL|function|cache_mode
id|cache_mode
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
id|cache_is_copyback
op_assign
id|ints
(braket
l_int|0
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; * TLB flushing:&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(mm, start, end) flushes a range of pages&n; *&n; * since the hardware hash table functions as an extension of the&n; * tlb as far as the linux tables are concerned, flush them too.&n; *    -- Cort&n; */
r_inline
r_void
DECL|function|flush_tlb
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|PTE
op_star
id|ptep
suffix:semicolon
r_int
id|context
op_assign
id|current-&gt;mm-&gt;context
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|v
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|v
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
multiline_comment|/* for every virtual memory address in the current context -- flush&n;     the hash table */
r_while
c_loop
(paren
id|v
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|v-&gt;vm_start
suffix:semicolon
id|i
op_le
id|v-&gt;vm_end
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|MMU_invalidate_page
c_func
(paren
id|v-&gt;vm_mm
comma
id|i
)paren
suffix:semicolon
)brace
id|v
op_assign
id|v-&gt;vm_next
suffix:semicolon
)brace
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/* flush all tlb/hash table entries except for kernels&n;&n;   although the kernel is mapped with the bats, it&squot;s dynamic areas&n;   obtained via kmalloc are mapped by the seg regs&n;                      -- Cort&n;   */
r_inline
r_void
DECL|function|flush_tlb_all
id|flush_tlb_all
c_func
(paren
r_void
)paren
(brace
id|PTE
op_star
id|ptep
suffix:semicolon
multiline_comment|/* flush hash table */
r_for
c_loop
(paren
id|ptep
op_assign
id|Hash
suffix:semicolon
id|ptep
OL
(paren
id|PTE
op_star
)paren
(paren
(paren
r_int
r_int
)paren
id|Hash
op_plus
id|Hash_size
)paren
suffix:semicolon
id|ptep
op_increment
)paren
(brace
multiline_comment|/* if not kernel vsids 0-7 (vsid greater than that for process 0)*/
r_if
c_cond
(paren
(paren
id|ptep-&gt;vsid
OG
l_int|7
)paren
op_logical_and
(paren
id|ptep-&gt;v
)paren
)paren
(brace
id|ptep-&gt;v
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
r_inline
r_void
DECL|function|flush_tlb_mm
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|PTE
op_star
id|ptep
suffix:semicolon
r_int
id|context
op_assign
id|mm-&gt;context
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|v
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
id|v
op_assign
id|mm-&gt;mmap
suffix:semicolon
r_while
c_loop
(paren
id|v
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
id|v-&gt;vm_start
suffix:semicolon
id|i
op_le
id|v-&gt;vm_end
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|MMU_invalidate_page
c_func
(paren
id|v-&gt;vm_mm
comma
id|i
)paren
suffix:semicolon
)brace
id|v
op_assign
id|v-&gt;vm_next
suffix:semicolon
)brace
id|_tlbia
c_func
(paren
)paren
suffix:semicolon
)brace
r_inline
r_void
DECL|function|flush_tlb_page
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
id|vmaddr
)paren
(brace
id|MMU_invalidate_page
c_func
(paren
id|vma-&gt;vm_mm
comma
id|vmaddr
)paren
suffix:semicolon
)brace
multiline_comment|/* for each page addr in the range, call mmu_invalidat_page()&n;   if the range is very large and the hash table is small it might be faster to&n;   do a search of the hash table and just invalidate pages that are in the range&n;   but that&squot;s for study later.&n;        -- Cort&n;   */
r_inline
r_void
DECL|function|flush_tlb_range
id|flush_tlb_range
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
id|start
comma
r_int
id|end
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
op_minus
id|PAGE_SIZE
)paren
suffix:semicolon
id|i
OL
id|PAGE_ALIGN
c_func
(paren
id|end
)paren
suffix:semicolon
id|i
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|MMU_invalidate_page
c_func
(paren
id|mm
comma
id|i
)paren
suffix:semicolon
)brace
)brace
r_inline
r_void
DECL|function|flush_page_to_ram
id|flush_page_to_ram
c_func
(paren
r_int
r_int
id|page
)paren
(brace
)brace
eof
