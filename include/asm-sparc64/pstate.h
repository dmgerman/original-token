multiline_comment|/* $Id: pstate.h,v 1.1 1996/12/12 11:57:14 davem Exp $ */
macro_line|#ifndef _SPARC64_PSTATE_H
DECL|macro|_SPARC64_PSTATE_H
mdefine_line|#define _SPARC64_PSTATE_H
multiline_comment|/* The V9 PSTATE Register (with SpitFire extensions).&n; *&n; * -----------------------------------------------------------------------&n; * | Resv | IG | MG | CLE | TLE |  MM  | RED | PEF | AM | PRIV | IE | AG |&n; * -----------------------------------------------------------------------&n; *  63  12  11   10    9     8    7   6   5     4     3     2     1    0&n; */
DECL|macro|PSTATE_IG
mdefine_line|#define PSTATE_IG&t;0x0000000000000800&t;/* Interrupt Globals.&t;&t;*/
DECL|macro|PSTATE_MG
mdefine_line|#define PSTATE_MG&t;0x0000000000000400&t;/* MMU Globals.&t;&t;&t;*/
DECL|macro|PSTATE_CLE
mdefine_line|#define PSTATE_CLE&t;0x0000000000000200&t;/* Current Little Endian.&t;*/
DECL|macro|PSTATE_TLE
mdefine_line|#define PSTATE_TLE&t;0x0000000000000100&t;/* Trap Little Endian.&t;&t;*/
DECL|macro|PSTATE_MM
mdefine_line|#define PSTATE_MM&t;0x00000000000000c0&t;/* Memory Model.&t;&t;*/
DECL|macro|PSTATE_RED
mdefine_line|#define PSTATE_RED&t;0x0000000000000020&t;/* Reset Error Debug State.&t;*/
DECL|macro|PSTATE_PEF
mdefine_line|#define PSTATE_PEF&t;0x0000000000000010&t;/* Floating Point Enable.&t;*/
DECL|macro|PSTATE_AM
mdefine_line|#define PSTATE_AM&t;0x0000000000000008&t;/* Address Mask.&t;&t;*/
DECL|macro|PSTATE_PRIV
mdefine_line|#define PSTATE_PRIV&t;0x0000000000000004&t;/* Privilege.&t;&t;&t;*/
DECL|macro|PSTATE_IE
mdefine_line|#define PSTATE_IE&t;0x0000000000000002&t;/* Interrupt Enable.&t;&t;*/
DECL|macro|PSTATE_AG
mdefine_line|#define PSTATE_AG&t;0x0000000000000001&t;/* Alternate Globals.&t;&t;*/
multiline_comment|/* The V9 TSTATE Register (with SpitFire extensions).&n; *&n; * ---------------------------------------------------------------&n; * |  Resv  |  CCR  |  ASI  |  Resv  |  PSTATE  |  Resv  |  CWP  |&n; * ---------------------------------------------------------------&n; *  63    40 39   32 31   24 23    20 19       8 7      5 4     0&n; */
DECL|macro|TSTATE_CCR
mdefine_line|#define TSTATE_CCR&t;0x000000ff00000000&t;/* Condition Codes.&t;&t;*/
DECL|macro|TSTATE_XNEG
mdefine_line|#define TSTATE_XNEG&t;0x0000008000000000&t;/* %xcc Negative.&t;&t;*/
DECL|macro|TSTATE_XZERO
mdefine_line|#define TSTATE_XZERO&t;0x0000004000000000&t;/* %xcc Zero.&t;&t;&t;*/
DECL|macro|TSTATE_XOVFL
mdefine_line|#define TSTATE_XOVFL&t;0x0000002000000000&t;/* %xcc Overflow.&t;&t;*/
DECL|macro|TSTATE_XCARRY
mdefine_line|#define TSTATE_XCARRY&t;0x0000001000000000&t;/* %xcc Carry.&t;&t;&t;*/
DECL|macro|TSTATE_INEG
mdefine_line|#define TSTATE_INEG&t;0x0000000800000000&t;/* %icc Negative.&t;&t;*/
DECL|macro|TSTATE_IZERO
mdefine_line|#define TSTATE_IZERO&t;0x0000000400000000&t;/* %icc Zero.&t;&t;&t;*/
DECL|macro|TSTATE_IOVFL
mdefine_line|#define TSTATE_IOVFL&t;0x0000000200000000&t;/* %icc Overflow.&t;&t;*/
DECL|macro|TSTATE_ICARRY
mdefine_line|#define TSTATE_ICARRY&t;0x0000000100000000&t;/* %icc Carry.&t;&t;&t;*/
DECL|macro|TSTATE_ASI
mdefine_line|#define TSTATE_ASI&t;0x00000000ff000000&t;/* Address Space Identifier.&t;*/
DECL|macro|TSTATE_PSTATE
mdefine_line|#define TSTATE_PSTATE&t;0x00000000000fff00&t;/* PSTATE.&t;&t;&t;*/
DECL|macro|TSTATE_IG
mdefine_line|#define TSTATE_IG&t;0x0000000000080000&t;/* Interrupt Globals.&t;&t;*/
DECL|macro|TSTATE_MG
mdefine_line|#define TSTATE_MG&t;0x0000000000040000&t;/* MMU Globals.&t;&t;&t;*/
DECL|macro|TSTATE_CLE
mdefine_line|#define TSTATE_CLE&t;0x0000000000020000&t;/* Current Little Endian.&t;*/
DECL|macro|TSTATE_TLE
mdefine_line|#define TSTATE_TLE&t;0x0000000000010000&t;/* Trap Little Endian.&t;&t;*/
DECL|macro|TSTATE_MM
mdefine_line|#define TSTATE_MM&t;0x000000000000c000&t;/* Memory Model.&t;&t;*/
DECL|macro|TSTATE_RED
mdefine_line|#define TSTATE_RED&t;0x0000000000002000&t;/* Reset Error Debug State.&t;*/
DECL|macro|TSTATE_PEF
mdefine_line|#define TSTATE_PEF&t;0x0000000000001000&t;/* Floating Point Enable.&t;*/
DECL|macro|TSTATE_AM
mdefine_line|#define TSTATE_AM&t;0x0000000000000800&t;/* Address Mask.&t;&t;*/
DECL|macro|TSTATE_PRIV
mdefine_line|#define TSTATE_PRIV&t;0x0000000000000400&t;/* Privilege.&t;&t;&t;*/
DECL|macro|TSTATE_IE
mdefine_line|#define TSTATE_IE&t;0x0000000000000200&t;/* Interrupt Enable.&t;&t;*/
DECL|macro|TSTATE_AG
mdefine_line|#define TSTATE_AG&t;0x0000000000000100&t;/* Alternate Globals.&t;&t;*/
DECL|macro|TSTATE_CWP
mdefine_line|#define TSTATE_CWP&t;0x000000000000001f&t;/* Current Window Pointer.&t;*/
multiline_comment|/* Floating-Point Registers State Register.&n; *&n; * --------------------------------&n; * |  Resv  |  FEF  |  DU  |  DL  |&n; * --------------------------------&n; *  63     3    2       1      0&n; */
DECL|macro|FPRS_FEF
mdefine_line|#define FPRS_FEF&t;0x0000000000000004&t;/* Enable Floating Point.&t;*/
DECL|macro|FPRS_DU
mdefine_line|#define FPRS_DU&t;&t;0x0000000000000002&t;/* Dirty Upper.&t;&t;&t;*/
DECL|macro|FPRS_DL
mdefine_line|#define FPRS_DL&t;&t;0x0000000000000001&t;/* Dirty Lower.&t;&t;&t;*/
multiline_comment|/* Version Register.&n; *&n; * ------------------------------------------------------&n; * | MANUF | IMPL | MASK | Resv | MAXTL | Resv | MAXWIN |&n; * ------------------------------------------------------&n; *  63   48 47  32 31  24 23  16 15    8 7    5 4      0&n; */
DECL|macro|VERS_MANUF
mdefine_line|#define VERS_MANUF&t;0xffff000000000000&t;/* Manufacturer.&t;&t;*/
DECL|macro|VERS_IMPL
mdefine_line|#define VERS_IMPL&t;0x0000ffff00000000&t;/* Implementation.&t;&t;*/
DECL|macro|VERS_MASK
mdefine_line|#define VERS_MASK&t;0x00000000ff000000&t;/* Mask Set Revision.&t;&t;*/
DECL|macro|VERS_MAXTL
mdefine_line|#define VERS_MAXTL&t;0x000000000000ff00&t;/* Maximum Trap Level.&t;&t;*/
DECL|macro|VERS_MAXWIN
mdefine_line|#define VERS_MAXWIN&t;0x000000000000001f&t;/* Maximum Reg Window Index.&t;*/
macro_line|#endif /* !(_SPARC64_PSTATE_H) */
eof