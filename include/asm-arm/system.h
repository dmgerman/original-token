macro_line|#ifndef __ASM_ARM_SYSTEM_H
DECL|macro|__ASM_ARM_SYSTEM_H
mdefine_line|#define __ASM_ARM_SYSTEM_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* The type of machine we&squot;re running on */
r_extern
r_int
r_int
id|machine_type
suffix:semicolon
DECL|macro|MACH_TYPE_EBSA110
mdefine_line|#define MACH_TYPE_EBSA110&t;0
DECL|macro|MACH_TYPE_RISCPC
mdefine_line|#define MACH_TYPE_RISCPC&t;1
DECL|macro|MACH_TYPE_NEXUSPCI
mdefine_line|#define MACH_TYPE_NEXUSPCI&t;3
DECL|macro|MACH_TYPE_EBSA285
mdefine_line|#define MACH_TYPE_EBSA285&t;4
DECL|macro|MACH_TYPE_NETWINDER
mdefine_line|#define MACH_TYPE_NETWINDER&t;5
DECL|macro|MACH_TYPE_CATS
mdefine_line|#define MACH_TYPE_CATS&t;&t;6
DECL|macro|MACH_TYPE_TBOX
mdefine_line|#define MACH_TYPE_TBOX&t;&t;7
macro_line|#ifdef CONFIG_ARCH_EBSA285
DECL|macro|machine_is_ebsa285
mdefine_line|#define machine_is_ebsa285()&t;(1)
macro_line|#else
DECL|macro|machine_is_ebsa285
mdefine_line|#define machine_is_ebsa285()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_VNC
DECL|macro|machine_is_netwinder
mdefine_line|#define machine_is_netwinder()&t;(1)
macro_line|#else
DECL|macro|machine_is_netwinder
mdefine_line|#define machine_is_netwinder()&t;(0)
macro_line|#endif
macro_line|#if defined(CONFIG_CATS)
DECL|macro|machine_is_cats
mdefine_line|#define machine_is_cats()&t;(machine_type == MACH_TYPE_CATS)
macro_line|#else
DECL|macro|machine_is_cats
mdefine_line|#define machine_is_cats()&t;(0)
macro_line|#endif
macro_line|#if 0
mdefine_line|#define machine_is_ebsa285()&t;(machine_type == MACH_TYPE_EBSA285)
mdefine_line|#define machine_is_netwinder()&t;(machine_type == MACH_TYPE_NETWINDER)
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
r_extern
r_void
id|arm_malalignedptr
c_func
(paren
r_const
r_char
op_star
comma
r_void
op_star
comma
r_volatile
r_void
op_star
)paren
suffix:semicolon
r_extern
r_void
id|arm_invalidptr
c_func
(paren
r_const
r_char
op_star
comma
r_int
)paren
suffix:semicolon
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;&t;((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; *&n; * `next&squot; and `prev&squot; should be struct task_struct, but it isn&squot;t always defined&n; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next) processor._switch_to(prev,next)
multiline_comment|/*&n; * Include processor dependent parts&n; */
macro_line|#include &lt;asm/proc/system.h&gt;
macro_line|#include &lt;asm/arch/system.h&gt;
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__ (&quot;&quot; : : : &quot;memory&quot;)
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__(&quot;mov r0,r0&bslash;n&bslash;t&quot;);
r_extern
id|asmlinkage
r_void
id|__backtrace
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
eof
