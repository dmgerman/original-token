multiline_comment|/*&n; *  linux/fs/buffer.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; *  &squot;buffer.c&squot; implements the buffer-cache functions. Race-conditions have&n; * been avoided by NEVER letting a interrupt change a buffer (except for the&n; * data, of course), but instead letting the caller do it.&n; */
multiline_comment|/*&n; * NOTE! There is one discordant note here: checking floppies for&n; * disk change. This is where it fits best, I think, as it should&n; * invalidate changed floppy-disk-caches.&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_SCSI
macro_line|#ifdef CONFIG_BLK_DEV_SR
r_extern
r_int
id|check_cdrom_media_change
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_SD
r_extern
r_int
id|check_scsidisk_media_change
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|revalidate_scsidisk
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
DECL|variable|hash_table
r_static
r_struct
id|buffer_head
op_star
id|hash_table
(braket
id|NR_HASH
)braket
suffix:semicolon
DECL|variable|free_list
r_static
r_struct
id|buffer_head
op_star
id|free_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|unused_list
r_static
r_struct
id|buffer_head
op_star
id|unused_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|buffer_wait
r_static
r_struct
id|wait_queue
op_star
id|buffer_wait
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|nr_buffers
r_int
id|nr_buffers
op_assign
l_int|0
suffix:semicolon
DECL|variable|buffermem
r_int
id|buffermem
op_assign
l_int|0
suffix:semicolon
DECL|variable|nr_buffer_heads
r_int
id|nr_buffer_heads
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Rewrote the wait-routines to use the &quot;new&quot; wait-queue functionality,&n; * and getting rid of the cli-sti pairs. The wait-queue routines still&n; * need cli-sti, but now it&squot;s just a couple of 386 instructions or so.&n; *&n; * Note that the real wait_on_buffer() is an inline function that checks&n; * if &squot;b_wait&squot; is set before calling this, so that the queues aren&squot;t set&n; * up unnecessarily.&n; */
DECL|function|__wait_on_buffer
r_void
id|__wait_on_buffer
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_struct
id|wait_queue
id|wait
op_assign
(brace
id|current
comma
l_int|NULL
)brace
suffix:semicolon
id|add_wait_queue
c_func
(paren
op_amp
id|bh-&gt;b_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|repeat
suffix:colon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_lock
)paren
(brace
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|remove_wait_queue
c_func
(paren
op_amp
id|bh-&gt;b_wait
comma
op_amp
id|wait
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
)brace
DECL|function|sync_buffers
r_static
r_void
id|sync_buffers
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|free_list
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr_buffers
op_star
l_int|2
suffix:semicolon
id|i
op_decrement
OG
l_int|0
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_next_free
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_lock
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_dirt
)paren
r_continue
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|WRITE
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
)brace
)brace
DECL|function|sync_dev
r_void
id|sync_dev
c_func
(paren
id|dev_t
id|dev
)paren
(brace
id|sync_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sync_supers
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sync_inodes
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sync_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|sys_sync
r_int
id|sys_sync
c_func
(paren
r_void
)paren
(brace
id|sync_dev
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|invalidate_buffers
r_void
id|invalidate_buffers
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|bh
op_assign
id|free_list
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nr_buffers
op_star
l_int|2
suffix:semicolon
op_decrement
id|i
OG
l_int|0
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_next_free
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_dev
op_ne
id|dev
)paren
r_continue
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_dev
op_eq
id|dev
)paren
id|bh-&gt;b_uptodate
op_assign
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This routine checks whether a floppy has been changed, and&n; * invalidates all buffer-cache-entries in that case. This&n; * is a relatively slow routine, so we have to try to minimize using&n; * it. Thus it is called only upon a &squot;mount&squot; or &squot;open&squot;. This&n; * is the best way of combining speed and utility, I think.&n; * People changing diskettes in the middle of an operation deserve&n; * to loose :-)&n; *&n; * NOTE! Although currently this is only for floppies, the idea is&n; * that any additional removable block-device will use this routine,&n; * and that mount/open needn&squot;t know that floppies/whatever are&n; * special.&n; */
DECL|function|check_disk_change
r_void
id|check_disk_change
c_func
(paren
id|dev_t
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_switch
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
)paren
(brace
r_case
l_int|2
suffix:colon
multiline_comment|/* floppy disc */
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|dev
comma
l_int|0
comma
l_int|1024
)paren
)paren
)paren
r_return
suffix:semicolon
id|i
op_assign
id|floppy_change
c_func
(paren
id|bh
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_SD) &amp;&amp; defined(CONFIG_SCSI)
r_case
l_int|8
suffix:colon
multiline_comment|/* Removable scsi disk */
id|i
op_assign
id|check_scsidisk_media_change
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;Flushing buffers and inodes for SCSI disk&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_SR) &amp;&amp; defined(CONFIG_SCSI)
r_case
l_int|11
suffix:colon
multiline_comment|/* CDROM */
id|i
op_assign
id|check_cdrom_media_change
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;Flushing buffers and inodes for CDROM&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
r_return
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
r_return
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
id|NR_SUPER
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|super_block
(braket
id|i
)braket
dot
id|s_dev
op_eq
id|dev
)paren
id|put_super
c_func
(paren
id|super_block
(braket
id|i
)braket
dot
id|s_dev
)paren
suffix:semicolon
id|invalidate_inodes
c_func
(paren
id|dev
)paren
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_BLK_DEV_SD) &amp;&amp; defined(CONFIG_SCSI)
multiline_comment|/* This is trickier for a removable hardisk, because we have to invalidate&n;   all of the partitions that lie on the disk. */
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|dev
)paren
op_eq
l_int|8
)paren
id|revalidate_scsidisk
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|macro|_hashfn
mdefine_line|#define _hashfn(dev,block) (((unsigned)(dev^block))%NR_HASH)
DECL|macro|hash
mdefine_line|#define hash(dev,block) hash_table[_hashfn(dev,block)]
DECL|function|remove_from_hash_queue
r_static
r_inline
r_void
id|remove_from_hash_queue
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_next
)paren
id|bh-&gt;b_next-&gt;b_prev
op_assign
id|bh-&gt;b_prev
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_prev
)paren
id|bh-&gt;b_prev-&gt;b_next
op_assign
id|bh-&gt;b_next
suffix:semicolon
r_if
c_cond
(paren
id|hash
c_func
(paren
id|bh-&gt;b_dev
comma
id|bh-&gt;b_blocknr
)paren
op_eq
id|bh
)paren
id|hash
c_func
(paren
id|bh-&gt;b_dev
comma
id|bh-&gt;b_blocknr
)paren
op_assign
id|bh-&gt;b_next
suffix:semicolon
id|bh-&gt;b_next
op_assign
id|bh-&gt;b_prev
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|remove_from_free_list
r_static
r_inline
r_void
id|remove_from_free_list
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh-&gt;b_prev_free
)paren
op_logical_or
op_logical_neg
(paren
id|bh-&gt;b_next_free
)paren
)paren
id|panic
c_func
(paren
l_string|&quot;Free block list corrupted&quot;
)paren
suffix:semicolon
id|bh-&gt;b_prev_free-&gt;b_next_free
op_assign
id|bh-&gt;b_next_free
suffix:semicolon
id|bh-&gt;b_next_free-&gt;b_prev_free
op_assign
id|bh-&gt;b_prev_free
suffix:semicolon
r_if
c_cond
(paren
id|free_list
op_eq
id|bh
)paren
id|free_list
op_assign
id|bh-&gt;b_next_free
suffix:semicolon
id|bh-&gt;b_next_free
op_assign
id|bh-&gt;b_prev_free
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|remove_from_queues
r_static
r_inline
r_void
id|remove_from_queues
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
id|remove_from_hash_queue
c_func
(paren
id|bh
)paren
suffix:semicolon
id|remove_from_free_list
c_func
(paren
id|bh
)paren
suffix:semicolon
)brace
DECL|function|put_first_free
r_static
r_inline
r_void
id|put_first_free
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
(paren
id|bh
op_eq
id|free_list
)paren
)paren
r_return
suffix:semicolon
id|remove_from_free_list
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* add to front of free list */
id|bh-&gt;b_next_free
op_assign
id|free_list
suffix:semicolon
id|bh-&gt;b_prev_free
op_assign
id|free_list-&gt;b_prev_free
suffix:semicolon
id|free_list-&gt;b_prev_free-&gt;b_next_free
op_assign
id|bh
suffix:semicolon
id|free_list-&gt;b_prev_free
op_assign
id|bh
suffix:semicolon
id|free_list
op_assign
id|bh
suffix:semicolon
)brace
DECL|function|put_last_free
r_static
r_inline
r_void
id|put_last_free
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|bh
op_eq
id|free_list
)paren
(brace
id|free_list
op_assign
id|bh-&gt;b_next_free
suffix:semicolon
r_return
suffix:semicolon
)brace
id|remove_from_free_list
c_func
(paren
id|bh
)paren
suffix:semicolon
multiline_comment|/* add to back of free list */
id|bh-&gt;b_next_free
op_assign
id|free_list
suffix:semicolon
id|bh-&gt;b_prev_free
op_assign
id|free_list-&gt;b_prev_free
suffix:semicolon
id|free_list-&gt;b_prev_free-&gt;b_next_free
op_assign
id|bh
suffix:semicolon
id|free_list-&gt;b_prev_free
op_assign
id|bh
suffix:semicolon
)brace
DECL|function|insert_into_queues
r_static
r_inline
r_void
id|insert_into_queues
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
multiline_comment|/* put at end of free list */
id|bh-&gt;b_next_free
op_assign
id|free_list
suffix:semicolon
id|bh-&gt;b_prev_free
op_assign
id|free_list-&gt;b_prev_free
suffix:semicolon
id|free_list-&gt;b_prev_free-&gt;b_next_free
op_assign
id|bh
suffix:semicolon
id|free_list-&gt;b_prev_free
op_assign
id|bh
suffix:semicolon
multiline_comment|/* put the buffer in new hash-queue if it has a device */
id|bh-&gt;b_prev
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_next
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_dev
)paren
r_return
suffix:semicolon
id|bh-&gt;b_next
op_assign
id|hash
c_func
(paren
id|bh-&gt;b_dev
comma
id|bh-&gt;b_blocknr
)paren
suffix:semicolon
id|hash
c_func
(paren
id|bh-&gt;b_dev
comma
id|bh-&gt;b_blocknr
)paren
op_assign
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_next
)paren
id|bh-&gt;b_next-&gt;b_prev
op_assign
id|bh
suffix:semicolon
)brace
DECL|function|find_buffer
r_static
r_struct
id|buffer_head
op_star
id|find_buffer
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
(brace
r_struct
id|buffer_head
op_star
id|tmp
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|hash
c_func
(paren
id|dev
comma
id|block
)paren
suffix:semicolon
id|tmp
op_ne
l_int|NULL
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_next
)paren
r_if
c_cond
(paren
id|tmp-&gt;b_dev
op_eq
id|dev
op_logical_and
id|tmp-&gt;b_blocknr
op_eq
id|block
)paren
r_if
c_cond
(paren
id|tmp-&gt;b_size
op_eq
id|size
)paren
r_return
id|tmp
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;wrong block-size on device %04x&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Why like this, I hear you say... The reason is race-conditions.&n; * As we don&squot;t lock buffers (unless we are readint them, that is),&n; * something might happen to it while we sleep (ie a read-error&n; * will force it bad). This shouldn&squot;t really happen currently, but&n; * the code is ready.&n; */
DECL|function|get_hash_table
r_struct
id|buffer_head
op_star
id|get_hash_table
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|find_buffer
c_func
(paren
id|dev
comma
id|block
comma
id|size
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|bh-&gt;b_count
op_increment
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_dev
op_eq
id|dev
op_logical_and
id|bh-&gt;b_blocknr
op_eq
id|block
op_logical_and
id|bh-&gt;b_size
op_eq
id|size
)paren
r_return
id|bh
suffix:semicolon
id|bh-&gt;b_count
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Ok, this is getblk, and it isn&squot;t very clear, again to hinder&n; * race-conditions. Most of the code is seldom used, (ie repeating),&n; * so it should be much more efficient than it looks.&n; *&n; * The algoritm is changed: hopefully better, and an elusive bug removed.&n; *&n; * 14.02.92: changed it to sync dirty buffers a bit: better performance&n; * when the filesystem starts to get full of dirty blocks (I hope).&n; */
DECL|macro|BADNESS
mdefine_line|#define BADNESS(bh) (((bh)-&gt;b_dirt&lt;&lt;1)+(bh)-&gt;b_lock)
DECL|function|getblk
r_struct
id|buffer_head
op_star
id|getblk
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|tmp
suffix:semicolon
r_int
id|buffers
suffix:semicolon
id|repeat
suffix:colon
id|bh
op_assign
id|get_hash_table
c_func
(paren
id|dev
comma
id|block
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_uptodate
op_logical_and
op_logical_neg
id|bh-&gt;b_dirt
)paren
id|put_last_free
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
r_if
c_cond
(paren
id|nr_free_pages
OG
l_int|30
op_logical_and
id|buffermem
OL
l_int|6
op_star
l_int|1024
op_star
l_int|1024
)paren
id|grow_buffers
c_func
(paren
id|size
)paren
suffix:semicolon
id|buffers
op_assign
id|nr_buffers
suffix:semicolon
id|bh
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|tmp
op_assign
id|free_list
suffix:semicolon
id|buffers
op_decrement
OG
l_int|0
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_next_free
)paren
(brace
r_if
c_cond
(paren
id|tmp-&gt;b_count
op_logical_or
id|tmp-&gt;b_size
op_ne
id|size
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_or
id|BADNESS
c_func
(paren
id|tmp
)paren
OL
id|BADNESS
c_func
(paren
id|bh
)paren
)paren
(brace
id|bh
op_assign
id|tmp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|BADNESS
c_func
(paren
id|tmp
)paren
)paren
r_break
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|tmp-&gt;b_dirt
)paren
id|ll_rw_block
c_func
(paren
id|WRITEA
comma
l_int|1
comma
op_amp
id|tmp
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
op_logical_neg
id|bh
op_logical_and
id|nr_free_pages
OG
l_int|5
)paren
(brace
id|grow_buffers
c_func
(paren
id|size
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* and repeat until we find something good */
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
(brace
id|sleep_on
c_func
(paren
op_amp
id|buffer_wait
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_count
op_logical_or
id|bh-&gt;b_size
op_ne
id|size
)paren
r_goto
id|repeat
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_dirt
)paren
(brace
id|sync_buffers
c_func
(paren
id|bh-&gt;b_dev
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
multiline_comment|/* NOTE!! While we slept waiting for this block, somebody else might */
multiline_comment|/* already have added &quot;this&quot; block to the cache. check it */
r_if
c_cond
(paren
id|find_buffer
c_func
(paren
id|dev
comma
id|block
comma
id|size
)paren
)paren
r_goto
id|repeat
suffix:semicolon
multiline_comment|/* OK, FINALLY we know that this buffer is the only one of it&squot;s kind, */
multiline_comment|/* and that it&squot;s unused (b_count=0), unlocked (b_lock=0), and clean */
id|bh-&gt;b_count
op_assign
l_int|1
suffix:semicolon
id|bh-&gt;b_dirt
op_assign
l_int|0
suffix:semicolon
id|bh-&gt;b_uptodate
op_assign
l_int|0
suffix:semicolon
id|remove_from_queues
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh-&gt;b_dev
op_assign
id|dev
suffix:semicolon
id|bh-&gt;b_blocknr
op_assign
id|block
suffix:semicolon
id|insert_into_queues
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
DECL|function|brelse
r_void
id|brelse
c_func
(paren
r_struct
id|buffer_head
op_star
id|buf
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buf-&gt;b_count
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|buf-&gt;b_count
)paren
r_return
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|buffer_wait
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free free buffer&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * bread() reads a specified block and returns the buffer that contains&n; * it. It returns NULL if the block was unreadable.&n; */
DECL|function|bread
r_struct
id|buffer_head
op_star
id|bread
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|block
comma
r_int
id|size
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|block
comma
id|size
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;bread: getblk returned NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bh-&gt;b_uptodate
)paren
r_return
id|bh
suffix:semicolon
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_uptodate
)paren
r_return
id|bh
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|macro|COPYBLK
mdefine_line|#define COPYBLK(from,to) &bslash;&n;__asm__(&quot;cld&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rep&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movsl&bslash;n&bslash;t&quot; &bslash;&n;&t;::&quot;c&quot; (BLOCK_SIZE/4),&quot;S&quot; (from),&quot;D&quot; (to) &bslash;&n;&t;:&quot;cx&quot;,&quot;di&quot;,&quot;si&quot;)
multiline_comment|/*&n; * bread_page reads four buffers into memory at the desired address. It&squot;s&n; * a function of its own, as there is some speed to be got by reading them&n; * all at the same time, not waiting for one to be read, and then another&n; * etc.&n; */
DECL|function|bread_page
r_void
id|bread_page
c_func
(paren
r_int
r_int
id|address
comma
id|dev_t
id|dev
comma
r_int
id|b
(braket
l_int|4
)braket
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bhr
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|bhnum
op_assign
l_int|0
suffix:semicolon
r_int
id|i
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|b
(braket
id|i
)braket
)paren
(brace
id|bh
(braket
id|i
)braket
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|b
(braket
id|i
)braket
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
op_logical_and
op_logical_neg
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_uptodate
)paren
id|bhr
(braket
id|bhnum
op_increment
)braket
op_assign
id|bh
(braket
id|i
)braket
suffix:semicolon
)brace
r_else
id|bh
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|bhnum
)paren
(brace
id|ll_rw_block
c_func
(paren
id|READ
comma
id|bhnum
comma
id|bhr
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
l_int|4
suffix:semicolon
id|i
op_increment
comma
id|address
op_add_assign
id|BLOCK_SIZE
)paren
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
)paren
(brace
id|wait_on_buffer
c_func
(paren
id|bh
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_uptodate
)paren
id|COPYBLK
c_func
(paren
(paren
r_int
r_int
)paren
id|bh
(braket
id|i
)braket
op_member_access_from_pointer
id|b_data
comma
id|address
)paren
suffix:semicolon
id|brelse
c_func
(paren
id|bh
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Ok, breada can be used as bread, but additionally to mark other&n; * blocks for reading as well. End the argument list with a negative&n; * number.&n; */
DECL|function|breada
r_struct
id|buffer_head
op_star
id|breada
c_func
(paren
id|dev_t
id|dev
comma
r_int
id|first
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|tmp
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|first
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|bh
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|first
comma
l_int|1024
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;breada: getblk returned NULL&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|bh-&gt;b_uptodate
)paren
id|ll_rw_block
c_func
(paren
id|READ
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|first
op_assign
id|va_arg
c_func
(paren
id|args
comma
r_int
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|tmp
op_assign
id|getblk
c_func
(paren
id|dev
comma
id|first
comma
l_int|1024
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tmp-&gt;b_uptodate
)paren
id|ll_rw_block
c_func
(paren
id|READA
comma
l_int|1
comma
op_amp
id|tmp
)paren
suffix:semicolon
id|tmp-&gt;b_count
op_decrement
suffix:semicolon
)brace
)brace
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_uptodate
)paren
r_return
id|bh
suffix:semicolon
id|brelse
c_func
(paren
id|bh
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * See fs/inode.c for the weird use of volatile..&n; */
DECL|function|put_unused_buffer_head
r_static
r_void
id|put_unused_buffer_head
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_struct
id|wait_queue
op_star
id|wait
suffix:semicolon
id|wait
op_assign
(paren
(paren
r_volatile
r_struct
id|buffer_head
op_star
)paren
id|bh
)paren
op_member_access_from_pointer
id|b_wait
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|bh
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|bh
)paren
)paren
suffix:semicolon
(paren
(paren
r_volatile
r_struct
id|buffer_head
op_star
)paren
id|bh
)paren
op_member_access_from_pointer
id|b_wait
op_assign
id|wait
suffix:semicolon
id|bh-&gt;b_next_free
op_assign
id|unused_list
suffix:semicolon
id|unused_list
op_assign
id|bh
suffix:semicolon
)brace
DECL|function|get_more_buffer_heads
r_static
r_void
id|get_more_buffer_heads
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_if
c_cond
(paren
id|unused_list
)paren
r_return
suffix:semicolon
id|page
op_assign
id|get_free_page
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
suffix:semicolon
id|bh
op_assign
(paren
r_struct
id|buffer_head
op_star
)paren
id|page
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
(paren
id|bh
op_plus
l_int|1
)paren
op_le
id|page
op_plus
l_int|4096
)paren
(brace
id|put_unused_buffer_head
c_func
(paren
id|bh
)paren
suffix:semicolon
id|bh
op_increment
suffix:semicolon
id|nr_buffer_heads
op_increment
suffix:semicolon
)brace
)brace
DECL|function|get_unused_buffer_head
r_static
r_struct
id|buffer_head
op_star
id|get_unused_buffer_head
c_func
(paren
r_void
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
id|get_more_buffer_heads
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|unused_list
)paren
r_return
l_int|NULL
suffix:semicolon
id|bh
op_assign
id|unused_list
suffix:semicolon
id|unused_list
op_assign
id|bh-&gt;b_next_free
suffix:semicolon
id|bh-&gt;b_next_free
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_data
op_assign
l_int|NULL
suffix:semicolon
id|bh-&gt;b_size
op_assign
l_int|0
suffix:semicolon
r_return
id|bh
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to increase the number of buffers available: the size argument&n; * is used to determine what kind of buffers we want. Currently only&n; * 1024-byte buffers are supported by the rest of the system, but I&n; * think this will change eventually.&n; */
DECL|function|grow_buffers
r_void
id|grow_buffers
c_func
(paren
r_int
id|size
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|buffer_head
op_star
id|bh
comma
op_star
id|tmp
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
op_amp
l_int|511
)paren
op_logical_or
(paren
id|size
OG
l_int|4096
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;grow_buffers: size = %d&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|page
op_assign
id|get_free_page
c_func
(paren
id|GFP_BUFFER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|page
)paren
r_return
suffix:semicolon
id|tmp
op_assign
l_int|NULL
suffix:semicolon
id|i
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
op_plus
id|size
op_le
l_int|4096
suffix:semicolon
id|i
op_add_assign
id|size
)paren
(brace
id|bh
op_assign
id|get_unused_buffer_head
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bh
)paren
r_goto
id|no_grow
suffix:semicolon
id|bh-&gt;b_this_page
op_assign
id|tmp
suffix:semicolon
id|tmp
op_assign
id|bh
suffix:semicolon
id|bh-&gt;b_data
op_assign
(paren
r_char
op_star
)paren
(paren
id|page
op_plus
id|i
)paren
suffix:semicolon
id|bh-&gt;b_size
op_assign
id|size
suffix:semicolon
)brace
id|tmp
op_assign
id|bh
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|free_list
)paren
(brace
id|tmp-&gt;b_next_free
op_assign
id|free_list
suffix:semicolon
id|tmp-&gt;b_prev_free
op_assign
id|free_list-&gt;b_prev_free
suffix:semicolon
id|free_list-&gt;b_prev_free-&gt;b_next_free
op_assign
id|tmp
suffix:semicolon
id|free_list-&gt;b_prev_free
op_assign
id|tmp
suffix:semicolon
)brace
r_else
(brace
id|tmp-&gt;b_prev_free
op_assign
id|tmp
suffix:semicolon
id|tmp-&gt;b_next_free
op_assign
id|tmp
suffix:semicolon
)brace
id|free_list
op_assign
id|tmp
suffix:semicolon
op_increment
id|nr_buffers
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;b_this_page
)paren
id|tmp
op_assign
id|tmp-&gt;b_this_page
suffix:semicolon
r_else
r_break
suffix:semicolon
)brace
id|tmp-&gt;b_this_page
op_assign
id|bh
suffix:semicolon
id|buffermem
op_add_assign
l_int|4096
suffix:semicolon
r_return
suffix:semicolon
multiline_comment|/*&n; * In case anything failed, we just free everything we got.&n; */
id|no_grow
suffix:colon
id|bh
op_assign
id|tmp
suffix:semicolon
r_while
c_loop
(paren
id|bh
)paren
(brace
id|tmp
op_assign
id|bh
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_this_page
suffix:semicolon
id|put_unused_buffer_head
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
id|free_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * try_to_free() checks if all the buffers on this particular page&n; * are unused, and free&squot;s the page if so.&n; */
DECL|function|try_to_free
r_static
r_int
id|try_to_free
c_func
(paren
r_struct
id|buffer_head
op_star
id|bh
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_struct
id|buffer_head
op_star
id|tmp
comma
op_star
id|p
suffix:semicolon
id|tmp
op_assign
id|bh
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;b_count
op_logical_or
id|tmp-&gt;b_dirt
op_logical_or
id|tmp-&gt;b_lock
)paren
r_return
l_int|0
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_this_page
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
op_ne
id|bh
)paren
suffix:semicolon
id|page
op_assign
(paren
r_int
r_int
)paren
id|bh-&gt;b_data
suffix:semicolon
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|tmp
op_assign
id|bh
suffix:semicolon
r_do
(brace
id|p
op_assign
id|tmp
suffix:semicolon
id|tmp
op_assign
id|tmp-&gt;b_this_page
suffix:semicolon
id|nr_buffers
op_decrement
suffix:semicolon
id|remove_from_queues
c_func
(paren
id|p
)paren
suffix:semicolon
id|put_unused_buffer_head
c_func
(paren
id|p
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|tmp
op_ne
id|bh
)paren
suffix:semicolon
id|buffermem
op_sub_assign
l_int|4096
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
multiline_comment|/*&n; * Try to free up some pages by shrinking the buffer-cache&n; *&n; * Priority tells the routine how hard to try to shrink the&n; * buffers: 3 means &quot;don&squot;t bother too much&quot;, while a value&n; * of 0 means &quot;we&squot;d better get some free pages now&quot;.&n; */
DECL|function|shrink_buffers
r_int
id|shrink_buffers
c_func
(paren
r_int
r_int
id|priority
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|priority
OL
l_int|2
)paren
id|sync_buffers
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|bh
op_assign
id|free_list
suffix:semicolon
id|i
op_assign
id|nr_buffers
op_rshift
id|priority
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
op_decrement
OG
l_int|0
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_next_free
)paren
(brace
r_if
c_cond
(paren
id|bh-&gt;b_count
op_logical_or
op_logical_neg
id|bh-&gt;b_this_page
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_lock
)paren
r_if
c_cond
(paren
id|priority
)paren
r_continue
suffix:semicolon
r_else
id|wait_on_buffer
c_func
(paren
id|bh
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bh-&gt;b_dirt
)paren
(brace
id|ll_rw_block
c_func
(paren
id|WRITEA
comma
l_int|1
comma
op_amp
id|bh
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|try_to_free
c_func
(paren
id|bh
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
multiline_comment|/*&n; * This initializes the initial buffer free list.  nr_buffers is set&n; * to one less the actual number of buffers, as a sop to backwards&n; * compatibility --- the old code did this (I think unintentionally,&n; * but I&squot;m not sure), and programs in the ps package expect it.&n; * &t;&t;&t;&t;&t;- TYT 8/30/92&n; */
DECL|function|buffer_init
r_void
id|buffer_init
c_func
(paren
r_void
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
l_int|0
suffix:semicolon
id|i
OL
id|NR_HASH
suffix:semicolon
id|i
op_increment
)paren
id|hash_table
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
id|free_list
op_assign
l_int|0
suffix:semicolon
id|grow_buffers
c_func
(paren
id|BLOCK_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|free_list
)paren
id|panic
c_func
(paren
l_string|&quot;Unable to initialize buffer free list!&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
eof
