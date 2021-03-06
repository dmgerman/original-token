multiline_comment|/*&n; *&t;$Id: proc.c,v 1.13 1998/05/12 07:36:07 mj Exp $&n; *&n; *&t;Procfs interface for the PCI bus.&n; *&n; *&t;Copyright (c) 1997--1999 Martin Mares &lt;mj@suse.cz&gt;&n; */
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
r_const
r_struct
id|inode
op_star
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
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
r_int
id|pos
op_assign
op_star
id|ppos
suffix:semicolon
r_int
r_int
id|cnt
comma
id|size
suffix:semicolon
multiline_comment|/*&n;&t; * Normal users can read only the standardized portion of the&n;&t; * configuration space as several chips lock up when trying to read&n;&t; * undefined locations (think of Intel PIIX4 as a typical example).&n;&t; */
r_if
c_cond
(paren
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
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
id|pci_read_config_byte
c_func
(paren
id|dev
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
id|pci_read_config_word
c_func
(paren
id|dev
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
id|pci_read_config_dword
c_func
(paren
id|dev
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
id|pci_read_config_word
c_func
(paren
id|dev
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
id|pci_read_config_byte
c_func
(paren
id|dev
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
r_const
r_struct
id|inode
op_star
id|ino
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_const
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
id|pci_write_config_byte
c_func
(paren
id|dev
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
id|pci_write_config_word
c_func
(paren
id|dev
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
id|pci_write_config_dword
c_func
(paren
id|dev
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
id|pci_write_config_word
c_func
(paren
id|dev
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
id|pci_write_config_byte
c_func
(paren
id|dev
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
id|llseek
suffix:colon
id|proc_bus_pci_lseek
comma
id|read
suffix:colon
id|proc_bus_pci_read
comma
id|write
suffix:colon
id|proc_bus_pci_write
comma
)brace
suffix:semicolon
macro_line|#if BITS_PER_LONG == 32
DECL|macro|LONG_FORMAT
mdefine_line|#define LONG_FORMAT &quot;&bslash;t%08lx&quot;
macro_line|#else
DECL|macro|LONG_FORMAT
mdefine_line|#define LONG_FORMAT &quot;&bslash;t%16lx&quot;
macro_line|#endif
r_static
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
)paren
(brace
r_const
r_struct
id|pci_dev
op_star
id|dev
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
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_const
r_struct
id|pci_driver
op_star
id|drv
op_assign
id|pci_dev_driver
c_func
(paren
id|dev
)paren
suffix:semicolon
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
multiline_comment|/* Here should be 7 and not PCI_NUM_RESOURCES as we need to preserve compatibility */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
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
id|LONG_FORMAT
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_or
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|7
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
id|LONG_FORMAT
comma
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
OL
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
ques
c_cond
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|end
op_minus
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|start
op_plus
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
)brace
id|buf
(braket
id|len
op_increment
)braket
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
r_if
c_cond
(paren
id|drv
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;%s&quot;
comma
id|drv-&gt;name
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
r_if
c_cond
(paren
id|cnt
op_ge
id|count
)paren
multiline_comment|/*&n;&t;&t;&t;&t; * proc_file_read() gives us 1KB of slack so it&squot;s OK if the&n;&t;&t;&t;&t; * above printfs write a little beyond the buffer end (we&n;&t;&t;&t;&t; * never write more than 1KB beyond the buffer end).&n;&t;&t;&t;&t; */
r_break
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
DECL|variable|proc_bus_pci_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_bus_pci_dir
suffix:semicolon
DECL|function|pci_proc_attach_device
r_int
id|pci_proc_attach_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_struct
id|proc_dir_entry
op_star
id|de
comma
op_star
id|e
suffix:semicolon
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|de
op_assign
id|bus-&gt;procdir
)paren
)paren
(brace
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
id|bus-&gt;procdir
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|proc_bus_pci_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|de
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
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
id|dev-&gt;procent
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
id|e-&gt;proc_fops
op_assign
op_amp
id|proc_bus_pci_operations
suffix:semicolon
id|e-&gt;data
op_assign
id|dev
suffix:semicolon
id|e-&gt;size
op_assign
id|PCI_CFG_SPACE_SIZE
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pci_proc_detach_device
r_int
id|pci_proc_detach_device
c_func
(paren
r_struct
id|pci_dev
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
id|dev-&gt;procent
)paren
)paren
(brace
r_if
c_cond
(paren
id|atomic_read
c_func
(paren
op_amp
id|e-&gt;count
)paren
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
id|dev-&gt;bus-&gt;procdir
)paren
suffix:semicolon
id|dev-&gt;procent
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *  Backward compatible /proc/pci interface.&n; */
multiline_comment|/*&n; * Convert some of the configuration space registers of the device at&n; * address (bus,devfn) into a string (possibly several lines each).&n; * The configuration string is stored starting at buf[len].  If the&n; * string would exceed the size of the buffer (SIZE), 0 is returned.&n; */
DECL|function|sprint_dev_config
r_static
r_int
id|sprint_dev_config
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
id|u32
id|class_rev
suffix:semicolon
r_int
r_char
id|latency
comma
id|min_gnt
comma
id|max_lat
comma
op_star
r_class
suffix:semicolon
r_int
id|reg
comma
id|len
op_assign
l_int|0
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|PCI_CLASS_REVISION
comma
op_amp
id|class_rev
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|latency
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_MIN_GNT
comma
op_amp
id|min_gnt
)paren
suffix:semicolon
id|pci_read_config_byte
(paren
id|dev
comma
id|PCI_MAX_LAT
comma
op_amp
id|max_lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
l_int|160
OG
id|size
)paren
r_return
op_minus
l_int|1
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
l_string|&quot;  Bus %2d, device %3d, function %2d:&bslash;n&quot;
comma
id|dev-&gt;bus-&gt;number
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
r_class
op_assign
id|pci_class_name
c_func
(paren
id|class_rev
op_rshift
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
r_class
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;    %s&quot;
comma
r_class
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;    Class %04x&quot;
comma
id|class_rev
op_rshift
l_int|16
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
l_string|&quot;: %s (rev %d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|class_rev
op_amp
l_int|0xff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
(brace
r_if
c_cond
(paren
id|len
op_plus
l_int|40
OG
id|size
)paren
r_return
op_minus
l_int|1
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
l_string|&quot;      IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|latency
op_logical_or
id|min_gnt
op_logical_or
id|max_lat
)paren
(brace
r_if
c_cond
(paren
id|len
op_plus
l_int|80
OG
id|size
)paren
r_return
op_minus
l_int|1
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
l_string|&quot;      Master Capable.  &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|latency
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Latency=%d.  &quot;
comma
id|latency
)paren
suffix:semicolon
r_else
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;No bursts.  &quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|min_gnt
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Min Gnt=%d.&quot;
comma
id|min_gnt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|max_lat
)paren
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Max Lat=%d.&quot;
comma
id|max_lat
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
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|reg
op_assign
l_int|0
suffix:semicolon
id|reg
OL
l_int|6
suffix:semicolon
id|reg
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|dev-&gt;resource
op_plus
id|reg
suffix:semicolon
r_int
r_int
id|base
comma
id|end
comma
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
l_int|40
OG
id|size
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|base
op_assign
id|res-&gt;start
suffix:semicolon
id|end
op_assign
id|res-&gt;end
suffix:semicolon
id|flags
op_assign
id|res-&gt;flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_SPACE_IO
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
l_string|&quot;      I/O at 0x%lx [0x%lx].&bslash;n&quot;
comma
id|base
comma
id|end
)paren
suffix:semicolon
)brace
r_else
(brace
r_const
r_char
op_star
id|pref
comma
op_star
id|type
op_assign
l_string|&quot;unknown&quot;
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_MEM_PREFETCH
)paren
id|pref
op_assign
l_string|&quot;P&quot;
suffix:semicolon
r_else
id|pref
op_assign
l_string|&quot;Non-p&quot;
suffix:semicolon
r_switch
c_cond
(paren
id|flags
op_amp
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
(brace
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_32
suffix:colon
id|type
op_assign
l_string|&quot;32 bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_1M
suffix:colon
id|type
op_assign
l_string|&quot;20 bit&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_BASE_ADDRESS_MEM_TYPE_64
suffix:colon
id|type
op_assign
l_string|&quot;64 bit&quot;
suffix:semicolon
r_break
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
l_string|&quot;      %srefetchable %s memory at &quot;
l_string|&quot;0x%lx [0x%lx].&bslash;n&quot;
comma
id|pref
comma
id|type
comma
id|base
comma
id|end
)paren
suffix:semicolon
)brace
)brace
r_return
id|len
suffix:semicolon
)brace
multiline_comment|/*&n; * Return list of PCI devices as a character string for /proc/pci.&n; * BUF is a buffer that is PAGE_SIZE bytes long.&n; */
DECL|function|pci_read_proc
r_static
r_int
id|pci_read_proc
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
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|nprinted
comma
id|len
comma
id|begin
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|len
op_assign
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;PCI devices found:&bslash;n&quot;
)paren
suffix:semicolon
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|nprinted
op_assign
id|sprint_dev_config
c_func
(paren
id|dev
comma
id|buf
op_plus
id|len
comma
id|PAGE_SIZE
op_minus
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|nprinted
OL
l_int|0
)paren
(brace
op_star
id|eof
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|len
op_add_assign
id|nprinted
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OL
id|off
)paren
(brace
id|begin
op_add_assign
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|len
op_plus
id|begin
op_ge
id|off
op_plus
id|count
)paren
r_break
suffix:semicolon
)brace
id|off
op_sub_assign
id|begin
suffix:semicolon
op_star
id|start
op_assign
id|buf
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
r_return
id|len
suffix:semicolon
)brace
DECL|function|pci_proc_init
r_static
r_int
id|__init
id|pci_proc_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pci_present
c_func
(paren
)paren
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
id|proc_bus_pci_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;pci&quot;
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
id|proc_bus_pci_dir
comma
id|get_pci_dev_info
)paren
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|pci_proc_attach_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|create_proc_read_entry
c_func
(paren
l_string|&quot;pci&quot;
comma
l_int|0
comma
l_int|NULL
comma
id|pci_read_proc
comma
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_proc_init
id|__initcall
c_func
(paren
id|pci_proc_init
)paren
suffix:semicolon
eof
