macro_line|#ifndef __irq_cpustat_h
DECL|macro|__irq_cpustat_h
mdefine_line|#define __irq_cpustat_h
multiline_comment|/*&n; * Contains default mappings for irq_cpustat_t, used by almost every&n; * architecture.  Some arch (like s390) have per cpu hardware pages and&n; * they define their own mappings for irq_stat.&n; *&n; * Keith Owens &lt;kaos@ocs.com.au&gt; July 2000.&n; */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Simple wrappers reducing source bloat.  Define all irq_stat fields&n; * here, even ones that are arch dependent.  That way we get common&n; * definitions instead of differing sets for each arch.&n; */
r_extern
id|irq_cpustat_t
id|irq_stat
(braket
)braket
suffix:semicolon
multiline_comment|/* defined in asm/hardirq.h */
macro_line|#ifdef CONFIG_SMP
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu, member)&t;(irq_stat[cpu].member)
macro_line|#else
DECL|macro|__IRQ_STAT
mdefine_line|#define __IRQ_STAT(cpu, member)&t;((void)(cpu), irq_stat[0].member)
macro_line|#endif&t;
multiline_comment|/* arch independent irq_stat fields */
DECL|macro|softirq_active
mdefine_line|#define softirq_active(cpu)&t;__IRQ_STAT((cpu), __softirq_active)
DECL|macro|softirq_mask
mdefine_line|#define softirq_mask(cpu)&t;__IRQ_STAT((cpu), __softirq_mask)
DECL|macro|local_irq_count
mdefine_line|#define local_irq_count(cpu)&t;__IRQ_STAT((cpu), __local_irq_count)
DECL|macro|local_bh_count
mdefine_line|#define local_bh_count(cpu)&t;__IRQ_STAT((cpu), __local_bh_count)
DECL|macro|syscall_count
mdefine_line|#define syscall_count(cpu)&t;__IRQ_STAT((cpu), __syscall_count)
multiline_comment|/* arch dependent irq_stat fields */
DECL|macro|nmi_count
mdefine_line|#define nmi_count(cpu)&t;&t;__IRQ_STAT((cpu), __nmi_count)&t;&t;/* i386, ia64 */
macro_line|#endif&t;/* __irq_cpustat_h */
eof
