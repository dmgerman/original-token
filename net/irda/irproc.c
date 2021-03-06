multiline_comment|/*********************************************************************&n; *                &n; * Filename:      irproc.c&n; * Version:       1.0&n; * Description:   Various entries in the /proc file system&n; * Status:        Experimental.&n; * Author:        Thomas Davis, &lt;ratbert@radiks.net&gt;&n; * Created at:    Sat Feb 21 21:33:24 1998&n; * Modified at:   Sun Nov 14 08:54:54 1999&n; * Modified by:   Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *&n; *     Copyright (c) 1998-1999, Dag Brattli &lt;dagb@cs.uit.no&gt;&n; *     Copyright (c) 1998, Thomas Davis, &lt;ratbert@radiks.net&gt;, &n; *     All Rights Reserved.&n; *      &n; *     This program is free software; you can redistribute it and/or &n; *     modify it under the terms of the GNU General Public License as &n; *     published by the Free Software Foundation; either version 2 of &n; *     the License, or (at your option) any later version.&n; *  &n; *     I, Thomas Davis, provide no warranty for any of this software. &n; *     This material is provided &quot;AS-IS&quot; and at no charge. &n; *     &n; ********************************************************************/
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;net/irda/irda.h&gt;
macro_line|#include &lt;net/irda/irmod.h&gt;
macro_line|#include &lt;net/irda/irlap.h&gt;
macro_line|#include &lt;net/irda/irlmp.h&gt;
r_extern
r_int
id|irlap_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|irlmp_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|irttp_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|irias_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_int
id|discovery_proc_read
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
suffix:semicolon
DECL|struct|irda_entry
r_struct
id|irda_entry
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|fn
r_int
(paren
op_star
id|fn
)paren
(paren
r_char
op_star
comma
r_char
op_star
op_star
comma
id|off_t
comma
r_int
)paren
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|proc_irda
r_struct
id|proc_dir_entry
op_star
id|proc_irda
suffix:semicolon
DECL|variable|dir
r_static
r_struct
id|irda_entry
id|dir
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;discovery&quot;
comma
id|discovery_proc_read
)brace
comma
(brace
l_string|&quot;irttp&quot;
comma
id|irttp_proc_read
)brace
comma
(brace
l_string|&quot;irlmp&quot;
comma
id|irlmp_proc_read
)brace
comma
(brace
l_string|&quot;irlap&quot;
comma
id|irlap_proc_read
)brace
comma
(brace
l_string|&quot;irias&quot;
comma
id|irias_proc_read
)brace
comma
)brace
suffix:semicolon
DECL|macro|IRDA_ENTRIES_NUM
mdefine_line|#define IRDA_ENTRIES_NUM (sizeof(dir)/sizeof(dir[0]))
multiline_comment|/*&n; * Function irda_proc_register (void)&n; *&n; *    Register irda entry in /proc file system&n; *&n; */
DECL|function|irda_proc_register
r_void
id|irda_proc_register
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|proc_irda
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;net/irda&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|proc_irda-&gt;owner
op_assign
id|THIS_MODULE
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
id|IRDA_ENTRIES_NUM
suffix:semicolon
id|i
op_increment
)paren
id|create_proc_info_entry
c_func
(paren
id|dir
(braket
id|i
)braket
dot
id|name
comma
l_int|0
comma
id|proc_irda
comma
id|dir
(braket
id|i
)braket
dot
id|fn
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Function irda_proc_unregister (void)&n; *&n; *    Unregister irda entry in /proc file system&n; *&n; */
DECL|function|irda_proc_unregister
r_void
id|irda_proc_unregister
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|IRDA_ENTRIES_NUM
suffix:semicolon
id|i
op_increment
)paren
id|remove_proc_entry
c_func
(paren
id|dir
(braket
id|i
)braket
dot
id|name
comma
id|proc_irda
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
l_string|&quot;net/irda&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
eof
