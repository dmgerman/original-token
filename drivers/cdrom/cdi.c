multiline_comment|/* -- cdi.c&n; *&n; *    Initialisation of software configurable cdrom interface &n; *    cards goes here.&n; *&n; *    Copyright (c) 1996 Eric van der Maarel &lt;H.T.M.v.d.Maarel@marin.nl&gt;&n; *&n; *    Version 0.1&n; *&n; *    History:&n; *    0.1 First release. Only support for ISP16/MAD16/Mozart.&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2 of the License, or&n; *    (at your option) any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/blk.h&gt;  /* where the proto type of cdi_init() is */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#ifdef CONFIG_ISP16_CDI
macro_line|#include &lt;linux/isp16.h&gt;
macro_line|#endif CONFIG_ISP16_CDI
multiline_comment|/*&n; *  Cdrom interface configuration.&n; */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|cdi_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
id|ret_val
op_assign
op_minus
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_ISP16_CDI
id|ret_val
op_and_assign
id|isp16_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif CONFIG_ISP16_CDI
r_return
id|ret_val
suffix:semicolon
)brace
eof
