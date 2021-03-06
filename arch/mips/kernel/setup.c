multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995  Linus Torvalds&n; * Copyright (C) 1995, 1996, 1997, 1998  Ralf Baechle&n; * Copyright (C) 1996  Stoned Elipot&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/utsname.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#ifdef CONFIG_RTC
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#ifdef CONFIG_SGI_IP22
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#endif
DECL|variable|boot_cpu_data
r_struct
id|mips_cpuinfo
id|boot_cpu_data
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*&n; * Not all of the MIPS CPUs have the &quot;wait&quot; instruction available. Moreover,&n; * the implementation of the &quot;wait&quot; feature differs between CPU families. This&n; * points to the function that implements CPU specific wait. &n; * The wait instruction stops the pipeline and reduces the power consumption of&n; * the CPU very much.&n; */
DECL|variable|cpu_wait
r_void
(paren
op_star
id|cpu_wait
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Do we have a cyclecounter available?&n; */
DECL|variable|cyclecounter_available
r_char
id|cyclecounter_available
suffix:semicolon
multiline_comment|/*&n; * There are several bus types available for MIPS machines.  &quot;RISC PC&quot;&n; * type machines have ISA, EISA, VLB or PCI available, DECstations&n; * have Turbochannel or Q-Bus, SGI has GIO, there are lots of VME&n; * boxes ...&n; * This flag is set if a EISA slots are available.&n; */
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
suffix:semicolon
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_FD
r_extern
r_struct
id|fd_ops
id|no_fd_ops
suffix:semicolon
DECL|variable|fd_ops
r_struct
id|fd_ops
op_star
id|fd_ops
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_IDE_MODULE)
r_extern
r_struct
id|ide_ops
id|no_ide_ops
suffix:semicolon
DECL|variable|ide_ops
r_struct
id|ide_ops
op_star
id|ide_ops
suffix:semicolon
macro_line|#endif
r_extern
r_struct
id|rtc_ops
id|no_rtc_ops
suffix:semicolon
DECL|variable|rtc_ops
r_struct
id|rtc_ops
op_star
id|rtc_ops
suffix:semicolon
macro_line|#ifdef CONFIG_PC_KEYB
r_extern
r_struct
id|kbd_ops
id|no_kbd_ops
suffix:semicolon
DECL|variable|kbd_ops
r_struct
id|kbd_ops
op_star
id|kbd_ops
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Setup information&n; *&n; * These are initialized so they are in the .data section&n; */
DECL|variable|mips_memory_upper
r_int
r_int
id|mips_memory_upper
op_assign
id|KSEG0
suffix:semicolon
multiline_comment|/* this is set by kernel_entry() */
DECL|variable|mips_cputype
r_int
r_int
id|mips_cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
DECL|variable|mips_machtype
r_int
r_int
id|mips_machtype
op_assign
id|MACH_UNKNOWN
suffix:semicolon
DECL|variable|mips_machgroup
r_int
r_int
id|mips_machgroup
op_assign
id|MACH_GROUP_UNKNOWN
suffix:semicolon
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
r_extern
r_int
id|_end
suffix:semicolon
DECL|variable|command_line
r_static
r_char
id|command_line
(braket
id|CL_SIZE
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
id|CL_SIZE
)braket
suffix:semicolon
r_extern
r_char
id|arcs_cmdline
(braket
id|CL_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n; * The board specific setup routine sets irq_setup to point to a board&n; * specific setup routine.&n; */
DECL|variable|irq_setup
r_void
(paren
op_star
id|irq_setup
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * mips_io_port_base is the begin of the address space to which x86 style&n; * I/O ports are mapped.&n; */
DECL|variable|mips_io_port_base
r_int
r_int
id|mips_io_port_base
suffix:semicolon
multiline_comment|/*&n; * isa_slot_offset is the address where E(ISA) busaddress 0 is is mapped&n; * for the processor.&n; */
DECL|variable|isa_slot_offset
r_int
r_int
id|isa_slot_offset
suffix:semicolon
r_extern
r_void
id|sgi_sysinit
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|SetUpBootInfo
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|loadmmu
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|prom_init
c_func
(paren
r_int
comma
r_char
op_star
op_star
comma
r_char
op_star
op_star
comma
r_int
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * Probe whether cpu has config register by trying to play with&n; * alternate cache bit and see whether it matters.&n; * It&squot;s used by cpu_probe to distinguish between R3000A and R3081.&n; */
DECL|function|cpu_has_confreg
r_static
r_inline
r_int
id|cpu_has_confreg
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_CPU_R3000
r_extern
r_int
r_int
id|r3k_cache_size
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|size1
comma
id|size2
suffix:semicolon
r_int
r_int
id|cfg
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_CONF
)paren
suffix:semicolon
id|size1
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_DE
)paren
suffix:semicolon
id|write_32bit_cp0_register
c_func
(paren
id|CP0_CONF
comma
id|cfg
op_xor
id|CONF_AC
)paren
suffix:semicolon
id|size2
op_assign
id|r3k_cache_size
c_func
(paren
id|ST0_DE
)paren
suffix:semicolon
id|write_32bit_cp0_register
c_func
(paren
id|CP0_CONF
comma
id|cfg
)paren
suffix:semicolon
r_return
id|size1
op_ne
id|size2
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|cpu_probe
r_static
r_inline
r_void
id|cpu_probe
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|prid
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_PRID
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|prid
op_amp
l_int|0xff00
)paren
(brace
r_case
id|PRID_IMP_R2000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R2000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R3000
suffix:colon
r_if
c_cond
(paren
(paren
id|prid
op_amp
l_int|0xff
)paren
op_eq
id|PRID_REV_R3000A
)paren
r_if
c_cond
(paren
id|cpu_has_confreg
c_func
(paren
)paren
)paren
(brace
id|mips_cputype
op_assign
id|CPU_R3081E
suffix:semicolon
)brace
r_else
id|mips_cputype
op_assign
id|CPU_R3000A
suffix:semicolon
r_else
id|mips_cputype
op_assign
id|CPU_R3000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4000
suffix:colon
r_if
c_cond
(paren
(paren
id|prid
op_amp
l_int|0xff
)paren
op_eq
id|PRID_REV_R4400
)paren
(brace
id|mips_cputype
op_assign
id|CPU_R4400SC
suffix:semicolon
)brace
r_else
id|mips_cputype
op_assign
id|CPU_R4000SC
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4600
suffix:colon
id|mips_cputype
op_assign
id|CPU_R4600
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4650
suffix:colon
id|mips_cputype
op_assign
id|CPU_R4650
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R4700
suffix:colon
id|mips_cputype
op_assign
id|CPU_R4700
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R5000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R5000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_NEVADA
suffix:colon
id|mips_cputype
op_assign
id|CPU_NEVADA
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R6000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R6000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R6000A
suffix:colon
id|mips_cputype
op_assign
id|CPU_R6000A
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R8000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R8000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_R10000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R10000
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PRID_IMP_RM7000
suffix:colon
id|mips_cputype
op_assign
id|CPU_R5000
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|mips_cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
)brace
)brace
DECL|function|init_arch
id|asmlinkage
r_void
id|__init
id|init_arch
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_int
op_star
id|prom_vec
)paren
(brace
r_int
r_int
id|s
suffix:semicolon
multiline_comment|/* Determine which MIPS variant we are running on. */
id|cpu_probe
c_func
(paren
)paren
suffix:semicolon
id|prom_init
c_func
(paren
id|argc
comma
id|argv
comma
id|envp
comma
id|prom_vec
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_IP22
id|sgi_sysinit
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_COBALT_MICRO_SERVER
id|SetUpBootInfo
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * Determine the mmu/cache attached to this machine,&n;&t; * then flush the tlb and caches.  On the r4xx0&n;&t; * variants this also sets CP0_WIRED to zero.&n;&t; */
id|loadmmu
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Disable coprocessors */
id|s
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
)paren
suffix:semicolon
id|s
op_and_assign
op_complement
(paren
id|ST0_CU1
op_or
id|ST0_CU2
op_or
id|ST0_CU3
op_or
id|ST0_KX
op_or
id|ST0_SX
)paren
suffix:semicolon
id|s
op_or_assign
id|ST0_CU0
suffix:semicolon
id|write_32bit_cp0_register
c_func
(paren
id|CP0_STATUS
comma
id|s
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Main should never return here, but&n;&t; * just in case, we know what happens.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|start_kernel
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|default_irq_setup
r_static
r_void
id|__init
id|default_irq_setup
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unknown machtype in init_IRQ&quot;
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
r_void
id|baget_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|cobalt_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|decstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|deskstation_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|jazz_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sni_rm200_pci_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|sgi_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|ddb_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|orion_setup
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Save defaults for configuration-dependent routines.  */
id|irq_setup
op_assign
id|default_irq_setup
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_FD
id|fd_ops
op_assign
op_amp
id|no_fd_ops
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_IDE
id|ide_ops
op_assign
op_amp
id|no_ide_ops
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_PC_KEYB
id|kbd_ops
op_assign
op_amp
id|no_kbd_ops
suffix:semicolon
macro_line|#endif
id|rtc_ops
op_assign
op_amp
id|no_rtc_ops
suffix:semicolon
r_switch
c_cond
(paren
id|mips_machgroup
)paren
(brace
macro_line|#ifdef CONFIG_BAGET_MIPS
r_case
id|MACH_GROUP_BAGET
suffix:colon
id|baget_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_COBALT_MICRO_SERVER
r_case
id|MACH_GROUP_COBALT
suffix:colon
id|cobalt_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DECSTATION
r_case
id|MACH_GROUP_DEC
suffix:colon
id|decstation_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS_JAZZ
r_case
id|MACH_GROUP_JAZZ
suffix:colon
id|jazz_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP22
multiline_comment|/* As of now this is only IP22.  */
r_case
id|MACH_GROUP_SGI
suffix:colon
id|sgi_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SNI_RM200_PCI
r_case
id|MACH_GROUP_SNI_RM
suffix:colon
id|sni_rm200_pci_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_DDB5074
r_case
id|MACH_GROUP_NEC_DDB
suffix:colon
id|ddb_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_ORION
r_case
id|MACH_GROUP_ORION
suffix:colon
id|orion_setup
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|panic
c_func
(paren
l_string|&quot;Unsupported architecture&quot;
)paren
suffix:semicolon
)brace
id|strncpy
(paren
id|command_line
comma
id|arcs_cmdline
comma
id|CL_SIZE
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|saved_command_line
comma
id|command_line
comma
id|CL_SIZE
)paren
suffix:semicolon
id|saved_command_line
(braket
id|CL_SIZE
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|command_line
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
macro_line|#error &quot;Fixme, I&squot;m broken.&quot;
id|tmp
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|_end
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_amp
id|PAGE_MASK
)paren
op_minus
l_int|8
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OL
(paren
r_int
r_int
)paren
op_amp
id|_end
)paren
id|tmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|initrd_header
op_assign
(paren
r_int
r_int
op_star
)paren
id|tmp
suffix:semicolon
r_if
c_cond
(paren
id|initrd_header
(braket
l_int|0
)braket
op_eq
l_int|0x494E5244
)paren
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|initrd_header
(braket
l_int|2
)braket
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|initrd_header
(braket
l_int|1
)braket
suffix:semicolon
id|initrd_below_start_ok
op_assign
l_int|1
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
r_else
op_star
id|memory_start_p
op_assign
id|initrd_end
suffix:semicolon
)brace
macro_line|#endif
id|paging_init
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|r3081_wait
r_void
id|r3081_wait
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|cfg
op_assign
id|read_32bit_cp0_register
c_func
(paren
id|CP0_CONF
)paren
suffix:semicolon
id|write_32bit_cp0_register
c_func
(paren
id|CP0_CONF
comma
id|cfg
op_or
id|CONF_HALT
)paren
suffix:semicolon
)brace
DECL|function|r4k_wait
r_void
id|r4k_wait
c_func
(paren
r_void
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;.set&bslash;tmips3&bslash;n&bslash;t&quot;
l_string|&quot;wait&bslash;n&bslash;t&quot;
l_string|&quot;.set&bslash;tmips0&quot;
)paren
suffix:semicolon
)brace
eof
