multiline_comment|/*&n; * Linux/MIPS specific definitions for signals.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 1996 by Ralf Baechle&n; */
macro_line|#ifndef __ASM_MIPS_SIGNAL_H
macro_line|#include &lt;asm/sgidefs.h&gt;
multiline_comment|/* Any one of these symbols __need_* means that GNU libc&n;   wants us just to define one data type.  So don&squot;t define&n;   the symbols that indicate this file&squot;s entire job has been done.  */
macro_line|#if !defined(__need_signums) &amp;&amp; !defined(__need_fake_sigfuns) &amp;&amp; &bslash;&n;    !defined(__need__nsig)
DECL|macro|__ASM_MIPS_SIGNAL_H
mdefine_line|#define __ASM_MIPS_SIGNAL_H
macro_line|#endif
macro_line|#ifdef __ASM_MIPS_SIGNAL_H
DECL|typedef|sigset_t
r_typedef
r_int
r_int
id|sigset_t
suffix:semicolon
macro_line|#endif /* __ASM_MIPS_SIGNAL_H */
macro_line|#if !defined (___nsig_defined) &amp;&amp; &bslash;&n;    (defined (__ASM_MIPS_SIGNAL_H) || defined (__need__nsig))
DECL|macro|___nsig_defined
mdefine_line|#define ___nsig_defined
DECL|macro|_NSIG
mdefine_line|#define _NSIG&t;&t;65
macro_line|#endif
DECL|macro|__need__nsig
macro_line|#undef __need__nsig
macro_line|#ifdef __KERNEL__
DECL|macro|NSIG
mdefine_line|#define NSIG&t;&t;_NSIG
macro_line|#endif
macro_line|#if !defined (__signums_defined) &amp;&amp; &bslash;&n;    (defined (__ASM_MIPS_SIGNAL_H) || defined (__need_signums))
DECL|macro|__signums_defined
mdefine_line|#define __signums_defined
multiline_comment|/*&n; * For 1.3.0 Linux/MIPS changed the signal numbers to be compatible the ABI.&n; */
DECL|macro|SIGHUP
mdefine_line|#define SIGHUP&t;&t; 1&t;/* Hangup (POSIX).  */
DECL|macro|SIGINT
mdefine_line|#define SIGINT&t;&t; 2&t;/* Interrupt (ANSI).  */
DECL|macro|SIGQUIT
mdefine_line|#define SIGQUIT&t;&t; 3&t;/* Quit (POSIX).  */
DECL|macro|SIGILL
mdefine_line|#define SIGILL&t;&t; 4&t;/* Illegal instruction (ANSI).  */
DECL|macro|SIGTRAP
mdefine_line|#define SIGTRAP&t;&t; 5&t;/* Trace trap (POSIX).  */
DECL|macro|SIGIOT
mdefine_line|#define SIGIOT&t;&t; 6&t;/* IOT trap (4.2 BSD).  */
DECL|macro|SIGABRT
mdefine_line|#define SIGABRT&t;&t; SIGIOT&t;/* Abort (ANSI).  */
DECL|macro|SIGEMT
mdefine_line|#define SIGEMT&t;&t; 7
DECL|macro|SIGFPE
mdefine_line|#define SIGFPE&t;&t; 8&t;/* Floating-point exception (ANSI).  */
DECL|macro|SIGKILL
mdefine_line|#define SIGKILL&t;&t; 9&t;/* Kill, unblockable (POSIX).  */
DECL|macro|SIGBUS
mdefine_line|#define SIGBUS&t;&t;10&t;/* BUS error (4.2 BSD).  */
DECL|macro|SIGSEGV
mdefine_line|#define SIGSEGV&t;&t;11&t;/* Segmentation violation (ANSI).  */
DECL|macro|SIGSYS
mdefine_line|#define SIGSYS&t;&t;12
DECL|macro|SIGPIPE
mdefine_line|#define SIGPIPE&t;&t;13&t;/* Broken pipe (POSIX).  */
DECL|macro|SIGALRM
mdefine_line|#define SIGALRM&t;&t;14&t;/* Alarm clock (POSIX).  */
DECL|macro|SIGTERM
mdefine_line|#define SIGTERM&t;&t;15&t;/* Termination (ANSI).  */
DECL|macro|SIGUSR1
mdefine_line|#define SIGUSR1&t;&t;16&t;/* User-defined signal 1 (POSIX).  */
DECL|macro|SIGUSR2
mdefine_line|#define SIGUSR2&t;&t;17&t;/* User-defined signal 2 (POSIX).  */
DECL|macro|SIGCHLD
mdefine_line|#define SIGCHLD&t;&t;18&t;/* Child status has changed (POSIX).  */
DECL|macro|SIGCLD
mdefine_line|#define SIGCLD&t;&t;SIGCHLD&t;/* Same as SIGCHLD (System V).  */
DECL|macro|SIGPWR
mdefine_line|#define SIGPWR&t;&t;19&t;/* Power failure restart (System V).  */
DECL|macro|SIGWINCH
mdefine_line|#define SIGWINCH&t;20&t;/* Window size change (4.3 BSD, Sun).  */
DECL|macro|SIGURG
mdefine_line|#define SIGURG&t;&t;21&t;/* Urgent condition on socket (4.2 BSD).  */
DECL|macro|SIGIO
mdefine_line|#define SIGIO&t;&t;22&t;/* I/O now possible (4.2 BSD).  */
DECL|macro|SIGPOLL
mdefine_line|#define SIGPOLL&t;&t;SIGIO&t;/* Pollable event occurred (System V).  */
DECL|macro|SIGSTOP
mdefine_line|#define SIGSTOP&t;&t;23&t;/* Stop, unblockable (POSIX).  */
DECL|macro|SIGTSTP
mdefine_line|#define SIGTSTP&t;&t;24&t;/* Keyboard stop (POSIX).  */
DECL|macro|SIGCONT
mdefine_line|#define SIGCONT&t;&t;25&t;/* Continue (POSIX).  */
DECL|macro|SIGTTIN
mdefine_line|#define SIGTTIN&t;&t;26&t;/* Background read from tty (POSIX).  */
DECL|macro|SIGTTOU
mdefine_line|#define SIGTTOU&t;&t;27&t;/* Background write to tty (POSIX).  */
DECL|macro|SIGVTALRM
mdefine_line|#define SIGVTALRM&t;28&t;/* Virtual alarm clock (4.2 BSD).  */
DECL|macro|SIGPROF
mdefine_line|#define SIGPROF&t;&t;29&t;/* Profiling alarm clock (4.2 BSD).  */
DECL|macro|SIGXCPU
mdefine_line|#define SIGXCPU&t;&t;30&t;/* CPU limit exceeded (4.2 BSD).  */
DECL|macro|SIGXFSZ
mdefine_line|#define SIGXFSZ&t;&t;31&t;/* File size limit exceeded (4.2 BSD).  */
macro_line|#endif /* need signums */
DECL|macro|__need_signums
macro_line|#undef __need_signums
macro_line|#ifdef __ASM_MIPS_SIGNAL_H
multiline_comment|/*&n; * sa_flags values: SA_STACK is not currently supported, but will allow the&n; * usage of signal stacks by using the (now obsolete) sa_restorer field in&n; * the sigaction structure as a stack pointer. This is now possible due to&n; * the changes in signal handling. LBT 010493.&n; * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the&n; * SA_RESTART flag to get restarting signals (which were the default long ago)&n; * SA_SHIRQ flag is for shared interrupt support on PCI and EISA.&n; */
DECL|macro|SA_STACK
mdefine_line|#define SA_STACK&t;0x1
DECL|macro|SA_ONSTACK
mdefine_line|#define SA_ONSTACK&t;SA_STACK
DECL|macro|SA_RESTART
mdefine_line|#define SA_RESTART&t;0x4
DECL|macro|SA_NOCLDSTOP
mdefine_line|#define SA_NOCLDSTOP&t;0x20000
multiline_comment|/* Non ABI signals */
DECL|macro|SA_INTERRUPT
mdefine_line|#define SA_INTERRUPT&t;0x01000000
DECL|macro|SA_NOMASK
mdefine_line|#define SA_NOMASK&t;0x02000000
DECL|macro|SA_ONESHOT
mdefine_line|#define SA_ONESHOT&t;0x04000000
DECL|macro|SA_SHIRQ
mdefine_line|#define SA_SHIRQ&t;0x08000000
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * These values of sa_flags are used only by the kernel as part of the&n; * irq handling routines.&n; *&n; * SA_INTERRUPT is also used by the irq handling routines.&n; */
DECL|macro|SA_PROBE
mdefine_line|#define SA_PROBE SA_ONESHOT
DECL|macro|SA_SAMPLE_RANDOM
mdefine_line|#define SA_SAMPLE_RANDOM SA_RESTART
macro_line|#endif /* __KERNEL__ */
DECL|macro|SIG_BLOCK
mdefine_line|#define SIG_BLOCK&t;1&t;/* for blocking signals */
DECL|macro|SIG_UNBLOCK
mdefine_line|#define SIG_UNBLOCK&t;2&t;/* for unblocking signals */
DECL|macro|SIG_SETMASK
mdefine_line|#define SIG_SETMASK&t;3&t;/* for setting the signal mask */
DECL|macro|SIG_SETMASK32
mdefine_line|#define SIG_SETMASK32&t;256&t;/* Goodie from SGI for BSD compatibility:&n;&t;&t;&t;&t;   set only the low 32 bit of the sigset.  */
macro_line|#ifndef __sighandler_t_defined
DECL|macro|__sighandler_t_defined
mdefine_line|#define __sighandler_t_defined
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
macro_line|#endif
macro_line|#endif
macro_line|#if !defined (__fake_sigfuns_defined) &amp;&amp; &bslash;&n;    (defined (__ASM_MIPS_SIGNAL_H) || defined (__need_fake_sigfuns))
DECL|macro|__fake_sigfuns_defined
mdefine_line|#define __fake_sigfuns_defined
multiline_comment|/* Fake signal functions */
DECL|macro|SIG_DFL
mdefine_line|#define SIG_DFL&t;((__sighandler_t)0)&t;/* default signal handling */
DECL|macro|SIG_IGN
mdefine_line|#define SIG_IGN&t;((__sighandler_t)1)&t;/* ignore signal */
DECL|macro|SIG_ERR
mdefine_line|#define SIG_ERR&t;((__sighandler_t)-1)&t;/* error return from signal */
macro_line|#endif
DECL|macro|__need_fake_sigfuns
macro_line|#undef __need_fake_sigfuns
macro_line|#ifdef __ASM_MIPS_SIGNAL_H
DECL|struct|sigaction
r_struct
id|sigaction
(brace
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_handler
id|__sighandler_t
id|sa_handler
suffix:semicolon
DECL|member|sa_mask
id|sigset_t
id|sa_mask
suffix:semicolon
DECL|member|__pad0
r_int
r_int
id|__pad0
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/* reserved, keep size constant */
multiline_comment|/* Abi says here follows reserved int[2] */
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
macro_line|#if (_MIPS_ISA == _MIPS_ISA_MIPS1) || (_MIPS_ISA == _MIPS_ISA_MIPS2)
multiline_comment|/*&n;&t; * For 32 bit code we have to pad struct sigaction to get&n;&t; * constant size for the ABI&n;&t; */
DECL|member|__pad1
r_int
id|__pad1
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* reserved */
macro_line|#endif
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#endif
macro_line|#if defined (__KERNEL__) || defined (__USE_MISC)
multiline_comment|/*&n; * The following break codes are or were in use for specific purposes in&n; * other MIPS operating systems.  Linux/MIPS doesn&squot;t use all of them.  The&n; * unused ones are here as placeholders; we might encounter them in&n; * non-Linux/MIPS object files or make use of them in the future.&n; */
DECL|macro|BRK_USERBP
mdefine_line|#define BRK_USERBP&t;0&t;/* User bp (used by debuggers) */
DECL|macro|BRK_KERNELBP
mdefine_line|#define BRK_KERNELBP&t;1&t;/* Break in the kernel */
DECL|macro|BRK_ABORT
mdefine_line|#define BRK_ABORT&t;2&t;/* Sometimes used by abort(3) to SIGIOT */
DECL|macro|BRK_BD_TAKEN
mdefine_line|#define BRK_BD_TAKEN&t;3&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_BD_NOTTAKEN
mdefine_line|#define BRK_BD_NOTTAKEN&t;4&t;/* For bd slot emulation - not implemented */
DECL|macro|BRK_SSTEPBP
mdefine_line|#define BRK_SSTEPBP&t;5&t;/* User bp (used by debuggers) */
DECL|macro|BRK_OVERFLOW
mdefine_line|#define BRK_OVERFLOW&t;6&t;/* Overflow check */
DECL|macro|BRK_DIVZERO
mdefine_line|#define BRK_DIVZERO&t;7&t;/* Divide by zero check */
DECL|macro|BRK_RANGE
mdefine_line|#define BRK_RANGE&t;8&t;/* Range error check */
DECL|macro|BRK_STACKOVERFLOW
mdefine_line|#define BRK_STACKOVERFLOW 9&t;/* For Ada stackchecking */
DECL|macro|BRK_NORLD
mdefine_line|#define BRK_NORLD&t;10&t;/* No rld found - not used by Linux/MIPS */
DECL|macro|_BRK_THREADBP
mdefine_line|#define _BRK_THREADBP&t;11&t;/* For threads, user bp (used by debuggers) */
DECL|macro|BRK_MULOVF
mdefine_line|#define BRK_MULOVF&t;1023&t;/* Multiply overflow */
macro_line|#endif /* defined (__KERNEL__) || defined (__USE_MISC) */
macro_line|#endif /* defined (__ASM_MIPS_SIGNAL_H) */
macro_line|#endif /* !defined (__ASM_MIPS_SIGNAL_H) */
eof
