multiline_comment|/*&n; *  linux/fs/filesystems.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  table of configured filesystems&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#ifdef MINIX_FS
macro_line|#include &lt;linux/minix_fs.h&gt;
macro_line|#endif
macro_line|#ifdef PROC_FS
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#endif
macro_line|#ifdef EXT_FS
macro_line|#include &lt;linux/ext_fs.h&gt;
macro_line|#endif
macro_line|#ifdef MSDOS_FS
macro_line|#include &lt;linux/msdos_fs.h&gt;
macro_line|#endif
macro_line|#ifdef NFS_FS
macro_line|#include &lt;linux/nfs_fs.h&gt;
macro_line|#endif
macro_line|#ifdef ISO9660_FS
macro_line|#include &lt;linux/iso_fs.h&gt;
macro_line|#endif
DECL|variable|file_systems
r_struct
id|file_system_type
id|file_systems
(braket
)braket
op_assign
(brace
macro_line|#ifdef MINIX_FS
(brace
id|minix_read_super
comma
l_string|&quot;minix&quot;
comma
l_int|1
)brace
comma
macro_line|#endif
macro_line|#ifdef EXT_FS
(brace
id|ext_read_super
comma
l_string|&quot;ext&quot;
comma
l_int|1
)brace
comma
macro_line|#endif
macro_line|#ifdef MSDOS_FS
(brace
id|msdos_read_super
comma
l_string|&quot;msdos&quot;
comma
l_int|1
)brace
comma
macro_line|#endif
macro_line|#ifdef PROC_FS
(brace
id|proc_read_super
comma
l_string|&quot;proc&quot;
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef NFS_FS
(brace
id|nfs_read_super
comma
l_string|&quot;nfs&quot;
comma
l_int|0
)brace
comma
macro_line|#endif
macro_line|#ifdef ISO9660_FS
(brace
id|isofs_read_super
comma
l_string|&quot;iso9660&quot;
comma
l_int|1
)brace
comma
macro_line|#endif
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
eof