multiline_comment|/* $Id: flash.c,v 1.20 2000/11/08 04:57:49 davem Exp $&n; * flash.c: Allow mmap access to the OBP Flash, for OBP updates.&n; *&n; * Copyright (C) 1997  Eddie C. Dost  (ecd@skynet.be)&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sbus.h&gt;
macro_line|#include &lt;asm/ebus.h&gt;
r_static
r_struct
(brace
DECL|member|read_base
r_int
r_int
id|read_base
suffix:semicolon
multiline_comment|/* Physical read address */
DECL|member|write_base
r_int
r_int
id|write_base
suffix:semicolon
multiline_comment|/* Physical write address */
DECL|member|read_size
r_int
r_int
id|read_size
suffix:semicolon
multiline_comment|/* Size of read area */
DECL|member|write_size
r_int
r_int
id|write_size
suffix:semicolon
multiline_comment|/* Size of write area */
DECL|member|busy
r_int
r_int
id|busy
suffix:semicolon
multiline_comment|/* In use? */
DECL|variable|flash
)brace
id|flash
suffix:semicolon
DECL|macro|FLASH_MINOR
mdefine_line|#define FLASH_MINOR&t;152
r_static
r_int
DECL|function|flash_mmap
id|flash_mmap
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|addr
suffix:semicolon
r_int
r_int
id|size
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flash.read_base
op_eq
id|flash.write_base
)paren
(brace
id|addr
op_assign
id|flash.read_base
suffix:semicolon
id|size
op_assign
id|flash.read_size
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_READ
)paren
op_logical_and
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
)paren
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_READ
)paren
(brace
id|addr
op_assign
id|flash.read_base
suffix:semicolon
id|size
op_assign
id|flash.read_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
(brace
id|addr
op_assign
id|flash.write_base
suffix:semicolon
id|size
op_assign
id|flash.write_size
suffix:semicolon
)brace
r_else
(brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
OG
id|size
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
id|addr
op_add_assign
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_minus
(paren
id|vma-&gt;vm_start
op_plus
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
)paren
OG
id|size
)paren
id|size
op_assign
id|vma-&gt;vm_end
op_minus
(paren
id|vma-&gt;vm_start
op_plus
(paren
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_and_assign
op_complement
(paren
id|_PAGE_CACHE
)paren
suffix:semicolon
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
op_or_assign
id|_PAGE_E
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|addr
comma
id|size
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|flash_llseek
id|flash_llseek
c_func
(paren
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
id|origin
)paren
(brace
r_switch
c_cond
(paren
id|origin
)paren
(brace
r_case
l_int|0
suffix:colon
id|file-&gt;f_pos
op_assign
id|offset
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|file-&gt;f_pos
op_add_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
OG
id|flash.read_size
)paren
id|file-&gt;f_pos
op_assign
id|flash.read_size
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|file-&gt;f_pos
op_assign
id|flash.read_size
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
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
r_static
id|ssize_t
DECL|function|flash_read
id|flash_read
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|flash.read_size
op_minus
id|p
)paren
id|count
op_assign
id|flash.read_size
op_minus
id|p
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buf
comma
id|flash.read_base
op_plus
id|p
comma
id|count
)paren
OL
l_int|0
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
DECL|function|flash_open
id|flash_open
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
)paren
(brace
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|flash.busy
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|flash_release
id|flash_release
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
)paren
(brace
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|flash.busy
op_assign
l_int|0
suffix:semicolon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|flash_fops
r_static
r_struct
id|file_operations
id|flash_fops
op_assign
(brace
multiline_comment|/* no write to the Flash, use mmap&n;&t; * and play flash dependent tricks.&n;&t; */
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|flash_llseek
comma
id|read
suffix:colon
id|flash_read
comma
id|mmap
suffix:colon
id|flash_mmap
comma
id|open
suffix:colon
id|flash_open
comma
id|release
suffix:colon
id|flash_release
comma
)brace
suffix:semicolon
DECL|variable|flash_dev
r_static
r_struct
id|miscdevice
id|flash_dev
op_assign
(brace
id|FLASH_MINOR
comma
l_string|&quot;flash&quot;
comma
op_amp
id|flash_fops
)brace
suffix:semicolon
id|EXPORT_NO_SYMBOLS
suffix:semicolon
DECL|function|flash_init
r_static
r_int
id|__init
id|flash_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|sbus_bus
op_star
id|sbus
suffix:semicolon
r_struct
id|sbus_dev
op_star
id|sdev
op_assign
l_int|0
suffix:semicolon
r_struct
id|linux_ebus
op_star
id|ebus
suffix:semicolon
r_struct
id|linux_ebus_device
op_star
id|edev
op_assign
l_int|0
suffix:semicolon
r_struct
id|linux_prom_registers
id|regs
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|len
comma
id|err
comma
id|nregs
suffix:semicolon
id|for_all_sbusdev
c_func
(paren
id|sdev
comma
id|sbus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|sdev-&gt;prom_name
comma
l_string|&quot;flashprom&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
op_eq
id|sdev-&gt;reg_addrs
(braket
l_int|1
)braket
dot
id|phys_addr
)paren
(brace
id|flash.read_base
op_assign
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
)paren
op_lshift
l_int|32UL
)paren
suffix:semicolon
id|flash.read_size
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
id|flash.write_base
op_assign
id|flash.read_base
suffix:semicolon
id|flash.write_size
op_assign
id|flash.read_size
suffix:semicolon
)brace
r_else
(brace
id|flash.read_base
op_assign
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|phys_addr
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|which_io
)paren
op_lshift
l_int|32UL
)paren
suffix:semicolon
id|flash.read_size
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
id|flash.write_base
op_assign
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|1
)braket
dot
id|phys_addr
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|sdev-&gt;reg_addrs
(braket
l_int|1
)braket
dot
id|which_io
)paren
op_lshift
l_int|32UL
)paren
suffix:semicolon
id|flash.write_size
op_assign
id|sdev-&gt;reg_addrs
(braket
l_int|1
)braket
dot
id|reg_size
suffix:semicolon
)brace
id|flash.busy
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|sdev
)paren
(brace
macro_line|#ifdef CONFIG_PCI
id|for_each_ebus
c_func
(paren
id|ebus
)paren
(brace
id|for_each_ebusdev
c_func
(paren
id|edev
comma
id|ebus
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|edev-&gt;prom_name
comma
l_string|&quot;flashprom&quot;
)paren
)paren
r_goto
id|ebus_done
suffix:semicolon
)brace
)brace
id|ebus_done
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|edev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|len
op_assign
id|prom_getproperty
c_func
(paren
id|edev-&gt;prom_node
comma
l_string|&quot;reg&quot;
comma
(paren
r_void
op_star
)paren
id|regs
comma
r_sizeof
(paren
id|regs
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_mod
r_sizeof
(paren
id|regs
(braket
l_int|0
)braket
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;flash: Strange reg property size %d&bslash;n&quot;
comma
id|len
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|nregs
op_assign
id|len
op_div
r_sizeof
(paren
id|regs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|flash.read_base
op_assign
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|flash.read_size
op_assign
id|regs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
r_if
c_cond
(paren
id|nregs
op_eq
l_int|1
)paren
(brace
id|flash.write_base
op_assign
id|edev-&gt;resource
(braket
l_int|0
)braket
dot
id|start
suffix:semicolon
id|flash.write_size
op_assign
id|regs
(braket
l_int|0
)braket
dot
id|reg_size
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|nregs
op_eq
l_int|2
)paren
(brace
id|flash.write_base
op_assign
id|edev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
suffix:semicolon
id|flash.write_size
op_assign
id|regs
(braket
l_int|1
)braket
dot
id|reg_size
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;flash: Strange number of regs %d&bslash;n&quot;
comma
id|nregs
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|flash.busy
op_assign
l_int|0
suffix:semicolon
macro_line|#else
r_return
op_minus
id|ENODEV
suffix:semicolon
macro_line|#endif
)brace
id|printk
c_func
(paren
l_string|&quot;OBP Flash: RD %lx[%lx] WR %lx[%lx]&bslash;n&quot;
comma
id|flash.read_base
comma
id|flash.read_size
comma
id|flash.write_base
comma
id|flash.write_size
)paren
suffix:semicolon
id|err
op_assign
id|misc_register
c_func
(paren
op_amp
id|flash_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;flash: unable to get misc minor&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|flash_cleanup
r_static
r_void
id|__exit
id|flash_cleanup
c_func
(paren
r_void
)paren
(brace
id|misc_deregister
c_func
(paren
op_amp
id|flash_dev
)paren
suffix:semicolon
)brace
DECL|variable|flash_init
id|module_init
c_func
(paren
id|flash_init
)paren
suffix:semicolon
DECL|variable|flash_cleanup
id|module_exit
c_func
(paren
id|flash_cleanup
)paren
suffix:semicolon
eof
