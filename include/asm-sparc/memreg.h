multiline_comment|/* $Id: memreg.h,v 1.6 1996/04/25 06:13:13 davem Exp $ */
macro_line|#ifndef _SPARC_MEMREG_H
DECL|macro|_SPARC_MEMREG_H
mdefine_line|#define _SPARC_MEMREG_H
multiline_comment|/* memreg.h:  Definitions of the values found in the synchronous&n; *            and asynchronous memory error registers when a fault&n; *            occurs on the sun4c.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
multiline_comment|/* First the synchronous error codes, these are usually just&n; * normal page faults.&n; */
DECL|macro|SUN4C_SYNC_WDRESET
mdefine_line|#define SUN4C_SYNC_WDRESET   0x0001  /* watchdog reset */
DECL|macro|SUN4C_SYNC_SIZE
mdefine_line|#define SUN4C_SYNC_SIZE      0x0002  /* bad access size? whuz this? */
DECL|macro|SUN4C_SYNC_PARITY
mdefine_line|#define SUN4C_SYNC_PARITY    0x0008  /* bad ram chips caused a parity error */
DECL|macro|SUN4C_SYNC_SBUS
mdefine_line|#define SUN4C_SYNC_SBUS      0x0010  /* the SBUS had some problems... */
DECL|macro|SUN4C_SYNC_NOMEM
mdefine_line|#define SUN4C_SYNC_NOMEM     0x0020  /* translation to non-existent ram */
DECL|macro|SUN4C_SYNC_PROT
mdefine_line|#define SUN4C_SYNC_PROT      0x0040  /* access violated pte protections */
DECL|macro|SUN4C_SYNC_NPRESENT
mdefine_line|#define SUN4C_SYNC_NPRESENT  0x0080  /* pte said that page was not present */
DECL|macro|SUN4C_SYNC_BADWRITE
mdefine_line|#define SUN4C_SYNC_BADWRITE  0x8000  /* while writing something went bogus */
DECL|macro|SUN4C_SYNC_BOLIXED
mdefine_line|#define SUN4C_SYNC_BOLIXED  &bslash;&n;        (SUN4C_SYNC_WDRESET | SUN4C_SYNC_SIZE | SUN4C_SYNC_SBUS | &bslash;&n;         SUN4C_SYNC_NOMEM | SUN4C_SYNC_PARITY)
multiline_comment|/* Now the asynchronous error codes, these are almost always produced&n; * by the cache writing things back to memory and getting a bad translation.&n; * Bad DVMA transactions can cause these faults too.&n; */
DECL|macro|SUN4C_ASYNC_BADDVMA
mdefine_line|#define SUN4C_ASYNC_BADDVMA 0x0010  /* error during DVMA access */
DECL|macro|SUN4C_ASYNC_NOMEM
mdefine_line|#define SUN4C_ASYNC_NOMEM   0x0020  /* write back pointed to bad phys addr */
DECL|macro|SUN4C_ASYNC_BADWB
mdefine_line|#define SUN4C_ASYNC_BADWB   0x0080  /* write back points to non-present page */
macro_line|#endif /* !(_SPARC_MEMREG_H) */
eof
