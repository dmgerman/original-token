multiline_comment|/* $Id: cypress.h,v 1.2 1995/11/25 02:31:29 davem Exp $&n; * cypress.h: Cypress module specific definitions and defines.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_CYPRESS_H
DECL|macro|_SPARC_CYPRESS_H
mdefine_line|#define _SPARC_CYPRESS_H
multiline_comment|/* Cypress chips have %psr &squot;impl&squot; of &squot;0001&squot; and &squot;vers&squot; of &squot;0001&squot;. */
multiline_comment|/* The MMU control register fields on the Sparc Cypress 604/605 MMU&squot;s.&n; *&n; * ---------------------------------------------------------------&n; * |implvers| MCA | MCM |MV| MID |BM| C|RSV|MR|CM|CL|CE|RSV|NF|ME|&n; * ---------------------------------------------------------------&n; *  31    24 23-22 21-20 19 18-15 14 13  12 11 10  9  8 7-2  1  0&n; *&n; * MCA: MultiChip Access -- Used for configuration of multiple&n; *      CY7C604/605 cache units.&n; * MCM: MultiChip Mask -- Again, for multiple cache unit config.&n; * MV: MultiChip Valid -- Indicates MCM and MCA have valid settings.&n; * MID: ModuleID -- Unique processor ID for MBus transactions. (605 only)&n; * BM: Boot Mode -- 0 = not in boot mode, 1 = in boot mode&n; * C: Cacheable -- Indicates whether accesses are cacheable while&n; *    the MMU is off.  0=no 1=yes&n; * MR: MemoryReflection -- Indicates whether the bus attacted to the&n; *     MBus supports memory reflection. 0=no 1=yes (605 only)&n; * CM: CacheMode -- Indicates whether the cache is operating in write&n; *     through or copy-back mode. 0=write-through 1=copy-back&n; * CL: CacheLock -- Indicates if the entire cache is locked or not.&n; *     0=not-locked 1=locked  (604 only)&n; * CE: CacheEnable -- Is the virtual cache on? 0=no 1=yes&n; * NF: NoFault -- Do faults generate traps? 0=yes 1=no&n; * ME: MmuEnable -- Is the MMU doing translations? 0=no 1=yes&n; */
multiline_comment|/* NEEDS TO BE FIXED */
DECL|macro|CYPRESS_MCABITS
mdefine_line|#define CYPRESS_MCABITS   0x01800000
DECL|macro|CYPRESS_MCMBITS
mdefine_line|#define CYPRESS_MCMBITS   0x00600000
DECL|macro|CYPRESS_MVALID
mdefine_line|#define CYPRESS_MVALID    0x00040000
DECL|macro|CYPRESS_MIDMASK
mdefine_line|#define CYPRESS_MIDMASK   0x0003c000   /* Only on 605 */
DECL|macro|CYPRESS_BMODE
mdefine_line|#define CYPRESS_BMODE     0x00002000
DECL|macro|CYPRESS_ACENABLE
mdefine_line|#define CYPRESS_ACENABLE  0x00001000
DECL|macro|CYPRESS_MRFLCT
mdefine_line|#define CYPRESS_MRFLCT    0x00000800   /* Only on 605 */
DECL|macro|CYPRESS_CMODE
mdefine_line|#define CYPRESS_CMODE     0x00000400
DECL|macro|CYPRESS_CLOCK
mdefine_line|#define CYPRESS_CLOCK     0x00000200   /* Only on 604 */
DECL|macro|CYPRESS_CENABLE
mdefine_line|#define CYPRESS_CENABLE   0x00000100
DECL|macro|CYPRESS_NFAULT
mdefine_line|#define CYPRESS_NFAULT    0x00000002
DECL|macro|CYPRESS_MENABLE
mdefine_line|#define CYPRESS_MENABLE   0x00000001
macro_line|#endif /* !(_SPARC_CYPRESS_H) */
eof
