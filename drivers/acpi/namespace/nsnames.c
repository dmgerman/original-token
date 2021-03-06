multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsnames - Name manipulation and search&n; *              $Revision: 51 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          NAMESPACE
id|MODULE_NAME
(paren
l_string|&quot;nsnames&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_get_table_pathname&n; *&n; * PARAMETERS:  Node        - Scope whose name is needed&n; *&n; * RETURN:      Pointer to storage containing the fully qualified name of&n; *              the scope, in Label format (all segments strung together&n; *              with no separators)&n; *&n; * DESCRIPTION: Used for debug printing in Acpi_ns_search_table().&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_ns_get_table_pathname
id|acpi_ns_get_table_pathname
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|node
)paren
(brace
id|NATIVE_CHAR
op_star
id|name_buffer
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|ACPI_NAME
id|name
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_root_node
op_logical_or
op_logical_neg
id|node
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the name space has not been initialized,&n;&t;&t; * this function should not have been called.&n;&t;&t; */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|child_node
op_assign
id|node-&gt;child
suffix:semicolon
multiline_comment|/* Calculate required buffer size based on depth below root */
id|size
op_assign
l_int|1
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
r_while
c_loop
(paren
id|parent_node
)paren
(brace
id|parent_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|parent_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parent_node
)paren
(brace
id|size
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
)brace
)brace
multiline_comment|/* Allocate a buffer to be returned to caller */
id|name_buffer
op_assign
id|acpi_cm_callocate
(paren
id|size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_buffer
)paren
(brace
id|REPORT_ERROR
(paren
(paren
l_string|&quot;Ns_get_table_pathname: allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Store terminator byte, then build name backwards */
id|name_buffer
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
id|size
OG
id|ACPI_NAME_SIZE
)paren
op_logical_and
id|acpi_ns_get_parent_object
(paren
id|child_node
)paren
)paren
(brace
id|size
op_sub_assign
id|ACPI_NAME_SIZE
suffix:semicolon
id|name
op_assign
id|acpi_ns_find_parent_name
(paren
id|child_node
)paren
suffix:semicolon
multiline_comment|/* Put the name into the buffer */
id|MOVE_UNALIGNED32_TO_32
(paren
(paren
id|name_buffer
op_plus
id|size
)paren
comma
op_amp
id|name
)paren
suffix:semicolon
id|child_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|child_node
)paren
suffix:semicolon
)brace
id|name_buffer
(braket
op_decrement
id|size
)braket
op_assign
id|AML_ROOT_PREFIX
suffix:semicolon
r_return
(paren
id|name_buffer
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_handle_to_pathname&n; *&n; * PARAMETERS:  Target_handle           - Handle of named object whose name is&n; *                                        to be found&n; *              Buf_size                - Size of the buffer provided&n; *              User_buffer             - Where the pathname is returned&n; *&n; * RETURN:      Status, Buffer is filled with pathname if status is AE_OK&n; *&n; * DESCRIPTION: Build and return a full namespace pathname&n; *&n; * MUTEX:       Locks Namespace&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ns_handle_to_pathname
id|acpi_ns_handle_to_pathname
(paren
id|ACPI_HANDLE
id|target_handle
comma
id|u32
op_star
id|buf_size
comma
id|NATIVE_CHAR
op_star
id|user_buffer
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|next_node
suffix:semicolon
id|u32
id|path_length
suffix:semicolon
id|u32
id|size
suffix:semicolon
id|u32
id|user_buf_size
suffix:semicolon
id|ACPI_NAME
id|name
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_root_node
op_logical_or
op_logical_neg
id|target_handle
)paren
(brace
multiline_comment|/*&n;&t;&t; * If the name space has not been initialized,&n;&t;&t; * this function should not have been called.&n;&t;&t; */
r_return
(paren
id|AE_NO_NAMESPACE
)paren
suffix:semicolon
)brace
id|node
op_assign
id|acpi_ns_convert_handle_to_entry
(paren
id|target_handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Compute length of pathname as 5 * number of name segments.&n;&t; * Go back up the parent tree to the root&n;&t; */
r_for
c_loop
(paren
id|size
op_assign
l_int|0
comma
id|next_node
op_assign
id|node
suffix:semicolon
id|acpi_ns_get_parent_object
(paren
id|next_node
)paren
suffix:semicolon
id|next_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|next_node
)paren
)paren
(brace
id|size
op_add_assign
id|PATH_SEGMENT_LENGTH
suffix:semicolon
)brace
multiline_comment|/* Special case for size still 0 - no parent for &quot;special&quot; nodes */
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|size
op_assign
id|PATH_SEGMENT_LENGTH
suffix:semicolon
)brace
multiline_comment|/* Set return length to the required path length */
id|path_length
op_assign
id|size
op_plus
l_int|1
suffix:semicolon
id|user_buf_size
op_assign
op_star
id|buf_size
suffix:semicolon
op_star
id|buf_size
op_assign
id|path_length
suffix:semicolon
multiline_comment|/* Check if the user buffer is sufficiently large */
r_if
c_cond
(paren
id|path_length
OG
id|user_buf_size
)paren
(brace
id|status
op_assign
id|AE_BUFFER_OVERFLOW
suffix:semicolon
r_goto
m_exit
suffix:semicolon
)brace
multiline_comment|/* Store null terminator */
id|user_buffer
(braket
id|size
)braket
op_assign
l_int|0
suffix:semicolon
id|size
op_sub_assign
id|ACPI_NAME_SIZE
suffix:semicolon
multiline_comment|/* Put the original ACPI name at the end of the path */
id|MOVE_UNALIGNED32_TO_32
(paren
(paren
id|user_buffer
op_plus
id|size
)paren
comma
op_amp
id|node-&gt;name
)paren
suffix:semicolon
id|user_buffer
(braket
op_decrement
id|size
)braket
op_assign
id|PATH_SEPARATOR
suffix:semicolon
multiline_comment|/* Build name backwards, putting &quot;.&quot; between segments */
r_while
c_loop
(paren
(paren
id|size
OG
id|ACPI_NAME_SIZE
)paren
op_logical_and
id|node
)paren
(brace
id|size
op_sub_assign
id|ACPI_NAME_SIZE
suffix:semicolon
id|name
op_assign
id|acpi_ns_find_parent_name
(paren
id|node
)paren
suffix:semicolon
id|MOVE_UNALIGNED32_TO_32
(paren
(paren
id|user_buffer
op_plus
id|size
)paren
comma
op_amp
id|name
)paren
suffix:semicolon
id|user_buffer
(braket
op_decrement
id|size
)braket
op_assign
id|PATH_SEPARATOR
suffix:semicolon
id|node
op_assign
id|acpi_ns_get_parent_object
(paren
id|node
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Overlay the &quot;.&quot; preceding the first segment with&n;&t; * the root name &quot;&bslash;&quot;&n;&t; */
id|user_buffer
(braket
id|size
)braket
op_assign
l_char|&squot;&bslash;&bslash;&squot;
suffix:semicolon
m_exit
suffix:colon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
