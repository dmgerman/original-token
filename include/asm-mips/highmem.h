multiline_comment|/* $Id: highmem.h,v 1.1 2000/01/27 01:05:37 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 by Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_HIGHMEM_H
DECL|macro|_ASM_HIGHMEM_H
mdefine_line|#define _ASM_HIGHMEM_H
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
multiline_comment|/* declarations for highmem.c */
r_extern
r_int
r_int
id|highstart_pfn
comma
id|highend_pfn
suffix:semicolon
r_extern
id|pte_t
op_star
id|kmap_pte
suffix:semicolon
r_extern
id|pgprot_t
id|kmap_prot
suffix:semicolon
DECL|macro|kmap_init
mdefine_line|#define kmap_init()&t;&t;&t;do { } while(0)
DECL|function|kmap
r_static
id|__inline__
r_int
r_int
id|kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|kunmap
mdefine_line|#define kunmap(page)&t;&t;&t;do { } while(0)
DECL|function|kmap_atomic
r_static
id|__inline__
r_int
r_int
id|kmap_atomic
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|type
)paren
(brace
r_return
id|page_address
c_func
(paren
id|page
)paren
)brace
DECL|macro|kunmap_atomic
mdefine_line|#define kunmap_atomic(page, type)&t;do { } while(0)
macro_line|#endif /* _ASM_HIGHMEM_H */
eof
