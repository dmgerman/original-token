multiline_comment|/*&n; * NET3:&t;Garbage Collector For AF_UNIX sockets (STUB)&n; *&n; * Authors:&t;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; * Fixes:&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/un.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/socket.h&gt;
macro_line|#include &lt;linux/sockios.h&gt;
macro_line|#include &lt;linux/net.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;net/sock.h&gt;
macro_line|#include &lt;net/tcp.h&gt;
macro_line|#include &lt;net/af_unix.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
multiline_comment|/*&n; *&t;Garbage Collector Stubs&n; */
DECL|variable|unix_gc_free
r_int
id|unix_gc_free
op_assign
l_int|128
suffix:semicolon
multiline_comment|/* GC slots free */
DECL|function|unix_gc_remove
r_void
id|unix_gc_remove
c_func
(paren
r_struct
id|file
op_star
id|fp
)paren
(brace
suffix:semicolon
)brace
DECL|function|unix_gc_add
r_void
id|unix_gc_add
c_func
(paren
r_struct
id|sock
op_star
id|sk
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
suffix:semicolon
)brace
eof
