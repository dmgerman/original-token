macro_line|#ifndef _SPARC_VADDRS_H
DECL|macro|_SPARC_VADDRS_H
mdefine_line|#define _SPARC_VADDRS_H
macro_line|#include &lt;asm/head.h&gt;
multiline_comment|/* asm-sparc/vaddrs.h:  Here will be define the virtual addresses at&n; *                      which important I/O addresses will be mapped.&n; *                      For instance the timer register virtual address&n; *                      is defined here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* I can see only one reason why we should have statically defined&n; * mappings for devices and is the speedup improvements of not loading&n; * a pointer and then the value in the assembly code&n; */
DECL|macro|AUXIO_VADDR
mdefine_line|#define  AUXIO_VADDR  (KERNBASE+0x6000)    /* Auxiliary IO register */
DECL|macro|TIMER_VADDR
mdefine_line|#define  TIMER_VADDR  (AUXIO_VADDR+0x1000) /* One page after AUXIO, length is&n;&t;&t;&t;&t;&t;    * 5 pages which is needed on sun4m.&n;&t;&t;&t;&t;&t;    */
DECL|macro|INTREG_VADDR
mdefine_line|#define  INTREG_VADDR (TIMER_VADDR+0x5000)
DECL|macro|IOBASE_VADDR
mdefine_line|#define  IOBASE_VADDR   0xfe000000  /* Base for mapping pages */
DECL|macro|IOBASE_LEN
mdefine_line|#define  IOBASE_LEN     0x00400000  /* Length of the IO area */
DECL|macro|IOBASE_SUN4C_SEGMAP
mdefine_line|#define  IOBASE_SUN4C_SEGMAP 100
DECL|macro|DVMA_VADDR
mdefine_line|#define  DVMA_VADDR     0xfff00000  /* Base area of the DVMA on the 4c */
DECL|macro|DVMA_LEN
mdefine_line|#define  DVMA_LEN       0x000c0000  /* Size of the DVMA address space */
multiline_comment|/* On sun4m machines we need per-cpu virtual areas */
DECL|macro|PERCPU_VADDR
mdefine_line|#define  PERCPU_VADDR   0xff000000  /* Base for per-cpu virtual mappings */
DECL|macro|PERCPU_ENTSIZE
mdefine_line|#define  PERCPU_ENTSIZE 0x00100000
DECL|macro|PERCPU_LEN
mdefine_line|#define  PERCPU_LEN     ((PERCPU_ENTSIZE*NCPUS))
multiline_comment|/* per-cpu offsets */
DECL|macro|PERCPU_TBR_OFFSET
mdefine_line|#define  PERCPU_TBR_OFFSET      0x00000      /* %tbr, mainly used for identification. */
DECL|macro|PERCPU_KSTACK_OFFSET
mdefine_line|#define  PERCPU_KSTACK_OFFSET   0x01000      /* Beginning of kernel stack for this cpu */
DECL|macro|PERCPU_MBOX_OFFSET
mdefine_line|#define  PERCPU_MBOX_OFFSET     0x02000      /* Prom SMP Mailbox */
DECL|macro|PERCPU_CPUID_OFFSET
mdefine_line|#define  PERCPU_CPUID_OFFSET    0x03000      /* Per-cpu ID number. */
DECL|macro|PERCPU_ISALIVE_OFFSET
mdefine_line|#define  PERCPU_ISALIVE_OFFSET  0x03004      /* Has CPU been initted yet? */
DECL|macro|PERCPU_ISIDLING_OFFSET
mdefine_line|#define  PERCPU_ISIDLING_OFFSET 0x03008      /* Is CPU in idle loop spinning? */
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
