multiline_comment|/*&n; * Export MIPS-specific functions needed for loadable modules.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1996, 1997 by Ralf Baechle&n; *&n; * $Id: mips_ksyms.c,v 1.2 1997/08/08 18:12:26 miguel Exp $&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/in6.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/floppy.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/sgihpc.h&gt;
macro_line|#include &lt;asm/softirq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|EISA_bus
id|EXPORT_SYMBOL
c_func
(paren
id|EISA_bus
)paren
suffix:semicolon
multiline_comment|/*&n; * String functions&n; */
DECL|variable|bcopy
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|bcopy
)paren
suffix:semicolon
DECL|variable|memcmp
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|memcmp
)paren
suffix:semicolon
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
DECL|variable|strcat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strcat
)paren
suffix:semicolon
DECL|variable|strchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strchr
)paren
suffix:semicolon
DECL|variable|strlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strlen
)paren
suffix:semicolon
DECL|variable|strncat
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strncat
)paren
suffix:semicolon
DECL|variable|strnlen
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strnlen
)paren
suffix:semicolon
DECL|variable|strrchr
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strrchr
)paren
suffix:semicolon
DECL|variable|strtok
id|EXPORT_SYMBOL_NOVERS
c_func
(paren
id|strtok
)paren
suffix:semicolon
DECL|variable|clear_page
id|EXPORT_SYMBOL
c_func
(paren
id|clear_page
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
multiline_comment|/*&n; * Userspace access stuff.&n; */
DECL|variable|__copy_user
id|EXPORT_SYMBOL
c_func
(paren
id|__copy_user
)paren
suffix:semicolon
DECL|variable|active_ds
id|EXPORT_SYMBOL
c_func
(paren
id|active_ds
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
DECL|variable|flush_page_to_ram
id|EXPORT_SYMBOL
c_func
(paren
id|flush_page_to_ram
)paren
suffix:semicolon
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
macro_line|#ifdef CONFIG_SGI
DECL|variable|hpc3c0
id|EXPORT_SYMBOL
c_func
(paren
id|hpc3c0
)paren
suffix:semicolon
macro_line|#endif
eof
