multiline_comment|/*&n; * Machine vector for IA-64.&n; * &n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; * Copyright (C) Srinivasa Thirumalachar &lt;sprasad@engr.sgi.com&gt;&n; * Copyright (C) Vijay Chander &lt;vijay@engr.sgi.com&gt;&n; * Copyright (C) 1999-2000 Hewlett-Packard Co.&n; * Copyright (C) 1999-2000 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#ifndef _ASM_IA64_MACHVEC_H
DECL|macro|_ASM_IA64_MACHVEC_H
mdefine_line|#define _ASM_IA64_MACHVEC_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
multiline_comment|/* forward declarations: */
r_struct
id|hw_interrupt_type
suffix:semicolon
r_struct
id|irq_desc
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|pt_regs
suffix:semicolon
r_struct
id|task_struct
suffix:semicolon
r_struct
id|timeval
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_struct
id|acpi_entry_iosapic
suffix:semicolon
DECL|typedef|ia64_mv_setup_t
r_typedef
r_void
id|ia64_mv_setup_t
(paren
r_char
op_star
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_irq_init_t
r_typedef
r_void
id|ia64_mv_irq_init_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_pci_fixup_t
r_typedef
r_void
id|ia64_mv_pci_fixup_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_map_nr_t
r_typedef
r_int
r_int
id|ia64_mv_map_nr_t
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|typedef|ia64_mv_mca_init_t
r_typedef
r_void
id|ia64_mv_mca_init_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_mca_handler_t
r_typedef
r_void
id|ia64_mv_mca_handler_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_cmci_handler_t
r_typedef
r_void
id|ia64_mv_cmci_handler_t
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|typedef|ia64_mv_log_print_t
r_typedef
r_void
id|ia64_mv_log_print_t
(paren
r_void
)paren
suffix:semicolon
DECL|typedef|ia64_mv_register_iosapic_t
r_typedef
r_void
id|ia64_mv_register_iosapic_t
(paren
r_struct
id|acpi_entry_iosapic
op_star
)paren
suffix:semicolon
r_extern
r_void
id|machvec_noop
(paren
r_void
)paren
suffix:semicolon
macro_line|# if defined (CONFIG_IA64_HP_SIM)
macro_line|#  include &lt;asm/machvec_hpsim.h&gt;
macro_line|# elif defined (CONFIG_IA64_DIG)
macro_line|#  include &lt;asm/machvec_dig.h&gt;
macro_line|# elif defined (CONFIG_IA64_SGI_SN1_SIM)
macro_line|#  include &lt;asm/machvec_sn1.h&gt;
macro_line|# elif defined (CONFIG_IA64_GENERIC)
macro_line|# ifdef MACHVEC_PLATFORM_HEADER
macro_line|#  include MACHVEC_PLATFORM_HEADER
macro_line|# else
DECL|macro|platform_name
macro_line|#  define platform_name&t;&t;ia64_mv.name
DECL|macro|platform_setup
macro_line|#  define platform_setup&t;ia64_mv.setup
DECL|macro|platform_irq_init
macro_line|#  define platform_irq_init&t;ia64_mv.irq_init
DECL|macro|platform_map_nr
macro_line|#  define platform_map_nr&t;ia64_mv.map_nr
DECL|macro|platform_mca_init
macro_line|#  define platform_mca_init&t;ia64_mv.mca_init
DECL|macro|platform_mca_handler
macro_line|#  define platform_mca_handler&t;ia64_mv.mca_handler
DECL|macro|platform_cmci_handler
macro_line|#  define platform_cmci_handler&t;ia64_mv.cmci_handler
DECL|macro|platform_log_print
macro_line|#  define platform_log_print&t;ia64_mv.log_print
DECL|macro|platform_pci_fixup
macro_line|#  define platform_pci_fixup&t;ia64_mv.pci_fixup
DECL|macro|platform_register_iosapic
macro_line|#  define platform_register_iosapic&t;ia64_mv.register_iosapic
macro_line|# endif
DECL|struct|ia64_machine_vector
r_struct
id|ia64_machine_vector
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|setup
id|ia64_mv_setup_t
op_star
id|setup
suffix:semicolon
DECL|member|irq_init
id|ia64_mv_irq_init_t
op_star
id|irq_init
suffix:semicolon
DECL|member|pci_fixup
id|ia64_mv_pci_fixup_t
op_star
id|pci_fixup
suffix:semicolon
DECL|member|map_nr
id|ia64_mv_map_nr_t
op_star
id|map_nr
suffix:semicolon
DECL|member|mca_init
id|ia64_mv_mca_init_t
op_star
id|mca_init
suffix:semicolon
DECL|member|mca_handler
id|ia64_mv_mca_handler_t
op_star
id|mca_handler
suffix:semicolon
DECL|member|cmci_handler
id|ia64_mv_cmci_handler_t
op_star
id|cmci_handler
suffix:semicolon
DECL|member|log_print
id|ia64_mv_log_print_t
op_star
id|log_print
suffix:semicolon
DECL|member|register_iosapic
id|ia64_mv_register_iosapic_t
op_star
id|register_iosapic
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MACHVEC_INIT
mdefine_line|#define MACHVEC_INIT(name)&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&bslash;&n;&t;#name,&t;&t;&t;&t;&t;&bslash;&n;&t;platform_setup,&t;&t;&t;&t;&bslash;&n;&t;platform_irq_init,&t;&t;&t;&bslash;&n;&t;platform_pci_fixup,&t;&t;&t;&bslash;&n;&t;platform_map_nr,&t;&t;&t;&bslash;&n;&t;platform_mca_init,&t;&t;&t;&bslash;&n;&t;platform_mca_handler,&t;&t;&t;&bslash;&n;&t;platform_cmci_handler,&t;&t;&t;&bslash;&n;&t;platform_log_print,&t;&t;&t;&bslash;&n;&t;platform_register_iosapic&t;&t;&t;&bslash;&n;}
r_extern
r_struct
id|ia64_machine_vector
id|ia64_mv
suffix:semicolon
r_extern
r_void
id|machvec_init
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|# else
macro_line|#  error Unknown configuration.  Update asm-ia64/machvec.h.
macro_line|# endif /* CONFIG_IA64_GENERIC */
multiline_comment|/*&n; * Define default versions so we can extend machvec for new platforms without having&n; * to update the machvec files for all existing platforms.&n; */
macro_line|#ifndef platform_setup
DECL|macro|platform_setup
macro_line|# define platform_setup&t;&t;((ia64_mv_setup_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_irq_init
DECL|macro|platform_irq_init
macro_line|# define platform_irq_init&t;((ia64_mv_irq_init_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_mca_init
DECL|macro|platform_mca_init
macro_line|# define platform_mca_init&t;((ia64_mv_mca_init_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_mca_handler
DECL|macro|platform_mca_handler
macro_line|# define platform_mca_handler&t;((ia64_mv_mca_handler_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_cmci_handler
DECL|macro|platform_cmci_handler
macro_line|# define platform_cmci_handler&t;((ia64_mv_cmci_handler_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_log_print
DECL|macro|platform_log_print
macro_line|# define platform_log_print&t;((ia64_mv_log_print_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_pci_fixup
DECL|macro|platform_pci_fixup
macro_line|# define platform_pci_fixup&t;((ia64_mv_pci_fixup_t *) machvec_noop)
macro_line|#endif
macro_line|#ifndef platform_register_iosapic
DECL|macro|platform_register_iosapic
macro_line|# define platform_register_iosapic&t;((ia64_mv_register_iosapic_t *) machvec_noop)
macro_line|#endif
macro_line|#endif /* _ASM_IA64_MACHVEC_H */
eof
