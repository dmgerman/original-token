macro_line|#ifndef _LINUX_WAIT_H
DECL|macro|_LINUX_WAIT_H
mdefine_line|#define _LINUX_WAIT_H
DECL|macro|WNOHANG
mdefine_line|#define WNOHANG&t;&t;0x00000001
DECL|macro|WUNTRACED
mdefine_line|#define WUNTRACED&t;0x00000002
DECL|macro|__WCLONE
mdefine_line|#define __WCLONE&t;0x80000000
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/page.h&gt;
DECL|struct|wait_queue
r_struct
id|wait_queue
(brace
DECL|member|task
r_struct
id|task_struct
op_star
id|task
suffix:semicolon
DECL|member|next
r_struct
id|wait_queue
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|WAIT_QUEUE_HEAD
mdefine_line|#define WAIT_QUEUE_HEAD(x) ((struct wait_queue *)((x)-1))
DECL|function|init_waitqueue
r_static
r_inline
r_void
id|init_waitqueue
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|q
)paren
(brace
op_star
id|q
op_assign
id|WAIT_QUEUE_HEAD
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
DECL|function|waitqueue_active
r_static
r_inline
r_int
id|waitqueue_active
c_func
(paren
r_struct
id|wait_queue
op_star
op_star
id|q
)paren
(brace
r_struct
id|wait_queue
op_star
id|head
op_assign
op_star
id|q
suffix:semicolon
r_return
id|head
op_logical_and
id|head
op_ne
id|WAIT_QUEUE_HEAD
c_func
(paren
id|q
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif
eof
