multiline_comment|/*&n; * arch/mips/sni/pcimt_scache.c&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (c) 1997 by Ralf Baechle&n; *&n; * $Id: pcimt_scache.c,v 1.2 1998/05/28 03:18:02 ralf Exp $&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;asm/bcache.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_void
id|sni_pcimt_sc_init
c_func
(paren
r_void
)paren
)paren
(brace
r_int
r_int
id|cacheconf
comma
id|sc_size
suffix:semicolon
id|cacheconf
op_assign
op_star
(paren
r_volatile
r_int
r_int
op_star
)paren
id|PCIMT_CACHECONF
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cacheconf
op_amp
l_int|7
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;No second level cache detected&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;WARNING: not activating second level cache, &quot;
l_string|&quot;tell ralf@gnu.org&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|cacheconf
op_amp
l_int|7
)paren
op_ge
l_int|6
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Invalid second level cache size detected&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sc_size
op_assign
l_int|128
op_lshift
(paren
id|cacheconf
op_amp
l_int|7
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%dkb second level cache detected.&bslash;n&quot;
comma
id|sc_size
)paren
suffix:semicolon
)brace
eof
