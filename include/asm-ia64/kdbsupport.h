macro_line|#ifndef _ASM_IA64_KDBSUPPORT_H
DECL|macro|_ASM_IA64_KDBSUPPORT_H
mdefine_line|#define _ASM_IA64_KDBSUPPORT_H
multiline_comment|/*&n; * Kernel Debugger Breakpoint Handler&n; *&n; * Copyright 1999, Silicon Graphics, Inc.&n; *&n; * Written March 1999 by Scott Lurndal at Silicon Graphics, Inc.&n; */
macro_line|#include &lt;asm/ptrace.h&gt;
multiline_comment|/*&n;&t; * This file provides definitions for functions that&n;&t; * are dependent upon the product into which  kdb is&n;&t; * linked. &n;&t; *&n;&t; * This version is for linux.&n;&t; */
DECL|typedef|handler_t
r_typedef
r_void
(paren
op_star
id|handler_t
)paren
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|typedef|k_machreg_t
r_typedef
r_int
r_int
id|k_machreg_t
suffix:semicolon
r_int
r_int
id|show_cur_stack_frame
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_char
op_star
id|kbd_getstr
c_func
(paren
r_char
op_star
comma
r_int
comma
r_char
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kdbinstalltrap
c_func
(paren
r_int
comma
id|handler_t
comma
id|handler_t
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kdbinstalldbreg
c_func
(paren
id|kdb_bp_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdbremovedbreg
c_func
(paren
id|kdb_bp_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdb_initbptab
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|kdbgetregcontents
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kdbsetregcontents
c_func
(paren
r_const
r_char
op_star
comma
r_struct
id|pt_regs
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|kdbdumpregs
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_const
r_char
op_star
comma
r_const
r_char
op_star
)paren
suffix:semicolon
DECL|typedef|kdbintstate_t
r_typedef
r_int
id|kdbintstate_t
suffix:semicolon
r_extern
r_void
id|kdb_disableint
c_func
(paren
id|kdbintstate_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdb_restoreint
c_func
(paren
id|kdbintstate_t
op_star
)paren
suffix:semicolon
r_extern
id|k_machreg_t
id|kdb_getpc
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
r_extern
r_int
id|kdb_setpc
c_func
(paren
r_struct
id|pt_regs
op_star
comma
id|k_machreg_t
)paren
suffix:semicolon
r_extern
r_int
id|kdb_putword
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_int
id|kdb_getcurrentframe
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n; * kdb_db_trap is a processor dependent routine invoked&n; * from kdb() via the #db trap handler.   It handles breakpoints involving&n; * the processor debug registers and handles single step traps&n; * using the processor trace flag.&n; */
DECL|macro|KDB_DB_BPT
mdefine_line|#define KDB_DB_BPT&t;0&t;/* Straight breakpoint */
DECL|macro|KDB_DB_SS
mdefine_line|#define KDB_DB_SS&t;1&t;/* Single Step trap */
DECL|macro|KDB_DB_SSB
mdefine_line|#define KDB_DB_SSB&t;2&t;/* Single Step, caller should continue */
r_extern
r_int
id|kdb_db_trap
c_func
(paren
r_struct
id|pt_regs
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
r_int
id|kdb_allocdbreg
c_func
(paren
id|kdb_bp_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdb_freedbreg
c_func
(paren
id|kdb_bp_t
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdb_initdbregs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kdb_setsinglestep
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *  Support for ia32 architecture debug registers.&n;&t; */
DECL|macro|KDB_DBREGS
mdefine_line|#define KDB_DBREGS&t;4&t;
r_extern
id|k_machreg_t
id|dbregs
(braket
)braket
suffix:semicolon
DECL|macro|DR6_BT
mdefine_line|#define DR6_BT  0x00008000
DECL|macro|DR6_BS
mdefine_line|#define DR6_BS&t;0x00004000
DECL|macro|DR6_BD
mdefine_line|#define DR6_BD  0x00002000
DECL|macro|DR6_B3
mdefine_line|#define DR6_B3  0x00000008
DECL|macro|DR6_B2
mdefine_line|#define DR6_B2&t;0x00000004
DECL|macro|DR6_B1
mdefine_line|#define DR6_B1  0x00000002
DECL|macro|DR6_B0
mdefine_line|#define DR6_B0&t;0x00000001
DECL|macro|DR7_RW_VAL
mdefine_line|#define DR7_RW_VAL(dr, drnum) &bslash;&n;       (((dr) &gt;&gt; (16 + (4 * (drnum)))) &amp; 0x3)
DECL|macro|DR7_RW_SET
mdefine_line|#define DR7_RW_SET(dr, drnum, rw)                              &bslash;&n;       do {                                                    &bslash;&n;               (dr) &amp;= ~(0x3 &lt;&lt; (16 + (4 * (drnum))));         &bslash;&n;               (dr) |= (((rw) &amp; 0x3) &lt;&lt; (16 + (4 * (drnum)))); &bslash;&n;       } while (0)
DECL|macro|DR7_RW0
mdefine_line|#define DR7_RW0(dr)       DR7_RW_VAL(dr, 0)
DECL|macro|DR7_RW0SET
mdefine_line|#define DR7_RW0SET(dr,rw)  DR7_RW_SET(dr, 0, rw)
DECL|macro|DR7_RW1
mdefine_line|#define DR7_RW1(dr)       DR7_RW_VAL(dr, 1)
DECL|macro|DR7_RW1SET
mdefine_line|#define DR7_RW1SET(dr,rw)  DR7_RW_SET(dr, 1, rw)
DECL|macro|DR7_RW2
mdefine_line|#define DR7_RW2(dr)       DR7_RW_VAL(dr, 2)
DECL|macro|DR7_RW2SET
mdefine_line|#define DR7_RW2SET(dr,rw)  DR7_RW_SET(dr, 2, rw)
DECL|macro|DR7_RW3
mdefine_line|#define DR7_RW3(dr)       DR7_RW_VAL(dr, 3)
DECL|macro|DR7_RW3SET
mdefine_line|#define DR7_RW3SET(dr,rw)  DR7_RW_SET(dr, 3, rw)
DECL|macro|DR7_LEN_VAL
mdefine_line|#define DR7_LEN_VAL(dr, drnum) &bslash;&n;       (((dr) &gt;&gt; (18 + (4 * (drnum)))) &amp; 0x3)
DECL|macro|DR7_LEN_SET
mdefine_line|#define DR7_LEN_SET(dr, drnum, rw)                             &bslash;&n;       do {                                                    &bslash;&n;               (dr) &amp;= ~(0x3 &lt;&lt; (18 + (4 * (drnum))));         &bslash;&n;               (dr) |= (((rw) &amp; 0x3) &lt;&lt; (18 + (4 * (drnum)))); &bslash;&n;       } while (0)
DECL|macro|DR7_LEN0
mdefine_line|#define DR7_LEN0(dr)        DR7_LEN_VAL(dr, 0)
DECL|macro|DR7_LEN0SET
mdefine_line|#define DR7_LEN0SET(dr,len)  DR7_LEN_SET(dr, 0, len)
DECL|macro|DR7_LEN1
mdefine_line|#define DR7_LEN1(dr)        DR7_LEN_VAL(dr, 1)
DECL|macro|DR7_LEN1SET
mdefine_line|#define DR7_LEN1SET(dr,len)  DR7_LEN_SET(dr, 1, len)
DECL|macro|DR7_LEN2
mdefine_line|#define DR7_LEN2(dr)        DR7_LEN_VAL(dr, 2)
DECL|macro|DR7_LEN2SET
mdefine_line|#define DR7_LEN2SET(dr,len)  DR7_LEN_SET(dr, 2, len)
DECL|macro|DR7_LEN3
mdefine_line|#define DR7_LEN3(dr)        DR7_LEN_VAL(dr, 3)
DECL|macro|DR7_LEN3SET
mdefine_line|#define DR7_LEN3SET(dr,len)  DR7_LEN_SET(dr, 3, len)
DECL|macro|DR7_G0
mdefine_line|#define DR7_G0(dr)    (((dr)&gt;&gt;1)&amp;0x1)
DECL|macro|DR7_G0SET
mdefine_line|#define DR7_G0SET(dr) ((dr) |= 0x2)
DECL|macro|DR7_G0CLR
mdefine_line|#define DR7_G0CLR(dr) ((dr) &amp;= ~0x2)
DECL|macro|DR7_G1
mdefine_line|#define DR7_G1(dr)    (((dr)&gt;&gt;3)&amp;0x1)
DECL|macro|DR7_G1SET
mdefine_line|#define DR7_G1SET(dr) ((dr) |= 0x8)
DECL|macro|DR7_G1CLR
mdefine_line|#define DR7_G1CLR(dr) ((dr) &amp;= ~0x8)
DECL|macro|DR7_G2
mdefine_line|#define DR7_G2(dr)    (((dr)&gt;&gt;5)&amp;0x1)
DECL|macro|DR7_G2SET
mdefine_line|#define DR7_G2SET(dr) ((dr) |= 0x20)
DECL|macro|DR7_G2CLR
mdefine_line|#define DR7_G2CLR(dr) ((dr) &amp;= ~0x20)
DECL|macro|DR7_G3
mdefine_line|#define DR7_G3(dr)    (((dr)&gt;&gt;7)&amp;0x1)
DECL|macro|DR7_G3SET
mdefine_line|#define DR7_G3SET(dr) ((dr) |= 0x80)
DECL|macro|DR7_G3CLR
mdefine_line|#define DR7_G3CLR(dr) ((dr) &amp;= ~0x80)
DECL|macro|DR7_L0
mdefine_line|#define DR7_L0(dr)    (((dr))&amp;0x1)
DECL|macro|DR7_L0SET
mdefine_line|#define DR7_L0SET(dr) ((dr) |= 0x1)
DECL|macro|DR7_L0CLR
mdefine_line|#define DR7_L0CLR(dr) ((dr) &amp;= ~0x1)
DECL|macro|DR7_L1
mdefine_line|#define DR7_L1(dr)    (((dr)&gt;&gt;2)&amp;0x1)
DECL|macro|DR7_L1SET
mdefine_line|#define DR7_L1SET(dr) ((dr) |= 0x4)
DECL|macro|DR7_L1CLR
mdefine_line|#define DR7_L1CLR(dr) ((dr) &amp;= ~0x4)
DECL|macro|DR7_L2
mdefine_line|#define DR7_L2(dr)    (((dr)&gt;&gt;4)&amp;0x1)
DECL|macro|DR7_L2SET
mdefine_line|#define DR7_L2SET(dr) ((dr) |= 0x10)
DECL|macro|DR7_L2CLR
mdefine_line|#define DR7_L2CLR(dr) ((dr) &amp;= ~0x10)
DECL|macro|DR7_L3
mdefine_line|#define DR7_L3(dr)    (((dr)&gt;&gt;6)&amp;0x1)
DECL|macro|DR7_L3SET
mdefine_line|#define DR7_L3SET(dr) ((dr) |= 0x40)
DECL|macro|DR7_L3CLR
mdefine_line|#define DR7_L3CLR(dr) ((dr) &amp;= ~0x40)
DECL|macro|DR7_GD
mdefine_line|#define DR7_GD&t;&t;0x00002000&t;&t;/* General Detect Enable */
DECL|macro|DR7_GE
mdefine_line|#define DR7_GE&t;&t;0x00000200&t;&t;/* Global exact */
DECL|macro|DR7_LE
mdefine_line|#define DR7_LE&t;&t;0x00000100&t;&t;/* Local exact */
r_extern
id|k_machreg_t
id|kdb_getdr6
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kdb_putdr6
c_func
(paren
id|k_machreg_t
)paren
suffix:semicolon
r_extern
id|k_machreg_t
id|kdb_getdr7
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kdb_putdr7
c_func
(paren
id|k_machreg_t
)paren
suffix:semicolon
r_extern
id|k_machreg_t
id|kdb_getdr
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kdb_putdr
c_func
(paren
r_int
comma
id|k_machreg_t
)paren
suffix:semicolon
r_extern
id|k_machreg_t
id|kdb_getcr
c_func
(paren
r_int
)paren
suffix:semicolon
r_extern
r_void
id|kdb_bp_install
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|kdb_bp_remove
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Support for setjmp/longjmp&n; */
DECL|macro|JB_BX
mdefine_line|#define JB_BX   0
DECL|macro|JB_SI
mdefine_line|#define JB_SI   1
DECL|macro|JB_DI
mdefine_line|#define JB_DI   2
DECL|macro|JB_BP
mdefine_line|#define JB_BP   3
DECL|macro|JB_SP
mdefine_line|#define JB_SP   4
DECL|macro|JB_PC
mdefine_line|#define JB_PC   5
DECL|struct|__kdb_jmp_buf
r_typedef
r_struct
id|__kdb_jmp_buf
(brace
DECL|member|regs
r_int
r_int
id|regs
(braket
l_int|6
)braket
suffix:semicolon
DECL|typedef|kdb_jmp_buf
)brace
id|kdb_jmp_buf
suffix:semicolon
r_extern
r_int
id|kdb_setjmp
c_func
(paren
id|kdb_jmp_buf
op_star
)paren
suffix:semicolon
r_extern
r_void
id|kdb_longjmp
c_func
(paren
id|kdb_jmp_buf
op_star
comma
r_int
)paren
suffix:semicolon
r_extern
id|kdb_jmp_buf
id|kdbjmpbuf
suffix:semicolon
DECL|macro|getprsregs
mdefine_line|#define getprsregs(regs)&t;((struct switch_stack *)regs -1)
DECL|macro|BITMASK
mdefine_line|#define BITMASK(bp,value)  (value &lt;&lt; bp)
multiline_comment|/* bkpt support using break inst instead of IBP reg */
multiline_comment|/*&n; * Define certain specific instructions&n; */
DECL|macro|BREAK_INSTR
mdefine_line|#define BREAK_INSTR             (0x00000080100L &lt;&lt; 11)
DECL|macro|INST_SLOT0_MASK
mdefine_line|#define INST_SLOT0_MASK         (0x1ffffffffffL &lt;&lt; 5)
macro_line|#if 0
mdefine_line|#define MAX_BREAKPOINTS         40
mdefine_line|#define PSR_SS                  40
macro_line|#endif
multiline_comment|/**&n; * IA-64 instruction format structures&n; */
DECL|union|bundle
r_typedef
r_union
id|bundle
(brace
r_struct
(brace
DECL|member|low8
r_int
id|low8
suffix:semicolon
DECL|member|high8
r_int
id|high8
suffix:semicolon
DECL|member|lform
)brace
id|lform
suffix:semicolon
r_struct
(brace
DECL|member|low_low4
r_int
id|low_low4
suffix:semicolon
DECL|member|low_high4
r_int
id|low_high4
suffix:semicolon
DECL|member|high8
r_int
id|high8
suffix:semicolon
DECL|member|iform
)brace
id|iform
suffix:semicolon
DECL|typedef|bundle_t
)brace
id|bundle_t
suffix:semicolon
DECL|macro|BKPTMODE_DATAR
mdefine_line|#define BKPTMODE_DATAR&t;3
DECL|macro|BKPTMODE_IO
mdefine_line|#define BKPTMODE_IO   &t;2
DECL|macro|BKPTMODE_DATAW
mdefine_line|#define BKPTMODE_DATAW&t;1
DECL|macro|BKPTMODE_INST
mdefine_line|#define BKPTMODE_INST&t;0
multiline_comment|/* Some of the fault registers needed by kdb but not passed with&n; * regs or switch stack.&n; */
DECL|struct|fault_regs
r_typedef
r_struct
id|fault_regs
(brace
DECL|member|isr
r_int
r_int
id|isr
suffix:semicolon
DECL|member|ifa
r_int
r_int
id|ifa
suffix:semicolon
DECL|member|iim
r_int
r_int
id|iim
suffix:semicolon
DECL|member|itir
r_int
r_int
id|itir
suffix:semicolon
DECL|typedef|fault_regs_t
)brace
id|fault_regs_t
suffix:semicolon
multiline_comment|/*&n; * State of kdb&n; */
DECL|struct|kdb_state
r_typedef
r_struct
id|kdb_state
(brace
DECL|member|cmd_given
r_int
id|cmd_given
suffix:semicolon
DECL|member|reason_for_entry
r_int
id|reason_for_entry
suffix:semicolon
DECL|member|bkpt_handling_state
r_int
id|bkpt_handling_state
suffix:semicolon
DECL|member|kdb_action
r_int
id|kdb_action
suffix:semicolon
DECL|typedef|kdb_state_t
)brace
id|kdb_state_t
suffix:semicolon
DECL|macro|BKPTSTATE_NOT_HANDLED
mdefine_line|#define BKPTSTATE_NOT_HANDLED &t;0
DECL|macro|BKPTSTATE_HANDLED
mdefine_line|#define BKPTSTATE_HANDLED &t;1
DECL|macro|CMDGIVEN_UNKNOWN
mdefine_line|#define CMDGIVEN_UNKNOWN&t;0&t;
DECL|macro|CMDGIVEN_SSTEP
mdefine_line|#define CMDGIVEN_SSTEP&t;&t;1&t;
DECL|macro|CMDGIVEN_GO
mdefine_line|#define CMDGIVEN_GO&t;&t;2&t;
DECL|macro|ENTRYREASON_GO
mdefine_line|#define ENTRYREASON_GO&t; &t;0
DECL|macro|ENTRYREASON_SSTEP
mdefine_line|#define ENTRYREASON_SSTEP&t;1
DECL|macro|ACTION_UNKNOWN
mdefine_line|#define ACTION_UNKNOWN&t;&t;0
DECL|macro|ACTION_NOBPINSTALL
mdefine_line|#define ACTION_NOBPINSTALL&t;1
DECL|macro|ACTION_NOPROMPT
mdefine_line|#define ACTION_NOPROMPT&t;&t;2
macro_line|#endif /* _ASM_IA64_KDBSUPPORT_H */
eof
