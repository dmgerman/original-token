multiline_comment|/* $Id: misc.c,v 1.6 1997/04/10 05:13:05 davem Exp $&n; * misc.c:  Miscellaneous prom functions that don&squot;t belong&n; *          anywhere else.&n; *&n; * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)&n; * Copyright (C) 1996,1997 Jakub Jelinek (jj@sunsite.mff.cuni.cz)&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/openprom.h&gt;
macro_line|#include &lt;asm/oplib.h&gt;
multiline_comment|/* Reset and reboot the machine with the command &squot;bcommand&squot;. */
r_void
DECL|function|prom_reboot
id|prom_reboot
c_func
(paren
r_char
op_star
id|bcommand
)paren
(brace
id|p1275_cmd
(paren
l_string|&quot;boot&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|0
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|0
)paren
comma
id|bcommand
)paren
suffix:semicolon
)brace
multiline_comment|/* Forth evaluate the expression contained in &squot;fstring&squot;. */
r_void
DECL|function|prom_feval
id|prom_feval
c_func
(paren
r_char
op_star
id|fstring
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|fstring
op_logical_or
id|fstring
(braket
l_int|0
)braket
op_eq
l_int|0
)paren
(brace
r_return
suffix:semicolon
)brace
id|p1275_cmd
(paren
l_string|&quot;interpret&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|0
comma
id|P1275_ARG_IN_STRING
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|fstring
)paren
suffix:semicolon
)brace
multiline_comment|/* We want to do this more nicely some day. */
macro_line|#ifdef CONFIG_SUN_CONSOLE
r_extern
r_void
id|console_restore_palette
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|set_palette
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|serial_console
suffix:semicolon
macro_line|#endif
multiline_comment|/* Drop into the prom, with the chance to continue with the &squot;go&squot;&n; * prom command.&n; */
multiline_comment|/* XXX Fix the pre and post calls as it locks up my Ultra at the moment -DaveM */
r_void
DECL|function|prom_cmdline
id|prom_cmdline
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|kernel_enter_debugger
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|install_obp_ticker
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|install_linux_ticker
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
multiline_comment|/* kernel_enter_debugger(); */
macro_line|#ifdef CONFIG_SUN_CONSOLE
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
(brace
id|console_restore_palette
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
multiline_comment|/* install_obp_ticker(); */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|p1275_cmd
(paren
l_string|&quot;enter&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* install_linux_ticker(); */
macro_line|#ifdef CONFIG_SUN_CONSOLE
macro_line|#if 0
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
(brace
id|set_palette
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
)brace
multiline_comment|/* Drop into the prom, but completely terminate the program.&n; * No chance of continuing.&n; */
r_void
DECL|function|prom_halt
id|prom_halt
c_func
(paren
r_void
)paren
(brace
id|again
suffix:colon
id|p1275_cmd
(paren
l_string|&quot;exit&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
r_goto
id|again
suffix:semicolon
multiline_comment|/* PROM is out to get me -DaveM */
)brace
multiline_comment|/* Set prom sync handler to call function &squot;funcp&squot;. */
r_void
DECL|function|prom_setsync
id|prom_setsync
c_func
(paren
id|sync_func_t
id|funcp
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|funcp
)paren
(brace
r_return
suffix:semicolon
)brace
id|p1275_cmd
(paren
l_string|&quot;set-callback&quot;
comma
id|P1275_ARG
c_func
(paren
l_int|0
comma
id|P1275_ARG_IN_FUNCTION
)paren
op_or
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|1
)paren
comma
id|funcp
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the idprom and stuff it into buffer &squot;idbuf&squot;.  Returns the&n; * format type.  &squot;num_bytes&squot; is the number of bytes that your idbuf&n; * has space for.  Returns 0xff on error.&n; */
r_int
r_char
DECL|function|prom_get_idprom
id|prom_get_idprom
c_func
(paren
r_char
op_star
id|idbuf
comma
r_int
id|num_bytes
)paren
(brace
r_int
id|len
suffix:semicolon
id|len
op_assign
id|prom_getproplen
c_func
(paren
id|prom_root_node
comma
l_string|&quot;idprom&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
OG
id|num_bytes
)paren
op_logical_or
(paren
id|len
op_eq
op_minus
l_int|1
)paren
)paren
(brace
r_return
l_int|0xff
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|prom_getproperty
c_func
(paren
id|prom_root_node
comma
l_string|&quot;idprom&quot;
comma
id|idbuf
comma
id|num_bytes
)paren
)paren
(brace
r_return
id|idbuf
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_return
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Get the major prom version number. */
r_int
DECL|function|prom_version
id|prom_version
c_func
(paren
r_void
)paren
(brace
r_return
id|PROM_P1275
suffix:semicolon
)brace
multiline_comment|/* Get the prom plugin-revision. */
r_int
DECL|function|prom_getrev
id|prom_getrev
c_func
(paren
r_void
)paren
(brace
r_return
id|prom_rev
suffix:semicolon
)brace
multiline_comment|/* Get the prom firmware print revision. */
r_int
DECL|function|prom_getprev
id|prom_getprev
c_func
(paren
r_void
)paren
(brace
r_return
id|prom_prev
suffix:semicolon
)brace
multiline_comment|/* Install Linux trap table so PROM uses that instead of it&squot;s own. */
DECL|function|prom_set_trap_table
r_void
id|prom_set_trap_table
c_func
(paren
r_int
r_int
id|tba
)paren
(brace
id|p1275_cmd
c_func
(paren
l_string|&quot;SUNW,set-trap-table&quot;
comma
id|P1275_INOUT
c_func
(paren
l_int|1
comma
l_int|0
)paren
comma
id|tba
)paren
suffix:semicolon
)brace
eof
