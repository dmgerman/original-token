macro_line|#ifndef __ASM_MIPS_PARAM_H
DECL|macro|__ASM_MIPS_PARAM_H
mdefine_line|#define __ASM_MIPS_PARAM_H
macro_line|#ifndef HZ
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_DECSTATION
multiline_comment|/*&n;    * log2(HZ), change this here if you want another&n;    * HZ value. This is also used in dec_time_init.&n;    * Minimum is 1, Maximum is 15.&n;    */
DECL|macro|LOG_2_HZ
macro_line|#  define LOG_2_HZ 7
DECL|macro|HZ
macro_line|#  define HZ (1 &lt;&lt; LOG_2_HZ)
multiline_comment|/*&n;    * Ye olde division-by-multiplication trick.&n;    *&n;    * This works only if 100 / HZ &lt;= 1&n;    */
DECL|macro|QUOTIENT
macro_line|#  define QUOTIENT ((1UL &lt;&lt; (32 - LOG_2_HZ)) * 100)
DECL|macro|HZ_TO_STD
macro_line|#  define HZ_TO_STD(a)                            &bslash;&n;   ({ int __res;                                  &bslash;&n;        __asm__(                                  &bslash;&n;           &quot;multu&bslash;t%0,%2&bslash;n&bslash;t&quot;&t;&t;&t;  &bslash;&n;           &quot;mfhi&bslash;t%0&quot;&t;&t;&t;&t;  &bslash;&n;        : &quot;=r&quot; (__res): &quot;0&quot; (a), &quot;r&quot; (QUOTIENT)); &bslash;&n;        __res;})
macro_line|#else
DECL|macro|HZ
macro_line|#  define HZ 100
DECL|macro|HZ_TO_STD
macro_line|#  define HZ_TO_STD(a) (a)
macro_line|#endif
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS&t;&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP&t;&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#endif /* __ASM_MIPS_PARAM_H */
eof
