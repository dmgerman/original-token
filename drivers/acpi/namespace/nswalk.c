multiline_comment|/******************************************************************************&n; *&n; * Module Name: nswalk - Functions for walking the APCI namespace&n; *              $Revision: 17 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          NAMESPACE
id|MODULE_NAME
(paren
l_string|&quot;nswalk&quot;
)paren
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    Acpi_get_next_object&n; *&n; * PARAMETERS:  Type                - Type of object to be searched for&n; *              Parent              - Parent object whose children we are&n; *                                      getting&n; *              Last_child          - Previous child that was found.&n; *                                    The NEXT child will be returned&n; *&n; * RETURN:      ACPI_NAMESPACE_NODE - Pointer to the NEXT child or NULL if&n; *                                      none is found.&n; *&n; * DESCRIPTION: Return the next peer object within the namespace.  If Handle&n; *              is valid, Scope is ignored.  Otherwise, the first object&n; *              within Scope is returned.&n; *&n; ****************************************************************************/
id|ACPI_NAMESPACE_NODE
op_star
DECL|function|acpi_ns_get_next_object
id|acpi_ns_get_next_object
(paren
id|OBJECT_TYPE_INTERNAL
id|type
comma
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
comma
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|next_node
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_node
)paren
(brace
multiline_comment|/* It&squot;s really the parent&squot;s _scope_ that we want */
r_if
c_cond
(paren
id|parent_node-&gt;child
)paren
(brace
id|next_node
op_assign
id|parent_node-&gt;child
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Start search at the NEXT object */
id|next_node
op_assign
id|acpi_ns_get_next_valid_object
(paren
id|child_node
)paren
suffix:semicolon
)brace
multiline_comment|/* If any type is OK, we are done */
r_if
c_cond
(paren
id|type
op_eq
id|ACPI_TYPE_ANY
)paren
(brace
multiline_comment|/* Next_node is NULL if we are at the end-of-list */
r_return
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Must search for the object -- but within this scope only */
r_while
c_loop
(paren
id|next_node
)paren
(brace
multiline_comment|/* If type matches, we are done */
r_if
c_cond
(paren
id|next_node-&gt;type
op_eq
id|type
)paren
(brace
r_return
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Otherwise, move on to the next object */
id|next_node
op_assign
id|acpi_ns_get_next_valid_object
(paren
id|next_node
)paren
suffix:semicolon
)brace
multiline_comment|/* Not found */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ns_walk_namespace&n; *&n; * PARAMETERS:  Type                - ACPI_OBJECT_TYPE to search for&n; *              Start_node          - Handle in namespace where search begins&n; *              Max_depth           - Depth to which search is to reach&n; *              Unlock_before_callback- Whether to unlock the NS before invoking&n; *                                    the callback routine&n; *              User_function       - Called when an object of &quot;Type&quot; is found&n; *              Context             - Passed to user function&n; *&n; * RETURNS      Return value from the User_function if terminated early.&n; *              Otherwise, returns NULL.&n; *&n; * DESCRIPTION: Performs a modified depth-first walk of the namespace tree,&n; *              starting (and ending) at the object specified by Start_handle.&n; *              The User_function is called whenever an object that matches&n; *              the type parameter is found.  If the user function returns&n; *              a non-zero value, the search is terminated immediately and this&n; *              value is returned to the caller.&n; *&n; *              The point of this procedure is to provide a generic namespace&n; *              walk routine that can be called from multiple places to&n; *              provide multiple services;  the User Function can be tailored&n; *              to each task, whether it is a print function, a compare&n; *              function, etc.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ns_walk_namespace
id|acpi_ns_walk_namespace
(paren
id|OBJECT_TYPE_INTERNAL
id|type
comma
id|ACPI_HANDLE
id|start_node
comma
id|u32
id|max_depth
comma
id|u8
id|unlock_before_callback
comma
id|WALK_CALLBACK
id|user_function
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|child_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|parent_node
suffix:semicolon
id|OBJECT_TYPE_INTERNAL
id|child_type
suffix:semicolon
id|u32
id|level
suffix:semicolon
multiline_comment|/* Special case for the namespace Root Node */
r_if
c_cond
(paren
id|start_node
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
id|start_node
op_assign
id|acpi_gbl_root_node
suffix:semicolon
)brace
multiline_comment|/* Null child means &quot;get first object&quot; */
id|parent_node
op_assign
id|start_node
suffix:semicolon
id|child_node
op_assign
l_int|0
suffix:semicolon
id|child_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|level
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the tree of objects until we bubble back up to where we&n;&t; * started. When Level is zero, the loop is done because we have&n;&t; * bubbled up to (and passed) the original parent handle (Start_entry)&n;&t; */
r_while
c_loop
(paren
id|level
OG
l_int|0
)paren
(brace
multiline_comment|/*&n;&t;&t; * Get the next typed object in this scope.  Null returned&n;&t;&t; * if not found&n;&t;&t; */
id|status
op_assign
id|AE_OK
suffix:semicolon
id|child_node
op_assign
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|parent_node
comma
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|child_node
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Found an object, Get the type if we are not&n;&t;&t;&t; * searching for ANY&n;&t;&t;&t; */
r_if
c_cond
(paren
id|type
op_ne
id|ACPI_TYPE_ANY
)paren
(brace
id|child_type
op_assign
id|child_node-&gt;type
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child_type
op_eq
id|type
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Found a matching object, invoke the user&n;&t;&t;&t;&t; * callback function&n;&t;&t;&t;&t; */
r_if
c_cond
(paren
id|unlock_before_callback
)paren
(brace
id|acpi_cm_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
)brace
id|status
op_assign
id|user_function
(paren
id|child_node
comma
id|level
comma
id|context
comma
id|return_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlock_before_callback
)paren
(brace
id|acpi_cm_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
r_case
id|AE_CTRL_DEPTH
suffix:colon
multiline_comment|/* Just keep going */
r_break
suffix:semicolon
r_case
id|AE_CTRL_TERMINATE
suffix:colon
multiline_comment|/* Exit now, with OK status */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All others are valid exceptions */
r_return
(paren
id|status
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t;&t; * Depth first search:&n;&t;&t;&t; * Attempt to go down another level in the namespace&n;&t;&t;&t; * if we are allowed to.  Don&squot;t go any further if we&n;&t;&t;&t; * have reached the caller specified maximum depth&n;&t;&t;&t; * or if the user function has specified that the&n;&t;&t;&t; * maximum depth has been reached.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|level
OL
id|max_depth
)paren
op_logical_and
(paren
id|status
op_ne
id|AE_CTRL_DEPTH
)paren
)paren
(brace
r_if
c_cond
(paren
id|acpi_ns_get_next_object
(paren
id|ACPI_TYPE_ANY
comma
id|child_node
comma
l_int|0
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * There is at least one child of this&n;&t;&t;&t;&t;&t; * object, visit the object&n;&t;&t;&t;&t;&t; */
id|level
op_increment
suffix:semicolon
id|parent_node
op_assign
id|child_node
suffix:semicolon
id|child_node
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t; * No more children in this object (Acpi_ns_get_next_object&n;&t;&t;&t; * failed), go back upwards in the namespace tree to&n;&t;&t;&t; * the object&squot;s parent.&n;&t;&t;&t; */
id|level
op_decrement
suffix:semicolon
id|child_node
op_assign
id|parent_node
suffix:semicolon
id|parent_node
op_assign
id|acpi_ns_get_parent_object
(paren
id|parent_node
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Complete walk, not terminated by user function */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
