multiline_comment|/*&n; * linux/arch/arm/lib/getconsdata.c&n; *&n; * Copyright (C) 1995, 1996 Russell King&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|OFF_TSK
mdefine_line|#define OFF_TSK(n) (unsigned long)&amp;(((struct task_struct *)0)-&gt;n)
DECL|macro|OFF_MM
mdefine_line|#define OFF_MM(n) (unsigned long)&amp;(((struct mm_struct *)0)-&gt;n)
macro_line|#ifdef KERNEL_DOMAIN
DECL|variable|kernel_domain
r_int
r_int
id|kernel_domain
op_assign
id|KERNEL_DOMAIN
suffix:semicolon
macro_line|#endif
macro_line|#ifdef USER_DOMAIN
DECL|variable|user_domain
r_int
r_int
id|user_domain
op_assign
id|USER_DOMAIN
suffix:semicolon
macro_line|#endif
DECL|variable|addr_limit
r_int
r_int
id|addr_limit
op_assign
id|OFF_TSK
c_func
(paren
id|addr_limit
)paren
suffix:semicolon
DECL|variable|tss_memmap
r_int
r_int
id|tss_memmap
op_assign
id|OFF_TSK
c_func
(paren
id|tss.memmap
)paren
suffix:semicolon
DECL|variable|mm
r_int
r_int
id|mm
op_assign
id|OFF_TSK
c_func
(paren
id|mm
)paren
suffix:semicolon
DECL|variable|pgd
r_int
r_int
id|pgd
op_assign
id|OFF_MM
c_func
(paren
id|pgd
)paren
suffix:semicolon
DECL|variable|tss_save
r_int
r_int
id|tss_save
op_assign
id|OFF_TSK
c_func
(paren
id|tss.save
)paren
suffix:semicolon
DECL|variable|tss_fpesave
r_int
r_int
id|tss_fpesave
op_assign
id|OFF_TSK
c_func
(paren
id|tss.fpstate.soft.save
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CPU_ARM2) || defined(CONFIG_CPU_ARM3)
DECL|variable|tss_memcmap
r_int
r_int
id|tss_memcmap
op_assign
id|OFF_TSK
c_func
(paren
id|tss.memcmap
)paren
suffix:semicolon
macro_line|#endif
eof
