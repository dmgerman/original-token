multiline_comment|/* $Id: siemens.h,v 1.4 1997/01/21 22:24:33 keil Exp $&n; *&n; * siemens.h   ISAC and HSCX spezific Macros&n; *&n; * Author&t;Karsten Keil (keil@temic-ech.spacenet.de)&n; *&n; *&n; * $Log: siemens.h,v $&n; * Revision 1.4  1997/01/21 22:24:33  keil&n; * cleanups&n; *&n; * Revision 1.3  1996/12/08 19:48:34  keil&n; * adding Monitor channel registers&n; *&n; * Revision 1.2  1996/10/27 22:24:00  keil&n; * HSCX version code removed&n; *&n; * Revision 1.1  1996/10/12 21:39:39  keil&n; * Initial revision&n; *&n; *&n;*/
multiline_comment|/* All Registers without FIFOs (original Siemens Spec - 20 hex) */
DECL|macro|ISAC_MASK
mdefine_line|#define ISAC_MASK 0x0
DECL|macro|ISAC_ISTA
mdefine_line|#define ISAC_ISTA 0x0
DECL|macro|ISAC_STAR
mdefine_line|#define ISAC_STAR 0x1
DECL|macro|ISAC_CMDR
mdefine_line|#define ISAC_CMDR 0x1
DECL|macro|ISAC_EXIR
mdefine_line|#define ISAC_EXIR 0x4
DECL|macro|ISAC_RBCH
mdefine_line|#define ISAC_RBCH 0xa
DECL|macro|ISAC_ADF2
mdefine_line|#define ISAC_ADF2 0x19
DECL|macro|ISAC_SPCR
mdefine_line|#define ISAC_SPCR 0x10
DECL|macro|ISAC_ADF1
mdefine_line|#define ISAC_ADF1 0x18
DECL|macro|ISAC_CIR0
mdefine_line|#define ISAC_CIR0 0x11
DECL|macro|ISAC_CIX0
mdefine_line|#define ISAC_CIX0 0x11
DECL|macro|ISAC_STCR
mdefine_line|#define ISAC_STCR 0x17
DECL|macro|ISAC_MODE
mdefine_line|#define ISAC_MODE 0x2
DECL|macro|ISAC_RSTA
mdefine_line|#define ISAC_RSTA 0x7
DECL|macro|ISAC_RBCL
mdefine_line|#define ISAC_RBCL 0x5
DECL|macro|ISAC_TIMR
mdefine_line|#define ISAC_TIMR 0x3
DECL|macro|ISAC_SQXR
mdefine_line|#define ISAC_SQXR 0x1b
DECL|macro|ISAC_MOSR
mdefine_line|#define ISAC_MOSR 0x1a
DECL|macro|ISAC_MOCR
mdefine_line|#define ISAC_MOCR 0x1a
DECL|macro|ISAC_MOR0
mdefine_line|#define ISAC_MOR0 0x12
DECL|macro|ISAC_MOX0
mdefine_line|#define ISAC_MOX0 0x12
DECL|macro|ISAC_MOR1
mdefine_line|#define ISAC_MOR1 0x14
DECL|macro|ISAC_MOX1
mdefine_line|#define ISAC_MOX1 0x14
DECL|macro|HSCX_ISTA
mdefine_line|#define HSCX_ISTA 0x0
DECL|macro|HSCX_CCR1
mdefine_line|#define HSCX_CCR1 0xf
DECL|macro|HSCX_CCR2
mdefine_line|#define HSCX_CCR2 0xc
DECL|macro|HSCX_TSAR
mdefine_line|#define HSCX_TSAR 0x11
DECL|macro|HSCX_TSAX
mdefine_line|#define HSCX_TSAX 0x10
DECL|macro|HSCX_XCCR
mdefine_line|#define HSCX_XCCR 0x12
DECL|macro|HSCX_RCCR
mdefine_line|#define HSCX_RCCR 0x13
DECL|macro|HSCX_MODE
mdefine_line|#define HSCX_MODE 0x2
DECL|macro|HSCX_CMDR
mdefine_line|#define HSCX_CMDR 0x1
DECL|macro|HSCX_EXIR
mdefine_line|#define HSCX_EXIR 0x4
DECL|macro|HSCX_XAD1
mdefine_line|#define HSCX_XAD1 0x4
DECL|macro|HSCX_XAD2
mdefine_line|#define HSCX_XAD2 0x5
DECL|macro|HSCX_RAH2
mdefine_line|#define HSCX_RAH2 0x7
DECL|macro|HSCX_RSTA
mdefine_line|#define HSCX_RSTA 0x7
DECL|macro|HSCX_TIMR
mdefine_line|#define HSCX_TIMR 0x3
DECL|macro|HSCX_STAR
mdefine_line|#define HSCX_STAR 0x1
DECL|macro|HSCX_RBCL
mdefine_line|#define HSCX_RBCL 0x5
DECL|macro|HSCX_XBCH
mdefine_line|#define HSCX_XBCH 0xd
DECL|macro|HSCX_VSTR
mdefine_line|#define HSCX_VSTR 0xe
DECL|macro|HSCX_RLCR
mdefine_line|#define HSCX_RLCR 0xe
DECL|macro|HSCX_MASK
mdefine_line|#define HSCX_MASK 0x0
eof
