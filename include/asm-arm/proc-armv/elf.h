multiline_comment|/*&n; * ELF definitions for 32-bit CPUs&n; */
DECL|macro|ELF_EXEC_PAGESIZE
mdefine_line|#define ELF_EXEC_PAGESIZE&t;4096
multiline_comment|/* We can execute both 32-bit and 26-bit code. */
DECL|macro|ELF_PROC_OK
mdefine_line|#define ELF_PROC_OK(x)&t;&t;(1)
macro_line|#ifdef __KERNEL__
macro_line|#if 0&t;&t;/* not yet */
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) &bslash;&n;&t;current_personality = (ex-&gt;e_flags &amp; EF_ARM_APCS26) ? &bslash;&n;&t;PER_LINUX : PER_LINUX_32BIT
macro_line|#else
DECL|macro|SET_PERSONALITY
mdefine_line|#define SET_PERSONALITY(ex,ibcs2) &bslash;&n;&t;current-&gt;personality = PER_LINUX_32BIT
macro_line|#endif
macro_line|#endif
eof
