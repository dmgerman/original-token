multiline_comment|/* s4clow.h: Defines for in-window low level tlb refill code.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caipfs.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_S4CLOW_H
DECL|macro|_SPARC_S4CLOW_H
mdefine_line|#define _SPARC_S4CLOW_H
DECL|macro|PAGE_SIZE
mdefine_line|#define         PAGE_SIZE       0x00001000
DECL|macro|REAL_PGDIR_MASK
mdefine_line|#define&t;&t;REAL_PGDIR_MASK&t;0xfffc0000
DECL|macro|VMALLOC_START
mdefine_line|#define&t;&t;VMALLOC_START&t;0xfe100000
DECL|macro|RING_RINGHD
mdefine_line|#define&t;&t;RING_RINGHD&t;0x00
DECL|macro|RING_NENTRIES
mdefine_line|#define&t;&t;RING_NENTRIES   0x10
DECL|macro|MMU_ENTRY_NEXT
mdefine_line|#define&t;&t;MMU_ENTRY_NEXT&t;0x00
DECL|macro|MMU_ENTRY_PREV
mdefine_line|#define&t;&t;MMU_ENTRY_PREV&t;0x04
DECL|macro|MMU_ENTRY_VADDR
mdefine_line|#define&t;&t;MMU_ENTRY_VADDR&t;0x08
DECL|macro|MMU_ENTRY_PSEG
mdefine_line|#define&t;&t;MMU_ENTRY_PSEG&t;0x0c
DECL|macro|MMU_ENTRY_LCK
mdefine_line|#define&t;&t;MMU_ENTRY_LCK&t;0x0d
DECL|macro|VACINFO_SIZE
mdefine_line|#define&t;&t;VACINFO_SIZE&t;0x00
DECL|macro|VACINFO_HWFLSH
mdefine_line|#define&t;&t;VACINFO_HWFLSH&t;0x08
DECL|macro|VACINFO_LSIZE
mdefine_line|#define&t;&t;VACINFO_LSIZE&t;0x0c
multiline_comment|/* Each of the routines could get called by any of the&n; * other low level sun4c tlb routines.  Well... at least&n; * we code it that way.  Because we are in window we need&n; * a way to make a routine completely self contained and&n; * only need to worry about saving it&squot;s own set of registers&n; * which it in fact uses.  With traps off this is difficult&n; * ... however...&n; *&n; * The Sparc can address anywhere in the two ranges&n; * 0 --&gt; PAGE_SIZE and -PAGE_SIZE --&gt; -1 without any&n; * address calculation registers.  So we pull a trick,&n; * we map a special page for these low level tlb routines&n; * since they must be as quick as possible.  Since the low&n; * page is the NULL unmapped page and in user space we use&n; * the high one for simplicity.  Kids, do not try this at&n; * home.&n; */
DECL|macro|REGSAVE_BASE
mdefine_line|#define          REGSAVE_BASE   (-PAGE_SIZE)
DECL|macro|FLUSHREGS
mdefine_line|#define          FLUSHREGS      0
DECL|macro|KFLTREGS
mdefine_line|#define          KFLTREGS       256
DECL|macro|UFLTREGS
mdefine_line|#define          UFLTREGS       512
macro_line|#endif /* !(_SPARC_S4CLOW_H) */
eof
