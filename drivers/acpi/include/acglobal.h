multiline_comment|/******************************************************************************&n; *&n; * Name: acglobal.h - Declarations for global variables&n; *       $Revision: 92 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACGLOBAL_H__
DECL|macro|__ACGLOBAL_H__
mdefine_line|#define __ACGLOBAL_H__
multiline_comment|/*&n; * Ensure that the globals are actually defined only once.&n; *&n; * The use of these defines allows a single list of globals (here) in order&n; * to simplify maintenance of the code.&n; */
macro_line|#ifdef DEFINE_ACPI_GLOBALS
DECL|macro|ACPI_EXTERN
mdefine_line|#define ACPI_EXTERN
macro_line|#else
DECL|macro|ACPI_EXTERN
mdefine_line|#define ACPI_EXTERN extern
macro_line|#endif
r_extern
id|NATIVE_CHAR
op_star
id|msg_acpi_error_break
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Debug support&n; *&n; ****************************************************************************/
multiline_comment|/* Runtime configuration of debug print levels */
r_extern
id|u32
id|acpi_dbg_level
suffix:semicolon
r_extern
id|u32
id|acpi_dbg_layer
suffix:semicolon
multiline_comment|/* Procedure nesting level for debug output */
r_extern
id|u32
id|acpi_gbl_nesting_level
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * ACPI Table globals&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Table pointers.&n; * Although these pointers are somewhat redundant with the global Acpi_table,&n; * they are convenient because they are typed pointers.&n; *&n; * These tables are single-table only; meaning that there can be at most one&n; * of each in the system.  Each global points to the actual table.&n; *&n; */
DECL|variable|acpi_gbl_RSDP
id|ACPI_EXTERN
id|RSDP_DESCRIPTOR
op_star
id|acpi_gbl_RSDP
suffix:semicolon
DECL|variable|acpi_gbl_XSDT
id|ACPI_EXTERN
id|XSDT_DESCRIPTOR
op_star
id|acpi_gbl_XSDT
suffix:semicolon
DECL|variable|acpi_gbl_FADT
id|ACPI_EXTERN
id|FADT_DESCRIPTOR
op_star
id|acpi_gbl_FADT
suffix:semicolon
DECL|variable|acpi_gbl_DSDT
id|ACPI_EXTERN
id|ACPI_TABLE_HEADER
op_star
id|acpi_gbl_DSDT
suffix:semicolon
DECL|variable|acpi_gbl_FACS
id|ACPI_EXTERN
id|ACPI_COMMON_FACS
op_star
id|acpi_gbl_FACS
suffix:semicolon
multiline_comment|/*&n; * Since there may be multiple SSDTs and PSDTS, a single pointer is not&n; * sufficient; Therefore, there isn&squot;t one!&n; */
multiline_comment|/*&n; * ACPI Table info arrays&n; */
r_extern
id|ACPI_TABLE_DESC
id|acpi_gbl_acpi_tables
(braket
id|NUM_ACPI_TABLES
)braket
suffix:semicolon
r_extern
id|ACPI_TABLE_SUPPORT
id|acpi_gbl_acpi_table_data
(braket
id|NUM_ACPI_TABLES
)braket
suffix:semicolon
multiline_comment|/*&n; * Predefined mutex objects.  This array contains the&n; * actual OS mutex handles, indexed by the local ACPI_MUTEX_HANDLEs.&n; * (The table maps local handles to the real OS handles)&n; */
DECL|variable|acpi_gbl_acpi_mutex_info
id|ACPI_EXTERN
id|ACPI_MUTEX_INFO
id|acpi_gbl_acpi_mutex_info
(braket
id|NUM_MTX
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Miscellaneous globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_gpe0enable_register_save
id|ACPI_EXTERN
id|u8
op_star
id|acpi_gbl_gpe0enable_register_save
suffix:semicolon
DECL|variable|acpi_gbl_gpe1_enable_register_save
id|ACPI_EXTERN
id|u8
op_star
id|acpi_gbl_gpe1_enable_register_save
suffix:semicolon
DECL|variable|acpi_gbl_breakpoint_walk
id|ACPI_EXTERN
id|ACPI_WALK_STATE
op_star
id|acpi_gbl_breakpoint_walk
suffix:semicolon
DECL|variable|acpi_gbl_generic_state_cache
id|ACPI_EXTERN
id|ACPI_GENERIC_STATE
op_star
id|acpi_gbl_generic_state_cache
suffix:semicolon
DECL|variable|acpi_gbl_parse_cache
id|ACPI_EXTERN
id|ACPI_PARSE_OBJECT
op_star
id|acpi_gbl_parse_cache
suffix:semicolon
DECL|variable|acpi_gbl_ext_parse_cache
id|ACPI_EXTERN
id|ACPI_PARSE2_OBJECT
op_star
id|acpi_gbl_ext_parse_cache
suffix:semicolon
DECL|variable|acpi_gbl_object_cache
id|ACPI_EXTERN
id|ACPI_OPERAND_OBJECT
op_star
id|acpi_gbl_object_cache
suffix:semicolon
DECL|variable|acpi_gbl_walk_state_cache
id|ACPI_EXTERN
id|ACPI_WALK_STATE
op_star
id|acpi_gbl_walk_state_cache
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_semaphore
id|ACPI_EXTERN
id|ACPI_HANDLE
id|acpi_gbl_global_lock_semaphore
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_thread_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_global_lock_thread_count
suffix:semicolon
DECL|variable|acpi_gbl_restore_acpi_chipset
id|ACPI_EXTERN
id|u32
id|acpi_gbl_restore_acpi_chipset
suffix:semicolon
DECL|variable|acpi_gbl_original_mode
id|ACPI_EXTERN
id|u32
id|acpi_gbl_original_mode
suffix:semicolon
DECL|variable|acpi_gbl_edge_level_save
id|ACPI_EXTERN
id|u32
id|acpi_gbl_edge_level_save
suffix:semicolon
DECL|variable|acpi_gbl_irq_enable_save
id|ACPI_EXTERN
id|u32
id|acpi_gbl_irq_enable_save
suffix:semicolon
DECL|variable|acpi_gbl_rsdp_original_location
id|ACPI_EXTERN
id|u32
id|acpi_gbl_rsdp_original_location
suffix:semicolon
DECL|variable|acpi_gbl_state_cache_requests
id|ACPI_EXTERN
id|u32
id|acpi_gbl_state_cache_requests
suffix:semicolon
DECL|variable|acpi_gbl_state_cache_hits
id|ACPI_EXTERN
id|u32
id|acpi_gbl_state_cache_hits
suffix:semicolon
DECL|variable|acpi_gbl_parse_cache_requests
id|ACPI_EXTERN
id|u32
id|acpi_gbl_parse_cache_requests
suffix:semicolon
DECL|variable|acpi_gbl_parse_cache_hits
id|ACPI_EXTERN
id|u32
id|acpi_gbl_parse_cache_hits
suffix:semicolon
DECL|variable|acpi_gbl_ext_parse_cache_requests
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ext_parse_cache_requests
suffix:semicolon
DECL|variable|acpi_gbl_ext_parse_cache_hits
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ext_parse_cache_hits
suffix:semicolon
DECL|variable|acpi_gbl_object_cache_requests
id|ACPI_EXTERN
id|u32
id|acpi_gbl_object_cache_requests
suffix:semicolon
DECL|variable|acpi_gbl_object_cache_hits
id|ACPI_EXTERN
id|u32
id|acpi_gbl_object_cache_hits
suffix:semicolon
DECL|variable|acpi_gbl_walk_state_cache_requests
id|ACPI_EXTERN
id|u32
id|acpi_gbl_walk_state_cache_requests
suffix:semicolon
DECL|variable|acpi_gbl_walk_state_cache_hits
id|ACPI_EXTERN
id|u32
id|acpi_gbl_walk_state_cache_hits
suffix:semicolon
DECL|variable|acpi_gbl_ns_lookup_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ns_lookup_count
suffix:semicolon
DECL|variable|acpi_gbl_ps_find_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ps_find_count
suffix:semicolon
DECL|variable|acpi_gbl_generic_state_cache_depth
id|ACPI_EXTERN
id|u16
id|acpi_gbl_generic_state_cache_depth
suffix:semicolon
DECL|variable|acpi_gbl_parse_cache_depth
id|ACPI_EXTERN
id|u16
id|acpi_gbl_parse_cache_depth
suffix:semicolon
DECL|variable|acpi_gbl_ext_parse_cache_depth
id|ACPI_EXTERN
id|u16
id|acpi_gbl_ext_parse_cache_depth
suffix:semicolon
DECL|variable|acpi_gbl_object_cache_depth
id|ACPI_EXTERN
id|u16
id|acpi_gbl_object_cache_depth
suffix:semicolon
DECL|variable|acpi_gbl_walk_state_cache_depth
id|ACPI_EXTERN
id|u16
id|acpi_gbl_walk_state_cache_depth
suffix:semicolon
DECL|variable|acpi_gbl_pm1_enable_register_save
id|ACPI_EXTERN
id|u16
id|acpi_gbl_pm1_enable_register_save
suffix:semicolon
DECL|variable|acpi_gbl_next_table_owner_id
id|ACPI_EXTERN
id|u16
id|acpi_gbl_next_table_owner_id
suffix:semicolon
DECL|variable|acpi_gbl_next_method_owner_id
id|ACPI_EXTERN
id|u16
id|acpi_gbl_next_method_owner_id
suffix:semicolon
DECL|variable|acpi_gbl_debugger_configuration
id|ACPI_EXTERN
id|u8
id|acpi_gbl_debugger_configuration
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_acquired
id|ACPI_EXTERN
id|u8
id|acpi_gbl_global_lock_acquired
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_set
id|ACPI_EXTERN
id|u8
id|acpi_gbl_global_lock_set
suffix:semicolon
multiline_comment|/* TBD: [Restructure] OBSOLETE?? */
DECL|variable|acpi_gbl_step_to_next_call
id|ACPI_EXTERN
id|u8
id|acpi_gbl_step_to_next_call
suffix:semicolon
DECL|variable|acpi_gbl_acpi_hardware_present
id|ACPI_EXTERN
id|u8
id|acpi_gbl_acpi_hardware_present
suffix:semicolon
DECL|variable|acpi_gbl_drv_notify
id|ACPI_EXTERN
id|ACPI_OBJECT_NOTIFY_HANDLER
id|acpi_gbl_drv_notify
suffix:semicolon
DECL|variable|acpi_gbl_sys_notify
id|ACPI_EXTERN
id|ACPI_OBJECT_NOTIFY_HANDLER
id|acpi_gbl_sys_notify
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_shutdown
suffix:semicolon
r_extern
id|u32
id|acpi_gbl_system_flags
suffix:semicolon
r_extern
id|u32
id|acpi_gbl_startup_flags
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_decode_to8bit
(braket
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Namespace globals&n; *&n; ****************************************************************************/
DECL|macro|NUM_NS_TYPES
mdefine_line|#define NUM_NS_TYPES                    INTERNAL_TYPE_INVALID+1
DECL|macro|NUM_PREDEFINED_NAMES
mdefine_line|#define NUM_PREDEFINED_NAMES            9
DECL|variable|acpi_gbl_root_node_struct
id|ACPI_EXTERN
id|ACPI_NAMESPACE_NODE
id|acpi_gbl_root_node_struct
suffix:semicolon
DECL|variable|acpi_gbl_root_node
id|ACPI_EXTERN
id|ACPI_NAMESPACE_NODE
op_star
id|acpi_gbl_root_node
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_ns_properties
(braket
id|NUM_NS_TYPES
)braket
suffix:semicolon
r_extern
id|PREDEFINED_NAMES
id|acpi_gbl_pre_defined_names
(braket
id|NUM_PREDEFINED_NAMES
)braket
suffix:semicolon
multiline_comment|/* Used to detect memory leaks (DEBUG ONLY) */
macro_line|#ifdef ACPI_DEBUG
DECL|variable|acpi_gbl_head_alloc_ptr
id|ACPI_EXTERN
id|ALLOCATION_INFO
op_star
id|acpi_gbl_head_alloc_ptr
suffix:semicolon
DECL|variable|acpi_gbl_tail_alloc_ptr
id|ACPI_EXTERN
id|ALLOCATION_INFO
op_star
id|acpi_gbl_tail_alloc_ptr
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * Interpreter globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_current_walk_list
id|ACPI_EXTERN
id|ACPI_WALK_LIST
op_star
id|acpi_gbl_current_walk_list
suffix:semicolon
multiline_comment|/*&n; * Handle to the last method found - used during pass1 of load&n; */
DECL|variable|acpi_gbl_last_method
id|ACPI_EXTERN
id|ACPI_HANDLE
id|acpi_gbl_last_method
suffix:semicolon
multiline_comment|/*&n; * Table of Address Space handlers&n; */
DECL|variable|acpi_gbl_address_spaces
id|ACPI_EXTERN
id|ACPI_ADDRESS_SPACE_INFO
id|acpi_gbl_address_spaces
(braket
id|ACPI_NUM_ADDRESS_SPACES
)braket
suffix:semicolon
multiline_comment|/* Control method single step flag */
DECL|variable|acpi_gbl_cm_single_step
id|ACPI_EXTERN
id|u8
id|acpi_gbl_cm_single_step
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Parser globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_parsed_namespace_root
id|ACPI_EXTERN
id|ACPI_PARSE_OBJECT
op_star
id|acpi_gbl_parsed_namespace_root
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Hardware globals&n; *&n; ****************************************************************************/
r_extern
id|ACPI_C_STATE_HANDLER
id|acpi_hw_cx_handlers
(braket
id|MAX_CX_STATES
)braket
suffix:semicolon
r_extern
id|u32
id|acpi_hw_active_cx_state
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Event globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_fixed_event_handlers
id|ACPI_EXTERN
id|ACPI_FIXED_EVENT_INFO
id|acpi_gbl_fixed_event_handlers
(braket
id|NUM_FIXED_EVENTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_gpe_obj_handle
id|ACPI_EXTERN
id|ACPI_HANDLE
id|acpi_gbl_gpe_obj_handle
suffix:semicolon
DECL|variable|acpi_gbl_gpe_register_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_gpe_register_count
suffix:semicolon
DECL|variable|acpi_gbl_gpe_registers
id|ACPI_EXTERN
id|ACPI_GPE_REGISTERS
op_star
id|acpi_gbl_gpe_registers
suffix:semicolon
DECL|variable|acpi_gbl_gpe_info
id|ACPI_EXTERN
id|ACPI_GPE_LEVEL_INFO
op_star
id|acpi_gbl_gpe_info
suffix:semicolon
multiline_comment|/*&n; * Gpe validation and translation table&n; * Indexed by the GPE number, returns GPE_INVALID if the GPE is not supported.&n; * Otherwise, returns a valid index into the global GPE table.&n; *&n; * This table is needed because the GPE numbers supported by block 1 do not&n; * have to be contiguous with the GPE numbers supported by block 0.&n; */
DECL|variable|acpi_gbl_gpe_valid
id|ACPI_EXTERN
id|u8
id|acpi_gbl_gpe_valid
(braket
id|NUM_GPE
)braket
suffix:semicolon
multiline_comment|/* Acpi_event counter for debug only */
macro_line|#ifdef ACPI_DEBUG
DECL|variable|acpi_gbl_event_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_event_count
(braket
id|NUM_FIXED_EVENTS
)braket
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * Debugger globals&n; *&n; ****************************************************************************/
macro_line|#ifdef ENABLE_DEBUGGER
DECL|variable|acpi_gbl_method_executing
id|ACPI_EXTERN
id|u8
id|acpi_gbl_method_executing
suffix:semicolon
DECL|variable|acpi_gbl_db_terminate_threads
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_terminate_threads
suffix:semicolon
macro_line|#endif
multiline_comment|/* Memory allocation metrics - Debug Only! */
macro_line|#ifdef ACPI_DEBUG
DECL|variable|acpi_gbl_current_alloc_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_alloc_size
suffix:semicolon
DECL|variable|acpi_gbl_current_alloc_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_alloc_count
suffix:semicolon
DECL|variable|acpi_gbl_running_alloc_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_running_alloc_size
suffix:semicolon
DECL|variable|acpi_gbl_running_alloc_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_running_alloc_count
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_alloc_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_alloc_size
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_alloc_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_alloc_count
suffix:semicolon
DECL|variable|acpi_gbl_current_object_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_object_count
suffix:semicolon
DECL|variable|acpi_gbl_current_object_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_object_size
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_object_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_object_count
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_object_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_object_size
suffix:semicolon
DECL|variable|acpi_gbl_running_object_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_running_object_count
suffix:semicolon
DECL|variable|acpi_gbl_running_object_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_running_object_size
suffix:semicolon
DECL|variable|acpi_gbl_current_node_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_node_count
suffix:semicolon
DECL|variable|acpi_gbl_current_node_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_node_size
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_node_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_node_count
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ACGLOBAL_H__ */
eof
