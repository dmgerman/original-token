multiline_comment|/*&n; * Export MIPS-specific functions needed for loadable modules.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996 by Ralf Baechle&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/floppy.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
DECL|variable|EISA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|EISA_bus
)paren
suffix:semicolon
multiline_comment|/*&n; * String functions&n; */
DECL|variable|memset
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memset
)paren
suffix:semicolon
DECL|variable|memcpy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcpy
)paren
suffix:semicolon
DECL|variable|memmove
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memmove
)paren
suffix:semicolon
DECL|variable|bcopy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|bcopy
)paren
suffix:semicolon
DECL|variable|__mips_bh_counter
id|EXPORT_SYMBOL
c_func
(paren
id|__mips_bh_counter
)paren
suffix:semicolon
DECL|variable|local_irq_count
id|EXPORT_SYMBOL
c_func
(paren
id|local_irq_count
)paren
suffix:semicolon
multiline_comment|/* Networking helper routines. */
DECL|variable|csum_partial_copy
id|EXPORT_SYMBOL
c_func
(paren
id|csum_partial_copy
)paren
suffix:semicolon
multiline_comment|/*&n; * Functions to control caches.&n; */
DECL|variable|fd_cacheflush
id|EXPORT_SYMBOL
c_func
(paren
id|fd_cacheflush
)paren
suffix:semicolon
multiline_comment|/*&n; * Base address of ports for Intel style I/O.&n; */
DECL|variable|port_base
id|EXPORT_SYMBOL
c_func
(paren
id|port_base
)paren
suffix:semicolon
eof
