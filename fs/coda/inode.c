multiline_comment|/*&n; * Inode operations for Coda filesystem&n; * Original version: (C) 1996 P. Braam and M. Callahan&n; * Rewritten for Linux 2.1. (C) 1997 Carnegie Mellon University&n; * &n; * Carnegie Mellon encourages users to contribute improvements to&n; * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/locks.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/coda.h&gt;
macro_line|#include &lt;linux/coda_linux.h&gt;
macro_line|#include &lt;linux/coda_psdev.h&gt;
macro_line|#include &lt;linux/coda_cnode.h&gt;
macro_line|#include &lt;linux/coda_namecache.h&gt;
multiline_comment|/* prototypes */
r_static
r_int
id|coda_readpage
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_static
r_int
id|coda_cnode_makectl
c_func
(paren
r_struct
id|inode
op_star
op_star
id|inode
comma
r_struct
id|super_block
op_star
id|sb
)paren
suffix:semicolon
eof
