macro_line|#ifndef _M68K_IRQ_H_
DECL|macro|_M68K_IRQ_H_
mdefine_line|#define _M68K_IRQ_H_
r_extern
r_void
id|disable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|enable_irq
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This should be the same as the max(NUM_X_SOURCES) for all the&n; * different m68k hosts compiled into the kernel.&n; * Currently the Atari has 72 and the Amiga 24, but if both are&n; * supported in the kernel it is better to make room for 72.&n; */
macro_line|#if defined(CONFIG_ATARI)
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 72
macro_line|#else
DECL|macro|NR_IRQS
mdefine_line|#define NR_IRQS 24
macro_line|#endif
multiline_comment|/*&n; * Interrupt source definitions&n; * General interrupt sources are the level 1-7.&n; * Adding an interrupt service routine for one of these sources&n; * results in the addition of that routine to a chain of routines.&n; * Each one is called in succession.  Each individual interrupt&n; * service routine should determine if the device associated with&n; * that routine requires service.&n; */
DECL|macro|IRQ1
mdefine_line|#define IRQ1&t;&t; (1)    /* level 1 interrupt */
DECL|macro|IRQ2
mdefine_line|#define IRQ2&t;&t; (2)    /* level 2 interrupt */
DECL|macro|IRQ3
mdefine_line|#define IRQ3&t;&t; (3)    /* level 3 interrupt */
DECL|macro|IRQ4
mdefine_line|#define IRQ4&t;&t; (4)    /* level 4 interrupt */
DECL|macro|IRQ5
mdefine_line|#define IRQ5&t;&t; (5)    /* level 5 interrupt */
DECL|macro|IRQ6
mdefine_line|#define IRQ6&t;&t; (6)    /* level 6 interrupt */
DECL|macro|IRQ7
mdefine_line|#define IRQ7&t;&t; (7)    /* level 7 interrupt (non-maskable) */
multiline_comment|/*&n; * &quot;Generic&quot; interrupt sources&n; */
DECL|macro|IRQ_SCHED_TIMER
mdefine_line|#define IRQ_SCHED_TIMER  (8)    /* interrupt source for scheduling timer */
multiline_comment|/*&n; * Machine specific interrupt sources.&n; *&n; * Adding an interrupt service routine for a source with this bit&n; * set indicates a special machine specific interrupt source.&n; * The machine specific files define these sources.&n; */
DECL|macro|IRQ_MACHSPEC
mdefine_line|#define IRQ_MACHSPEC&t; (0x10000000L)
macro_line|#ifndef ISRFUNC_T
r_struct
id|pt_regs
suffix:semicolon
DECL|typedef|isrfunc
r_typedef
r_void
(paren
op_star
id|isrfunc
)paren
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|macro|ISRFUNC_T
mdefine_line|#define ISRFUNC_T
macro_line|#endif /* ISRFUNC_T */
multiline_comment|/*&n; * This structure is used to chain together the ISRs for a particular&n; * interrupt source (if it supports chaining).&n; */
DECL|struct|isr_node
r_typedef
r_struct
id|isr_node
(brace
DECL|member|isr
id|isrfunc
id|isr
suffix:semicolon
DECL|member|pri
r_int
id|pri
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|next
r_struct
id|isr_node
op_star
id|next
suffix:semicolon
DECL|typedef|isr_node_t
)brace
id|isr_node_t
suffix:semicolon
multiline_comment|/* count of spurious interrupts */
r_extern
r_volatile
r_int
r_int
id|num_spurious
suffix:semicolon
multiline_comment|/*&n; * This function returns a new isr_node_t&n; */
r_extern
id|isr_node_t
op_star
id|new_isr_node
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * This function is used to add a specific interrupt service routine&n; * for the specified interrupt source.&n; *&n; * If the source is machine specific, it will be passed along to the&n; * machine specific routine.&n; *&n; * &quot;data&quot; is user specified data which will be passed to the isr routine.&n; *&n; * (isrfunc is defined in linux/config.h)&n; */
r_extern
r_int
id|add_isr
(paren
r_int
r_int
id|source
comma
id|isrfunc
id|isr
comma
r_int
id|pri
comma
r_void
op_star
id|data
comma
r_char
op_star
id|name
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine will remove an isr for the specified interrupt source.&n; */
r_extern
r_int
id|remove_isr
(paren
r_int
r_int
id|source
comma
id|isrfunc
id|isr
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine will insert an isr_node_t into a chain of nodes, using&n; * the priority stored in the node.&n; */
r_extern
r_void
id|insert_isr
(paren
id|isr_node_t
op_star
op_star
id|listp
comma
id|isr_node_t
op_star
id|node
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine will delete the isr node for isr from a chain of nodes&n; */
r_extern
r_void
id|delete_isr
(paren
id|isr_node_t
op_star
op_star
id|listp
comma
id|isrfunc
id|isr
)paren
suffix:semicolon
multiline_comment|/*&n; * This routine may be used to call the isr routines in the passed list.&n; */
r_extern
r_void
id|call_isr_list
(paren
r_int
id|irq
comma
id|isr_node_t
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
suffix:semicolon
macro_line|#endif /* _M68K_IRQ_H_ */
eof
