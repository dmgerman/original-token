macro_line|#ifndef __M68K_ENTRY_H
DECL|macro|__M68K_ENTRY_H
mdefine_line|#define __M68K_ENTRY_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#ifdef CONFIG_KGDB
macro_line|#include &lt;asm/kgdb.h&gt;
macro_line|#endif
multiline_comment|/*&n; * Stack layout in &squot;ret_from_exception&squot;:&n; *&n; *&t;This allows access to the syscall arguments in registers d1-d5&n; *&n; *&t; 0(sp) - d1&n; *&t; 4(sp) - d2&n; *&t; 8(sp) - d3&n; *&t; C(sp) - d4&n; *&t;10(sp) - d5&n; *&t;14(sp) - a0&n; *&t;18(sp) - a1&n; *&t;1C(sp) - a2&n; *&t;20(sp) - d0&n; *&t;24(sp) - orig_d0&n; *&t;28(sp) - stack adjustment&n; *&t;2C(sp) - sr&n; *&t;2E(sp) - pc&n; *&t;32(sp) - format &amp; vector&n; */
multiline_comment|/*&n; * 97/05/14 Andreas: Register %a2 is now set to the current task throughout&n; *&t;&t;     the whole kernel.&n; */
macro_line|#ifdef __ASSEMBLY__
DECL|macro|curptr
mdefine_line|#define curptr a2
multiline_comment|/*&n; * these are offsets into the task-struct&n; */
id|LTASK_STATE
op_assign
l_int|0
id|LTASK_COUNTER
op_assign
l_int|4
id|LTASK_PRIORITY
op_assign
l_int|8
id|LTASK_SIGNAL
op_assign
l_int|12
id|LTASK_BLOCKED
op_assign
l_int|16
id|LTASK_FLAGS
op_assign
l_int|20
id|LTSS_KSP
op_assign
l_int|0
id|LTSS_USP
op_assign
l_int|4
id|LTSS_SR
op_assign
l_int|8
id|LTSS_FS
op_assign
l_int|10
id|LTSS_CRP
op_assign
l_int|12
id|LTSS_FPCTXT
op_assign
l_int|24
multiline_comment|/* the following macro is used when enabling interrupts */
macro_line|#if defined(MACH_ATARI_ONLY)
multiline_comment|/* block out HSYNC on the atari */
DECL|macro|ALLOWINT
mdefine_line|#define ALLOWINT 0xfbff
DECL|macro|MAX_NOINT_IPL
mdefine_line|#define&t;MAX_NOINT_IPL&t;3
macro_line|#else
multiline_comment|/* portable version */
mdefine_line|#define ALLOWINT 0xf8ff
mdefine_line|#define&t;MAX_NOINT_IPL&t;0
macro_line|#endif /* machine compilation types */ 
id|LPT_OFF_D0
op_assign
l_int|0x20
id|LPT_OFF_ORIG_D0
op_assign
l_int|0x24
id|LPT_OFF_SR
op_assign
l_int|0x2C
id|LPT_OFF_FORMATVEC
op_assign
l_int|0x32
id|LFLUSH_I_AND_D
op_assign
l_int|0x00000808
id|LENOSYS
op_assign
l_int|38
id|LSIGTRAP
op_assign
l_int|5
id|LPF_TRACESYS_OFF
op_assign
l_int|3
id|LPF_TRACESYS_BIT
op_assign
l_int|5
id|LPF_PTRACED_OFF
op_assign
l_int|3
id|LPF_PTRACED_BIT
op_assign
l_int|4
id|LPF_DTRACE_OFF
op_assign
l_int|1
id|LPF_DTRACE_BIT
op_assign
l_int|5
multiline_comment|/*&n; * This defines the normal kernel pt-regs layout.&n; *&n; * regs a3-a6 and d6-d7 are preserved by C code&n; * the kernel doesn&squot;t mess with usp unless it needs to&n; */
macro_line|#ifndef CONFIG_KGDB
multiline_comment|/*&n; * a -1 in the orig_d0 field signifies&n; * that the stack frame is NOT for syscall&n; */
DECL|macro|SAVE_ALL_INT
mdefine_line|#define SAVE_ALL_INT&t;&t;&t;&t;&bslash;&n;&t;clrl&t;%sp@-;&t;&t;/* stk_adj */&t;&bslash;&n;&t;pea&t;-1:w;&t;&t;/* orig d0 */&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* d0 */&t;&bslash;&n;&t;moveml&t;%d1-%d5/%a0-%a1/%curptr,%sp@-
DECL|macro|SAVE_ALL_SYS
mdefine_line|#define SAVE_ALL_SYS&t;&t;&t;&t;&bslash;&n;&t;clrl&t;%sp@-;&t;&t;/* stk_adj */&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* orig d0 */&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* d0 */&t;&bslash;&n;&t;moveml  %d1-%d5/%a0-%a1/%curptr,%sp@-
macro_line|#else
multiline_comment|/* Need to save the &quot;missing&quot; registers for kgdb...&n; */
mdefine_line|#define SAVE_ALL_INT&t;&t;&t;&t;&t;&bslash;&n;&t;clrl&t;%sp@-;&t;&t;/* stk_adj */&t;&t;&bslash;&n;&t;pea&t;-1:w;&t;&t;/* orig d0 */&t;&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* d0 */&t;&t;&bslash;&n;&t;moveml&t;%d1-%d5/%a0-%a1/%curptr,%sp@-;&t;&t;&bslash;&n;&t;moveml&t;%d6-%d7,kgdb_registers+GDBOFFA_D6;&t;&bslash;&n;&t;moveml&t;%a3-%a6,kgdb_registers+GDBOFFA_A3
mdefine_line|#define SAVE_ALL_SYS&t;&t;&t;&t;&t;&bslash;&n;&t;clrl&t;%sp@-;&t;&t;/* stk_adj */&t;&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* orig d0 */&t;&t;&bslash;&n;&t;movel&t;%d0,%sp@-;&t;/* d0 */&t;&t;&bslash;&n;&t;moveml&t;%d1-%d5/%a0-%a1/%curptr,%sp@-;&t;&t;&bslash;&n;&t;moveml&t;%d6-%d7,kgdb_registers+GDBOFFA_D6;&t;&bslash;&n;&t;moveml&t;%a3-%a6,kgdb_registers+GDBOFFA_A3
macro_line|#endif
DECL|macro|RESTORE_ALL
mdefine_line|#define RESTORE_ALL&t;&t;&t;&bslash;&n;&t;moveml&t;%sp@+,%a0-%a1/%curptr/%d1-%d5;&t;&bslash;&n;&t;movel&t;%sp@+,%d0;&t;&t;&bslash;&n;&t;addql&t;#4,%sp;&t; /* orig d0 */&t;&bslash;&n;&t;addl&t;%sp@+,%sp; /* stk adj */&t;&bslash;&n;&t;rte
DECL|macro|SWITCH_STACK_SIZE
mdefine_line|#define SWITCH_STACK_SIZE (6*4+4)&t;/* includes return address */
DECL|macro|SAVE_SWITCH_STACK
mdefine_line|#define SAVE_SWITCH_STACK &bslash;&n;&t;moveml&t;%a3-%a6/%d6-%d7,%sp@-
DECL|macro|RESTORE_SWITCH_STACK
mdefine_line|#define RESTORE_SWITCH_STACK &bslash;&n;&t;moveml&t;%sp@+,%a3-%a6/%d6-%d7
DECL|macro|GET_CURRENT
mdefine_line|#define GET_CURRENT(tmp) &bslash;&n;&t;movel&t;%sp,tmp; &bslash;&n;&t;andw&t;&amp;-8192,tmp; &bslash;&n;&t;movel&t;tmp,%curptr;
macro_line|#else /* C source */
mdefine_line|#define STR(X) STR1(X)
mdefine_line|#define STR1(X) #X
mdefine_line|#define PT_OFF_ORIG_D0&t; 0x24
mdefine_line|#define PT_OFF_FORMATVEC 0x32
mdefine_line|#define PT_OFF_SR&t; 0x2C
macro_line|#ifndef CONFIG_KGDB
mdefine_line|#define SAVE_ALL_INT&t;&t;&t;&t;&bslash;&n;&t;&quot;clrl&t;%%sp@-;&quot;    /* stk_adj */&t;&bslash;&n;&t;&quot;pea&t;-1:w;&quot;&t;    /* orig d0 = -1 */&t;&bslash;&n;&t;&quot;movel&t;%%d0,%%sp@-;&quot; /* d0 */&t;&t;&bslash;&n;&t;&quot;moveml&t;%%d1-%%d5/%%a0-%%a2,%%sp@-&quot;
macro_line|#else
mdefine_line|#define SAVE_ALL_INT&t;&t;&t;&t;&bslash;&n;&t;&quot;clrl&t;%%sp@-&bslash;n&bslash;t&quot; /* stk_adj */&t;&bslash;&n;&t;&quot;pea&t;-1:w&bslash;n&bslash;t&quot;   /* orig d0 = -1 */&t;&bslash;&n;&t;&quot;movel&t;%%d0,%%sp@-&bslash;n&bslash;t&quot; /* d0 */&t;&bslash;&n;&t;&quot;moveml&t;%%d1-%%d5/%%a0-%%a2,%%sp@-&bslash;n&bslash;t&quot;&t;&bslash;&n;&t;&quot;moveml&t;%%d6-%%d7,kgdb_registers+&quot;STR(GDBOFFA_D6)&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;moveml&t;%%a3-%%a6,kgdb_registers+&quot;STR(GDBOFFA_A3)
macro_line|#endif
mdefine_line|#define GET_CURRENT(tmp) &bslash;&n;&t;&quot;movel&t;%%sp,&quot;#tmp&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;andw&t;#-8192,&quot;#tmp&quot;&bslash;n&bslash;t&quot; &bslash;&n;&t;&quot;movel&t;&quot;#tmp&quot;,%%a2&quot;
macro_line|#endif
macro_line|#endif /* __M68K_ENTRY_H */
eof
