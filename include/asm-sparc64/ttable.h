multiline_comment|/* $Id: ttable.h,v 1.3 1997/08/29 15:52:35 jj Exp $ */
macro_line|#ifndef _SPARC64_TTABLE_H
DECL|macro|_SPARC64_TTABLE_H
mdefine_line|#define _SPARC64_TTABLE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|BOOT_KERNEL
mdefine_line|#define BOOT_KERNEL b sparc64_boot; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* We need a &quot;cleaned&quot; instruction... */
DECL|macro|CLEAN_WINDOW
mdefine_line|#define CLEAN_WINDOW&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;rdpr&t;%cleanwin, %l0;&t;&t;add&t;%l0, 1, %l0;&t;&t;&bslash;&n;&t;wrpr&t;%l0, 0x0, %cleanwin;&t;&t;&t;&t;&t;&bslash;&n;&t;clr&t;%o0;&t;clr&t;%o1;&t;clr&t;%o2;&t;clr&t;%o3;&t;&bslash;&n;&t;clr&t;%o4;&t;clr&t;%o5;&t;clr&t;%o6;&t;clr&t;%o7;&t;&bslash;&n;&t;clr&t;%l0;&t;clr&t;%l1;&t;clr&t;%l2;&t;clr&t;%l3;&t;&bslash;&n;&t;clr&t;%l4;&t;clr&t;%l5;&t;clr&t;%l6;&t;clr&t;%l7;&t;&bslash;&n;&t;retry;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;nop;
DECL|macro|TRAP
mdefine_line|#define TRAP(routine)&t;&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_NOSAVE
mdefine_line|#define TRAP_NOSAVE(routine)&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, routine;&t;&t;&t;&t;&bslash;&n;&t; nop;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop;
DECL|macro|TRAPTL1
mdefine_line|#define TRAPTL1(routine)&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etraptl1;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_ARG
mdefine_line|#define TRAP_ARG(routine, arg)&t;&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; mov&t;arg, %o1;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|TRAPTL1_ARG
mdefine_line|#define TRAPTL1_ARG(routine, arg)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etraptl1;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; mov&t;arg, %o1;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|SYSCALL_TRAP
mdefine_line|#define SYSCALL_TRAP(routine, systbl)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; sethi&t;%hi(systbl), %l7;&t;&t;&t;&bslash;&n;&t;nop; nop; nop;
DECL|macro|ACCESS_EXCEPTION_TRAP
mdefine_line|#define ACCESS_EXCEPTION_TRAP(routine)&t;&t;&t;&bslash;&n;&t;rdpr&t;%pstate, %g1;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g1, PSTATE_MG|PSTATE_AG, %pstate;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|ACCESS_EXCEPTION_TRAPTL1
mdefine_line|#define ACCESS_EXCEPTION_TRAPTL1(routine)&t;&t;&bslash;&n;&t;rdpr&t;%pstate, %g1;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g1, PSTATE_MG|PSTATE_AG, %pstate;&t;&bslash;&n;&t;ba,pt&t;%xcc, etraptl1;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
DECL|macro|INDIRECT_SOLARIS_SYSCALL
mdefine_line|#define INDIRECT_SOLARIS_SYSCALL(num)&t;&t;&t;&bslash;&n;&t;sethi&t;%hi(109f), %g7;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&bslash;&n;109:&t; or&t;%g7, %lo(109b), %g7;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, tl0_solaris + 0xc;&t;&t;&bslash;&n;&t; mov&t;num, %g1;&t;&t;&t;&t;&bslash;&n;&t;nop;nop;nop;
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall, sunos_sys_table)
DECL|macro|LINUX_32BIT_SYSCALL_TRAP
mdefine_line|#define&t;LINUX_32BIT_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall, sys_call_table32)
DECL|macro|LINUX_64BIT_SYSCALL_TRAP
mdefine_line|#define LINUX_64BIT_SYSCALL_TRAP SYSCALL_TRAP(linux_sparc_syscall, sys_call_table64)
DECL|macro|GETCC_TRAP
mdefine_line|#define GETCC_TRAP TRAP(getcc)
DECL|macro|SETCC_TRAP
mdefine_line|#define SETCC_TRAP TRAP(setcc)
macro_line|#ifdef CONFIG_SOLARIS_EMUL
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP TRAP(solaris_sparc_syscall)
macro_line|#else
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP TRAP(solaris_syscall)
macro_line|#endif
multiline_comment|/* FIXME: Write these actually */
DECL|macro|NETBSD_SYSCALL_TRAP
mdefine_line|#define NETBSD_SYSCALL_TRAP TRAP(netbsd_syscall)
DECL|macro|BREAKPOINT_TRAP
mdefine_line|#define BREAKPOINT_TRAP TRAP(breakpoint_trap)
DECL|macro|TRAP_IRQ
mdefine_line|#define TRAP_IRQ(routine, level)&t;&t;&t;&bslash;&n;&t;rdpr&t;%pil, %g2;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g0, 15, %pil;&t;&t;&t;&t;&bslash;&n;&t;b,pt&t;%xcc, etrap_irq;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;mov&t;level, %o0;&t;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o1;&t;&bslash;&n;&t;ba,a,pt&t;%xcc, rtrap_clr_l6;
macro_line|#ifdef __SMP__
DECL|macro|TRAP_TICK
mdefine_line|#define TRAP_TICK&t;&t;&t;&t;&t;&bslash;&n;&t;rdpr&t;%pil, %g2;&t;&t;&t;&t;&bslash;&n;&t;wrpr&t;%g0, 15, %pil;&t;&t;&t;&t;&bslash;&n;&t;b,pt&t;%xcc, etrap_irq;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;call&t;smp_percpu_timer_interrupt;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;b,pt&t;%xcc, rtrap;&t;&t;&t;&t;&bslash;&n;&t; clr&t;%l6;
macro_line|#else
DECL|macro|TRAP_TICK
mdefine_line|#define TRAP_TICK&t;TRAP_IRQ(handler_irq, 14)
macro_line|#endif
DECL|macro|TRAP_IVEC
mdefine_line|#define TRAP_IVEC TRAP_NOSAVE(do_ivec)
DECL|macro|BTRAP
mdefine_line|#define BTRAP(lvl) TRAP_ARG(bad_trap, lvl)
DECL|macro|BTRAPTL1
mdefine_line|#define BTRAPTL1(lvl) TRAPTL1_ARG(bad_trap_tl1, lvl)
DECL|macro|FLUSH_WINDOW_TRAP
mdefine_line|#define FLUSH_WINDOW_TRAP&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ba,pt&t;%xcc, etrap;&t;&t;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;flushw;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TNPC], %l1;&t;&bslash;&n;&t;add&t;%l1, 4, %l2;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;stx&t;%l1, [%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TPC];&t;&bslash;&n;&t;ba,pt&t;%xcc, rtrap_clr_l6;&t;&t;&t;&t;&t;&bslash;&n;&t; stx&t;%l2, [%sp + STACK_BIAS + REGWIN_SZ + PT_V9_TNPC];
multiline_comment|/* Before touching these macros, you owe it to yourself to go and&n; * see how arch/sparc64/kernel/winfixup.S works... -DaveM&n; */
multiline_comment|/* Normal kernel spill */
DECL|macro|SPILL_0_NORMAL
mdefine_line|#define SPILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;stx&t;%l0, [%sp + STACK_BIAS + 0x00];&t;&t;&bslash;&n;&t;stx&t;%l1, [%sp + STACK_BIAS + 0x08];&t;&t;&bslash;&n;&t;stx&t;%l2, [%sp + STACK_BIAS + 0x10];&t;&t;&bslash;&n;&t;stx&t;%l3, [%sp + STACK_BIAS + 0x18];&t;&t;&bslash;&n;&t;stx&t;%l4, [%sp + STACK_BIAS + 0x20];&t;&t;&bslash;&n;&t;stx&t;%l5, [%sp + STACK_BIAS + 0x28];&t;&t;&bslash;&n;&t;stx&t;%l6, [%sp + STACK_BIAS + 0x30];&t;&t;&bslash;&n;&t;stx&t;%l7, [%sp + STACK_BIAS + 0x38];&t;&t;&bslash;&n;&t;stx&t;%i0, [%sp + STACK_BIAS + 0x40];&t;&t;&bslash;&n;&t;stx&t;%i1, [%sp + STACK_BIAS + 0x48];&t;&t;&bslash;&n;&t;stx&t;%i2, [%sp + STACK_BIAS + 0x50];&t;&t;&bslash;&n;&t;stx&t;%i3, [%sp + STACK_BIAS + 0x58];&t;&t;&bslash;&n;&t;stx&t;%i4, [%sp + STACK_BIAS + 0x60];&t;&t;&bslash;&n;&t;stx&t;%i5, [%sp + STACK_BIAS + 0x68];&t;&t;&bslash;&n;&t;stx&t;%i6, [%sp + STACK_BIAS + 0x70];&t;&t;&bslash;&n;&t;stx&t;%i7, [%sp + STACK_BIAS + 0x78];&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit spill */
DECL|macro|SPILL_1_GENERIC
mdefine_line|#define SPILL_1_GENERIC(xxx)&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, xxx, %asi;&t;&t;&t;&t;&bslash;&n;&t;stxa&t;%l0, [%sp + STACK_BIAS + 0x00] %asi;&t;&bslash;&n;&t;stxa&t;%l1, [%sp + STACK_BIAS + 0x08] %asi;&t;&bslash;&n;&t;stxa&t;%l2, [%sp + STACK_BIAS + 0x10] %asi;&t;&bslash;&n;&t;stxa&t;%l3, [%sp + STACK_BIAS + 0x18] %asi;&t;&bslash;&n;&t;stxa&t;%l4, [%sp + STACK_BIAS + 0x20] %asi;&t;&bslash;&n;&t;stxa&t;%l5, [%sp + STACK_BIAS + 0x28] %asi;&t;&bslash;&n;&t;stxa&t;%l6, [%sp + STACK_BIAS + 0x30] %asi;&t;&bslash;&n;&t;stxa&t;%l7, [%sp + STACK_BIAS + 0x38] %asi;&t;&bslash;&n;&t;stxa&t;%i0, [%sp + STACK_BIAS + 0x40] %asi;&t;&bslash;&n;&t;stxa&t;%i1, [%sp + STACK_BIAS + 0x48] %asi;&t;&bslash;&n;&t;stxa&t;%i2, [%sp + STACK_BIAS + 0x50] %asi;&t;&bslash;&n;&t;stxa&t;%i3, [%sp + STACK_BIAS + 0x58] %asi;&t;&bslash;&n;&t;stxa&t;%i4, [%sp + STACK_BIAS + 0x60] %asi;&t;&bslash;&n;&t;stxa&t;%i5, [%sp + STACK_BIAS + 0x68] %asi;&t;&bslash;&n;&t;stxa&t;%i6, [%sp + STACK_BIAS + 0x70] %asi;&t;&bslash;&n;&t;stxa&t;%i7, [%sp + STACK_BIAS + 0x78] %asi;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup;
multiline_comment|/* Normal 32bit spill */
DECL|macro|SPILL_2_GENERIC
mdefine_line|#define SPILL_2_GENERIC(xxx)&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, xxx, %asi;&t;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;stwa&t;%l0, [%sp + 0x00] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l1, [%sp + 0x04] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l2, [%sp + 0x08] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l3, [%sp + 0x0c] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l4, [%sp + 0x10] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l5, [%sp + 0x14] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l6, [%sp + 0x18] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%l7, [%sp + 0x1c] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i0, [%sp + 0x20] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i1, [%sp + 0x24] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i2, [%sp + 0x28] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i3, [%sp + 0x2c] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i4, [%sp + 0x30] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i5, [%sp + 0x34] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i6, [%sp + 0x38] %asi;&t;&t;&t;&bslash;&n;&t;stwa&t;%i7, [%sp + 0x3c] %asi;&t;&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, spill_fixup;
DECL|macro|SPILL_1_NORMAL
mdefine_line|#define SPILL_1_NORMAL SPILL_1_GENERIC(ASI_AIUP)
DECL|macro|SPILL_2_NORMAL
mdefine_line|#define SPILL_2_NORMAL SPILL_2_GENERIC(ASI_AIUP)
DECL|macro|SPILL_3_NORMAL
mdefine_line|#define SPILL_3_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_4_NORMAL
mdefine_line|#define SPILL_4_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_5_NORMAL
mdefine_line|#define SPILL_5_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_6_NORMAL
mdefine_line|#define SPILL_6_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_7_NORMAL
mdefine_line|#define SPILL_7_NORMAL SPILL_0_NORMAL
DECL|macro|SPILL_0_OTHER
mdefine_line|#define SPILL_0_OTHER SPILL_0_NORMAL
DECL|macro|SPILL_1_OTHER
mdefine_line|#define SPILL_1_OTHER SPILL_1_GENERIC(ASI_AIUS)
DECL|macro|SPILL_2_OTHER
mdefine_line|#define SPILL_2_OTHER SPILL_2_GENERIC(ASI_AIUS)
DECL|macro|SPILL_3_OTHER
mdefine_line|#define SPILL_3_OTHER SPILL_3_NORMAL
DECL|macro|SPILL_4_OTHER
mdefine_line|#define SPILL_4_OTHER SPILL_4_NORMAL
DECL|macro|SPILL_5_OTHER
mdefine_line|#define SPILL_5_OTHER SPILL_5_NORMAL
DECL|macro|SPILL_6_OTHER
mdefine_line|#define SPILL_6_OTHER SPILL_6_NORMAL
DECL|macro|SPILL_7_OTHER
mdefine_line|#define SPILL_7_OTHER SPILL_7_NORMAL
multiline_comment|/* Normal kernel fill */
DECL|macro|FILL_0_NORMAL
mdefine_line|#define FILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x00], %l0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x08], %l1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x10], %l2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x18], %l3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x20], %l4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x28], %l5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x30], %l6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x38], %l7;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x40], %i0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x48], %i1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x50], %i2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x58], %i3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x60], %i4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x68], %i5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x70], %i6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x78], %i7;&t;&t;&bslash;&n;&t;restored; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit fill */
DECL|macro|FILL_1_GENERIC
mdefine_line|#define FILL_1_GENERIC(xxx)&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, xxx, %asi;&t;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x00] %asi, %l0;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x08] %asi, %l1;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x10] %asi, %l2;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x18] %asi, %l3;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x20] %asi, %l4;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x28] %asi, %l5;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x30] %asi, %l6;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x38] %asi, %l7;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x40] %asi, %i0;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x48] %asi, %i1;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x50] %asi, %i2;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x58] %asi, %i3;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x60] %asi, %i4;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x68] %asi, %i5;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x70] %asi, %i6;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x78] %asi, %i7;&t;&bslash;&n;&t;restored; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup;
multiline_comment|/* Normal 32bit fill */
DECL|macro|FILL_2_GENERIC
mdefine_line|#define FILL_2_GENERIC(xxx)&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, xxx, %asi;&t;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x00] %asi, %l0;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x04] %asi, %l1;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x08] %asi, %l2;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x0c] %asi, %l3;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x10] %asi, %l4;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x14] %asi, %l5;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x18] %asi, %l6;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x1c] %asi, %l7;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x20] %asi, %i0;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x24] %asi, %i1;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x28] %asi, %i2;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x2c] %asi, %i3;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x30] %asi, %i4;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x34] %asi, %i5;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x38] %asi, %i6;&t;&t;&t;&bslash;&n;&t;lduwa&t;[%sp + 0x3c] %asi, %i7;&t;&t;&t;&bslash;&n;&t;restored; retry; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup_mna;&t;&t;&t;&bslash;&n;&t;b,a,pt&t;%xcc, fill_fixup;
DECL|macro|FILL_1_NORMAL
mdefine_line|#define FILL_1_NORMAL FILL_1_GENERIC(ASI_AIUP)
DECL|macro|FILL_2_NORMAL
mdefine_line|#define FILL_2_NORMAL FILL_2_GENERIC(ASI_AIUP)
DECL|macro|FILL_3_NORMAL
mdefine_line|#define FILL_3_NORMAL FILL_0_NORMAL
DECL|macro|FILL_4_NORMAL
mdefine_line|#define FILL_4_NORMAL FILL_0_NORMAL
DECL|macro|FILL_5_NORMAL
mdefine_line|#define FILL_5_NORMAL FILL_0_NORMAL
DECL|macro|FILL_6_NORMAL
mdefine_line|#define FILL_6_NORMAL FILL_0_NORMAL
DECL|macro|FILL_7_NORMAL
mdefine_line|#define FILL_7_NORMAL FILL_0_NORMAL
DECL|macro|FILL_0_OTHER
mdefine_line|#define FILL_0_OTHER FILL_0_NORMAL
DECL|macro|FILL_1_OTHER
mdefine_line|#define FILL_1_OTHER FILL_1_GENERIC(ASI_AIUS)
DECL|macro|FILL_2_OTHER
mdefine_line|#define FILL_2_OTHER FILL_2_GENERIC(ASI_AIUS)
DECL|macro|FILL_3_OTHER
mdefine_line|#define FILL_3_OTHER FILL_3_NORMAL
DECL|macro|FILL_4_OTHER
mdefine_line|#define FILL_4_OTHER FILL_4_NORMAL
DECL|macro|FILL_5_OTHER
mdefine_line|#define FILL_5_OTHER FILL_5_NORMAL
DECL|macro|FILL_6_OTHER
mdefine_line|#define FILL_6_OTHER FILL_6_NORMAL
DECL|macro|FILL_7_OTHER
mdefine_line|#define FILL_7_OTHER FILL_7_NORMAL
macro_line|#endif /* !(_SPARC64_TTABLE_H) */
eof