macro_line|#ifndef _SPARC_CONTREGS_H
DECL|macro|_SPARC_CONTREGS_H
mdefine_line|#define _SPARC_CONTREGS_H
multiline_comment|/* contregs.h:  Addresses of registers in the ASI_CONTROL alternate address&n;                space. These are for the mmu&squot;s context register, etc.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
DECL|macro|AC_CONTEXT
mdefine_line|#define AC_CONTEXT    0x30000000    /* current mmu-context, handy for invalidate()&squot;s ;-)   */
DECL|macro|AC_SENABLE
mdefine_line|#define AC_SENABLE    0x40000000    /* system dvma/cache enable, plus special reset poking */
DECL|macro|AC_CACHETAGS
mdefine_line|#define AC_CACHETAGS  0x80000000    /* direct access to the VAC cache, unused...          */
DECL|macro|AC_SYNC_ERR
mdefine_line|#define AC_SYNC_ERR   0x60000000    /* what type of synchronous memory error happened      */
DECL|macro|AC_SYNC_VA
mdefine_line|#define AC_SYNC_VA    0x60000004    /* what virtual address caused the error to occur      */
DECL|macro|AC_ASYNC_ERR
mdefine_line|#define AC_ASYNC_ERR  0x60000008    /* what type of asynchronous mem-error happened        */
DECL|macro|AC_ASYNC_VA
mdefine_line|#define AC_ASYNC_VA   0x6000000c    /* what virtual address caused the async-err to happen */
DECL|macro|AC_CACHEDDATA
mdefine_line|#define AC_CACHEDDATA 0x90000000    /* where the actual VAC cached data sits               */
macro_line|#endif /* _SPARC_CONTREGS_H */
eof
