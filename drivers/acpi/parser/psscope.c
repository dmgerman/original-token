multiline_comment|/******************************************************************************&n; *&n; * Module Name: psscope - Parser scope stack management routines&n; *              $Revision: 22 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          PARSER
id|MODULE_NAME
(paren
l_string|&quot;psscope&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_parent_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to an Op object&n; *&n; * DESCRIPTION: Get parent of current op being parsed&n; *&n; ******************************************************************************/
id|ACPI_PARSE_OBJECT
op_star
DECL|function|acpi_ps_get_parent_scope
id|acpi_ps_get_parent_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
)paren
(brace
r_return
(paren
id|parser_state-&gt;scope-&gt;parse_scope.op
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_has_completed_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Boolean, TRUE = scope completed.&n; *&n; * DESCRIPTION: Is parsing of current argument complete?  Determined by&n; *              1) AML pointer is at or beyond the end of the scope&n; *              2) The scope argument count has reached zero.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ps_has_completed_scope
id|acpi_ps_has_completed_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
)paren
(brace
r_return
(paren
(paren
id|u8
)paren
(paren
(paren
id|parser_state-&gt;aml
op_ge
id|parser_state-&gt;scope-&gt;parse_scope.arg_end
op_logical_or
op_logical_neg
id|parser_state-&gt;scope-&gt;parse_scope.arg_count
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_init_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Root                - the Root Node of this new scope&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Allocate and init a new scope object&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ps_init_scope
id|acpi_ps_init_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|root_op
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|scope
suffix:semicolon
id|scope
op_assign
id|acpi_cm_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|scope-&gt;parse_scope.op
op_assign
id|root_op
suffix:semicolon
id|scope-&gt;parse_scope.arg_count
op_assign
id|ACPI_VAR_ARGS
suffix:semicolon
id|scope-&gt;parse_scope.arg_end
op_assign
id|parser_state-&gt;aml_end
suffix:semicolon
id|scope-&gt;parse_scope.pkg_end
op_assign
id|parser_state-&gt;aml_end
suffix:semicolon
id|parser_state-&gt;scope
op_assign
id|scope
suffix:semicolon
id|parser_state-&gt;start_op
op_assign
id|root_op
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_push_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Op                  - Current op to be pushed&n; *              Remaining_args      - List of args remaining&n; *              Arg_count           - Fixed or variable number of args&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Push current op to begin parsing its argument&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ps_push_scope
id|acpi_ps_push_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|u32
id|remaining_args
comma
id|u32
id|arg_count
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|scope
suffix:semicolon
id|scope
op_assign
id|acpi_cm_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|scope-&gt;parse_scope.op
op_assign
id|op
suffix:semicolon
id|scope-&gt;parse_scope.arg_list
op_assign
id|remaining_args
suffix:semicolon
id|scope-&gt;parse_scope.arg_count
op_assign
id|arg_count
suffix:semicolon
id|scope-&gt;parse_scope.pkg_end
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
multiline_comment|/* Push onto scope stack */
id|acpi_cm_push_generic_state
(paren
op_amp
id|parser_state-&gt;scope
comma
id|scope
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg_count
op_eq
id|ACPI_VAR_ARGS
)paren
(brace
multiline_comment|/* multiple arguments */
id|scope-&gt;parse_scope.arg_end
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* single argument */
id|scope-&gt;parse_scope.arg_end
op_assign
id|ACPI_MAX_AML
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_pop_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Op                  - Where the popped op is returned&n; *              Arg_list            - Where the popped &quot;next argument&quot; is&n; *                                    returned&n; *              Arg_count           - Count of objects in Arg_list&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Return to parsing a previous op&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_pop_scope
id|acpi_ps_pop_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
comma
id|ACPI_PARSE_OBJECT
op_star
op_star
id|op
comma
id|u32
op_star
id|arg_list
comma
id|u32
op_star
id|arg_count
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|scope
op_assign
id|parser_state-&gt;scope
suffix:semicolon
multiline_comment|/*&n;&t; * Only pop the scope if there is in fact a next scope&n;&t; */
r_if
c_cond
(paren
id|scope-&gt;common.next
)paren
(brace
id|scope
op_assign
id|acpi_cm_pop_generic_state
(paren
op_amp
id|parser_state-&gt;scope
)paren
suffix:semicolon
multiline_comment|/* return to parsing previous op */
op_star
id|op
op_assign
id|scope-&gt;parse_scope.op
suffix:semicolon
op_star
id|arg_list
op_assign
id|scope-&gt;parse_scope.arg_list
suffix:semicolon
op_star
id|arg_count
op_assign
id|scope-&gt;parse_scope.arg_count
suffix:semicolon
id|parser_state-&gt;pkg_end
op_assign
id|scope-&gt;parse_scope.pkg_end
suffix:semicolon
multiline_comment|/* All done with this scope state structure */
id|acpi_cm_delete_generic_state
(paren
id|scope
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* empty parse stack, prepare to fetch next opcode */
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
op_star
id|arg_list
op_assign
l_int|0
suffix:semicolon
op_star
id|arg_count
op_assign
l_int|0
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_cleanup_scope&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Destroy available list, remaining stack levels, and return&n; *              root scope&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_cleanup_scope
id|acpi_ps_cleanup_scope
(paren
id|ACPI_PARSE_STATE
op_star
id|parser_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|scope
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parser_state
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Delete anything on the scope stack */
r_while
c_loop
(paren
id|parser_state-&gt;scope
)paren
(brace
id|scope
op_assign
id|acpi_cm_pop_generic_state
(paren
op_amp
id|parser_state-&gt;scope
)paren
suffix:semicolon
id|acpi_cm_delete_generic_state
(paren
id|scope
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
