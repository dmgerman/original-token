multiline_comment|/*&n; *  linux/arch/i386/kernel/process.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; *&n; *  Pentium III FXSR, SSE support&n; *&t;Gareth Hughes &lt;gareth@valinux.com&gt;, May 2000&n; */
multiline_comment|/*&n; * This file handles the architecture-dependent parts of process handling..&n; */
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/reboot.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ldt.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#ifdef CONFIG_MATH_EMULATION
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/irq.h&gt;
id|asmlinkage
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
id|__asm__
c_func
(paren
l_string|&quot;ret_from_fork&quot;
)paren
suffix:semicolon
DECL|variable|hlt_counter
r_int
id|hlt_counter
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Powermanagement idle function, if any..&n; */
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Power off function, if any&n; */
DECL|variable|pm_power_off
r_void
(paren
op_star
id|pm_power_off
)paren
(paren
r_void
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|function|disable_hlt
r_void
id|disable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_increment
suffix:semicolon
)brace
DECL|function|enable_hlt
r_void
id|enable_hlt
c_func
(paren
r_void
)paren
(brace
id|hlt_counter
op_decrement
suffix:semicolon
)brace
multiline_comment|/*&n; * We use this if we don&squot;t have any better&n; * idle routine..&n; */
DECL|function|default_idle
r_static
r_void
id|default_idle
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|current_cpu_data.hlt_works_ok
op_logical_and
op_logical_neg
id|hlt_counter
)paren
(brace
id|__cli
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
id|safe_halt
c_func
(paren
)paren
suffix:semicolon
r_else
id|__sti
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * The idle thread. There&squot;s no useful work to be&n; * done, so just try to conserve power and have a&n; * low exit latency (ie sit in a loop waiting for&n; * somebody to say that they&squot;d like to reschedule)&n; */
DECL|function|cpu_idle
r_void
id|cpu_idle
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* endless idle loop with no priority at all */
id|init_idle
c_func
(paren
)paren
suffix:semicolon
id|current-&gt;priority
op_assign
l_int|0
suffix:semicolon
id|current-&gt;counter
op_assign
op_minus
l_int|100
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_void
(paren
op_star
id|idle
)paren
(paren
r_void
)paren
op_assign
id|pm_idle
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|idle
)paren
id|idle
op_assign
id|default_idle
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|current-&gt;need_resched
)paren
id|idle
c_func
(paren
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
id|check_pgt_cache
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|variable|no_idt
r_static
r_int
id|no_idt
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|reboot_mode
r_static
r_int
id|reboot_mode
op_assign
l_int|0
suffix:semicolon
DECL|variable|reboot_thru_bios
r_static
r_int
id|reboot_thru_bios
op_assign
l_int|0
suffix:semicolon
DECL|function|reboot_setup
r_static
r_int
id|__init
id|reboot_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_switch
c_cond
(paren
op_star
id|str
)paren
(brace
r_case
l_char|&squot;w&squot;
suffix:colon
multiline_comment|/* &quot;warm&quot; reboot (no memory testing etc) */
id|reboot_mode
op_assign
l_int|0x1234
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;c&squot;
suffix:colon
multiline_comment|/* &quot;cold&quot; reboot (with memory testing etc) */
id|reboot_mode
op_assign
l_int|0x0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;b&squot;
suffix:colon
multiline_comment|/* &quot;bios&quot; reboot by jumping through the BIOS */
id|reboot_thru_bios
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;h&squot;
suffix:colon
multiline_comment|/* &quot;hard&quot; reboot by toggling RESET and/or crashing the CPU */
id|reboot_thru_bios
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|str
op_assign
id|strchr
c_func
(paren
id|str
comma
l_char|&squot;,&squot;
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
id|str
op_increment
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;reboot=&quot;
comma
id|reboot_setup
)paren
suffix:semicolon
multiline_comment|/* The following code and data reboots the machine by switching to real&n;   mode and jumping to the BIOS reset entry point, as if the CPU has&n;   really been reset.  The previous version asked the keyboard&n;   controller to pulse the CPU reset line, which is more thorough, but&n;   doesn&squot;t work with at least one type of 486 motherboard.  It is easy&n;   to stop this code working; hence the copious comments. */
r_static
r_int
r_int
r_int
DECL|variable|real_mode_gdt_entries
id|real_mode_gdt_entries
(braket
l_int|3
)braket
op_assign
(brace
l_int|0x0000000000000000ULL
comma
multiline_comment|/* Null descriptor */
l_int|0x00009a000000ffffULL
comma
multiline_comment|/* 16-bit real-mode 64k code at 0x00000000 */
l_int|0x000092000100ffffULL
multiline_comment|/* 16-bit real-mode 64k data at 0x00000100 */
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|size
r_int
r_int
id|size
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
DECL|member|base
r_int
r_int
r_int
op_star
id|base
id|__attribute__
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
DECL|variable|real_mode_gdt
id|real_mode_gdt
op_assign
(brace
r_sizeof
(paren
id|real_mode_gdt_entries
)paren
op_minus
l_int|1
comma
id|real_mode_gdt_entries
)brace
comma
DECL|variable|real_mode_idt
id|real_mode_idt
op_assign
(brace
l_int|0x3ff
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* This is 16-bit protected mode code to disable paging and the cache,&n;   switch to real mode and jump to the BIOS reset code.&n;&n;   The instruction that switches to real mode by writing to CR0 must be&n;   followed immediately by a far jump instruction, which set CS to a&n;   valid value for real mode, and flushes the prefetch queue to avoid&n;   running instructions that have already been decoded in protected&n;   mode.&n;&n;   Clears all the flags except ET, especially PG (paging), PE&n;   (protected-mode enable) and TS (task switch for coprocessor state&n;   save).  Flushes the TLB after paging has been disabled.  Sets CD and&n;   NW, to disable the cache on a 486, and invalidates the cache.  This&n;   is more like the state of a 486 after reset.  I don&squot;t know if&n;   something else should be done for other chips.&n;&n;   More could be done here to set up the registers as if a CPU reset had&n;   occurred; hopefully real BIOSs don&squot;t assume much. */
DECL|variable|real_mode_switch
r_static
r_int
r_char
id|real_mode_switch
(braket
)braket
op_assign
(brace
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x20
comma
l_int|0xc0
comma
multiline_comment|/*    movl  %cr0,%eax        */
l_int|0x66
comma
l_int|0x83
comma
l_int|0xe0
comma
l_int|0x11
comma
multiline_comment|/*    andl  $0x00000011,%eax */
l_int|0x66
comma
l_int|0x0d
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x60
comma
multiline_comment|/*    orl   $0x60000000,%eax */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xc0
comma
multiline_comment|/*    movl  %eax,%cr0        */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xd8
comma
multiline_comment|/*    movl  %eax,%cr3        */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x20
comma
l_int|0xc3
comma
multiline_comment|/*    movl  %cr0,%ebx        */
l_int|0x66
comma
l_int|0x81
comma
l_int|0xe3
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0x60
comma
multiline_comment|/*    andl  $0x60000000,%ebx */
l_int|0x74
comma
l_int|0x02
comma
multiline_comment|/*    jz    f                */
l_int|0x0f
comma
l_int|0x08
comma
multiline_comment|/*    invd                   */
l_int|0x24
comma
l_int|0x10
comma
multiline_comment|/* f: andb  $0x10,al         */
l_int|0x66
comma
l_int|0x0f
comma
l_int|0x22
comma
l_int|0xc0
multiline_comment|/*    movl  %eax,%cr0        */
)brace
suffix:semicolon
DECL|variable|jump_to_bios
r_static
r_int
r_char
id|jump_to_bios
(braket
)braket
op_assign
(brace
l_int|0xea
comma
l_int|0x00
comma
l_int|0x00
comma
l_int|0xff
comma
l_int|0xff
multiline_comment|/*    ljmp  $0xffff,$0x0000  */
)brace
suffix:semicolon
DECL|function|kb_wait
r_static
r_inline
r_void
id|kb_wait
c_func
(paren
r_void
)paren
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
l_int|0x10000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|inb_p
c_func
(paren
l_int|0x64
)paren
op_amp
l_int|0x02
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/*&n; * Switch to real mode and then execute the code&n; * specified by the code and length parameters.&n; * We assume that length will aways be less that 100!&n; */
DECL|function|machine_real_restart
r_void
id|machine_real_restart
c_func
(paren
r_int
r_char
op_star
id|code
comma
r_int
id|length
)paren
(brace
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Write zero to CMOS register number 0x0f, which the BIOS POST&n;&t;   routine will recognize as telling it to do a proper reboot.  (Well&n;&t;   that&squot;s what this book in front of me says -- it may only apply to&n;&t;   the Phoenix BIOS though, it&squot;s not clear).  At the same time,&n;&t;   disable NMIs by setting the top bit in the CMOS address register,&n;&t;   as we&squot;re about to do peculiar things to the CPU.  I&squot;m not sure if&n;&t;   `outb_p&squot; is needed instead of just `outb&squot;.  Use it to be on the&n;&t;   safe side. */
id|outb_p
(paren
l_int|0x8f
comma
l_int|0x70
)paren
suffix:semicolon
id|outb_p
(paren
l_int|0x00
comma
l_int|0x71
)paren
suffix:semicolon
multiline_comment|/* Remap the kernel at virtual address zero, as well as offset zero&n;&t;   from the kernel segment.  This assumes the kernel segment starts at&n;&t;   virtual address PAGE_OFFSET. */
id|memcpy
(paren
id|swapper_pg_dir
comma
id|swapper_pg_dir
op_plus
id|USER_PGD_PTRS
comma
r_sizeof
(paren
id|swapper_pg_dir
(braket
l_int|0
)braket
)paren
op_star
id|KERNEL_PGD_PTRS
)paren
suffix:semicolon
multiline_comment|/* Make sure the first page is mapped to the start of physical memory.&n;&t;   It is normally not mapped, to trap kernel NULL pointer dereferences. */
id|pg0
(braket
l_int|0
)braket
op_assign
id|_PAGE_RW
op_or
id|_PAGE_PRESENT
suffix:semicolon
multiline_comment|/*&n;&t; * Use `swapper_pg_dir&squot; as our page directory.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %0,%%cr3&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|__pa
c_func
(paren
id|swapper_pg_dir
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Write 0x1234 to absolute memory location 0x472.  The BIOS reads&n;&t;   this on booting to tell it to &quot;Bypass memory test (also warm&n;&t;   boot)&quot;.  This seems like a fairly standard thing that gets set by&n;&t;   REBOOT.COM programs, and the previous reset routine did this&n;&t;   too. */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
l_int|0x472
)paren
op_assign
id|reboot_mode
suffix:semicolon
multiline_comment|/* For the switch to real mode, copy some code to low memory.  It has&n;&t;   to be in the first 64k because it is running in 16-bit mode, and it&n;&t;   has to have the same physical and virtual address, because it turns&n;&t;   off paging.  Copy it near the end of the first page, out of the way&n;&t;   of BIOS variables. */
id|memcpy
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
r_sizeof
(paren
id|real_mode_switch
)paren
op_minus
l_int|100
)paren
comma
id|real_mode_switch
comma
r_sizeof
(paren
id|real_mode_switch
)paren
)paren
suffix:semicolon
id|memcpy
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
l_int|100
)paren
comma
id|code
comma
id|length
)paren
suffix:semicolon
multiline_comment|/* Set up the IDT for real mode. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|real_mode_idt
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up a GDT from which we can load segment descriptors for real&n;&t;   mode.  The GDT is not used in real mode; it is just needed here to&n;&t;   prepare the descriptors. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;lgdt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|real_mode_gdt
)paren
)paren
suffix:semicolon
multiline_comment|/* Load the data segment registers, and thus the descriptors ready for&n;&t;   real mode.  The base address of each segment is 0x100, 16 times the&n;&t;   selector value being loaded here.  This is so that the segment&n;&t;   registers don&squot;t have to be reloaded after switching to real mode:&n;&t;   the values are consistent for real mode operation already. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;movl $0x0010,%%eax&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%ds&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%es&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%fs&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%gs&bslash;n&quot;
l_string|&quot;&bslash;tmovl %%eax,%%ss&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;eax&quot;
)paren
suffix:semicolon
multiline_comment|/* Jump to the 16-bit code that we copied earlier.  It disables paging&n;&t;   and the cache, switches to real mode, and jumps to the BIOS reset&n;&t;   entry point. */
id|__asm__
id|__volatile__
(paren
l_string|&quot;ljmp $0x0008,%0&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
(paren
r_void
op_star
)paren
(paren
l_int|0x1000
op_minus
r_sizeof
(paren
id|real_mode_switch
)paren
op_minus
l_int|100
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|machine_restart
r_void
id|machine_restart
c_func
(paren
r_char
op_star
id|__unused
)paren
(brace
macro_line|#if CONFIG_SMP
multiline_comment|/*&n;&t; * Stop all CPUs and turn off local APICs and the IO-APIC, so&n;&t; * other OSs see a clean IRQ state.&n;&t; */
id|smp_send_stop
c_func
(paren
)paren
suffix:semicolon
id|disable_IO_APIC
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|reboot_thru_bios
)paren
(brace
multiline_comment|/* rebooting needs to touch the page at absolute addr 0 */
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|__va
c_func
(paren
l_int|0x472
)paren
)paren
op_assign
id|reboot_mode
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
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
l_int|100
suffix:semicolon
id|i
op_increment
)paren
(brace
id|kb_wait
c_func
(paren
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xfe
comma
l_int|0x64
)paren
suffix:semicolon
multiline_comment|/* pulse reset low */
id|udelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
)brace
multiline_comment|/* That didn&squot;t work - force a triple fault.. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;lidt %0&quot;
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|no_idt
)paren
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;int3&quot;
)paren
suffix:semicolon
)brace
)brace
id|machine_real_restart
c_func
(paren
id|jump_to_bios
comma
r_sizeof
(paren
id|jump_to_bios
)paren
)paren
suffix:semicolon
)brace
DECL|function|machine_halt
r_void
id|machine_halt
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|machine_power_off
r_void
id|machine_power_off
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pm_power_off
)paren
id|pm_power_off
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|show_regs
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|cr0
op_assign
l_int|0L
comma
id|cr2
op_assign
l_int|0L
comma
id|cr3
op_assign
l_int|0L
comma
id|cr4
op_assign
l_int|0L
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EIP: %04x:[&lt;%08lx&gt;]&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xcs
comma
id|regs-&gt;eip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;xcs
op_amp
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot; ESP: %04x:%08lx&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xss
comma
id|regs-&gt;esp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; EFLAGS: %08lx&bslash;n&quot;
comma
id|regs-&gt;eflags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx&bslash;n&quot;
comma
id|regs-&gt;eax
comma
id|regs-&gt;ebx
comma
id|regs-&gt;ecx
comma
id|regs-&gt;edx
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ESI: %08lx EDI: %08lx EBP: %08lx&quot;
comma
id|regs-&gt;esi
comma
id|regs-&gt;edi
comma
id|regs-&gt;ebp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; DS: %04x ES: %04x&bslash;n&quot;
comma
l_int|0xffff
op_amp
id|regs-&gt;xds
comma
l_int|0xffff
op_amp
id|regs-&gt;xes
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr0, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr0
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr2, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr2
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movl %%cr3, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr3
)paren
)paren
suffix:semicolon
multiline_comment|/* This could fault if %cr4 does not exist */
id|__asm__
c_func
(paren
l_string|&quot;1: movl %%cr4, %0&t;&t;&bslash;n&quot;
l_string|&quot;2:&t;&t;&t;&t;&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&t;&bslash;n&quot;
l_string|&quot;.long 1b,2b&t;&t;&t;&bslash;n&quot;
l_string|&quot;.previous&t;&t;&t;&bslash;n&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|cr4
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CR0: %08lx CR2: %08lx CR3: %08lx CR4: %08lx&bslash;n&quot;
comma
id|cr0
comma
id|cr2
comma
id|cr3
comma
id|cr4
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * No need to lock the MM as we are the last user&n; */
DECL|function|release_segments
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_void
op_star
id|ldt
op_assign
id|mm-&gt;segments
suffix:semicolon
multiline_comment|/*&n;&t; * free the LDT&n;&t; */
r_if
c_cond
(paren
id|ldt
)paren
(brace
id|mm-&gt;segments
op_assign
l_int|NULL
suffix:semicolon
id|clear_LDT
c_func
(paren
)paren
suffix:semicolon
id|vfree
c_func
(paren
id|ldt
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Create a kernel thread&n; */
DECL|function|kernel_thread
r_int
id|kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_int
r_int
id|flags
)paren
(brace
r_int
id|retval
comma
id|d0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;movl %%esp,%%esi&bslash;n&bslash;t&quot;
l_string|&quot;int $0x80&bslash;n&bslash;t&quot;
multiline_comment|/* Linux/i386 system call */
l_string|&quot;cmpl %%esp,%%esi&bslash;n&bslash;t&quot;
multiline_comment|/* child or parent? */
l_string|&quot;je 1f&bslash;n&bslash;t&quot;
multiline_comment|/* parent - jump */
multiline_comment|/* Load the argument into eax, and push it.  That way, it does&n;&t;&t; * not matter whether the called function is compiled with&n;&t;&t; * -mregparm or not.  */
l_string|&quot;movl %4,%%eax&bslash;n&bslash;t&quot;
l_string|&quot;pushl %%eax&bslash;n&bslash;t&quot;
l_string|&quot;call *%5&bslash;n&bslash;t&quot;
multiline_comment|/* call fn */
l_string|&quot;movl %3,%0&bslash;n&bslash;t&quot;
multiline_comment|/* exit */
l_string|&quot;int $0x80&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
suffix:colon
l_string|&quot;=&amp;a&quot;
(paren
id|retval
)paren
comma
l_string|&quot;=&amp;S&quot;
(paren
id|d0
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|__NR_clone
)paren
comma
l_string|&quot;i&quot;
(paren
id|__NR_exit
)paren
comma
l_string|&quot;r&quot;
(paren
id|arg
)paren
comma
l_string|&quot;r&quot;
(paren
id|fn
)paren
comma
l_string|&quot;b&quot;
(paren
id|flags
op_or
id|CLONE_VM
)paren
suffix:colon
l_string|&quot;memory&quot;
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * Free current thread data structures etc..&n; */
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* nothing to do ... */
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
id|memset
c_func
(paren
id|tsk-&gt;thread.debugreg
comma
l_int|0
comma
r_sizeof
(paren
r_int
r_int
)paren
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Forget coprocessor state..&n;&t; */
id|clear_fpu
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|tsk-&gt;used_math
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|release_thread
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|dead_task
)paren
(brace
r_if
c_cond
(paren
id|dead_task-&gt;mm
)paren
(brace
r_void
op_star
id|ldt
op_assign
id|dead_task-&gt;mm-&gt;segments
suffix:semicolon
singleline_comment|// temporary debugging check
r_if
c_cond
(paren
id|ldt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;WARNING: dead process %8s still has LDT? &lt;%p&gt;&bslash;n&quot;
comma
id|dead_task-&gt;comm
comma
id|ldt
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * we do not have to muck with descriptors here, that is&n; * done in switch_mm() as needed.&n; */
DECL|function|copy_segments
r_void
id|copy_segments
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|new_mm
)paren
(brace
r_struct
id|mm_struct
op_star
id|old_mm
op_assign
id|current-&gt;mm
suffix:semicolon
r_void
op_star
id|old_ldt
op_assign
id|old_mm-&gt;segments
comma
op_star
id|ldt
op_assign
id|old_ldt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|old_mm-&gt;segments
)paren
(brace
multiline_comment|/*&n;&t;&t; * default LDT - use the one from init_task&n;&t;&t; */
id|new_mm-&gt;segments
op_assign
l_int|NULL
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Completely new LDT, we initialize it from the parent:&n;&t; */
id|ldt
op_assign
id|vmalloc
c_func
(paren
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ldt
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ldt allocation failed&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|ldt
comma
id|old_ldt
comma
id|LDT_ENTRIES
op_star
id|LDT_ENTRY_SIZE
)paren
suffix:semicolon
id|new_mm-&gt;segments
op_assign
id|ldt
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * Save a segment.&n; */
DECL|macro|savesegment
mdefine_line|#define savesegment(seg,value) &bslash;&n;&t;asm volatile(&quot;movl %%&quot; #seg &quot;,%0&quot;:&quot;=m&quot; (*(int *)&amp;(value)))
DECL|function|copy_thread
r_int
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|esp
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
suffix:semicolon
id|childregs
op_assign
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|THREAD_SIZE
op_plus
(paren
r_int
r_int
)paren
id|p
)paren
)paren
op_minus
l_int|1
suffix:semicolon
id|struct_cpy
c_func
(paren
id|childregs
comma
id|regs
)paren
suffix:semicolon
id|childregs-&gt;eax
op_assign
l_int|0
suffix:semicolon
id|childregs-&gt;esp
op_assign
id|esp
suffix:semicolon
id|p-&gt;thread.esp
op_assign
(paren
r_int
r_int
)paren
id|childregs
suffix:semicolon
id|p-&gt;thread.esp0
op_assign
(paren
r_int
r_int
)paren
(paren
id|childregs
op_plus
l_int|1
)paren
suffix:semicolon
id|p-&gt;thread.eip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|savesegment
c_func
(paren
id|fs
comma
id|p-&gt;thread.fs
)paren
suffix:semicolon
id|savesegment
c_func
(paren
id|gs
comma
id|p-&gt;thread.gs
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
id|struct_cpy
c_func
(paren
op_amp
id|p-&gt;thread.i387
comma
op_amp
id|current-&gt;thread.i387
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * fill in the user structure for a core dump..&n; */
DECL|function|dump_thread
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|user
op_star
id|dump
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* changed the size calculations - should hopefully work better. lbt */
id|dump-&gt;magic
op_assign
id|CMAGIC
suffix:semicolon
id|dump-&gt;start_code
op_assign
l_int|0
suffix:semicolon
id|dump-&gt;start_stack
op_assign
id|regs-&gt;esp
op_amp
op_complement
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|dump-&gt;u_tsize
op_assign
(paren
(paren
r_int
r_int
)paren
id|current-&gt;mm-&gt;end_code
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|current-&gt;mm-&gt;brk
op_plus
(paren
id|PAGE_SIZE
op_minus
l_int|1
)paren
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;u_dsize
op_sub_assign
id|dump-&gt;u_tsize
suffix:semicolon
id|dump-&gt;u_ssize
op_assign
l_int|0
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|dump-&gt;u_debugreg
(braket
id|i
)braket
op_assign
id|current-&gt;thread.debugreg
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dump-&gt;start_stack
OL
id|TASK_SIZE
)paren
id|dump-&gt;u_ssize
op_assign
(paren
(paren
r_int
r_int
)paren
(paren
id|TASK_SIZE
op_minus
id|dump-&gt;start_stack
)paren
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dump-&gt;regs.ebx
op_assign
id|regs-&gt;ebx
suffix:semicolon
id|dump-&gt;regs.ecx
op_assign
id|regs-&gt;ecx
suffix:semicolon
id|dump-&gt;regs.edx
op_assign
id|regs-&gt;edx
suffix:semicolon
id|dump-&gt;regs.esi
op_assign
id|regs-&gt;esi
suffix:semicolon
id|dump-&gt;regs.edi
op_assign
id|regs-&gt;edi
suffix:semicolon
id|dump-&gt;regs.ebp
op_assign
id|regs-&gt;ebp
suffix:semicolon
id|dump-&gt;regs.eax
op_assign
id|regs-&gt;eax
suffix:semicolon
id|dump-&gt;regs.ds
op_assign
id|regs-&gt;xds
suffix:semicolon
id|dump-&gt;regs.es
op_assign
id|regs-&gt;xes
suffix:semicolon
id|savesegment
c_func
(paren
id|fs
comma
id|dump-&gt;regs.fs
)paren
suffix:semicolon
id|savesegment
c_func
(paren
id|gs
comma
id|dump-&gt;regs.gs
)paren
suffix:semicolon
id|dump-&gt;regs.orig_eax
op_assign
id|regs-&gt;orig_eax
suffix:semicolon
id|dump-&gt;regs.eip
op_assign
id|regs-&gt;eip
suffix:semicolon
id|dump-&gt;regs.cs
op_assign
id|regs-&gt;xcs
suffix:semicolon
id|dump-&gt;regs.eflags
op_assign
id|regs-&gt;eflags
suffix:semicolon
id|dump-&gt;regs.esp
op_assign
id|regs-&gt;esp
suffix:semicolon
id|dump-&gt;regs.ss
op_assign
id|regs-&gt;xss
suffix:semicolon
id|dump-&gt;u_fpvalid
op_assign
id|dump_fpu
(paren
id|regs
comma
op_amp
id|dump-&gt;i387
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This special macro can be used to load a debugging register&n; */
DECL|macro|loaddebug
mdefine_line|#define loaddebug(thread,register) &bslash;&n;&t;&t;__asm__(&quot;movl %0,%%db&quot; #register  &bslash;&n;&t;&t;&t;: /* no output */ &bslash;&n;&t;&t;&t;:&quot;r&quot; (thread-&gt;debugreg[register]))
multiline_comment|/*&n; *&t;switch_to(x,yn) should switch tasks from x to y.&n; *&n; * We fsave/fwait so that an exception goes off at the right time&n; * (as a call from the fsave or fwait in effect) rather than to&n; * the wrong process. Lazy FP saving no longer makes any sense&n; * with modern CPU&squot;s, and this simplifies a lot of things (SMP&n; * and UP become the same).&n; *&n; * NOTE! We used to use the x86 hardware context switching. The&n; * reason for not using it any more becomes apparent when you&n; * try to recover gracefully from saved state that is no longer&n; * valid (stale segment register values in particular). With the&n; * hardware task-switch, there is no way to fix up bad state in&n; * a reasonable manner.&n; *&n; * The fact that Intel documents the hardware task-switching to&n; * be slow is a fairly red herring - this code is not noticeably&n; * faster. However, there _is_ some room for improvement here,&n; * so the performance issues may eventually be a valid point.&n; * More important, however, is the fact that this allows us much&n; * more flexibility.&n; */
DECL|function|__switch_to
r_void
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev_p
comma
r_struct
id|task_struct
op_star
id|next_p
)paren
(brace
r_struct
id|thread_struct
op_star
id|prev
op_assign
op_amp
id|prev_p-&gt;thread
comma
op_star
id|next
op_assign
op_amp
id|next_p-&gt;thread
suffix:semicolon
r_struct
id|tss_struct
op_star
id|tss
op_assign
id|init_tss
op_plus
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|unlazy_fpu
c_func
(paren
id|prev_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reload esp0, LDT and the page table pointer:&n;&t; */
id|tss-&gt;esp0
op_assign
id|next-&gt;esp0
suffix:semicolon
multiline_comment|/*&n;&t; * Save away %fs and %gs. No need to save %es and %ds, as&n;&t; * those are always kernel segments while inside the kernel.&n;&t; */
id|asm
r_volatile
(paren
l_string|&quot;movl %%fs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
op_amp
id|prev-&gt;fs
)paren
)paren
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;movl %%gs,%0&quot;
suffix:colon
l_string|&quot;=m&quot;
(paren
op_star
(paren
r_int
op_star
)paren
op_amp
id|prev-&gt;gs
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Restore %fs and %gs.&n;&t; */
id|loadsegment
c_func
(paren
id|fs
comma
id|next-&gt;fs
)paren
suffix:semicolon
id|loadsegment
c_func
(paren
id|gs
comma
id|next-&gt;gs
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Now maybe reload the debug registers&n;&t; */
r_if
c_cond
(paren
id|next-&gt;debugreg
(braket
l_int|7
)braket
)paren
(brace
id|loaddebug
c_func
(paren
id|next
comma
l_int|0
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|1
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|2
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* no 4 and 5 */
id|loaddebug
c_func
(paren
id|next
comma
l_int|6
)paren
suffix:semicolon
id|loaddebug
c_func
(paren
id|next
comma
l_int|7
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev-&gt;ioperm
op_logical_or
id|next-&gt;ioperm
)paren
(brace
r_if
c_cond
(paren
id|next-&gt;ioperm
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 4 cachelines copy ... not good, but not that&n;&t;&t;&t; * bad either. Anyone got something better?&n;&t;&t;&t; * This only affects processes which use ioperm().&n;&t;&t;&t; * [Putting the TSSs into 4k-tlb mapped regions&n;&t;&t;&t; * and playing VM tricks to switch the IO bitmap&n;&t;&t;&t; * is not really acceptable.]&n;&t;&t;&t; */
id|memcpy
c_func
(paren
id|tss-&gt;io_bitmap
comma
id|next-&gt;io_bitmap
comma
id|IO_BITMAP_SIZE
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
id|tss-&gt;bitmap
op_assign
id|IO_BITMAP_OFFSET
suffix:semicolon
)brace
r_else
multiline_comment|/*&n;&t;&t;&t; * a bitmap offset pointing outside of the TSS limit&n;&t;&t;&t; * causes a nicely controllable SIGSEGV if a process&n;&t;&t;&t; * tries to use a port IO instruction. The first&n;&t;&t;&t; * sys_ioperm() call sets up the bitmap properly.&n;&t;&t;&t; */
id|tss-&gt;bitmap
op_assign
id|INVALID_IO_BITMAP_OFFSET
suffix:semicolon
)brace
)brace
DECL|function|sys_fork
id|asmlinkage
r_int
id|sys_fork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs.esp
comma
op_amp
id|regs
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
id|asmlinkage
r_int
id|sys_clone
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
r_int
id|clone_flags
suffix:semicolon
r_int
r_int
id|newsp
suffix:semicolon
id|clone_flags
op_assign
id|regs.ebx
suffix:semicolon
id|newsp
op_assign
id|regs.ecx
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|newsp
)paren
id|newsp
op_assign
id|regs.esp
suffix:semicolon
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|newsp
comma
op_amp
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is trivial, and on the face of it looks like it&n; * could equally well be done in user mode.&n; *&n; * Not so, for quite unobvious reasons - register pressure.&n; * In user mode vfork() cannot have a stack frame, and if&n; * done by calling the &quot;clone()&quot; system call directly, you&n; * do not have enough call-clobbered registers to hold all&n; * the information you need.&n; */
DECL|function|sys_vfork
id|asmlinkage
r_int
id|sys_vfork
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_return
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs.esp
comma
op_amp
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|sys_execve
id|asmlinkage
r_int
id|sys_execve
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|regs.ebx
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
id|regs.ecx
comma
(paren
r_char
op_star
op_star
)paren
id|regs.edx
comma
op_amp
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched&t;((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched&t;((unsigned long) scheduling_functions_end_here)
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|ebp
comma
id|esp
comma
id|eip
suffix:semicolon
r_int
r_int
id|stack_page
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|esp
op_assign
id|p-&gt;thread.esp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack_page
op_logical_or
id|esp
template_param
l_int|8188
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* include/asm-i386/system.h:switch_to() pushes ebp last. */
id|ebp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|esp
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|ebp
template_param
l_int|8184
op_plus
id|stack_page
)paren
r_return
l_int|0
suffix:semicolon
id|eip
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|ebp
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|eip
OL
id|first_sched
op_logical_or
id|eip
op_ge
id|last_sched
)paren
r_return
id|eip
suffix:semicolon
id|ebp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|ebp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|last_sched
macro_line|#undef last_sched
DECL|macro|first_sched
macro_line|#undef first_sched
eof
