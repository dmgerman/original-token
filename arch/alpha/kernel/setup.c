multiline_comment|/*&n; *  linux/arch/alpha/kernel/setup.c&n; *&n; *  Copyright (C) 1995  Linus Torvalds&n; */
multiline_comment|/*&n; * bootup setup stuff..&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ldt.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/a.out.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/hwrpb.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|aux_device_present
r_int
r_char
id|aux_device_present
suffix:semicolon
multiline_comment|/*&n; * The format of &quot;screen_info&quot; is strange, and due to early&n; * i386-setup code. This is just enough to make the console&n; * code think we&squot;re on a EGA+ colour display.&n; */
DECL|variable|screen_info
r_struct
id|screen_info
id|screen_info
op_assign
(brace
l_int|0
comma
l_int|0
comma
multiline_comment|/* orig-x, orig-y */
l_int|0
comma
l_int|0
comma
multiline_comment|/* unused */
l_int|0
comma
multiline_comment|/* orig-video-page */
l_int|0
comma
multiline_comment|/* orig-video-mode */
l_int|80
comma
multiline_comment|/* orig-video-cols */
l_int|0
comma
l_int|0
comma
l_int|0
comma
multiline_comment|/* ega_ax, ega_bx, ega_cx */
l_int|25
multiline_comment|/* orig-video-lines */
)brace
suffix:semicolon
DECL|function|bios32_init
r_int
r_int
id|bios32_init
c_func
(paren
r_int
r_int
id|memory_start
comma
r_int
r_int
id|memory_end
)paren
(brace
r_return
id|memory_start
suffix:semicolon
)brace
DECL|function|find_end_memory
r_static
r_int
r_int
id|find_end_memory
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|high
op_assign
l_int|0
suffix:semicolon
r_struct
id|memclust_struct
op_star
id|cluster
suffix:semicolon
r_struct
id|memdesc_struct
op_star
id|memdesc
suffix:semicolon
id|memdesc
op_assign
(paren
r_struct
id|memdesc_struct
op_star
)paren
(paren
id|INIT_HWRPB-&gt;mddt_offset
op_plus
(paren
r_int
r_int
)paren
id|INIT_HWRPB
)paren
suffix:semicolon
id|cluster
op_assign
id|memdesc-&gt;cluster
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|memdesc-&gt;numclusters
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
comma
id|cluster
op_increment
)paren
(brace
r_int
r_int
id|tmp
suffix:semicolon
id|tmp
op_assign
(paren
id|cluster-&gt;start_pfn
op_plus
id|cluster-&gt;numpages
)paren
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_if
c_cond
(paren
id|tmp
OG
id|high
)paren
id|high
op_assign
id|tmp
suffix:semicolon
)brace
multiline_comment|/* round it up to an even number of pages.. */
id|high
op_assign
(paren
id|high
op_plus
id|PAGE_SIZE
)paren
op_amp
(paren
id|PAGE_MASK
op_star
l_int|2
)paren
suffix:semicolon
r_return
id|PAGE_OFFSET
op_plus
id|high
suffix:semicolon
)brace
DECL|function|setup_arch
r_void
id|setup_arch
c_func
(paren
r_char
op_star
op_star
id|cmdline_p
comma
r_int
r_int
op_star
id|memory_start_p
comma
r_int
r_int
op_star
id|memory_end_p
)paren
(brace
r_static
r_char
id|cmdline
(braket
)braket
op_assign
l_string|&quot;&quot;
suffix:semicolon
r_extern
r_int
id|_end
suffix:semicolon
id|ROOT_DEV
op_assign
l_int|0x0200
suffix:semicolon
multiline_comment|/* fd0 */
id|aux_device_present
op_assign
l_int|0xaa
suffix:semicolon
op_star
id|cmdline_p
op_assign
id|cmdline
suffix:semicolon
op_star
id|memory_start_p
op_assign
(paren
r_int
r_int
)paren
op_amp
id|_end
suffix:semicolon
op_star
id|memory_end_p
op_assign
id|find_end_memory
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|sys_ioperm
id|asmlinkage
r_int
id|sys_ioperm
c_func
(paren
r_int
r_int
id|from
comma
r_int
r_int
id|num
comma
r_int
id|on
)paren
(brace
r_return
op_minus
id|EIO
suffix:semicolon
)brace
eof
