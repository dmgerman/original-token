multiline_comment|/* $Id: vaddrs.h,v 1.8 1997/06/27 14:55:13 jj Exp $ */
macro_line|#ifndef _SPARC64_VADDRS_H
DECL|macro|_SPARC64_VADDRS_H
mdefine_line|#define _SPARC64_VADDRS_H
multiline_comment|/* asm-sparc64/vaddrs.h:  Here will be define the virtual addresses at&n; *                      which important I/O addresses will be mapped.&n; *                      For instance the timer register virtual address&n; *                      is defined here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* I can see only one reason why we should have statically defined&n; * mappings for devices and is the speedup improvements of not loading&n; * a pointer and then the value in the assembly code&n; */
DECL|macro|IOBASE_VADDR
mdefine_line|#define  IOBASE_VADDR   0x0000006000000000ULL  /* Base for mapping pages */
DECL|macro|IOBASE_LEN
mdefine_line|#define  IOBASE_LEN     0x0000001000000000ULL  /* Length of the IO area */
DECL|macro|IOBASE_END
mdefine_line|#define  IOBASE_END     0x0000007000000000ULL
DECL|macro|DVMA_VADDR
mdefine_line|#define  DVMA_VADDR     0x0000007000000000ULL  /* Base area of the DVMA on suns */
DECL|macro|DVMA_LEN
mdefine_line|#define  DVMA_LEN       0x0000001000000000ULL  /* Size of the DVMA address space */
DECL|macro|DVMA_END
mdefine_line|#define  DVMA_END       0x0000008000000000ULL
DECL|macro|MODULES_VADDR
mdefine_line|#define  MODULES_VADDR&t;0x0000000001000000ULL  /* Where to map modules */
DECL|macro|MODULES_LEN
mdefine_line|#define  MODULES_LEN&t;0x000000007f000000ULL
DECL|macro|MODULES_END
mdefine_line|#define  MODULES_END&t;0x0000000080000000ULL
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
