multiline_comment|/*&n; * include/asm-mips/bcache.h&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1997 by Ralf Baechle&n; *&n; * $Id: bcache.h,v 1.1 1998/05/01 01:35:46 ralf Exp $&n; */
DECL|struct|bcache_ops
r_struct
id|bcache_ops
(brace
DECL|member|bc_enable
r_void
(paren
op_star
id|bc_enable
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|bc_disable
r_void
(paren
op_star
id|bc_disable
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|bc_wback_inv
r_void
(paren
op_star
id|bc_wback_inv
)paren
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
suffix:semicolon
DECL|member|bc_inv
r_void
(paren
op_star
id|bc_inv
)paren
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|size
)paren
suffix:semicolon
)brace
suffix:semicolon
r_extern
r_void
id|indy_sc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|sni_pcimt_sc_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|bcache_ops
op_star
id|bcops
suffix:semicolon
eof