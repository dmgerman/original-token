multiline_comment|/*&n; * linux/include/asm-arm/arch-arc/serial.h&n; *&n; * Copyright (c) 1996 Russell King.&n; *&n; * Changelog:&n; *  15-10-1996&t;RMK&t;Created&n; *  04-04-1998&t;PJB&t;Merged `arc&squot; and `a5k&squot; architectures&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE&t;16
macro_line|#if defined(CONFIG_ARCH_A5K)
multiline_comment|/* UART CLK        PORT  IRQ     FLAGS        */
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
(brace
l_int|0
comma
id|BASE_BAUD
comma
l_int|0x3F8
comma
l_int|10
comma
id|STD_COM_FLAGS
)brace
comma
multiline_comment|/* ttyS0 */
"&bslash;"
(brace
l_int|0
comma
id|BASE_BAUD
comma
l_int|0x2F8
comma
l_int|10
comma
id|STD_COM_FLAGS
)brace
comma
multiline_comment|/* ttyS1 */
macro_line|#else
DECL|macro|STD_SERIAL_PORT_DEFNS
mdefine_line|#define STD_SERIAL_PORT_DEFNS
(brace
l_int|0
comma
id|BASE_BAUD
comma
l_int|0
comma
l_int|0
comma
id|STD_COM_FLAGS
)brace
comma
multiline_comment|/* ttyS0 */
"&bslash;"
(brace
l_int|0
comma
id|BASE_BAUD
comma
l_int|0
comma
l_int|0
comma
id|STD_COM_FLAGS
)brace
comma
multiline_comment|/* ttyS1 */
macro_line|#endif
DECL|macro|EXTRA_SERIAL_PORT_DEFNS
mdefine_line|#define EXTRA_SERIAL_PORT_DEFNS &bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS3 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS }, &t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS8 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS9 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS10 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS11 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS12 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS13 */
macro_line|#endif
eof
