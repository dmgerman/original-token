multiline_comment|/*  $Id: asyncd.c,v 1.9 1996/12/18 06:43:22 tridge Exp $&n; *  The asyncd kernel daemon. This handles paging on behalf of &n; *  processes that receive page faults due to remote (async) memory&n; *  accesses. &n; *&n; *  Idea and skeleton code courtesy of David Miller (bless his cotton socks)&n; *&n; *  Implemented by tridge&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/swap.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/system.h&gt; /* for cli()/sti() */
macro_line|#include &lt;asm/segment.h&gt; /* for memcpy_to/fromfs */
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
DECL|macro|DEBUG
mdefine_line|#define DEBUG 0
DECL|macro|WRITE_LIMIT
mdefine_line|#define WRITE_LIMIT 100
DECL|macro|LOOP_LIMIT
mdefine_line|#define LOOP_LIMIT 200
r_static
r_struct
(brace
DECL|member|faults
DECL|member|read
DECL|member|write
DECL|member|success
DECL|member|failure
DECL|member|errors
r_int
id|faults
comma
id|read
comma
id|write
comma
id|success
comma
id|failure
comma
id|errors
suffix:semicolon
DECL|variable|stats
)brace
id|stats
suffix:semicolon
multiline_comment|/* &n; * The wait queue for waking up the async daemon:&n; */
DECL|variable|asyncd_wait
r_static
r_struct
id|wait_queue
op_star
id|asyncd_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|struct|async_job
r_struct
id|async_job
(brace
DECL|member|next
r_volatile
r_struct
id|async_job
op_star
id|next
suffix:semicolon
DECL|member|taskid
r_int
id|taskid
suffix:semicolon
DECL|member|mm
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
DECL|member|address
r_int
r_int
id|address
suffix:semicolon
DECL|member|write
r_int
id|write
suffix:semicolon
DECL|member|callback
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|async_queue
r_static
r_volatile
r_struct
id|async_job
op_star
id|async_queue
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|async_queue_end
r_static
r_volatile
r_struct
id|async_job
op_star
id|async_queue_end
op_assign
l_int|NULL
suffix:semicolon
DECL|function|add_to_async_queue
r_static
r_void
id|add_to_async_queue
c_func
(paren
r_int
id|taskid
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
comma
r_int
id|write
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
)paren
(brace
r_struct
id|async_job
op_star
id|a
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|a
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERROR: out of memory in asyncd&bslash;n&quot;
)paren
suffix:semicolon
id|a
op_member_access_from_pointer
id|callback
c_func
(paren
id|taskid
comma
id|address
comma
id|write
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
)paren
id|stats.write
op_increment
suffix:semicolon
r_else
id|stats.read
op_increment
suffix:semicolon
id|a-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|a-&gt;taskid
op_assign
id|taskid
suffix:semicolon
id|a-&gt;mm
op_assign
id|mm
suffix:semicolon
id|a-&gt;address
op_assign
id|address
suffix:semicolon
id|a-&gt;write
op_assign
id|write
suffix:semicolon
id|a-&gt;callback
op_assign
id|callback
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|async_queue
)paren
(brace
id|async_queue
op_assign
id|a
suffix:semicolon
)brace
r_else
(brace
id|async_queue_end-&gt;next
op_assign
id|a
suffix:semicolon
)brace
id|async_queue_end
op_assign
id|a
suffix:semicolon
)brace
DECL|function|async_fault
r_void
id|async_fault
c_func
(paren
r_int
r_int
id|address
comma
r_int
id|write
comma
r_int
id|taskid
comma
r_void
(paren
op_star
id|callback
)paren
(paren
r_int
comma
r_int
r_int
comma
r_int
comma
r_int
)paren
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|task
(braket
id|taskid
)braket
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
id|stats.faults
op_increment
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
l_string|&quot;paging in %x for task=%d&bslash;n&quot;
comma
id|address
comma
id|taskid
)paren
suffix:semicolon
macro_line|#endif
id|add_to_async_queue
c_func
(paren
id|taskid
comma
id|mm
comma
id|address
comma
id|write
comma
id|callback
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|asyncd_wait
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|TQUEUE_BH
)paren
suffix:semicolon
)brace
DECL|function|fault_in_page
r_static
r_int
id|fault_in_page
c_func
(paren
r_int
id|taskid
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
id|address
comma
r_int
id|write
)paren
(brace
r_static
r_int
id|last_address
suffix:semicolon
r_static
r_int
id|last_task
comma
id|loop_counter
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|task
(braket
id|taskid
)braket
suffix:semicolon
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
op_logical_or
op_logical_neg
id|tsk-&gt;mm
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
op_logical_or
(paren
id|write
op_logical_and
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
)paren
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
OG
id|address
)paren
r_goto
id|bad_area
suffix:semicolon
r_if
c_cond
(paren
id|address
op_eq
id|last_address
op_logical_and
id|taskid
op_eq
id|last_task
)paren
(brace
id|loop_counter
op_increment
suffix:semicolon
)brace
r_else
(brace
id|loop_counter
op_assign
l_int|0
suffix:semicolon
id|last_address
op_assign
id|address
suffix:semicolon
id|last_task
op_assign
id|taskid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loop_counter
op_eq
id|WRITE_LIMIT
op_logical_and
op_logical_neg
id|write
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MSC bug? setting write request&bslash;n&quot;
)paren
suffix:semicolon
id|stats.errors
op_increment
suffix:semicolon
id|write
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|loop_counter
op_eq
id|LOOP_LIMIT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;MSC bug? failing request&bslash;n&quot;
)paren
suffix:semicolon
id|stats.errors
op_increment
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|pgd
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
(brace
r_goto
id|no_memory
suffix:semicolon
)brace
id|pte
op_assign
id|pte_alloc
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
(brace
r_goto
id|no_memory
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|do_no_page
c_func
(paren
id|tsk
comma
id|vma
comma
id|address
comma
id|write
)paren
suffix:semicolon
r_goto
id|finish_up
suffix:semicolon
)brace
id|set_pte
c_func
(paren
id|pte
comma
id|pte_mkyoung
c_func
(paren
op_star
id|pte
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
r_if
c_cond
(paren
op_logical_neg
id|write
)paren
(brace
r_goto
id|finish_up
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pte_write
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|set_pte
c_func
(paren
id|pte
comma
id|pte_mkdirty
c_func
(paren
op_star
id|pte
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
r_goto
id|finish_up
suffix:semicolon
)brace
id|do_wp_page
c_func
(paren
id|tsk
comma
id|vma
comma
id|address
comma
id|write
)paren
suffix:semicolon
multiline_comment|/* Fall through for do_wp_page */
id|finish_up
suffix:colon
id|stats.success
op_increment
suffix:semicolon
id|update_mmu_cache
c_func
(paren
id|vma
comma
id|address
comma
op_star
id|pte
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|no_memory
suffix:colon
id|stats.failure
op_increment
suffix:semicolon
id|oom
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
id|bad_area
suffix:colon
id|stats.failure
op_increment
suffix:semicolon
id|tsk-&gt;tss.sig_address
op_assign
id|address
suffix:semicolon
id|tsk-&gt;tss.sig_desc
op_assign
id|SUBSIG_NOMAPPING
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGSEGV
comma
id|tsk
comma
l_int|1
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Note the semaphore operations must be done here, and _not_&n; * in async_fault().&n; */
DECL|function|run_async_queue
r_static
r_void
id|run_async_queue
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_int
id|flags
suffix:semicolon
r_while
c_loop
(paren
id|async_queue
)paren
(brace
r_volatile
r_struct
id|async_job
op_star
id|a
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
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
id|a
op_assign
id|async_queue
suffix:semicolon
id|async_queue
op_assign
id|async_queue-&gt;next
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|mm
op_assign
id|a-&gt;mm
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|mm
comma
id|a-&gt;address
)paren
suffix:semicolon
id|ret
op_assign
id|fault_in_page
c_func
(paren
id|a-&gt;taskid
comma
id|vma
comma
id|a-&gt;address
comma
id|a-&gt;write
)paren
suffix:semicolon
macro_line|#if DEBUG
id|printk
c_func
(paren
l_string|&quot;fault_in_page(task=%d addr=%x write=%d) = %d&bslash;n&quot;
comma
id|a-&gt;taskid
comma
id|a-&gt;address
comma
id|a-&gt;write
comma
id|ret
)paren
suffix:semicolon
macro_line|#endif
id|a
op_member_access_from_pointer
id|callback
c_func
(paren
id|a-&gt;taskid
comma
id|a-&gt;address
comma
id|a-&gt;write
comma
id|ret
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
(paren
r_void
op_star
)paren
id|a
comma
r_sizeof
(paren
op_star
id|a
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#if CONFIG_AP1000
DECL|function|asyncd_info
r_static
r_void
id|asyncd_info
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CID(%d) faults: total=%d  read=%d  write=%d  success=%d fail=%d err=%d&bslash;n&quot;
comma
id|mpp_cid
c_func
(paren
)paren
comma
id|stats.faults
comma
id|stats.read
comma
id|stats.write
comma
id|stats.success
comma
id|stats.failure
comma
id|stats.errors
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * The background async daemon.&n; * Started as a kernel thread from the init process.&n; */
DECL|function|asyncd
r_int
id|asyncd
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|current-&gt;session
op_assign
l_int|1
suffix:semicolon
id|current-&gt;pgrp
op_assign
l_int|1
suffix:semicolon
id|sprintf
c_func
(paren
id|current-&gt;comm
comma
l_string|&quot;asyncd&quot;
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
op_complement
l_int|0UL
suffix:semicolon
multiline_comment|/* block all signals */
multiline_comment|/* Give asyncd a realtime priority. */
id|current-&gt;policy
op_assign
id|SCHED_FIFO
suffix:semicolon
id|current-&gt;priority
op_assign
l_int|32
suffix:semicolon
multiline_comment|/* Fixme --- we need to standardise our&n;&t;&t;&t;&t;    namings for POSIX.4 realtime scheduling&n;&t;&t;&t;&t;    priorities.  */
id|printk
c_func
(paren
l_string|&quot;Started asyncd&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#if CONFIG_AP1000
id|bif_add_debug_key
c_func
(paren
l_char|&squot;a&squot;
comma
id|asyncd_info
comma
l_string|&quot;stats on asyncd&quot;
)paren
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
l_int|1
)paren
(brace
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
r_while
c_loop
(paren
op_logical_neg
id|async_queue
)paren
(brace
id|current-&gt;signal
op_assign
l_int|0
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|asyncd_wait
)paren
suffix:semicolon
)brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|run_async_queue
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
eof
