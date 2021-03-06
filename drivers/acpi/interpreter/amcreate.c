multiline_comment|/******************************************************************************&n; *&n; * Module Name: amcreate - Named object creation&n; *              $Revision: 51 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acdispat.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          INTERPRETER
id|MODULE_NAME
(paren
l_string|&quot;amcreate&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_field&n; *&n; * PARAMETERS:  Opcode              - The opcode to be executed&n; *              Operands            - List of operands for the opcode&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute Create_field operators: Create_bit_field_op,&n; *              Create_byte_field_op, Create_word_field_op, Create_dWord_field_op,&n; *              Create_field_op (which define fields in buffers)&n; *&n; * ALLOCATION:  Deletes Create_field_op&squot;s count operand descriptor&n; *&n; *&n; *  ACPI SPECIFICATION REFERENCES:&n; *  Def_create_bit_field := Create_bit_field_op Src_buf Bit_idx   Name_string&n; *  Def_create_byte_field := Create_byte_field_op Src_buf Byte_idx Name_string&n; *  Def_create_dWord_field := Create_dWord_field_op Src_buf Byte_idx Name_string&n; *  Def_create_field    :=  Create_field_op     Src_buf Bit_idx   Num_bits    Name_string&n; *  Def_create_word_field := Create_word_field_op Src_buf Byte_idx Name_string&n; *  Bit_index           :=  Term_arg=&gt;Integer&n; *  Byte_index          :=  Term_arg=&gt;Integer&n; *  Num_bits            :=  Term_arg=&gt;Integer&n; *  Source_buff         :=  Term_arg=&gt;Buffer&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_field
id|acpi_aml_exec_create_field
(paren
id|u8
op_star
id|aml_ptr
comma
id|u32
id|aml_length
comma
id|ACPI_NAMESPACE_NODE
op_star
id|node
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|tmp_desc
suffix:semicolon
multiline_comment|/* Create the region descriptor */
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_FIELD_UNIT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Construct the field object */
id|obj_desc-&gt;field_unit.access
op_assign
(paren
id|u8
)paren
id|ACCESS_ANY_ACC
suffix:semicolon
id|obj_desc-&gt;field_unit.lock_rule
op_assign
(paren
id|u8
)paren
id|GLOCK_NEVER_LOCK
suffix:semicolon
id|obj_desc-&gt;field_unit.update_rule
op_assign
(paren
id|u8
)paren
id|UPDATE_PRESERVE
suffix:semicolon
multiline_comment|/*&n;&t; * Allocate a method object for this field unit&n;&t; */
id|obj_desc-&gt;field_unit.extra
op_assign
id|acpi_cm_create_internal_object
(paren
id|INTERNAL_TYPE_EXTRA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc-&gt;field_unit.extra
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Remember location in AML stream of the field unit&n;&t; * opcode and operands -- since the buffer and index&n;&t; * operands must be evaluated.&n;&t; */
id|obj_desc-&gt;field_unit.extra-&gt;extra.pcode
op_assign
id|aml_ptr
suffix:semicolon
id|obj_desc-&gt;field_unit.extra-&gt;extra.pcode_length
op_assign
id|aml_length
suffix:semicolon
id|obj_desc-&gt;field_unit.node
op_assign
id|node
suffix:semicolon
multiline_comment|/*&n;&t; * This operation is supposed to cause the destination Name to refer&n;&t; * to the defined Field_unit -- it must not store the constructed&n;&t; * Field_unit object (or its current value) in some location that the&n;&t; * Name may already be pointing to.  So, if the Name currently contains&n;&t; * a reference which would cause Acpi_aml_exec_store() to perform an indirect&n;&t; * store rather than setting the value of the Name itself, clobber that&n;&t; * reference before calling Acpi_aml_exec_store().&n;&t; */
multiline_comment|/* Type of Name&squot;s existing value */
r_switch
c_cond
(paren
id|acpi_ns_get_type
(paren
id|node
)paren
)paren
(brace
r_case
id|ACPI_TYPE_FIELD_UNIT
suffix:colon
r_case
id|INTERNAL_TYPE_ALIAS
suffix:colon
r_case
id|INTERNAL_TYPE_BANK_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_DEF_FIELD
suffix:colon
r_case
id|INTERNAL_TYPE_INDEX_FIELD
suffix:colon
id|tmp_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tmp_desc
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * There is an existing object here;  delete it and zero out the&n;&t;&t;&t; * object field within the Node&n;&t;&t;&t; */
id|acpi_cm_remove_reference
(paren
id|tmp_desc
)paren
suffix:semicolon
id|acpi_ns_attach_object
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
id|node
comma
l_int|NULL
comma
id|ACPI_TYPE_ANY
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the type to ANY (or the store below will fail) */
(paren
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
id|node
)paren
op_member_access_from_pointer
id|type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Store constructed field descriptor in result location */
id|status
op_assign
id|acpi_aml_exec_store
(paren
id|obj_desc
comma
(paren
id|ACPI_OPERAND_OBJECT
op_star
)paren
id|node
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the field descriptor was not physically stored (or if a failure&n;&t; * above), we must delete it&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;common.reference_count
op_le
l_int|1
)paren
(brace
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
id|cleanup
suffix:colon
multiline_comment|/* Delete region object and method subobject */
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/* Remove deletes both objects! */
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|obj_desc
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_alias&n; *&n; * PARAMETERS:  Operands            - List of operands for the opcode&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new named alias&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_alias
id|acpi_aml_exec_create_alias
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_NAMESPACE_NODE
op_star
id|source_node
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|alias_node
suffix:semicolon
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/* Get the source/alias operands (both NTEs) */
id|status
op_assign
id|acpi_ds_obj_stack_pop_object
(paren
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
)paren
op_amp
id|source_node
comma
id|walk_state
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Don&squot;t pop it, it gets removed in the calling routine&n;&t; */
id|alias_node
op_assign
id|acpi_ds_obj_stack_get_value
(paren
l_int|0
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* Add an additional reference to the object */
id|acpi_cm_add_reference
(paren
id|source_node-&gt;object
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Attach the original source Node to the new Alias Node.&n;&t; */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|alias_node
comma
id|source_node-&gt;object
comma
id|source_node-&gt;type
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The new alias assumes the type of the source, but it points&n;&t; * to the same object.  The reference count of the object has two&n;&t; * additional references to prevent deletion out from under either the&n;&t; * source or the alias Node&n;&t; */
multiline_comment|/* Since both operands are NTEs, we don&squot;t need to delete them */
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_event&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new event object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_event
id|acpi_aml_exec_create_event
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|BREAKPOINT3
suffix:semicolon
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_EVENT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Create the actual OS semaphore */
multiline_comment|/* TBD: [Investigate] should be created with 0 or 1 units? */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
id|ACPI_NO_UNIT_LIMIT
comma
l_int|1
comma
op_amp
id|obj_desc-&gt;event.semaphore
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
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Attach object to the Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|acpi_ds_obj_stack_get_value
(paren
l_int|0
comma
id|walk_state
)paren
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_EVENT
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
id|acpi_os_delete_semaphore
(paren
id|obj_desc-&gt;event.semaphore
)paren
suffix:semicolon
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|cleanup
suffix:colon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_mutex&n; *&n; * PARAMETERS:  Interpreter_mode    - Current running mode (load1/Load2/Exec)&n; *              Operands            - List of operands for the opcode&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new mutex object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_mutex
id|acpi_aml_exec_create_mutex
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|sync_desc
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
multiline_comment|/* Get the operand */
id|status
op_assign
id|acpi_ds_obj_stack_pop_object
(paren
op_amp
id|sync_desc
comma
id|walk_state
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Attempt to allocate a new object */
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_MUTEX
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Create the actual OS semaphore */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
l_int|1
comma
l_int|1
comma
op_amp
id|obj_desc-&gt;mutex.semaphore
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
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|obj_desc-&gt;mutex.sync_level
op_assign
(paren
id|u8
)paren
id|sync_desc-&gt;number.value
suffix:semicolon
multiline_comment|/* Obj_desc was on the stack top, and the name is below it */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|acpi_ds_obj_stack_get_value
(paren
l_int|0
comma
id|walk_state
)paren
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_MUTEX
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
id|acpi_os_delete_semaphore
(paren
id|obj_desc-&gt;mutex.semaphore
)paren
suffix:semicolon
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|cleanup
suffix:colon
multiline_comment|/* Always delete the operand */
id|acpi_cm_remove_reference
(paren
id|sync_desc
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_region&n; *&n; * PARAMETERS:  Aml_ptr             - Pointer to the region declaration AML&n; *              Aml_length          - Max length of the declaration AML&n; *              Operands            - List of operands for the opcode&n; *              Interpreter_mode    - Load1/Load2/Execute&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new operation region object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_region
id|acpi_aml_exec_create_region
(paren
id|u8
op_star
id|aml_ptr
comma
id|u32
id|aml_length
comma
id|u8
id|region_space
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
multiline_comment|/*&n;&t; * Space ID must be one of the predefined IDs, or in the user-defined&n;&t; * range&n;&t; */
r_if
c_cond
(paren
(paren
id|region_space
op_ge
id|NUM_REGION_TYPES
)paren
op_logical_and
(paren
id|region_space
OL
id|USER_REGION_BEGIN
)paren
)paren
(brace
id|REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid Address_space type %X&bslash;n&quot;
comma
id|region_space
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_AML_INVALID_SPACE_ID
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the Node from the object stack  */
id|node
op_assign
(paren
id|ACPI_NAMESPACE_NODE
op_star
)paren
id|acpi_ds_obj_stack_get_value
(paren
l_int|0
comma
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* Create the region descriptor */
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_REGION
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate a method object for this region.&n;&t; */
id|obj_desc-&gt;region.extra
op_assign
id|acpi_cm_create_internal_object
(paren
id|INTERNAL_TYPE_EXTRA
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc-&gt;region.extra
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Remember location in AML stream of address &amp; length&n;&t; * operands since they need to be evaluated at run time.&n;&t; */
id|obj_desc-&gt;region.extra-&gt;extra.pcode
op_assign
id|aml_ptr
suffix:semicolon
id|obj_desc-&gt;region.extra-&gt;extra.pcode_length
op_assign
id|aml_length
suffix:semicolon
multiline_comment|/* Init the region from the operands */
id|obj_desc-&gt;region.space_id
op_assign
id|region_space
suffix:semicolon
id|obj_desc-&gt;region.address
op_assign
l_int|0
suffix:semicolon
id|obj_desc-&gt;region.length
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Install the new region object in the parent Node */
id|obj_desc-&gt;region.node
op_assign
id|node
suffix:semicolon
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_REGION
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
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we have a valid region, initialize it&n;&t; * Namespace is NOT locked at this point.&n;&t; */
id|status
op_assign
id|acpi_ev_initialize_region
(paren
id|obj_desc
comma
id|FALSE
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
multiline_comment|/*&n;&t;&t; *  If AE_NOT_EXIST is returned, it is not fatal&n;&t;&t; *  because many regions get created before a handler&n;&t;&t; *  is installed for said region.&n;&t;&t; */
r_if
c_cond
(paren
id|AE_NOT_EXIST
op_eq
id|status
)paren
(brace
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
)brace
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Delete region object and method subobject */
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/* Remove deletes both objects! */
id|acpi_cm_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|obj_desc
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_processor&n; *&n; * PARAMETERS:  Op              - Op containing the Processor definition and&n; *                                args&n; *              Processor_nTE   - Node for the containing Node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new processor object and populate the fields&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_processor
id|acpi_aml_exec_create_processor
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_HANDLE
id|processor_nTE
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|arg
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_PROCESSOR
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new processor object in the parent Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|processor_nTE
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_PROCESSOR
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
r_return
id|status
suffix:semicolon
)brace
id|arg
op_assign
id|op-&gt;value.arg
suffix:semicolon
multiline_comment|/* check existence */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* First arg is the Processor ID */
id|obj_desc-&gt;processor.proc_id
op_assign
(paren
id|u8
)paren
id|arg-&gt;value.integer
suffix:semicolon
multiline_comment|/* Move to next arg and check existence */
id|arg
op_assign
id|arg-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Second arg is the PBlock Address */
id|obj_desc-&gt;processor.address
op_assign
(paren
id|ACPI_IO_ADDRESS
)paren
id|arg-&gt;value.integer
suffix:semicolon
multiline_comment|/* Move to next arg and check existence */
id|arg
op_assign
id|arg-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Third arg is the PBlock Length */
id|obj_desc-&gt;processor.length
op_assign
(paren
id|u8
)paren
id|arg-&gt;value.integer
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_power_resource&n; *&n; * PARAMETERS:  Op              - Op containing the Power_resource definition&n; *                                and args&n; *              Power_res_nTE   - Node for the containing Node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new Power_resource object and populate the fields&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_power_resource
id|acpi_aml_exec_create_power_resource
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_HANDLE
id|power_res_nTE
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|arg
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_POWER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Install the new power resource object in the parent Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|power_res_nTE
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_POWER
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
r_return
id|status
suffix:semicolon
)brace
id|arg
op_assign
id|op-&gt;value.arg
suffix:semicolon
multiline_comment|/* check existence */
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* First arg is the System_level */
id|obj_desc-&gt;power_resource.system_level
op_assign
(paren
id|u8
)paren
id|arg-&gt;value.integer
suffix:semicolon
multiline_comment|/* Move to next arg and check existence */
id|arg
op_assign
id|arg-&gt;next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|status
op_assign
id|AE_AML_NO_OPERAND
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Second arg is the PBlock Address */
id|obj_desc-&gt;power_resource.resource_order
op_assign
(paren
id|u16
)paren
id|arg-&gt;value.integer
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_exec_create_method&n; *&n; * PARAMETERS:  Aml_ptr         - First byte of the method&squot;s AML&n; *              Aml_length      - AML byte count for this method&n; *              Method_flags    - AML method flag byte&n; *              Method          - Method Node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Create a new method object&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_exec_create_method
id|acpi_aml_exec_create_method
(paren
id|u8
op_star
id|aml_ptr
comma
id|u32
id|aml_length
comma
id|u32
id|method_flags
comma
id|ACPI_HANDLE
id|method
)paren
(brace
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/* Create a new method object */
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|ACPI_TYPE_METHOD
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the method&squot;s AML pointer/length from the Op */
id|obj_desc-&gt;method.pcode
op_assign
id|aml_ptr
suffix:semicolon
id|obj_desc-&gt;method.pcode_length
op_assign
id|aml_length
suffix:semicolon
multiline_comment|/*&n;&t; * First argument is the Method Flags (contains parameter count for the&n;&t; * method)&n;&t; */
id|obj_desc-&gt;method.method_flags
op_assign
(paren
id|u8
)paren
id|method_flags
suffix:semicolon
id|obj_desc-&gt;method.param_count
op_assign
(paren
id|u8
)paren
(paren
id|method_flags
op_amp
id|METHOD_FLAGS_ARG_COUNT
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the concurrency count.  If required, a semaphore will be&n;&t; * created for this method when it is parsed.&n;&t; *&n;&t; * TBD: [Future]  for APCI 2.0, there will be a Sync_level value, not&n;&t; * just a flag&n;&t; * Concurrency = Sync_level + 1;.&n;&t; */
r_if
c_cond
(paren
id|method_flags
op_amp
id|METHOD_FLAGS_SERIALIZED
)paren
(brace
id|obj_desc-&gt;method.concurrency
op_assign
l_int|1
suffix:semicolon
)brace
r_else
(brace
id|obj_desc-&gt;method.concurrency
op_assign
id|INFINITE_CONCURRENCY
suffix:semicolon
)brace
multiline_comment|/* Attach the new object to the method Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|method
comma
id|obj_desc
comma
(paren
id|u8
)paren
id|ACPI_TYPE_METHOD
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
id|acpi_cm_delete_object_desc
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
