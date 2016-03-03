multiline_comment|/******************************************************************************&n; *&n; * Name: acconfig.h - Global configuration constants&n; *       $Revision: 48 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACCONFIG_H
DECL|macro|_ACCONFIG_H
mdefine_line|#define _ACCONFIG_H
multiline_comment|/******************************************************************************&n; *&n; * Compile-time options&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * ACPI_DEBUG           - This switch enables all the debug facilities of the ACPI&n; *                          subsystem.  This includes the DEBUG_PRINT output statements&n; *                          When disabled, all DEBUG_PRINT statements are compiled out.&n; *&n; * ACPI_APPLICATION     - Use this switch if the subsystem is going to be run&n; *                          at the application level.&n; *&n; */
multiline_comment|/******************************************************************************&n; *&n; * Subsystem Constants&n; *&n; *****************************************************************************/
multiline_comment|/* Version string */
DECL|macro|ACPI_CA_VERSION
mdefine_line|#define ACPI_CA_VERSION             __DATE__
multiline_comment|/* Maximum objects in the various object caches */
DECL|macro|MAX_STATE_CACHE_DEPTH
mdefine_line|#define MAX_STATE_CACHE_DEPTH       64         /* State objects for stacks */
DECL|macro|MAX_PARSE_CACHE_DEPTH
mdefine_line|#define MAX_PARSE_CACHE_DEPTH       96          /* Parse tree objects */
DECL|macro|MAX_EXTPARSE_CACHE_DEPTH
mdefine_line|#define MAX_EXTPARSE_CACHE_DEPTH    64          /* Parse tree objects */
DECL|macro|MAX_OBJECT_CACHE_DEPTH
mdefine_line|#define MAX_OBJECT_CACHE_DEPTH      64          /* Interpreter operand objects */
DECL|macro|MAX_WALK_CACHE_DEPTH
mdefine_line|#define MAX_WALK_CACHE_DEPTH        2           /* Objects for parse tree walks (method execution) */
multiline_comment|/* String size constants */
DECL|macro|MAX_STRING_LENGTH
mdefine_line|#define MAX_STRING_LENGTH           512
DECL|macro|PATHNAME_MAX
mdefine_line|#define PATHNAME_MAX                256     /* A full namespace pathname */
multiline_comment|/* Maximum count for a semaphore object */
DECL|macro|MAX_SEMAPHORE_COUNT
mdefine_line|#define MAX_SEMAPHORE_COUNT         256
multiline_comment|/* Max reference count (for debug only) */
DECL|macro|MAX_REFERENCE_COUNT
mdefine_line|#define MAX_REFERENCE_COUNT         0x200
multiline_comment|/* Size of cached memory mapping for system memory operation region */
DECL|macro|SYSMEM_REGION_WINDOW_SIZE
mdefine_line|#define SYSMEM_REGION_WINDOW_SIZE   4096
multiline_comment|/*&n; * Debugger threading model&n; * Use single threaded if the entire subsystem is contained in an application&n; * Use multiple threaded when the the subsystem is running in the kernel.&n; *&n; * By default the model is single threaded if ACPI_APPLICATION is set,&n; * multi-threaded if ACPI_APPLICATION is not set.&n; */
DECL|macro|DEBUGGER_SINGLE_THREADED
mdefine_line|#define DEBUGGER_SINGLE_THREADED    0
DECL|macro|DEBUGGER_MULTI_THREADED
mdefine_line|#define DEBUGGER_MULTI_THREADED     1
macro_line|#ifdef ACPI_APPLICATION
DECL|macro|DEBUGGER_THREADING
mdefine_line|#define DEBUGGER_THREADING          DEBUGGER_SINGLE_THREADED
macro_line|#else
DECL|macro|DEBUGGER_THREADING
mdefine_line|#define DEBUGGER_THREADING          DEBUGGER_MULTI_THREADED
macro_line|#endif
multiline_comment|/******************************************************************************&n; *&n; * ACPI Specification constants (Do not change unless the specification changes)&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Method info (in WALK_STATE), containing local variables and argumetns&n; */
DECL|macro|MTH_NUM_LOCALS
mdefine_line|#define MTH_NUM_LOCALS              8
DECL|macro|MTH_MAX_LOCAL
mdefine_line|#define MTH_MAX_LOCAL               7
DECL|macro|MTH_NUM_ARGS
mdefine_line|#define MTH_NUM_ARGS                7
DECL|macro|MTH_MAX_ARG
mdefine_line|#define MTH_MAX_ARG                 6
multiline_comment|/*&n; * Operand Stack (in WALK_STATE), Must be large enough to contain MTH_MAX_ARG&n; */
DECL|macro|OBJ_NUM_OPERANDS
mdefine_line|#define OBJ_NUM_OPERANDS            8
DECL|macro|OBJ_MAX_OPERAND
mdefine_line|#define OBJ_MAX_OPERAND             7
multiline_comment|/* Names within the namespace are 4 bytes long */
DECL|macro|ACPI_NAME_SIZE
mdefine_line|#define ACPI_NAME_SIZE              4
DECL|macro|PATH_SEGMENT_LENGTH
mdefine_line|#define PATH_SEGMENT_LENGTH         5           /* 4 chars for name + 1 s8 for separator */
DECL|macro|PATH_SEPARATOR
mdefine_line|#define PATH_SEPARATOR              &squot;.&squot;
multiline_comment|/* Constants used in searching for the RSDP in low memory */
DECL|macro|LO_RSDP_WINDOW_BASE
mdefine_line|#define LO_RSDP_WINDOW_BASE         0           /* Physical Address */
DECL|macro|HI_RSDP_WINDOW_BASE
mdefine_line|#define HI_RSDP_WINDOW_BASE         0xE0000     /* Physical Address */
DECL|macro|LO_RSDP_WINDOW_SIZE
mdefine_line|#define LO_RSDP_WINDOW_SIZE         0x400
DECL|macro|HI_RSDP_WINDOW_SIZE
mdefine_line|#define HI_RSDP_WINDOW_SIZE         0x20000
DECL|macro|RSDP_SCAN_STEP
mdefine_line|#define RSDP_SCAN_STEP              16
multiline_comment|/* Maximum nesting of package objects */
DECL|macro|MAX_PACKAGE_DEPTH
mdefine_line|#define MAX_PACKAGE_DEPTH           16
macro_line|#endif /* _ACCONFIG_H */
eof
