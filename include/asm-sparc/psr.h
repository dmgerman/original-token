multiline_comment|/* psr.h: This file holds the macros for masking off various parts of&n;          the processor status register on the Sparc. This is valid&n;&t;  for Version 8. On the V9 this is renamed to the PSTATE&n;&t;  register and its members are accessed as fields like&n;&t;  PSTATE.PRIV for the current CPU privilege level.&n;&n;   Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)&n;*/
macro_line|#ifndef __LINUX_SPARC_PSR_H
DECL|macro|__LINUX_SPARC_PSR_H
mdefine_line|#define __LINUX_SPARC_PSR_H
DECL|macro|__LINUX_SPARC_V8
mdefine_line|#define __LINUX_SPARC_V8  /* duh */
macro_line|#ifdef __LINUX_SPARC_V8
multiline_comment|/* The Sparc PSR fields are laid out as the following:&n;&n;    ------------------------------------------------------------------------&n;    | impl  | vers  | icc   | resv  | EC | EF | PIL  | S | PS | ET |  CWP  |&n;bits| 31-28 | 27-24 | 23-20 | 19-14 | 13 | 12 | 11-8 | 7 | 6  | 5  |  4-0  |&n;    ------------------------------------------------------------------------&n;&n;   The PSR can only be directly be written/read by the privileged instructions&n;   &squot;rd&squot; and &squot;wr&squot;. Certain fields are changed as a side effect due to the &squot;Ticc&squot;,&n;   &squot;save&squot;, &squot;restore&squot;, and &squot;rett&squot; instructions. Also the integer condition codes&n;   &squot;icc&squot; are modified by various arithmetic instructions.&n;&n;   For example:  wr  %o2, or&squot;d_bit_pattern, %psr&n;                 rd  %psr, %o3&n;&n;*/
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
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Get the %psr register. */
DECL|function|get_psr
r_extern
r_inline
r_int
r_int
id|get_psr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|psr
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rd %%psr, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|psr
)paren
)paren
suffix:semicolon
r_return
id|psr
suffix:semicolon
)brace
DECL|function|put_psr
r_extern
r_inline
r_void
id|put_psr
c_func
(paren
r_int
r_int
id|new_psr
)paren
(brace
id|__asm__
c_func
(paren
l_string|&quot;wr %0, 0x0, %%psr&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|new_psr
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the %fsr register.  Be careful, make sure the floating point&n; * enable bit is set in the %psr when you execute this or you will&n; * incur a trap.&n; */
r_extern
r_int
r_int
id|fsr_storage
suffix:semicolon
DECL|function|get_fsr
r_extern
r_inline
r_int
r_int
id|get_fsr
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|fsr
op_assign
l_int|0
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;st %%fsr, %1&bslash;n&bslash;t&quot;
l_string|&quot;ld %1, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fsr
)paren
suffix:colon
l_string|&quot;m&quot;
(paren
id|fsr_storage
)paren
)paren
suffix:semicolon
r_return
id|fsr
suffix:semicolon
)brace
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__LINUX_SPARC_V8) */
macro_line|#ifdef __LINUX_SPARC_V9
multiline_comment|/* The information available in the %psr on the V8 is spread amongst&n;   a whole bunch of registers on the V9. The main one being PSTATE.&n;&n;     --------------------------------------------------------&n;     |  CLE  | TLE |  MM  | RED | PEF | AM | PRIV | IE | AG |&n;bits |   9   |  8  |  7-6 |  5  |  4  |  3 |   2  |  1 |  0 |&n;     --------------------------------------------------------&n;&n;   Writes and reads to PSTATE are done via &squot;wrpr&squot; and &squot;rdpr&squot; instructions.&n;&n;   For example:  wrpr %o2, or&squot;d_bit_pattern, %pstate&n;                 rdpr %pstate, %o3&n;*/
DECL|macro|PSTATE_AG
mdefine_line|#define PSTATE_AG    0x001   /* Alternate Globals             */
DECL|macro|PSTATE_IE
mdefine_line|#define PSTATE_IE    0x002   /* Interrupt Enable              */
DECL|macro|PSTATE_PRIV
mdefine_line|#define PSTATE_PRIV  0x004   /* Current privilege level       */
DECL|macro|PSTATE_AM
mdefine_line|#define PSTATE_AM    0x008   /* Address mask (data reads can  */
multiline_comment|/* be chosen to be either big or */
multiline_comment|/* little endian on V9).         */
DECL|macro|PSTATE_PEF
mdefine_line|#define PSTATE_PEF   0x010   /* enable floating point         */
DECL|macro|PSTATE_RED
mdefine_line|#define PSTATE_RED   0x020   /* RED trap state (set if trap   */
multiline_comment|/* trap_level == max_tl).        */
DECL|macro|PSTATE_MM
mdefine_line|#define PSTATE_MM    0x0c0   /* Memory model (Total Store     */
multiline_comment|/* Order=0, Partial Store Order  */
multiline_comment|/* =1 or Relaxed Memory Order=2) */
DECL|macro|PSTATE_TLE
mdefine_line|#define PSTATE_TLE   0x100   /* Trap Little Endian            */
DECL|macro|PSTATE_CLE
mdefine_line|#define PSTATE_CLE   0x200   /* Current Little Endian         */
DECL|function|get_v9_pstate
r_extern
r_inline
r_int
r_int
id|get_v9_pstate
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pstate
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %pstate, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
r_return
id|pstate
suffix:semicolon
)brace
DECL|function|put_v9_pstate
r_extern
r_inline
r_void
id|put_v9_pstate
c_func
(paren
r_int
r_int
id|pstate
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wrpr %0, 0x0, %pstate&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* The Version Register holds vendor information for the chip:&n;&n;    ---------------------------------------------------------------------------&n;    | manufacturer | implementation | mask | reserved | maxtl | resv | maxwin |&n;bits|  63-48       |   47-32        | 31-24|   23-16  | 15-8  | 7-5  |  4-0   |&n;    ---------------------------------------------------------------------------&n;&n;*/
DECL|macro|VERS_MAXWIN
mdefine_line|#define VERS_MAXWIN  0x000000000000001f     /* &squot;nwindows&squot; on this chip       */
DECL|macro|VERS_MAXTL
mdefine_line|#define VERS_MAXTL   0x00000000000ff000     /* Maximum Trap-level supported  */
DECL|macro|VERS_MASK
mdefine_line|#define VERS_MASK    0x0000000ff0000000     /* impl. dep. chip mask revision */
DECL|macro|VERS_MANUF
mdefine_line|#define VERS_MANUF   0xffff000000000000     /* Manufacturer ID code          */
DECL|function|get_v9_version
r_extern
r_inline
r_int
r_int
id|get_v9_version
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|vers
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %ver, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|vers
)paren
)paren
suffix:semicolon
r_return
id|vers
suffix:semicolon
)brace
DECL|function|get_v9_tstate
r_extern
r_inline
r_int
r_int
id|get_v9_tstate
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|tstate
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %tstate, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
r_return
id|tstate
suffix:semicolon
)brace
DECL|function|get_v9_pil
r_extern
r_inline
r_int
r_int
id|get_v9_pil
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|pil
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;rdpr %pil, %0&bslash;n&bslash;t&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|pstate
)paren
)paren
suffix:semicolon
r_return
id|pil
suffix:semicolon
)brace
DECL|function|put_v9_pil
r_extern
r_inline
r_void
id|put_v9_pil
c_func
(paren
r_int
r_int
id|pil
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;wrpr %0, 0x0, %pil&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|pil
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif /* !(__LINUX_SPARC_V9) */
macro_line|#endif /* !(__LINUX_SPARC_PSR_H) */
eof