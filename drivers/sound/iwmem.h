multiline_comment|/*&n; * sound/iwmem.h&n; *&n; * DRAM size encoding table for AMD Interwave chip.&n; */
multiline_comment|/*&n; * Copyright (C) by Hannu Savolainen 1993-1997&n; *&n; * OSS/Free for Linux is distributed under the GNU GENERAL PUBLIC LICENSE (GPL)&n; * Version 2 (June 1991). See the &quot;COPYING&quot; file distributed with this software&n; * for more info.&n; *&n; * Changes:&n; * Bartlomiej Zolnierkiewicz&t;: added __initdata to mem_decode&n; */
DECL|macro|K
mdefine_line|#define K 1024
DECL|macro|M
mdefine_line|#define M (1024*K)
DECL|variable|__initdata
r_static
r_int
id|mem_decode
(braket
)braket
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
multiline_comment|/*&t;Bank0&t;Bank1&t;Bank2&t;Bank3&t;Encoding bits&t;*/
(brace
l_int|256
op_star
id|K
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/*  0 */
(brace
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/*  1 */
(brace
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
)brace
comma
multiline_comment|/*  2 */
(brace
l_int|256
op_star
id|K
comma
l_int|1
op_star
id|M
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/*  3 */
(brace
l_int|256
op_star
id|K
comma
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
)brace
comma
multiline_comment|/*  4 */
(brace
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
comma
l_int|1
op_star
id|M
comma
l_int|0
)brace
comma
multiline_comment|/*  5 */
(brace
l_int|256
op_star
id|K
comma
l_int|256
op_star
id|K
comma
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
)brace
comma
multiline_comment|/*  6 */
(brace
l_int|1
op_star
id|M
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/*  7 */
(brace
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/*  8 */
(brace
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
comma
l_int|1
op_star
id|M
)brace
comma
multiline_comment|/*  9 */
(brace
l_int|4
op_star
id|M
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 10 */
(brace
l_int|4
op_star
id|M
comma
l_int|4
op_star
id|M
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* 11 */
(brace
l_int|4
op_star
id|M
comma
l_int|4
op_star
id|M
comma
l_int|4
op_star
id|M
comma
l_int|4
op_star
id|M
)brace
multiline_comment|/* 12 */
)brace
suffix:semicolon
eof
