multiline_comment|/* $Id: vaddrs.h,v 1.25 2000/06/05 06:08:46 anton Exp $ */
macro_line|#ifndef _SPARC_VADDRS_H
DECL|macro|_SPARC_VADDRS_H
mdefine_line|#define _SPARC_VADDRS_H
macro_line|#include &lt;asm/head.h&gt;
multiline_comment|/*&n; * asm-sparc/vaddrs.h:  Here we define the virtual addresses at&n; *                      which important things will be mapped.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 2000 Anton Blanchard (anton@linuxcare.com)&n; */
DECL|macro|SUN4M_IOBASE_VADDR
mdefine_line|#define SUN4M_IOBASE_VADDR&t;0xfd000000 /* Base for mapping pages */
DECL|macro|IOBASE_VADDR
mdefine_line|#define IOBASE_VADDR&t;&t;0xfe000000
DECL|macro|IOBASE_END
mdefine_line|#define IOBASE_END&t;&t;0xfe300000
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;0xfe300000
multiline_comment|/* XXX Alter this when I get around to fixing sun4c - Anton */
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;0xffc00000
multiline_comment|/*&n; * On the sun4/4c we need a place&n; * to reliably map locked down kernel data.  This includes the&n; * task_struct and kernel stack pages of each process plus the&n; * scsi buffers during dvma IO transfers, also the floppy buffers&n; * during pseudo dma which runs with traps off (no faults allowed).&n; * Some quick calculations yield:&n; *       NR_TASKS &lt;512&gt; * (3 * PAGE_SIZE) == 0x600000&n; * Subtract this from 0xc00000 and you get 0x927C0 of vm left&n; * over to map SCSI dvma + floppy pseudo-dma buffers.  So be&n; * careful if you change NR_TASKS or else there won&squot;t be enough&n; * room for it all.&n; */
DECL|macro|SUN4C_LOCK_VADDR
mdefine_line|#define SUN4C_LOCK_VADDR&t;0xff000000
DECL|macro|SUN4C_LOCK_END
mdefine_line|#define SUN4C_LOCK_END&t;&t;0xffc00000
DECL|macro|KADB_DEBUGGER_BEGVM
mdefine_line|#define KADB_DEBUGGER_BEGVM&t;0xffc00000 /* Where kern debugger is in virt-mem */
DECL|macro|KADB_DEBUGGER_ENDVM
mdefine_line|#define KADB_DEBUGGER_ENDVM&t;0xffd00000
DECL|macro|DEBUG_FIRSTVADDR
mdefine_line|#define DEBUG_FIRSTVADDR&t;KADB_DEBUGGER_BEGVM
DECL|macro|DEBUG_LASTVADDR
mdefine_line|#define DEBUG_LASTVADDR&t;&t;KADB_DEBUGGER_ENDVM
DECL|macro|LINUX_OPPROM_BEGVM
mdefine_line|#define LINUX_OPPROM_BEGVM&t;0xffd00000
DECL|macro|LINUX_OPPROM_ENDVM
mdefine_line|#define LINUX_OPPROM_ENDVM&t;0xfff00000
DECL|macro|DVMA_VADDR
mdefine_line|#define DVMA_VADDR&t;&t;0xfff00000 /* Base area of the DVMA on suns */
DECL|macro|DVMA_END
mdefine_line|#define DVMA_END&t;&t;0xfffc0000
macro_line|#endif /* !(_SPARC_VADDRS_H) */
eof
