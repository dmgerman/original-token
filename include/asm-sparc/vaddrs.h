macro_line|#ifndef _SPARC_VADDRS_H
DECL|macro|_SPARC_VADDRS_H
mdefine_line|#define _SPARC_VADDRS_H
multiline_comment|/* asm-sparc/vaddrs.h:  Here will be define the virtual addresses at&n; *                      which important I/O addresses will be mapped.&n; *                      For instance the timer register virtual address&n; *                      is defined here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
DECL|macro|TIMER_VADDR
mdefine_line|#define  TIMER_VADDR    0x3000   /* Next page after where the interrupt enable&n;&t;&t;&t;&t;  * register gets mapped at boot.&n;&t;&t;&t;&t;  */
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
