multiline_comment|/*&n; * tqueue.h --- task queue handling for Linux.&n; *&n; * Mostly based on a proposed bottom-half replacement code written by&n; * Kai Petzke, wpp@marie.physik.tu-berlin.de.&n; *&n; * Modified for use in the Linux kernel by Theodore Ts&squot;o,&n; * tytso@mit.edu.  Any bugs are my fault, not Kai&squot;s.&n; *&n; * The original comment follows below.&n; */
macro_line|#ifndef _LINUX_TQUEUE_H
DECL|macro|_LINUX_TQUEUE_H
mdefine_line|#define _LINUX_TQUEUE_H
macro_line|#ifdef INCLUDE_INLINE_FUNCS
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_ extern
macro_line|#else
DECL|macro|_INLINE_
mdefine_line|#define _INLINE_ extern __inline__
macro_line|#endif
multiline_comment|/*&n; * New proposed &quot;bottom half&quot; handlers:&n; * (C) 1994 Kai Petzke, wpp@marie.physik.tu-berlin.de&n; *&n; * Advantages:&n; * - Bottom halfs are implemented as a linked list.  You can have as many&n; *   of them, as you want.&n; * - No more scanning of a bit field is required upon call of a bottom half.&n; * - Support for chained bottom half lists.  The run_task_queue() function can be&n; *   used as a bottom half handler.  This is for example useful for bottom&n; *   halfs, which want to be delayed until the next clock tick.&n; *&n; * Problems:&n; * - The queue_task_irq() inline function is only atomic with respect to itself.&n; *   Problems can occur, when queue_task_irq() is called from a normal system&n; *   call, and an interrupt comes in.  No problems occur, when queue_task_irq()&n; *   is called from an interrupt or bottom half, and interrupted, as run_task_queue()&n; *   will not be executed/continued before the last interrupt returns.  If in&n; *   doubt, use queue_task(), not queue_task_irq().&n; * - Bottom halfs are called in the reverse order that they were linked into&n; *   the list.&n; */
DECL|struct|tq_struct
r_struct
id|tq_struct
(brace
DECL|member|next
r_struct
id|tq_struct
op_star
id|next
suffix:semicolon
multiline_comment|/* linked list of active bh&squot;s */
DECL|member|sync
r_int
id|sync
suffix:semicolon
multiline_comment|/* must be initialized to zero */
DECL|member|routine
r_void
(paren
op_star
id|routine
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
multiline_comment|/* function to call */
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
multiline_comment|/* argument to function */
)brace
suffix:semicolon
DECL|typedef|task_queue
r_typedef
r_struct
id|tq_struct
op_star
id|task_queue
suffix:semicolon
DECL|macro|DECLARE_TASK_QUEUE
mdefine_line|#define DECLARE_TASK_QUEUE(q)  task_queue q = &amp;tq_last
r_extern
r_struct
id|tq_struct
id|tq_last
suffix:semicolon
r_extern
id|task_queue
id|tq_timer
suffix:semicolon
macro_line|#ifdef INCLUDE_INLINE_FUNCS
DECL|variable|tq_last
r_struct
id|tq_struct
id|tq_last
op_assign
(brace
op_amp
id|tq_last
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * To implement your own list of active bottom halfs, use the following&n; * two definitions:&n; *&n; * struct tq_struct *my_bh = &amp;tq_last;&n; * struct tq_struct run_my_bh = {&n; *&t;0, 0, (void *)(void *) run_task_queue, &amp;my_bh&n; * };&n; *&n; * To activate a bottom half on your list, use:&n; *&n; *     queue_task(tq_pointer, &amp;my_bh);&n; *&n; * To run the bottom halfs on your list put them on the immediate list by:&n; *&n; *     queue_task(&amp;run_my_bh, &amp;tq_immediate);&n; *&n; * This allows you to do deferred procession.  For example, you could&n; * have a bottom half list tq_timer, which is marked active by the timer&n; * interrupt.&n; */
multiline_comment|/*&n; * queue_task_irq: put the bottom half handler &quot;bh_pointer&quot; on the list&n; * &quot;bh_list&quot;.  You may call this function only from an interrupt&n; * handler or a bottom half handler.&n; */
DECL|function|queue_task_irq
id|_INLINE_
r_void
id|queue_task_irq
c_func
(paren
r_struct
id|tq_struct
op_star
id|bh_pointer
comma
id|task_queue
op_star
id|bh_list
)paren
(brace
r_int
id|l1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;btsl $0,%1&bslash;n&bslash;t&quot;
multiline_comment|/* bottom half already marked? */
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;leal %2,%3&bslash;n&bslash;t&quot;
multiline_comment|/* address of the &quot;next&quot; field of bh_struct */
l_string|&quot;xchgl %3,%0&bslash;n&bslash;t&quot;
multiline_comment|/* link bottom half into list */
l_string|&quot;movl %3,%2&bslash;n1:&quot;
multiline_comment|/* save the pointer to next bottom half */
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|bh_list
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|sync
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|next
)paren
comma
l_string|&quot;=r&quot;
(paren
id|l1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * queue_task_irq_off: put the bottom half handler &quot;bh_pointer&quot; on the list&n; * &quot;bh_list&quot;.  You may call this function only when interrupts are off.&n; */
DECL|function|queue_task_irq_off
id|_INLINE_
r_void
id|queue_task_irq_off
c_func
(paren
r_struct
id|tq_struct
op_star
id|bh_pointer
comma
id|task_queue
op_star
id|bh_list
)paren
(brace
r_int
id|l1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;testl $1,%1&bslash;n&bslash;t&quot;
multiline_comment|/* bottom half already marked? */
l_string|&quot;jne 1f&bslash;n&bslash;t&quot;
l_string|&quot;movl $1,%1&bslash;n&bslash;t&quot;
l_string|&quot;leal %2,%3&bslash;n&bslash;t&quot;
multiline_comment|/* address of the &quot;next&quot; field of bh_struct */
l_string|&quot;xchgl %3,%0&bslash;n&bslash;t&quot;
multiline_comment|/* link bottom half into list */
l_string|&quot;movl %3,%2&bslash;n1:&quot;
multiline_comment|/* save the pointer to next bottom half */
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|bh_list
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|sync
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|next
)paren
comma
l_string|&quot;=r&quot;
(paren
id|l1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * queue_task: as queue_task_irq, but can be called from anywhere.&n; */
DECL|function|queue_task
id|_INLINE_
r_void
id|queue_task
c_func
(paren
r_struct
id|tq_struct
op_star
id|bh_pointer
comma
id|task_queue
op_star
id|bh_list
)paren
(brace
r_int
id|l1
suffix:semicolon
id|__asm__
id|__volatile__
(paren
l_string|&quot;btsl $0,%1&bslash;n&bslash;t&quot;
l_string|&quot;jc 1f&bslash;n&bslash;t&quot;
l_string|&quot;leal %2,%3&bslash;n&bslash;t&quot;
l_string|&quot;pushfl&bslash;n&bslash;t&quot;
multiline_comment|/* save interrupt flag */
l_string|&quot;cli&bslash;n&bslash;t&quot;
multiline_comment|/* turn off interrupts */
l_string|&quot;xchgl %3,%0&bslash;n&bslash;t&quot;
l_string|&quot;movl %3,%2&bslash;n&bslash;t&quot;
multiline_comment|/* now the linking step is really atomic! */
l_string|&quot;popfl&bslash;n1:&quot;
multiline_comment|/* restore interrupt flag */
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
id|bh_list
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|sync
)paren
comma
l_string|&quot;=m&quot;
(paren
id|bh_pointer
op_member_access_from_pointer
id|next
)paren
comma
l_string|&quot;=r&quot;
(paren
id|l1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Call all &quot;bottom halfs&quot; on a given list.&n; */
DECL|function|run_task_queue
id|_INLINE_
r_void
id|run_task_queue
c_func
(paren
id|task_queue
op_star
id|list
)paren
(brace
r_register
r_struct
id|tq_struct
op_star
id|save_p
suffix:semicolon
r_register
r_struct
id|tq_struct
op_star
id|p
suffix:semicolon
r_void
op_star
id|arg
suffix:semicolon
r_void
(paren
op_star
id|f
)paren
(paren
r_void
op_star
)paren
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
id|tq_last
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;xchgl %0,%2&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|p
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|p
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|list
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
op_amp
id|tq_last
)paren
(brace
r_break
suffix:semicolon
)brace
r_do
(brace
id|arg
op_assign
id|p
op_member_access_from_pointer
id|data
suffix:semicolon
id|f
op_assign
id|p
op_member_access_from_pointer
id|routine
suffix:semicolon
id|save_p
op_assign
id|p
op_member_access_from_pointer
id|next
suffix:semicolon
id|p
op_member_access_from_pointer
id|sync
op_assign
l_int|0
suffix:semicolon
(paren
op_star
id|f
)paren
(paren
id|arg
)paren
suffix:semicolon
id|p
op_assign
id|save_p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
op_ne
op_amp
id|tq_last
)paren
(brace
suffix:semicolon
)brace
)brace
)brace
DECL|macro|_INLINE_
macro_line|#undef _INLINE_
macro_line|#endif /* _LINUX_TQUEUE_H */
eof
