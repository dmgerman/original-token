multiline_comment|/*&n; *  linux/init/main.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  GK 2/5/95  -  Changed to support mounting root fs via NFS&n; *  Added initrd &amp; change_root: Werner Almesberger &amp; Hans Lermen, Feb &squot;96&n; *  Moan early if gcc is old, avoiding bogus kernels - Paul Gortmaker, May &squot;96&n; *  Simplified starting of init:  Michael A. Griffith &lt;grif@acm.org&gt; &n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/raid/md.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/iobuf.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bugs.h&gt;
macro_line|#ifdef CONFIG_PCI
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_DIO
macro_line|#include &lt;linux/dio.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_ZORRO
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_MTRR
macro_line|#  include &lt;asm/mtrr.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_3215_CONSOLE
r_extern
r_int
id|con3215_activate
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
r_extern
r_void
id|nubus_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISAPNP
macro_line|#include &lt;linux/isapnp.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_IRDA
macro_line|#include &lt;net/irda/irda_device.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_X86_IO_APIC
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Versions of gcc older than that listed below may actually compile&n; * and link okay, but the end product can have subtle run time bugs.&n; * To avoid associated bogus bug reports, we flatly refuse to compile&n; * with a gcc that is known to be too old from the very beginning.&n; */
macro_line|#if __GNUC__ &lt; 2 || (__GNUC__ == 2 &amp;&amp; __GNUC_MINOR__ &lt; 7)
macro_line|#error sorry, your GCC is too old. It builds incorrect kernels.
macro_line|#endif
r_extern
r_char
id|_stext
comma
id|_etext
suffix:semicolon
r_extern
r_char
op_star
id|linux_banner
suffix:semicolon
r_extern
r_int
id|console_loglevel
suffix:semicolon
r_static
r_int
id|init
c_func
(paren
r_void
op_star
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
r_void
id|sock_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fork_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|mca_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sbus_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ppc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sysctl_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|signals_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|bdev_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|init_pcmcia_ds
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_initmem
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|filesystem_setup
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_TC
r_extern
r_void
id|tc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|ecard_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SYSVIPC)
r_extern
r_void
id|ipc_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_QUOTA)
r_extern
r_void
id|dquot_init_hash
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Boot command-line arguments&n; */
DECL|macro|MAX_INIT_ARGS
mdefine_line|#define MAX_INIT_ARGS 8
DECL|macro|MAX_INIT_ENVS
mdefine_line|#define MAX_INIT_ENVS 8
r_extern
r_void
id|time_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|softirq_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|rows
DECL|variable|cols
r_int
id|rows
comma
id|cols
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|variable|real_root_dev
id|kdev_t
id|real_root_dev
suffix:semicolon
macro_line|#endif
DECL|variable|root_mountflags
r_int
id|root_mountflags
op_assign
id|MS_RDONLY
suffix:semicolon
DECL|variable|execute_command
r_char
op_star
id|execute_command
suffix:semicolon
DECL|variable|root_device_name
r_char
id|root_device_name
(braket
l_int|64
)braket
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
l_string|&quot;TERM=linux&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
DECL|function|profile_setup
r_static
r_int
id|__init
id|profile_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|par
suffix:semicolon
r_if
c_cond
(paren
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|par
)paren
)paren
id|prof_shift
op_assign
id|par
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;profile=&quot;
comma
id|profile_setup
)paren
suffix:semicolon
DECL|struct|dev_name_struct
r_static
r_struct
id|dev_name_struct
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|num
r_const
r_int
id|num
suffix:semicolon
DECL|variable|__initdata
)brace
id|root_dev_names
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_string|&quot;nfs&quot;
comma
l_int|0x00ff
)brace
comma
(brace
l_string|&quot;hda&quot;
comma
l_int|0x0300
)brace
comma
(brace
l_string|&quot;hdb&quot;
comma
l_int|0x0340
)brace
comma
(brace
l_string|&quot;hdc&quot;
comma
l_int|0x1600
)brace
comma
(brace
l_string|&quot;hdd&quot;
comma
l_int|0x1640
)brace
comma
(brace
l_string|&quot;hde&quot;
comma
l_int|0x2100
)brace
comma
(brace
l_string|&quot;hdf&quot;
comma
l_int|0x2140
)brace
comma
(brace
l_string|&quot;hdg&quot;
comma
l_int|0x2200
)brace
comma
(brace
l_string|&quot;hdh&quot;
comma
l_int|0x2240
)brace
comma
(brace
l_string|&quot;hdi&quot;
comma
l_int|0x3800
)brace
comma
(brace
l_string|&quot;hdj&quot;
comma
l_int|0x3840
)brace
comma
(brace
l_string|&quot;hdk&quot;
comma
l_int|0x3900
)brace
comma
(brace
l_string|&quot;hdl&quot;
comma
l_int|0x3940
)brace
comma
(brace
l_string|&quot;hdm&quot;
comma
l_int|0x5800
)brace
comma
(brace
l_string|&quot;hdn&quot;
comma
l_int|0x5840
)brace
comma
(brace
l_string|&quot;hdo&quot;
comma
l_int|0x5900
)brace
comma
(brace
l_string|&quot;hdp&quot;
comma
l_int|0x5940
)brace
comma
(brace
l_string|&quot;hdq&quot;
comma
l_int|0x5A00
)brace
comma
(brace
l_string|&quot;hdr&quot;
comma
l_int|0x5A40
)brace
comma
(brace
l_string|&quot;hds&quot;
comma
l_int|0x5B00
)brace
comma
(brace
l_string|&quot;hdt&quot;
comma
l_int|0x5B40
)brace
comma
(brace
l_string|&quot;sda&quot;
comma
l_int|0x0800
)brace
comma
(brace
l_string|&quot;sdb&quot;
comma
l_int|0x0810
)brace
comma
(brace
l_string|&quot;sdc&quot;
comma
l_int|0x0820
)brace
comma
(brace
l_string|&quot;sdd&quot;
comma
l_int|0x0830
)brace
comma
(brace
l_string|&quot;sde&quot;
comma
l_int|0x0840
)brace
comma
(brace
l_string|&quot;sdf&quot;
comma
l_int|0x0850
)brace
comma
(brace
l_string|&quot;sdg&quot;
comma
l_int|0x0860
)brace
comma
(brace
l_string|&quot;sdh&quot;
comma
l_int|0x0870
)brace
comma
(brace
l_string|&quot;sdi&quot;
comma
l_int|0x0880
)brace
comma
(brace
l_string|&quot;sdj&quot;
comma
l_int|0x0890
)brace
comma
(brace
l_string|&quot;sdk&quot;
comma
l_int|0x08a0
)brace
comma
(brace
l_string|&quot;sdl&quot;
comma
l_int|0x08b0
)brace
comma
(brace
l_string|&quot;sdm&quot;
comma
l_int|0x08c0
)brace
comma
(brace
l_string|&quot;sdn&quot;
comma
l_int|0x08d0
)brace
comma
(brace
l_string|&quot;sdo&quot;
comma
l_int|0x08e0
)brace
comma
(brace
l_string|&quot;sdp&quot;
comma
l_int|0x08f0
)brace
comma
(brace
l_string|&quot;ada&quot;
comma
l_int|0x1c00
)brace
comma
(brace
l_string|&quot;adb&quot;
comma
l_int|0x1c10
)brace
comma
(brace
l_string|&quot;adc&quot;
comma
l_int|0x1c20
)brace
comma
(brace
l_string|&quot;add&quot;
comma
l_int|0x1c30
)brace
comma
(brace
l_string|&quot;ade&quot;
comma
l_int|0x1c40
)brace
comma
(brace
l_string|&quot;fd&quot;
comma
l_int|0x0200
)brace
comma
(brace
l_string|&quot;md&quot;
comma
l_int|0x0900
)brace
comma
(brace
l_string|&quot;xda&quot;
comma
l_int|0x0d00
)brace
comma
(brace
l_string|&quot;xdb&quot;
comma
l_int|0x0d40
)brace
comma
(brace
l_string|&quot;ram&quot;
comma
l_int|0x0100
)brace
comma
(brace
l_string|&quot;scd&quot;
comma
l_int|0x0b00
)brace
comma
(brace
l_string|&quot;mcd&quot;
comma
l_int|0x1700
)brace
comma
(brace
l_string|&quot;cdu535&quot;
comma
l_int|0x1800
)brace
comma
(brace
l_string|&quot;sonycd&quot;
comma
l_int|0x1800
)brace
comma
(brace
l_string|&quot;aztcd&quot;
comma
l_int|0x1d00
)brace
comma
(brace
l_string|&quot;cm206cd&quot;
comma
l_int|0x2000
)brace
comma
(brace
l_string|&quot;gscd&quot;
comma
l_int|0x1000
)brace
comma
(brace
l_string|&quot;sbpcd&quot;
comma
l_int|0x1900
)brace
comma
(brace
l_string|&quot;eda&quot;
comma
l_int|0x2400
)brace
comma
(brace
l_string|&quot;edb&quot;
comma
l_int|0x2440
)brace
comma
(brace
l_string|&quot;pda&quot;
comma
l_int|0x2d00
)brace
comma
(brace
l_string|&quot;pdb&quot;
comma
l_int|0x2d10
)brace
comma
(brace
l_string|&quot;pdc&quot;
comma
l_int|0x2d20
)brace
comma
(brace
l_string|&quot;pdd&quot;
comma
l_int|0x2d30
)brace
comma
(brace
l_string|&quot;pcd&quot;
comma
l_int|0x2e00
)brace
comma
(brace
l_string|&quot;pf&quot;
comma
l_int|0x2f00
)brace
comma
(brace
l_string|&quot;apblock&quot;
comma
id|APBLOCK_MAJOR
op_lshift
l_int|8
)brace
comma
(brace
l_string|&quot;ddv&quot;
comma
id|DDV_MAJOR
op_lshift
l_int|8
)brace
comma
(brace
l_string|&quot;jsfd&quot;
comma
id|JSFD_MAJOR
op_lshift
l_int|8
)brace
comma
macro_line|#ifdef CONFIG_MDISK
(brace
l_string|&quot;mnda&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
)brace
comma
(brace
l_string|&quot;mndb&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|1
)brace
comma
(brace
l_string|&quot;mndc&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|2
)brace
comma
(brace
l_string|&quot;mndd&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|3
)brace
comma
(brace
l_string|&quot;mnde&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|4
)brace
comma
(brace
l_string|&quot;mndf&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|5
)brace
comma
(brace
l_string|&quot;mndg&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|6
)brace
comma
(brace
l_string|&quot;mndh&quot;
comma
(paren
id|MDISK_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
l_int|7
)brace
comma
macro_line|#endif
macro_line|#ifdef CONFIG_DASD
(brace
l_string|&quot;dasda&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
)brace
comma
(brace
l_string|&quot;dasdb&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|1
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasdc&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|2
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasdd&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|3
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasde&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|4
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasdf&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|5
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasdg&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|6
op_lshift
l_int|2
)paren
)brace
comma
(brace
l_string|&quot;dasdh&quot;
comma
(paren
id|DASD_MAJOR
op_lshift
id|MINORBITS
)paren
op_plus
(paren
l_int|7
op_lshift
l_int|2
)paren
)brace
comma
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_CPQ_DA) || defined(CONFIG_BLK_CPQ_DA_MODULE)
(brace
l_string|&quot;ida/c0d0p&quot;
comma
l_int|0x4800
)brace
comma
(brace
l_string|&quot;ida/c0d1p&quot;
comma
l_int|0x4810
)brace
comma
(brace
l_string|&quot;ida/c0d2p&quot;
comma
l_int|0x4820
)brace
comma
(brace
l_string|&quot;ida/c0d3p&quot;
comma
l_int|0x4830
)brace
comma
(brace
l_string|&quot;ida/c0d4p&quot;
comma
l_int|0x4840
)brace
comma
(brace
l_string|&quot;ida/c0d5p&quot;
comma
l_int|0x4850
)brace
comma
(brace
l_string|&quot;ida/c0d6p&quot;
comma
l_int|0x4860
)brace
comma
(brace
l_string|&quot;ida/c0d7p&quot;
comma
l_int|0x4870
)brace
comma
(brace
l_string|&quot;ida/c0d8p&quot;
comma
l_int|0x4880
)brace
comma
(brace
l_string|&quot;ida/c0d9p&quot;
comma
l_int|0x4890
)brace
comma
(brace
l_string|&quot;ida/c0d10p&quot;
comma
l_int|0x48A0
)brace
comma
(brace
l_string|&quot;ida/c0d11p&quot;
comma
l_int|0x48B0
)brace
comma
(brace
l_string|&quot;ida/c0d12p&quot;
comma
l_int|0x48C0
)brace
comma
(brace
l_string|&quot;ida/c0d13p&quot;
comma
l_int|0x48D0
)brace
comma
(brace
l_string|&quot;ida/c0d14p&quot;
comma
l_int|0x48E0
)brace
comma
(brace
l_string|&quot;ida/c0d15p&quot;
comma
l_int|0x48F0
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|name_to_kdev_t
id|kdev_t
id|__init
id|name_to_kdev_t
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|base
op_assign
l_int|0
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
op_eq
l_int|0
)paren
(brace
r_struct
id|dev_name_struct
op_star
id|dev
op_assign
id|root_dev_names
suffix:semicolon
id|line
op_add_assign
l_int|5
suffix:semicolon
r_do
(brace
r_int
id|len
op_assign
id|strlen
c_func
(paren
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|line
comma
id|dev-&gt;name
comma
id|len
)paren
op_eq
l_int|0
)paren
(brace
id|line
op_add_assign
id|len
suffix:semicolon
id|base
op_assign
id|dev-&gt;num
suffix:semicolon
r_break
suffix:semicolon
)brace
id|dev
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_return
id|to_kdev_t
c_func
(paren
id|base
op_plus
id|simple_strtoul
c_func
(paren
id|line
comma
l_int|NULL
comma
id|base
ques
c_cond
l_int|10
suffix:colon
l_int|16
)paren
)paren
suffix:semicolon
)brace
DECL|function|root_dev_setup
r_static
r_int
id|__init
id|root_dev_setup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_int
id|i
suffix:semicolon
r_char
id|ch
suffix:semicolon
id|ROOT_DEV
op_assign
id|name_to_kdev_t
c_func
(paren
id|line
)paren
suffix:semicolon
id|memset
(paren
id|root_device_name
comma
l_int|0
comma
r_sizeof
id|root_device_name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
(paren
id|line
comma
l_string|&quot;/dev/&quot;
comma
l_int|5
)paren
op_eq
l_int|0
)paren
id|line
op_add_assign
l_int|5
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
r_sizeof
id|root_device_name
op_minus
l_int|1
suffix:semicolon
op_increment
id|i
)paren
(brace
id|ch
op_assign
id|line
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|isspace
(paren
id|ch
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;,&squot;
)paren
op_logical_or
(paren
id|ch
op_eq
l_char|&squot;&bslash;0&squot;
)paren
)paren
r_break
suffix:semicolon
id|root_device_name
(braket
id|i
)braket
op_assign
id|ch
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;root=&quot;
comma
id|root_dev_setup
)paren
suffix:semicolon
DECL|function|checksetup
r_static
r_int
id|__init
id|checksetup
c_func
(paren
r_char
op_star
id|line
)paren
(brace
r_struct
id|kernel_param
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|__setup_start
suffix:semicolon
r_do
(brace
r_int
id|n
op_assign
id|strlen
c_func
(paren
id|p-&gt;str
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
id|p-&gt;str
comma
id|n
)paren
)paren
(brace
r_if
c_cond
(paren
id|p
op_member_access_from_pointer
id|setup_func
c_func
(paren
id|line
op_plus
id|n
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
id|p
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|p
OL
op_amp
id|__setup_end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* this should be approx 2 Bo*oMips to start (note initial shift), and will&n;   still work even if initially too large, it will just take slightly longer */
DECL|variable|loops_per_sec
r_int
r_int
id|loops_per_sec
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
multiline_comment|/* This is the number of bits of precision for the loops_per_second.  Each&n;   bit takes on average 1.5/HZ seconds.  This (like the original) is a little&n;   better than 1% */
DECL|macro|LPS_PREC
mdefine_line|#define LPS_PREC 8
DECL|function|calibrate_delay
r_void
id|__init
id|calibrate_delay
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|ticks
comma
id|loopbit
suffix:semicolon
r_int
id|lps_precision
op_assign
id|LPS_PREC
suffix:semicolon
id|loops_per_sec
op_assign
(paren
l_int|1
op_lshift
l_int|12
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Calibrating delay loop... &quot;
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
multiline_comment|/* wait for &quot;start of&quot; clock tick */
id|ticks
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_eq
id|jiffies
)paren
multiline_comment|/* nothing */
suffix:semicolon
multiline_comment|/* Go .. */
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
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* Do a binary approximation to get loops_per_second set to equal one clock&n;   (up to lps_precision bits) */
id|loops_per_sec
op_rshift_assign
l_int|1
suffix:semicolon
id|loopbit
op_assign
id|loops_per_sec
suffix:semicolon
r_while
c_loop
(paren
id|lps_precision
op_decrement
op_logical_and
(paren
id|loopbit
op_rshift_assign
l_int|1
)paren
)paren
(brace
id|loops_per_sec
op_or_assign
id|loopbit
suffix:semicolon
id|ticks
op_assign
id|jiffies
suffix:semicolon
r_while
c_loop
(paren
id|ticks
op_eq
id|jiffies
)paren
suffix:semicolon
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
r_if
c_cond
(paren
id|jiffies
op_ne
id|ticks
)paren
multiline_comment|/* longer than 1 tick */
id|loops_per_sec
op_and_assign
op_complement
id|loopbit
suffix:semicolon
)brace
multiline_comment|/* finally, adjust loops per second in terms of seconds instead of clocks */
id|loops_per_sec
op_mul_assign
id|HZ
suffix:semicolon
multiline_comment|/* Round the value and print it */
id|printk
c_func
(paren
l_string|&quot;%lu.%02lu BogoMIPS&bslash;n&quot;
comma
(paren
id|loops_per_sec
op_plus
l_int|2500
)paren
op_div
l_int|500000
comma
(paren
(paren
id|loops_per_sec
op_plus
l_int|2500
)paren
op_div
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
DECL|function|readonly
r_static
r_int
id|__init
id|readonly
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|root_mountflags
op_or_assign
id|MS_RDONLY
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|readwrite
r_static
r_int
id|__init
id|readwrite
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|debug_kernel
r_static
r_int
id|__init
id|debug_kernel
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|console_loglevel
op_assign
l_int|10
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|quiet_kernel
r_static
r_int
id|__init
id|quiet_kernel
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_star
id|str
)paren
r_return
l_int|0
suffix:semicolon
id|console_loglevel
op_assign
l_int|4
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;ro&quot;
comma
id|readonly
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;rw&quot;
comma
id|readwrite
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;debug&quot;
comma
id|debug_kernel
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;quiet&quot;
comma
id|quiet_kernel
)paren
suffix:semicolon
multiline_comment|/*&n; * This is a simple kernel command line parsing function: it parses&n; * the command line, and fills in the arguments/environment to init&n; * as appropriate. Any cmd-line option is taken to be an environment&n; * variable if it contains the character &squot;=&squot;.&n; *&n; * This routine also checks for options meant for the kernel.&n; * These options are not given to init - they are for internal kernel use only.&n; */
DECL|function|parse_options
r_static
r_void
id|__init
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
comma
op_star
id|quote
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
multiline_comment|/* TERM is set to &squot;linux&squot; by default */
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
id|quote
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|next
op_ne
l_int|NULL
op_logical_and
id|quote
op_ne
l_int|NULL
op_logical_and
id|quote
OL
id|next
)paren
(brace
multiline_comment|/* we found a left quote before the next blank&n;                         * now we have to find the matching right quote&n;                         */
id|next
op_assign
id|strchr
c_func
(paren
id|quote
op_plus
l_int|1
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
op_ne
l_int|NULL
)paren
(brace
id|quote
op_assign
id|strchr
c_func
(paren
id|next
op_plus
l_int|1
comma
l_char|&squot;&quot;&squot;
)paren
suffix:semicolon
id|next
op_assign
id|strchr
c_func
(paren
id|next
op_plus
l_int|1
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|next
op_ne
l_int|NULL
)paren
op_star
id|next
op_increment
op_assign
l_int|0
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
l_string|&quot;init=&quot;
comma
l_int|5
)paren
)paren
(brace
id|line
op_add_assign
l_int|5
suffix:semicolon
id|execute_command
op_assign
id|line
suffix:semicolon
multiline_comment|/* In case LILO is going to boot us with default command line,&n;&t;&t;&t; * it prepends &quot;auto&quot; before the whole cmdline which makes&n;&t;&t;&t; * the shell think it should execute a script with such name.&n;&t;&t;&t; * So we ignore all arguments entered _before_ init=... [MJ]&n;&t;&t;&t; */
id|args
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|checksetup
c_func
(paren
id|line
)paren
)paren
r_continue
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
r_if
c_cond
(paren
op_star
id|line
)paren
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
r_extern
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
r_extern
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
macro_line|#ifdef CONFIG_X86_IO_APIC
DECL|function|smp_init
r_static
r_void
id|__init
id|smp_init
c_func
(paren
r_void
)paren
(brace
id|IO_APIC_init_uniprocessor
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|smp_init
mdefine_line|#define smp_init()&t;do { } while (0)
macro_line|#endif
macro_line|#else
multiline_comment|/* Called by boot processor to activate the rest. */
DECL|function|smp_init
r_static
r_void
id|__init
id|smp_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Get other processors into their bootup holding patterns. */
id|smp_boot_cpus
c_func
(paren
)paren
suffix:semicolon
id|smp_threads_ready
op_assign
l_int|1
suffix:semicolon
id|smp_commence
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; *&t;Activate the first processor.&n; */
DECL|function|start_kernel
id|asmlinkage
r_void
id|__init
id|start_kernel
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|command_line
suffix:semicolon
r_int
r_int
id|mempages
suffix:semicolon
r_extern
r_char
id|saved_command_line
(braket
)braket
suffix:semicolon
multiline_comment|/*&n; * Interrupts are still disabled. Do necessary setups, then&n; * enable them&n; */
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|linux_banner
)paren
suffix:semicolon
id|setup_arch
c_func
(paren
op_amp
id|command_line
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Kernel command line: %s&bslash;n&quot;
comma
id|saved_command_line
)paren
suffix:semicolon
id|parse_options
c_func
(paren
id|command_line
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
id|time_init
c_func
(paren
)paren
suffix:semicolon
id|softirq_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * HACK ALERT! This is early. We&squot;re enabling the console before&n;&t; * we&squot;ve done PCI setups etc, and console_init() must be aware of&n;&t; * this. But we do want output early, in case something goes wrong.&n;&t; */
id|console_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MODULES
id|init_modules
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|prof_shift
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* only text is profiled */
id|prof_len
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
(paren
r_int
r_int
)paren
op_amp
id|_stext
suffix:semicolon
id|prof_len
op_rshift_assign
id|prof_shift
suffix:semicolon
id|size
op_assign
id|prof_len
op_star
r_sizeof
(paren
r_int
r_int
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
suffix:semicolon
id|prof_buffer
op_assign
(paren
r_int
r_int
op_star
)paren
id|alloc_bootmem
c_func
(paren
id|size
)paren
suffix:semicolon
)brace
id|kmem_cache_init
c_func
(paren
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
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|initrd_start
op_logical_and
op_logical_neg
id|initrd_below_start_ok
op_logical_and
id|initrd_start
OL
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;initrd overwritten (0x%08lx &lt; 0x%08lx) - &quot;
l_string|&quot;disabling it.&bslash;n&quot;
comma
id|initrd_start
comma
id|min_low_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
macro_line|#endif
id|mem_init
c_func
(paren
)paren
suffix:semicolon
id|kmem_cache_sizes_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_3215_CONSOLE
id|con3215_activate
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PROC_FS
id|proc_root_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|mempages
op_assign
id|num_physpages
suffix:semicolon
id|fork_init
c_func
(paren
id|mempages
)paren
suffix:semicolon
id|proc_caches_init
c_func
(paren
)paren
suffix:semicolon
id|vfs_caches_init
c_func
(paren
id|mempages
)paren
suffix:semicolon
id|buffer_init
c_func
(paren
id|mempages
)paren
suffix:semicolon
id|page_cache_init
c_func
(paren
id|mempages
)paren
suffix:semicolon
id|kiobuf_setup
c_func
(paren
)paren
suffix:semicolon
id|signals_init
c_func
(paren
)paren
suffix:semicolon
id|bdev_init
c_func
(paren
)paren
suffix:semicolon
id|inode_init
c_func
(paren
id|mempages
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_SYSVIPC)
id|ipc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_QUOTA)
id|dquot_init_hash
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|check_bugs
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;POSIX conformance testing by UNIFIX&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* &n;&t; *&t;We count on the initial thread going ok &n;&t; *&t;Like idlers init is an unlocked kernel thread, which will&n;&t; *&t;make syscalls (and thus be locked).&n;&t; */
id|smp_init
c_func
(paren
)paren
suffix:semicolon
id|kernel_thread
c_func
(paren
id|init
comma
l_int|NULL
comma
id|CLONE_FS
op_or
id|CLONE_FILES
op_or
id|CLONE_SIGNAL
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;need_resched
op_assign
l_int|1
suffix:semicolon
id|cpu_idle
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
DECL|function|do_linuxrc
r_static
r_int
id|do_linuxrc
c_func
(paren
r_void
op_star
id|shell
)paren
(brace
r_static
r_char
op_star
id|argv
(braket
)braket
op_assign
(brace
l_string|&quot;linuxrc&quot;
comma
l_int|NULL
comma
)brace
suffix:semicolon
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
l_string|&quot;/dev/console&quot;
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
r_return
id|execve
c_func
(paren
id|shell
comma
id|argv
comma
id|envp_init
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|variable|child_reaper
r_struct
id|task_struct
op_star
id|child_reaper
op_assign
op_amp
id|init_task
suffix:semicolon
DECL|function|do_initcalls
r_static
r_void
id|__init
id|do_initcalls
c_func
(paren
r_void
)paren
(brace
id|initcall_t
op_star
id|call
suffix:semicolon
id|call
op_assign
op_amp
id|__initcall_start
suffix:semicolon
r_do
(brace
(paren
op_star
id|call
)paren
(paren
)paren
suffix:semicolon
id|call
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|call
OL
op_amp
id|__initcall_end
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Ok, the machine is now initialized. None of the devices&n; * have been touched yet, but the CPU subsystem is up and&n; * running, and memory and process management works.&n; *&n; * Now we can finally start doing some real work..&n; */
DECL|function|do_basic_setup
r_static
r_void
id|__init
id|do_basic_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_int
id|real_root_mountflags
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Tell the world that we&squot;re going to be the grim&n;&t; * reaper of innocent orphaned children.&n;&t; *&n;&t; * We don&squot;t want people to have to make incorrect&n;&t; * assumptions about where in the task array this&n;&t; * can be found.&n;&t; */
id|child_reaper
op_assign
id|current
suffix:semicolon
macro_line|#if defined(CONFIG_MTRR)&t;/* Do this after SMP initialization */
multiline_comment|/*&n; * We should probably create some architecture-dependent &quot;fixup after&n; * everything is up&quot; style function where this would belong better&n; * than in init/main.c..&n; */
id|mtrr_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SYSCTL
id|sysctl_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Ok, at this point all CPU&squot;s should be initialized, so&n;&t; * we can start looking into devices..&n;&t; */
macro_line|#ifdef CONFIG_PCI
id|pci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SBUS
id|sbus_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_PPC)
id|ppc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
id|mca_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_ACORN
id|ecard_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ZORRO
id|zorro_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DIO
id|dio_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MAC
id|nubus_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ISAPNP
id|isapnp_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_TC
id|tc_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Networking initialization needs a process context */
id|sock_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|real_root_dev
op_assign
id|ROOT_DEV
suffix:semicolon
id|real_root_mountflags
op_assign
id|root_mountflags
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
op_logical_and
id|mount_initrd
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
r_else
id|mount_initrd
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
id|do_initcalls
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* .. filesystems .. */
id|filesystem_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRDA
id|irda_device_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Must be done after protocol initialization */
macro_line|#endif
macro_line|#ifdef CONFIG_PCMCIA
id|init_pcmcia_ds
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do this last */
macro_line|#endif
multiline_comment|/* Mount the root filesystem.. */
id|mount_root
c_func
(paren
)paren
suffix:semicolon
id|mount_devfs_fs
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|root_mountflags
op_assign
id|real_root_mountflags
suffix:semicolon
r_if
c_cond
(paren
id|mount_initrd
op_logical_and
id|ROOT_DEV
op_ne
id|real_root_dev
op_logical_and
id|MAJOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
id|RAMDISK_MAJOR
op_logical_and
id|MINOR
c_func
(paren
id|ROOT_DEV
)paren
op_eq
l_int|0
)paren
(brace
r_int
id|error
suffix:semicolon
r_int
id|i
comma
id|pid
suffix:semicolon
id|pid
op_assign
id|kernel_thread
c_func
(paren
id|do_linuxrc
comma
l_string|&quot;/linuxrc&quot;
comma
id|SIGCHLD
)paren
suffix:semicolon
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
suffix:semicolon
r_if
c_cond
(paren
id|MAJOR
c_func
(paren
id|real_root_dev
)paren
op_ne
id|RAMDISK_MAJOR
op_logical_or
id|MINOR
c_func
(paren
id|real_root_dev
)paren
op_ne
l_int|0
)paren
(brace
id|error
op_assign
id|change_root
c_func
(paren
id|real_root_dev
comma
l_string|&quot;/initrd&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Change root to /initrd: &quot;
l_string|&quot;error %d&bslash;n&quot;
comma
id|error
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|function|init
r_static
r_int
id|init
c_func
(paren
r_void
op_star
id|unused
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|do_basic_setup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Ok, we have completed the initial bootup, and&n;&t; * we&squot;re essentially up and running. Get rid of the&n;&t; * initmem segments and start the user-mode stuff..&n;&t; */
id|free_initmem
c_func
(paren
)paren
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|open
c_func
(paren
l_string|&quot;/dev/console&quot;
comma
id|O_RDWR
comma
l_int|0
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: unable to open an initial console.&bslash;n&quot;
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
multiline_comment|/*&n;&t; * We try each of these until one succeeds.&n;&t; *&n;&t; * The Bourne shell can be used instead of init if we are &n;&t; * trying to recover a really broken machine.&n;&t; */
r_if
c_cond
(paren
id|execute_command
)paren
id|execve
c_func
(paren
id|execute_command
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
l_string|&quot;/bin/sh&quot;
comma
id|argv_init
comma
id|envp_init
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;No init found.  Try passing init= option to kernel.&quot;
)paren
suffix:semicolon
)brace
eof
