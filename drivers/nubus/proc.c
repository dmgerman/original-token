multiline_comment|/* drivers/nubus/proc.c: Proc FS interface for NuBus.&n;&n;   By David Huggins-Daines &lt;dhd@debian.org&gt;&n;&n;   Much code and many ideas from drivers/pci/proc.c:&n;   Copyright (c) 1997, 1998 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n;&n;   This is initially based on the Zorro and PCI interfaces.  However,&n;   it works somewhat differently.  The intent is to provide a&n;   structure in /proc analogous to the structure of the NuBus ROM&n;   resources.&n;&n;   Therefore each NuBus device is in fact a directory, which may in&n;   turn contain subdirectories.  The &quot;files&quot; correspond to NuBus&n;   resource records.  For those types of records which we know how to&n;   convert to formats that are meaningful to userspace (mostly just&n;   icons) these files will provide &quot;cooked&quot; data.  Otherwise they will&n;   simply provide raw access (read-only of course) to the ROM.  */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/nubus.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
r_int
DECL|function|get_nubus_dev_info
id|get_nubus_dev_info
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
comma
r_int
id|wr
)paren
(brace
r_struct
id|nubus_dev
op_star
id|dev
op_assign
id|nubus_devices
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
id|cnt
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|dev
op_logical_and
id|count
OG
id|cnt
)paren
(brace
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%x&bslash;t%04x %04x %04x %04x&quot;
comma
id|dev-&gt;board-&gt;slot
comma
id|dev-&gt;category
comma
id|dev-&gt;type
comma
id|dev-&gt;dr_sw
comma
id|dev-&gt;dr_hw
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&bslash;t%08lx&quot;
comma
id|dev-&gt;board-&gt;slot_addr
)paren
suffix:semicolon
id|buf
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;n&squot;
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
id|dev
op_assign
id|dev-&gt;next
suffix:semicolon
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
DECL|variable|proc_nubus_devices
r_static
r_struct
id|proc_dir_entry
id|proc_nubus_devices
op_assign
(brace
id|PROC_BUS_NUBUS_DEVICES
comma
l_int|7
comma
l_string|&quot;devices&quot;
comma
id|S_IFREG
op_or
id|S_IRUGO
comma
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
op_amp
id|proc_array_inode_operations
comma
id|get_nubus_dev_info
)brace
suffix:semicolon
DECL|variable|proc_bus_nubus_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_bus_nubus_dir
suffix:semicolon
DECL|function|nubus_proc_subdir
r_static
r_void
id|nubus_proc_subdir
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
comma
r_struct
id|proc_dir_entry
op_star
id|parent
comma
r_struct
id|nubus_dir
op_star
id|dir
)paren
(brace
r_struct
id|nubus_dirent
id|ent
suffix:semicolon
multiline_comment|/* Some of these are directories, others aren&squot;t */
r_while
c_loop
(paren
id|nubus_readdir
c_func
(paren
id|dir
comma
op_amp
id|ent
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%x&quot;
comma
id|ent.type
)paren
suffix:semicolon
id|e
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Can&squot;t do this recursively since the root directory is structured&n;   somewhat differently from the subdirectories */
DECL|function|nubus_proc_populate
r_static
r_void
id|nubus_proc_populate
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
comma
r_struct
id|proc_dir_entry
op_star
id|parent
comma
r_struct
id|nubus_dir
op_star
id|root
)paren
(brace
r_struct
id|nubus_dirent
id|ent
suffix:semicolon
multiline_comment|/* We know these are all directories (board resource + one or&n;&t;   more functional resources) */
r_while
c_loop
(paren
id|nubus_readdir
c_func
(paren
id|root
comma
op_amp
id|ent
)paren
op_ne
op_minus
l_int|1
)paren
(brace
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
r_struct
id|nubus_dir
id|dir
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%x&quot;
comma
id|ent.type
)paren
suffix:semicolon
id|e
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFDIR
comma
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
suffix:semicolon
multiline_comment|/* And descend */
r_if
c_cond
(paren
id|nubus_get_subdir
c_func
(paren
op_amp
id|ent
comma
op_amp
id|dir
)paren
op_eq
op_minus
l_int|1
)paren
(brace
multiline_comment|/* This shouldn&squot;t happen */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NuBus root directory node %x:%x has no subdir!&bslash;n&quot;
comma
id|dev-&gt;board-&gt;slot
comma
id|ent.type
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_else
(brace
id|nubus_proc_subdir
c_func
(paren
id|dev
comma
id|e
comma
op_amp
id|dir
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|nubus_proc_attach_device
r_int
id|nubus_proc_attach_device
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
r_struct
id|nubus_dir
id|root
suffix:semicolon
r_char
id|name
(braket
l_int|8
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NULL pointer in nubus_proc_attach_device, shoot the programmer!&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;board
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;NULL pointer in nubus_proc_attach_device, shoot the programmer!&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;dev = %p, dev-&gt;board = %p&bslash;n&quot;
comma
id|dev
comma
id|dev-&gt;board
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Create a directory */
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%x&quot;
comma
id|dev-&gt;board-&gt;slot
)paren
suffix:semicolon
id|e
op_assign
id|dev-&gt;procdir
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFDIR
comma
id|proc_bus_nubus_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|e
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
multiline_comment|/* Now recursively populate it with files */
id|nubus_get_root_dir
c_func
(paren
id|dev-&gt;board
comma
op_amp
id|root
)paren
suffix:semicolon
id|nubus_proc_populate
c_func
(paren
id|dev
comma
id|e
comma
op_amp
id|root
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* FIXME: this is certainly broken! */
DECL|function|nubus_proc_detach_device
r_int
id|nubus_proc_detach_device
c_func
(paren
r_struct
id|nubus_dev
op_star
id|dev
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|e
suffix:semicolon
r_if
c_cond
(paren
(paren
id|e
op_assign
id|dev-&gt;procdir
)paren
)paren
(brace
r_if
c_cond
(paren
id|e-&gt;count
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|e-&gt;name
comma
id|proc_bus_nubus_dir
)paren
suffix:semicolon
id|dev-&gt;procdir
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|proc_bus_nubus_add_devices
r_void
id|__init
id|proc_bus_nubus_add_devices
c_func
(paren
r_void
)paren
(brace
r_struct
id|nubus_dev
op_star
id|dev
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|nubus_devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;next
)paren
(brace
id|nubus_proc_attach_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|nubus_proc_init
r_void
id|__init
id|nubus_proc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MAC
)paren
r_return
suffix:semicolon
id|proc_bus_nubus_dir
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;nubus&quot;
comma
id|S_IFDIR
comma
id|proc_bus
)paren
suffix:semicolon
id|proc_register
c_func
(paren
id|proc_bus_nubus_dir
comma
op_amp
id|proc_nubus_devices
)paren
suffix:semicolon
id|proc_bus_nubus_add_devices
c_func
(paren
)paren
suffix:semicolon
)brace
eof
