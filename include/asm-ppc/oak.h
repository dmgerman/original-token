multiline_comment|/*&n; *&n; *    Copyright (c) 1999 Grant Erickson &lt;grant@lcse.umn.edu&gt;&n; *&n; *    Module name: oak.h&n; *&n; *    Description:&n; *&t;Macros, definitions, and data structures specific to the IBM PowerPC&n; *      403G{A,B,C,CX} &quot;Oak&quot; evaluation board. Anything specific to the pro-&n; *      cessor itself is defined elsewhere.&n; *&n; */
macro_line|#ifndef&t;__OAK_H__
DECL|macro|__OAK_H__
mdefine_line|#define&t;__OAK_H__
macro_line|#ifdef __cplusplus
r_extern
l_string|&quot;C&quot;
(brace
macro_line|#endif
DECL|macro|_IO_BASE
mdefine_line|#define _IO_BASE&t;0
DECL|macro|_ISA_MEM_BASE
mdefine_line|#define _ISA_MEM_BASE&t;0
DECL|macro|PCI_DRAM_OFFSET
mdefine_line|#define PCI_DRAM_OFFSET&t;0
macro_line|#ifdef __cplusplus
)brace
macro_line|#endif
macro_line|#endif /* __OAK_H__ */
eof
