macro_line|#ifndef _PPC_KERNEL_OPEN_PIC_H
DECL|macro|_PPC_KERNEL_OPEN_PIC_H
mdefine_line|#define _PPC_KERNEL_OPEN_PIC_H
r_extern
r_struct
id|hw_interrupt_type
id|open_pic
suffix:semicolon
r_void
id|openpic_ipi_action
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
r_void
id|openpic_enable_IPI
c_func
(paren
id|u_int
id|ipi
)paren
suffix:semicolon
macro_line|#endif /* _PPC_KERNEL_OPEN_PIC_H */
eof
