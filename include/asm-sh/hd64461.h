macro_line|#ifndef __ASM_SH_HD64461
DECL|macro|__ASM_SH_HD64461
mdefine_line|#define __ASM_SH_HD64461
multiline_comment|/*&n; *&t;$Id: hd64461.h,v 1.1 2000/06/10 21:45:48 yaegashi Exp $&n; *&t;Copyright (C) 2000 YAEGASHI Takeshi&n; *&t;Hitachi HD64461 companion chip support&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|HD64461_CPTWAR
mdefine_line|#define HD64461_CPTWAR&t;0x1030&t;
DECL|macro|HD64461_CPTWDR
mdefine_line|#define HD64461_CPTWDR&t;0x1032
DECL|macro|HD64461_CPTRAR
mdefine_line|#define HD64461_CPTRAR&t;0x1034&t;
DECL|macro|HD64461_CPTRDR
mdefine_line|#define HD64461_CPTRDR&t;0x1036
DECL|macro|HD64461_PCC0ISR
mdefine_line|#define HD64461_PCC0ISR         0x2000
DECL|macro|HD64461_PCC0GCR
mdefine_line|#define HD64461_PCC0GCR         0x2002
DECL|macro|HD64461_PCC0CSCR
mdefine_line|#define HD64461_PCC0CSCR        0x2004
DECL|macro|HD64461_PCC0CSCIER
mdefine_line|#define HD64461_PCC0CSCIER      0x2006
DECL|macro|HD64461_PCC0SCR
mdefine_line|#define HD64461_PCC0SCR         0x2008
DECL|macro|HD64461_PCC1ISR
mdefine_line|#define HD64461_PCC1ISR         0x2010
DECL|macro|HD64461_PCC1GCR
mdefine_line|#define HD64461_PCC1GCR         0x2012
DECL|macro|HD64461_PCC1CSCR
mdefine_line|#define HD64461_PCC1CSCR        0x2014
DECL|macro|HD64461_PCC1CSCIER
mdefine_line|#define HD64461_PCC1CSCIER      0x2016
DECL|macro|HD64461_PCC1SCR
mdefine_line|#define HD64461_PCC1SCR         0x2018
DECL|macro|HD64461_P0OCR
mdefine_line|#define HD64461_P0OCR           0x202a
DECL|macro|HD64461_P1OCR
mdefine_line|#define HD64461_P1OCR           0x202c
DECL|macro|HD64461_PGCR
mdefine_line|#define HD64461_PGCR            0x202e
DECL|macro|HD64461_NIRR
mdefine_line|#define HD64461_NIRR&t;&t;0x5000
DECL|macro|HD64461_NIMR
mdefine_line|#define HD64461_NIMR&t;&t;0x5002
macro_line|#ifndef CONFIG_HD64461_IOBASE
DECL|macro|CONFIG_HD64461_IOBASE
mdefine_line|#define CONFIG_HD64461_IOBASE&t;0xb0000000
macro_line|#endif
DECL|macro|HD64461_IRQBASE
mdefine_line|#define HD64461_IRQBASE&t;64
macro_line|#endif
eof
