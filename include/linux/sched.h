macro_line|#ifndef _SCHED_H
DECL|macro|_SCHED_H
mdefine_line|#define _SCHED_H
DECL|macro|HZ
mdefine_line|#define HZ 100
DECL|macro|NR_TASKS
mdefine_line|#define NR_TASKS&t;64
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;0x04000000
DECL|macro|LIBRARY_SIZE
mdefine_line|#define LIBRARY_SIZE&t;0x00400000
macro_line|#if (TASK_SIZE &amp; 0x3fffff)
macro_line|#error &quot;TASK_SIZE must be multiple of 4M&quot;
macro_line|#endif
macro_line|#if (LIBRARY_SIZE &amp; 0x3fffff)
macro_line|#error &quot;LIBRARY_SIZE must be a multiple of 4M&quot;
macro_line|#endif
macro_line|#if (LIBRARY_SIZE &gt;= (TASK_SIZE/2))
macro_line|#error &quot;LIBRARY_SIZE too damn big!&quot;
macro_line|#endif
macro_line|#if (((TASK_SIZE&gt;&gt;16)*NR_TASKS) != 0x10000)
macro_line|#error &quot;TASK_SIZE*NR_TASKS must be 4GB&quot;
macro_line|#endif
DECL|macro|LIBRARY_OFFSET
mdefine_line|#define LIBRARY_OFFSET (TASK_SIZE - LIBRARY_SIZE)
DECL|macro|CT_TO_SECS
mdefine_line|#define CT_TO_SECS(x)&t;((x) / HZ)
DECL|macro|CT_TO_USECS
mdefine_line|#define CT_TO_USECS(x)&t;(((x) % HZ) * 1000000/HZ)
DECL|macro|FIRST_TASK
mdefine_line|#define FIRST_TASK task[0]
DECL|macro|LAST_TASK
mdefine_line|#define LAST_TASK task[NR_TASKS-1]
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;sys/param.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/resource.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#if (NR_OPEN &gt; 32)
macro_line|#error &quot;Currently the close-on-exec-flags and select masks are in one long, max 32 files/proc&quot;
macro_line|#endif
DECL|macro|TASK_RUNNING
mdefine_line|#define TASK_RUNNING&t;&t;0
DECL|macro|TASK_INTERRUPTIBLE
mdefine_line|#define TASK_INTERRUPTIBLE&t;1
DECL|macro|TASK_UNINTERRUPTIBLE
mdefine_line|#define TASK_UNINTERRUPTIBLE&t;2
DECL|macro|TASK_ZOMBIE
mdefine_line|#define TASK_ZOMBIE&t;&t;3
DECL|macro|TASK_STOPPED
mdefine_line|#define TASK_STOPPED&t;&t;4
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL ((void *) 0)
macro_line|#endif
r_extern
r_int
id|copy_page_tables
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|to
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|free_page_tables
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_void
id|sched_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|schedule
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|trap_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|panic
c_func
(paren
r_const
r_char
op_star
id|str
)paren
suffix:semicolon
r_extern
r_int
id|tty_write
c_func
(paren
r_int
id|minor
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
suffix:semicolon
DECL|typedef|fn_ptr
r_typedef
r_int
(paren
op_star
id|fn_ptr
)paren
(paren
)paren
suffix:semicolon
DECL|struct|i387_struct
r_struct
id|i387_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
)brace
suffix:semicolon
DECL|struct|tss_struct
r_struct
id|tss_struct
(brace
DECL|member|back_link
r_int
id|back_link
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|esp0
r_int
id|esp0
suffix:semicolon
DECL|member|ss0
r_int
id|ss0
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|esp1
r_int
id|esp1
suffix:semicolon
DECL|member|ss1
r_int
id|ss1
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|esp2
r_int
id|esp2
suffix:semicolon
DECL|member|ss2
r_int
id|ss2
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|cr3
r_int
id|cr3
suffix:semicolon
DECL|member|eip
r_int
id|eip
suffix:semicolon
DECL|member|eflags
r_int
id|eflags
suffix:semicolon
DECL|member|eax
DECL|member|ecx
DECL|member|edx
DECL|member|ebx
r_int
id|eax
comma
id|ecx
comma
id|edx
comma
id|ebx
suffix:semicolon
DECL|member|esp
r_int
id|esp
suffix:semicolon
DECL|member|ebp
r_int
id|ebp
suffix:semicolon
DECL|member|esi
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
id|edi
suffix:semicolon
DECL|member|es
r_int
id|es
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|cs
r_int
id|cs
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|ss
r_int
id|ss
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|ds
r_int
id|ds
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|fs
r_int
id|fs
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|gs
r_int
id|gs
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|ldt
r_int
id|ldt
suffix:semicolon
multiline_comment|/* 16 high bits zero */
DECL|member|trace_bitmap
r_int
id|trace_bitmap
suffix:semicolon
multiline_comment|/* bits: trace 0, bitmap 16-31 */
DECL|member|i387
r_struct
id|i387_struct
id|i387
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|task_struct
r_struct
id|task_struct
(brace
multiline_comment|/* these are hardcoded - don&squot;t touch */
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* -1 unrunnable, 0 runnable, &gt;0 stopped */
DECL|member|counter
r_int
id|counter
suffix:semicolon
DECL|member|priority
r_int
id|priority
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|sigaction
r_struct
id|sigaction
id|sigaction
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|blocked
r_int
id|blocked
suffix:semicolon
multiline_comment|/* bitmap of masked signals */
multiline_comment|/* various fields */
DECL|member|exit_code
r_int
id|exit_code
suffix:semicolon
DECL|member|start_code
DECL|member|end_code
DECL|member|end_data
DECL|member|brk
DECL|member|start_stack
r_int
r_int
id|start_code
comma
id|end_code
comma
id|end_data
comma
id|brk
comma
id|start_stack
suffix:semicolon
DECL|member|pid
DECL|member|pgrp
DECL|member|session
DECL|member|leader
r_int
id|pid
comma
id|pgrp
comma
id|session
comma
id|leader
suffix:semicolon
DECL|member|groups
r_int
id|groups
(braket
id|NGROUPS
)braket
suffix:semicolon
multiline_comment|/* &n;&t; * pointers to parent process, youngest child, younger sibling,&n;&t; * older sibling, respectively.  (p-&gt;father can be replaced with &n;&t; * p-&gt;p_pptr-&gt;pid)&n;&t; */
DECL|member|p_pptr
DECL|member|p_cptr
DECL|member|p_ysptr
DECL|member|p_osptr
r_struct
id|task_struct
op_star
id|p_pptr
comma
op_star
id|p_cptr
comma
op_star
id|p_ysptr
comma
op_star
id|p_osptr
suffix:semicolon
multiline_comment|/*&n;&t; * sleep makes a singly linked list with this.&n;&t; */
DECL|member|next_wait
r_struct
id|task_struct
op_star
id|next_wait
suffix:semicolon
DECL|member|uid
DECL|member|euid
DECL|member|suid
r_int
r_int
id|uid
comma
id|euid
comma
id|suid
suffix:semicolon
DECL|member|gid
DECL|member|egid
DECL|member|sgid
r_int
r_int
id|gid
comma
id|egid
comma
id|sgid
suffix:semicolon
DECL|member|timeout
DECL|member|alarm
r_int
r_int
id|timeout
comma
id|alarm
suffix:semicolon
DECL|member|utime
DECL|member|stime
DECL|member|cutime
DECL|member|cstime
DECL|member|start_time
r_int
id|utime
comma
id|stime
comma
id|cutime
comma
id|cstime
comma
id|start_time
suffix:semicolon
DECL|member|min_flt
DECL|member|maj_flt
r_int
r_int
id|min_flt
comma
id|maj_flt
suffix:semicolon
DECL|member|cmin_flt
DECL|member|cmaj_flt
r_int
r_int
id|cmin_flt
comma
id|cmaj_flt
suffix:semicolon
DECL|member|rlim
r_struct
id|rlimit
id|rlim
(braket
id|RLIM_NLIMITS
)braket
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* per process flags, defined below */
DECL|member|used_math
r_int
r_int
id|used_math
suffix:semicolon
DECL|member|rss
r_int
r_int
id|rss
suffix:semicolon
multiline_comment|/* number of resident pages */
DECL|member|comm
r_char
id|comm
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* file system info */
DECL|member|link_count
r_int
id|link_count
suffix:semicolon
DECL|member|tty
r_int
id|tty
suffix:semicolon
multiline_comment|/* -1 if no tty, so it must be signed */
DECL|member|umask
r_int
r_int
id|umask
suffix:semicolon
DECL|member|pwd
r_struct
id|inode
op_star
id|pwd
suffix:semicolon
DECL|member|root
r_struct
id|inode
op_star
id|root
suffix:semicolon
DECL|member|executable
r_struct
id|inode
op_star
id|executable
suffix:semicolon
DECL|member|library
r_struct
id|inode
op_star
id|library
suffix:semicolon
DECL|member|close_on_exec
r_int
r_int
id|close_on_exec
suffix:semicolon
DECL|member|filp
r_struct
id|file
op_star
id|filp
(braket
id|NR_OPEN
)braket
suffix:semicolon
multiline_comment|/* ldt for this task 0 - zero 1 - cs 2 - ds&amp;ss */
DECL|member|ldt
r_struct
id|desc_struct
id|ldt
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* tss for this task */
DECL|member|tss
r_struct
id|tss_struct
id|tss
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Per process flags&n; */
DECL|macro|PF_ALIGNWARN
mdefine_line|#define PF_ALIGNWARN&t;0x00000001&t;/* Print alignment warning msgs */
multiline_comment|/* Not implemented yet, only for 486*/
DECL|macro|PF_PTRACED
mdefine_line|#define PF_PTRACED&t;0x00000010&t;/* set if ptrace (0) has been called. */
DECL|macro|PF_VM86
mdefine_line|#define PF_VM86&t;&t;0x00000020&t;/* set if process can execute a vm86 */
multiline_comment|/* task. */
multiline_comment|/* not impelmented. */
multiline_comment|/*&n; *  INIT_TASK is used to set up the first task table, touch at&n; * your own risk!. Base=0, limit=0x9ffff (=640kB)&n; */
DECL|macro|INIT_TASK
mdefine_line|#define INIT_TASK &bslash;&n;/* state etc */&t;{ 0,15,15, &bslash;&n;/* signals */&t;0,{{},},0, &bslash;&n;/* ec,brk... */&t;0,0,0,0,0,0, &bslash;&n;/* pid etc.. */&t;0,0,0,0, &bslash;&n;/* suppl grps*/ {NOGROUP,}, &bslash;&n;/* proc links*/ &amp;init_task.task,NULL,NULL,NULL,NULL, &bslash;&n;/* uid etc */&t;0,0,0,0,0,0, &bslash;&n;/* timeout */&t;0,0,0,0,0,0,0, &bslash;&n;/* min_flt */&t;0,0,0,0, &bslash;&n;/* rlimits */   { {0x7fffffff, 0x7fffffff}, {0x7fffffff, 0x7fffffff},  &bslash;&n;&t;&t;  {0x7fffffff, 0x7fffffff}, {0x7fffffff, 0x7fffffff}, &bslash;&n;&t;&t;  {0x7fffffff, 0x7fffffff}, {0x7fffffff, 0x7fffffff}}, &bslash;&n;/* flags */&t;0, &bslash;&n;/* math */&t;0, &bslash;&n;/* rss */&t;2, &bslash;&n;/* comm */&t;&quot;swapper&quot;, &bslash;&n;/* fs info */&t;0,-1,0022,NULL,NULL,NULL,NULL,0, &bslash;&n;/* filp */&t;{NULL,}, &bslash;&n;&t;{ &bslash;&n;&t;&t;{0,0}, &bslash;&n;/* ldt */&t;{0x9f,0xc0fa00}, &bslash;&n;&t;&t;{0x9f,0xc0f200}, &bslash;&n;&t;}, &bslash;&n;/*tss*/&t;{0,PAGE_SIZE+(long)&amp;init_task,0x10,0,0,0,0,(long)&amp;pg_dir,&bslash;&n;&t; 0,0,0,0,0,0,0,0, &bslash;&n;&t; 0,0,0x17,0x17,0x17,0x17,0x17,0x17, &bslash;&n;&t; _LDT(0),0x80000000, &bslash;&n;&t;&t;{} &bslash;&n;&t;}, &bslash;&n;}
r_extern
r_struct
id|task_struct
op_star
id|task
(braket
id|NR_TASKS
)braket
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|last_task_used_math
suffix:semicolon
r_extern
r_struct
id|task_struct
op_star
id|current
suffix:semicolon
r_extern
r_int
r_int
r_volatile
id|jiffies
suffix:semicolon
r_extern
r_int
r_int
id|startup_time
suffix:semicolon
r_extern
r_int
id|jiffies_offset
suffix:semicolon
DECL|macro|CURRENT_TIME
mdefine_line|#define CURRENT_TIME (startup_time+(jiffies+jiffies_offset)/HZ)
r_extern
r_void
id|add_timer
c_func
(paren
r_int
id|jiffies
comma
r_void
(paren
op_star
id|fn
)paren
(paren
r_void
)paren
)paren
suffix:semicolon
r_extern
r_void
id|sleep_on
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|interruptible_sleep_on
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_void
id|wake_up
c_func
(paren
r_struct
id|task_struct
op_star
op_star
id|p
)paren
suffix:semicolon
r_extern
r_int
id|in_group_p
c_func
(paren
id|gid_t
id|grp
)paren
suffix:semicolon
multiline_comment|/*&n; * Entry into gdt where to find first TSS. 0-nul, 1-cs, 2-ds, 3-syscall&n; * 4-TSS0, 5-LDT0, 6-TSS1 etc ...&n; */
DECL|macro|FIRST_TSS_ENTRY
mdefine_line|#define FIRST_TSS_ENTRY 4
DECL|macro|FIRST_LDT_ENTRY
mdefine_line|#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
DECL|macro|_TSS
mdefine_line|#define _TSS(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_TSS_ENTRY&lt;&lt;3))
DECL|macro|_LDT
mdefine_line|#define _LDT(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_LDT_ENTRY&lt;&lt;3))
DECL|macro|ltr
mdefine_line|#define ltr(n) __asm__(&quot;ltr %%ax&quot;::&quot;a&quot; (_TSS(n)))
DECL|macro|lldt
mdefine_line|#define lldt(n) __asm__(&quot;lldt %%ax&quot;::&quot;a&quot; (_LDT(n)))
DECL|macro|str
mdefine_line|#define str(n) &bslash;&n;__asm__(&quot;str %%ax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;subl %2,%%eax&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;shrl $4,%%eax&quot; &bslash;&n;&t;:&quot;=a&quot; (n) &bslash;&n;&t;:&quot;0&quot; (0),&quot;i&quot; (FIRST_TSS_ENTRY&lt;&lt;3))
multiline_comment|/*&n; *&t;switch_to(n) should switch tasks to task nr n, first&n; * checking that n isn&squot;t the current task, in which case it does nothing.&n; * This also clears the TS-flag if the task we switched to has used&n; * tha math co-processor latest.&n; */
DECL|macro|switch_to
mdefine_line|#define switch_to(n) {&bslash;&n;struct {long a,b;} __tmp; &bslash;&n;__asm__(&quot;cmpl %%ecx,_current&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;je 1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movw %%dx,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;xchgl %%ecx,_current&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;ljmp %0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;cmpl %%ecx,_last_task_used_math&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;jne 1f&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;clts&bslash;n&quot; &bslash;&n;&t;&quot;1:&quot; &bslash;&n;&t;::&quot;m&quot; (*&amp;__tmp.a),&quot;m&quot; (*&amp;__tmp.b), &bslash;&n;&t;&quot;d&quot; (_TSS(n)),&quot;c&quot; ((long) task[n]) &bslash;&n;&t;:&quot;cx&quot;); &bslash;&n;}
DECL|macro|PAGE_ALIGN
mdefine_line|#define PAGE_ALIGN(n) (((n)+0xfff)&amp;0xfffff000)
DECL|macro|_set_base
mdefine_line|#define _set_base(addr,base) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dh,%2&quot; &bslash;&n;&t;::&quot;m&quot; (*((addr)+2)), &bslash;&n;&t;  &quot;m&quot; (*((addr)+4)), &bslash;&n;&t;  &quot;m&quot; (*((addr)+7)), &bslash;&n;&t;  &quot;d&quot; (base) &bslash;&n;&t;:&quot;dx&quot;)
DECL|macro|_set_limit
mdefine_line|#define _set_limit(addr,limit) &bslash;&n;__asm__(&quot;movw %%dx,%0&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;rorl $16,%%edx&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %1,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andb $0xf0,%%dh&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;orb %%dh,%%dl&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movb %%dl,%1&quot; &bslash;&n;&t;::&quot;m&quot; (*(addr)), &bslash;&n;&t;  &quot;m&quot; (*((addr)+6)), &bslash;&n;&t;  &quot;d&quot; (limit) &bslash;&n;&t;:&quot;dx&quot;)
DECL|macro|set_base
mdefine_line|#define set_base(ldt,base) _set_base( ((char *)&amp;(ldt)) , base )
DECL|macro|set_limit
mdefine_line|#define set_limit(ldt,limit) _set_limit( ((char *)&amp;(ldt)) , (limit-1)&gt;&gt;12 )
DECL|function|_get_base
r_static
r_int
r_int
r_inline
id|_get_base
c_func
(paren
r_char
op_star
id|addr
)paren
(brace
r_int
r_int
id|__base
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movb %3,%%dh&bslash;n&bslash;t&quot;
l_string|&quot;movb %2,%%dl&bslash;n&bslash;t&quot;
l_string|&quot;shll $16,%%edx&bslash;n&bslash;t&quot;
l_string|&quot;movw %1,%%dx&quot;
suffix:colon
l_string|&quot;=&amp;d&quot;
(paren
id|__base
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|2
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|4
)paren
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
(paren
(paren
id|addr
)paren
op_plus
l_int|7
)paren
)paren
)paren
suffix:semicolon
r_return
id|__base
suffix:semicolon
)brace
DECL|macro|get_base
mdefine_line|#define get_base(ldt) _get_base( ((char *)&amp;(ldt)) )
DECL|function|get_limit
r_static
r_int
r_int
r_inline
id|get_limit
c_func
(paren
r_int
r_int
id|segment
)paren
(brace
r_int
r_int
id|__limit
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;lsll %1,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|__limit
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|segment
)paren
)paren
suffix:semicolon
r_return
id|__limit
op_plus
l_int|1
suffix:semicolon
)brace
macro_line|#endif
eof
