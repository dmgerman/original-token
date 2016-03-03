multiline_comment|/* $Id: parport.h,v 1.2 2000/02/18 00:24:48 ralf Exp $&n; *&n; * parport.h: ia32-specific parport initialisation&n; *&n; * Copyright (C) 1999, 2000  Tim Waugh &lt;tim@cyberelk.demon.co.uk&gt;&n; *&n; * This file should only be included by drivers/parport/parport_pc.c.&n; */
macro_line|#ifndef _ASM_PARPORT_H
DECL|macro|_ASM_PARPORT_H
mdefine_line|#define _ASM_PARPORT_H 1
r_static
r_int
id|__devinit
id|parport_pc_find_isa_ports
(paren
r_int
id|autoirq
comma
r_int
id|autodma
)paren
suffix:semicolon
DECL|function|parport_pc_find_nonpci_ports
r_static
r_int
id|__devinit
id|parport_pc_find_nonpci_ports
(paren
r_int
id|autoirq
comma
r_int
id|autodma
)paren
(brace
r_return
id|parport_pc_find_isa_ports
(paren
id|autoirq
comma
id|autodma
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_ASM_PARPORT_H) */
eof
