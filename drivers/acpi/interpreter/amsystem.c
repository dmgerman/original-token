multiline_comment|/******************************************************************************&n; *&n; * Module Name: amsystem - Interface to OS services&n; *              $Revision: 52 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;achware.h&quot;
macro_line|#include &quot;acevents.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          INTERPRETER
id|MODULE_NAME
(paren
l_string|&quot;amsystem&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_thread_id&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Current Thread ID (for this implementation a 1 is returned)&n; *&n; * DESCRIPTION: An invocation is identified by its Thread ID.  In a single&n; *              threaded OS the Thread ID is undefined so a 1 will be&n; *              returned.&n; *&n; ******************************************************************************/
id|u16
DECL|function|acpi_aml_system_thread_id
id|acpi_aml_system_thread_id
(paren
r_void
)paren
(brace
r_return
(paren
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_wait_semaphore&n; *&n; * PARAMETERS:  Semaphore           - OSD semaphore to wait on&n; *              Timeout             - Max time to wait&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Implements a semaphore wait with a check to see if the&n; *              semaphore is available immediately.  If it is not, the&n; *              interpreter is released.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_wait_semaphore
id|acpi_aml_system_wait_semaphore
(paren
id|ACPI_HANDLE
id|semaphore
comma
id|u32
id|timeout
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
id|status
op_assign
id|acpi_os_wait_semaphore
(paren
id|semaphore
comma
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_TIME
)paren
(brace
multiline_comment|/* We must wait, so unlock the interpreter */
id|acpi_aml_exit_interpreter
(paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_os_wait_semaphore
(paren
id|semaphore
comma
l_int|1
comma
id|timeout
)paren
suffix:semicolon
multiline_comment|/* Reacquire the interpreter */
id|acpi_aml_enter_interpreter
(paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_do_stall&n; *&n; * PARAMETERS:  How_long            - The amount of time to stall&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Suspend running thread for specified amount of time.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_aml_system_do_stall
id|acpi_aml_system_do_stall
(paren
id|u32
id|how_long
)paren
(brace
r_if
c_cond
(paren
id|how_long
OG
l_int|1000
)paren
multiline_comment|/* 1 millisecond */
(brace
multiline_comment|/* Since this thread will sleep, we must release the interpreter */
id|acpi_aml_exit_interpreter
(paren
)paren
suffix:semicolon
id|acpi_os_sleep_usec
(paren
id|how_long
)paren
suffix:semicolon
multiline_comment|/* And now we must get the interpreter again */
id|acpi_aml_enter_interpreter
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|acpi_os_sleep_usec
(paren
id|how_long
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_do_suspend&n; *&n; * PARAMETERS:  How_long            - The amount of time to suspend&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Suspend running thread for specified amount of time.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_aml_system_do_suspend
id|acpi_aml_system_do_suspend
(paren
id|u32
id|how_long
)paren
(brace
multiline_comment|/* Since this thread will sleep, we must release the interpreter */
id|acpi_aml_exit_interpreter
(paren
)paren
suffix:semicolon
id|acpi_os_sleep
(paren
(paren
id|u16
)paren
(paren
id|how_long
op_div
(paren
id|u32
)paren
l_int|1000
)paren
comma
(paren
id|u16
)paren
(paren
id|how_long
op_mod
(paren
id|u32
)paren
l_int|1000
)paren
)paren
suffix:semicolon
multiline_comment|/* And now we must get the interpreter again */
id|acpi_aml_enter_interpreter
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_acquire_mutex&n; *&n; * PARAMETERS:  *Time_desc          - The &squot;time to delay&squot; object descriptor&n; *              *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Provides an access point to perform synchronization operations&n; *              within the AML.  This function will cause a lock to be generated&n; *              for the Mutex pointed to by Obj_desc.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_acquire_mutex
id|acpi_aml_system_acquire_mutex
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|time_desc
comma
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Support for the _GL_ Mutex object -- go get the global lock&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.semaphore
op_eq
id|acpi_gbl_global_lock_semaphore
)paren
(brace
id|status
op_assign
id|acpi_ev_acquire_global_lock
(paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_aml_system_wait_semaphore
(paren
id|obj_desc-&gt;mutex.semaphore
comma
(paren
id|u32
)paren
id|time_desc-&gt;number.value
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_release_mutex&n; *&n; * PARAMETERS:  *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Provides an access point to perform synchronization operations&n; *              within the AML.  This operation is a request to release a&n; *              previously acquired Mutex.  If the Mutex variable is set then&n; *              it will be decremented.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_release_mutex
id|acpi_aml_system_release_mutex
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Support for the _GL_ Mutex object -- release the global lock&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.semaphore
op_eq
id|acpi_gbl_global_lock_semaphore
)paren
(brace
id|acpi_ev_release_global_lock
(paren
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_os_signal_semaphore
(paren
id|obj_desc-&gt;mutex.semaphore
comma
l_int|1
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_signal_event&n; *&n; * PARAMETERS:  *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      AE_OK&n; *&n; * DESCRIPTION: Provides an access point to perform synchronization operations&n; *              within the AML.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_signal_event
id|acpi_aml_system_signal_event
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
id|status
op_assign
id|acpi_os_signal_semaphore
(paren
id|obj_desc-&gt;event.semaphore
comma
l_int|1
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_wait_event&n; *&n; * PARAMETERS:  *Time_desc          - The &squot;time to delay&squot; object descriptor&n; *              *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Provides an access point to perform synchronization operations&n; *              within the AML.  This operation is a request to wait for an&n; *              event.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_wait_event
id|acpi_aml_system_wait_event
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|time_desc
comma
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
id|status
op_assign
id|acpi_aml_system_wait_semaphore
(paren
id|obj_desc-&gt;event.semaphore
comma
(paren
id|u32
)paren
id|time_desc-&gt;number.value
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_system_reset_event&n; *&n; * PARAMETERS:  *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Provides an access point to perform synchronization operations&n; *              within the AML.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_system_reset_event
id|acpi_aml_system_reset_event
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_void
op_star
id|temp_semaphore
suffix:semicolon
multiline_comment|/*&n;&t; * We are going to simply delete the existing semaphore and&n;&t; * create a new one!&n;&t; */
id|status
op_assign
id|acpi_os_create_semaphore
(paren
id|ACPI_NO_UNIT_LIMIT
comma
l_int|0
comma
op_amp
id|temp_semaphore
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
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
id|obj_desc-&gt;mutex.semaphore
op_assign
id|temp_semaphore
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
