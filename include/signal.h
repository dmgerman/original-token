macro_line|#ifndef _SIGNAL_H
DECL|macro|_SIGNAL_H
mdefine_line|#define _SIGNAL_H
macro_line|#include &lt;sys/types.h&gt;
DECL|typedef|sig_atomic_t
r_typedef
r_int
id|sig_atomic_t
suffix:semicolon
DECL|typedef|sigset_t
r_typedef
r_int
r_int
id|sigset_t
suffix:semicolon
multiline_comment|/* 32 bits */
DECL|macro|_NSIG
mdefine_line|#define _NSIG             32
DECL|macro|NSIG
mdefine_line|#define NSIG&t;&t;_NSIG
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
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;&t; 6
DECL|macro|SIGUNUSED
mdefine_line|#define SIGUNUSED&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;10
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15
DECL|macro|SIGSTKFLT
mdefine_line|#define SIGSTKFLT&t;16
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;17
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;18
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;19
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;20
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;21
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;22
multiline_comment|/*&n; * Most of these aren&squot;t used yet (and perhaps never will),&n; * so they are commented out.&n; */
multiline_comment|/*&n;#define SIGIO&t;&t;23&n;#define SIGPOLL&t;&t;SIGIO&n;#define SIGXCPU&t;&t;24&n;#define SIGXFSZ&t;&t;25&n;*/
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM&t;26
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF&t;&t;27
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH&t;28
multiline_comment|/*&n;#define SIGLOST&t;&t;29&n;*/
multiline_comment|/* Ok, I haven&squot;t implemented sigactions, but trying to keep headers POSIX */
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;1
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x20000000
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;0x40000000
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;0x80000000
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK          0&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK        1&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK        2&t;/* for setting the signal mask */
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;&t;((void (*)(int))0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;&t;((void (*)(int))1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;&t;((void (*)(int))-1)&t;/* error return from signal */
macro_line|#ifdef notdef
DECL|macro|sigemptyset
mdefine_line|#define sigemptyset(mask) ((*(mask) = 0), 1)
DECL|macro|sigfillset
mdefine_line|#define sigfillset(mask) ((*(mask) = ~0), 1)
macro_line|#endif
DECL|struct|sigaction
r_struct
id|sigaction
(brace
DECL|member|sa_handler
r_void
(paren
op_star
id|sa_handler
)paren
(paren
r_int
)paren
suffix:semicolon
DECL|member|sa_mask
id|sigset_t
id|sa_mask
suffix:semicolon
DECL|member|sa_flags
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_void
(paren
op_star
id|sa_restorer
)paren
(paren
r_void
)paren
suffix:semicolon
)brace
suffix:semicolon
r_void
(paren
op_star
id|signal
c_func
(paren
r_int
id|_sig
comma
r_void
(paren
op_star
id|_func
)paren
(paren
r_int
)paren
)paren
)paren
(paren
r_int
)paren
suffix:semicolon
r_int
id|raise
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
r_int
id|kill
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|sig
)paren
suffix:semicolon
r_int
id|sigaddset
c_func
(paren
id|sigset_t
op_star
id|mask
comma
r_int
id|signo
)paren
suffix:semicolon
r_int
id|sigdelset
c_func
(paren
id|sigset_t
op_star
id|mask
comma
r_int
id|signo
)paren
suffix:semicolon
r_int
id|sigemptyset
c_func
(paren
id|sigset_t
op_star
id|mask
)paren
suffix:semicolon
r_int
id|sigfillset
c_func
(paren
id|sigset_t
op_star
id|mask
)paren
suffix:semicolon
r_int
id|sigismember
c_func
(paren
id|sigset_t
op_star
id|mask
comma
r_int
id|signo
)paren
suffix:semicolon
multiline_comment|/* 1 - is, 0 - not, -1 error */
r_int
id|sigpending
c_func
(paren
id|sigset_t
op_star
id|set
)paren
suffix:semicolon
r_int
id|sigprocmask
c_func
(paren
r_int
id|how
comma
id|sigset_t
op_star
id|set
comma
id|sigset_t
op_star
id|oldset
)paren
suffix:semicolon
r_int
id|sigsuspend
c_func
(paren
id|sigset_t
op_star
id|sigmask
)paren
suffix:semicolon
r_int
id|sigaction
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigaction
op_star
id|act
comma
r_struct
id|sigaction
op_star
id|oldact
)paren
suffix:semicolon
macro_line|#endif /* _SIGNAL_H */
eof
