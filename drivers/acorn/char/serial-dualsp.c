multiline_comment|/*&n; * linux/arch/arm/drivers/char/serial-dualsp.c&n; *&n; * Copyright (c) 1996 Russell King.&n; *&n; * Changelog:&n; *  30-07-1996&t;RMK&t;Created&n; */
DECL|macro|MY_CARD_LIST
mdefine_line|#define MY_CARD_LIST { MANU_SERPORT, PROD_SERPORT_DSPORT }
DECL|macro|MY_NUMPORTS
mdefine_line|#define MY_NUMPORTS 2
DECL|macro|MY_BAUD_BASE
mdefine_line|#define MY_BAUD_BASE (3686400 / 16)
DECL|macro|MY_INIT
mdefine_line|#define MY_INIT dualsp_serial_init
DECL|macro|MY_BASE_ADDRESS
mdefine_line|#define MY_BASE_ADDRESS(ec) &bslash;&n;&t;ecard_address (ec, ECARD_IOC, ECARD_SLOW) + (0x2000 &gt;&gt; 2)
DECL|macro|MY_PORT_ADDRESS
mdefine_line|#define MY_PORT_ADDRESS(port,cardaddress) &bslash;&n;&t;((cardaddress) + (port) * 8)
macro_line|#include &quot;serial-card.c&quot;
eof