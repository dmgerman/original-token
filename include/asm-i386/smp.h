macro_line|#ifndef __ASM_SMP_H
DECL|macro|__ASM_SMP_H
mdefine_line|#define __ASM_SMP_H
multiline_comment|/*&n; * We need the APIC definitions automatically as part of &squot;smp.h&squot;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#ifndef ASSEMBLY
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/i82489.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#endif
macro_line|#endif
macro_line|#ifdef __SMP__
macro_line|#ifndef ASSEMBLY
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
multiline_comment|/*&n; *&t;Support definitions for SMP machines following the intel multiprocessing&n; *&t;specification&n; */
multiline_comment|/*&n; *&t;This tag identifies where the SMP configuration&n; *&t;information is. &n; */
DECL|macro|SMP_MAGIC_IDENT
mdefine_line|#define SMP_MAGIC_IDENT&t;((&squot;_&squot;&lt;&lt;24)|(&squot;P&squot;&lt;&lt;16)|(&squot;M&squot;&lt;&lt;8)|&squot;_&squot;)
DECL|struct|intel_mp_floating
r_struct
id|intel_mp_floating
(brace
DECL|member|mpf_signature
r_char
id|mpf_signature
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* &quot;_MP_&quot; &t;&t;&t;*/
DECL|member|mpf_physptr
r_int
r_int
id|mpf_physptr
suffix:semicolon
multiline_comment|/* Configuration table address&t;*/
DECL|member|mpf_length
r_int
r_char
id|mpf_length
suffix:semicolon
multiline_comment|/* Our length (paragraphs)&t;*/
DECL|member|mpf_specification
r_int
r_char
id|mpf_specification
suffix:semicolon
multiline_comment|/* Specification version&t;*/
DECL|member|mpf_checksum
r_int
r_char
id|mpf_checksum
suffix:semicolon
multiline_comment|/* Checksum (makes sum 0)&t;*/
DECL|member|mpf_feature1
r_int
r_char
id|mpf_feature1
suffix:semicolon
multiline_comment|/* Standard or configuration ? &t;*/
DECL|member|mpf_feature2
r_int
r_char
id|mpf_feature2
suffix:semicolon
multiline_comment|/* Bit7 set for IMCR|PIC&t;*/
DECL|member|mpf_feature3
r_int
r_char
id|mpf_feature3
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
DECL|member|mpf_feature4
r_int
r_char
id|mpf_feature4
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
DECL|member|mpf_feature5
r_int
r_char
id|mpf_feature5
suffix:semicolon
multiline_comment|/* Unused (0)&t;&t;&t;*/
)brace
suffix:semicolon
DECL|struct|mp_config_table
r_struct
id|mp_config_table
(brace
DECL|member|mpc_signature
r_char
id|mpc_signature
(braket
l_int|4
)braket
suffix:semicolon
DECL|macro|MPC_SIGNATURE
mdefine_line|#define MPC_SIGNATURE &quot;PCMP&quot;
DECL|member|mpc_length
r_int
r_int
id|mpc_length
suffix:semicolon
multiline_comment|/* Size of table */
DECL|member|mpc_spec
r_char
id|mpc_spec
suffix:semicolon
multiline_comment|/* 0x01 */
DECL|member|mpc_checksum
r_char
id|mpc_checksum
suffix:semicolon
DECL|member|mpc_oem
r_char
id|mpc_oem
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|mpc_productid
r_char
id|mpc_productid
(braket
l_int|12
)braket
suffix:semicolon
DECL|member|mpc_oemptr
r_int
r_int
id|mpc_oemptr
suffix:semicolon
multiline_comment|/* 0 if not present */
DECL|member|mpc_oemsize
r_int
r_int
id|mpc_oemsize
suffix:semicolon
multiline_comment|/* 0 if not present */
DECL|member|mpc_oemcount
r_int
r_int
id|mpc_oemcount
suffix:semicolon
DECL|member|mpc_lapic
r_int
r_int
id|mpc_lapic
suffix:semicolon
multiline_comment|/* APIC address */
DECL|member|reserved
r_int
r_int
id|reserved
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Followed by entries */
DECL|macro|MP_PROCESSOR
mdefine_line|#define&t;MP_PROCESSOR&t;0
DECL|macro|MP_BUS
mdefine_line|#define&t;MP_BUS&t;&t;1
DECL|macro|MP_IOAPIC
mdefine_line|#define&t;MP_IOAPIC&t;2
DECL|macro|MP_INTSRC
mdefine_line|#define&t;MP_INTSRC&t;3
DECL|macro|MP_LINTSRC
mdefine_line|#define&t;MP_LINTSRC&t;4
DECL|struct|mpc_config_processor
r_struct
id|mpc_config_processor
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_apicid
r_int
r_char
id|mpc_apicid
suffix:semicolon
multiline_comment|/* Local APIC number */
DECL|member|mpc_apicver
r_int
r_char
id|mpc_apicver
suffix:semicolon
multiline_comment|/* Its versions */
DECL|member|mpc_cpuflag
r_int
r_char
id|mpc_cpuflag
suffix:semicolon
DECL|macro|CPU_ENABLED
mdefine_line|#define CPU_ENABLED&t;&t;1&t;/* Processor is available */
DECL|macro|CPU_BOOTPROCESSOR
mdefine_line|#define CPU_BOOTPROCESSOR&t;2&t;/* Processor is the BP */
DECL|member|mpc_cpufeature
r_int
r_int
id|mpc_cpufeature
suffix:semicolon
DECL|macro|CPU_STEPPING_MASK
mdefine_line|#define CPU_STEPPING_MASK 0x0F
DECL|macro|CPU_MODEL_MASK
mdefine_line|#define CPU_MODEL_MASK&t;0xF0
DECL|macro|CPU_FAMILY_MASK
mdefine_line|#define CPU_FAMILY_MASK&t;0xF00
DECL|member|mpc_featureflag
r_int
r_int
id|mpc_featureflag
suffix:semicolon
multiline_comment|/* CPUID feature value */
DECL|member|mpc_reserved
r_int
r_int
id|mpc_reserved
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpc_config_bus
r_struct
id|mpc_config_bus
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_busid
r_int
r_char
id|mpc_busid
suffix:semicolon
r_int
r_char
id|mpc_bustype
(braket
l_int|6
)braket
id|__attribute
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|BUSTYPE_EISA
mdefine_line|#define BUSTYPE_EISA&t;&quot;EISA&quot;
DECL|macro|BUSTYPE_ISA
mdefine_line|#define BUSTYPE_ISA&t;&quot;ISA&quot;
DECL|macro|BUSTYPE_INTERN
mdefine_line|#define BUSTYPE_INTERN&t;&quot;INTERN&quot;&t;/* Internal BUS */
DECL|macro|BUSTYPE_MCA
mdefine_line|#define BUSTYPE_MCA&t;&quot;MCA&quot;
DECL|macro|BUSTYPE_VL
mdefine_line|#define BUSTYPE_VL&t;&quot;VL&quot;&t;&t;/* Local bus */
DECL|macro|BUSTYPE_PCI
mdefine_line|#define BUSTYPE_PCI&t;&quot;PCI&quot;
DECL|macro|BUSTYPE_PCMCIA
mdefine_line|#define BUSTYPE_PCMCIA&t;&quot;PCMCIA&quot;
multiline_comment|/* We don&squot;t understand the others */
DECL|struct|mpc_config_ioapic
r_struct
id|mpc_config_ioapic
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_apicid
r_int
r_char
id|mpc_apicid
suffix:semicolon
DECL|member|mpc_apicver
r_int
r_char
id|mpc_apicver
suffix:semicolon
DECL|member|mpc_flags
r_int
r_char
id|mpc_flags
suffix:semicolon
DECL|macro|MPC_APIC_USABLE
mdefine_line|#define MPC_APIC_USABLE&t;&t;0x01
DECL|member|mpc_apicaddr
r_int
r_int
id|mpc_apicaddr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|mpc_config_intsrc
r_struct
id|mpc_config_intsrc
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_irqtype
r_int
r_char
id|mpc_irqtype
suffix:semicolon
DECL|member|mpc_irqflag
r_int
r_int
id|mpc_irqflag
suffix:semicolon
DECL|member|mpc_srcbus
r_int
r_char
id|mpc_srcbus
suffix:semicolon
DECL|member|mpc_srcbusirq
r_int
r_char
id|mpc_srcbusirq
suffix:semicolon
DECL|member|mpc_dstapic
r_int
r_char
id|mpc_dstapic
suffix:semicolon
DECL|member|mpc_dstirq
r_int
r_char
id|mpc_dstirq
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MP_INT_VECTORED
mdefine_line|#define MP_INT_VECTORED&t;&t;0
DECL|macro|MP_INT_NMI
mdefine_line|#define MP_INT_NMI&t;&t;1
DECL|macro|MP_INT_SMI
mdefine_line|#define MP_INT_SMI&t;&t;2
DECL|macro|MP_INT_EXTINT
mdefine_line|#define MP_INT_EXTINT&t;&t;3
DECL|macro|MP_IRQDIR_DEFAULT
mdefine_line|#define MP_IRQDIR_DEFAULT&t;0
DECL|macro|MP_IRQDIR_HIGH
mdefine_line|#define MP_IRQDIR_HIGH&t;&t;1
DECL|macro|MP_IRQDIR_LOW
mdefine_line|#define MP_IRQDIR_LOW&t;&t;3
DECL|struct|mpc_config_intlocal
r_struct
id|mpc_config_intlocal
(brace
DECL|member|mpc_type
r_int
r_char
id|mpc_type
suffix:semicolon
DECL|member|mpc_irqtype
r_int
r_char
id|mpc_irqtype
suffix:semicolon
DECL|member|mpc_irqflag
r_int
r_int
id|mpc_irqflag
suffix:semicolon
DECL|member|mpc_srcbusid
r_int
r_char
id|mpc_srcbusid
suffix:semicolon
DECL|member|mpc_srcbusirq
r_int
r_char
id|mpc_srcbusirq
suffix:semicolon
DECL|member|mpc_destapic
r_int
r_char
id|mpc_destapic
suffix:semicolon
DECL|macro|MP_APIC_ALL
mdefine_line|#define MP_APIC_ALL&t;0xFF
DECL|member|mpc_destapiclint
r_int
r_char
id|mpc_destapiclint
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Default configurations&n; *&n; *&t;1&t;2 CPU ISA 82489DX&n; *&t;2&t;2 CPU EISA 82489DX no IRQ 8 or timer chaining&n; *&t;3&t;2 CPU EISA 82489DX&n; *&t;4&t;2 CPU MCA 82489DX&n; *&t;5&t;2 CPU ISA+PCI&n; *&t;6&t;2 CPU EISA+PCI&n; *&t;7&t;2 CPU MCA+PCI&n; */
multiline_comment|/*&n; *&t;Private routines/data&n; */
r_extern
r_int
id|smp_found_config
suffix:semicolon
r_extern
r_void
id|init_smp_config
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
r_int
id|smp_alloc_memory
c_func
(paren
r_int
r_int
id|mem_base
)paren
suffix:semicolon
r_extern
r_int
r_char
id|boot_cpu_id
suffix:semicolon
r_extern
r_int
r_int
id|cpu_present_map
suffix:semicolon
r_extern
r_int
r_int
id|cpu_online_map
suffix:semicolon
r_extern
r_volatile
r_int
id|cpu_number_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|smp_invalidate_needed
suffix:semicolon
r_extern
r_void
id|smp_flush_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_volatile
r_int
r_int
id|cpu_callin_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
r_extern
r_void
id|smp_message_irq
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|smp_send_reschedule
c_func
(paren
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ipi_count
suffix:semicolon
r_extern
r_void
id|smp_invalidate_rcv
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Process an NMI */
r_extern
r_void
id|smp_local_timer_interrupt
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|mtrr_hook
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_APIC_clock
(paren
r_void
)paren
suffix:semicolon
r_extern
r_volatile
r_int
id|__cpu_logical_map
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|cpu_logical_map
r_extern
r_inline
r_int
id|cpu_logical_map
c_func
(paren
r_int
id|cpu
)paren
(brace
r_return
id|__cpu_logical_map
(braket
id|cpu
)braket
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;General functions that each host system must provide.&n; */
r_extern
r_void
id|smp_callin
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_boot_cpus
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|smp_store_cpu_info
c_func
(paren
r_int
id|id
)paren
suffix:semicolon
multiline_comment|/* Store per CPU info (like the initial udelay numbers */
multiline_comment|/*&n; * This function is needed by all SMP systems. It must _always_ be valid&n; * from the initial startup. We map APIC_BASE very early in page_setup(),&n; * so this is correct in the x86 case.&n; */
DECL|macro|smp_processor_id
mdefine_line|#define smp_processor_id() (current-&gt;processor)
DECL|function|hard_smp_processor_id
r_extern
id|__inline
r_int
id|hard_smp_processor_id
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* we don&squot;t want to mark this access volatile - bad code generation */
r_return
id|GET_APIC_ID
c_func
(paren
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|APIC_ID
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !ASSEMBLY */
DECL|macro|NO_PROC_ID
mdefine_line|#define NO_PROC_ID&t;&t;0xFF&t;&t;/* No processor magic marker */
multiline_comment|/*&n; *&t;This magic constant controls our willingness to transfer&n; *&t;a process across CPUs. Such a transfer incurs misses on the L1&n; *&t;cache, and on a P6 or P5 with multiple L2 caches L2 hits. My&n; *&t;gut feeling is this will vary by board in value. For a board&n; *&t;with separate L2 cache it probably depends also on the RSS, and&n; *&t;for a board with shared L2 cache it ought to decay fast as other&n; *&t;processes are run.&n; */
DECL|macro|PROC_CHANGE_PENALTY
mdefine_line|#define PROC_CHANGE_PENALTY&t;15&t;&t;/* Schedule penalty */
macro_line|#endif
macro_line|#endif
eof
