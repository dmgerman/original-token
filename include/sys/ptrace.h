multiline_comment|/* ptrace.h */
multiline_comment|/* structs and defines to help the user use the ptrace system call. */
macro_line|#ifndef _SYS_PTRACE_H
DECL|macro|_SYS_PTRACE_H
mdefine_line|#define _SYS_PTRACE_H
multiline_comment|/* has the defines to get at the registers. */
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
r_int
id|ds
suffix:semicolon
DECL|member|es
r_int
id|es
suffix:semicolon
DECL|member|fs
r_int
id|fs
suffix:semicolon
DECL|member|gs
r_int
id|gs
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
r_int
id|cs
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
r_int
id|ss
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif /* _SYS_PTRACE_H */
eof
