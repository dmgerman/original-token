multiline_comment|/* $Id: setup.c,v 1.9 2000/03/14 01:39:27 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995 Linus Torvalds&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999 Ralf Baechle&n; * Copyright (C) 1996 Stoned Elipot&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
macro_line|#ifdef CONFIG_BLK_DEV_RAM
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/cpu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/stackframe.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#ifdef CONFIG_SGI_IP27
multiline_comment|/* XXX Origin garbage has no business in this file  */
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
macro_line|#endif
macro_line|#ifndef CONFIG_SMP
DECL|variable|cpu_data
r_struct
id|cpuinfo_mips
id|cpu_data
(braket
l_int|1
)braket
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Not all of the MIPS CPUs have the &quot;wait&quot; instruction available.  This&n; * is set to true if it is available.  The wait instruction stops the&n; * pipeline and reduces the power consumption of the CPU very much.&n; */
DECL|variable|wait_available
r_char
id|wait_available
suffix:semicolon
multiline_comment|/*&n; * Do we have a cyclecounter available?&n; */
DECL|variable|cyclecounter_available
r_char
id|cyclecounter_available
suffix:semicolon
multiline_comment|/*&n; * Set if box has EISA slots.&n; */
DECL|variable|EISA_bus
r_int
id|EISA_bus
op_assign
l_int|0
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
macro_line|#ifdef CONFIG_BLK_DEV_IDE
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
multiline_comment|/*&n; * Setup information&n; *&n; * These are initialized so they are in the .data section&n; */
DECL|variable|mips_memory_upper
r_int
r_int
id|mips_memory_upper
op_assign
id|KSEG0
suffix:semicolon
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
r_extern
r_void
id|load_mmu
c_func
(paren
r_void
)paren
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
multiline_comment|/*&n; * mips_io_port_base is the begin of the address space to which x86 style&n; * I/O ports are mapped.&n; */
macro_line|#ifdef CONFIG_SGI_IP27
multiline_comment|/* XXX Origin garbage has no business in this file  */
DECL|variable|mips_io_port_base
r_int
r_int
id|mips_io_port_base
op_assign
id|IO_BASE
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|ip22_setup
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ip27_setup
c_func
(paren
r_void
)paren
suffix:semicolon
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
r_default
suffix:colon
id|mips_cputype
op_assign
id|CPU_UNKNOWN
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_int
r_int
id|tmp
suffix:semicolon
r_int
r_int
op_star
id|initrd_header
suffix:semicolon
macro_line|#endif
r_int
id|i
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
id|kpmdtbl
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
id|kptbl
suffix:semicolon
id|cpu_probe
c_func
(paren
)paren
suffix:semicolon
id|load_mmu
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_IP22
id|ip22_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_IP27
id|ip27_setup
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
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
macro_line|#error &quot;Initrd is broken, please fit it.&quot;
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
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kptbl
comma
l_int|0
comma
id|PAGE_SIZE
op_lshift
id|KPTBL_PAGE_ORDER
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|kpmdtbl
comma
l_int|0
comma
id|PAGE_SIZE
)paren
suffix:semicolon
id|pgd_set
c_func
(paren
id|swapper_pg_dir
comma
id|kpmdtbl
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
(paren
l_int|1
op_lshift
id|KPTBL_PAGE_ORDER
)paren
suffix:semicolon
id|pmd
op_increment
comma
id|i
op_increment
comma
id|pte
op_add_assign
id|PTRS_PER_PTE
)paren
id|pmd_val
c_func
(paren
op_star
id|pmd
)paren
op_assign
(paren
r_int
r_int
)paren
id|pte
suffix:semicolon
)brace
eof
