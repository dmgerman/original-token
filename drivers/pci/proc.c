multiline_comment|/*&n; *&t;$Id: proc.c,v 1.10 1998/04/16 20:48:30 mj Exp $&n; *&n; *&t;Procfs interface for the PCI bus.&n; *&n; *&t;Copyright (c) 1997, 1998 Martin Mares &lt;mj@atrey.karlin.mff.cuni.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
DECL|macro|PCI_CFG_SPACE_SIZE
mdefine_line|#define PCI_CFG_SPACE_SIZE 256
r_static
id|loff_t
DECL|function|proc_bus_pci_lseek
id|proc_bus_pci_lseek
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
id|PCI_CFG_SPACE_SIZE
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
id|PCI_CFG_SPACE_SIZE
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
DECL|function|proc_bus_pci_read
id|proc_bus_pci_read
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
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_char
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_int
r_char
id|dfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_int
id|cnt
comma
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Normal users can read only the standardized portion of the&n;&t; * configuration space as several chips lock up when trying to read&n;&t; * undefined locations (think of Intel PIIX4 as a typical example).&n;&t; */
r_if
c_cond
(paren
id|fsuser
c_func
(paren
)paren
)paren
id|size
op_assign
id|PCI_CFG_SPACE_SIZE
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dev-&gt;hdr_type
op_eq
id|PCI_HEADER_TYPE_CARDBUS
)paren
id|size
op_assign
l_int|128
suffix:semicolon
r_else
id|size
op_assign
l_int|64
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|size
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|size
)paren
id|nbytes
op_assign
id|size
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
id|size
)paren
id|nbytes
op_assign
id|size
op_minus
id|pos
suffix:semicolon
id|cnt
op_assign
id|nbytes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|cnt
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|1
)paren
op_logical_and
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pcibios_read_config_byte
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|3
)paren
op_logical_and
id|cnt
OG
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pcibios_read_config_word
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le16
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pcibios_read_config_dword
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le32
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
id|pos
op_add_assign
l_int|4
suffix:semicolon
id|cnt
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_ge
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|pcibios_read_config_word
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|cpu_to_le16
c_func
(paren
id|val
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|pcibios_read_config_byte
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
op_amp
id|val
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|proc_bus_pci_write
id|proc_bus_pci_write
c_func
(paren
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
id|pci_dev
op_star
id|dev
op_assign
id|dp-&gt;data
suffix:semicolon
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_char
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_int
r_char
id|dfn
op_assign
id|dev-&gt;devfn
suffix:semicolon
r_int
id|cnt
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_ge
id|PCI_CFG_SPACE_SIZE
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
op_ge
id|PCI_CFG_SPACE_SIZE
)paren
id|nbytes
op_assign
id|PCI_CFG_SPACE_SIZE
suffix:semicolon
r_if
c_cond
(paren
id|pos
op_plus
id|nbytes
OG
id|PCI_CFG_SPACE_SIZE
)paren
id|nbytes
op_assign
id|PCI_CFG_SPACE_SIZE
op_minus
id|pos
suffix:semicolon
id|cnt
op_assign
id|nbytes
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|cnt
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|1
)paren
op_logical_and
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
id|val
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|pos
op_amp
l_int|3
)paren
op_logical_and
id|cnt
OG
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pcibios_write_config_word
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
id|le16_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
op_ge
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pcibios_write_config_dword
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
id|le32_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|4
suffix:semicolon
id|pos
op_add_assign
l_int|4
suffix:semicolon
id|cnt
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
op_ge
l_int|2
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|buf
)paren
suffix:semicolon
id|pcibios_write_config_word
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
id|le16_to_cpu
c_func
(paren
id|val
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
l_int|2
suffix:semicolon
id|pos
op_add_assign
l_int|2
suffix:semicolon
id|cnt
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cnt
)paren
(brace
r_int
r_char
id|val
suffix:semicolon
id|__get_user
c_func
(paren
id|val
comma
id|buf
)paren
suffix:semicolon
id|pcibios_write_config_byte
c_func
(paren
id|bus
comma
id|dfn
comma
id|pos
comma
id|val
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|pos
op_increment
suffix:semicolon
id|cnt
op_decrement
suffix:semicolon
)brace
op_star
id|ppos
op_assign
id|pos
suffix:semicolon
r_return
id|nbytes
suffix:semicolon
)brace
DECL|variable|proc_bus_pci_operations
r_static
r_struct
id|file_operations
id|proc_bus_pci_operations
op_assign
(brace
id|proc_bus_pci_lseek
comma
id|proc_bus_pci_read
comma
id|proc_bus_pci_write
comma
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
DECL|variable|proc_bus_pci_inode_operations
r_static
r_struct
id|inode_operations
id|proc_bus_pci_inode_operations
op_assign
(brace
op_amp
id|proc_bus_pci_operations
comma
multiline_comment|/* default base directory file-ops */
l_int|NULL
comma
multiline_comment|/* create */
l_int|NULL
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
r_int
DECL|function|get_pci_dev_info
id|get_pci_dev_info
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
id|pci_dev
op_star
id|dev
op_assign
id|pci_devices
suffix:semicolon
id|off_t
id|at
op_assign
l_int|0
suffix:semicolon
r_int
id|len
comma
id|i
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
l_string|&quot;%02x%02x&bslash;t%04x%04x&bslash;t%x&quot;
comma
id|dev-&gt;bus-&gt;number
comma
id|dev-&gt;devfn
comma
id|dev-&gt;vendor
comma
id|dev-&gt;device
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
macro_line|#if BITS_PER_LONG == 32
l_string|&quot;&bslash;t%08lx&quot;
comma
macro_line|#else
l_string|&quot;&bslash;t%016lx&quot;
comma
macro_line|#endif
id|dev-&gt;base_address
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
macro_line|#if BITS_PER_LONG == 32
l_string|&quot;&bslash;t%08lx&quot;
comma
macro_line|#else
l_string|&quot;&bslash;t%016lx&quot;
comma
macro_line|#endif
id|dev-&gt;rom_address
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
DECL|variable|proc_pci_devices
r_static
r_struct
id|proc_dir_entry
id|proc_pci_devices
op_assign
(brace
id|PROC_BUS_PCI_DEVICES
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
id|get_pci_dev_info
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|proc_bus_pci_add
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_struct
id|proc_dir_entry
op_star
id|proc_pci
)paren
)paren
(brace
r_while
c_loop
(paren
id|bus
)paren
(brace
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
id|de
op_assign
id|create_proc_entry
c_func
(paren
id|name
comma
id|S_IFDIR
comma
id|proc_pci
)paren
suffix:semicolon
r_for
c_loop
(paren
id|dev
op_assign
id|bus-&gt;devices
suffix:semicolon
id|dev
suffix:semicolon
id|dev
op_assign
id|dev-&gt;sibling
)paren
(brace
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
l_string|&quot;%02x.%x&quot;
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
comma
id|PCI_FUNC
c_func
(paren
id|dev-&gt;devfn
)paren
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
id|de
)paren
suffix:semicolon
id|e-&gt;ops
op_assign
op_amp
id|proc_bus_pci_inode_operations
suffix:semicolon
id|e-&gt;data
op_assign
id|dev
suffix:semicolon
id|e-&gt;size
op_assign
id|PCI_CFG_SPACE_SIZE
suffix:semicolon
)brace
r_if
c_cond
(paren
id|bus-&gt;children
)paren
id|proc_bus_pci_add
c_func
(paren
id|bus-&gt;children
comma
id|proc_pci
)paren
suffix:semicolon
id|bus
op_assign
id|bus-&gt;next
suffix:semicolon
)brace
)brace
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|pci_proc_init
c_func
(paren
r_void
)paren
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|proc_pci
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_present
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
id|proc_pci
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;pci&quot;
comma
id|S_IFDIR
comma
id|proc_bus
)paren
suffix:semicolon
id|proc_register
c_func
(paren
id|proc_pci
comma
op_amp
id|proc_pci_devices
)paren
suffix:semicolon
id|proc_bus_pci_add
c_func
(paren
op_amp
id|pci_root
comma
id|proc_pci
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_OLD_PROC
id|proc_old_pci_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
