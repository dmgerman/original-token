multiline_comment|/* $Id: setup.c,v 1.4 1999/10/17 02:49:24 gniibe Exp $&n; *&n; *  linux/arch/sh/kernel/setup.c&n; *&n; *  Copyright (C) 1999  Niibe Yutaka&n; *&n; */
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
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
multiline_comment|/*&n; * Machine setup..&n; */
DECL|variable|boot_cpu_data
r_struct
id|sh_cpuinfo
id|boot_cpu_data
op_assign
(brace
id|CPU_SH_NONE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
)brace
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
id|_text
comma
id|_etext
comma
id|_edata
comma
id|_end
suffix:semicolon
multiline_comment|/*&n; * This is set up by the setup-routine at boot-time&n; */
DECL|macro|PARAM
mdefine_line|#define PARAM&t;((unsigned char *)empty_zero_page)
DECL|macro|MOUNT_ROOT_RDONLY
mdefine_line|#define MOUNT_ROOT_RDONLY (*(unsigned long *) (PARAM+0x000))
DECL|macro|RAMDISK_FLAGS
mdefine_line|#define RAMDISK_FLAGS (*(unsigned long *) (PARAM+0x004))
DECL|macro|ORIG_ROOT_DEV
mdefine_line|#define ORIG_ROOT_DEV (*(unsigned long *) (PARAM+0x008))
DECL|macro|LOADER_TYPE
mdefine_line|#define LOADER_TYPE (*(unsigned long *) (PARAM+0x00c))
DECL|macro|INITRD_START
mdefine_line|#define INITRD_START (*(unsigned long *) (PARAM+0x010))
DECL|macro|INITRD_SIZE
mdefine_line|#define INITRD_SIZE (*(unsigned long *) (PARAM+0x014))
DECL|macro|MEMORY_END
mdefine_line|#define MEMORY_END (*(unsigned long *) (PARAM+0x018))
multiline_comment|/* ... */
DECL|macro|COMMAND_LINE
mdefine_line|#define COMMAND_LINE ((char *) (PARAM+0x100))
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
DECL|variable|standard_io_resources
r_struct
id|resource
id|standard_io_resources
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;dma1&quot;
comma
l_int|0x00
comma
l_int|0x1f
)brace
comma
(brace
l_string|&quot;pic1&quot;
comma
l_int|0x20
comma
l_int|0x3f
)brace
comma
(brace
l_string|&quot;timer&quot;
comma
l_int|0x40
comma
l_int|0x5f
)brace
comma
(brace
l_string|&quot;keyboard&quot;
comma
l_int|0x60
comma
l_int|0x6f
)brace
comma
(brace
l_string|&quot;dma page reg&quot;
comma
l_int|0x80
comma
l_int|0x8f
)brace
comma
(brace
l_string|&quot;pic2&quot;
comma
l_int|0xa0
comma
l_int|0xbf
)brace
comma
(brace
l_string|&quot;dma2&quot;
comma
l_int|0xc0
comma
l_int|0xdf
)brace
comma
(brace
l_string|&quot;fpu&quot;
comma
l_int|0xf0
comma
l_int|0xff
)brace
)brace
suffix:semicolon
DECL|macro|STANDARD_IO_RESOURCES
mdefine_line|#define STANDARD_IO_RESOURCES (sizeof(standard_io_resources)/sizeof(struct resource))
multiline_comment|/* System RAM - interrupted by the 640kB-1M hole */
DECL|macro|code_resource
mdefine_line|#define code_resource (ram_resources[3])
DECL|macro|data_resource
mdefine_line|#define data_resource (ram_resources[4])
DECL|variable|ram_resources
r_static
r_struct
id|resource
id|ram_resources
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;System RAM&quot;
comma
l_int|0x000000
comma
l_int|0x09ffff
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;System RAM&quot;
comma
l_int|0x100000
comma
l_int|0x100000
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;Video RAM area&quot;
comma
l_int|0x0a0000
comma
l_int|0x0bffff
)brace
comma
(brace
l_string|&quot;Kernel code&quot;
comma
l_int|0x100000
comma
l_int|0
)brace
comma
(brace
l_string|&quot;Kernel data&quot;
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/* System ROM resources */
DECL|macro|MAXROMS
mdefine_line|#define MAXROMS 6
DECL|variable|rom_resources
r_static
r_struct
id|resource
id|rom_resources
(braket
id|MAXROMS
)braket
op_assign
(brace
(brace
l_string|&quot;System ROM&quot;
comma
l_int|0xF0000
comma
l_int|0xFFFFF
comma
id|IORESOURCE_BUSY
)brace
comma
(brace
l_string|&quot;Video ROM&quot;
comma
l_int|0xc0000
comma
l_int|0xc7fff
)brace
)brace
suffix:semicolon
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
(brace
r_int
r_int
id|memory_start
comma
id|memory_end
suffix:semicolon
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
id|ORIG_ROOT_DEV
)paren
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
id|memory_end
op_assign
id|MEMORY_END
suffix:semicolon
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
id|code_resource.start
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_text
)paren
suffix:semicolon
id|code_resource.end
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_etext
)paren
op_minus
l_int|1
suffix:semicolon
id|data_resource.start
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_etext
)paren
suffix:semicolon
id|data_resource.end
op_assign
id|virt_to_bus
c_func
(paren
op_amp
id|_edata
)paren
op_minus
l_int|1
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
id|memcpy
c_func
(paren
id|command_line
comma
id|COMMAND_LINE
comma
id|COMMAND_LINE_SIZE
)paren
suffix:semicolon
id|command_line
(braket
id|COMMAND_LINE_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
multiline_comment|/* Not support &quot;mem=XXX[kKmM]&quot; command line option. */
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
id|memory_end
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|ram_resources
(braket
l_int|1
)braket
dot
id|end
op_assign
id|memory_end
op_minus
l_int|1
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
macro_line|#if 0
multiline_comment|/*&n;&t; * Request the standard RAM and ROM resources -&n;&t; * they eat up PCI memory space&n;&t; */
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|ram_resources
op_plus
l_int|0
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|ram_resources
op_plus
l_int|1
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|iomem_resource
comma
id|ram_resources
op_plus
l_int|2
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|ram_resources
op_plus
l_int|1
comma
op_amp
id|code_resource
)paren
suffix:semicolon
id|request_resource
c_func
(paren
id|ram_resources
op_plus
l_int|1
comma
op_amp
id|data_resource
)paren
suffix:semicolon
id|probe_roms
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* request I/O space for devices used on all i[345]86 PCs */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|STANDARD_IO_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
id|standard_io_resources
op_plus
id|i
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/*&n; *&t;Get CPU information for use by the procfs.&n; */
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
macro_line|#if defined(__sh3__)
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;cpu family&bslash;t: SH-3&bslash;n&quot;
l_string|&quot;cache size&bslash;t: 8K-byte&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#elif defined(__SH4__)
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;cpu family&bslash;t: SH-4&bslash;n&quot;
l_string|&quot;cache size&bslash;t: 8K-byte/16K-byte&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&bslash;n&quot;
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
r_return
id|p
op_minus
id|buffer
suffix:semicolon
)brace
eof
