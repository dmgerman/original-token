macro_line|#ifndef _ASMAXP_SIGNAL_H
DECL|macro|_ASMAXP_SIGNAL_H
mdefine_line|#define _ASMAXP_SIGNAL_H
DECL|typedef|sigset_t
r_typedef
r_int
r_int
id|sigset_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
DECL|macro|_NSIG
mdefine_line|#define _NSIG             32
DECL|macro|NSIG
mdefine_line|#define NSIG&t;&t;_NSIG
multiline_comment|/*&n; * Linux/AXP has different signal numbers that Linux/i386: I&squot;m trying&n; * to make it OSF/1 binary compatible, at least for normal binaries.&n; */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP&t;&t; 1
DECL|macro|SIGINT
mdefine_line|#define SIGINT&t;&t; 2
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT&t;&t; 3
DECL|macro|SIGILL
mdefine_line|#define SIGILL&t;&t; 4
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP&t;&t; 5
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT&t;&t; 6
DECL|macro|SIGEMT
mdefine_line|#define SIGEMT&t;&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS&t;&t;10
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15
DECL|macro|SIGURG
mdefine_line|#define SIGURG&t;&t;16
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;17
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;18
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;19
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;20
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;21
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;22
DECL|macro|SIGIO
mdefine_line|#define SIGIO&t;&t;23
DECL|macro|SIGXCPU
mdefine_line|#define SIGXCPU&t;&t;24
DECL|macro|SIGXFSZ
mdefine_line|#define SIGXFSZ&t;&t;25
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM&t;26
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF&t;&t;27
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH&t;28
DECL|macro|SIGINFO
mdefine_line|#define SIGINFO&t;&t;29
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;30
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;31
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;SIGIO
multiline_comment|/*&n; * sa_flags values: SA_STACK is not currently supported, but will allow the&n; * usage of signal stacks by using the (now obsolete) sa_restorer field in&n; * the sigaction structure as a stack pointer. This is now possible due to&n; * the changes in signal handling. LBT 010493.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;0x00000004
DECL|macro|SA_STACK
mdefine_line|#define SA_STACK&t;0x00000001
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;0x00000002
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x20000000
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;0x00000008
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;0x00000010
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          1&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        2&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        3&t;/* for setting the signal mask */
multiline_comment|/* Type of a signal handler.  */
DECL|typedef|__sighandler_t
r_typedef
r_void
(paren
op_star
id|__sighandler_t
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;((__sighandler_t)0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;((__sighandler_t)1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;((__sighandler_t)-1)&t;/* error return from signal */
DECL|struct|sigaction
r_struct
id|sigaction
(brace
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
DECL|struct|sigcontext_struct
r_struct
id|sigcontext_struct
(brace
multiline_comment|/*&n;&t; * what should we have here? I&squot;d probably better use the same&n;&t; * stack layout as OSF/1, just in case we ever want to try&n;&t; * running their binaries.. &n;&t; *&n;&t; * This is the basic layout, but I don&squot;t know if we&squot;ll ever&n;&t; * actually fill in all the values..&n;&t; */
DECL|member|sc_onstack
r_int
id|sc_onstack
suffix:semicolon
DECL|member|sc_mask
r_int
id|sc_mask
suffix:semicolon
DECL|member|sc_pc
r_int
id|sc_pc
suffix:semicolon
DECL|member|sc_ps
r_int
id|sc_ps
suffix:semicolon
DECL|member|sc_regs
r_int
id|sc_regs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_ownedfp
r_int
id|sc_ownedfp
suffix:semicolon
DECL|member|sc_fpregs
r_int
id|sc_fpregs
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sc_fpcr
r_int
r_int
id|sc_fpcr
suffix:semicolon
DECL|member|sc_fp_control
r_int
r_int
id|sc_fp_control
suffix:semicolon
DECL|member|sc_reserved1
DECL|member|sc_reserved2
r_int
r_int
id|sc_reserved1
comma
id|sc_reserved2
suffix:semicolon
DECL|member|sc_ssize
r_int
r_int
id|sc_ssize
suffix:semicolon
DECL|member|sc_sbase
r_char
op_star
id|sc_sbase
suffix:semicolon
DECL|member|sc_traparg_a0
r_int
r_int
id|sc_traparg_a0
suffix:semicolon
DECL|member|sc_traparg_a1
r_int
r_int
id|sc_traparg_a1
suffix:semicolon
DECL|member|sc_traparg_a2
r_int
r_int
id|sc_traparg_a2
suffix:semicolon
DECL|member|sc_fp_trap_pc
r_int
r_int
id|sc_fp_trap_pc
suffix:semicolon
DECL|member|sc_fp_trigger_sum
r_int
r_int
id|sc_fp_trigger_sum
suffix:semicolon
DECL|member|sc_fp_trigger_inst
r_int
r_int
id|sc_fp_trigger_inst
suffix:semicolon
DECL|member|sc_retcode
r_int
r_int
id|sc_retcode
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
