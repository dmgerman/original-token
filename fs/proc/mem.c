multiline_comment|/*&n; *  linux/fs/proc/mem.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/*&n; * mem_write isn&squot;t really a good idea right now. It needs&n; * to check a lot more: if the process we try to write to &n; * dies in the middle right now, mem_write will overwrite&n; * kernel memory.. This disables it altogether.&n; */
DECL|macro|mem_write
mdefine_line|#define mem_write NULL
DECL|function|check_range
r_static
r_int
id|check_range
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|addr
comma
r_int
id|count
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_start
OG
id|addr
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_READ
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_while
c_loop
(paren
(paren
id|retval
op_assign
id|vma-&gt;vm_end
op_minus
id|addr
)paren
OL
id|count
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|next
op_assign
id|vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_end
op_ne
id|next-&gt;vm_start
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|next-&gt;vm_flags
op_amp
id|VM_READ
)paren
)paren
r_break
suffix:semicolon
id|vma
op_assign
id|next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
OG
id|count
)paren
id|retval
op_assign
id|count
suffix:semicolon
r_return
id|retval
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
id|pgd_t
op_star
id|page_dir
suffix:semicolon
id|pmd_t
op_star
id|page_middle
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
r_int
id|addr
comma
id|pid
suffix:semicolon
r_char
op_star
id|tmp
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
id|pid
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|pid
op_rshift_assign
l_int|16
suffix:semicolon
id|tsk
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_logical_and
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
(brace
id|tsk
op_assign
id|task
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
id|addr
op_assign
id|file-&gt;f_pos
suffix:semicolon
id|count
op_assign
id|check_range
c_func
(paren
id|tsk
comma
id|addr
comma
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
l_int|0
)paren
r_return
id|count
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
id|page_dir
op_assign
id|pgd_offset
c_func
(paren
id|tsk-&gt;mm
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|page_dir
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|page_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad page dir entry %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|page_dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|page_dir
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|page_middle
op_assign
id|pmd_offset
c_func
(paren
id|page_dir
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|page_middle
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|page_middle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad page middle entry %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|page_middle
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|page_middle
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pte
op_assign
op_star
id|pte_offset
c_func
(paren
id|page_middle
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
r_break
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|pte_page
c_func
(paren
id|pte
)paren
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|i
op_assign
id|PAGE_SIZE
op_minus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
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
macro_line|#ifndef mem_write
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
id|pgd_t
op_star
id|page_dir
suffix:semicolon
id|pmd_t
op_star
id|page_middle
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
r_char
op_star
id|page
suffix:semicolon
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
r_int
r_int
id|addr
comma
id|pid
suffix:semicolon
r_char
op_star
id|tmp
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
id|pid
op_assign
id|inode-&gt;i_ino
suffix:semicolon
id|pid
op_rshift_assign
l_int|16
suffix:semicolon
id|tsk
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_logical_and
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
id|pid
)paren
(brace
id|tsk
op_assign
id|task
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
r_return
op_minus
id|EACCES
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
id|page_dir
op_assign
id|pgd_offset
c_func
(paren
id|tsk
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|page_dir
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|page_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad page dir entry %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|page_dir
)paren
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|page_dir
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|page_middle
op_assign
id|pmd_offset
c_func
(paren
id|page_dir
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|page_middle
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|page_middle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad page middle entry %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|page_middle
)paren
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|page_middle
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|pte
op_assign
op_star
id|pte_offset
c_func
(paren
id|page_middle
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_write
c_func
(paren
id|pte
)paren
)paren
r_break
suffix:semicolon
id|page
op_assign
(paren
r_char
op_star
)paren
id|pte_page
c_func
(paren
id|pte
)paren
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
suffix:semicolon
id|i
op_assign
id|PAGE_SIZE
op_minus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
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
macro_line|#endif
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
)brace
multiline_comment|/*&n; * This isn&squot;t really reliable by any means..&n; */
DECL|function|mem_mmap
r_int
id|mem_mmap
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
r_struct
id|task_struct
op_star
id|tsk
suffix:semicolon
id|pgd_t
op_star
id|src_dir
comma
op_star
id|dest_dir
suffix:semicolon
id|pmd_t
op_star
id|src_middle
comma
op_star
id|dest_middle
suffix:semicolon
id|pte_t
op_star
id|src_table
comma
op_star
id|dest_table
suffix:semicolon
r_int
r_int
id|stmp
comma
id|dtmp
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|src_vma
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Get the source&squot;s task information */
id|tsk
op_assign
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|NR_TASKS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|task
(braket
id|i
)braket
op_logical_and
id|task
(braket
id|i
)braket
op_member_access_from_pointer
id|pid
op_eq
(paren
id|inode-&gt;i_ino
op_rshift
l_int|16
)paren
)paren
(brace
id|tsk
op_assign
id|task
(braket
id|i
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* Ensure that we have a valid source area.  (Has to be mmap&squot;ed and&n;&t; have valid page information.)  We can&squot;t map shared memory at the&n;&t; moment because working out the vm_area_struct &amp; nattach stuff isn&squot;t&n;&t; worth it. */
id|src_vma
op_assign
id|tsk-&gt;mm-&gt;mmap
suffix:semicolon
id|stmp
op_assign
id|vma-&gt;vm_offset
suffix:semicolon
r_while
c_loop
(paren
id|stmp
OL
id|vma-&gt;vm_offset
op_plus
(paren
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
)paren
)paren
(brace
r_while
c_loop
(paren
id|src_vma
op_logical_and
id|stmp
OG
id|src_vma-&gt;vm_end
)paren
id|src_vma
op_assign
id|src_vma-&gt;vm_next
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|src_vma
op_logical_or
(paren
id|src_vma-&gt;vm_flags
op_amp
id|VM_SHM
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|src_dir
op_assign
id|pgd_offset
c_func
(paren
id|tsk-&gt;mm
comma
id|stmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|src_dir
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|src_dir
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad source page dir entry %08lx&bslash;n&quot;
comma
id|pgd_val
c_func
(paren
op_star
id|src_dir
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|src_middle
op_assign
id|pmd_offset
c_func
(paren
id|src_dir
comma
id|stmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|src_middle
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|src_middle
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Bad source page middle entry %08lx&bslash;n&quot;
comma
id|pmd_val
c_func
(paren
op_star
id|src_middle
)paren
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|src_table
op_assign
id|pte_offset
c_func
(paren
id|src_middle
comma
id|stmp
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
op_star
id|src_table
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|stmp
OL
id|src_vma-&gt;vm_start
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|src_vma-&gt;vm_flags
op_amp
id|VM_GROWSDOWN
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|src_vma-&gt;vm_end
op_minus
id|stmp
OG
id|current-&gt;rlim
(braket
id|RLIMIT_STACK
)braket
dot
id|rlim_cur
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|stmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|src_vma
op_assign
id|tsk-&gt;mm-&gt;mmap
suffix:semicolon
id|stmp
op_assign
id|vma-&gt;vm_offset
suffix:semicolon
id|dtmp
op_assign
id|vma-&gt;vm_start
suffix:semicolon
r_while
c_loop
(paren
id|dtmp
OL
id|vma-&gt;vm_end
)paren
(brace
r_while
c_loop
(paren
id|src_vma
op_logical_and
id|stmp
OG
id|src_vma-&gt;vm_end
)paren
id|src_vma
op_assign
id|src_vma-&gt;vm_next
suffix:semicolon
id|src_dir
op_assign
id|pgd_offset
c_func
(paren
id|tsk-&gt;mm
comma
id|stmp
)paren
suffix:semicolon
id|src_middle
op_assign
id|pmd_offset
c_func
(paren
id|src_dir
comma
id|stmp
)paren
suffix:semicolon
id|src_table
op_assign
id|pte_offset
c_func
(paren
id|src_middle
comma
id|stmp
)paren
suffix:semicolon
id|dest_dir
op_assign
id|pgd_offset
c_func
(paren
id|current-&gt;mm
comma
id|dtmp
)paren
suffix:semicolon
id|dest_middle
op_assign
id|pmd_alloc
c_func
(paren
id|dest_dir
comma
id|dtmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_middle
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|dest_table
op_assign
id|pte_alloc
c_func
(paren
id|dest_middle
comma
id|dtmp
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_table
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
op_star
id|src_table
)paren
)paren
id|do_no_page
c_func
(paren
id|tsk
comma
id|src_vma
comma
id|stmp
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|vma-&gt;vm_flags
op_amp
id|VM_WRITE
)paren
op_logical_and
op_logical_neg
id|pte_write
c_func
(paren
op_star
id|src_table
)paren
)paren
id|do_wp_page
c_func
(paren
id|tsk
comma
id|src_vma
comma
id|stmp
comma
l_int|1
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|src_table
comma
id|pte_mkdirty
c_func
(paren
op_star
id|src_table
)paren
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|dest_table
comma
op_star
id|src_table
)paren
suffix:semicolon
id|mem_map
(braket
id|MAP_NR
c_func
(paren
id|pte_page
c_func
(paren
op_star
id|src_table
)paren
)paren
)braket
op_increment
suffix:semicolon
id|stmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|dtmp
op_add_assign
id|PAGE_SIZE
suffix:semicolon
)brace
id|invalidate
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|proc_mem_operations
r_static
r_struct
id|file_operations
id|proc_mem_operations
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
id|mem_mmap
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
DECL|variable|proc_mem_inode_operations
r_struct
id|inode_operations
id|proc_mem_inode_operations
op_assign
(brace
op_amp
id|proc_mem_operations
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
multiline_comment|/* bmap */
l_int|NULL
comma
multiline_comment|/* truncate */
l_int|NULL
multiline_comment|/* permission */
)brace
suffix:semicolon
eof
