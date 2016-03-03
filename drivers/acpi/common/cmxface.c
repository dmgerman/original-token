multiline_comment|/******************************************************************************&n; *&n; * Module Name: cmxface - External interfaces for &quot;global&quot; ACPI functions&n; *              $Revision: 43 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acdebug.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          MISCELLANEOUS
id|MODULE_NAME
(paren
l_string|&quot;cmxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_initialize&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Initializes all global variables.  This is the first function&n; *              called, so any early initialization belongs here.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_initialize
id|acpi_initialize
(paren
id|ACPI_INIT_DATA
op_star
id|init_data
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/* Initialize all globals used by the subsystem */
id|acpi_cm_init_globals
(paren
id|init_data
)paren
suffix:semicolon
multiline_comment|/* Initialize the OS-Dependent layer */
id|status
op_assign
id|acpi_os_initialize
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|REPORT_ERROR
(paren
l_string|&quot;OSD Initialization Failure&quot;
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Create the default mutex objects */
id|status
op_assign
id|acpi_cm_mutex_initialize
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|REPORT_ERROR
(paren
l_string|&quot;Global Mutex Initialization Failure&quot;
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* If configured, initialize the AML debugger */
id|DEBUGGER_EXEC
(paren
id|acpi_db_initialize
(paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_terminate&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Shutdown the ACPI subsystem.  Release all resources.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_terminate
id|acpi_terminate
(paren
r_void
)paren
(brace
multiline_comment|/* Terminate the AML Debuger if present */
id|acpi_gbl_db_terminate_threads
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* TBD: [Investigate] This is no longer needed?*/
multiline_comment|/*    Acpi_cm_release_mutex (ACPI_MTX_DEBUG_CMD_READY); */
multiline_comment|/* Shutdown and free all resources */
id|acpi_cm_subsystem_shutdown
(paren
)paren
suffix:semicolon
multiline_comment|/* Free the mutex objects */
id|acpi_cm_mutex_terminate
(paren
)paren
suffix:semicolon
multiline_comment|/* Now we can shutdown the OS-dependent layer */
id|acpi_os_terminate
(paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_system_info&n; *&n; * PARAMETERS:  Out_buffer      - a pointer to a buffer to receive the&n; *                                resources for the device&n; *              Buffer_length   - the number of bytes available in the buffer&n; *&n; * RETURN:      Status          - the status of the call&n; *&n; * DESCRIPTION: This function is called to get information about the current&n; *              state of the ACPI subsystem.  It will return system information&n; *              in the Out_buffer.&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the value of Out_buffer is undefined.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_get_system_info
id|acpi_get_system_info
(paren
id|ACPI_BUFFER
op_star
id|out_buffer
)paren
(brace
id|ACPI_SYSTEM_INFO
op_star
id|info_ptr
suffix:semicolon
id|u32
id|i
suffix:semicolon
multiline_comment|/*&n;&t; *  Must have a valid buffer&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|out_buffer
)paren
op_logical_or
(paren
op_logical_neg
id|out_buffer-&gt;pointer
)paren
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|out_buffer-&gt;length
OL
r_sizeof
(paren
id|ACPI_SYSTEM_INFO
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *  Caller&squot;s buffer is too small&n;&t;&t; */
id|out_buffer-&gt;length
op_assign
r_sizeof
(paren
id|ACPI_SYSTEM_INFO
)paren
suffix:semicolon
r_return
(paren
id|AE_BUFFER_OVERFLOW
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Set return length and get data&n;&t; */
id|out_buffer-&gt;length
op_assign
r_sizeof
(paren
id|ACPI_SYSTEM_INFO
)paren
suffix:semicolon
id|info_ptr
op_assign
(paren
id|ACPI_SYSTEM_INFO
op_star
)paren
id|out_buffer-&gt;pointer
suffix:semicolon
multiline_comment|/* TBD [Future]: need a version number, or use the version string */
id|info_ptr-&gt;acpi_ca_version
op_assign
l_int|0x1234
suffix:semicolon
multiline_comment|/* System flags (ACPI capabilities) */
id|info_ptr-&gt;flags
op_assign
id|acpi_gbl_system_flags
suffix:semicolon
multiline_comment|/* Timer resolution - 24 or 32 bits  */
id|info_ptr-&gt;timer_resolution
op_assign
id|acpi_hw_pmt_resolution
(paren
)paren
suffix:semicolon
multiline_comment|/* Clear the reserved fields */
id|info_ptr-&gt;reserved1
op_assign
l_int|0
suffix:semicolon
id|info_ptr-&gt;reserved2
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Current debug levels */
id|info_ptr-&gt;debug_layer
op_assign
id|acpi_dbg_layer
suffix:semicolon
id|info_ptr-&gt;debug_level
op_assign
id|acpi_dbg_level
suffix:semicolon
multiline_comment|/* Current status of the ACPI tables, per table type */
id|info_ptr-&gt;num_table_types
op_assign
id|NUM_ACPI_TABLES
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|NUM_ACPI_TABLES
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
(brace
id|info_ptr-&gt;table_info
(braket
id|i
)braket
dot
id|count
op_assign
id|acpi_gbl_acpi_tables
(braket
id|i
)braket
dot
id|count
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_format_exception&n; *&n; * PARAMETERS:  Out_buffer      - a pointer to a buffer to receive the&n; *                                exception name&n; *&n; * RETURN:      Status          - the status of the call&n; *&n; * DESCRIPTION: This function translates an ACPI exception into an ASCII string.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_format_exception
id|acpi_format_exception
(paren
id|ACPI_STATUS
id|exception
comma
id|ACPI_BUFFER
op_star
id|out_buffer
)paren
(brace
id|u32
id|length
suffix:semicolon
id|NATIVE_CHAR
op_star
id|formatted_exception
suffix:semicolon
multiline_comment|/*&n;&t; *  Must have a valid buffer&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|out_buffer
)paren
op_logical_or
(paren
op_logical_neg
id|out_buffer-&gt;pointer
)paren
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert the exception code (Handles bad exception codes) */
id|formatted_exception
op_assign
id|acpi_cm_format_exception
(paren
id|exception
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get length of string and check if it will fit in caller&squot;s buffer&n;&t; */
id|length
op_assign
id|STRLEN
(paren
id|formatted_exception
)paren
suffix:semicolon
r_if
c_cond
(paren
id|out_buffer-&gt;length
OL
id|length
)paren
(brace
id|out_buffer-&gt;length
op_assign
id|length
suffix:semicolon
r_return
(paren
id|AE_BUFFER_OVERFLOW
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the string, all done */
id|STRCPY
(paren
id|out_buffer-&gt;pointer
comma
id|formatted_exception
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
