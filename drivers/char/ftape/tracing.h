macro_line|#ifndef _TRACING_H
DECL|macro|_TRACING_H
mdefine_line|#define _TRACING_H
multiline_comment|/*&n; * Copyright (C) 1994-1995 Bas Laarhoven.&n;&n; This program is free software; you can redistribute it and/or modify&n; it under the terms of the GNU General Public License as published by&n; the Free Software Foundation; either version 2, or (at your option)&n; any later version.&n;&n; This program is distributed in the hope that it will be useful,&n; but WITHOUT ANY WARRANTY; without even the implied warranty of&n; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; GNU General Public License for more details.&n;&n; You should have received a copy of the GNU General Public License&n; along with this program; see the file COPYING.  If not, write to&n; the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n;&n; *&n; $Source: /home/bas/distr/ftape-2.03b/RCS/tracing.h,v $&n; $Author: bas $&n; *&n; $Revision: 1.10 $&n; $Date: 1995/04/22 07:30:15 $&n; $State: Beta $&n; *&n; *      This file contains definitions that eases the debugging&n; *      of the QIC-40/80 floppy-tape driver for Linux.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifdef NO_TRACE_AT_ALL
DECL|function|trace_dummy
r_static
r_inline
r_void
id|trace_dummy
c_func
(paren
r_void
)paren
(brace
)brace
DECL|macro|TRACE_FUN
mdefine_line|#define TRACE_FUN( level, name) int _trace_dummy
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT              _trace_dummy= 0
DECL|macro|TRACE_
mdefine_line|#define TRACE_(l,m)             trace_dummy()
DECL|macro|TRACE
mdefine_line|#define TRACE(l,m)              trace_dummy()
DECL|macro|TRACEi
mdefine_line|#define TRACEi(l,m,i)           trace_dummy()
DECL|macro|TRACElx
mdefine_line|#define TRACElx(l,m,i)          trace_dummy()
DECL|macro|TRACEx1
mdefine_line|#define TRACEx1(l,m,a)          trace_dummy()
DECL|macro|TRACEx2
mdefine_line|#define TRACEx2(l,m,a,b)        trace_dummy()
DECL|macro|TRACEx3
mdefine_line|#define TRACEx3(l,m,a,b,c)      trace_dummy()
DECL|macro|TRACEx4
mdefine_line|#define TRACEx4(l,m,a,b,c,d)    trace_dummy()
DECL|macro|TRACEx5
mdefine_line|#define TRACEx5(l,m,a,b,c,d,e)  trace_dummy()
DECL|macro|TRACEx6
mdefine_line|#define TRACEx6(l,m,a,b,c,d,e,f)  trace_dummy()
macro_line|#else
macro_line|#ifdef NO_TRACE
DECL|macro|TOP_LEVEL
mdefine_line|#define TOP_LEVEL 2
macro_line|#else
DECL|macro|TOP_LEVEL
mdefine_line|#define TOP_LEVEL 10
macro_line|#endif
DECL|macro|TRACE_FUN
mdefine_line|#define TRACE_FUN( level, name) &bslash;&n;  char _trace_fun[] = name; &bslash;&n;  int _function_nest_level = trace_call( level, __FILE__, _trace_fun); &bslash;&n;  int _tracing = level
DECL|macro|TRACE_EXIT
mdefine_line|#define TRACE_EXIT &bslash;&n;  function_nest_level = _function_nest_level; &bslash;&n;  trace_exit( _tracing, __FILE__, _trace_fun)
DECL|macro|TRACE_
mdefine_line|#define TRACE_(l,m) &bslash;&n;{ &bslash;&n;  if (tracing &gt;= (l) &amp;&amp; (l) &lt;= TOP_LEVEL) { &bslash;&n;    trace_log( __FILE__, _trace_fun); &bslash;&n;    m; &bslash;&n;  } &bslash;&n;}
DECL|macro|TRACE
mdefine_line|#define TRACE(l,m) TRACE_(l,printk(m&quot;.&bslash;n&quot;))
DECL|macro|TRACEi
mdefine_line|#define TRACEi(l,m,i) TRACE_(l,printk(m&quot; %d.&bslash;n&quot;,i))
DECL|macro|TRACElx
mdefine_line|#define TRACElx(l,m,i) TRACE_(l,printk(m&quot; 0x%08lx.&bslash;n&quot;,i))
DECL|macro|TRACEx1
mdefine_line|#define TRACEx1(l,m,a) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a))
DECL|macro|TRACEx2
mdefine_line|#define TRACEx2(l,m,a,b) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a,b))
DECL|macro|TRACEx3
mdefine_line|#define TRACEx3(l,m,a,b,c) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a,b,c))
DECL|macro|TRACEx4
mdefine_line|#define TRACEx4(l,m,a,b,c,d) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a,b,c,d))
DECL|macro|TRACEx5
mdefine_line|#define TRACEx5(l,m,a,b,c,d,e) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a,b,c,d,e))
DECL|macro|TRACEx6
mdefine_line|#define TRACEx6(l,m,a,b,c,d,e,f) TRACE_(l,printk(m&quot;.&bslash;n&quot;,a,b,c,d,e,f))
multiline_comment|/*      Global variables declared in tracing.c&n; */
r_extern
r_int
r_char
id|trace_id
suffix:semicolon
r_extern
r_int
id|tracing
suffix:semicolon
multiline_comment|/* sets default level */
r_extern
r_int
id|function_nest_level
suffix:semicolon
multiline_comment|/*      Global functions declared in tracing.c&n; */
r_extern
r_int
id|trace_call
c_func
(paren
r_int
id|level
comma
r_char
op_star
id|file
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|trace_exit
c_func
(paren
r_int
id|level
comma
r_char
op_star
id|file
comma
r_char
op_star
id|name
)paren
suffix:semicolon
r_extern
r_void
id|trace_log
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif&t;&t;&t;&t;/* NO_TRACE_AT_ALL */
macro_line|#endif
eof
