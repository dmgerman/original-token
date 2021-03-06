macro_line|#ifndef _M68K_UCONTEXT_H
DECL|macro|_M68K_UCONTEXT_H
mdefine_line|#define _M68K_UCONTEXT_H
DECL|typedef|greg_t
r_typedef
r_int
id|greg_t
suffix:semicolon
DECL|macro|NGREG
mdefine_line|#define NGREG 18
DECL|typedef|gregset_t
r_typedef
id|greg_t
id|gregset_t
(braket
id|NGREG
)braket
suffix:semicolon
DECL|struct|fpregset
r_typedef
r_struct
id|fpregset
(brace
DECL|member|f_pcr
r_int
id|f_pcr
suffix:semicolon
DECL|member|f_psr
r_int
id|f_psr
suffix:semicolon
DECL|member|f_fpiaddr
r_int
id|f_fpiaddr
suffix:semicolon
DECL|member|f_fpregs
r_int
id|f_fpregs
(braket
l_int|8
)braket
(braket
l_int|3
)braket
suffix:semicolon
DECL|typedef|fpregset_t
)brace
id|fpregset_t
suffix:semicolon
DECL|struct|mcontext
r_struct
id|mcontext
(brace
DECL|member|version
r_int
id|version
suffix:semicolon
DECL|member|gregs
id|gregset_t
id|gregs
suffix:semicolon
DECL|member|fpregs
id|fpregset_t
id|fpregs
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MCONTEXT_VERSION
mdefine_line|#define MCONTEXT_VERSION 2
DECL|struct|ucontext
r_struct
id|ucontext
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_struct
id|ucontext
op_star
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_t
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|mcontext
id|uc_mcontext
suffix:semicolon
DECL|member|uc_filler
r_int
r_int
id|uc_filler
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
macro_line|#endif
eof
