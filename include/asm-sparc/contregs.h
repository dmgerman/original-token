macro_line|#ifndef _SPARC_CONTREGS_H
DECL|macro|_SPARC_CONTREGS_H
mdefine_line|#define _SPARC_CONTREGS_H
multiline_comment|/* contregs.h:  Addresses of registers in the ASI_CONTROL alternate address&n; *              space. These are for the mmu&squot;s context register, etc.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* 4 = sun4 (as in sun4 sysmaint student book), c = sun4c (according to davem) */
DECL|macro|AC_IDPROM
mdefine_line|#define AC_IDPROM     0x00000000    /* 4  ID PROM, R/O, byte, 32 bytes                        */
DECL|macro|AC_CONTEXT
mdefine_line|#define AC_CONTEXT    0x30000000    /* 4c current mmu-context, handy for invalidate()&squot;s ;-)   */
DECL|macro|AC_SENABLE
mdefine_line|#define AC_SENABLE    0x40000000    /* 4c system dvma/cache enable, plus special reset poking */
DECL|macro|AC_UDVMA_ENB
mdefine_line|#define AC_UDVMA_ENB  0x50000000    /* 4  Not used on Sun boards, byte                        */
DECL|macro|AC_BUS_ERROR
mdefine_line|#define AC_BUS_ERROR  0x60000000    /* 4  Cleared on read, byte. Probably same as sun4c.      */
DECL|macro|AC_SYNC_ERR
mdefine_line|#define AC_SYNC_ERR   0x60000000    /*  c what type of synchronous memory error happened      */
DECL|macro|AC_SYNC_VA
mdefine_line|#define AC_SYNC_VA    0x60000004    /*  c what virtual address caused the error to occur      */
DECL|macro|AC_ASYNC_ERR
mdefine_line|#define AC_ASYNC_ERR  0x60000008    /*  c what type of asynchronous mem-error happened        */
DECL|macro|AC_ASYNC_VA
mdefine_line|#define AC_ASYNC_VA   0x6000000c    /*  c what virtual address caused the async-err to happen */
DECL|macro|AC_LEDS
mdefine_line|#define AC_LEDS       0x70000000    /* 4  Zero turns on LEDs, byte                            */
DECL|macro|AC_CACHETAGS
mdefine_line|#define AC_CACHETAGS  0x80000000    /* 4c direct access to the VAC cache, unused...           */
DECL|macro|AC_CACHEDDATA
mdefine_line|#define AC_CACHEDDATA 0x90000000    /*  c where the actual VAC cached data sits               */
DECL|macro|AC_UDVMA_MAP
mdefine_line|#define AC_UDVMA_MAP  0xD0000000    /* 4  Not used on Sun boards, byte                        */
DECL|macro|AC_VME_VECTOR
mdefine_line|#define AC_VME_VECTOR 0xE0000000    /* 4  For non-Autovector VME, byte                        */
DECL|macro|AC_BOOT_SCC
mdefine_line|#define AC_BOOT_SCC   0xF0000000    /* 4  To bypass MMU and access Zilog 8530 on boot. byte.  */
multiline_comment|/* SPARCstation-5. I changed Paul&squot;s names to the hardware guy&squot;s ones. --P3 */
DECL|macro|AC_M_PCR
mdefine_line|#define AC_M_PCR      0x0000        /* 5  Processor Control Register */
DECL|macro|AC_M_CTPR
mdefine_line|#define AC_M_CTPR     0x0100        /* 5  Context Table Pointer Register  */
DECL|macro|AC_M_CXR
mdefine_line|#define AC_M_CXR      0x0200        /* 5  Context Register */
DECL|macro|AC_M_SFSR
mdefine_line|#define AC_M_SFSR     0x0300        /* 5  Synchronous Fault Status Register */
DECL|macro|AC_M_SFAR
mdefine_line|#define AC_M_SFAR     0x0400        /* 5  Synchronous Fault Address Register */
DECL|macro|AC_M_AFSR
mdefine_line|#define AC_M_AFSR     0x0500        /* 5  Asynchronous Fault Status Register */
DECL|macro|AC_M_AFAR
mdefine_line|#define AC_M_AFAR     0x0600        /* 5  Asynchronous Fault Address Register */
DECL|macro|AC_M_RESET
mdefine_line|#define AC_M_RESET    0x0700        /* 5  Reset Register  Aieee! */
DECL|macro|AC_M_RPR
mdefine_line|#define AC_M_RPR      0x1000        /* 5  Root Pointer Register */
DECL|macro|AC_M_TSUTRCR
mdefine_line|#define AC_M_TSUTRCR  0x1000        /* 5  TLB Replacement Control Reg on Tsunami */
DECL|macro|AC_M_IAPTP
mdefine_line|#define AC_M_IAPTP    0x1100        /* 5  Instruction Access PTP */
DECL|macro|AC_M_DAPTP
mdefine_line|#define AC_M_DAPTP    0x1200        /* 5  Data Access PTP */
DECL|macro|AC_M_ITR
mdefine_line|#define AC_M_ITR      0x1300        /* 5  Index Tag Register */
DECL|macro|AC_M_TRCR
mdefine_line|#define AC_M_TRCR     0x1400        /* 5  TLB Replacement Control Register */
multiline_comment|/* The following are Ross HyperSparc only. */
DECL|macro|AC_M_RPR1
mdefine_line|#define AC_M_RPR1     0x1500        /* 5  Root Pointer Register (entry 2) */
DECL|macro|AC_M_IAPTP1
mdefine_line|#define AC_M_IAPTP1   0x1600        /* 5  Instruction Access PTP (entry 2) */
DECL|macro|AC_M_DAPTP1
mdefine_line|#define AC_M_DAPTP1   0x1700        /* 5  Data Access PTP (entry 2) */
macro_line|#endif /* _SPARC_CONTREGS_H */
eof
