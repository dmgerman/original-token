multiline_comment|/* atm_suni.h - Driver-specific declarations of the SUNI driver (for use by&n;&t;&t;driver-specific utilities) */
multiline_comment|/* Written 1998 by Werner Almesberger, EPFL ICA */
macro_line|#ifndef LINUX_ATM_SUNI_H
DECL|macro|LINUX_ATM_SUNI_H
mdefine_line|#define LINUX_ATM_SUNI_H
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|SUNI_GETLOOP
mdefine_line|#define SUNI_GETLOOP&t;_IOR(&squot;a&squot;,ATMIOC_PHYPRV,int)&t;/* get loopback mode */
DECL|macro|SUNI_SETLOOP
mdefine_line|#define SUNI_SETLOOP&t;_IO(&squot;a&squot;,ATMIOC_PHYPRV+1)&t;/* set loopback mode */
DECL|macro|SUNI_LM_NONE
mdefine_line|#define SUNI_LM_NONE&t;0&t;/* no loopback */
DECL|macro|SUNI_LM_DIAG
mdefine_line|#define SUNI_LM_DIAG&t;1&t;/* diagnostic (i.e. loop TX to RX) */
DECL|macro|SUNI_LM_LOOP
mdefine_line|#define SUNI_LM_LOOP&t;2&t;/* line (i.e. loop RX to TX) */
macro_line|#endif
eof
