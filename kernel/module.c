macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;linux/mm.h&gt;&t;&t;/* defines GFP_KERNEL */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
DECL|variable|module_list
r_struct
id|module
op_star
id|module_list
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|freeing_modules
r_int
id|freeing_modules
suffix:semicolon
multiline_comment|/* true if some modules are marked for deletion */
r_struct
id|module
op_star
id|find_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
suffix:semicolon
r_int
id|get_mod_name
c_func
(paren
r_char
op_star
id|user_name
comma
r_char
op_star
id|buf
)paren
suffix:semicolon
r_int
id|free_modules
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Allocate space for a module.&n; */
id|asmlinkage
r_int
DECL|function|sys_create_module
id|sys_create_module
c_func
(paren
r_char
op_star
id|module_name
comma
r_int
r_int
id|size
)paren
(brace
r_int
id|npages
suffix:semicolon
r_void
op_star
id|addr
suffix:semicolon
r_int
id|len
suffix:semicolon
r_char
id|name
(braket
id|MOD_MAX_NAME
)braket
suffix:semicolon
r_char
op_star
id|savename
suffix:semicolon
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_int
id|error
suffix:semicolon
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
r_if
c_cond
(paren
id|module_name
op_eq
l_int|NULL
op_logical_or
id|size
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_mod_name
c_func
(paren
id|module_name
comma
id|name
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
id|find_module
c_func
(paren
id|name
)paren
op_ne
l_int|NULL
)paren
(brace
r_return
op_minus
id|EEXIST
suffix:semicolon
)brace
id|len
op_assign
id|strlen
c_func
(paren
id|name
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|savename
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|len
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memcpy
c_func
(paren
id|savename
comma
id|name
comma
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mp
op_assign
(paren
r_struct
id|module
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
op_star
id|mp
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|savename
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|npages
op_assign
(paren
id|size
op_plus
r_sizeof
(paren
r_int
)paren
op_plus
l_int|4095
)paren
op_div
l_int|4096
suffix:semicolon
r_if
c_cond
(paren
(paren
id|addr
op_assign
id|vmalloc
c_func
(paren
id|npages
op_star
l_int|4096
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|kfree_s
c_func
(paren
id|mp
comma
r_sizeof
op_star
id|mp
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|savename
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|mp-&gt;name
op_assign
id|savename
suffix:semicolon
id|mp-&gt;size
op_assign
id|npages
suffix:semicolon
id|mp-&gt;addr
op_assign
id|addr
suffix:semicolon
id|mp-&gt;state
op_assign
id|MOD_UNINITIALIZED
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
id|addr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* set use count to zero */
id|mp-&gt;cleanup
op_assign
l_int|NULL
suffix:semicolon
id|mp-&gt;next
op_assign
id|module_list
suffix:semicolon
id|module_list
op_assign
id|mp
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;module `%s&squot; (%lu pages @ 0x%08lx) created&bslash;n&quot;
comma
id|mp-&gt;name
comma
(paren
r_int
r_int
)paren
id|mp-&gt;size
comma
(paren
r_int
r_int
)paren
id|mp-&gt;addr
)paren
suffix:semicolon
r_return
(paren
r_int
)paren
id|addr
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize a module.&n; */
id|asmlinkage
r_int
DECL|function|sys_init_module
id|sys_init_module
c_func
(paren
r_char
op_star
id|module_name
comma
r_char
op_star
id|code
comma
r_int
id|codesize
comma
r_struct
id|mod_routines
op_star
id|routines
)paren
(brace
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_char
id|name
(braket
id|MOD_MAX_NAME
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
r_struct
id|mod_routines
id|rt
suffix:semicolon
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
multiline_comment|/*&n;&t; * First reclaim any memory from dead modules that where not&n;&t; * freed when deleted. Should I think be done by timers when&n;&t; * the module was deleted - Jon.&n;&t; */
id|free_modules
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_mod_name
c_func
(paren
id|module_name
comma
id|name
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|error
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;initializing module `%s&squot;, %d (0x%x) bytes&bslash;n&quot;
comma
id|name
comma
id|codesize
comma
id|codesize
)paren
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|rt
comma
id|routines
comma
r_sizeof
id|rt
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mp
op_assign
id|find_module
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
(paren
id|codesize
op_plus
r_sizeof
(paren
r_int
)paren
op_plus
l_int|4095
)paren
op_div
l_int|4096
OG
id|mp-&gt;size
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
(paren
r_char
op_star
)paren
id|mp-&gt;addr
op_plus
r_sizeof
(paren
r_int
)paren
comma
id|code
comma
id|codesize
)paren
suffix:semicolon
id|memset
c_func
(paren
(paren
r_char
op_star
)paren
id|mp-&gt;addr
op_plus
r_sizeof
(paren
r_int
)paren
op_plus
id|codesize
comma
l_int|0
comma
id|mp-&gt;size
op_star
l_int|4096
op_minus
(paren
id|codesize
op_plus
r_sizeof
(paren
r_int
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;  init entry @ 0x%08lx, cleanup entry @ 0x%08lx&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|rt.init
comma
(paren
r_int
r_int
)paren
id|rt.cleanup
)paren
suffix:semicolon
id|mp-&gt;cleanup
op_assign
id|rt.cleanup
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|rt.init
)paren
(paren
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|mp-&gt;state
op_assign
id|MOD_RUNNING
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_delete_module
id|sys_delete_module
c_func
(paren
r_char
op_star
id|module_name
)paren
(brace
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_char
id|name
(braket
id|MOD_MAX_NAME
)braket
suffix:semicolon
r_int
id|error
suffix:semicolon
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
r_if
c_cond
(paren
id|module_name
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|error
op_assign
id|get_mod_name
c_func
(paren
id|module_name
comma
id|name
)paren
)paren
op_ne
l_int|0
)paren
r_return
id|error
suffix:semicolon
r_if
c_cond
(paren
(paren
id|mp
op_assign
id|find_module
c_func
(paren
id|name
)paren
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOENT
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;state
op_eq
id|MOD_RUNNING
)paren
(paren
op_star
id|mp-&gt;cleanup
)paren
(paren
)paren
suffix:semicolon
id|mp-&gt;state
op_assign
id|MOD_DELETED
suffix:semicolon
)brace
id|free_modules
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy the kernel symbol table to user space.  If the argument is null,&n; * just return the size of the table.&n; */
id|asmlinkage
r_int
DECL|function|sys_get_kernel_syms
id|sys_get_kernel_syms
c_func
(paren
r_struct
id|kernel_sym
op_star
id|table
)paren
(brace
r_struct
id|symbol
(brace
r_int
r_int
id|addr
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_int
id|symbol_table_size
suffix:semicolon
r_extern
r_struct
id|symbol
id|symbol_table
(braket
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|symbol
op_star
id|from
suffix:semicolon
r_struct
id|kernel_sym
op_star
id|to
suffix:semicolon
r_struct
id|kernel_sym
id|sym
suffix:semicolon
r_if
c_cond
(paren
id|table
op_ne
l_int|NULL
)paren
(brace
id|from
op_assign
id|symbol_table
suffix:semicolon
id|to
op_assign
id|table
suffix:semicolon
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|to
comma
id|symbol_table_size
op_star
r_sizeof
op_star
id|table
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
)paren
r_return
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|symbol_table_size
suffix:semicolon
op_decrement
id|i
op_ge
l_int|0
suffix:semicolon
)paren
(brace
id|sym.value
op_assign
id|from-&gt;addr
suffix:semicolon
id|strncpy
c_func
(paren
id|sym.name
comma
id|from-&gt;name
comma
r_sizeof
id|sym.name
)paren
suffix:semicolon
id|memcpy_tofs
c_func
(paren
id|to
comma
op_amp
id|sym
comma
r_sizeof
id|sym
)paren
suffix:semicolon
id|from
op_increment
comma
id|to
op_increment
suffix:semicolon
)brace
)brace
r_return
id|symbol_table_size
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy the name of a module from user space.&n; */
r_int
DECL|function|get_mod_name
id|get_mod_name
c_func
(paren
r_char
op_star
id|user_name
comma
r_char
op_star
id|buf
)paren
(brace
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|buf
(braket
id|i
)braket
op_assign
id|get_fs_byte
c_func
(paren
id|user_name
op_plus
id|i
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
op_increment
id|i
op_ge
id|MOD_MAX_NAME
)paren
r_return
op_minus
id|E2BIG
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Look for a module by name, ignoring modules marked for deletion.&n; */
r_struct
id|module
op_star
DECL|function|find_module
id|find_module
c_func
(paren
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_for
c_loop
(paren
id|mp
op_assign
id|module_list
suffix:semicolon
id|mp
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;state
op_eq
id|MOD_DELETED
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|mp-&gt;name
comma
id|name
)paren
)paren
r_break
suffix:semicolon
)brace
r_return
id|mp
suffix:semicolon
)brace
multiline_comment|/*&n; * Try to free modules which have been marked for deletion.  Returns nonzero&n; * if a module was actually freed.&n; */
r_int
DECL|function|free_modules
id|free_modules
c_func
(paren
r_void
)paren
(brace
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_struct
id|module
op_star
op_star
id|mpp
suffix:semicolon
r_int
id|did_deletion
suffix:semicolon
id|did_deletion
op_assign
l_int|0
suffix:semicolon
id|freeing_modules
op_assign
l_int|0
suffix:semicolon
id|mpp
op_assign
op_amp
id|module_list
suffix:semicolon
r_while
c_loop
(paren
(paren
id|mp
op_assign
op_star
id|mpp
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
id|mp-&gt;state
op_ne
id|MOD_DELETED
)paren
(brace
id|mpp
op_assign
op_amp
id|mp-&gt;next
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|GET_USE_COUNT
c_func
(paren
id|mp
)paren
op_ne
l_int|0
)paren
(brace
id|freeing_modules
op_assign
l_int|1
suffix:semicolon
id|mpp
op_assign
op_amp
id|mp-&gt;next
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* delete it */
op_star
id|mpp
op_assign
id|mp-&gt;next
suffix:semicolon
id|vfree
c_func
(paren
id|mp-&gt;addr
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mp-&gt;name
)paren
suffix:semicolon
id|kfree_s
c_func
(paren
id|mp
comma
r_sizeof
op_star
id|mp
)paren
suffix:semicolon
id|did_deletion
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_return
id|did_deletion
suffix:semicolon
)brace
multiline_comment|/*&n; * Called by the /proc file system to return a current list of modules.&n; */
DECL|function|get_module_list
r_int
id|get_module_list
c_func
(paren
r_char
op_star
id|buf
)paren
(brace
r_char
op_star
id|p
suffix:semicolon
r_char
op_star
id|q
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|module
op_star
id|mp
suffix:semicolon
r_char
id|size
(braket
l_int|32
)braket
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
r_for
c_loop
(paren
id|mp
op_assign
id|module_list
suffix:semicolon
id|mp
suffix:semicolon
id|mp
op_assign
id|mp-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|p
op_minus
id|buf
OG
l_int|4096
op_minus
l_int|100
)paren
r_break
suffix:semicolon
multiline_comment|/* avoid overflowing buffer */
id|q
op_assign
id|mp-&gt;name
suffix:semicolon
id|i
op_assign
l_int|20
suffix:semicolon
r_while
c_loop
(paren
op_star
id|q
)paren
(brace
op_star
id|p
op_increment
op_assign
op_star
id|q
op_increment
suffix:semicolon
id|i
op_decrement
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|size
comma
l_string|&quot;%d&quot;
comma
id|mp-&gt;size
)paren
suffix:semicolon
id|i
op_sub_assign
id|strlen
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_le
l_int|0
)paren
id|i
op_assign
l_int|1
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|q
op_assign
id|size
suffix:semicolon
r_while
c_loop
(paren
op_star
id|q
)paren
op_star
id|p
op_increment
op_assign
op_star
id|q
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|mp-&gt;state
op_eq
id|MOD_UNINITIALIZED
)paren
id|q
op_assign
l_string|&quot;  (uninitialized)&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mp-&gt;state
op_eq
id|MOD_RUNNING
)paren
id|q
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_else
r_if
c_cond
(paren
id|mp-&gt;state
op_eq
id|MOD_DELETED
)paren
id|q
op_assign
l_string|&quot;  (deleted)&quot;
suffix:semicolon
r_else
id|q
op_assign
l_string|&quot;  (bad state)&quot;
suffix:semicolon
r_while
c_loop
(paren
op_star
id|q
)paren
op_star
id|p
op_increment
op_assign
op_star
id|q
op_increment
suffix:semicolon
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;n&squot;
suffix:semicolon
)brace
r_return
id|p
op_minus
id|buf
suffix:semicolon
)brace
eof
