macro_line|#ifndef __SPARC_HEAD_H
DECL|macro|__SPARC_HEAD_H
mdefine_line|#define __SPARC_HEAD_H
DECL|macro|KERNSIZE
mdefine_line|#define KERNSIZE&t;134217728   /* this is how much of a mapping the prom promises */
DECL|macro|PAGESIZE
mdefine_line|#define PAGESIZE&t;4096        /* luckily this is the same on sun4c&squot;s and sun4m&squot;s */
DECL|macro|PAGESHIFT
mdefine_line|#define PAGESHIFT       12
DECL|macro|PROM_BASE
mdefine_line|#define PROM_BASE&t;-1568768    /* casa &squot;de PROM */
DECL|macro|LOAD_ADDR
mdefine_line|#define LOAD_ADDR       0x4000      /* prom jumps to us here */
DECL|macro|C_STACK
mdefine_line|#define C_STACK         96
DECL|macro|SUN4C_SEGSZ
mdefine_line|#define SUN4C_SEGSZ     (1 &lt;&lt; 18)
DECL|macro|USRSTACK
mdefine_line|#define USRSTACK        0x0         /* no joke, this is temporary, trust me */
DECL|macro|INT_ENABLE_REG_PHYSADR
mdefine_line|#define INT_ENABLE_REG_PHYSADR      0xf5000000
DECL|macro|INTS_ENAB
mdefine_line|#define INTS_ENAB   0x01
DECL|macro|WRITE_PAUSE
mdefine_line|#define WRITE_PAUSE     nop; nop; nop;
DECL|macro|PAGE_SIZE
mdefine_line|#define PAGE_SIZE       4096
multiline_comment|/* Here are some trap goodies */
multiline_comment|/* Generic trap entry. */
DECL|macro|TRAP_ENTRY
mdefine_line|#define TRAP_ENTRY(type, label) &bslash;&n;&t;mov (type), %l3; b label; mov %psr, %l0; nop;
multiline_comment|/* This is for hard interrupts from level 1-14, 15 is non-maskable (nmi) and&n; * gets handled with another macro.&n; */
DECL|macro|TRAP_ENTRY_INTERRUPT
mdefine_line|#define TRAP_ENTRY_INTERRUPT(int_level) &bslash;&n;        mov int_level, %l4; b trap_entry; mov %psr, %l0; nop;
multiline_comment|/* Here is the macro for soft interrupts (ie. not as urgent as hard ones)&n;   which need to jump to a different handler.&n;*/
DECL|macro|TRAP_ENTRY_INTERRUPT_SOFT
mdefine_line|#define TRAP_ENTRY_INTERRUPT_SOFT(int_level, ident) &bslash;&n;        mov int_level, %l4; mov %psr, %l0; b trap_entry; mov ident, %l3;
multiline_comment|/* Non-maskable interrupt entry macro. You have to turn off all interrupts&n;   to not receive this. This is usually due to a asynchronous memory error.&n;   All we can really do is stop the show. :-(&n;*/
DECL|macro|TRAP_ENTRY_INTERRUPT_NMI
mdefine_line|#define TRAP_ENTRY_INTERRUPT_NMI(t_type, jmp_to) &bslash;&n;        mov t_type, %l3; b jmp_to; mov %psr, %l0; nop;
multiline_comment|/* Trap entry code in entry.S needs the offsets into task_struct&n; * to get at the thread_struct goodies during window craziness.&n; *&n; * NOTE: We need to keep these values under 0x3ff in order to do&n; *       efficient load/stores in the window fill/spill handlers.&n; *       See TRAP_WIN_CLEAN in entry.S for details.&n; */
DECL|macro|THREAD_UWINDOWS
mdefine_line|#define THREAD_UWINDOWS 0x3a8
DECL|macro|THREAD_WIM
mdefine_line|#define THREAD_WIM 0x3ac
DECL|macro|THREAD_W_SAVED
mdefine_line|#define THREAD_W_SAVED 0x3b0
DECL|macro|THREAD_KSP
mdefine_line|#define THREAD_KSP 0x3b4
DECL|macro|THREAD_USP
mdefine_line|#define THREAD_USP 0x3b8
DECL|macro|THREAD_REG_WINDOW
mdefine_line|#define THREAD_REG_WINDOW 0x3c0
macro_line|#endif __SPARC_HEAD_H
eof
