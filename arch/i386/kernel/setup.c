multiline_comment|/*&n; *  linux/arch/i386/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of initialization&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_APM
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * Tell us the machine setup..&n; */
DECL|variable|hard_math
r_char
id|hard_math
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set by kernel/head.S */
DECL|variable|x86
r_char
id|x86
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set by kernel/head.S to 3..6 */
DECL|variable|x86_model
r_char
id|x86_model
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set by kernel/head.S */
DECL|variable|x86_mask
r_char
id|x86_mask
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set by kernel/head.S */
DECL|variable|x86_capability
r_int
id|x86_capability
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set by kernel/head.S */
DECL|variable|fdiv_bug
r_int
id|fdiv_bug
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set if Pentium(TM) with FP bug */
DECL|variable|have_cpuid
r_int
id|have_cpuid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set if CPUID instruction works */
DECL|variable|x86_vendor_id
r_char
id|x86_vendor_id
(braket
l_int|13
)braket
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
DECL|variable|ignore_irq13
r_char
id|ignore_irq13
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set if exception 16 works */
DECL|variable|wp_works_ok
r_char
id|wp_works_ok
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* set if paging hardware honours WP */
DECL|variable|hlt_works_ok
r_char
id|hlt_works_ok
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* set if the &quot;hlt&quot; instruction works */
multiline_comment|/*&n; * Bus types ..&n; */
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
DECL|variable|MCA_bus
r_int
id|MCA_bus
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* for MCA, but anyone else can use it if they want */
DECL|variable|machine_id
r_int
r_int
id|machine_id
op_assign
l_int|0
suffix:semicolon
DECL|variable|machine_submodel_id
r_int
r_int
id|machine_submodel_id
op_assign
l_int|0
suffix:semicolon
DECL|variable|BIOS_revision
r_int
r_int
id|BIOS_revision
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Setup options&n; */
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
macro_line|#ifdef CONFIG_APM
DECL|variable|apm_bios_info
r_struct
id|apm_bios_info
id|apm_bios_info
suffix:semicolon
macro_line|#endif
DECL|struct|sys_desc_table_struct
r_struct
id|sys_desc_table_struct
(brace
DECL|member|length
r_int
r_int
id|length
suffix:semicolon
DECL|member|table
r_int
r_char
id|table
(braket
l_int|0
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
multiline_comment|/* 1 = load ramdisk, 0 = don&squot;t load */
r_extern
r_int
id|rd_prompt
suffix:semicolon
multiline_comment|/* 1 = prompt for ramdisk, 0 = don&squot;t prompt */
r_extern
r_int
id|rd_image_start
suffix:semicolon
multiline_comment|/* starting block # of image */
macro_line|#endif
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_int
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
r_extern
r_char
id|empty_zero_page
(braket
id|PAGE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;empty_zero_page
DECL|macro|EXT_MEM_K
mdefine_line|#define EXT_MEM_K (*(unsigned short *) (PARAM+2))
macro_line|#ifdef CONFIG_APM
DECL|macro|APM_BIOS_INFO
mdefine_line|#define APM_BIOS_INFO (*(struct apm_bios_info *) (PARAM+64))
macro_line|#endif
DECL|macro|DRIVE_INFO
mdefine_line|#define DRIVE_INFO (*(struct drive_info_struct *) (PARAM+0x80))
DECL|macro|SCREEN_INFO
mdefine_line|#define SCREEN_INFO (*(struct screen_info *) (PARAM+0))
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned short *) (PARAM+0x1F2))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS (*(unsigned short *) (PARAM+0x1F8))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned short *) (PARAM+0x1FC))
DECL|macro|AUX_DEVICE_INFO
mdefine_line|#define AUX_DEVICE_INFO (*(unsigned char *) (PARAM+0x1FF))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned char *) (PARAM+0x210))
DECL|macro|KERNEL_START
mdefine_line|#define KERNEL_START (*(unsigned long *) (PARAM+0x214))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x218))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x21c))
DECL|macro|SYS_DESC_TABLE
mdefine_line|#define SYS_DESC_TABLE (*(struct sys_desc_table_struct*)(PARAM+0x220))
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE ((char *) (PARAM+2048))
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 256
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK  &t;0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;0x4000&t;
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
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
comma
r_int
r_int
op_star
id|memory_start_p
comma
r_int
r_int
op_star
id|memory_end_p
)paren
)paren
(brace
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
r_char
id|c
op_assign
l_char|&squot; &squot;
comma
op_star
id|to
op_assign
id|command_line
comma
op_star
id|from
op_assign
id|COMMAND_LINE
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_static
r_int
r_char
id|smptrap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|smptrap
op_eq
l_int|1
)paren
(brace
r_return
suffix:semicolon
)brace
id|smptrap
op_assign
l_int|1
suffix:semicolon
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
id|ORIG_ROOT_DEV
)paren
suffix:semicolon
id|drive_info
op_assign
id|DRIVE_INFO
suffix:semicolon
id|screen_info
op_assign
id|SCREEN_INFO
suffix:semicolon
macro_line|#ifdef CONFIG_APM
id|apm_bios_info
op_assign
id|APM_BIOS_INFO
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|SYS_DESC_TABLE.length
op_ne
l_int|0
)paren
(brace
id|MCA_bus
op_assign
id|SYS_DESC_TABLE.table
(braket
l_int|3
)braket
op_amp
l_int|0x2
suffix:semicolon
id|machine_id
op_assign
id|SYS_DESC_TABLE.table
(braket
l_int|0
)braket
suffix:semicolon
id|machine_submodel_id
op_assign
id|SYS_DESC_TABLE.table
(braket
l_int|1
)braket
suffix:semicolon
id|BIOS_revision
op_assign
id|SYS_DESC_TABLE.table
(braket
l_int|2
)braket
suffix:semicolon
)brace
id|aux_device_present
op_assign
id|AUX_DEVICE_INFO
suffix:semicolon
macro_line|#ifdef STANDARD_MEMORY_BIOS_CALL
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
macro_line|#else
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
op_star
l_int|64L
op_star
l_int|1024L
)paren
suffix:semicolon
multiline_comment|/* 64kb chunks */
macro_line|#endif
id|memory_end
op_and_assign
id|PAGE_MASK
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
id|rd_image_start
op_assign
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_PROMPT_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
id|rd_doload
op_assign
(paren
(paren
id|RAMDISK_FLAGS
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|MOUNT_ROOT_RDONLY
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
id|init_task.mm-&gt;start_code
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|init_task.mm-&gt;end_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|init_task.mm-&gt;end_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
suffix:semicolon
id|init_task.mm-&gt;brk
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
multiline_comment|/* Save unparsed command line copy for /proc/cmdline */
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|COMMAND_LINE
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
multiline_comment|/*&n;&t;&t; * &quot;mem=nopentium&quot; disables the 4MB page tables.&n;&t;&t; * &quot;mem=XXX[kKmM]&quot; overrides the BIOS-reported&n;&t;&t; * memory size&n;&t;&t; */
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot; &squot;
op_logical_and
op_star
(paren
r_const
r_int
r_int
op_star
)paren
id|from
op_eq
op_star
(paren
r_const
r_int
r_int
op_star
)paren
l_string|&quot;mem=&quot;
)paren
(brace
r_if
c_cond
(paren
id|to
op_ne
id|command_line
)paren
id|to
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|from
op_plus
l_int|4
comma
l_string|&quot;nopentium&quot;
comma
l_int|9
)paren
)paren
(brace
id|from
op_add_assign
l_int|9
op_plus
l_int|4
suffix:semicolon
id|x86_capability
op_and_assign
op_complement
l_int|8
suffix:semicolon
)brace
r_else
(brace
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
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|10
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|from
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|memory_end
op_assign
id|memory_end
op_lshift
l_int|20
suffix:semicolon
id|from
op_increment
suffix:semicolon
)brace
)brace
)brace
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
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
id|memory_end
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
op_star
id|memory_start_p
op_assign
id|memory_start
suffix:semicolon
op_star
id|memory_end_p
op_assign
id|memory_end
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|LOADER_TYPE
)paren
(brace
id|initrd_start
op_assign
id|INITRD_START
ques
c_cond
id|INITRD_START
op_plus
id|PAGE_OFFSET
suffix:colon
l_int|0
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|INITRD_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|initrd_end
OG
id|memory_end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
id|memory_end
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
macro_line|#endif
multiline_comment|/* request io space for devices used on all i[345]86 PC&squot;S */
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xf0
comma
l_int|0x10
comma
l_string|&quot;fpu&quot;
)paren
suffix:semicolon
)brace
DECL|function|i486model
r_static
r_const
r_char
op_star
id|i486model
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_static
r_const
r_char
op_star
id|model
(braket
)braket
op_assign
(brace
l_string|&quot;0&quot;
comma
l_string|&quot;DX&quot;
comma
l_string|&quot;SX&quot;
comma
l_string|&quot;DX/2&quot;
comma
l_string|&quot;4&quot;
comma
l_string|&quot;SX/2&quot;
comma
l_string|&quot;6&quot;
comma
l_string|&quot;DX/2-WB&quot;
comma
l_string|&quot;DX/4&quot;
comma
l_string|&quot;DX/4-WB&quot;
comma
l_string|&quot;10&quot;
comma
l_string|&quot;11&quot;
comma
l_string|&quot;12&quot;
comma
l_string|&quot;13&quot;
comma
l_string|&quot;Am5x86-WT&quot;
comma
l_string|&quot;Am5x86-WB&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
r_sizeof
(paren
id|model
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
id|model
(braket
id|nr
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|i586model
r_static
r_const
r_char
op_star
id|i586model
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_static
r_const
r_char
op_star
id|model
(braket
)braket
op_assign
(brace
l_string|&quot;0&quot;
comma
l_string|&quot;Pentium 60/66&quot;
comma
l_string|&quot;Pentium 75+&quot;
comma
l_string|&quot;OverDrive PODP5V83&quot;
comma
l_string|&quot;Pentium MMX&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
r_sizeof
(paren
id|model
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
id|model
(braket
id|nr
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|i686model
r_static
r_const
r_char
op_star
id|i686model
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_static
r_const
r_char
op_star
id|model
(braket
)braket
op_assign
(brace
l_string|&quot;PPro A-step&quot;
comma
l_string|&quot;Pentium Pro&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;Pentium II&quot;
)brace
suffix:semicolon
r_if
c_cond
(paren
id|nr
OL
r_sizeof
(paren
id|model
)paren
op_div
r_sizeof
(paren
r_char
op_star
)paren
)paren
r_return
id|model
(braket
id|nr
)braket
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|getmodel
r_static
r_const
r_char
op_star
id|getmodel
c_func
(paren
r_int
id|x86
comma
r_int
id|model
)paren
(brace
r_const
r_char
op_star
id|p
op_assign
l_int|NULL
suffix:semicolon
r_static
r_char
id|nbuf
(braket
l_int|12
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|x86
)paren
(brace
r_case
l_int|4
suffix:colon
id|p
op_assign
id|i486model
c_func
(paren
id|model
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|p
op_assign
id|i586model
c_func
(paren
id|model
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|p
op_assign
id|i686model
c_func
(paren
id|model
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|p
)paren
r_return
id|p
suffix:semicolon
id|sprintf
c_func
(paren
id|nbuf
comma
l_string|&quot;%d&quot;
comma
id|model
)paren
suffix:semicolon
r_return
id|nbuf
suffix:semicolon
)brace
DECL|function|get_cpuinfo
r_int
id|get_cpuinfo
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
op_assign
l_int|0
suffix:semicolon
r_int
id|sep_bug
suffix:semicolon
r_static
r_const
r_char
op_star
id|x86_cap_flags
(braket
)braket
op_assign
(brace
l_string|&quot;fpu&quot;
comma
l_string|&quot;vme&quot;
comma
l_string|&quot;de&quot;
comma
l_string|&quot;pse&quot;
comma
l_string|&quot;tsc&quot;
comma
l_string|&quot;msr&quot;
comma
l_string|&quot;pae&quot;
comma
l_string|&quot;mce&quot;
comma
l_string|&quot;cx8&quot;
comma
l_string|&quot;apic&quot;
comma
l_string|&quot;10&quot;
comma
l_string|&quot;sep&quot;
comma
l_string|&quot;mtrr&quot;
comma
l_string|&quot;pge&quot;
comma
l_string|&quot;mca&quot;
comma
l_string|&quot;cmov&quot;
comma
l_string|&quot;16&quot;
comma
l_string|&quot;17&quot;
comma
l_string|&quot;18&quot;
comma
l_string|&quot;19&quot;
comma
l_string|&quot;20&quot;
comma
l_string|&quot;21&quot;
comma
l_string|&quot;22&quot;
comma
l_string|&quot;mmx&quot;
comma
l_string|&quot;24&quot;
comma
l_string|&quot;25&quot;
comma
l_string|&quot;26&quot;
comma
l_string|&quot;27&quot;
comma
l_string|&quot;28&quot;
comma
l_string|&quot;29&quot;
comma
l_string|&quot;30&quot;
comma
l_string|&quot;31&quot;
)brace
suffix:semicolon
macro_line|#ifdef __SMP__
r_int
id|n
suffix:semicolon
DECL|macro|CD
mdefine_line|#define CD(X)&t;&t;(cpu_data[n].X)
multiline_comment|/* SMP has the wrong name for loops_per_sec */
DECL|macro|loops_per_sec
mdefine_line|#define loops_per_sec&t;udelay_val
DECL|macro|CPUN
mdefine_line|#define CPUN n
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
l_int|32
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_present_map
op_amp
(paren
l_int|1
op_lshift
id|n
)paren
)paren
(brace
r_if
c_cond
(paren
id|len
)paren
id|buffer
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
macro_line|#else
mdefine_line|#define CD(X) (X)
mdefine_line|#define CPUN 0
macro_line|#endif
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
l_string|&quot;cpu&bslash;t&bslash;t: %c86&bslash;n&quot;
l_string|&quot;model&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;vendor_id&bslash;t: %s&bslash;n&quot;
comma
id|CPUN
comma
id|CD
c_func
(paren
id|x86
)paren
op_plus
l_char|&squot;0&squot;
comma
id|CD
c_func
(paren
id|have_cpuid
)paren
ques
c_cond
id|getmodel
c_func
(paren
id|CD
c_func
(paren
id|x86
)paren
comma
id|CD
c_func
(paren
id|x86_model
)paren
)paren
suffix:colon
l_string|&quot;unknown&quot;
comma
id|CD
c_func
(paren
id|x86_vendor_id
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|CD
c_func
(paren
id|x86_mask
)paren
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
l_string|&quot;stepping&bslash;t: %d&bslash;n&quot;
comma
id|CD
c_func
(paren
id|x86_mask
)paren
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;stepping&bslash;t: unknown&bslash;n&quot;
)paren
suffix:semicolon
id|sep_bug
op_assign
id|CD
c_func
(paren
id|have_cpuid
)paren
op_logical_and
(paren
id|CD
c_func
(paren
id|x86_capability
)paren
op_amp
l_int|0x800
)paren
op_logical_and
op_logical_neg
id|memcmp
c_func
(paren
id|x86_vendor_id
comma
l_string|&quot;GenuineIntel&quot;
comma
l_int|12
)paren
op_logical_and
id|CD
c_func
(paren
id|x86
)paren
op_eq
l_int|6
op_logical_and
id|CD
c_func
(paren
id|x86_model
)paren
OL
l_int|3
op_logical_and
id|CD
c_func
(paren
id|x86_mask
)paren
OL
l_int|3
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
l_string|&quot;fdiv_bug&bslash;t: %s&bslash;n&quot;
l_string|&quot;hlt_bug&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;sep_bug&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu_exception&bslash;t: %s&bslash;n&quot;
l_string|&quot;cpuid&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;wp&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;flags&bslash;t&bslash;t:&quot;
comma
id|CD
c_func
(paren
id|fdiv_bug
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|CD
c_func
(paren
id|hlt_works_ok
)paren
ques
c_cond
l_string|&quot;no&quot;
suffix:colon
l_string|&quot;yes&quot;
comma
id|sep_bug
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|CD
c_func
(paren
id|hard_math
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
(paren
id|CD
c_func
(paren
id|hard_math
)paren
op_logical_and
id|ignore_irq13
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|CD
c_func
(paren
id|have_cpuid
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
comma
id|CD
c_func
(paren
id|wp_works_ok
)paren
ques
c_cond
l_string|&quot;yes&quot;
suffix:colon
l_string|&quot;no&quot;
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
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|CD
c_func
(paren
id|x86_capability
)paren
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot; %s&quot;
comma
id|x86_cap_flags
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|len
comma
l_string|&quot;&bslash;nbogomips&bslash;t: %lu.%02lu&bslash;n&quot;
comma
id|CD
c_func
(paren
id|loops_per_sec
op_plus
l_int|2500
)paren
op_div
l_int|500000
comma
(paren
id|CD
c_func
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
macro_line|#ifdef __SMP__
)brace
)brace
macro_line|#endif
r_return
id|len
suffix:semicolon
)brace
eof
