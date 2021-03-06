multiline_comment|/*    $Id: setup.c,v 1.8 2000/02/02 04:42:38 prumpf Exp $&n; *&n; *    Initial setup-routines for HP 9000 based hardware.&n; * &n; *    Copyright (C) 1991, 1992, 1995  Linus Torvalds&n; *    Modifications for PA-RISC (C) 1999 Helge Deller &lt;helge.deller@ruhr-uni-bochum.de&gt;&n; *    Modifications copyright 1999 SuSE GmbH (Philipp Rumpf)&n; *    Modifications copyright 2000 Martin K. Petersen &lt;mkp@mkp.net&gt;&n; *    Modifications copyright 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n; *&n; *    Initial PA-RISC Version: 04-23-1999 by Helge Deller&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; * &n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;&t;/* for register_driver() stuff */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pdc.h&gt;
macro_line|#include &lt;asm/led.h&gt;
macro_line|#include &lt;asm/real.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;&t;/* for pa7300lc_init() proto */
macro_line|#include &lt;asm/irq.h&gt;&t;&t;/* for struct irq_region */
macro_line|#include &lt;asm/pdcpat.h&gt;&t;&t;/* for PA_VIEW PDC_PAT_CPU_GET_NUMBER etc */
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|macro|COMMAND_LINE_SIZE
mdefine_line|#define COMMAND_LINE_SIZE 1024
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
id|COMMAND_LINE_SIZE
)braket
suffix:semicolon
multiline_comment|/*&n;** KLUGE ALERT!&n;**&n;** We *really* should be using a combination of request_resource()&n;** and request_region()! But request_region() requires kmalloc since&n;** returns a new struct resource. And kmalloc just isn&squot;t available&n;** until after mem_init() is called from start_kernel().&n;**&n;** FIXME: assume contiguous memory initially.&n;**     Additional chunks of memory might be added to sysram_resource.sibling.&n;*/
DECL|variable|sysrom_resource
r_static
r_struct
id|resource
id|sysrom_resource
op_assign
(brace
id|name
suffix:colon
l_string|&quot;System ROM&quot;
comma
id|start
suffix:colon
l_int|0x0f0000000UL
comma
id|end
suffix:colon
l_int|0x0f00fffffUL
comma
id|flags
suffix:colon
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
id|parent
suffix:colon
op_amp
id|iomem_resource
comma
id|sibling
suffix:colon
l_int|NULL
comma
id|child
suffix:colon
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pdcdata_resource
r_static
r_struct
id|resource
id|pdcdata_resource
suffix:semicolon
DECL|variable|sysram_resource
r_static
r_struct
id|resource
id|sysram_resource
op_assign
(brace
id|name
suffix:colon
l_string|&quot;System RAM&quot;
comma
id|start
suffix:colon
l_int|0UL
comma
id|end
suffix:colon
op_complement
l_int|0UL
multiline_comment|/* bogus */
comma
id|flags
suffix:colon
id|IORESOURCE_MEM
comma
id|parent
suffix:colon
op_amp
id|iomem_resource
comma
id|sibling
suffix:colon
op_amp
id|sysrom_resource
comma
id|child
suffix:colon
op_amp
id|pdcdata_resource
)brace
suffix:semicolon
r_extern
r_char
id|_text
suffix:semicolon
multiline_comment|/* start of kernel code, defined by linker */
r_extern
r_int
id|data_start
suffix:semicolon
r_extern
r_char
id|_edata
suffix:semicolon
multiline_comment|/* end of data, begin BSS, defined by linker */
r_extern
r_char
id|_end
suffix:semicolon
multiline_comment|/* end of BSS, defined by linker */
DECL|variable|data_resource
r_static
r_struct
id|resource
id|data_resource
op_assign
(brace
id|name
suffix:colon
l_string|&quot;kernel Data&quot;
comma
id|start
suffix:colon
id|virt_to_phys
c_func
(paren
op_amp
id|data_start
)paren
comma
id|end
suffix:colon
id|virt_to_phys
c_func
(paren
op_amp
id|_end
)paren
op_minus
l_int|1
comma
id|flags
suffix:colon
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
id|parent
suffix:colon
op_amp
id|sysram_resource
comma
id|sibling
suffix:colon
l_int|NULL
comma
id|child
suffix:colon
l_int|NULL
)brace
suffix:semicolon
DECL|variable|code_resource
r_static
r_struct
id|resource
id|code_resource
op_assign
(brace
id|name
suffix:colon
l_string|&quot;Kernel Code&quot;
comma
id|start
suffix:colon
id|virt_to_phys
c_func
(paren
op_amp
id|_text
)paren
comma
id|end
suffix:colon
id|virt_to_phys
c_func
(paren
op_amp
id|data_start
)paren
op_minus
l_int|1
comma
id|flags
suffix:colon
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
id|parent
suffix:colon
op_amp
id|sysram_resource
comma
id|sibling
suffix:colon
op_amp
id|data_resource
comma
id|child
suffix:colon
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pdcdata_resource
r_static
r_struct
id|resource
id|pdcdata_resource
op_assign
(brace
id|name
suffix:colon
l_string|&quot;PDC data (Page Zero)&quot;
comma
id|start
suffix:colon
l_int|0
comma
id|end
suffix:colon
l_int|0x9ff
comma
id|flags
suffix:colon
id|IORESOURCE_BUSY
op_or
id|IORESOURCE_MEM
comma
id|parent
suffix:colon
op_amp
id|sysram_resource
comma
id|sibling
suffix:colon
op_amp
id|code_resource
comma
id|child
suffix:colon
l_int|NULL
)brace
suffix:semicolon
DECL|variable|boot_cpu_data
r_struct
id|system_cpuinfo_parisc
id|boot_cpu_data
suffix:semicolon
DECL|variable|cpu_data
r_struct
id|cpuinfo_parisc
id|cpu_data
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|do_inventory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|hp_device
op_star
id|register_module
c_func
(paren
r_void
op_star
id|hpa
)paren
suffix:semicolon
r_static
r_int
id|cpu_driver_callback
c_func
(paren
r_struct
id|hp_device
op_star
comma
r_struct
id|pa_iodc_driver
op_star
)paren
suffix:semicolon
DECL|variable|cpu_drivers_for
r_static
r_struct
id|pa_iodc_driver
id|cpu_drivers_for
(braket
)braket
op_assign
(brace
(brace
id|HPHW_NPROC
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0x0
comma
l_int|0
comma
l_int|0
comma
id|DRIVER_CHECK_HWTYPE
comma
l_string|&quot;CPU&quot;
comma
l_string|&quot;PARISC&quot;
comma
(paren
r_void
op_star
)paren
id|cpu_driver_callback
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
(paren
r_char
op_star
)paren
l_int|NULL
comma
(paren
r_char
op_star
)paren
l_int|NULL
comma
(paren
r_void
op_star
)paren
l_int|NULL
)brace
)brace
suffix:semicolon
DECL|variable|fallback_cpu_hpa
r_static
r_int
id|fallback_cpu_hpa
(braket
)braket
op_assign
(brace
l_int|0xfffa0000L
comma
l_int|0xfffbe000L
comma
l_int|0x0
)brace
suffix:semicolon
multiline_comment|/*&n;**  &t;PARISC CPU driver - claim &quot;device&quot; and initialize CPU data structures.&n;**&n;** Consolidate per CPU initialization into (mostly) one module.&n;** Monarch CPU will initialize boot_cpu_data which shouldn&squot;t&n;** change once the system has booted.&n;**&n;** The callback *should* do per-instance initialization of&n;** everything including the monarch. Some of the code that&squot;s&n;** in setup.c:start_parisc() should migrate here and start_parisc()&n;** should &quot;register_driver(cpu_driver_for)&quot; before calling&n;** do_inventory().&n;**&n;** The goal of consolidating CPU initialization into one place is&n;** to make sure all CPU&squot;s get initialized the same way.&n;** It would be nice if the even the manarch through the exact same code path.&n;** (up to rendevous at least).&n;*/
DECL|macro|ASSERT
macro_line|#undef ASSERT
DECL|macro|ASSERT
mdefine_line|#define ASSERT(expr) &bslash;&n;&t;if(!(expr)) { &bslash;&n;&t;&t;printk( &quot;&bslash;n&quot; __FILE__ &quot;:%d: Assertion &quot; #expr &quot; failed!&bslash;n&quot;,__LINE__); &bslash;&n;&t;&t;panic(#expr); &bslash;&n;&t;}
r_static
r_int
DECL|function|cpu_driver_callback
id|cpu_driver_callback
c_func
(paren
r_struct
id|hp_device
op_star
id|d
comma
r_struct
id|pa_iodc_driver
op_star
id|dri
)paren
(brace
macro_line|#ifdef __LP64__
r_extern
r_int
id|pdc_pat
suffix:semicolon
multiline_comment|/* arch/parisc/kernel/inventory.c */
r_static
r_int
r_int
id|pdc_result
(braket
l_int|32
)braket
id|__attribute__
(paren
(paren
id|aligned
(paren
l_int|8
)paren
)paren
)paren
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
macro_line|#endif
r_struct
id|cpuinfo_parisc
op_star
id|p
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
r_if
c_cond
(paren
id|boot_cpu_data.cpu_count
OG
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;CONFIG_SMP disabled - not claiming addional CPUs&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
id|p
op_assign
op_amp
id|cpu_data
(braket
id|boot_cpu_data.cpu_count
)braket
suffix:semicolon
id|boot_cpu_data.cpu_count
op_increment
suffix:semicolon
multiline_comment|/* TODO: Enable FP regs - done early in start_parisc() now */
multiline_comment|/* initialize counters */
id|memset
c_func
(paren
id|p
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cpuinfo_parisc
)paren
)paren
suffix:semicolon
id|p-&gt;hpa
op_assign
(paren
r_int
r_int
)paren
id|d-&gt;hpa
suffix:semicolon
multiline_comment|/* save CPU hpa */
macro_line|#ifdef __LP64__
r_if
c_cond
(paren
id|pdc_pat
)paren
(brace
id|ulong
id|status
suffix:semicolon
id|pdc_pat_cell_mod_maddr_block_t
id|pa_pdc_cell
suffix:semicolon
id|status
op_assign
id|pdc_pat_cell_module
c_func
(paren
op_amp
id|pdc_result
comma
id|d-&gt;pcell_loc
comma
id|d-&gt;mod_index
comma
id|PA_VIEW
comma
op_amp
id|pa_pdc_cell
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|PDC_RET_OK
op_eq
id|status
)paren
suffix:semicolon
multiline_comment|/* verify it&squot;s the same as what do_pat_inventory() found */
id|ASSERT
c_func
(paren
id|d-&gt;mod_info
op_eq
id|pa_pdc_cell.mod_info
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|d-&gt;pmod_loc
op_eq
id|pa_pdc_cell.mod_location
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|d-&gt;mod_path
op_eq
id|pa_pdc_cell.mod_path
)paren
suffix:semicolon
id|p-&gt;txn_addr
op_assign
id|pa_pdc_cell.mod
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* id_eid for IO sapic */
multiline_comment|/* get the cpu number */
id|status
op_assign
id|mem_pdc_call
c_func
(paren
id|PDC_PAT_CPU
comma
id|PDC_PAT_CPU_GET_NUMBER
comma
id|__pa
c_func
(paren
op_amp
id|pdc_result
)paren
comma
id|d-&gt;hpa
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|PDC_RET_OK
op_eq
id|status
)paren
suffix:semicolon
id|p-&gt;cpuid
op_assign
id|pdc_result
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
macro_line|#endif
(brace
id|p-&gt;txn_addr
op_assign
(paren
r_int
r_int
)paren
id|d-&gt;hpa
suffix:semicolon
multiline_comment|/* for normal parisc */
multiline_comment|/* logical CPU ID and update global counter */
id|p-&gt;cpuid
op_assign
id|boot_cpu_data.cpu_count
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t;** itimer and ipi IRQ handlers are statically initialized in&n;&t;** arch/parisc/kernel/irq.c&n;&t;*/
id|p-&gt;region
op_assign
id|irq_region
(braket
id|IRQ_FROM_REGION
c_func
(paren
id|CPU_IRQ_REGION
)paren
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__xchg_called_with_bad_pointer
r_void
id|__xchg_called_with_bad_pointer
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_EMERG
l_string|&quot;xchg() called with bad pointer !&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Some versions of IODC don&squot;t list the CPU, and since we don&squot;t walk&n; * the bus yet, we have to probe for processors at well known hpa&n; * addresses.  &n; */
DECL|function|register_fallback_cpu
r_void
id|__init
id|register_fallback_cpu
(paren
r_void
)paren
(brace
r_struct
id|hp_device
op_star
id|d
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|#error &quot;Revisit CPU fallback addresses for SMP (Assuming bus walk hasn&squot;t been implemented)&quot;
macro_line|#endif
id|printk
(paren
l_string|&quot;No CPUs reported by firmware - probing...&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|fallback_cpu_hpa
(braket
id|i
)braket
)paren
(brace
id|d
op_assign
id|register_module
(paren
(paren
r_void
op_star
)paren
id|fallback_cpu_hpa
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d
OG
l_int|0
)paren
(brace
id|printk
(paren
l_string|&quot;Found CPU at %lx&bslash;n&quot;
comma
id|fallback_cpu_hpa
(braket
id|i
)braket
)paren
suffix:semicolon
id|cpu_driver_callback
(paren
id|d
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|i
op_increment
suffix:semicolon
)brace
id|panic
(paren
l_string|&quot;No CPUs found.  System halted.&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Get CPU information and store it in the boot_cpu_data structure.  */
DECL|function|collect_boot_cpu_data
r_void
id|__init
id|collect_boot_cpu_data
c_func
(paren
r_void
)paren
(brace
id|memset
c_func
(paren
op_amp
id|boot_cpu_data
comma
l_int|0
comma
r_sizeof
(paren
id|boot_cpu_data
)paren
)paren
suffix:semicolon
id|boot_cpu_data.cpu_hz
op_assign
l_int|100
op_star
id|PAGE0-&gt;mem_10msec
suffix:semicolon
multiline_comment|/* Hz of this PARISC */
multiline_comment|/* get CPU-Model Information... */
DECL|macro|p
mdefine_line|#define p ((unsigned long *)&amp;boot_cpu_data.pdc.model)
r_if
c_cond
(paren
id|pdc_model_info
c_func
(paren
op_amp
id|boot_cpu_data.pdc.model
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;model&t;%08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx %08lx&bslash;n&quot;
comma
id|p
(braket
l_int|0
)braket
comma
id|p
(braket
l_int|1
)braket
comma
id|p
(braket
l_int|2
)braket
comma
id|p
(braket
l_int|3
)braket
comma
id|p
(braket
l_int|4
)braket
comma
id|p
(braket
l_int|5
)braket
comma
id|p
(braket
l_int|6
)braket
comma
id|p
(braket
l_int|7
)braket
comma
id|p
(braket
l_int|8
)braket
)paren
suffix:semicolon
)brace
DECL|macro|p
macro_line|#undef p
r_if
c_cond
(paren
id|pdc_model_versions
c_func
(paren
op_amp
id|boot_cpu_data.pdc.versions
comma
l_int|0
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;vers&t;%08lx&bslash;n&quot;
comma
id|boot_cpu_data.pdc.versions.cpuid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pdc_model_cpuid
c_func
(paren
op_amp
id|boot_cpu_data.pdc.cpuid
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;cpuid&t;%08lx&bslash;n&quot;
comma
id|boot_cpu_data.pdc.cpuid.cpuid
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;CPUID&t;vers %ld rev %ld&bslash;n&quot;
comma
(paren
id|boot_cpu_data.pdc.cpuid.cpuid
op_rshift
l_int|5
)paren
op_amp
l_int|127
comma
id|boot_cpu_data.pdc.cpuid.cpuid
op_amp
l_int|31
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pdc_model_sysmodel
c_func
(paren
id|boot_cpu_data.pdc.sys_model_name
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;model&t;%s&bslash;n&quot;
comma
id|boot_cpu_data.pdc.sys_model_name
)paren
suffix:semicolon
id|boot_cpu_data.model_name
op_assign
id|parisc_getHWdescription
c_func
(paren
id|HPHW_NPROC
comma
id|boot_cpu_data.pdc.model.hversion
op_rshift
l_int|4
comma
id|boot_cpu_data.pdc.model.sversion
op_rshift
l_int|8
)paren
suffix:semicolon
id|boot_cpu_data.hversion
op_assign
id|boot_cpu_data.pdc.model.hversion
suffix:semicolon
id|boot_cpu_data.sversion
op_assign
id|boot_cpu_data.pdc.model.sversion
suffix:semicolon
id|boot_cpu_data.cpu_type
op_assign
id|parisc_get_cpu_type
c_func
(paren
id|boot_cpu_data.pdc.model.hversion
)paren
suffix:semicolon
id|boot_cpu_data.cpu_name
op_assign
id|cpu_name_version
(braket
id|boot_cpu_data.cpu_type
)braket
(braket
l_int|0
)braket
suffix:semicolon
id|boot_cpu_data.family_name
op_assign
id|cpu_name_version
(braket
id|boot_cpu_data.cpu_type
)braket
(braket
l_int|1
)braket
suffix:semicolon
)brace
macro_line|#ifdef __LP64__
DECL|macro|COMMAND_GLOBAL
mdefine_line|#define COMMAND_GLOBAL  0xfffffffffffe0030UL
macro_line|#else
DECL|macro|COMMAND_GLOBAL
mdefine_line|#define COMMAND_GLOBAL  0xfffe0030
macro_line|#endif
DECL|macro|CMD_RESET
mdefine_line|#define CMD_RESET       5       /* reset any module */
multiline_comment|/*&n;** The Wright Brothers and Gecko systems have a H/W problem&n;** (Lasi...&squot;nuf said) may cause a broadcast reset to lockup&n;** the system. An HVERSION dependent PDC call was developed&n;** to perform a &quot;safe&quot;, platform specific broadcast reset instead&n;** of kludging up all the code.&n;**&n;** Older machines which do not implement PDC_BROADCAST_RESET will&n;** return (with an error) and the regular broadcast reset can be&n;** issued. Obviously, if the PDC does implement PDC_BROADCAST_RESET&n;** the PDC call will not return (the system will be reset).&n;*/
r_static
r_int
DECL|function|reset_parisc
id|reset_parisc
c_func
(paren
r_struct
id|notifier_block
op_star
id|self
comma
r_int
r_int
id|command
comma
r_void
op_star
id|ptr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: %s(cmd=%lu)&bslash;n&quot;
comma
id|__FILE__
comma
id|__FUNCTION__
comma
id|command
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|command
)paren
(brace
r_case
id|MACH_RESTART
suffix:colon
macro_line|#ifdef FASTBOOT_SELFTEST_SUPPORT
multiline_comment|/*&n;&t;&t;** If user has modified the Firmware Selftest Bitmap,&n;&t;&t;** run the tests specified in the bitmap after the&n;&t;&t;** system is rebooted w/PDC_DO_RESET.&n;&t;&t;**&n;&t;&t;** ftc_bitmap = 0x1AUL &quot;Skip destructive memory tests&quot;&n;&t;&t;**&n;&t;&t;** Using &quot;directed resets&quot; at each processor with the MEM_TOC&n;&t;&t;** vector cleared will also avoid running destructive&n;&t;&t;** memory self tests. (Not implemented yet)&n;&t;&t;*/
r_if
c_cond
(paren
id|ftc_bitmap
)paren
(brace
id|mem_pdc_call
c_func
(paren
id|PDC_BROADCAST_RESET
comma
id|PDC_DO_FIRM_TEST_RESET
comma
id|PDC_FIRM_TEST_MAGIC
comma
id|ftc_bitmap
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* &quot;Normal&quot; system reset */
(paren
r_void
)paren
id|mem_pdc_call
c_func
(paren
id|PDC_BROADCAST_RESET
comma
id|PDC_DO_RESET
comma
l_int|0L
comma
l_int|0L
comma
l_int|0L
)paren
suffix:semicolon
multiline_comment|/* Nope...box should reset with just CMD_RESET now */
id|gsc_writel
c_func
(paren
id|CMD_RESET
comma
id|COMMAND_GLOBAL
)paren
suffix:semicolon
multiline_comment|/* Wait for RESET to lay us to rest. */
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|NOTIFY_DONE
suffix:semicolon
)brace
DECL|variable|parisc_block
r_static
r_struct
id|notifier_block
id|parisc_block
op_assign
(brace
id|reset_parisc
comma
l_int|NULL
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/*  start_parisc() will be called from head.S to setup our new memory_start &n;    and actually start our kernel !&n;    Memory-Layout is:&n;&t;- Kernel-Image (code+data+BSS)&n;&t;- Stack (stack-size see below!, stack-setup-code is in head.S)&n;&t;- memory_start at end of stack..&n;*/
DECL|variable|mem_start
DECL|variable|mem_max
r_int
r_int
id|mem_start
comma
id|mem_max
suffix:semicolon
DECL|variable|start_pfn
DECL|variable|max_pfn
r_int
r_int
id|start_pfn
comma
id|max_pfn
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|__init
id|start_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|PFN_UP
mdefine_line|#define PFN_UP(x)&t;(((x) + PAGE_SIZE-1) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_DOWN
mdefine_line|#define PFN_DOWN(x)&t;((x) &gt;&gt; PAGE_SHIFT)
DECL|macro|PFN_PHYS
mdefine_line|#define PFN_PHYS(x)&t;((x) &lt;&lt; PAGE_SHIFT)
DECL|function|start_parisc
r_void
id|__init
id|start_parisc
c_func
(paren
r_int
id|arg0
comma
r_int
id|arg1
comma
r_int
id|arg2
comma
r_int
id|arg3
)paren
(brace
r_register
r_int
r_int
id|ccr
suffix:semicolon
r_int
r_int
id|memory_start
suffix:semicolon
multiline_comment|/* Clear BSS */
(brace
r_char
op_star
id|p
op_assign
op_amp
id|_edata
comma
op_star
id|q
op_assign
op_amp
id|_end
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|q
)paren
(brace
op_star
id|p
op_increment
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|pdc_console_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
id|printk
c_func
(paren
l_string|&quot;The 64-bit Kernel has started...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;The 32-bit Kernel has started...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t;** Enable FP coprocessor&n;&t;**&n;&t;** REVISIT: ccr should be set by PDC_COPROC results to support PA1.0.&n;&t;** Hardcoding works for PA1.1 processors.&n;&t;**&n;&t;** REVISIT: this could be done in the &quot;code 22&quot; trap handler.&n;&t;** (frowands idea - that way we know which processes need FP&n;&t;** registers saved on the interrupt stack.)&n;&t;**&n;&t;** NEWS FLASH: wide kernels need FP coprocessor enabled to handle&n;&t;** formatted printing of %lx for example (double divides I think)&n;&t;*/
id|ccr
op_assign
l_int|0xc0
suffix:semicolon
id|mtctl
c_func
(paren
id|ccr
comma
l_int|10
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Enabled FP coprocessor&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#ifdef __LP64__
id|printk
c_func
(paren
l_string|&quot;If this is the LAST MESSAGE YOU SEE, you&squot;re probably using&bslash;n&quot;
l_string|&quot;32-bit millicode by mistake.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|memory_start
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
id|memory_start
op_assign
(paren
id|memory_start
op_plus
id|PAGE_SIZE
)paren
op_amp
id|PAGE_MASK
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Free memory starts at: 0x%lx&bslash;n&quot;
comma
id|memory_start
)paren
suffix:semicolon
multiline_comment|/* Collect stuff passed in from the boot loader */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s(0x%x,0x%x,0x%x,0x%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|arg0
comma
id|arg1
comma
id|arg2
comma
id|arg3
)paren
suffix:semicolon
multiline_comment|/* arg0 is free-mem start, arg1 is ptr to command line */
r_if
c_cond
(paren
id|arg0
OL
l_int|64
)paren
(brace
multiline_comment|/* called from hpux boot loader */
id|saved_command_line
(braket
l_int|0
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_else
(brace
id|strcpy
c_func
(paren
id|saved_command_line
comma
(paren
r_char
op_star
)paren
id|__va
c_func
(paren
id|arg1
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PALO command line: &squot;%s&squot;&bslash;nPALO initrd %x-%x&bslash;n&quot;
comma
id|saved_command_line
comma
id|arg2
comma
id|arg3
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|arg2
op_ne
l_int|0
)paren
multiline_comment|/* did palo pass us a ramdisk? */
(brace
id|initrd_start
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|arg2
)paren
suffix:semicolon
id|initrd_end
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|arg3
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
id|mem_start
op_assign
id|__pa
c_func
(paren
id|memory_start
)paren
suffix:semicolon
DECL|macro|MAX_MEM
mdefine_line|#define MAX_MEM (512*1024*1024)
id|mem_max
op_assign
(paren
id|PAGE0-&gt;imm_max_mem
OG
id|MAX_MEM
ques
c_cond
id|MAX_MEM
suffix:colon
id|PAGE0-&gt;imm_max_mem
)paren
suffix:semicolon
id|collect_boot_cpu_data
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* initialize the LCD/LED after boot_cpu_data is available ! */
id|led_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* LCD/LED initialization */
id|do_inventory
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* probe for hardware */
id|register_driver
c_func
(paren
id|cpu_drivers_for
)paren
suffix:semicolon
multiline_comment|/* claim all the CPUs */
r_if
c_cond
(paren
id|boot_cpu_data.cpu_count
op_eq
l_int|0
)paren
id|register_fallback_cpu
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU(s): %d x %s at %d.%06d MHz&bslash;n&quot;
comma
id|boot_cpu_data.cpu_count
comma
id|boot_cpu_data.cpu_name
comma
id|boot_cpu_data.cpu_hz
op_div
l_int|1000000
comma
id|boot_cpu_data.cpu_hz
op_mod
l_int|1000000
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|boot_cpu_data.cpu_type
)paren
(brace
r_case
id|pcx
suffix:colon
r_case
id|pcxs
suffix:colon
r_case
id|pcxt
suffix:colon
id|hppa_dma_ops
op_assign
op_amp
id|pcx_dma_ops
suffix:semicolon
r_break
suffix:semicolon
r_case
id|pcxl2
suffix:colon
id|pa7300lc_init
c_func
(paren
)paren
suffix:semicolon
r_case
id|pcxl
suffix:colon
multiline_comment|/* falls through */
id|hppa_dma_ops
op_assign
op_amp
id|pcxl_dma_ops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
macro_line|#if 1
multiline_comment|/* KLUGE! this really belongs in kernel/resource.c! */
id|iomem_resource.end
op_assign
op_complement
l_int|0UL
suffix:semicolon
macro_line|#endif
id|sysram_resource.end
op_assign
id|mem_max
op_minus
l_int|1
suffix:semicolon
id|notifier_chain_register
c_func
(paren
op_amp
id|mach_notifier
comma
op_amp
id|parisc_block
)paren
suffix:semicolon
id|start_kernel
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* now back to arch-generic code... */
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
r_int
r_int
id|bootmap_size
suffix:semicolon
r_int
r_int
id|start_pfn
suffix:semicolon
r_int
r_int
id|mem_free
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|saved_command_line
suffix:semicolon
multiline_comment|/* initialize bootmem */
id|start_pfn
op_assign
id|PFN_UP
c_func
(paren
id|mem_start
)paren
suffix:semicolon
id|max_pfn
op_assign
id|PFN_DOWN
c_func
(paren
id|mem_max
)paren
suffix:semicolon
id|bootmap_size
op_assign
id|init_bootmem
c_func
(paren
id|start_pfn
comma
id|max_pfn
)paren
suffix:semicolon
id|mem_start
op_add_assign
id|bootmap_size
suffix:semicolon
id|mem_free
op_assign
id|mem_max
op_minus
id|mem_start
suffix:semicolon
multiline_comment|/* free_bootmem handles rounding nicely */
id|printk
c_func
(paren
l_string|&quot;free_bootmem(0x%lx, 0x%lx)&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|mem_start
comma
(paren
r_int
r_int
)paren
id|mem_free
)paren
suffix:semicolon
id|free_bootmem
c_func
(paren
id|mem_start
comma
id|mem_free
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
id|printk
c_func
(paren
l_string|&quot;initrd: %08x-%08x&bslash;n&quot;
comma
(paren
r_int
)paren
id|initrd_start
comma
(paren
r_int
)paren
id|initrd_end
)paren
suffix:semicolon
r_if
c_cond
(paren
id|initrd_end
op_ne
l_int|0
)paren
(brace
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
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
)brace
macro_line|#endif
id|cache_init
c_func
(paren
)paren
suffix:semicolon
id|paging_init
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
op_amp
id|init_task_union
op_amp
(paren
id|INIT_TASK_SIZE
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;init_task_union not aligned.  Please recompile the kernel after changing the first line in arch/parisc/kernel/init_task.c from &bslash;n&bslash;&quot;#define PAD 0&bslash;&quot; to&bslash;n&bslash;&quot;#define PAD 1&bslash;&quot; or vice versa&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_SERIAL_CONSOLE
multiline_comment|/* nothing */
macro_line|#elif CONFIG_VT
macro_line|#if   defined(CONFIG_STI_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
multiline_comment|/* we use take_over_console() later ! */
macro_line|#elif defined(CONFIG_IODC_CONSOLE)
id|conswitchp
op_assign
op_amp
id|prom_con
suffix:semicolon
multiline_comment|/* it&squot;s currently really &quot;prom_con&quot; */
macro_line|#elif defined(CONFIG_DUMMY_CONSOLE)
id|conswitchp
op_assign
op_amp
id|dummy_con
suffix:semicolon
macro_line|#endif
macro_line|#endif
)brace
macro_line|#ifdef CONFIG_PROC_FS
multiline_comment|/*&n; *&t;Get CPU information for use by procfs.&n; */
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
r_int
id|n
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
OL
id|boot_cpu_data.cpu_count
suffix:semicolon
id|n
op_increment
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
l_int|1
op_lshift
id|n
)paren
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;processor&bslash;t: %d&bslash;n&quot;
l_string|&quot;cpu family&bslash;t: PA-RISC %s&bslash;n&quot;
comma
id|n
comma
id|boot_cpu_data.family_name
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
comma
id|boot_cpu_data.cpu_name
)paren
suffix:semicolon
multiline_comment|/* cpu MHz */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;cpu MHz&bslash;t&bslash;t: %d.%06d&bslash;n&quot;
comma
id|boot_cpu_data.cpu_hz
op_div
l_int|1000000
comma
id|boot_cpu_data.cpu_hz
op_mod
l_int|1000000
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;model&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;model name&bslash;t: %s&bslash;n&quot;
comma
id|boot_cpu_data.pdc.sys_model_name
comma
id|boot_cpu_data.model_name
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;hversion&bslash;t: 0x%08x&bslash;n&quot;
l_string|&quot;sversion&bslash;t: 0x%08x&bslash;n&quot;
comma
id|boot_cpu_data.hversion
comma
id|boot_cpu_data.sversion
)paren
suffix:semicolon
id|p
op_add_assign
id|get_cache_info
c_func
(paren
id|p
)paren
suffix:semicolon
multiline_comment|/* print cachesize info ? */
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;bogomips&bslash;t: %lu.%02lu&bslash;n&quot;
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
r_return
id|p
op_minus
id|buffer
suffix:semicolon
)brace
macro_line|#endif
eof
