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
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
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
id|elf_fpregset_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|__lock_kernel
c_func
(paren
r_void
)paren
suffix:semicolon
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
multiline_comment|/* platform dependent support */
DECL|variable|boot_cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|boot_cpu_data
)paren
suffix:semicolon
DECL|variable|EISA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|EISA_bus
)paren
suffix:semicolon
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
DECL|variable|local_bh_count
id|EXPORT_SYMBOL
c_func
(paren
id|local_bh_count
)paren
suffix:semicolon
DECL|variable|local_irq_count
id|EXPORT_SYMBOL
c_func
(paren
id|local_irq_count
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
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy
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
DECL|variable|strlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|strlen_user
)paren
suffix:semicolon
macro_line|#ifdef __SMP__
DECL|variable|cpu_data
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_data
)paren
suffix:semicolon
DECL|variable|kernel_flag
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|kernel_flag
)paren
suffix:semicolon
DECL|variable|active_kernel_processor
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|active_kernel_processor
)paren
suffix:semicolon
DECL|variable|smp_invalidate_needed
id|EXPORT_SYMBOL
c_func
(paren
id|smp_invalidate_needed
)paren
suffix:semicolon
DECL|variable|__lock_kernel
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lock_kernel
)paren
suffix:semicolon
DECL|variable|lk_lockmsg
id|EXPORT_SYMBOL
c_func
(paren
id|lk_lockmsg
)paren
suffix:semicolon
DECL|variable|__cpu_logical_map
id|EXPORT_SYMBOL
c_func
(paren
id|__cpu_logical_map
)paren
suffix:semicolon
DECL|variable|smp_num_cpus
id|EXPORT_SYMBOL
c_func
(paren
id|smp_num_cpus
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
DECL|variable|synchronize_bh
id|EXPORT_SYMBOL
c_func
(paren
id|synchronize_bh
)paren
suffix:semicolon
DECL|variable|global_bh_count
id|EXPORT_SYMBOL
c_func
(paren
id|global_bh_count
)paren
suffix:semicolon
DECL|variable|global_bh_lock
id|EXPORT_SYMBOL
c_func
(paren
id|global_bh_lock
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
macro_line|#endif
macro_line|#ifdef CONFIG_MCA
multiline_comment|/* Adapter probing and info methods. */
DECL|variable|machine_id
id|EXPORT_SYMBOL
c_func
(paren
id|machine_id
)paren
suffix:semicolon
DECL|variable|mca_find_adapter
id|EXPORT_SYMBOL
c_func
(paren
id|mca_find_adapter
)paren
suffix:semicolon
DECL|variable|mca_write_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_write_pos
)paren
suffix:semicolon
DECL|variable|mca_read_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_read_pos
)paren
suffix:semicolon
DECL|variable|mca_read_stored_pos
id|EXPORT_SYMBOL
c_func
(paren
id|mca_read_stored_pos
)paren
suffix:semicolon
DECL|variable|mca_set_adapter_name
id|EXPORT_SYMBOL
c_func
(paren
id|mca_set_adapter_name
)paren
suffix:semicolon
DECL|variable|mca_get_adapter_name
id|EXPORT_SYMBOL
c_func
(paren
id|mca_get_adapter_name
)paren
suffix:semicolon
DECL|variable|mca_set_adapter_procfn
id|EXPORT_SYMBOL
c_func
(paren
id|mca_set_adapter_procfn
)paren
suffix:semicolon
DECL|variable|mca_isenabled
id|EXPORT_SYMBOL
c_func
(paren
id|mca_isenabled
)paren
suffix:semicolon
DECL|variable|mca_isadapter
id|EXPORT_SYMBOL
c_func
(paren
id|mca_isadapter
)paren
suffix:semicolon
macro_line|#endif
eof
