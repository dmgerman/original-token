macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_SD
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &quot;../blk.h&quot;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;sd.h&quot;
r_extern
r_int
id|scsi_ioctl
(paren
r_int
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|function|sd_ioctl
r_int
id|sd_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|dev
op_assign
id|inode-&gt;i_rdev
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
id|RO_IOCTLS
c_func
(paren
id|dev
comma
id|arg
)paren
suffix:semicolon
r_default
suffix:colon
r_return
id|scsi_ioctl
c_func
(paren
id|rscsi_disks
(braket
id|MINOR
c_func
(paren
id|dev
)paren
op_rshift
l_int|4
)braket
dot
id|device
comma
id|cmd
comma
(paren
r_void
op_star
)paren
id|arg
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
eof