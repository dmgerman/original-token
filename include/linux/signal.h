macro_line|#ifndef _LINUX_SIGNAL_H
DECL|macro|_LINUX_SIGNAL_H
mdefine_line|#define _LINUX_SIGNAL_H
macro_line|#include &lt;asm/signal.h&gt;
macro_line|#include &lt;asm/siginfo.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * Real Time signals may be queued.&n; */
DECL|struct|sigqueue
r_struct
id|sigqueue
(brace
DECL|member|next
r_struct
id|sigqueue
op_star
id|next
suffix:semicolon
DECL|member|info
id|siginfo_t
id|info
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigpending
r_struct
id|sigpending
(brace
DECL|member|head
DECL|member|tail
r_struct
id|sigqueue
op_star
id|head
comma
op_star
op_star
id|tail
suffix:semicolon
DECL|member|signal
id|sigset_t
id|signal
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Define some primitives to manipulate sigset_t.&n; */
macro_line|#ifndef __HAVE_ARCH_SIG_BITOPS
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/* We don&squot;t use &lt;asm/bitops.h&gt; for these because there is no need to&n;   be atomic.  */
DECL|function|sigaddset
r_static
r_inline
r_void
id|sigaddset
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
r_int
r_int
id|sig
op_assign
id|_sig
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|_NSIG_WORDS
op_eq
l_int|1
)paren
id|set-&gt;sig
(braket
l_int|0
)braket
op_or_assign
l_int|1UL
op_lshift
id|sig
suffix:semicolon
r_else
id|set-&gt;sig
(braket
id|sig
op_div
id|_NSIG_BPW
)braket
op_or_assign
l_int|1UL
op_lshift
(paren
id|sig
op_mod
id|_NSIG_BPW
)paren
suffix:semicolon
)brace
DECL|function|sigdelset
r_static
r_inline
r_void
id|sigdelset
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
r_int
r_int
id|sig
op_assign
id|_sig
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|_NSIG_WORDS
op_eq
l_int|1
)paren
id|set-&gt;sig
(braket
l_int|0
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
id|sig
)paren
suffix:semicolon
r_else
id|set-&gt;sig
(braket
id|sig
op_div
id|_NSIG_BPW
)braket
op_and_assign
op_complement
(paren
l_int|1UL
op_lshift
(paren
id|sig
op_mod
id|_NSIG_BPW
)paren
)paren
suffix:semicolon
)brace
DECL|function|sigismember
r_static
r_inline
r_int
id|sigismember
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
id|_sig
)paren
(brace
r_int
r_int
id|sig
op_assign
id|_sig
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|_NSIG_WORDS
op_eq
l_int|1
)paren
r_return
l_int|1
op_amp
(paren
id|set-&gt;sig
(braket
l_int|0
)braket
op_rshift
id|sig
)paren
suffix:semicolon
r_else
r_return
l_int|1
op_amp
(paren
id|set-&gt;sig
(braket
id|sig
op_div
id|_NSIG_BPW
)braket
op_rshift
(paren
id|sig
op_mod
id|_NSIG_BPW
)paren
)paren
suffix:semicolon
)brace
DECL|function|sigfindinword
r_static
r_inline
r_int
id|sigfindinword
c_func
(paren
r_int
r_int
id|word
)paren
(brace
r_return
id|ffz
c_func
(paren
op_complement
id|word
)paren
suffix:semicolon
)brace
DECL|macro|sigmask
mdefine_line|#define sigmask(sig)&t;(1UL &lt;&lt; ((sig) - 1))
macro_line|#endif /* __HAVE_ARCH_SIG_BITOPS */
macro_line|#ifndef __HAVE_ARCH_SIG_SETOPS
macro_line|#include &lt;linux/string.h&gt;
DECL|macro|_SIG_SET_BINOP
mdefine_line|#define _SIG_SET_BINOP(name, op)&t;&t;&t;&t;&t;&bslash;&n;static inline void name(sigset_t *r, const sigset_t *a, const sigset_t *b) &bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long a0, a1, a2, a3, b0, b1, b2, b3;&t;&t;&t;&bslash;&n;&t;unsigned long i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; i &lt; _NSIG_WORDS/4; ++i) {&t;&t;&t;&t;&bslash;&n;&t;&t;a0 = a-&gt;sig[4*i+0]; a1 = a-&gt;sig[4*i+1];&t;&t;&t;&bslash;&n;&t;&t;a2 = a-&gt;sig[4*i+2]; a3 = a-&gt;sig[4*i+3];&t;&t;&t;&bslash;&n;&t;&t;b0 = b-&gt;sig[4*i+0]; b1 = b-&gt;sig[4*i+1];&t;&t;&t;&bslash;&n;&t;&t;b2 = b-&gt;sig[4*i+2]; b3 = b-&gt;sig[4*i+3];&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+0] = op(a0, b0);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+1] = op(a1, b1);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+2] = op(a2, b2);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+3] = op(a3, b3);&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (_NSIG_WORDS % 4) {&t;&t;&t;&t;&t;&bslash;&n;&t;    case 3:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;a0 = a-&gt;sig[4*i+0]; a1 = a-&gt;sig[4*i+1]; a2 = a-&gt;sig[4*i+2]; &bslash;&n;&t;&t;b0 = b-&gt;sig[4*i+0]; b1 = b-&gt;sig[4*i+1]; b2 = b-&gt;sig[4*i+2]; &bslash;&n;&t;&t;r-&gt;sig[4*i+0] = op(a0, b0);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+1] = op(a1, b1);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+2] = op(a2, b2);&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case 2:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;a0 = a-&gt;sig[4*i+0]; a1 = a-&gt;sig[4*i+1];&t;&t;&t;&bslash;&n;&t;&t;b0 = b-&gt;sig[4*i+0]; b1 = b-&gt;sig[4*i+1];&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+0] = op(a0, b0);&t;&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+1] = op(a1, b1);&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;    case 1:&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;a0 = a-&gt;sig[4*i+0]; b0 = b-&gt;sig[4*i+0];&t;&t;&t;&bslash;&n;&t;&t;r-&gt;sig[4*i+0] = op(a0, b0);&t;&t;&t;&t;&bslash;&n;&t;&t;break;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_sig_or
mdefine_line|#define _sig_or(x,y)&t;((x) | (y))
id|_SIG_SET_BINOP
c_func
(paren
id|sigorsets
comma
id|_sig_or
)paren
DECL|macro|_sig_and
mdefine_line|#define _sig_and(x,y)&t;((x) &amp; (y))
id|_SIG_SET_BINOP
c_func
(paren
id|sigandsets
comma
id|_sig_and
)paren
DECL|macro|_sig_nand
mdefine_line|#define _sig_nand(x,y)&t;((x) &amp; ~(y))
id|_SIG_SET_BINOP
c_func
(paren
id|signandsets
comma
id|_sig_nand
)paren
DECL|macro|_SIG_SET_BINOP
macro_line|#undef _SIG_SET_BINOP
DECL|macro|_sig_or
macro_line|#undef _sig_or
DECL|macro|_sig_and
macro_line|#undef _sig_and
DECL|macro|_sig_nand
macro_line|#undef _sig_nand
DECL|macro|_SIG_SET_OP
mdefine_line|#define _SIG_SET_OP(name, op)&t;&t;&t;&t;&t;&t;&bslash;&n;static inline void name(sigset_t *set)&t;&t;&t;&t;&t;&bslash;&n;{&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long i;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;for (i = 0; i &lt; _NSIG_WORDS/4; ++i) {&t;&t;&t;&t;&bslash;&n;&t;&t;set-&gt;sig[4*i+0] = op(set-&gt;sig[4*i+0]);&t;&t;&t;&bslash;&n;&t;&t;set-&gt;sig[4*i+1] = op(set-&gt;sig[4*i+1]);&t;&t;&t;&bslash;&n;&t;&t;set-&gt;sig[4*i+2] = op(set-&gt;sig[4*i+2]);&t;&t;&t;&bslash;&n;&t;&t;set-&gt;sig[4*i+3] = op(set-&gt;sig[4*i+3]);&t;&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;switch (_NSIG_WORDS % 4) {&t;&t;&t;&t;&t;&bslash;&n;&t;    case 3: set-&gt;sig[4*i+2] = op(set-&gt;sig[4*i+2]);&t;&t;&bslash;&n;&t;    case 2: set-&gt;sig[4*i+1] = op(set-&gt;sig[4*i+1]);&t;&t;&bslash;&n;&t;    case 1: set-&gt;sig[4*i+0] = op(set-&gt;sig[4*i+0]);&t;&t;&bslash;&n;&t;}&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;}
DECL|macro|_sig_not
mdefine_line|#define _sig_not(x)&t;(~(x))
id|_SIG_SET_OP
c_func
(paren
id|signotset
comma
id|_sig_not
)paren
DECL|macro|_SIG_SET_OP
macro_line|#undef _SIG_SET_OP
DECL|macro|_sig_not
macro_line|#undef _sig_not
DECL|function|sigemptyset
r_static
r_inline
r_void
id|sigemptyset
c_func
(paren
id|sigset_t
op_star
id|set
)paren
(brace
r_switch
c_cond
(paren
id|_NSIG_WORDS
)paren
(brace
r_default
suffix:colon
id|memset
c_func
(paren
id|set
comma
l_int|0
comma
r_sizeof
(paren
id|sigset_t
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|set-&gt;sig
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set-&gt;sig
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|sigfillset
r_static
r_inline
r_void
id|sigfillset
c_func
(paren
id|sigset_t
op_star
id|set
)paren
(brace
r_switch
c_cond
(paren
id|_NSIG_WORDS
)paren
(brace
r_default
suffix:colon
id|memset
c_func
(paren
id|set
comma
op_minus
l_int|1
comma
r_sizeof
(paren
id|sigset_t
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|set-&gt;sig
(braket
l_int|1
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
id|set-&gt;sig
(braket
l_int|0
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_extern
r_char
op_star
id|render_sigset_t
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_char
op_star
id|buffer
)paren
suffix:semicolon
multiline_comment|/* Some extensions for manipulating the low 32 signals in particular.  */
DECL|function|sigaddsetmask
r_static
r_inline
r_void
id|sigaddsetmask
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|mask
)paren
(brace
id|set-&gt;sig
(braket
l_int|0
)braket
op_or_assign
id|mask
suffix:semicolon
)brace
DECL|function|sigdelsetmask
r_static
r_inline
r_void
id|sigdelsetmask
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|mask
)paren
(brace
id|set-&gt;sig
(braket
l_int|0
)braket
op_and_assign
op_complement
id|mask
suffix:semicolon
)brace
DECL|function|sigtestsetmask
r_static
r_inline
r_int
id|sigtestsetmask
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|mask
)paren
(brace
r_return
(paren
id|set-&gt;sig
(braket
l_int|0
)braket
op_amp
id|mask
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|siginitset
r_static
r_inline
r_void
id|siginitset
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|mask
)paren
(brace
id|set-&gt;sig
(braket
l_int|0
)braket
op_assign
id|mask
suffix:semicolon
r_switch
c_cond
(paren
id|_NSIG_WORDS
)paren
(brace
r_default
suffix:colon
id|memset
c_func
(paren
op_amp
id|set-&gt;sig
(braket
l_int|1
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|_NSIG_WORDS
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|set-&gt;sig
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_case
l_int|1
suffix:colon
suffix:semicolon
)brace
)brace
DECL|function|siginitsetinv
r_static
r_inline
r_void
id|siginitsetinv
c_func
(paren
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|mask
)paren
(brace
id|set-&gt;sig
(braket
l_int|0
)braket
op_assign
op_complement
id|mask
suffix:semicolon
r_switch
c_cond
(paren
id|_NSIG_WORDS
)paren
(brace
r_default
suffix:colon
id|memset
c_func
(paren
op_amp
id|set-&gt;sig
(braket
l_int|1
)braket
comma
op_minus
l_int|1
comma
r_sizeof
(paren
r_int
)paren
op_star
(paren
id|_NSIG_WORDS
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|set-&gt;sig
(braket
l_int|1
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_case
l_int|1
suffix:colon
suffix:semicolon
)brace
)brace
macro_line|#endif /* __HAVE_ARCH_SIG_SETOPS */
DECL|function|init_sigpending
r_static
r_inline
r_void
id|init_sigpending
c_func
(paren
r_struct
id|sigpending
op_star
id|sig
)paren
(brace
id|sigemptyset
c_func
(paren
op_amp
id|sig-&gt;signal
)paren
suffix:semicolon
id|sig-&gt;head
op_assign
l_int|NULL
suffix:semicolon
id|sig-&gt;tail
op_assign
op_amp
id|sig-&gt;head
suffix:semicolon
)brace
r_extern
r_int
id|do_sigpending
c_func
(paren
r_void
op_star
comma
r_int
r_int
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _LINUX_SIGNAL_H */
eof
