multiline_comment|/* atm_eni.h - Driver-specific declarations of the ENI driver (for use by&n;&t;       driver-specific utilities) */
multiline_comment|/* Written 1995-1997 by Werner Almesberger, EPFL LRC */
macro_line|#ifndef LINUX_ATM_ENI_H
DECL|macro|LINUX_ATM_ENI_H
mdefine_line|#define LINUX_ATM_ENI_H
macro_line|#include &lt;linux/atmioc.h&gt;
DECL|macro|ENI_MEMDUMP
mdefine_line|#define ENI_MEMDUMP     _IOW(&squot;a&squot;,ATMIOC_SARPRV,struct atmif_sioc)
multiline_comment|/* printk memory map */
macro_line|#endif
eof
