multiline_comment|/*&n; *  linux/fs/exec.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
multiline_comment|/*&n; * #!-checking implemented by tytso.&n; */
multiline_comment|/*&n; * Demand-loading implemented 01.12.91 - no need to read anything but&n; * the header into memory. The inode of the executable is put into&n; * &quot;current-&gt;executable&quot;, and page faults do the actual loading. Clean.&n; *&n; * Once more I can proudly say that linux stood up to being changed: it&n; * was less than 2 hours work to get demand-loading completely implemented.&n; *&n; * Demand loading changed July 1993 by Eric Youngdale.   Use mmap instead,&n; * current-&gt;executable is only used by the procfs.  This allows a dispatch&n; * table to check for several different types  of binary formats.  We keep&n; * trying until we recognize the file or we run out of supported binary&n; * formats. &n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/file.h&gt;
macro_line|#include &lt;linux/mman.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_KERNELD
macro_line|#include &lt;linux/kerneld.h&gt;
macro_line|#endif
id|asmlinkage
r_int
id|sys_exit
c_func
(paren
r_int
id|exit_code
)paren
suffix:semicolon
id|asmlinkage
r_int
id|sys_brk
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * Here are the actual binaries that will be accepted:&n; * add more with &quot;register_binfmt()&quot; if using modules...&n; *&n; * These are defined again for the &squot;real&squot; modules if you are using a&n; * module definition for these routines.&n; */
DECL|variable|formats
r_static
r_struct
id|linux_binfmt
op_star
id|formats
op_assign
(paren
r_struct
id|linux_binfmt
op_star
)paren
l_int|NULL
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|binfmt_setup
c_func
(paren
r_void
)paren
)paren
(brace
macro_line|#ifdef CONFIG_BINFMT_MISC
id|init_misc_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_ELF
id|init_elf_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_ELF32
id|init_elf32_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_AOUT
id|init_aout_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_AOUT32
id|init_aout32_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_JAVA
id|init_java_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_EM86
id|init_em86_binfmt
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* This cannot be configured out of the kernel */
id|init_script_binfmt
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|register_binfmt
r_int
id|register_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
id|fmt
)paren
(brace
r_struct
id|linux_binfmt
op_star
op_star
id|tmp
op_assign
op_amp
id|formats
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fmt
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|fmt-&gt;next
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_while
c_loop
(paren
op_star
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|fmt
op_eq
op_star
id|tmp
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|tmp
op_assign
op_amp
(paren
op_star
id|tmp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
id|fmt-&gt;next
op_assign
id|formats
suffix:semicolon
id|formats
op_assign
id|fmt
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MODULES
DECL|function|unregister_binfmt
r_int
id|unregister_binfmt
c_func
(paren
r_struct
id|linux_binfmt
op_star
id|fmt
)paren
(brace
r_struct
id|linux_binfmt
op_star
op_star
id|tmp
op_assign
op_amp
id|formats
suffix:semicolon
r_while
c_loop
(paren
op_star
id|tmp
)paren
(brace
r_if
c_cond
(paren
id|fmt
op_eq
op_star
id|tmp
)paren
(brace
op_star
id|tmp
op_assign
id|fmt-&gt;next
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|tmp
op_assign
op_amp
(paren
op_star
id|tmp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_MODULES */
multiline_comment|/* N.B. Error returns must be &lt; 0 */
DECL|function|open_dentry
r_int
id|open_dentry
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
id|mode
)paren
(brace
r_int
id|fd
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_struct
id|file
op_star
id|f
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;default_file_ops
)paren
r_goto
id|out
suffix:semicolon
id|fd
op_assign
id|get_unused_fd
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
op_ge
l_int|0
)paren
(brace
id|error
op_assign
op_minus
id|ENFILE
suffix:semicolon
id|f
op_assign
id|get_empty_filp
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|f
)paren
r_goto
id|out_fd
suffix:semicolon
id|f-&gt;f_flags
op_assign
id|mode
suffix:semicolon
id|f-&gt;f_mode
op_assign
(paren
id|mode
op_plus
l_int|1
)paren
op_amp
id|O_ACCMODE
suffix:semicolon
id|f-&gt;f_dentry
op_assign
id|dentry
suffix:semicolon
id|f-&gt;f_pos
op_assign
l_int|0
suffix:semicolon
id|f-&gt;f_reada
op_assign
l_int|0
suffix:semicolon
id|f-&gt;f_op
op_assign
id|inode-&gt;i_op-&gt;default_file_ops
suffix:semicolon
r_if
c_cond
(paren
id|f-&gt;f_op-&gt;open
)paren
(brace
id|error
op_assign
id|f-&gt;f_op
op_member_access_from_pointer
id|open
c_func
(paren
id|inode
comma
id|f
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_goto
id|out_filp
suffix:semicolon
)brace
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
op_assign
id|f
suffix:semicolon
id|dget
c_func
(paren
id|dentry
)paren
suffix:semicolon
)brace
r_return
id|fd
suffix:semicolon
id|out_filp
suffix:colon
r_if
c_cond
(paren
id|error
OG
l_int|0
)paren
id|error
op_assign
op_minus
id|EIO
suffix:semicolon
id|put_filp
c_func
(paren
id|f
)paren
suffix:semicolon
id|out_fd
suffix:colon
id|put_unused_fd
c_func
(paren
id|fd
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that a shared library must be both readable and executable due to&n; * security reasons.&n; *&n; * Also note that we take the address to load from from the file itself.&n; */
DECL|function|sys_uselib
id|asmlinkage
r_int
id|sys_uselib
c_func
(paren
r_const
r_char
op_star
id|library
)paren
(brace
r_int
id|fd
comma
id|retval
suffix:semicolon
r_struct
id|file
op_star
id|file
suffix:semicolon
r_struct
id|linux_binfmt
op_star
id|fmt
suffix:semicolon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|fd
op_assign
id|sys_open
c_func
(paren
id|library
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
r_goto
id|out
suffix:semicolon
id|file
op_assign
id|current-&gt;files-&gt;fd
(braket
id|fd
)braket
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
id|file
op_logical_and
id|file-&gt;f_dentry
op_logical_and
id|file-&gt;f_op
op_logical_and
id|file-&gt;f_op-&gt;read
)paren
(brace
r_for
c_loop
(paren
id|fmt
op_assign
id|formats
suffix:semicolon
id|fmt
suffix:semicolon
id|fmt
op_assign
id|fmt-&gt;next
)paren
(brace
r_int
(paren
op_star
id|fn
)paren
(paren
r_int
)paren
op_assign
id|fmt-&gt;load_shlib
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
r_continue
suffix:semicolon
id|retval
op_assign
id|fn
c_func
(paren
id|fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
op_minus
id|ENOEXEC
)paren
r_break
suffix:semicolon
)brace
)brace
id|sys_close
c_func
(paren
id|fd
)paren
suffix:semicolon
id|out
suffix:colon
id|unlock_kernel
c_func
(paren
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * count() counts the number of arguments/envelopes&n; */
DECL|function|count
r_static
r_int
id|count
c_func
(paren
r_char
op_star
op_star
id|argv
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|argv
op_ne
l_int|NULL
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_int
id|error
suffix:semicolon
id|error
op_assign
id|get_user
c_func
(paren
id|p
comma
id|argv
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_break
suffix:semicolon
id|argv
op_increment
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
)brace
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * &squot;copy_string()&squot; copies argument/envelope strings from user&n; * memory to free pages in kernel mem. These are in a format ready&n; * to be put directly into the top of new user memory.&n; *&n; * Modified by TYT, 11/24/91 to add the from_kmem argument, which specifies&n; * whether the string and the string array are from user or kernel segments:&n; * &n; * from_kmem     argv *        argv **&n; *    0          user space    user space&n; *    1          kernel space  user space&n; *    2          kernel space  kernel space&n; * &n; * We do this by playing games with the fs segment register.  Since it&n; * is expensive to load a segment register, we try to avoid calling&n; * set_fs() unless we absolutely have to.&n; */
DECL|function|copy_strings
r_int
r_int
id|copy_strings
c_func
(paren
r_int
id|argc
comma
r_char
op_star
op_star
id|argv
comma
r_int
r_int
op_star
id|page
comma
r_int
r_int
id|p
comma
r_int
id|from_kmem
)paren
(brace
r_char
op_star
id|str
suffix:semicolon
r_int
r_int
id|old_fs
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* bullet-proofing */
id|old_fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
r_while
c_loop
(paren
id|argc
op_decrement
OG
l_int|0
)paren
(brace
r_int
id|len
suffix:semicolon
r_int
r_int
id|pos
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|1
)paren
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|get_user
c_func
(paren
id|str
comma
id|argv
op_plus
id|argc
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|str
)paren
id|panic
c_func
(paren
l_string|&quot;VFS: argc is wrong&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|1
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
id|len
op_assign
id|strlen_user
c_func
(paren
id|str
)paren
suffix:semicolon
multiline_comment|/* includes the &squot;&bslash;0&squot; */
r_if
c_cond
(paren
id|p
OL
id|len
)paren
(brace
multiline_comment|/* this shouldn&squot;t happen - 128kB */
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_sub_assign
id|len
suffix:semicolon
id|pos
op_assign
id|p
suffix:semicolon
r_while
c_loop
(paren
id|len
)paren
(brace
r_char
op_star
id|pag
suffix:semicolon
r_int
id|offset
comma
id|bytes_to_copy
suffix:semicolon
id|offset
op_assign
id|pos
op_mod
id|PAGE_SIZE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|pag
op_assign
(paren
r_char
op_star
)paren
id|page
(braket
id|pos
op_div
id|PAGE_SIZE
)braket
)paren
op_logical_and
op_logical_neg
(paren
id|pag
op_assign
(paren
r_char
op_star
)paren
id|page
(braket
id|pos
op_div
id|PAGE_SIZE
)braket
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_free_page
c_func
(paren
id|GFP_USER
)paren
)paren
)paren
(brace
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|bytes_to_copy
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|bytes_to_copy
OG
id|len
)paren
id|bytes_to_copy
op_assign
id|len
suffix:semicolon
id|copy_from_user
c_func
(paren
id|pag
op_plus
id|offset
comma
id|str
comma
id|bytes_to_copy
)paren
suffix:semicolon
id|pos
op_add_assign
id|bytes_to_copy
suffix:semicolon
id|str
op_add_assign
id|bytes_to_copy
suffix:semicolon
id|len
op_sub_assign
id|bytes_to_copy
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|from_kmem
op_eq
l_int|2
)paren
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
r_return
id|p
suffix:semicolon
)brace
DECL|function|setup_arg_pages
r_int
r_int
id|setup_arg_pages
c_func
(paren
r_int
r_int
id|p
comma
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_int
r_int
id|stack_base
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|mpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|stack_base
op_assign
id|STACK_TOP
op_minus
id|MAX_ARG_PAGES
op_star
id|PAGE_SIZE
suffix:semicolon
id|p
op_add_assign
id|stack_base
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;loader
)paren
id|bprm-&gt;loader
op_add_assign
id|stack_base
suffix:semicolon
id|bprm-&gt;exec
op_add_assign
id|stack_base
suffix:semicolon
id|mpnt
op_assign
id|kmem_cache_alloc
c_func
(paren
id|vm_area_cachep
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mpnt
)paren
(brace
id|mpnt-&gt;vm_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|mpnt-&gt;vm_start
op_assign
id|PAGE_MASK
op_amp
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|mpnt-&gt;vm_end
op_assign
id|STACK_TOP
suffix:semicolon
id|mpnt-&gt;vm_page_prot
op_assign
id|PAGE_COPY
suffix:semicolon
id|mpnt-&gt;vm_flags
op_assign
id|VM_STACK_FLAGS
suffix:semicolon
id|mpnt-&gt;vm_ops
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_offset
op_assign
l_int|0
suffix:semicolon
id|mpnt-&gt;vm_dentry
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_pte
op_assign
l_int|0
suffix:semicolon
id|insert_vm_struct
c_func
(paren
id|current-&gt;mm
comma
id|mpnt
)paren
suffix:semicolon
id|current-&gt;mm-&gt;total_vm
op_assign
(paren
id|mpnt-&gt;vm_end
op_minus
id|mpnt-&gt;vm_start
)paren
op_rshift
id|PAGE_SHIFT
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
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|bprm-&gt;page
(braket
id|i
)braket
)paren
(brace
id|current-&gt;mm-&gt;rss
op_increment
suffix:semicolon
id|put_dirty_page
c_func
(paren
id|current
comma
id|bprm-&gt;page
(braket
id|i
)braket
comma
id|stack_base
)paren
suffix:semicolon
)brace
id|stack_base
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
r_return
id|p
suffix:semicolon
)brace
multiline_comment|/*&n; * Read in the complete executable. This is used for &quot;-N&quot; files&n; * that aren&squot;t on a block boundary, and for files on filesystems&n; * without bmap support.&n; */
DECL|function|read_exec
r_int
id|read_exec
c_func
(paren
r_struct
id|dentry
op_star
id|dentry
comma
r_int
r_int
id|offset
comma
r_char
op_star
id|addr
comma
r_int
r_int
id|count
comma
r_int
id|to_kmem
)paren
(brace
r_struct
id|file
id|file
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|dentry-&gt;d_inode
suffix:semicolon
r_int
id|result
op_assign
op_minus
id|ENOEXEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_op
op_logical_or
op_logical_neg
id|inode-&gt;i_op-&gt;default_file_ops
)paren
r_goto
id|end_readexec
suffix:semicolon
r_if
c_cond
(paren
id|init_private_file
c_func
(paren
op_amp
id|file
comma
id|dentry
comma
l_int|1
)paren
)paren
r_goto
id|end_readexec
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|file.f_op-&gt;read
)paren
r_goto
id|close_readexec
suffix:semicolon
r_if
c_cond
(paren
id|file.f_op-&gt;llseek
)paren
(brace
r_if
c_cond
(paren
id|file.f_op
op_member_access_from_pointer
id|llseek
c_func
(paren
id|inode
comma
op_amp
id|file
comma
id|offset
comma
l_int|0
)paren
op_ne
id|offset
)paren
r_goto
id|close_readexec
suffix:semicolon
)brace
r_else
id|file.f_pos
op_assign
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|to_kmem
)paren
(brace
r_int
r_int
id|old_fs
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
id|result
op_assign
id|file.f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
op_amp
id|file
comma
id|addr
comma
id|count
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|old_fs
)paren
suffix:semicolon
)brace
r_else
(brace
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|addr
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|close_readexec
suffix:semicolon
id|result
op_assign
id|file.f_op
op_member_access_from_pointer
id|read
c_func
(paren
id|inode
comma
op_amp
id|file
comma
id|addr
comma
id|count
)paren
suffix:semicolon
)brace
id|close_readexec
suffix:colon
r_if
c_cond
(paren
id|file.f_op-&gt;release
)paren
id|file.f_op
op_member_access_from_pointer
id|release
c_func
(paren
id|inode
comma
op_amp
id|file
)paren
suffix:semicolon
id|end_readexec
suffix:colon
r_return
id|result
suffix:semicolon
)brace
DECL|function|exec_mmap
r_static
r_int
id|exec_mmap
c_func
(paren
r_void
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
comma
op_star
id|old_mm
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;mm-&gt;count
op_eq
l_int|1
)paren
(brace
id|flush_cache_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
id|exit_mmap
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
id|clear_page_tables
c_func
(paren
id|current
)paren
suffix:semicolon
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The clear_page_tables done later on exec does the right thing&n;&t; * to the page directory when shared, except for graceful abort&n;&t; * (the oom is wrong there, too, IMHO)&n;&t; */
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
id|mm
op_assign
id|mm_alloc
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_goto
id|fail_nomem
suffix:semicolon
id|mm-&gt;cpu_vm_mask
op_assign
(paren
l_int|1UL
op_lshift
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|mm-&gt;total_vm
op_assign
l_int|0
suffix:semicolon
id|mm-&gt;rss
op_assign
l_int|0
suffix:semicolon
id|old_mm
op_assign
id|current-&gt;mm
suffix:semicolon
id|current-&gt;mm
op_assign
id|mm
suffix:semicolon
id|retval
op_assign
id|new_page_tables
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|fail_restore
suffix:semicolon
id|mmput
c_func
(paren
id|old_mm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Failure ... restore the prior mm_struct.&n;&t; */
id|fail_restore
suffix:colon
id|current-&gt;mm
op_assign
id|old_mm
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * N.B. binfmt_xxx needs to handle the error instead of oom()&n;&t; */
id|fail_nomem
suffix:colon
multiline_comment|/* this is wrong, I think. */
id|oom
c_func
(paren
id|current
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * These functions flushes out all traces of the currently running executable&n; * so that a new one can be started&n; */
DECL|function|flush_old_signals
r_static
r_inline
r_void
id|flush_old_signals
c_func
(paren
r_struct
id|signal_struct
op_star
id|sig
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|sigaction
op_star
id|sa
op_assign
id|sig-&gt;action
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|32
suffix:semicolon
id|i
op_ne
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|sa-&gt;sa_mask
op_assign
l_int|0
suffix:semicolon
id|sa-&gt;sa_flags
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sa-&gt;sa_handler
op_ne
id|SIG_IGN
)paren
id|sa-&gt;sa_handler
op_assign
l_int|NULL
suffix:semicolon
id|sa
op_increment
suffix:semicolon
)brace
)brace
DECL|function|flush_old_files
r_static
r_inline
r_void
id|flush_old_files
c_func
(paren
r_struct
id|files_struct
op_star
id|files
)paren
(brace
r_int
r_int
id|j
suffix:semicolon
id|j
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|set
comma
id|i
suffix:semicolon
id|i
op_assign
id|j
op_star
id|__NFDBITS
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ge
id|NR_OPEN
)paren
r_break
suffix:semicolon
id|set
op_assign
id|files-&gt;close_on_exec.fds_bits
(braket
id|j
)braket
suffix:semicolon
id|files-&gt;close_on_exec.fds_bits
(braket
id|j
)braket
op_assign
l_int|0
suffix:semicolon
id|j
op_increment
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|set
suffix:semicolon
id|i
op_increment
comma
id|set
op_rshift_assign
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|set
op_amp
l_int|1
)paren
id|sys_close
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|flush_old_exec
r_void
id|flush_old_exec
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_char
op_star
id|name
suffix:semicolon
r_int
id|i
comma
id|ch
comma
id|retval
suffix:semicolon
multiline_comment|/* &n;&t; * Release all of the old mmap stuff ... do this first&n;&t; * so we can bail out on failure.&n;&t; */
id|retval
op_assign
id|exec_mmap
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;euid
op_eq
id|current-&gt;uid
op_logical_and
id|current-&gt;egid
op_eq
id|current-&gt;gid
)paren
id|current-&gt;dumpable
op_assign
l_int|1
suffix:semicolon
id|name
op_assign
id|bprm-&gt;filename
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|ch
op_assign
op_star
(paren
id|name
op_increment
)paren
)paren
op_ne
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|ch
op_eq
l_char|&squot;/&squot;
)paren
id|i
op_assign
l_int|0
suffix:semicolon
r_else
r_if
c_cond
(paren
id|i
OL
l_int|15
)paren
id|current-&gt;comm
(braket
id|i
op_increment
)braket
op_assign
id|ch
suffix:semicolon
)brace
id|current-&gt;comm
(braket
id|i
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|flush_thread
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;e_uid
op_ne
id|current-&gt;euid
op_logical_or
id|bprm-&gt;e_gid
op_ne
id|current-&gt;egid
op_logical_or
id|permission
c_func
(paren
id|bprm-&gt;dentry-&gt;d_inode
comma
id|MAY_READ
)paren
)paren
id|current-&gt;dumpable
op_assign
l_int|0
suffix:semicolon
id|flush_old_signals
c_func
(paren
id|current-&gt;sig
)paren
suffix:semicolon
id|flush_old_files
c_func
(paren
id|current-&gt;files
)paren
suffix:semicolon
id|out
suffix:colon
r_return
suffix:semicolon
multiline_comment|/* retval; FIXME. */
)brace
multiline_comment|/* &n; * Fill the binprm structure from the inode. &n; * Check permissions, then read the first 512 bytes&n; */
DECL|function|prepare_binprm
r_int
id|prepare_binprm
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_int
id|mode
suffix:semicolon
r_int
id|retval
comma
id|id_change
suffix:semicolon
r_struct
id|inode
op_star
id|inode
op_assign
id|bprm-&gt;dentry-&gt;d_inode
suffix:semicolon
id|mode
op_assign
id|inode-&gt;i_mode
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|S_ISREG
c_func
(paren
id|mode
)paren
)paren
multiline_comment|/* must be regular file */
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mode
op_amp
l_int|0111
)paren
)paren
multiline_comment|/* with at least _one_ execute bit set */
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|IS_NOEXEC
c_func
(paren
id|inode
)paren
)paren
multiline_comment|/* FS mustn&squot;t be mounted noexec */
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|inode-&gt;i_sb
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|permission
c_func
(paren
id|inode
comma
id|MAY_EXEC
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* better not execute files which are being written to */
r_if
c_cond
(paren
id|inode-&gt;i_writecount
OG
l_int|0
)paren
r_return
op_minus
id|ETXTBSY
suffix:semicolon
id|bprm-&gt;e_uid
op_assign
id|current-&gt;euid
suffix:semicolon
id|bprm-&gt;e_gid
op_assign
id|current-&gt;egid
suffix:semicolon
id|id_change
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Set-uid? */
r_if
c_cond
(paren
id|mode
op_amp
id|S_ISUID
)paren
(brace
id|bprm-&gt;e_uid
op_assign
id|inode-&gt;i_uid
suffix:semicolon
r_if
c_cond
(paren
id|bprm-&gt;e_uid
op_ne
id|current-&gt;euid
)paren
id|id_change
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Set-gid? */
multiline_comment|/*&n;&t; * If setgid is set but no group execute bit then this&n;&t; * is a candidate for mandatory locking, not a setgid&n;&t; * executable.&n;&t; */
r_if
c_cond
(paren
(paren
id|mode
op_amp
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
op_eq
(paren
id|S_ISGID
op_or
id|S_IXGRP
)paren
)paren
(brace
id|bprm-&gt;e_gid
op_assign
id|inode-&gt;i_gid
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_group_p
c_func
(paren
id|bprm-&gt;e_gid
)paren
)paren
id|id_change
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|id_change
)paren
(brace
multiline_comment|/* We can&squot;t suid-execute if we&squot;re sharing parts of the executable */
multiline_comment|/* or if we&squot;re being traced (or if suid execs are not allowed)    */
multiline_comment|/* (current-&gt;mm-&gt;count &gt; 1 is ok, as we&squot;ll get a new mm anyway)   */
r_if
c_cond
(paren
id|IS_NOSUID
c_func
(paren
id|inode
)paren
op_logical_or
(paren
id|current-&gt;flags
op_amp
id|PF_PTRACED
)paren
op_logical_or
(paren
id|current-&gt;fs-&gt;count
OG
l_int|1
)paren
op_logical_or
(paren
id|atomic_read
c_func
(paren
op_amp
id|current-&gt;sig-&gt;count
)paren
OG
l_int|1
)paren
op_logical_or
(paren
id|current-&gt;files-&gt;count
OG
l_int|1
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
)brace
)brace
id|memset
c_func
(paren
id|bprm-&gt;buf
comma
l_int|0
comma
r_sizeof
(paren
id|bprm-&gt;buf
)paren
)paren
suffix:semicolon
r_return
id|read_exec
c_func
(paren
id|bprm-&gt;dentry
comma
l_int|0
comma
id|bprm-&gt;buf
comma
l_int|128
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|remove_arg_zero
r_void
id|remove_arg_zero
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
(brace
r_if
c_cond
(paren
id|bprm-&gt;argc
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
id|offset
op_assign
id|bprm-&gt;p
op_mod
id|PAGE_SIZE
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|bprm-&gt;page
(braket
id|bprm-&gt;p
op_div
id|PAGE_SIZE
)braket
suffix:semicolon
r_while
c_loop
(paren
id|bprm-&gt;p
op_increment
comma
op_star
(paren
id|page
op_plus
id|offset
op_increment
)paren
)paren
r_if
c_cond
(paren
id|offset
op_eq
id|PAGE_SIZE
)paren
(brace
id|offset
op_assign
l_int|0
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|bprm-&gt;page
(braket
id|bprm-&gt;p
op_div
id|PAGE_SIZE
)braket
suffix:semicolon
)brace
id|bprm-&gt;argc
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * cycle the list of binary formats handler, until one recognizes the image&n; */
DECL|function|search_binary_handler
r_int
id|search_binary_handler
c_func
(paren
r_struct
id|linux_binprm
op_star
id|bprm
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_try
comma
id|retval
op_assign
l_int|0
suffix:semicolon
r_struct
id|linux_binfmt
op_star
id|fmt
suffix:semicolon
macro_line|#ifdef __alpha__
multiline_comment|/* handle /sbin/loader.. */
(brace
r_struct
id|exec
op_star
id|eh
op_assign
(paren
r_struct
id|exec
op_star
)paren
id|bprm-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;loader
op_logical_and
id|eh-&gt;fh.f_magic
op_eq
l_int|0x183
op_logical_and
(paren
id|eh-&gt;fh.f_flags
op_amp
l_int|0x3000
)paren
op_eq
l_int|0x3000
)paren
(brace
r_char
op_star
id|dynloader
(braket
)braket
op_assign
(brace
l_string|&quot;/sbin/loader&quot;
)brace
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
id|dput
c_func
(paren
id|bprm-&gt;dentry
)paren
suffix:semicolon
id|bprm-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
id|remove_arg_zero
c_func
(paren
id|bprm
)paren
suffix:semicolon
id|bprm-&gt;p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
id|dynloader
comma
id|bprm-&gt;page
comma
id|bprm-&gt;p
comma
l_int|2
)paren
suffix:semicolon
id|bprm-&gt;argc
op_increment
suffix:semicolon
id|bprm-&gt;loader
op_assign
id|bprm-&gt;p
suffix:semicolon
id|dentry
op_assign
id|open_namei
c_func
(paren
id|dynloader
(braket
l_int|0
)braket
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_return
id|retval
suffix:semicolon
id|bprm-&gt;dentry
op_assign
id|dentry
suffix:semicolon
id|retval
op_assign
id|prepare_binprm
c_func
(paren
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
OL
l_int|0
)paren
r_return
id|retval
suffix:semicolon
multiline_comment|/* should call search_binary_handler recursively here,&n;&t;&t;   but it does not matter */
)brace
)brace
macro_line|#endif
r_for
c_loop
(paren
r_try
op_assign
l_int|0
suffix:semicolon
r_try
OL
l_int|2
suffix:semicolon
r_try
op_increment
)paren
(brace
r_for
c_loop
(paren
id|fmt
op_assign
id|formats
suffix:semicolon
id|fmt
suffix:semicolon
id|fmt
op_assign
id|fmt-&gt;next
)paren
(brace
r_int
(paren
op_star
id|fn
)paren
(paren
r_struct
id|linux_binprm
op_star
comma
r_struct
id|pt_regs
op_star
)paren
op_assign
id|fmt-&gt;load_binary
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fn
)paren
r_continue
suffix:semicolon
id|retval
op_assign
id|fn
c_func
(paren
id|bprm
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|bprm-&gt;dentry
)paren
id|dput
c_func
(paren
id|bprm-&gt;dentry
)paren
suffix:semicolon
id|bprm-&gt;dentry
op_assign
l_int|NULL
suffix:semicolon
id|current-&gt;did_exec
op_assign
l_int|1
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ne
op_minus
id|ENOEXEC
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bprm-&gt;dentry
)paren
multiline_comment|/* We don&squot;t have the dentry anymore */
r_return
id|retval
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ne
op_minus
id|ENOEXEC
)paren
(brace
r_break
suffix:semicolon
macro_line|#ifdef CONFIG_KERNELD
)brace
r_else
(brace
DECL|macro|printable
mdefine_line|#define printable(c) (((c)==&squot;&bslash;t&squot;) || ((c)==&squot;&bslash;n&squot;) || (0x20&lt;=(c) &amp;&amp; (c)&lt;=0x7e))
r_char
id|modname
(braket
l_int|20
)braket
suffix:semicolon
r_if
c_cond
(paren
id|printable
c_func
(paren
id|bprm-&gt;buf
(braket
l_int|0
)braket
)paren
op_logical_and
id|printable
c_func
(paren
id|bprm-&gt;buf
(braket
l_int|1
)braket
)paren
op_logical_and
id|printable
c_func
(paren
id|bprm-&gt;buf
(braket
l_int|2
)braket
)paren
op_logical_and
id|printable
c_func
(paren
id|bprm-&gt;buf
(braket
l_int|3
)braket
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* -ENOEXEC */
id|sprintf
c_func
(paren
id|modname
comma
l_string|&quot;binfmt-%04x&quot;
comma
op_star
(paren
r_int
r_int
op_star
)paren
(paren
op_amp
id|bprm-&gt;buf
(braket
l_int|2
)braket
)paren
)paren
suffix:semicolon
id|request_module
c_func
(paren
id|modname
)paren
suffix:semicolon
macro_line|#endif
)brace
)brace
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * sys_execve() executes a new program.&n; */
DECL|function|do_execve
r_int
id|do_execve
c_func
(paren
r_char
op_star
id|filename
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|envp
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|linux_binprm
id|bprm
suffix:semicolon
r_struct
id|dentry
op_star
id|dentry
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|i
suffix:semicolon
id|bprm.p
op_assign
id|PAGE_SIZE
op_star
id|MAX_ARG_PAGES
op_minus
r_sizeof
(paren
r_void
op_star
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
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* clear page-table */
id|bprm.page
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|dentry
op_assign
id|open_namei
c_func
(paren
id|filename
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|retval
op_assign
id|PTR_ERR
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|dentry
)paren
)paren
r_return
id|retval
suffix:semicolon
id|bprm.dentry
op_assign
id|dentry
suffix:semicolon
id|bprm.filename
op_assign
id|filename
suffix:semicolon
id|bprm.sh_bang
op_assign
l_int|0
suffix:semicolon
id|bprm.java
op_assign
l_int|0
suffix:semicolon
id|bprm.loader
op_assign
l_int|0
suffix:semicolon
id|bprm.exec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
id|bprm.argc
op_assign
id|count
c_func
(paren
id|argv
)paren
)paren
OL
l_int|0
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|bprm.argc
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|bprm.envc
op_assign
id|count
c_func
(paren
id|envp
)paren
)paren
OL
l_int|0
)paren
(brace
id|dput
c_func
(paren
id|dentry
)paren
suffix:semicolon
r_return
id|bprm.envc
suffix:semicolon
)brace
id|retval
op_assign
id|prepare_binprm
c_func
(paren
op_amp
id|bprm
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
(brace
id|bprm.p
op_assign
id|copy_strings
c_func
(paren
l_int|1
comma
op_amp
id|bprm.filename
comma
id|bprm.page
comma
id|bprm.p
comma
l_int|2
)paren
suffix:semicolon
id|bprm.exec
op_assign
id|bprm.p
suffix:semicolon
id|bprm.p
op_assign
id|copy_strings
c_func
(paren
id|bprm.envc
comma
id|envp
comma
id|bprm.page
comma
id|bprm.p
comma
l_int|0
)paren
suffix:semicolon
id|bprm.p
op_assign
id|copy_strings
c_func
(paren
id|bprm.argc
comma
id|argv
comma
id|bprm.page
comma
id|bprm.p
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bprm.p
)paren
id|retval
op_assign
op_minus
id|E2BIG
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
id|retval
op_assign
id|search_binary_handler
c_func
(paren
op_amp
id|bprm
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ge
l_int|0
)paren
multiline_comment|/* execve success */
r_return
id|retval
suffix:semicolon
multiline_comment|/* Something went wrong, return the inode and free the argument pages*/
r_if
c_cond
(paren
id|bprm.dentry
)paren
id|dput
c_func
(paren
id|bprm.dentry
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
id|MAX_ARG_PAGES
suffix:semicolon
id|i
op_increment
)paren
id|free_page
c_func
(paren
id|bprm.page
(braket
id|i
)braket
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
eof
