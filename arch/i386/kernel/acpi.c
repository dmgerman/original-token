multiline_comment|/*&n; *  acpi.c - Linux ACPI arch-specific functions&n; *&n; *  Copyright (C) 1999-2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Changes:&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 2000/08/31&n; * - check copy*user return&n; * - get rid of check_region&n; * - get rid of verify_area&n; * Arnaldo Carvalho de Melo &lt;acme@conectiva.com.br&gt; - 2000/09/28&n; * - do proper release on failure in acpi_claim_ioports and acpi_init&n; * Andrew Grover &lt;andrew.grover@intel.com&gt; - 2000/11/13&n; * - Took out support for user-level interpreter. ACPI 2.0 changes preclude&n; *   its maintenance.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
DECL|macro|_LINUX
mdefine_line|#define _LINUX
macro_line|#include &lt;linux/acpi.h&gt;
multiline_comment|/* Is there a better way to include this? */
macro_line|#include &lt;../drivers/acpi/include/acpi.h&gt;
id|ACPI_PHYSICAL_ADDRESS
DECL|function|acpi_get_rsdp_ptr
id|acpi_get_rsdp_ptr
c_func
(paren
)paren
(brace
id|ACPI_PHYSICAL_ADDRESS
id|rsdp_phys
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|acpi_find_root_pointer
c_func
(paren
op_amp
id|rsdp_phys
)paren
)paren
)paren
(brace
r_return
id|rsdp_phys
suffix:semicolon
)brace
r_else
r_return
l_int|0
suffix:semicolon
)brace
eof
