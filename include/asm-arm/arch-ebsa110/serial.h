multiline_comment|/*&n; * linux/include/asm-arm/arch-ebsa110/serial.h&n; *&n; * Copyright (c) 1996,1997,1998 Russell King.&n; *&n; * Changelog:&n; *  15-10-1996&t;RMK&t;Created&n; */
macro_line|#ifndef __ASM_ARCH_SERIAL_H
DECL|macro|__ASM_ARCH_SERIAL_H
mdefine_line|#define __ASM_ARCH_SERIAL_H
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/* UART CLK        PORT  IRQ     FLAGS        */
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS &bslash;&n;&t;{ 0, BASE_BAUD, 0x3F8,  1, STD_COM_FLAGS },&t;/* ttyS0 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0x2F8,  2, STD_COM_FLAGS },&t;/* ttyS1 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS2 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS3 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS }, &t;/* ttyS4 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS5 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS6 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS7 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS8 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS9 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS10 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS11 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS12 */&t;&bslash;&n;&t;{ 0, BASE_BAUD, 0    ,  0, STD_COM_FLAGS },&t;/* ttyS13 */
macro_line|#endif
eof
