multiline_comment|/* $Id: mostek.h,v 1.5 1996/04/25 06:13:17 davem Exp $&n; * mostek.h:  Describes the various Mostek time of day clock registers.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_MOSTEK_H
DECL|macro|_SPARC_MOSTEK_H
mdefine_line|#define _SPARC_MOSTEK_H
macro_line|#include &lt;asm/idprom.h&gt;
multiline_comment|/* First the Mostek 48t02 clock chip.  The registers other than the&n; * control register are in binary coded decimal.&n; */
DECL|struct|mostek48t02
r_struct
id|mostek48t02
(brace
DECL|member|eeprom
r_char
id|eeprom
(braket
l_int|2008
)braket
suffix:semicolon
multiline_comment|/* This is the eeprom, don&squot;t touch! */
DECL|member|idprom
r_struct
id|idp_struct
id|idprom
suffix:semicolon
multiline_comment|/* The idprom lives here. */
DECL|member|creg
r_volatile
r_int
r_char
id|creg
suffix:semicolon
multiline_comment|/* Control register */
DECL|member|sec
r_volatile
r_int
r_char
id|sec
suffix:semicolon
multiline_comment|/* Seconds (0-59) */
DECL|member|min
r_volatile
r_int
r_char
id|min
suffix:semicolon
multiline_comment|/* Minutes (0-59) */
DECL|member|hour
r_volatile
r_int
r_char
id|hour
suffix:semicolon
multiline_comment|/* Hour (0-23) */
DECL|member|dow
r_volatile
r_int
r_char
id|dow
suffix:semicolon
multiline_comment|/* Day of the week (1-7) */
DECL|member|dom
r_volatile
r_int
r_char
id|dom
suffix:semicolon
multiline_comment|/* Day of the month (1-31) */
DECL|member|mnth
r_volatile
r_int
r_char
id|mnth
suffix:semicolon
multiline_comment|/* Month of year (1-12) */
DECL|member|yr
r_volatile
r_int
r_char
id|yr
suffix:semicolon
multiline_comment|/* Year (0-99) */
)brace
suffix:semicolon
r_extern
r_struct
id|mostek48t02
op_star
id|mstk48t02_regs
suffix:semicolon
multiline_comment|/* Control register values. */
DECL|macro|MSTK_CREG_WRITE
mdefine_line|#define MSTK_CREG_WRITE    0x80   /* Must set this before placing values. */
DECL|macro|MSTK_CREG_READ
mdefine_line|#define MSTK_CREG_READ     0x40   /* Stop the clock, I want to fetch values. */
DECL|macro|MSTK_CREG_SIGN
mdefine_line|#define MSTK_CREG_SIGN     0x20   /* Grrr... what&squot;s this??? */
DECL|macro|MSTK_YR_ZERO
mdefine_line|#define MSTK_YR_ZERO       1968   /* If year reg has zero, it is 1968 */
DECL|macro|MSTK_CVT_YEAR
mdefine_line|#define MSTK_CVT_YEAR(yr)  ((yr) + MSTK_YR_ZERO)
multiline_comment|/* Fun with masks. */
DECL|macro|MSTK_SEC_MASK
mdefine_line|#define MSTK_SEC_MASK      0x7f
DECL|macro|MSTK_MIN_MASK
mdefine_line|#define MSTK_MIN_MASK      0x7f
DECL|macro|MSTK_HOUR_MASK
mdefine_line|#define MSTK_HOUR_MASK     0x3f
DECL|macro|MSTK_DOW_MASK
mdefine_line|#define MSTK_DOW_MASK      0x07
DECL|macro|MSTK_DOM_MASK
mdefine_line|#define MSTK_DOM_MASK      0x3f
DECL|macro|MSTK_MNTH_MASK
mdefine_line|#define MSTK_MNTH_MASK     0x1f
DECL|macro|MSTK_YR_MASK
mdefine_line|#define MSTK_YR_MASK       0xff
multiline_comment|/* Conversion routines. */
DECL|macro|MSTK_REGVAL_TO_DECIMAL
mdefine_line|#define MSTK_REGVAL_TO_DECIMAL(x)  (((x) &amp; 0xf) + 0xa * ((x) &gt;&gt; 0x4))
DECL|macro|MSTK_DECIMAL_TO_REGVAL
mdefine_line|#define MSTK_DECIMAL_TO_REGVAL(x)  ((((x) / 0xa) &lt;&lt; 0x4) + ((x) % 0xa))
multiline_comment|/* Macros to make register access easier on our fingers. These give you&n; * the decimal value of the register requested if applicable.  You pass&n; * the a pointer to a &squot;struct mostek48t02&squot;.&n; */
DECL|macro|MSTK_REG_CREG
mdefine_line|#define MSTK_REG_CREG(ptr)  (ptr-&gt;creg)
DECL|macro|MSTK_REG_SEC
mdefine_line|#define MSTK_REG_SEC(ptr)   (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;sec &amp; MSTK_SEC_MASK)))
DECL|macro|MSTK_REG_MIN
mdefine_line|#define MSTK_REG_MIN(ptr)   (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;min &amp; MSTK_MIN_MASK)))
DECL|macro|MSTK_REG_HOUR
mdefine_line|#define MSTK_REG_HOUR(ptr)  (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;hour &amp; MSTK_HOUR_MASK)))
DECL|macro|MSTK_REG_DOW
mdefine_line|#define MSTK_REG_DOW(ptr)   (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;dow &amp; MSTK_DOW_MASK)))
DECL|macro|MSTK_REG_DOM
mdefine_line|#define MSTK_REG_DOM(ptr)   (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;dom &amp; MSTK_DOM_MASK)))
DECL|macro|MSTK_REG_MNTH
mdefine_line|#define MSTK_REG_MNTH(ptr)  (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;mnth &amp; MSTK_MNTH_MASK)))
DECL|macro|MSTK_REG_YR
mdefine_line|#define MSTK_REG_YR(ptr)    (MSTK_REGVAL_TO_DECIMAL((ptr-&gt;yr &amp; MSTK_YR_MASK)))
multiline_comment|/* The Mostek 48t02 clock chip.  Found on Sun4m&squot;s I think.  It has the&n; * same (basically) layout of the 48t02 chip.&n; */
DECL|struct|mostek48t08
r_struct
id|mostek48t08
(brace
DECL|member|offset
r_char
id|offset
(braket
l_int|6
op_star
l_int|1024
)braket
suffix:semicolon
multiline_comment|/* Magic things may be here, who knows? */
DECL|member|regs
r_struct
id|mostek48t02
id|regs
suffix:semicolon
multiline_comment|/* Here is what we are interested in.   */
)brace
suffix:semicolon
r_extern
r_struct
id|mostek48t08
op_star
id|mstk48t08_regs
suffix:semicolon
DECL|enum|sparc_clock_type
DECL|enumerator|MSTK48T02
DECL|enumerator|MSTK48T08
DECL|enumerator|MSTK_INVALID
r_enum
id|sparc_clock_type
(brace
id|MSTK48T02
comma
id|MSTK48T08
comma
id|MSTK_INVALID
)brace
suffix:semicolon
r_extern
r_enum
id|sparc_clock_type
id|sp_clock_typ
suffix:semicolon
macro_line|#endif /* !(_SPARC_MOSTEK_H) */
eof
