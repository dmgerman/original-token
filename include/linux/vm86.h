macro_line|#ifndef _LINUX_VM86_H
DECL|macro|_LINUX_VM86_H
mdefine_line|#define _LINUX_VM86_H
multiline_comment|/*&n; * I&squot;m guessing at the VIF/VIP flag usage, but hope that this is how&n; * the Pentium uses them. Linux will return from vm86 mode when both&n; * VIF and VIP is set.&n; *&n; * On a Pentium, we could probably optimize the virtual flags directly&n; * in the eflags register instead of doing it &quot;by hand&quot; in vflags...&n; *&n; * Linus&n; */
DECL|macro|TF_MASK
mdefine_line|#define TF_MASK&t;&t;0x00000100
DECL|macro|IF_MASK
mdefine_line|#define IF_MASK&t;&t;0x00000200
DECL|macro|IOPL_MASK
mdefine_line|#define IOPL_MASK&t;0x00003000
DECL|macro|NT_MASK
mdefine_line|#define NT_MASK&t;&t;0x00004000
DECL|macro|VM_MASK
mdefine_line|#define VM_MASK&t;&t;0x00020000
DECL|macro|AC_MASK
mdefine_line|#define AC_MASK&t;&t;0x00040000
DECL|macro|VIF_MASK
mdefine_line|#define VIF_MASK&t;0x00080000&t;/* virtual interrupt flag */
DECL|macro|VIP_MASK
mdefine_line|#define VIP_MASK&t;0x00100000&t;/* virtual interrupt pending */
DECL|macro|ID_MASK
mdefine_line|#define ID_MASK&t;&t;0x00200000
DECL|macro|BIOSSEG
mdefine_line|#define BIOSSEG&t;&t;0x0f000
DECL|macro|CPU_086
mdefine_line|#define CPU_086&t;&t;0
DECL|macro|CPU_186
mdefine_line|#define CPU_186&t;&t;1
DECL|macro|CPU_286
mdefine_line|#define CPU_286&t;&t;2
DECL|macro|CPU_386
mdefine_line|#define CPU_386&t;&t;3
DECL|macro|CPU_486
mdefine_line|#define CPU_486&t;&t;4
DECL|macro|CPU_586
mdefine_line|#define CPU_586&t;&t;5
multiline_comment|/*&n; * Return values for the &squot;vm86()&squot; system call&n; */
DECL|macro|VM86_TYPE
mdefine_line|#define VM86_TYPE(retval)&t;((retval) &amp; 0xff)
DECL|macro|VM86_ARG
mdefine_line|#define VM86_ARG(retval)&t;((retval) &gt;&gt; 8)
DECL|macro|VM86_SIGNAL
mdefine_line|#define VM86_SIGNAL&t;0&t;/* return due to signal */
DECL|macro|VM86_UNKNOWN
mdefine_line|#define VM86_UNKNOWN&t;1&t;/* unhandled GP fault - IO-instruction or similar */
DECL|macro|VM86_INTx
mdefine_line|#define VM86_INTx&t;2&t;/* int3/int x instruction (ARG = x) */
DECL|macro|VM86_STI
mdefine_line|#define VM86_STI&t;3&t;/* sti/popfl instruction enabled virtual interrupts */
multiline_comment|/*&n; * This is the stack-layout when we have done a &quot;SAVE_ALL&quot; from vm86&n; * mode - the main change is that the old segment descriptors aren&squot;t&n; * useful any more and are forced to be zero by the kernel (and the&n; * hardware when a trap occurs), and the real segment descriptors are&n; * at the end of the structure. Look at ptrace.h to see the &quot;normal&quot;&n; * setup.&n; */
DECL|struct|vm86_regs
r_struct
id|vm86_regs
(brace
multiline_comment|/*&n; * normal regs, with special meaning for the segment descriptors..&n; */
DECL|member|ebx
r_int
id|ebx
suffix:semicolon
DECL|member|ecx
r_int
id|ecx
suffix:semicolon
DECL|member|edx
r_int
id|edx
suffix:semicolon
DECL|member|esi
r_int
id|esi
suffix:semicolon
DECL|member|edi
r_int
id|edi
suffix:semicolon
DECL|member|ebp
r_int
id|ebp
suffix:semicolon
DECL|member|eax
r_int
id|eax
suffix:semicolon
DECL|member|__null_ds
r_int
id|__null_ds
suffix:semicolon
DECL|member|__null_es
r_int
id|__null_es
suffix:semicolon
DECL|member|__null_fs
r_int
id|__null_fs
suffix:semicolon
DECL|member|__null_gs
r_int
id|__null_gs
suffix:semicolon
DECL|member|orig_eax
r_int
id|orig_eax
suffix:semicolon
DECL|member|eip
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
id|eflags
suffix:semicolon
DECL|member|esp
r_int
id|esp
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
multiline_comment|/*&n; * these are specific to v86 mode:&n; */
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
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
)brace
suffix:semicolon
DECL|struct|revectored_struct
r_struct
id|revectored_struct
(brace
DECL|member|__map
r_int
r_int
id|__map
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* 256 bits */
)brace
suffix:semicolon
DECL|struct|vm86_struct
r_struct
id|vm86_struct
(brace
DECL|member|regs
r_struct
id|vm86_regs
id|regs
suffix:semicolon
DECL|member|flags
r_int
r_int
id|flags
suffix:semicolon
DECL|member|screen_bitmap
r_int
r_int
id|screen_bitmap
suffix:semicolon
DECL|member|cpu_type
r_int
r_int
id|cpu_type
suffix:semicolon
DECL|member|int_revectored
r_struct
id|revectored_struct
id|int_revectored
suffix:semicolon
DECL|member|int21_revectored
r_struct
id|revectored_struct
id|int21_revectored
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * flags masks&n; */
DECL|macro|VM86_SCREEN_BITMAP
mdefine_line|#define VM86_SCREEN_BITMAP&t;0x0001
macro_line|#ifdef __KERNEL__
r_void
id|handle_vm86_fault
c_func
(paren
r_struct
id|vm86_regs
op_star
comma
r_int
)paren
suffix:semicolon
DECL|function|is_revectored
r_extern
r_inline
r_int
id|is_revectored
c_func
(paren
r_int
id|nr
comma
r_struct
id|revectored_struct
op_star
id|bitmap
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;btl %2,%%fs:%1&bslash;n&bslash;tsbbl %0,%0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|nr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
op_star
id|bitmap
)paren
comma
l_string|&quot;r&quot;
(paren
id|nr
)paren
)paren
suffix:semicolon
r_return
id|nr
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif
eof
