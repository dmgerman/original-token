multiline_comment|/*&n;&t;The st.c file is a sub-stub file.  I just wanted to have all the detect code, etc in the&n;&t;mid level driver present and working.  If no one else volunteers for this, I&squot;ll&n;&t;do it - but it&squot;s low on my list of priorities.&n;*/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_ST
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;st.h&quot;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 9
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &quot;../blk.h&quot; 
DECL|variable|scsi_tapes
id|Scsi_Tape
id|scsi_tapes
(braket
id|MAX_ST
)braket
suffix:semicolon
DECL|variable|st_sizes
r_static
r_int
id|st_sizes
(braket
id|MAX_ST
)braket
suffix:semicolon
DECL|variable|NR_ST
r_int
id|NR_ST
op_assign
l_int|0
suffix:semicolon
DECL|function|do_st_request
r_void
id|do_st_request
c_func
(paren
r_void
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;There is no st driver.&bslash;n&bslash;r&quot;
)paren
suffix:semicolon
)brace
DECL|function|st_init
r_void
id|st_init
c_func
(paren
r_void
)paren
(brace
id|blk_dev
(braket
id|MAJOR_NR
)braket
dot
id|request_fn
op_assign
id|do_st_request
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|st_sizes
suffix:semicolon
)brace
macro_line|#endif&t;
eof
