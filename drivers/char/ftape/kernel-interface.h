macro_line|#ifndef _KERNEL_INTERFACE_H
DECL|macro|_KERNEL_INTERFACE_H
mdefine_line|#define _KERNEL_INTERFACE_H
multiline_comment|/*&n; * Copyright (C) 1993-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/kernel-interface.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.24 $&n; $Date: 1995/04/30 13:15:14 $&n; $State: Beta $&n; *&n; * ----Description----&n; *&n; */
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_NEVER_BLOCK
mdefine_line|#define _NEVER_BLOCK    (_S(SIGKILL)|_S(SIGSTOP))
DECL|macro|_DONT_BLOCK
mdefine_line|#define _DONT_BLOCK     (_NEVER_BLOCK|_S(SIGINT))
DECL|macro|_DO_BLOCK
mdefine_line|#define _DO_BLOCK       (_S(SIGPIPE))
DECL|macro|_BLOCK_ALL
mdefine_line|#define _BLOCK_ALL      (0xffffffffL)
macro_line|#ifndef QIC117_TAPE_MAJOR
DECL|macro|QIC117_TAPE_MAJOR
mdefine_line|#define QIC117_TAPE_MAJOR 27
macro_line|#endif
DECL|macro|FTAPE_NO_REWIND
mdefine_line|#define FTAPE_NO_REWIND 4&t;/* mask for minor nr */
multiline_comment|/*      kernel-interface.c defined global variables.&n; */
r_extern
id|byte
op_star
id|tape_buffer
(braket
)braket
suffix:semicolon
r_extern
r_char
id|kernel_version
(braket
)braket
suffix:semicolon
multiline_comment|/*      kernel-interface.c defined global functions.&n; */
id|asmlinkage
r_extern
r_int
id|init_module
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_extern
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*      kernel global functions not (yet) standard accessible&n; *      (linked at load time by modules package).&n; */
id|asmlinkage
r_extern
id|sys_sgetmask
c_func
(paren
r_void
)paren
suffix:semicolon
id|asmlinkage
r_extern
id|sys_ssetmask
c_func
(paren
r_int
)paren
suffix:semicolon
macro_line|#endif
eof
