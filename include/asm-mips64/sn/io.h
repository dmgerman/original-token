multiline_comment|/* $Id: io.h,v 1.1 2000/02/04 07:40:53 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_SN_IO_H
DECL|macro|_ASM_SN_IO_H
mdefine_line|#define _ASM_SN_IO_H
macro_line|#include &lt;asm/sn/sn0/addrs.h&gt;
DECL|macro|IO_SPACE_BASE
mdefine_line|#define IO_SPACE_BASE IO_BASE
multiline_comment|/* Because we only have PCI I/O ports.  */
DECL|macro|IO_SPACE_LIMIT
mdefine_line|#define IO_SPACE_LIMIT 0xffffffff
multiline_comment|/* No isa_* versions, the Origin doesn&squot;t have ISA / EISA bridges.  */
macro_line|#endif /* _ASM_SN_IO_H */
eof
