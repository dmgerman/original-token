multiline_comment|/*&n; *  linux/init/main.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/head.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
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
r_char
id|edata
comma
id|end
suffix:semicolon
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
id|asmlinkage
r_void
id|lcall7
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|default_ldt
r_struct
id|desc_struct
id|default_ldt
suffix:semicolon
multiline_comment|/*&n; * we need this inline - forking from kernel space will result&n; * in NO COPY ON WRITE (!!!), until an execve is executed. This&n; * is no problem, but for the stack. This is handled by not letting&n; * main() use the stack at all after fork(). Thus, no function&n; * calls - which means inline code for fork too, as otherwise we&n; * would use the stack upon exit from &squot;fork()&squot;.&n; *&n; * Actually only pause and fork are needed inline, so that there&n; * won&squot;t be any messing with the stack from main(), but we define&n; * some others too.&n; */
DECL|macro|__NR__exit
mdefine_line|#define __NR__exit __NR_exit
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
id|_syscall0
c_func
(paren
r_int
comma
id|setup
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
id|_syscall1
c_func
(paren
r_int
comma
id|_exit
comma
r_int
comma
id|exitcode
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
id|console_loglevel
suffix:semicolon
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
r_extern
r_int
id|vsprintf
c_func
(paren
r_char
op_star
comma
r_const
r_char
op_star
comma
id|va_list
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
r_void
id|init_modules
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kmalloc_init
(paren
r_int
comma
r_int
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
r_int
r_int
id|net_dev_init
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|hd_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|bmouse_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|eth_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|xd_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|mcd_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|st_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|st0x_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|tmc8xx_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|t128_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|generic_NCR5380_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|intr
)paren
suffix:semicolon
r_extern
r_void
id|aha152x_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|scsi_luns_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
r_extern
r_void
id|sound_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SBPCD
r_extern
r_void
id|sbpcd_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
suffix:semicolon
macro_line|#endif CONFIG_SBPCD
macro_line|#ifdef CONFIG_SYSVIPC
r_extern
r_void
id|ipc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
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
DECL|macro|PARAM
mdefine_line|#define PARAM&t;empty_zero_page
DECL|macro|EXT_MEM_K
mdefine_line|#define EXT_MEM_K (*(unsigned short *) (PARAM+2))
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (*(struct drive_info_struct *) (PARAM+0x80))
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (*(struct screen_info *) (PARAM+0))
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned short *) (PARAM+0x1F2))
DECL|macro|RAMDISK_SIZE
mdefine_line|#define RAMDISK_SIZE (*(unsigned short *) (PARAM+0x1F8))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
DECL|macro|AUX_DEVICE_INFO
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
multiline_comment|/*&n; * Boot command-line arguments&n; */
DECL|macro|MAX_INIT_ARGS
mdefine_line|#define MAX_INIT_ARGS 8
DECL|macro|MAX_INIT_ENVS
mdefine_line|#define MAX_INIT_ENVS 8
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE ((char *) (PARAM+2048))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
r_extern
r_void
id|time_init
c_func
(paren
r_void
)paren
suffix:semicolon
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
DECL|variable|term
r_static
r_char
id|term
(braket
l_int|21
)braket
suffix:semicolon
DECL|variable|rows
DECL|variable|cols
r_int
id|rows
comma
id|cols
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
l_string|&quot;init&quot;
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
id|term
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
id|term
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
id|term
comma
l_int|NULL
)brace
suffix:semicolon
DECL|struct|drive_info_struct
DECL|member|dummy
DECL|variable|drive_info
r_struct
id|drive_info_struct
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
DECL|variable|ramdisk_size
r_int
id|ramdisk_size
suffix:semicolon
DECL|variable|root_mountflags
r_int
id|root_mountflags
op_assign
l_int|0
suffix:semicolon
DECL|variable|fpu_error
r_static
r_char
id|fpu_error
op_assign
l_int|0
suffix:semicolon
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|COMMAND_LINE_SIZE
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|function|get_options
r_char
op_star
id|get_options
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_char
op_star
id|cur
op_assign
id|str
suffix:semicolon
r_int
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|cur
op_logical_and
id|isdigit
c_func
(paren
op_star
id|cur
)paren
op_logical_and
id|i
op_le
l_int|10
)paren
(brace
id|ints
(braket
id|i
op_increment
)braket
op_assign
id|simple_strtoul
c_func
(paren
id|cur
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cur
op_assign
id|strchr
c_func
(paren
id|cur
comma
l_char|&squot;,&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
id|cur
op_increment
suffix:semicolon
)brace
id|ints
(braket
l_int|0
)braket
op_assign
id|i
op_minus
l_int|1
suffix:semicolon
r_return
id|cur
suffix:semicolon
)brace
r_struct
(brace
DECL|member|str
r_char
op_star
id|str
suffix:semicolon
DECL|member|setup_func
r_void
(paren
op_star
id|setup_func
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|variable|bootsetups
)brace
id|bootsetups
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;reserve=&quot;
comma
id|reserve_setup
)brace
comma
macro_line|#ifdef CONFIG_INET
(brace
l_string|&quot;ether=&quot;
comma
id|eth_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI
(brace
l_string|&quot;max_scsi_luns=&quot;
comma
id|scsi_luns_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_HD
(brace
l_string|&quot;hd=&quot;
comma
id|hd_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_CHR_DEV_ST
(brace
l_string|&quot;st=&quot;
comma
id|st_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BUSMOUSE
(brace
l_string|&quot;bmouse=&quot;
comma
id|bmouse_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_SEAGATE
(brace
l_string|&quot;st0x=&quot;
comma
id|st0x_setup
)brace
comma
(brace
l_string|&quot;tmc8xx=&quot;
comma
id|tmc8xx_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_T128
(brace
l_string|&quot;t128=&quot;
comma
id|t128_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_GENERIC_NCR5380
(brace
l_string|&quot;ncr5380=&quot;
comma
id|generic_NCR5380_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SCSI_AHA152X
(brace
l_string|&quot;aha152x=&quot;
comma
id|aha152x_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_XD
(brace
l_string|&quot;xd=&quot;
comma
id|xd_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_MCD
(brace
l_string|&quot;mcd=&quot;
comma
id|mcd_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SOUND
(brace
l_string|&quot;sound=&quot;
comma
id|sound_setup
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_SBPCD
(brace
l_string|&quot;sbpcd=&quot;
comma
id|sbpcd_setup
)brace
comma
macro_line|#endif CONFIG_SBPCD
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|checksetup
r_int
id|checksetup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_int
id|ints
(braket
l_int|11
)braket
suffix:semicolon
r_while
c_loop
(paren
id|bootsetups
(braket
id|i
)braket
dot
id|str
)paren
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|bootsetups
(braket
id|i
)braket
dot
id|str
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
id|bootsetups
(braket
id|i
)braket
dot
id|str
comma
id|n
)paren
)paren
(brace
id|bootsetups
(braket
id|i
)braket
dot
id|setup_func
c_func
(paren
id|get_options
c_func
(paren
id|line
op_plus
id|n
comma
id|ints
)paren
comma
id|ints
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|loops_per_sec
r_int
r_int
id|loops_per_sec
op_assign
l_int|1
suffix:semicolon
DECL|function|calibrate_delay
r_static
r_void
id|calibrate_delay
c_func
(paren
r_void
)paren
(brace
r_int
id|ticks
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Calibrating delay loop.. &quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|loops_per_sec
op_lshift_assign
l_int|1
)paren
(brace
id|ticks
op_assign
id|jiffies
suffix:semicolon
id|__delay
c_func
(paren
id|loops_per_sec
)paren
suffix:semicolon
id|ticks
op_assign
id|jiffies
op_minus
id|ticks
suffix:semicolon
r_if
c_cond
(paren
id|ticks
op_ge
id|HZ
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;mull %1 ; divl %2&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
id|loops_per_sec
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|HZ
)paren
comma
l_string|&quot;r&quot;
(paren
id|ticks
)paren
comma
l_string|&quot;0&quot;
(paren
id|loops_per_sec
)paren
suffix:colon
l_string|&quot;dx&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ok - %lu.%02lu BogoMips&bslash;n&quot;
comma
id|loops_per_sec
op_div
l_int|500000
comma
(paren
id|loops_per_sec
op_div
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
r_char
op_star
id|devnames
(braket
)braket
op_assign
(brace
l_string|&quot;hda&quot;
comma
l_string|&quot;hdb&quot;
comma
l_string|&quot;sda&quot;
comma
l_string|&quot;sdb&quot;
comma
l_string|&quot;sdc&quot;
comma
l_string|&quot;sdd&quot;
comma
l_string|&quot;sde&quot;
comma
l_string|&quot;fd&quot;
comma
l_string|&quot;xda&quot;
comma
l_string|&quot;xdb&quot;
comma
l_int|NULL
)brace
suffix:semicolon
r_int
id|devnums
(braket
)braket
op_assign
(brace
l_int|0x300
comma
l_int|0x340
comma
l_int|0x800
comma
l_int|0x810
comma
l_int|0x820
comma
l_int|0x830
comma
l_int|0x840
comma
l_int|0x200
comma
l_int|0xD00
comma
l_int|0xD40
comma
l_int|0
)brace
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
(paren
id|line
op_assign
id|next
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
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
op_ne
l_int|NULL
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
r_int
id|n
suffix:semicolon
id|line
op_add_assign
l_int|5
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|line
comma
l_string|&quot;/dev/&quot;
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
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|line
op_add_assign
l_int|5
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|devnames
(braket
id|n
)braket
suffix:semicolon
id|n
op_increment
)paren
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|devnames
(braket
id|n
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|line
comma
id|devnames
(braket
id|n
)braket
comma
id|len
)paren
)paren
(brace
id|ROOT_DEV
op_assign
id|devnums
(braket
id|n
)braket
op_plus
id|simple_strtoul
c_func
(paren
id|line
op_plus
id|len
comma
l_int|NULL
comma
l_int|16
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;ro&quot;
)paren
)paren
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;rw&quot;
)paren
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;debug&quot;
)paren
)paren
id|console_loglevel
op_assign
l_int|10
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;no387&quot;
)paren
)paren
(brace
id|hard_math
op_assign
l_int|0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr0,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;orl $0xE,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;movl %%eax,%%cr0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;ax&quot;
)paren
suffix:semicolon
)brace
r_else
id|checksetup
c_func
(paren
id|line
)paren
suffix:semicolon
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
DECL|function|copy_options
r_static
r_void
id|copy_options
c_func
(paren
r_char
op_star
id|to
comma
r_char
op_star
id|from
)paren
(brace
r_char
id|c
op_assign
l_char|&squot; &squot;
suffix:semicolon
r_int
id|len
op_assign
l_int|0
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
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
op_star
(paren
r_int
r_int
op_star
)paren
id|from
op_eq
op_star
(paren
r_int
r_int
op_star
)paren
l_string|&quot;mem=&quot;
)paren
id|memory_end
op_assign
id|simple_strtoul
c_func
(paren
id|from
op_plus
l_int|4
comma
op_amp
id|from
comma
l_int|0
)paren
suffix:semicolon
id|c
op_assign
op_star
(paren
id|from
op_increment
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|c
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|COMMAND_LINE_SIZE
op_le
op_increment
id|len
)paren
r_break
suffix:semicolon
op_star
(paren
id|to
op_increment
)paren
op_assign
id|c
suffix:semicolon
)brace
op_star
id|to
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
DECL|function|copro_timeout
r_static
r_void
id|copro_timeout
c_func
(paren
r_void
)paren
(brace
id|fpu_error
op_assign
l_int|1
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
l_int|100
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|COPRO_TIMER
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;387 failed: trying to reset&bslash;n&quot;
)paren
suffix:semicolon
id|send_sig
c_func
(paren
id|SIGFPE
comma
id|last_task_used_math
comma
l_int|1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xf1
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
l_int|0xf0
)paren
suffix:semicolon
)brace
DECL|function|start_kernel
id|asmlinkage
r_void
id|start_kernel
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n; * Interrupts are still disabled. Do necessary setups, then&n; * enable them&n; */
id|set_call_gate
c_func
(paren
op_amp
id|default_ldt
comma
id|lcall7
)paren
suffix:semicolon
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
id|PAGE_MASK
suffix:semicolon
id|ramdisk_size
op_assign
id|RAMDISK_SIZE
suffix:semicolon
id|copy_options
c_func
(paren
id|command_line
comma
id|COMMAND_LINE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MAX_16M
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
r_if
c_cond
(paren
id|MOUNT_ROOT_RDONLY
)paren
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
op_amp
id|end
op_ge
(paren
l_int|1024
op_star
l_int|1024
)paren
)paren
(brace
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|end
suffix:semicolon
id|low_memory_start
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_else
(brace
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
)brace
id|low_memory_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|low_memory_start
)paren
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
id|strncmp
c_func
(paren
(paren
r_char
op_star
)paren
l_int|0x0FFFD9
comma
l_string|&quot;EISA&quot;
comma
l_int|4
)paren
op_eq
l_int|0
)paren
id|EISA_bus
op_assign
l_int|1
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
id|init_modules
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PROFILE
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
l_int|2
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
id|kmalloc_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
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
id|sti
c_func
(paren
)paren
suffix:semicolon
id|calibrate_delay
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_INET
id|memory_start
op_assign
id|net_dev_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
macro_line|#endif
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
id|memory_start
op_assign
id|inode_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
id|memory_start
op_assign
id|file_table_init
c_func
(paren
id|memory_start
comma
id|memory_end
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_SYSVIPC
id|ipc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check if exception 16 works correctly.. This is truly evil&n;&t; * code: it disables the high 8 interrupts to make sure that&n;&t; * the irq13 doesn&squot;t happen. But as this will lead to a lockup&n;&t; * if no exception16 arrives, it depends on the fact that the&n;&t; * high 8 interrupts will be re-enabled by the next timer tick.&n;&t; * So the irq13 will happen eventually, but the exception 16&n;&t; * should get there first..&n;&t; */
r_if
c_cond
(paren
id|hard_math
)paren
(brace
r_int
r_int
id|control_word
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking 386/387 coupling... &quot;
)paren
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|expires
op_assign
id|jiffies
op_plus
l_int|50
suffix:semicolon
id|timer_table
(braket
id|COPRO_TIMER
)braket
dot
id|fn
op_assign
id|copro_timeout
suffix:semicolon
id|timer_active
op_or_assign
l_int|1
op_lshift
id|COPRO_TIMER
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;clts ; fninit ; fnstcw %0 ; fwait&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
op_amp
id|control_word
)paren
)paren
suffix:semicolon
id|control_word
op_and_assign
l_int|0xffc0
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fldcw %0 ; fwait&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
op_amp
id|control_word
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|inb_p
c_func
(paren
l_int|0x21
)paren
op_or
(paren
l_int|1
op_lshift
l_int|2
)paren
comma
l_int|0x21
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;fldz ; fld1 ; fdiv %st,%st(1) ; fwait&quot;
)paren
suffix:semicolon
id|timer_active
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|COPRO_TIMER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fpu_error
)paren
id|printk
c_func
(paren
l_string|&quot;Ok, fpu using %s error reporting.&bslash;n&quot;
comma
id|ignore_irq13
ques
c_cond
l_string|&quot;exception 16&quot;
suffix:colon
l_string|&quot;irq13&quot;
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_MATH_EMULATION
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;No coprocessor found and no math emulation present.&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Giving up.&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
)brace
macro_line|#endif
id|system_utsname.machine
(braket
l_int|1
)braket
op_assign
l_char|&squot;0&squot;
op_plus
id|x86
suffix:semicolon
id|printk
c_func
(paren
id|linux_banner
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
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|term
comma
l_string|&quot;TERM=con%dx%d&quot;
comma
id|ORIG_VIDEO_COLS
comma
id|ORIG_VIDEO_LINES
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
id|execve
c_func
(paren
l_string|&quot;/sbin/init&quot;
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
l_string|&quot;Fork failed in init&bslash;n&bslash;r&quot;
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
)brace
eof
