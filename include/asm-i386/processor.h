multiline_comment|/*&n; * include/asm-i386/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_I386_PROCESSOR_H
DECL|macro|__ASM_I386_PROCESSOR_H
mdefine_line|#define __ASM_I386_PROCESSOR_H
macro_line|#include &lt;asm/vm86.h&gt;
macro_line|#include &lt;asm/math_emu.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; *  CPU type and hardware bug flags. Kept separately for each CPU.&n; *  Members of this structure are referenced in head.S, so think twice&n; *  before touching them. [mj]&n; */
DECL|struct|cpuinfo_x86
r_struct
id|cpuinfo_x86
(brace
DECL|member|x86
id|__u8
id|x86
suffix:semicolon
multiline_comment|/* CPU family */
DECL|member|x86_vendor
id|__u8
id|x86_vendor
suffix:semicolon
multiline_comment|/* CPU vendor */
DECL|member|x86_model
id|__u8
id|x86_model
suffix:semicolon
DECL|member|x86_mask
id|__u8
id|x86_mask
suffix:semicolon
DECL|member|wp_works_ok
r_char
id|wp_works_ok
suffix:semicolon
multiline_comment|/* It doesn&squot;t on 386&squot;s */
DECL|member|hlt_works_ok
r_char
id|hlt_works_ok
suffix:semicolon
multiline_comment|/* Problems on some 486Dx4&squot;s and old 386&squot;s */
DECL|member|hard_math
r_char
id|hard_math
suffix:semicolon
DECL|member|rfu
r_char
id|rfu
suffix:semicolon
DECL|member|cpuid_level
r_int
id|cpuid_level
suffix:semicolon
multiline_comment|/* Maximum supported CPUID level, -1=no CPUID */
DECL|member|x86_capability
id|__u32
id|x86_capability
suffix:semicolon
DECL|member|x86_vendor_id
r_char
id|x86_vendor_id
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|x86_model_id
r_char
id|x86_model_id
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|fdiv_bug
r_int
id|fdiv_bug
suffix:semicolon
DECL|member|f00f_bug
r_int
id|f00f_bug
suffix:semicolon
DECL|member|loops_per_sec
r_int
r_int
id|loops_per_sec
suffix:semicolon
DECL|member|pgd_quick
r_int
r_int
op_star
id|pgd_quick
suffix:semicolon
DECL|member|pte_quick
r_int
r_int
op_star
id|pte_quick
suffix:semicolon
DECL|member|pgtable_cache_sz
r_int
r_int
id|pgtable_cache_sz
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|X86_VENDOR_INTEL
mdefine_line|#define X86_VENDOR_INTEL 0
DECL|macro|X86_VENDOR_CYRIX
mdefine_line|#define X86_VENDOR_CYRIX 1
DECL|macro|X86_VENDOR_AMD
mdefine_line|#define X86_VENDOR_AMD 2
DECL|macro|X86_VENDOR_UMC
mdefine_line|#define X86_VENDOR_UMC 3
DECL|macro|X86_VENDOR_NEXGEN
mdefine_line|#define X86_VENDOR_NEXGEN 4
DECL|macro|X86_VENDOR_CENTAUR
mdefine_line|#define X86_VENDOR_CENTAUR 5
DECL|macro|X86_VENDOR_UNKNOWN
mdefine_line|#define X86_VENDOR_UNKNOWN 0xff
multiline_comment|/*&n; * capabilities of CPUs&n; */
DECL|macro|X86_FEATURE_FPU
mdefine_line|#define X86_FEATURE_FPU&t;&t;0x00000001&t;/* onboard FPU */
DECL|macro|X86_FEATURE_VME
mdefine_line|#define X86_FEATURE_VME&t;&t;0x00000002&t;/* Virtual Mode Extensions */
DECL|macro|X86_FEATURE_DE
mdefine_line|#define X86_FEATURE_DE&t;&t;0x00000004&t;/* Debugging Extensions */
DECL|macro|X86_FEATURE_PSE
mdefine_line|#define X86_FEATURE_PSE&t;&t;0x00000008&t;/* Page Size Extensions */
DECL|macro|X86_FEATURE_TSC
mdefine_line|#define X86_FEATURE_TSC&t;&t;0x00000010&t;/* Time Stamp Counter */
DECL|macro|X86_FEATURE_MSR
mdefine_line|#define X86_FEATURE_MSR&t;&t;0x00000020&t;/* Model-Specific Registers, RDMSR, WRMSR */
DECL|macro|X86_FEATURE_PAE
mdefine_line|#define X86_FEATURE_PAE&t;&t;0x00000040&t;/* Physical Address Extensions */
DECL|macro|X86_FEATURE_MCE
mdefine_line|#define X86_FEATURE_MCE&t;&t;0x00000080&t;/* Machine Check Exceptions */
DECL|macro|X86_FEATURE_CX8
mdefine_line|#define X86_FEATURE_CX8&t;&t;0x00000100&t;/* CMPXCHG8 instruction */
DECL|macro|X86_FEATURE_APIC
mdefine_line|#define X86_FEATURE_APIC&t;0x00000200&t;/* onboard APIC */
DECL|macro|X86_FEATURE_10
mdefine_line|#define X86_FEATURE_10&t;&t;0x00000400
DECL|macro|X86_FEATURE_SEP
mdefine_line|#define X86_FEATURE_SEP&t;&t;0x00000800&t;/* Fast System Call */ 
DECL|macro|X86_FEATURE_MTRR
mdefine_line|#define X86_FEATURE_MTRR&t;0x00001000&t;/* Memory Type Range Registers */
DECL|macro|X86_FEATURE_PGE
mdefine_line|#define X86_FEATURE_PGE&t;&t;0x00002000&t;/* Page Global Enable */
DECL|macro|X86_FEATURE_MCA
mdefine_line|#define X86_FEATURE_MCA&t;&t;0x00004000&t;/* Machine Check Architecture */
DECL|macro|X86_FEATURE_CMOV
mdefine_line|#define X86_FEATURE_CMOV&t;0x00008000&t;/* CMOV instruction (FCMOVCC and FCOMI too if FPU present) */
DECL|macro|X86_FEATURE_PAT
mdefine_line|#define X86_FEATURE_PAT&t;0x00010000&t;/* Page Attribute Table */
DECL|macro|X86_FEATURE_PSE36
mdefine_line|#define X86_FEATURE_PSE36&t;0x00020000&t;/* 36-bit PSEs */
DECL|macro|X86_FEATURE_18
mdefine_line|#define X86_FEATURE_18&t;&t;0x00040000
DECL|macro|X86_FEATURE_19
mdefine_line|#define X86_FEATURE_19&t;&t;0x00080000
DECL|macro|X86_FEATURE_20
mdefine_line|#define X86_FEATURE_20&t;&t;0x00100000
DECL|macro|X86_FEATURE_21
mdefine_line|#define X86_FEATURE_21&t;&t;0x00200000
DECL|macro|X86_FEATURE_22
mdefine_line|#define X86_FEATURE_22&t;&t;0x00400000
DECL|macro|X86_FEATURE_MMX
mdefine_line|#define X86_FEATURE_MMX&t;&t;0x00800000&t;/* multimedia extensions */
DECL|macro|X86_FEATURE_FXSR
mdefine_line|#define X86_FEATURE_FXSR&t;0x01000000&t;/* FXSAVE and FXRSTOR instructions (fast save and restore of FPU context), and CR4.OSFXSR (OS uses these instructions) available */
DECL|macro|X86_FEATURE_25
mdefine_line|#define X86_FEATURE_25&t;&t;0x02000000
DECL|macro|X86_FEATURE_26
mdefine_line|#define X86_FEATURE_26&t;&t;0x04000000
DECL|macro|X86_FEATURE_27
mdefine_line|#define X86_FEATURE_27&t;&t;0x08000000
DECL|macro|X86_FEATURE_28
mdefine_line|#define X86_FEATURE_28&t;&t;0x10000000
DECL|macro|X86_FEATURE_29
mdefine_line|#define X86_FEATURE_29&t;&t;0x20000000
DECL|macro|X86_FEATURE_30
mdefine_line|#define X86_FEATURE_30&t;&t;0x40000000
DECL|macro|X86_FEATURE_AMD3D
mdefine_line|#define X86_FEATURE_AMD3D&t;0x80000000
r_extern
r_struct
id|cpuinfo_x86
id|boot_cpu_data
suffix:semicolon
macro_line|#ifdef __SMP__
r_extern
r_struct
id|cpuinfo_x86
id|cpu_data
(braket
)braket
suffix:semicolon
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data cpu_data[smp_processor_id()]
macro_line|#else
DECL|macro|cpu_data
mdefine_line|#define cpu_data &amp;boot_cpu_data
DECL|macro|current_cpu_data
mdefine_line|#define current_cpu_data boot_cpu_data
macro_line|#endif
r_extern
r_char
id|ignore_irq13
suffix:semicolon
r_extern
r_void
id|identify_cpu
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
)paren
suffix:semicolon
r_extern
r_void
id|print_cpu_info
c_func
(paren
r_struct
id|cpuinfo_x86
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; *&t;Generic CPUID function&n; */
DECL|function|cpuid
r_extern
r_inline
r_void
id|cpuid
c_func
(paren
r_int
id|op
comma
r_int
op_star
id|eax
comma
r_int
op_star
id|ebx
comma
r_int
op_star
id|ecx
comma
r_int
op_star
id|edx
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;cpuid&quot;
suffix:colon
l_string|&quot;=a&quot;
(paren
op_star
id|eax
)paren
comma
l_string|&quot;=b&quot;
(paren
op_star
id|ebx
)paren
comma
l_string|&quot;=c&quot;
(paren
op_star
id|ecx
)paren
comma
l_string|&quot;=d&quot;
(paren
op_star
id|edx
)paren
suffix:colon
l_string|&quot;a&quot;
(paren
id|op
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; *      Cyrix CPU configuration register indexes&n; */
DECL|macro|CX86_CCR2
mdefine_line|#define CX86_CCR2 0xc2
DECL|macro|CX86_CCR3
mdefine_line|#define CX86_CCR3 0xc3
DECL|macro|CX86_CCR4
mdefine_line|#define CX86_CCR4 0xe8
DECL|macro|CX86_CCR5
mdefine_line|#define CX86_CCR5 0xe9
DECL|macro|CX86_DIR0
mdefine_line|#define CX86_DIR0 0xfe
DECL|macro|CX86_DIR1
mdefine_line|#define CX86_DIR1 0xff
multiline_comment|/*&n; *      Cyrix CPU indexed register access macros&n; */
DECL|macro|getCx86
mdefine_line|#define getCx86(reg) ({ outb((reg), 0x22); inb(0x23); })
DECL|macro|setCx86
mdefine_line|#define setCx86(reg, data) do { &bslash;&n;&t;outb((reg), 0x22); &bslash;&n;&t;outb((data), 0x23); &bslash;&n;} while (0)
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; */
r_extern
r_int
id|EISA_bus
suffix:semicolon
r_extern
r_int
id|MCA_bus
suffix:semicolon
multiline_comment|/* from system description table in BIOS.  Mostly for MCA use, but&n;others may find it useful. */
r_extern
r_int
r_int
id|machine_id
suffix:semicolon
r_extern
r_int
r_int
id|machine_submodel_id
suffix:semicolon
r_extern
r_int
r_int
id|BIOS_revision
suffix:semicolon
multiline_comment|/*&n; * User space process size: 3GB (default).&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(PAGE_OFFSET)
multiline_comment|/* This decides where the kernel will search for a free chunk of vm&n; * space during mmap&squot;s.&n; */
DECL|macro|TASK_UNMAPPED_BASE
mdefine_line|#define TASK_UNMAPPED_BASE&t;(TASK_SIZE / 3)
multiline_comment|/*&n; * Size of io_bitmap in longwords: 32 is ports 0-0x3ff.&n; */
DECL|macro|IO_BITMAP_SIZE
mdefine_line|#define IO_BITMAP_SIZE&t;32
DECL|struct|i387_hard_struct
r_struct
id|i387_hard_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
DECL|member|status
r_int
id|status
suffix:semicolon
multiline_comment|/* software status information */
)brace
suffix:semicolon
DECL|struct|i387_soft_struct
r_struct
id|i387_soft_struct
(brace
DECL|member|cwd
r_int
id|cwd
suffix:semicolon
DECL|member|swd
r_int
id|swd
suffix:semicolon
DECL|member|twd
r_int
id|twd
suffix:semicolon
DECL|member|fip
r_int
id|fip
suffix:semicolon
DECL|member|fcs
r_int
id|fcs
suffix:semicolon
DECL|member|foo
r_int
id|foo
suffix:semicolon
DECL|member|fos
r_int
id|fos
suffix:semicolon
DECL|member|st_space
r_int
id|st_space
(braket
l_int|20
)braket
suffix:semicolon
multiline_comment|/* 8*10 bytes for each FP-reg = 80 bytes */
DECL|member|ftop
DECL|member|changed
DECL|member|lookahead
DECL|member|no_update
DECL|member|rm
DECL|member|alimit
r_int
r_char
id|ftop
comma
id|changed
comma
id|lookahead
comma
id|no_update
comma
id|rm
comma
id|alimit
suffix:semicolon
DECL|member|info
r_struct
id|info
op_star
id|info
suffix:semicolon
DECL|member|entry_eip
r_int
r_int
id|entry_eip
suffix:semicolon
)brace
suffix:semicolon
DECL|union|i387_union
r_union
id|i387_union
(brace
DECL|member|hard
r_struct
id|i387_hard_struct
id|hard
suffix:semicolon
DECL|member|soft
r_struct
id|i387_soft_struct
id|soft
suffix:semicolon
)brace
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|seg
r_int
r_int
id|seg
suffix:semicolon
DECL|typedef|mm_segment_t
)brace
id|mm_segment_t
suffix:semicolon
DECL|struct|thread_struct
r_struct
id|thread_struct
(brace
DECL|member|back_link
DECL|member|__blh
r_int
r_int
id|back_link
comma
id|__blh
suffix:semicolon
DECL|member|esp0
r_int
r_int
id|esp0
suffix:semicolon
DECL|member|ss0
DECL|member|__ss0h
r_int
r_int
id|ss0
comma
id|__ss0h
suffix:semicolon
DECL|member|esp1
r_int
r_int
id|esp1
suffix:semicolon
DECL|member|ss1
DECL|member|__ss1h
r_int
r_int
id|ss1
comma
id|__ss1h
suffix:semicolon
DECL|member|esp2
r_int
r_int
id|esp2
suffix:semicolon
DECL|member|ss2
DECL|member|__ss2h
r_int
r_int
id|ss2
comma
id|__ss2h
suffix:semicolon
DECL|member|cr3
r_int
r_int
id|cr3
suffix:semicolon
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|eax
DECL|member|ecx
DECL|member|edx
DECL|member|ebx
r_int
r_int
id|eax
comma
id|ecx
comma
id|edx
comma
id|ebx
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|ebp
r_int
r_int
id|ebp
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
DECL|member|ldt
DECL|member|__ldth
r_int
r_int
id|ldt
comma
id|__ldth
suffix:semicolon
DECL|member|trace
DECL|member|bitmap
r_int
r_int
id|trace
comma
id|bitmap
suffix:semicolon
DECL|member|io_bitmap
r_int
r_int
id|io_bitmap
(braket
id|IO_BITMAP_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
DECL|member|tr
r_int
r_int
id|tr
suffix:semicolon
DECL|member|cr2
DECL|member|trap_no
DECL|member|error_code
r_int
r_int
id|cr2
comma
id|trap_no
comma
id|error_code
suffix:semicolon
DECL|member|segment
id|mm_segment_t
id|segment
suffix:semicolon
multiline_comment|/* debug registers */
DECL|member|debugreg
r_int
id|debugreg
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Hardware debugging registers */
multiline_comment|/* floating point info */
DECL|member|i387
r_union
id|i387_union
id|i387
suffix:semicolon
multiline_comment|/* virtual 86 mode info */
DECL|member|vm86_info
r_struct
id|vm86_struct
op_star
id|vm86_info
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|v86flags
DECL|member|v86mask
DECL|member|v86mode
DECL|member|saved_esp0
r_int
r_int
id|v86flags
comma
id|v86mask
comma
id|v86mode
comma
id|saved_esp0
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP &bslash;&n;{ &amp;init_mm, 0, 0, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC, NULL, &amp;init_mm.mmap }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;0,0, /* back_link, __blh */&t;&t;&t;&t;&bslash;&n;&t;sizeof(init_stack) + (long) &amp;init_stack, /* esp0 */&t;&bslash;&n;&t;__KERNEL_DS, 0, /* ss0 */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* stack1, stack2 */&t;&t;&t;&bslash;&n;&t;(long) &amp;swapper_pg_dir - PAGE_OFFSET, /* cr3 */&t;&t;&bslash;&n;&t;0,0, /* eip,eflags */&t;&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0, /* eax,ecx,edx,ebx */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0, /* esp,ebp,esi,edi */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* es,cs,ss */&t;&t;&t;&t;&bslash;&n;&t;0,0,0,0,0,0, /* ds,fs,gs */&t;&t;&t;&t;&bslash;&n;&t;_LDT(0),0, /* ldt */&t;&t;&t;&t;&t;&bslash;&n;&t;0, 0x8000, /* tace, bitmap */&t;&t;&t;&t;&bslash;&n;&t;{~0, }, /* ioperm */&t;&t;&t;&t;&t;&bslash;&n;&t;_TSS(0), 0, 0, 0, (mm_segment_t) { 0 }, /* obsolete */&t;&bslash;&n;&t;{ 0, },&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;{ { 0, }, },  /* 387 state */&t;&t;&t;&t;&bslash;&n;&t;NULL, 0, 0, 0, 0, 0, /* vm86_info */&t;&t;&t;&bslash;&n;}
DECL|macro|start_thread
mdefine_line|#define start_thread(regs, new_eip, new_esp) do {&t;&t;&bslash;&n;&t;__asm__(&quot;movl %w0,%%fs ; movl %w0,%%gs&quot;: :&quot;r&quot; (0));&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xds = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xes = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xss = __USER_DS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;xcs = __USER_CS;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;eip = new_eip;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;esp = new_esp;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
multiline_comment|/* Forward declaration, a strange C thing */
r_struct
id|mm_struct
suffix:semicolon
multiline_comment|/* Free all resources held by a thread. */
r_extern
r_void
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
multiline_comment|/* Copy and release all segment info associated with a VM */
r_extern
r_void
id|copy_segments
c_func
(paren
r_int
id|nr
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|release_segments
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
multiline_comment|/*&n; * Return saved PC of a blocked thread.&n; */
DECL|function|thread_saved_pc
r_extern
r_inline
r_int
r_int
id|thread_saved_pc
c_func
(paren
r_struct
id|thread_struct
op_star
id|t
)paren
(brace
r_return
(paren
(paren
r_int
r_int
op_star
)paren
id|t-&gt;esp
)paren
(braket
l_int|3
)braket
suffix:semicolon
)brace
r_extern
r_struct
id|task_struct
op_star
id|alloc_task_struct
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_task_struct
c_func
(paren
r_struct
id|task_struct
op_star
)paren
suffix:semicolon
DECL|macro|init_task
mdefine_line|#define init_task&t;(init_task_union.task)
DECL|macro|init_stack
mdefine_line|#define init_stack&t;(init_task_union.stack)
macro_line|#endif /* __ASM_I386_PROCESSOR_H */
eof
