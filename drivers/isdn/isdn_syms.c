multiline_comment|/* $Id: isdn_syms.c,v 1.3 1997/02/16 01:02:47 fritz Exp $&n;&n; * Linux ISDN subsystem, exported symbols (linklevel).&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * $Log: isdn_syms.c,v $&n; * Revision 1.3  1997/02/16 01:02:47  fritz&n; * Added GPL-Header, Id and Log&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#ifndef __GENKSYMS__      /* Don&squot;t want genksyms report unneeded structs */
macro_line|#include &lt;linux/isdn.h&gt;
macro_line|#endif
macro_line|#include &quot;isdn_common.h&quot;
macro_line|#if (LINUX_VERSION_CODE &lt; 0x020111)
DECL|variable|has_exported
r_static
r_int
id|has_exported
suffix:semicolon
DECL|variable|isdn_syms
r_static
r_struct
id|symbol_table
id|isdn_syms
op_assign
(brace
macro_line|#include &lt;linux/symtab_begin.h&gt;
id|X
c_func
(paren
id|register_isdn
)paren
comma
macro_line|#include &lt;linux/symtab_end.h&gt;
)brace
suffix:semicolon
r_void
DECL|function|isdn_export_syms
id|isdn_export_syms
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|has_exported
)paren
r_return
suffix:semicolon
id|register_symtab
c_func
(paren
op_amp
id|isdn_syms
)paren
suffix:semicolon
id|has_exported
op_assign
l_int|1
suffix:semicolon
)brace
macro_line|#else
DECL|variable|register_isdn
id|EXPORT_SYMBOL
c_func
(paren
id|register_isdn
)paren
suffix:semicolon
macro_line|#endif
eof
