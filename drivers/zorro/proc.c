multiline_comment|/*&n; *&t;$Id: proc.c,v 1.1.2.1 1998/06/07 23:21:01 geert Exp $&n; *&n; *&t;Procfs interface for the Zorro bus.&n; *&n; *&t;Copyright (C) 1998-2000 Geert Uytterhoeven&n; *&n; *&t;Heavily based on the procfs interface for the PCI bus, which is&n; *&n; *&t;Copyright (C) 1997, 1998 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
r_static
id|loff_t
DECL|function|proc_bus_zorro_lseek
id|proc_bus_zorro_lseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
id|off
comma
r_int
id|whence
)paren
(brace
id|loff_t
r_new
suffix:semicolon
r_switch
c_cond
(paren
id|whence
)paren
(brace
r_case
l_int|0
suffix:colon
r_new
op_assign
id|off
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_new
op_assign
id|file-&gt;f_pos
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_new
op_assign
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
op_plus
id|off
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
r_new
template_param
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
(paren
id|file-&gt;f_pos
op_assign
r_new
)paren
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|proc_bus_zorro_read
id|proc_bus_zorro_read
c_func
(paren
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
id|nbytes
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|dp
op_assign
id|ino-&gt;u.generic_ip
suffix:semicolon
r_struct
id|zorro_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_struct
id|ConfigDev
id|cd
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
)paren
id|nbytes
op_assign
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
)paren
id|nbytes
op_assign
r_sizeof
(paren
r_struct
id|ConfigDev
)paren
op_minus
id|pos
suffix:semicolon
multiline_comment|/* Construct a ConfigDev */
id|memset
c_func
(paren
op_amp
id|cd
comma
l_int|0
comma
r_sizeof
(paren
id|cd
)paren
)paren
suffix:semicolon
id|cd.cd_Rom
op_assign
id|dev-&gt;rom
suffix:semicolon
id|cd.cd_SlotAddr
op_assign
id|dev-&gt;slotaddr
suffix:semicolon
id|cd.cd_SlotSize
op_assign
id|dev-&gt;slotsize
suffix:semicolon
id|cd.cd_BoardAddr
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;resource.start
suffix:semicolon
id|cd.cd_BoardSize
op_assign
id|dev-&gt;resource.end
op_minus
id|dev-&gt;resource.start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
op_amp
id|cd
comma
id|nbytes
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
op_star
id|ppos
op_add_assign
id|nbytes
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
DECL|variable|proc_bus_zorro_operations
r_static
r_struct
id|file_operations
id|proc_bus_zorro_operations
op_assign
(brace
id|llseek
suffix:colon
id|proc_bus_zorro_lseek
comma
id|read
suffix:colon
id|proc_bus_zorro_read
comma
)brace
suffix:semicolon
r_static
r_int
DECL|function|get_zorro_dev_info
id|get_zorro_dev_info
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
id|pos
comma
r_int
id|count
)paren
(brace
id|u_int
id|slot
suffix:semicolon
id|off_t
id|at
op_assign
l_int|0
suffix:semicolon
r_int
id|len
comma
id|cnt
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
id|cnt
op_assign
l_int|0
suffix:semicolon
id|slot
template_param
id|cnt
suffix:semicolon
id|slot
op_increment
)paren
(brace
r_struct
id|zorro_dev
op_star
id|dev
op_assign
op_amp
id|zorro_autocon
(braket
id|slot
)braket
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%02x&bslash;t%08x&bslash;t%08lx&bslash;t%08lx&bslash;t%02x&bslash;n&quot;
comma
id|slot
comma
id|dev-&gt;id
comma
id|dev-&gt;resource.start
comma
id|dev-&gt;resource.end
op_minus
id|dev-&gt;resource.start
op_plus
l_int|1
comma
id|dev-&gt;rom.er_Type
)paren
suffix:semicolon
id|at
op_add_assign
id|len
suffix:semicolon
r_if
c_cond
(paren
id|at
op_ge
id|pos
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
op_star
id|start
)paren
(brace
op_star
id|start
op_assign
id|buf
op_plus
(paren
id|pos
op_minus
(paren
id|at
op_minus
id|len
)paren
)paren
suffix:semicolon
id|cnt
op_assign
id|at
op_minus
id|pos
suffix:semicolon
)brace
r_else
id|cnt
op_add_assign
id|len
suffix:semicolon
id|buf
op_add_assign
id|len
suffix:semicolon
)brace
)brace
r_return
(paren
id|count
OG
id|cnt
)paren
ques
c_cond
id|cnt
suffix:colon
id|count
suffix:semicolon
)brace
DECL|variable|proc_bus_zorro_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_bus_zorro_dir
suffix:semicolon
DECL|function|zorro_proc_attach_device
r_static
r_int
id|__init
id|zorro_proc_attach_device
c_func
(paren
id|u_int
id|slot
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_char
id|name
(braket
l_int|4
)braket
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|slot
)paren
suffix:semicolon
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
l_int|0
comma
id|proc_bus_zorro_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|entry-&gt;proc_fops
op_assign
op_amp
id|proc_bus_zorro_operations
suffix:semicolon
id|entry-&gt;data
op_assign
op_amp
id|zorro_autocon
(braket
id|slot
)braket
suffix:semicolon
id|entry-&gt;size
op_assign
r_sizeof
(paren
r_struct
id|zorro_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|zorro_proc_init
r_static
r_int
id|__init
id|zorro_proc_init
c_func
(paren
r_void
)paren
(brace
id|u_int
id|slot
suffix:semicolon
r_if
c_cond
(paren
id|MACH_IS_AMIGA
op_logical_and
id|AMIGAHW_PRESENT
c_func
(paren
id|ZORRO
)paren
)paren
(brace
id|proc_bus_zorro_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;zorro&quot;
comma
id|proc_bus
)paren
suffix:semicolon
id|create_proc_info_entry
c_func
(paren
l_string|&quot;devices&quot;
comma
l_int|0
comma
id|proc_bus_zorro_dir
comma
id|get_zorro_dev_info
)paren
suffix:semicolon
r_for
c_loop
(paren
id|slot
op_assign
l_int|0
suffix:semicolon
id|slot
OL
id|zorro_num_autocon
suffix:semicolon
id|slot
op_increment
)paren
id|zorro_proc_attach_device
c_func
(paren
id|slot
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|zorro_proc_init
id|__initcall
c_func
(paren
id|zorro_proc_init
)paren
suffix:semicolon
eof
