macro_line|#ifndef _SPARC_MEMREG_H
DECL|macro|_SPARC_MEMREG_H
mdefine_line|#define _SPARC_MEMREG_H
multiline_comment|/* memreg.h:  Definitions of the values found in the synchronous&n; *            and asynchronous memory error registers when a fault&n; *            occurs on the sun4c.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* First the synchronous error codes, these are usually just&n; * normal page faults.&n; */
DECL|macro|SUN4C_SYNC_WDRESET
mdefine_line|#define SUN4C_SYNC_WDRESET   0x1  /* watchdog reset, only the prom sees this */
DECL|macro|SUN4C_SYNC_SIZE
mdefine_line|#define SUN4C_SYNC_SIZE      0x2  /* bad access size? whuz this? */
DECL|macro|SUN4C_SYNC_PARITY
mdefine_line|#define SUN4C_SYNC_PARITY    0x8  /* bad ram chips caused a parity error */
DECL|macro|SUN4C_SYNC_SBUS
mdefine_line|#define SUN4C_SYNC_SBUS      0x10 /* the SBUS had some problems... */
DECL|macro|SUN4C_SYNC_NOMEM
mdefine_line|#define SUN4C_SYNC_NOMEM     0x20 /* translation pointed to non-existant ram */
DECL|macro|SUN4C_SYNC_PROT
mdefine_line|#define SUN4C_SYNC_PROT      0x40 /* access violated pte protection settings */
DECL|macro|SUN4C_SYNC_NPRESENT
mdefine_line|#define SUN4C_SYNC_NPRESENT  0x80 /* pte said that page was not present */
DECL|macro|SUN4C_SYNC_BADWRITE
mdefine_line|#define SUN4C_SYNC_BADWRITE  0x8000  /* while writing something went bogus */
multiline_comment|/* Now the asynchronous error codes, these are almost always produced&n; * by the cache writing things back to memory and getting a bad translation.&n; * Bad DVMA transactions can cause these faults too.&n; */
DECL|macro|SUN4C_ASYNC_BADDVMA
mdefine_line|#define SUN4C_ASYNC_BADDVMA  0x10 /* error during DVMA access */
DECL|macro|SUN4C_ASYNC_NOMEM
mdefine_line|#define SUN4C_ASYNC_NOMEM    0x20 /* write back pointed to bad phys addr */
DECL|macro|SUN4C_ASYNC_BADWB
mdefine_line|#define SUN4C_ASYNC_BADWB    0x80 /* write back points to non-present page */
multiline_comment|/* These are the values passed as the first arguement to the fault&n; * entry c-code from the assembly entry points.&n; */
DECL|macro|FAULT_ASYNC
mdefine_line|#define FAULT_ASYNC          0x0
DECL|macro|FAULT_SYNC
mdefine_line|#define FAULT_SYNC           0x1
macro_line|#endif /* !(_SPARC_MEMREG_H) */
eof
