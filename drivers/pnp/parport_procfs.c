multiline_comment|/* $Id: parport_procfs.c,v 1.1.2.2 1997/03/26 17:50:36 phil Exp $&n; * Parallel port /proc interface code.&n; * &n; * Authors: David Campbell &lt;campbell@tirian.che.curtin.edu.au&gt;&n; *          Tim Waugh &lt;tmw20@cam.ac.uk&gt;&n; *&n; * based on work by Grant Guenther &lt;grant@torque.net&gt;&n; *              and Philip Blundell &lt;Philip.Blundell@pobox.com&gt;&n; */
macro_line|#include &lt;linux/tasks.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#ifdef CONFIG_PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(NOT_DEFINED)
multiline_comment|/************************************************/
DECL|function|proc_readparport
r_static
r_int
id|proc_readparport
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;proc_readparport&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_writeparport
r_static
r_int
id|proc_writeparport
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
r_int
id|count
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;proc_writeparport&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_parportlseek
r_static
r_int
r_int
id|proc_parportlseek
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|orig
)paren
(brace
r_switch
c_cond
(paren
id|orig
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
r_case
l_int|2
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
DECL|variable|proc_dir_operations
r_static
r_struct
id|file_operations
id|proc_dir_operations
op_assign
(brace
id|proc_parportlseek
comma
multiline_comment|/* lseek   */
id|proc_readparport
comma
multiline_comment|/* read&t;   */
id|proc_writeparport
comma
multiline_comment|/* write   */
id|proc_readdir
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll    */
l_int|NULL
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
multiline_comment|/************************************************/
DECL|variable|parport_proc_dir_inode_operations
r_static
r_struct
id|inode_operations
id|parport_proc_dir_inode_operations
op_assign
(brace
op_amp
id|proc_dir_operations
comma
multiline_comment|/* default net directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
id|proc_lookup
comma
multiline_comment|/* lookup */
l_int|NULL
comma
multiline_comment|/* link */
l_int|NULL
comma
multiline_comment|/* unlink */
l_int|NULL
comma
multiline_comment|/* symlink */
l_int|NULL
comma
multiline_comment|/* mkdir */
l_int|NULL
comma
multiline_comment|/* rmdir */
l_int|NULL
comma
multiline_comment|/* mknod */
l_int|NULL
comma
multiline_comment|/* rename */
l_int|NULL
comma
multiline_comment|/* readlink */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage */
l_int|NULL
comma
multiline_comment|/* writepage */
l_int|NULL
comma
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
DECL|variable|proc_root_parport
r_static
r_struct
id|proc_dir_entry
id|proc_root_parport
op_assign
(brace
id|PROC_PARPORT
comma
l_int|7
comma
l_string|&quot;parport&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|parport_proc_dir_inode_operations
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|proc_root
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)brace
suffix:semicolon
macro_line|#endif
DECL|function|parport_proc_register
r_int
id|parport_proc_register
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(NOT_DEFINED)
r_return
id|proc_register
c_func
(paren
op_amp
id|proc_root
comma
op_amp
id|proc_root_parport
)paren
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
DECL|function|parport_proc_unregister
r_void
id|parport_proc_unregister
c_func
(paren
r_struct
id|parport
op_star
id|pp
)paren
(brace
macro_line|#if defined(CONFIG_PROC_FS) &amp;&amp; defined(NOT_DEFINED)
r_if
c_cond
(paren
id|pp
)paren
(brace
id|proc_unregister
c_func
(paren
op_amp
id|proc_root_parport
comma
id|pp-&gt;proc_dir-&gt;low_ino
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|pp-&gt;proc_dir
)paren
suffix:semicolon
)brace
r_else
(brace
id|proc_unregister
c_func
(paren
op_amp
id|proc_root
comma
id|proc_root_parport.low_ino
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
eof
