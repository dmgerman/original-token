macro_line|#ifndef __SPARC_HEAD_H
DECL|macro|__SPARC_HEAD_H
mdefine_line|#define __SPARC_HEAD_H
DECL|macro|KERNBASE
mdefine_line|#define KERNBASE        0xf0000000  /* First address the kernel will eventually be */
DECL|macro|LOAD_ADDR
mdefine_line|#define LOAD_ADDR       0x4000      /* prom jumps to us here unless this is elf /boot */
DECL|macro|C_STACK
mdefine_line|#define C_STACK         96
DECL|macro|SUN4C_SEGSZ
mdefine_line|#define SUN4C_SEGSZ     (1 &lt;&lt; 18)
DECL|macro|SRMMU_L1_KBASE_OFFSET
mdefine_line|#define SRMMU_L1_KBASE_OFFSET ((KERNBASE&gt;&gt;24)&lt;&lt;2)  /* Used in boot remapping. */
DECL|macro|INTS_ENAB
mdefine_line|#define INTS_ENAB   0x01            /* entry.S uses this. */
DECL|macro|NCPUS
mdefine_line|#define NCPUS           4            /* Architectual limit of sun4m. */
DECL|macro|SUN4_PROM_VECTOR
mdefine_line|#define  SUN4_PROM_VECTOR   0xFFE81000    /* To safely die on a SUN4 */
DECL|macro|SUN4_PRINTF
mdefine_line|#define  SUN4_PRINTF   0x84               /* Offset into SUN4_PROM_VECTOR */
DECL|macro|WRITE_PAUSE
mdefine_line|#define WRITE_PAUSE     nop; nop; nop;
DECL|macro|NOP_INSN
mdefine_line|#define NOP_INSN        0x01000000        /* Used to patch sparc_save_state */
multiline_comment|/* Here are some trap goodies */
multiline_comment|/* Generic trap entry. */
DECL|macro|TRAP_ENTRY
mdefine_line|#define TRAP_ENTRY(type, label) &bslash;&n;&t;mov (type), %l3; b label; rd %psr, %l0; nop;
multiline_comment|/* Notice that for the system calls we pull a trick.  We load up a&n; * different pointer to the system call vector table in %l7, but call&n; * the same generic system call low-level entry point.  The trap table&n; * entry sequences are also HyperSparc pipeline friendly ;-)&n; */
multiline_comment|/* Software trap for Linux system calls. */
DECL|macro|LINUX_SYSCALL_TRAP
mdefine_line|#define LINUX_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; or %l7, %lo(C_LABEL(sys_call_table)), %l7; b linux_sparc_syscall; mov %psr, %l0;
multiline_comment|/* Software trap for SunOS4.1.x system calls. */
DECL|macro|SUNOS_SYSCALL_TRAP
mdefine_line|#define SUNOS_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; or %l7, %lo(C_LABEL(sys_call_table)), %l7; b linux_sparc_syscall; mov %psr, %l0;
multiline_comment|/* Software trap for Slowaris system calls. */
DECL|macro|SOLARIS_SYSCALL_TRAP
mdefine_line|#define SOLARIS_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; or %l7, %lo(C_LABEL(sys_call_table)), %l7; b linux_sparc_syscall; mov %psr, %l0;
multiline_comment|/* Software trap for Sparc-netbsd system calls. */
DECL|macro|NETBSD_SYSCALL_TRAP
mdefine_line|#define NETBSD_SYSCALL_TRAP &bslash;&n;        sethi %hi(C_LABEL(sys_call_table)), %l7; or %l7, %lo(C_LABEL(sys_call_table)), %l7; b linux_sparc_syscall; mov %psr, %l0;
multiline_comment|/* The Get Condition Codes software trap for userland. */
DECL|macro|GETCC_TRAP
mdefine_line|#define GETCC_TRAP &bslash;&n;        b getcc_trap_handler; mov %psr, %l0; nop; nop
multiline_comment|/* The Set Condition Codes software trap for userland. */
DECL|macro|SETCC_TRAP
mdefine_line|#define SETCC_TRAP &bslash;&n;        b setcc_trap_handler; mov %psr, %l0; nop; nop
multiline_comment|/* This is for hard interrupts from level 1-14, 15 is non-maskable (nmi) and&n; * gets handled with another macro.&n; */
DECL|macro|TRAP_ENTRY_INTERRUPT
mdefine_line|#define TRAP_ENTRY_INTERRUPT(int_level) &bslash;&n;        mov int_level, %l3; b real_irq_entry; rd %psr, %l0; nop;
multiline_comment|/* NMI&squot;s (Non Maskable Interrupts) are special, you can&squot;t keep them&n; * from coming in, and basically if you get one, the shows over. ;(&n; */
DECL|macro|NMI_TRAP
mdefine_line|#define NMI_TRAP &bslash;&n;        b linux_trap_nmi; mov %psr, %l0; nop; nop
multiline_comment|/* The above two macros are for generic traps. The following is made&n; * especially for timer interrupts at IRQ level 14.&n; */
DECL|macro|TRAP_ENTRY_TIMER
mdefine_line|#define TRAP_ENTRY_TIMER &bslash;&n;        rd %psr, %l0; b sparc_timer; nop; nop;
multiline_comment|/* Trap entry code in entry.S needs the offsets into task_struct&n; * to get at the thread_struct goodies during window craziness.&n; *&n; * NOTE: We need to keep these values under 0x3ff in order to do&n; *       efficient load/stores in the window fill/spill handlers.&n; *       See TRAP_WIN_CLEAN in entry.S for details.&n; */
multiline_comment|/* First generic task_struct offsets */
DECL|macro|TASK_STATE
mdefine_line|#define TASK_STATE        0x000
DECL|macro|TASK_PRI
mdefine_line|#define TASK_PRI          0x008
DECL|macro|TASK_KSTACK_PG
mdefine_line|#define TASK_KSTACK_PG    0x250
DECL|macro|THREAD_UWINDOWS
mdefine_line|#define THREAD_UWINDOWS   0x3b8
DECL|macro|THREAD_WIM
mdefine_line|#define THREAD_WIM        0x3bc
DECL|macro|THREAD_W_SAVED
mdefine_line|#define THREAD_W_SAVED    0x3c0
DECL|macro|THREAD_KSP
mdefine_line|#define THREAD_KSP        0x3c4
DECL|macro|THREAD_USP
mdefine_line|#define THREAD_USP        0x3c8
DECL|macro|THREAD_PSR
mdefine_line|#define THREAD_PSR        0x3cc
DECL|macro|THREAD_PC
mdefine_line|#define THREAD_PC         0x3d0
DECL|macro|THREAD_NPC
mdefine_line|#define THREAD_NPC        0x3d4
DECL|macro|THREAD_Y
mdefine_line|#define THREAD_Y          0x3d8
DECL|macro|THREAD_REG_WINDOW
mdefine_line|#define THREAD_REG_WINDOW 0x3e0
multiline_comment|/* More fun offset macros. These are for pt_regs. */
DECL|macro|PT_PSR
mdefine_line|#define PT_PSR    0x0
DECL|macro|PT_PC
mdefine_line|#define PT_PC     0x4
DECL|macro|PT_NPC
mdefine_line|#define PT_NPC    0x8
DECL|macro|PT_Y
mdefine_line|#define PT_Y      0xc
DECL|macro|PT_G0
mdefine_line|#define PT_G0     0x10
DECL|macro|PT_G1
mdefine_line|#define PT_G1     0x14
DECL|macro|PT_G2
mdefine_line|#define PT_G2     0x18
DECL|macro|PT_G3
mdefine_line|#define PT_G3     0x1c
DECL|macro|PT_G4
mdefine_line|#define PT_G4     0x20
DECL|macro|PT_G5
mdefine_line|#define PT_G5     0x24
DECL|macro|PT_G6
mdefine_line|#define PT_G6     0x28
DECL|macro|PT_G7
mdefine_line|#define PT_G7     0x2c
DECL|macro|PT_I0
mdefine_line|#define PT_I0     0x30
DECL|macro|PT_I1
mdefine_line|#define PT_I1     0x34
DECL|macro|PT_I2
mdefine_line|#define PT_I2     0x38
DECL|macro|PT_I3
mdefine_line|#define PT_I3     0x3c
DECL|macro|PT_I4
mdefine_line|#define PT_I4     0x40
DECL|macro|PT_I5
mdefine_line|#define PT_I5     0x44
DECL|macro|PT_I6
mdefine_line|#define PT_I6     0x48
DECL|macro|PT_I7
mdefine_line|#define PT_I7     0x4c
macro_line|#endif __SPARC_HEAD_H
eof
