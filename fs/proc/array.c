multiline_comment|/*&n; *  linux/fs/proc/array.c&n; *&n; *  Copyright (C) 1992  by Linus Torvalds&n; *  based on ideas by Darren Senn&n; *&n; *  stat,statm extensions by Michael K. Johnson, johnsonm@stolaf.edu&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|LOAD_INT
mdefine_line|#define LOAD_INT(x) ((x) &gt;&gt; FSHIFT)
DECL|macro|LOAD_FRAC
mdefine_line|#define LOAD_FRAC(x) LOAD_INT(((x) &amp; (FIXED_1-1)) * 100)
macro_line|#ifdef CONFIG_DEBUG_MALLOC
r_int
id|get_malloc
c_func
(paren
r_char
op_star
id|buffer
)paren
suffix:semicolon
macro_line|#endif
DECL|function|read_core
r_static
r_int
id|read_core
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_int
id|read
suffix:semicolon
r_int
id|count1
suffix:semicolon
r_char
op_star
id|pnt
suffix:semicolon
r_struct
id|user
id|dump
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|dump
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|user
)paren
)paren
suffix:semicolon
id|dump.magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump.u_dsize
op_assign
id|high_memory
op_rshift
l_int|12
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|high_memory
op_plus
id|PAGE_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|high_memory
op_plus
id|PAGE_SIZE
op_minus
id|p
)paren
id|count
op_assign
id|high_memory
op_plus
id|PAGE_SIZE
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p
template_param
l_int|0
)paren
(brace
id|count1
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|p
op_plus
id|count1
OG
r_sizeof
(paren
r_struct
id|user
)paren
)paren
id|count1
op_assign
r_sizeof
(paren
r_struct
id|user
)paren
op_minus
id|p
suffix:semicolon
id|pnt
op_assign
(paren
r_char
op_star
)paren
op_amp
id|dump
op_plus
id|p
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|pnt
comma
id|count1
)paren
suffix:semicolon
id|buf
op_add_assign
id|count1
suffix:semicolon
id|p
op_add_assign
id|count1
suffix:semicolon
id|count
op_sub_assign
id|count1
suffix:semicolon
id|read
op_add_assign
id|count1
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|read
op_increment
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
(paren
id|p
op_minus
id|PAGE_SIZE
)paren
comma
id|count
)paren
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
DECL|function|get_loadavg
r_static
r_int
id|get_loadavg
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|a
comma
id|b
comma
id|c
suffix:semicolon
id|a
op_assign
id|avenrun
(braket
l_int|0
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
id|b
op_assign
id|avenrun
(braket
l_int|1
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
id|c
op_assign
id|avenrun
(braket
l_int|2
)braket
op_plus
(paren
id|FIXED_1
op_div
l_int|200
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d.%02d %d.%02d %d.%02d&bslash;n&quot;
comma
id|LOAD_INT
c_func
(paren
id|a
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|a
)paren
comma
id|LOAD_INT
c_func
(paren
id|b
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|b
)paren
comma
id|LOAD_INT
c_func
(paren
id|c
)paren
comma
id|LOAD_FRAC
c_func
(paren
id|c
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_kstat
r_static
r_int
id|get_kstat
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
id|i
comma
id|len
suffix:semicolon
r_int
id|sum
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
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|sum
op_add_assign
id|kstat.interrupts
(braket
id|i
)braket
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu  %u %u %u %lu&bslash;n&quot;
l_string|&quot;disk %u %u %u %u&bslash;n&quot;
l_string|&quot;page %u %u&bslash;n&quot;
l_string|&quot;swap %u %u&bslash;n&quot;
l_string|&quot;%u&quot;
comma
id|kstat.cpu_user
comma
id|kstat.cpu_nice
comma
id|kstat.cpu_system
comma
id|jiffies
op_minus
(paren
id|kstat.cpu_user
op_plus
id|kstat.cpu_nice
op_plus
id|kstat.cpu_system
)paren
comma
id|kstat.dk_drive
(braket
l_int|0
)braket
comma
id|kstat.dk_drive
(braket
l_int|1
)braket
comma
id|kstat.dk_drive
(braket
l_int|2
)braket
comma
id|kstat.dk_drive
(braket
l_int|3
)braket
comma
id|kstat.pgpgin
comma
id|kstat.pgpgout
comma
id|kstat.pswpin
comma
id|kstat.pswpout
comma
id|sum
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %u&quot;
comma
id|kstat.interrupts
(braket
id|i
)braket
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nctxt %u&bslash;n&quot;
l_string|&quot;btime %lu&bslash;n&quot;
comma
id|kstat.context_swtch
comma
id|xtime.tv_sec
op_minus
id|jiffies
op_div
id|HZ
)paren
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|get_uptime
r_static
r_int
id|get_uptime
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|uptime
suffix:semicolon
r_int
r_int
id|idle
suffix:semicolon
id|uptime
op_assign
id|jiffies
suffix:semicolon
id|idle
op_assign
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|utime
op_plus
id|task
(braket
l_int|0
)braket
op_member_access_from_pointer
id|stime
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%lu.%02lu %lu.%02lu&bslash;n&quot;
comma
id|uptime
op_div
id|HZ
comma
id|uptime
op_mod
id|HZ
comma
id|idle
op_div
id|HZ
comma
id|idle
op_mod
id|HZ
)paren
suffix:semicolon
)brace
DECL|function|get_meminfo
r_static
r_int
id|get_meminfo
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|sysinfo
id|i
suffix:semicolon
id|si_meminfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
id|si_swapinfo
c_func
(paren
op_amp
id|i
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;        total:   used:    free:   shared:  buffers:&bslash;n&quot;
l_string|&quot;Mem:  %8lu %8lu %8lu %8lu %8lu&bslash;n&quot;
l_string|&quot;Swap: %8lu %8lu %8lu&bslash;n&quot;
comma
id|i.totalram
comma
id|i.totalram
op_minus
id|i.freeram
comma
id|i.freeram
comma
id|i.sharedram
comma
id|i.bufferram
comma
id|i.totalswap
comma
id|i.totalswap
op_minus
id|i.freeswap
comma
id|i.freeswap
)paren
suffix:semicolon
)brace
DECL|function|get_version
r_static
r_int
id|get_version
c_func
(paren
r_char
op_star
id|buffer
)paren
(brace
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
id|strcpy
c_func
(paren
id|buffer
comma
id|linux_banner
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|get_task
r_static
r_struct
id|task_struct
op_star
op_star
id|get_task
c_func
(paren
id|pid_t
id|pid
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
suffix:semicolon
id|p
op_assign
id|task
suffix:semicolon
r_while
c_loop
(paren
op_increment
id|p
OL
id|task
op_plus
id|NR_TASKS
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_logical_and
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
r_return
id|p
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|get_phys_addr
r_static
r_int
r_int
id|get_phys_addr
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
comma
r_int
r_int
id|ptr
)paren
(brace
r_int
r_int
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
op_logical_or
id|ptr
op_ge
id|TASK_SIZE
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_assign
op_star
id|PAGE_DIR_OFFSET
c_func
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|tss.cr3
comma
id|ptr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|page
op_add_assign
id|PAGE_PTR
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
l_int|1
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|page
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|page
op_add_assign
id|ptr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
r_return
id|page
suffix:semicolon
)brace
DECL|function|get_array
r_static
r_int
id|get_array
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_char
op_star
id|buffer
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
id|size
op_assign
l_int|0
comma
id|result
op_assign
l_int|0
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
id|result
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|addr
op_assign
id|get_phys_addr
c_func
(paren
id|p
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
id|result
suffix:semicolon
r_do
(brace
id|c
op_assign
op_star
(paren
r_char
op_star
)paren
id|addr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
id|result
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|size
OL
id|PAGE_SIZE
)paren
id|buffer
(braket
id|size
op_increment
)braket
op_assign
id|c
suffix:semicolon
r_else
r_return
id|result
suffix:semicolon
id|addr
op_increment
suffix:semicolon
id|start
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|start
op_ge
id|end
)paren
r_return
id|result
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|get_env
r_static
r_int
id|get_env
c_func
(paren
r_int
id|pid
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|get_task
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|get_array
c_func
(paren
id|p
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|env_start
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|env_end
comma
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|get_arg
r_static
r_int
id|get_arg
c_func
(paren
r_int
id|pid
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|get_task
c_func
(paren
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|get_array
c_func
(paren
id|p
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|arg_start
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|arg_end
comma
id|buffer
)paren
suffix:semicolon
)brace
DECL|function|get_wchan
r_static
r_int
r_int
id|get_wchan
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
id|ebp
comma
id|eip
suffix:semicolon
r_int
r_int
id|stack_page
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|stack_page
op_assign
id|p-&gt;kernel_stack_page
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|ebp
op_assign
id|p-&gt;tss.ebp
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|ebp
OL
id|stack_page
op_logical_or
id|ebp
op_ge
l_int|4092
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|eip
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|ebp
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_void
op_star
)paren
id|eip
op_ne
id|sleep_on
op_logical_and
(paren
r_void
op_star
)paren
id|eip
op_ne
id|interruptible_sleep_on
)paren
r_return
id|eip
suffix:semicolon
id|ebp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|ebp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|KSTK_EIP
mdefine_line|#define&t;KSTK_EIP(stack)&t;(((unsigned long *)stack)[1019])
DECL|macro|KSTK_ESP
mdefine_line|#define&t;KSTK_ESP(stack)&t;(((unsigned long *)stack)[1022])
DECL|function|get_stat
r_static
r_int
id|get_stat
c_func
(paren
r_int
id|pid
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|get_task
c_func
(paren
id|pid
)paren
suffix:semicolon
r_int
r_int
id|sigignore
op_assign
l_int|0
comma
id|sigcatch
op_assign
l_int|0
comma
id|bit
op_assign
l_int|1
comma
id|wchan
suffix:semicolon
r_int
r_int
id|vsize
comma
id|eip
comma
id|esp
suffix:semicolon
r_int
id|i
comma
id|tty_pgrp
suffix:semicolon
r_char
id|state
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
template_param
l_int|5
)paren
id|state
op_assign
l_char|&squot;.&squot;
suffix:semicolon
r_else
id|state
op_assign
l_string|&quot;RSDZTD&quot;
(braket
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
)braket
suffix:semicolon
id|eip
op_assign
id|esp
op_assign
l_int|0
suffix:semicolon
id|vsize
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|kernel_stack_page
suffix:semicolon
r_if
c_cond
(paren
id|vsize
)paren
(brace
id|eip
op_assign
id|KSTK_EIP
c_func
(paren
id|vsize
)paren
suffix:semicolon
id|esp
op_assign
id|KSTK_ESP
c_func
(paren
id|vsize
)paren
suffix:semicolon
id|vsize
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|brk
op_minus
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|start_code
op_plus
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|esp
)paren
id|vsize
op_add_assign
id|TASK_SIZE
op_minus
id|esp
suffix:semicolon
)brace
id|wchan
op_assign
id|get_wchan
c_func
(paren
op_star
id|p
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
l_int|32
suffix:semicolon
op_increment
id|i
)paren
(brace
r_switch
c_cond
(paren
(paren
r_int
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|sigaction
(braket
id|i
)braket
dot
id|sa_handler
)paren
(brace
r_case
l_int|1
suffix:colon
id|sigignore
op_or_assign
id|bit
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|sigcatch
op_or_assign
id|bit
suffix:semicolon
)brace
id|bit
op_lshift_assign
l_int|1
suffix:semicolon
)brace
id|tty_pgrp
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|tty
suffix:semicolon
r_if
c_cond
(paren
id|tty_pgrp
OG
l_int|0
op_logical_and
id|tty_table
(braket
id|tty_pgrp
)braket
)paren
id|tty_pgrp
op_assign
id|tty_table
(braket
id|tty_pgrp
)braket
op_member_access_from_pointer
id|pgrp
suffix:semicolon
r_else
id|tty_pgrp
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d (%s) %c %d %d %d %d %d %lu %lu &bslash;&n;%lu %lu %lu %ld %ld %ld %ld %ld %ld %lu %lu %ld %lu %u %u %lu %lu %lu %lu %lu %lu &bslash;&n;%lu %lu %lu %lu&bslash;n&quot;
comma
id|pid
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|comm
comma
id|state
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|p_pptr-&gt;pid
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|pgrp
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|session
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|tty
comma
id|tty_pgrp
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|flags
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|min_flt
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|cmin_flt
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|maj_flt
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|cmaj_flt
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|utime
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|stime
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|cutime
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|cstime
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|counter
comma
multiline_comment|/* this is the kernel priority ---&n;&t;&t;&t;&t;   subtract 30 in your user-level program. */
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|priority
comma
multiline_comment|/* this is the nice value ---&n;&t;&t;&t;&t;   subtract 15 in your user-level program. */
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|timeout
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|it_real_value
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|start_time
comma
id|vsize
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rss
comma
multiline_comment|/* you might want to shift this left 3 */
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|rlim
(braket
id|RLIMIT_RSS
)braket
dot
id|rlim_cur
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|start_code
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|end_code
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|start_stack
comma
id|esp
comma
id|eip
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|signal
comma
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|blocked
comma
id|sigignore
comma
id|sigcatch
comma
id|wchan
)paren
suffix:semicolon
)brace
DECL|function|get_statm
r_static
r_int
id|get_statm
c_func
(paren
r_int
id|pid
comma
r_char
op_star
id|buffer
)paren
(brace
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|get_task
c_func
(paren
id|pid
)paren
suffix:semicolon
r_int
id|i
comma
id|tpag
suffix:semicolon
r_int
id|size
op_assign
l_int|0
comma
id|resident
op_assign
l_int|0
comma
id|share
op_assign
l_int|0
comma
id|trs
op_assign
l_int|0
comma
id|lrs
op_assign
l_int|0
comma
id|drs
op_assign
l_int|0
comma
id|dt
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|ptbl
comma
op_star
id|buf
comma
op_star
id|pte
comma
op_star
id|pagedir
comma
id|map_nr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|0
suffix:semicolon
id|tpag
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|end_code
op_div
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|state
op_ne
id|TASK_ZOMBIE
)paren
(brace
id|pagedir
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|tss.cr3
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
l_int|0x300
suffix:semicolon
op_increment
id|i
)paren
(brace
r_if
c_cond
(paren
(paren
id|ptbl
op_assign
id|pagedir
(braket
id|i
)braket
)paren
op_eq
l_int|0
)paren
(brace
id|tpag
op_sub_assign
id|PTRS_PER_PAGE
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|buf
op_assign
(paren
r_int
r_int
op_star
)paren
(paren
id|ptbl
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pte
op_assign
id|buf
suffix:semicolon
id|pte
OL
(paren
id|buf
op_plus
id|PTRS_PER_PAGE
)paren
suffix:semicolon
op_increment
id|pte
)paren
(brace
r_if
c_cond
(paren
op_star
id|pte
op_ne
l_int|0
)paren
(brace
op_increment
id|size
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pte
op_amp
l_int|1
)paren
(brace
op_increment
id|resident
suffix:semicolon
r_if
c_cond
(paren
id|tpag
OG
l_int|0
)paren
op_increment
id|trs
suffix:semicolon
r_else
op_increment
id|drs
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
l_int|15
op_logical_and
id|i
OL
l_int|0x2f0
)paren
(brace
op_increment
id|lrs
suffix:semicolon
r_if
c_cond
(paren
op_star
id|pte
op_amp
l_int|0x40
)paren
op_increment
id|dt
suffix:semicolon
r_else
op_decrement
id|drs
suffix:semicolon
)brace
id|map_nr
op_assign
id|MAP_NR
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
r_if
c_cond
(paren
id|map_nr
template_param
l_int|1
)paren
op_increment
id|share
suffix:semicolon
)brace
)brace
op_decrement
id|tpag
suffix:semicolon
)brace
)brace
)brace
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;%d %d %d %d %d %d %d&bslash;n&quot;
comma
id|size
comma
id|resident
comma
id|share
comma
id|trs
comma
id|lrs
comma
id|drs
comma
id|dt
)paren
suffix:semicolon
)brace
DECL|function|get_maps
r_static
r_int
id|get_maps
c_func
(paren
r_int
id|pid
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|sz
op_assign
l_int|0
suffix:semicolon
r_struct
id|task_struct
op_star
op_star
id|p
op_assign
id|get_task
c_func
(paren
id|pid
)paren
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|map
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
op_logical_neg
op_star
id|p
)paren
r_return
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|map
op_assign
(paren
op_star
id|p
)paren
op_member_access_from_pointer
id|mmap
suffix:semicolon
id|map
op_ne
l_int|NULL
suffix:semicolon
id|map
op_assign
id|map-&gt;vm_next
)paren
(brace
r_char
id|str
(braket
l_int|7
)braket
comma
op_star
id|cp
op_assign
id|str
suffix:semicolon
r_int
id|prot
op_assign
id|map-&gt;vm_page_prot
suffix:semicolon
r_int
id|perms
comma
id|flags
suffix:semicolon
r_int
id|end
op_assign
id|sz
op_plus
l_int|80
suffix:semicolon
multiline_comment|/* Length of line */
id|dev_t
id|dev
suffix:semicolon
r_int
r_int
id|ino
suffix:semicolon
multiline_comment|/*&n;&t;&t; * This tries to get an &quot;rwxsp&quot; string out of silly&n;&t;&t; * intel page permissions.  The vm_area_struct should&n;&t;&t; * probably have the original mmap args preserved.&n;&t;&t; */
id|flags
op_assign
id|perms
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|prot
op_amp
id|PAGE_READONLY
)paren
op_eq
id|PAGE_READONLY
)paren
id|perms
op_or_assign
id|PROT_READ
op_or
id|PROT_EXEC
suffix:semicolon
r_if
c_cond
(paren
id|prot
op_amp
(paren
id|PAGE_COW
op_or
id|PAGE_RW
)paren
)paren
(brace
id|perms
op_or_assign
id|PROT_WRITE
op_or
id|PROT_READ
suffix:semicolon
id|flags
op_assign
id|prot
op_amp
id|PAGE_COW
ques
c_cond
id|MAP_PRIVATE
suffix:colon
id|MAP_SHARED
suffix:semicolon
)brace
op_star
id|cp
op_increment
op_assign
id|perms
op_amp
id|PROT_READ
ques
c_cond
l_char|&squot;r&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|perms
op_amp
id|PROT_WRITE
ques
c_cond
l_char|&squot;w&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|perms
op_amp
id|PROT_EXEC
ques
c_cond
l_char|&squot;x&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|flags
op_amp
id|MAP_SHARED
ques
c_cond
l_char|&squot;s&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
id|flags
op_amp
id|MAP_PRIVATE
ques
c_cond
l_char|&squot;p&squot;
suffix:colon
l_char|&squot;-&squot;
suffix:semicolon
op_star
id|cp
op_increment
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|end
op_ge
id|PAGE_SIZE
)paren
(brace
id|sprintf
c_func
(paren
id|buf
op_plus
id|sz
comma
l_string|&quot;...&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|map-&gt;vm_inode
op_ne
l_int|NULL
)paren
(brace
id|dev
op_assign
id|map-&gt;vm_inode-&gt;i_dev
suffix:semicolon
id|ino
op_assign
id|map-&gt;vm_inode-&gt;i_ino
suffix:semicolon
)brace
r_else
(brace
id|dev
op_assign
l_int|0
suffix:semicolon
id|ino
op_assign
l_int|0
suffix:semicolon
)brace
id|sz
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|sz
comma
l_string|&quot;%08lx-%08lx %s %08lx %02x:%02x %lu&bslash;n&quot;
comma
id|map-&gt;vm_start
comma
id|map-&gt;vm_end
comma
id|str
comma
id|map-&gt;vm_offset
comma
id|MAJOR
c_func
(paren
id|dev
)paren
comma
id|MINOR
c_func
(paren
id|dev
)paren
comma
id|ino
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sz
OG
id|end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;get_maps: end(%d) &lt; sz(%d)&bslash;n&quot;
comma
id|end
comma
id|sz
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_return
id|sz
suffix:semicolon
)brace
r_extern
r_int
id|get_module_list
c_func
(paren
r_char
op_star
)paren
suffix:semicolon
DECL|function|array_read
r_static
r_int
id|array_read
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_char
op_star
id|page
suffix:semicolon
r_int
id|length
suffix:semicolon
r_int
id|end
suffix:semicolon
r_int
r_int
id|type
comma
id|pid
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
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
id|page
op_assign
(paren
r_char
op_star
)paren
id|__get_free_page
c_func
(paren
id|GFP_KERNEL
)paren
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|type
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|pid
op_assign
id|type
op_rshift
l_int|16
suffix:semicolon
id|type
op_and_assign
l_int|0x0000ffff
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
l_int|2
suffix:colon
id|length
op_assign
id|get_loadavg
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|length
op_assign
id|get_uptime
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|length
op_assign
id|get_meminfo
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|length
op_assign
id|get_version
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|9
suffix:colon
id|length
op_assign
id|get_env
c_func
(paren
id|pid
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|10
suffix:colon
id|length
op_assign
id|get_arg
c_func
(paren
id|pid
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|11
suffix:colon
id|length
op_assign
id|get_stat
c_func
(paren
id|pid
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|12
suffix:colon
id|length
op_assign
id|get_statm
c_func
(paren
id|pid
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_MALLOC
r_case
l_int|13
suffix:colon
id|length
op_assign
id|get_malloc
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
l_int|14
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
id|read_core
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_case
l_int|15
suffix:colon
id|length
op_assign
id|get_maps
c_func
(paren
id|pid
comma
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
suffix:colon
id|length
op_assign
id|get_module_list
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|17
suffix:colon
id|length
op_assign
id|get_kstat
c_func
(paren
id|page
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
op_minus
id|EBADF
suffix:semicolon
)brace
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
id|length
)paren
(brace
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_plus
id|file-&gt;f_pos
OG
id|length
)paren
id|count
op_assign
id|length
op_minus
id|file-&gt;f_pos
suffix:semicolon
id|end
op_assign
id|count
op_plus
id|file-&gt;f_pos
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|page
op_plus
id|file-&gt;f_pos
comma
id|count
)paren
suffix:semicolon
id|free_page
c_func
(paren
(paren
r_int
r_int
)paren
id|page
)paren
suffix:semicolon
id|file-&gt;f_pos
op_assign
id|end
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|variable|proc_array_operations
r_static
r_struct
id|file_operations
id|proc_array_operations
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* array_lseek */
id|array_read
comma
l_int|NULL
comma
multiline_comment|/* array_write */
l_int|NULL
comma
multiline_comment|/* array_readdir */
l_int|NULL
comma
multiline_comment|/* array_select */
l_int|NULL
comma
multiline_comment|/* array_ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|proc_array_inode_operations
r_struct
id|inode_operations
id|proc_array_inode_operations
op_assign
(brace
op_amp
id|proc_array_operations
comma
multiline_comment|/* default base directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
