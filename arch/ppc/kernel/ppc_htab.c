multiline_comment|/*&n; * $Id: ppc_htab.c,v 1.25 1998/08/26 10:28:26 davem Exp $&n; *&n; * PowerPC hash table management proc entry.  Will show information&n; * about the current hash table and will allow changes to it.&n; *&n; * Written by Cort Dougan (cort@cs.nmt.edu)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/stat.h&gt;
macro_line|#include &lt;linux/sysctl.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/residual.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
r_static
id|ssize_t
id|ppc_htab_read
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
suffix:semicolon
r_static
id|ssize_t
id|ppc_htab_write
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
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
suffix:semicolon
r_static
r_int
r_int
id|ppc_htab_lseek
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
suffix:semicolon
r_int
id|proc_dol2crvec
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
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
r_extern
r_int
r_int
id|htab_reloads
suffix:semicolon
r_extern
r_int
r_int
id|htab_evicts
suffix:semicolon
r_extern
r_int
r_int
id|pte_misses
suffix:semicolon
r_extern
r_int
r_int
id|pte_errors
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
multiline_comment|/* flush */
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
multiline_comment|/* these will go into processor.h when I&squot;m done debugging -- Cort */
DECL|macro|MMCR0
mdefine_line|#define MMCR0 952
DECL|macro|MMCR0_PMC1_CYCLES
mdefine_line|#define MMCR0_PMC1_CYCLES (0x1&lt;&lt;7)
DECL|macro|MMCR0_PMC1_ICACHEMISS
mdefine_line|#define MMCR0_PMC1_ICACHEMISS (0x5&lt;&lt;7)
DECL|macro|MMCR0_PMC1_DTLB
mdefine_line|#define MMCR0_PMC1_DTLB (0x6&lt;&lt;7)
DECL|macro|MMCR0_PMC2_DCACHEMISS
mdefine_line|#define MMCR0_PMC2_DCACHEMISS (0x6)
DECL|macro|MMCR0_PMC2_CYCLES
mdefine_line|#define MMCR0_PMC2_CYCLES (0x1)
DECL|macro|MMCR0_PMC2_ITLB
mdefine_line|#define MMCR0_PMC2_ITLB (0x7)
DECL|macro|MMCR0_PMC2_LOADMISSTIME
mdefine_line|#define MMCR0_PMC2_LOADMISSTIME (0x5)
DECL|macro|PMC1
mdefine_line|#define PMC1 953
DECL|macro|PMC2
mdefine_line|#define PMC2 954
DECL|function|pmc1_lookup
r_char
op_star
id|pmc1_lookup
c_func
(paren
r_int
r_int
id|mmcr0
)paren
(brace
r_switch
c_cond
(paren
id|mmcr0
op_amp
(paren
l_int|0x7f
op_lshift
l_int|7
)paren
)paren
(brace
r_case
l_int|0x0
suffix:colon
r_return
l_string|&quot;none&quot;
suffix:semicolon
r_case
id|MMCR0_PMC1_CYCLES
suffix:colon
r_return
l_string|&quot;cycles&quot;
suffix:semicolon
r_case
id|MMCR0_PMC1_ICACHEMISS
suffix:colon
r_return
l_string|&quot;ic miss&quot;
suffix:semicolon
r_case
id|MMCR0_PMC1_DTLB
suffix:colon
r_return
l_string|&quot;dtlb miss&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
)brace
DECL|function|pmc2_lookup
r_char
op_star
id|pmc2_lookup
c_func
(paren
r_int
r_int
id|mmcr0
)paren
(brace
r_switch
c_cond
(paren
id|mmcr0
op_amp
l_int|0x3f
)paren
(brace
r_case
l_int|0x0
suffix:colon
r_return
l_string|&quot;none&quot;
suffix:semicolon
r_case
id|MMCR0_PMC2_CYCLES
suffix:colon
r_return
l_string|&quot;cycles&quot;
suffix:semicolon
r_case
id|MMCR0_PMC2_DCACHEMISS
suffix:colon
r_return
l_string|&quot;dc miss&quot;
suffix:semicolon
r_case
id|MMCR0_PMC2_ITLB
suffix:colon
r_return
l_string|&quot;itlb miss&quot;
suffix:semicolon
r_case
id|MMCR0_PMC2_LOADMISSTIME
suffix:colon
r_return
l_string|&quot;load miss time&quot;
suffix:semicolon
r_default
suffix:colon
r_return
l_string|&quot;unknown&quot;
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * print some useful info about the hash table.  This function&n; * is _REALLY_ slow (see the nested for loops below) but nothing&n; * in here should be really timing critical. -- Cort&n; */
DECL|function|ppc_htab_read
r_static
id|ssize_t
id|ppc_htab_read
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
r_int
r_int
id|mmcr0
op_assign
l_int|0
comma
id|pmc1
op_assign
l_int|0
comma
id|pmc2
op_assign
l_int|0
suffix:semicolon
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
comma
id|zombie_ptes
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
l_int|512
)braket
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
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
id|asm
r_volatile
(paren
l_string|&quot;mfspr %0,952 &bslash;n&bslash;t&quot;
l_string|&quot;mfspr %1,953 &bslash;n&bslash;t&quot;
l_string|&quot;mfspr %2,954 &bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|mmcr0
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pmc1
)paren
comma
l_string|&quot;=r&quot;
(paren
id|pmc2
)paren
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;604 Performance Monitoring&bslash;n&quot;
l_string|&quot;MMCR0&bslash;t&bslash;t: %08lx %s%s &quot;
comma
id|mmcr0
comma
(paren
id|mmcr0
op_rshift
l_int|28
op_amp
l_int|0x2
)paren
ques
c_cond
l_string|&quot;(user mode counted)&quot;
suffix:colon
l_string|&quot;&quot;
comma
(paren
id|mmcr0
op_rshift
l_int|28
op_amp
l_int|0x4
)paren
ques
c_cond
l_string|&quot;(kernel mode counted)&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;&bslash;nPMC1&bslash;t&bslash;t: %08lx (%s)&bslash;n&quot;
l_string|&quot;PMC2&bslash;t&bslash;t: %08lx (%s)&bslash;n&quot;
comma
id|pmc1
comma
id|pmc1_lookup
c_func
(paren
id|mmcr0
)paren
comma
id|pmc2
comma
id|pmc2_lookup
c_func
(paren
id|mmcr0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* if we don&squot;t have a htab */
r_if
c_cond
(paren
id|Hash_size
op_eq
l_int|0
)paren
(brace
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;No Hash Table used&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|return_string
suffix:semicolon
)brace
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
op_increment
)paren
(brace
r_if
c_cond
(paren
id|ptr-&gt;v
)paren
(brace
multiline_comment|/* make sure someone is using this context/vsid */
id|valid
op_assign
l_int|0
suffix:semicolon
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
(brace
id|zombie_ptes
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
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
op_plus
id|n
comma
l_string|&quot;PTE Hash Table Information&bslash;n&quot;
l_string|&quot;Size&bslash;t&bslash;t: %luKb&bslash;n&quot;
l_string|&quot;Buckets&bslash;t&bslash;t: %lu&bslash;n&quot;
l_string|&quot;Address&bslash;t&bslash;t: %08lx&bslash;n&quot;
l_string|&quot;Entries&bslash;t&bslash;t: %lu&bslash;n&quot;
l_string|&quot;User ptes&bslash;t: %u&bslash;n&quot;
l_string|&quot;Kernel ptes&bslash;t: %u&bslash;n&quot;
l_string|&quot;Overflows&bslash;t: %u&bslash;n&quot;
l_string|&quot;Zombies&bslash;t&bslash;t: %u&bslash;n&quot;
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
id|zombie_ptes
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
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;Reloads&bslash;t&bslash;t: %08lx&bslash;n&quot;
l_string|&quot;Evicts&bslash;t&bslash;t: %08lx&bslash;n&quot;
comma
id|htab_reloads
comma
id|htab_evicts
)paren
suffix:semicolon
id|return_string
suffix:colon
id|n
op_add_assign
id|sprintf
c_func
(paren
id|buffer
op_plus
id|n
comma
l_string|&quot;Non-error misses: %08lx&bslash;n&quot;
l_string|&quot;Error misses&bslash;t: %08lx&bslash;n&quot;
comma
id|pte_misses
comma
id|pte_errors
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|ppos
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
op_star
id|ppos
)paren
id|n
op_assign
id|strlen
c_func
(paren
id|buffer
)paren
op_minus
op_star
id|ppos
suffix:semicolon
id|copy_to_user
c_func
(paren
id|buf
comma
id|buffer
op_plus
op_star
id|ppos
comma
id|n
)paren
suffix:semicolon
op_star
id|ppos
op_add_assign
id|n
suffix:semicolon
r_return
id|n
suffix:semicolon
)brace
multiline_comment|/*&n; * Allow user to define performance counters and resize the hash table&n; */
DECL|function|ppc_htab_write
r_static
id|ssize_t
id|ppc_htab_write
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
id|buffer
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
macro_line|#ifndef CONFIG_8xx
r_int
r_int
id|tmp
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
multiline_comment|/* don&squot;t set the htab size for now */
r_if
c_cond
(paren
op_logical_neg
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
id|EBUSY
suffix:semicolon
multiline_comment|/* turn off performance monitoring */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;off&quot;
comma
l_int|3
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
id|asm
r_volatile
(paren
l_string|&quot;mtspr %0, %3 &bslash;n&bslash;t&quot;
l_string|&quot;mtspr %1, %3 &bslash;n&bslash;t&quot;
l_string|&quot;mtspr %2, %3 &bslash;n&bslash;t&quot;
op_scope_resolution
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC1
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;reset&quot;
comma
l_int|5
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* reset PMC1 and PMC2 */
id|asm
r_volatile
(paren
l_string|&quot;mtspr 953, %0 &bslash;n&bslash;t&quot;
l_string|&quot;mtspr 954, %0 &bslash;n&bslash;t&quot;
op_scope_resolution
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|htab_reloads
op_assign
l_int|0
suffix:semicolon
id|htab_evicts
op_assign
l_int|0
suffix:semicolon
id|pte_misses
op_assign
l_int|0
suffix:semicolon
id|pte_errors
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;user&quot;
comma
l_int|4
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
c_func
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x60000000
)paren
suffix:semicolon
id|tmp
op_or_assign
l_int|0x20000000
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
l_string|&quot;mtspr %5,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc2 */
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC1
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;kernel&quot;
comma
l_int|6
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
c_func
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x60000000
)paren
suffix:semicolon
id|tmp
op_or_assign
l_int|0x40000000
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
l_string|&quot;mtspr %5,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc2 */
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC1
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* PMC1 values */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;dtlb&quot;
comma
l_int|4
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
c_func
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x7f
op_lshift
l_int|7
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MMCR0_PMC1_DTLB
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0_PMC1_DTLB
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC1
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;ic miss&quot;
comma
l_int|7
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
c_func
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
(paren
l_int|0x7f
op_lshift
l_int|7
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MMCR0_PMC1_ICACHEMISS
suffix:semicolon
id|asm
r_volatile
(paren
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
op_scope_resolution
l_string|&quot;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0_PMC1_ICACHEMISS
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC1
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* PMC2 values */
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;load miss time&quot;
comma
l_int|14
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
r_volatile
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
multiline_comment|/* get current mccr0 */
l_string|&quot;rlwinm %0,%0,0,0,31-6&bslash;n&bslash;t&quot;
multiline_comment|/* clear bits [26-31] */
l_string|&quot;ori   %0,%0,%2 &bslash;n&bslash;t&quot;
multiline_comment|/* or in mmcr0 settings */
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0_PMC2_LOADMISSTIME
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;itlb&quot;
comma
l_int|4
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
r_volatile
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
multiline_comment|/* get current mccr0 */
l_string|&quot;rlwinm %0,%0,0,0,31-6&bslash;n&bslash;t&quot;
multiline_comment|/* clear bits [26-31] */
l_string|&quot;ori   %0,%0,%2 &bslash;n&bslash;t&quot;
multiline_comment|/* or in mmcr0 settings */
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0_PMC2_ITLB
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buffer
comma
l_string|&quot;dc miss&quot;
comma
l_int|7
)paren
)paren
(brace
r_switch
c_cond
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
(brace
r_case
l_int|4
suffix:colon
multiline_comment|/* 604 */
r_case
l_int|9
suffix:colon
multiline_comment|/* 604e */
r_case
l_int|10
suffix:colon
multiline_comment|/* 604ev5 */
multiline_comment|/* setup mmcr0 and clear the correct pmc */
id|asm
r_volatile
(paren
l_string|&quot;mfspr %0,%1&bslash;n&bslash;t&quot;
multiline_comment|/* get current mccr0 */
l_string|&quot;rlwinm %0,%0,0,0,31-6&bslash;n&bslash;t&quot;
multiline_comment|/* clear bits [26-31] */
l_string|&quot;ori   %0,%0,%2 &bslash;n&bslash;t&quot;
multiline_comment|/* or in mmcr0 settings */
l_string|&quot;mtspr %1,%0 &bslash;n&bslash;t&quot;
multiline_comment|/* set new mccr0 */
l_string|&quot;mtspr %3,%4 &bslash;n&bslash;t&quot;
multiline_comment|/* reset the pmc */
suffix:colon
l_string|&quot;=r&quot;
(paren
id|tmp
)paren
suffix:colon
l_string|&quot;i&quot;
(paren
id|MMCR0
)paren
comma
l_string|&quot;i&quot;
(paren
id|MMCR0_PMC2_DCACHEMISS
)paren
comma
l_string|&quot;i&quot;
(paren
id|PMC2
)paren
comma
l_string|&quot;r&quot;
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
)brace
r_return
id|count
suffix:semicolon
macro_line|#if 0 /* resizing htab is a bit difficult right now -- Cort */
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
macro_line|#endif&t;
r_return
id|count
suffix:semicolon
macro_line|#else /* CONFIG_8xx */
r_return
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_8xx */
)brace
r_static
r_int
r_int
DECL|function|ppc_htab_lseek
id|ppc_htab_lseek
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
DECL|function|proc_dol2crvec
r_int
id|proc_dol2crvec
c_func
(paren
id|ctl_table
op_star
id|table
comma
r_int
id|write
comma
r_struct
id|file
op_star
id|filp
comma
r_void
op_star
id|buffer
comma
r_int
op_star
id|lenp
)paren
(brace
r_int
id|vleft
comma
id|first
op_assign
l_int|1
comma
id|len
comma
id|left
comma
id|val
suffix:semicolon
DECL|macro|TMPBUFLEN
mdefine_line|#define TMPBUFLEN 256
r_char
id|buf
(braket
id|TMPBUFLEN
)braket
comma
op_star
id|p
suffix:semicolon
r_if
c_cond
(paren
(paren
id|_get_PVR
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_ne
l_int|8
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
multiline_comment|/*!table-&gt;maxlen ||*/
(paren
id|filp-&gt;f_pos
op_logical_and
op_logical_neg
id|write
)paren
)paren
(brace
op_star
id|lenp
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|vleft
op_assign
id|table-&gt;maxlen
op_div
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|left
op_assign
op_star
id|lenp
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|left
multiline_comment|/*&amp;&amp; vleft--*/
suffix:semicolon
id|first
op_assign
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|write
)paren
(brace
r_while
c_loop
(paren
id|left
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|left
op_decrement
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|buffer
)paren
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|left
)paren
r_break
suffix:semicolon
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|TMPBUFLEN
op_minus
l_int|1
)paren
id|len
op_assign
id|TMPBUFLEN
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|buf
comma
id|buffer
comma
id|len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|buf
(braket
id|len
)braket
op_assign
l_int|0
suffix:semicolon
id|p
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_star
id|p
template_param
l_char|&squot;9&squot;
)paren
r_break
suffix:semicolon
id|val
op_assign
id|simple_strtoul
c_func
(paren
id|p
comma
op_amp
id|p
comma
l_int|0
)paren
suffix:semicolon
id|len
op_assign
id|p
op_minus
id|buf
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
OL
id|left
)paren
op_logical_and
op_star
id|p
op_logical_and
op_logical_neg
id|isspace
c_func
(paren
op_star
id|p
)paren
)paren
r_break
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
id|left
op_sub_assign
id|len
suffix:semicolon
id|_set_L2CR
c_func
(paren
id|val
)paren
suffix:semicolon
r_while
c_loop
(paren
id|_get_L2CR
c_func
(paren
)paren
op_amp
l_int|0x1
)paren
multiline_comment|/* wait for invalidate to finish */
suffix:semicolon
)brace
r_else
(brace
id|p
op_assign
id|buf
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|first
)paren
op_star
id|p
op_increment
op_assign
l_char|&squot;&bslash;t&squot;
suffix:semicolon
id|val
op_assign
id|_get_L2CR
c_func
(paren
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%08x: &quot;
comma
id|val
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot; %s&quot;
comma
(paren
id|val
op_amp
l_int|0x80000000
)paren
ques
c_cond
l_string|&quot;enabled&quot;
suffix:colon
l_string|&quot;disabled&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,%sparity&quot;
comma
(paren
id|val
op_amp
l_int|0x40000000
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;no &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|val
op_rshift
l_int|28
)paren
op_amp
l_int|0x3
)paren
(brace
r_case
l_int|1
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,256Kb&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,512Kb&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,1M&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,unknown size&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|val
op_rshift
l_int|25
)paren
op_amp
l_int|0x7
)paren
(brace
r_case
l_int|0
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,clock disabled&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,+1 clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,+1.5 clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|7
suffix:colon
r_case
l_int|3
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,reserved clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,+2 clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,+2.5 clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|6
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,+3 clock&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
(paren
id|val
op_rshift
l_int|23
)paren
op_amp
l_int|0x2
)paren
(brace
r_case
l_int|0
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,flow-through burst SRAM&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,reserved SRAM&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,pipelined burst SRAM&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,pipelined late-write SRAM&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s&quot;
comma
(paren
id|val
op_rshift
l_int|22
)paren
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;,data only&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;%s&quot;
comma
(paren
id|val
op_rshift
l_int|20
)paren
ques
c_cond
l_string|&quot;,ZZ enabled&quot;
suffix:colon
l_string|&quot;&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,%s&quot;
comma
(paren
id|val
op_rshift
l_int|19
)paren
ques
c_cond
l_string|&quot;write-through&quot;
suffix:colon
l_string|&quot;copy-back&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;,%sns hold&quot;
comma
(paren
id|val
op_rshift
l_int|16
)paren
ques
c_cond
l_string|&quot;1.0&quot;
suffix:colon
l_string|&quot;0.5&quot;
)paren
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|left
)paren
id|len
op_assign
id|left
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
id|buffer
comma
id|buf
comma
id|len
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|left
op_sub_assign
id|len
suffix:semicolon
id|buffer
op_add_assign
id|len
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|write
op_logical_and
op_logical_neg
id|first
op_logical_and
id|left
)paren
(brace
r_if
c_cond
(paren
id|put_user
c_func
(paren
l_char|&squot;&bslash;n&squot;
comma
(paren
r_char
op_star
)paren
id|buffer
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
id|left
op_decrement
comma
id|buffer
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|write
)paren
(brace
id|p
op_assign
(paren
r_char
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|left
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|c
comma
id|p
op_increment
)paren
)paren
(brace
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|isspace
c_func
(paren
id|c
)paren
)paren
r_break
suffix:semicolon
id|left
op_decrement
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|write
op_logical_and
id|first
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
op_star
id|lenp
op_sub_assign
id|left
suffix:semicolon
id|filp-&gt;f_pos
op_add_assign
op_star
id|lenp
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
