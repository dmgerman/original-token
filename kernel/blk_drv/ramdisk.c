multiline_comment|/*&n; *  linux/kernel/blk_drv/ramdisk.c&n; *&n; *  Written by Theodore Ts&squot;o&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 1
macro_line|#include &quot;blk.h&quot;
DECL|variable|ram_disk
r_char
op_star
id|ram_disk
suffix:semicolon
multiline_comment|/* Start of ram disk */
DECL|variable|ram_disk_size
r_int
id|ram_disk_size
suffix:semicolon
multiline_comment|/* Size of ram disk */
DECL|function|do_ram_request
r_void
id|do_ram_request
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|r
suffix:semicolon
r_int
r_int
id|block
comma
id|dev
suffix:semicolon
r_int
r_int
id|sec
comma
id|head
comma
id|cyl
suffix:semicolon
r_int
r_int
id|nsect
suffix:semicolon
id|INIT_REQUEST
suffix:semicolon
r_if
c_cond
(paren
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
op_ne
l_int|0
)paren
(brace
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
id|block
op_assign
id|CURRENT-&gt;sector
suffix:semicolon
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ram_init
r_void
id|ram_init
c_func
(paren
r_void
)paren
(brace
)brace
eof
