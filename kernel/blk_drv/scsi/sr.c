multiline_comment|/*&n; *      sr.c by David Giller&n; *&n; *      adapted from:&n; *&t;sd.c Copyright (C) 1992 Drew Eckhardt &n; *&t;Linux scsi disk driver by&n; *&t;&t;Drew Eckhardt &n; *&n; *&t;&lt;drew@colorado.edu&gt;&n; *&n; *       Modified by Eric Youngdale eric@tantalus.nrl.navy.mil to&n; *       add scatter-gather, multiple outstanding request, and other&n; *       enhancements.&n; */
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|MAJOR_NR
mdefine_line|#define MAJOR_NR 11
macro_line|#include &quot;../blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;sr.h&quot;
macro_line|#include &quot;scsi_ioctl.h&quot;   /* For the door lock/unlock commands */
DECL|macro|MAX_RETRIES
mdefine_line|#define MAX_RETRIES 0
DECL|macro|SR_TIMEOUT
mdefine_line|#define SR_TIMEOUT 250
DECL|variable|NR_SR
r_int
id|NR_SR
op_assign
l_int|0
suffix:semicolon
DECL|variable|MAX_SR
r_int
id|MAX_SR
op_assign
l_int|0
suffix:semicolon
DECL|variable|scsi_CDs
id|Scsi_CD
op_star
id|scsi_CDs
suffix:semicolon
DECL|variable|sr_sizes
r_static
r_int
op_star
id|sr_sizes
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
r_void
id|requeue_sr_request
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
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
multiline_comment|/*&n; * rw_intr is the interrupt routine for the device driver.  It will be notified on the &n; * end of a SCSI read / write, and will take on of several actions based on success or failure.&n; */
DECL|function|rw_intr
r_static
r_void
id|rw_intr
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
r_int
id|this_count
op_assign
id|SCpnt-&gt;this_count
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sr.c done: %x %x&bslash;n&quot;
comma
id|result
comma
id|SCpnt-&gt;request.bh-&gt;b_data
)paren
suffix:semicolon
macro_line|#endif
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
id|SCpnt-&gt;use_sg
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;buffer
op_ne
id|SCpnt-&gt;request.buffer
)paren
(brace
r_int
id|offset
suffix:semicolon
id|offset
op_assign
(paren
id|SCpnt-&gt;request.sector
op_mod
l_int|4
)paren
op_lshift
l_int|9
suffix:semicolon
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|SCpnt-&gt;request.buffer
comma
id|SCpnt-&gt;buffer
op_plus
id|offset
comma
id|this_count
op_lshift
l_int|9
)paren
suffix:semicolon
multiline_comment|/* Even though we are not using scatter-gather, we look&n;&t;&t;&t;   ahead and see if there is a linked request for the&n;&t;&t;&t;   other half of this buffer.  If there is, then satisfy&n;&t;&t;&t;   it. */
r_if
c_cond
(paren
(paren
id|offset
op_eq
l_int|0
)paren
op_logical_and
id|this_count
op_eq
l_int|2
op_logical_and
id|SCpnt-&gt;request.nr_sectors
OG
id|this_count
op_logical_and
id|SCpnt-&gt;request.bh
op_logical_and
id|SCpnt-&gt;request.bh-&gt;b_reqnext
op_logical_and
id|SCpnt-&gt;request.bh-&gt;b_reqnext-&gt;b_size
op_eq
l_int|1024
)paren
(brace
id|memcpy
c_func
(paren
(paren
r_char
op_star
)paren
id|SCpnt-&gt;request.bh-&gt;b_reqnext-&gt;b_data
comma
id|SCpnt-&gt;buffer
op_plus
l_int|1024
comma
l_int|1024
)paren
suffix:semicolon
id|this_count
op_add_assign
l_int|2
suffix:semicolon
)brace
suffix:semicolon
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
l_int|2048
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sgpnt
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;buffer
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
id|SCpnt-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
)paren
(brace
r_if
c_cond
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
op_ne
id|sgpnt
(braket
id|i
)braket
dot
id|address
)paren
(brace
id|memcpy
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
)brace
suffix:semicolon
id|scsi_free
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;sglist_len
)paren
suffix:semicolon
multiline_comment|/* Free list of scatter-gather pointers */
r_if
c_cond
(paren
id|SCpnt-&gt;request.sector
op_mod
l_int|4
)paren
(brace
id|this_count
op_sub_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* See   if there is a padding record at the end that needs to be removed */
r_if
c_cond
(paren
id|this_count
OG
id|SCpnt-&gt;request.nr_sectors
)paren
(brace
id|this_count
op_sub_assign
l_int|2
suffix:semicolon
)brace
)brace
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;(%x %x %x) &quot;
comma
id|SCpnt-&gt;request.bh
comma
id|SCpnt-&gt;request.nr_sectors
comma
id|this_count
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|SCpnt-&gt;request.nr_sectors
OG
id|this_count
)paren
(brace
id|SCpnt-&gt;request.errors
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCpnt-&gt;request.bh
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;sr.c: linked page request. (%x %x)&quot;
comma
id|SCpnt-&gt;request.sector
comma
id|this_count
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Aiiiiiiiiiiiieeeeeeeee&quot;
)paren
suffix:semicolon
)brace
)brace
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|1
comma
id|this_count
)paren
suffix:semicolon
multiline_comment|/* All done */
id|requeue_sr_request
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Normal completion */
multiline_comment|/* We only come through here if we have an error of some kind */
multiline_comment|/* Free up any indirection buffers we allocated for DMA purposes. */
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
)paren
(brace
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
id|sgpnt
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|SCpnt-&gt;buffer
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
id|SCpnt-&gt;use_sg
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|alt_address
)paren
(brace
id|scsi_free
c_func
(paren
id|sgpnt
(braket
id|i
)braket
dot
id|address
comma
id|sgpnt
(braket
id|i
)braket
dot
id|length
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;sglist_len
)paren
suffix:semicolon
multiline_comment|/* Free list of scatter-gather pointers */
)brace
r_else
(brace
r_if
c_cond
(paren
id|SCpnt-&gt;buffer
op_ne
id|SCpnt-&gt;request.buffer
)paren
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;bufflen
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
id|result
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
(paren
id|SCpnt-&gt;sense_buffer
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
id|SCpnt-&gt;sense_buffer
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
id|SCpnt-&gt;request.dev
)paren
)braket
dot
id|device-&gt;changed
op_assign
l_int|1
suffix:semicolon
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|requeue_sr_request
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|SCpnt-&gt;sense_buffer
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
id|SCpnt-&gt;request.dev
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
id|SCpnt-&gt;request.dev
)paren
)braket
dot
id|ten
op_assign
l_int|0
suffix:semicolon
id|requeue_sr_request
c_func
(paren
id|SCpnt
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
id|SCpnt-&gt;sense_buffer
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|requeue_sr_request
c_func
(paren
id|SCpnt
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
id|SCpnt-&gt;sense_buffer
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
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|this_count
)paren
suffix:semicolon
id|requeue_sr_request
c_func
(paren
id|SCpnt
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
id|SCpnt-&gt;request.dev
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
id|SCpnt-&gt;request.dev
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
id|SCpnt-&gt;request.dev
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
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.current_nr_sectors
)paren
suffix:semicolon
id|requeue_sr_request
c_func
(paren
id|SCpnt
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
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
op_ge
id|NR_SR
op_logical_or
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
id|device
)paren
(brace
r_return
op_minus
id|EACCES
suffix:semicolon
)brace
multiline_comment|/* No such device */
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
r_static
r_void
id|do_sr_request
(paren
r_void
)paren
(brace
id|Scsi_Cmnd
op_star
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|request
op_star
id|req
op_assign
l_int|NULL
suffix:semicolon
r_while
c_loop
(paren
l_int|1
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|CURRENT
op_ne
l_int|NULL
op_logical_and
id|CURRENT-&gt;dev
op_eq
op_minus
l_int|1
)paren
r_return
suffix:semicolon
id|INIT_REQUEST
suffix:semicolon
id|SCpnt
op_assign
id|allocate_device
c_func
(paren
op_amp
id|CURRENT
comma
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|MINOR
c_func
(paren
id|CURRENT-&gt;dev
)paren
)paren
)braket
dot
id|device-&gt;index
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* This is a performance enhancement.  We dig down into the request list and&n;   try and find a queueable request (i.e. device not busy, and host able to&n;   accept another command.  If we find one, then we queue it. This can&n;   make a big difference on systems with more than one disk drive.  We want&n;   to have the interrupts off when monkeying with the request list, because&n;   otherwise the kernel might try and slip in a request inbetween somewhere. */
r_if
c_cond
(paren
op_logical_neg
id|SCpnt
op_logical_and
id|NR_SR
OG
l_int|1
)paren
(brace
r_struct
id|request
op_star
id|req1
suffix:semicolon
id|req1
op_assign
l_int|NULL
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|req
op_assign
id|CURRENT
suffix:semicolon
r_while
c_loop
(paren
id|req
)paren
(brace
id|SCpnt
op_assign
id|request_queueable
c_func
(paren
id|req
comma
id|scsi_CDs
(braket
id|DEVICE_NR
c_func
(paren
id|MINOR
c_func
(paren
id|req-&gt;dev
)paren
)paren
)braket
dot
id|device-&gt;index
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt
)paren
(brace
r_break
suffix:semicolon
)brace
id|req1
op_assign
id|req
suffix:semicolon
id|req
op_assign
id|req-&gt;next
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt
)paren
(brace
r_if
c_cond
(paren
id|req
op_eq
id|CURRENT
)paren
id|CURRENT
op_assign
id|CURRENT-&gt;next
suffix:semicolon
r_else
id|req1-&gt;next
op_assign
id|req-&gt;next
suffix:semicolon
)brace
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|SCpnt
)paren
r_return
suffix:semicolon
multiline_comment|/* Could not find anything to do */
id|wake_up
c_func
(paren
op_amp
id|wait_for_request
)paren
suffix:semicolon
multiline_comment|/* Queue command */
id|requeue_sr_request
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* While */
)brace
DECL|function|requeue_sr_request
r_void
id|requeue_sr_request
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
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
r_int
id|this_count
comma
id|start
comma
id|end_rec
suffix:semicolon
id|tries
op_assign
l_int|2
suffix:semicolon
id|repeat
suffix:colon
r_if
c_cond
(paren
id|SCpnt-&gt;request.dev
op_le
l_int|0
)paren
(brace
r_return
id|do_sr_request
c_func
(paren
)paren
suffix:semicolon
)brace
id|dev
op_assign
id|MINOR
c_func
(paren
id|SCpnt-&gt;request.dev
)paren
suffix:semicolon
id|block
op_assign
id|SCpnt-&gt;request.sector
suffix:semicolon
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|this_count
op_assign
l_int|0
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
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.nr_sectors
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
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.nr_sectors
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
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.nr_sectors
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
r_switch
c_cond
(paren
id|SCpnt-&gt;request.cmd
)paren
(brace
r_case
id|WRITE
suffix:colon
id|end_scsi_request
c_func
(paren
id|SCpnt
comma
l_int|0
comma
id|SCpnt-&gt;request.nr_sectors
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
id|SCpnt-&gt;request.cmd
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
id|SCpnt-&gt;lun
op_lshift
l_int|5
)paren
op_amp
l_int|0xe0
suffix:semicolon
multiline_comment|/*&n;           Now do the grungy work of figuring out which sectors we need, and&n;&t;   where in memory we are going to put them.&n;&n;&t;   The variables we need are:&n;&n;&t;   this_count= number of 512 byte sectors being read &n;&t;   block     = starting cdrom sector to read.&n;&t;   realcount = # of cdrom sectors to read&n;&n;&t;   The major difference between a scsi disk and a scsi cdrom&n;is that we will always use scatter-gather if we can, because we can&n;work around the fact that the buffer cache has a block size of 1024,&n;and we have 2048 byte sectors.  This code should work for buffers that&n;are any multiple of 512 bytes long.  */
id|SCpnt-&gt;use_sg
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|scsi_hosts
(braket
id|SCpnt-&gt;host
)braket
dot
id|sg_tablesize
OG
l_int|0
op_logical_and
(paren
op_logical_neg
id|need_isa_buffer
op_logical_or
id|dma_free_sectors
op_ge
l_int|10
)paren
)paren
(brace
r_struct
id|buffer_head
op_star
id|bh
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sgpnt
suffix:semicolon
r_int
id|count
comma
id|this_count_max
suffix:semicolon
id|bh
op_assign
id|SCpnt-&gt;request.bh
suffix:semicolon
id|this_count
op_assign
l_int|0
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|this_count_max
op_assign
(paren
id|scsi_CDs
(braket
id|dev
)braket
dot
id|ten
ques
c_cond
l_int|0xffff
suffix:colon
l_int|0xff
)paren
op_lshift
l_int|4
suffix:semicolon
multiline_comment|/* Calculate how many links we can use.  First see if we need&n;&t;   a padding record at the start */
id|this_count
op_assign
id|SCpnt-&gt;request.sector
op_mod
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|this_count
)paren
(brace
id|count
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|bh
op_logical_and
id|count
OL
id|scsi_hosts
(braket
id|SCpnt-&gt;host
)braket
dot
id|sg_tablesize
)paren
(brace
r_if
c_cond
(paren
(paren
id|this_count
op_plus
(paren
id|bh-&gt;b_size
op_rshift
l_int|9
)paren
)paren
OG
id|this_count_max
)paren
r_break
suffix:semicolon
id|this_count
op_add_assign
(paren
id|bh-&gt;b_size
op_rshift
l_int|9
)paren
suffix:semicolon
id|count
op_increment
suffix:semicolon
id|bh
op_assign
id|bh-&gt;b_reqnext
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Fix up in case of an odd record at the end */
id|end_rec
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|this_count
op_mod
l_int|4
)paren
(brace
r_if
c_cond
(paren
id|count
OL
id|scsi_hosts
(braket
id|SCpnt-&gt;host
)braket
dot
id|sg_tablesize
)paren
(brace
id|count
op_increment
suffix:semicolon
id|end_rec
op_assign
(paren
l_int|4
op_minus
(paren
id|this_count
op_mod
l_int|4
)paren
)paren
op_lshift
l_int|9
suffix:semicolon
id|this_count
op_add_assign
l_int|4
op_minus
(paren
id|this_count
op_mod
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
id|count
op_decrement
suffix:semicolon
id|this_count
op_sub_assign
(paren
id|this_count
op_mod
l_int|4
)paren
suffix:semicolon
)brace
suffix:semicolon
)brace
suffix:semicolon
id|SCpnt-&gt;use_sg
op_assign
id|count
suffix:semicolon
multiline_comment|/* Number of chains */
id|count
op_assign
l_int|512
suffix:semicolon
multiline_comment|/* scsi_malloc can only allocate in chunks of 512 bytes*/
r_while
c_loop
(paren
id|count
OL
(paren
id|SCpnt-&gt;use_sg
op_star
r_sizeof
(paren
r_struct
id|scatterlist
)paren
)paren
)paren
(brace
id|count
op_assign
id|count
op_lshift
l_int|1
suffix:semicolon
)brace
id|SCpnt-&gt;sglist_len
op_assign
id|count
suffix:semicolon
id|sgpnt
op_assign
(paren
r_struct
id|scatterlist
op_star
)paren
id|scsi_malloc
c_func
(paren
id|count
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgpnt
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Warning - running *really* short on DMA buffers&bslash;n&quot;
)paren
suffix:semicolon
id|SCpnt-&gt;use_sg
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* No memory left - bail out */
)brace
r_else
(brace
id|buffer
op_assign
(paren
r_char
op_star
)paren
id|sgpnt
suffix:semicolon
id|count
op_assign
l_int|0
suffix:semicolon
id|bh
op_assign
id|SCpnt-&gt;request.bh
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;request.sector
op_mod
l_int|4
)paren
(brace
id|sgpnt
(braket
id|count
)braket
dot
id|length
op_assign
(paren
id|SCpnt-&gt;request.sector
op_mod
l_int|4
)paren
op_lshift
l_int|9
suffix:semicolon
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_assign
id|scsi_malloc
c_func
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgpnt
(braket
id|count
)braket
dot
id|address
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SCSI DMA pool exhausted.&quot;
)paren
suffix:semicolon
)brace
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
op_assign
id|sgpnt
(braket
id|count
)braket
dot
id|address
suffix:semicolon
multiline_comment|/* Flag to delete&n;&t;&t;&t;&t;&t;&t;&t;&t;  if needed */
id|count
op_increment
suffix:semicolon
)brace
suffix:semicolon
r_for
c_loop
(paren
id|bh
op_assign
id|SCpnt-&gt;request.bh
suffix:semicolon
id|count
OL
id|SCpnt-&gt;use_sg
suffix:semicolon
id|count
op_increment
comma
id|bh
op_assign
id|bh-&gt;b_reqnext
)paren
(brace
r_if
c_cond
(paren
id|bh
)paren
(brace
multiline_comment|/* Need a placeholder at the end of the record? */
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_assign
id|bh-&gt;b_data
suffix:semicolon
id|sgpnt
(braket
id|count
)braket
dot
id|length
op_assign
id|bh-&gt;b_size
suffix:semicolon
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_assign
id|scsi_malloc
c_func
(paren
id|end_rec
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sgpnt
(braket
id|count
)braket
dot
id|address
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;SCSI DMA pool exhausted.&quot;
)paren
suffix:semicolon
)brace
id|sgpnt
(braket
id|count
)braket
dot
id|length
op_assign
id|end_rec
suffix:semicolon
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
op_assign
id|sgpnt
(braket
id|count
)braket
dot
id|address
suffix:semicolon
r_if
c_cond
(paren
id|count
op_plus
l_int|1
op_ne
id|SCpnt-&gt;use_sg
)paren
id|panic
c_func
(paren
l_string|&quot;Bad sr request list&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|sgpnt
(braket
id|count
)braket
dot
id|address
)paren
op_plus
id|sgpnt
(braket
id|count
)braket
dot
id|length
OG
id|ISA_DMA_THRESHOLD
op_amp
(paren
id|scsi_hosts
(braket
id|SCpnt-&gt;host
)braket
dot
id|unchecked_isa_dma
)paren
)paren
(brace
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
op_assign
id|sgpnt
(braket
id|count
)braket
dot
id|address
suffix:semicolon
multiline_comment|/* We try and avoid exhausting the DMA pool, since it is easier&n;&t;&t;   to control usage here.  In other places we might have a more&n;&t;&t;   pressing need, and we would be screwed if we ran out */
r_if
c_cond
(paren
id|dma_free_sectors
OL
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|length
op_rshift
l_int|9
)paren
op_plus
l_int|5
)paren
(brace
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_assign
id|scsi_malloc
c_func
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|length
)paren
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* If we start running low on DMA buffers, we abort the scatter-gather&n;   operation, and free all of the memory we have allocated.  We want to&n;   ensure that all scsi operations are able to do at least a non-scatter/gather&n;   operation */
r_if
c_cond
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|address
op_eq
l_int|NULL
)paren
(brace
multiline_comment|/* Out of dma memory */
id|printk
c_func
(paren
l_string|&quot;Warning: Running low on SCSI DMA buffers&quot;
)paren
suffix:semicolon
multiline_comment|/* Try switching back to a non scatter-gather operation. */
r_while
c_loop
(paren
op_decrement
id|count
)paren
(brace
r_if
c_cond
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
)paren
(brace
id|scsi_free
c_func
(paren
id|sgpnt
(braket
id|count
)braket
dot
id|address
comma
id|sgpnt
(braket
id|count
)braket
dot
id|length
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
id|SCpnt-&gt;use_sg
op_assign
l_int|0
suffix:semicolon
id|scsi_free
c_func
(paren
id|buffer
comma
id|SCpnt-&gt;sglist_len
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* if address == NULL */
)brace
suffix:semicolon
multiline_comment|/* if need DMA fixup */
)brace
suffix:semicolon
multiline_comment|/* for loop to fill list */
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;SG: %d %d %d %d %d *** &quot;
comma
id|SCpnt-&gt;use_sg
comma
id|SCpnt-&gt;request.sector
comma
id|this_count
comma
id|SCpnt-&gt;request.current_nr_sectors
comma
id|SCpnt-&gt;request.nr_sectors
)paren
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
l_int|0
suffix:semicolon
id|count
OL
id|SCpnt-&gt;use_sg
suffix:semicolon
id|count
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SGlist: %d %x %x %x&bslash;n&quot;
comma
id|count
comma
id|sgpnt
(braket
id|count
)braket
dot
id|address
comma
id|sgpnt
(braket
id|count
)braket
dot
id|alt_address
comma
id|sgpnt
(braket
id|count
)braket
dot
id|length
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
suffix:semicolon
multiline_comment|/* Able to allocate scatter-gather list */
)brace
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;use_sg
op_eq
l_int|0
)paren
(brace
multiline_comment|/* We cannot use scatter-gather.  Do this the old fashion way */
r_if
c_cond
(paren
op_logical_neg
id|SCpnt-&gt;request.bh
)paren
id|this_count
op_assign
id|SCpnt-&gt;request.nr_sectors
suffix:semicolon
r_else
id|this_count
op_assign
(paren
id|SCpnt-&gt;request.bh-&gt;b_size
op_rshift
l_int|9
)paren
suffix:semicolon
id|start
op_assign
id|block
op_mod
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|start
)paren
(brace
id|this_count
op_assign
(paren
(paren
id|this_count
OG
l_int|4
op_minus
id|start
)paren
ques
c_cond
(paren
l_int|4
op_minus
id|start
)paren
suffix:colon
(paren
id|this_count
)paren
)paren
suffix:semicolon
id|buffer
op_assign
id|scsi_malloc
c_func
(paren
l_int|2048
)paren
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
id|buffer
op_assign
id|scsi_malloc
c_func
(paren
l_int|2048
)paren
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
id|SCpnt-&gt;request.buffer
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|buffer
)paren
op_plus
(paren
id|this_count
op_lshift
l_int|9
)paren
OG
id|ISA_DMA_THRESHOLD
op_amp
(paren
id|scsi_hosts
(braket
id|SCpnt-&gt;host
)braket
dot
id|unchecked_isa_dma
)paren
)paren
id|buffer
op_assign
id|scsi_malloc
c_func
(paren
id|this_count
op_lshift
l_int|9
)paren
suffix:semicolon
)brace
)brace
suffix:semicolon
id|block
op_assign
id|block
op_rshift
l_int|2
suffix:semicolon
multiline_comment|/* These are the sectors that the cdrom uses */
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
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;ReadCD: %d %d %d&bslash;n&quot;
comma
id|block
comma
id|realcount
comma
id|buffer
)paren
suffix:semicolon
macro_line|#endif
id|SCpnt-&gt;this_count
op_assign
id|this_count
suffix:semicolon
id|scsi_do_cmd
(paren
id|SCpnt
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
id|MAX_RETRIES
)paren
suffix:semicolon
)brace
DECL|function|sr_init1
r_int
r_int
(def_block
id|sr_init1
c_func
(paren
r_int
r_int
id|mem_start
comma
r_int
r_int
id|mem_end
)paren
(brace
id|scsi_CDs
op_assign
(paren
id|Scsi_CD
op_star
)paren
id|mem_start
suffix:semicolon
id|mem_start
op_add_assign
id|MAX_SR
op_star
r_sizeof
(paren
id|Scsi_CD
)paren
suffix:semicolon
r_return
id|mem_start
suffix:semicolon
)brace
)def_block
suffix:semicolon
DECL|function|sr_attach
r_void
(def_block
id|sr_attach
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
id|scsi_CDs
(braket
id|NR_SR
op_increment
)braket
dot
id|device
op_assign
id|SDp
suffix:semicolon
r_if
c_cond
(paren
id|NR_SR
OG
id|MAX_SR
)paren
(brace
id|panic
(paren
l_string|&quot;scsi_devices corrupt (sr)&quot;
)paren
suffix:semicolon
)brace
)brace
)def_block
suffix:semicolon
DECL|function|sr_init
r_int
r_int
id|sr_init
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
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|MAX_SR
op_eq
l_int|0
)paren
(brace
r_return
id|memory_start
suffix:semicolon
)brace
id|sr_sizes
op_assign
(paren
r_int
op_star
)paren
id|memory_start
suffix:semicolon
id|memory_start
op_add_assign
id|MAX_SR
op_star
r_sizeof
(paren
r_int
)paren
suffix:semicolon
id|memset
c_func
(paren
id|sr_sizes
comma
l_int|0
comma
id|MAX_SR
op_star
r_sizeof
(paren
r_int
)paren
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
multiline_comment|/* If our host adapter is capable of scatter-gather, then we increase&n;&t;   the read-ahead to 8 blocks (16 sectors).  If not, we use&n;&t;   a two block (4 sector) read ahead. */
r_if
c_cond
(paren
id|scsi_hosts
(braket
id|scsi_CDs
(braket
l_int|0
)braket
dot
id|device-&gt;host_no
)braket
dot
id|sg_tablesize
)paren
(brace
id|read_ahead
(braket
id|MAJOR_NR
)braket
op_assign
l_int|16
suffix:semicolon
)brace
multiline_comment|/* 16 sector read-ahead */
r_else
id|read_ahead
(braket
id|MAJOR_NR
)braket
op_assign
l_int|4
suffix:semicolon
multiline_comment|/* 4 sector read-ahead */
id|blkdev_fops
(braket
id|MAJOR_NR
)braket
op_assign
op_amp
id|sr_fops
suffix:semicolon
r_return
id|memory_start
suffix:semicolon
)brace
eof
