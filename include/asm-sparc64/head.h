multiline_comment|/* $Id: head.h,v 1.4 1997/02/25 20:00:32 jj Exp $ */
macro_line|#ifndef _SPARC64_HEAD_H
DECL|macro|_SPARC64_HEAD_H
mdefine_line|#define _SPARC64_HEAD_H
DECL|macro|BOOT_KERNEL
mdefine_line|#define BOOT_KERNEL b sparc64_boot; nop; nop; nop; nop; nop; nop; nop;
DECL|macro|CLEAN_WINDOW
mdefine_line|#define CLEAN_WINDOW&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clr&t;%o0;&t;clr&t;%o1;&t;clr&t;%o2;&t;clr&t;%o3;&t;&bslash;&n;&t;clr&t;%o4;&t;clr&t;%o5;&t;clr&t;%o6;&t;clr&t;%o7;&t;&bslash;&n;&t;clr&t;%l0;&t;clr&t;%l1;&t;clr&t;%l2;&t;clr&t;%l3;&t;&bslash;&n;&t;clr&t;%l4;&t;clr&t;%l5;&t;clr&t;%l6;&t;clr&t;%l7;&t;&bslash;&n;&t;rdpr %cleanwin, %g1; &t;&t;add %g1, 1, %g1;&t;&t;&bslash;&n;&t;wrpr %g1, 0x0, %cleanwin;&t;retry;&t;&t;&t;&t;&bslash;&n;&t;nop;&t;&t;nop;&t;&t;nop;&t;&t;nop;
DECL|macro|TRAP
mdefine_line|#define TRAP(routine)&t;&t;&t;&t;&t;&bslash;&n;&t;b&t;etrap;&t;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;b&t;rtrap;&t;&t;&t;&t;&t;&bslash;&n;&t; subcc&t;%g0, %o0, %g0;&t;&t;&t;&t;&bslash;&n;&t;nop;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;nop;
DECL|macro|TRAP_ARG
mdefine_line|#define TRAP_ARG(routine, arg)&t;&t;&t;&t;&bslash;&n;&t;b&t;etrap;&t;&t;&t;&t;&t;&bslash;&n;&t; rd&t;%pc, %g7;&t;&t;&t;&t;&bslash;&n;&t;add&t;%sp, STACK_BIAS + REGWIN_SZ, %o0;&t;&bslash;&n;&t;call&t;routine;&t;&t;&t;&t;&bslash;&n;&t; mov&t;arg, %o1;&t;&t;&t;&t;&bslash;&n;&t;b&t;rtrap;&t;&t;&t;&t;&t;&bslash;&n;&t; subcc&t;%g0, %o0, %g0;&t;&t;&t;&t;&bslash;&n;&t;nop;
multiline_comment|/* FIXME: Write these actually */
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP TRAP(sunos_syscall)
DECL|macro|LINUX_32BIT_SYSCALL_TRAP
mdefine_line|#define&t;LINUX_32BIT_SYSCALL_TRAP TRAP(linux32_syscall)
DECL|macro|LINUX_64BIT_SYSCALL_TRAP
mdefine_line|#define LINUX_64BIT_SYSCALL_TRAP TRAP(linux64_syscall)
DECL|macro|NETBSD_SYSCALL_TRAP
mdefine_line|#define NETBSD_SYSCALL_TRAP TRAP(netbsd_syscall)
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP TRAP(solaris_syscall)
DECL|macro|BREAKPOINT_TRAP
mdefine_line|#define BREAKPOINT_TRAP TRAP(breakpoint_trap)
DECL|macro|GETCC_TRAP
mdefine_line|#define GETCC_TRAP TRAP(getcc)
DECL|macro|SETCC_TRAP
mdefine_line|#define SETCC_TRAP TRAP(setcc)
DECL|macro|INDIRECT_SOLARIS_SYSCALL
mdefine_line|#define INDIRECT_SOLARIS_SYSCALL(tlvl) TRAP_ARG(indirect_syscall, tlvl)
DECL|macro|TRAP_IRQ
mdefine_line|#define TRAP_IRQ(routine, level) TRAP_ARG(routine, level)
DECL|macro|BTRAP
mdefine_line|#define BTRAP(lvl) TRAP_ARG(bad_trap, lvl)
DECL|macro|BTRAPTL1
mdefine_line|#define BTRAPTL1(lvl) TRAP_ARG(bad_trap_tl1, lvl)
DECL|macro|FLUSH_WINDOW_TRAP
mdefine_line|#define FLUSH_WINDOW_TRAP&t;&t;&t;&t;&t;&bslash;&n;&t;flushw;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;done; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal kernel spill */
DECL|macro|SPILL_0_NORMAL
mdefine_line|#define SPILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;stx&t;%l0, [%sp + STACK_BIAS + 0x00];&t;&t;&bslash;&n;&t;stx&t;%l1, [%sp + STACK_BIAS + 0x08];&t;&t;&bslash;&n;&t;stx&t;%l2, [%sp + STACK_BIAS + 0x10];&t;&t;&bslash;&n;&t;stx&t;%l3, [%sp + STACK_BIAS + 0x18];&t;&t;&bslash;&n;&t;stx&t;%l4, [%sp + STACK_BIAS + 0x20];&t;&t;&bslash;&n;&t;stx&t;%l5, [%sp + STACK_BIAS + 0x28];&t;&t;&bslash;&n;&t;stx&t;%l6, [%sp + STACK_BIAS + 0x30];&t;&t;&bslash;&n;&t;stx&t;%l7, [%sp + STACK_BIAS + 0x38];&t;&t;&bslash;&n;&t;stx&t;%i0, [%sp + STACK_BIAS + 0x40];&t;&t;&bslash;&n;&t;stx&t;%i1, [%sp + STACK_BIAS + 0x48];&t;&t;&bslash;&n;&t;stx&t;%i2, [%sp + STACK_BIAS + 0x50];&t;&t;&bslash;&n;&t;stx&t;%i3, [%sp + STACK_BIAS + 0x58];&t;&t;&bslash;&n;&t;stx&t;%i4, [%sp + STACK_BIAS + 0x60];&t;&t;&bslash;&n;&t;stx&t;%i5, [%sp + STACK_BIAS + 0x68];&t;&t;&bslash;&n;&t;stx&t;%i6, [%sp + STACK_BIAS + 0x70];&t;&t;&bslash;&n;&t;stx&t;%i7, [%sp + STACK_BIAS + 0x78];&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit spill */
DECL|macro|SPILL_1_NORMAL
mdefine_line|#define SPILL_1_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, ASI_AIUP, %asi;&t;&t;&t;&bslash;&n;&t;stxa&t;%l0, [%sp + STACK_BIAS + 0x00] %asi;&t;&bslash;&n;&t;stxa&t;%l1, [%sp + STACK_BIAS + 0x08] %asi;&t;&bslash;&n;&t;stxa&t;%l2, [%sp + STACK_BIAS + 0x10] %asi;&t;&bslash;&n;&t;stxa&t;%l3, [%sp + STACK_BIAS + 0x18] %asi;&t;&bslash;&n;&t;stxa&t;%l4, [%sp + STACK_BIAS + 0x20] %asi;&t;&bslash;&n;&t;stxa&t;%l5, [%sp + STACK_BIAS + 0x28] %asi;&t;&bslash;&n;&t;stxa&t;%l6, [%sp + STACK_BIAS + 0x30] %asi;&t;&bslash;&n;&t;stxa&t;%l7, [%sp + STACK_BIAS + 0x38] %asi;&t;&bslash;&n;&t;stxa&t;%i0, [%sp + STACK_BIAS + 0x40] %asi;&t;&bslash;&n;&t;stxa&t;%i1, [%sp + STACK_BIAS + 0x48] %asi;&t;&bslash;&n;&t;stxa&t;%i2, [%sp + STACK_BIAS + 0x50] %asi;&t;&bslash;&n;&t;stxa&t;%i3, [%sp + STACK_BIAS + 0x58] %asi;&t;&bslash;&n;&t;stxa&t;%i4, [%sp + STACK_BIAS + 0x60] %asi;&t;&bslash;&n;&t;stxa&t;%i5, [%sp + STACK_BIAS + 0x68] %asi;&t;&bslash;&n;&t;stxa&t;%i6, [%sp + STACK_BIAS + 0x70] %asi;&t;&bslash;&n;&t;stxa&t;%i7, [%sp + STACK_BIAS + 0x78] %asi;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 32bit spill */
DECL|macro|SPILL_2_NORMAL
mdefine_line|#define SPILL_2_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, ASI_AIUP, %asi;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;stda&t;%l0, [%sp + 0x00] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%l2, [%sp + 0x10] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%l4, [%sp + 0x20] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%l6, [%sp + 0x30] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%i0, [%sp + 0x40] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%i2, [%sp + 0x50] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%i4, [%sp + 0x60] %asi;&t;&t;&t;&bslash;&n;&t;stda&t;%i6, [%sp + 0x70] %asi;&t;&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
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
mdefine_line|#define SPILL_1_OTHER SPILL_1_NORMAL
DECL|macro|SPILL_2_OTHER
mdefine_line|#define SPILL_2_OTHER SPILL_2_NORMAL
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
mdefine_line|#define FILL_0_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x00], %l0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x08], %l1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x10], %l2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x18], %l3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x20], %l4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x28], %l5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x30], %l6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x38], %l7;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x40], %i0;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x48], %i1;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x50], %i2;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x58], %i3;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x60], %i4;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x68], %i5;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x70], %i6;&t;&t;&bslash;&n;&t;ldx&t;[%sp + STACK_BIAS + 0x78], %i7;&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 64bit fill */
DECL|macro|FILL_1_NORMAL
mdefine_line|#define FILL_1_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, ASI_AIUP, %asi;&t;&t;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x00] %asi, %l0;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x08] %asi, %l1;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x10] %asi, %l2;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x18] %asi, %l3;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x20] %asi, %l4;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x28] %asi, %l5;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x30] %asi, %l6;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x38] %asi, %l7;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x40] %asi, %i0;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x48] %asi, %i1;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x50] %asi, %i2;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x58] %asi, %i3;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x60] %asi, %i4;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x68] %asi, %i5;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x70] %asi, %i6;&t;&bslash;&n;&t;ldxa&t;[%sp + STACK_BIAS + 0x78] %asi, %i7;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop; nop;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop;
multiline_comment|/* Normal 32bit fill */
DECL|macro|FILL_2_NORMAL
mdefine_line|#define FILL_2_NORMAL&t;&t;&t;&t;&t;&bslash;&n;&t;wr&t;%g0, ASI_AIUP, %asi;&t;&t;&t;&bslash;&n;&t;srl&t;%sp, 0, %sp;&t;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x00] %asi, %l0;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x10] %asi, %l2;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x20] %asi, %l4;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x30] %asi, %l6;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x40] %asi, %i0;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x50] %asi, %i2;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x60] %asi, %i4;&t;&t;&t;&bslash;&n;&t;ldda&t;[%sp + 0x70] %asi, %i6;&t;&t;&t;&bslash;&n;&t;saved; retry; nop; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;&t;&t;&bslash;&n;&t;nop; nop; nop; nop; nop; nop; nop; nop;
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
mdefine_line|#define FILL_1_OTHER FILL_1_NORMAL
DECL|macro|FILL_2_OTHER
mdefine_line|#define FILL_2_OTHER FILL_2_NORMAL
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
macro_line|#endif /* !(_SPARC64_HEAD_H) */
eof
