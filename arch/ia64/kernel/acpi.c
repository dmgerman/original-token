multiline_comment|/*&n; * Advanced Configuration and Power Interface &n; *&n; * Based on &squot;ACPI Specification 1.0b&squot; February 2, 1999 and &n; * &squot;IA-64 Extensions to ACPI Specification&squot; Revision 0.6&n; * &n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999,2000 Walt Drummond &lt;drummond@valinux.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;asm/acpi-ext.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/efi.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/iosapic.h&gt;
DECL|macro|ACPI_DEBUG
macro_line|#undef ACPI_DEBUG&t;&t;/* Guess what this does? */
macro_line|#ifdef CONFIG_SMP
r_extern
r_struct
id|smp_boot_data
id|smp
suffix:semicolon
macro_line|#endif
multiline_comment|/* These are ugly but will be reclaimed by the kernel */
DECL|variable|available_cpus
r_int
id|__initdata
id|available_cpus
op_assign
l_int|0
suffix:semicolon
DECL|variable|total_cpus
r_int
id|__initdata
id|total_cpus
op_assign
l_int|0
suffix:semicolon
DECL|variable|pm_idle
r_void
(paren
op_star
id|pm_idle
)paren
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Identify usable CPU&squot;s and remember them for SMP bringup later.&n; */
r_static
r_void
id|__init
DECL|function|acpi_lsapic
id|acpi_lsapic
c_func
(paren
r_char
op_star
id|p
)paren
(brace
r_int
id|add
op_assign
l_int|1
suffix:semicolon
id|acpi_entry_lsapic_t
op_star
id|lsapic
op_assign
(paren
id|acpi_entry_lsapic_t
op_star
)paren
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lsapic-&gt;flags
op_amp
id|LSAPIC_PRESENT
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;      CPU %d (%.04x:%.04x): &quot;
comma
id|total_cpus
comma
id|lsapic-&gt;eid
comma
id|lsapic-&gt;id
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|lsapic-&gt;flags
op_amp
id|LSAPIC_ENABLED
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Disabled.&bslash;n&quot;
)paren
suffix:semicolon
id|add
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lsapic-&gt;flags
op_amp
id|LSAPIC_PERFORMANCE_RESTRICTED
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Performance Restricted; ignoring.&bslash;n&quot;
)paren
suffix:semicolon
id|add
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|add
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Available.&bslash;n&quot;
)paren
suffix:semicolon
id|available_cpus
op_increment
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
macro_line|# if LARGE_CPU_ID_OK
id|smp.cpu_map
(braket
id|total_cpus
)braket
op_assign
(paren
id|lsapic-&gt;id
op_lshift
l_int|8
)paren
op_or
id|lsapic-&gt;eid
suffix:semicolon
macro_line|# else
id|smp.cpu_map
(braket
id|total_cpus
)braket
op_assign
id|lsapic-&gt;id
suffix:semicolon
macro_line|# endif
macro_line|#endif
)brace
id|total_cpus
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * Find all IOSAPICs and tag the iosapic_vector structure with the appropriate &n; * base addresses.&n; */
r_static
r_void
id|__init
DECL|function|acpi_iosapic
id|acpi_iosapic
c_func
(paren
r_char
op_star
id|p
)paren
(brace
multiline_comment|/*&n;&t; * This is not good.  ACPI is not necessarily limited to CONFIG_IA64_SV, yet&n;&t; * ACPI does not necessarily imply IOSAPIC either.  Perhaps there should be&n;&t; * a means for platform_setup() to register ACPI handlers?&n;&t; */
macro_line|#ifdef CONFIG_IA64_DIG
id|acpi_entry_iosapic_t
op_star
id|iosapic
op_assign
(paren
id|acpi_entry_iosapic_t
op_star
)paren
id|p
suffix:semicolon
r_int
r_int
id|ver
comma
id|v
suffix:semicolon
r_int
id|l
comma
id|pins
suffix:semicolon
id|ver
op_assign
id|iosapic_version
c_func
(paren
id|iosapic-&gt;address
)paren
suffix:semicolon
id|pins
op_assign
(paren
id|ver
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;IOSAPIC Version %x.%x: address 0x%lx IRQs 0x%x - 0x%x&bslash;n&quot;
comma
(paren
id|ver
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
comma
(paren
id|ver
op_amp
l_int|0x0f
)paren
comma
id|iosapic-&gt;address
comma
id|iosapic-&gt;irq_base
comma
id|iosapic-&gt;irq_base
op_plus
id|pins
)paren
suffix:semicolon
r_for
c_loop
(paren
id|l
op_assign
l_int|0
suffix:semicolon
id|l
OL
id|pins
suffix:semicolon
id|l
op_increment
)paren
(brace
id|v
op_assign
id|iosapic-&gt;irq_base
op_plus
id|l
suffix:semicolon
r_if
c_cond
(paren
id|v
OL
l_int|16
)paren
id|v
op_assign
id|isa_irq_to_vector
c_func
(paren
id|v
)paren
suffix:semicolon
r_if
c_cond
(paren
id|v
OG
id|IA64_MAX_VECTORED_IRQ
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;    !!! bad IOSAPIC interrupt vector: %u&bslash;n&quot;
comma
id|v
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
multiline_comment|/* XXX Check for IOSAPIC collisions */
id|iosapic_addr
c_func
(paren
id|v
)paren
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|iosapic-&gt;address
comma
l_int|0
)paren
suffix:semicolon
id|iosapic_baseirq
c_func
(paren
id|v
)paren
op_assign
id|iosapic-&gt;irq_base
suffix:semicolon
)brace
id|iosapic_init
c_func
(paren
id|iosapic-&gt;address
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Configure legacy IRQ information in iosapic_vector&n; */
r_static
r_void
id|__init
DECL|function|acpi_legacy_irq
id|acpi_legacy_irq
c_func
(paren
r_char
op_star
id|p
)paren
(brace
multiline_comment|/*&n;&t; * This is not good.  ACPI is not necessarily limited to CONFIG_IA64_DIG, yet&n;&t; * ACPI does not necessarily imply IOSAPIC either.  Perhaps there should be&n;&t; * a means for platform_setup() to register ACPI handlers?&n;&t; */
macro_line|#ifdef CONFIG_IA64_IRQ_ACPI
id|acpi_entry_int_override_t
op_star
id|legacy
op_assign
(paren
id|acpi_entry_int_override_t
op_star
)paren
id|p
suffix:semicolon
r_int
r_char
id|vector
suffix:semicolon
r_int
id|i
suffix:semicolon
id|vector
op_assign
id|isa_irq_to_vector
c_func
(paren
id|legacy-&gt;isa_irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clobber any old pin mapping.  It may be that it gets replaced later on&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|IA64_MAX_VECTORED_IRQ
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|vector
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|iosapic_pin
c_func
(paren
id|i
)paren
op_eq
id|iosapic_pin
c_func
(paren
id|vector
)paren
)paren
id|iosapic_pin
c_func
(paren
id|i
)paren
op_assign
l_int|0xff
suffix:semicolon
)brace
id|iosapic_pin
c_func
(paren
id|vector
)paren
op_assign
id|legacy-&gt;pin
suffix:semicolon
id|iosapic_bus
c_func
(paren
id|vector
)paren
op_assign
id|BUS_ISA
suffix:semicolon
multiline_comment|/* This table only overrides the ISA devices */
id|iosapic_busdata
c_func
(paren
id|vector
)paren
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &n;&t; * External timer tick is special... &n;&t; */
r_if
c_cond
(paren
id|vector
op_ne
id|TIMER_IRQ
)paren
id|iosapic_dmode
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_LOWEST_PRIORITY
suffix:semicolon
r_else
id|iosapic_dmode
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_FIXED
suffix:semicolon
multiline_comment|/* See MPS 1.4 section 4.3.4 */
r_switch
c_cond
(paren
id|legacy-&gt;flags
)paren
(brace
r_case
l_int|0x5
suffix:colon
id|iosapic_polarity
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_POL_HIGH
suffix:semicolon
id|iosapic_trigger
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_EDGE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x8
suffix:colon
id|iosapic_polarity
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_POL_LOW
suffix:semicolon
id|iosapic_trigger
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_EDGE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xd
suffix:colon
id|iosapic_polarity
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_POL_HIGH
suffix:semicolon
id|iosapic_trigger
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xf
suffix:colon
id|iosapic_polarity
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_POL_LOW
suffix:semicolon
id|iosapic_trigger
c_func
(paren
id|vector
)paren
op_assign
id|IO_SAPIC_LEVEL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;    ACPI Legacy IRQ 0x%02x: Unknown flags 0x%x&bslash;n&quot;
comma
id|legacy-&gt;isa_irq
comma
id|legacy-&gt;flags
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#if 1/*def ACPI_DEBUG*/
id|printk
c_func
(paren
l_string|&quot;Legacy ISA IRQ %x -&gt; IA64 Vector %x IOSAPIC Pin %x Active %s %s Trigger&bslash;n&quot;
comma
id|legacy-&gt;isa_irq
comma
id|vector
comma
id|iosapic_pin
c_func
(paren
id|vector
)paren
comma
(paren
(paren
id|iosapic_polarity
c_func
(paren
id|vector
)paren
op_eq
id|IO_SAPIC_POL_LOW
)paren
ques
c_cond
l_string|&quot;Low&quot;
suffix:colon
l_string|&quot;High&quot;
)paren
comma
(paren
(paren
id|iosapic_trigger
c_func
(paren
id|vector
)paren
op_eq
id|IO_SAPIC_LEVEL
)paren
ques
c_cond
l_string|&quot;Level&quot;
suffix:colon
l_string|&quot;Edge&quot;
)paren
)paren
suffix:semicolon
macro_line|#endif /* ACPI_DEBUG */
macro_line|#endif /* CONFIG_IA64_IRQ_ACPI */
)brace
multiline_comment|/*&n; * Info on platform interrupt sources: NMI. PMI, INIT, etc.&n; */
r_static
r_void
id|__init
DECL|function|acpi_platform
id|acpi_platform
c_func
(paren
r_char
op_star
id|p
)paren
(brace
id|acpi_entry_platform_src_t
op_star
id|plat
op_assign
(paren
id|acpi_entry_platform_src_t
op_star
)paren
id|p
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PLATFORM: IOSAPIC %x -&gt; Vector %lx on CPU %.04u:%.04u&bslash;n&quot;
comma
id|plat-&gt;iosapic_vector
comma
id|plat-&gt;global_vector
comma
id|plat-&gt;eid
comma
id|plat-&gt;id
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Parse the ACPI Multiple SAPIC Table&n; */
r_static
r_void
id|__init
DECL|function|acpi_parse_msapic
id|acpi_parse_msapic
c_func
(paren
id|acpi_sapic_t
op_star
id|msapic
)paren
(brace
r_char
op_star
id|p
comma
op_star
id|end
suffix:semicolon
multiline_comment|/* Base address of IPI Message Block */
id|ipi_base_addr
op_assign
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|msapic-&gt;interrupt_block
comma
l_int|0
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|memset
c_func
(paren
op_amp
id|smp
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|smp
)paren
)paren
suffix:semicolon
macro_line|#endif
id|p
op_assign
(paren
r_char
op_star
)paren
(paren
id|msapic
op_plus
l_int|1
)paren
suffix:semicolon
id|end
op_assign
id|p
op_plus
(paren
id|msapic-&gt;header.length
op_minus
r_sizeof
(paren
id|acpi_sapic_t
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|p
OL
id|end
)paren
(brace
r_switch
c_cond
(paren
op_star
id|p
)paren
(brace
r_case
id|ACPI_ENTRY_LOCAL_SAPIC
suffix:colon
id|acpi_lsapic
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ENTRY_IO_SAPIC
suffix:colon
id|acpi_iosapic
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ENTRY_INT_SRC_OVERRIDE
suffix:colon
id|acpi_legacy_irq
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_ENTRY_PLATFORM_INT_SOURCE
suffix:colon
id|acpi_platform
c_func
(paren
id|p
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Move to next table entry. */
DECL|macro|BAD_ACPI_TABLE
mdefine_line|#define BAD_ACPI_TABLE
macro_line|#ifdef BAD_ACPI_TABLE
multiline_comment|/*&n;&t;&t; * Some prototype Lion&squot;s have a bad ACPI table&n;&t;&t; * requiring this fix.  Without this fix, those&n;&t;&t; * machines crash during bootup.&n;&t;&t; */
r_if
c_cond
(paren
id|p
(braket
l_int|1
)braket
op_eq
l_int|0
)paren
id|p
op_assign
id|end
suffix:semicolon
r_else
macro_line|#endif
id|p
op_add_assign
id|p
(braket
l_int|1
)braket
suffix:semicolon
)brace
multiline_comment|/* Make bootup pretty */
id|printk
c_func
(paren
l_string|&quot;      %d CPUs available, %d CPUs total&bslash;n&quot;
comma
id|available_cpus
comma
id|total_cpus
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_parse
id|acpi_parse
c_func
(paren
id|acpi_rsdp_t
op_star
id|rsdp
)paren
(brace
id|acpi_rsdt_t
op_star
id|rsdt
suffix:semicolon
id|acpi_desc_table_hdr_t
op_star
id|hdrp
suffix:semicolon
r_int
id|tables
comma
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rsdp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Uh-oh, no ACPI Root System Description Pointer table!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|rsdp-&gt;signature
comma
id|ACPI_RSDP_SIG
comma
id|ACPI_RSDP_SIG_LEN
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Uh-oh, ACPI RSDP signature incorrect!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|rsdp-&gt;rsdt
op_assign
id|__va
c_func
(paren
id|rsdp-&gt;rsdt
)paren
suffix:semicolon
id|rsdt
op_assign
id|rsdp-&gt;rsdt
suffix:semicolon
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|rsdt-&gt;header.signature
comma
id|ACPI_RSDT_SIG
comma
id|ACPI_RSDT_SIG_LEN
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Uh-oh, ACPI RDST signature incorrect!&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ACPI: %.6s %.8s %d.%d&bslash;n&quot;
comma
id|rsdt-&gt;header.oem_id
comma
id|rsdt-&gt;header.oem_table_id
comma
id|rsdt-&gt;header.oem_revision
op_rshift
l_int|16
comma
id|rsdt-&gt;header.oem_revision
op_amp
l_int|0xffff
)paren
suffix:semicolon
id|tables
op_assign
(paren
id|rsdt-&gt;header.length
op_minus
r_sizeof
(paren
id|acpi_desc_table_hdr_t
)paren
)paren
op_div
l_int|8
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
id|tables
suffix:semicolon
id|i
op_increment
)paren
(brace
id|hdrp
op_assign
(paren
id|acpi_desc_table_hdr_t
op_star
)paren
id|__va
c_func
(paren
id|rsdt-&gt;entry_ptrs
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* Only interested int the MSAPIC table for now ... */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|hdrp-&gt;signature
comma
id|ACPI_SAPIC_SIG
comma
id|ACPI_SAPIC_SIG_LEN
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|acpi_parse_msapic
c_func
(paren
(paren
id|acpi_sapic_t
op_star
)paren
id|hdrp
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|available_cpus
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ACPI: Found 0 CPUS; assuming 1&bslash;n&quot;
)paren
suffix:semicolon
id|available_cpus
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* We&squot;ve got at least one of these, no? */
)brace
id|smp.cpu_count
op_assign
id|available_cpus
suffix:semicolon
macro_line|#endif
r_return
l_int|1
suffix:semicolon
)brace
r_const
r_char
op_star
DECL|function|acpi_get_sysname
id|acpi_get_sysname
(paren
r_void
)paren
(brace
multiline_comment|/* the following should go away once we have an ACPI parser: */
macro_line|#ifdef CONFIG_IA64_GENERIC
r_return
l_string|&quot;hpsim&quot;
suffix:semicolon
macro_line|#else
macro_line|# if defined (CONFIG_IA64_HP_SIM)
r_return
l_string|&quot;hpsim&quot;
suffix:semicolon
macro_line|# elif defined (CONFIG_IA64_SGI_SN1_SIM)
r_return
l_string|&quot;sn1&quot;
suffix:semicolon
macro_line|# elif defined (CONFIG_IA64_DIG)
r_return
l_string|&quot;dig&quot;
suffix:semicolon
macro_line|# else
macro_line|#&t;error Unknown platform.  Fix acpi.c.
macro_line|# endif
macro_line|#endif
)brace
eof
