multiline_comment|/*&n; * $Id: ppc_htab.c,v 1.7 1997/08/24 19:33:32 cort Exp $&n; *&n; * PowerPC hash table management proc entry.  Will show information&n; * about the current hash table and will allow changes to it.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_static
r_int
id|ppc_htab_read
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
r_int
id|nbytes
)paren
suffix:semicolon
r_static
r_int
id|ppc_htab_write
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
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
suffix:semicolon
r_static
r_int
r_int
id|ppc_htab_lseek
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
r_int
r_int
id|offset
comma
r_int
id|orig
)paren
suffix:semicolon
r_extern
id|PTE
op_star
id|Hash
comma
op_star
id|Hash_end
suffix:semicolon
r_extern
r_int
r_int
id|Hash_size
comma
id|Hash_mask
suffix:semicolon
r_extern
r_int
r_int
id|_SDR1
suffix:semicolon
DECL|variable|ppc_htab_operations
r_static
r_struct
id|file_operations
id|ppc_htab_operations
op_assign
(brace
id|ppc_htab_lseek
comma
multiline_comment|/* lseek   */
id|ppc_htab_read
comma
multiline_comment|/* read&t;   */
id|ppc_htab_write
comma
multiline_comment|/* write   */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* poll    */
l_int|NULL
comma
multiline_comment|/* ioctl   */
l_int|NULL
comma
multiline_comment|/* mmap&t;   */
l_int|NULL
comma
multiline_comment|/* no special open code&t;   */
l_int|NULL
comma
multiline_comment|/* no special release code */
l_int|NULL
multiline_comment|/* can&squot;t fsync */
)brace
suffix:semicolon
multiline_comment|/*&n; * proc files can do almost nothing..&n; */
DECL|variable|proc_ppc_htab_inode_operations
r_struct
id|inode_operations
id|proc_ppc_htab_inode_operations
op_assign
(brace
op_amp
id|ppc_htab_operations
comma
multiline_comment|/* default proc file-ops */
l_int|NULL
comma
multiline_comment|/* create&t;   */
l_int|NULL
comma
multiline_comment|/* lookup&t;   */
l_int|NULL
comma
multiline_comment|/* link&t;   */
l_int|NULL
comma
multiline_comment|/* unlink&t;   */
l_int|NULL
comma
multiline_comment|/* symlink&t;   */
l_int|NULL
comma
multiline_comment|/* mkdir&t;   */
l_int|NULL
comma
multiline_comment|/* rmdir&t;   */
l_int|NULL
comma
multiline_comment|/* mknod&t;   */
l_int|NULL
comma
multiline_comment|/* rename&t;   */
l_int|NULL
comma
multiline_comment|/* readlink&t;   */
l_int|NULL
comma
multiline_comment|/* follow_link */
l_int|NULL
comma
multiline_comment|/* readpage&t;   */
l_int|NULL
comma
multiline_comment|/* writepage   */
l_int|NULL
comma
multiline_comment|/* bmap&t;   */
l_int|NULL
comma
multiline_comment|/* truncate&t;   */
l_int|NULL
multiline_comment|/* permission  */
)brace
suffix:semicolon
multiline_comment|/*&n; * print some useful info about the hash table.  This function&n; * is _REALLY_ slow (see the nested for loops below) but nothing&n; * in here should be really timing critical. -- Cort&n; */
DECL|function|ppc_htab_read
r_static
r_int
id|ppc_htab_read
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
r_int
id|nbytes
)paren
(brace
r_int
id|n
op_assign
l_int|0
comma
id|valid
suffix:semicolon
r_int
r_int
id|kptes
op_assign
l_int|0
comma
id|overflow
op_assign
l_int|0
comma
id|uptes
op_assign
l_int|0
suffix:semicolon
id|PTE
op_star
id|ptr
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
r_char
id|buffer
(braket
l_int|128
)braket
suffix:semicolon
r_if
c_cond
(paren
id|nbytes
OL
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/*&n;&t; * compute user/kernel pte&squot;s table this info can be&n;&t; * misleading since there can be valid (v bit set) entries&n;&t; * in the table but their vsid is used by no process (mm-&gt;context)&n;&t; * due to the way tlb invalidation is handled on the ppc&n;&t; * -- Cort&n;&t; */
r_for
c_loop
(paren
id|ptr
op_assign
id|Hash
suffix:semicolon
id|ptr
OL
id|Hash_end
suffix:semicolon
id|ptr
op_add_assign
r_sizeof
(paren
id|PTE
)paren
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;v
)paren
(brace
multiline_comment|/* make sure someone is using this context/vsid */
id|for_each_task
c_func
(paren
id|p
)paren
(brace
r_if
c_cond
(paren
(paren
id|ptr-&gt;vsid
op_rshift
l_int|4
)paren
op_eq
id|p-&gt;mm-&gt;context
)paren
(brace
id|valid
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|valid
)paren
r_continue
suffix:semicolon
multiline_comment|/* user not allowed read or write */
r_if
c_cond
(paren
id|ptr-&gt;pp
op_eq
id|PP_RWXX
)paren
id|kptes
op_increment
suffix:semicolon
r_else
id|uptes
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ptr-&gt;h
op_eq
l_int|1
)paren
id|overflow
op_increment
suffix:semicolon
)brace
)brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
comma
l_string|&quot;Size&bslash;t&bslash;t: %luKb&bslash;n&quot;
l_string|&quot;Buckets&bslash;t&bslash;t: %lu&bslash;n&quot;
l_string|&quot;Address&bslash;t&bslash;t: %08lx&bslash;n&quot;
l_string|&quot;Entries&bslash;t&bslash;t: %lu&bslash;n&quot;
l_string|&quot;User ptes&bslash;t: %u&bslash;n&quot;
l_string|&quot;Kernel ptes&bslash;t: %u&bslash;n&quot;
l_string|&quot;Overflows&bslash;t: %u&bslash;n&quot;
l_string|&quot;Percent full&bslash;t: %%%lu&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
(paren
id|Hash_size
op_rshift
l_int|10
)paren
comma
(paren
id|Hash_size
op_div
(paren
r_sizeof
(paren
id|PTE
)paren
op_star
l_int|8
)paren
)paren
comma
(paren
r_int
r_int
)paren
id|Hash
comma
id|Hash_size
op_div
r_sizeof
(paren
id|PTE
)paren
comma
id|uptes
comma
id|kptes
comma
id|overflow
comma
(paren
(paren
id|kptes
op_plus
id|uptes
)paren
op_star
l_int|100
)paren
op_div
(paren
id|Hash_size
op_div
r_sizeof
(paren
id|PTE
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|file-&gt;f_pos
op_ge
id|strlen
c_func
(paren
id|buffer
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|n
OG
id|strlen
c_func
(paren
id|buffer
)paren
op_minus
id|file-&gt;f_pos
)paren
id|n
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
op_minus
id|file-&gt;f_pos
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
id|buffer
op_plus
id|file-&gt;f_pos
comma
id|n
)paren
suffix:semicolon
id|file-&gt;f_pos
op_add_assign
id|n
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Can&squot;t _yet_ adjust the hash table size while running. -- Cort&n; */
r_static
r_int
DECL|function|ppc_htab_write
id|ppc_htab_write
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
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_extern
r_void
id|reset_SDR1
c_func
(paren
r_void
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;uid
op_ne
l_int|0
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
multiline_comment|/* only know how to set size right now */
r_if
c_cond
(paren
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;size &quot;
comma
l_int|5
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|size
op_assign
id|simple_strtoul
c_func
(paren
op_amp
id|buffer
(braket
l_int|5
)braket
comma
l_int|NULL
comma
l_int|10
)paren
suffix:semicolon
multiline_comment|/* only allow to shrink */
r_if
c_cond
(paren
id|size
op_ge
id|Hash_size
op_rshift
l_int|10
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* minimum size of htab */
r_if
c_cond
(paren
id|size
OL
l_int|64
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* make sure it&squot;s a multiple of 64k */
r_if
c_cond
(paren
id|size
op_mod
l_int|64
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Hash table resize to %luk&bslash;n&quot;
comma
id|size
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We need to rehash all kernel entries for the new htab size.&n;&t; * Kernel only since we do a flush_tlb_all().  Since it&squot;s kernel&n;&t; * we only need to bother with vsids 0-15.  To avoid problems of&n;&t; * clobbering un-rehashed values we put the htab at a new spot&n;&t; * and put everything there.&n;&t; * -- Cort&n;&t; */
id|Hash_size
op_assign
id|size
op_lshift
l_int|10
suffix:semicolon
id|Hash_mask
op_assign
(paren
id|Hash_size
op_rshift
l_int|6
)paren
op_minus
l_int|1
suffix:semicolon
id|_SDR1
op_assign
id|__pa
c_func
(paren
id|Hash
)paren
op_or
(paren
id|Hash_mask
op_rshift
l_int|10
)paren
suffix:semicolon
id|flush_tlb_all
c_func
(paren
)paren
suffix:semicolon
id|reset_SDR1
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;done&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|ppc_htab_lseek
id|ppc_htab_lseek
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
r_int
r_int
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
r_case
l_int|2
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
eof