multiline_comment|/*&n; * Architecture-specific setup.&n; *&n; * Copyright (C) 1998-2000 Hewlett-Packard Co&n; * Copyright (C) 1998-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1998, 1999 Stephane Eranian &lt;eranian@hpl.hp.com&gt;&n; * Copyright (C) 2000, Rohit Seth &lt;rohit.seth@intel.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * 04/04/00 D.Mosberger renamed cpu_initialized to cpu_online_map&n; * 03/31/00 R.Seth&t;cpu_initialized and current-&gt;processor fixes&n; * 02/04/00 D.Mosberger&t;some more get_cpuinfo fixes...&n; * 02/01/00 R.Seth&t;fixed get_cpuinfo for SMP&n; * 01/07/99 S.Eranian&t;added the support for command line argument&n; * 06/24/99 W.Drummond&t;added boot_cpu_data.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;asm/acpi-ext.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/sal.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/mca.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|# include &lt;linux/blk.h&gt;
macro_line|#endif
r_extern
r_char
id|_end
suffix:semicolon
multiline_comment|/* cpu_data[0] is data for the bootstrap processor: */
DECL|variable|cpu_data
r_struct
id|cpuinfo_ia64
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|ia64_cycles_per_usec
r_int
r_int
id|ia64_cycles_per_usec
suffix:semicolon
DECL|variable|ia64_boot_param
r_struct
id|ia64_boot_param
id|ia64_boot_param
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
multiline_comment|/* This tells _start which CPU is booting.  */
DECL|variable|cpu_now_booting
r_int
id|cpu_now_booting
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|cpu_online_map
r_volatile
r_int
r_int
id|cpu_online_map
suffix:semicolon
macro_line|#endif
DECL|variable|ia64_iobase
r_int
r_int
id|ia64_iobase
suffix:semicolon
multiline_comment|/* virtual address for I/O accesses */
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE&t;512
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/* used in proc filesystem */
r_static
r_int
DECL|function|find_max_pfn
id|find_max_pfn
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
op_star
id|max_pfn
op_assign
id|arg
comma
id|pfn
suffix:semicolon
id|pfn
op_assign
(paren
id|PAGE_ALIGN
c_func
(paren
id|end
op_minus
l_int|1
)paren
op_minus
id|PAGE_OFFSET
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|pfn
OG
op_star
id|max_pfn
)paren
op_star
id|max_pfn
op_assign
id|pfn
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|free_available_memory
id|free_available_memory
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_void
op_star
id|arg
)paren
(brace
DECL|macro|KERNEL_END
macro_line|#&t;define KERNEL_END&t;((unsigned long) &amp;_end)
DECL|macro|MIN
macro_line|#&t;define MIN(a,b)&t;&t;((a) &lt; (b) ? (a) : (b))
DECL|macro|MAX
macro_line|#&t;define MAX(a,b)&t;&t;((a) &gt; (b) ? (a) : (b))
r_int
r_int
id|range_start
comma
id|range_end
suffix:semicolon
id|range_start
op_assign
id|MIN
c_func
(paren
id|start
comma
id|KERNEL_START
)paren
suffix:semicolon
id|range_end
op_assign
id|MIN
c_func
(paren
id|end
comma
id|KERNEL_START
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * XXX This should not be necessary, but the bootmem allocator&n;&t; * is broken and fails to work correctly when the starting&n;&t; * address is not properly aligned.&n;&t; */
id|range_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|range_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|range_start
OL
id|range_end
)paren
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|range_start
)paren
comma
id|range_end
op_minus
id|range_start
)paren
suffix:semicolon
id|range_start
op_assign
id|MAX
c_func
(paren
id|start
comma
id|KERNEL_END
)paren
suffix:semicolon
id|range_end
op_assign
id|MAX
c_func
(paren
id|end
comma
id|KERNEL_END
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * XXX This should not be necessary, but the bootmem allocator&n;&t; * is broken and fails to work correctly when the starting&n;&t; * address is not properly aligned.&n;&t; */
id|range_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|range_start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|range_start
OL
id|range_end
)paren
id|free_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|range_start
)paren
comma
id|range_end
op_minus
id|range_start
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_void
id|__init
DECL|function|setup_arch
id|setup_arch
(paren
r_char
op_star
op_star
id|cmdline_p
)paren
(brace
r_extern
r_int
r_int
id|ia64_iobase
suffix:semicolon
r_int
r_int
id|max_pfn
comma
id|bootmap_start
comma
id|bootmap_size
suffix:semicolon
id|unw_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The secondary bootstrap loader passes us the boot&n;&t; * parameters at the beginning of the ZERO_PAGE, so let&squot;s&n;&t; * stash away those values before ZERO_PAGE gets cleared out.&n;&t; */
id|memcpy
c_func
(paren
op_amp
id|ia64_boot_param
comma
(paren
r_void
op_star
)paren
id|ZERO_PAGE_ADDR
comma
r_sizeof
(paren
id|ia64_boot_param
)paren
)paren
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|__va
c_func
(paren
id|ia64_boot_param.command_line
)paren
suffix:semicolon
id|strncpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
comma
r_sizeof
(paren
id|saved_command_line
)paren
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
multiline_comment|/* for safety */
id|efi_init
c_func
(paren
)paren
suffix:semicolon
id|max_pfn
op_assign
l_int|0
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|find_max_pfn
comma
op_amp
id|max_pfn
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * This is wrong, wrong, wrong.  Darn it, you&squot;d think if they&n;&t; * change APIs, they&squot;d do things for the better.  Grumble...&n;&t; */
id|bootmap_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|__pa
c_func
(paren
op_amp
id|_end
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ia64_boot_param.initrd_size
)paren
id|bootmap_start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|bootmap_start
op_plus
id|ia64_boot_param.initrd_size
)paren
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|bootmap_start
op_rshift
id|PAGE_SHIFT
comma
id|max_pfn
)paren
suffix:semicolon
id|efi_memmap_walk
c_func
(paren
id|free_available_memory
comma
l_int|0
)paren
suffix:semicolon
id|reserve_bootmem
c_func
(paren
id|bootmap_start
comma
id|bootmap_size
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|initrd_start
op_assign
id|ia64_boot_param.initrd_start
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
)paren
(brace
id|u64
id|start
comma
id|size
suffix:semicolon
DECL|macro|is_same_page
macro_line|#&t;&t;define is_same_page(a,b) (((a)&amp;PAGE_MASK) == ((b)&amp;PAGE_MASK))
macro_line|#if 1
multiline_comment|/* XXX for now some backwards compatibility... */
r_if
c_cond
(paren
id|initrd_start
op_ge
id|PAGE_OFFSET
)paren
id|printk
c_func
(paren
l_string|&quot;Warning: boot loader passed virtual address &quot;
l_string|&quot;for initrd, please upgrade the loader&bslash;n&quot;
)paren
suffix:semicolon
r_else
macro_line|#endif
multiline_comment|/* &n;&t;&t;&t; * The loader ONLY passes physical addresses&n;&t;&t;&t; */
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|initrd_start
)paren
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|ia64_boot_param.initrd_size
suffix:semicolon
id|start
op_assign
id|initrd_start
suffix:semicolon
id|size
op_assign
id|ia64_boot_param.initrd_size
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initial ramdisk at: 0x%p (%lu bytes)&bslash;n&quot;
comma
(paren
r_void
op_star
)paren
id|initrd_start
comma
id|ia64_boot_param.initrd_size
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The kernel end and the beginning of initrd can be&n;&t;&t; * on the same page. This would cause the page to be&n;&t;&t; * reserved twice.  While not harmful, it does lead to&n;&t;&t; * a warning message which can cause confusion.  Thus,&n;&t;&t; * we make sure that in this case we only reserve new&n;&t;&t; * pages, i.e., initrd only pages. We need to:&n;&t;&t; *&n;&t;&t; *&t;- align up start&n;&t;&t; *&t;- adjust size of reserved section accordingly&n;&t;&t; *&n;&t;&t; * It should be noted that this operation is only&n;&t;&t; * valid for the reserve_bootmem() call and does not&n;&t;&t; * affect the integrety of the initrd itself.&n;&t;&t; *&n;&t;&t; * reserve_bootmem() considers partial pages as reserved.&n;&t;&t; */
r_if
c_cond
(paren
id|is_same_page
c_func
(paren
id|initrd_start
comma
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
)paren
(brace
id|start
op_assign
id|PAGE_ALIGN
c_func
(paren
id|start
)paren
suffix:semicolon
id|size
op_sub_assign
id|start
op_minus
id|initrd_start
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Initial ramdisk &amp; kernel on the same page: &quot;
l_string|&quot;reserving start=%lx size=%ld bytes&bslash;n&quot;
comma
id|start
comma
id|size
)paren
suffix:semicolon
)brace
id|reserve_bootmem
c_func
(paren
id|__pa
c_func
(paren
id|start
)paren
comma
id|size
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0
multiline_comment|/* XXX fix me */
id|init_mm.start_code
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_stext
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
macro_line|#endif
multiline_comment|/* process SAL system table: */
id|ia64_sal_init
c_func
(paren
id|efi.sal_systab
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|current-&gt;processor
op_assign
l_int|0
suffix:semicolon
id|cpu_physical_id
c_func
(paren
l_int|0
)paren
op_assign
id|hard_smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; *  Set `iobase&squot; to the appropriate address in region 6&n;&t; *    (uncached access range)&n;&t; */
id|__asm__
(paren
l_string|&quot;mov %0=ar.k0;;&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|ia64_iobase
)paren
)paren
suffix:semicolon
id|ia64_iobase
op_assign
id|__IA64_UNCACHED_OFFSET
op_or
(paren
id|ia64_iobase
op_amp
op_complement
id|PAGE_OFFSET
)paren
suffix:semicolon
id|cpu_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* initialize the bootstrap CPU */
macro_line|#ifdef CONFIG_IA64_GENERIC
id|machvec_init
c_func
(paren
id|acpi_get_sysname
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef&t;CONFIG_ACPI20
r_if
c_cond
(paren
id|efi.acpi20
)paren
(brace
multiline_comment|/* Parse the ACPI 2.0 tables */
id|acpi20_parse
c_func
(paren
id|efi.acpi20
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
id|efi.acpi
)paren
(brace
multiline_comment|/* Parse the ACPI tables */
id|acpi_parse
c_func
(paren
id|efi.acpi
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_VT
macro_line|# if defined(CONFIG_VGA_CONSOLE)
id|conswitchp
op_assign
op_amp
id|vga_con
suffix:semicolon
macro_line|# elif defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_IA64_MCA
multiline_comment|/* enable IA-64 Machine Check Abort Handling */
id|ia64_mca_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|paging_init
c_func
(paren
)paren
suffix:semicolon
id|platform_setup
c_func
(paren
id|cmdline_p
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Display cpu info for all cpu&squot;s.&n; */
r_int
DECL|function|get_cpuinfo
id|get_cpuinfo
(paren
r_char
op_star
id|buffer
)paren
(brace
macro_line|#ifdef CONFIG_SMP
DECL|macro|lpj
macro_line|#&t;define lpj&t;c-&gt;loops_per_jiffy
macro_line|#else
macro_line|#&t;define lpj&t;loops_per_jiffy
macro_line|#endif
r_char
id|family
(braket
l_int|32
)braket
comma
id|model
(braket
l_int|32
)braket
comma
id|features
(braket
l_int|128
)braket
comma
op_star
id|cp
comma
op_star
id|p
op_assign
id|buffer
suffix:semicolon
r_struct
id|cpuinfo_ia64
op_star
id|c
suffix:semicolon
r_int
r_int
id|mask
suffix:semicolon
r_for
c_loop
(paren
id|c
op_assign
id|cpu_data
suffix:semicolon
id|c
OL
id|cpu_data
op_plus
id|NR_CPUS
suffix:semicolon
op_increment
id|c
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1UL
op_lshift
(paren
id|c
op_minus
id|cpu_data
)paren
)paren
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|mask
op_assign
id|c-&gt;features
suffix:semicolon
r_if
c_cond
(paren
id|c-&gt;family
op_eq
l_int|7
)paren
id|memcpy
c_func
(paren
id|family
comma
l_string|&quot;IA-64&quot;
comma
l_int|6
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|family
comma
l_string|&quot;%u&quot;
comma
id|c-&gt;family
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|c-&gt;model
)paren
(brace
r_case
l_int|0
suffix:colon
id|strcpy
c_func
(paren
id|model
comma
l_string|&quot;Itanium&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|sprintf
c_func
(paren
id|model
comma
l_string|&quot;%u&quot;
comma
id|c-&gt;model
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* build the feature string: */
id|memcpy
c_func
(paren
id|features
comma
l_string|&quot; standard&quot;
comma
l_int|10
)paren
suffix:semicolon
id|cp
op_assign
id|features
suffix:semicolon
r_if
c_cond
(paren
id|mask
op_amp
l_int|1
)paren
(brace
id|strcpy
c_func
(paren
id|cp
comma
l_string|&quot; branchlong&quot;
)paren
suffix:semicolon
id|cp
op_assign
id|strchr
c_func
(paren
id|cp
comma
l_char|&squot;&bslash;0&squot;
)paren
suffix:semicolon
id|mask
op_and_assign
op_complement
l_int|1UL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mask
)paren
id|sprintf
c_func
(paren
id|cp
comma
l_string|&quot; 0x%lx&quot;
comma
id|mask
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;processor  : %lu&bslash;n&quot;
l_string|&quot;vendor     : %s&bslash;n&quot;
l_string|&quot;family     : %s&bslash;n&quot;
l_string|&quot;model      : %s&bslash;n&quot;
l_string|&quot;revision   : %u&bslash;n&quot;
l_string|&quot;archrev    : %u&bslash;n&quot;
l_string|&quot;features   :%s&bslash;n&quot;
multiline_comment|/* don&squot;t change this---it _is_ right! */
l_string|&quot;cpu number : %lu&bslash;n&quot;
l_string|&quot;cpu regs   : %u&bslash;n&quot;
l_string|&quot;cpu MHz    : %lu.%06lu&bslash;n&quot;
l_string|&quot;itc MHz    : %lu.%06lu&bslash;n&quot;
l_string|&quot;BogoMIPS   : %lu.%02lu&bslash;n&bslash;n&quot;
comma
id|c
op_minus
id|cpu_data
comma
id|c-&gt;vendor
comma
id|family
comma
id|model
comma
id|c-&gt;revision
comma
id|c-&gt;archrev
comma
id|features
comma
id|c-&gt;ppn
comma
id|c-&gt;number
comma
id|c-&gt;proc_freq
op_div
l_int|1000000
comma
id|c-&gt;proc_freq
op_mod
l_int|1000000
comma
id|c-&gt;itc_freq
op_div
l_int|1000000
comma
id|c-&gt;itc_freq
op_mod
l_int|1000000
comma
id|lpj
op_star
id|HZ
op_div
l_int|500000
comma
(paren
id|lpj
op_star
id|HZ
op_div
l_int|5000
)paren
op_mod
l_int|100
)paren
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buffer
suffix:semicolon
)brace
r_void
DECL|function|identify_cpu
id|identify_cpu
(paren
r_struct
id|cpuinfo_ia64
op_star
id|c
)paren
(brace
r_union
(brace
r_int
r_int
id|bits
(braket
l_int|5
)braket
suffix:semicolon
r_struct
(brace
multiline_comment|/* id 0 &amp; 1: */
r_char
id|vendor
(braket
l_int|16
)braket
suffix:semicolon
multiline_comment|/* id 2 */
id|u64
id|ppn
suffix:semicolon
multiline_comment|/* processor serial number */
multiline_comment|/* id 3: */
r_int
id|number
suffix:colon
l_int|8
suffix:semicolon
r_int
id|revision
suffix:colon
l_int|8
suffix:semicolon
r_int
id|model
suffix:colon
l_int|8
suffix:semicolon
r_int
id|family
suffix:colon
l_int|8
suffix:semicolon
r_int
id|archrev
suffix:colon
l_int|8
suffix:semicolon
r_int
id|reserved
suffix:colon
l_int|24
suffix:semicolon
multiline_comment|/* id 4: */
id|u64
id|features
suffix:semicolon
)brace
id|field
suffix:semicolon
)brace
id|cpuid
suffix:semicolon
id|pal_vm_info_1_u_t
id|vm1
suffix:semicolon
id|pal_vm_info_2_u_t
id|vm2
suffix:semicolon
id|pal_status_t
id|status
suffix:semicolon
r_int
r_int
id|impl_va_msb
op_assign
l_int|50
comma
id|phys_addr_size
op_assign
l_int|44
suffix:semicolon
multiline_comment|/* Itanium defaults */
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
l_int|5
suffix:semicolon
op_increment
id|i
)paren
id|cpuid.bits
(braket
id|i
)braket
op_assign
id|ia64_get_cpuid
c_func
(paren
id|i
)paren
suffix:semicolon
id|memset
c_func
(paren
id|c
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpuinfo_ia64
)paren
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|c-&gt;vendor
comma
id|cpuid.field.vendor
comma
l_int|16
)paren
suffix:semicolon
id|c-&gt;ppn
op_assign
id|cpuid.field.ppn
suffix:semicolon
id|c-&gt;number
op_assign
id|cpuid.field.number
suffix:semicolon
id|c-&gt;revision
op_assign
id|cpuid.field.revision
suffix:semicolon
id|c-&gt;model
op_assign
id|cpuid.field.model
suffix:semicolon
id|c-&gt;family
op_assign
id|cpuid.field.family
suffix:semicolon
id|c-&gt;archrev
op_assign
id|cpuid.field.archrev
suffix:semicolon
id|c-&gt;features
op_assign
id|cpuid.field.features
suffix:semicolon
id|status
op_assign
id|ia64_pal_vm_summary
c_func
(paren
op_amp
id|vm1
comma
op_amp
id|vm2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|PAL_STATUS_SUCCESS
)paren
(brace
id|impl_va_msb
op_assign
id|vm2.pal_vm_info_2_s.impl_va_msb
suffix:semicolon
id|phys_addr_size
op_assign
id|vm1.pal_vm_info_1_s.phys_add_size
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;CPU %d: %lu virtual and %lu physical address bits&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
comma
id|impl_va_msb
op_plus
l_int|1
comma
id|phys_addr_size
)paren
suffix:semicolon
id|c-&gt;unimpl_va_mask
op_assign
op_complement
(paren
(paren
l_int|7L
op_lshift
l_int|61
)paren
op_or
(paren
(paren
l_int|1L
op_lshift
(paren
id|impl_va_msb
op_plus
l_int|1
)paren
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
id|c-&gt;unimpl_pa_mask
op_assign
op_complement
(paren
(paren
l_int|1L
op_lshift
l_int|63
)paren
op_or
(paren
(paren
l_int|1L
op_lshift
id|phys_addr_size
)paren
op_minus
l_int|1
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IA64_SOFTSDV_HACKS
multiline_comment|/* BUG: SoftSDV doesn&squot;t support the cpuid registers. */
r_if
c_cond
(paren
id|c-&gt;vendor
(braket
l_int|0
)braket
op_eq
l_char|&squot;&bslash;0&squot;
)paren
id|memcpy
c_func
(paren
id|c-&gt;vendor
comma
l_string|&quot;Intel&quot;
comma
l_int|6
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * cpu_init() initializes state that is per-CPU.  This function acts&n; * as a &squot;CPU state barrier&squot;, nothing should get across.&n; */
r_void
DECL|function|cpu_init
id|cpu_init
(paren
r_void
)paren
(brace
r_extern
r_void
id|__init
id|ia64_rid_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|ia64_tlb_init
(paren
r_void
)paren
suffix:semicolon
id|pal_vm_info_2_u_t
id|vmi
suffix:semicolon
r_int
r_int
id|max_ctx
suffix:semicolon
id|identify_cpu
c_func
(paren
op_amp
id|my_cpu_data
)paren
suffix:semicolon
multiline_comment|/* Clear the stack memory reserved for pt_regs: */
id|memset
c_func
(paren
id|ia64_task_regs
c_func
(paren
id|current
)paren
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Initialize default control register to defer all speculative faults.  The&n;&t; * kernel MUST NOT depend on a particular setting of these bits (in other words,&n;&t; * the kernel must have recovery code for all speculative accesses).&n;&t; */
id|ia64_set_dcr
c_func
(paren
id|IA64_DCR_DM
op_or
id|IA64_DCR_DP
op_or
id|IA64_DCR_DK
op_or
id|IA64_DCR_DX
op_or
id|IA64_DCR_DR
op_or
id|IA64_DCR_DA
op_or
id|IA64_DCR_DD
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|ia64_set_fpu_owner
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* initialize ar.k5 */
macro_line|#endif
id|atomic_inc
c_func
(paren
op_amp
id|init_mm.mm_count
)paren
suffix:semicolon
id|current-&gt;active_mm
op_assign
op_amp
id|init_mm
suffix:semicolon
id|ia64_rid_init
c_func
(paren
)paren
suffix:semicolon
id|ia64_tlb_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef&t;CONFIG_IA32_SUPPORT
multiline_comment|/* initialize global ia32 state - CR0 and CR4 */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.cflg = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
(paren
id|ulong
)paren
id|IA32_CR4
op_lshift
l_int|32
)paren
op_or
id|IA32_CR0
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|normal_xtp
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set ia64_ctx.max_rid to the maximum RID that is supported by all CPUs: */
r_if
c_cond
(paren
id|ia64_pal_vm_summary
c_func
(paren
l_int|NULL
comma
op_amp
id|vmi
)paren
op_eq
l_int|0
)paren
id|max_ctx
op_assign
(paren
l_int|1U
op_lshift
(paren
id|vmi.pal_vm_info_2_s.rid_size
op_minus
l_int|3
)paren
)paren
op_minus
l_int|1
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;ia64_rid_init: PAL VM summary failed, assuming 18 RID bits&bslash;n&quot;
)paren
suffix:semicolon
id|max_ctx
op_assign
(paren
l_int|1U
op_lshift
l_int|15
)paren
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* use architected minimum */
)brace
r_while
c_loop
(paren
id|max_ctx
OL
id|ia64_ctx.max_ctx
)paren
(brace
r_int
r_int
id|old
op_assign
id|ia64_ctx.max_ctx
suffix:semicolon
r_if
c_cond
(paren
id|cmpxchg
c_func
(paren
op_amp
id|ia64_ctx.max_ctx
comma
id|old
comma
id|max_ctx
)paren
op_eq
id|old
)paren
r_break
suffix:semicolon
)brace
)brace
eof
