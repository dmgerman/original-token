macro_line|#ifndef _LINUX_MATH_EMU_H
DECL|macro|_LINUX_MATH_EMU_H
mdefine_line|#define _LINUX_MATH_EMU_H
DECL|struct|fpu_reg
r_struct
id|fpu_reg
(brace
DECL|member|sign
r_char
id|sign
suffix:semicolon
DECL|member|tag
r_char
id|tag
suffix:semicolon
DECL|member|exp
r_int
id|exp
suffix:semicolon
DECL|member|sigl
r_int
id|sigl
suffix:semicolon
DECL|member|sigh
r_int
id|sigh
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|info
r_struct
id|info
(brace
DECL|member|___orig_eip
r_int
id|___orig_eip
suffix:semicolon
DECL|member|___ret_from_system_call
r_int
id|___ret_from_system_call
suffix:semicolon
DECL|member|___ebx
r_int
id|___ebx
suffix:semicolon
DECL|member|___ecx
r_int
id|___ecx
suffix:semicolon
DECL|member|___edx
r_int
id|___edx
suffix:semicolon
DECL|member|___esi
r_int
id|___esi
suffix:semicolon
DECL|member|___edi
r_int
id|___edi
suffix:semicolon
DECL|member|___ebp
r_int
id|___ebp
suffix:semicolon
DECL|member|___eax
r_int
id|___eax
suffix:semicolon
DECL|member|___ds
r_int
id|___ds
suffix:semicolon
DECL|member|___es
r_int
id|___es
suffix:semicolon
DECL|member|___fs
r_int
id|___fs
suffix:semicolon
DECL|member|___gs
r_int
id|___gs
suffix:semicolon
DECL|member|___orig_eax
r_int
id|___orig_eax
suffix:semicolon
DECL|member|___eip
r_int
id|___eip
suffix:semicolon
DECL|member|___cs
r_int
id|___cs
suffix:semicolon
DECL|member|___eflags
r_int
id|___eflags
suffix:semicolon
DECL|member|___esp
r_int
id|___esp
suffix:semicolon
DECL|member|___ss
r_int
id|___ss
suffix:semicolon
)brace
suffix:semicolon
macro_line|#if 0
mdefine_line|#define EAX (info-&gt;___eax)
mdefine_line|#define EBX (info-&gt;___ebx)
mdefine_line|#define ECX (info-&gt;___ecx)
mdefine_line|#define EDX (info-&gt;___edx)
mdefine_line|#define ESI (info-&gt;___esi)
mdefine_line|#define EDI (info-&gt;___edi)
mdefine_line|#define EBP (info-&gt;___ebp)
mdefine_line|#define ESP (info-&gt;___esp)
mdefine_line|#define EIP (info-&gt;___eip)
mdefine_line|#define ORIG_EIP (info-&gt;___orig_eip)
mdefine_line|#define EFLAGS (info-&gt;___eflags)
mdefine_line|#define DS (*(unsigned short *) &amp;(info-&gt;___ds))
mdefine_line|#define ES (*(unsigned short *) &amp;(info-&gt;___es))
mdefine_line|#define FS (*(unsigned short *) &amp;(info-&gt;___fs))
mdefine_line|#define CS (*(unsigned short *) &amp;(info-&gt;___cs))
mdefine_line|#define SS (*(unsigned short *) &amp;(info-&gt;___ss))
macro_line|#endif
r_void
id|__math_abort
c_func
(paren
r_struct
id|info
op_star
comma
r_int
r_int
)paren
suffix:semicolon
DECL|macro|math_abort
mdefine_line|#define math_abort(x,y) &bslash;&n;(((volatile void (*)(struct info *,unsigned int)) __math_abort)((x),(y)))
macro_line|#endif
eof
