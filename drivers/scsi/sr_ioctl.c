macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &lt;scsi/scsi_ioctl.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &quot;sr.h&quot;
macro_line|#if 0
mdefine_line|#define DEBUG
macro_line|#endif
multiline_comment|/* The sr_is_xa() seems to trigger firmware bugs with some drives :-(&n; * It is off by default and can be turned on with this module parameter */
DECL|variable|xa_test
r_static
r_int
id|xa_test
op_assign
l_int|0
suffix:semicolon
r_extern
r_void
id|get_sectorsize
c_func
(paren
r_int
)paren
suffix:semicolon
DECL|macro|IOCTL_RETRIES
mdefine_line|#define IOCTL_RETRIES 3
multiline_comment|/* The CDROM is fairly slow, so we need a little extra time */
multiline_comment|/* In fact, it is very slow if it has to spin up first */
DECL|macro|IOCTL_TIMEOUT
mdefine_line|#define IOCTL_TIMEOUT 30*HZ
DECL|function|sr_ioctl_done
r_static
r_void
id|sr_ioctl_done
c_func
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
id|req
op_assign
op_amp
id|SCpnt-&gt;request
suffix:semicolon
id|req-&gt;rq_status
op_assign
id|RQ_SCSI_DONE
suffix:semicolon
multiline_comment|/* Busy, but indicate request done */
r_if
c_cond
(paren
id|SCpnt-&gt;buffer
op_logical_and
id|req-&gt;buffer
op_logical_and
id|SCpnt-&gt;buffer
op_ne
id|req-&gt;buffer
)paren
(brace
id|memcpy
c_func
(paren
id|req-&gt;buffer
comma
id|SCpnt-&gt;buffer
comma
id|SCpnt-&gt;bufflen
)paren
suffix:semicolon
id|scsi_free
c_func
(paren
id|SCpnt-&gt;buffer
comma
(paren
id|SCpnt-&gt;bufflen
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|511
)paren
suffix:semicolon
id|SCpnt-&gt;buffer
op_assign
id|req-&gt;buffer
suffix:semicolon
)brace
r_if
c_cond
(paren
id|req-&gt;sem
op_ne
l_int|NULL
)paren
(brace
id|up
c_func
(paren
id|req-&gt;sem
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* We do our own retries because we want to know what the specific&n;   error code is.  Normally the UNIT_ATTENTION code will automatically&n;   clear after one error */
DECL|function|sr_do_ioctl
r_int
id|sr_do_ioctl
c_func
(paren
r_int
id|target
comma
r_int
r_char
op_star
id|sr_cmd
comma
r_void
op_star
id|buffer
comma
r_int
id|buflength
comma
r_int
id|quiet
)paren
(brace
id|Scsi_Cmnd
op_star
id|SCpnt
suffix:semicolon
id|Scsi_Device
op_star
id|SDev
suffix:semicolon
r_int
id|result
comma
id|err
op_assign
l_int|0
comma
id|retries
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|bounce_buffer
suffix:semicolon
id|SDev
op_assign
id|scsi_CDs
(braket
id|target
)braket
dot
id|device
suffix:semicolon
id|SCpnt
op_assign
id|scsi_allocate_device
c_func
(paren
id|scsi_CDs
(braket
id|target
)braket
dot
id|device
comma
l_int|1
comma
id|FALSE
)paren
suffix:semicolon
multiline_comment|/* use ISA DMA buffer if necessary */
id|SCpnt-&gt;request.buffer
op_assign
id|buffer
suffix:semicolon
r_if
c_cond
(paren
id|buffer
op_logical_and
id|SCpnt-&gt;host-&gt;unchecked_isa_dma
op_logical_and
(paren
id|virt_to_phys
c_func
(paren
id|buffer
)paren
op_plus
id|buflength
op_minus
l_int|1
OG
id|ISA_DMA_THRESHOLD
)paren
)paren
(brace
id|bounce_buffer
op_assign
(paren
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
(paren
id|buflength
op_plus
l_int|511
)paren
op_amp
op_complement
l_int|511
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bounce_buffer
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SCSI DMA pool exhausted.&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|bounce_buffer
comma
(paren
r_char
op_star
)paren
id|buffer
comma
id|buflength
)paren
suffix:semicolon
id|buffer
op_assign
id|bounce_buffer
suffix:semicolon
)brace
id|retry
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|scsi_block_when_processing_errors
c_func
(paren
id|SDev
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|scsi_wait_cmd
c_func
(paren
id|SCpnt
comma
(paren
r_void
op_star
)paren
id|sr_cmd
comma
(paren
r_void
op_star
)paren
id|buffer
comma
id|buflength
comma
id|sr_ioctl_done
comma
id|IOCTL_TIMEOUT
comma
id|IOCTL_RETRIES
)paren
suffix:semicolon
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
multiline_comment|/* Minimal error checking.  Ignore cases we know about, and report the rest. */
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
id|UNIT_ATTENTION
suffix:colon
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;changed
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr%d: disc change detected.&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_increment
OL
l_int|10
)paren
r_goto
id|retry
suffix:semicolon
id|err
op_assign
op_minus
id|ENOMEDIUM
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
id|SCpnt-&gt;sense_buffer
(braket
l_int|12
)braket
op_eq
l_int|0x04
op_logical_and
id|SCpnt-&gt;sense_buffer
(braket
l_int|13
)braket
op_eq
l_int|0x01
)paren
(brace
multiline_comment|/* sense: Logical unit is in process of becoming ready */
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr%d: CDROM not ready yet.&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_increment
OL
l_int|10
)paren
(brace
multiline_comment|/* sleep 2 sec and try again */
id|scsi_sleep
c_func
(paren
l_int|2
op_star
id|HZ
)paren
suffix:semicolon
r_goto
id|retry
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* 20 secs are enough? */
id|err
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;sr%d: CDROM not ready.  Make sure there is a disc in the drive.&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|print_sense
c_func
(paren
l_string|&quot;sr&quot;
comma
id|SCpnt
)paren
suffix:semicolon
macro_line|#endif
id|err
op_assign
op_minus
id|ENOMEDIUM
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ILLEGAL_REQUEST
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|quiet
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sr%d: CDROM (ioctl) reports ILLEGAL &quot;
l_string|&quot;REQUEST.&bslash;n&quot;
comma
id|target
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SCpnt-&gt;sense_buffer
(braket
l_int|12
)braket
op_eq
l_int|0x20
op_logical_and
id|SCpnt-&gt;sense_buffer
(braket
l_int|13
)braket
op_eq
l_int|0x00
)paren
(brace
multiline_comment|/* sense: Invalid command operation code */
id|err
op_assign
op_minus
id|EDRIVE_CANT_DO_THIS
suffix:semicolon
)brace
r_else
(brace
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|print_command
c_func
(paren
id|sr_cmd
)paren
suffix:semicolon
id|print_sense
c_func
(paren
l_string|&quot;sr&quot;
comma
id|SCpnt
)paren
suffix:semicolon
macro_line|#endif
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;sr%d: CDROM (ioctl) error, command: &quot;
comma
id|target
)paren
suffix:semicolon
id|print_command
c_func
(paren
id|sr_cmd
)paren
suffix:semicolon
id|print_sense
c_func
(paren
l_string|&quot;sr&quot;
comma
id|SCpnt
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
)brace
)brace
id|result
op_assign
id|SCpnt-&gt;result
suffix:semicolon
multiline_comment|/* Wake up a process waiting for device */
id|scsi_release_command
c_func
(paren
id|SCpnt
)paren
suffix:semicolon
id|SCpnt
op_assign
l_int|NULL
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* ---------------------------------------------------------------------- */
multiline_comment|/* interface to cdrom.c                                                   */
DECL|function|test_unit_ready
r_static
r_int
id|test_unit_ready
c_func
(paren
r_int
id|minor
)paren
(brace
id|u_char
id|sr_cmd
(braket
l_int|10
)braket
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_TEST_UNIT_READY
suffix:semicolon
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
id|sr_cmd
(braket
l_int|3
)braket
op_assign
id|sr_cmd
(braket
l_int|4
)braket
op_assign
id|sr_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|sr_cmd
comma
l_int|NULL
comma
l_int|255
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|sr_tray_move
r_int
id|sr_tray_move
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|pos
)paren
(brace
id|u_char
id|sr_cmd
(braket
l_int|10
)braket
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_START_STOP_UNIT
suffix:semicolon
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
id|sr_cmd
(braket
l_int|3
)braket
op_assign
id|sr_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|4
)braket
op_assign
(paren
id|pos
op_eq
l_int|0
)paren
ques
c_cond
l_int|0x03
multiline_comment|/* close */
suffix:colon
l_int|0x02
multiline_comment|/* eject */
suffix:semicolon
r_return
id|sr_do_ioctl
c_func
(paren
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
comma
id|sr_cmd
comma
l_int|NULL
comma
l_int|255
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sr_lock_door
r_int
id|sr_lock_door
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|lock
)paren
(brace
r_return
id|scsi_ioctl
c_func
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|device
comma
id|lock
ques
c_cond
id|SCSI_IOCTL_DOORLOCK
suffix:colon
id|SCSI_IOCTL_DOORUNLOCK
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|sr_drive_status
r_int
id|sr_drive_status
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|slot
)paren
(brace
r_if
c_cond
(paren
id|CDSL_CURRENT
op_ne
id|slot
)paren
(brace
multiline_comment|/* we have no changer support */
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
l_int|0
op_eq
id|test_unit_ready
c_func
(paren
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)paren
)paren
r_return
id|CDS_DISC_OK
suffix:semicolon
r_return
id|CDS_TRAY_OPEN
suffix:semicolon
)brace
DECL|function|sr_disk_status
r_int
id|sr_disk_status
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
(brace
r_struct
id|cdrom_tochdr
id|toc_h
suffix:semicolon
r_struct
id|cdrom_tocentry
id|toc_e
suffix:semicolon
r_int
id|i
comma
id|rc
comma
id|have_datatracks
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* look for data tracks */
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|rc
op_assign
id|sr_audio_ioctl
c_func
(paren
id|cdi
comma
id|CDROMREADTOCHDR
comma
op_amp
id|toc_h
)paren
)paren
)paren
r_return
(paren
id|rc
op_eq
op_minus
id|ENOMEDIUM
)paren
ques
c_cond
id|CDS_NO_DISC
suffix:colon
id|CDS_NO_INFO
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|toc_h.cdth_trk0
suffix:semicolon
id|i
op_le
id|toc_h.cdth_trk1
suffix:semicolon
id|i
op_increment
)paren
(brace
id|toc_e.cdte_track
op_assign
id|i
suffix:semicolon
id|toc_e.cdte_format
op_assign
id|CDROM_LBA
suffix:semicolon
r_if
c_cond
(paren
id|sr_audio_ioctl
c_func
(paren
id|cdi
comma
id|CDROMREADTOCENTRY
comma
op_amp
id|toc_e
)paren
)paren
r_return
id|CDS_NO_INFO
suffix:semicolon
r_if
c_cond
(paren
id|toc_e.cdte_ctrl
op_amp
id|CDROM_DATA_TRACK
)paren
(brace
id|have_datatracks
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|have_datatracks
)paren
r_return
id|CDS_AUDIO
suffix:semicolon
r_if
c_cond
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|xa_flag
)paren
r_return
id|CDS_XA_2_1
suffix:semicolon
r_else
r_return
id|CDS_DATA_1
suffix:semicolon
)brace
DECL|function|sr_get_last_session
r_int
id|sr_get_last_session
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_struct
id|cdrom_multisession
op_star
id|ms_info
)paren
(brace
id|ms_info-&gt;addr.lba
op_assign
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|ms_offset
suffix:semicolon
id|ms_info-&gt;xa_flag
op_assign
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|xa_flag
op_logical_or
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|ms_offset
OG
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sr_get_mcn
r_int
id|sr_get_mcn
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_struct
id|cdrom_mcn
op_star
id|mcn
)paren
(brace
id|u_char
id|sr_cmd
(braket
l_int|10
)braket
suffix:semicolon
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|result
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_READ_SUBCHANNEL
suffix:semicolon
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
l_int|0x40
suffix:semicolon
multiline_comment|/* I do want the subchannel info */
id|sr_cmd
(braket
l_int|3
)braket
op_assign
l_int|0x02
suffix:semicolon
multiline_comment|/* Give me medium catalog number info */
id|sr_cmd
(braket
l_int|4
)braket
op_assign
id|sr_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|8
)braket
op_assign
l_int|24
suffix:semicolon
id|sr_cmd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|sr_do_ioctl
c_func
(paren
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
comma
id|sr_cmd
comma
id|buffer
comma
l_int|24
comma
l_int|0
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|mcn-&gt;medium_catalog_number
comma
id|buffer
op_plus
l_int|9
comma
l_int|13
)paren
suffix:semicolon
id|mcn-&gt;medium_catalog_number
(braket
l_int|13
)braket
op_assign
l_int|0
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|sr_reset
r_int
id|sr_reset
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
(brace
id|invalidate_buffers
c_func
(paren
id|cdi-&gt;dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sr_select_speed
r_int
id|sr_select_speed
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|speed
)paren
(brace
id|u_char
id|sr_cmd
(braket
l_int|12
)braket
suffix:semicolon
r_if
c_cond
(paren
id|speed
op_eq
l_int|0
)paren
id|speed
op_assign
l_int|0xffff
suffix:semicolon
multiline_comment|/* set to max */
r_else
id|speed
op_mul_assign
l_int|177
suffix:semicolon
multiline_comment|/* Nx to kbyte/s */
id|memset
c_func
(paren
id|sr_cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_SET_SPEED
suffix:semicolon
multiline_comment|/* SET CD SPEED */
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
(paren
id|speed
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* MSB for speed (in kbytes/sec) */
id|sr_cmd
(braket
l_int|3
)braket
op_assign
id|speed
op_amp
l_int|0xff
suffix:semicolon
multiline_comment|/* LSB */
r_if
c_cond
(paren
id|sr_do_ioctl
c_func
(paren
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
comma
id|sr_cmd
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* ----------------------------------------------------------------------- */
multiline_comment|/* this is called by the generic cdrom driver. arg is a _kernel_ pointer,  */
multiline_comment|/* becauce the generic cdrom driver does the user access stuff for us.     */
multiline_comment|/* only cdromreadtochdr and cdromreadtocentry are left - for use with the  */
multiline_comment|/* sr_disk_status interface for the generic cdrom driver.                  */
DECL|function|sr_audio_ioctl
r_int
id|sr_audio_ioctl
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
r_int
id|cmd
comma
r_void
op_star
id|arg
)paren
(brace
id|u_char
id|sr_cmd
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|result
comma
id|target
op_assign
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
suffix:semicolon
r_int
r_char
id|buffer
(braket
l_int|32
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|CDROMREADTOCHDR
suffix:colon
(brace
r_struct
id|cdrom_tochdr
op_star
id|tochdr
op_assign
(paren
r_struct
id|cdrom_tochdr
op_star
)paren
id|arg
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_READ_TOC_PMA_ATIP
suffix:semicolon
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
id|sr_cmd
(braket
l_int|3
)braket
op_assign
id|sr_cmd
(braket
l_int|4
)braket
op_assign
id|sr_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|6
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* MSB of length (12) */
id|sr_cmd
(braket
l_int|8
)braket
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* LSB of length */
id|sr_cmd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|sr_do_ioctl
c_func
(paren
id|target
comma
id|sr_cmd
comma
id|buffer
comma
l_int|12
comma
l_int|1
)paren
suffix:semicolon
id|tochdr-&gt;cdth_trk0
op_assign
id|buffer
(braket
l_int|2
)braket
suffix:semicolon
id|tochdr-&gt;cdth_trk1
op_assign
id|buffer
(braket
l_int|3
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_case
id|CDROMREADTOCENTRY
suffix:colon
(brace
r_struct
id|cdrom_tocentry
op_star
id|tocentry
op_assign
(paren
r_struct
id|cdrom_tocentry
op_star
)paren
id|arg
suffix:semicolon
id|sr_cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_READ_TOC_PMA_ATIP
suffix:semicolon
id|sr_cmd
(braket
l_int|1
)braket
op_assign
(paren
(paren
id|scsi_CDs
(braket
id|target
)braket
dot
id|device-&gt;lun
)paren
op_lshift
l_int|5
)paren
op_or
(paren
id|tocentry-&gt;cdte_format
op_eq
id|CDROM_MSF
ques
c_cond
l_int|0x02
suffix:colon
l_int|0
)paren
suffix:semicolon
id|sr_cmd
(braket
l_int|2
)braket
op_assign
id|sr_cmd
(braket
l_int|3
)braket
op_assign
id|sr_cmd
(braket
l_int|4
)braket
op_assign
id|sr_cmd
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|sr_cmd
(braket
l_int|6
)braket
op_assign
id|tocentry-&gt;cdte_track
suffix:semicolon
id|sr_cmd
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* MSB of length (12)  */
id|sr_cmd
(braket
l_int|8
)braket
op_assign
l_int|12
suffix:semicolon
multiline_comment|/* LSB of length */
id|sr_cmd
(braket
l_int|9
)braket
op_assign
l_int|0
suffix:semicolon
id|result
op_assign
id|sr_do_ioctl
c_func
(paren
id|target
comma
id|sr_cmd
comma
id|buffer
comma
l_int|12
comma
l_int|0
)paren
suffix:semicolon
id|tocentry-&gt;cdte_ctrl
op_assign
id|buffer
(braket
l_int|5
)braket
op_amp
l_int|0xf
suffix:semicolon
id|tocentry-&gt;cdte_adr
op_assign
id|buffer
(braket
l_int|5
)braket
op_rshift
l_int|4
suffix:semicolon
id|tocentry-&gt;cdte_datamode
op_assign
(paren
id|tocentry-&gt;cdte_ctrl
op_amp
l_int|0x04
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|tocentry-&gt;cdte_format
op_eq
id|CDROM_MSF
)paren
(brace
id|tocentry-&gt;cdte_addr.msf.minute
op_assign
id|buffer
(braket
l_int|9
)braket
suffix:semicolon
id|tocentry-&gt;cdte_addr.msf.second
op_assign
id|buffer
(braket
l_int|10
)braket
suffix:semicolon
id|tocentry-&gt;cdte_addr.msf.frame
op_assign
id|buffer
(braket
l_int|11
)braket
suffix:semicolon
)brace
r_else
id|tocentry-&gt;cdte_addr.lba
op_assign
(paren
(paren
(paren
(paren
(paren
id|buffer
(braket
l_int|8
)braket
op_lshift
l_int|8
)paren
op_plus
id|buffer
(braket
l_int|9
)braket
)paren
op_lshift
l_int|8
)paren
op_plus
id|buffer
(braket
l_int|10
)braket
)paren
op_lshift
l_int|8
)paren
op_plus
id|buffer
(braket
l_int|11
)braket
suffix:semicolon
r_break
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#if 0
r_if
c_cond
(paren
id|result
)paren
id|printk
c_func
(paren
l_string|&quot;DEBUG: sr_audio: result for ioctl %x: %x&bslash;n&quot;
comma
id|cmd
comma
id|result
)paren
suffix:semicolon
macro_line|#endif
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/* -----------------------------------------------------------------------&n; * a function to read all sorts of funny cdrom sectors using the READ_CD&n; * scsi-3 mmc command&n; *&n; * lba:     linear block address&n; * format:  0 = data (anything)&n; *          1 = audio&n; *          2 = data (mode 1)&n; *          3 = data (mode 2)&n; *          4 = data (mode 2 form1)&n; *          5 = data (mode 2 form2)&n; * blksize: 2048 | 2336 | 2340 | 2352&n; */
DECL|function|sr_read_cd
r_int
id|sr_read_cd
c_func
(paren
r_int
id|minor
comma
r_int
r_char
op_star
id|dest
comma
r_int
id|lba
comma
r_int
id|format
comma
r_int
id|blksize
)paren
(brace
r_int
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sr%d: sr_read_cd lba=%d format=%d blksize=%d&bslash;n&quot;
comma
id|minor
comma
id|lba
comma
id|format
comma
id|blksize
)paren
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_READ_CD
suffix:semicolon
multiline_comment|/* READ_CD */
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|format
op_amp
l_int|7
)paren
op_lshift
l_int|2
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
id|lba
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
id|lba
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
id|lba
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
id|lba
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|1
suffix:semicolon
r_switch
c_cond
(paren
id|blksize
)paren
(brace
r_case
l_int|2336
suffix:colon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x58
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2340
suffix:colon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x78
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2352
suffix:colon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0xf8
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|cmd
(braket
l_int|9
)braket
op_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|dest
comma
id|blksize
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * read sectors with blocksizes other than 2048&n; */
DECL|function|sr_read_sector
r_int
id|sr_read_sector
c_func
(paren
r_int
id|minor
comma
r_int
id|lba
comma
r_int
id|blksize
comma
r_int
r_char
op_star
id|dest
)paren
(brace
r_int
r_char
id|cmd
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* the scsi-command */
r_int
id|rc
suffix:semicolon
multiline_comment|/* we try the READ CD command first... */
r_if
c_cond
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|readcd_known
)paren
(brace
id|rc
op_assign
id|sr_read_cd
c_func
(paren
id|minor
comma
id|dest
comma
id|lba
comma
l_int|0
comma
id|blksize
)paren
suffix:semicolon
r_if
c_cond
(paren
op_minus
id|EDRIVE_CANT_DO_THIS
op_ne
id|rc
)paren
r_return
id|rc
suffix:semicolon
id|scsi_CDs
(braket
id|minor
)braket
dot
id|readcd_known
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CDROM does&squot;nt support READ CD (0xbe) command&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* fall &amp; retry the other way */
)brace
multiline_comment|/* ... if this fails, we switch the blocksize using MODE SELECT */
r_if
c_cond
(paren
id|blksize
op_ne
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;sector_size
)paren
(brace
r_if
c_cond
(paren
l_int|0
op_ne
(paren
id|rc
op_assign
id|sr_set_blocklength
c_func
(paren
id|minor
comma
id|blksize
)paren
)paren
)paren
r_return
id|rc
suffix:semicolon
)brace
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sr%d: sr_read_sector lba=%d blksize=%d&bslash;n&quot;
comma
id|minor
comma
id|lba
comma
id|blksize
)paren
suffix:semicolon
macro_line|#endif
id|memset
c_func
(paren
id|cmd
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|cmd
(braket
l_int|0
)braket
op_assign
id|GPCMD_READ_10
suffix:semicolon
id|cmd
(braket
l_int|1
)braket
op_assign
(paren
id|scsi_CDs
(braket
id|minor
)braket
dot
id|device-&gt;lun
op_lshift
l_int|5
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
id|lba
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
id|lba
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
id|lba
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
id|lba
op_amp
l_int|0xff
suffix:semicolon
id|cmd
(braket
l_int|8
)braket
op_assign
l_int|1
suffix:semicolon
id|rc
op_assign
id|sr_do_ioctl
c_func
(paren
id|minor
comma
id|cmd
comma
id|dest
comma
id|blksize
comma
l_int|0
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/*&n; * read a sector in raw mode to check the sector format&n; * ret: 1 == mode2 (XA), 0 == mode1, &lt;0 == error &n; */
DECL|function|sr_is_xa
r_int
id|sr_is_xa
c_func
(paren
r_int
id|minor
)paren
(brace
r_int
r_char
op_star
id|raw_sector
suffix:semicolon
r_int
id|is_xa
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xa_test
)paren
r_return
l_int|0
suffix:semicolon
id|raw_sector
op_assign
(paren
r_int
r_char
op_star
)paren
id|scsi_malloc
c_func
(paren
l_int|2048
op_plus
l_int|512
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|raw_sector
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
l_int|0
op_eq
id|sr_read_sector
c_func
(paren
id|minor
comma
id|scsi_CDs
(braket
id|minor
)braket
dot
id|ms_offset
op_plus
l_int|16
comma
id|CD_FRAMESIZE_RAW1
comma
id|raw_sector
)paren
)paren
(brace
id|is_xa
op_assign
(paren
id|raw_sector
(braket
l_int|3
)braket
op_eq
l_int|0x02
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* read a raw sector failed for some reason. */
id|is_xa
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
id|scsi_free
c_func
(paren
id|raw_sector
comma
l_int|2048
op_plus
l_int|512
)paren
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;sr%d: sr_is_xa: %d&bslash;n&quot;
comma
id|minor
comma
id|is_xa
)paren
suffix:semicolon
macro_line|#endif
r_return
id|is_xa
suffix:semicolon
)brace
DECL|function|sr_dev_ioctl
r_int
id|sr_dev_ioctl
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
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
id|target
suffix:semicolon
id|target
op_assign
id|MINOR
c_func
(paren
id|cdi-&gt;dev
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|BLKROSET
suffix:colon
r_case
id|BLKROGET
suffix:colon
r_case
id|BLKRASET
suffix:colon
r_case
id|BLKRAGET
suffix:colon
r_case
id|BLKFLSBUF
suffix:colon
r_case
id|BLKSSZGET
suffix:colon
r_return
id|blk_ioctl
c_func
(paren
id|cdi-&gt;dev
comma
id|cmd
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
id|scsi_CDs
(braket
id|target
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
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-indent-level: 4&n; * c-brace-imaginary-offset: 0&n; * c-brace-offset: -4&n; * c-argdecl-indent: 4&n; * c-label-offset: -4&n; * c-continued-statement-offset: 4&n; * c-continued-brace-offset: 0&n; * indent-tabs-mode: nil&n; * tab-width: 8&n; * End:&n; */
eof
