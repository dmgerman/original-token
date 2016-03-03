multiline_comment|/*&n; *  arch/s390/lib/checksum.c&n; *    S390 fast network checksum routines&n; *&n; *  S390 version&n; *    Copyright (C) 1999 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Ulrich Hild        (first version),&n; *               Martin Schwidefsky (schwidefsky@de.ibm.com),&n; *               Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com),&n; *&n; * This file contains network checksum routines&n; */
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/checksum.h&gt;
multiline_comment|/*&n; * computes a partial checksum, e.g. for TCP/UDP fragments&n; */
r_int
r_int
DECL|function|csum_partial
id|csum_partial
(paren
r_const
r_int
r_char
op_star
id|buff
comma
r_int
id|len
comma
r_int
r_int
id|sum
)paren
(brace
multiline_comment|/*&n;&t;   * Experiments with ethernet and slip connections show that buff&n;&t;   * is aligned on either a 2-byte or 4-byte boundary.&n;&t;   */
id|__asm__
id|__volatile__
(paren
l_string|&quot;    lr   2,%1&bslash;n&quot;
multiline_comment|/* address in gpr 2 */
l_string|&quot;    lr   3,%2&bslash;n&quot;
multiline_comment|/* length in gpr 3 */
l_string|&quot;0:  cksm %0,2&bslash;n&quot;
multiline_comment|/* do checksum on longs */
l_string|&quot;    jo   0b&bslash;n&quot;
suffix:colon
l_string|&quot;+&amp;d&quot;
(paren
id|sum
)paren
suffix:colon
l_string|&quot;d&quot;
(paren
id|buff
)paren
comma
l_string|&quot;d&quot;
(paren
id|len
)paren
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Fold a partial checksum without adding pseudo headers&n; */
DECL|function|csum_fold
r_int
r_int
id|csum_fold
c_func
(paren
r_int
r_int
id|sum
)paren
(brace
id|__asm__
id|__volatile__
(paren
l_string|&quot;    sr   3,3&bslash;n&quot;
multiline_comment|/* %0 = H*65536 + L */
l_string|&quot;    lr   2,%0&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = H L / 0 0 */
l_string|&quot;    srdl 2,16&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = 0 H / L 0 */
l_string|&quot;    alr  2,3&bslash;n&quot;
multiline_comment|/* %0 = H L, R2/R3 = L H / L 0 */
l_string|&quot;    alr  %0,2&bslash;n&quot;
multiline_comment|/* %0 = H+L+C L+H */
l_string|&quot;    srl  %0,16&bslash;n&quot;
multiline_comment|/* %0 = H+L+C */
suffix:colon
l_string|&quot;+d&quot;
(paren
id|sum
)paren
suffix:colon
suffix:colon
l_string|&quot;cc&quot;
comma
l_string|&quot;2&quot;
comma
l_string|&quot;3&quot;
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
op_complement
id|sum
)paren
suffix:semicolon
)brace
eof
