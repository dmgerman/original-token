macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;../blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_ioctl.h&quot;
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES 5&t;
DECL|macro|MAX_TIMEOUT
mdefine_line|#define MAX_TIMEOUT 200
DECL|macro|MAX_BUF
mdefine_line|#define MAX_BUF 4096
DECL|macro|max
mdefine_line|#define max(a,b) (((a) &gt; (b)) ? (a) : (b))
multiline_comment|/*&n; * If we are told to probe a host, we will return 0 if  the host is not&n; * present, 1 if the host is present, and will return an identifying&n; * string at *arg, if arg is non null, filling to the length stored at&n; * (int *) arg&n; */
DECL|function|ioctl_probe
r_static
r_int
id|ioctl_probe
c_func
(paren
r_int
id|dev
comma
r_void
op_star
id|buffer
)paren
(brace
r_int
id|temp
suffix:semicolon
r_int
r_int
id|len
comma
id|slen
suffix:semicolon
r_const
r_char
op_star
id|string
suffix:semicolon
r_if
c_cond
(paren
(paren
id|temp
op_assign
id|scsi_hosts
(braket
id|dev
)braket
dot
id|present
)paren
op_logical_and
id|buffer
)paren
(brace
id|len
op_assign
id|get_fs_long
(paren
(paren
r_int
r_int
op_star
)paren
id|buffer
)paren
suffix:semicolon
id|string
op_assign
id|scsi_hosts
(braket
id|dev
)braket
dot
id|info
c_func
(paren
)paren
suffix:semicolon
id|slen
op_assign
id|strlen
c_func
(paren
id|string
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|slen
)paren
id|len
op_assign
id|slen
op_plus
l_int|1
suffix:semicolon
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buffer
comma
id|len
)paren
suffix:semicolon
id|memcpy_tofs
(paren
id|buffer
comma
id|string
comma
id|len
)paren
suffix:semicolon
)brace
r_return
id|temp
suffix:semicolon
)brace
multiline_comment|/*&n; * &n; * The SCSI_IOCTL_SEND_COMMAND ioctl sends a command out to the SCSI host.&n; * The MAX_TIMEOUT and MAX_RETRIES  variables are used.  &n; * &n; * dev is the SCSI device struct ptr, *(int *) arg is the length of the&n; * input data, if any, not including the command string &amp; counts, &n; * *((int *)arg + 1) is the output buffer size in bytes.&n; * &n; * *(char *) ((int *) arg)[2] the actual command byte.   &n; * &n; * Note that no more than MAX_BUF data bytes will be transfered.  Since&n; * SCSI block device size is 512 bytes, I figured 1K was good.&n; * but (WDE) changed it to 8192 to handle large bad track buffers.&n; * ERY: I changed this to a dynamic allocation using scsi_malloc - we were&n; * getting a kernel stack overflow which was crashing the system when we&n; * were using 8192 bytes.&n; * &n; * This size *does not* include the initial lengths that were passed.&n; * &n; * The SCSI command is read from the memory location immediately after the&n; * length words, and the input data is right after the command.  The SCSI&n; * routines know the command size based on the opcode decode.  &n; * &n; * The output area is then filled in starting from the command byte. &n; */
DECL|function|scsi_ioctl_done
r_static
r_void
id|scsi_ioctl_done
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_struct
id|request
op_star
id|req
suffix:semicolon
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|req
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
id|req-&gt;dev
op_assign
l_int|0xfffe
suffix:semicolon
multiline_comment|/* Busy, but indicate request done */
r_if
c_cond
(paren
(paren
id|p
op_assign
id|req-&gt;waiting
)paren
op_ne
l_int|NULL
)paren
(brace
id|req-&gt;waiting
op_assign
l_int|NULL
suffix:semicolon
id|p-&gt;state
op_assign
id|TASK_RUNNING
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;counter
OG
id|current-&gt;counter
)paren
id|need_resched
op_assign
l_int|1
suffix:semicolon
)brace
)brace
DECL|function|ioctl_internal_command
r_static
r_int
id|ioctl_internal_command
c_func
(paren
id|Scsi_Device
op_star
id|dev
comma
r_char
op_star
id|cmd
)paren
(brace
r_int
id|host
comma
id|result
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|host
op_assign
id|dev-&gt;host_no
suffix:semicolon
id|SCpnt
op_assign
id|allocate_device
c_func
(paren
l_int|NULL
comma
id|dev-&gt;index
comma
l_int|1
)paren
suffix:semicolon
id|scsi_do_cmd
c_func
(paren
id|SCpnt
comma
id|cmd
comma
l_int|NULL
comma
l_int|0
comma
id|scsi_ioctl_done
comma
id|MAX_TIMEOUT
comma
id|MAX_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;request.dev
op_ne
l_int|0xfffe
)paren
(brace
id|SCpnt-&gt;request.waiting
op_assign
id|current
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
r_while
c_loop
(paren
id|SCpnt-&gt;request.dev
op_ne
l_int|0xfffe
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|driver_byte
c_func
(paren
id|SCpnt-&gt;result
)paren
op_ne
l_int|0
)paren
r_switch
c_cond
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
(brace
r_case
id|ILLEGAL_REQUEST
suffix:colon
r_if
c_cond
(paren
id|cmd
(braket
l_int|0
)braket
op_eq
id|ALLOW_MEDIUM_REMOVAL
)paren
(brace
id|dev-&gt;lockable
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;SCSI device (ioctl) reports ILLEGAL REQUEST.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NOT_READY
suffix:colon
multiline_comment|/* This happens if there is no disc in drive */
r_if
c_cond
(paren
id|dev-&gt;removable
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Device not ready.  Make sure there is a disc in the drive.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_case
id|UNIT_ATTENTION
suffix:colon
r_if
c_cond
(paren
id|dev-&gt;removable
)paren
(brace
id|dev-&gt;changed
op_assign
l_int|1
suffix:semicolon
id|SCpnt-&gt;result
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This is no longer considered an error */
id|printk
c_func
(paren
l_string|&quot;Disc change detected.&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Fall through for non-removable media */
id|printk
c_func
(paren
l_string|&quot;SCSI CD error: host %d id %d lun %d return code = %x&bslash;n&quot;
comma
id|dev-&gt;host_no
comma
id|dev-&gt;id
comma
id|dev-&gt;lun
comma
id|SCpnt-&gt;result
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;tSense class %x, sense error %x, extended sense %x&bslash;n&quot;
comma
id|sense_class
c_func
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|sense_error
c_func
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
suffix:semicolon
)brace
suffix:semicolon
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
id|SCpnt-&gt;request.dev
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Mark as not busy */
id|wake_up
c_func
(paren
op_amp
id|scsi_devices
(braket
id|SCpnt-&gt;index
)braket
dot
id|device_wait
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|ioctl_command
r_static
r_int
id|ioctl_command
c_func
(paren
id|Scsi_Device
op_star
id|dev
comma
r_void
op_star
id|buffer
)paren
(brace
r_char
op_star
id|buf
suffix:semicolon
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
r_char
op_star
id|cmd_in
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
r_int
r_char
id|opcode
suffix:semicolon
r_int
id|inlen
comma
id|outlen
comma
id|cmdlen
comma
id|host
suffix:semicolon
r_int
id|needed
suffix:semicolon
r_int
id|result
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|inlen
op_assign
id|get_fs_long
c_func
(paren
(paren
r_int
r_int
op_star
)paren
id|buffer
)paren
suffix:semicolon
id|outlen
op_assign
id|get_fs_long
c_func
(paren
(paren
(paren
r_int
r_int
op_star
)paren
id|buffer
)paren
op_plus
l_int|1
)paren
suffix:semicolon
id|cmd_in
op_assign
(paren
r_char
op_star
)paren
(paren
(paren
(paren
r_int
op_star
)paren
id|buffer
)paren
op_plus
l_int|2
)paren
suffix:semicolon
id|opcode
op_assign
id|get_fs_byte
c_func
(paren
id|cmd_in
)paren
suffix:semicolon
id|needed
op_assign
(paren
id|inlen
OG
id|outlen
ques
c_cond
id|inlen
suffix:colon
id|outlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|needed
)paren
(brace
id|needed
op_assign
(paren
id|needed
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|511
suffix:semicolon
r_if
c_cond
(paren
id|needed
OG
id|MAX_BUF
)paren
id|needed
op_assign
id|MAX_BUF
suffix:semicolon
id|buf
op_assign
(paren
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
id|needed
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buf
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_else
id|buf
op_assign
l_int|NULL
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_void
op_star
)paren
id|cmd
comma
id|cmd_in
comma
id|cmdlen
op_assign
id|COMMAND_SIZE
(paren
id|opcode
)paren
)paren
suffix:semicolon
id|memcpy_fromfs
(paren
(paren
r_void
op_star
)paren
id|buf
comma
(paren
r_void
op_star
)paren
(paren
id|cmd_in
op_plus
id|cmdlen
)paren
comma
id|inlen
OG
id|MAX_BUF
ques
c_cond
id|MAX_BUF
suffix:colon
id|inlen
)paren
suffix:semicolon
id|host
op_assign
id|dev-&gt;host_no
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|cmd
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_or
(paren
id|dev-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
macro_line|#ifndef DEBUG_NO_CMD
id|SCpnt
op_assign
id|allocate_device
c_func
(paren
l_int|NULL
comma
id|dev-&gt;index
comma
l_int|1
)paren
suffix:semicolon
id|scsi_do_cmd
c_func
(paren
id|SCpnt
comma
id|cmd
comma
id|buf
comma
(paren
(paren
id|outlen
OG
id|MAX_BUF
)paren
ques
c_cond
id|MAX_BUF
suffix:colon
id|outlen
)paren
comma
id|scsi_ioctl_done
comma
id|MAX_TIMEOUT
comma
id|MAX_RETRIES
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;request.dev
op_ne
l_int|0xfffe
)paren
(brace
id|SCpnt-&gt;request.waiting
op_assign
id|current
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
r_while
c_loop
(paren
id|SCpnt-&gt;request.dev
op_ne
l_int|0xfffe
)paren
id|schedule
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
id|result
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|cmd_in
comma
(paren
id|outlen
OG
id|MAX_BUF
)paren
ques
c_cond
id|MAX_BUF
suffix:colon
id|outlen
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_return
id|result
suffix:semicolon
id|memcpy_tofs
(paren
(paren
r_void
op_star
)paren
id|cmd_in
comma
id|buf
comma
(paren
id|outlen
OG
id|MAX_BUF
)paren
ques
c_cond
id|MAX_BUF
suffix:colon
id|outlen
)paren
suffix:semicolon
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
id|SCpnt-&gt;request.dev
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Mark as not busy */
r_if
c_cond
(paren
id|buf
)paren
id|scsi_free
c_func
(paren
id|buf
comma
id|needed
)paren
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|scsi_devices
(braket
id|SCpnt-&gt;index
)braket
dot
id|device_wait
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
macro_line|#else
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;scsi_ioctl : device %d.  command = &quot;
comma
id|dev-&gt;id
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|cmd
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;nbuffer =&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|20
suffix:semicolon
op_increment
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;%02x &quot;
comma
id|buf
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;inlen = %d, outlen = %d, cmdlen = %d&bslash;n&quot;
comma
id|inlen
comma
id|outlen
comma
id|cmdlen
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;buffer = %d, cmd_in = %d&bslash;n&quot;
comma
id|buffer
comma
id|cmd_in
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n;&t;the scsi_ioctl() function differs from most ioctls in that it does&n;&t;not take a major/minor number as the dev filed.  Rather, it takes&n;&t;a pointer to a scsi_devices[] element, a structure. &n;*/
DECL|function|scsi_ioctl
r_int
id|scsi_ioctl
(paren
id|Scsi_Device
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_char
id|scsi_cmd
(braket
l_int|10
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_ne
l_int|0
op_logical_and
id|dev-&gt;index
OG
id|NR_SCSI_DEVICES
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
(paren
id|cmd
op_eq
l_int|0
op_logical_and
id|dev-&gt;host_no
OG
id|max_scsi_hosts
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|SCSI_IOCTL_GET_IDLUN
suffix:colon
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_int
)paren
)paren
suffix:semicolon
id|put_fs_long
c_func
(paren
id|dev-&gt;id
op_plus
(paren
id|dev-&gt;lun
op_lshift
l_int|8
)paren
op_plus
(paren
id|dev-&gt;host_no
op_lshift
l_int|16
)paren
comma
(paren
r_int
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SCSI_IOCTL_PROBE_HOST
suffix:colon
r_return
id|ioctl_probe
c_func
(paren
id|dev-&gt;host_no
comma
id|arg
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_SEND_COMMAND
suffix:colon
r_return
id|ioctl_command
c_func
(paren
(paren
id|Scsi_Device
op_star
)paren
id|dev
comma
id|arg
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_DOORLOCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;removable
op_logical_or
op_logical_neg
id|dev-&gt;lockable
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|ALLOW_MEDIUM_REMOVAL
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
id|dev-&gt;lun
op_lshift
l_int|5
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
id|SCSI_REMOVAL_PREVENT
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
(paren
id|Scsi_Device
op_star
)paren
id|dev
comma
id|scsi_cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SCSI_IOCTL_DOORUNLOCK
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;removable
op_logical_or
op_logical_neg
id|dev-&gt;lockable
)paren
r_return
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|ALLOW_MEDIUM_REMOVAL
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
id|dev-&gt;lun
op_lshift
l_int|5
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
id|SCSI_REMOVAL_ALLOW
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
(paren
id|Scsi_Device
op_star
)paren
id|dev
comma
id|scsi_cmd
)paren
suffix:semicolon
r_case
id|SCSI_IOCTL_TEST_UNIT_READY
suffix:colon
id|scsi_cmd
(braket
l_int|0
)braket
op_assign
id|TEST_UNIT_READY
suffix:semicolon
id|scsi_cmd
(braket
l_int|1
)braket
op_assign
id|dev-&gt;lun
op_lshift
l_int|5
suffix:semicolon
id|scsi_cmd
(braket
l_int|2
)braket
op_assign
id|scsi_cmd
(braket
l_int|3
)braket
op_assign
id|scsi_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|scsi_cmd
(braket
l_int|4
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|ioctl_internal_command
c_func
(paren
(paren
id|Scsi_Device
op_star
)paren
id|dev
comma
id|scsi_cmd
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Just like scsi_ioctl, only callable from kernel space with no &n; * fs segment fiddling.&n; */
DECL|function|kernel_scsi_ioctl
r_int
id|kernel_scsi_ioctl
(paren
id|Scsi_Device
op_star
id|dev
comma
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
r_int
r_int
id|oldfs
suffix:semicolon
r_int
id|tmp
suffix:semicolon
id|oldfs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|get_ds
c_func
(paren
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|scsi_ioctl
(paren
id|dev
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|oldfs
)paren
suffix:semicolon
r_return
id|tmp
suffix:semicolon
)brace
eof
