multiline_comment|/*&n; * $Id: idle.c,v 1.68 1999/10/15 18:16:03 cort Exp $&n; *&n; * Idle daemon for PowerPC.  Idle daemon will handle any action&n; * that needs to be taken when the system becomes idle.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
r_void
id|zero_paged
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|power_save
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
r_inline
id|htab_reclaim
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|htab_reclaim_on
r_int
r_int
id|htab_reclaim_on
op_assign
l_int|0
suffix:semicolon
DECL|variable|zero_paged_on
r_int
r_int
id|zero_paged_on
op_assign
l_int|0
suffix:semicolon
DECL|variable|powersave_nap
r_int
r_int
id|powersave_nap
op_assign
l_int|0
suffix:semicolon
DECL|variable|zero_cache
r_int
r_int
op_star
id|zero_cache
suffix:semicolon
multiline_comment|/* head linked list of pre-zero&squot;d pages */
DECL|variable|zerototal
id|atomic_t
id|zerototal
suffix:semicolon
multiline_comment|/* # pages zero&squot;d over time */
DECL|variable|zeropage_hits
id|atomic_t
id|zeropage_hits
suffix:semicolon
multiline_comment|/* # zero&squot;d pages request that we&squot;ve done */
DECL|variable|zero_sz
id|atomic_t
id|zero_sz
suffix:semicolon
multiline_comment|/* # currently pre-zero&squot;d pages */
DECL|variable|zeropage_calls
id|atomic_t
id|zeropage_calls
suffix:semicolon
multiline_comment|/* # zero&squot;d pages request that&squot;ve been made */
DECL|function|idled
r_int
id|idled
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless loop with no priority at all */
id|current-&gt;nice
op_assign
l_int|20
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
id|init_idle
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*if ( !current-&gt;need_resched &amp;&amp; zero_paged_on ) zero_paged();*/
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
op_logical_and
id|htab_reclaim_on
)paren
id|htab_reclaim
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
id|power_save
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
macro_line|#endif
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * SMP entry into the idle task - calls the same thing as the&n; * non-smp versions. -- Cort&n; */
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
id|idled
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Mark &squot;zombie&squot; pte&squot;s in the hash table as invalid.&n; * This improves performance for the hash table reload code&n; * a bit since we don&squot;t consider unused pages as valid.&n; *  -- Cort&n; */
DECL|variable|reclaim_ptr
id|PTE
op_star
id|reclaim_ptr
op_assign
l_int|0
suffix:semicolon
DECL|function|htab_reclaim
r_void
r_inline
id|htab_reclaim
c_func
(paren
r_void
)paren
(brace
macro_line|#ifndef CONFIG_8xx&t;&t;
macro_line|#if 0&t;
id|PTE
op_star
id|ptr
comma
op_star
id|start
suffix:semicolon
r_static
r_int
id|dir
op_assign
l_int|1
suffix:semicolon
macro_line|#endif&t;
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_int
r_int
id|valid
op_assign
l_int|0
suffix:semicolon
r_extern
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
r_extern
r_int
r_int
id|Hash_size
suffix:semicolon
multiline_comment|/* if we don&squot;t have a htab */
r_if
c_cond
(paren
id|Hash_size
op_eq
l_int|0
)paren
r_return
suffix:semicolon
macro_line|#if 0&t;
multiline_comment|/* find a random place in the htab to start each time */
id|start
op_assign
op_amp
id|Hash
(braket
id|jiffies
op_mod
(paren
id|Hash_size
op_div
r_sizeof
(paren
id|PTE
)paren
)paren
)braket
suffix:semicolon
multiline_comment|/* go a different direction each time */
id|dir
op_mul_assign
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|start
suffix:semicolon
op_logical_neg
id|current-&gt;need_resched
op_logical_and
(paren
id|ptr
op_ne
id|Hash_end
)paren
op_logical_and
(paren
id|ptr
op_ne
id|Hash
)paren
suffix:semicolon
id|ptr
op_add_assign
id|dir
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
op_logical_neg
id|reclaim_ptr
)paren
id|reclaim_ptr
op_assign
id|Hash
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
(brace
id|reclaim_ptr
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|reclaim_ptr
op_eq
id|Hash_end
)paren
id|reclaim_ptr
op_assign
id|Hash
suffix:semicolon
macro_line|#endif&t;  
r_if
c_cond
(paren
op_logical_neg
id|reclaim_ptr-&gt;v
)paren
r_continue
suffix:semicolon
id|valid
op_assign
l_int|0
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
id|current-&gt;need_resched
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* if this vsid/context is in use */
r_if
c_cond
(paren
(paren
id|reclaim_ptr-&gt;vsid
op_rshift
l_int|4
)paren
op_eq
id|p-&gt;mm-&gt;context
)paren
(brace
id|valid
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|valid
)paren
r_continue
suffix:semicolon
multiline_comment|/* this pte isn&squot;t used */
id|reclaim_ptr-&gt;v
op_assign
l_int|0
suffix:semicolon
)brace
id|out
suffix:colon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|printk
c_func
(paren
l_string|&quot;need_resched: %lx&bslash;n&quot;
comma
id|current-&gt;need_resched
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_8xx */
)brace
macro_line|#if 0
multiline_comment|/*&n; * Returns a pre-zero&squot;d page from the list otherwise returns&n; * NULL.&n; */
r_int
r_int
id|get_zero_page_fast
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|page
op_assign
l_int|0
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|zero_cache_calls
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zero_quicklist
)paren
(brace
multiline_comment|/* atomically remove this page from the list */
r_register
r_int
r_int
id|tmp
suffix:semicolon
id|asm
(paren
l_string|&quot;101:lwarx  %1,0,%3&bslash;n&quot;
multiline_comment|/* reserve zero_cache */
l_string|&quot;    lwz    %0,0(%1)&bslash;n&quot;
multiline_comment|/* get next -- new zero_cache */
l_string|&quot;    stwcx. %0,0,%3&bslash;n&quot;
multiline_comment|/* update zero_cache */
l_string|&quot;    bne-   101b&bslash;n&quot;
multiline_comment|/* if lost reservation try again */
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|page
)paren
comma
l_string|&quot;+m&quot;
(paren
id|zero_cache
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|zero_quicklist
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* if another cpu beat us above this can happen -- Cort */
r_if
c_cond
(paren
id|page
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */&t;&t;
multiline_comment|/* we can update zerocount after the fact since it is not&n;&t;&t; * used for anything but control of a loop which doesn&squot;t&n;&t;&t; * matter since it won&squot;t affect anything if it zeros one&n;&t;&t; * less page -- Cort&n;&t;&t; */
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zero_cache_hits
)paren
suffix:semicolon
id|atomic_dec
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zero_cache_sz
)paren
suffix:semicolon
multiline_comment|/* zero out the pointer to next in the page */
op_star
(paren
r_int
r_int
op_star
)paren
id|page
op_assign
l_int|0
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Experimental stuff to zero out pages in the idle task&n; * to speed up get_free_pages(). Zero&squot;s out pages until&n; * we&squot;ve reached the limit of zero&squot;d pages.  We handle&n; * reschedule()&squot;s in here so when we return we know we&squot;ve&n; * zero&squot;d all we need to for now.&n; */
r_int
id|zero_cache_water
(braket
l_int|2
)braket
op_assign
(brace
l_int|25
comma
l_int|96
)brace
suffix:semicolon
multiline_comment|/* high and low water marks for zero cache */
r_void
id|zero_paged
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pageptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* current page being zero&squot;d */
r_int
r_int
id|bytecount
op_assign
l_int|0
suffix:semicolon
r_register
r_int
r_int
id|tmp
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|zero_cache_sz
)paren
op_ge
id|zero_cache_water
(braket
l_int|0
)braket
)paren
r_return
suffix:semicolon
r_while
c_loop
(paren
(paren
id|atomic_read
c_func
(paren
op_amp
id|zero_cache_sz
)paren
OL
id|zero_cache_water
(braket
l_int|1
)braket
)paren
op_logical_and
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * Mark a page as reserved so we can mess with it&n;&t;&t; * If we&squot;re interrupted we keep this page and our place in it&n;&t;&t; * since we validly hold it and it&squot;s reserved for us.&n;&t;&t; */
id|pageptr
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_ATOMIC
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pageptr
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make the page no cache so we don&squot;t blow our cache with 0&squot;s&n;&t;&t; */
id|pte
op_assign
id|find_pte
c_func
(paren
op_amp
id|init_mm
comma
id|pageptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pte NULL in zero_paged()&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte_uncache
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|find_vma
c_func
(paren
op_amp
id|init_mm
comma
id|pageptr
)paren
comma
id|pageptr
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Important here to not take time away from real processes.&n;&t;&t; */
r_for
c_loop
(paren
id|bytecount
op_assign
l_int|0
suffix:semicolon
id|bytecount
OL
id|PAGE_SIZE
suffix:semicolon
id|bytecount
op_add_assign
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|bytecount
op_plus
id|pageptr
)paren
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If we finished zero-ing out a page add this page to&n;&t;&t; * the zero_cache atomically -- we can&squot;t use&n;&t;&t; * down/up since we can&squot;t sleep in idle.&n;&t;&t; * Disabling interrupts is also a bad idea since we would&n;&t;&t; * steal time away from real processes.&n;&t;&t; * We can also have several zero_paged&squot;s running&n;&t;&t; * on different processors so we can&squot;t interfere with them.&n;&t;&t; * So we update the list atomically without locking it.&n;&t;&t; * -- Cort&n;&t;&t; */
multiline_comment|/* turn cache on for this page */
id|pte_cache
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|find_vma
c_func
(paren
op_amp
id|init_mm
comma
id|pageptr
)paren
comma
id|pageptr
)paren
suffix:semicolon
multiline_comment|/* atomically add this page to the list */
id|asm
(paren
l_string|&quot;101:lwarx  %0,0,%2&bslash;n&quot;
multiline_comment|/* reserve zero_cache */
l_string|&quot;    stw    %0,0(%3)&bslash;n&quot;
multiline_comment|/* update *pageptr */
macro_line|#ifdef CONFIG_SMP
l_string|&quot;    sync&bslash;n&quot;
multiline_comment|/* let store settle */
macro_line|#endif&t;&t;&t;
l_string|&quot;    stwcx. %3,0,%2&bslash;n&quot;
multiline_comment|/* update zero_cache in mem */
l_string|&quot;    bne-   101b&bslash;n&quot;
multiline_comment|/* if lost reservation try again */
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;+m&quot;
(paren
id|zero_quicklist
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|zero_quicklist
)paren
comma
l_string|&quot;r&quot;
(paren
id|pageptr
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This variable is used in the above loop and nowhere&n;&t;&t; * else so the worst that could happen is we would&n;&t;&t; * zero out one more or one less page than we want&n;&t;&t; * per processor on the machine.  This is because&n;&t;&t; * we could add our page to the list but not have&n;&t;&t; * zerocount updated yet when another processor&n;&t;&t; * reads it.  -- Cort&n;&t;&t; */
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zero_cache_sz
)paren
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zero_cache_total
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|power_save
r_void
id|power_save
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|msr
comma
id|hid0
suffix:semicolon
multiline_comment|/* only sleep on the 603-family/750 processors */
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|3
suffix:colon
multiline_comment|/* 603 */
r_case
l_int|6
suffix:colon
multiline_comment|/* 603e */
r_case
l_int|7
suffix:colon
multiline_comment|/* 603ev */
r_case
l_int|8
suffix:colon
multiline_comment|/* 750 */
r_case
l_int|12
suffix:colon
multiline_comment|/* 7400 */
id|save_flags
c_func
(paren
id|msr
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
(brace
id|asm
c_func
(paren
l_string|&quot;mfspr %0,1008&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|hid0
)paren
suffix:colon
)paren
suffix:semicolon
id|hid0
op_and_assign
op_complement
(paren
id|HID0_NAP
op_or
id|HID0_SLEEP
op_or
id|HID0_DOZE
)paren
suffix:semicolon
id|hid0
op_or_assign
(paren
id|powersave_nap
ques
c_cond
id|HID0_NAP
suffix:colon
id|HID0_DOZE
)paren
op_or
id|HID0_DPM
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mtspr 1008,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|hid0
)paren
)paren
suffix:semicolon
multiline_comment|/* set the POW bit in the MSR, and enable interrupts&n;&t;&t;&t; * so we wake up sometime! */
id|__sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* this keeps rtl from getting confused -- Cort */
id|_nmask_and_or_msr
c_func
(paren
l_int|0
comma
id|MSR_POW
op_or
id|MSR_EE
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|msr
)paren
suffix:semicolon
r_default
suffix:colon
r_return
suffix:semicolon
)brace
)brace
eof
