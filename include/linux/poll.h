macro_line|#ifndef _LINUX_POLL_H
DECL|macro|_LINUX_POLL_H
mdefine_line|#define _LINUX_POLL_H
macro_line|#include &lt;asm/poll.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|struct|poll_table_entry
r_struct
id|poll_table_entry
(brace
DECL|member|filp
r_struct
id|file
op_star
id|filp
suffix:semicolon
DECL|member|wait
r_struct
id|wait_queue
id|wait
suffix:semicolon
DECL|member|wait_address
r_struct
id|wait_queue
op_star
op_star
id|wait_address
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|poll_table_struct
r_typedef
r_struct
id|poll_table_struct
(brace
DECL|member|nr
r_int
r_int
id|nr
suffix:semicolon
DECL|member|entry
r_struct
id|poll_table_entry
op_star
id|entry
suffix:semicolon
DECL|typedef|poll_table
)brace
id|poll_table
suffix:semicolon
DECL|macro|__MAX_POLL_TABLE_ENTRIES
mdefine_line|#define __MAX_POLL_TABLE_ENTRIES (PAGE_SIZE / sizeof (struct poll_table_entry))
DECL|function|poll_wait
r_extern
r_inline
r_void
id|poll_wait
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|wait_queue
op_star
op_star
id|wait_address
comma
id|poll_table
op_star
id|p
)paren
(brace
r_struct
id|poll_table_entry
op_star
id|entry
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
id|wait_address
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;nr
op_ge
id|__MAX_POLL_TABLE_ENTRIES
)paren
r_return
suffix:semicolon
id|entry
op_assign
id|p-&gt;entry
op_plus
id|p-&gt;nr
suffix:semicolon
id|entry-&gt;filp
op_assign
id|filp
suffix:semicolon
id|filp-&gt;f_count
op_increment
suffix:semicolon
id|entry-&gt;wait_address
op_assign
id|wait_address
suffix:semicolon
id|entry-&gt;wait.task
op_assign
id|current
suffix:semicolon
id|entry-&gt;wait.next
op_assign
l_int|NULL
suffix:semicolon
id|add_wait_queue
c_func
(paren
id|wait_address
comma
op_amp
id|entry-&gt;wait
)paren
suffix:semicolon
id|p-&gt;nr
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * For the kernel fd_set we use a fixed set-size for allocation purposes.&n; * This set-size doesn&squot;t necessarily bear any relation to the size the user&n; * uses, but should preferably obviously be larger than any possible user&n; * size (NR_OPEN bits).&n; *&n; * We need 6 bitmaps (in/out/ex for both incoming and outgoing), and we&n; * allocate one page for all the bitmaps. Thus we have 8*PAGE_SIZE bits,&n; * to be divided by 6. And we&squot;d better make sure we round to a full&n; * long-word (in fact, we&squot;ll round to 64 bytes).&n; */
DECL|macro|KFDS_64BLOCK
mdefine_line|#define KFDS_64BLOCK ((PAGE_SIZE/(6*64))*64)
DECL|macro|KFDS_NR
mdefine_line|#define KFDS_NR (KFDS_64BLOCK*8 &gt; NR_OPEN ? NR_OPEN : KFDS_64BLOCK*8)
DECL|typedef|kernel_fd_set
r_typedef
r_int
r_int
id|kernel_fd_set
(braket
id|KFDS_NR
op_div
id|__NFDBITS
)braket
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|in
DECL|member|out
DECL|member|ex
id|kernel_fd_set
id|in
comma
id|out
comma
id|ex
suffix:semicolon
DECL|member|res_in
DECL|member|res_out
DECL|member|res_ex
id|kernel_fd_set
id|res_in
comma
id|res_out
comma
id|res_ex
suffix:semicolon
DECL|typedef|fd_set_buffer
)brace
id|fd_set_buffer
suffix:semicolon
multiline_comment|/*&n; * We do a VERIFY_WRITE here even though we are only reading this time:&n; * we&squot;ll write to it eventually..&n; *&n; * Use &quot;unsigned long&quot; accesses to let user-mode fd_set&squot;s be long-aligned.&n; */
r_static
r_inline
DECL|function|get_fd_set
r_int
id|get_fd_set
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|ufdset
comma
r_int
r_int
op_star
id|fdset
)paren
(brace
multiline_comment|/* round up nr to nearest &quot;unsigned long&quot; */
id|nr
op_assign
(paren
id|nr
op_plus
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ufdset
)paren
(brace
r_int
id|error
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|ufdset
comma
id|nr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|error
)paren
id|error
op_assign
id|__copy_from_user
c_func
(paren
id|fdset
comma
id|ufdset
comma
id|nr
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
id|memset
c_func
(paren
id|fdset
comma
l_int|0
comma
id|nr
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
DECL|function|set_fd_set
r_void
id|set_fd_set
c_func
(paren
r_int
r_int
id|nr
comma
r_void
op_star
id|ufdset
comma
r_int
r_int
op_star
id|fdset
)paren
(brace
r_if
c_cond
(paren
id|ufdset
)paren
(brace
id|nr
op_assign
(paren
id|nr
op_plus
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|__copy_to_user
c_func
(paren
id|ufdset
comma
id|fdset
comma
id|nr
)paren
suffix:semicolon
)brace
)brace
r_static
r_inline
DECL|function|zero_fd_set
r_void
id|zero_fd_set
c_func
(paren
r_int
r_int
id|nr
comma
r_int
r_int
op_star
id|fdset
)paren
(brace
id|nr
op_assign
(paren
id|nr
op_plus
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
op_div
(paren
l_int|8
op_star
r_sizeof
(paren
r_int
)paren
)paren
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|memset
c_func
(paren
id|fdset
comma
l_int|0
comma
id|nr
)paren
suffix:semicolon
)brace
r_extern
r_int
id|do_select
c_func
(paren
r_int
id|n
comma
id|fd_set_buffer
op_star
id|fds
comma
r_int
r_int
id|timeout
)paren
suffix:semicolon
macro_line|#endif /* KERNEL */
macro_line|#endif /* _LINUX_POLL_H */
eof
