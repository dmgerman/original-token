macro_line|#ifndef _SPARC_ASI4M_H
DECL|macro|_SPARC_ASI4M_H
mdefine_line|#define _SPARC_ASI4M_H
multiline_comment|/* asi4m.h: Address Space Identifier values for sun4m&n; &n;   Copyright (C) 1995 Paul Hatchman (paul@sfe.com.au)&n;*/
DECL|macro|ASI_PTE
mdefine_line|#define ASI_PTE 0x0
DECL|macro|ASI_NULL1
mdefine_line|#define ASI_NULL1&t;&t;&t;0x0
DECL|macro|ASI_NULL2
mdefine_line|#define ASI_NULL2&t;&t;&t;0x1
DECL|macro|ASI_CONTROL
mdefine_line|#define&t;ASI_CONTROL&t;&t;&t;0x4&t;/* hmm? */
DECL|macro|ASI_USERTXT
mdefine_line|#define&t;ASI_USERTXT&t;&t;&t;0x8&t;/* user text */
DECL|macro|ASI_KERNELTXT
mdefine_line|#define&t;ASI_KERNELTXT&t;&t;0x9&t;/* kernel text */
DECL|macro|ASI_USERDATA
mdefine_line|#define&t;ASI_USERDATA&t;&t;0xA&t;/* user data */
DECL|macro|ASI_KERNELDATA
mdefine_line|#define&t;ASI_KERNELDATA&t;&t;0xB&t;/* kernel data */
multiline_comment|/* cache flushing */
DECL|macro|ASI_FLUSHPG
mdefine_line|#define ASI_FLUSHPG&t;&t;&t;0x10 
DECL|macro|ASI_FLUSHSEG
mdefine_line|#define ASI_FLUSHSEG&t;&t;0x11
DECL|macro|ASI_FLUSHRGN
mdefine_line|#define ASI_FLUSHRGN&t;&t;0x12
DECL|macro|ASI_FLUSHCTX
mdefine_line|#define ASI_FLUSHCTX&t;&t;0x13
multiline_comment|/* MMU REGS */
DECL|macro|SRMMU_CTL
mdefine_line|#define SRMMU_CTL 0x000
DECL|macro|SRMMU_CTP
mdefine_line|#define SRMMU_CTP 0x100&t;&t;/* set/get context pointer */
DECL|macro|SRMMU_CTX
mdefine_line|#define SRMMU_CTX 0x200 &t;/* get/set context */
macro_line|#endif _SPARC_ASI4M_H
eof
