multiline_comment|/* $Id: ns87303.h,v 1.1 1997/10/14 13:30:37 ecd Exp $&n; * ns87303.h: Configuration Register Description for the&n; *            National Semiconductor PC87303 (SuperIO).&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#ifndef _SPARC_NS87303_H
DECL|macro|_SPARC_NS87303_H
mdefine_line|#define _SPARC_NS87303_H 1
multiline_comment|/*&n; * Controll Register Index Values&n; */
DECL|macro|FER
mdefine_line|#define FER&t;0x00
DECL|macro|FAR
mdefine_line|#define FAR&t;0x01
DECL|macro|PTR
mdefine_line|#define PTR&t;0x02
DECL|macro|FCR
mdefine_line|#define FCR&t;0x03
DECL|macro|PCR
mdefine_line|#define PCR&t;0x04
DECL|macro|KRR
mdefine_line|#define KRR&t;0x05
DECL|macro|PMC
mdefine_line|#define PMC&t;0x06
DECL|macro|TUP
mdefine_line|#define TUP&t;0x07
DECL|macro|SID
mdefine_line|#define SID&t;0x08
DECL|macro|ASC
mdefine_line|#define ASC&t;0x09
DECL|macro|CS0CF0
mdefine_line|#define CS0CF0&t;0x0a
DECL|macro|CS0CF1
mdefine_line|#define CS0CF1&t;0x0b
DECL|macro|CS1CF0
mdefine_line|#define CS1CF0&t;0x0c
DECL|macro|CS1CF1
mdefine_line|#define CS1CF1&t;0x0d
multiline_comment|/* Function Address Register (FAR) bits */
DECL|macro|FAR_LPT_MASK
mdefine_line|#define FAR_LPT_MASK&t;0x03
DECL|macro|FAR_LPTB
mdefine_line|#define FAR_LPTB&t;0x00
DECL|macro|FAR_LPTA
mdefine_line|#define FAR_LPTA&t;0x01
DECL|macro|FAR_LPTC
mdefine_line|#define FAR_LPTC&t;0x02
multiline_comment|/* Power and Test Register (PTR) bits */
DECL|macro|PTR_LPTB_IRQ7
mdefine_line|#define PTR_LPTB_IRQ7&t;0x08
DECL|macro|PTR_LEVEL_IRQ
mdefine_line|#define PTR_LEVEL_IRQ&t;0x80&t;/* When not ECP/EPP: Use level IRQ           */
DECL|macro|PTR_LPT_REG_DIR
mdefine_line|#define PTR_LPT_REG_DIR&t;0x80&t;/* When ECP/EPP: LPT CTR controlls direction */
multiline_comment|/*               of the parallel port&t;     */
multiline_comment|/* Function Control Register (FCR) bits */
DECL|macro|FCR_ZWS_ENA
mdefine_line|#define FCR_ZWS_ENA&t;0x20&t;/* Enable short host read/write in ECP/EPP   */
multiline_comment|/* Printer Controll Register (PCR) bits */
DECL|macro|PCR_EPP_ENABLE
mdefine_line|#define PCR_EPP_ENABLE&t;0x01
DECL|macro|PCR_EPP_IEEE
mdefine_line|#define PCR_EPP_IEEE&t;0x02&t;/* Enable EPP Version 1.9 (IEEE 1284)        */
DECL|macro|PCR_ECP_ENABLE
mdefine_line|#define PCR_ECP_ENABLE&t;0x04
DECL|macro|PCR_ECP_CLK_ENA
mdefine_line|#define PCR_ECP_CLK_ENA&t;0x08&t;/* If 0 ECP Clock is stopped on Power down   */
DECL|macro|PCR_IRQ_POLAR
mdefine_line|#define PCR_IRQ_POLAR&t;0x20&t;/* If 0 IRQ is level high or negative pulse, */
multiline_comment|/* if 1 polarity is inverted                 */
DECL|macro|PCR_IRQ_ODRAIN
mdefine_line|#define PCR_IRQ_ODRAIN&t;0x40&t;/* If 1, IRQ is open drain                   */
multiline_comment|/* Tape UARTs and Parallel Port Config Register (TUP) bits */
DECL|macro|TUP_EPP_TIMO
mdefine_line|#define TUP_EPP_TIMO&t;0x02&t;/* Enable EPP timeout IRQ                    */
multiline_comment|/* Advanced SuperIO Config Register (ASC) bits */
DECL|macro|ASC_LPT_IRQ7
mdefine_line|#define ASC_LPT_IRQ7&t;0x01&t;/* Allways use IRQ7 for LPT                  */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|ns87303_writeb
r_static
id|__inline__
r_void
id|ns87303_writeb
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|index
comma
r_int
r_char
id|value
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|index
comma
id|port
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|port
op_plus
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|value
comma
id|port
op_plus
l_int|1
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|ns87303_readb
r_static
id|__inline__
r_int
r_char
id|ns87303_readb
c_func
(paren
r_int
r_int
id|port
comma
r_int
id|index
)paren
(brace
id|outb
c_func
(paren
id|index
comma
id|port
)paren
suffix:semicolon
r_return
id|inb
c_func
(paren
id|port
op_plus
l_int|1
)paren
suffix:semicolon
)brace
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !(_SPARC_NS87303_H) */
eof
