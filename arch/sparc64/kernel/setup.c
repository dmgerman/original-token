multiline_comment|/*  $Id: setup.c,v 1.5 1997/04/04 00:49:52 davem Exp $&n; *  linux/arch/sparc64/kernel/setup.c&n; *&n; *  Copyright (C) 1995,1996  David S. Miller (davem@caip.rutgers.edu)&n; *  Copyright (C) 1997       Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
(brace
l_int|0
comma
l_int|0
comma
)brace
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|128
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|54
comma
multiline_comment|/* orig-video-lines */
l_int|0
comma
multiline_comment|/* orig-video-isVGA */
l_int|16
multiline_comment|/* orig-video-points */
)brace
suffix:semicolon
DECL|variable|phys_bytes_of_ram
DECL|variable|end_of_phys_memory
r_int
r_int
id|phys_bytes_of_ram
comma
id|end_of_phys_memory
suffix:semicolon
DECL|function|bios32_init
r_int
r_int
id|bios32_init
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
r_return
id|memory_start
suffix:semicolon
)brace
multiline_comment|/* Typing sync at the prom prompt calls the function pointed to by&n; * the sync callback which I set to the following function.&n; * This should sync all filesystems and return, for now it just&n; * prints out pretty messages and returns.&n; */
r_extern
r_int
r_int
id|sparc64_ttable_tl0
suffix:semicolon
r_extern
r_void
id|breakpoint
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if CONFIG_SUN_CONSOLE
r_extern
r_void
id|console_restore_palette
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
id|asmlinkage
r_void
id|sys_sync
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* it&squot;s really int */
multiline_comment|/* Pretty sick eh? */
DECL|function|prom_sync_me
r_void
id|prom_sync_me
c_func
(paren
r_int
op_star
id|args
)paren
(brace
r_int
r_int
id|prom_tba
comma
id|flags
suffix:semicolon
id|save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;flushw; rdpr %%tba, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|prom_tba
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wrpr %0, 0x0, %%tba&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|sparc64_ttable_tl0
)paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_CONSOLE
id|console_restore_palette
(paren
)paren
suffix:semicolon
macro_line|#endif
id|prom_printf
c_func
(paren
l_string|&quot;PROM SYNC COMMAND...&bslash;n&quot;
)paren
suffix:semicolon
id|show_free_areas
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;pid
op_ne
l_int|0
)paren
(brace
id|sti
c_func
(paren
)paren
suffix:semicolon
id|sys_sync
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
id|prom_printf
c_func
(paren
l_string|&quot;Returning to prom&bslash;n&quot;
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;flushw; wrpr %0, 0x0, %%tba&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|prom_tba
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_extern
r_void
id|rs_kgdb_hook
c_func
(paren
r_int
id|tty_num
)paren
suffix:semicolon
multiline_comment|/* sparc/serial.c */
DECL|variable|boot_flags
r_int
r_int
id|boot_flags
op_assign
l_int|0
suffix:semicolon
DECL|macro|BOOTME_DEBUG
mdefine_line|#define BOOTME_DEBUG  0x1
DECL|macro|BOOTME_SINGLE
mdefine_line|#define BOOTME_SINGLE 0x2
DECL|macro|BOOTME_KGDB
mdefine_line|#define BOOTME_KGDB   0x4
macro_line|#ifdef CONFIG_SUN_CONSOLE
r_extern
r_char
op_star
id|console_fb_path
suffix:semicolon
DECL|variable|console_fb
r_static
r_int
id|console_fb
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|variable|memory_size
r_static
r_int
r_int
id|memory_size
op_assign
l_int|0
suffix:semicolon
DECL|function|kernel_enter_debugger
r_void
id|kernel_enter_debugger
c_func
(paren
r_void
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: Entered&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|obp_system_intr
r_int
id|obp_system_intr
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;KGDB: system interrupted&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|boot_flags
op_amp
id|BOOTME_DEBUG
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OBP: system interrupted&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* &n; * Process kernel command line switches that are specific to the&n; * SPARC or that require special low-level processing.&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|process_switch
c_func
(paren
r_char
id|c
)paren
)paren
(brace
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;d&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_DEBUG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;s&squot;
suffix:colon
id|boot_flags
op_or_assign
id|BOOTME_SINGLE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
id|prom_printf
c_func
(paren
l_string|&quot;boot_flags_init: Halt!&bslash;n&quot;
)paren
suffix:semicolon
id|halt
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;Unknown boot switch (-%c)&bslash;n&quot;
comma
id|c
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_static
r_void
id|boot_flags_init
c_func
(paren
r_char
op_star
id|commands
)paren
)paren
(brace
r_while
c_loop
(paren
op_star
id|commands
)paren
(brace
multiline_comment|/* Move to the start of the next &quot;argument&quot;. */
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_eq
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
multiline_comment|/* Process any command switches, otherwise skip it. */
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;&bslash;0&squot;
)paren
r_break
suffix:semicolon
r_else
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;-&squot;
)paren
(brace
id|commands
op_increment
suffix:semicolon
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|process_switch
c_func
(paren
op_star
id|commands
op_increment
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|commands
)paren
op_ge
l_int|9
op_logical_and
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;kgdb=tty&quot;
comma
l_int|8
)paren
)paren
(brace
id|boot_flags
op_or_assign
id|BOOTME_KGDB
suffix:semicolon
r_switch
c_cond
(paren
id|commands
(braket
l_int|8
)braket
)paren
(brace
macro_line|#ifdef CONFIG_SUN_SERIAL
r_case
l_char|&squot;a&squot;
suffix:colon
id|rs_kgdb_hook
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;KGDB: Using serial line /dev/ttya.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
id|rs_kgdb_hook
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;KGDB: Using serial line /dev/ttyb.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
macro_line|#endif
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;KGDB: Unknown tty line.&bslash;n&quot;
)paren
suffix:semicolon
id|boot_flags
op_and_assign
op_complement
id|BOOTME_KGDB
suffix:semicolon
r_break
suffix:semicolon
)brace
id|commands
op_add_assign
l_int|9
suffix:semicolon
)brace
r_else
(brace
macro_line|#if CONFIG_SUN_CONSOLE
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;console=&quot;
comma
l_int|8
)paren
)paren
(brace
id|commands
op_add_assign
l_int|8
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|commands
comma
l_string|&quot;ttya&quot;
comma
l_int|4
)paren
)paren
(brace
id|console_fb
op_assign
l_int|2
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Using /dev/ttya as console.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
(paren
id|commands
comma
l_string|&quot;ttyb&quot;
comma
l_int|4
)paren
)paren
(brace
id|console_fb
op_assign
l_int|3
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Using /dev/ttyb as console.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|console_fb
op_assign
l_int|1
suffix:semicolon
id|console_fb_path
op_assign
id|commands
suffix:semicolon
)brace
)brace
r_else
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|commands
comma
l_string|&quot;mem=&quot;
comma
l_int|4
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * &quot;mem=XXX[kKmM]&quot; overrides the PROM-reported&n;&t;&t;&t;&t; * memory size.&n;&t;&t;&t;&t; */
id|memory_size
op_assign
id|simple_strtoul
c_func
(paren
id|commands
op_plus
l_int|4
comma
op_amp
id|commands
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;K&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;k&squot;
)paren
(brace
id|memory_size
op_lshift_assign
l_int|10
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_star
id|commands
op_eq
l_char|&squot;M&squot;
op_logical_or
op_star
id|commands
op_eq
l_char|&squot;m&squot;
)paren
(brace
id|memory_size
op_lshift_assign
l_int|20
suffix:semicolon
id|commands
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_star
id|commands
op_logical_and
op_star
id|commands
op_ne
l_char|&squot; &squot;
)paren
id|commands
op_increment
suffix:semicolon
)brace
)brace
)brace
r_extern
r_int
id|prom_probe_memory
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|start
comma
id|end
suffix:semicolon
r_extern
r_void
id|panic_setup
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
r_int
r_int
id|sun_serial_setup
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
r_int
id|root_flags
suffix:semicolon
r_extern
r_int
r_int
id|root_dev
suffix:semicolon
r_extern
r_int
r_int
id|ram_flags
suffix:semicolon
r_extern
r_int
id|ramdisk_image
suffix:semicolon
r_extern
r_int
id|ramdisk_size
suffix:semicolon
DECL|macro|RAMDISK_IMAGE_START_MASK
mdefine_line|#define RAMDISK_IMAGE_START_MASK&t;0x07FF
DECL|macro|RAMDISK_PROMPT_FLAG
mdefine_line|#define RAMDISK_PROMPT_FLAG&t;&t;0x8000
DECL|macro|RAMDISK_LOAD_FLAG
mdefine_line|#define RAMDISK_LOAD_FLAG&t;&t;0x4000
r_extern
r_int
id|root_mountflags
suffix:semicolon
r_extern
r_void
id|register_console
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
DECL|variable|saved_command_line
r_char
id|saved_command_line
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|reboot_command
r_char
id|reboot_command
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|phys_base
r_int
r_int
id|phys_base
suffix:semicolon
DECL|variable|fake_swapper_regs
r_static
r_struct
id|pt_regs
id|fake_swapper_regs
op_assign
(brace
(brace
l_int|0
comma
)brace
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
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
id|lowest_paddr
suffix:semicolon
r_int
id|total
comma
id|i
suffix:semicolon
multiline_comment|/* Initialize PROM console and command line. */
op_star
id|cmdline_p
op_assign
id|prom_getbootargs
c_func
(paren
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|saved_command_line
comma
op_star
id|cmdline_p
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ARCH: SUN4U&bslash;n&quot;
)paren
suffix:semicolon
id|boot_flags_init
c_func
(paren
op_star
id|cmdline_p
)paren
suffix:semicolon
macro_line|#if 0&t;
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_DEBUG
)paren
op_logical_and
(paren
id|linux_dbvec
op_ne
l_int|0
)paren
op_logical_and
(paren
(paren
op_star
(paren
r_int
op_star
)paren
id|linux_dbvec
)paren
op_ne
op_minus
l_int|1
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Booted under KADB. Syncing trap table.&bslash;n&quot;
)paren
suffix:semicolon
(paren
op_star
(paren
id|linux_dbvec-&gt;teach_debugger
)paren
)paren
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|boot_flags
op_amp
id|BOOTME_KGDB
)paren
)paren
(brace
id|set_debug_traps
c_func
(paren
)paren
suffix:semicolon
id|prom_printf
(paren
l_string|&quot;Breakpoint!&bslash;n&quot;
)paren
suffix:semicolon
id|breakpoint
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;
id|idprom_init
c_func
(paren
)paren
suffix:semicolon
id|total
op_assign
id|prom_probe_memory
c_func
(paren
)paren
suffix:semicolon
id|lowest_paddr
op_assign
l_int|0xffffffffffffffffUL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_ne
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
OL
id|lowest_paddr
)paren
(brace
id|lowest_paddr
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
suffix:semicolon
)brace
id|end_of_phys_memory
op_assign
id|sp_banks
(braket
id|i
)braket
dot
id|base_addr
op_plus
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
suffix:semicolon
r_if
c_cond
(paren
id|memory_size
)paren
(brace
r_if
c_cond
(paren
id|end_of_phys_memory
OG
id|memory_size
)paren
(brace
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_sub_assign
(paren
id|end_of_phys_memory
op_minus
id|memory_size
)paren
suffix:semicolon
id|end_of_phys_memory
op_assign
id|memory_size
suffix:semicolon
id|sp_banks
(braket
op_increment
id|i
)braket
dot
id|base_addr
op_assign
l_int|0xdeadbeef
suffix:semicolon
id|sp_banks
(braket
id|i
)braket
dot
id|num_bytes
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
id|prom_setsync
c_func
(paren
id|prom_sync_me
)paren
suffix:semicolon
multiline_comment|/* In paging_init() we tip off this value to see if we need&n;&t; * to change init_mm.pgd to point to the real alias mapping.&n;&t; */
id|phys_base
op_assign
id|lowest_paddr
suffix:semicolon
op_star
id|memory_start_p
op_assign
id|PAGE_ALIGN
c_func
(paren
(paren
(paren
r_int
r_int
)paren
op_amp
id|end
)paren
)paren
suffix:semicolon
op_star
id|memory_end_p
op_assign
(paren
id|end_of_phys_memory
op_plus
id|PAGE_OFFSET
)paren
suffix:semicolon
macro_line|#ifndef NO_DAVEM_DEBUGGING
id|prom_printf
c_func
(paren
l_string|&quot;phys_base[%016lx] memory_start[%016lx] memory_end[%016lx]&bslash;n&quot;
comma
id|phys_base
comma
op_star
id|memory_start_p
comma
op_star
id|memory_end_p
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|root_flags
)paren
id|root_mountflags
op_and_assign
op_complement
id|MS_RDONLY
suffix:semicolon
id|ROOT_DEV
op_assign
id|to_kdev_t
c_func
(paren
id|root_dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_RAM
id|rd_image_start
op_assign
id|ram_flags
op_amp
id|RAMDISK_IMAGE_START_MASK
suffix:semicolon
id|rd_prompt
op_assign
(paren
(paren
id|ram_flags
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
id|ram_flags
op_amp
id|RAMDISK_LOAD_FLAG
)paren
op_ne
l_int|0
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BLK_DEV_INITRD
r_if
c_cond
(paren
id|ramdisk_image
)paren
(brace
id|initrd_start
op_assign
id|ramdisk_image
suffix:semicolon
r_if
c_cond
(paren
id|initrd_start
OL
id|PAGE_OFFSET
)paren
id|initrd_start
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
id|initrd_end
op_assign
id|initrd_start
op_plus
id|ramdisk_size
suffix:semicolon
r_if
c_cond
(paren
id|initrd_end
OG
op_star
id|memory_end_p
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;initrd extends beyond end of memory &quot;
l_string|&quot;(0x%016lx &gt; 0x%016lx)&bslash;ndisabling initrd&bslash;n&quot;
comma
id|initrd_end
comma
op_star
id|memory_end_p
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
op_ge
op_star
id|memory_start_p
op_logical_and
id|initrd_start
OL
op_star
id|memory_start_p
op_plus
l_int|2
op_star
id|PAGE_SIZE
)paren
(brace
id|initrd_below_start_ok
op_assign
l_int|1
suffix:semicolon
op_star
id|memory_start_p
op_assign
id|PAGE_ALIGN
(paren
id|initrd_end
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif&t;
multiline_comment|/* Due to stack alignment restrictions and assumptions... */
id|init_task.mm-&gt;mmap-&gt;vm_page_prot
op_assign
id|PAGE_SHARED
suffix:semicolon
id|init_task.mm-&gt;mmap-&gt;vm_start
op_assign
id|PAGE_OFFSET
suffix:semicolon
id|init_task.mm-&gt;mmap-&gt;vm_end
op_assign
op_star
id|memory_end_p
suffix:semicolon
id|init_task.mm-&gt;context
op_assign
(paren
r_int
r_int
)paren
id|NO_CONTEXT
suffix:semicolon
id|init_task.tss.kregs
op_assign
op_amp
id|fake_swapper_regs
suffix:semicolon
macro_line|#ifdef CONFIG_SUN_SERIAL
op_star
id|memory_start_p
op_assign
id|sun_serial_setup
c_func
(paren
op_star
id|memory_start_p
)paren
suffix:semicolon
multiline_comment|/* set this up ASAP */
macro_line|#endif
(brace
r_extern
r_int
id|serial_console
suffix:semicolon
multiline_comment|/* in console.c, of course */
macro_line|#if !CONFIG_SUN_SERIAL
id|serial_console
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_switch
c_cond
(paren
id|console_fb
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* Let&squot;s get our io devices from prom */
(brace
r_int
id|idev
op_assign
id|prom_query_input_device
c_func
(paren
)paren
suffix:semicolon
r_int
id|odev
op_assign
id|prom_query_output_device
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_IKBD
op_logical_and
id|odev
op_eq
id|PROMDEV_OSCREEN
)paren
(brace
id|serial_console
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYA
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYA
)paren
(brace
id|serial_console
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|idev
op_eq
id|PROMDEV_ITTYB
op_logical_and
id|odev
op_eq
id|PROMDEV_OTTYB
)paren
(brace
id|serial_console
op_assign
l_int|2
suffix:semicolon
)brace
r_else
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Inconsistent console&bslash;n&quot;
)paren
suffix:semicolon
id|prom_halt
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|serial_console
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force one of the framebuffers as console */
r_case
l_int|2
suffix:colon
id|serial_console
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force ttya as console */
r_case
l_int|3
suffix:colon
id|serial_console
op_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* Force ttyb as console */
)brace
macro_line|#endif
)brace
)brace
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
multiline_comment|/* BUFFER is PAGE_SIZE bytes long. */
r_extern
r_char
op_star
id|sparc_cpu_type
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|sparc_fpu_type
(braket
)braket
suffix:semicolon
r_extern
r_char
op_star
id|smp_info
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_char
op_star
id|mmu_info
c_func
(paren
r_void
)paren
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
r_int
id|cpuid
op_assign
id|get_cpuid
c_func
(paren
)paren
suffix:semicolon
r_return
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;cpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;fpu&bslash;t&bslash;t: %s&bslash;n&quot;
l_string|&quot;promlib&bslash;t&bslash;t: Version 3 Revision %d&bslash;n&quot;
l_string|&quot;prom&bslash;t&bslash;t: %d.%d.%d&bslash;n&quot;
l_string|&quot;type&bslash;t&bslash;t: sun4u&bslash;n&quot;
l_string|&quot;ncpus probed&bslash;t: %d&bslash;n&quot;
l_string|&quot;ncpus active&bslash;t: %d&bslash;n&quot;
macro_line|#ifndef __SMP__
l_string|&quot;BogoMips&bslash;t: %lu.%02lu&bslash;n&quot;
macro_line|#else
l_string|&quot;Cpu0Bogo&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;Cpu1Bogo&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;Cpu2Bogo&bslash;t: %lu.%02lu&bslash;n&quot;
l_string|&quot;Cpu3Bogo&bslash;t: %lu.%02lu&bslash;n&quot;
macro_line|#endif
l_string|&quot;%s&quot;
macro_line|#ifdef __SMP__
l_string|&quot;%s&quot;
macro_line|#endif
comma
id|sparc_cpu_type
(braket
id|cpuid
)braket
comma
id|sparc_fpu_type
(braket
id|cpuid
)braket
comma
id|prom_rev
comma
id|prom_prev
op_rshift
l_int|16
comma
(paren
id|prom_prev
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|prom_prev
op_amp
l_int|0xff
comma
id|linux_num_cpus
comma
id|smp_num_cpus
comma
macro_line|#ifndef __SMP__
id|loops_per_sec
op_div
l_int|500000
comma
(paren
id|loops_per_sec
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
macro_line|#else
id|cpu_data
(braket
l_int|0
)braket
dot
id|udelay_val
op_div
l_int|500000
comma
(paren
id|cpu_data
(braket
l_int|0
)braket
dot
id|udelay_val
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
id|cpu_data
(braket
l_int|1
)braket
dot
id|udelay_val
op_div
l_int|500000
comma
(paren
id|cpu_data
(braket
l_int|1
)braket
dot
id|udelay_val
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
id|cpu_data
(braket
l_int|2
)braket
dot
id|udelay_val
op_div
l_int|500000
comma
(paren
id|cpu_data
(braket
l_int|2
)braket
dot
id|udelay_val
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
id|cpu_data
(braket
l_int|3
)braket
dot
id|udelay_val
op_div
l_int|500000
comma
(paren
id|cpu_data
(braket
l_int|3
)braket
dot
id|udelay_val
op_div
l_int|5000
)paren
op_mod
l_int|100
comma
macro_line|#endif
id|mmu_info
c_func
(paren
)paren
macro_line|#ifdef __SMP__
comma
id|smp_info
c_func
(paren
)paren
macro_line|#endif
)paren
suffix:semicolon
)brace
eof
