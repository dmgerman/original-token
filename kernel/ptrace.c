multiline_comment|/*&n; * linux/kernel/ptrace.c&n; *&n; * (C) Copyright 1999 Linus Torvalds&n; *&n; * Common interfaces for &quot;ptrace()&quot; which we do not want&n; * to continually duplicate across every architecture.&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/highmem.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Access another process&squot; address space, one page at a time.&n; */
DECL|function|access_one_page
r_static
r_int
id|access_one_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
(brace
id|pgd_t
op_star
id|pgdir
suffix:semicolon
id|pmd_t
op_star
id|pgmiddle
suffix:semicolon
id|pte_t
op_star
id|pgtable
suffix:semicolon
r_char
op_star
id|maddr
suffix:semicolon
r_struct
id|page
op_star
id|page
suffix:semicolon
id|repeat
suffix:colon
id|pgdir
op_assign
id|pgd_offset
c_func
(paren
id|vma-&gt;vm_mm
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
id|pgdir
)paren
)paren
r_goto
id|fault_in_page
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgdir
)paren
)paren
r_goto
id|bad_pgd
suffix:semicolon
id|pgmiddle
op_assign
id|pmd_offset
c_func
(paren
id|pgdir
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
id|pgmiddle
)paren
)paren
r_goto
id|fault_in_page
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pgmiddle
)paren
)paren
r_goto
id|bad_pmd
suffix:semicolon
id|pgtable
op_assign
id|pte_offset
c_func
(paren
id|pgmiddle
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
op_star
id|pgtable
)paren
)paren
r_goto
id|fault_in_page
suffix:semicolon
r_if
c_cond
(paren
id|write
op_logical_and
(paren
op_logical_neg
id|pte_write
c_func
(paren
op_star
id|pgtable
)paren
op_logical_or
op_logical_neg
id|pte_dirty
c_func
(paren
op_star
id|pgtable
)paren
)paren
)paren
r_goto
id|fault_in_page
suffix:semicolon
id|page
op_assign
id|pte_page
c_func
(paren
op_star
id|pgtable
)paren
suffix:semicolon
multiline_comment|/* ZERO_PAGE is special: reads from it are ok even though it&squot;s marked reserved */
r_if
c_cond
(paren
id|page
op_ne
id|ZERO_PAGE
c_func
(paren
id|addr
)paren
op_logical_or
id|write
)paren
(brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|VALID_PAGE
c_func
(paren
id|page
)paren
)paren
op_logical_or
id|PageReserved
c_func
(paren
id|page
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
id|flush_cache_page
c_func
(paren
id|vma
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|write
)paren
(brace
id|maddr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|maddr
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
comma
id|buf
comma
id|len
)paren
suffix:semicolon
id|flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
id|flush_icache_page
c_func
(paren
id|vma
comma
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_else
(brace
id|maddr
op_assign
id|kmap
c_func
(paren
id|page
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
id|maddr
op_plus
(paren
id|addr
op_amp
op_complement
id|PAGE_MASK
)paren
comma
id|len
)paren
suffix:semicolon
id|flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
id|kunmap
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
r_return
id|len
suffix:semicolon
id|fault_in_page
suffix:colon
multiline_comment|/* -1: out of memory. 0 - unmapped page */
r_if
c_cond
(paren
id|handle_mm_fault
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
comma
id|write
)paren
OG
l_int|0
)paren
r_goto
id|repeat
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_pgd
suffix:colon
id|pgd_ERROR
c_func
(paren
op_star
id|pgdir
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|bad_pmd
suffix:colon
id|pmd_ERROR
c_func
(paren
op_star
id|pgmiddle
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|access_mm
r_static
r_int
id|access_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
comma
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
(brace
r_int
id|copied
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
id|offset
op_assign
id|addr
op_amp
op_complement
id|PAGE_MASK
suffix:semicolon
r_int
id|this_len
op_assign
id|PAGE_SIZE
op_minus
id|offset
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|this_len
OG
id|len
)paren
id|this_len
op_assign
id|len
suffix:semicolon
id|retval
op_assign
id|access_one_page
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
comma
id|buf
comma
id|this_len
comma
id|write
)paren
suffix:semicolon
id|copied
op_add_assign
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|retval
op_ne
id|this_len
)paren
r_break
suffix:semicolon
id|len
op_sub_assign
id|retval
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
r_break
suffix:semicolon
id|addr
op_add_assign
id|retval
suffix:semicolon
id|buf
op_add_assign
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|addr
OL
id|vma-&gt;vm_end
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|vma-&gt;vm_next
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|vma-&gt;vm_next-&gt;vm_start
op_ne
id|vma-&gt;vm_end
)paren
r_break
suffix:semicolon
id|vma
op_assign
id|vma-&gt;vm_next
suffix:semicolon
)brace
r_return
id|copied
suffix:semicolon
)brace
DECL|function|access_process_vm
r_int
id|access_process_vm
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
r_void
op_star
id|buf
comma
r_int
id|len
comma
r_int
id|write
)paren
(brace
r_int
id|copied
suffix:semicolon
r_struct
id|mm_struct
op_star
id|mm
suffix:semicolon
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
multiline_comment|/* Worry about races with exit() */
id|task_lock
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|mm
op_assign
id|tsk-&gt;mm
suffix:semicolon
r_if
c_cond
(paren
id|mm
)paren
id|atomic_inc
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
suffix:semicolon
id|task_unlock
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mm
)paren
r_return
l_int|0
suffix:semicolon
id|down
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|vma
op_assign
id|find_extend_vma
c_func
(paren
id|mm
comma
id|addr
)paren
suffix:semicolon
id|copied
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|vma
)paren
id|copied
op_assign
id|access_mm
c_func
(paren
id|mm
comma
id|vma
comma
id|addr
comma
id|buf
comma
id|len
comma
id|write
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|mm-&gt;mmap_sem
)paren
suffix:semicolon
id|mmput
c_func
(paren
id|mm
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
)brace
DECL|function|ptrace_readdata
r_int
id|ptrace_readdata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|this_len
comma
id|retval
suffix:semicolon
id|this_len
op_assign
(paren
id|len
OG
r_sizeof
(paren
id|buf
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|buf
)paren
suffix:colon
id|len
suffix:semicolon
id|retval
op_assign
id|access_process_vm
c_func
(paren
id|tsk
comma
id|src
comma
id|buf
comma
id|this_len
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
id|copied
)paren
r_break
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|dst
comma
id|buf
comma
id|retval
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|copied
op_add_assign
id|retval
suffix:semicolon
id|src
op_add_assign
id|retval
suffix:semicolon
id|dst
op_add_assign
id|retval
suffix:semicolon
id|len
op_sub_assign
id|retval
suffix:semicolon
)brace
r_return
id|copied
suffix:semicolon
)brace
DECL|function|ptrace_writedata
r_int
id|ptrace_writedata
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_char
op_star
id|src
comma
r_int
r_int
id|dst
comma
r_int
id|len
)paren
(brace
r_int
id|copied
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|len
OG
l_int|0
)paren
(brace
r_char
id|buf
(braket
l_int|128
)braket
suffix:semicolon
r_int
id|this_len
comma
id|retval
suffix:semicolon
id|this_len
op_assign
(paren
id|len
OG
r_sizeof
(paren
id|buf
)paren
)paren
ques
c_cond
r_sizeof
(paren
id|buf
)paren
suffix:colon
id|len
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|src
comma
id|this_len
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|retval
op_assign
id|access_process_vm
c_func
(paren
id|tsk
comma
id|dst
comma
id|buf
comma
id|this_len
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|retval
)paren
(brace
r_if
c_cond
(paren
id|copied
)paren
r_break
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|copied
op_add_assign
id|retval
suffix:semicolon
id|src
op_add_assign
id|retval
suffix:semicolon
id|dst
op_add_assign
id|retval
suffix:semicolon
id|len
op_sub_assign
id|retval
suffix:semicolon
)brace
r_return
id|copied
suffix:semicolon
)brace
eof
