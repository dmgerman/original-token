multiline_comment|/*&n; *  linux/fs/locks.c&n; *&n; *  Provide support for fcntl()&squot;s F_GETLK, F_SETLK, and F_SETLKW calls.&n; *  Doug Evans, 92Aug07, dje@sspiff.uucp.&n; *&n; * FIXME: two things aren&squot;t handled yet:&n; *&t;- deadlock detection/avoidance (of dubious merit, but since it&squot;s in&n; *&t;  the definition, I guess it should be provided eventually)&n; *&t;- mandatory locks (requires lots of changes elsewhere)&n; *&n; *  Edited by Kai Petzke, wpp@marie.physik.tu-berlin.de&n; */
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
DECL|macro|OFFSET_MAX
mdefine_line|#define OFFSET_MAX&t;((off_t)0x7fffffff)&t;/* FIXME: move elsewhere? */
r_static
r_int
id|copy_flock
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|file_lock
op_star
id|fl
comma
r_struct
id|flock
op_star
id|l
)paren
suffix:semicolon
r_static
r_int
id|conflict
c_func
(paren
r_struct
id|file_lock
op_star
id|caller_fl
comma
r_struct
id|file_lock
op_star
id|sys_fl
)paren
suffix:semicolon
r_static
r_int
id|overlap
c_func
(paren
r_struct
id|file_lock
op_star
id|fl1
comma
r_struct
id|file_lock
op_star
id|fl2
)paren
suffix:semicolon
r_static
r_int
id|lock_it
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|file_lock
op_star
id|caller
)paren
suffix:semicolon
r_static
r_struct
id|file_lock
op_star
id|alloc_lock
c_func
(paren
r_struct
id|file_lock
op_star
op_star
id|pos
comma
r_struct
id|file_lock
op_star
id|fl
)paren
suffix:semicolon
r_static
r_void
id|free_lock
c_func
(paren
r_struct
id|file_lock
op_star
op_star
id|fl
)paren
suffix:semicolon
DECL|variable|file_lock_table
r_static
r_struct
id|file_lock
id|file_lock_table
(braket
id|NR_FILE_LOCKS
)braket
suffix:semicolon
DECL|variable|file_lock_free_list
r_static
r_struct
id|file_lock
op_star
id|file_lock_free_list
suffix:semicolon
multiline_comment|/*&n; * Called at boot time to initialize the lock table ...&n; */
DECL|function|fcntl_init_locks
r_void
id|fcntl_init_locks
c_func
(paren
r_void
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
r_for
c_loop
(paren
id|fl
op_assign
op_amp
id|file_lock_table
(braket
l_int|0
)braket
suffix:semicolon
id|fl
OL
id|file_lock_table
op_plus
id|NR_FILE_LOCKS
op_minus
l_int|1
suffix:semicolon
id|fl
op_increment
)paren
(brace
id|fl-&gt;fl_next
op_assign
id|fl
op_plus
l_int|1
suffix:semicolon
id|fl-&gt;fl_owner
op_assign
l_int|NULL
suffix:semicolon
)brace
id|file_lock_table
(braket
id|NR_FILE_LOCKS
op_minus
l_int|1
)braket
dot
id|fl_next
op_assign
l_int|NULL
suffix:semicolon
id|file_lock_table
(braket
id|NR_FILE_LOCKS
op_minus
l_int|1
)braket
dot
id|fl_owner
op_assign
l_int|NULL
suffix:semicolon
id|file_lock_free_list
op_assign
op_amp
id|file_lock_table
(braket
l_int|0
)braket
suffix:semicolon
)brace
DECL|function|fcntl_getlk
r_int
id|fcntl_getlk
c_func
(paren
r_int
r_int
id|fd
comma
r_struct
id|flock
op_star
id|l
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|flock
id|flock
suffix:semicolon
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_struct
id|file_lock
op_star
id|fl
comma
id|file_lock
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|filp
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|l
comma
r_sizeof
(paren
op_star
id|l
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|flock
comma
id|l
comma
r_sizeof
(paren
id|flock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flock.l_type
op_eq
id|F_UNLCK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_flock
c_func
(paren
id|filp
comma
op_amp
id|file_lock
comma
op_amp
id|flock
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_for
c_loop
(paren
id|fl
op_assign
id|filp-&gt;f_inode-&gt;i_flock
suffix:semicolon
id|fl
op_ne
l_int|NULL
suffix:semicolon
id|fl
op_assign
id|fl-&gt;fl_next
)paren
(brace
r_if
c_cond
(paren
id|conflict
c_func
(paren
op_amp
id|file_lock
comma
id|fl
)paren
)paren
(brace
id|flock.l_pid
op_assign
id|fl-&gt;fl_owner-&gt;pid
suffix:semicolon
id|flock.l_start
op_assign
id|fl-&gt;fl_start
suffix:semicolon
id|flock.l_len
op_assign
id|fl-&gt;fl_end
op_eq
id|OFFSET_MAX
ques
c_cond
l_int|0
suffix:colon
id|fl-&gt;fl_end
op_minus
id|fl-&gt;fl_start
op_plus
l_int|1
suffix:semicolon
id|flock.l_whence
op_assign
id|fl-&gt;fl_whence
suffix:semicolon
id|flock.l_type
op_assign
id|fl-&gt;fl_type
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|l
comma
op_amp
id|flock
comma
r_sizeof
(paren
id|flock
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|flock.l_type
op_assign
id|F_UNLCK
suffix:semicolon
multiline_comment|/* no conflict found */
id|memcpy_tofs
c_func
(paren
id|l
comma
op_amp
id|flock
comma
r_sizeof
(paren
id|flock
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This function implements both F_SETLK and F_SETLKW.&n; */
DECL|function|fcntl_setlk
r_int
id|fcntl_setlk
c_func
(paren
r_int
r_int
id|fd
comma
r_int
r_int
id|cmd
comma
r_struct
id|flock
op_star
id|l
)paren
(brace
r_int
id|error
suffix:semicolon
r_struct
id|file
op_star
id|filp
suffix:semicolon
r_struct
id|file_lock
op_star
id|fl
comma
id|file_lock
suffix:semicolon
r_struct
id|flock
id|flock
suffix:semicolon
multiline_comment|/*&n;&t; * Get arguments and validate them ...&n;&t; */
r_if
c_cond
(paren
id|fd
op_ge
id|NR_OPEN
op_logical_or
op_logical_neg
(paren
id|filp
op_assign
id|current-&gt;filp
(braket
id|fd
)braket
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|error
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|l
comma
r_sizeof
(paren
op_star
id|l
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|flock
comma
id|l
comma
r_sizeof
(paren
id|flock
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|copy_flock
c_func
(paren
id|filp
comma
op_amp
id|file_lock
comma
op_amp
id|flock
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_switch
c_cond
(paren
id|file_lock.fl_type
)paren
(brace
r_case
id|F_RDLCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_mode
op_amp
l_int|1
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_WRLCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_mode
op_amp
l_int|2
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_SHLCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_mode
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|file_lock.fl_type
op_assign
id|F_RDLCK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_EXLCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|filp-&gt;f_mode
op_amp
l_int|3
)paren
)paren
r_return
op_minus
id|EBADF
suffix:semicolon
id|file_lock.fl_type
op_assign
id|F_WRLCK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|F_UNLCK
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;  &t; * Scan for a conflicting lock ...&n;  &t; */
r_if
c_cond
(paren
id|file_lock.fl_type
op_ne
id|F_UNLCK
)paren
(brace
id|repeat
suffix:colon
r_for
c_loop
(paren
id|fl
op_assign
id|filp-&gt;f_inode-&gt;i_flock
suffix:semicolon
id|fl
op_ne
l_int|NULL
suffix:semicolon
id|fl
op_assign
id|fl-&gt;fl_next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|conflict
c_func
(paren
op_amp
id|file_lock
comma
id|fl
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * File is locked by another process. If this is&n;&t;&t;&t; * F_SETLKW wait for the lock to be released.&n;&t;&t;&t; * FIXME: We need to check for deadlocks here.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|cmd
op_eq
id|F_SETLKW
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|fl-&gt;fl_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Lock doesn&squot;t conflict with any other lock ...&n;&t; */
r_return
id|lock_it
c_func
(paren
id|filp
comma
op_amp
id|file_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function is called when the file is closed.&n; */
DECL|function|fcntl_remove_locks
r_void
id|fcntl_remove_locks
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_struct
id|file
op_star
id|filp
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
r_struct
id|file_lock
op_star
op_star
id|before
suffix:semicolon
multiline_comment|/* Find first lock owned by caller ... */
id|before
op_assign
op_amp
id|filp-&gt;f_inode-&gt;i_flock
suffix:semicolon
r_while
c_loop
(paren
(paren
id|fl
op_assign
op_star
id|before
)paren
op_logical_and
id|task
op_ne
id|fl-&gt;fl_owner
)paren
id|before
op_assign
op_amp
id|fl-&gt;fl_next
suffix:semicolon
multiline_comment|/* The list is sorted by owner ... */
r_while
c_loop
(paren
(paren
id|fl
op_assign
op_star
id|before
)paren
op_logical_and
id|task
op_eq
id|fl-&gt;fl_owner
)paren
id|free_lock
c_func
(paren
id|before
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Verify a &quot;struct flock&quot; and copy it to a &quot;struct file_lock&quot; ...&n; * Result is a boolean indicating success.&n; */
DECL|function|copy_flock
r_static
r_int
id|copy_flock
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|file_lock
op_star
id|fl
comma
r_struct
id|flock
op_star
id|l
)paren
(brace
id|off_t
id|start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|filp-&gt;f_inode
)paren
multiline_comment|/* just in case */
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|filp-&gt;f_inode-&gt;i_mode
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|l-&gt;l_type
op_ne
id|F_UNLCK
op_logical_and
id|l-&gt;l_type
op_ne
id|F_RDLCK
op_logical_and
id|l-&gt;l_type
op_ne
id|F_WRLCK
op_logical_and
id|l-&gt;l_type
op_ne
id|F_SHLCK
op_logical_and
id|l-&gt;l_type
op_ne
id|F_EXLCK
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|l-&gt;l_whence
)paren
(brace
r_case
l_int|0
multiline_comment|/*SEEK_SET*/
suffix:colon
id|start
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
multiline_comment|/*SEEK_CUR*/
suffix:colon
id|start
op_assign
id|filp-&gt;f_pos
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
multiline_comment|/*SEEK_END*/
suffix:colon
id|start
op_assign
id|filp-&gt;f_inode-&gt;i_size
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|start
op_add_assign
id|l-&gt;l_start
)paren
OL
l_int|0
op_logical_or
id|l-&gt;l_len
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|fl-&gt;fl_type
op_assign
id|l-&gt;l_type
suffix:semicolon
id|fl-&gt;fl_start
op_assign
id|start
suffix:semicolon
multiline_comment|/* we record the absolute position */
id|fl-&gt;fl_whence
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME: do we record {l_start} as passed? */
r_if
c_cond
(paren
id|l-&gt;l_len
op_eq
l_int|0
op_logical_or
(paren
id|fl-&gt;fl_end
op_assign
id|start
op_plus
id|l-&gt;l_len
op_minus
l_int|1
)paren
OL
l_int|0
)paren
id|fl-&gt;fl_end
op_assign
id|OFFSET_MAX
suffix:semicolon
id|fl-&gt;fl_owner
op_assign
id|current
suffix:semicolon
id|fl-&gt;fl_wait
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* just for cleanliness */
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine if lock {sys_fl} blocks lock {caller_fl} ...&n; */
DECL|function|conflict
r_static
r_int
id|conflict
c_func
(paren
r_struct
id|file_lock
op_star
id|caller_fl
comma
r_struct
id|file_lock
op_star
id|sys_fl
)paren
(brace
r_if
c_cond
(paren
id|caller_fl-&gt;fl_owner
op_eq
id|sys_fl-&gt;fl_owner
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|overlap
c_func
(paren
id|caller_fl
comma
id|sys_fl
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|caller_fl-&gt;fl_type
)paren
(brace
r_case
id|F_RDLCK
suffix:colon
r_return
id|sys_fl-&gt;fl_type
op_ne
id|F_RDLCK
suffix:semicolon
r_case
id|F_WRLCK
suffix:colon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* overlapping region not owned by caller */
)brace
r_return
l_int|0
suffix:semicolon
multiline_comment|/* shouldn&squot;t get here, but just in case */
)brace
DECL|function|overlap
r_static
r_int
id|overlap
c_func
(paren
r_struct
id|file_lock
op_star
id|fl1
comma
r_struct
id|file_lock
op_star
id|fl2
)paren
(brace
r_return
id|fl1-&gt;fl_end
op_ge
id|fl2-&gt;fl_start
op_logical_and
id|fl2-&gt;fl_end
op_ge
id|fl1-&gt;fl_start
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a lock to a file ...&n; * Result is 0 for success or -ENOLCK.&n; *&n; * We merge adjacent locks whenever possible.&n; *&n; * WARNING: We assume the lock doesn&squot;t conflict with any other lock.&n; */
multiline_comment|/*&n; * Rewritten by Kai Petzke:&n; * We sort the lock list first by owner, then by the starting address.&n; *&n; * To make freeing a lock much faster, we keep a pointer to the lock before the&n; * actual one. But the real gain of the new coding was, that lock_it() and&n; * unlock_it() became one function.&n; *&n; * To all purists: Yes, I use a few goto&squot;s. Just pass on to the next function.&n; */
DECL|function|lock_it
r_static
r_int
id|lock_it
c_func
(paren
r_struct
id|file
op_star
id|filp
comma
r_struct
id|file_lock
op_star
id|caller
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
r_struct
id|file_lock
op_star
id|left
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_lock
op_star
id|right
op_assign
l_int|0
suffix:semicolon
r_struct
id|file_lock
op_star
op_star
id|before
suffix:semicolon
r_int
id|added
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Find the first old lock with the same owner as the new lock.&n;&t; */
id|before
op_assign
op_amp
id|filp-&gt;f_inode-&gt;i_flock
suffix:semicolon
r_while
c_loop
(paren
(paren
id|fl
op_assign
op_star
id|before
)paren
op_logical_and
id|caller-&gt;fl_owner
op_ne
id|fl-&gt;fl_owner
)paren
id|before
op_assign
op_amp
id|fl-&gt;fl_next
suffix:semicolon
multiline_comment|/*&n;&t; * Look up all locks of this owner.&n;&t; */
r_while
c_loop
(paren
(paren
id|fl
op_assign
op_star
id|before
)paren
op_logical_and
id|caller-&gt;fl_owner
op_eq
id|fl-&gt;fl_owner
)paren
(brace
multiline_comment|/*&n;&t;&t; * Detect adjacent or overlapping regions (if same lock type)&n;&t;&t; */
r_if
c_cond
(paren
id|caller-&gt;fl_type
op_eq
id|fl-&gt;fl_type
)paren
(brace
r_if
c_cond
(paren
id|fl-&gt;fl_end
OL
id|caller-&gt;fl_start
op_minus
l_int|1
)paren
r_goto
id|next_lock
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If the next lock in the list has entirely bigger&n;&t;&t;&t; * addresses than the new one, insert the lock here.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|fl-&gt;fl_start
OG
id|caller-&gt;fl_end
op_plus
l_int|1
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * If we come here, the new and old lock are of the&n;&t;&t;&t; * same type and adjacent or overlapping. Make one&n;&t;&t;&t; * lock yielding from the lower start address of both&n;&t;&t;&t; * locks to the higher end address.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|fl-&gt;fl_start
OG
id|caller-&gt;fl_start
)paren
id|fl-&gt;fl_start
op_assign
id|caller-&gt;fl_start
suffix:semicolon
r_else
id|caller-&gt;fl_start
op_assign
id|fl-&gt;fl_start
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_end
OL
id|caller-&gt;fl_end
)paren
id|fl-&gt;fl_end
op_assign
id|caller-&gt;fl_end
suffix:semicolon
r_else
id|caller-&gt;fl_end
op_assign
id|fl-&gt;fl_end
suffix:semicolon
r_if
c_cond
(paren
id|added
)paren
(brace
id|free_lock
c_func
(paren
id|before
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|caller
op_assign
id|fl
suffix:semicolon
id|added
op_assign
l_int|1
suffix:semicolon
r_goto
id|next_lock
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Processing for different lock types is a bit more complex.&n;&t;&t; */
r_if
c_cond
(paren
id|fl-&gt;fl_end
OL
id|caller-&gt;fl_start
)paren
r_goto
id|next_lock
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_start
OG
id|caller-&gt;fl_end
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|caller-&gt;fl_type
op_eq
id|F_UNLCK
)paren
id|added
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_start
OL
id|caller-&gt;fl_start
)paren
id|left
op_assign
id|fl
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the next lock in the list has a higher end address than&n;&t;&t; * the new one, insert the new one here.&n;&t;&t; */
r_if
c_cond
(paren
id|fl-&gt;fl_end
OG
id|caller-&gt;fl_end
)paren
(brace
id|right
op_assign
id|fl
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|fl-&gt;fl_start
op_ge
id|caller-&gt;fl_start
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The new lock completely replaces an old one (This may&n;&t;&t;&t; * happen several times).&n;&t;&t;&t; */
r_if
c_cond
(paren
id|added
)paren
(brace
id|free_lock
c_func
(paren
id|before
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Replace the old lock with the new one. Wake up&n;&t;&t;&t; * anybody waiting for the old one, as the change in&n;&t;&t;&t; * lock type migth satisfy his needs.&n;&t;&t;&t; */
id|wake_up
c_func
(paren
op_amp
id|fl-&gt;fl_wait
)paren
suffix:semicolon
id|fl-&gt;fl_start
op_assign
id|caller-&gt;fl_start
suffix:semicolon
id|fl-&gt;fl_end
op_assign
id|caller-&gt;fl_end
suffix:semicolon
id|fl-&gt;fl_type
op_assign
id|caller-&gt;fl_type
suffix:semicolon
id|fl-&gt;fl_wait
op_assign
l_int|0
suffix:semicolon
id|caller
op_assign
id|fl
suffix:semicolon
id|added
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Go on to next lock.&n;&t;&t; */
id|next_lock
suffix:colon
id|before
op_assign
op_amp
(paren
op_star
id|before
)paren
op_member_access_from_pointer
id|fl_next
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|added
)paren
(brace
r_if
c_cond
(paren
id|caller-&gt;fl_type
op_eq
id|F_UNLCK
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|caller
op_assign
id|alloc_lock
c_func
(paren
id|before
comma
id|caller
)paren
)paren
)paren
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|right
)paren
(brace
r_if
c_cond
(paren
id|left
op_eq
id|right
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * The new lock breaks the old one in two pieces, so we&n;&t;&t;&t; * have to allocate one more lock (in this case, even&n;&t;&t;&t; * F_UNLCK may fail!).&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|left
op_assign
id|alloc_lock
c_func
(paren
id|before
comma
id|right
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|added
)paren
id|free_lock
c_func
(paren
id|before
)paren
suffix:semicolon
r_return
op_minus
id|ENOLCK
suffix:semicolon
)brace
)brace
id|right-&gt;fl_start
op_assign
id|caller-&gt;fl_end
op_plus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|left
)paren
id|left-&gt;fl_end
op_assign
id|caller-&gt;fl_start
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * File_lock() inserts a lock at the position pos of the linked list.&n; */
DECL|function|alloc_lock
r_static
r_struct
id|file_lock
op_star
id|alloc_lock
c_func
(paren
r_struct
id|file_lock
op_star
op_star
id|pos
comma
r_struct
id|file_lock
op_star
id|fl
)paren
(brace
r_struct
id|file_lock
op_star
id|tmp
suffix:semicolon
id|tmp
op_assign
id|file_lock_free_list
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* no available entry */
r_if
c_cond
(paren
id|tmp-&gt;fl_owner
op_ne
l_int|NULL
)paren
id|panic
c_func
(paren
l_string|&quot;alloc_lock: broken free list&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* remove from free list */
id|file_lock_free_list
op_assign
id|tmp-&gt;fl_next
suffix:semicolon
op_star
id|tmp
op_assign
op_star
id|fl
suffix:semicolon
id|tmp-&gt;fl_next
op_assign
op_star
id|pos
suffix:semicolon
multiline_comment|/* insert into file&squot;s list */
op_star
id|pos
op_assign
id|tmp
suffix:semicolon
id|tmp-&gt;fl_owner
op_assign
id|current
suffix:semicolon
multiline_comment|/* FIXME: needed? */
id|tmp-&gt;fl_wait
op_assign
l_int|NULL
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
multiline_comment|/*&n; * Add a lock to the free list ...&n; */
DECL|function|free_lock
r_static
r_void
id|free_lock
c_func
(paren
r_struct
id|file_lock
op_star
op_star
id|fl_p
)paren
(brace
r_struct
id|file_lock
op_star
id|fl
suffix:semicolon
id|fl
op_assign
op_star
id|fl_p
suffix:semicolon
r_if
c_cond
(paren
id|fl-&gt;fl_owner
op_eq
l_int|NULL
)paren
multiline_comment|/* sanity check */
id|panic
c_func
(paren
l_string|&quot;free_lock: broken lock list&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|fl_p
op_assign
(paren
op_star
id|fl_p
)paren
op_member_access_from_pointer
id|fl_next
suffix:semicolon
id|fl-&gt;fl_next
op_assign
id|file_lock_free_list
suffix:semicolon
multiline_comment|/* add to free list */
id|file_lock_free_list
op_assign
id|fl
suffix:semicolon
id|fl-&gt;fl_owner
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* for sanity checks */
id|wake_up
c_func
(paren
op_amp
id|fl-&gt;fl_wait
)paren
suffix:semicolon
)brace
eof
