multiline_comment|/* parser config.in&n; *&n; * Version 1.0&n; * Eric Youngdale&n; * 10/95&n; *&n; * The general idea here is that we want to parse a config.in file and &n; * from this, we generate a wish script which gives us effectively the&n; * same functionality that the original config.in script provided.&n; *&n; * This task is split roughly into 3 parts.  The first parse is the parse&n; * of the input file itself.  The second part is where we analyze the &n; * #ifdef clauses, and attach a linked list of tokens to each of the&n; * menu items.  In this way, each menu item has a complete list of&n; * dependencies that are used to enable/disable the options.&n; * The third part is to take the configuration database we have build,&n; * and build the actual wish script.&n; *&n; * This file contains the code to further process the conditions from&n; * the &quot;ifdef&quot; clauses.&n; *&n; * The conditions are assumed to be one of the folowing formats&n; *&n; * simple_condition:= &quot;$VARIABLE&quot; == y/n/m&n; * simple_condition:= &quot;$VARIABLE != y/n/m&n; *&n; * simple_condition -a simple_condition&n; *&n; * If the input condition contains &squot;(&squot; or &squot;)&squot; it would screw us up, but for now&n; * this is not a problem.&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &quot;tkparse.h&quot;
multiline_comment|/*&n; * Walk a condition chain and invert it so that the logical result is&n; * inverted.&n; */
DECL|function|invert_condition
r_static
r_int
id|invert_condition
c_func
(paren
r_struct
id|condition
op_star
id|cnd
)paren
(brace
multiline_comment|/*&n;   * This is simple.  Just walk through the list, and invert&n;   * all of the operators.&n;   */
r_for
c_loop
(paren
suffix:semicolon
id|cnd
suffix:semicolon
id|cnd
op_assign
id|cnd-&gt;next
)paren
(brace
r_switch
c_cond
(paren
id|cnd-&gt;op
)paren
(brace
r_case
id|op_and
suffix:colon
id|cnd-&gt;op
op_assign
id|op_or
suffix:semicolon
r_break
suffix:semicolon
r_case
id|op_or
suffix:colon
multiline_comment|/*&n;&t;   * This is not turned into op_and - we need to keep track&n;&t;   * of what operators were used here since we have an optimization&n;&t;   * later on to remove duplicate conditions, and having&n;&t;   * inverted ors in there would make it harder if we did not&n;&t;   * distinguish an inverted or from an and we inserted because&n;&t;   * of nested ifs.&n;&t;   */
id|cnd-&gt;op
op_assign
id|op_and1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|op_neq
suffix:colon
id|cnd-&gt;op
op_assign
id|op_eq
suffix:semicolon
r_break
suffix:semicolon
r_case
id|op_eq
suffix:colon
id|cnd-&gt;op
op_assign
id|op_neq
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Walk a condition chain, and free the memory associated with it.&n; */
DECL|function|free_condition
r_static
r_int
id|free_condition
c_func
(paren
r_struct
id|condition
op_star
id|cnd
)paren
(brace
r_struct
id|condition
op_star
id|next
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|cnd
suffix:semicolon
id|cnd
op_assign
id|next
)paren
(brace
id|next
op_assign
id|cnd-&gt;next
suffix:semicolon
r_if
c_cond
(paren
id|cnd-&gt;variable.str
op_ne
l_int|NULL
)paren
(brace
id|free
c_func
(paren
id|cnd-&gt;variable.str
)paren
suffix:semicolon
)brace
id|free
c_func
(paren
id|cnd
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Walk all of the conditions, and look for choice values.  Convert&n; * the tokens into something more digestable.&n; */
DECL|function|fix_choice_cond
r_void
id|fix_choice_cond
c_func
(paren
)paren
(brace
r_struct
id|condition
op_star
id|cond
suffix:semicolon
r_struct
id|condition
op_star
id|cond2
suffix:semicolon
r_struct
id|kconfig
op_star
id|cfg
suffix:semicolon
r_char
id|tmpbuf
(braket
l_int|10
)braket
suffix:semicolon
r_for
c_loop
(paren
id|cfg
op_assign
id|config
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|cfg-&gt;cond
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cond
op_assign
id|cfg-&gt;cond
suffix:semicolon
id|cond
op_ne
l_int|NULL
suffix:semicolon
id|cond
op_assign
id|cond-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|cond-&gt;op
op_ne
id|op_kvariable
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cond-&gt;variable.cfg-&gt;tok
op_ne
id|tok_choice
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   * Look ahead for what we are comparing this to.  There should&n;&t;   * be one operator inbetween.&n;&t;   */
id|cond2
op_assign
id|cond-&gt;next-&gt;next
suffix:semicolon
id|sprintf
c_func
(paren
id|tmpbuf
comma
l_string|&quot;%d&quot;
comma
id|cond-&gt;variable.cfg-&gt;choice_value
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cond2-&gt;variable.str
comma
l_string|&quot;y&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|cond-&gt;variable.cfg
op_assign
id|cond-&gt;variable.cfg-&gt;choice_label
suffix:semicolon
id|cond2-&gt;variable.str
op_assign
id|strdup
c_func
(paren
id|tmpbuf
)paren
suffix:semicolon
)brace
r_else
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Ooops&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
multiline_comment|/*&n; * Walk the stack of conditions, and clone all of them with &quot;&amp;&amp;&quot; operators&n; * gluing them together.  The conditions from each level of the stack&n; * are wrapped in parenthesis so as to guarantee that the results&n; * are logically correct.&n; */
DECL|function|get_token_cond
r_struct
id|condition
op_star
id|get_token_cond
c_func
(paren
r_struct
id|condition
op_star
op_star
id|cond
comma
r_int
id|depth
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|condition
op_star
id|newcond
suffix:semicolon
r_struct
id|condition
op_star
id|tail
suffix:semicolon
r_struct
id|condition
op_star
r_new
suffix:semicolon
r_struct
id|condition
op_star
id|ocond
suffix:semicolon
r_struct
id|kconfig
op_star
id|cfg
suffix:semicolon
id|newcond
op_assign
id|tail
op_assign
l_int|NULL
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
id|depth
suffix:semicolon
id|i
op_increment
comma
id|cond
op_increment
)paren
(brace
multiline_comment|/*&n;       * First insert the left parenthesis&n;       */
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|op_lparen
suffix:semicolon
r_if
c_cond
(paren
id|tail
op_eq
l_int|NULL
)paren
(brace
id|newcond
op_assign
id|tail
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
)brace
multiline_comment|/*&n;       * Now duplicate the chain.&n;       */
id|ocond
op_assign
op_star
id|cond
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|ocond
op_ne
l_int|NULL
suffix:semicolon
id|ocond
op_assign
id|ocond-&gt;next
)paren
(brace
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|ocond-&gt;op
suffix:semicolon
r_if
c_cond
(paren
id|ocond-&gt;variable.str
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|ocond-&gt;op
op_eq
id|op_variable
)paren
(brace
multiline_comment|/*&n;&t;&t;   * Search for structure to insert here.&n;&t;&t;   */
r_for
c_loop
(paren
id|cfg
op_assign
id|config
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|cfg-&gt;tok
op_ne
id|tok_bool
op_logical_and
id|cfg-&gt;tok
op_ne
id|tok_int
op_logical_and
id|cfg-&gt;tok
op_ne
id|tok_tristate
op_logical_and
id|cfg-&gt;tok
op_ne
id|tok_choice
op_logical_and
id|cfg-&gt;tok
op_ne
id|tok_dep_tristate
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cfg-&gt;optionname
comma
id|ocond-&gt;variable.str
)paren
op_eq
l_int|0
)paren
(brace
r_new
op_member_access_from_pointer
id|variable.cfg
op_assign
id|cfg
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|op_kvariable
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cfg
op_eq
l_int|NULL
)paren
(brace
r_new
op_member_access_from_pointer
id|variable.str
op_assign
id|strdup
c_func
(paren
id|ocond-&gt;variable.str
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_new
op_member_access_from_pointer
id|variable.str
op_assign
id|strdup
c_func
(paren
id|ocond-&gt;variable.str
)paren
suffix:semicolon
)brace
)brace
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
)brace
multiline_comment|/*&n;       * Next insert the left parenthesis&n;       */
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|op_rparen
suffix:semicolon
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
multiline_comment|/*&n;       * Insert an and operator, if we have another condition.&n;       */
r_if
c_cond
(paren
id|i
OL
id|depth
op_minus
l_int|1
)paren
(brace
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|op_and
suffix:semicolon
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
)brace
)brace
r_return
id|newcond
suffix:semicolon
)brace
multiline_comment|/*&n; * Walk a single chain of conditions and clone it.  These are assumed&n; * to be created/processed by  get_token_cond in a previous pass.&n; */
DECL|function|get_token_cond_frag
r_struct
id|condition
op_star
id|get_token_cond_frag
c_func
(paren
r_struct
id|condition
op_star
id|cond
comma
r_struct
id|condition
op_star
op_star
id|last
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|condition
op_star
id|newcond
suffix:semicolon
r_struct
id|condition
op_star
id|tail
suffix:semicolon
r_struct
id|condition
op_star
r_new
suffix:semicolon
r_struct
id|condition
op_star
id|ocond
suffix:semicolon
r_struct
id|kconfig
op_star
id|cfg
suffix:semicolon
id|newcond
op_assign
id|tail
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;   * Now duplicate the chain.&n;   */
r_for
c_loop
(paren
id|ocond
op_assign
id|cond
suffix:semicolon
id|ocond
op_ne
l_int|NULL
suffix:semicolon
id|ocond
op_assign
id|ocond-&gt;next
)paren
(brace
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|ocond-&gt;op
suffix:semicolon
r_new
op_member_access_from_pointer
id|variable.cfg
op_assign
id|ocond-&gt;variable.cfg
suffix:semicolon
r_if
c_cond
(paren
id|tail
op_eq
l_int|NULL
)paren
(brace
id|newcond
op_assign
id|tail
op_assign
r_new
suffix:semicolon
)brace
r_else
(brace
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
)brace
)brace
r_new
op_assign
(paren
r_struct
id|condition
op_star
)paren
id|malloc
c_func
(paren
r_sizeof
(paren
r_struct
id|condition
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
r_new
comma
l_int|0
comma
r_sizeof
(paren
op_star
r_new
)paren
)paren
suffix:semicolon
r_new
op_member_access_from_pointer
id|op
op_assign
id|op_and
suffix:semicolon
id|tail-&gt;next
op_assign
r_new
suffix:semicolon
id|tail
op_assign
r_new
suffix:semicolon
op_star
id|last
op_assign
id|tail
suffix:semicolon
r_return
id|newcond
suffix:semicolon
)brace
multiline_comment|/*&n; * Walk through the if conditionals and maintain a chain.&n; */
DECL|function|fix_conditionals
r_int
id|fix_conditionals
c_func
(paren
r_struct
id|kconfig
op_star
id|scfg
)paren
(brace
r_int
id|depth
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|kconfig
op_star
id|cfg
suffix:semicolon
r_struct
id|kconfig
op_star
id|cfg1
suffix:semicolon
r_struct
id|condition
op_star
id|conditions
(braket
l_int|25
)braket
suffix:semicolon
r_struct
id|condition
op_star
id|cnd
suffix:semicolon
r_struct
id|condition
op_star
id|cnd1
suffix:semicolon
r_struct
id|condition
op_star
id|cnd2
suffix:semicolon
r_struct
id|condition
op_star
id|cnd3
suffix:semicolon
r_struct
id|condition
op_star
id|newcond
suffix:semicolon
r_struct
id|condition
op_star
id|last
suffix:semicolon
multiline_comment|/*&n;   * Start by walking the chain.  Every time we see an ifdef, push&n;   * the condition chain on the stack.  When we see an &quot;else&quot;, we invert&n;   * the condition at the top of the stack, and when we see an &quot;endif&quot;&n;   * we free all of the memory for the condition at the top of the stack&n;   * and remove the condition from the top of the stack.&n;   *&n;   * For any other type of token (i.e. a bool), we clone a new condition chain&n;   * by anding together all of the conditions that are currently stored on&n;   * the stack.  In this way, we have a correct representation of whatever&n;   * conditions govern the usage of each option.&n;   */
id|memset
c_func
(paren
id|conditions
comma
l_int|0
comma
r_sizeof
(paren
id|conditions
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|cfg
op_assign
id|scfg
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
r_switch
c_cond
(paren
id|cfg-&gt;tok
)paren
(brace
r_case
id|tok_if
suffix:colon
multiline_comment|/*&n;&t;   * Push this condition on the stack, and nuke the token&n;&t;   * representing the ifdef, since we no longer need it.&n;&t;   */
id|conditions
(braket
id|depth
)braket
op_assign
id|cfg-&gt;cond
suffix:semicolon
id|depth
op_increment
suffix:semicolon
id|cfg-&gt;tok
op_assign
id|tok_nop
suffix:semicolon
id|cfg-&gt;cond
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|tok_else
suffix:colon
multiline_comment|/*&n;&t;   * For an else, we just invert the condition at the top of&n;&t;   * the stack.  This is done in place with no reallocation&n;&t;   * of memory taking place.&n;&t;   */
id|invert_condition
c_func
(paren
id|conditions
(braket
id|depth
op_minus
l_int|1
)braket
)paren
suffix:semicolon
id|cfg-&gt;tok
op_assign
id|tok_nop
suffix:semicolon
r_break
suffix:semicolon
r_case
id|tok_fi
suffix:colon
id|depth
op_decrement
suffix:semicolon
id|free_condition
c_func
(paren
id|conditions
(braket
id|depth
)braket
)paren
suffix:semicolon
id|conditions
(braket
id|depth
)braket
op_assign
l_int|NULL
suffix:semicolon
id|cfg-&gt;tok
op_assign
id|tok_nop
suffix:semicolon
r_break
suffix:semicolon
r_case
id|tok_comment
suffix:colon
r_case
id|tok_define
suffix:colon
r_case
id|tok_menuoption
suffix:colon
r_case
id|tok_bool
suffix:colon
r_case
id|tok_tristate
suffix:colon
r_case
id|tok_dep_tristate
suffix:colon
r_case
id|tok_int
suffix:colon
r_case
id|tok_choice
suffix:colon
multiline_comment|/*&n;&t;   * We need to duplicate the chain of conditions and attach them to&n;&t;   * this token.&n;&t;   */
id|cfg-&gt;cond
op_assign
id|get_token_cond
c_func
(paren
op_amp
id|conditions
(braket
l_int|0
)braket
comma
id|depth
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   * Fix any conditions involving the &quot;choice&quot; operator.&n;   */
id|fix_choice_cond
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;   * Walk through and see if there are multiple options that control the&n;   * same kvariable.  If there are we need to treat them a little bit&n;   * special.&n;   */
r_for
c_loop
(paren
id|cfg
op_assign
id|scfg
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
r_switch
c_cond
(paren
id|cfg-&gt;tok
)paren
(brace
r_case
id|tok_bool
suffix:colon
r_case
id|tok_tristate
suffix:colon
r_case
id|tok_dep_tristate
suffix:colon
r_case
id|tok_int
suffix:colon
r_for
c_loop
(paren
id|cfg1
op_assign
id|cfg
suffix:semicolon
id|cfg1
op_ne
l_int|NULL
suffix:semicolon
id|cfg1
op_assign
id|cfg1-&gt;next
)paren
(brace
r_switch
c_cond
(paren
id|cfg1-&gt;tok
)paren
(brace
r_case
id|tok_define
suffix:colon
r_case
id|tok_bool
suffix:colon
r_case
id|tok_tristate
suffix:colon
r_case
id|tok_dep_tristate
suffix:colon
r_case
id|tok_int
suffix:colon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|cfg-&gt;optionname
comma
id|cfg1-&gt;optionname
)paren
op_eq
l_int|0
)paren
(brace
id|cfg-&gt;flags
op_or_assign
id|CFG_DUP
suffix:semicolon
id|cfg1-&gt;flags
op_or_assign
id|CFG_DUP
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   * Now go through the list, and every time we see a kvariable, check&n;   * to see whether it also has some dependencies.  If so, then&n;   * append it to our list.  The reason we do this is that we might have&n;   * option CONFIG_FOO which is only used if CONFIG_BAR is set.  It may&n;   * turn out that in config.in that the default value for CONFIG_BAR is&n;   * set to &quot;y&quot;, but that CONFIG_BAR is not enabled because CONFIG_XYZZY&n;   * is not set.  The current condition chain does not reflect this, but&n;   * we can fix this by searching for the tokens that this option depends&n;   * upon and cloning the conditions and merging them with the list.&n;   */
r_for
c_loop
(paren
id|cfg
op_assign
id|scfg
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
multiline_comment|/*&n;       * Search for a token that has a condition list.&n;       */
r_if
c_cond
(paren
id|cfg-&gt;cond
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnd
op_assign
id|cfg-&gt;cond
suffix:semicolon
id|cnd
suffix:semicolon
id|cnd
op_assign
id|cnd-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;   * Now search the condition list for a known configuration variable&n;&t;   * that has conditions of it&squot;s own.&n;&t;   */
r_if
c_cond
(paren
id|cnd-&gt;op
op_ne
id|op_kvariable
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnd-&gt;variable.cfg-&gt;cond
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnd-&gt;variable.cfg-&gt;flags
op_amp
id|CFG_DUP
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;   * OK, we have some conditions to append to cfg.  Make  a clone&n;&t;   * of the conditions,&n;&t;   */
id|newcond
op_assign
id|get_token_cond_frag
c_func
(paren
id|cnd-&gt;variable.cfg-&gt;cond
comma
op_amp
id|last
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   * Finally, we splice it into our list.&n;&t;   */
id|last-&gt;next
op_assign
id|cfg-&gt;cond
suffix:semicolon
id|cfg-&gt;cond
op_assign
id|newcond
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;   * There is a strong possibility that we have duplicate conditions&n;   * in here.  It would make the script more efficient and readable to&n;   * remove these.  Here is where we assume here that there are no&n;   * parenthesis in the input script.&n;   */
r_for
c_loop
(paren
id|cfg
op_assign
id|scfg
suffix:semicolon
id|cfg
op_ne
l_int|NULL
suffix:semicolon
id|cfg
op_assign
id|cfg-&gt;next
)paren
(brace
multiline_comment|/*&n;       * Search for configuration options that have conditions.&n;       */
r_if
c_cond
(paren
id|cfg-&gt;cond
op_eq
l_int|NULL
)paren
(brace
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnd
op_assign
id|cfg-&gt;cond
suffix:semicolon
id|cnd
suffix:semicolon
id|cnd
op_assign
id|cnd-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;   * Search for a left parenthesis.&n;&t;   */
r_if
c_cond
(paren
id|cnd-&gt;op
op_ne
id|op_lparen
)paren
(brace
r_continue
suffix:semicolon
)brace
r_for
c_loop
(paren
id|cnd1
op_assign
id|cnd-&gt;next
suffix:semicolon
id|cnd1
suffix:semicolon
id|cnd1
op_assign
id|cnd1-&gt;next
)paren
(brace
multiline_comment|/*&n;&t;       * Search after the previous left parenthesis, and try&n;&t;       * and find a second left parenthesis.&n;&t;       */
r_if
c_cond
(paren
id|cnd1-&gt;op
op_ne
id|op_lparen
)paren
(brace
r_continue
suffix:semicolon
)brace
multiline_comment|/*&n;&t;       * Now compare the next 5 tokens to see if they are&n;&t;       * identical.  We are looking for two chains that&n;&t;       * are like: &squot;(&squot; $VARIABLE operator constant &squot;)&squot;.&n;&t;       */
id|cnd2
op_assign
id|cnd
suffix:semicolon
id|cnd3
op_assign
id|cnd1
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
l_int|5
suffix:semicolon
id|i
op_increment
comma
id|cnd2
op_assign
id|cnd2-&gt;next
comma
id|cnd3
op_assign
id|cnd3-&gt;next
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cnd2
op_logical_or
op_logical_neg
id|cnd3
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnd2-&gt;op
op_ne
id|cnd3-&gt;op
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
op_logical_and
(paren
id|cnd2-&gt;op
op_ne
id|op_kvariable
op_logical_or
id|cnd2-&gt;variable.cfg
op_ne
id|cnd3-&gt;variable.cfg
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|2
op_logical_and
id|cnd2-&gt;op
op_ne
id|op_eq
op_logical_and
id|cnd2-&gt;op
op_ne
id|op_neq
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|3
op_logical_and
id|cnd2-&gt;op
op_ne
id|op_constant
op_logical_and
id|strcmp
c_func
(paren
id|cnd2-&gt;variable.str
comma
id|cnd3-&gt;variable.str
)paren
op_ne
l_int|0
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|4
op_logical_and
id|cnd2-&gt;op
op_ne
id|op_rparen
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;       * If these match, and there is an and gluing these together,&n;&t;       * then we can nuke the second one.&n;&t;       */
r_if
c_cond
(paren
id|i
op_eq
l_int|5
op_logical_and
(paren
(paren
id|cnd3
op_logical_and
id|cnd3-&gt;op
op_eq
id|op_and
)paren
op_logical_or
(paren
id|cnd2
op_logical_and
id|cnd2-&gt;op
op_eq
id|op_and
)paren
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;   * We have a duplicate.  Nuke 5 ops.&n;&t;&t;   */
id|cnd3
op_assign
id|cnd1
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
l_int|5
suffix:semicolon
id|i
op_increment
comma
id|cnd3
op_assign
id|cnd3-&gt;next
)paren
(brace
id|cnd3-&gt;op
op_assign
id|op_nuked
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;   * Nuke the and that glues the conditions together.&n;&t;&t;   */
r_if
c_cond
(paren
id|cnd3
op_logical_and
id|cnd3-&gt;op
op_eq
id|op_and
)paren
(brace
id|cnd3-&gt;op
op_assign
id|op_nuked
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|cnd2
op_logical_and
id|cnd2-&gt;op
op_eq
id|op_and
)paren
(brace
id|cnd2-&gt;op
op_assign
id|op_nuked
suffix:semicolon
)brace
)brace
)brace
)brace
)brace
)brace
eof
