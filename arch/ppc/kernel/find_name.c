macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;strings.h&gt;
multiline_comment|/*&n; * Finds a given address in the System.map and prints it out&n; * with its neighbors.  -- Cort&n; */
DECL|function|main
r_int
id|main
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
r_int
id|addr
comma
id|cmp
comma
id|i
suffix:semicolon
id|FILE
op_star
id|f
suffix:semicolon
r_char
id|s
(braket
l_int|256
)braket
comma
id|last
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|argc
OL
l_int|2
)paren
(brace
id|fprintf
c_func
(paren
id|stderr
comma
l_string|&quot;Usage: %s &lt;address&gt;&bslash;n&quot;
comma
id|argv
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|argv
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|sscanf
c_func
(paren
id|argv
(braket
id|i
)braket
comma
l_string|&quot;%0lx&quot;
comma
op_amp
id|addr
)paren
suffix:semicolon
multiline_comment|/* adjust if addr is relative to kernelbase */
r_if
c_cond
(paren
id|addr
OL
id|PAGE_OFFSET
)paren
id|addr
op_add_assign
id|PAGE_OFFSET
suffix:semicolon
r_if
c_cond
(paren
(paren
id|f
op_assign
id|fopen
c_func
(paren
l_string|&quot;System.map&quot;
comma
l_string|&quot;r&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;fopen()&bslash;n&quot;
)paren
suffix:semicolon
m_exit
(paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
op_logical_neg
id|feof
c_func
(paren
id|f
)paren
)paren
(brace
id|fgets
c_func
(paren
id|s
comma
l_int|255
comma
id|f
)paren
suffix:semicolon
id|sscanf
c_func
(paren
id|s
comma
l_string|&quot;%0lx&quot;
comma
op_amp
id|cmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|cmp
)paren
r_break
suffix:semicolon
id|strcpy
c_func
(paren
id|last
comma
id|s
)paren
suffix:semicolon
)brace
id|printf
c_func
(paren
l_string|&quot;%s%s&quot;
comma
id|last
comma
id|s
)paren
suffix:semicolon
)brace
id|fclose
c_func
(paren
id|f
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
