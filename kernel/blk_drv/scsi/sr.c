multiline_comment|/*&n; *      sr.c by David Giller&n; *&n; *      adapted from:&n; *&t;sd.c Copyright (C) 1992 Drew Eckhardt &n; *&t;Linux scsi disk driver by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_BLK_DEV_SR
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;sr.h&quot;
macro_line|#include &quot;scsi_ioctl.h&quot;   /* For the door lock/unlock commands */
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 11
macro_line|#include &quot;../blk.h&quot;
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES 0
DECL|macro|SR_TIMEOUT
mdefine_line|#define SR_TIMEOUT 200
DECL|variable|NR_SR
r_int
id|NR_SR
op_assign
l_int|0
suffix:semicolon
DECL|variable|scsi_CDs
id|Scsi_CD
id|scsi_CDs
(braket
id|MAX_SR
)braket
suffix:semicolon
DECL|variable|sr_sizes
r_static
r_int
id|sr_sizes
(braket
id|MAX_SR
op_lshift
l_int|4
)braket
suffix:semicolon
DECL|variable|this_count
r_static
r_int
r_int
r_int
id|this_count
suffix:semicolon
DECL|struct|block_buffer
r_struct
id|block_buffer
(brace
DECL|member|block
r_int
id|block
suffix:semicolon
DECL|member|start
r_int
id|start
suffix:semicolon
DECL|member|use
r_int
id|use
suffix:colon
l_int|1
suffix:semicolon
DECL|member|buffer
r_int
r_char
id|buffer
(braket
l_int|2048
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|bb
r_static
r_struct
id|block_buffer
id|bb
(braket
id|MAX_SR
)braket
suffix:semicolon
r_static
r_int
id|sr_open
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
)paren
suffix:semicolon
r_extern
r_int
id|sr_ioctl
c_func
(paren
r_struct
id|inode
op_star
comma
r_struct
id|file
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
DECL|function|sr_release
r_static
r_void
id|sr_release
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
)paren
(brace
id|sync_dev
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|device-&gt;access_count
)paren
(brace
id|sr_ioctl
c_func
(paren
id|inode
comma
l_int|NULL
comma
id|SCSI_IOCTL_DOORUNLOCK
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|variable|sr_fops
r_static
r_struct
id|file_operations
id|sr_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek - default */
id|block_read
comma
multiline_comment|/* read - general block-dev read */
id|block_write
comma
multiline_comment|/* write - general block-dev write */
l_int|NULL
comma
multiline_comment|/* readdir - bad */
l_int|NULL
comma
multiline_comment|/* select */
id|sr_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|sr_open
comma
multiline_comment|/* no special open code */
id|sr_release
multiline_comment|/* release */
)brace
suffix:semicolon
multiline_comment|/*&n; * This function checks to see if the media has been changed in the&n; * CDROM drive.  It is possible that we have already sensed a change,&n; * or the drive may have sensed one and not yet reported it.  We must&n; * be ready for either case. This function always reports the current&n; * value of the changed bit.  If flag is 0, then the changed bit is reset.&n; * This function could be done as an ioctl, but we would need to have&n; * an inode for that to work, and we do not always have one.&n; */
DECL|function|check_cdrom_media_change
r_int
(def_block
id|check_cdrom_media_change
c_func
(paren
r_int
id|full_dev
comma
r_int
id|flag
)paren
(brace
r_int
id|retval
comma
id|target
suffix:semicolon
r_struct
id|inode
id|inode
suffix:semicolon
id|target
op_assign
id|MINOR
c_func
(paren
id|full_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|target
op_ge
id|NR_SR
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CD-ROM request error: invalid device.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
id|inode.i_rdev
op_assign
id|full_dev
suffix:semicolon
multiline_comment|/* This is all we really need here */
id|retval
op_assign
id|sr_ioctl
c_func
(paren
op_amp
id|inode
comma
l_int|NULL
comma
id|SCSI_IOCTL_TEST_UNIT_READY
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
multiline_comment|/* Unable to test, unit probably not ready.  This usually&n;&t;&t;     means there is no disc in the drive.  Mark as changed,&n;&t;&t;     and we will figure it out later once the drive is&n;&t;&t;     available again.  */
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;changed
op_assign
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
multiline_comment|/* This will force a flush, if called from&n;&t;&t;       check_disk_change */
)brace
suffix:semicolon
id|retval
op_assign
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;changed
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|flag
)paren
(brace
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;changed
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|retval
suffix:semicolon
)brace
)def_block
multiline_comment|/*&n; * The sense_buffer is where we put data for all mode sense commands performed.&n; */
DECL|variable|sense_buffer
r_static
r_int
r_char
id|sense_buffer
(braket
l_int|255
)braket
suffix:semicolon
multiline_comment|/*&n; * rw_intr is the interrupt routine for the device driver.  It will be notified on the &n; * end of a SCSI read / write, and will take on of several actions based on success or failure.&n; */
DECL|function|rw_intr
r_static
r_void
id|rw_intr
(paren
r_int
id|host
comma
r_int
id|result
)paren
(brace
r_if
c_cond
(paren
id|SR_HOST
op_ne
id|host
)paren
(brace
id|panic
(paren
l_string|&quot;sr.o : rw_intr() recieving interrupt for different host.&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|result
)paren
(brace
multiline_comment|/* No error */
r_if
c_cond
(paren
id|bb
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|use
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|CURRENT-&gt;buffer
comma
id|bb
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|buffer
op_plus
(paren
id|bb
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|start
op_lshift
l_int|9
)paren
comma
id|this_count
op_lshift
l_int|9
)paren
suffix:semicolon
)brace
id|CURRENT-&gt;nr_sectors
op_sub_assign
id|this_count
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;(%x %x %x) &quot;
comma
id|CURRENT-&gt;bh
comma
id|CURRENT-&gt;nr_sectors
comma
id|this_count
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|CURRENT-&gt;nr_sectors
)paren
(brace
id|CURRENT-&gt;sector
op_add_assign
id|this_count
suffix:semicolon
id|CURRENT-&gt;errors
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|CURRENT-&gt;bh
)paren
(brace
(paren
r_char
op_star
)paren
id|CURRENT-&gt;buffer
op_add_assign
id|this_count
op_lshift
l_int|9
suffix:semicolon
)brace
r_else
(brace
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|end_request
c_func
(paren
l_int|1
)paren
suffix:semicolon
multiline_comment|/* All done */
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* We only come through here if we have an error of some kind */
r_if
c_cond
(paren
id|driver_byte
c_func
(paren
id|result
)paren
op_ne
l_int|0
)paren
(brace
id|bb
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|block
op_assign
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|sense_buffer
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
op_eq
l_int|0x70
)paren
(brace
r_if
c_cond
(paren
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
op_eq
id|UNIT_ATTENTION
)paren
(brace
multiline_comment|/* detected disc change.  set a bit and quietly refuse&t;*/
multiline_comment|/* further access.&t;&t;&t;&t;&t;*/
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|device-&gt;changed
op_assign
l_int|1
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_eq
id|ILLEGAL_REQUEST
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CD-ROM error: Drive reports ILLEGAL REQUEST.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|ten
)paren
(brace
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|ten
op_assign
l_int|0
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
id|result
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;CD-ROM error: Drive reports %d.&bslash;n&quot;
comma
id|sense_buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do next request */
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|sense_buffer
(braket
l_int|2
)braket
op_eq
id|NOT_READY
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;CDROM not ready.  Make sure you have a disc in the drive.&bslash;n&quot;
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Do next request */
r_return
suffix:semicolon
)brace
suffix:semicolon
)brace
multiline_comment|/* We only get this far if we have an error we have not recognized */
r_if
c_cond
(paren
id|result
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SCSI CD error : host %d id %d lun %d return code = %03x&bslash;n&quot;
comma
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|device-&gt;host_no
comma
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|device-&gt;id
comma
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)braket
dot
id|device-&gt;lun
comma
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status_byte
c_func
(paren
id|result
)paren
op_eq
id|CHECK_CONDITION
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;tSense class %x, sense error %x, extended sense %x&bslash;n&quot;
comma
id|sense_class
c_func
(paren
id|sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|sense_error
c_func
(paren
id|sense_buffer
(braket
l_int|0
)braket
)paren
comma
id|sense_buffer
(braket
l_int|2
)braket
op_amp
l_int|0xf
)paren
suffix:semicolon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|sr_open
r_static
r_int
id|sr_open
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
id|filp
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_mode
)paren
id|check_disk_change
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
)braket
dot
id|device-&gt;access_count
op_increment
)paren
(brace
id|sr_ioctl
c_func
(paren
id|inode
comma
l_int|NULL
comma
id|SCSI_IOCTL_DOORLOCK
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * do_sr_request() is the request handler function for the sr driver.  Its function in life &n; * is to take block device requests, and translate them to SCSI commands.&n; */
DECL|function|do_sr_request
r_void
id|do_sr_request
(paren
r_void
)paren
(brace
r_int
r_int
id|dev
comma
id|block
comma
id|realcount
suffix:semicolon
r_int
r_char
id|cmd
(braket
l_int|10
)braket
comma
op_star
id|buffer
comma
id|tries
suffix:semicolon
id|tries
op_assign
l_int|2
suffix:semicolon
id|repeat
suffix:colon
id|INIT_REQUEST
suffix:semicolon
id|dev
op_assign
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
suffix:semicolon
id|block
op_assign
id|CURRENT-&gt;sector
suffix:semicolon
id|bb
(braket
id|dev
)braket
dot
id|start
op_assign
id|block
op_mod
l_int|4
suffix:semicolon
id|block
op_assign
id|block
op_div
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|NR_SR
)paren
(brace
multiline_comment|/* printk(&quot;CD-ROM request error: invalid device.&bslash;n&quot;);&t;&t;&t;*/
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tries
op_assign
l_int|2
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|scsi_CDs
(braket
id|dev
)braket
dot
id|use
)paren
(brace
multiline_comment|/* printk(&quot;CD-ROM request error: device marked not in use.&bslash;n&quot;);&t;&t;*/
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tries
op_assign
l_int|2
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
id|scsi_CDs
(braket
id|dev
)braket
dot
id|device-&gt;changed
)paren
(brace
multiline_comment|/* &n; * quietly refuse to do anything to a changed disc until the changed bit has been reset&n; */
multiline_comment|/* printk(&quot;CD-ROM has been changed.  Prohibiting further I/O.&bslash;n&quot;);&t;*/
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|tries
op_assign
l_int|2
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|CURRENT-&gt;bh
)paren
id|this_count
op_assign
id|CURRENT-&gt;nr_sectors
suffix:semicolon
r_else
id|this_count
op_assign
(paren
id|CURRENT-&gt;bh-&gt;b_size
op_div
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bb
(braket
id|dev
)braket
dot
id|start
)paren
(brace
id|bb
(braket
id|dev
)braket
dot
id|use
op_assign
l_int|1
suffix:semicolon
id|this_count
op_assign
(paren
(paren
id|this_count
OG
l_int|4
op_minus
id|bb
(braket
id|dev
)braket
dot
id|start
)paren
ques
c_cond
(paren
l_int|4
op_minus
id|bb
(braket
id|dev
)braket
dot
id|start
)paren
suffix:colon
(paren
id|this_count
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bb
(braket
id|dev
)braket
dot
id|block
op_eq
id|block
)paren
(brace
id|rw_intr
c_func
(paren
id|SR_HOST
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|buffer
op_assign
id|bb
(braket
id|dev
)braket
dot
id|buffer
suffix:semicolon
id|bb
(braket
id|dev
)braket
dot
id|block
op_assign
id|block
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|this_count
OL
l_int|4
)paren
(brace
id|bb
(braket
id|dev
)braket
dot
id|use
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|bb
(braket
id|dev
)braket
dot
id|block
op_eq
id|block
)paren
(brace
id|rw_intr
c_func
(paren
id|SR_HOST
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|buffer
op_assign
id|bb
(braket
id|dev
)braket
dot
id|buffer
suffix:semicolon
id|bb
(braket
id|dev
)braket
dot
id|block
op_assign
id|block
suffix:semicolon
)brace
r_else
(brace
id|this_count
op_sub_assign
id|this_count
op_mod
l_int|4
suffix:semicolon
id|buffer
op_assign
id|CURRENT-&gt;buffer
suffix:semicolon
id|bb
(braket
id|dev
)braket
dot
id|use
op_assign
l_int|0
suffix:semicolon
)brace
id|realcount
op_assign
(paren
id|this_count
op_plus
l_int|3
)paren
op_div
l_int|4
suffix:semicolon
r_switch
c_cond
(paren
id|CURRENT-&gt;cmd
)paren
(brace
r_case
id|WRITE
suffix:colon
id|end_request
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|repeat
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ
suffix:colon
id|cmd
(braket
l_int|0
)braket
op_assign
id|READ_6
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
(paren
l_string|&quot;Unknown sr command %d&bslash;r&bslash;n&quot;
comma
id|CURRENT-&gt;cmd
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;&quot;
)paren
suffix:semicolon
)brace
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|SR_LUN
op_lshift
l_int|5
)paren
op_amp
l_int|0xe0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|realcount
OG
l_int|0xff
)paren
op_logical_or
(paren
id|block
OG
l_int|0x1fffff
)paren
)paren
op_logical_and
id|scsi_CDs
(braket
id|dev
)braket
dot
id|ten
)paren
(brace
r_if
c_cond
(paren
id|realcount
OG
l_int|0xffff
)paren
(brace
id|realcount
op_assign
l_int|0xffff
suffix:semicolon
id|this_count
op_assign
id|realcount
op_star
l_int|4
suffix:semicolon
)brace
id|cmd
(braket
l_int|0
)braket
op_add_assign
id|READ_10
op_minus
id|READ_6
suffix:semicolon
id|cmd
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|block
op_rshift
l_int|24
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|block
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|block
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_char
)paren
id|block
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|6
)braket
op_assign
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|cmd
(braket
l_int|7
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
id|realcount
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
(paren
r_int
r_char
)paren
id|realcount
op_amp
l_int|0xff
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|realcount
OG
l_int|0xff
)paren
(brace
id|realcount
op_assign
l_int|0xff
suffix:semicolon
id|this_count
op_assign
id|realcount
op_star
l_int|4
suffix:semicolon
)brace
id|cmd
(braket
l_int|1
)braket
op_or_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|block
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
suffix:semicolon
id|cmd
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
id|block
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
)paren
suffix:semicolon
id|cmd
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_char
)paren
id|block
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_char
)paren
id|realcount
suffix:semicolon
id|cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|scsi_do_cmd
(paren
id|SR_HOST
comma
id|SR_ID
comma
(paren
r_void
op_star
)paren
id|cmd
comma
id|buffer
comma
id|realcount
op_lshift
l_int|11
comma
id|rw_intr
comma
id|SR_TIMEOUT
comma
id|sense_buffer
comma
id|MAX_RETRIES
)paren
suffix:semicolon
)brace
DECL|function|sr_init
r_void
id|sr_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|NR_SR
suffix:semicolon
op_increment
id|i
)paren
(brace
id|scsi_CDs
(braket
id|i
)braket
dot
id|capacity
op_assign
l_int|0x1fffff
suffix:semicolon
id|scsi_CDs
(braket
id|i
)braket
dot
id|sector_size
op_assign
l_int|2048
suffix:semicolon
id|scsi_CDs
(braket
id|i
)braket
dot
id|use
op_assign
l_int|1
suffix:semicolon
id|scsi_CDs
(braket
id|i
)braket
dot
id|ten
op_assign
l_int|1
suffix:semicolon
id|scsi_CDs
(braket
id|i
)braket
dot
id|remap
op_assign
l_int|1
suffix:semicolon
id|sr_sizes
(braket
id|i
)braket
op_assign
id|scsi_CDs
(braket
id|i
)braket
dot
id|capacity
suffix:semicolon
id|bb
(braket
id|i
)braket
dot
id|block
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|blk_dev
(braket
id|MAJOR_NR
)braket
dot
id|request_fn
op_assign
id|DEVICE_REQUEST
suffix:semicolon
id|blk_size
(braket
id|MAJOR_NR
)braket
op_assign
id|sr_sizes
suffix:semicolon
id|blkdev_fops
(braket
id|MAJOR_NR
)braket
op_assign
op_amp
id|sr_fops
suffix:semicolon
)brace
macro_line|#endif
eof
