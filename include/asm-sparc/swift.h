multiline_comment|/* swift.h: Specific definitions for the _broken_ Swift SRMMU&n; *          MMU.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _SPARC_SWIFT_H
DECL|macro|_SPARC_SWIFT_H
mdefine_line|#define _SPARC_SWIFT_H
multiline_comment|/* Swift is so brain damaged, here is the mmu control register. */
DECL|macro|SWIFT_ST
mdefine_line|#define SWIFT_ST       0x00800000   /* SW tablewalk enable */
DECL|macro|SWIFT_WP
mdefine_line|#define SWIFT_WP       0x00400000   /* Watchpoint enable   */
multiline_comment|/* Branch folding (buggy, disable on production systems!)  */
DECL|macro|SWIFT_BF
mdefine_line|#define SWIFT_BF       0x00200000
DECL|macro|SWIFT_PMC
mdefine_line|#define SWIFT_PMC      0x00180000   /* Page mode control   */
DECL|macro|SWIFT_PE
mdefine_line|#define SWIFT_PE       0x00040000   /* Parity enable       */
DECL|macro|SWIFT_PC
mdefine_line|#define SWIFT_PC       0x00020000   /* Parity control      */
DECL|macro|SWIFT_AP
mdefine_line|#define SWIFT_AP       0x00010000   /* Graphics page mode control (TCX/SX) */
DECL|macro|SWIFT_AC
mdefine_line|#define SWIFT_AC       0x00008000   /* Alternate Cacheability (see viking.h) */
DECL|macro|SWIFT_BM
mdefine_line|#define SWIFT_BM       0x00004000   /* Boot mode */
DECL|macro|SWIFT_RC
mdefine_line|#define SWIFT_RC       0x00003c00   /* DRAM refresh control */
DECL|macro|SWIFT_IE
mdefine_line|#define SWIFT_IE       0x00000200   /* Instruction cache enable */
DECL|macro|SWIFT_DE
mdefine_line|#define SWIFT_DE       0x00000100   /* Data cache enable */
DECL|macro|SWIFT_SA
mdefine_line|#define SWIFT_SA       0x00000080   /* Store Allocate */
DECL|macro|SWIFT_NF
mdefine_line|#define SWIFT_NF       0x00000002   /* No fault mode */
DECL|macro|SWIFT_EN
mdefine_line|#define SWIFT_EN       0x00000001   /* MMU enable */
DECL|function|swift_inv_insn_tag
r_extern
r_inline
r_void
id|swift_inv_insn_tag
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_TXTC_TAG
)paren
)paren
suffix:semicolon
)brace
DECL|function|swift_inv_data_tag
r_extern
r_inline
r_void
id|swift_inv_data_tag
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_DATAC_TAG
)paren
)paren
suffix:semicolon
)brace
DECL|function|swift_flush_page
r_extern
r_inline
r_void
id|swift_flush_page
c_func
(paren
r_int
r_int
id|page
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|page
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_PAGE
)paren
)paren
suffix:semicolon
)brace
DECL|function|swift_flush_segment
r_extern
r_inline
r_void
id|swift_flush_segment
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_SEG
)paren
)paren
suffix:semicolon
)brace
DECL|function|swift_flush_region
r_extern
r_inline
r_void
id|swift_flush_region
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%0] %1&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;r&quot;
(paren
id|addr
)paren
comma
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_REGION
)paren
)paren
suffix:semicolon
)brace
DECL|function|swift_flush_context
r_extern
r_inline
r_void
id|swift_flush_context
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sta %%g0, [%%g0] %0&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
l_string|&quot;i&quot;
(paren
id|ASI_M_FLUSH_CTX
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* !(_SPARC_SWIFT_H) */
eof