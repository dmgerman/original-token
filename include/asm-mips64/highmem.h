multiline_comment|/* $Id: highmem.h,v 1.2 2000/01/29 01:42:28 ralf Exp $&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 by Ralf Baechle&n; * Copyright (C) 2000 Silicon Graphics, Inc.&n; */
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
DECL|macro|kmap
mdefine_line|#define kmap(page)&t;&t;&t;page_address(page)
DECL|macro|kunmap
mdefine_line|#define kunmap(page)&t;&t;&t;do { } while(0)
DECL|macro|kmap_atomic
mdefine_line|#define kmap_atomic(page, type)&t;&t;page_address(page)
DECL|macro|kunmap_atomic
mdefine_line|#define kunmap_atomic(page, type)&t;do { } while(0)
macro_line|#endif /* _ASM_HIGHMEM_H */
eof
