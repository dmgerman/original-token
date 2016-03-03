macro_line|#ifndef _ASM_IA64_IA32_H
DECL|macro|_ASM_IA64_IA32_H
mdefine_line|#define _ASM_IA64_IA32_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA32_SUPPORT
macro_line|#include &lt;linux/param.h&gt;
multiline_comment|/*&n; * 32 bit structures for IA32 support.&n; */
multiline_comment|/* 32bit compatibility types */
DECL|typedef|__kernel_size_t32
r_typedef
r_int
r_int
id|__kernel_size_t32
suffix:semicolon
DECL|typedef|__kernel_ssize_t32
r_typedef
r_int
id|__kernel_ssize_t32
suffix:semicolon
DECL|typedef|__kernel_ptrdiff_t32
r_typedef
r_int
id|__kernel_ptrdiff_t32
suffix:semicolon
DECL|typedef|__kernel_time_t32
r_typedef
r_int
id|__kernel_time_t32
suffix:semicolon
DECL|typedef|__kernel_clock_t32
r_typedef
r_int
id|__kernel_clock_t32
suffix:semicolon
DECL|typedef|__kernel_pid_t32
r_typedef
r_int
id|__kernel_pid_t32
suffix:semicolon
DECL|typedef|__kernel_ipc_pid_t32
r_typedef
r_int
r_int
id|__kernel_ipc_pid_t32
suffix:semicolon
DECL|typedef|__kernel_uid_t32
r_typedef
r_int
r_int
id|__kernel_uid_t32
suffix:semicolon
DECL|typedef|__kernel_gid_t32
r_typedef
r_int
r_int
id|__kernel_gid_t32
suffix:semicolon
DECL|typedef|__kernel_dev_t32
r_typedef
r_int
r_int
id|__kernel_dev_t32
suffix:semicolon
DECL|typedef|__kernel_ino_t32
r_typedef
r_int
r_int
id|__kernel_ino_t32
suffix:semicolon
DECL|typedef|__kernel_mode_t32
r_typedef
r_int
r_int
id|__kernel_mode_t32
suffix:semicolon
DECL|typedef|__kernel_umode_t32
r_typedef
r_int
r_int
id|__kernel_umode_t32
suffix:semicolon
DECL|typedef|__kernel_nlink_t32
r_typedef
r_int
id|__kernel_nlink_t32
suffix:semicolon
DECL|typedef|__kernel_daddr_t32
r_typedef
r_int
id|__kernel_daddr_t32
suffix:semicolon
DECL|typedef|__kernel_off_t32
r_typedef
r_int
id|__kernel_off_t32
suffix:semicolon
DECL|typedef|__kernel_caddr_t32
r_typedef
r_int
r_int
id|__kernel_caddr_t32
suffix:semicolon
DECL|typedef|__kernel_loff_t32
r_typedef
r_int
id|__kernel_loff_t32
suffix:semicolon
DECL|typedef|__kernel_fsid_t32
r_typedef
id|__kernel_fsid_t
id|__kernel_fsid_t32
suffix:semicolon
DECL|macro|IA32_PAGE_SHIFT
mdefine_line|#define IA32_PAGE_SHIFT&t;&t;12&t;/* 4KB pages */
DECL|macro|IA32_PAGE_SIZE
mdefine_line|#define IA32_PAGE_SIZE&t;&t;(1ULL &lt;&lt; IA32_PAGE_SHIFT)
DECL|macro|IA32_CLOCKS_PER_SEC
mdefine_line|#define IA32_CLOCKS_PER_SEC&t;100&t;/* Cast in stone for IA32 Linux */
DECL|macro|IA32_TICK
mdefine_line|#define IA32_TICK(tick)&t;&t;((unsigned long long)(tick) * IA32_CLOCKS_PER_SEC / CLOCKS_PER_SEC)
multiline_comment|/* fcntl.h */
DECL|struct|flock32
r_struct
id|flock32
(brace
DECL|member|l_type
r_int
id|l_type
suffix:semicolon
DECL|member|l_whence
r_int
id|l_whence
suffix:semicolon
DECL|member|l_start
id|__kernel_off_t32
id|l_start
suffix:semicolon
DECL|member|l_len
id|__kernel_off_t32
id|l_len
suffix:semicolon
DECL|member|l_pid
id|__kernel_pid_t32
id|l_pid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* sigcontext.h */
multiline_comment|/*&n; * As documented in the iBCS2 standard..&n; *&n; * The first part of &quot;struct _fpstate&quot; is just the&n; * normal i387 hardware setup, the extra &quot;status&quot;&n; * word is used to save the coprocessor status word&n; * before entering the handler.&n; */
DECL|struct|_fpreg_ia32
r_struct
id|_fpreg_ia32
(brace
DECL|member|significand
r_int
r_int
id|significand
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|exponent
r_int
r_int
id|exponent
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|_fpstate_ia32
r_struct
id|_fpstate_ia32
(brace
DECL|member|cw
r_int
r_int
id|cw
comma
DECL|member|sw
id|sw
comma
DECL|member|tag
id|tag
comma
DECL|member|ipoff
id|ipoff
comma
DECL|member|cssel
id|cssel
comma
DECL|member|dataoff
id|dataoff
comma
DECL|member|datasel
id|datasel
suffix:semicolon
DECL|member|_st
r_struct
id|_fpreg_ia32
id|_st
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|status
r_int
r_int
id|status
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|sigcontext_ia32
r_struct
id|sigcontext_ia32
(brace
DECL|member|gs
DECL|member|__gsh
r_int
r_int
id|gs
comma
id|__gsh
suffix:semicolon
DECL|member|fs
DECL|member|__fsh
r_int
r_int
id|fs
comma
id|__fsh
suffix:semicolon
DECL|member|es
DECL|member|__esh
r_int
r_int
id|es
comma
id|__esh
suffix:semicolon
DECL|member|ds
DECL|member|__dsh
r_int
r_int
id|ds
comma
id|__dsh
suffix:semicolon
DECL|member|edi
r_int
r_int
id|edi
suffix:semicolon
DECL|member|esi
r_int
r_int
id|esi
suffix:semicolon
DECL|member|ebp
r_int
r_int
id|ebp
suffix:semicolon
DECL|member|esp
r_int
r_int
id|esp
suffix:semicolon
DECL|member|ebx
r_int
r_int
id|ebx
suffix:semicolon
DECL|member|edx
r_int
r_int
id|edx
suffix:semicolon
DECL|member|ecx
r_int
r_int
id|ecx
suffix:semicolon
DECL|member|eax
r_int
r_int
id|eax
suffix:semicolon
DECL|member|trapno
r_int
r_int
id|trapno
suffix:semicolon
DECL|member|err
r_int
r_int
id|err
suffix:semicolon
DECL|member|eip
r_int
r_int
id|eip
suffix:semicolon
DECL|member|cs
DECL|member|__csh
r_int
r_int
id|cs
comma
id|__csh
suffix:semicolon
DECL|member|eflags
r_int
r_int
id|eflags
suffix:semicolon
DECL|member|esp_at_signal
r_int
r_int
id|esp_at_signal
suffix:semicolon
DECL|member|ss
DECL|member|__ssh
r_int
r_int
id|ss
comma
id|__ssh
suffix:semicolon
DECL|member|fpstate
r_int
r_int
id|fpstate
suffix:semicolon
multiline_comment|/* really (struct _fpstate_ia32 *) */
DECL|member|oldmask
r_int
r_int
id|oldmask
suffix:semicolon
DECL|member|cr2
r_int
r_int
id|cr2
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* signal.h */
DECL|macro|_IA32_NSIG
mdefine_line|#define _IA32_NSIG&t;       64
DECL|macro|_IA32_NSIG_BPW
mdefine_line|#define _IA32_NSIG_BPW&t;       32
DECL|macro|_IA32_NSIG_WORDS
mdefine_line|#define _IA32_NSIG_WORDS&t;       (_IA32_NSIG / _IA32_NSIG_BPW)
r_typedef
r_struct
(brace
DECL|member|sig
r_int
r_int
id|sig
(braket
id|_IA32_NSIG_WORDS
)braket
suffix:semicolon
DECL|typedef|sigset32_t
)brace
id|sigset32_t
suffix:semicolon
DECL|struct|sigaction32
r_struct
id|sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal &n;&t;&t;&t;&t;&t;     with 32 bits */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
DECL|member|sa_mask
id|sigset32_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
)brace
suffix:semicolon
DECL|typedef|old_sigset32_t
r_typedef
r_int
r_int
id|old_sigset32_t
suffix:semicolon
multiline_comment|/* at least 32 bits */
DECL|struct|old_sigaction32
r_struct
id|old_sigaction32
(brace
DECL|member|sa_handler
r_int
r_int
id|sa_handler
suffix:semicolon
multiline_comment|/* Really a pointer, but need to deal &n;&t;&t;&t;&t;&t;     with 32 bits */
DECL|member|sa_mask
id|old_sigset32_t
id|sa_mask
suffix:semicolon
multiline_comment|/* A 32 bit mask */
DECL|member|sa_flags
r_int
r_int
id|sa_flags
suffix:semicolon
DECL|member|sa_restorer
r_int
r_int
id|sa_restorer
suffix:semicolon
multiline_comment|/* Another 32 bit pointer */
)brace
suffix:semicolon
DECL|struct|sigaltstack_ia32
r_typedef
r_struct
id|sigaltstack_ia32
(brace
DECL|member|ss_sp
r_int
r_int
id|ss_sp
suffix:semicolon
DECL|member|ss_flags
r_int
id|ss_flags
suffix:semicolon
DECL|member|ss_size
r_int
r_int
id|ss_size
suffix:semicolon
DECL|typedef|stack_ia32_t
)brace
id|stack_ia32_t
suffix:semicolon
DECL|struct|ucontext_ia32
r_struct
id|ucontext_ia32
(brace
DECL|member|uc_flags
r_int
r_int
id|uc_flags
suffix:semicolon
DECL|member|uc_link
r_int
r_int
id|uc_link
suffix:semicolon
DECL|member|uc_stack
id|stack_ia32_t
id|uc_stack
suffix:semicolon
DECL|member|uc_mcontext
r_struct
id|sigcontext_ia32
id|uc_mcontext
suffix:semicolon
DECL|member|uc_sigmask
id|sigset_t
id|uc_sigmask
suffix:semicolon
multiline_comment|/* mask last for extensibility */
)brace
suffix:semicolon
DECL|struct|stat32
r_struct
id|stat32
(brace
DECL|member|st_dev
r_int
r_int
id|st_dev
suffix:semicolon
DECL|member|__pad1
r_int
r_int
id|__pad1
suffix:semicolon
DECL|member|st_ino
r_int
r_int
id|st_ino
suffix:semicolon
DECL|member|st_mode
r_int
r_int
id|st_mode
suffix:semicolon
DECL|member|st_nlink
r_int
r_int
id|st_nlink
suffix:semicolon
DECL|member|st_uid
r_int
r_int
id|st_uid
suffix:semicolon
DECL|member|st_gid
r_int
r_int
id|st_gid
suffix:semicolon
DECL|member|st_rdev
r_int
r_int
id|st_rdev
suffix:semicolon
DECL|member|__pad2
r_int
r_int
id|__pad2
suffix:semicolon
DECL|member|st_size
r_int
r_int
id|st_size
suffix:semicolon
DECL|member|st_blksize
r_int
r_int
id|st_blksize
suffix:semicolon
DECL|member|st_blocks
r_int
r_int
id|st_blocks
suffix:semicolon
DECL|member|st_atime
r_int
r_int
id|st_atime
suffix:semicolon
DECL|member|__unused1
r_int
r_int
id|__unused1
suffix:semicolon
DECL|member|st_mtime
r_int
r_int
id|st_mtime
suffix:semicolon
DECL|member|__unused2
r_int
r_int
id|__unused2
suffix:semicolon
DECL|member|st_ctime
r_int
r_int
id|st_ctime
suffix:semicolon
DECL|member|__unused3
r_int
r_int
id|__unused3
suffix:semicolon
DECL|member|__unused4
r_int
r_int
id|__unused4
suffix:semicolon
DECL|member|__unused5
r_int
r_int
id|__unused5
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|statfs32
r_struct
id|statfs32
(brace
DECL|member|f_type
r_int
id|f_type
suffix:semicolon
DECL|member|f_bsize
r_int
id|f_bsize
suffix:semicolon
DECL|member|f_blocks
r_int
id|f_blocks
suffix:semicolon
DECL|member|f_bfree
r_int
id|f_bfree
suffix:semicolon
DECL|member|f_bavail
r_int
id|f_bavail
suffix:semicolon
DECL|member|f_files
r_int
id|f_files
suffix:semicolon
DECL|member|f_ffree
r_int
id|f_ffree
suffix:semicolon
DECL|member|f_fsid
id|__kernel_fsid_t32
id|f_fsid
suffix:semicolon
DECL|member|f_namelen
r_int
id|f_namelen
suffix:semicolon
multiline_comment|/* SunOS ignores this field. */
DECL|member|f_spare
r_int
id|f_spare
(braket
l_int|6
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|union|sigval32
r_typedef
r_union
id|sigval32
(brace
DECL|member|sival_int
r_int
id|sival_int
suffix:semicolon
DECL|member|sival_ptr
r_int
r_int
id|sival_ptr
suffix:semicolon
DECL|typedef|sigval_t32
)brace
id|sigval_t32
suffix:semicolon
DECL|struct|siginfo32
r_typedef
r_struct
id|siginfo32
(brace
DECL|member|si_signo
r_int
id|si_signo
suffix:semicolon
DECL|member|si_errno
r_int
id|si_errno
suffix:semicolon
DECL|member|si_code
r_int
id|si_code
suffix:semicolon
r_union
(brace
DECL|member|_pad
r_int
id|_pad
(braket
(paren
(paren
l_int|128
op_div
r_sizeof
(paren
r_int
)paren
)paren
op_minus
l_int|3
)paren
)braket
suffix:semicolon
multiline_comment|/* kill() */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_kill
)brace
id|_kill
suffix:semicolon
multiline_comment|/* POSIX.1b timers */
r_struct
(brace
DECL|member|_timer1
r_int
r_int
id|_timer1
suffix:semicolon
DECL|member|_timer2
r_int
r_int
id|_timer2
suffix:semicolon
DECL|member|_timer
)brace
id|_timer
suffix:semicolon
multiline_comment|/* POSIX.1b signals */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* sender&squot;s pid */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_sigval
id|sigval_t32
id|_sigval
suffix:semicolon
DECL|member|_rt
)brace
id|_rt
suffix:semicolon
multiline_comment|/* SIGCHLD */
r_struct
(brace
DECL|member|_pid
r_int
r_int
id|_pid
suffix:semicolon
multiline_comment|/* which child */
DECL|member|_uid
r_int
r_int
id|_uid
suffix:semicolon
multiline_comment|/* sender&squot;s uid */
DECL|member|_status
r_int
id|_status
suffix:semicolon
multiline_comment|/* exit code */
DECL|member|_utime
id|__kernel_clock_t32
id|_utime
suffix:semicolon
DECL|member|_stime
id|__kernel_clock_t32
id|_stime
suffix:semicolon
DECL|member|_sigchld
)brace
id|_sigchld
suffix:semicolon
multiline_comment|/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
r_struct
(brace
DECL|member|_addr
r_int
r_int
id|_addr
suffix:semicolon
multiline_comment|/* faulting insn/memory ref. */
DECL|member|_sigfault
)brace
id|_sigfault
suffix:semicolon
multiline_comment|/* SIGPOLL */
r_struct
(brace
DECL|member|_band
r_int
id|_band
suffix:semicolon
multiline_comment|/* POLL_IN, POLL_OUT, POLL_MSG */
DECL|member|_fd
r_int
id|_fd
suffix:semicolon
DECL|member|_sigpoll
)brace
id|_sigpoll
suffix:semicolon
DECL|member|_sifields
)brace
id|_sifields
suffix:semicolon
DECL|typedef|siginfo_t32
)brace
id|siginfo_t32
suffix:semicolon
multiline_comment|/*&n; * IA-32 ELF specific definitions for IA-64.&n; */
DECL|macro|_ASM_IA64_ELF_H
mdefine_line|#define _ASM_IA64_ELF_H&t;&t;/* Don&squot;t include elf.h */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
multiline_comment|/*&n; * This is used to ensure we don&squot;t load something for the wrong architecture.&n; */
DECL|macro|elf_check_arch
mdefine_line|#define elf_check_arch(x) ((x)-&gt;e_machine == EM_386)
multiline_comment|/*&n; * These are used to set parameters in the core dumps.&n; */
DECL|macro|ELF_CLASS
mdefine_line|#define ELF_CLASS&t;ELFCLASS32
DECL|macro|ELF_DATA
mdefine_line|#define ELF_DATA&t;ELFDATA2LSB
DECL|macro|ELF_ARCH
mdefine_line|#define ELF_ARCH&t;EM_386
DECL|macro|IA32_PAGE_OFFSET
mdefine_line|#define IA32_PAGE_OFFSET&t;0xc0000000
DECL|macro|USE_ELF_CORE_DUMP
mdefine_line|#define USE_ELF_CORE_DUMP
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;IA32_PAGE_SIZE
multiline_comment|/*&n; * This is the location that an ET_DYN program is loaded if exec&squot;ed.&n; * Typical use of this is to invoke &quot;./ld.so someprog&quot; to test out a&n; * new version of the loader.  We need to make sure that it is out of&n; * the way of the program that it will &quot;exec&quot;, and that there is&n; * sufficient room for the brk.&n; */
DECL|macro|ELF_ET_DYN_BASE
mdefine_line|#define ELF_ET_DYN_BASE&t;&t;(IA32_PAGE_OFFSET/3 + 0x1000000)
r_void
id|ia64_elf32_init
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
DECL|macro|ELF_PLAT_INIT
mdefine_line|#define ELF_PLAT_INIT(_r)&t;ia64_elf32_init(_r)
DECL|macro|elf_addr_t
mdefine_line|#define elf_addr_t&t;u32
DECL|macro|elf_caddr_t
mdefine_line|#define elf_caddr_t&t;u32
multiline_comment|/* ELF register definitions.  This is needed for core dump support.  */
DECL|macro|ELF_NGREG
mdefine_line|#define ELF_NGREG&t;128&t;&t;&t;/* XXX fix me */
DECL|macro|ELF_NFPREG
mdefine_line|#define ELF_NFPREG&t;128&t;&t;&t;/* XXX fix me */
DECL|typedef|elf_greg_t
r_typedef
r_int
r_int
id|elf_greg_t
suffix:semicolon
DECL|typedef|elf_gregset_t
r_typedef
id|elf_greg_t
id|elf_gregset_t
(braket
id|ELF_NGREG
)braket
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|w0
r_int
r_int
id|w0
suffix:semicolon
DECL|member|w1
r_int
r_int
id|w1
suffix:semicolon
DECL|typedef|elf_fpreg_t
)brace
id|elf_fpreg_t
suffix:semicolon
DECL|typedef|elf_fpregset_t
r_typedef
id|elf_fpreg_t
id|elf_fpregset_t
(braket
id|ELF_NFPREG
)braket
suffix:semicolon
multiline_comment|/* This macro yields a bitmask that programs can use to figure out&n;   what instruction set this CPU supports.  */
DECL|macro|ELF_HWCAP
mdefine_line|#define ELF_HWCAP &t;0
multiline_comment|/* This macro yields a string that ld.so will use to load&n;   implementation specific libraries for optimization.  Not terribly&n;   relevant until we have real hardware to play with... */
DECL|macro|ELF_PLATFORM
mdefine_line|#define ELF_PLATFORM&t;0
macro_line|#ifdef __KERNEL__
DECL|macro|SET_PERSONALITY
macro_line|# define SET_PERSONALITY(EX,IBCS2)&t;&t;&t;&t;&bslash;&n;&t;(current-&gt;personality = (IBCS2) ? PER_SVR4 : PER_LINUX)
macro_line|#endif
DECL|macro|IA32_EFLAG
mdefine_line|#define IA32_EFLAG&t;0x200
multiline_comment|/*&n; * IA-32 ELF specific definitions for IA-64.&n; */
DECL|macro|__USER_CS
mdefine_line|#define __USER_CS      0x23
DECL|macro|__USER_DS
mdefine_line|#define __USER_DS      0x2B
DECL|macro|SEG_LIM
mdefine_line|#define SEG_LIM     32
DECL|macro|SEG_TYPE
mdefine_line|#define SEG_TYPE    52
DECL|macro|SEG_SYS
mdefine_line|#define SEG_SYS     56
DECL|macro|SEG_DPL
mdefine_line|#define SEG_DPL     57
DECL|macro|SEG_P
mdefine_line|#define SEG_P       59
DECL|macro|SEG_DB
mdefine_line|#define SEG_DB      62
DECL|macro|SEG_G
mdefine_line|#define SEG_G       63
DECL|macro|FIRST_TSS_ENTRY
mdefine_line|#define FIRST_TSS_ENTRY 6
DECL|macro|FIRST_LDT_ENTRY
mdefine_line|#define FIRST_LDT_ENTRY (FIRST_TSS_ENTRY+1)
DECL|macro|_TSS
mdefine_line|#define _TSS(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_TSS_ENTRY&lt;&lt;3))
DECL|macro|_LDT
mdefine_line|#define _LDT(n) ((((unsigned long) n)&lt;&lt;4)+(FIRST_LDT_ENTRY&lt;&lt;3))
DECL|macro|IA64_SEG_DESCRIPTOR
mdefine_line|#define IA64_SEG_DESCRIPTOR(base, limit, segtype, nonsysseg, dpl, segpresent, segdb, granularity) &bslash;&n;&t;       ((base)&t;&t;&t;       |       &bslash;&n;&t;&t;(limit &lt;&lt; SEG_LIM)&t;       |       &bslash;&n;&t;&t;(segtype &lt;&lt; SEG_TYPE)&t;       |       &bslash;&n;&t;&t;(nonsysseg &lt;&lt; SEG_SYS)&t;       |       &bslash;&n;&t;&t;(dpl &lt;&lt; SEG_DPL)&t;       |       &bslash;&n;&t;&t;(segpresent &lt;&lt; SEG_P)&t;       |       &bslash;&n;&t;&t;(segdb &lt;&lt; SEG_DB)&t;       |       &bslash;&n;&t;&t;(granularity &lt;&lt; SEG_G))
DECL|macro|IA32_SEG_BASE
mdefine_line|#define IA32_SEG_BASE 16
DECL|macro|IA32_SEG_TYPE
mdefine_line|#define IA32_SEG_TYPE 40
DECL|macro|IA32_SEG_SYS
mdefine_line|#define IA32_SEG_SYS  44
DECL|macro|IA32_SEG_DPL
mdefine_line|#define IA32_SEG_DPL  45
DECL|macro|IA32_SEG_P
mdefine_line|#define IA32_SEG_P    47
DECL|macro|IA32_SEG_HIGH_LIMIT
mdefine_line|#define IA32_SEG_HIGH_LIMIT    48
DECL|macro|IA32_SEG_AVL
mdefine_line|#define IA32_SEG_AVL   52
DECL|macro|IA32_SEG_DB
mdefine_line|#define IA32_SEG_DB    54
DECL|macro|IA32_SEG_G
mdefine_line|#define IA32_SEG_G     55
DECL|macro|IA32_SEG_HIGH_BASE
mdefine_line|#define IA32_SEG_HIGH_BASE 56
DECL|macro|IA32_SEG_DESCRIPTOR
mdefine_line|#define IA32_SEG_DESCRIPTOR(base, limit, segtype, nonsysseg, dpl, segpresent, avl, segdb, granularity) &bslash;&n;&t;       ((limit &amp; 0xFFFF)&t;&t;&t;       |       &bslash;&n;&t;&t; (base &amp; 0xFFFFFF &lt;&lt; IA32_SEG_BASE)&t;       |       &bslash;&n;&t;&t;(segtype &lt;&lt; IA32_SEG_TYPE)&t;&t;       |       &bslash;&n;&t;&t;(nonsysseg &lt;&lt; IA32_SEG_SYS)&t;&t;       |       &bslash;&n;&t;&t;(dpl &lt;&lt; IA32_SEG_DPL)&t;&t;&t;       |       &bslash;&n;&t;&t;(segpresent &lt;&lt; IA32_SEG_P)&t;&t;       |       &bslash;&n;&t;&t;(((limit &gt;&gt; 16) &amp; 0xF) &lt;&lt; IA32_SEG_HIGH_LIMIT) |       &bslash;&n;&t;&t;(avl &lt;&lt; IA32_SEG_AVL)&t;&t;&t;       |       &bslash;&n;&t;&t;(segdb &lt;&lt; IA32_SEG_DB)&t;&t;&t;       |       &bslash;&n;&t;&t;(granularity &lt;&lt; IA32_SEG_G)&t;&t;       |       &bslash;&n;&t;&t;(((base &gt;&gt; 24) &amp; 0xFF) &lt;&lt; IA32_SEG_HIGH_BASE)) 
DECL|macro|IA32_IOBASE
mdefine_line|#define IA32_IOBASE    0x2000000000000000 /* Virtual addres for I/O space */
DECL|macro|IA32_CR0
mdefine_line|#define IA32_CR0       0x80000001      /* Enable PG and PE bits */
DECL|macro|IA32_CR4
mdefine_line|#define IA32_CR4       0&t;       /* No architectural extensions */
multiline_comment|/*&n; *  IA32 floating point control registers starting values&n; */
DECL|macro|IA32_FSR_DEFAULT
mdefine_line|#define IA32_FSR_DEFAULT&t;0x55550000&t;&t;/* set all tag bits */
DECL|macro|IA32_FCR_DEFAULT
mdefine_line|#define IA32_FCR_DEFAULT&t;0x17800000037fULL&t;/* extended precision, all masks */
DECL|macro|IA32_PTRACE_GETREGS
mdefine_line|#define IA32_PTRACE_GETREGS&t;12
DECL|macro|IA32_PTRACE_SETREGS
mdefine_line|#define IA32_PTRACE_SETREGS&t;13
DECL|macro|IA32_PTRACE_GETFPREGS
mdefine_line|#define IA32_PTRACE_GETFPREGS&t;14
DECL|macro|IA32_PTRACE_SETFPREGS
mdefine_line|#define IA32_PTRACE_SETFPREGS&t;15
DECL|macro|ia32_start_thread
mdefine_line|#define ia32_start_thread(regs,new_ip,new_sp) do {&t;&t;&t;&t;&bslash;&n;&t;set_fs(USER_DS);&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;cpl = 3;&t;/* set user mode */&t;&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;ri = 0;&t;&t;/* clear return slot number */&t;&t;&bslash;&n;&t;ia64_psr(regs)-&gt;is = 1;&t;&t;/* IA-32 instruction set */&t;&t;&bslash;&n;&t;regs-&gt;cr_iip = new_ip;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;r12 = new_sp;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;ar_rnat = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;regs-&gt;loadrs = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
r_extern
r_void
id|ia32_gdt_init
(paren
r_void
)paren
suffix:semicolon
r_extern
r_int
id|ia32_setup_frame1
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_void
id|ia32_init_addr_space
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_extern
r_int
id|ia32_setup_arg_pages
(paren
r_struct
id|linux_binprm
op_star
id|bprm
)paren
suffix:semicolon
r_extern
r_int
id|ia32_exception
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|isr
)paren
suffix:semicolon
macro_line|#endif /* !CONFIG_IA32_SUPPORT */
macro_line|#endif /* _ASM_IA64_IA32_H */
eof
