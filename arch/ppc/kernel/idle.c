multiline_comment|/*&n; * $Id: idle.c,v 1.13 1998/01/06 06:44:55 cort Exp $&n; *&n; * Idle daemon for PowerPC.  Idle daemon will handle any action&n; * that needs to be taken when the system becomes idle.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
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
macro_line|#include &lt;asm/smp_lock.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
r_int
id|zero_paged
c_func
(paren
r_void
op_star
id|unused
)paren
suffix:semicolon
r_void
r_inline
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
DECL|function|idled
r_int
id|idled
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_int
id|ret
op_assign
op_minus
id|EPERM
suffix:semicolon
multiline_comment|/*&n;&t; * want one per cpu since it would be nice to have all&n;&t; * processors who aren&squot;t doing anything&n;&t; * zero-ing pages since this daemon is lock-free&n;&t; * -- Cort&n;&t; */
multiline_comment|/* kernel_thread(zero_paged, NULL, 0); */
macro_line|#ifdef __SMP__&t;
id|printk
c_func
(paren
l_string|&quot;SMP %d: in idle.  current = %s/%d&bslash;n&quot;
comma
id|current-&gt;processor
comma
id|current-&gt;comm
comma
id|current-&gt;pid
)paren
suffix:semicolon
macro_line|#endif /* __SMP__ */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/* endless loop with no priority at all */
id|current-&gt;priority
op_assign
op_minus
l_int|100
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
multiline_comment|/* endless idle loop with no priority at all */
multiline_comment|/* htab_reclaim(); */
id|schedule
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifndef __SMP__
multiline_comment|/* can&squot;t do this on smp since second processor&n;&t;&t;   will never wake up -- Cort */
multiline_comment|/* power_save(); */
macro_line|#endif /* __SMP__  */
)brace
id|ret
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Mark &squot;zombie&squot; pte&squot;s in the hash table as invalid.&n; * This improves performance for the hash table reload code&n; * a bit since we don&squot;t consider unused pages as valid.&n; * I haven&squot;t done any rigorous performance analysis yet&n; * so it&squot;s still experimental and turned off here.&n; *  -- Cort&n; */
DECL|function|htab_reclaim
r_void
r_inline
id|htab_reclaim
c_func
(paren
r_void
)paren
(brace
id|PTE
op_star
id|ptr
comma
op_star
id|start
suffix:semicolon
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
multiline_comment|/*lock_dcache();*/
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
id|ptr
)paren
)paren
)braket
suffix:semicolon
r_for
c_loop
(paren
id|ptr
op_assign
id|start
suffix:semicolon
id|ptr
OL
id|Hash_end
suffix:semicolon
id|ptr
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ptr
op_eq
id|start
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ptr
op_eq
id|Hash_end
)paren
id|ptr
op_assign
id|Hash
suffix:semicolon
id|valid
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ptr-&gt;v
)paren
r_continue
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
id|need_resched
)paren
(brace
multiline_comment|/*unlock_dcache();*/
r_return
suffix:semicolon
)brace
multiline_comment|/* if this vsid/context is in use */
r_if
c_cond
(paren
(paren
id|ptr-&gt;vsid
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
id|ptr-&gt;v
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*unlock_dcache();*/
)brace
multiline_comment|/*&n; * Syscall entry into the idle task. -- Cort&n; */
DECL|function|sys_idle
id|asmlinkage
r_int
id|sys_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
(brace
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|idled
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* should never execute this but it makes gcc happy -- Cort */
)brace
macro_line|#ifdef __SMP__
multiline_comment|/*&n; * SMP entry into the idle task - calls the same thing as the&n; * non-smp versions. -- Cort&n; */
DECL|function|cpu_idle
r_int
id|cpu_idle
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|idled
c_func
(paren
id|unused
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* __SMP__ */
multiline_comment|/*&n; * vars for idle task zero&squot;ing out pages&n; */
DECL|variable|zero_list
r_int
r_int
id|zero_list
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* head linked list of pre-zero&squot;d pages */
DECL|variable|bytecount
r_int
r_int
id|bytecount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* pointer into the currently being zero&squot;d page */
DECL|variable|zerocount
r_int
r_int
id|zerocount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # currently pre-zero&squot;d pages */
DECL|variable|zerototal
r_int
r_int
id|zerototal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # pages zero&squot;d over time -- for ooh&squot;s and ahhh&squot;s */
DECL|variable|pageptr
r_int
r_int
id|pageptr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* current page being zero&squot;d */
DECL|variable|zeropage_hits
r_int
r_int
id|zeropage_hits
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # zero&squot;d pages request that we&squot;ve done */
DECL|variable|zeropage_calls
r_int
r_int
id|zeropage_calls
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* # zero&squot;d pages request that&squot;ve been made */
DECL|variable|page_zerod_wait
r_static
r_struct
id|wait_queue
op_star
id|page_zerod_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|macro|PAGE_THRESHOLD
mdefine_line|#define PAGE_THRESHOLD 96       /* how many pages to keep pre-zero&squot;d */
multiline_comment|/*&n; * Returns a pre-zero&squot;d page from the list otherwise returns&n; * NULL.&n; */
DECL|function|get_prezerod_page
r_int
r_int
id|get_prezerod_page
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zeropage_calls
)paren
suffix:semicolon
r_if
c_cond
(paren
id|zero_list
)paren
(brace
multiline_comment|/* atomically remove this page from the list */
id|asm
(paren
l_string|&quot;101:lwarx  %1,0,%2&bslash;n&quot;
multiline_comment|/* reserve zero_list */
l_string|&quot;    lwz    %0,0(%1)&bslash;n&quot;
multiline_comment|/* get next -- new zero_list */
l_string|&quot;    stwcx. %0,0,%2&bslash;n&quot;
multiline_comment|/* update zero_list */
l_string|&quot;    bne-   101b&bslash;n&quot;
multiline_comment|/* if lost reservation try again */
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|zero_list
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|page
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|zero_list
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
multiline_comment|/* we can update zerocount after the fact since it is not&n;&t;&t; * used for anything but control of a loop which doesn&squot;t&n;&t;&t; * matter since it won&squot;t effect anything if it zero&squot;s one&n;&t;&t; * less page -- Cort&n;&t;&t; */
id|atomic_inc
c_func
(paren
(paren
id|atomic_t
op_star
)paren
op_amp
id|zeropage_hits
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
id|zerocount
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|page_zerod_wait
)paren
suffix:semicolon
id|need_resched
op_assign
l_int|1
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
multiline_comment|/*&n; * Experimental stuff to zero out pages in the idle task&n; * to speed up get_free_pages() -- Cort&n; * Zero&squot;s out pages until we need to resched or&n; * we&squot;ve reached the limit of zero&squot;d pages.&n; */
DECL|function|zero_paged
r_int
id|zero_paged
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
r_extern
id|pte_t
op_star
id|get_pte
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
)paren
suffix:semicolon
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;zero_paged (idle)&quot;
)paren
suffix:semicolon
multiline_comment|/* current-&gt;blocked = ~0UL; */
macro_line|#ifdef __SMP__
id|printk
c_func
(paren
l_string|&quot;Started zero_paged (cpu %d)&bslash;n&quot;
comma
id|hard_smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;Started zero_paged&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif /* __SMP__ */
id|__sti
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
multiline_comment|/* don&squot;t want to be pre-empted by swapper or power_save */
id|current-&gt;priority
op_assign
op_minus
l_int|98
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|98
suffix:semicolon
multiline_comment|/* we don&squot;t want to run until we have something to do */
r_while
c_loop
(paren
id|zerocount
op_ge
id|PAGE_THRESHOLD
)paren
id|sleep_on
c_func
(paren
op_amp
id|page_zerod_wait
)paren
suffix:semicolon
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
r_goto
id|retry
suffix:semicolon
r_if
c_cond
(paren
id|need_resched
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Make the page no cache so we don&squot;t blow our cache with 0&squot;s&n;&t;&t; */
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|init_task.mm
comma
id|pageptr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|pageptr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|pageptr
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte
op_logical_and
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
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
id|init_task.mm
comma
id|pageptr
)paren
comma
id|pageptr
)paren
suffix:semicolon
)brace
)brace
)brace
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
id|need_resched
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
multiline_comment|/*&n;&t;&t; * If we finished zero-ing out a page add this page to&n;&t;&t; * the zero_list atomically -- we can&squot;t use&n;&t;&t; * down/up since we can&squot;t sleep in idle.&n;&t;&t; * Disabling interrupts is also a bad idea since we would&n;&t;&t; * steal time away from real processes.&n;&t;&t; * We can also have several zero_paged&squot;s running&n;&t;&t; * on different processors so we can&squot;t interfere with them.&n;&t;&t; * So we update the list atomically without locking it.&n;&t;&t; * -- Cort&n;&t;&t; */
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
id|init_task.mm
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
l_string|&quot;101:lwarx  %0,0,%1&bslash;n&quot;
multiline_comment|/* reserve zero_list */
l_string|&quot;    stw    %0,0(%2)&bslash;n&quot;
multiline_comment|/* update *pageptr */
macro_line|#ifdef __SMP__
l_string|&quot;    sync&bslash;n&quot;
multiline_comment|/* let store settle */
macro_line|#endif&t;&t;&t;
l_string|&quot;    mr     %0,%2&bslash;n&quot;
multiline_comment|/* update zero_list in reg */
l_string|&quot;    stwcx. %2,0,%1&bslash;n&quot;
multiline_comment|/* update zero_list in mem */
l_string|&quot;    bne-   101b&bslash;n&quot;
multiline_comment|/* if lost reservation try again */
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|zero_list
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|zero_list
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
id|zerocount
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
id|zerototal
)paren
suffix:semicolon
id|retry
suffix:colon
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|power_save
r_void
r_inline
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
multiline_comment|/* no powersaving modes on the 601 */
r_if
c_cond
(paren
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_eq
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|__sti
c_func
(paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
multiline_comment|/* clear powersaving modes and set nap mode */
l_string|&quot;mfspr %3,1008 &bslash;n&bslash;t&quot;
l_string|&quot;andc  %3,%3,%4 &bslash;n&bslash;t&quot;
l_string|&quot;or    %3,%3,%5 &bslash;n&bslash;t&quot;
l_string|&quot;mtspr 1008,%3 &bslash;n&bslash;t&quot;
multiline_comment|/* enter the mode */
l_string|&quot;mfmsr %0 &bslash;n&bslash;t&quot;
l_string|&quot;oris  %0,%0,%2 &bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t&quot;
l_string|&quot;mtmsr %0 &bslash;n&bslash;t&quot;
l_string|&quot;isync &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|msr
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|msr
)paren
comma
l_string|&quot;i&quot;
(paren
id|MSR_POW
op_rshift
l_int|16
)paren
comma
l_string|&quot;r&quot;
(paren
id|hid0
)paren
comma
l_string|&quot;r&quot;
(paren
id|HID0_DOZE
op_or
id|HID0_NAP
op_or
id|HID0_SLEEP
)paren
comma
l_string|&quot;r&quot;
(paren
id|HID0_NAP
)paren
)paren
suffix:semicolon
)brace
eof
