multiline_comment|/*&n; * include/asm-i386/processor.h&n; *&n; * Copyright (C) 1994 Linus Torvalds&n; */
macro_line|#ifndef __ASM_I386_PROCESSOR_H
DECL|macro|__ASM_I386_PROCESSOR_H
mdefine_line|#define __ASM_I386_PROCESSOR_H
multiline_comment|/*&n; * System setup and hardware bug flags..&n; */
r_extern
r_char
id|hard_math
suffix:semicolon
r_extern
r_char
id|x86
suffix:semicolon
multiline_comment|/* lower 4 bits */
r_extern
r_char
id|x86_vendor_id
(braket
l_int|13
)braket
suffix:semicolon
r_extern
r_char
id|x86_model
suffix:semicolon
multiline_comment|/* lower 4 bits */
r_extern
r_char
id|x86_mask
suffix:semicolon
multiline_comment|/* lower 4 bits */
r_extern
r_int
id|x86_capability
suffix:semicolon
multiline_comment|/* field of flags */
r_extern
r_int
id|fdiv_bug
suffix:semicolon
r_extern
r_char
id|ignore_irq13
suffix:semicolon
r_extern
r_char
id|wp_works_ok
suffix:semicolon
multiline_comment|/* doesn&squot;t work on a 386 */
r_extern
r_char
id|hlt_works_ok
suffix:semicolon
multiline_comment|/* problems on some 486Dx4&squot;s and old 386&squot;s */
multiline_comment|/*&n; * Bus types (default is ISA, but people can check others with these..)&n; * MCA_bus hardcoded to 0 for now.&n; */
r_extern
r_int
id|EISA_bus
suffix:semicolon
DECL|macro|MCA_bus
mdefine_line|#define MCA_bus 0
DECL|macro|MCA_bus__is_a_macro
mdefine_line|#define MCA_bus__is_a_macro /* for versions in ksyms.c */
multiline_comment|/*&n; * User space process size: 3GB. This is hardcoded into a few places,&n; * so don&squot;t change it unless you know what you are doing.&n; */
DECL|macro|TASK_SIZE
mdefine_line|#define TASK_SIZE&t;(0xC0000000UL)
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
DECL|member|top
r_int
id|top
suffix:semicolon
DECL|member|regs
r_struct
id|fpu_reg
id|regs
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 8*16 bytes for each FP-reg = 128 bytes */
DECL|member|lookahead
r_int
r_char
id|lookahead
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
r_int
r_int
id|v86flags
comma
id|v86mask
comma
id|v86mode
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|INIT_MMAP
mdefine_line|#define INIT_MMAP { &amp;init_task, 0, 0x40000000, PAGE_SHARED, VM_READ | VM_WRITE | VM_EXEC }
DECL|macro|INIT_TSS
mdefine_line|#define INIT_TSS  { &bslash;&n;&t;0,0, &bslash;&n;&t;sizeof(init_kernel_stack) + (long) &amp;init_kernel_stack, &bslash;&n;&t;KERNEL_DS, 0, &bslash;&n;&t;0,0,0,0,0,0, &bslash;&n;&t;(long) &amp;swapper_pg_dir, &bslash;&n;&t;0,0,0,0,0,0,0,0,0,0, &bslash;&n;&t;USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0,USER_DS,0, &bslash;&n;&t;_LDT(0),0, &bslash;&n;&t;0, 0x8000, &bslash;&n;&t;{~0, }, /* ioperm */ &bslash;&n;&t;_TSS(0), 0, 0,0, &bslash;&n;&t;{ { 0, }, },  /* 387 state */ &bslash;&n;&t;NULL, 0, 0, 0, 0 /* vm86_info */ &bslash;&n;}
DECL|function|start_thread
r_static
r_inline
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|eip
comma
r_int
r_int
id|esp
)paren
(brace
id|regs-&gt;cs
op_assign
id|USER_CS
suffix:semicolon
id|regs-&gt;ds
op_assign
id|regs-&gt;es
op_assign
id|regs-&gt;ss
op_assign
id|regs-&gt;fs
op_assign
id|regs-&gt;gs
op_assign
id|USER_DS
suffix:semicolon
id|regs-&gt;eip
op_assign
id|eip
suffix:semicolon
id|regs-&gt;esp
op_assign
id|esp
suffix:semicolon
)brace
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
macro_line|#endif /* __ASM_I386_PROCESSOR_H */
eof