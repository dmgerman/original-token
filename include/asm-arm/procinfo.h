multiline_comment|/*&n; * linux/include/asm-arm/procinfo.h&n; *&n; * Copyright (C) 1996 Russell King&n; */
macro_line|#ifndef __ASM_PROCINFO_H
DECL|macro|__ASM_PROCINFO_H
mdefine_line|#define __ASM_PROCINFO_H
macro_line|#include &lt;asm/proc-fns.h&gt;
DECL|macro|F_MEMC
mdefine_line|#define F_MEMC   (1&lt;&lt;0)
DECL|macro|F_MMU
mdefine_line|#define F_MMU    (1&lt;&lt;1)
DECL|macro|F_32BIT
mdefine_line|#define F_32BIT  (1&lt;&lt;2)
DECL|macro|F_CACHE
mdefine_line|#define F_CACHE  (1&lt;&lt;3)
DECL|macro|F_IOEB
mdefine_line|#define F_IOEB   (1&lt;&lt;31)
macro_line|#ifndef __ASSEMBLER__
DECL|struct|armversions
r_struct
id|armversions
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|mask
r_int
r_int
id|mask
suffix:semicolon
DECL|member|features
r_int
r_int
id|features
suffix:semicolon
DECL|member|manu
r_const
r_char
op_star
id|manu
suffix:semicolon
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|proc
r_const
r_struct
id|processor
op_star
id|proc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
eof
