multiline_comment|/*&n; *  linux/arch/arm/kernel/setup.c&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; */
multiline_comment|/*&n; * This file obtains various parameters about the system that the kernel&n; * is running on.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/procinfo.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#ifndef MEM_SIZE
DECL|macro|MEM_SIZE
mdefine_line|#define MEM_SIZE&t;(16*1024*1024)
macro_line|#endif
macro_line|#ifndef CONFIG_CMDLINE
DECL|macro|CONFIG_CMDLINE
mdefine_line|#define CONFIG_CMDLINE &quot;&quot;
macro_line|#endif
macro_line|#ifndef PARAMS_BASE
DECL|macro|PARAMS_BASE
mdefine_line|#define PARAMS_BASE NULL
macro_line|#endif
r_extern
r_void
id|reboot_setup
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
id|disable_hlt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_int
id|_stext
comma
id|_text
comma
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
DECL|variable|processor_id
r_int
r_int
id|processor_id
suffix:semicolon
DECL|variable|__machine_arch_type
r_int
r_int
id|__machine_arch_type
suffix:semicolon
DECL|variable|vram_size
r_int
r_int
id|vram_size
suffix:semicolon
DECL|variable|system_rev
r_int
r_int
id|system_rev
suffix:semicolon
DECL|variable|system_serial_low
r_int
r_int
id|system_serial_low
suffix:semicolon
DECL|variable|system_serial_high
r_int
r_int
id|system_serial_high
suffix:semicolon
DECL|variable|elf_hwcap
r_int
r_int
id|elf_hwcap
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_ACORN
DECL|variable|memc_ctrl_reg
r_int
r_int
id|memc_ctrl_reg
suffix:semicolon
DECL|variable|number_mfm_drives
r_int
r_int
id|number_mfm_drives
suffix:semicolon
macro_line|#endif
DECL|variable|meminfo
r_struct
id|meminfo
id|meminfo
suffix:semicolon
macro_line|#ifdef MULTI_CPU
DECL|variable|processor
r_struct
id|processor
id|processor
suffix:semicolon
macro_line|#endif
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
op_assign
(brace
id|orig_video_lines
suffix:colon
l_int|30
comma
id|orig_video_cols
suffix:colon
l_int|80
comma
id|orig_video_mode
suffix:colon
l_int|0
comma
id|orig_video_ega_bx
suffix:colon
l_int|0
comma
id|orig_video_isVGA
suffix:colon
l_int|1
comma
id|orig_video_points
suffix:colon
l_int|8
)brace
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
DECL|variable|elf_platform
r_char
id|elf_platform
(braket
id|ELF_PLATFORM_SIZE
)braket
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
DECL|variable|proc_info
r_static
r_struct
id|proc_info_item
id|proc_info
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
DECL|variable|__initdata
r_static
r_char
id|default_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
id|__initdata
op_assign
id|CONFIG_CMDLINE
suffix:semicolon
DECL|member|c
DECL|member|l
DECL|variable|__initdata
r_static
r_union
(brace
r_char
id|c
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_int
id|l
suffix:semicolon
)brace
id|endian_test
id|__initdata
op_assign
(brace
(brace
l_char|&squot;l&squot;
comma
l_char|&squot;?&squot;
comma
l_char|&squot;?&squot;
comma
l_char|&squot;b&squot;
)brace
)brace
suffix:semicolon
DECL|macro|ENDIANNESS
mdefine_line|#define ENDIANNESS ((char)endian_test.l)
multiline_comment|/*&n; * Standard memory resources&n; */
DECL|variable|mem_res
r_static
r_struct
id|resource
id|mem_res
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;System RAM&quot;
comma
l_int|0
comma
l_int|0
comma
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;Video RAM&quot;
comma
l_int|0
comma
l_int|0
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Kernel code&quot;
comma
l_int|0
comma
l_int|0
comma
id|IORESOURCE_MEM
)brace
comma
(brace
l_string|&quot;Kernel data&quot;
comma
l_int|0
comma
l_int|0
comma
id|IORESOURCE_MEM
)brace
)brace
suffix:semicolon
DECL|macro|system_ram
mdefine_line|#define system_ram  mem_res[0]
DECL|macro|video_ram
mdefine_line|#define video_ram   mem_res[1]
DECL|macro|kernel_code
mdefine_line|#define kernel_code mem_res[2]
DECL|macro|kernel_data
mdefine_line|#define kernel_data mem_res[3]
DECL|variable|io_res
r_static
r_struct
id|resource
id|io_res
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;reserved&quot;
comma
l_int|0x3bc
comma
l_int|0x3be
comma
id|IORESOURCE_IO
op_or
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;reserved&quot;
comma
l_int|0x378
comma
l_int|0x37f
comma
id|IORESOURCE_IO
op_or
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;reserved&quot;
comma
l_int|0x278
comma
l_int|0x27f
comma
id|IORESOURCE_IO
op_or
id|IORESOURCE_BUSY
)brace
)brace
suffix:semicolon
DECL|macro|lp0
mdefine_line|#define lp0 io_res[0]
DECL|macro|lp1
mdefine_line|#define lp1 io_res[1]
DECL|macro|lp2
mdefine_line|#define lp2 io_res[2]
DECL|function|setup_processor
r_static
r_void
id|__init
id|setup_processor
c_func
(paren
r_void
)paren
(brace
r_extern
r_struct
id|proc_info_list
id|__proc_info_begin
comma
id|__proc_info_end
suffix:semicolon
r_struct
id|proc_info_list
op_star
id|list
suffix:semicolon
multiline_comment|/*&n;&t; * locate processor in the list of supported processor&n;&t; * types.  The linker builds this table for us from the&n;&t; * entries in arch/arm/mm/proc-*.S&n;&t; */
r_for
c_loop
(paren
id|list
op_assign
op_amp
id|__proc_info_begin
suffix:semicolon
id|list
OL
op_amp
id|__proc_info_end
suffix:semicolon
id|list
op_increment
)paren
r_if
c_cond
(paren
(paren
id|processor_id
op_amp
id|list-&gt;cpu_mask
)paren
op_eq
id|list-&gt;cpu_val
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * If processor type is unrecognised, then we&n;&t; * can do nothing...&n;&t; */
r_if
c_cond
(paren
id|list
op_ge
op_amp
id|__proc_info_end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CPU configuration botched (ID %08x), unable &quot;
l_string|&quot;to continue.&bslash;n&quot;
comma
id|processor_id
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|proc_info
op_assign
op_star
id|list-&gt;info
suffix:semicolon
macro_line|#ifdef MULTI_CPU
id|processor
op_assign
op_star
id|list-&gt;proc
suffix:semicolon
macro_line|#endif
id|sprintf
c_func
(paren
id|system_utsname.machine
comma
l_string|&quot;%s%c&quot;
comma
id|list-&gt;arch_name
comma
id|ENDIANNESS
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|elf_platform
comma
l_string|&quot;%s%c&quot;
comma
id|list-&gt;elf_name
comma
id|ENDIANNESS
)paren
suffix:semicolon
id|elf_hwcap
op_assign
id|list-&gt;elf_hwcap
suffix:semicolon
id|cpu_proc_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|memparse
r_static
r_int
r_int
id|__init
id|memparse
c_func
(paren
r_char
op_star
id|ptr
comma
r_char
op_star
op_star
id|retptr
)paren
(brace
r_int
r_int
id|ret
op_assign
id|simple_strtoul
c_func
(paren
id|ptr
comma
id|retptr
comma
l_int|0
)paren
suffix:semicolon
r_switch
c_cond
(paren
op_star
op_star
id|retptr
)paren
(brace
r_case
l_char|&squot;M&squot;
suffix:colon
r_case
l_char|&squot;m&squot;
suffix:colon
id|ret
op_lshift_assign
l_int|10
suffix:semicolon
r_case
l_char|&squot;K&squot;
suffix:colon
r_case
l_char|&squot;k&squot;
suffix:colon
id|ret
op_lshift_assign
l_int|10
suffix:semicolon
(paren
op_star
id|retptr
)paren
op_increment
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n; * Initial parsing of the command line.  We need to pick out the&n; * memory size.  We look for mem=size@start, where start and size&n; * are &quot;size[KkMm]&quot;&n; */
r_static
r_void
id|__init
DECL|function|parse_cmdline
id|parse_cmdline
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
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
comma
op_star
id|to
op_assign
id|command_line
suffix:semicolon
r_int
id|usermem
op_assign
l_int|0
comma
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
op_logical_neg
id|memcmp
c_func
(paren
id|from
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
)paren
(brace
r_int
r_int
id|size
comma
id|start
suffix:semicolon
r_if
c_cond
(paren
id|to
op_ne
id|command_line
)paren
id|to
op_sub_assign
l_int|1
suffix:semicolon
multiline_comment|/* If the user specifies memory size, we&n;&t;&t;&t; * blow away any automatically generated&n;&t;&t;&t; * size.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|usermem
op_eq
l_int|0
)paren
(brace
id|usermem
op_assign
l_int|1
suffix:semicolon
id|meminfo.nr_banks
op_assign
l_int|0
suffix:semicolon
)brace
id|start
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
id|memparse
c_func
(paren
id|from
op_plus
l_int|4
comma
op_amp
id|from
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|from
op_eq
l_char|&squot;@&squot;
)paren
id|start
op_assign
id|memparse
c_func
(paren
id|from
op_plus
l_int|1
comma
op_amp
id|from
)paren
suffix:semicolon
id|meminfo.bank
(braket
id|meminfo.nr_banks
)braket
dot
id|start
op_assign
id|start
suffix:semicolon
id|meminfo.bank
(braket
id|meminfo.nr_banks
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|meminfo.nr_banks
op_add_assign
l_int|1
suffix:semicolon
)brace
id|c
op_assign
op_star
id|from
op_increment
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
id|to
op_increment
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
)brace
r_static
r_void
id|__init
DECL|function|setup_ramdisk
id|setup_ramdisk
c_func
(paren
r_int
id|doload
comma
r_int
id|prompt
comma
r_int
id|image_start
comma
r_int
r_int
id|rd_sz
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_RAM
r_extern
r_int
id|rd_doload
suffix:semicolon
r_extern
r_int
id|rd_prompt
suffix:semicolon
r_extern
r_int
id|rd_image_start
suffix:semicolon
r_extern
r_int
id|rd_size
suffix:semicolon
id|rd_image_start
op_assign
id|image_start
suffix:semicolon
id|rd_prompt
op_assign
id|prompt
suffix:semicolon
id|rd_doload
op_assign
id|doload
suffix:semicolon
r_if
c_cond
(paren
id|rd_sz
)paren
id|rd_size
op_assign
id|rd_sz
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * initial ram disk&n; */
DECL|function|setup_initrd
r_static
r_void
id|__init
id|setup_initrd
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|size
)paren
(brace
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|start
op_eq
l_int|0
)paren
id|size
op_assign
l_int|0
suffix:semicolon
id|initrd_start
op_assign
id|start
suffix:semicolon
id|initrd_end
op_assign
id|start
op_plus
id|size
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Work out our memory regions.  Note that &quot;pfn&quot; is the physical page number&n; * relative to the first physical page, not the physical address itself.&n; */
DECL|function|setup_bootmem
r_static
r_void
id|__init
id|setup_bootmem
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|end_pfn
comma
id|bootmem_end
suffix:semicolon
r_int
id|bank
suffix:semicolon
multiline_comment|/*&n;&t; * Calculate the end of memory.&n;&t; */
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
id|meminfo.nr_banks
suffix:semicolon
id|bank
op_increment
)paren
(brace
r_if
c_cond
(paren
id|meminfo.bank
(braket
id|bank
)braket
dot
id|size
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
id|end
op_assign
id|meminfo.bank
(braket
id|bank
)braket
dot
id|start
op_plus
id|meminfo.bank
(braket
id|bank
)braket
dot
id|size
suffix:semicolon
r_if
c_cond
(paren
id|meminfo.end
OL
id|end
)paren
id|meminfo.end
op_assign
id|end
suffix:semicolon
)brace
)brace
id|bootmem_end
op_assign
id|__pa
c_func
(paren
id|PAGE_ALIGN
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
id|end_pfn
op_assign
id|meminfo.end
op_rshift
id|PAGE_SHIFT
suffix:semicolon
multiline_comment|/*&n;&t; * Initialise the boot-time allocator&n;&t; */
id|bootmem_end
op_add_assign
id|init_bootmem
c_func
(paren
id|bootmem_end
op_rshift
id|PAGE_SHIFT
comma
id|end_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register all available RAM with the bootmem allocator.&n;&t; * The address is relative to the start of physical memory.&n;&t; */
r_for
c_loop
(paren
id|bank
op_assign
l_int|0
suffix:semicolon
id|bank
OL
id|meminfo.nr_banks
suffix:semicolon
id|bank
op_increment
)paren
id|free_bootmem
c_func
(paren
id|meminfo.bank
(braket
id|bank
)braket
dot
id|start
comma
id|meminfo.bank
(braket
id|bank
)braket
dot
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * reserve the following regions:&n;&t; *  physical page 0 - it contains the exception vectors&n;&t; *  kernel and the bootmem structure&n;&t; *  swapper page directory (if any)&n;&t; *  initrd (if any)&n;&t; */
id|reserve_bootmem
c_func
(paren
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_32
id|reserve_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
comma
id|PTRS_PER_PGD
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
macro_line|#endif
id|reserve_bootmem
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|_stext
)paren
comma
id|bootmem_end
op_minus
id|__pa
c_func
(paren
op_amp
id|_stext
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|__pa
c_func
(paren
id|initrd_end
)paren
OG
(paren
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%08lx &gt; 0x%08x) - disabling initrd&bslash;n&quot;
comma
id|__pa
c_func
(paren
id|initrd_end
)paren
comma
id|end_pfn
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|initrd_start
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|initrd_start
)paren
id|reserve_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|initrd_start
)paren
comma
id|initrd_end
op_minus
id|initrd_start
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|function|request_standard_resources
r_static
r_void
id|__init
id|request_standard_resources
c_func
(paren
r_void
)paren
(brace
id|kernel_code.start
op_assign
id|__virt_to_bus
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_text
)paren
suffix:semicolon
id|kernel_code.end
op_assign
id|__virt_to_bus
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_etext
op_minus
l_int|1
)paren
suffix:semicolon
id|kernel_data.start
op_assign
id|__virt_to_bus
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_etext
)paren
suffix:semicolon
id|kernel_data.end
op_assign
id|__virt_to_bus
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|_edata
op_minus
l_int|1
)paren
suffix:semicolon
id|system_ram.start
op_assign
id|__virt_to_bus
c_func
(paren
id|PAGE_OFFSET
)paren
suffix:semicolon
id|system_ram.end
op_assign
id|__virt_to_bus
c_func
(paren
id|meminfo.end
op_plus
id|PAGE_OFFSET
op_minus
l_int|1
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|system_ram
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|system_ram
comma
op_amp
id|kernel_code
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|system_ram
comma
op_amp
id|kernel_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|video_ram.start
op_ne
id|video_ram.end
)paren
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
op_amp
id|video_ram
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Some machines don&squot;t have the possibility of ever&n;&t; * possessing LPT1 (lp0) and LPT3 (lp2)&n;&t; */
r_if
c_cond
(paren
id|machine_is_ebsa110
c_func
(paren
)paren
op_logical_or
id|machine_is_riscpc
c_func
(paren
)paren
op_logical_or
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|lp0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_riscpc
c_func
(paren
)paren
)paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|lp1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|machine_is_ebsa110
c_func
(paren
)paren
op_logical_or
id|machine_is_netwinder
c_func
(paren
)paren
)paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|lp2
)paren
suffix:semicolon
)brace
DECL|function|setup_arch
r_void
id|__init
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_struct
id|param_struct
op_star
id|params
op_assign
(paren
r_struct
id|param_struct
op_star
)paren
id|PARAMS_BASE
suffix:semicolon
r_char
op_star
id|from
op_assign
id|default_command_line
suffix:semicolon
macro_line|#if defined(CONFIG_ARCH_ARC)
id|__machine_arch_type
op_assign
id|MACH_TYPE_ARCHIMEDES
suffix:semicolon
macro_line|#elif defined(CONFIG_ARCH_A5K)
id|__machine_arch_type
op_assign
id|MACH_TYPE_A5K
suffix:semicolon
macro_line|#endif
id|setup_processor
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Defaults&n;&t; */
id|ROOT_DEV
op_assign
id|MKDEV
c_func
(paren
l_int|0
comma
l_int|255
)paren
suffix:semicolon
id|setup_ramdisk
c_func
(paren
l_int|1
comma
l_int|1
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Add your machine dependencies here&n;&t; */
r_switch
c_cond
(paren
id|machine_arch_type
)paren
(brace
r_case
id|MACH_TYPE_EBSA110
suffix:colon
multiline_comment|/* EBSA110 locks if we execute &squot;wait for interrupt&squot; */
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|params
op_logical_and
id|params-&gt;u1.s.page_size
op_ne
id|PAGE_SIZE
)paren
id|params
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_ARCH_ACORN
macro_line|#ifdef CONFIG_ARCH_RPC
r_case
id|MACH_TYPE_RISCPC
suffix:colon
multiline_comment|/* RiscPC can&squot;t handle half-word loads and stores */
id|elf_hwcap
op_and_assign
op_complement
id|HWCAP_HALF
suffix:semicolon
r_switch
c_cond
(paren
id|params-&gt;u1.s.pages_in_vram
)paren
(brace
r_case
l_int|512
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_case
l_int|256
suffix:colon
id|vram_size
op_add_assign
id|PAGE_SIZE
op_star
l_int|256
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
(brace
r_int
id|i
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
id|meminfo.bank
(braket
id|i
)braket
dot
id|start
op_assign
id|i
op_lshift
l_int|26
suffix:semicolon
id|meminfo.bank
(braket
id|i
)braket
dot
id|size
op_assign
id|params-&gt;u1.s.pages_in_bank
(braket
id|i
)braket
op_star
id|params-&gt;u1.s.page_size
suffix:semicolon
)brace
id|meminfo.nr_banks
op_assign
l_int|4
suffix:semicolon
)brace
macro_line|#endif
r_case
id|MACH_TYPE_ARCHIMEDES
suffix:colon
r_case
id|MACH_TYPE_A5K
suffix:colon
id|memc_ctrl_reg
op_assign
id|params-&gt;u1.s.memc_control_reg
suffix:semicolon
id|number_mfm_drives
op_assign
(paren
id|params-&gt;u1.s.adfsdrives
op_rshift
l_int|3
)paren
op_amp
l_int|3
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_case
id|MACH_TYPE_EBSA285
suffix:colon
r_if
c_cond
(paren
id|params
)paren
(brace
id|ORIG_X
op_assign
id|params-&gt;u1.s.video_x
suffix:semicolon
id|ORIG_Y
op_assign
id|params-&gt;u1.s.video_y
suffix:semicolon
id|ORIG_VIDEO_COLS
op_assign
id|params-&gt;u1.s.video_num_cols
suffix:semicolon
id|ORIG_VIDEO_LINES
op_assign
id|params-&gt;u1.s.video_num_rows
suffix:semicolon
id|video_ram.start
op_assign
l_int|0x0a0000
suffix:semicolon
id|video_ram.end
op_assign
l_int|0x0bffff
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MACH_TYPE_CO285
suffix:colon
(brace
macro_line|#if 0
r_extern
r_int
r_int
id|boot_memory_end
suffix:semicolon
r_extern
r_char
id|boot_command_line
(braket
)braket
suffix:semicolon
id|from
op_assign
id|boot_command_line
suffix:semicolon
id|memory_end
op_assign
id|boot_memory_end
suffix:semicolon
macro_line|#endif
id|params
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|MACH_TYPE_CATS
suffix:colon
multiline_comment|/* CATS uses soft-reboot by default, since hard reboots&n;&t;&t; * fail on early boards.&n;&t;&t; */
id|reboot_setup
c_func
(paren
l_string|&quot;s&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|params
op_assign
l_int|NULL
suffix:semicolon
id|ORIG_VIDEO_LINES
op_assign
l_int|25
suffix:semicolon
id|ORIG_VIDEO_POINTS
op_assign
l_int|16
suffix:semicolon
id|ORIG_Y
op_assign
l_int|24
suffix:semicolon
id|video_ram.start
op_assign
l_int|0x0a0000
suffix:semicolon
id|video_ram.end
op_assign
l_int|0x0bffff
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MACH_TYPE_NETWINDER
suffix:colon
multiline_comment|/*&n;&t;&t; * to be fixed in a future NeTTrom&n;&t;&t; */
r_if
c_cond
(paren
id|params-&gt;u1.s.page_size
op_eq
id|PAGE_SIZE
)paren
(brace
r_if
c_cond
(paren
id|params-&gt;u1.s.nr_pages
op_ne
l_int|0x2000
op_logical_and
id|params-&gt;u1.s.nr_pages
op_ne
l_int|0x4000
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: bad NeTTrom parameters detected, using defaults&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; * This stuff doesn&squot;t appear to be initialised&n;&t;&t;&t;&t; * properly by NeTTrom 2.0.6 and 2.0.7&n;&t;&t;&t;&t; */
id|params-&gt;u1.s.nr_pages
op_assign
l_int|0x2000
suffix:semicolon
multiline_comment|/* 32MB */
id|params-&gt;u1.s.ramdisk_size
op_assign
l_int|0
suffix:semicolon
id|params-&gt;u1.s.flags
op_assign
id|FLAG_READONLY
suffix:semicolon
id|params-&gt;u1.s.initrd_start
op_assign
l_int|0
suffix:semicolon
id|params-&gt;u1.s.initrd_size
op_assign
l_int|0
suffix:semicolon
id|params-&gt;u1.s.rd_start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: no NeTTrom parameter page detected, using &quot;
l_string|&quot;compiled-in settings&bslash;n&quot;
)paren
suffix:semicolon
id|params
op_assign
l_int|NULL
suffix:semicolon
)brace
id|video_ram.start
op_assign
l_int|0x0a0000
suffix:semicolon
id|video_ram.end
op_assign
l_int|0x0bffff
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|params
op_logical_and
id|params-&gt;u1.s.page_size
op_ne
id|PAGE_SIZE
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning: wrong page size configuration, &quot;
l_string|&quot;trying to continue&bslash;n&quot;
)paren
suffix:semicolon
id|params
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|params
)paren
(brace
r_if
c_cond
(paren
id|meminfo.nr_banks
op_eq
l_int|0
)paren
(brace
id|meminfo.nr_banks
op_assign
l_int|1
suffix:semicolon
id|meminfo.bank
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|meminfo.bank
(braket
l_int|0
)braket
dot
id|size
op_assign
id|params-&gt;u1.s.nr_pages
op_lshift
id|PAGE_SHIFT
suffix:semicolon
)brace
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
id|params-&gt;u1.s.rootdev
)paren
suffix:semicolon
id|system_rev
op_assign
id|params-&gt;u1.s.system_rev
suffix:semicolon
id|system_serial_low
op_assign
id|params-&gt;u1.s.system_serial_low
suffix:semicolon
id|system_serial_high
op_assign
id|params-&gt;u1.s.system_serial_high
suffix:semicolon
id|setup_ramdisk
c_func
(paren
(paren
id|params-&gt;u1.s.flags
op_amp
id|FLAG_RDLOAD
)paren
op_eq
l_int|0
comma
(paren
id|params-&gt;u1.s.flags
op_amp
id|FLAG_RDPROMPT
)paren
op_eq
l_int|0
comma
id|params-&gt;u1.s.rd_start
comma
id|params-&gt;u1.s.ramdisk_size
)paren
suffix:semicolon
id|setup_initrd
c_func
(paren
id|params-&gt;u1.s.initrd_start
comma
id|params-&gt;u1.s.initrd_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|params-&gt;u1.s.flags
op_amp
id|FLAG_READONLY
)paren
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
id|from
op_assign
id|params-&gt;commandline
suffix:semicolon
)brace
r_if
c_cond
(paren
id|meminfo.nr_banks
op_eq
l_int|0
)paren
(brace
id|meminfo.nr_banks
op_assign
l_int|1
suffix:semicolon
id|meminfo.bank
(braket
l_int|0
)braket
dot
id|start
op_assign
l_int|0
suffix:semicolon
id|meminfo.bank
(braket
l_int|0
)braket
dot
id|size
op_assign
id|MEM_SIZE
suffix:semicolon
)brace
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_text
suffix:semicolon
id|init_mm.end_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_etext
suffix:semicolon
id|init_mm.end_data
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_edata
suffix:semicolon
id|init_mm.brk
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
id|from
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
id|parse_cmdline
c_func
(paren
id|cmdline_p
comma
id|from
)paren
suffix:semicolon
id|setup_bootmem
c_func
(paren
)paren
suffix:semicolon
id|request_standard_resources
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_VT
macro_line|#if defined(CONFIG_VGA_CONSOLE)
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|#elif defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
DECL|variable|machine_desc
r_static
r_const
r_char
op_star
id|machine_desc
(braket
)braket
op_assign
(brace
multiline_comment|/* Machine name&t;&t;Allocater&t;&t;&t;*/
l_string|&quot;EBSA110&quot;
comma
multiline_comment|/* RMK&t;&t;&t;&t;*/
l_string|&quot;Acorn-RiscPC&quot;
comma
multiline_comment|/* RMK&t;&t;&t;&t;*/
l_string|&quot;unknown&quot;
comma
l_string|&quot;Nexus-FTV/PCI&quot;
comma
multiline_comment|/* Philip Blundell&t;&t;*/
l_string|&quot;EBSA285&quot;
comma
multiline_comment|/* RMK&t;&t;&t;&t;*/
l_string|&quot;Rebel-NetWinder&quot;
comma
multiline_comment|/* RMK&t;&t;&t;&t;*/
l_string|&quot;Chalice-CATS&quot;
comma
multiline_comment|/* Philip Blundell&t;&t;*/
l_string|&quot;unknown-TBOX&quot;
comma
multiline_comment|/* Philip Blundell&t;&t;*/
l_string|&quot;co-EBSA285&quot;
comma
multiline_comment|/* Mark van Doesburg&t;&t;*/
l_string|&quot;CL-PS7110&quot;
comma
multiline_comment|/* Werner Almesberger&t;&t;*/
l_string|&quot;Acorn-Archimedes&quot;
comma
multiline_comment|/* RMK/DAG&t;&t;&t;*/
l_string|&quot;Acorn-A5000&quot;
comma
multiline_comment|/* RMK/PB&t;&t;&t;*/
l_string|&quot;Etoile&quot;
comma
multiline_comment|/* Alex de Vries&t;&t;*/
l_string|&quot;LaCie_NAS&quot;
comma
multiline_comment|/* Benjamin Herrenschmidt&t;*/
l_string|&quot;CL-PS7500&quot;
comma
multiline_comment|/* Philip Blundell&t;&t;*/
l_string|&quot;Shark&quot;
multiline_comment|/* Alexander Schulz&t;&t;*/
)brace
suffix:semicolon
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
r_char
op_star
id|p
op_assign
id|buffer
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Processor&bslash;t: %s %s rev %d (%s)&bslash;n&quot;
comma
id|proc_info.manufacturer
comma
id|proc_info.cpu_name
comma
(paren
r_int
)paren
id|processor_id
op_amp
l_int|15
comma
id|elf_platform
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;BogoMIPS&bslash;t: %lu.%02lu&bslash;n&quot;
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
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Hardware&bslash;t: %s&bslash;n&quot;
comma
id|machine_desc
(braket
id|machine_arch_type
)braket
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Revision&bslash;t: %04x&bslash;n&quot;
comma
id|system_rev
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;Serial&bslash;t&bslash;t: %08x%08x&bslash;n&quot;
comma
id|system_serial_high
comma
id|system_serial_low
)paren
suffix:semicolon
r_return
id|p
op_minus
id|buffer
suffix:semicolon
)brace
eof
