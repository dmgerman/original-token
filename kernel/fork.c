multiline_comment|/*&n; *  linux/kernel/fork.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *  &squot;fork.c&squot; contains the help-routines for the &squot;fork&squot; system call&n; * (see also system_call.s).&n; * Fork is rather simple, once you get the hang of it, but the memory&n; * management can be a bitch. See &squot;mm/mm.c&squot;: &squot;copy_page_tables()&squot;&n; */
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
multiline_comment|/* The idle threads do not count.. */
DECL|variable|nr_threads
r_int
id|nr_threads
op_assign
l_int|0
suffix:semicolon
DECL|variable|nr_running
r_int
id|nr_running
op_assign
l_int|0
suffix:semicolon
DECL|variable|max_threads
r_int
id|max_threads
suffix:semicolon
DECL|variable|total_forks
r_int
r_int
id|total_forks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Handle normal Linux uptimes. */
DECL|variable|last_pid
r_int
id|last_pid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* SLAB cache for mm_struct&squot;s. */
DECL|variable|mm_cachep
id|kmem_cache_t
op_star
id|mm_cachep
suffix:semicolon
multiline_comment|/* SLAB cache for files structs */
DECL|variable|files_cachep
id|kmem_cache_t
op_star
id|files_cachep
suffix:semicolon
DECL|variable|pidhash
r_struct
id|task_struct
op_star
id|pidhash
(braket
id|PIDHASH_SZ
)braket
suffix:semicolon
multiline_comment|/* UID task count cache, to prevent walking entire process list every&n; * single fork() operation.&n; */
DECL|macro|UIDHASH_SZ
mdefine_line|#define UIDHASH_SZ&t;(PIDHASH_SZ &gt;&gt; 2)
DECL|struct|user_struct
r_static
r_struct
id|user_struct
(brace
DECL|member|count
id|atomic_t
id|count
suffix:semicolon
DECL|member|next
DECL|member|pprev
r_struct
id|user_struct
op_star
id|next
comma
op_star
op_star
id|pprev
suffix:semicolon
DECL|member|uid
r_int
r_int
id|uid
suffix:semicolon
DECL|variable|uidhash
)brace
op_star
id|uidhash
(braket
id|UIDHASH_SZ
)braket
suffix:semicolon
DECL|variable|uidhash_lock
id|spinlock_t
id|uidhash_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|uid_cachep
id|kmem_cache_t
op_star
id|uid_cachep
suffix:semicolon
DECL|macro|uidhashfn
mdefine_line|#define uidhashfn(uid)&t;(((uid &gt;&gt; 8) ^ uid) &amp; (UIDHASH_SZ - 1))
multiline_comment|/*&n; * These routines must be called with the uidhash spinlock held!&n; */
DECL|function|uid_hash_insert
r_static
r_inline
r_void
id|uid_hash_insert
c_func
(paren
r_struct
id|user_struct
op_star
id|up
comma
r_int
r_int
id|hashent
)paren
(brace
r_if
c_cond
(paren
(paren
id|up-&gt;next
op_assign
id|uidhash
(braket
id|hashent
)braket
)paren
op_ne
l_int|NULL
)paren
(brace
id|uidhash
(braket
id|hashent
)braket
op_member_access_from_pointer
id|pprev
op_assign
op_amp
id|up-&gt;next
suffix:semicolon
)brace
id|up-&gt;pprev
op_assign
op_amp
id|uidhash
(braket
id|hashent
)braket
suffix:semicolon
id|uidhash
(braket
id|hashent
)braket
op_assign
id|up
suffix:semicolon
)brace
DECL|function|uid_hash_remove
r_static
r_inline
r_void
id|uid_hash_remove
c_func
(paren
r_struct
id|user_struct
op_star
id|up
)paren
(brace
r_if
c_cond
(paren
id|up-&gt;next
)paren
(brace
id|up-&gt;next-&gt;pprev
op_assign
id|up-&gt;pprev
suffix:semicolon
)brace
op_star
id|up-&gt;pprev
op_assign
id|up-&gt;next
suffix:semicolon
)brace
DECL|function|uid_hash_find
r_static
r_inline
r_struct
id|user_struct
op_star
id|uid_hash_find
c_func
(paren
r_int
r_int
id|uid
comma
r_int
r_int
id|hashent
)paren
(brace
r_struct
id|user_struct
op_star
id|up
comma
op_star
id|next
suffix:semicolon
id|next
op_assign
id|uidhash
(braket
id|hashent
)braket
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|up
op_assign
id|next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
id|next
op_assign
id|up-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|up-&gt;uid
op_ne
id|uid
)paren
r_continue
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|up-&gt;count
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
id|up
suffix:semicolon
)brace
multiline_comment|/*&n; * For SMP, we need to re-test the user struct counter&n; * after having aquired the spinlock. This allows us to do&n; * the common case (not freeing anything) without having&n; * any locking.&n; */
macro_line|#ifdef __SMP__
DECL|macro|uid_hash_free
mdefine_line|#define uid_hash_free(up)&t;(!atomic_read(&amp;(up)-&gt;count))
macro_line|#else
DECL|macro|uid_hash_free
mdefine_line|#define uid_hash_free(up)&t;(1)
macro_line|#endif
DECL|function|free_uid
r_void
id|free_uid
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_struct
id|user_struct
op_star
id|up
op_assign
id|p-&gt;user
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
id|p-&gt;user
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|up-&gt;count
)paren
)paren
(brace
id|spin_lock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|uid_hash_free
c_func
(paren
id|up
)paren
)paren
(brace
id|uid_hash_remove
c_func
(paren
id|up
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|uid_cachep
comma
id|up
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|alloc_uid
r_int
id|alloc_uid
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|hashent
op_assign
id|uidhashfn
c_func
(paren
id|p-&gt;uid
)paren
suffix:semicolon
r_struct
id|user_struct
op_star
id|up
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
id|up
op_assign
id|uid_hash_find
c_func
(paren
id|p-&gt;uid
comma
id|hashent
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|up
)paren
(brace
r_struct
id|user_struct
op_star
r_new
suffix:semicolon
r_new
op_assign
id|kmem_cache_alloc
c_func
(paren
id|uid_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
r_new
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_new
op_member_access_from_pointer
id|uid
op_assign
id|p-&gt;uid
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
r_new
op_member_access_from_pointer
id|count
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Before adding this, check whether we raced&n;&t;&t; * on adding the same user already..&n;&t;&t; */
id|spin_lock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
id|up
op_assign
id|uid_hash_find
c_func
(paren
id|p-&gt;uid
comma
id|hashent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|up
)paren
(brace
id|kmem_cache_free
c_func
(paren
id|uid_cachep
comma
r_new
)paren
suffix:semicolon
)brace
r_else
(brace
id|uid_hash_insert
c_func
(paren
r_new
comma
id|hashent
)paren
suffix:semicolon
id|up
op_assign
r_new
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|uidhash_lock
)paren
suffix:semicolon
)brace
id|p-&gt;user
op_assign
id|up
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fork_init
r_void
id|__init
id|fork_init
c_func
(paren
r_int
r_int
id|mempages
)paren
(brace
r_int
id|i
suffix:semicolon
id|uid_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;uid_cache&quot;
comma
r_sizeof
(paren
r_struct
id|user_struct
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|uid_cachep
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Cannot create uid taskcount SLAB cache&bslash;n&quot;
)paren
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
id|UIDHASH_SZ
suffix:semicolon
id|i
op_increment
)paren
(brace
id|uidhash
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The default maximum number of threads is set to a safe&n;&t; * value: the thread structures can take up at most half&n;&t; * of memory.&n;&t; */
id|max_threads
op_assign
id|mempages
op_div
(paren
id|THREAD_SIZE
op_div
id|PAGE_SIZE
)paren
op_div
l_int|2
suffix:semicolon
id|init_task.rlim
(braket
id|RLIMIT_NPROC
)braket
dot
id|rlim_cur
op_assign
id|max_threads
op_div
l_int|2
suffix:semicolon
id|init_task.rlim
(braket
id|RLIMIT_NPROC
)braket
dot
id|rlim_max
op_assign
id|max_threads
op_div
l_int|2
suffix:semicolon
)brace
multiline_comment|/* Protects next_safe and last_pid. */
DECL|variable|lastpid_lock
id|spinlock_t
id|lastpid_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|get_pid
r_static
r_int
id|get_pid
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_static
r_int
id|next_safe
op_assign
id|PID_MAX
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|CLONE_PID
)paren
r_return
id|current-&gt;pid
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|lastpid_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
op_increment
id|last_pid
)paren
op_amp
l_int|0xffff8000
)paren
(brace
id|last_pid
op_assign
l_int|300
suffix:semicolon
multiline_comment|/* Skip daemons etc. */
r_goto
id|inside
suffix:semicolon
)brace
r_if
c_cond
(paren
id|last_pid
op_ge
id|next_safe
)paren
(brace
id|inside
suffix:colon
id|next_safe
op_assign
id|PID_MAX
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|repeat
suffix:colon
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
id|p-&gt;pid
op_eq
id|last_pid
op_logical_or
id|p-&gt;pgrp
op_eq
id|last_pid
op_logical_or
id|p-&gt;session
op_eq
id|last_pid
)paren
(brace
r_if
c_cond
(paren
op_increment
id|last_pid
op_ge
id|next_safe
)paren
(brace
r_if
c_cond
(paren
id|last_pid
op_amp
l_int|0xffff8000
)paren
(brace
id|last_pid
op_assign
l_int|300
suffix:semicolon
)brace
id|next_safe
op_assign
id|PID_MAX
suffix:semicolon
)brace
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;pid
OG
id|last_pid
op_logical_and
id|next_safe
OG
id|p-&gt;pid
)paren
(brace
id|next_safe
op_assign
id|p-&gt;pid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;pgrp
OG
id|last_pid
op_logical_and
id|next_safe
OG
id|p-&gt;pgrp
)paren
(brace
id|next_safe
op_assign
id|p-&gt;pgrp
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p-&gt;session
OG
id|last_pid
op_logical_and
id|next_safe
OG
id|p-&gt;session
)paren
(brace
id|next_safe
op_assign
id|p-&gt;session
suffix:semicolon
)brace
)brace
id|read_unlock
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|lastpid_lock
)paren
suffix:semicolon
r_return
id|last_pid
suffix:semicolon
)brace
DECL|function|dup_mmap
r_static
r_inline
r_int
id|dup_mmap
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|mpnt
comma
op_star
id|tmp
comma
op_star
op_star
id|pprev
suffix:semicolon
r_int
id|retval
suffix:semicolon
multiline_comment|/* Kill me slowly. UGLY! FIXME! */
id|memcpy
c_func
(paren
op_amp
id|mm-&gt;start_code
comma
op_amp
id|current-&gt;mm-&gt;start_code
comma
l_int|15
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|flush_cache_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
id|pprev
op_assign
op_amp
id|mm-&gt;mmap
suffix:semicolon
r_for
c_loop
(paren
id|mpnt
op_assign
id|current-&gt;mm-&gt;mmap
suffix:semicolon
id|mpnt
suffix:semicolon
id|mpnt
op_assign
id|mpnt-&gt;vm_next
)paren
(brace
r_struct
id|file
op_star
id|file
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|tmp
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vm_area_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_goto
id|fail_nomem
suffix:semicolon
op_star
id|tmp
op_assign
op_star
id|mpnt
suffix:semicolon
id|tmp-&gt;vm_flags
op_and_assign
op_complement
id|VM_LOCKED
suffix:semicolon
id|tmp-&gt;vm_mm
op_assign
id|mm
suffix:semicolon
id|mm-&gt;map_count
op_increment
suffix:semicolon
id|tmp-&gt;vm_next
op_assign
l_int|NULL
suffix:semicolon
id|file
op_assign
id|tmp-&gt;vm_file
suffix:semicolon
r_if
c_cond
(paren
id|file
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
id|get_file
c_func
(paren
id|file
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;vm_flags
op_amp
id|VM_DENYWRITE
)paren
id|atomic_dec
c_func
(paren
op_amp
id|inode-&gt;i_writecount
)paren
suffix:semicolon
multiline_comment|/* insert tmp into the share list, just after mpnt */
id|spin_lock
c_func
(paren
op_amp
id|inode-&gt;i_mapping-&gt;i_shared_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|tmp-&gt;vm_next_share
op_assign
id|mpnt-&gt;vm_next_share
)paren
op_ne
l_int|NULL
)paren
(brace
id|mpnt-&gt;vm_next_share-&gt;vm_pprev_share
op_assign
op_amp
id|tmp-&gt;vm_next_share
suffix:semicolon
)brace
id|mpnt-&gt;vm_next_share
op_assign
id|tmp
suffix:semicolon
id|tmp-&gt;vm_pprev_share
op_assign
op_amp
id|mpnt-&gt;vm_next_share
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|inode-&gt;i_mapping-&gt;i_shared_lock
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the pages, but defer checking for errors */
id|retval
op_assign
id|copy_page_range
c_func
(paren
id|mm
comma
id|current-&gt;mm
comma
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
op_logical_and
id|tmp-&gt;vm_ops
op_logical_and
id|tmp-&gt;vm_ops-&gt;open
)paren
id|tmp-&gt;vm_ops
op_member_access_from_pointer
id|open
c_func
(paren
id|tmp
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Link in the new vma even if an error occurred,&n;&t;&t; * so that exit_mmap() can clean up the mess.&n;&t;&t; */
id|tmp-&gt;vm_next
op_assign
op_star
id|pprev
suffix:semicolon
op_star
id|pprev
op_assign
id|tmp
suffix:semicolon
id|pprev
op_assign
op_amp
id|tmp-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fail_nomem
suffix:semicolon
)brace
id|retval
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;map_count
op_ge
id|AVL_MIN_MAP_COUNT
)paren
id|build_mmap_avl
c_func
(paren
id|mm
)paren
suffix:semicolon
id|fail_nomem
suffix:colon
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate and initialize an mm_struct.&n; */
DECL|function|mm_alloc
r_struct
id|mm_struct
op_star
id|mm_alloc
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
id|mm
op_assign
id|kmem_cache_alloc
c_func
(paren
id|mm_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
(brace
id|memset
c_func
(paren
id|mm
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|mm
)paren
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mm-&gt;mm_users
comma
l_int|1
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|mm-&gt;mm_count
comma
l_int|1
)paren
suffix:semicolon
id|init_MUTEX
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mm-&gt;page_table_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
id|mm-&gt;pgd
op_assign
id|pgd_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mm-&gt;pgd
)paren
r_return
id|mm
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|mm_cachep
comma
id|mm
)paren
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Called when the last reference to the mm&n; * is dropped: either by a lazy thread or by&n; * mmput. Free the page directory and the mm.&n; */
DECL|function|__mmdrop
r_inline
r_void
id|__mmdrop
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|mm
op_eq
op_amp
id|init_mm
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|pgd_free
c_func
(paren
id|mm-&gt;pgd
)paren
suffix:semicolon
id|destroy_context
c_func
(paren
id|mm
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|mm_cachep
comma
id|mm
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Decrement the use count and release all resources for an mm.&n; */
DECL|function|mmput
r_void
id|mmput
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|atomic_dec_and_test
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
)paren
(brace
id|exit_mmap
c_func
(paren
id|mm
)paren
suffix:semicolon
id|mmdrop
c_func
(paren
id|mm
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Please note the differences between mmput and mm_release.&n; * mmput is called whenever we stop holding onto a mm_struct,&n; * error success whatever.&n; *&n; * mm_release is called after a mm_struct has been removed&n; * from the current process.&n; *&n; * This difference is important for error handling, when we&n; * only half set up a mm_struct for a new process and need to restore&n; * the old one.  Because we mmput the new mm_struct before&n; * restoring the old one. . .&n; * Eric Biederman 10 January 1998&n; */
DECL|function|mm_release
r_void
id|mm_release
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
multiline_comment|/* notify parent sleeping on vfork() */
r_if
c_cond
(paren
id|tsk-&gt;flags
op_amp
id|PF_VFORK
)paren
(brace
id|tsk-&gt;flags
op_and_assign
op_complement
id|PF_VFORK
suffix:semicolon
id|up
c_func
(paren
id|tsk-&gt;p_opptr-&gt;vfork_sem
)paren
suffix:semicolon
)brace
)brace
DECL|function|copy_mm
r_static
r_inline
r_int
id|copy_mm
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|tsk-&gt;min_flt
op_assign
id|tsk-&gt;maj_flt
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;cmin_flt
op_assign
id|tsk-&gt;cmaj_flt
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;nswap
op_assign
id|tsk-&gt;cnswap
op_assign
l_int|0
suffix:semicolon
id|tsk-&gt;mm
op_assign
l_int|NULL
suffix:semicolon
id|tsk-&gt;active_mm
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Are we cloning a kernel thread?&n;&t; *&n;&t; * We need to steal a active VM for that..&n;&t; */
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_VM
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
r_goto
id|good_mm
suffix:semicolon
)brace
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|mm
op_assign
id|mm_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|fail_nomem
suffix:semicolon
id|tsk-&gt;mm
op_assign
id|mm
suffix:semicolon
id|tsk-&gt;active_mm
op_assign
id|mm
suffix:semicolon
multiline_comment|/*&n;&t; * child gets a private LDT (if there was an LDT in the parent)&n;&t; */
id|copy_segments
c_func
(paren
id|tsk
comma
id|mm
)paren
suffix:semicolon
id|down
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
id|retval
op_assign
id|dup_mmap
c_func
(paren
id|mm
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|current-&gt;mm-&gt;mmap_sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|free_pt
suffix:semicolon
id|good_mm
suffix:colon
id|tsk-&gt;mm
op_assign
id|mm
suffix:semicolon
id|tsk-&gt;active_mm
op_assign
id|mm
suffix:semicolon
id|init_new_context
c_func
(paren
id|tsk
comma
id|mm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|free_pt
suffix:colon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
id|fail_nomem
suffix:colon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|copy_fs
r_static
r_inline
r_int
id|copy_fs
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_FS
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|current-&gt;fs-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tsk-&gt;fs
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tsk-&gt;fs
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;fs
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tsk-&gt;fs-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|tsk-&gt;fs-&gt;umask
op_assign
id|current-&gt;fs-&gt;umask
suffix:semicolon
id|tsk-&gt;fs-&gt;root
op_assign
id|dget
c_func
(paren
id|current-&gt;fs-&gt;root
)paren
suffix:semicolon
id|tsk-&gt;fs-&gt;pwd
op_assign
id|dget
c_func
(paren
id|current-&gt;fs-&gt;pwd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|count_open_files
r_static
r_int
id|count_open_files
c_func
(paren
r_struct
id|files_struct
op_star
id|files
comma
r_int
id|size
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* Find the last open fd */
r_for
c_loop
(paren
id|i
op_assign
id|size
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|files-&gt;open_fds-&gt;fds_bits
(braket
op_decrement
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
id|i
op_assign
(paren
id|i
op_plus
l_int|1
)paren
op_star
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|copy_files
r_static
r_int
id|copy_files
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|files_struct
op_star
id|oldf
comma
op_star
id|newf
suffix:semicolon
r_struct
id|file
op_star
op_star
id|old_fds
comma
op_star
op_star
id|new_fds
suffix:semicolon
r_int
id|open_files
comma
id|nfds
comma
id|size
comma
id|i
comma
id|error
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * A background process may not have any files ...&n;&t; */
id|oldf
op_assign
id|current-&gt;files
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldf
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_FILES
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|oldf-&gt;count
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|tsk-&gt;files
op_assign
l_int|NULL
suffix:semicolon
id|error
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|newf
op_assign
id|kmem_cache_alloc
c_func
(paren
id|files_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newf
)paren
r_goto
id|out
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|newf-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|newf-&gt;file_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
id|newf-&gt;next_fd
op_assign
l_int|0
suffix:semicolon
id|newf-&gt;max_fds
op_assign
id|NR_OPEN_DEFAULT
suffix:semicolon
id|newf-&gt;max_fdset
op_assign
id|__FD_SETSIZE
suffix:semicolon
id|newf-&gt;close_on_exec
op_assign
op_amp
id|newf-&gt;close_on_exec_init
suffix:semicolon
id|newf-&gt;open_fds
op_assign
op_amp
id|newf-&gt;open_fds_init
suffix:semicolon
id|newf-&gt;fd
op_assign
op_amp
id|newf-&gt;fd_array
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* We don&squot;t yet have the oldf readlock, but even if the old&n;           fdset gets grown now, we&squot;ll only copy up to &quot;size&quot; fds */
id|size
op_assign
id|oldf-&gt;max_fdset
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
id|__FD_SETSIZE
)paren
(brace
id|newf-&gt;max_fdset
op_assign
l_int|0
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|newf-&gt;file_lock
)paren
suffix:semicolon
id|error
op_assign
id|expand_fdset
c_func
(paren
id|newf
comma
id|size
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|newf-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_release
suffix:semicolon
)brace
id|read_lock
c_func
(paren
op_amp
id|oldf-&gt;file_lock
)paren
suffix:semicolon
id|open_files
op_assign
id|count_open_files
c_func
(paren
id|oldf
comma
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether we need to allocate a larger fd array.&n;&t; * Note: we&squot;re not a clone task, so the open count won&squot;t&n;&t; * change.&n;&t; */
id|nfds
op_assign
id|NR_OPEN_DEFAULT
suffix:semicolon
r_if
c_cond
(paren
id|open_files
OG
id|nfds
)paren
(brace
id|read_unlock
c_func
(paren
op_amp
id|oldf-&gt;file_lock
)paren
suffix:semicolon
id|newf-&gt;max_fds
op_assign
l_int|0
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|newf-&gt;file_lock
)paren
suffix:semicolon
id|error
op_assign
id|expand_fd_array
c_func
(paren
id|newf
comma
id|open_files
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|newf-&gt;file_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_release
suffix:semicolon
id|nfds
op_assign
id|newf-&gt;max_fds
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|oldf-&gt;file_lock
)paren
suffix:semicolon
)brace
id|old_fds
op_assign
id|oldf-&gt;fd
suffix:semicolon
id|new_fds
op_assign
id|newf-&gt;fd
suffix:semicolon
id|memcpy
c_func
(paren
id|newf-&gt;open_fds-&gt;fds_bits
comma
id|oldf-&gt;open_fds-&gt;fds_bits
comma
id|open_files
op_div
l_int|8
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|newf-&gt;close_on_exec-&gt;fds_bits
comma
id|oldf-&gt;close_on_exec-&gt;fds_bits
comma
id|open_files
op_div
l_int|8
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|open_files
suffix:semicolon
id|i
op_ne
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|file
op_star
id|f
op_assign
op_star
id|old_fds
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|f
)paren
id|get_file
c_func
(paren
id|f
)paren
suffix:semicolon
op_star
id|new_fds
op_increment
op_assign
id|f
suffix:semicolon
)brace
id|read_unlock
c_func
(paren
op_amp
id|oldf-&gt;file_lock
)paren
suffix:semicolon
multiline_comment|/* compute the remainder to be cleared */
id|size
op_assign
(paren
id|newf-&gt;max_fds
op_minus
id|open_files
)paren
op_star
r_sizeof
(paren
r_struct
id|file
op_star
)paren
suffix:semicolon
multiline_comment|/* This is long word aligned thus could use a optimized version */
id|memset
c_func
(paren
id|new_fds
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newf-&gt;max_fdset
OG
id|open_files
)paren
(brace
r_int
id|left
op_assign
(paren
id|newf-&gt;max_fdset
op_minus
id|open_files
)paren
op_div
l_int|8
suffix:semicolon
r_int
id|start
op_assign
id|open_files
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|newf-&gt;open_fds-&gt;fds_bits
(braket
id|start
)braket
comma
l_int|0
comma
id|left
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|newf-&gt;close_on_exec-&gt;fds_bits
(braket
id|start
)braket
comma
l_int|0
comma
id|left
)paren
suffix:semicolon
)brace
id|tsk-&gt;files
op_assign
id|newf
suffix:semicolon
id|error
op_assign
l_int|0
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
id|out_release
suffix:colon
id|free_fdset
(paren
id|newf-&gt;close_on_exec
comma
id|newf-&gt;max_fdset
)paren
suffix:semicolon
id|free_fdset
(paren
id|newf-&gt;open_fds
comma
id|newf-&gt;max_fdset
)paren
suffix:semicolon
id|kmem_cache_free
c_func
(paren
id|files_cachep
comma
id|newf
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
DECL|function|copy_sighand
r_static
r_inline
r_int
id|copy_sighand
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SIGHAND
)paren
(brace
id|atomic_inc
c_func
(paren
op_amp
id|current-&gt;sig-&gt;count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tsk-&gt;sig
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tsk-&gt;sig
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;sig
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|tsk-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|atomic_set
c_func
(paren
op_amp
id|tsk-&gt;sig-&gt;count
comma
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|tsk-&gt;sig-&gt;action
comma
id|current-&gt;sig-&gt;action
comma
r_sizeof
(paren
id|tsk-&gt;sig-&gt;action
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|copy_flags
r_static
r_inline
r_void
id|copy_flags
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|new_flags
op_assign
id|p-&gt;flags
suffix:semicolon
id|new_flags
op_and_assign
op_complement
(paren
id|PF_SUPERPRIV
op_or
id|PF_USEDFPU
op_or
id|PF_VFORK
)paren
suffix:semicolon
id|new_flags
op_or_assign
id|PF_FORKNOEXEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|clone_flags
op_amp
id|CLONE_PTRACE
)paren
)paren
id|new_flags
op_and_assign
op_complement
(paren
id|PF_PTRACED
op_or
id|PF_TRACESYS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_VFORK
)paren
id|new_flags
op_or_assign
id|PF_VFORK
suffix:semicolon
id|p-&gt;flags
op_assign
id|new_flags
suffix:semicolon
)brace
multiline_comment|/*&n; *  Ok, this is the main fork-routine. It copies the system process&n; * information (task[nr]) and sets up the necessary registers. It&n; * also copies the data segment in its entirety.&n; */
DECL|function|do_fork
r_int
id|do_fork
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|DECLARE_MUTEX_LOCKED
c_func
(paren
id|sem
)paren
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_PID
)paren
(brace
multiline_comment|/* This is only allowed from the boot up thread */
r_if
c_cond
(paren
id|current-&gt;pid
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
id|current-&gt;vfork_sem
op_assign
op_amp
id|sem
suffix:semicolon
id|p
op_assign
id|alloc_task_struct
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_goto
id|fork_out
suffix:semicolon
op_star
id|p
op_assign
op_star
id|current
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|EAGAIN
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;user
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|p-&gt;user-&gt;count
)paren
op_ge
id|p-&gt;rlim
(braket
id|RLIMIT_NPROC
)braket
dot
id|rlim_cur
)paren
r_goto
id|bad_fork_free
suffix:semicolon
id|atomic_inc
c_func
(paren
op_amp
id|p-&gt;user-&gt;count
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Counter increases are protected by&n;&t; * the kernel lock so nr_threads can&squot;t&n;&t; * increase under us (but it may decrease).&n;&t; */
r_if
c_cond
(paren
id|nr_threads
op_ge
id|max_threads
)paren
r_goto
id|bad_fork_cleanup_count
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;exec_domain
op_logical_and
id|p-&gt;exec_domain-&gt;module
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|p-&gt;exec_domain-&gt;module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;binfmt
op_logical_and
id|p-&gt;binfmt-&gt;module
)paren
id|__MOD_INC_USE_COUNT
c_func
(paren
id|p-&gt;binfmt-&gt;module
)paren
suffix:semicolon
id|p-&gt;did_exec
op_assign
l_int|0
suffix:semicolon
id|p-&gt;swappable
op_assign
l_int|0
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|copy_flags
c_func
(paren
id|clone_flags
comma
id|p
)paren
suffix:semicolon
id|p-&gt;pid
op_assign
id|get_pid
c_func
(paren
id|clone_flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is a &quot;shadow run&quot; state. The process&n;&t; * is marked runnable, but isn&squot;t actually on&n;&t; * any run queue yet.. (that happens at the&n;&t; * very end).&n;&t; */
id|p-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
id|p-&gt;run_list.next
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;run_list.prev
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|clone_flags
op_amp
id|CLONE_VFORK
)paren
op_logical_or
op_logical_neg
(paren
id|clone_flags
op_amp
id|CLONE_PARENT
)paren
)paren
id|p-&gt;p_pptr
op_assign
id|p-&gt;p_opptr
op_assign
id|current
suffix:semicolon
id|p-&gt;p_cptr
op_assign
l_int|NULL
suffix:semicolon
id|init_waitqueue_head
c_func
(paren
op_amp
id|p-&gt;wait_chldexit
)paren
suffix:semicolon
id|p-&gt;vfork_sem
op_assign
l_int|NULL
suffix:semicolon
id|sema_init
c_func
(paren
op_amp
id|p-&gt;exit_sem
comma
l_int|1
)paren
suffix:semicolon
id|p-&gt;sigpending
op_assign
l_int|0
suffix:semicolon
id|sigemptyset
c_func
(paren
op_amp
id|p-&gt;signal
)paren
suffix:semicolon
id|p-&gt;sigqueue
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;sigqueue_tail
op_assign
op_amp
id|p-&gt;sigqueue
suffix:semicolon
id|p-&gt;it_real_value
op_assign
id|p-&gt;it_virt_value
op_assign
id|p-&gt;it_prof_value
op_assign
l_int|0
suffix:semicolon
id|p-&gt;it_real_incr
op_assign
id|p-&gt;it_virt_incr
op_assign
id|p-&gt;it_prof_incr
op_assign
l_int|0
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|p-&gt;real_timer
)paren
suffix:semicolon
id|p-&gt;real_timer.data
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p-&gt;leader
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* session leadership doesn&squot;t inherit */
id|p-&gt;tty_old_pgrp
op_assign
l_int|0
suffix:semicolon
id|p-&gt;times.tms_utime
op_assign
id|p-&gt;times.tms_stime
op_assign
l_int|0
suffix:semicolon
id|p-&gt;times.tms_cutime
op_assign
id|p-&gt;times.tms_cstime
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef __SMP__
(brace
r_int
id|i
suffix:semicolon
id|p-&gt;has_cpu
op_assign
l_int|0
suffix:semicolon
id|p-&gt;processor
op_assign
id|current-&gt;processor
suffix:semicolon
multiline_comment|/* ?? should we just memset this ?? */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|smp_num_cpus
suffix:semicolon
id|i
op_increment
)paren
(brace
id|p-&gt;per_cpu_utime
(braket
id|i
)braket
op_assign
id|p-&gt;per_cpu_stime
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|spin_lock_init
c_func
(paren
op_amp
id|p-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
macro_line|#endif
id|p-&gt;lock_depth
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* -1 = no lock */
id|p-&gt;start_time
op_assign
id|jiffies
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* copy all the process information */
r_if
c_cond
(paren
id|copy_files
c_func
(paren
id|clone_flags
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup
suffix:semicolon
r_if
c_cond
(paren
id|copy_fs
c_func
(paren
id|clone_flags
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup_files
suffix:semicolon
r_if
c_cond
(paren
id|copy_sighand
c_func
(paren
id|clone_flags
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup_fs
suffix:semicolon
r_if
c_cond
(paren
id|copy_mm
c_func
(paren
id|clone_flags
comma
id|p
)paren
)paren
r_goto
id|bad_fork_cleanup_sighand
suffix:semicolon
id|retval
op_assign
id|copy_thread
c_func
(paren
l_int|0
comma
id|clone_flags
comma
id|usp
comma
id|p
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|bad_fork_cleanup_sighand
suffix:semicolon
id|p-&gt;semundo
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Our parent execution domain becomes current domain&n;&t;   These must match for thread signalling to apply */
id|p-&gt;parent_exec_id
op_assign
id|p-&gt;self_exec_id
suffix:semicolon
multiline_comment|/* ok, now we should be set up.. */
id|p-&gt;swappable
op_assign
l_int|1
suffix:semicolon
id|p-&gt;exit_signal
op_assign
id|clone_flags
op_amp
id|CSIGNAL
suffix:semicolon
id|p-&gt;pdeath_signal
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * &quot;share&quot; dynamic priority between parent and child, thus the&n;&t; * total amount of dynamic priorities in the system doesnt change,&n;&t; * more scheduling fairness. This is only important in the first&n;&t; * timeslice, on the long run the scheduling behaviour is unchanged.&n;&t; */
id|current-&gt;counter
op_rshift_assign
l_int|1
suffix:semicolon
id|p-&gt;counter
op_assign
id|current-&gt;counter
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, add it to the run-queues and make it&n;&t; * visible to the rest of the system.&n;&t; *&n;&t; * Let it rip!&n;&t; */
id|retval
op_assign
id|p-&gt;pid
suffix:semicolon
id|write_lock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|SET_LINKS
c_func
(paren
id|p
)paren
suffix:semicolon
id|hash_pid
c_func
(paren
id|p
)paren
suffix:semicolon
id|nr_threads
op_increment
suffix:semicolon
id|write_unlock_irq
c_func
(paren
op_amp
id|tasklist_lock
)paren
suffix:semicolon
id|wake_up_process
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* do this last */
op_increment
id|total_forks
suffix:semicolon
id|bad_fork
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fork_out
suffix:colon
r_if
c_cond
(paren
(paren
id|clone_flags
op_amp
id|CLONE_VFORK
)paren
op_logical_and
(paren
id|retval
OG
l_int|0
)paren
)paren
id|down
c_func
(paren
op_amp
id|sem
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|bad_fork_cleanup_sighand
suffix:colon
id|exit_sighand
c_func
(paren
id|p
)paren
suffix:semicolon
id|bad_fork_cleanup_fs
suffix:colon
id|exit_fs
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* blocking */
id|bad_fork_cleanup_files
suffix:colon
id|exit_files
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* blocking */
id|bad_fork_cleanup
suffix:colon
r_if
c_cond
(paren
id|p-&gt;exec_domain
op_logical_and
id|p-&gt;exec_domain-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|p-&gt;exec_domain-&gt;module
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;binfmt
op_logical_and
id|p-&gt;binfmt-&gt;module
)paren
id|__MOD_DEC_USE_COUNT
c_func
(paren
id|p-&gt;binfmt-&gt;module
)paren
suffix:semicolon
id|bad_fork_cleanup_count
suffix:colon
r_if
c_cond
(paren
id|p-&gt;user
)paren
id|free_uid
c_func
(paren
id|p
)paren
suffix:semicolon
id|bad_fork_free
suffix:colon
id|free_task_struct
c_func
(paren
id|p
)paren
suffix:semicolon
r_goto
id|bad_fork
suffix:semicolon
)brace
DECL|function|filescache_init
r_void
id|__init
id|filescache_init
c_func
(paren
r_void
)paren
(brace
id|files_cachep
op_assign
id|kmem_cache_create
c_func
(paren
l_string|&quot;files_cache&quot;
comma
r_sizeof
(paren
r_struct
id|files_struct
)paren
comma
l_int|0
comma
id|SLAB_HWCACHE_ALIGN
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|files_cachep
)paren
id|panic
c_func
(paren
l_string|&quot;Cannot create files cache&quot;
)paren
suffix:semicolon
)brace
eof
