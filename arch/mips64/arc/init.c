multiline_comment|/* $Id: init.c,v 1.3 1999/11/19 23:29:05 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * PROM library initialisation code.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
DECL|macro|DEBUG_PROM_INIT
macro_line|#undef DEBUG_PROM_INIT
multiline_comment|/* Master romvec interface. */
DECL|variable|romvec
r_struct
id|linux_romvec
op_star
id|romvec
suffix:semicolon
DECL|variable|sgi_pblock
id|PSYSTEM_PARAMETER_BLOCK
id|sgi_pblock
suffix:semicolon
DECL|variable|prom_argc
r_int
id|prom_argc
suffix:semicolon
DECL|variable|_prom_argv
DECL|variable|_prom_envp
id|LONG
op_star
id|_prom_argv
comma
op_star
id|_prom_envp
suffix:semicolon
DECL|variable|prom_vers
DECL|variable|prom_rev
r_int
r_int
id|prom_vers
comma
id|prom_rev
suffix:semicolon
r_extern
r_void
id|prom_testtree
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|__init
DECL|function|prom_init
id|prom_init
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
)paren
(brace
id|PSYSTEM_PARAMETER_BLOCK
id|pb
suffix:semicolon
id|romvec
op_assign
id|ROMVECTOR
suffix:semicolon
id|pb
op_assign
id|sgi_pblock
op_assign
id|PROMBLOCK
suffix:semicolon
id|prom_argc
op_assign
id|argc
suffix:semicolon
id|_prom_argv
op_assign
(paren
id|LONG
op_star
)paren
id|argv
suffix:semicolon
id|_prom_envp
op_assign
(paren
id|LONG
op_star
)paren
id|envp
suffix:semicolon
r_if
c_cond
(paren
id|pb-&gt;magic
op_ne
l_int|0x53435241
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Aieee, bad prom vector magic %08lx&bslash;n&quot;
comma
id|pb-&gt;magic
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
id|prom_init_cmdline
c_func
(paren
)paren
suffix:semicolon
id|prom_vers
op_assign
id|pb-&gt;ver
suffix:semicolon
id|prom_rev
op_assign
id|pb-&gt;rev
suffix:semicolon
id|prom_identify_arch
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PROMLIB: ARC firmware Version %d Revision %d&bslash;n&quot;
comma
id|prom_vers
comma
id|prom_rev
)paren
suffix:semicolon
id|prom_meminit
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef DEBUG_PROM_INIT
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Press a key to reboot&bslash;n&quot;
)paren
suffix:semicolon
(paren
r_void
)paren
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|ArcEnterInteractiveMode
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
eof
