macro_line|#ifndef __ASM_ARM_SYSTEM_H
DECL|macro|__ASM_ARM_SYSTEM_H
mdefine_line|#define __ASM_ARM_SYSTEM_H
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__ebsa285_data
mdefine_line|#define __ebsa285_data&t;&t;__attribute__((__section__(&quot;.data.ebsa285&quot;)))
DECL|macro|__netwinder_data
mdefine_line|#define __netwinder_data&t;__attribute__((__section__(&quot;.data.netwinder&quot;)))
macro_line|#ifdef CONFIG_TEXT_SECTIONS
DECL|macro|__ebsa285_text
mdefine_line|#define __ebsa285_text&t;&t;__attribute__((__section__(&quot;.text.ebsa285&quot;)))
DECL|macro|__netwinder_text
mdefine_line|#define __netwinder_text&t;__attribute__((__section__(&quot;.text.netwinder&quot;)))
macro_line|#else
DECL|macro|__ebsa285_text
mdefine_line|#define __ebsa285_text
DECL|macro|__netwinder_text
mdefine_line|#define __netwinder_text
macro_line|#endif
multiline_comment|/* The type of machine we&squot;re running on */
r_extern
r_int
r_int
id|__machine_arch_type
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
DECL|macro|MACH_TYPE_CO285
mdefine_line|#define MACH_TYPE_CO285&t;&t;8
DECL|macro|MACH_TYPE_CLPS7110
mdefine_line|#define MACH_TYPE_CLPS7110&t;9
DECL|macro|MACH_TYPE_ARCHIMEDES
mdefine_line|#define MACH_TYPE_ARCHIMEDES&t;10
DECL|macro|MACH_TYPE_A5K
mdefine_line|#define MACH_TYPE_A5K&t;&t;11
multiline_comment|/*&n; * Sort out a definition for machine_arch_type&n; * The rules are:&n; * 1. If one architecture is selected, then all machine_is_xxx()&n; *    are constant.&n; * 2. If two or more architectures are selected, then the selected&n; *    machine_is_xxx() are variable, and the unselected machine_is_xxx()&n; *    are constant zero.&n; */
macro_line|#ifdef CONFIG_ARCH_EBSA110
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_EBSA110
macro_line|# endif
DECL|macro|machine_is_ebsa110
macro_line|# define machine_is_ebsa110()&t;(machine_arch_type == MACH_TYPE_EBSA110)
macro_line|#else
DECL|macro|machine_is_ebsa110
macro_line|# define machine_is_ebsa110()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_RPC
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_RISCPC
macro_line|# endif
DECL|macro|machine_is_riscpc
macro_line|# define machine_is_riscpc()&t;(machine_arch_type == MACH_TYPE_RISCPC)
macro_line|#else
DECL|macro|machine_is_riscpc
macro_line|# define machine_is_riscpc()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_EBSA285
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_EBSA285
macro_line|# endif
DECL|macro|machine_is_ebsa285
macro_line|# define machine_is_ebsa285()&t;(machine_arch_type == MACH_TYPE_EBSA285)
macro_line|#else
DECL|macro|machine_is_ebsa285
macro_line|# define machine_is_ebsa285()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_NETWINDER
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_NETWINDER
macro_line|# endif
DECL|macro|machine_is_netwinder
macro_line|# define machine_is_netwinder()&t;(machine_arch_type == MACH_TYPE_NETWINDER)
macro_line|#else
DECL|macro|machine_is_netwinder
macro_line|# define machine_is_netwinder()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_CATS
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_CATS
macro_line|# endif
DECL|macro|machine_is_cats
macro_line|# define machine_is_cats()&t;(machine_arch_type == MACH_TYPE_CATS)
macro_line|#else
DECL|macro|machine_is_cats
macro_line|# define machine_is_cats()&t;(0)
macro_line|#endif
macro_line|#ifdef CONFIG_ARCH_CO285
macro_line|# ifdef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  undef machine_arch_type
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;__machine_arch_type
macro_line|# else
DECL|macro|machine_arch_type
macro_line|#  define machine_arch_type&t;MACH_TYPE_CO285
macro_line|# endif
DECL|macro|machine_is_co285
macro_line|# define machine_is_co285()&t;(machine_arch_type == MACH_TYPE_CO285)
macro_line|#else
DECL|macro|machine_is_co285
macro_line|# define machine_is_co285()&t;(0)
macro_line|#endif
macro_line|#ifndef machine_arch_type
DECL|macro|machine_arch_type
mdefine_line|#define machine_arch_type&t;__machine_arch_type
macro_line|#endif
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|macro|xchg
mdefine_line|#define xchg(ptr,x) &bslash;&n;&t;((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
DECL|macro|tas
mdefine_line|#define tas(ptr) (xchg((ptr),1))
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
r_extern
id|asmlinkage
r_void
id|__backtrace
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Include processor dependent parts&n; */
macro_line|#include &lt;asm/proc/system.h&gt;
macro_line|#include &lt;asm/arch/system.h&gt;
DECL|macro|mb
mdefine_line|#define mb() __asm__ __volatile__ (&quot;&quot; : : : &quot;memory&quot;)
DECL|macro|rmb
mdefine_line|#define rmb() mb()
DECL|macro|wmb
mdefine_line|#define wmb() mb()
DECL|macro|nop
mdefine_line|#define nop() __asm__ __volatile__(&quot;mov&bslash;tr0,r0&bslash;t@ nop&bslash;n&bslash;t&quot;);
multiline_comment|/*&n; * switch_to(prev, next) should switch from task `prev&squot; to `next&squot;&n; * `prev&squot; will never be the same as `next&squot;.&n; * The `mb&squot; is to tell GCC not to cache `current&squot; across this call.&n; */
DECL|macro|switch_to
mdefine_line|#define switch_to(prev,next,last)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t; &t;&t;&t;&bslash;&n;&t;&t;last = processor._switch_to(prev,next);&t;&bslash;&n;&t;&t;mb();&t;&t;&t;&t;&t;&bslash;&n;&t;} while (0)
macro_line|#endif
macro_line|#endif
eof
