multiline_comment|/******************************************************************************&n; *&n; * Name: acenv.h - Generation environment specific items&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACENV_H__
DECL|macro|__ACENV_H__
mdefine_line|#define __ACENV_H__
multiline_comment|/*&n; * Environment configuration.  The purpose of this file is to interface to the&n; * local generation environment.&n; *&n; * 1) ACPI_USE_SYSTEM_CLIBRARY - Define this if linking to an actual C library.&n; *      Otherwise, local versions of string/memory functions will be used.&n; * 2) ACPI_USE_STANDARD_HEADERS - Define this if linking to a C library and&n; *      the standard header files may be used.&n; *&n; * The ACPI subsystem only uses low level C library functions that do not call&n; * operating system services and may therefore be inlined in the code.&n; *&n; * It may be necessary to tailor these include files to the target&n; * generation environment.&n; *&n; *&n; * Functions and constants used from each header:&n; *&n; * string.h:    memcpy&n; *              memset&n; *              strcat&n; *              strcmp&n; *              strcpy&n; *              strlen&n; *              strncmp&n; *              strncat&n; *              strncpy&n; *&n; * stdlib.h:    strtoul&n; *&n; * stdarg.h:    va_list&n; *              va_arg&n; *              va_start&n; *              va_end&n; *&n; */
multiline_comment|/*&n; * Environment-specific configuration&n; */
macro_line|#ifdef _LINUX
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/ctype.h&gt;
macro_line|#include &lt;asm/system.h&gt;
multiline_comment|/* Single threaded */
DECL|macro|ACPI_APPLICATION
mdefine_line|#define ACPI_APPLICATION
multiline_comment|/* Use native Linux string library */
DECL|macro|ACPI_USE_SYSTEM_CLIBRARY
mdefine_line|#define ACPI_USE_SYSTEM_CLIBRARY
multiline_comment|/* Special functions */
DECL|macro|strtoul
mdefine_line|#define strtoul             simple_strtoul
macro_line|#else
multiline_comment|/* All other environments */
DECL|macro|ACPI_USE_STANDARD_HEADERS
mdefine_line|#define ACPI_USE_STANDARD_HEADERS
macro_line|#endif
multiline_comment|/******************************************************************************&n; *&n; * C library configuration&n; *&n; *****************************************************************************/
macro_line|#ifdef ACPI_USE_SYSTEM_CLIBRARY
multiline_comment|/*&n; * Use the standard C library headers.&n; * We want to keep these to a minimum.&n; *&n; */
macro_line|#ifdef ACPI_USE_STANDARD_HEADERS
multiline_comment|/*&n; * Use the standard headers from the standard locations&n; */
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#endif /* ACPI_USE_STANDARD_HEADERS */
multiline_comment|/*&n; * We will be linking to the standard Clib functions&n; */
DECL|macro|STRSTR
mdefine_line|#define STRSTR(s1,s2)           strstr((char *) (s1), (char *) (s2))
DECL|macro|STRUPR
mdefine_line|#define STRUPR(s)               strupr((char *) (s))
DECL|macro|STRLEN
mdefine_line|#define STRLEN(s)               strlen((char *) (s))
DECL|macro|STRCPY
mdefine_line|#define STRCPY(d,s)             strcpy((char *) (d), (char *) (s))
DECL|macro|STRNCPY
mdefine_line|#define STRNCPY(d,s,n)          strncpy((char *) (d), (char *) (s), (n))
DECL|macro|STRNCMP
mdefine_line|#define STRNCMP(d,s,n)          strncmp((char *) (d), (char *) (s), (n))
DECL|macro|STRCMP
mdefine_line|#define STRCMP(d,s)             strcmp((char *) (d), (char *) (s))
DECL|macro|STRCAT
mdefine_line|#define STRCAT(d,s)             strcat((char *) (d), (char *) (s))
DECL|macro|STRNCAT
mdefine_line|#define STRNCAT(d,s,n)          strncat((char *) (d), (char *) (s), (n))
DECL|macro|STRTOUL
mdefine_line|#define STRTOUL(d,s,n)          strtoul((char *) (d), (char **) (s), (n))
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(d,s,n)           memcpy(d, s, (size_t) n)
DECL|macro|MEMSET
mdefine_line|#define MEMSET(d,s,n)           memset(d, s, (size_t) n)
DECL|macro|TOUPPER
mdefine_line|#define TOUPPER                 toupper
DECL|macro|TOLOWER
mdefine_line|#define TOLOWER                 tolower
multiline_comment|/******************************************************************************&n; *&n; * Not using native C library, use local implementations&n; *&n; *****************************************************************************/
macro_line|#else
multiline_comment|/*&n; * Use local definitions of C library macros and functions&n; * NOTE: The function implementations may not be as efficient&n; * as an inline or assembly code implementation provided by a&n; * native C library.&n; */
macro_line|#ifndef va_arg
macro_line|#ifndef _VALIST
DECL|macro|_VALIST
mdefine_line|#define _VALIST
DECL|typedef|va_list
r_typedef
r_char
op_star
id|va_list
suffix:semicolon
macro_line|#endif /* _VALIST */
multiline_comment|/*&n; * Storage alignment properties&n; */
DECL|macro|_AUPBND
mdefine_line|#define  _AUPBND                (sizeof(int) - 1)
DECL|macro|_ADNBND
mdefine_line|#define  _ADNBND                (sizeof(int) - 1)
multiline_comment|/*&n; * Variable argument list macro definitions&n; */
DECL|macro|_bnd
mdefine_line|#define _bnd(X, bnd)            (((sizeof(X)) + (bnd)) &amp; (~(bnd)))
DECL|macro|va_arg
mdefine_line|#define va_arg(ap, T)           (*(T *)(((ap) += ((_bnd(T, _AUPBND))) &bslash;&n;&t;  - (_bnd(T, _ADNBND)))))
DECL|macro|va_end
mdefine_line|#define va_end(ap)              (void)0
DECL|macro|va_start
mdefine_line|#define va_start(ap, A)         (void) ((ap) = (((char *)&amp;(A)) &bslash;&n;&t;&t;&t;   + (_bnd(A, _AUPBND))))
macro_line|#endif /* va_arg */
DECL|macro|STRSTR
mdefine_line|#define STRSTR(s1,s2)           acpi_cm_strstr  ((char *) (s1), (char *) (s2))
DECL|macro|STRUPR
mdefine_line|#define STRUPR(s)               acpi_cm_strupr  ((char *) (s))
DECL|macro|STRLEN
mdefine_line|#define STRLEN(s)               acpi_cm_strlen  ((char *) (s))
DECL|macro|STRCPY
mdefine_line|#define STRCPY(d,s)             acpi_cm_strcpy  ((char *) (d), (char *) (s))
DECL|macro|STRNCPY
mdefine_line|#define STRNCPY(d,s,n)          acpi_cm_strncpy ((char *) (d), (char *) (s), (n))
DECL|macro|STRNCMP
mdefine_line|#define STRNCMP(d,s,n)          acpi_cm_strncmp ((char *) (d), (char *) (s), (n))
DECL|macro|STRCMP
mdefine_line|#define STRCMP(d,s)             acpi_cm_strcmp  ((char *) (d), (char *) (s))
DECL|macro|STRCAT
mdefine_line|#define STRCAT(d,s)             acpi_cm_strcat  ((char *) (d), (char *) (s))
DECL|macro|STRNCAT
mdefine_line|#define STRNCAT(d,s,n)          acpi_cm_strncat ((char *) (d), (char *) (s), (n))
DECL|macro|STRTOUL
mdefine_line|#define STRTOUL(d,s,n)          acpi_cm_strtoul ((char *) (d), (char **) (s), (n))
DECL|macro|MEMCPY
mdefine_line|#define MEMCPY(d,s,n)           acpi_cm_memcpy  ((void *) (d), (const void *) (s), (n))
DECL|macro|MEMSET
mdefine_line|#define MEMSET(d,v,n)           acpi_cm_memset  ((void *) (d), (v), (n))
DECL|macro|TOUPPER
mdefine_line|#define TOUPPER                 acpi_cm_to_upper
DECL|macro|TOLOWER
mdefine_line|#define TOLOWER                 acpi_cm_to_lower
macro_line|#endif /* ACPI_USE_SYSTEM_CLIBRARY */
multiline_comment|/******************************************************************************&n; *&n; * Assembly code macros&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Handle platform- and compiler-specific assembly language differences.&n; *&n; * Notes:&n; * 1) Interrupt 3 is used to break into a debugger&n; * 2) Interrupts are turned off during ACPI register setup&n; */
macro_line|#ifdef __GNUC__
macro_line|#ifdef __ia64__
DECL|macro|_IA64
mdefine_line|#define _IA64
macro_line|#endif
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|disable
mdefine_line|#define disable() __cli()
DECL|macro|enable
mdefine_line|#define enable()  __sti()
DECL|macro|halt
mdefine_line|#define halt()    __asm__ __volatile__ (&quot;sti; hlt&quot;:::&quot;memory&quot;)
DECL|macro|wbinvd
mdefine_line|#define wbinvd()
multiline_comment|/*! [Begin] no source code translation&n; *&n; * A brief explanation as GNU inline assembly is a bit hairy&n; *  %0 is the output parameter in EAX (&quot;=a&quot;)&n; *  %1 and %2 are the input parameters in ECX (&quot;c&quot;) and an immediate value (&quot;i&quot;) respectively&n; *  All actual register references are preceded with &quot;%%&quot; as in &quot;%%edx&quot;&n; *  Immediate values in the assembly are preceded by &quot;$&quot; as in &quot;$0x1&quot;&n; *  The final asm parameter is the non-output registers altered by the operation&n; */
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;btsl   $0x1,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;adcl   $0x0,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;cmpb   $0x3,%%dl;&quot; &bslash;&n;&t;&t;&t;&quot;sbbl   %%eax,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~1L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(GLptr, Acq) &bslash;&n;&t;do { &bslash;&n;&t;&t;int dummy; &bslash;&n;&t;&t;asm(&quot;1:     movl (%1),%%eax;&quot; &bslash;&n;&t;&t;&t;&quot;movl   %%eax,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;andl   %2,%%edx;&quot; &bslash;&n;&t;&t;&t;&quot;lock;  cmpxchgl %%edx,(%1);&quot; &bslash;&n;&t;&t;&t;&quot;jnz    1b;&quot; &bslash;&n;&t;&t;&t;&quot;andl   $0x1,%%eax&quot; &bslash;&n;&t;&t;&t;:&quot;=a&quot;(Acq),&quot;=c&quot;(dummy):&quot;c&quot;(GLptr),&quot;i&quot;(~3L):&quot;dx&quot;); &bslash;&n;&t;} while(0)
multiline_comment|/*! [End] no source code translation !*/
macro_line|#endif /* __GNUC__ */
macro_line|#ifndef ACPI_ASM_MACROS
multiline_comment|/* Unrecognized compiler, use defaults */
DECL|macro|ACPI_ASM_MACROS
mdefine_line|#define ACPI_ASM_MACROS
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
DECL|macro|disable
mdefine_line|#define disable()
DECL|macro|enable
mdefine_line|#define enable()
DECL|macro|halt
mdefine_line|#define halt()
DECL|macro|ACPI_ACQUIRE_GLOBAL_LOCK
mdefine_line|#define ACPI_ACQUIRE_GLOBAL_LOCK(Glptr, acq)
DECL|macro|ACPI_RELEASE_GLOBAL_LOCK
mdefine_line|#define ACPI_RELEASE_GLOBAL_LOCK(Glptr, acq)
macro_line|#endif /* ACPI_ASM_MACROS */
macro_line|#ifdef ACPI_APPLICATION
multiline_comment|/* Don&squot;t want software interrupts within a ring3 application */
DECL|macro|causeinterrupt
macro_line|#undef causeinterrupt
DECL|macro|BREAKPOINT3
macro_line|#undef BREAKPOINT3
DECL|macro|causeinterrupt
mdefine_line|#define causeinterrupt(level)
DECL|macro|BREAKPOINT3
mdefine_line|#define BREAKPOINT3
macro_line|#endif
macro_line|#endif /* __ACENV_H__ */
eof
