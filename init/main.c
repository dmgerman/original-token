multiline_comment|/*&n; *  linux/init/main.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/mktime.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
r_extern
r_int
r_int
op_star
id|prof_buffer
suffix:semicolon
r_extern
r_int
r_int
id|prof_len
suffix:semicolon
r_extern
r_int
id|end
suffix:semicolon
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|idle
)paren
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|fork
)paren
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|pause
)paren
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|setup
comma
r_void
op_star
comma
id|BIOS
)paren
r_static
r_inline
id|_syscall0
c_func
(paren
r_int
comma
id|sync
)paren
r_static
r_inline
id|_syscall0
c_func
(paren
id|pid_t
comma
id|setsid
)paren
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|write
comma
r_int
comma
id|fd
comma
r_const
r_char
op_star
comma
id|buf
comma
id|off_t
comma
id|count
)paren
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|dup
comma
r_int
comma
id|fd
)paren
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|execve
comma
r_const
r_char
op_star
comma
id|file
comma
r_char
op_star
op_star
comma
id|argv
comma
r_char
op_star
op_star
comma
id|envp
)paren
r_static
r_inline
id|_syscall3
c_func
(paren
r_int
comma
id|open
comma
r_const
r_char
op_star
comma
id|file
comma
r_int
comma
id|flag
comma
r_int
comma
id|mode
)paren
r_static
r_inline
id|_syscall1
c_func
(paren
r_int
comma
id|close
comma
r_int
comma
id|fd
)paren
r_static
r_inline
id|_syscall3
c_func
(paren
id|pid_t
comma
id|waitpid
comma
id|pid_t
comma
id|pid
comma
r_int
op_star
comma
id|wait_stat
comma
r_int
comma
id|options
)paren
DECL|function|wait
r_static
r_inline
id|pid_t
id|wait
c_func
(paren
r_int
op_star
id|wait_stat
)paren
(brace
r_return
id|waitpid
c_func
(paren
op_minus
l_int|1
comma
id|wait_stat
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|printbuf
r_static
r_char
id|printbuf
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
)paren
suffix:semicolon
r_extern
r_void
id|init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_IRQ
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|blk_dev_init
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|chr_dev_init
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|floppy_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|rd_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_int
id|kernel_mktime
c_func
(paren
r_struct
id|mktime
op_star
id|time
)paren
suffix:semicolon
r_extern
r_int
r_int
id|simple_strtoul
c_func
(paren
r_const
r_char
op_star
id|cp
comma
r_char
op_star
op_star
id|endp
comma
r_int
r_int
id|base
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI
r_extern
r_int
r_int
id|scsi_dev_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|EXT_MEM_K
mdefine_line|#define EXT_MEM_K (*(unsigned short *)0x90002)
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (*(struct drive_info *)0x90080)
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (*(struct screen_info *)0x90000)
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *)0x901FC)
DECL|macro|AUX_DEVICE_INFO
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *)0x901FF)
multiline_comment|/*&n; * Boot command-line arguments&n; */
DECL|macro|MAX_INIT_ARGS
mdefine_line|#define MAX_INIT_ARGS 8
DECL|macro|MAX_INIT_ENVS
mdefine_line|#define MAX_INIT_ENVS 8
DECL|macro|CL_MAGIC_ADDR
mdefine_line|#define CL_MAGIC_ADDR (*(unsigned short *) 0x90020)
DECL|macro|CL_MAGIC
mdefine_line|#define CL_MAGIC 0xa33f
DECL|macro|CL_BASE_ADDR
mdefine_line|#define CL_BASE_ADDR ((char *) 0x90000)
DECL|macro|CL_OFFSET
mdefine_line|#define CL_OFFSET (*(unsigned short *) 0x90022)
multiline_comment|/*&n; * Yeah, yeah, it&squot;s ugly, but I cannot find how to do this correctly&n; * and this seems to work. I anybody has more info on the real-time&n; * clock I&squot;d be interested. Most of this was trial and error, and some&n; * bios-listing reading. Urghh.&n; */
DECL|macro|CMOS_READ
mdefine_line|#define CMOS_READ(addr) ({ &bslash;&n;outb_p(0x80|addr,0x70); &bslash;&n;inb_p(0x71); &bslash;&n;})
DECL|macro|BCD_TO_BIN
mdefine_line|#define BCD_TO_BIN(val) ((val)=((val)&amp;15) + ((val)&gt;&gt;4)*10)
DECL|function|time_init
r_static
r_void
id|time_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|mktime
id|time
suffix:semicolon
r_do
(brace
id|time.sec
op_assign
id|CMOS_READ
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|time.min
op_assign
id|CMOS_READ
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|time.hour
op_assign
id|CMOS_READ
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|time.day
op_assign
id|CMOS_READ
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|time.mon
op_assign
id|CMOS_READ
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|time.year
op_assign
id|CMOS_READ
c_func
(paren
l_int|9
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|time.sec
op_ne
id|CMOS_READ
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.sec
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.min
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.hour
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.day
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.mon
)paren
suffix:semicolon
id|BCD_TO_BIN
c_func
(paren
id|time.year
)paren
suffix:semicolon
id|time.mon
op_decrement
suffix:semicolon
id|startup_time
op_assign
id|kernel_mktime
c_func
(paren
op_amp
id|time
)paren
suffix:semicolon
)brace
DECL|variable|memory_start
r_static
r_int
r_int
id|memory_start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* After mem_init, stores the */
multiline_comment|/* amount of free user memory */
DECL|variable|memory_end
r_static
r_int
r_int
id|memory_end
op_assign
l_int|0
suffix:semicolon
DECL|variable|low_memory_start
r_static
r_int
r_int
id|low_memory_start
op_assign
l_int|0
suffix:semicolon
DECL|variable|argv_init
r_static
r_char
op_star
id|argv_init
(braket
id|MAX_INIT_ARGS
op_plus
l_int|2
)braket
op_assign
(brace
l_string|&quot;/bin/init&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|envp_init
r_static
r_char
op_star
id|envp_init
(braket
id|MAX_INIT_ENVS
op_plus
l_int|2
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=console&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|variable|argv_rc
r_static
r_char
op_star
id|argv_rc
(braket
)braket
op_assign
(brace
l_string|&quot;/bin/sh&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|envp_rc
r_static
r_char
op_star
id|envp_rc
(braket
)braket
op_assign
(brace
l_string|&quot;HOME=/&quot;
comma
l_string|&quot;TERM=console&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|argv
r_static
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;-/bin/sh&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|envp
r_static
r_char
op_star
id|envp
(braket
)braket
op_assign
(brace
l_string|&quot;HOME=/usr/root&quot;
comma
l_string|&quot;TERM=console&quot;
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|drive_info
DECL|member|dummy
DECL|variable|drive_info
r_struct
id|drive_info
(brace
r_char
id|dummy
(braket
l_int|32
)braket
suffix:semicolon
)brace
id|drive_info
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
l_int|80
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * This is a simple kernel command line parsing function: it parses&n; * the command line, and fills in the arguments/environment to init&n; * as appropriate. Any cmd-line option is taken to be an environment&n; * variable if it contains the character &squot;=&squot;.&n; *&n; *&n; * This routine also checks for options meant for the kernel - currently&n; * only the &quot;root=XXXX&quot; option is recognized. These options are not given&n; * to init - they are for internal kernel use only.&n; */
DECL|function|parse_options
r_static
r_void
id|parse_options
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_char
op_star
id|next
suffix:semicolon
r_int
id|args
comma
id|envs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|line
)paren
r_return
suffix:semicolon
id|args
op_assign
l_int|0
suffix:semicolon
id|envs
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* TERM is set to &squot;console&squot; by default */
id|next
op_assign
id|line
suffix:semicolon
r_while
c_loop
(paren
id|line
op_assign
id|next
)paren
(brace
r_if
c_cond
(paren
id|next
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot; &squot;
)paren
)paren
op_star
id|next
op_increment
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * check for kernel options first..&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;root=&quot;
comma
l_int|5
)paren
)paren
(brace
id|ROOT_DEV
op_assign
id|simple_strtoul
c_func
(paren
id|line
op_plus
l_int|5
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Then check if it&squot;s an environment variable or&n;&t;&t; * an option.&n;&t;&t; */
r_if
c_cond
(paren
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;=&squot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|envs
op_ge
id|MAX_INIT_ENVS
)paren
r_break
suffix:semicolon
id|envp_init
(braket
op_increment
id|envs
)braket
op_assign
id|line
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|args
op_ge
id|MAX_INIT_ARGS
)paren
r_break
suffix:semicolon
id|argv_init
(braket
op_increment
id|args
)braket
op_assign
id|line
suffix:semicolon
)brace
)brace
id|argv_init
(braket
id|args
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
id|envp_init
(braket
id|envs
op_plus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|start_kernel
r_void
id|start_kernel
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * Interrupts are still disabled. Do necessary setups, then&n; * enable them&n; */
id|ROOT_DEV
op_assign
id|ORIG_ROOT_DEV
suffix:semicolon
id|drive_info
op_assign
id|DRIVE_INFO
suffix:semicolon
id|screen_info
op_assign
id|SCREEN_INFO
suffix:semicolon
id|aux_device_present
op_assign
id|AUX_DEVICE_INFO
suffix:semicolon
id|memory_end
op_assign
(paren
l_int|1
op_lshift
l_int|20
)paren
op_plus
(paren
id|EXT_MEM_K
op_lshift
l_int|10
)paren
suffix:semicolon
id|memory_end
op_and_assign
l_int|0xfffff000
suffix:semicolon
macro_line|#ifdef MAX_16M
r_if
c_cond
(paren
id|memory_end
OG
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
id|memory_end
op_assign
l_int|16
op_star
l_int|1024
op_star
l_int|1024
suffix:semicolon
macro_line|#endif
id|memory_start
op_assign
l_int|1024
op_star
l_int|1024
suffix:semicolon
id|low_memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|end
suffix:semicolon
id|low_memory_start
op_add_assign
l_int|0xfff
suffix:semicolon
id|low_memory_start
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|memory_start
op_assign
id|paging_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CL_MAGIC_ADDR
op_eq
id|CL_MAGIC
)paren
id|strcpy
c_func
(paren
id|command_line
comma
id|CL_BASE_ADDR
op_plus
id|CL_OFFSET
)paren
suffix:semicolon
id|trap_init
c_func
(paren
)paren
suffix:semicolon
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
id|sched_init
c_func
(paren
)paren
suffix:semicolon
id|parse_options
c_func
(paren
id|command_line
)paren
suffix:semicolon
macro_line|#ifdef PROFILE_SHIFT
id|prof_buffer
op_assign
(paren
r_int
r_int
op_star
)paren
id|memory_start
suffix:semicolon
id|prof_len
op_assign
(paren
r_int
r_int
)paren
op_amp
id|end
suffix:semicolon
id|prof_len
op_rshift_assign
id|PROFILE_SHIFT
suffix:semicolon
id|memory_start
op_add_assign
id|prof_len
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif
id|memory_start
op_assign
id|chr_dev_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
id|memory_start
op_assign
id|blk_dev_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SCSI
id|memory_start
op_assign
id|scsi_dev_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
macro_line|#endif
id|mem_init
c_func
(paren
id|low_memory_start
comma
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
id|buffer_init
c_func
(paren
)paren
suffix:semicolon
id|inode_init
c_func
(paren
)paren
suffix:semicolon
id|time_init
c_func
(paren
)paren
suffix:semicolon
id|floppy_init
c_func
(paren
)paren
suffix:semicolon
id|sock_init
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|move_to_user_mode
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fork
c_func
(paren
)paren
)paren
multiline_comment|/* we count on this going ok */
id|init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n; * task[0] is meant to be used as an &quot;idle&quot; task: it may not sleep, but&n; * it might do some general things like count free pages or it could be&n; * used to implement a reasonable LRU algorithm for the paging routines:&n; * anything that can be useful, but shouldn&squot;t take time from the real&n; * processes.&n; *&n; * Right now task[0] just does a infinite idle loop.&n; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|idle
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|printf
r_static
r_int
id|printf
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|write
c_func
(paren
l_int|1
comma
id|printbuf
comma
id|i
op_assign
id|vsprintf
c_func
(paren
id|printbuf
comma
id|fmt
comma
id|args
)paren
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|init
r_void
id|init
c_func
(paren
r_void
)paren
(brace
r_int
id|pid
comma
id|i
suffix:semicolon
id|setup
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|drive_info
)paren
suffix:semicolon
(paren
r_void
)paren
id|open
c_func
(paren
l_string|&quot;/dev/tty1&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|printf
c_func
(paren
id|linux_banner
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/etc/init&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/bin/init&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
multiline_comment|/* if this fails, fall through to original stuff */
r_if
c_cond
(paren
op_logical_neg
(paren
id|pid
op_assign
id|fork
c_func
(paren
)paren
)paren
)paren
(brace
id|close
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|open
c_func
(paren
l_string|&quot;/etc/rc&quot;
comma
id|O_RDONLY
comma
l_int|0
)paren
)paren
id|_exit
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|execve
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
id|argv_rc
comma
id|envp_rc
)paren
suffix:semicolon
id|_exit
c_func
(paren
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pid
OG
l_int|0
)paren
r_while
c_loop
(paren
id|pid
op_ne
id|wait
c_func
(paren
op_amp
id|i
)paren
)paren
multiline_comment|/* nothing */
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
(paren
id|pid
op_assign
id|fork
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Fork failed in init&bslash;r&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pid
)paren
(brace
id|close
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|close
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|setsid
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|open
c_func
(paren
l_string|&quot;/dev/tty1&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
(paren
r_void
)paren
id|dup
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|_exit
c_func
(paren
id|execve
c_func
(paren
l_string|&quot;/bin/sh&quot;
comma
id|argv
comma
id|envp
)paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
r_if
c_cond
(paren
id|pid
op_eq
id|wait
c_func
(paren
op_amp
id|i
)paren
)paren
r_break
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&bslash;rchild %d died with code %04x&bslash;n&bslash;r&quot;
comma
id|pid
comma
id|i
)paren
suffix:semicolon
id|sync
c_func
(paren
)paren
suffix:semicolon
)brace
id|_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* NOTE! _exit, not exit() */
)brace
eof
