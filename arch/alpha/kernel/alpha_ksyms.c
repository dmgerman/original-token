multiline_comment|/*&n; * linux/arch/alpha/kernel/ksyms.c&n; *&n; * Export the alpha-specific functions that are needed for loadable&n; * modules.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;asm/unistd.h&gt;
r_extern
r_struct
id|hwrpb_struct
op_star
id|hwrpb
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
r_extern
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
comma
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|___delay
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* these are C runtime functions with special calling conventions: */
r_extern
r_void
id|__divl
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__reml
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remq
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remlu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divqu
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__remqu
(paren
r_void
)paren
suffix:semicolon
DECL|variable|alpha_mv
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_mv
)paren
suffix:semicolon
DECL|variable|enable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|enable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq
)paren
suffix:semicolon
DECL|variable|disable_irq_nosync
id|EXPORT_SYMBOL
c_func
(paren
id|disable_irq_nosync
)paren
suffix:semicolon
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
DECL|variable|perf_irq
id|EXPORT_SYMBOL
c_func
(paren
id|perf_irq
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|_inb
id|EXPORT_SYMBOL
c_func
(paren
id|_inb
)paren
suffix:semicolon
DECL|variable|_inw
id|EXPORT_SYMBOL
c_func
(paren
id|_inw
)paren
suffix:semicolon
DECL|variable|_inl
id|EXPORT_SYMBOL
c_func
(paren
id|_inl
)paren
suffix:semicolon
DECL|variable|_outb
id|EXPORT_SYMBOL
c_func
(paren
id|_outb
)paren
suffix:semicolon
DECL|variable|_outw
id|EXPORT_SYMBOL
c_func
(paren
id|_outw
)paren
suffix:semicolon
DECL|variable|_outl
id|EXPORT_SYMBOL
c_func
(paren
id|_outl
)paren
suffix:semicolon
DECL|variable|_readb
id|EXPORT_SYMBOL
c_func
(paren
id|_readb
)paren
suffix:semicolon
DECL|variable|_readw
id|EXPORT_SYMBOL
c_func
(paren
id|_readw
)paren
suffix:semicolon
DECL|variable|_readl
id|EXPORT_SYMBOL
c_func
(paren
id|_readl
)paren
suffix:semicolon
DECL|variable|_writeb
id|EXPORT_SYMBOL
c_func
(paren
id|_writeb
)paren
suffix:semicolon
DECL|variable|_writew
id|EXPORT_SYMBOL
c_func
(paren
id|_writew
)paren
suffix:semicolon
DECL|variable|_writel
id|EXPORT_SYMBOL
c_func
(paren
id|_writel
)paren
suffix:semicolon
DECL|variable|_memcpy_fromio
id|EXPORT_SYMBOL
c_func
(paren
id|_memcpy_fromio
)paren
suffix:semicolon
DECL|variable|_memcpy_toio
id|EXPORT_SYMBOL
c_func
(paren
id|_memcpy_toio
)paren
suffix:semicolon
DECL|variable|_memset_c_io
id|EXPORT_SYMBOL
c_func
(paren
id|_memset_c_io
)paren
suffix:semicolon
DECL|variable|insb
id|EXPORT_SYMBOL
c_func
(paren
id|insb
)paren
suffix:semicolon
DECL|variable|insw
id|EXPORT_SYMBOL
c_func
(paren
id|insw
)paren
suffix:semicolon
DECL|variable|insl
id|EXPORT_SYMBOL
c_func
(paren
id|insl
)paren
suffix:semicolon
DECL|variable|outsb
id|EXPORT_SYMBOL
c_func
(paren
id|outsb
)paren
suffix:semicolon
DECL|variable|outsw
id|EXPORT_SYMBOL
c_func
(paren
id|outsw
)paren
suffix:semicolon
DECL|variable|outsl
id|EXPORT_SYMBOL
c_func
(paren
id|outsl
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strcpy
id|EXPORT_SYMBOL
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|__memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|__memcpy
)paren
suffix:semicolon
DECL|variable|__memset
id|EXPORT_SYMBOL
c_func
(paren
id|__memset
)paren
suffix:semicolon
DECL|variable|__memsetw
id|EXPORT_SYMBOL
c_func
(paren
id|__memsetw
)paren
suffix:semicolon
DECL|variable|__constant_c_memset
id|EXPORT_SYMBOL
c_func
(paren
id|__constant_c_memset
)paren
suffix:semicolon
DECL|variable|dump_thread
id|EXPORT_SYMBOL
c_func
(paren
id|dump_thread
)paren
suffix:semicolon
DECL|variable|dump_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_fpu
)paren
suffix:semicolon
DECL|variable|hwrpb
id|EXPORT_SYMBOL
c_func
(paren
id|hwrpb
)paren
suffix:semicolon
DECL|variable|wrusp
id|EXPORT_SYMBOL
c_func
(paren
id|wrusp
)paren
suffix:semicolon
DECL|variable|start_thread
id|EXPORT_SYMBOL
c_func
(paren
id|start_thread
)paren
suffix:semicolon
DECL|variable|alpha_read_fp_reg
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_read_fp_reg
)paren
suffix:semicolon
DECL|variable|alpha_write_fp_reg
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_write_fp_reg
)paren
suffix:semicolon
multiline_comment|/* In-kernel system calls.  */
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|sys_dup
id|EXPORT_SYMBOL
c_func
(paren
id|sys_dup
)paren
suffix:semicolon
DECL|variable|sys_exit
id|EXPORT_SYMBOL
c_func
(paren
id|sys_exit
)paren
suffix:semicolon
DECL|variable|sys_write
id|EXPORT_SYMBOL
c_func
(paren
id|sys_write
)paren
suffix:semicolon
DECL|variable|sys_read
id|EXPORT_SYMBOL
c_func
(paren
id|sys_read
)paren
suffix:semicolon
DECL|variable|sys_lseek
id|EXPORT_SYMBOL
c_func
(paren
id|sys_lseek
)paren
suffix:semicolon
DECL|variable|__kernel_execve
id|EXPORT_SYMBOL
c_func
(paren
id|__kernel_execve
)paren
suffix:semicolon
DECL|variable|sys_setsid
id|EXPORT_SYMBOL
c_func
(paren
id|sys_setsid
)paren
suffix:semicolon
DECL|variable|sys_sync
id|EXPORT_SYMBOL
c_func
(paren
id|sys_sync
)paren
suffix:semicolon
DECL|variable|sys_wait4
id|EXPORT_SYMBOL
c_func
(paren
id|sys_wait4
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_tcpudp_magic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_tcpudp_magic
)paren
suffix:semicolon
DECL|variable|ip_compute_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_compute_csum
)paren
suffix:semicolon
DECL|variable|ip_fast_csum
id|EXPORT_SYMBOL
c_func
(paren
id|ip_fast_csum
)paren
suffix:semicolon
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_from_user
)paren
suffix:semicolon
DECL|variable|csum_ipv6_magic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_ipv6_magic
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_MATHEMU_MODULE
r_extern
r_int
(paren
op_star
id|alpha_fp_emul_imprecise
)paren
(paren
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
(paren
op_star
id|alpha_fp_emul
)paren
(paren
r_int
r_int
id|pc
)paren
suffix:semicolon
DECL|variable|alpha_fp_emul_imprecise
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_fp_emul_imprecise
)paren
suffix:semicolon
DECL|variable|alpha_fp_emul
id|EXPORT_SYMBOL
c_func
(paren
id|alpha_fp_emul
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * The following are specially called from the uaccess assembly stubs.&n; */
DECL|variable|__copy_user
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|__do_clear_user
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__do_clear_user
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strnlen_user
)paren
suffix:semicolon
multiline_comment|/*&n; * The following are specially called from the semaphore assembly stubs.&n; */
DECL|variable|__down_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed
)paren
suffix:semicolon
DECL|variable|__down_failed_interruptible
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed_interruptible
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
multiline_comment|/*&n; * This is called specially from __delay.&n; */
DECL|variable|___delay
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|___delay
)paren
suffix:semicolon
multiline_comment|/* &n; * SMP-specific symbols.&n; */
macro_line|#ifdef __SMP__
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
)paren
suffix:semicolon
DECL|variable|flush_tlb_all
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_all
)paren
suffix:semicolon
DECL|variable|flush_tlb_mm
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_mm
)paren
suffix:semicolon
DECL|variable|flush_tlb_page
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_page
)paren
suffix:semicolon
DECL|variable|flush_tlb_range
id|EXPORT_SYMBOL
c_func
(paren
id|flush_tlb_range
)paren
suffix:semicolon
DECL|variable|cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_data
)paren
suffix:semicolon
DECL|variable|cpu_number_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_number_map
)paren
suffix:semicolon
DECL|variable|global_bh_lock
id|EXPORT_SYMBOL
c_func
(paren
id|global_bh_lock
)paren
suffix:semicolon
DECL|variable|global_bh_count
id|EXPORT_SYMBOL
c_func
(paren
id|global_bh_count
)paren
suffix:semicolon
DECL|variable|synchronize_bh
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_bh
)paren
suffix:semicolon
DECL|variable|global_irq_holder
id|EXPORT_SYMBOL
c_func
(paren
id|global_irq_holder
)paren
suffix:semicolon
DECL|variable|__global_cli
id|EXPORT_SYMBOL
c_func
(paren
id|__global_cli
)paren
suffix:semicolon
DECL|variable|__global_sti
id|EXPORT_SYMBOL
c_func
(paren
id|__global_sti
)paren
suffix:semicolon
DECL|variable|__global_save_flags
id|EXPORT_SYMBOL
c_func
(paren
id|__global_save_flags
)paren
suffix:semicolon
DECL|variable|__global_restore_flags
id|EXPORT_SYMBOL
c_func
(paren
id|__global_restore_flags
)paren
suffix:semicolon
macro_line|#if DEBUG_SPINLOCK
DECL|variable|spin_unlock
id|EXPORT_SYMBOL
c_func
(paren
id|spin_unlock
)paren
suffix:semicolon
DECL|variable|debug_spin_lock
id|EXPORT_SYMBOL
c_func
(paren
id|debug_spin_lock
)paren
suffix:semicolon
DECL|variable|debug_spin_trylock
id|EXPORT_SYMBOL
c_func
(paren
id|debug_spin_trylock
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if DEBUG_RWLOCK
DECL|variable|write_lock
id|EXPORT_SYMBOL
c_func
(paren
id|write_lock
)paren
suffix:semicolon
DECL|variable|read_lock
id|EXPORT_SYMBOL
c_func
(paren
id|read_lock
)paren
suffix:semicolon
macro_line|#endif
macro_line|#else /* __SMP__ */
DECL|variable|__local_bh_count
id|EXPORT_SYMBOL
c_func
(paren
id|__local_bh_count
)paren
suffix:semicolon
DECL|variable|__local_irq_count
id|EXPORT_SYMBOL
c_func
(paren
id|__local_irq_count
)paren
suffix:semicolon
macro_line|#endif /* __SMP__ */
multiline_comment|/*&n; * The following are special because they&squot;re not called&n; * explicitly (the C compiler or assembler generates them in&n; * response to division operations).  Fortunately, their&n; * interface isn&squot;t gonna change any time soon now, so it&squot;s OK&n; * to leave it out of version control.&n; */
DECL|macro|memcpy
macro_line|# undef memcpy
DECL|macro|memset
macro_line|# undef memset
DECL|variable|__divl
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divl
)paren
suffix:semicolon
DECL|variable|__divlu
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divlu
)paren
suffix:semicolon
DECL|variable|__divq
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divq
)paren
suffix:semicolon
DECL|variable|__divqu
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divqu
)paren
suffix:semicolon
DECL|variable|__reml
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__reml
)paren
suffix:semicolon
DECL|variable|__remlu
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__remlu
)paren
suffix:semicolon
DECL|variable|__remq
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__remq
)paren
suffix:semicolon
DECL|variable|__remqu
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__remqu
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
eof
