multiline_comment|/*&n; *  linux/arch/arm/kernel/setup.c&n; *&n; *  Copyright (C) 1995-2000 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/procinfo.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;arch.h&quot;
macro_line|#ifndef MEM_SIZE
DECL|macro|MEM_SIZE
mdefine_line|#define MEM_SIZE&t;(16*1024*1024)
macro_line|#endif
macro_line|#ifndef CONFIG_CMDLINE
DECL|macro|CONFIG_CMDLINE
mdefine_line|#define CONFIG_CMDLINE &quot;&quot;
macro_line|#endif
r_extern
r_void
id|paging_init
c_func
(paren
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
r_extern
r_void
id|bootmem_init
c_func
(paren
r_struct
id|meminfo
op_star
)paren
suffix:semicolon
r_extern
r_void
id|reboot_setup
c_func
(paren
r_char
op_star
id|str
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
r_int
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
DECL|variable|mem_fclk_21285
r_int
r_int
id|mem_fclk_21285
op_assign
l_int|50000000
suffix:semicolon
DECL|variable|elf_hwcap
r_int
r_int
id|elf_hwcap
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
DECL|variable|machine_name
r_static
r_const
r_char
op_star
id|machine_name
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
DECL|macro|video_ram
mdefine_line|#define video_ram   mem_res[0]
DECL|macro|kernel_code
mdefine_line|#define kernel_code mem_res[1]
DECL|macro|kernel_data
mdefine_line|#define kernel_data mem_res[2]
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
id|printk
c_func
(paren
l_string|&quot;Processor: %s %s revision %d&bslash;n&quot;
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
)paren
suffix:semicolon
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
DECL|function|setup_architecture
r_static
r_struct
id|machine_desc
op_star
id|__init
id|setup_architecture
c_func
(paren
r_int
r_int
id|nr
)paren
(brace
r_extern
r_struct
id|machine_desc
id|__arch_info_begin
comma
id|__arch_info_end
suffix:semicolon
r_struct
id|machine_desc
op_star
id|list
suffix:semicolon
multiline_comment|/*&n;&t; * locate architecture in the list of supported architectures.&n;&t; */
r_for
c_loop
(paren
id|list
op_assign
op_amp
id|__arch_info_begin
suffix:semicolon
id|list
OL
op_amp
id|__arch_info_end
suffix:semicolon
id|list
op_increment
)paren
r_if
c_cond
(paren
id|list-&gt;nr
op_eq
id|nr
)paren
r_break
suffix:semicolon
multiline_comment|/*&n;&t; * If the architecture type is not recognised, then we&n;&t; * can co nothing...&n;&t; */
r_if
c_cond
(paren
id|list
op_ge
op_amp
id|__arch_info_end
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Architecture configuration botched (nr %d), unable &quot;
l_string|&quot;to continue.&bslash;n&quot;
comma
id|nr
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Architecture: %s&bslash;n&quot;
comma
id|list-&gt;name
)paren
suffix:semicolon
r_return
id|list
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
r_struct
id|meminfo
op_star
id|mi
comma
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
multiline_comment|/*&n;&t;&t;&t; * If the user specifies memory size, we&n;&t;&t;&t; * blow away any automatically generated&n;&t;&t;&t; * size.&n;&t;&t;&t; */
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
id|mi-&gt;nr_banks
op_assign
l_int|0
suffix:semicolon
)brace
id|start
op_assign
id|PHYS_OFFSET
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
id|mi-&gt;bank
(braket
id|mi-&gt;nr_banks
)braket
dot
id|start
op_assign
id|start
suffix:semicolon
id|mi-&gt;bank
(braket
id|mi-&gt;nr_banks
)braket
dot
id|size
op_assign
id|size
suffix:semicolon
id|mi-&gt;bank
(braket
id|mi-&gt;nr_banks
)braket
dot
id|node
op_assign
l_int|0
suffix:semicolon
id|mi-&gt;nr_banks
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
comma
id|rd_prompt
comma
id|rd_image_start
comma
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
r_static
r_void
id|__init
DECL|function|request_standard_resources
id|request_standard_resources
c_func
(paren
r_struct
id|meminfo
op_star
id|mi
comma
r_struct
id|machine_desc
op_star
id|mdesc
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|i
suffix:semicolon
id|kernel_code.start
op_assign
id|__virt_to_bus
c_func
(paren
id|init_mm.start_code
)paren
suffix:semicolon
id|kernel_code.end
op_assign
id|__virt_to_bus
c_func
(paren
id|init_mm.end_code
op_minus
l_int|1
)paren
suffix:semicolon
id|kernel_data.start
op_assign
id|__virt_to_bus
c_func
(paren
id|init_mm.end_code
)paren
suffix:semicolon
id|kernel_data.end
op_assign
id|__virt_to_bus
c_func
(paren
id|init_mm.brk
op_minus
l_int|1
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
id|mi-&gt;nr_banks
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|virt_start
comma
id|virt_end
suffix:semicolon
r_if
c_cond
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|virt_start
op_assign
id|__phys_to_virt
c_func
(paren
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|start
)paren
suffix:semicolon
id|virt_end
op_assign
id|virt_start
op_plus
id|mi-&gt;bank
(braket
id|i
)braket
dot
id|size
op_minus
l_int|1
suffix:semicolon
id|res
op_assign
id|alloc_bootmem_low
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|res-&gt;name
op_assign
l_string|&quot;System RAM&quot;
suffix:semicolon
id|res-&gt;start
op_assign
id|__virt_to_bus
c_func
(paren
id|virt_start
)paren
suffix:semicolon
id|res-&gt;end
op_assign
id|__virt_to_bus
c_func
(paren
id|virt_end
)paren
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_BUSY
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kernel_code.start
op_ge
id|res-&gt;start
op_logical_and
id|kernel_code.end
op_le
id|res-&gt;end
)paren
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|kernel_code
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kernel_data.start
op_ge
id|res-&gt;start
op_logical_and
id|kernel_data.end
op_le
id|res-&gt;end
)paren
id|request_resource
c_func
(paren
id|res
comma
op_amp
id|kernel_data
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mdesc-&gt;video_start
)paren
(brace
id|video_ram.start
op_assign
id|mdesc-&gt;video_start
suffix:semicolon
id|video_ram.end
op_assign
id|mdesc-&gt;video_end
suffix:semicolon
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
)brace
multiline_comment|/*&n;&t; * Some machines don&squot;t have the possibility of ever&n;&t; * possessing lp0, lp1 or lp2&n;&t; */
r_if
c_cond
(paren
id|mdesc-&gt;reserve_lp0
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
id|mdesc-&gt;reserve_lp1
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
id|mdesc-&gt;reserve_lp2
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
l_int|NULL
suffix:semicolon
r_struct
id|machine_desc
op_star
id|mdesc
suffix:semicolon
r_struct
id|meminfo
id|meminfo
suffix:semicolon
r_char
op_star
id|from
op_assign
id|default_command_line
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|meminfo
comma
l_int|0
comma
r_sizeof
(paren
id|meminfo
)paren
)paren
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
id|mdesc
op_assign
id|setup_architecture
c_func
(paren
id|machine_arch_type
)paren
suffix:semicolon
id|machine_name
op_assign
id|mdesc-&gt;name
suffix:semicolon
r_if
c_cond
(paren
id|mdesc-&gt;broken_hlt
)paren
id|disable_hlt
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdesc-&gt;soft_reboot
)paren
id|reboot_setup
c_func
(paren
l_string|&quot;s&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdesc-&gt;param_offset
)paren
id|params
op_assign
id|phys_to_virt
c_func
(paren
id|mdesc-&gt;param_offset
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mdesc-&gt;fixup
)paren
id|mdesc
op_member_access_from_pointer
id|fixup
c_func
(paren
id|mdesc
comma
id|params
comma
op_amp
id|from
comma
op_amp
id|meminfo
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
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Warning: bad configuration page, &quot;
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
r_if
c_cond
(paren
id|params-&gt;u1.s.mem_fclk_21285
OG
l_int|0
)paren
id|mem_fclk_21285
op_assign
id|params-&gt;u1.s.mem_fclk_21285
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
id|PHYS_OFFSET
suffix:semicolon
id|meminfo.bank
(braket
l_int|0
)braket
dot
id|node
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|params
)paren
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
r_else
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
op_amp
id|meminfo
comma
id|cmdline_p
comma
id|from
)paren
suffix:semicolon
id|bootmem_init
c_func
(paren
op_amp
id|meminfo
)paren
suffix:semicolon
id|paging_init
c_func
(paren
op_amp
id|meminfo
)paren
suffix:semicolon
id|request_standard_resources
c_func
(paren
op_amp
id|meminfo
comma
id|mdesc
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
id|machine_name
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
