multiline_comment|/*&n; *  linux/kernel/chr_drv/mem.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mouse.h&gt;
macro_line|#include &lt;linux/tpqic02.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifdef CONFIG_SOUND
r_extern
r_int
id|soundcard_init
c_func
(paren
r_int
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
DECL|function|read_ram
r_static
r_int
id|read_ram
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
id|count
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|write_ram
r_static
r_int
id|write_ram
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
id|count
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
DECL|function|read_mem
r_static
r_int
id|read_mem
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
id|count
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_int
id|read
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|high_memory
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|high_memory
op_minus
id|p
)paren
id|count
op_assign
id|high_memory
op_minus
id|p
suffix:semicolon
id|read
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|read
op_increment
suffix:semicolon
)brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
(paren
r_void
op_star
)paren
id|p
comma
id|count
)paren
suffix:semicolon
id|read
op_add_assign
id|count
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|read
suffix:semicolon
r_return
id|read
suffix:semicolon
)brace
DECL|function|write_mem
r_static
r_int
id|write_mem
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
id|count
)paren
(brace
r_int
r_int
id|p
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_int
id|written
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|p
op_ge
id|high_memory
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|high_memory
op_minus
id|p
)paren
id|count
op_assign
id|high_memory
op_minus
id|p
suffix:semicolon
id|written
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|p
template_param
l_int|0
)paren
(brace
multiline_comment|/* Hmm. Do something? */
id|buf
op_increment
suffix:semicolon
id|p
op_increment
suffix:semicolon
id|count
op_decrement
suffix:semicolon
id|written
op_increment
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
(paren
r_void
op_star
)paren
id|p
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|written
op_add_assign
id|count
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|written
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|mmap_mem
r_static
r_int
id|mmap_mem
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_offset
op_amp
op_complement
id|PAGE_MASK
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|x86
OG
l_int|3
op_logical_and
id|vma-&gt;vm_offset
op_ge
id|high_memory
)paren
id|vma-&gt;vm_page_prot
op_or_assign
id|PAGE_PCD
suffix:semicolon
r_if
c_cond
(paren
id|remap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_offset
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|vma-&gt;vm_inode
op_assign
id|inode
suffix:semicolon
id|inode-&gt;i_count
op_increment
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current
comma
id|vma
)paren
suffix:semicolon
id|merge_segments
c_func
(paren
id|current-&gt;mm-&gt;mmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_kmem
r_static
r_int
id|read_kmem
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
id|count
)paren
(brace
r_int
id|read1
comma
id|read2
suffix:semicolon
id|read1
op_assign
id|read_mem
c_func
(paren
id|inode
comma
id|file
comma
id|buf
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read1
OL
l_int|0
)paren
r_return
id|read1
suffix:semicolon
id|read2
op_assign
id|vread
c_func
(paren
id|buf
op_plus
id|read1
comma
(paren
r_char
op_star
)paren
id|file-&gt;f_pos
comma
id|count
op_minus
id|read1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read2
OL
l_int|0
)paren
r_return
id|read2
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|read2
suffix:semicolon
r_return
id|read1
op_plus
id|read2
suffix:semicolon
)brace
DECL|function|read_port
r_static
r_int
id|read_port
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
id|count
)paren
(brace
r_int
r_int
id|i
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
id|put_fs_byte
c_func
(paren
id|inb
c_func
(paren
id|i
)paren
comma
id|tmp
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
id|file-&gt;f_pos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|write_port
r_static
r_int
id|write_port
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
id|count
)paren
(brace
r_int
r_int
id|i
op_assign
id|file-&gt;f_pos
suffix:semicolon
r_char
op_star
id|tmp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
op_decrement
OG
l_int|0
op_logical_and
id|i
OL
l_int|65536
)paren
(brace
id|outb
c_func
(paren
id|get_fs_byte
c_func
(paren
id|tmp
)paren
comma
id|i
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|tmp
op_increment
suffix:semicolon
)brace
id|file-&gt;f_pos
op_assign
id|i
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|read_null
r_static
r_int
id|read_null
c_func
(paren
r_struct
id|inode
op_star
id|node
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
id|count
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_null
r_static
r_int
id|write_null
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
id|count
)paren
(brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|read_zero
r_static
r_int
id|read_zero
c_func
(paren
r_struct
id|inode
op_star
id|node
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
id|count
)paren
(brace
r_int
id|left
suffix:semicolon
r_for
c_loop
(paren
id|left
op_assign
id|count
suffix:semicolon
id|left
OG
l_int|0
suffix:semicolon
id|left
op_decrement
)paren
(brace
id|put_fs_byte
c_func
(paren
l_int|0
comma
id|buf
)paren
suffix:semicolon
id|buf
op_increment
suffix:semicolon
)brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|mmap_zero
r_static
r_int
id|mmap_zero
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
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_if
c_cond
(paren
id|vma-&gt;vm_page_prot
op_amp
id|PAGE_RW
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|zeromap_page_range
c_func
(paren
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current
comma
id|vma
)paren
suffix:semicolon
id|merge_segments
c_func
(paren
id|current-&gt;mm-&gt;mmap
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|read_full
r_static
r_int
id|read_full
c_func
(paren
r_struct
id|inode
op_star
id|node
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
id|count
)paren
(brace
r_return
id|count
suffix:semicolon
)brace
DECL|function|write_full
r_static
r_int
id|write_full
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
id|count
)paren
(brace
r_return
op_minus
id|ENOSPC
suffix:semicolon
)brace
multiline_comment|/*&n; * Special lseek() function for /dev/null and /dev/zero.  Most notably, you can fopen()&n; * both devices with &quot;a&quot; now.  This was previously impossible.  SRB.&n; */
DECL|function|null_lseek
r_static
r_int
id|null_lseek
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
id|off_t
id|offset
comma
r_int
id|orig
)paren
(brace
r_return
id|file-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The memory devices use the full 32 bits of the offset, and so we cannot&n; * check against negative addresses: they are ok. The return value is weird,&n; * though, in that case (0).&n; *&n; * also note that seeking relative to the &quot;end of file&quot; isn&squot;t supported:&n; * it has no meaning, so it returns -EINVAL.&n; */
DECL|function|memory_lseek
r_static
r_int
id|memory_lseek
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
id|off_t
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
id|file-&gt;f_pos
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|file-&gt;f_pos
suffix:semicolon
)brace
DECL|macro|write_kmem
mdefine_line|#define write_kmem&t;write_mem
DECL|macro|mmap_kmem
mdefine_line|#define mmap_kmem&t;mmap_mem
DECL|macro|zero_lseek
mdefine_line|#define zero_lseek&t;null_lseek
DECL|macro|write_zero
mdefine_line|#define write_zero&t;write_null
DECL|variable|ram_fops
r_static
r_struct
id|file_operations
id|ram_fops
op_assign
(brace
id|memory_lseek
comma
id|read_ram
comma
id|write_ram
comma
l_int|NULL
comma
multiline_comment|/* ram_readdir */
l_int|NULL
comma
multiline_comment|/* ram_select */
l_int|NULL
comma
multiline_comment|/* ram_ioctl */
l_int|NULL
comma
multiline_comment|/* ram_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|mem_fops
r_static
r_struct
id|file_operations
id|mem_fops
op_assign
(brace
id|memory_lseek
comma
id|read_mem
comma
id|write_mem
comma
l_int|NULL
comma
multiline_comment|/* mem_readdir */
l_int|NULL
comma
multiline_comment|/* mem_select */
l_int|NULL
comma
multiline_comment|/* mem_ioctl */
id|mmap_mem
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|kmem_fops
r_static
r_struct
id|file_operations
id|kmem_fops
op_assign
(brace
id|memory_lseek
comma
id|read_kmem
comma
id|write_kmem
comma
l_int|NULL
comma
multiline_comment|/* kmem_readdir */
l_int|NULL
comma
multiline_comment|/* kmem_select */
l_int|NULL
comma
multiline_comment|/* kmem_ioctl */
id|mmap_kmem
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|null_fops
r_static
r_struct
id|file_operations
id|null_fops
op_assign
(brace
id|null_lseek
comma
id|read_null
comma
id|write_null
comma
l_int|NULL
comma
multiline_comment|/* null_readdir */
l_int|NULL
comma
multiline_comment|/* null_select */
l_int|NULL
comma
multiline_comment|/* null_ioctl */
l_int|NULL
comma
multiline_comment|/* null_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|port_fops
r_static
r_struct
id|file_operations
id|port_fops
op_assign
(brace
id|memory_lseek
comma
id|read_port
comma
id|write_port
comma
l_int|NULL
comma
multiline_comment|/* port_readdir */
l_int|NULL
comma
multiline_comment|/* port_select */
l_int|NULL
comma
multiline_comment|/* port_ioctl */
l_int|NULL
comma
multiline_comment|/* port_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|variable|zero_fops
r_static
r_struct
id|file_operations
id|zero_fops
op_assign
(brace
id|zero_lseek
comma
id|read_zero
comma
id|write_zero
comma
l_int|NULL
comma
multiline_comment|/* zero_readdir */
l_int|NULL
comma
multiline_comment|/* zero_select */
l_int|NULL
comma
multiline_comment|/* zero_ioctl */
id|mmap_zero
comma
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
DECL|variable|full_fops
r_static
r_struct
id|file_operations
id|full_fops
op_assign
(brace
id|memory_lseek
comma
id|read_full
comma
id|write_full
comma
l_int|NULL
comma
multiline_comment|/* full_readdir */
l_int|NULL
comma
multiline_comment|/* full_select */
l_int|NULL
comma
multiline_comment|/* full_ioctl */
l_int|NULL
comma
multiline_comment|/* full_mmap */
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
DECL|function|memory_open
r_static
r_int
id|memory_open
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
id|filp
)paren
(brace
r_switch
c_cond
(paren
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|ram_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|mem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|kmem_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|null_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|port_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|zero_fops
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
id|filp-&gt;f_op
op_assign
op_amp
id|full_fops
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
id|filp-&gt;f_op
op_logical_and
id|filp-&gt;f_op-&gt;open
)paren
r_return
id|filp-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|filp
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|memory_fops
r_static
r_struct
id|file_operations
id|memory_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
l_int|NULL
comma
multiline_comment|/* read */
l_int|NULL
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select */
l_int|NULL
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|memory_open
comma
multiline_comment|/* just a selector for the real open */
l_int|NULL
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_FTAPE
DECL|variable|ftape_big_buffer
r_char
op_star
id|ftape_big_buffer
suffix:semicolon
macro_line|#endif
DECL|function|chr_dev_init
r_int
id|chr_dev_init
c_func
(paren
r_int
id|mem_start
comma
r_int
id|mem_end
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MEM_MAJOR
comma
l_string|&quot;mem&quot;
comma
op_amp
id|memory_fops
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;unable to get major %d for memory devs&bslash;n&quot;
comma
id|MEM_MAJOR
)paren
suffix:semicolon
id|mem_start
op_assign
id|tty_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PRINTER
id|mem_start
op_assign
id|lp_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined (CONFIG_BUSMOUSE) || defined (CONFIG_82C710_MOUSE) || &bslash;&n;    defined (CONFIG_PSMOUSE) || defined (CONFIG_MS_BUSMOUSE) || &bslash;&n;    defined (CONFIG_ATIXL_BUSMOUSE)
id|mem_start
op_assign
id|mouse_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SOUND
id|mem_start
op_assign
id|soundcard_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if CONFIG_QIC02_TAPE
id|mem_start
op_assign
id|qic02_tape_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; *      Rude way to allocate kernel memory buffer for tape device&n; */
macro_line|#ifdef CONFIG_FTAPE
multiline_comment|/* allocate NR_FTAPE_BUFFERS 32Kb buffers at aligned address */
id|ftape_big_buffer
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
id|mem_start
op_plus
l_int|0x7fff
)paren
op_amp
op_complement
l_int|0x7fff
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ftape: allocated %d buffers aligned at: %p&bslash;n&quot;
comma
id|NR_FTAPE_BUFFERS
comma
id|ftape_big_buffer
)paren
suffix:semicolon
id|mem_start
op_assign
(paren
r_int
)paren
id|ftape_big_buffer
op_plus
id|NR_FTAPE_BUFFERS
op_star
l_int|0x8000
suffix:semicolon
macro_line|#endif 
r_return
id|mem_start
suffix:semicolon
)brace
eof
