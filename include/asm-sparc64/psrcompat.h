multiline_comment|/* $Id: psrcompat.h,v 1.2 1997/04/07 18:57:17 jj Exp $ */
macro_line|#ifndef _SPARC64_PSRCOMPAT_H
DECL|macro|_SPARC64_PSRCOMPAT_H
mdefine_line|#define _SPARC64_PSRCOMPAT_H
macro_line|#include &lt;asm/pstate.h&gt;
multiline_comment|/* Old 32-bit PSR fields for the compatability conversion code. */
DECL|macro|PSR_CWP
mdefine_line|#define PSR_CWP     0x0000001f         /* current window pointer     */
DECL|macro|PSR_ET
mdefine_line|#define PSR_ET      0x00000020         /* enable traps field         */
DECL|macro|PSR_PS
mdefine_line|#define PSR_PS      0x00000040         /* previous privilege level   */
DECL|macro|PSR_S
mdefine_line|#define PSR_S       0x00000080         /* current privilege level    */
DECL|macro|PSR_PIL
mdefine_line|#define PSR_PIL     0x00000f00         /* processor interrupt level  */
DECL|macro|PSR_EF
mdefine_line|#define PSR_EF      0x00001000         /* enable floating point      */
DECL|macro|PSR_EC
mdefine_line|#define PSR_EC      0x00002000         /* enable co-processor        */
DECL|macro|PSR_LE
mdefine_line|#define PSR_LE      0x00008000         /* SuperSparcII little-endian */
DECL|macro|PSR_ICC
mdefine_line|#define PSR_ICC     0x00f00000         /* integer condition codes    */
DECL|macro|PSR_C
mdefine_line|#define PSR_C       0x00100000         /* carry bit                  */
DECL|macro|PSR_V
mdefine_line|#define PSR_V       0x00200000         /* overflow bit               */
DECL|macro|PSR_Z
mdefine_line|#define PSR_Z       0x00400000         /* zero bit                   */
DECL|macro|PSR_N
mdefine_line|#define PSR_N       0x00800000         /* negative bit               */
DECL|macro|PSR_VERS
mdefine_line|#define PSR_VERS    0x0f000000         /* cpu-version field          */
DECL|macro|PSR_IMPL
mdefine_line|#define PSR_IMPL    0xf0000000         /* cpu-implementation field   */
DECL|function|tstate_to_psr
r_extern
r_inline
r_int
r_int
id|tstate_to_psr
c_func
(paren
r_int
r_int
id|tstate
)paren
(brace
r_int
r_int
id|psr
suffix:semicolon
r_int
r_int
id|vers
suffix:semicolon
multiline_comment|/* These fields are in the same place. */
id|psr
op_assign
(paren
id|tstate
op_amp
(paren
id|TSTATE_CWP
op_or
id|TSTATE_PEF
)paren
)paren
suffix:semicolon
multiline_comment|/* This is what the user would have always seen. */
id|psr
op_or_assign
id|PSR_S
suffix:semicolon
multiline_comment|/* Slam in the 32-bit condition codes. */
id|psr
op_or_assign
(paren
(paren
id|tstate
op_amp
id|TSTATE_ICC
)paren
op_rshift
l_int|12
)paren
suffix:semicolon
multiline_comment|/* This is completely arbitrary. */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr&t;%%ver, %0&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|vers
)paren
)paren
suffix:semicolon
id|psr
op_or_assign
(paren
(paren
id|vers
op_lshift
l_int|8
)paren
op_rshift
l_int|32
)paren
op_amp
id|PSR_IMPL
suffix:semicolon
id|psr
op_or_assign
(paren
(paren
id|vers
op_lshift
l_int|24
)paren
op_rshift
l_int|36
)paren
op_amp
id|PSR_VERS
suffix:semicolon
r_return
id|psr
suffix:semicolon
)brace
DECL|function|psr_to_tstate_icc
r_extern
r_inline
r_int
r_int
id|psr_to_tstate_icc
c_func
(paren
r_int
r_int
id|psr
)paren
(brace
r_int
r_int
id|tstate
suffix:semicolon
id|tstate
op_assign
(paren
id|psr
op_amp
id|PSR_ICC
)paren
op_lshift
l_int|12
suffix:semicolon
r_return
id|tstate
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC64_PSRCOMPAT_H) */
eof
