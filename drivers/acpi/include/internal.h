multiline_comment|/******************************************************************************&n; *&n; * Name: internal.h - Internal data types used across the ACPI subsystem&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACPI_INTERNAL_H
DECL|macro|_ACPI_INTERNAL_H
mdefine_line|#define _ACPI_INTERNAL_H
macro_line|#include &quot;config.h&quot;
DECL|macro|WAIT_FOREVER
mdefine_line|#define WAIT_FOREVER                ((u32) -1)
DECL|typedef|ACPI_MUTEX
r_typedef
r_void
op_star
id|ACPI_MUTEX
suffix:semicolon
DECL|typedef|ACPI_MUTEX_HANDLE
r_typedef
id|u32
id|ACPI_MUTEX_HANDLE
suffix:semicolon
multiline_comment|/* Object descriptor types */
DECL|macro|ACPI_DESC_TYPE_INTERNAL
mdefine_line|#define ACPI_DESC_TYPE_INTERNAL     0xAA
DECL|macro|ACPI_DESC_TYPE_PARSER
mdefine_line|#define ACPI_DESC_TYPE_PARSER       0xBB
DECL|macro|ACPI_DESC_TYPE_STATE
mdefine_line|#define ACPI_DESC_TYPE_STATE        0xCC
DECL|macro|ACPI_DESC_TYPE_WALK
mdefine_line|#define ACPI_DESC_TYPE_WALK         0xDD
DECL|macro|ACPI_DESC_TYPE_NAMED
mdefine_line|#define ACPI_DESC_TYPE_NAMED        0xEE
multiline_comment|/*****************************************************************************&n; *&n; * Mutex typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Predefined handles for the mutex objects used within the subsystem&n; * All mutex objects are automatically created by Acpi_cm_mutex_initialize.&n; * NOTE: any changes here must be reflected in the Acpi_gbl_Mutex_names table also!&n; */
DECL|macro|ACPI_MTX_HARDWARE
mdefine_line|#define ACPI_MTX_HARDWARE           0
DECL|macro|ACPI_MTX_MEMORY
mdefine_line|#define ACPI_MTX_MEMORY             1
DECL|macro|ACPI_MTX_CACHES
mdefine_line|#define ACPI_MTX_CACHES             2
DECL|macro|ACPI_MTX_TABLES
mdefine_line|#define ACPI_MTX_TABLES             3
DECL|macro|ACPI_MTX_PARSER
mdefine_line|#define ACPI_MTX_PARSER             4
DECL|macro|ACPI_MTX_DISPATCHER
mdefine_line|#define ACPI_MTX_DISPATCHER         5
DECL|macro|ACPI_MTX_INTERPRETER
mdefine_line|#define ACPI_MTX_INTERPRETER        6
DECL|macro|ACPI_MTX_EXECUTE
mdefine_line|#define ACPI_MTX_EXECUTE            7
DECL|macro|ACPI_MTX_NAMESPACE
mdefine_line|#define ACPI_MTX_NAMESPACE          8
DECL|macro|ACPI_MTX_EVENTS
mdefine_line|#define ACPI_MTX_EVENTS             9
DECL|macro|ACPI_MTX_OP_REGIONS
mdefine_line|#define ACPI_MTX_OP_REGIONS         10
DECL|macro|ACPI_MTX_DEBUG_CMD_READY
mdefine_line|#define ACPI_MTX_DEBUG_CMD_READY    11
DECL|macro|ACPI_MTX_DEBUG_CMD_COMPLETE
mdefine_line|#define ACPI_MTX_DEBUG_CMD_COMPLETE 12
DECL|macro|MAX_MTX
mdefine_line|#define MAX_MTX                     12
DECL|macro|NUM_MTX
mdefine_line|#define NUM_MTX                     MAX_MTX+1
macro_line|#ifdef ACPI_DEBUG
macro_line|#ifdef DEFINE_ACPI_GLOBALS
multiline_comment|/* Names for the mutexes used in the subsystem */
DECL|variable|acpi_gbl_mutex_names
r_static
r_char
op_star
id|acpi_gbl_mutex_names
(braket
)braket
op_assign
(brace
l_string|&quot;ACPI_MTX_Hardware&quot;
comma
l_string|&quot;ACPI_MTX_Memory&quot;
comma
l_string|&quot;ACPI_MTX_Caches&quot;
comma
l_string|&quot;ACPI_MTX_Tables&quot;
comma
l_string|&quot;ACPI_MTX_Parser&quot;
comma
l_string|&quot;ACPI_MTX_Dispatcher&quot;
comma
l_string|&quot;ACPI_MTX_Interpreter&quot;
comma
l_string|&quot;ACPI_MTX_Execute&quot;
comma
l_string|&quot;ACPI_MTX_Namespace&quot;
comma
l_string|&quot;ACPI_MTX_Events&quot;
comma
l_string|&quot;ACPI_MTX_Op_regions&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_ready&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_complete&quot;
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* Table for the global mutexes */
DECL|struct|acpi_mutex_info
r_typedef
r_struct
id|acpi_mutex_info
(brace
DECL|member|mutex
id|ACPI_MUTEX
id|mutex
suffix:semicolon
DECL|member|use_count
id|u32
id|use_count
suffix:semicolon
DECL|member|locked
id|u8
id|locked
suffix:semicolon
DECL|typedef|ACPI_MUTEX_INFO
)brace
id|ACPI_MUTEX_INFO
suffix:semicolon
multiline_comment|/* Lock flag parameter for various interfaces */
DECL|macro|ACPI_MTX_DO_NOT_LOCK
mdefine_line|#define ACPI_MTX_DO_NOT_LOCK        0
DECL|macro|ACPI_MTX_LOCK
mdefine_line|#define ACPI_MTX_LOCK               1
DECL|typedef|ACPI_OWNER_ID
r_typedef
id|u16
id|ACPI_OWNER_ID
suffix:semicolon
DECL|macro|OWNER_TYPE_TABLE
mdefine_line|#define OWNER_TYPE_TABLE            0x0
DECL|macro|OWNER_TYPE_METHOD
mdefine_line|#define OWNER_TYPE_METHOD           0x1
DECL|macro|FIRST_METHOD_ID
mdefine_line|#define FIRST_METHOD_ID             0x0000
DECL|macro|FIRST_TABLE_ID
mdefine_line|#define FIRST_TABLE_ID              0x8000
multiline_comment|/* TBD: [Restructure] get rid of the need for this! */
DECL|macro|TABLE_ID_DSDT
mdefine_line|#define TABLE_ID_DSDT               (ACPI_OWNER_ID) 0xD1D1
multiline_comment|/*****************************************************************************&n; *&n; * Namespace typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Operational modes of the AML interpreter/scanner */
r_typedef
r_enum
(brace
DECL|enumerator|IMODE_LOAD_PASS1
id|IMODE_LOAD_PASS1
op_assign
l_int|0x01
comma
DECL|enumerator|IMODE_LOAD_PASS2
id|IMODE_LOAD_PASS2
op_assign
l_int|0x02
comma
DECL|enumerator|IMODE_EXECUTE
id|IMODE_EXECUTE
op_assign
l_int|0x0E
DECL|typedef|OPERATING_MODE
)brace
id|OPERATING_MODE
suffix:semicolon
multiline_comment|/*&n; * The Acpi_named_object describes a named object that appears in the AML&n; * An Acpi_name_table is used to store Acpi_named_objects.&n; *&n; * Data_type is used to differentiate between internal descriptors, and MUST&n; * be the first byte in this structure.&n; */
DECL|struct|acpi_named_object
r_typedef
r_struct
id|acpi_named_object
(brace
DECL|member|data_type
id|u8
id|data_type
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Type associated with this name */
DECL|member|this_index
id|u8
id|this_index
suffix:semicolon
multiline_comment|/* Entry number */
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|member|name
id|u32
id|name
suffix:semicolon
multiline_comment|/* ACPI Name, always 4 chars per ACPI spec */
DECL|member|object
r_void
op_star
id|object
suffix:semicolon
multiline_comment|/* Pointer to attached ACPI object (optional) */
DECL|member|child_table
r_struct
id|acpi_name_table
op_star
id|child_table
suffix:semicolon
multiline_comment|/* Scope owned by this name (optional) */
DECL|member|owner_id
id|ACPI_OWNER_ID
id|owner_id
suffix:semicolon
multiline_comment|/* ID of owner - either an ACPI table or a method */
DECL|member|reference_count
id|u16
id|reference_count
suffix:semicolon
multiline_comment|/* Current count of references and children */
macro_line|#ifdef _IA64
DECL|member|fill1
id|u32
id|fill1
suffix:semicolon
multiline_comment|/* 64-bit alignment */
macro_line|#endif
DECL|typedef|ACPI_NAMED_OBJECT
)brace
id|ACPI_NAMED_OBJECT
suffix:semicolon
DECL|struct|acpi_name_table
r_typedef
r_struct
id|acpi_name_table
(brace
DECL|member|next_table
r_struct
id|acpi_name_table
op_star
id|next_table
suffix:semicolon
DECL|member|parent_table
r_struct
id|acpi_name_table
op_star
id|parent_table
suffix:semicolon
DECL|member|parent_entry
id|ACPI_NAMED_OBJECT
op_star
id|parent_entry
suffix:semicolon
DECL|member|entries
id|ACPI_NAMED_OBJECT
id|entries
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|ACPI_NAME_TABLE
)brace
id|ACPI_NAME_TABLE
suffix:semicolon
DECL|macro|ENTRY_NOT_FOUND
mdefine_line|#define ENTRY_NOT_FOUND     NULL
multiline_comment|/* NTE flags */
DECL|macro|NTE_AML_ATTACHMENT
mdefine_line|#define NTE_AML_ATTACHMENT  0x1
multiline_comment|/*&n; * ACPI Table Descriptor.  One per ACPI table&n; */
DECL|struct|acpi_table_desc
r_typedef
r_struct
id|acpi_table_desc
(brace
DECL|member|prev
r_struct
id|acpi_table_desc
op_star
id|prev
suffix:semicolon
DECL|member|next
r_struct
id|acpi_table_desc
op_star
id|next
suffix:semicolon
DECL|member|installed_desc
r_struct
id|acpi_table_desc
op_star
id|installed_desc
suffix:semicolon
DECL|member|pointer
id|ACPI_TABLE_HEADER
op_star
id|pointer
suffix:semicolon
DECL|member|base_pointer
r_void
op_star
id|base_pointer
suffix:semicolon
DECL|member|aml_pointer
id|u8
op_star
id|aml_pointer
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|table_id
id|ACPI_OWNER_ID
id|table_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|allocation
id|u8
id|allocation
suffix:semicolon
DECL|member|loaded_into_namespace
id|u8
id|loaded_into_namespace
suffix:semicolon
DECL|typedef|ACPI_TABLE_DESC
)brace
id|ACPI_TABLE_DESC
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|search_for
r_char
op_star
id|search_for
suffix:semicolon
DECL|member|list
id|ACPI_HANDLE
op_star
id|list
suffix:semicolon
DECL|member|count
id|s32
op_star
id|count
suffix:semicolon
DECL|typedef|FIND_CONTEXT
)brace
id|FIND_CONTEXT
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|name_table
id|ACPI_NAME_TABLE
op_star
id|name_table
suffix:semicolon
DECL|member|position
id|u32
id|position
suffix:semicolon
DECL|member|table_full
id|u8
id|table_full
suffix:semicolon
DECL|typedef|NS_SEARCH_DATA
)brace
id|NS_SEARCH_DATA
suffix:semicolon
multiline_comment|/*&n; * Predefined Namespace items&n; */
DECL|macro|ACPI_MAX_ADDRESS_SPACE
mdefine_line|#define ACPI_MAX_ADDRESS_SPACE      255
DECL|macro|ACPI_NUM_ADDRESS_SPACES
mdefine_line|#define ACPI_NUM_ADDRESS_SPACES     256
r_typedef
r_struct
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|type
id|ACPI_OBJECT_TYPE
id|type
suffix:semicolon
DECL|member|val
r_char
op_star
id|val
suffix:semicolon
DECL|typedef|PREDEFINED_NAMES
)brace
id|PREDEFINED_NAMES
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Event typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Status bits. */
DECL|macro|ACPI_STATUS_PMTIMER
mdefine_line|#define ACPI_STATUS_PMTIMER                  0x0001
DECL|macro|ACPI_STATUS_GLOBAL
mdefine_line|#define ACPI_STATUS_GLOBAL                   0x0020
DECL|macro|ACPI_STATUS_POWER_BUTTON
mdefine_line|#define ACPI_STATUS_POWER_BUTTON             0x0100
DECL|macro|ACPI_STATUS_SLEEP_BUTTON
mdefine_line|#define ACPI_STATUS_SLEEP_BUTTON             0x0200
DECL|macro|ACPI_STATUS_RTC_ALARM
mdefine_line|#define ACPI_STATUS_RTC_ALARM                0x0400
multiline_comment|/* Enable bits. */
DECL|macro|ACPI_ENABLE_PMTIMER
mdefine_line|#define ACPI_ENABLE_PMTIMER                  0x0001
DECL|macro|ACPI_ENABLE_GLOBAL
mdefine_line|#define ACPI_ENABLE_GLOBAL                   0x0020
DECL|macro|ACPI_ENABLE_POWER_BUTTON
mdefine_line|#define ACPI_ENABLE_POWER_BUTTON             0x0100
DECL|macro|ACPI_ENABLE_SLEEP_BUTTON
mdefine_line|#define ACPI_ENABLE_SLEEP_BUTTON             0x0200
DECL|macro|ACPI_ENABLE_RTC_ALARM
mdefine_line|#define ACPI_ENABLE_RTC_ALARM                0x0400
multiline_comment|/*&n; * Entry in the Address_space (AKA Operation Region) table&n; */
r_typedef
r_struct
(brace
DECL|member|handler
id|ADDRESS_SPACE_HANDLER
id|handler
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|ACPI_ADDRESS_SPACE_INFO
)brace
id|ACPI_ADDRESS_SPACE_INFO
suffix:semicolon
multiline_comment|/* Values and addresses of the GPE registers (both banks) */
r_typedef
r_struct
(brace
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* Current value of status reg */
DECL|member|enable
id|u8
id|enable
suffix:semicolon
multiline_comment|/* Current value of enable reg */
DECL|member|status_addr
id|u16
id|status_addr
suffix:semicolon
multiline_comment|/* Address of status reg */
DECL|member|enable_addr
id|u16
id|enable_addr
suffix:semicolon
multiline_comment|/* Address of enable reg */
DECL|member|gpe_base
id|u8
id|gpe_base
suffix:semicolon
multiline_comment|/* Base GPE number */
DECL|typedef|ACPI_GPE_REGISTERS
)brace
id|ACPI_GPE_REGISTERS
suffix:semicolon
DECL|macro|ACPI_GPE_LEVEL_TRIGGERED
mdefine_line|#define ACPI_GPE_LEVEL_TRIGGERED            1
DECL|macro|ACPI_GPE_EDGE_TRIGGERED
mdefine_line|#define ACPI_GPE_EDGE_TRIGGERED             2
multiline_comment|/* Information about each particular GPE level */
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Level or Edge */
DECL|member|method_handle
id|ACPI_HANDLE
id|method_handle
suffix:semicolon
multiline_comment|/* Method handle for direct (fast) execution */
DECL|member|handler
id|GPE_HANDLER
id|handler
suffix:semicolon
multiline_comment|/* Address of handler, if any */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|typedef|ACPI_GPE_LEVEL_INFO
)brace
id|ACPI_GPE_LEVEL_INFO
suffix:semicolon
multiline_comment|/* Information about each particular fixed event */
r_typedef
r_struct
(brace
DECL|member|handler
id|FIXED_EVENT_HANDLER
id|handler
suffix:semicolon
multiline_comment|/* Address of handler. */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|typedef|ACPI_FIXED_EVENT_INFO
)brace
id|ACPI_FIXED_EVENT_INFO
suffix:semicolon
multiline_comment|/* Information used during field processing */
r_typedef
r_struct
(brace
DECL|member|skip_field
id|u8
id|skip_field
suffix:semicolon
DECL|member|field_flag
id|u8
id|field_flag
suffix:semicolon
DECL|member|pkg_length
id|u32
id|pkg_length
suffix:semicolon
DECL|typedef|ACPI_FIELD_INFO
)brace
id|ACPI_FIELD_INFO
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Parser typedefs and structs&n; *&n; ****************************************************************************/
DECL|macro|OP_INFO_TYPE
mdefine_line|#define OP_INFO_TYPE                0x1F
DECL|macro|OP_INFO_HAS_ARGS
mdefine_line|#define OP_INFO_HAS_ARGS            0x20
DECL|macro|OP_INFO_CHILD_LOCATION
mdefine_line|#define OP_INFO_CHILD_LOCATION      0xC0
multiline_comment|/*&n; * AML opcode, name, and argument layout&n; */
DECL|struct|acpi_op_info
r_typedef
r_struct
id|acpi_op_info
(brace
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
multiline_comment|/* AML opcode */
DECL|member|flags
id|u8
id|flags
suffix:semicolon
multiline_comment|/* Opcode type, Has_args flag */
DECL|member|parse_args
id|u32
id|parse_args
suffix:semicolon
multiline_comment|/* Grammar/Parse time arguments */
DECL|member|runtime_args
id|u32
id|runtime_args
suffix:semicolon
multiline_comment|/* Interpret time arguments */
id|DEBUG_ONLY_MEMBERS
(paren
r_char
op_star
id|name
)paren
multiline_comment|/* op name (debug only) */
DECL|typedef|ACPI_OP_INFO
)brace
id|ACPI_OP_INFO
suffix:semicolon
DECL|union|acpi_op_value
r_typedef
r_union
id|acpi_op_value
(brace
DECL|member|integer
id|u32
id|integer
suffix:semicolon
multiline_comment|/* integer constant */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* bytelist or field size */
DECL|member|string
r_char
op_star
id|string
suffix:semicolon
multiline_comment|/* NULL terminated string */
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
multiline_comment|/* buffer or string */
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* NULL terminated string */
DECL|member|arg
r_struct
id|acpi_generic_op
op_star
id|arg
suffix:semicolon
multiline_comment|/* arguments and contained ops */
DECL|member|entry
id|ACPI_NAMED_OBJECT
op_star
id|entry
suffix:semicolon
multiline_comment|/* entry in interpreter namespace tbl */
DECL|typedef|ACPI_OP_VALUE
)brace
id|ACPI_OP_VALUE
suffix:semicolon
DECL|macro|ACPI_COMMON_OP
mdefine_line|#define ACPI_COMMON_OP &bslash;&n;&t;u8                      data_type;      /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags;          /* Type of Op */&bslash;&n;&t;u16                     opcode;         /* AML opcode */&bslash;&n;&t;u32                     aml_offset;     /* offset of declaration in AML */&bslash;&n;&t;struct acpi_generic_op  *parent;        /* parent op */&bslash;&n;&t;struct acpi_generic_op  *next;          /* next op */&bslash;&n;&t;DEBUG_ONLY_MEMBERS (&bslash;&n;&t;char                    op_name[16])    /* op name (debug only) */&bslash;&n;&t;&t;&t;  /* NON-DEBUG members below: */&bslash;&n;&t;void                    *acpi_named_object;/* for use by interpreter */&bslash;&n;&t;ACPI_OP_VALUE           value;          /* Value or args associated with the opcode */&bslash;&n;
multiline_comment|/*&n; * generic operation (eg. If, While, Store)&n; */
DECL|struct|acpi_generic_op
r_typedef
r_struct
id|acpi_generic_op
(brace
id|ACPI_COMMON_OP
DECL|typedef|ACPI_GENERIC_OP
)brace
id|ACPI_GENERIC_OP
suffix:semicolon
multiline_comment|/*&n; * operation with a name (eg. Scope, Method, Name, Named_field, ...)&n; */
DECL|struct|acpi_named_op
r_typedef
r_struct
id|acpi_named_op
(brace
id|ACPI_COMMON_OP
DECL|member|name
id|u32
id|name
suffix:semicolon
multiline_comment|/* 4-byte name or zero if no name */
DECL|typedef|ACPI_NAMED_OP
)brace
id|ACPI_NAMED_OP
suffix:semicolon
multiline_comment|/*&n; * special operation for methods and regions (parsing must be deferred&n; * until a first pass parse is completed)&n; */
DECL|struct|acpi_deferred_op
r_typedef
r_struct
id|acpi_deferred_op
(brace
id|ACPI_COMMON_OP
DECL|member|name
id|u32
id|name
suffix:semicolon
multiline_comment|/* 4-byte name or 0 if none */
DECL|member|body_length
id|u32
id|body_length
suffix:semicolon
multiline_comment|/* AML body size */
DECL|member|body
id|u8
op_star
id|body
suffix:semicolon
multiline_comment|/* AML body */
DECL|member|thread_count
id|u16
id|thread_count
suffix:semicolon
multiline_comment|/* Count of threads currently executing a method */
DECL|typedef|ACPI_DEFERRED_OP
)brace
id|ACPI_DEFERRED_OP
suffix:semicolon
multiline_comment|/*&n; * special operation for bytelists (Byte_list only)&n; */
DECL|struct|acpi_bytelist_op
r_typedef
r_struct
id|acpi_bytelist_op
(brace
id|ACPI_COMMON_OP
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
multiline_comment|/* bytelist data */
DECL|typedef|ACPI_BYTELIST_OP
)brace
id|ACPI_BYTELIST_OP
suffix:semicolon
multiline_comment|/*&n; * Parse state - one state per parser invocation and each control&n; * method.&n; */
DECL|struct|acpi_parse_state
r_typedef
r_struct
id|acpi_parse_state
(brace
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
multiline_comment|/* first AML byte */
DECL|member|aml
id|u8
op_star
id|aml
suffix:semicolon
multiline_comment|/* next AML byte */
DECL|member|aml_end
id|u8
op_star
id|aml_end
suffix:semicolon
multiline_comment|/* (last + 1) AML byte */
DECL|member|pkg_end
id|u8
op_star
id|pkg_end
suffix:semicolon
multiline_comment|/* current package end */
DECL|member|start_op
id|ACPI_GENERIC_OP
op_star
id|start_op
suffix:semicolon
multiline_comment|/* root of parse tree */
DECL|member|scope
r_struct
id|acpi_parse_scope
op_star
id|scope
suffix:semicolon
multiline_comment|/* current scope */
DECL|member|scope_avail
r_struct
id|acpi_parse_scope
op_star
id|scope_avail
suffix:semicolon
multiline_comment|/* unused (extra) scope structs */
DECL|member|next
r_struct
id|acpi_parse_state
op_star
id|next
suffix:semicolon
DECL|typedef|ACPI_PARSE_STATE
)brace
id|ACPI_PARSE_STATE
suffix:semicolon
multiline_comment|/*&n; * Parse scope - one per ACPI scope&n; */
DECL|struct|acpi_parse_scope
r_typedef
r_struct
id|acpi_parse_scope
(brace
DECL|member|op
id|ACPI_GENERIC_OP
op_star
id|op
suffix:semicolon
multiline_comment|/* current op being parsed */
DECL|member|arg_end
id|u8
op_star
id|arg_end
suffix:semicolon
multiline_comment|/* current argument end */
DECL|member|pkg_end
id|u8
op_star
id|pkg_end
suffix:semicolon
multiline_comment|/* current package end */
DECL|member|parent
r_struct
id|acpi_parse_scope
op_star
id|parent
suffix:semicolon
multiline_comment|/* parent scope */
DECL|member|arg_list
id|u32
id|arg_list
suffix:semicolon
multiline_comment|/* next argument to parse */
DECL|member|arg_count
id|u32
id|arg_count
suffix:semicolon
multiline_comment|/* Number of fixed arguments */
DECL|typedef|ACPI_PARSE_SCOPE
)brace
id|ACPI_PARSE_SCOPE
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Generic &quot;state&quot; object for stacks&n; *&n; ****************************************************************************/
DECL|macro|CONTROL_NORMAL
mdefine_line|#define CONTROL_NORMAL                        0xC0
DECL|macro|CONTROL_CONDITIONAL_EXECUTING
mdefine_line|#define CONTROL_CONDITIONAL_EXECUTING         0xC1
DECL|macro|CONTROL_PREDICATE_EXECUTING
mdefine_line|#define CONTROL_PREDICATE_EXECUTING           0xC2
DECL|macro|CONTROL_PREDICATE_FALSE
mdefine_line|#define CONTROL_PREDICATE_FALSE               0xC3
DECL|macro|CONTROL_PREDICATE_TRUE
mdefine_line|#define CONTROL_PREDICATE_TRUE                0xC4
DECL|macro|ACPI_STATE_COMMON
mdefine_line|#define ACPI_STATE_COMMON                  /* Two 32-bit fields and a pointer */&bslash;&n;&t;u8                      data_type;          /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags; &bslash;&n;&t;u16                     value; &bslash;&n;&t;u16                     state; &bslash;&n;&t;u16                     acpi_eval; &bslash;&n;&t;void                    *next; &bslash;&n;
DECL|struct|acpi_common_state
r_typedef
r_struct
id|acpi_common_state
(brace
id|ACPI_STATE_COMMON
DECL|typedef|ACPI_COMMON_STATE
)brace
id|ACPI_COMMON_STATE
suffix:semicolon
multiline_comment|/*&n; * Update state - used to traverse complex objects such as packages&n; */
DECL|struct|acpi_update_state
r_typedef
r_struct
id|acpi_update_state
(brace
id|ACPI_STATE_COMMON
DECL|member|object
r_union
id|acpi_obj_internal
op_star
id|object
suffix:semicolon
DECL|typedef|ACPI_UPDATE_STATE
)brace
id|ACPI_UPDATE_STATE
suffix:semicolon
multiline_comment|/*&n; * Control state - one per if/else and while constructs.&n; * Allows nesting of these constructs&n; */
DECL|struct|acpi_control_state
r_typedef
r_struct
id|acpi_control_state
(brace
id|ACPI_STATE_COMMON
DECL|member|predicate_op
id|ACPI_GENERIC_OP
op_star
id|predicate_op
suffix:semicolon
multiline_comment|/* Start of if/while predicate */
DECL|typedef|ACPI_CONTROL_STATE
)brace
id|ACPI_CONTROL_STATE
suffix:semicolon
multiline_comment|/*&n; * Scope state - current scope during namespace lookups&n; */
DECL|struct|acpi_scope_state
r_typedef
r_struct
id|acpi_scope_state
(brace
id|ACPI_STATE_COMMON
DECL|member|name_table
id|ACPI_NAME_TABLE
op_star
id|name_table
suffix:semicolon
DECL|typedef|ACPI_SCOPE_STATE
)brace
id|ACPI_SCOPE_STATE
suffix:semicolon
DECL|union|acpi_gen_state
r_typedef
r_union
id|acpi_gen_state
(brace
DECL|member|common
id|ACPI_COMMON_STATE
id|common
suffix:semicolon
DECL|member|control
id|ACPI_CONTROL_STATE
id|control
suffix:semicolon
DECL|member|update
id|ACPI_UPDATE_STATE
id|update
suffix:semicolon
DECL|member|scope
id|ACPI_SCOPE_STATE
id|scope
suffix:semicolon
DECL|typedef|ACPI_GENERIC_STATE
)brace
id|ACPI_GENERIC_STATE
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Tree walking typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Walk state - current state of a parse tree walk.  Used for both a leisurely stroll through&n; * the tree (for whatever reason), and for control method execution.&n; */
DECL|macro|NEXT_OP_DOWNWARD
mdefine_line|#define NEXT_OP_DOWNWARD    1
DECL|macro|NEXT_OP_UPWARD
mdefine_line|#define NEXT_OP_UPWARD      2
DECL|struct|acpi_walk_state
r_typedef
r_struct
id|acpi_walk_state
(brace
DECL|member|data_type
id|u8
id|data_type
suffix:semicolon
multiline_comment|/* To differentiate various internal objs */
"&bslash;"
DECL|member|owner_id
id|ACPI_OWNER_ID
id|owner_id
suffix:semicolon
multiline_comment|/* Owner of objects created during the walk */
DECL|member|last_predicate
id|u8
id|last_predicate
suffix:semicolon
multiline_comment|/* Result of last predicate */
DECL|member|next_op_info
id|u8
id|next_op_info
suffix:semicolon
multiline_comment|/* Info about Next_op */
DECL|member|num_operands
id|u8
id|num_operands
suffix:semicolon
multiline_comment|/* Stack pointer for Operands[] array */
DECL|member|num_results
id|u8
id|num_results
suffix:semicolon
multiline_comment|/* Stack pointer for Results[] array */
DECL|member|current_result
id|u8
id|current_result
suffix:semicolon
multiline_comment|/* */
DECL|member|next
r_struct
id|acpi_walk_state
op_star
id|next
suffix:semicolon
multiline_comment|/* Next Walk_state in list */
DECL|member|origin
id|ACPI_GENERIC_OP
op_star
id|origin
suffix:semicolon
multiline_comment|/* Start of walk */
DECL|member|prev_op
id|ACPI_GENERIC_OP
op_star
id|prev_op
suffix:semicolon
multiline_comment|/* Last op that was processed */
DECL|member|next_op
id|ACPI_GENERIC_OP
op_star
id|next_op
suffix:semicolon
multiline_comment|/* next op to be processed */
DECL|member|control_state
id|ACPI_GENERIC_STATE
op_star
id|control_state
suffix:semicolon
multiline_comment|/* List of control states (nested IFs) */
DECL|member|scope_info
id|ACPI_GENERIC_STATE
op_star
id|scope_info
suffix:semicolon
multiline_comment|/* Stack of nested scopes */
DECL|member|return_desc
r_union
id|acpi_obj_internal
op_star
id|return_desc
suffix:semicolon
multiline_comment|/* Return object, if any */
DECL|member|method_desc
r_union
id|acpi_obj_internal
op_star
id|method_desc
suffix:semicolon
multiline_comment|/* Method descriptor if running a method */
DECL|member|method_call_op
id|ACPI_GENERIC_OP
op_star
id|method_call_op
suffix:semicolon
multiline_comment|/* Method_call Op if running a method */
DECL|member|operands
r_union
id|acpi_obj_internal
op_star
id|operands
(braket
id|OBJ_NUM_OPERANDS
)braket
suffix:semicolon
multiline_comment|/* Operands passed to the interpreter */
DECL|member|results
r_union
id|acpi_obj_internal
op_star
id|results
(braket
id|OBJ_NUM_OPERANDS
)braket
suffix:semicolon
multiline_comment|/* Accumulated results */
DECL|member|arguments
r_struct
id|acpi_named_object
id|arguments
(braket
id|MTH_NUM_ARGS
)braket
suffix:semicolon
multiline_comment|/* Control method arguments */
DECL|member|local_variables
r_struct
id|acpi_named_object
id|local_variables
(braket
id|MTH_NUM_LOCALS
)braket
suffix:semicolon
multiline_comment|/* Control method locals */
DECL|typedef|ACPI_WALK_STATE
)brace
id|ACPI_WALK_STATE
suffix:semicolon
multiline_comment|/*&n; * Walk list - head of a tree of walk states.  Multiple walk states are created when there&n; * are nested control methods executing.&n; */
DECL|struct|acpi_walk_list
r_typedef
r_struct
id|acpi_walk_list
(brace
DECL|member|walk_state
id|ACPI_WALK_STATE
op_star
id|walk_state
suffix:semicolon
DECL|typedef|ACPI_WALK_LIST
)brace
id|ACPI_WALK_LIST
suffix:semicolon
r_typedef
DECL|typedef|INTERPRETER_CALLBACK
id|ACPI_STATUS
(paren
op_star
id|INTERPRETER_CALLBACK
)paren
(paren
id|ACPI_WALK_STATE
op_star
id|state
comma
id|ACPI_GENERIC_OP
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* Info used by Acpi_ps_init_objects */
DECL|struct|init_walk_info
r_typedef
r_struct
id|init_walk_info
(brace
DECL|member|method_count
id|u32
id|method_count
suffix:semicolon
DECL|member|op_region_count
id|u32
id|op_region_count
suffix:semicolon
DECL|member|table_desc
id|ACPI_TABLE_DESC
op_star
id|table_desc
suffix:semicolon
DECL|typedef|INIT_WALK_INFO
)brace
id|INIT_WALK_INFO
suffix:semicolon
multiline_comment|/* TBD: [Restructure] Merge with struct above */
DECL|struct|acpi_walk_info
r_typedef
r_struct
id|acpi_walk_info
(brace
DECL|member|debug_level
id|u32
id|debug_level
suffix:semicolon
DECL|member|owner_id
id|u32
id|owner_id
suffix:semicolon
DECL|typedef|ACPI_WALK_INFO
)brace
id|ACPI_WALK_INFO
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Hardware and PNP&n; *&n; ****************************************************************************/
multiline_comment|/* Sleep states */
DECL|macro|SLWA_DEBUG_LEVEL
mdefine_line|#define SLWA_DEBUG_LEVEL    4
DECL|macro|GTS_CALL
mdefine_line|#define GTS_CALL            0
DECL|macro|GTS_WAKE
mdefine_line|#define GTS_WAKE            1
multiline_comment|/* Cx States */
DECL|macro|MAX_CX_STATE_LATENCY
mdefine_line|#define MAX_CX_STATE_LATENCY 0xFFFFFFFF
DECL|macro|MAX_CX_STATES
mdefine_line|#define MAX_CX_STATES       4
multiline_comment|/*&n; * The #define&squot;s and enum below establish an abstract way of identifying what&n; * register block and register is to be accessed.  Do not change any of the&n; * values as they are used in switch statements and offset calculations.&n; */
DECL|macro|REGISTER_BLOCK_MASK
mdefine_line|#define REGISTER_BLOCK_MASK     0xFF00
DECL|macro|BIT_IN_REGISTER_MASK
mdefine_line|#define BIT_IN_REGISTER_MASK    0x00FF
DECL|macro|PM1_EVT
mdefine_line|#define PM1_EVT                 0x0100
DECL|macro|PM1_CONTROL
mdefine_line|#define PM1_CONTROL             0x0200
DECL|macro|PM2_CONTROL
mdefine_line|#define PM2_CONTROL             0x0300
DECL|macro|PM_TIMER
mdefine_line|#define PM_TIMER                0x0400
DECL|macro|PROCESSOR_BLOCK
mdefine_line|#define PROCESSOR_BLOCK         0x0500
DECL|macro|GPE0_STS_BLOCK
mdefine_line|#define GPE0_STS_BLOCK          0x0600
DECL|macro|GPE0_EN_BLOCK
mdefine_line|#define GPE0_EN_BLOCK           0x0700
DECL|macro|GPE1_STS_BLOCK
mdefine_line|#define GPE1_STS_BLOCK          0x0800
DECL|macro|GPE1_EN_BLOCK
mdefine_line|#define GPE1_EN_BLOCK           0x0900
r_enum
(brace
multiline_comment|/* PM1 status register ids */
DECL|enumerator|TMR_STS
id|TMR_STS
op_assign
(paren
id|PM1_EVT
op_or
l_int|0x01
)paren
comma
DECL|enumerator|BM_STS
id|BM_STS
comma
DECL|enumerator|GBL_STS
id|GBL_STS
comma
DECL|enumerator|PWRBTN_STS
id|PWRBTN_STS
comma
DECL|enumerator|SLPBTN_STS
id|SLPBTN_STS
comma
DECL|enumerator|RTC_STS
id|RTC_STS
comma
DECL|enumerator|WAK_STS
id|WAK_STS
comma
multiline_comment|/* PM1 enable register ids */
DECL|enumerator|TMR_EN
id|TMR_EN
comma
multiline_comment|/* need to skip 1 enable number since there&squot;s no bus master enable register */
DECL|enumerator|GBL_EN
id|GBL_EN
op_assign
(paren
id|PM1_EVT
op_or
l_int|0x0A
)paren
comma
DECL|enumerator|PWRBTN_EN
id|PWRBTN_EN
comma
DECL|enumerator|SLPBTN_EN
id|SLPBTN_EN
comma
DECL|enumerator|RTC_EN
id|RTC_EN
comma
multiline_comment|/* PM1 control register ids */
DECL|enumerator|SCI_EN
id|SCI_EN
op_assign
(paren
id|PM1_CONTROL
op_or
l_int|0x01
)paren
comma
DECL|enumerator|BM_RLD
id|BM_RLD
comma
DECL|enumerator|GBL_RLS
id|GBL_RLS
comma
DECL|enumerator|SLP_TYPE_A
id|SLP_TYPE_A
comma
DECL|enumerator|SLP_TYPE_B
id|SLP_TYPE_B
comma
DECL|enumerator|SLP_EN
id|SLP_EN
comma
multiline_comment|/* PM2 control register ids */
DECL|enumerator|ARB_DIS
id|ARB_DIS
op_assign
(paren
id|PM2_CONTROL
op_or
l_int|0x01
)paren
comma
multiline_comment|/* PM Timer register ids */
DECL|enumerator|TMR_VAL
id|TMR_VAL
op_assign
(paren
id|PM_TIMER
op_or
l_int|0x01
)paren
comma
DECL|enumerator|GPE0_STS
id|GPE0_STS
op_assign
(paren
id|GPE0_STS_BLOCK
op_or
l_int|0x01
)paren
comma
DECL|enumerator|GPE0_EN
id|GPE0_EN
op_assign
(paren
id|GPE0_EN_BLOCK
op_or
l_int|0x01
)paren
comma
DECL|enumerator|GPE1_STS
id|GPE1_STS
op_assign
(paren
id|GPE1_STS_BLOCK
op_or
l_int|0x01
)paren
comma
DECL|enumerator|GPE1_EN
id|GPE1_EN
op_assign
(paren
id|GPE0_EN_BLOCK
op_or
l_int|0x01
)paren
comma
multiline_comment|/* Last register value is one less than LAST_REG */
DECL|enumerator|LAST_REG
id|LAST_REG
)brace
suffix:semicolon
DECL|macro|TMR_STS_MASK
mdefine_line|#define TMR_STS_MASK        0x0001
DECL|macro|BM_STS_MASK
mdefine_line|#define BM_STS_MASK         0x0010
DECL|macro|GBL_STS_MASK
mdefine_line|#define GBL_STS_MASK        0x0020
DECL|macro|PWRBTN_STS_MASK
mdefine_line|#define PWRBTN_STS_MASK     0x0100
DECL|macro|SLPBTN_STS_MASK
mdefine_line|#define SLPBTN_STS_MASK     0x0200
DECL|macro|RTC_STS_MASK
mdefine_line|#define RTC_STS_MASK        0x0400
DECL|macro|WAK_STS_MASK
mdefine_line|#define WAK_STS_MASK        0x8000
DECL|macro|ALL_FIXED_STS_BITS
mdefine_line|#define ALL_FIXED_STS_BITS  (TMR_STS_MASK   | BM_STS_MASK  | GBL_STS_MASK | PWRBTN_STS_MASK |  &bslash;&n;&t;&t;&t; SLPBTN_STS_MASK | RTC_STS_MASK | WAK_STS_MASK)
DECL|macro|TMR_EN_MASK
mdefine_line|#define TMR_EN_MASK         0x0001
DECL|macro|GBL_EN_MASK
mdefine_line|#define GBL_EN_MASK         0x0020
DECL|macro|PWRBTN_EN_MASK
mdefine_line|#define PWRBTN_EN_MASK      0x0100
DECL|macro|SLPBTN_EN_MASK
mdefine_line|#define SLPBTN_EN_MASK      0x0200
DECL|macro|RTC_EN_MASK
mdefine_line|#define RTC_EN_MASK         0x0400
DECL|macro|SCI_EN_MASK
mdefine_line|#define SCI_EN_MASK         0x0001
DECL|macro|BM_RLD_MASK
mdefine_line|#define BM_RLD_MASK         0x0002
DECL|macro|GBL_RLS_MASK
mdefine_line|#define GBL_RLS_MASK        0x0004
DECL|macro|SLP_TYPE_X_MASK
mdefine_line|#define SLP_TYPE_X_MASK     0x1C00
DECL|macro|SLP_EN_MASK
mdefine_line|#define SLP_EN_MASK         0x2000
DECL|macro|ARB_DIS_MASK
mdefine_line|#define ARB_DIS_MASK        0x0001
DECL|macro|GPE0_STS_MASK
mdefine_line|#define GPE0_STS_MASK
DECL|macro|GPE0_EN_MASK
mdefine_line|#define GPE0_EN_MASK
DECL|macro|GPE1_STS_MASK
mdefine_line|#define GPE1_STS_MASK
DECL|macro|GPE1_EN_MASK
mdefine_line|#define GPE1_EN_MASK
DECL|macro|ACPI_READ
mdefine_line|#define ACPI_READ           1
DECL|macro|ACPI_WRITE
mdefine_line|#define ACPI_WRITE          2
DECL|macro|LOW_BYTE
mdefine_line|#define LOW_BYTE            0x00FF
DECL|macro|ONE_BYTE
mdefine_line|#define ONE_BYTE            0x08
macro_line|#ifndef SET
DECL|macro|SET
mdefine_line|#define SET             1
macro_line|#endif
macro_line|#ifndef CLEAR
DECL|macro|CLEAR
mdefine_line|#define CLEAR           0
macro_line|#endif
multiline_comment|/* Plug and play */
multiline_comment|/* Pnp and ACPI data */
DECL|macro|VERSION_NO
mdefine_line|#define VERSION_NO                      0x01
DECL|macro|LOGICAL_DEVICE_ID
mdefine_line|#define LOGICAL_DEVICE_ID               0x02
DECL|macro|COMPATIBLE_DEVICE_ID
mdefine_line|#define COMPATIBLE_DEVICE_ID            0x03
DECL|macro|IRQ_FORMAT
mdefine_line|#define IRQ_FORMAT                      0x04
DECL|macro|DMA_FORMAT
mdefine_line|#define DMA_FORMAT                      0x05
DECL|macro|START_DEPENDENT_TAG
mdefine_line|#define START_DEPENDENT_TAG             0x06
DECL|macro|END_DEPENDENT_TAG
mdefine_line|#define END_DEPENDENT_TAG               0x07
DECL|macro|IO_PORT_DESCRIPTOR
mdefine_line|#define IO_PORT_DESCRIPTOR              0x08
DECL|macro|FIXED_LOCATION_IO_DESCRIPTOR
mdefine_line|#define FIXED_LOCATION_IO_DESCRIPTOR    0x09
DECL|macro|RESERVED_TYPE0
mdefine_line|#define RESERVED_TYPE0                  0x0A
DECL|macro|RESERVED_TYPE1
mdefine_line|#define RESERVED_TYPE1                  0x0B
DECL|macro|RESERVED_TYPE2
mdefine_line|#define RESERVED_TYPE2                  0x0C
DECL|macro|RESERVED_TYPE3
mdefine_line|#define RESERVED_TYPE3                  0x0D
DECL|macro|SMALL_VENDOR_DEFINED
mdefine_line|#define SMALL_VENDOR_DEFINED            0x0E
DECL|macro|END_TAG
mdefine_line|#define END_TAG                         0x0F
multiline_comment|/* Pnp and ACPI data */
DECL|macro|MEMORY_RANGE_24
mdefine_line|#define MEMORY_RANGE_24                 0x81
DECL|macro|ISA_MEMORY_RANGE
mdefine_line|#define ISA_MEMORY_RANGE                0x81
DECL|macro|LARGE_VENDOR_DEFINED
mdefine_line|#define LARGE_VENDOR_DEFINED            0x84
DECL|macro|EISA_MEMORY_RANGE
mdefine_line|#define EISA_MEMORY_RANGE               0x85
DECL|macro|MEMORY_RANGE_32
mdefine_line|#define MEMORY_RANGE_32                 0x85
DECL|macro|FIXED_EISA_MEMORY_RANGE
mdefine_line|#define FIXED_EISA_MEMORY_RANGE         0x86
DECL|macro|FIXED_MEMORY_RANGE_32
mdefine_line|#define FIXED_MEMORY_RANGE_32           0x86
multiline_comment|/* ACPI only data */
DECL|macro|DWORD_ADDRESS_SPACE
mdefine_line|#define DWORD_ADDRESS_SPACE             0x87
DECL|macro|WORD_ADDRESS_SPACE
mdefine_line|#define WORD_ADDRESS_SPACE              0x88
DECL|macro|EXTENDED_IRQ
mdefine_line|#define EXTENDED_IRQ                    0x89
multiline_comment|/* MUST HAVES */
r_typedef
r_enum
(brace
DECL|enumerator|DWORD_DEVICE_ID
id|DWORD_DEVICE_ID
comma
DECL|enumerator|STRING_PTR_DEVICE_ID
id|STRING_PTR_DEVICE_ID
comma
DECL|enumerator|STRING_DEVICE_ID
id|STRING_DEVICE_ID
DECL|typedef|DEVICE_ID_TYPE
)brace
id|DEVICE_ID_TYPE
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|DEVICE_ID_TYPE
id|type
suffix:semicolon
r_union
(brace
DECL|member|number
id|u32
id|number
suffix:semicolon
DECL|member|string_ptr
r_char
op_star
id|string_ptr
suffix:semicolon
DECL|member|buffer
r_char
id|buffer
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|data
)brace
id|data
suffix:semicolon
DECL|typedef|DEVICE_ID
)brace
id|DEVICE_ID
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Debug&n; *&n; ****************************************************************************/
multiline_comment|/* Entry for a memory allocation (debug only) */
macro_line|#ifdef ACPI_DEBUG
DECL|macro|MEM_MALLOC
mdefine_line|#define MEM_MALLOC          0
DECL|macro|MEM_CALLOC
mdefine_line|#define MEM_CALLOC          1
DECL|macro|MAX_MODULE_NAME
mdefine_line|#define MAX_MODULE_NAME     16
DECL|struct|allocation_info
r_typedef
r_struct
id|allocation_info
(brace
DECL|member|previous
r_struct
id|allocation_info
op_star
id|previous
suffix:semicolon
DECL|member|next
r_struct
id|allocation_info
op_star
id|next
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|component
id|u32
id|component
suffix:semicolon
DECL|member|line
id|u32
id|line
suffix:semicolon
DECL|member|module
r_char
id|module
(braket
id|MAX_MODULE_NAME
)braket
suffix:semicolon
DECL|member|alloc_type
id|u8
id|alloc_type
suffix:semicolon
DECL|typedef|ALLOCATION_INFO
)brace
id|ALLOCATION_INFO
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
