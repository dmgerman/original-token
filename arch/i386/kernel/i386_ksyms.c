macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elfcore.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/apm_bios.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/i387.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mmx.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
id|spinlock_t
id|rtc_lock
suffix:semicolon
macro_line|#if defined(CONFIG_APM) || defined(CONFIG_APM_MODULE)
r_extern
r_void
id|machine_real_restart
c_func
(paren
r_int
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|variable|machine_real_restart
id|EXPORT_SYMBOL
c_func
(paren
id|machine_real_restart
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__write_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
)paren
suffix:semicolon
r_extern
r_void
id|FASTCALL
c_func
(paren
id|__read_lock_failed
c_func
(paren
id|rwlock_t
op_star
id|rw
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_BLK_DEV_IDE) || defined(CONFIG_BLK_DEV_HD) || defined(CONFIG_BLK_DEV_IDE_MODULE) || defined(CONFIG_BLK_DEV_HD_MODULE)
r_extern
r_struct
id|drive_info_struct
id|drive_info
suffix:semicolon
DECL|variable|drive_info
id|EXPORT_SYMBOL
c_func
(paren
id|drive_info
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_int
r_int
id|get_cmos_time
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* platform dependent support */
DECL|variable|boot_cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|boot_cpu_data
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_EISA
DECL|variable|EISA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|EISA_bus
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|MCA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|MCA_bus
)paren
suffix:semicolon
DECL|variable|__verify_write
id|EXPORT_SYMBOL
c_func
(paren
id|__verify_write
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
DECL|variable|dump_extended_fpu
id|EXPORT_SYMBOL
c_func
(paren
id|dump_extended_fpu
)paren
suffix:semicolon
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|iounmap
)paren
suffix:semicolon
DECL|variable|__io_virt_debug
id|EXPORT_SYMBOL
c_func
(paren
id|__io_virt_debug
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
DECL|variable|probe_irq_mask
id|EXPORT_SYMBOL
c_func
(paren
id|probe_irq_mask
)paren
suffix:semicolon
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|pm_idle
id|EXPORT_SYMBOL
c_func
(paren
id|pm_idle
)paren
suffix:semicolon
DECL|variable|pm_power_off
id|EXPORT_SYMBOL
c_func
(paren
id|pm_power_off
)paren
suffix:semicolon
DECL|variable|get_cmos_time
id|EXPORT_SYMBOL
c_func
(paren
id|get_cmos_time
)paren
suffix:semicolon
DECL|variable|apm_info
id|EXPORT_SYMBOL
c_func
(paren
id|apm_info
)paren
suffix:semicolon
DECL|variable|gdt
id|EXPORT_SYMBOL
c_func
(paren
id|gdt
)paren
suffix:semicolon
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
DECL|variable|__down_failed_trylock
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed_trylock
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
DECL|variable|__down_write_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_write_failed
)paren
suffix:semicolon
DECL|variable|__down_read_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_read_failed
)paren
suffix:semicolon
DECL|variable|__rwsem_wake
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__rwsem_wake
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy_generic
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_generic
)paren
suffix:semicolon
multiline_comment|/* Delay loops */
DECL|variable|__udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__udelay
)paren
suffix:semicolon
DECL|variable|__delay
id|EXPORT_SYMBOL
c_func
(paren
id|__delay
)paren
suffix:semicolon
DECL|variable|__const_udelay
id|EXPORT_SYMBOL
c_func
(paren
id|__const_udelay
)paren
suffix:semicolon
DECL|variable|__get_user_1
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_1
)paren
suffix:semicolon
DECL|variable|__get_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_2
)paren
suffix:semicolon
DECL|variable|__get_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__get_user_4
)paren
suffix:semicolon
DECL|variable|__put_user_1
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_1
)paren
suffix:semicolon
DECL|variable|__put_user_2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_2
)paren
suffix:semicolon
DECL|variable|__put_user_4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__put_user_4
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
DECL|variable|simple_strtol
id|EXPORT_SYMBOL
c_func
(paren
id|simple_strtol
)paren
suffix:semicolon
DECL|variable|strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|strncpy_from_user
)paren
suffix:semicolon
DECL|variable|__strncpy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__strncpy_from_user
)paren
suffix:semicolon
DECL|variable|clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|clear_user
)paren
suffix:semicolon
DECL|variable|__clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__clear_user
)paren
suffix:semicolon
DECL|variable|__generic_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__generic_copy_from_user
)paren
suffix:semicolon
DECL|variable|__generic_copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|__generic_copy_to_user
)paren
suffix:semicolon
DECL|variable|strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|strnlen_user
)paren
suffix:semicolon
DECL|variable|pci_alloc_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_alloc_consistent
)paren
suffix:semicolon
DECL|variable|pci_free_consistent
id|EXPORT_SYMBOL
c_func
(paren
id|pci_free_consistent
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI
DECL|variable|pcibios_penalize_isa_irq
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_penalize_isa_irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_X86_USE_3DNOW
DECL|variable|_mmx_memcpy
id|EXPORT_SYMBOL
c_func
(paren
id|_mmx_memcpy
)paren
suffix:semicolon
DECL|variable|mmx_clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|mmx_clear_page
)paren
suffix:semicolon
DECL|variable|mmx_copy_page
id|EXPORT_SYMBOL
c_func
(paren
id|mmx_copy_page
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
DECL|variable|cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_data
)paren
suffix:semicolon
DECL|variable|kernel_flag
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_flag
)paren
suffix:semicolon
DECL|variable|smp_num_cpus
id|EXPORT_SYMBOL
c_func
(paren
id|smp_num_cpus
)paren
suffix:semicolon
DECL|variable|cpu_online_map
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_online_map
)paren
suffix:semicolon
DECL|variable|__write_lock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__write_lock_failed
)paren
suffix:semicolon
DECL|variable|__read_lock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__read_lock_failed
)paren
suffix:semicolon
multiline_comment|/* Global SMP irq stuff */
DECL|variable|synchronize_irq
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_irq
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
DECL|variable|smp_call_function
id|EXPORT_SYMBOL
c_func
(paren
id|smp_call_function
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
DECL|variable|machine_id
id|EXPORT_SYMBOL
c_func
(paren
id|machine_id
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_VT
DECL|variable|screen_info
id|EXPORT_SYMBOL
c_func
(paren
id|screen_info
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|get_wchan
id|EXPORT_SYMBOL
c_func
(paren
id|get_wchan
)paren
suffix:semicolon
DECL|variable|rtc_lock
id|EXPORT_SYMBOL
c_func
(paren
id|rtc_lock
)paren
suffix:semicolon
DECL|macro|memcpy
macro_line|#undef memcpy
DECL|macro|memset
macro_line|#undef memset
r_extern
r_void
op_star
id|memset
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
id|memcpy
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
macro_line|#ifdef CONFIG_X86_PAE
DECL|variable|empty_zero_page
id|EXPORT_SYMBOL
c_func
(paren
id|empty_zero_page
)paren
suffix:semicolon
macro_line|#endif
eof
