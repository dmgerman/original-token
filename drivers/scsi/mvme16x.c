multiline_comment|/*&n; * Detection routine for the NCR53c710 based MVME16x SCSI Controllers for Linux.&n; *&n; * Based on work by Alan Hourihane&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/zorro.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mvme16xhw.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;53c7xx.h&quot;
macro_line|#include &quot;mvme16x.h&quot;
macro_line|#include &quot;asm/mvme16xhw.h&quot;
macro_line|#include&lt;linux/stat.h&gt;
DECL|variable|proc_scsi_mvme16x
r_struct
id|proc_dir_entry
id|proc_scsi_mvme16x
op_assign
(brace
id|PROC_SCSI_MVME16x
comma
l_int|7
comma
l_string|&quot;MVME16x&quot;
comma
id|S_IFDIR
op_or
id|S_IRUGO
op_or
id|S_IXUGO
comma
l_int|2
)brace
suffix:semicolon
r_extern
id|ncr53c7xx_init
(paren
id|Scsi_Host_Template
op_star
id|tpnt
comma
r_int
id|board
comma
r_int
id|chip
comma
id|u32
id|base
comma
r_int
id|io_port
comma
r_int
id|irq
comma
r_int
id|dma
comma
r_int
r_int
id|options
comma
r_int
id|clock
)paren
suffix:semicolon
DECL|function|mvme16x_scsi_detect
r_int
id|mvme16x_scsi_detect
c_func
(paren
id|Scsi_Host_Template
op_star
id|tpnt
)paren
(brace
r_static
r_int
r_char
id|called
op_assign
l_int|0
suffix:semicolon
r_int
id|clock
suffix:semicolon
r_int
r_int
id|options
suffix:semicolon
r_if
c_cond
(paren
id|mvme16x_config
op_amp
id|MVME16x_CONFIG_NO_SCSICHIP
)paren
(brace
id|printk
(paren
l_string|&quot;SCSI detection disabled, SCSI chip not present&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|called
)paren
r_return
l_int|0
suffix:semicolon
id|tpnt-&gt;proc_dir
op_assign
op_amp
id|proc_scsi_mvme16x
suffix:semicolon
id|options
op_assign
id|OPTION_MEMORY_MAPPED
op_or
id|OPTION_DEBUG_TEST1
op_or
id|OPTION_INTFLY
op_or
id|OPTION_SYNCHRONOUS
op_or
id|OPTION_ALWAYS_SYNCHRONOUS
op_or
id|OPTION_DISCONNECT
suffix:semicolon
id|clock
op_assign
l_int|66000000
suffix:semicolon
multiline_comment|/* 66MHz SCSI Clock */
id|ncr53c7xx_init
c_func
(paren
id|tpnt
comma
l_int|0
comma
l_int|710
comma
(paren
id|u32
)paren
l_int|0xfff47000
comma
l_int|0
comma
l_int|0x55
comma
id|DMA_NONE
comma
id|options
comma
id|clock
)paren
suffix:semicolon
id|called
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof