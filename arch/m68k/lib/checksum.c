multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;IP/TCP/UDP checksumming routines&n; *&n; * Authors:&t;Jorge Cwik, &lt;jorge@laser.satlink.net&gt;&n; *&t;&t;Arnt Gulbrandsen, &lt;agulbra@nvg.unit.no&gt;&n; *&t;&t;Tom May, &lt;ftom@netcom.com&gt;&n; *&t;&t;Andreas Schwab, &lt;schwab@issan.informatik.uni-dortmund.de&gt;&n; *&t;&t;Lots of code moved from tcp.c and ip.c; see those files&n; *&t;&t;for more names.&n; *&n; * 03/02/96&t;Jes Sorensen, Andreas Schwab, Roman Hodek:&n; *&t;&t;Fixed some nasty bugs, causing some horrible crashes.&n; *&t;&t;A: At some points, the sum (%0) was used as&n; *&t;&t;length-counter instead of the length counter&n; *&t;&t;(%1). Thanks to Roman Hodek for pointing this out.&n; *&t;&t;B: GCC seems to mess up if one uses too many&n; *&t;&t;data-registers to hold input values and one tries to&n; *&t;&t;specify d0 and d1 as scratch registers. Letting gcc choose these&n; *      registers itself solves the problem.&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;net/checksum.h&gt;
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
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
multiline_comment|/*&n;&t;   * Experiments with ethernet and slip connections show that buff&n;&t;   * is aligned on either a 2-byte or 4-byte boundary.&n;&t;   */
id|__asm__
c_func
(paren
l_string|&quot;movel %2,%3&bslash;n&bslash;t&quot;
l_string|&quot;btst #1,%3&bslash;n&bslash;t&quot;
multiline_comment|/* Check alignment */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* buff%4==2: treat first word */
l_string|&quot;jgt 1f&bslash;n&bslash;t&quot;
l_string|&quot;addql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len was == 2, treat only rest */
l_string|&quot;jra 4f&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;addw %2@+,%0&bslash;n&bslash;t&quot;
multiline_comment|/* add first word to sum */
l_string|&quot;clrl %3&bslash;n&bslash;t&quot;
l_string|&quot;addxl %3,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;2:&bslash;t&quot;
multiline_comment|/* unrolled loop for the main part: do 8 longs at once */
l_string|&quot;movel %1,%3&bslash;n&bslash;t&quot;
multiline_comment|/* save len in tmp1 */
l_string|&quot;lsrl #5,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len/32 */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
multiline_comment|/* not enough... */
l_string|&quot;subql #1,%1&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,1b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
multiline_comment|/* add X bit */
l_string|&quot;clrw %1&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;jcc 1b&bslash;n&quot;
l_string|&quot;2:&bslash;t&quot;
l_string|&quot;movel %3,%1&bslash;n&bslash;t&quot;
multiline_comment|/* restore len from tmp1 */
l_string|&quot;andw #0x1c,%3&bslash;n&bslash;t&quot;
multiline_comment|/* number of rest longs */
l_string|&quot;jeq 4f&bslash;n&bslash;t&quot;
l_string|&quot;lsrw #2,%3&bslash;n&bslash;t&quot;
l_string|&quot;subqw #1,%3&bslash;n&quot;
l_string|&quot;3:&bslash;t&quot;
multiline_comment|/* loop for rest longs */
l_string|&quot;movel %2@+,%4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;dbra %3,3b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;4:&bslash;t&quot;
multiline_comment|/* now check for rest bytes that do not fit into longs */
l_string|&quot;andw #3,%1&bslash;n&bslash;t&quot;
l_string|&quot;jeq 7f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
multiline_comment|/* clear tmp2 for rest bytes */
l_string|&quot;subqw #2,%1&bslash;n&bslash;t&quot;
l_string|&quot;jlt 5f&bslash;n&bslash;t&quot;
l_string|&quot;movew %2@+,%4&bslash;n&bslash;t&quot;
multiline_comment|/* have rest &gt;= 2: get word */
l_string|&quot;swap %4&bslash;n&bslash;t&quot;
multiline_comment|/* into bits 16..31 */
l_string|&quot;tstw %1&bslash;n&bslash;t&quot;
multiline_comment|/* another byte? */
l_string|&quot;jeq 6f&bslash;n&quot;
l_string|&quot;5:&bslash;t&quot;
l_string|&quot;moveb %2@,%4&bslash;n&bslash;t&quot;
multiline_comment|/* have odd rest: get byte */
l_string|&quot;lslw #8,%4&bslash;n&bslash;t&quot;
multiline_comment|/* into bits 8..15; 16..31 untouched */
l_string|&quot;6:&bslash;t&quot;
l_string|&quot;addl %4,%0&bslash;n&bslash;t&quot;
multiline_comment|/* now add rest long to sum */
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;7:&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=d&quot;
(paren
id|len
)paren
comma
l_string|&quot;=a&quot;
(paren
id|buff
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|len
)paren
comma
l_string|&quot;2&quot;
(paren
id|buff
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * copy from fs while checksumming, otherwise like csum_partial&n; */
r_int
r_int
DECL|function|csum_partial_copy_fromuser
id|csum_partial_copy_fromuser
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
id|sum
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movel %2,%4&bslash;n&bslash;t&quot;
l_string|&quot;btst #1,%4&bslash;n&bslash;t&quot;
multiline_comment|/* Check alignment */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* buff%4==2: treat first word */
l_string|&quot;jgt 1f&bslash;n&bslash;t&quot;
l_string|&quot;addql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len was == 2, treat only rest */
l_string|&quot;jra 4f&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movesw %2@+,%4&bslash;n&bslash;t&quot;
multiline_comment|/* add first word to sum */
l_string|&quot;addw %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movew %4,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;2:&bslash;t&quot;
multiline_comment|/* unrolled loop for the main part: do 8 longs at once */
l_string|&quot;movel %1,%4&bslash;n&bslash;t&quot;
multiline_comment|/* save len in tmp1 */
l_string|&quot;lsrl #5,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len/32 */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
multiline_comment|/* not enough... */
l_string|&quot;subql #1,%1&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,1b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
multiline_comment|/* add X bit */
l_string|&quot;clrw %1&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;jcc 1b&bslash;n&quot;
l_string|&quot;2:&bslash;t&quot;
l_string|&quot;movel %4,%1&bslash;n&bslash;t&quot;
multiline_comment|/* restore len from tmp1 */
l_string|&quot;andw #0x1c,%4&bslash;n&bslash;t&quot;
multiline_comment|/* number of rest longs */
l_string|&quot;jeq 4f&bslash;n&bslash;t&quot;
l_string|&quot;lsrw #2,%4&bslash;n&bslash;t&quot;
l_string|&quot;subqw #1,%4&bslash;n&quot;
l_string|&quot;3:&bslash;t&quot;
multiline_comment|/* loop for rest longs */
l_string|&quot;movesl %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %4,3b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;4:&bslash;t&quot;
multiline_comment|/* now check for rest bytes that do not fit into longs */
l_string|&quot;andw #3,%1&bslash;n&bslash;t&quot;
l_string|&quot;jeq 7f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
multiline_comment|/* clear tmp2 for rest bytes */
l_string|&quot;subqw #2,%1&bslash;n&bslash;t&quot;
l_string|&quot;jlt 5f&bslash;n&bslash;t&quot;
l_string|&quot;movesw %2@+,%5&bslash;n&bslash;t&quot;
multiline_comment|/* have rest &gt;= 2: get word */
l_string|&quot;movew %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;swap %5&bslash;n&bslash;t&quot;
multiline_comment|/* into bits 16..31 */
l_string|&quot;tstw %1&bslash;n&bslash;t&quot;
multiline_comment|/* another byte? */
l_string|&quot;jeq 6f&bslash;n&quot;
l_string|&quot;5:&bslash;t&quot;
l_string|&quot;movesb %2@,%5&bslash;n&bslash;t&quot;
multiline_comment|/* have odd rest: get byte */
l_string|&quot;moveb %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;lslw #8,%5&bslash;n&bslash;t&quot;
multiline_comment|/* into bits 8..15; 16..31 untouched */
l_string|&quot;6:&bslash;t&quot;
l_string|&quot;addl %5,%0&bslash;n&bslash;t&quot;
multiline_comment|/* now add rest long to sum */
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;7:&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=d&quot;
(paren
id|len
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|len
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|dst
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
multiline_comment|/*&n; * copy from ds while checksumming, otherwise like csum_partial&n; */
r_int
r_int
DECL|function|csum_partial_copy
id|csum_partial_copy
c_func
(paren
r_const
r_char
op_star
id|src
comma
r_char
op_star
id|dst
comma
r_int
id|len
comma
r_int
id|sum
)paren
(brace
r_int
r_int
id|tmp1
comma
id|tmp2
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;movel %2,%4&bslash;n&bslash;t&quot;
l_string|&quot;btst #1,%4&bslash;n&bslash;t&quot;
multiline_comment|/* Check alignment */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
l_string|&quot;subql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* buff%4==2: treat first word */
l_string|&quot;jgt 1f&bslash;n&bslash;t&quot;
l_string|&quot;addql #2,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len was == 2, treat only rest */
l_string|&quot;jra 4f&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movew %2@+,%4&bslash;n&bslash;t&quot;
multiline_comment|/* add first word to sum */
l_string|&quot;addw %4,%0&bslash;n&bslash;t&quot;
l_string|&quot;movew %4,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;clrl %4&bslash;n&bslash;t&quot;
l_string|&quot;addxl %4,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;2:&bslash;t&quot;
multiline_comment|/* unrolled loop for the main part: do 8 longs at once */
l_string|&quot;movel %1,%4&bslash;n&bslash;t&quot;
multiline_comment|/* save len in tmp1 */
l_string|&quot;lsrl #5,%1&bslash;n&bslash;t&quot;
multiline_comment|/* len/32 */
l_string|&quot;jeq 2f&bslash;n&bslash;t&quot;
multiline_comment|/* not enough... */
l_string|&quot;subql #1,%1&bslash;n&quot;
l_string|&quot;1:&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %1,1b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
multiline_comment|/* add X bit */
l_string|&quot;clrw %1&bslash;n&bslash;t&quot;
l_string|&quot;subql #1,%1&bslash;n&bslash;t&quot;
l_string|&quot;jcc 1b&bslash;n&quot;
l_string|&quot;2:&bslash;t&quot;
l_string|&quot;movel %4,%1&bslash;n&bslash;t&quot;
multiline_comment|/* restore len from tmp1 */
l_string|&quot;andw #0x1c,%4&bslash;n&bslash;t&quot;
multiline_comment|/* number of rest longs */
l_string|&quot;jeq 4f&bslash;n&bslash;t&quot;
l_string|&quot;lsrw #2,%4&bslash;n&bslash;t&quot;
l_string|&quot;subqw #1,%4&bslash;n&quot;
l_string|&quot;3:&bslash;t&quot;
multiline_comment|/* loop for rest longs */
l_string|&quot;movel %2@+,%5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&bslash;t&quot;
l_string|&quot;movel %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;dbra %4,3b&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;4:&bslash;t&quot;
multiline_comment|/* now check for rest bytes that do not fit into longs */
l_string|&quot;andw #3,%1&bslash;n&bslash;t&quot;
l_string|&quot;jeq 7f&bslash;n&bslash;t&quot;
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
multiline_comment|/* clear tmp2 for rest bytes */
l_string|&quot;subqw #2,%1&bslash;n&bslash;t&quot;
l_string|&quot;jlt 5f&bslash;n&bslash;t&quot;
l_string|&quot;movew %2@+,%5&bslash;n&bslash;t&quot;
multiline_comment|/* have rest &gt;= 2: get word */
l_string|&quot;movew %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;swap %5&bslash;n&bslash;t&quot;
multiline_comment|/* into bits 16..31 */
l_string|&quot;tstw %1&bslash;n&bslash;t&quot;
multiline_comment|/* another byte? */
l_string|&quot;jeq 6f&bslash;n&quot;
l_string|&quot;5:&bslash;t&quot;
l_string|&quot;moveb %2@,%5&bslash;n&bslash;t&quot;
multiline_comment|/* have odd rest: get byte */
l_string|&quot;moveb %5,%3@+&bslash;n&bslash;t&quot;
l_string|&quot;lslw #8,%5&bslash;n&quot;
multiline_comment|/* into bits 8..15; 16..31 untouched */
l_string|&quot;6:&bslash;t&quot;
l_string|&quot;addl %5,%0&bslash;n&bslash;t&quot;
multiline_comment|/* now add rest long to sum */
l_string|&quot;clrl %5&bslash;n&bslash;t&quot;
l_string|&quot;addxl %5,%0&bslash;n&quot;
multiline_comment|/* add X bit */
l_string|&quot;7:&bslash;t&quot;
suffix:colon
l_string|&quot;=d&quot;
(paren
id|sum
)paren
comma
l_string|&quot;=d&quot;
(paren
id|len
)paren
comma
l_string|&quot;=a&quot;
(paren
id|src
)paren
comma
l_string|&quot;=a&quot;
(paren
id|dst
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp1
)paren
comma
l_string|&quot;=&amp;d&quot;
(paren
id|tmp2
)paren
suffix:colon
l_string|&quot;0&quot;
(paren
id|sum
)paren
comma
l_string|&quot;1&quot;
(paren
id|len
)paren
comma
l_string|&quot;2&quot;
(paren
id|src
)paren
comma
l_string|&quot;3&quot;
(paren
id|dst
)paren
)paren
suffix:semicolon
r_return
id|sum
suffix:semicolon
)brace
eof