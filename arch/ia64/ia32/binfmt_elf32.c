multiline_comment|/*&n; * IA-32 ELF support.&n; *&n; * Copyright (C) 1999 Arun Sharma &lt;arun.sharma@intel.com&gt;&n; */
macro_line|#include &lt;linux/posix_types.h&gt;
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
DECL|macro|CONFIG_BINFMT_ELF32
mdefine_line|#define CONFIG_BINFMT_ELF32
multiline_comment|/* Override some function names */
DECL|macro|start_thread
macro_line|#undef start_thread
DECL|macro|start_thread
mdefine_line|#define start_thread&t;&t;&t;ia32_start_thread
DECL|macro|init_elf_binfmt
mdefine_line|#define init_elf_binfmt&t;&t;&t;init_elf32_binfmt
DECL|macro|CONFIG_BINFMT_ELF
macro_line|#undef CONFIG_BINFMT_ELF
macro_line|#ifdef CONFIG_BINFMT_ELF32
DECL|macro|CONFIG_BINFMT_ELF
macro_line|# define CONFIG_BINFMT_ELF&t;&t;CONFIG_BINFMT_ELF32
macro_line|#endif
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|#undef CONFIG_BINFMT_ELF_MODULE
macro_line|#ifdef CONFIG_BINFMT_ELF32_MODULE
DECL|macro|CONFIG_BINFMT_ELF_MODULE
macro_line|# define CONFIG_BINFMT_ELF_MODULE&t;CONFIG_BINFMT_ELF32_MODULE
macro_line|#endif
r_void
id|ia64_elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;&t;ia64_elf32_init(_r)
DECL|macro|setup_arg_pages
mdefine_line|#define setup_arg_pages(bprm)&t;&t;ia32_setup_arg_pages(bprm)
multiline_comment|/* Ugly but avoids duplication */
macro_line|#include &quot;../../../fs/binfmt_elf.c&quot;
multiline_comment|/* Global descriptor table */
DECL|variable|ia32_gdt_table
DECL|variable|ia32_tss
r_int
r_int
op_star
id|ia32_gdt_table
comma
op_star
id|ia32_tss
suffix:semicolon
r_struct
id|page
op_star
DECL|function|put_shared_page
id|put_shared_page
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|address
)paren
(brace
id|pgd_t
op_star
id|pgd
suffix:semicolon
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|page_count
c_func
(paren
id|page
)paren
op_ne
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;mem_map disagrees with %p at %08lx&bslash;n&quot;
comma
id|page
comma
id|address
)paren
suffix:semicolon
id|pgd
op_assign
id|pgd_offset
c_func
(paren
id|tsk-&gt;mm
comma
id|address
)paren
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
id|pgd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
(brace
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|oom
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|pte
op_assign
id|pte_alloc
c_func
(paren
id|pmd
comma
id|address
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
(brace
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
id|oom
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
(brace
id|pte_ERROR
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
id|__free_page
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|flush_page_to_ram
c_func
(paren
id|page
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|pte_mkwrite
c_func
(paren
id|mk_pte
c_func
(paren
id|page
comma
id|PAGE_SHARED
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* no need for flush_tlb */
r_return
id|page
suffix:semicolon
)brace
DECL|function|ia64_elf32_init
r_void
id|ia64_elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|nr
suffix:semicolon
id|put_shared_page
c_func
(paren
id|current
comma
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|ia32_gdt_table
)paren
comma
id|IA32_PAGE_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|PAGE_SHIFT
op_le
id|IA32_PAGE_SHIFT
)paren
id|put_shared_page
c_func
(paren
id|current
comma
id|mem_map
op_plus
id|MAP_NR
c_func
(paren
id|ia32_tss
)paren
comma
id|IA32_PAGE_OFFSET
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
id|nr
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do all the IA-32 setup here */
multiline_comment|/* CS descriptor */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.csd = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0xBL
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
)paren
suffix:semicolon
multiline_comment|/* SS descriptor */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.ssd = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
)paren
suffix:semicolon
multiline_comment|/* EFLAGS */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.eflag = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
id|IA32_EFLAG
)paren
)paren
suffix:semicolon
multiline_comment|/* Control registers */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.cflg = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
(paren
id|ulong
)paren
id|IA32_CR4
op_lshift
l_int|32
)paren
op_or
id|IA32_CR0
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov ar.fsr = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|ulong
)paren
id|IA32_FSR_DEFAULT
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov ar.fcr = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
(paren
id|ulong
)paren
id|IA32_FCR_DEFAULT
)paren
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov ar.fir = r0&quot;
)paren
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;mov ar.fdr = r0&quot;
)paren
suffix:semicolon
multiline_comment|/* TSS */
id|__asm__
c_func
(paren
l_string|&quot;mov ar.k1 = %0&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
id|IA64_SEG_DESCRIPTOR
c_func
(paren
id|IA32_PAGE_OFFSET
op_plus
id|PAGE_SIZE
comma
l_int|0x1FFFL
comma
l_int|0xBL
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the segment selectors right */
id|regs-&gt;r16
op_assign
(paren
id|__USER_DS
op_lshift
l_int|16
)paren
op_or
(paren
id|__USER_DS
)paren
suffix:semicolon
multiline_comment|/* ES == DS, GS, FS are zero */
id|regs-&gt;r17
op_assign
(paren
id|_TSS
c_func
(paren
id|nr
)paren
op_lshift
l_int|48
)paren
op_or
(paren
id|_LDT
c_func
(paren
id|nr
)paren
op_lshift
l_int|32
)paren
op_or
(paren
id|__USER_DS
op_lshift
l_int|16
)paren
op_or
id|__USER_CS
suffix:semicolon
multiline_comment|/* Setup other segment descriptors - ESD, DSD, FSD, GSD */
id|regs-&gt;r24
op_assign
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
suffix:semicolon
id|regs-&gt;r27
op_assign
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
suffix:semicolon
id|regs-&gt;r28
op_assign
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
suffix:semicolon
id|regs-&gt;r29
op_assign
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0L
comma
l_int|0xFFFFFL
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
suffix:semicolon
multiline_comment|/* Setup the LDT and GDT */
id|regs-&gt;r30
op_assign
id|ia32_gdt_table
(braket
id|_LDT
c_func
(paren
id|nr
)paren
)braket
suffix:semicolon
id|regs-&gt;r31
op_assign
id|IA64_SEG_DESCRIPTOR
c_func
(paren
l_int|0xc0000000L
comma
l_int|0x400L
comma
l_int|0x3L
comma
l_int|1L
comma
l_int|3L
comma
l_int|1L
comma
l_int|1L
comma
l_int|1L
)paren
suffix:semicolon
multiline_comment|/* Clear psr.ac */
id|regs-&gt;cr_ipsr
op_and_assign
op_complement
id|IA64_PSR_AC
suffix:semicolon
id|regs-&gt;loadrs
op_assign
l_int|0
suffix:semicolon
)brace
DECL|macro|STACK_TOP
macro_line|#undef STACK_TOP
DECL|macro|STACK_TOP
mdefine_line|#define STACK_TOP ((IA32_PAGE_OFFSET/3) * 2)
DECL|function|ia32_setup_arg_pages
r_int
id|ia32_setup_arg_pages
c_func
(paren
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
id|bprm-&gt;p
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
op_logical_neg
id|mpnt
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
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
id|bprm-&gt;p
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
id|mpnt-&gt;vm_pgoff
op_assign
l_int|0
suffix:semicolon
id|mpnt-&gt;vm_file
op_assign
l_int|NULL
suffix:semicolon
id|mpnt-&gt;vm_private_data
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
l_int|0
suffix:semicolon
)brace
eof
