multiline_comment|/*&n; *  linux/kernel/chr_drv/mem.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/mouse.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
id|addr
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|pde
comma
id|pte
comma
id|page
suffix:semicolon
r_int
id|i
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
id|addr
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|tmp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_break
suffix:semicolon
id|pde
op_assign
id|current-&gt;tss.cr3
op_plus
(paren
id|addr
op_rshift
l_int|20
op_amp
l_int|0xffc
)paren
suffix:semicolon
id|pte
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pde
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte
op_amp
id|PAGE_PRESENT
)paren
)paren
r_break
suffix:semicolon
id|pte
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|pte
op_add_assign
(paren
id|addr
op_rshift
l_int|10
)paren
op_amp
l_int|0xffc
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
l_int|1
)paren
)paren
r_break
suffix:semicolon
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
id|addr
op_amp
l_int|0xfff
suffix:semicolon
id|i
op_assign
l_int|4096
op_minus
(paren
id|addr
op_amp
l_int|0xfff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|count
)paren
id|i
op_assign
id|count
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|tmp
comma
(paren
r_void
op_star
)paren
id|page
comma
id|i
)paren
suffix:semicolon
id|addr
op_add_assign
id|i
suffix:semicolon
id|tmp
op_add_assign
id|i
suffix:semicolon
id|count
op_sub_assign
id|i
suffix:semicolon
)brace
id|file-&gt;f_pos
op_assign
id|addr
suffix:semicolon
r_return
id|tmp
op_minus
id|buf
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
id|addr
suffix:semicolon
r_char
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|pde
comma
id|pte
comma
id|page
suffix:semicolon
r_int
id|i
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
id|addr
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|tmp
op_assign
id|buf
suffix:semicolon
r_while
c_loop
(paren
id|count
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_break
suffix:semicolon
id|pde
op_assign
id|current-&gt;tss.cr3
op_plus
(paren
id|addr
op_rshift
l_int|20
op_amp
l_int|0xffc
)paren
suffix:semicolon
id|pte
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pde
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pte
op_amp
id|PAGE_PRESENT
)paren
)paren
r_break
suffix:semicolon
id|pte
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|pte
op_add_assign
(paren
id|addr
op_rshift
l_int|10
)paren
op_amp
l_int|0xffc
suffix:semicolon
id|page
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|pte
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
id|PAGE_PRESENT
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|page
op_amp
l_int|2
)paren
)paren
(brace
id|do_wp_page
c_func
(paren
l_int|0
comma
id|addr
comma
id|current
comma
l_int|0
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|page
op_and_assign
l_int|0xfffff000
suffix:semicolon
id|page
op_add_assign
id|addr
op_amp
l_int|0xfff
suffix:semicolon
id|i
op_assign
l_int|4096
op_minus
(paren
id|addr
op_amp
l_int|0xfff
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|count
)paren
id|i
op_assign
id|count
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
(paren
r_void
op_star
)paren
id|page
comma
id|tmp
comma
id|i
)paren
suffix:semicolon
id|addr
op_add_assign
id|i
suffix:semicolon
id|tmp
op_add_assign
id|i
suffix:semicolon
id|count
op_sub_assign
id|i
suffix:semicolon
)brace
id|file-&gt;f_pos
op_assign
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_ne
id|buf
)paren
r_return
id|tmp
op_minus
id|buf
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
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
r_int
id|p
op_assign
id|file-&gt;f_pos
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
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|write_kmem
r_static
r_int
id|write_kmem
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
id|file-&gt;f_pos
op_add_assign
id|count
suffix:semicolon
r_return
id|count
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
multiline_comment|/*&n; * The memory devices use the full 32 bits of the offset, and so we cannot&n; * check against negative addresses: they are ok. The return value is weird,&n; * though, in that case (0).&n; *&n; * also note that seeking relative to the &quot;end of file&quot; isn&squot;t supported:&n; * it has no meaning, so it returns -EINVAL.&n; */
DECL|function|mem_lseek
r_static
r_int
id|mem_lseek
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
DECL|function|mem_read
r_static
r_int
id|mem_read
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
r_return
id|read_ram
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
r_case
l_int|1
suffix:colon
r_return
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
r_case
l_int|2
suffix:colon
r_return
id|read_kmem
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
r_case
l_int|3
suffix:colon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* /dev/null */
r_case
l_int|4
suffix:colon
r_return
id|read_port
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
r_case
l_int|5
suffix:colon
r_return
id|read_zero
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
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|function|mem_write
r_static
r_int
id|mem_write
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
r_return
id|write_ram
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
r_case
l_int|1
suffix:colon
r_return
id|write_mem
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
r_case
l_int|2
suffix:colon
r_return
id|write_kmem
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
r_case
l_int|3
suffix:colon
r_return
id|count
suffix:semicolon
multiline_comment|/* /dev/null */
r_case
l_int|4
suffix:colon
r_return
id|write_port
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
r_case
l_int|5
suffix:colon
r_return
id|count
suffix:semicolon
multiline_comment|/* /dev/zero */
r_default
suffix:colon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
)brace
DECL|variable|mem_fops
r_static
r_struct
id|file_operations
id|mem_fops
op_assign
(brace
id|mem_lseek
comma
id|mem_read
comma
id|mem_write
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
l_int|NULL
comma
multiline_comment|/* no special open code */
l_int|NULL
multiline_comment|/* no special release code */
)brace
suffix:semicolon
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
id|chrdev_fops
(braket
l_int|1
)braket
op_assign
op_amp
id|mem_fops
suffix:semicolon
id|mem_start
op_assign
id|tty_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
id|mem_start
op_assign
id|lp_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
id|mem_start
op_assign
id|mouse_init
c_func
(paren
id|mem_start
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
eof
