multiline_comment|/*&n;** asm/setup.h -- Definition of the Linux/m68k setup information&n;**&n;** Copyright 1992 by Greg Harp&n;**&n;** This file is subject to the terms and conditions of the GNU General Public&n;** License.  See the file COPYING in the main directory of this archive&n;** for more details.&n;**&n;** Created 09/29/92 by Greg Harp&n;**&n;** 5/2/94 Roman Hodek:&n;**   Added bi_atari part of the machine dependent union bi_un; for now it&n;**   contains just a model field to distinguish between TT and Falcon.&n;** 26/7/96 Roman Zippel:&n;**   Renamed to setup.h; added some useful macros to allow gcc some&n;**   optimizations if possible.&n;** 5/10/96 Geert Uytterhoeven:&n;**   Redesign of the boot information structure; moved boot information&n;**   structure to bootinfo.h&n;*/
macro_line|#ifndef _M68K_SETUP_H
DECL|macro|_M68K_SETUP_H
mdefine_line|#define _M68K_SETUP_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n;     *  Linux/m68k Architectures&n;     */
DECL|macro|MACH_AMIGA
mdefine_line|#define MACH_AMIGA   1
DECL|macro|MACH_ATARI
mdefine_line|#define MACH_ATARI   2
DECL|macro|MACH_MAC
mdefine_line|#define MACH_MAC     3
DECL|macro|MACH_APOLLO
mdefine_line|#define MACH_APOLLO  4
DECL|macro|MACH_SUN3
mdefine_line|#define MACH_SUN3    5
multiline_comment|/* MVME 166/167/162/147?? */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
id|u_long
id|m68k_machtype
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#if !defined(CONFIG_AMIGA)
DECL|macro|MACH_IS_AMIGA
macro_line|#  define MACH_IS_AMIGA (0)
macro_line|#elif defined(CONFIG_ATARI) || defined(CONFIG_MAC)
DECL|macro|MACH_IS_AMIGA
macro_line|#  define MACH_IS_AMIGA (m68k_machtype == MACH_AMIGA)
macro_line|#else
DECL|macro|MACH_AMIGA_ONLY
macro_line|#  define MACH_AMIGA_ONLY
DECL|macro|MACH_IS_AMIGA
macro_line|#  define MACH_IS_AMIGA (1)
DECL|macro|MACH_TYPE
macro_line|#  define MACH_TYPE (MACH_AMIGA)
macro_line|#endif
macro_line|#if !defined(CONFIG_ATARI)
DECL|macro|MACH_IS_ATARI
macro_line|#  define MACH_IS_ATARI (0)
macro_line|#elif defined(CONFIG_AMIGA) || defined(CONFIG_MAC)
DECL|macro|MACH_IS_ATARI
macro_line|#  define MACH_IS_ATARI (m68k_machtype == MACH_ATARI)
macro_line|#else
DECL|macro|MACH_ATARI_ONLY
macro_line|#  define MACH_ATARI_ONLY
DECL|macro|MACH_IS_ATARI
macro_line|#  define MACH_IS_ATARI (1)
DECL|macro|MACH_TYPE
macro_line|#  define MACH_TYPE (MACH_ATARI)
macro_line|#endif
macro_line|#if defined(CONFIG_MAC)
macro_line|#  error Currently no Mac support!
macro_line|#endif
macro_line|#if defined(CONFIG_SUN3)
macro_line|#  error Currently no Sun-3 support!
macro_line|#endif
macro_line|#if defined(CONFIG_APOLLO)
macro_line|#  error Currently no Apollo support!
macro_line|#endif
macro_line|#ifndef MACH_TYPE
DECL|macro|MACH_TYPE
macro_line|#  define MACH_TYPE (m68k_machtype)
macro_line|#endif
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n;     *  CPU, FPU and MMU types&n;     *&n;     *  Note: we may rely on the following equalities:&n;     *&n;     *      CPU_68020 == MMU_68851&n;     *      CPU_68030 == MMU_68030&n;     *      CPU_68040 == FPU_68040 == MMU_68040&n;     *      CPU_68060 == FPU_68060 == MMU_68060&n;     */
DECL|macro|CPUB_68020
mdefine_line|#define CPUB_68020     0
DECL|macro|CPUB_68030
mdefine_line|#define CPUB_68030     1
DECL|macro|CPUB_68040
mdefine_line|#define CPUB_68040     2
DECL|macro|CPUB_68060
mdefine_line|#define CPUB_68060     3
DECL|macro|CPU_68020
mdefine_line|#define CPU_68020      (1&lt;&lt;CPUB_68020)
DECL|macro|CPU_68030
mdefine_line|#define CPU_68030      (1&lt;&lt;CPUB_68030)
DECL|macro|CPU_68040
mdefine_line|#define CPU_68040      (1&lt;&lt;CPUB_68040)
DECL|macro|CPU_68060
mdefine_line|#define CPU_68060      (1&lt;&lt;CPUB_68060)
DECL|macro|FPUB_68881
mdefine_line|#define FPUB_68881     0
DECL|macro|FPUB_68882
mdefine_line|#define FPUB_68882     1
DECL|macro|FPUB_68040
mdefine_line|#define FPUB_68040     2                       /* Internal FPU */
DECL|macro|FPUB_68060
mdefine_line|#define FPUB_68060     3                       /* Internal FPU */
DECL|macro|FPUB_SUNFPA
mdefine_line|#define FPUB_SUNFPA    4                       /* Sun-3 FPA */
DECL|macro|FPU_68881
mdefine_line|#define FPU_68881      (1&lt;&lt;FPUB_68881)
DECL|macro|FPU_68882
mdefine_line|#define FPU_68882      (1&lt;&lt;FPUB_68882)
DECL|macro|FPU_68040
mdefine_line|#define FPU_68040      (1&lt;&lt;FPUB_68040)
DECL|macro|FPU_68060
mdefine_line|#define FPU_68060      (1&lt;&lt;FPUB_68060)
DECL|macro|FPU_SUNFPA
mdefine_line|#define FPU_SUNFPA     (1&lt;&lt;FPUB_SUNFPA)
DECL|macro|MMUB_68851
mdefine_line|#define MMUB_68851     0
DECL|macro|MMUB_68030
mdefine_line|#define MMUB_68030     1                       /* Internal MMU */
DECL|macro|MMUB_68040
mdefine_line|#define MMUB_68040     2                       /* Internal MMU */
DECL|macro|MMUB_68060
mdefine_line|#define MMUB_68060     3                       /* Internal MMU */
DECL|macro|MMUB_APOLLO
mdefine_line|#define MMUB_APOLLO    4                       /* Custom Apollo */
DECL|macro|MMUB_SUN3
mdefine_line|#define MMUB_SUN3      5                       /* Custom Sun-3 */
DECL|macro|MMU_68851
mdefine_line|#define MMU_68851      (1&lt;&lt;MMUB_68851)
DECL|macro|MMU_68030
mdefine_line|#define MMU_68030      (1&lt;&lt;MMUB_68030)
DECL|macro|MMU_68040
mdefine_line|#define MMU_68040      (1&lt;&lt;MMUB_68040)
DECL|macro|MMU_68060
mdefine_line|#define MMU_68060      (1&lt;&lt;MMUB_68060)
DECL|macro|MMU_SUN3
mdefine_line|#define MMU_SUN3       (1&lt;&lt;MMUB_SUN3)
DECL|macro|MMU_APOLLO
mdefine_line|#define MMU_APOLLO     (1&lt;&lt;MMUB_APOLLO)
macro_line|#ifdef __KERNEL__
macro_line|#ifndef __ASSEMBLY__
r_extern
id|u_long
id|m68k_cputype
suffix:semicolon
r_extern
id|u_long
id|m68k_fputype
suffix:semicolon
r_extern
id|u_long
id|m68k_mmutype
suffix:semicolon
multiline_comment|/* Not really used yet */
multiline_comment|/*&n;     *  m68k_is040or060 is != 0 for a &squot;040 or higher;&n;     *  used numbers are 4 for 68040 and 6 for 68060.&n;     */
r_extern
r_int
id|m68k_is040or060
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#if !defined(CONFIG_M68020)
DECL|macro|CPU_IS_020
macro_line|#  define CPU_IS_020 (0)
macro_line|#elif defined(CONFIG_M68030) || defined(CONFIG_M68040) || defined(CONFIG_M68060)
DECL|macro|CPU_IS_020
macro_line|#  define CPU_IS_020 (m68k_cputype &amp; CPU_68020)
macro_line|#else
DECL|macro|CPU_M68020_ONLY
macro_line|#  define CPU_M68020_ONLY
DECL|macro|CPU_IS_020
macro_line|#  define CPU_IS_020 (1)
macro_line|#endif
macro_line|#if !defined(CONFIG_M68030)
DECL|macro|CPU_IS_030
macro_line|#  define CPU_IS_030 (0)
macro_line|#elif defined(CONFIG_M68020) || defined(CONFIG_M68040) || defined(CONFIG_M68060)
DECL|macro|CPU_IS_030
macro_line|#  define CPU_IS_030 (m68k_cputype &amp; CPU_68030)
macro_line|#else
DECL|macro|CPU_M68030_ONLY
macro_line|#  define CPU_M68030_ONLY
DECL|macro|CPU_IS_030
macro_line|#  define CPU_IS_030 (1)
macro_line|#endif
macro_line|#if !defined(CONFIG_M68040)
DECL|macro|CPU_IS_040
macro_line|#  define CPU_IS_040 (0)
macro_line|#elif defined(CONFIG_M68020) || defined(CONFIG_M68030) || defined(CONFIG_M68060)
DECL|macro|CPU_IS_040
macro_line|#  define CPU_IS_040 (m68k_cputype &amp; CPU_68040)
macro_line|#else
DECL|macro|CPU_M68040_ONLY
macro_line|#  define CPU_M68040_ONLY
DECL|macro|CPU_IS_040
macro_line|#  define CPU_IS_040 (1)
macro_line|#endif
macro_line|#if !defined(CONFIG_M68060)
DECL|macro|CPU_IS_060
macro_line|#  define CPU_IS_060 (0)
macro_line|#elif defined(CONFIG_M68020) || defined(CONFIG_M68030) || defined(CONFIG_M68040)
DECL|macro|CPU_IS_060
macro_line|#  define CPU_IS_060 (m68k_cputype &amp; CPU_68060)
macro_line|#else
DECL|macro|CPU_M68060_ONLY
macro_line|#  define CPU_M68060_ONLY
DECL|macro|CPU_IS_060
macro_line|#  define CPU_IS_060 (1)
macro_line|#endif
macro_line|#if !defined(CONFIG_M68020) &amp;&amp; !defined(CONFIG_M68030)
DECL|macro|CPU_IS_020_OR_030
macro_line|#  define CPU_IS_020_OR_030 (0)
macro_line|#else
DECL|macro|CPU_M68020_OR_M68030
macro_line|#  define CPU_M68020_OR_M68030
macro_line|#  if defined(CONFIG_M68040) || defined(CONFIG_M68060)
DECL|macro|CPU_IS_020_OR_030
macro_line|#    define CPU_IS_020_OR_030 (!m68k_is040or060)
macro_line|#  else
DECL|macro|CPU_M68020_OR_M68030_ONLY
macro_line|#    define CPU_M68020_OR_M68030_ONLY
DECL|macro|CPU_IS_020_OR_030
macro_line|#    define CPU_IS_020_OR_030 (1)
macro_line|#  endif
macro_line|#endif
macro_line|#if !defined(CONFIG_M68040) &amp;&amp; !defined(CONFIG_M68060)
DECL|macro|CPU_IS_040_OR_060
macro_line|#  define CPU_IS_040_OR_060 (0)
macro_line|#else
DECL|macro|CPU_M68040_OR_M68060
macro_line|#  define CPU_M68040_OR_M68060
macro_line|#  if defined(CONFIG_M68020) || defined(CONFIG_M68030)
DECL|macro|CPU_IS_040_OR_060
macro_line|#    define CPU_IS_040_OR_060 (m68k_is040or060)
macro_line|#  else
DECL|macro|CPU_M68040_OR_M68060_ONLY
macro_line|#    define CPU_M68040_OR_M68060_ONLY
DECL|macro|CPU_IS_040_OR_060
macro_line|#    define CPU_IS_040_OR_060 (1)
macro_line|#  endif
macro_line|#endif
DECL|macro|CPU_TYPE
mdefine_line|#define CPU_TYPE (m68k_cputype)
macro_line|#endif /* __KERNEL__ */
multiline_comment|/*&n;     *  Miscellaneous&n;     */
DECL|macro|NUM_MEMINFO
mdefine_line|#define NUM_MEMINFO&t;(4)
DECL|macro|CL_SIZE
mdefine_line|#define CL_SIZE&t;&t;(256)
macro_line|#ifndef __ASSEMBLY__
DECL|struct|mem_info
r_struct
id|mem_info
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
multiline_comment|/* physical address of memory chunk */
DECL|member|size
r_int
r_int
id|size
suffix:semicolon
multiline_comment|/* length of memory chunk (in bytes) */
)brace
suffix:semicolon
macro_line|#ifdef __KERNEL__
r_extern
r_int
id|m68k_num_memory
suffix:semicolon
multiline_comment|/* # of memory blocks found */
r_extern
r_struct
id|mem_info
id|m68k_memory
(braket
id|NUM_MEMINFO
)braket
suffix:semicolon
multiline_comment|/* memory description */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _M68K_SETUP_H */
eof
