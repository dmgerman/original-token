multiline_comment|/* $Id: sparc_ksyms.c,v 1.32 1996/12/18 06:33:45 tridge Exp $&n; * arch/sparc/kernel/ksyms.c: Sparc specific ksyms support.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996 Eddie C. Dost (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/auxio.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/idprom.h&gt;
macro_line|#include &lt;asm/svr4.h&gt;
macro_line|#include &lt;asm/head.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#ifdef CONFIG_SBUS
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/a.out.h&gt;
DECL|struct|poll
r_struct
id|poll
(brace
DECL|member|fd
r_int
id|fd
suffix:semicolon
DECL|member|events
r_int
id|events
suffix:semicolon
DECL|member|revents
r_int
id|revents
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|svr4_getcontext
(paren
id|svr4_ucontext_t
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|svr4_setcontext
(paren
id|svr4_ucontext_t
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sunos_poll
c_func
(paren
r_struct
id|poll
op_star
id|ufds
comma
r_int
id|nfds
comma
r_int
id|timeout
)paren
suffix:semicolon
r_extern
r_int
r_int
id|sunos_mmap
c_func
(paren
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|_sigpause_common
(paren
r_int
r_int
id|set
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__copy_1page
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memcpy
c_func
(paren
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memset
c_func
(paren
r_void
op_star
comma
r_int
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_void
op_star
id|bzero_1page
c_func
(paren
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__bzero
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memscan_zero
c_func
(paren
r_void
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
op_star
id|__memscan_generic
c_func
(paren
r_void
op_star
comma
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__memcmp
c_func
(paren
r_const
r_void
op_star
comma
r_const
r_void
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_int
id|__strncmp
c_func
(paren
r_const
r_char
op_star
comma
r_const
r_char
op_star
comma
id|__kernel_size_t
)paren
suffix:semicolon
r_extern
r_int
id|__copy_user
c_func
(paren
r_int
r_int
id|to
comma
r_int
r_int
id|from
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|__clear_user
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
id|__strncpy_from_user
c_func
(paren
r_int
r_int
id|dest
comma
r_int
r_int
id|src
comma
r_int
id|count
)paren
suffix:semicolon
r_extern
r_void
id|bcopy
(paren
r_const
r_char
op_star
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|__ashrdi3
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
r_void
id|dump_thread
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_struct
id|user
op_star
)paren
suffix:semicolon
multiline_comment|/* One thing to note is that the way the symbols of the mul/div&n; * support routines are named is a mess, they all start with&n; * a &squot;.&squot; which makes it a bitch to export, here is the trick:&n; */
DECL|macro|DD
mdefine_line|#define DD(sym) extern int __sparc_dot_ ## sym (int) __asm__(&quot;.&quot; ## #sym)
DECL|macro|XD
mdefine_line|#define XD(sym) { (void *) &amp; __sparc_dot_ ## sym, &quot;.&quot; ## #sym }
DECL|variable|rem
id|DD
c_func
(paren
id|rem
)paren
suffix:semicolon
DECL|variable|urem
id|DD
c_func
(paren
id|urem
)paren
suffix:semicolon
DECL|variable|div
id|DD
c_func
(paren
id|div
)paren
suffix:semicolon
DECL|variable|udiv
id|DD
c_func
(paren
id|udiv
)paren
suffix:semicolon
DECL|variable|mul
id|DD
c_func
(paren
id|mul
)paren
suffix:semicolon
DECL|variable|umul
id|DD
c_func
(paren
id|umul
)paren
suffix:semicolon
DECL|variable|arch_symbol_table
r_static
r_struct
id|symbol_table
id|arch_symbol_table
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
multiline_comment|/* used by various drivers */
id|X
c_func
(paren
id|sparc_cpu_model
)paren
comma
macro_line|#ifdef __SMP__
id|X
c_func
(paren
id|kernel_flag
)paren
comma
id|X
c_func
(paren
id|kernel_counter
)paren
comma
id|X
c_func
(paren
id|active_kernel_processor
)paren
comma
id|X
c_func
(paren
id|syscall_count
)paren
comma
macro_line|#endif
id|X
c_func
(paren
id|page_offset
)paren
comma
id|X
c_func
(paren
id|stack_top
)paren
comma
id|X
c_func
(paren
id|udelay
)paren
comma
id|X
c_func
(paren
id|mstk48t02_regs
)paren
comma
macro_line|#if CONFIG_SUN_AUXIO
id|X
c_func
(paren
id|auxio_register
)paren
comma
macro_line|#endif
id|X
c_func
(paren
id|request_fast_irq
)paren
comma
id|X
c_func
(paren
id|sparc_alloc_io
)paren
comma
id|X
c_func
(paren
id|sparc_free_io
)paren
comma
id|X
c_func
(paren
id|mmu_v2p
)paren
comma
id|X
c_func
(paren
id|mmu_unlockarea
)paren
comma
id|X
c_func
(paren
id|mmu_lockarea
)paren
comma
id|X
c_func
(paren
id|mmu_get_scsi_sgl
)paren
comma
id|X
c_func
(paren
id|mmu_get_scsi_one
)paren
comma
id|X
c_func
(paren
id|mmu_release_scsi_sgl
)paren
comma
id|X
c_func
(paren
id|mmu_release_scsi_one
)paren
comma
id|X
c_func
(paren
id|sparc_dvma_malloc
)paren
comma
id|X
c_func
(paren
id|sun4c_unmapioaddr
)paren
comma
id|X
c_func
(paren
id|srmmu_unmapioaddr
)paren
comma
macro_line|#if CONFIG_SBUS
id|X
c_func
(paren
id|SBus_chain
)paren
comma
macro_line|#endif
multiline_comment|/* Solaris/SunOS binary compatibility */
id|X
c_func
(paren
id|svr4_setcontext
)paren
comma
id|X
c_func
(paren
id|svr4_getcontext
)paren
comma
id|X
c_func
(paren
id|_sigpause_common
)paren
comma
id|X
c_func
(paren
id|sunos_mmap
)paren
comma
id|X
c_func
(paren
id|sunos_poll
)paren
comma
multiline_comment|/* Should really be in linux/kernel/ksyms.c */
id|X
c_func
(paren
id|dump_thread
)paren
comma
multiline_comment|/* prom symbols */
id|X
c_func
(paren
id|idprom
)paren
comma
id|X
c_func
(paren
id|prom_root_node
)paren
comma
id|X
c_func
(paren
id|prom_getchild
)paren
comma
id|X
c_func
(paren
id|prom_getsibling
)paren
comma
id|X
c_func
(paren
id|prom_searchsiblings
)paren
comma
id|X
c_func
(paren
id|prom_firstprop
)paren
comma
id|X
c_func
(paren
id|prom_nextprop
)paren
comma
id|X
c_func
(paren
id|prom_getproplen
)paren
comma
id|X
c_func
(paren
id|prom_getproperty
)paren
comma
id|X
c_func
(paren
id|prom_setprop
)paren
comma
id|X
c_func
(paren
id|prom_nodeops
)paren
comma
id|X
c_func
(paren
id|prom_getbootargs
)paren
comma
id|X
c_func
(paren
id|prom_apply_obio_ranges
)paren
comma
id|X
c_func
(paren
id|prom_getname
)paren
comma
id|X
c_func
(paren
id|prom_feval
)paren
comma
id|X
c_func
(paren
id|prom_getstring
)paren
comma
id|X
c_func
(paren
id|prom_apply_sbus_ranges
)paren
comma
id|X
c_func
(paren
id|prom_getint
)paren
comma
id|X
c_func
(paren
id|prom_getintdefault
)paren
comma
id|X
c_func
(paren
id|romvec
)paren
comma
multiline_comment|/* sparc library symbols */
id|X
c_func
(paren
id|bcopy
)paren
comma
id|X
c_func
(paren
id|memmove
)paren
comma
id|X
c_func
(paren
id|memscan
)paren
comma
id|X
c_func
(paren
id|strlen
)paren
comma
id|X
c_func
(paren
id|strnlen
)paren
comma
id|X
c_func
(paren
id|strcpy
)paren
comma
id|X
c_func
(paren
id|strncpy
)paren
comma
id|X
c_func
(paren
id|strcat
)paren
comma
id|X
c_func
(paren
id|strncat
)paren
comma
id|X
c_func
(paren
id|strcmp
)paren
comma
id|X
c_func
(paren
id|strncmp
)paren
comma
id|X
c_func
(paren
id|strchr
)paren
comma
id|X
c_func
(paren
id|strrchr
)paren
comma
id|X
c_func
(paren
id|strpbrk
)paren
comma
id|X
c_func
(paren
id|strtok
)paren
comma
id|X
c_func
(paren
id|strstr
)paren
comma
id|X
c_func
(paren
id|strspn
)paren
comma
multiline_comment|/* Special internal versions of library functions. */
id|X
c_func
(paren
id|__copy_1page
)paren
comma
id|X
c_func
(paren
id|__memcpy
)paren
comma
id|X
c_func
(paren
id|__memset
)paren
comma
id|X
c_func
(paren
id|bzero_1page
)paren
comma
id|X
c_func
(paren
id|__bzero
)paren
comma
id|X
c_func
(paren
id|__memscan_zero
)paren
comma
id|X
c_func
(paren
id|__memscan_generic
)paren
comma
id|X
c_func
(paren
id|__memcmp
)paren
comma
id|X
c_func
(paren
id|__strncmp
)paren
comma
multiline_comment|/* Moving data to/from userspace. */
id|X
c_func
(paren
id|__copy_user
)paren
comma
id|X
c_func
(paren
id|__clear_user
)paren
comma
id|X
c_func
(paren
id|__strncpy_from_user
)paren
comma
multiline_comment|/* No version information on this, heavily used in inline asm,&n;&t; * and will always be &squot;void __ret_efault(void)&squot;.&n;&t; */
id|XNOVERS
c_func
(paren
id|__ret_efault
)paren
comma
multiline_comment|/* No version information on these, as gcc produces such symbols. */
id|XNOVERS
c_func
(paren
id|memcmp
)paren
comma
id|XNOVERS
c_func
(paren
id|memcpy
)paren
comma
id|XNOVERS
c_func
(paren
id|memset
)paren
comma
id|XNOVERS
c_func
(paren
id|__ashrdi3
)paren
comma
id|XD
c_func
(paren
id|rem
)paren
comma
id|XD
c_func
(paren
id|urem
)paren
comma
id|XD
c_func
(paren
id|mul
)paren
comma
id|XD
c_func
(paren
id|umul
)paren
comma
id|XD
c_func
(paren
id|div
)paren
comma
id|XD
c_func
(paren
id|udiv
)paren
comma
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
DECL|function|arch_syms_export
r_void
id|arch_syms_export
c_func
(paren
r_void
)paren
(brace
id|register_symtab
c_func
(paren
op_amp
id|arch_symbol_table
)paren
suffix:semicolon
)brace
eof