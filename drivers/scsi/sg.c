multiline_comment|/*&n;   History:&n;    Started: Aug 9 by Lawrence Foard (entropy@world.std.com), to allow user &n;     process control of SCSI devices.&n;    Development Sponsored by Killy Corp. NY NY&n;    &n;    Borrows code from st driver.&n;*/
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/mtio.h&gt;
macro_line|#include &lt;linux/ioctl.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &quot;../block/blk.h&quot;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;scsi_ioctl.h&quot;
macro_line|#include &quot;sg.h&quot;
r_static
r_void
id|sg_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_int
id|sg_attach
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_static
r_int
id|sg_detect
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
r_static
r_void
id|sg_detach
c_func
(paren
id|Scsi_Device
op_star
)paren
suffix:semicolon
DECL|variable|sg_template
r_struct
id|Scsi_Device_Template
id|sg_template
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_string|&quot;sg&quot;
comma
l_int|0xff
comma
id|SCSI_GENERIC_MAJOR
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|sg_detect
comma
id|sg_init
comma
l_int|NULL
comma
id|sg_attach
comma
id|sg_detach
)brace
suffix:semicolon
macro_line|#ifdef SG_BIG_BUFF
DECL|variable|big_buff
r_static
r_char
op_star
id|big_buff
suffix:semicolon
DECL|variable|big_wait
r_static
r_struct
id|wait_queue
op_star
id|big_wait
suffix:semicolon
multiline_comment|/* wait for buffer available */
DECL|variable|big_inuse
r_static
r_int
id|big_inuse
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
DECL|struct|scsi_generic
r_struct
id|scsi_generic
(brace
DECL|member|device
id|Scsi_Device
op_star
id|device
suffix:semicolon
DECL|member|users
r_int
id|users
suffix:semicolon
multiline_comment|/* how many people have it open? */
DECL|member|generic_wait
r_struct
id|wait_queue
op_star
id|generic_wait
suffix:semicolon
multiline_comment|/* wait for device to be available */
DECL|member|read_wait
r_struct
id|wait_queue
op_star
id|read_wait
suffix:semicolon
multiline_comment|/* wait for response */
DECL|member|write_wait
r_struct
id|wait_queue
op_star
id|write_wait
suffix:semicolon
multiline_comment|/* wait for free buffer */
DECL|member|timeout
r_int
id|timeout
suffix:semicolon
multiline_comment|/* current default value for device */
DECL|member|buff_len
r_int
id|buff_len
suffix:semicolon
multiline_comment|/* length of current buffer */
DECL|member|buff
r_char
op_star
id|buff
suffix:semicolon
multiline_comment|/* the buffer */
DECL|member|header
r_struct
id|sg_header
id|header
suffix:semicolon
multiline_comment|/* header of pending command */
DECL|member|exclude
r_char
id|exclude
suffix:semicolon
multiline_comment|/* opened for exclusive access */
DECL|member|pending
r_char
id|pending
suffix:semicolon
multiline_comment|/* don&squot;t accept writes now */
DECL|member|complete
r_char
id|complete
suffix:semicolon
multiline_comment|/* command complete allow a read */
)brace
suffix:semicolon
DECL|variable|scsi_generics
r_static
r_struct
id|scsi_generic
op_star
id|scsi_generics
op_assign
l_int|NULL
suffix:semicolon
r_static
r_void
id|sg_free
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|size
)paren
suffix:semicolon
DECL|function|sg_ioctl
r_static
r_int
id|sg_ioctl
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
id|cmd_in
comma
r_int
r_int
id|arg
)paren
(brace
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
OL
l_int|0
)paren
op_logical_or
(paren
id|dev
op_ge
id|sg_template.dev_max
)paren
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_switch
c_cond
(paren
id|cmd_in
)paren
(brace
r_case
id|SG_SET_TIMEOUT
suffix:colon
id|scsi_generics
(braket
id|dev
)braket
dot
id|timeout
op_assign
id|get_fs_long
c_func
(paren
(paren
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
id|SG_GET_TIMEOUT
suffix:colon
r_return
id|scsi_generics
(braket
id|dev
)braket
dot
id|timeout
suffix:semicolon
r_default
suffix:colon
r_return
id|scsi_ioctl
c_func
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|device
comma
id|cmd_in
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
DECL|function|sg_open
r_static
r_int
id|sg_open
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
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|flags
op_assign
id|filp-&gt;f_flags
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ge
id|sg_template.dev_max
op_logical_or
op_logical_neg
id|scsi_generics
(braket
id|dev
)braket
dot
id|device
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|O_RDWR
op_ne
(paren
id|flags
op_amp
id|O_ACCMODE
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|O_EXCL
)paren
(brace
r_while
c_loop
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|users
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|scsi_generics
(braket
id|dev
)braket
dot
id|generic_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|scsi_generics
(braket
id|dev
)braket
dot
id|exclude
op_assign
l_int|1
suffix:semicolon
)brace
r_else
r_while
c_loop
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|exclude
)paren
(brace
r_if
c_cond
(paren
id|flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|scsi_generics
(braket
id|dev
)braket
dot
id|generic_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|scsi_generics
(braket
id|dev
)braket
dot
id|users
op_logical_and
id|scsi_generics
(braket
id|dev
)braket
dot
id|pending
op_logical_and
id|scsi_generics
(braket
id|dev
)braket
dot
id|complete
)paren
(brace
r_if
c_cond
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|buff
op_ne
l_int|NULL
)paren
id|sg_free
c_func
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|buff
comma
id|scsi_generics
(braket
id|dev
)braket
dot
id|buff_len
)paren
suffix:semicolon
id|scsi_generics
(braket
id|dev
)braket
dot
id|buff
op_assign
l_int|NULL
suffix:semicolon
id|scsi_generics
(braket
id|dev
)braket
dot
id|pending
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|scsi_generics
(braket
id|dev
)braket
dot
id|users
)paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|timeout
op_assign
id|SG_DEFAULT_TIMEOUT
suffix:semicolon
r_if
c_cond
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|device-&gt;host-&gt;hostt-&gt;usage_count
)paren
(paren
op_star
id|scsi_generics
(braket
id|dev
)braket
dot
id|device-&gt;host-&gt;hostt-&gt;usage_count
)paren
op_increment
suffix:semicolon
id|scsi_generics
(braket
id|dev
)braket
dot
id|users
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sg_close
r_static
r_void
id|sg_close
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
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|scsi_generics
(braket
id|dev
)braket
dot
id|users
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|scsi_generics
(braket
id|dev
)braket
dot
id|device-&gt;host-&gt;hostt-&gt;usage_count
)paren
(paren
op_star
id|scsi_generics
(braket
id|dev
)braket
dot
id|device-&gt;host-&gt;hostt-&gt;usage_count
)paren
op_decrement
suffix:semicolon
id|scsi_generics
(braket
id|dev
)braket
dot
id|exclude
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|scsi_generics
(braket
id|dev
)braket
dot
id|generic_wait
)paren
suffix:semicolon
)brace
DECL|function|sg_malloc
r_static
r_char
op_star
id|sg_malloc
c_func
(paren
r_int
id|size
)paren
(brace
r_if
c_cond
(paren
id|size
op_le
l_int|4096
)paren
r_return
(paren
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
id|size
)paren
suffix:semicolon
macro_line|#ifdef SG_BIG_BUFF
r_if
c_cond
(paren
id|size
OL
id|SG_BIG_BUFF
)paren
(brace
r_while
c_loop
(paren
id|big_inuse
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|big_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
id|big_inuse
op_assign
l_int|1
suffix:semicolon
r_return
id|big_buff
suffix:semicolon
)brace
macro_line|#endif   
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|sg_free
r_static
r_void
id|sg_free
c_func
(paren
r_char
op_star
id|buff
comma
r_int
id|size
)paren
(brace
macro_line|#ifdef SG_BIG_BUFF
r_if
c_cond
(paren
id|buff
op_eq
id|big_buff
)paren
(brace
id|big_inuse
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|big_wait
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|scsi_free
c_func
(paren
id|buff
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|sg_read
r_static
r_int
id|sg_read
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_struct
id|scsi_generic
op_star
id|device
op_assign
op_amp
id|scsi_generics
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|buf
comma
id|count
)paren
)paren
)paren
r_return
id|i
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|device-&gt;pending
op_logical_or
op_logical_neg
id|device-&gt;complete
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EWOULDBLOCK
suffix:semicolon
id|interruptible_sleep_on
c_func
(paren
op_amp
id|device-&gt;read_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|device-&gt;header.pack_len
op_assign
id|device-&gt;header.reply_len
suffix:semicolon
id|device-&gt;header.result
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
op_ge
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
(brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
op_amp
id|device-&gt;header
comma
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
suffix:semicolon
id|buf
op_add_assign
r_sizeof
(paren
r_struct
id|sg_header
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|device-&gt;header.pack_len
)paren
id|count
op_assign
id|device-&gt;header.pack_len
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
(brace
id|memcpy_tofs
c_func
(paren
id|buf
comma
id|device-&gt;buff
comma
id|count
op_minus
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
suffix:semicolon
)brace
)brace
r_else
id|count
op_assign
l_int|0
suffix:semicolon
id|sg_free
c_func
(paren
id|device-&gt;buff
comma
id|device-&gt;buff_len
)paren
suffix:semicolon
id|device-&gt;buff
op_assign
l_int|NULL
suffix:semicolon
id|device-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|device-&gt;write_wait
)paren
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
DECL|function|sg_command_done
r_static
r_void
id|sg_command_done
c_func
(paren
id|Scsi_Cmnd
op_star
id|SCpnt
)paren
(brace
r_int
id|dev
op_assign
id|SCpnt-&gt;request.dev
suffix:semicolon
r_struct
id|scsi_generic
op_star
id|device
op_assign
op_amp
id|scsi_generics
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device-&gt;pending
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unexpected done for sg %d&bslash;n&quot;
comma
id|dev
)paren
suffix:semicolon
id|SCpnt-&gt;request.dev
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|device-&gt;header.sense_buffer
comma
id|SCpnt-&gt;sense_buffer
comma
r_sizeof
(paren
id|SCpnt-&gt;sense_buffer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|0
)braket
)paren
(brace
id|device-&gt;header.result
op_assign
id|EIO
suffix:semicolon
)brace
r_else
id|device-&gt;header.result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
id|device-&gt;complete
op_assign
l_int|1
suffix:semicolon
id|SCpnt-&gt;request.dev
op_assign
op_minus
l_int|1
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|scsi_generics
(braket
id|dev
)braket
dot
id|read_wait
)paren
suffix:semicolon
)brace
DECL|function|sg_write
r_static
r_int
id|sg_write
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
comma
r_char
op_star
id|buf
comma
r_int
id|count
)paren
(brace
r_int
id|dev
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
r_int
id|bsize
comma
id|size
comma
id|amt
comma
id|i
suffix:semicolon
r_int
r_char
id|opcode
suffix:semicolon
r_int
r_char
id|cmnd
(braket
id|MAX_COMMAND_SIZE
)braket
suffix:semicolon
r_struct
id|scsi_generic
op_star
id|device
op_assign
op_amp
id|scsi_generics
(braket
id|dev
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_assign
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|buf
comma
id|count
)paren
)paren
)paren
r_return
id|i
suffix:semicolon
multiline_comment|/*&n;   * The minimum scsi command length is 6 bytes.  If we get anything less than this,&n;   * it is clearly bogus.&n;   */
r_if
c_cond
(paren
id|count
OL
(paren
r_sizeof
(paren
r_struct
id|sg_header
)paren
op_plus
l_int|6
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
multiline_comment|/* make sure we can fit */
r_while
c_loop
(paren
id|device-&gt;pending
)paren
(brace
r_if
c_cond
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EWOULDBLOCK
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sg_write: sleeping on pending request&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif     
id|interruptible_sleep_on
c_func
(paren
op_amp
id|device-&gt;write_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;signal
op_amp
op_complement
id|current-&gt;blocked
)paren
r_return
op_minus
id|ERESTARTSYS
suffix:semicolon
)brace
id|device-&gt;pending
op_assign
l_int|1
suffix:semicolon
id|device-&gt;complete
op_assign
l_int|0
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
op_amp
id|device-&gt;header
comma
id|buf
comma
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
suffix:semicolon
multiline_comment|/* fix input size */
id|device-&gt;header.pack_len
op_assign
id|count
suffix:semicolon
id|buf
op_add_assign
r_sizeof
(paren
r_struct
id|sg_header
)paren
suffix:semicolon
id|bsize
op_assign
(paren
id|device-&gt;header.pack_len
OG
id|device-&gt;header.reply_len
)paren
ques
c_cond
id|device-&gt;header.pack_len
suffix:colon
id|device-&gt;header.reply_len
suffix:semicolon
id|bsize
op_sub_assign
r_sizeof
(paren
r_struct
id|sg_header
)paren
suffix:semicolon
id|amt
op_assign
id|bsize
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bsize
)paren
id|bsize
op_increment
suffix:semicolon
id|bsize
op_assign
(paren
id|bsize
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
(paren
id|bsize
OL
l_int|0
)paren
op_logical_or
op_logical_neg
(paren
id|device-&gt;buff
op_assign
id|sg_malloc
c_func
(paren
id|device-&gt;buff_len
op_assign
id|bsize
)paren
)paren
)paren
(brace
id|device-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|device-&gt;write_wait
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;allocating device&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
(paren
id|SCpnt
op_assign
id|allocate_device
c_func
(paren
l_int|NULL
comma
id|device-&gt;device
comma
op_logical_neg
(paren
id|filp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
)paren
)paren
)paren
(brace
id|device-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|device-&gt;write_wait
)paren
suffix:semicolon
id|sg_free
c_func
(paren
id|device-&gt;buff
comma
id|device-&gt;buff_len
)paren
suffix:semicolon
id|device-&gt;buff
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EWOULDBLOCK
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;device allocated&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif    
multiline_comment|/* now issue command */
id|SCpnt-&gt;request.dev
op_assign
id|dev
suffix:semicolon
id|SCpnt-&gt;sense_buffer
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|opcode
op_assign
id|get_fs_byte
c_func
(paren
id|buf
)paren
suffix:semicolon
id|size
op_assign
id|COMMAND_SIZE
c_func
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|opcode
op_ge
l_int|0xc0
op_logical_and
id|device-&gt;header.twelve_byte
)paren
id|size
op_assign
l_int|12
suffix:semicolon
id|SCpnt-&gt;cmd_len
op_assign
id|size
suffix:semicolon
multiline_comment|/*&n;   * Verify that the user has actually passed enough bytes for this command.&n;   */
r_if
c_cond
(paren
id|count
OL
(paren
r_sizeof
(paren
r_struct
id|sg_header
)paren
op_plus
id|size
)paren
)paren
(brace
id|device-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|wake_up
c_func
(paren
op_amp
id|device-&gt;write_wait
)paren
suffix:semicolon
id|sg_free
c_func
(paren
id|device-&gt;buff
comma
id|device-&gt;buff_len
)paren
suffix:semicolon
id|device-&gt;buff
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|memcpy_fromfs
c_func
(paren
id|cmnd
comma
id|buf
comma
id|size
)paren
suffix:semicolon
id|buf
op_add_assign
id|size
suffix:semicolon
id|memcpy_fromfs
c_func
(paren
id|device-&gt;buff
comma
id|buf
comma
id|device-&gt;header.pack_len
op_minus
id|size
op_minus
r_sizeof
(paren
r_struct
id|sg_header
)paren
)paren
suffix:semicolon
id|cmnd
(braket
l_int|1
)braket
op_assign
(paren
id|cmnd
(braket
l_int|1
)braket
op_amp
l_int|0x1f
)paren
op_or
(paren
id|device-&gt;device-&gt;lun
op_lshift
l_int|5
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;do cmd&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
id|scsi_do_cmd
(paren
id|SCpnt
comma
(paren
r_void
op_star
)paren
id|cmnd
comma
(paren
r_void
op_star
)paren
id|device-&gt;buff
comma
id|amt
comma
id|sg_command_done
comma
id|device-&gt;timeout
comma
id|SG_DEFAULT_RETRIES
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;done cmd&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif               
r_return
id|count
suffix:semicolon
)brace
DECL|variable|sg_fops
r_static
r_struct
id|file_operations
id|sg_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
id|sg_read
comma
multiline_comment|/* read */
id|sg_write
comma
multiline_comment|/* write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select */
id|sg_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|sg_open
comma
multiline_comment|/* open */
id|sg_close
comma
multiline_comment|/* release */
l_int|NULL
multiline_comment|/* fsync */
)brace
suffix:semicolon
DECL|function|sg_detect
r_static
r_int
(def_block
id|sg_detect
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
op_increment
id|sg_template.dev_noticed
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)def_block
multiline_comment|/* Driver initialization */
DECL|function|sg_init
r_static
r_void
id|sg_init
c_func
(paren
)paren
(brace
r_static
r_int
id|sg_registered
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|sg_template.dev_noticed
op_eq
l_int|0
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sg_registered
)paren
(brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|SCSI_GENERIC_MAJOR
comma
l_string|&quot;sg&quot;
comma
op_amp
id|sg_fops
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Unable to get major %d for generic SCSI device&bslash;n&quot;
comma
id|SCSI_GENERIC_MAJOR
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sg_registered
op_increment
suffix:semicolon
)brace
multiline_comment|/* If we have already been through here, return */
r_if
c_cond
(paren
id|scsi_generics
)paren
(brace
r_return
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sg: Init generic device.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef SG_BIG_BUFF
id|big_buff
op_assign
(paren
r_char
op_star
)paren
id|scsi_init_malloc
c_func
(paren
id|SG_BIG_BUFF
comma
id|GFP_ATOMIC
op_or
id|GFP_DMA
)paren
suffix:semicolon
macro_line|#endif
id|scsi_generics
op_assign
(paren
r_struct
id|scsi_generic
op_star
)paren
id|scsi_init_malloc
c_func
(paren
(paren
id|sg_template.dev_noticed
op_plus
id|SG_EXTRA_DEVS
)paren
op_star
r_sizeof
(paren
r_struct
id|scsi_generic
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|memset
c_func
(paren
id|scsi_generics
comma
l_int|0
comma
(paren
id|sg_template.dev_noticed
op_plus
id|SG_EXTRA_DEVS
)paren
op_star
r_sizeof
(paren
r_struct
id|scsi_generic
)paren
)paren
suffix:semicolon
id|sg_template.dev_max
op_assign
id|sg_template.dev_noticed
op_plus
id|SG_EXTRA_DEVS
suffix:semicolon
)brace
DECL|function|sg_attach
r_static
r_int
id|sg_attach
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
r_struct
id|scsi_generic
op_star
id|gpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|sg_template.nr_dev
op_ge
id|sg_template.dev_max
)paren
(brace
id|SDp-&gt;attached
op_decrement
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|gpnt
op_assign
id|scsi_generics
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sg_template.dev_max
suffix:semicolon
id|i
op_increment
comma
id|gpnt
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|gpnt-&gt;device
)paren
(brace
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_ge
id|sg_template.dev_max
)paren
(brace
id|panic
(paren
l_string|&quot;scsi_devices corrupt (sg)&quot;
)paren
suffix:semicolon
)brace
id|scsi_generics
(braket
id|i
)braket
dot
id|device
op_assign
id|SDp
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|users
op_assign
l_int|0
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|generic_wait
op_assign
l_int|NULL
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|read_wait
op_assign
l_int|NULL
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|write_wait
op_assign
l_int|NULL
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|buff
op_assign
l_int|NULL
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|exclude
op_assign
l_int|0
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|pending
op_assign
l_int|0
suffix:semicolon
id|scsi_generics
(braket
id|i
)braket
dot
id|timeout
op_assign
id|SG_DEFAULT_TIMEOUT
suffix:semicolon
id|sg_template.nr_dev
op_increment
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
suffix:semicolon
DECL|function|sg_detach
r_static
r_void
id|sg_detach
c_func
(paren
id|Scsi_Device
op_star
id|SDp
)paren
(brace
r_struct
id|scsi_generic
op_star
id|gpnt
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|gpnt
op_assign
id|scsi_generics
comma
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|sg_template.dev_max
suffix:semicolon
id|i
op_increment
comma
id|gpnt
op_increment
)paren
r_if
c_cond
(paren
id|gpnt-&gt;device
op_eq
id|SDp
)paren
(brace
id|gpnt-&gt;device
op_assign
l_int|NULL
suffix:semicolon
id|SDp-&gt;attached
op_decrement
suffix:semicolon
id|sg_template.nr_dev
op_decrement
suffix:semicolon
r_return
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
