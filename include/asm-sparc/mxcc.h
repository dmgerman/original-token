multiline_comment|/* mxcc.h:  Definitions of the Viking MXCC registers&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MXCC_H
DECL|macro|_SPARC_MXCC_H
mdefine_line|#define _SPARC_MXCC_H
multiline_comment|/* These registers are accessed through ASI 0x2. */
DECL|macro|MXCC_DATSTREAM
mdefine_line|#define MXCC_DATSTREAM       0x1C00000  /* Data stream register */
DECL|macro|MXCC_SRCSTREAM
mdefine_line|#define MXCC_SRCSTREAM       0x1C00100  /* Source stream register */
DECL|macro|MXCC_DESSTREAM
mdefine_line|#define MXCC_DESSTREAM       0x1C00200  /* Destination stream register */
DECL|macro|MXCC_RMCOUNT
mdefine_line|#define MXCC_RMCOUNT         0x1C00300  /* Count of references and misses */
DECL|macro|MXCC_STEST
mdefine_line|#define MXCC_STEST           0x1C00804  /* Internal self-test */
DECL|macro|MXCC_CREG
mdefine_line|#define MXCC_CREG            0x1C00A04  /* Control register */
DECL|macro|MXCC_SREG
mdefine_line|#define MXCC_SREG            0x1C00B00  /* Status register */
DECL|macro|MXCC_RREG
mdefine_line|#define MXCC_RREG            0x1C00C04  /* Reset register */
DECL|macro|MXCC_EREG
mdefine_line|#define MXCC_EREG            0x1C00E00  /* Error code register */
DECL|macro|MXCC_PREG
mdefine_line|#define MXCC_PREG            0x1C00F04  /* Address port register */
multiline_comment|/* The MXCC Control Register:&n; *&n; * ----------------------------------------------------------------------&n; * |                                   | RRC | RSV |PRE|MCE|PARE|ECE|RSV|&n; * ----------------------------------------------------------------------&n; *  31                              10    9    8-6   5   4    3   2  1-0&n; *&n; * RRC: Controls what you read from MXCC_RMCOUNT reg.&n; *      0=Misses 1=References&n; * PRE: Prefetch enable&n; * MCE: Multiple Command Enable&n; * PARE: Parity enable&n; * ECE: External cache enable&n; */
DECL|macro|MXCC_CTL_RRC
mdefine_line|#define MXCC_CTL_RRC   0x00000200
DECL|macro|MXCC_CTL_PRE
mdefine_line|#define MXCC_CTL_PRE   0x00000020
DECL|macro|MXCC_CTL_MCE
mdefine_line|#define MXCC_CTL_MCE   0x00000010
DECL|macro|MXCC_CTL_PARE
mdefine_line|#define MXCC_CTL_PARE  0x00000008
DECL|macro|MXCC_CTL_ECE
mdefine_line|#define MXCC_CTL_ECE   0x00000004
multiline_comment|/* The MXCC Error Register:&n; *&n; * --------------------------------------------------------&n; * |ME| RSV|CE|PEW|PEE|ASE|EIV| MOPC|ECODE|PRIV|RSV|HPADDR|&n; * --------------------------------------------------------&n; *  31   30 29  28  27  26  25 24-15  14-7   6  5-3   2-0&n; *&n; * ME: Multiple Errors have occurred&n; * CE: Cache consistancy Error&n; * PEW: Parity Error during a Write operation&n; * PEE: Parity Error involving the External cache&n; * ASE: ASynchronous Error&n; * EIV: This register is toast&n; * MOPC: MXCC Operation Code for instance causing error&n; * ECODE: The Error CODE&n; * PRIV: A privileged mode error? 0=no 1=yes&n; * HPADDR: High PhysicalADDRess bits (35-32)&n; */
DECL|macro|MXCC_ERR_ME
mdefine_line|#define MXCC_ERR_ME     0x80000000
DECL|macro|MXCC_ERR_CE
mdefine_line|#define MXCC_ERR_CE     0x20000000
DECL|macro|MXCC_ERR_PEW
mdefine_line|#define MXCC_ERR_PEW    0x10000000
DECL|macro|MXCC_ERR_PEE
mdefine_line|#define MXCC_ERR_PEE    0x08000000
DECL|macro|MXCC_ERR_ASE
mdefine_line|#define MXCC_ERR_ASE    0x04000000
DECL|macro|MXCC_ERR_EIV
mdefine_line|#define MXCC_ERR_EIV    0x02000000
DECL|macro|MXCC_ERR_MOPC
mdefine_line|#define MXCC_ERR_MOPC   0x01FF8000
DECL|macro|MXCC_ERR_ECODE
mdefine_line|#define MXCC_ERR_ECODE  0x00007F80
DECL|macro|MXCC_ERR_PRIV
mdefine_line|#define MXCC_ERR_PRIV   0x00000040
DECL|macro|MXCC_ERR_HPADDR
mdefine_line|#define MXCC_ERR_HPADDR 0x0000000f
multiline_comment|/* The MXCC Port register:&n; *&n; * -----------------------------------------------------&n; * |                | MID |                            |&n; * -----------------------------------------------------&n; *  31            21 20-18 17                         0&n; *&n; * MID: The moduleID of the cpu your read this from.&n; */
macro_line|#endif /* !(_SPARC_MXCC_H) */
eof
