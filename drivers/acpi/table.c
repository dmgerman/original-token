multiline_comment|/*&n; *  table.c - ACPI tables, chipset, and errata handling&n; *&n; *  Copyright (C) 2000 Andrew Henroid&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;driver.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;OS_DEPENDENT
id|MODULE_NAME
(paren
l_string|&quot;table&quot;
)paren
DECL|variable|acpi_fadt
id|FADT_DESCRIPTOR
id|acpi_fadt
suffix:semicolon
multiline_comment|/*&n; * Fetch the fadt information&n; */
r_static
r_int
DECL|function|acpi_fetch_fadt
id|acpi_fetch_fadt
c_func
(paren
r_void
)paren
(brace
id|ACPI_BUFFER
id|buffer
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|acpi_fadt
comma
l_int|0
comma
r_sizeof
(paren
id|acpi_fadt
)paren
)paren
suffix:semicolon
id|buffer.pointer
op_assign
op_amp
id|acpi_fadt
suffix:semicolon
id|buffer.length
op_assign
r_sizeof
(paren
id|acpi_fadt
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ACPI_SUCCESS
c_func
(paren
id|acpi_get_table
c_func
(paren
id|ACPI_TABLE_FADT
comma
l_int|1
comma
op_amp
id|buffer
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ACPI: missing fadt&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_fadt.plvl2_lat
op_logical_and
id|acpi_fadt.plvl2_lat
op_le
id|ACPI_MAX_P_LVL2_LAT
)paren
(brace
id|acpi_c2_exit_latency
op_assign
id|ACPI_MICROSEC_TO_TMR_TICKS
c_func
(paren
id|acpi_fadt.plvl2_lat
)paren
suffix:semicolon
id|acpi_c2_enter_latency
op_assign
id|ACPI_MICROSEC_TO_TMR_TICKS
c_func
(paren
id|ACPI_TMR_HZ
op_div
l_int|1000
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_fadt.plvl3_lat
op_logical_and
id|acpi_fadt.plvl3_lat
op_le
id|ACPI_MAX_P_LVL3_LAT
)paren
(brace
id|acpi_c3_exit_latency
op_assign
id|ACPI_MICROSEC_TO_TMR_TICKS
c_func
(paren
id|acpi_fadt.plvl3_lat
)paren
suffix:semicolon
id|acpi_c3_enter_latency
op_assign
id|ACPI_MICROSEC_TO_TMR_TICKS
c_func
(paren
id|acpi_fadt.plvl3_lat
op_star
l_int|5
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find and load ACPI tables&n; */
r_int
DECL|function|acpi_find_and_load_tables
id|acpi_find_and_load_tables
c_func
(paren
id|u64
id|rsdp
)paren
(brace
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|acpi_load_tables
c_func
(paren
id|rsdp
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: System description tables loaded&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ACPI: System description table load failed&bslash;n&quot;
)paren
suffix:semicolon
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_fetch_fadt
c_func
(paren
)paren
)paren
(brace
id|acpi_terminate
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
