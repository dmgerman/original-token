macro_line|#ident &quot;$Id$&quot;
multiline_comment|/* ----------------------------------------------------------------------- *&n; *   &n; *   Copyright 2000 H. Peter Anvin - All Rights Reserved&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation, Inc., 675 Mass Ave, Cambridge MA 02139,&n; *   USA; either version 2 of the License, or (at your option) any later&n; *   version; incorporated herein by reference.&n; *&n; * ----------------------------------------------------------------------- */
multiline_comment|/*&n; * msr.c&n; *&n; * x86 MSR access device&n; *&n; * This device is accessed by lseek() to the appropriate register number&n; * and then read/write in chunks of 8 bytes.  A larger size means multiple&n; * reads or writes of the same register.&n; *&n; * This driver uses /dev/cpu/%d/msr where %d is the minor number, and on&n; * an SMP box will direct the access to CPU %d.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/msr.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Note: &quot;err&quot; is handled in a funny way below.  Otherwise one version&n;   of gcc or another breaks. */
DECL|function|wrmsr_eio
r_extern
r_inline
r_int
id|wrmsr_eio
c_func
(paren
id|u32
id|reg
comma
id|u32
id|eax
comma
id|u32
id|edx
)paren
(brace
r_int
id|err
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1:&t;wrmsr&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&t;movl %4,%0&bslash;n&quot;
l_string|&quot;&t;jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;bDS&quot;
(paren
id|err
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|eax
)paren
comma
l_string|&quot;d&quot;
(paren
id|edx
)paren
comma
l_string|&quot;c&quot;
(paren
id|reg
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EIO
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|rdmsr_eio
r_extern
r_inline
r_int
id|rdmsr_eio
c_func
(paren
id|u32
id|reg
comma
id|u32
op_star
id|eax
comma
id|u32
op_star
id|edx
)paren
(brace
r_int
id|err
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;1:&t;rdmsr&bslash;n&quot;
l_string|&quot;2:&bslash;n&quot;
l_string|&quot;.section .fixup,&bslash;&quot;ax&bslash;&quot;&bslash;n&quot;
l_string|&quot;3:&t;movl %4,%0&bslash;n&quot;
l_string|&quot;&t;jmp 2b&bslash;n&quot;
l_string|&quot;.previous&bslash;n&quot;
l_string|&quot;.section __ex_table,&bslash;&quot;a&bslash;&quot;&bslash;n&quot;
l_string|&quot;&t;.align 4&bslash;n&quot;
l_string|&quot;&t;.long 1b,3b&bslash;n&quot;
l_string|&quot;.previous&quot;
suffix:colon
l_string|&quot;=&amp;bDS&quot;
(paren
id|err
)paren
comma
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|edx
)paren
suffix:colon
l_string|&quot;c&quot;
(paren
id|reg
)paren
comma
l_string|&quot;i&quot;
(paren
op_minus
id|EIO
)paren
comma
l_string|&quot;0&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
DECL|struct|msr_command
r_struct
id|msr_command
(brace
DECL|member|cpu
r_int
id|cpu
suffix:semicolon
DECL|member|err
r_int
id|err
suffix:semicolon
DECL|member|reg
id|u32
id|reg
suffix:semicolon
DECL|member|data
id|u32
id|data
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|msr_smp_wrmsr
r_static
r_void
id|msr_smp_wrmsr
c_func
(paren
r_void
op_star
id|cmd_block
)paren
(brace
r_struct
id|msr_command
op_star
id|cmd
op_assign
(paren
r_struct
id|msr_command
op_star
)paren
id|cmd_block
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
id|cmd-&gt;err
op_assign
id|wrmsr_eio
c_func
(paren
id|cmd-&gt;reg
comma
id|cmd-&gt;data
(braket
l_int|0
)braket
comma
id|cmd-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|msr_smp_rdmsr
r_static
r_void
id|msr_smp_rdmsr
c_func
(paren
r_void
op_star
id|cmd_block
)paren
(brace
r_struct
id|msr_command
op_star
id|cmd
op_assign
(paren
r_struct
id|msr_command
op_star
)paren
id|cmd_block
suffix:semicolon
r_if
c_cond
(paren
id|cmd-&gt;cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
id|cmd-&gt;err
op_assign
id|rdmsr_eio
c_func
(paren
id|cmd-&gt;reg
comma
op_amp
id|cmd-&gt;data
(braket
l_int|0
)braket
comma
op_amp
id|cmd-&gt;data
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|do_wrmsr
r_extern
r_inline
r_int
id|do_wrmsr
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
id|eax
comma
id|u32
id|edx
)paren
(brace
r_struct
id|msr_command
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
r_return
id|wrmsr_eio
c_func
(paren
id|reg
comma
id|eax
comma
id|edx
)paren
suffix:semicolon
)brace
r_else
(brace
id|cmd.cpu
op_assign
id|cpu
suffix:semicolon
id|cmd.reg
op_assign
id|reg
suffix:semicolon
id|cmd.data
(braket
l_int|0
)braket
op_assign
id|eax
suffix:semicolon
id|cmd.data
(braket
l_int|1
)braket
op_assign
id|edx
suffix:semicolon
id|smp_call_function
c_func
(paren
id|msr_smp_wrmsr
comma
op_amp
id|cmd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_return
id|cmd.err
suffix:semicolon
)brace
)brace
DECL|function|do_rdmsr
r_extern
r_inline
r_int
id|do_rdmsr
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
op_star
id|eax
comma
id|u32
op_star
id|edx
)paren
(brace
r_struct
id|msr_command
id|cmd
suffix:semicolon
r_if
c_cond
(paren
id|cpu
op_eq
id|smp_processor_id
c_func
(paren
)paren
)paren
(brace
r_return
id|rdmsr_eio
c_func
(paren
id|reg
comma
id|eax
comma
id|edx
)paren
suffix:semicolon
)brace
r_else
(brace
id|cmd.cpu
op_assign
id|cpu
suffix:semicolon
id|cmd.reg
op_assign
id|reg
suffix:semicolon
id|smp_call_function
c_func
(paren
id|msr_smp_rdmsr
comma
op_amp
id|cmd
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
op_star
id|eax
op_assign
id|cmd.data
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|edx
op_assign
id|cmd.data
(braket
l_int|1
)braket
suffix:semicolon
r_return
id|cmd.err
suffix:semicolon
)brace
)brace
macro_line|#else /* ! CONFIG_SMP */
DECL|function|do_wrmsr
r_extern
r_inline
r_int
id|do_wrmsr
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
id|eax
comma
id|u32
id|edx
)paren
(brace
r_return
id|wrmsr_eio
c_func
(paren
id|reg
comma
id|eax
comma
id|edx
)paren
suffix:semicolon
)brace
DECL|function|do_rdmsr
r_extern
r_inline
r_int
id|do_rdmsr
c_func
(paren
r_int
id|cpu
comma
id|u32
id|reg
comma
id|u32
op_star
id|eax
comma
id|u32
op_star
id|edx
)paren
(brace
r_return
id|rdmsr_eio
c_func
(paren
id|reg
comma
id|eax
comma
id|edx
)paren
suffix:semicolon
)brace
macro_line|#endif /* ! CONFIG_SMP */
DECL|function|msr_seek
r_static
id|loff_t
id|msr_seek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|loff_t
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
multiline_comment|/* SEEK_END not supported */
)brace
)brace
DECL|function|msr_read
r_static
id|ssize_t
id|msr_read
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
id|u32
op_star
id|tmp
op_assign
(paren
id|u32
op_star
)paren
id|buf
suffix:semicolon
id|u32
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|u32
id|reg
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|cpu
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|count
op_mod
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Invalid chunk size */
r_for
c_loop
(paren
id|rv
op_assign
l_int|0
suffix:semicolon
id|count
suffix:semicolon
id|count
op_sub_assign
l_int|8
)paren
(brace
id|err
op_assign
id|do_rdmsr
c_func
(paren
id|cpu
comma
id|reg
comma
op_amp
id|data
(braket
l_int|0
)braket
comma
op_amp
id|data
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|tmp
comma
op_amp
id|data
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|tmp
op_add_assign
l_int|2
suffix:semicolon
)brace
r_return
(paren
(paren
r_char
op_star
)paren
id|tmp
)paren
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|msr_write
r_static
id|ssize_t
id|msr_write
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
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_const
id|u32
op_star
id|tmp
op_assign
(paren
r_const
id|u32
op_star
)paren
id|buf
suffix:semicolon
id|u32
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|rv
suffix:semicolon
id|u32
id|reg
op_assign
op_star
id|ppos
suffix:semicolon
r_int
id|cpu
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|count
op_mod
l_int|8
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Invalid chunk size */
r_for
c_loop
(paren
id|rv
op_assign
l_int|0
suffix:semicolon
id|count
suffix:semicolon
id|count
op_sub_assign
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|data
comma
id|tmp
comma
l_int|8
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_assign
id|do_wrmsr
c_func
(paren
id|cpu
comma
id|reg
comma
id|data
(braket
l_int|0
)braket
comma
id|data
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|tmp
op_add_assign
l_int|2
suffix:semicolon
)brace
r_return
(paren
(paren
r_char
op_star
)paren
id|tmp
)paren
op_minus
id|buf
suffix:semicolon
)brace
DECL|function|msr_open
r_static
r_int
id|msr_open
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
r_int
id|cpu
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|cpuinfo_x86
op_star
id|c
op_assign
op_amp
(paren
id|cpu_data
)paren
(braket
id|cpu
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cpu_online_map
op_amp
(paren
l_int|1UL
op_lshift
id|cpu
)paren
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* No such CPU */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|X86_FEATURE_MSR
comma
op_amp
id|c-&gt;x86_capability
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* MSR not supported */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * File operations we support&n; */
DECL|variable|msr_fops
r_static
r_struct
id|file_operations
id|msr_fops
op_assign
(brace
id|owner
suffix:colon
id|THIS_MODULE
comma
id|llseek
suffix:colon
id|msr_seek
comma
id|read
suffix:colon
id|msr_read
comma
id|write
suffix:colon
id|msr_write
comma
id|open
suffix:colon
id|msr_open
comma
)brace
suffix:semicolon
DECL|function|msr_init
r_int
id|__init
id|msr_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|MSR_MAJOR
comma
l_string|&quot;cpu/msr&quot;
comma
op_amp
id|msr_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;msr: unable to get major %d for msr&bslash;n&quot;
comma
id|MSR_MAJOR
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|msr_exit
r_void
id|__exit
id|msr_exit
c_func
(paren
r_void
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|MSR_MAJOR
comma
l_string|&quot;cpu/msr&quot;
)paren
suffix:semicolon
)brace
DECL|variable|msr_init
id|module_init
c_func
(paren
id|msr_init
)paren
suffix:semicolon
id|module_exit
c_func
(paren
id|msr_exit
)paren
id|EXPORT_NO_SYMBOLS
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;H. Peter Anvin &lt;hpa@zytor.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;x86 generic MSR driver&quot;
)paren
suffix:semicolon
eof
