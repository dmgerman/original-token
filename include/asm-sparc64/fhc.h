multiline_comment|/* $Id: fhc.h,v 1.1 1997/08/08 04:26:40 davem Exp $&n; * fhc.h: Structures for central/fhc pseudo driver on Sunfire/Starfire/Wildfire.&n; *&n; * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC64_FHC_H
DECL|macro|_SPARC64_FHC_H
mdefine_line|#define _SPARC64_FHC_H
macro_line|#include &lt;asm/firehose.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
r_struct
id|linux_fhc
suffix:semicolon
DECL|struct|linux_central
r_struct
id|linux_central
(brace
DECL|member|child
r_struct
id|linux_fhc
op_star
id|child
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|central_ranges
r_struct
id|linux_prom_ranges
id|central_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_central_ranges
r_int
id|num_central_ranges
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|linux_fhc
r_struct
id|linux_fhc
(brace
DECL|member|next
r_struct
id|linux_fhc
op_star
id|next
suffix:semicolon
DECL|member|parent
r_struct
id|linux_central
op_star
id|parent
suffix:semicolon
multiline_comment|/* NULL if not central FHC */
DECL|member|fhc_regs
r_struct
id|fhc_regs
id|fhc_regs
suffix:semicolon
DECL|member|prom_node
r_int
id|prom_node
suffix:semicolon
DECL|member|prom_name
r_char
id|prom_name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fhc_ranges
r_struct
id|linux_prom_ranges
id|fhc_ranges
(braket
id|PROMREG_MAX
)braket
suffix:semicolon
DECL|member|num_fhc_ranges
r_int
id|num_fhc_ranges
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_struct
id|linux_central
op_star
id|central_bus
suffix:semicolon
r_extern
r_void
id|prom_apply_central_ranges
c_func
(paren
r_struct
id|linux_central
op_star
id|central
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
suffix:semicolon
r_extern
r_void
id|prom_apply_fhc_ranges
c_func
(paren
r_struct
id|linux_fhc
op_star
id|fhc
comma
r_struct
id|linux_prom_registers
op_star
id|regs
comma
r_int
id|nregs
)paren
suffix:semicolon
macro_line|#endif /* !(_SPARC64_FHC_H) */
eof