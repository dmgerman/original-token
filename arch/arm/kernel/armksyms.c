macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/elf.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
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
r_struct
id|user_fp_struct
op_star
)paren
suffix:semicolon
r_extern
r_void
id|inswb
c_func
(paren
r_int
r_int
id|port
comma
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|outswb
c_func
(paren
r_int
r_int
id|port
comma
r_const
r_void
op_star
id|to
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
r_int
id|local_bh_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_int
r_int
id|local_irq_count
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
id|pid_t
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
suffix:semicolon
multiline_comment|/*&n; * syscalls&n; */
r_extern
r_int
id|sys_write
c_func
(paren
r_int
comma
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_read
c_func
(paren
r_int
comma
r_char
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_lseek
c_func
(paren
r_int
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_exit
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_int
id|sys_wait4
c_func
(paren
r_int
comma
r_int
op_star
comma
r_int
comma
r_struct
id|rusage
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * libgcc functions - functions that are used internally by the&n; * compiler...  (prototypes are not correct though, but that&n; * doesn&squot;t really matter since they&squot;re not versioned).&n; */
r_extern
r_void
id|__gcc_bcmp
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ashrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__cmpdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__divsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__lshrdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__moddi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__modsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__muldi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__negdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__ucmpdi2
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivdi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivmoddi4
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__udivsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__umoddi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__umodsi3
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ret_from_exception
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fpundefinstr
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|fp_enter
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|EXPORT_SYMBOL_ALIAS
mdefine_line|#define EXPORT_SYMBOL_ALIAS(sym,orig) &bslash;&n; const char __kstrtab_##sym##[] __attribute__((section(&quot;.kstrtab&quot;))) = &bslash;&n;    __MODULE_STRING(##sym##); &bslash;&n; const struct module_symbol __ksymtab_##sym __attribute__((section(&quot;__ksymtab&quot;))) = &bslash;&n;    { (unsigned long)&amp;##orig, __kstrtab_##sym };
multiline_comment|/*&n;&t; * floating point math emulator support.&n;&t; * These symbols will never change their calling convention...&n;&t; */
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|kern_fp_enter
comma
id|fp_enter
)paren
suffix:semicolon
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|fp_printk
comma
id|printk
)paren
suffix:semicolon
id|EXPORT_SYMBOL_ALIAS
c_func
(paren
id|fp_send_sig
comma
id|send_sig
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_CPU_26
DECL|variable|fpundefinstr
id|EXPORT_SYMBOL
c_func
(paren
id|fpundefinstr
)paren
suffix:semicolon
DECL|variable|ret_from_exception
id|EXPORT_SYMBOL
c_func
(paren
id|ret_from_exception
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* platform dependent support */
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
DECL|variable|udelay
id|EXPORT_SYMBOL
c_func
(paren
id|udelay
)paren
suffix:semicolon
DECL|variable|xchg_str
id|EXPORT_SYMBOL
c_func
(paren
id|xchg_str
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
macro_line|#ifdef CONFIG_CPU_32
DECL|variable|__ioremap
id|EXPORT_SYMBOL
c_func
(paren
id|__ioremap
)paren
suffix:semicolon
DECL|variable|__iounmap
id|EXPORT_SYMBOL
c_func
(paren
id|__iounmap
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|kernel_thread
id|EXPORT_SYMBOL
c_func
(paren
id|kernel_thread
)paren
suffix:semicolon
DECL|variable|system_rev
id|EXPORT_SYMBOL
c_func
(paren
id|system_rev
)paren
suffix:semicolon
DECL|variable|system_serial_low
id|EXPORT_SYMBOL
c_func
(paren
id|system_serial_low
)paren
suffix:semicolon
DECL|variable|system_serial_high
id|EXPORT_SYMBOL
c_func
(paren
id|system_serial_high
)paren
suffix:semicolon
DECL|variable|__bug
id|EXPORT_SYMBOL
c_func
(paren
id|__bug
)paren
suffix:semicolon
DECL|variable|__readwrite_bug
id|EXPORT_SYMBOL
c_func
(paren
id|__readwrite_bug
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
multiline_comment|/* processor dependencies */
macro_line|#ifdef MULTI_CPU
DECL|variable|processor
id|EXPORT_SYMBOL
c_func
(paren
id|processor
)paren
suffix:semicolon
macro_line|#else
DECL|variable|cpu_flush_cache_all
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_cache_all
)paren
suffix:semicolon
DECL|variable|cpu_flush_cache_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_cache_area
)paren
suffix:semicolon
DECL|variable|cpu_flush_cache_entry
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_cache_entry
)paren
suffix:semicolon
DECL|variable|cpu_clean_cache_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_clean_cache_area
)paren
suffix:semicolon
DECL|variable|cpu_flush_ram_page
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_ram_page
)paren
suffix:semicolon
DECL|variable|cpu_flush_tlb_all
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_tlb_all
)paren
suffix:semicolon
DECL|variable|cpu_flush_tlb_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_tlb_area
)paren
suffix:semicolon
DECL|variable|cpu_set_pgd
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pgd
)paren
suffix:semicolon
DECL|variable|cpu_set_pmd
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pmd
)paren
suffix:semicolon
DECL|variable|cpu_set_pte
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_set_pte
)paren
suffix:semicolon
DECL|variable|cpu_flush_icache_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_flush_icache_area
)paren
suffix:semicolon
DECL|variable|cpu_cache_wback_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_cache_wback_area
)paren
suffix:semicolon
DECL|variable|cpu_cache_purge_area
id|EXPORT_SYMBOL
c_func
(paren
id|cpu_cache_purge_area
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__machine_arch_type
id|EXPORT_SYMBOL
c_func
(paren
id|__machine_arch_type
)paren
suffix:semicolon
multiline_comment|/* networking */
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy
)paren
suffix:semicolon
DECL|variable|csum_partial_copy_nocheck
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy_nocheck
)paren
suffix:semicolon
DECL|variable|__csum_ipv6_magic
id|EXPORT_SYMBOL
c_func
(paren
id|__csum_ipv6_magic
)paren
suffix:semicolon
multiline_comment|/* io */
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
multiline_comment|/* address translation */
macro_line|#ifndef __virt_to_phys__is_a_macro
DECL|variable|__virt_to_phys
id|EXPORT_SYMBOL
c_func
(paren
id|__virt_to_phys
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __phys_to_virt__is_a_macro
DECL|variable|__phys_to_virt
id|EXPORT_SYMBOL
c_func
(paren
id|__phys_to_virt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __virt_to_bus__is_a_macro
DECL|variable|__virt_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|__virt_to_bus
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef __bus_to_virt__is_a_macro
DECL|variable|__bus_to_virt
id|EXPORT_SYMBOL
c_func
(paren
id|__bus_to_virt
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CONFIG_NO_PGT_CACHE
DECL|variable|quicklists
id|EXPORT_SYMBOL
c_func
(paren
id|quicklists
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|__handle_bad_pmd
id|EXPORT_SYMBOL
c_func
(paren
id|__handle_bad_pmd
)paren
suffix:semicolon
DECL|variable|__handle_bad_pmd_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|__handle_bad_pmd_kernel
)paren
suffix:semicolon
multiline_comment|/* string / mem functions */
DECL|variable|strcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcpy
)paren
suffix:semicolon
DECL|variable|strncpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncpy
)paren
suffix:semicolon
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcmp
)paren
suffix:semicolon
DECL|variable|strncmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncmp
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strspn
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strspn
)paren
suffix:semicolon
DECL|variable|strpbrk
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strpbrk
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strstr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strstr
)paren
suffix:semicolon
DECL|variable|__memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__memset
)paren
suffix:semicolon
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
multiline_comment|/* needed for some versions of gcc */
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
DECL|variable|memscan
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memscan
)paren
suffix:semicolon
DECL|variable|__memzero
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__memzero
)paren
suffix:semicolon
multiline_comment|/* user mem (segment) */
macro_line|#if defined(CONFIG_CPU_32)
DECL|variable|__arch_copy_from_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_copy_from_user
)paren
suffix:semicolon
DECL|variable|__arch_copy_to_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_copy_to_user
)paren
suffix:semicolon
DECL|variable|__arch_clear_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_clear_user
)paren
suffix:semicolon
DECL|variable|__arch_strnlen_user
id|EXPORT_SYMBOL
c_func
(paren
id|__arch_strnlen_user
)paren
suffix:semicolon
macro_line|#elif defined(CONFIG_CPU_26)
DECL|variable|uaccess_kernel
id|EXPORT_SYMBOL
c_func
(paren
id|uaccess_kernel
)paren
suffix:semicolon
DECL|variable|uaccess_user
id|EXPORT_SYMBOL
c_func
(paren
id|uaccess_user
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* gcc lib functions */
DECL|variable|__gcc_bcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__gcc_bcmp
)paren
suffix:semicolon
DECL|variable|__ashldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashldi3
)paren
suffix:semicolon
DECL|variable|__ashrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ashrdi3
)paren
suffix:semicolon
DECL|variable|__cmpdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__cmpdi2
)paren
suffix:semicolon
DECL|variable|__divdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divdi3
)paren
suffix:semicolon
DECL|variable|__divsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__divsi3
)paren
suffix:semicolon
DECL|variable|__lshrdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__lshrdi3
)paren
suffix:semicolon
DECL|variable|__moddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__moddi3
)paren
suffix:semicolon
DECL|variable|__modsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__modsi3
)paren
suffix:semicolon
DECL|variable|__muldi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__muldi3
)paren
suffix:semicolon
DECL|variable|__negdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__negdi2
)paren
suffix:semicolon
DECL|variable|__ucmpdi2
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__ucmpdi2
)paren
suffix:semicolon
DECL|variable|__udivdi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivdi3
)paren
suffix:semicolon
DECL|variable|__udivmoddi4
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivmoddi4
)paren
suffix:semicolon
DECL|variable|__udivsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__udivsi3
)paren
suffix:semicolon
DECL|variable|__umoddi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umoddi3
)paren
suffix:semicolon
DECL|variable|__umodsi3
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__umodsi3
)paren
suffix:semicolon
multiline_comment|/* bitops */
DECL|variable|set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|set_bit
)paren
suffix:semicolon
DECL|variable|test_and_set_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_set_bit
)paren
suffix:semicolon
DECL|variable|clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|clear_bit
)paren
suffix:semicolon
DECL|variable|test_and_clear_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_clear_bit
)paren
suffix:semicolon
DECL|variable|change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|change_bit
)paren
suffix:semicolon
DECL|variable|test_and_change_bit
id|EXPORT_SYMBOL
c_func
(paren
id|test_and_change_bit
)paren
suffix:semicolon
DECL|variable|find_first_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_first_zero_bit
)paren
suffix:semicolon
DECL|variable|find_next_zero_bit
id|EXPORT_SYMBOL
c_func
(paren
id|find_next_zero_bit
)paren
suffix:semicolon
multiline_comment|/* elf */
DECL|variable|elf_platform
id|EXPORT_SYMBOL
c_func
(paren
id|elf_platform
)paren
suffix:semicolon
DECL|variable|elf_hwcap
id|EXPORT_SYMBOL
c_func
(paren
id|elf_hwcap
)paren
suffix:semicolon
multiline_comment|/* syscalls */
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
DECL|variable|sys_open
id|EXPORT_SYMBOL
c_func
(paren
id|sys_open
)paren
suffix:semicolon
DECL|variable|sys_exit
id|EXPORT_SYMBOL
c_func
(paren
id|sys_exit
)paren
suffix:semicolon
DECL|variable|sys_wait4
id|EXPORT_SYMBOL
c_func
(paren
id|sys_wait4
)paren
suffix:semicolon
multiline_comment|/* semaphores */
DECL|variable|__down_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_failed
)paren
suffix:semicolon
DECL|variable|__down_interruptible_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_interruptible_failed
)paren
suffix:semicolon
DECL|variable|__down_trylock_failed
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__down_trylock_failed
)paren
suffix:semicolon
DECL|variable|__up_wakeup
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|__up_wakeup
)paren
suffix:semicolon
eof
