multiline_comment|/*&n; *&t;linux/kernel/resource.c&n; *&n; * Copyright (C) 1999&t;Linus Torvalds&n; * Copyright (C) 1999&t;Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; * Arbitrary resource management.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|ioport_resource
r_struct
id|resource
id|ioport_resource
op_assign
(brace
l_string|&quot;PCI IO&quot;
comma
l_int|0x0000
comma
id|IO_SPACE_LIMIT
comma
id|IORESOURCE_IO
)brace
suffix:semicolon
DECL|variable|iomem_resource
r_struct
id|resource
id|iomem_resource
op_assign
(brace
l_string|&quot;PCI mem&quot;
comma
l_int|0x00000000
comma
l_int|0xffffffff
comma
id|IORESOURCE_MEM
)brace
suffix:semicolon
DECL|variable|resource_lock
r_static
id|rwlock_t
id|resource_lock
op_assign
id|RW_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * This generates reports for /proc/ioports and /proc/iomem&n; */
DECL|function|do_resource_list
r_static
r_char
op_star
id|do_resource_list
c_func
(paren
r_struct
id|resource
op_star
id|entry
comma
r_const
r_char
op_star
id|fmt
comma
r_int
id|offset
comma
r_char
op_star
id|buf
comma
r_char
op_star
id|end
)paren
(brace
r_if
c_cond
(paren
id|offset
OL
l_int|0
)paren
id|offset
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|entry
)paren
(brace
r_const
r_char
op_star
id|name
op_assign
id|entry-&gt;name
suffix:semicolon
r_int
r_int
id|from
comma
id|to
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|end
op_minus
id|buf
)paren
OL
l_int|80
)paren
r_return
id|buf
suffix:semicolon
id|from
op_assign
id|entry-&gt;start
suffix:semicolon
id|to
op_assign
id|entry-&gt;end
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name
)paren
id|name
op_assign
l_string|&quot;&lt;BAD&gt;&quot;
suffix:semicolon
id|buf
op_add_assign
id|sprintf
c_func
(paren
id|buf
comma
id|fmt
op_plus
id|offset
comma
id|from
comma
id|to
comma
id|name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|entry-&gt;child
)paren
id|buf
op_assign
id|do_resource_list
c_func
(paren
id|entry-&gt;child
comma
id|fmt
comma
id|offset
op_minus
l_int|2
comma
id|buf
comma
id|end
)paren
suffix:semicolon
id|entry
op_assign
id|entry-&gt;sibling
suffix:semicolon
)brace
r_return
id|buf
suffix:semicolon
)brace
DECL|function|get_resource_list
r_int
id|get_resource_list
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_char
op_star
id|buf
comma
r_int
id|size
)paren
(brace
r_char
op_star
id|fmt
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|fmt
op_assign
l_string|&quot;        %08lx-%08lx : %s&bslash;n&quot;
suffix:semicolon
r_if
c_cond
(paren
id|root-&gt;end
OL
l_int|0x10000
)paren
id|fmt
op_assign
l_string|&quot;        %04lx-%04lx : %s&bslash;n&quot;
suffix:semicolon
id|read_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|retval
op_assign
id|do_resource_list
c_func
(paren
id|root-&gt;child
comma
id|fmt
comma
l_int|8
comma
id|buf
comma
id|buf
op_plus
id|size
)paren
op_minus
id|buf
suffix:semicolon
id|read_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/* Return the conflict entry if you can&squot;t request it */
DECL|function|__request_resource
r_static
r_struct
id|resource
op_star
id|__request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_int
r_int
id|start
op_assign
r_new
op_member_access_from_pointer
id|start
suffix:semicolon
r_int
r_int
id|end
op_assign
r_new
op_member_access_from_pointer
id|end
suffix:semicolon
r_struct
id|resource
op_star
id|tmp
comma
op_star
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
id|root
suffix:semicolon
r_if
c_cond
(paren
id|start
OL
id|root-&gt;start
)paren
r_return
id|root
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|root-&gt;end
)paren
r_return
id|root
suffix:semicolon
id|p
op_assign
op_amp
id|root-&gt;child
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
op_logical_or
id|tmp-&gt;start
OG
id|end
)paren
(brace
r_new
op_member_access_from_pointer
id|sibling
op_assign
id|tmp
suffix:semicolon
op_star
id|p
op_assign
r_new
suffix:semicolon
r_new
op_member_access_from_pointer
id|parent
op_assign
id|root
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|tmp-&gt;sibling
suffix:semicolon
r_if
c_cond
(paren
id|tmp-&gt;end
OL
id|start
)paren
r_continue
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
)brace
DECL|function|__release_resource
r_static
r_int
id|__release_resource
c_func
(paren
r_struct
id|resource
op_star
id|old
)paren
(brace
r_struct
id|resource
op_star
id|tmp
comma
op_star
op_star
id|p
suffix:semicolon
id|p
op_assign
op_amp
id|old-&gt;parent-&gt;child
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|tmp
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_eq
id|old
)paren
(brace
op_star
id|p
op_assign
id|tmp-&gt;sibling
suffix:semicolon
id|old-&gt;parent
op_assign
l_int|NULL
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|tmp-&gt;sibling
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|request_resource
r_int
id|request_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
)paren
(brace
r_struct
id|resource
op_star
id|conflict
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|root
comma
r_new
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|conflict
ques
c_cond
op_minus
id|EBUSY
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|release_resource
r_int
id|release_resource
c_func
(paren
r_struct
id|resource
op_star
id|old
)paren
(brace
r_int
id|retval
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|retval
op_assign
id|__release_resource
c_func
(paren
id|old
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|check_resource
r_int
id|check_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_int
r_int
id|start
comma
r_int
r_int
id|len
)paren
(brace
r_struct
id|resource
op_star
id|conflict
comma
id|tmp
suffix:semicolon
id|tmp.start
op_assign
id|start
suffix:semicolon
id|tmp.end
op_assign
id|start
op_plus
id|len
op_minus
l_int|1
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|root
comma
op_amp
id|tmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conflict
)paren
id|__release_resource
c_func
(paren
op_amp
id|tmp
)paren
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|conflict
ques
c_cond
op_minus
id|EBUSY
suffix:colon
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Find empty slot in the resource tree given range and alignment.&n; */
DECL|function|find_resource
r_static
r_int
id|find_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
(brace
r_struct
id|resource
op_star
id|this
op_assign
id|root-&gt;child
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
id|root-&gt;start
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|this
)paren
r_new
op_member_access_from_pointer
id|end
op_assign
id|this-&gt;start
suffix:semicolon
r_else
r_new
op_member_access_from_pointer
id|end
op_assign
id|root-&gt;end
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|start
OL
id|min
)paren
r_new
op_member_access_from_pointer
id|start
op_assign
id|min
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|end
OG
id|max
)paren
r_new
op_member_access_from_pointer
id|end
op_assign
id|max
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
(paren
r_new
op_member_access_from_pointer
id|start
op_plus
id|align
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|align
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alignf
)paren
id|alignf
c_func
(paren
id|alignf_data
comma
r_new
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|start
OL
r_new
op_member_access_from_pointer
id|end
op_logical_and
r_new
op_member_access_from_pointer
id|end
op_minus
r_new
op_member_access_from_pointer
id|start
op_plus
l_int|1
op_ge
id|size
)paren
(brace
r_new
op_member_access_from_pointer
id|end
op_assign
r_new
op_member_access_from_pointer
id|start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|this
)paren
r_break
suffix:semicolon
r_new
op_member_access_from_pointer
id|start
op_assign
id|this-&gt;end
op_plus
l_int|1
suffix:semicolon
id|this
op_assign
id|this-&gt;sibling
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate empty slot in the resource tree given range and alignment.&n; */
DECL|function|allocate_resource
r_int
id|allocate_resource
c_func
(paren
r_struct
id|resource
op_star
id|root
comma
r_struct
id|resource
op_star
r_new
comma
r_int
r_int
id|size
comma
r_int
r_int
id|min
comma
r_int
r_int
id|max
comma
r_int
r_int
id|align
comma
r_void
(paren
op_star
id|alignf
)paren
(paren
r_void
op_star
comma
r_struct
id|resource
op_star
comma
r_int
r_int
)paren
comma
r_void
op_star
id|alignf_data
)paren
(brace
r_int
id|err
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
id|err
op_assign
id|find_resource
c_func
(paren
id|root
comma
r_new
comma
id|size
comma
id|min
comma
id|max
comma
id|align
comma
id|alignf
comma
id|alignf_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ge
l_int|0
op_logical_and
id|__request_resource
c_func
(paren
id|root
comma
r_new
)paren
)paren
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * This is compatibility stuff for IO resources.&n; *&n; * Note how this, unlike the above, knows about&n; * the IO flag meanings (busy etc).&n; *&n; * Request-region creates a new busy region.&n; *&n; * Check-region returns non-zero if the area is already busy&n; *&n; * Release-region releases a matching busy region.&n; */
DECL|function|__request_region
r_struct
id|resource
op_star
id|__request_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
comma
r_const
r_char
op_star
id|name
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|res
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res
)paren
(brace
id|memset
c_func
(paren
id|res
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|res
)paren
)paren
suffix:semicolon
id|res-&gt;name
op_assign
id|name
suffix:semicolon
id|res-&gt;start
op_assign
id|start
suffix:semicolon
id|res-&gt;end
op_assign
id|start
op_plus
id|n
op_minus
l_int|1
suffix:semicolon
id|res-&gt;flags
op_assign
id|IORESOURCE_BUSY
suffix:semicolon
id|write_lock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|resource
op_star
id|conflict
suffix:semicolon
id|conflict
op_assign
id|__request_resource
c_func
(paren
id|parent
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|conflict
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|conflict
op_ne
id|parent
)paren
(brace
id|parent
op_assign
id|conflict
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|conflict-&gt;flags
op_amp
id|IORESOURCE_BUSY
)paren
)paren
r_continue
suffix:semicolon
)brace
multiline_comment|/* Uhhuh, that didn&squot;t work out.. */
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
id|res
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|write_unlock
c_func
(paren
op_amp
id|resource_lock
)paren
suffix:semicolon
)brace
r_return
id|res
suffix:semicolon
)brace
DECL|function|__check_region
r_int
id|__check_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|resource
op_star
id|res
suffix:semicolon
id|res
op_assign
id|__request_region
c_func
(paren
id|parent
comma
id|start
comma
id|n
comma
l_string|&quot;check-region&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|release_resource
c_func
(paren
id|res
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__release_region
r_void
id|__release_region
c_func
(paren
r_struct
id|resource
op_star
id|parent
comma
r_int
r_int
id|start
comma
r_int
r_int
id|n
)paren
(brace
r_struct
id|resource
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
id|p
op_assign
op_amp
id|parent-&gt;child
suffix:semicolon
id|end
op_assign
id|start
op_plus
id|n
op_minus
l_int|1
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;start
op_le
id|start
op_logical_and
id|res-&gt;end
op_ge
id|end
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_BUSY
)paren
)paren
(brace
id|p
op_assign
op_amp
id|res-&gt;child
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;start
op_ne
id|start
op_logical_or
id|res-&gt;end
op_ne
id|end
)paren
r_break
suffix:semicolon
op_star
id|p
op_assign
id|res-&gt;sibling
suffix:semicolon
id|kfree
c_func
(paren
id|res
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|p
op_assign
op_amp
id|res-&gt;sibling
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;Trying to free nonexistent resource &lt;%08lx-%08lx&gt;&bslash;n&quot;
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Called from init/main.c to reserve IO ports.&n; */
DECL|macro|MAXRESERVE
mdefine_line|#define MAXRESERVE 4
DECL|function|reserve_setup
r_static
r_int
id|__init
id|reserve_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|opt
op_assign
l_int|2
comma
id|io_start
comma
id|io_num
suffix:semicolon
r_static
r_int
id|reserved
op_assign
l_int|0
suffix:semicolon
r_static
r_struct
id|resource
id|reserve
(braket
id|MAXRESERVE
)braket
suffix:semicolon
r_while
c_loop
(paren
id|opt
op_eq
l_int|2
)paren
(brace
r_int
id|x
op_assign
id|reserved
suffix:semicolon
r_if
c_cond
(paren
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|io_start
)paren
op_ne
l_int|2
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|get_option
(paren
op_amp
id|str
comma
op_amp
id|io_num
)paren
op_eq
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|x
OL
id|MAXRESERVE
)paren
(brace
r_struct
id|resource
op_star
id|res
op_assign
id|reserve
op_plus
id|x
suffix:semicolon
id|res-&gt;name
op_assign
l_string|&quot;reserved&quot;
suffix:semicolon
id|res-&gt;start
op_assign
id|io_start
suffix:semicolon
id|res-&gt;end
op_assign
id|io_start
op_plus
id|io_num
op_minus
l_int|1
suffix:semicolon
id|res-&gt;child
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|request_resource
c_func
(paren
id|res-&gt;start
op_ge
l_int|0x10000
ques
c_cond
op_amp
id|iomem_resource
suffix:colon
op_amp
id|ioport_resource
comma
id|res
)paren
op_eq
l_int|0
)paren
id|reserved
op_assign
id|x
op_plus
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;reserve=&quot;
comma
id|reserve_setup
)paren
suffix:semicolon
eof
