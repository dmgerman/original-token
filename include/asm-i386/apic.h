macro_line|#ifndef __ASM_APIC_H
DECL|macro|__ASM_APIC_H
mdefine_line|#define __ASM_APIC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/apicdef.h&gt;
DECL|macro|APIC_DEBUG
mdefine_line|#define APIC_DEBUG 1
macro_line|#ifdef CONFIG_X86_LOCAL_APIC
macro_line|#if APIC_DEBUG
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...) printk(##x)
macro_line|#else
DECL|macro|Dprintk
mdefine_line|#define Dprintk(x...)
macro_line|#endif
multiline_comment|/*&n; * Basic functions accessing APICs.&n; */
DECL|function|apic_write
r_extern
id|__inline
r_void
id|apic_write
c_func
(paren
r_int
r_int
id|reg
comma
r_int
r_int
id|v
)paren
(brace
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|reg
)paren
)paren
op_assign
id|v
suffix:semicolon
)brace
DECL|function|apic_read
r_extern
id|__inline
r_int
r_int
id|apic_read
c_func
(paren
r_int
r_int
id|reg
)paren
(brace
r_return
op_star
(paren
(paren
r_volatile
r_int
r_int
op_star
)paren
(paren
id|APIC_BASE
op_plus
id|reg
)paren
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|apic_timer_irqs
(braket
id|NR_CPUS
)braket
suffix:semicolon
macro_line|#ifdef CONFIG_X86_GOOD_APIC
DECL|macro|FORCE_READ_AROUND_WRITE
macro_line|# define FORCE_READ_AROUND_WRITE 0
DECL|macro|apic_readaround
macro_line|# define apic_readaround(x)
macro_line|#else
DECL|macro|FORCE_READ_AROUND_WRITE
macro_line|# define FORCE_READ_AROUND_WRITE 1
DECL|macro|apic_readaround
macro_line|# define apic_readaround(x) apic_read(x)
macro_line|#endif
DECL|macro|apic_write_around
mdefine_line|#define apic_write_around(x,y) &bslash;&n;&t;&t;do { apic_readaround(x); apic_write(x,y); } while (0)
DECL|function|ack_APIC_irq
r_extern
r_inline
r_void
id|ack_APIC_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Clear the IPI */
id|apic_readaround
c_func
(paren
id|APIC_EOI
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * on P6+ cores (CONFIG_X86_GOOD_APIC) ack_APIC_irq() actually&n;&t; * gets compiled as a single instruction ... yummie.&n;&t; */
id|apic_write
c_func
(paren
id|APIC_EOI
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Docs say use 0 for future compatibility */
)brace
r_extern
r_int
id|get_maxlvt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|disable_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|cache_APIC_registers
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|setup_local_APIC
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|init_apic_mappings
c_func
(paren
r_void
)paren
suffix:semicolon
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
id|setup_APIC_clocks
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
