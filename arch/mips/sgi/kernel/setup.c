multiline_comment|/* $Id: setup.c,v 1.1 1997/06/06 09:36:33 ralf Exp $&n; * setup.c: SGI specific setup, including init of the feature struct.&n; *&n; * Copyright (C) 1996 David S. Miller (dm@engr.sgi.com)&n; */
macro_line|#ifndef __GOGOGO__
macro_line|#error &quot;... about to fuckup your Indy?&quot;
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/reboot.h&gt;
macro_line|#include &lt;asm/vector.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/sgi.h&gt;
macro_line|#include &lt;asm/sgimc.h&gt;
macro_line|#include &lt;asm/sgihpc.h&gt;
macro_line|#include &lt;asm/sgint23.h&gt;
r_extern
r_int
id|serial_console
suffix:semicolon
multiline_comment|/* in console.c, of course */
r_extern
r_void
id|sgi_machine_restart
c_func
(paren
r_char
op_star
id|command
)paren
suffix:semicolon
r_extern
r_void
id|sgi_machine_halt
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sgi_machine_power_off
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|sgi_feature
r_struct
id|feature
id|sgi_feature
op_assign
(brace
)brace
suffix:semicolon
DECL|function|sgi_irq_setup
r_static
r_void
id|sgi_irq_setup
c_func
(paren
r_void
)paren
(brace
id|sgint_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
r_extern
r_void
id|register_console
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_const
r_char
op_star
)paren
)paren
suffix:semicolon
r_static
r_void
id|sgi_print
c_func
(paren
r_const
r_char
op_star
id|p
)paren
(brace
r_char
id|c
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|p
op_increment
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|prom_putchar
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
id|prom_putchar
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|sgi_setup
r_void
id|sgi_setup
c_func
(paren
r_void
)paren
(brace
r_char
op_star
id|ctype
suffix:semicolon
id|irq_setup
op_assign
id|sgi_irq_setup
suffix:semicolon
id|feature
op_assign
op_amp
id|sgi_feature
suffix:semicolon
id|_machine_restart
op_assign
id|sgi_machine_restart
suffix:semicolon
id|_machine_halt
op_assign
id|sgi_machine_halt
suffix:semicolon
id|_machine_power_off
op_assign
id|sgi_machine_power_off
suffix:semicolon
multiline_comment|/* register_console(sgi_print); */
id|sgi_sysinit
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init the INDY HPC I/O controller.  Need to call this before&n;&t; * fucking with the memory controller because it needs to know the&n;&t; * boardID and whether this is a Guiness or a FullHouse machine.&n;&t; */
id|sgihpc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Init INDY memory controller. */
id|sgimc_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* ARCS console environment variable is set to &quot;g?&quot; for&n;&t; * graphics console, it is set to &quot;d&quot; for the first serial&n;&t; * line and &quot;d2&quot; for the second serial line.&n;&t; */
id|ctype
op_assign
id|prom_getenv
c_func
(paren
l_string|&quot;console&quot;
)paren
suffix:semicolon
id|serial_console
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ctype
op_eq
l_char|&squot;d&squot;
)paren
(brace
r_if
c_cond
(paren
op_star
(paren
id|ctype
op_plus
l_int|1
)paren
op_eq
l_char|&squot;2&squot;
)paren
(brace
id|serial_console
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|serial_console
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|serial_console
)paren
(brace
id|prom_printf
c_func
(paren
l_string|&quot;Weird console env setting %s&bslash;n&quot;
comma
id|ctype
)paren
suffix:semicolon
id|prom_printf
c_func
(paren
l_string|&quot;Press a key to reboot.&bslash;n&quot;
)paren
suffix:semicolon
id|prom_getchar
c_func
(paren
)paren
suffix:semicolon
id|prom_imode
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
eof
