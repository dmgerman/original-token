DECL|macro|__KERNEL_SYSCALLS__
mdefine_line|#define __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|errno
r_static
r_int
id|errno
suffix:semicolon
DECL|function|do_mod_firmware_load
r_static
r_int
id|do_mod_firmware_load
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_char
op_star
op_star
id|fp
)paren
(brace
r_int
id|fd
suffix:semicolon
r_int
id|l
suffix:semicolon
r_char
op_star
id|dp
suffix:semicolon
id|fd
op_assign
id|open
c_func
(paren
id|fn
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_eq
op_minus
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Unable to load &squot;%s&squot;.&bslash;n&quot;
comma
id|fn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|l
op_assign
id|lseek
c_func
(paren
id|fd
comma
l_int|0L
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l
op_le
l_int|0
op_logical_or
id|l
OG
l_int|65535
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Invalid firmware &squot;%s&squot;&bslash;n&quot;
comma
id|fn
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|lseek
c_func
(paren
id|fd
comma
l_int|0L
comma
l_int|0
)paren
suffix:semicolon
id|dp
op_assign
id|kmalloc
c_func
(paren
id|l
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Out of memory loading &squot;%s&squot;.&bslash;n&quot;
comma
id|fn
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|read
c_func
(paren
id|fd
comma
id|dp
comma
id|l
)paren
op_ne
id|l
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Failed to read &squot;%s&squot;.&bslash;n&quot;
comma
id|fn
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dp
)paren
suffix:semicolon
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|close
c_func
(paren
id|fd
)paren
suffix:semicolon
op_star
id|fp
op_assign
id|dp
suffix:semicolon
r_return
(paren
r_int
)paren
id|l
suffix:semicolon
)brace
DECL|function|mod_firmware_load
r_int
id|mod_firmware_load
c_func
(paren
r_const
r_char
op_star
id|fn
comma
r_char
op_star
op_star
id|fp
)paren
(brace
r_int
id|r
suffix:semicolon
id|mm_segment_t
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|r
op_assign
id|do_mod_firmware_load
c_func
(paren
id|fn
comma
id|fp
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
r_return
id|r
suffix:semicolon
)brace
eof