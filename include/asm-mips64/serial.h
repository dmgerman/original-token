multiline_comment|/* $Id: serial.h,v 1.2 2000/01/17 23:32:47 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1999 by Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SERIAL_H
DECL|macro|_ASM_SERIAL_H
mdefine_line|#define _ASM_SERIAL_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/sn/sn0/ip27.h&gt;
multiline_comment|/*&n; * This assumes you have a 1.8432 MHz clock for your UART.&n; *&n; * It&squot;d be nice if someone built a serial card with a 24.576 MHz&n; * clock, since the 16550A is capable of handling a top speed of 1.5&n; * megabits/second; but this requires the faster clock.&n; */
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
multiline_comment|/* Standard COM flags (except for COM4, because of the 8514 problem) */
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST)
multiline_comment|/*&n; * The IOC3 serials use a 22MHz clock rate with an additional divider by 3.&n; */
DECL|macro|IOC3_BAUD
mdefine_line|#define IOC3_BAUD (22000000 / (3*16))
DECL|macro|IOC3_COM_FLAGS
mdefine_line|#define IOC3_COM_FLAGS (ASYNC_BOOT_AUTOCONF | ASYNC_SKIP_TEST | ASYNC_IOC3)
multiline_comment|/* Let the compiler figure out the size.  */
DECL|macro|RS_TABLE_SIZE
mdefine_line|#define RS_TABLE_SIZE
macro_line|#ifdef CONFIG_SGI_IP27
DECL|macro|_ORIGIN_SERIAL_INIT
mdefine_line|#define _ORIGIN_SERIAL_INIT(int, base)&t;&t;&t;&t;&t;&bslash;&n;&t;{ baud_base: IOC3_BAUD, irq: int, flags: IOC3_COM_FLAGS,&t;&bslash;&n;&t;  iomem_base: (u8 *) base, iomem_reg_shift: 0,&t;&t;&t;&bslash;&n;&t;  io_type: SERIAL_IO_MEM }
DECL|macro|ORIGIN_SERIAL_PORT_DFNS
mdefine_line|#define ORIGIN_SERIAL_PORT_DFNS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;_ORIGIN_SERIAL_INIT(0, 0x9200000008620178UL),&t;&t;&t;&bslash;&n;&t;_ORIGIN_SERIAL_INIT(0, 0x9200000008620170UL),
macro_line|#else
DECL|macro|ORIGIN_SERIAL_PORT_DFNS
mdefine_line|#define ORIGIN_SERIAL_PORT_DFNS
macro_line|#endif
DECL|macro|SERIAL_PORT_DFNS
mdefine_line|#define SERIAL_PORT_DFNS&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ORIGIN_SERIAL_PORT_DFNS
macro_line|#endif /* _ASM_SERIAL_H */
eof
