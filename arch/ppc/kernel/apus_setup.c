multiline_comment|/*&n; *  linux/arch/ppc/kernel/apus_setup.c&n; *&n; *  Copyright (C) 1998  Jesper Skov&n; *&n; *  Basically what is needed to replace functionality found in&n; *  arch/m68k allowing Amiga drivers to work under APUS.&n; *  Bits of code and/or ideas from arch/m68k and arch/ppc files.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kd.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/amigappc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|m68k_machtype
r_int
r_int
id|m68k_machtype
suffix:semicolon
DECL|variable|debug_device
r_char
id|debug_device
(braket
l_int|6
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_void
(paren
op_star
id|mach_sched_init
)paren
(paren
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
)paren
id|__initdata
suffix:semicolon
multiline_comment|/* machine dependent keyboard functions */
r_int
(paren
op_star
id|mach_keyb_init
)paren
(paren
r_void
)paren
id|__initdata
suffix:semicolon
DECL|variable|mach_kbdrate
r_int
(paren
op_star
id|mach_kbdrate
)paren
(paren
r_struct
id|kbd_repeat
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_kbd_leds
r_void
(paren
op_star
id|mach_kbd_leds
)paren
(paren
r_int
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* machine dependent irq functions */
r_void
(paren
op_star
id|mach_init_IRQ
)paren
(paren
r_void
)paren
id|__initdata
suffix:semicolon
DECL|variable|mach_default_handler
r_void
(paren
op_star
(paren
op_star
id|mach_default_handler
)paren
(braket
)braket
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_model
r_void
(paren
op_star
id|mach_get_model
)paren
(paren
r_char
op_star
id|model
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_hardware_list
r_int
(paren
op_star
id|mach_get_hardware_list
)paren
(paren
r_char
op_star
id|buffer
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_get_irq_list
r_int
(paren
op_star
id|mach_get_irq_list
)paren
(paren
r_char
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_process_int
r_void
(paren
op_star
id|mach_process_int
)paren
(paren
r_int
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* machine dependent timer functions */
DECL|variable|mach_gettimeoffset
r_int
r_int
(paren
op_star
id|mach_gettimeoffset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mach_gettod
r_void
(paren
op_star
id|mach_gettod
)paren
(paren
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
comma
r_int
op_star
)paren
suffix:semicolon
DECL|variable|mach_hwclk
r_int
(paren
op_star
id|mach_hwclk
)paren
(paren
r_int
comma
r_struct
id|hwclk_time
op_star
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_set_clock_mmss
r_int
(paren
op_star
id|mach_set_clock_mmss
)paren
(paren
r_int
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_reset
r_void
(paren
op_star
id|mach_reset
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|variable|mach_max_dma_address
r_int
id|mach_max_dma_address
op_assign
l_int|0x00ffffff
suffix:semicolon
multiline_comment|/* default set to the lower 16MB */
macro_line|#if defined(CONFIG_AMIGA_FLOPPY) || defined(CONFIG_ATARI_FLOPPY)
r_void
(paren
op_star
id|mach_floppy_setup
)paren
(paren
r_char
op_star
comma
r_int
op_star
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|mach_floppy_eject
r_void
(paren
op_star
id|mach_floppy_eject
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_HEARTBEAT
DECL|variable|mach_heartbeat
r_void
(paren
op_star
id|mach_heartbeat
)paren
(paren
r_int
)paren
op_assign
l_int|NULL
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|amiga_model
suffix:semicolon
r_extern
r_int
id|decrementer_count
suffix:semicolon
multiline_comment|/* count value for 1e6/HZ microseconds */
r_extern
r_int
id|count_period_num
suffix:semicolon
multiline_comment|/* 1 decrementer count equals */
r_extern
r_int
id|count_period_den
suffix:semicolon
multiline_comment|/* count_period_num / count_period_den us */
r_extern
r_struct
id|mem_info
id|memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
multiline_comment|/* memory description */
r_extern
r_void
id|amiga_floppy_setup
c_func
(paren
r_char
op_star
comma
r_int
op_star
)paren
suffix:semicolon
r_extern
r_void
id|config_amiga
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__60nsram
r_static
r_int
id|__60nsram
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*********************************************************** SETUP */
multiline_comment|/* From arch/m68k/kernel/setup.c. */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|apus_setup_arch
c_func
(paren
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
r_extern
r_char
id|cmd_line
(braket
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_char
op_star
id|p
comma
op_star
id|q
suffix:semicolon
multiline_comment|/* Parse the command line for arch-specific options.&n;&t; * For the m68k, this is currently only &quot;debug=xxx&quot; to enable printing&n;&t; * certain kernel messages to some machine-specific device.  */
r_for
c_loop
(paren
id|p
op_assign
id|cmd_line
suffix:semicolon
id|p
op_logical_and
op_star
id|p
suffix:semicolon
)paren
(brace
id|i
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
id|p
comma
l_string|&quot;debug=&quot;
comma
l_int|6
)paren
)paren
(brace
id|strncpy
c_func
(paren
id|debug_device
comma
id|p
op_plus
l_int|6
comma
r_sizeof
(paren
id|debug_device
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|debug_device
(braket
r_sizeof
(paren
id|debug_device
)paren
op_minus
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|q
op_assign
id|strchr
c_func
(paren
id|debug_device
comma
l_char|&squot; &squot;
)paren
)paren
)paren
op_star
id|q
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|p
comma
l_string|&quot;60nsram&quot;
comma
l_int|7
)paren
)paren
(brace
id|APUS_WRITE
(paren
id|APUS_REG_WAITSTATE
comma
id|REGWAITSTATE_SETRESET
op_or
id|REGWAITSTATE_PPCR
op_or
id|REGWAITSTATE_PPCW
)paren
suffix:semicolon
id|__60nsram
op_assign
l_int|1
suffix:semicolon
id|i
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
)paren
(brace
multiline_comment|/* option processed, delete it */
r_if
c_cond
(paren
(paren
id|q
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot; &squot;
)paren
)paren
)paren
id|strcpy
c_func
(paren
id|p
comma
id|q
op_plus
l_int|1
)paren
suffix:semicolon
r_else
op_star
id|p
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|p
op_assign
id|strchr
c_func
(paren
id|p
comma
l_char|&squot; &squot;
)paren
)paren
)paren
op_increment
id|p
suffix:semicolon
)brace
)brace
id|config_amiga
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|get_current_tb
r_void
id|get_current_tb
c_func
(paren
r_int
r_int
r_int
op_star
id|time
)paren
(brace
id|__asm
id|__volatile
(paren
l_string|&quot;1:mftbu 4      &bslash;n&bslash;t&quot;
l_string|&quot;  mftb  5      &bslash;n&bslash;t&quot;
l_string|&quot;  mftbu 6      &bslash;n&bslash;t&quot;
l_string|&quot;  cmpw  4,6    &bslash;n&bslash;t&quot;
l_string|&quot;  bne   1b     &bslash;n&bslash;t&quot;
l_string|&quot;  stw   4,0(%0)&bslash;n&bslash;t&quot;
l_string|&quot;  stw   5,4(%0)&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|time
)paren
suffix:colon
l_string|&quot;r4&quot;
comma
l_string|&quot;r5&quot;
comma
l_string|&quot;r6&quot;
)paren
suffix:semicolon
)brace
DECL|function|apus_calibrate_decr
r_void
id|apus_calibrate_decr
c_func
(paren
r_void
)paren
(brace
r_int
id|freq
comma
id|divisor
suffix:semicolon
multiline_comment|/* This algorithm for determining the bus speed was&n;           contributed by Ralph Schmidt. */
r_int
r_int
r_int
id|start
comma
id|stop
suffix:semicolon
r_int
id|bus_speed
suffix:semicolon
(brace
r_int
r_int
id|loop
op_assign
id|amiga_eclock
op_div
l_int|10
suffix:semicolon
id|get_current_tb
(paren
op_amp
id|start
)paren
suffix:semicolon
r_while
c_loop
(paren
id|loop
op_decrement
)paren
(brace
r_int
r_char
id|tmp
suffix:semicolon
id|tmp
op_assign
id|ciaa.pra
suffix:semicolon
)brace
id|get_current_tb
(paren
op_amp
id|stop
)paren
suffix:semicolon
)brace
id|bus_speed
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
(paren
id|stop
op_minus
id|start
)paren
)paren
op_star
l_int|10
op_star
l_int|4
)paren
op_div
l_int|1000000
suffix:semicolon
r_if
c_cond
(paren
id|AMI_1200
op_eq
id|amiga_model
)paren
id|bus_speed
op_div_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bus_speed
op_ge
l_int|47
)paren
op_logical_and
(paren
id|bus_speed
OL
l_int|53
)paren
)paren
(brace
id|bus_speed
op_assign
l_int|50
suffix:semicolon
id|freq
op_assign
l_int|12500000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|bus_speed
op_ge
l_int|57
)paren
op_logical_and
(paren
id|bus_speed
OL
l_int|63
)paren
)paren
(brace
id|bus_speed
op_assign
l_int|60
suffix:semicolon
id|freq
op_assign
l_int|15000000
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|bus_speed
op_ge
l_int|63
)paren
op_logical_and
(paren
id|bus_speed
OL
l_int|69
)paren
)paren
(brace
id|bus_speed
op_assign
l_int|66
suffix:semicolon
id|freq
op_assign
l_int|16500000
suffix:semicolon
)brace
r_else
(brace
id|printk
(paren
l_string|&quot;APUS: Unable to determine bus speed (%d). &quot;
l_string|&quot;Defaulting to 50MHz&quot;
comma
id|bus_speed
)paren
suffix:semicolon
id|bus_speed
op_assign
l_int|50
suffix:semicolon
id|freq
op_assign
l_int|12500000
suffix:semicolon
)brace
multiline_comment|/* Ease diagnostics... */
(brace
r_extern
r_int
id|__map_without_bats
suffix:semicolon
id|printk
(paren
l_string|&quot;APUS: BATs=%d, BUS=%dMHz, RAM=%dns&bslash;n&quot;
comma
(paren
id|__map_without_bats
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
comma
id|bus_speed
comma
(paren
id|__60nsram
)paren
ques
c_cond
l_int|60
suffix:colon
l_int|70
)paren
suffix:semicolon
multiline_comment|/* print a bit more if asked politely... */
r_if
c_cond
(paren
op_logical_neg
(paren
id|ciaa.pra
op_amp
l_int|0x40
)paren
)paren
(brace
r_extern
r_int
r_int
id|bat_addrs
(braket
l_int|4
)braket
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|b
suffix:semicolon
r_for
c_loop
(paren
id|b
op_assign
l_int|0
suffix:semicolon
id|b
OL
l_int|4
suffix:semicolon
op_increment
id|b
)paren
(brace
id|printk
(paren
l_string|&quot;APUS: BAT%d &quot;
comma
id|b
)paren
suffix:semicolon
id|printk
(paren
l_string|&quot;%08x-%08x -&gt; %08x&bslash;n&quot;
comma
id|bat_addrs
(braket
id|b
)braket
(braket
l_int|0
)braket
comma
id|bat_addrs
(braket
id|b
)braket
(braket
l_int|1
)braket
comma
id|bat_addrs
(braket
id|b
)braket
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
)brace
)brace
id|freq
op_mul_assign
l_int|60
suffix:semicolon
multiline_comment|/* try to make freq/1e6 an integer */
id|divisor
op_assign
l_int|60
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;time_init: decrementer frequency = %d/%d&bslash;n&quot;
comma
id|freq
comma
id|divisor
)paren
suffix:semicolon
id|decrementer_count
op_assign
id|freq
op_div
id|HZ
op_div
id|divisor
suffix:semicolon
id|count_period_num
op_assign
id|divisor
suffix:semicolon
id|count_period_den
op_assign
id|freq
op_div
l_int|1000000
suffix:semicolon
)brace
DECL|function|arch_gettod
r_void
id|arch_gettod
c_func
(paren
r_int
op_star
id|year
comma
r_int
op_star
id|mon
comma
r_int
op_star
id|day
comma
r_int
op_star
id|hour
comma
r_int
op_star
id|min
comma
r_int
op_star
id|sec
)paren
(brace
r_if
c_cond
(paren
id|mach_gettod
)paren
id|mach_gettod
c_func
(paren
id|year
comma
id|mon
comma
id|day
comma
id|hour
comma
id|min
comma
id|sec
)paren
suffix:semicolon
r_else
op_star
id|year
op_assign
op_star
id|mon
op_assign
op_star
id|day
op_assign
op_star
id|hour
op_assign
op_star
id|min
op_assign
op_star
id|sec
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*********************************************************** FLOPPY */
macro_line|#if defined(CONFIG_AMIGA_FLOPPY) || defined(CONFIG_ATARI_FLOPPY)
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|floppy_setup
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
)paren
(brace
r_if
c_cond
(paren
id|mach_floppy_setup
)paren
id|mach_floppy_setup
(paren
id|str
comma
id|ints
)paren
suffix:semicolon
)brace
DECL|function|floppy_eject
r_void
id|floppy_eject
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|mach_floppy_eject
)paren
id|mach_floppy_eject
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*********************************************************** MEMORY */
r_extern
r_void
id|map_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|flags
)paren
suffix:semicolon
DECL|macro|KMAP_MAX
mdefine_line|#define KMAP_MAX 8
DECL|variable|kmap_chunks
r_static
r_int
r_int
id|kmap_chunks
(braket
id|KMAP_MAX
op_star
l_int|3
)braket
suffix:semicolon
DECL|variable|kmap_chunk_count
r_static
r_int
id|kmap_chunk_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Based on arch/ppc/mm/init.c:ioremap() which maps the address range&n;   to the same virtual address as the physical address - which may&n;   cause problems since Z3 IO space is not the same as PCI/ISA.&n;   This should be rewritten to something more like the m68k version. */
DECL|function|kernel_map
r_int
r_int
id|kernel_map
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|size
comma
r_int
id|cacheflag
comma
r_int
r_int
op_star
id|memavailp
)paren
(brace
r_int
r_int
id|v_ret
comma
id|end
suffix:semicolon
multiline_comment|/* Remap to 0x90000000. Related comment in ppc/mm/init.c. */
r_static
r_int
r_int
id|virt
op_assign
l_int|0x90000000
suffix:semicolon
id|v_ret
op_assign
id|virt
suffix:semicolon
r_if
c_cond
(paren
id|kmap_chunk_count
op_eq
id|KMAP_MAX
op_star
l_int|3
)paren
id|panic
(paren
l_string|&quot;kernel_map: Can only map %d chunks.&bslash;n&quot;
comma
id|KMAP_MAX
)paren
suffix:semicolon
id|kmap_chunks
(braket
id|kmap_chunk_count
op_increment
)braket
op_assign
id|phys_addr
suffix:semicolon
id|kmap_chunks
(braket
id|kmap_chunk_count
op_increment
)braket
op_assign
id|size
suffix:semicolon
id|kmap_chunks
(braket
id|kmap_chunk_count
op_increment
)braket
op_assign
id|v_ret
suffix:semicolon
r_for
c_loop
(paren
id|end
op_assign
id|phys_addr
op_plus
id|size
suffix:semicolon
id|phys_addr
OL
id|end
suffix:semicolon
id|phys_addr
op_add_assign
id|PAGE_SIZE
comma
id|virt
op_add_assign
id|PAGE_SIZE
)paren
(brace
id|map_page
c_func
(paren
op_amp
id|init_task
comma
id|virt
comma
id|phys_addr
comma
id|pgprot_val
c_func
(paren
id|PAGE_KERNEL_CI
)paren
op_or
id|_PAGE_GUARDED
)paren
suffix:semicolon
)brace
r_return
id|v_ret
suffix:semicolon
)brace
multiline_comment|/* From pgtable.h */
DECL|function|my_find_pte
r_extern
id|__inline__
id|pte_t
op_star
id|my_find_pte
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|va
)paren
(brace
id|pgd_t
op_star
id|dir
op_assign
l_int|0
suffix:semicolon
id|pmd_t
op_star
id|pmd
op_assign
l_int|0
suffix:semicolon
id|pte_t
op_star
id|pte
op_assign
l_int|0
suffix:semicolon
id|va
op_and_assign
id|PAGE_MASK
suffix:semicolon
id|dir
op_assign
id|pgd_offset
c_func
(paren
id|mm
comma
id|va
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dir
)paren
(brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|va
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd
op_logical_and
id|pmd_present
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pte
op_assign
id|pte_offset
c_func
(paren
id|pmd
comma
id|va
)paren
suffix:semicolon
)brace
)brace
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* Again simulating an m68k/mm/kmap.c function. */
DECL|function|kernel_set_cachemode
r_void
id|kernel_set_cachemode
c_func
(paren
r_int
r_int
id|address
comma
r_int
r_int
id|size
comma
r_int
r_int
id|cmode
)paren
(brace
r_int
id|mask
comma
id|flags
suffix:semicolon
r_switch
c_cond
(paren
id|cmode
)paren
(brace
r_case
id|KERNELMAP_FULL_CACHING
suffix:colon
id|mask
op_assign
op_complement
(paren
id|_PAGE_NO_CACHE
op_or
id|_PAGE_GUARDED
)paren
suffix:semicolon
id|flags
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|KERNELMAP_NOCACHE_SER
suffix:colon
id|mask
op_assign
op_complement
l_int|0
suffix:semicolon
id|flags
op_assign
(paren
id|_PAGE_NO_CACHE
op_or
id|_PAGE_GUARDED
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|panic
(paren
l_string|&quot;kernel_set_cachemode() doesn&squot;t support mode %d&bslash;n&quot;
comma
id|cmode
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|size
op_div_assign
id|PAGE_SIZE
suffix:semicolon
id|address
op_and_assign
id|PAGE_MASK
suffix:semicolon
r_while
c_loop
(paren
id|size
op_decrement
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
id|pte
op_assign
id|my_find_pte
c_func
(paren
id|init_task.mm
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;pte NULL in kernel_set_cachemode()&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte_val
(paren
op_star
id|pte
)paren
op_and_assign
id|mask
suffix:semicolon
id|pte_val
(paren
op_star
id|pte
)paren
op_or_assign
id|flags
suffix:semicolon
id|flush_tlb_page
c_func
(paren
id|find_vma
c_func
(paren
id|init_task.mm
comma
id|address
)paren
comma
id|address
)paren
suffix:semicolon
id|address
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
)brace
DECL|function|mm_ptov
r_int
r_int
id|mm_ptov
(paren
r_int
r_int
id|paddr
)paren
(brace
r_int
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|paddr
OL
l_int|16
op_star
l_int|1024
op_star
l_int|1024
)paren
id|ret
op_assign
id|ZTWO_VADDR
c_func
(paren
id|paddr
)paren
suffix:semicolon
r_else
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
id|kmap_chunk_count
suffix:semicolon
)paren
(brace
r_int
r_int
id|phys
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_int
id|size
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_int
r_int
id|virt
op_assign
id|kmap_chunks
(braket
id|i
op_increment
)braket
suffix:semicolon
r_if
c_cond
(paren
id|paddr
op_ge
id|phys
op_logical_and
id|paddr
OL
(paren
id|phys
op_plus
id|size
)paren
)paren
(brace
id|ret
op_assign
id|virt
op_plus
id|paddr
op_minus
id|phys
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
)brace
id|ret
op_assign
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|paddr
)paren
suffix:semicolon
)brace
m_exit
suffix:colon
macro_line|#ifdef DEBUGPV
id|printk
(paren
l_string|&quot;PTOV(%lx)=%lx&bslash;n&quot;
comma
id|paddr
comma
id|ret
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ret
suffix:semicolon
)brace
DECL|function|mm_end_of_chunk
r_int
id|mm_end_of_chunk
(paren
r_int
r_int
id|addr
comma
r_int
id|len
)paren
(brace
r_if
c_cond
(paren
id|memory
(braket
l_int|0
)braket
dot
id|addr
op_plus
id|memory
(braket
l_int|0
)braket
dot
id|size
op_eq
id|addr
op_plus
id|len
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*********************************************************** CACHE */
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES 32
DECL|macro|MAX_CACHE_SIZE
mdefine_line|#define MAX_CACHE_SIZE 8192
DECL|function|cache_push
r_void
id|cache_push
c_func
(paren
id|__u32
id|addr
comma
r_int
id|length
)paren
(brace
id|addr
op_assign
id|mm_ptov
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|MAX_CACHE_SIZE
OL
id|length
)paren
id|length
op_assign
id|MAX_CACHE_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
id|__asm
(paren
l_string|&quot;dcbf 0,%0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|length
op_sub_assign
id|L1_CACHE_BYTES
suffix:semicolon
)brace
multiline_comment|/* Also flush trailing block */
id|__asm
(paren
l_string|&quot;dcbf 0,%0&bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
DECL|function|cache_clear
r_void
id|cache_clear
c_func
(paren
id|__u32
id|addr
comma
r_int
id|length
)paren
(brace
r_if
c_cond
(paren
id|MAX_CACHE_SIZE
OL
id|length
)paren
id|length
op_assign
id|MAX_CACHE_SIZE
suffix:semicolon
id|addr
op_assign
id|mm_ptov
c_func
(paren
id|addr
)paren
suffix:semicolon
id|__asm
(paren
l_string|&quot;dcbf 0,%0&bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t&quot;
l_string|&quot;icbi 0,%0 &bslash;n&bslash;t&quot;
l_string|&quot;isync &bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|length
op_sub_assign
id|L1_CACHE_BYTES
suffix:semicolon
r_while
c_loop
(paren
id|length
OG
l_int|0
)paren
(brace
id|__asm
(paren
l_string|&quot;dcbf 0,%0&bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t&quot;
l_string|&quot;icbi 0,%0 &bslash;n&bslash;t&quot;
l_string|&quot;isync &bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
id|addr
op_add_assign
id|L1_CACHE_BYTES
suffix:semicolon
id|length
op_sub_assign
id|L1_CACHE_BYTES
suffix:semicolon
)brace
id|__asm
(paren
l_string|&quot;dcbf 0,%0&bslash;n&bslash;t&quot;
l_string|&quot;sync &bslash;n&bslash;t&quot;
l_string|&quot;icbi 0,%0 &bslash;n&bslash;t&quot;
l_string|&quot;isync &bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
)paren
suffix:semicolon
)brace
eof
