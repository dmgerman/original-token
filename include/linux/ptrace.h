macro_line|#ifndef _LINUX_PTRACE_H
DECL|macro|_LINUX_PTRACE_H
mdefine_line|#define _LINUX_PTRACE_H
multiline_comment|/* ptrace.h */
multiline_comment|/* structs and defines to help the user use the ptrace system call. */
multiline_comment|/* has the defines to get at the registers. */
DECL|macro|PTRACE_TRACEME
mdefine_line|#define PTRACE_TRACEME&t;&t;   0
DECL|macro|PTRACE_PEEKTEXT
mdefine_line|#define PTRACE_PEEKTEXT&t;&t;   1
DECL|macro|PTRACE_PEEKDATA
mdefine_line|#define PTRACE_PEEKDATA&t;&t;   2
DECL|macro|PTRACE_PEEKUSR
mdefine_line|#define PTRACE_PEEKUSR&t;&t;   3
DECL|macro|PTRACE_POKETEXT
mdefine_line|#define PTRACE_POKETEXT&t;&t;   4
DECL|macro|PTRACE_POKEDATA
mdefine_line|#define PTRACE_POKEDATA&t;&t;   5
DECL|macro|PTRACE_POKEUSR
mdefine_line|#define PTRACE_POKEUSR&t;&t;   6
DECL|macro|PTRACE_CONT
mdefine_line|#define PTRACE_CONT&t;&t;   7
DECL|macro|PTRACE_KILL
mdefine_line|#define PTRACE_KILL&t;&t;   8
DECL|macro|PTRACE_SINGLESTEP
mdefine_line|#define PTRACE_SINGLESTEP&t;   9
DECL|macro|PTRACE_ATTACH
mdefine_line|#define PTRACE_ATTACH&t;&t;0x10
DECL|macro|PTRACE_DETACH
mdefine_line|#define PTRACE_DETACH&t;&t;0x11
DECL|macro|PTRACE_SYSCALL
mdefine_line|#define PTRACE_SYSCALL&t;&t;  24
multiline_comment|/* use ptrace (3 or 6, pid, PT_EXCL, data); to read or write&n;   the processes registers. */
DECL|macro|EBX
mdefine_line|#define EBX 0
DECL|macro|ECX
mdefine_line|#define ECX 1
DECL|macro|EDX
mdefine_line|#define EDX 2
DECL|macro|ESI
mdefine_line|#define ESI 3
DECL|macro|EDI
mdefine_line|#define EDI 4
DECL|macro|EBP
mdefine_line|#define EBP 5
DECL|macro|EAX
mdefine_line|#define EAX 6
DECL|macro|DS
mdefine_line|#define DS 7
DECL|macro|ES
mdefine_line|#define ES 8
DECL|macro|FS
mdefine_line|#define FS 9
DECL|macro|GS
mdefine_line|#define GS 10
DECL|macro|ORIG_EAX
mdefine_line|#define ORIG_EAX 11
DECL|macro|EIP
mdefine_line|#define EIP 12
DECL|macro|CS
mdefine_line|#define CS  13
DECL|macro|EFL
mdefine_line|#define EFL 14
DECL|macro|UESP
mdefine_line|#define UESP 15
DECL|macro|SS
mdefine_line|#define SS   16
multiline_comment|/* this struct defines the way the registers are stored on the &n;   stack during a system call. */
DECL|struct|pt_regs
r_struct
id|pt_regs
(brace
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
DECL|member|ds
DECL|member|__dsu
r_int
r_int
id|ds
comma
id|__dsu
suffix:semicolon
DECL|member|es
DECL|member|__esu
r_int
r_int
id|es
comma
id|__esu
suffix:semicolon
DECL|member|fs
DECL|member|__fsu
r_int
r_int
id|fs
comma
id|__fsu
suffix:semicolon
DECL|member|gs
DECL|member|__gsu
r_int
r_int
id|gs
comma
id|__gsu
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
DECL|member|__csu
r_int
r_int
id|cs
comma
id|__csu
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
DECL|member|__ssu
r_int
r_int
id|ss
comma
id|__ssu
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
eof
