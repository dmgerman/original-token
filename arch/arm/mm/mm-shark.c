multiline_comment|/*&n; * arch/arm/mm/mm-shark.c&n; *&n; * by Alexander.Schulz@stud.uni-karlsruhe.de&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &quot;map.h&quot;
DECL|variable|__initdata
r_struct
id|map_desc
id|io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|FB_BASE
comma
id|FB_START
comma
id|FB_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|FBREG_BASE
comma
id|FBREG_START
comma
id|FBREG_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|macro|SIZEOFMAP
mdefine_line|#define SIZEOFMAP (sizeof(io_desc) / sizeof(io_desc[0]))
DECL|variable|io_desc_size
r_int
r_int
id|__initdata
id|io_desc_size
op_assign
id|SIZEOFMAP
suffix:semicolon
eof
