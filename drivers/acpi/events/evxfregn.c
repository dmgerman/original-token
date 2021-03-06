multiline_comment|/******************************************************************************&n; *&n; * Module Name: evxfregn - External Interfaces, ACPI Operation Regions and&n; *                         Address Spaces.&n; *              $Revision: 26 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          EVENT_HANDLING
id|MODULE_NAME
(paren
l_string|&quot;evxfregn&quot;
)paren
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_install_address_space_handler&n; *&n; * PARAMETERS:  Device          - Handle for the device&n; *              Space_id        - The address space ID&n; *              Handler         - Address of the handler&n; *              Setup           - Address of the setup function&n; *              Context         - Value passed to the handler on each access&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for all Op_regions of a given Space_id.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_install_address_space_handler
id|acpi_install_address_space_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|ACPI_ADDRESS_SPACE_TYPE
id|space_id
comma
id|ADDRESS_SPACE_HANDLER
id|handler
comma
id|ADDRESS_SPACE_SETUP
id|setup
comma
r_void
op_star
id|context
)paren
(brace
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|handler_obj
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|OBJECT_TYPE_INTERNAL
id|type
suffix:semicolon
id|u16
id|flags
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
(paren
op_logical_neg
id|device
)paren
op_logical_or
(paren
(paren
op_logical_neg
id|handler
)paren
op_logical_and
(paren
id|handler
op_ne
id|ACPI_DEFAULT_HANDLER
)paren
)paren
op_logical_or
(paren
id|space_id
OG
id|ACPI_MAX_ADDRESS_SPACE
)paren
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|acpi_cm_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_convert_handle_to_entry
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  This registration is valid for only the types below&n;&t; *  and the root.  This is where the default handlers&n;&t; *  get placed.&n;&t; */
r_if
c_cond
(paren
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_DEVICE
)paren
op_logical_and
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_PROCESSOR
)paren
op_logical_and
(paren
id|node-&gt;type
op_ne
id|ACPI_TYPE_THERMAL
)paren
op_logical_and
(paren
id|node
op_ne
id|acpi_gbl_root_node
)paren
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|handler
op_eq
id|ACPI_DEFAULT_HANDLER
)paren
(brace
id|flags
op_assign
id|ADDR_HANDLER_DEFAULT_INSTALLED
suffix:semicolon
r_switch
c_cond
(paren
id|space_id
)paren
(brace
r_case
id|ADDRESS_SPACE_SYSTEM_MEMORY
suffix:colon
id|handler
op_assign
id|acpi_aml_system_memory_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_system_memory_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ADDRESS_SPACE_SYSTEM_IO
suffix:colon
id|handler
op_assign
id|acpi_aml_system_io_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_io_space_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ADDRESS_SPACE_PCI_CONFIG
suffix:colon
id|handler
op_assign
id|acpi_aml_pci_config_space_handler
suffix:semicolon
id|setup
op_assign
id|acpi_ev_pci_config_region_setup
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  If the caller hasn&squot;t specified a setup routine, use the default&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|setup
)paren
(brace
id|setup
op_assign
id|acpi_ev_default_region_setup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Check for an existing internal object&n;&t; */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
(paren
id|ACPI_HANDLE
)paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; *  The object exists.&n;&t;&t; *  Make sure the handler is not already installed.&n;&t;&t; */
multiline_comment|/* check the address handler the user requested */
id|handler_obj
op_assign
id|obj_desc-&gt;device.addr_handler
suffix:semicolon
r_while
c_loop
(paren
id|handler_obj
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *  We have an Address handler, see if user requested this&n;&t;&t;&t; *  address space.&n;&t;&t;&t; */
r_if
c_cond
(paren
id|handler_obj-&gt;addr_handler.space_id
op_eq
id|space_id
)paren
(brace
id|status
op_assign
id|AE_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *  Move through the linked list of handlers&n;&t;&t;&t; */
id|handler_obj
op_assign
id|handler_obj-&gt;addr_handler.next
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Obj_desc does not exist, create one */
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|ACPI_TYPE_ANY
)paren
(brace
id|type
op_assign
id|ACPI_TYPE_DEVICE
suffix:semicolon
)brace
r_else
(brace
id|type
op_assign
id|node-&gt;type
suffix:semicolon
)brace
id|obj_desc
op_assign
id|acpi_cm_create_internal_object
(paren
id|type
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
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Init new descriptor */
id|obj_desc-&gt;common.type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
multiline_comment|/* Attach the new object to the Node */
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
id|type
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
id|unlock_and_exit
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; *  Now we can install the handler&n;&t; *&n;&t; *  At this point we know that there is no existing handler.&n;&t; *  So, we just allocate the object for the handler and link it&n;&t; *  into the list.&n;&t; */
id|handler_obj
op_assign
id|acpi_cm_create_internal_object
(paren
id|INTERNAL_TYPE_ADDRESS_HANDLER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler_obj
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
id|handler_obj-&gt;addr_handler.space_id
op_assign
(paren
id|u8
)paren
id|space_id
suffix:semicolon
id|handler_obj-&gt;addr_handler.hflags
op_assign
id|flags
suffix:semicolon
id|handler_obj-&gt;addr_handler.next
op_assign
id|obj_desc-&gt;device.addr_handler
suffix:semicolon
id|handler_obj-&gt;addr_handler.region_list
op_assign
l_int|NULL
suffix:semicolon
id|handler_obj-&gt;addr_handler.node
op_assign
id|node
suffix:semicolon
id|handler_obj-&gt;addr_handler.handler
op_assign
id|handler
suffix:semicolon
id|handler_obj-&gt;addr_handler.context
op_assign
id|context
suffix:semicolon
id|handler_obj-&gt;addr_handler.setup
op_assign
id|setup
suffix:semicolon
multiline_comment|/*&n;&t; *  Now walk the namespace finding all of the regions this&n;&t; *  handler will manage.&n;&t; *&n;&t; *  We start at the device and search the branch toward&n;&t; *  the leaf nodes until either the leaf is encountered or&n;&t; *  a device is detected that has an address handler of the&n;&t; *  same type.&n;&t; *&n;&t; *  In either case we back up and search down the remainder&n;&t; *  of the branch&n;&t; */
id|status
op_assign
id|acpi_ns_walk_namespace
(paren
id|ACPI_TYPE_ANY
comma
id|device
comma
id|ACPI_UINT32_MAX
comma
id|NS_WALK_UNLOCK
comma
id|acpi_ev_addr_handler_helper
comma
id|handler_obj
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Place this handler 1st on the list&n;&t; */
id|handler_obj-&gt;common.reference_count
op_assign
(paren
id|u16
)paren
(paren
id|handler_obj-&gt;common.reference_count
op_plus
id|obj_desc-&gt;common.reference_count
op_minus
l_int|1
)paren
suffix:semicolon
id|obj_desc-&gt;device.addr_handler
op_assign
id|handler_obj
suffix:semicolon
id|unlock_and_exit
suffix:colon
id|acpi_cm_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_remove_address_space_handler&n; *&n; * PARAMETERS:  Space_id        - The address space ID&n; *              Handler         - Address of the handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for accesses on an Operation Region&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_remove_address_space_handler
id|acpi_remove_address_space_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|ACPI_ADDRESS_SPACE_TYPE
id|space_id
comma
id|ADDRESS_SPACE_HANDLER
id|handler
)paren
(brace
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|handler_obj
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|region_obj
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|last_obj_ptr
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
(paren
op_logical_neg
id|device
)paren
op_logical_or
(paren
(paren
op_logical_neg
id|handler
)paren
op_logical_and
(paren
id|handler
op_ne
id|ACPI_DEFAULT_HANDLER
)paren
)paren
op_logical_or
(paren
id|space_id
OG
id|ACPI_MAX_ADDRESS_SPACE
)paren
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|acpi_cm_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_convert_handle_to_entry
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Make sure the internal object exists */
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
(paren
id|ACPI_HANDLE
)paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/*&n;&t;&t; *  The object DNE.&n;&t;&t; */
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  find the address handler the user requested&n;&t; */
id|handler_obj
op_assign
id|obj_desc-&gt;device.addr_handler
suffix:semicolon
id|last_obj_ptr
op_assign
op_amp
id|obj_desc-&gt;device.addr_handler
suffix:semicolon
r_while
c_loop
(paren
id|handler_obj
)paren
(brace
multiline_comment|/*&n;&t;&t; *  We have a handler, see if user requested this one&n;&t;&t; */
r_if
c_cond
(paren
id|handler_obj-&gt;addr_handler.space_id
op_eq
id|space_id
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *  Got it, first dereference this in the Regions&n;&t;&t;&t; */
id|region_obj
op_assign
id|handler_obj-&gt;addr_handler.region_list
suffix:semicolon
multiline_comment|/* Walk the handler&squot;s region list */
r_while
c_loop
(paren
id|region_obj
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; *  First disassociate the handler from the region.&n;&t;&t;&t;&t; *&n;&t;&t;&t;&t; *  NOTE: this doesn&squot;t mean that the region goes away&n;&t;&t;&t;&t; *  The region is just inaccessible as indicated to&n;&t;&t;&t;&t; *  the _REG method&n;&t;&t;&t;&t; */
id|acpi_ev_disassociate_region_from_handler
c_func
(paren
id|region_obj
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t;&t; *  Walk the list, since we took the first region and it&n;&t;&t;&t;&t; *  was removed from the list by the dissassociate call&n;&t;&t;&t;&t; *  we just get the first item on the list again&n;&t;&t;&t;&t; */
id|region_obj
op_assign
id|handler_obj-&gt;addr_handler.region_list
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; *  Remove this Handler object from the list&n;&t;&t;&t; */
op_star
id|last_obj_ptr
op_assign
id|handler_obj-&gt;addr_handler.next
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  Now we can delete the handler object&n;&t;&t;&t; */
id|acpi_cm_remove_reference
(paren
id|handler_obj
)paren
suffix:semicolon
id|acpi_cm_remove_reference
(paren
id|handler_obj
)paren
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *  Move through the linked list of handlers&n;&t;&t; */
id|last_obj_ptr
op_assign
op_amp
id|handler_obj-&gt;addr_handler.next
suffix:semicolon
id|handler_obj
op_assign
id|handler_obj-&gt;addr_handler.next
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  The handler does not exist&n;&t; */
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
id|unlock_and_exit
suffix:colon
id|acpi_cm_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
