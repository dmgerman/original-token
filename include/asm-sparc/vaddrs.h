multiline_comment|/* $Id: vaddrs.h,v 1.21 1996/10/07 03:03:02 davem Exp $ */
macro_line|#ifndef _SPARC_VADDRS_H
DECL|macro|_SPARC_VADDRS_H
mdefine_line|#define _SPARC_VADDRS_H
macro_line|#include &lt;asm/head.h&gt;
multiline_comment|/* asm-sparc/vaddrs.h:  Here will be define the virtual addresses at&n; *                      which important I/O addresses will be mapped.&n; *                      For instance the timer register virtual address&n; *                      is defined here.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* I can see only one reason why we should have statically defined&n; * mappings for devices and is the speedup improvements of not loading&n; * a pointer and then the value in the assembly code&n; */
DECL|macro|IOBASE_VADDR
mdefine_line|#define  IOBASE_VADDR   0xfe000000  /* Base for mapping pages */
DECL|macro|IOBASE_LEN
mdefine_line|#define  IOBASE_LEN     0x00300000  /* Length of the IO area */
DECL|macro|IOBASE_END
mdefine_line|#define  IOBASE_END     0xfe300000
DECL|macro|DVMA_VADDR
mdefine_line|#define  DVMA_VADDR     0xfff00000  /* Base area of the DVMA on suns */
DECL|macro|DVMA_LEN
mdefine_line|#define  DVMA_LEN       0x00040000  /* Size of the DVMA address space */
DECL|macro|DVMA_END
mdefine_line|#define  DVMA_END       0xfff40000
multiline_comment|/* IOMMU Mapping area, must be on a 16MB boundary!  Note this&n; * doesn&squot;t count the DVMA areas, the prom lives between the&n; * iommu mapping area (for scsi transfer buffers) and the&n; * dvma upper range (for lance packet ring buffers).&n; */
DECL|macro|IOMMU_VADDR
mdefine_line|#define  IOMMU_VADDR    0xff000000
DECL|macro|IOMMU_LEN
mdefine_line|#define  IOMMU_LEN      0x00c00000
DECL|macro|IOMMU_END
mdefine_line|#define  IOMMU_END      0xffc00000 /* KADB debugger vm starts here */
multiline_comment|/* On the sun4/4c we don&squot;t need an IOMMU area, but we need a place&n; * to reliably map locked down kernel data.  This includes the&n; * task_struct and kernel stack pages of each process plus the&n; * scsi buffers during dvma IO transfers, also the floppy buffers&n; * during pseudo dma which runs with traps off (no faults allowed).&n; * Some quick calculations yield:&n; *       NR_TASKS &lt;512&gt; * (3 * PAGE_SIZE) == 0x600000&n; * Subtract this from 0xc00000 and you get 0x927C0 of vm left&n; * over to map SCSI dvma + floppy pseudo-dma buffers.  So be&n; * careful if you change NR_TASKS or else there won&squot;t be enough&n; * room for it all.&n; */
DECL|macro|SUN4C_LOCK_VADDR
mdefine_line|#define  SUN4C_LOCK_VADDR  0xff000000
DECL|macro|SUN4C_LOCK_LEN
mdefine_line|#define  SUN4C_LOCK_LEN    0x00c00000
DECL|macro|SUN4C_LOCK_END
mdefine_line|#define  SUN4C_LOCK_END    0xffc00000
multiline_comment|/* On sun4m machines we need per-cpu virtual areas */
DECL|macro|PERCPU_VADDR
mdefine_line|#define  PERCPU_VADDR   0xffc00000  /* Base for per-cpu virtual mappings */
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
mdefine_line|#define  PERCPU_MBOX_OFFSET     0x03000      /* Prom SMP Mailbox */
DECL|macro|PERCPU_CPUID_OFFSET
mdefine_line|#define  PERCPU_CPUID_OFFSET    0x04000      /* Per-cpu ID number. */
DECL|macro|PERCPU_ISALIVE_OFFSET
mdefine_line|#define  PERCPU_ISALIVE_OFFSET  0x04004      /* Has CPU been initted yet? */
DECL|macro|PERCPU_ISIDLING_OFFSET
mdefine_line|#define  PERCPU_ISIDLING_OFFSET 0x04008      /* Is CPU in idle loop spinning? */
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
