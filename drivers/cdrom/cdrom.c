multiline_comment|/* cdrom.c. Common ioctl and open routines for various Linux cdrom drivers. -*- linux-c -*-&n;   Copyright (c) 1996 David van Leeuwen. &n;&n;   The routines in the file should provide an interface between&n;   software accessing cdroms and the various drivers that implement&n;   specific hardware devices. &n;&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/fcntl.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/ucdrom.h&gt;
DECL|macro|FM_WRITE
mdefine_line|#define FM_WRITE&t;0x2                 /* file mode write bit */
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;Generic CD-ROM driver, v 1.21 1996/11/08 03:24:49&quot;
multiline_comment|/* Not-exported routines. */
r_static
r_int
id|cdrom_open
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
suffix:semicolon
r_static
r_void
id|cdrom_release
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
suffix:semicolon
r_static
r_int
id|cdrom_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
comma
r_int
r_int
id|cmd
comma
r_int
r_int
id|arg
)paren
suffix:semicolon
r_static
r_int
id|cdrom_media_changed
c_func
(paren
id|kdev_t
id|dev
)paren
suffix:semicolon
DECL|variable|cdrom_fops
r_struct
id|file_operations
id|cdrom_fops
op_assign
(brace
l_int|NULL
comma
multiline_comment|/* lseek */
id|block_read
comma
multiline_comment|/* read - general block-dev read */
id|block_write
comma
multiline_comment|/* write - general block-dev write */
l_int|NULL
comma
multiline_comment|/* readdir */
l_int|NULL
comma
multiline_comment|/* select */
id|cdrom_ioctl
comma
multiline_comment|/* ioctl */
l_int|NULL
comma
multiline_comment|/* mmap */
id|cdrom_open
comma
multiline_comment|/* open */
id|cdrom_release
comma
multiline_comment|/* release */
l_int|NULL
comma
multiline_comment|/* fsync */
l_int|NULL
comma
multiline_comment|/* fasync */
id|cdrom_media_changed
comma
multiline_comment|/* media_change */
l_int|NULL
multiline_comment|/* revalidate */
)brace
suffix:semicolon
DECL|variable|cdromdevs
r_static
r_struct
id|cdrom_device_info
op_star
id|cdromdevs
(braket
id|MAX_BLKDEV
)braket
op_assign
(brace
l_int|NULL
comma
)brace
suffix:semicolon
multiline_comment|/* This macro makes sure we don&squot;t have to check on cdrom_device_ops&n; * existence in the run-time routines below. Change_capability is a&n; * hack to have the capability flags defined const, while we can still&n; * change it here without gcc complaining at every line.&n; */
DECL|macro|ENSURE
mdefine_line|#define ENSURE(call, bits) if (cdo-&gt;call == NULL) *change_capability &amp;= ~(bits)
multiline_comment|/* We don&squot;t use $name$ yet, but it could be used for the /proc&n; * filesystem in the future, or for other purposes.  &n; */
DECL|function|register_cdrom
r_int
id|register_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_char
op_star
id|name
)paren
(brace
r_int
id|major
op_assign
id|MAJOR
(paren
id|cdi-&gt;dev
)paren
suffix:semicolon
r_struct
id|cdrom_device_ops
op_star
id|cdo
op_assign
id|cdi-&gt;ops
suffix:semicolon
r_int
op_star
id|change_capability
op_assign
(paren
r_int
op_star
)paren
op_amp
id|cdo-&gt;capability
suffix:semicolon
multiline_comment|/* hack */
r_if
c_cond
(paren
id|major
OL
l_int|0
op_logical_or
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|cdo-&gt;open
op_eq
l_int|NULL
op_logical_or
id|cdo-&gt;release
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|2
suffix:semicolon
id|ENSURE
c_func
(paren
id|tray_move
comma
id|CDC_CLOSE_TRAY
op_or
id|CDC_OPEN_TRAY
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|lock_door
comma
id|CDC_LOCK
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|select_speed
comma
id|CDC_SELECT_SPEED
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|select_disc
comma
id|CDC_SELECT_DISC
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|get_last_session
comma
id|CDC_MULTI_SESSION
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|audio_ioctl
comma
id|CDC_PLAY_AUDIO
)paren
suffix:semicolon
id|ENSURE
c_func
(paren
id|media_changed
comma
id|CDC_MEDIA_CHANGED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdromdevs
(braket
id|major
)braket
op_eq
l_int|NULL
)paren
id|cdo-&gt;n_minors
op_assign
l_int|0
suffix:semicolon
r_else
id|cdo-&gt;n_minors
op_increment
suffix:semicolon
id|cdi-&gt;next
op_assign
id|cdromdevs
(braket
id|major
)braket
suffix:semicolon
id|cdromdevs
(braket
id|major
)braket
op_assign
id|cdi
suffix:semicolon
id|cdi-&gt;options
op_assign
id|CDO_AUTO_CLOSE
op_or
id|CDO_USE_FFLAGS
op_or
id|CDO_LOCK
suffix:semicolon
id|cdi-&gt;mc_flags
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|ENSURE
macro_line|#undef ENSURE
DECL|function|unregister_cdrom
r_int
id|unregister_cdrom
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|unreg
)paren
(brace
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
op_star
id|prev
suffix:semicolon
r_int
id|major
op_assign
id|MAJOR
(paren
id|unreg-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|major
OL
l_int|0
op_logical_or
id|major
op_ge
id|MAX_BLKDEV
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|cdi
op_assign
id|cdromdevs
(braket
id|major
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cdi
op_ne
l_int|NULL
op_logical_and
id|cdi-&gt;dev
op_ne
id|unreg-&gt;dev
)paren
(brace
id|prev
op_assign
id|cdi
suffix:semicolon
id|cdi
op_assign
id|cdi-&gt;next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cdi
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|prev
)paren
id|prev-&gt;next
op_assign
id|cdi-&gt;next
suffix:semicolon
r_else
id|cdromdevs
(braket
id|major
)braket
op_assign
id|cdi-&gt;next
suffix:semicolon
id|cdi-&gt;ops-&gt;n_minors
op_decrement
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
DECL|function|cdrom_find_device
r_struct
id|cdrom_device_info
op_star
id|cdrom_find_device
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|cdrom_device_info
op_star
id|cdi
op_assign
id|cdromdevs
(braket
id|MAJOR
(paren
id|dev
)paren
)braket
suffix:semicolon
r_while
c_loop
(paren
id|cdi
op_ne
l_int|NULL
op_logical_and
id|cdi-&gt;dev
op_ne
id|dev
)paren
id|cdi
op_assign
id|cdi-&gt;next
suffix:semicolon
r_return
id|cdi
suffix:semicolon
)brace
multiline_comment|/* We use the open-option O_NONBLOCK to indicate that the&n; * purpose of opening is only for subsequent ioctl() calls; no device&n; * integrity checks are performed.&n; *&n; * We hope that all cd-player programs will adopt this convention. It&n; * is in their own interest: device control becomes a lot easier&n; * this way.&n; */
r_static
r_int
id|open_for_data
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
suffix:semicolon
r_static
DECL|function|cdrom_open
r_int
id|cdrom_open
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
id|kdev_t
id|dev
op_assign
id|ip-&gt;i_rdev
suffix:semicolon
r_struct
id|cdrom_device_info
op_star
id|cdi
op_assign
id|cdrom_find_device
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
id|purpose
op_assign
op_logical_neg
op_logical_neg
(paren
id|fp-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|cdi
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|fp-&gt;f_mode
op_amp
id|FM_WRITE
)paren
r_return
op_minus
id|EROFS
suffix:semicolon
id|purpose
op_assign
id|purpose
op_logical_or
op_logical_neg
(paren
id|cdi-&gt;options
op_amp
id|CDO_USE_FFLAGS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;use_count
op_logical_or
id|purpose
)paren
id|ret
op_assign
id|cdi-&gt;ops
op_member_access_from_pointer
id|open
c_func
(paren
id|cdi
comma
id|purpose
)paren
suffix:semicolon
r_else
id|ret
op_assign
id|open_for_data
c_func
(paren
id|cdi
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
)paren
id|cdi-&gt;use_count
op_increment
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_static
DECL|function|open_for_data
r_int
id|open_for_data
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
)paren
(brace
r_int
id|ret
suffix:semicolon
r_struct
id|cdrom_device_ops
op_star
id|cdo
op_assign
id|cdi-&gt;ops
suffix:semicolon
r_if
c_cond
(paren
id|cdo-&gt;drive_status
op_ne
l_int|NULL
)paren
(brace
r_int
id|ds
op_assign
id|cdo
op_member_access_from_pointer
id|drive_status
c_func
(paren
id|cdi
comma
id|CDSL_CURRENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ds
op_eq
id|CDS_TRAY_OPEN
)paren
(brace
multiline_comment|/* can/may i close it? */
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_CLOSE_TRAY
op_logical_and
id|cdi-&gt;options
op_amp
id|CDO_AUTO_CLOSE
)paren
(brace
r_if
c_cond
(paren
id|cdo
op_member_access_from_pointer
id|tray_move
c_func
(paren
id|cdi
comma
l_int|0
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_else
r_return
op_minus
id|ENXIO
suffix:semicolon
multiline_comment|/* can&squot;t close: too bad */
id|ds
op_assign
id|cdo
op_member_access_from_pointer
id|drive_status
c_func
(paren
id|cdi
comma
id|CDSL_CURRENT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ds
op_eq
id|CDS_NO_DISC
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|cdo-&gt;disc_status
op_ne
l_int|NULL
)paren
(brace
r_int
id|ds
op_assign
id|cdo
op_member_access_from_pointer
id|disc_status
c_func
(paren
id|cdi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ds
op_eq
id|CDS_NO_DISC
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;options
op_amp
id|CDO_CHECK_TYPE
op_logical_and
id|ds
op_ne
id|CDS_DATA_1
)paren
r_return
op_minus
id|ENODATA
suffix:semicolon
)brace
multiline_comment|/* all is well, we can open the device */
id|ret
op_assign
id|cdo
op_member_access_from_pointer
id|open
c_func
(paren
id|cdi
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* open for data */
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_LOCK
op_logical_and
id|cdi-&gt;options
op_amp
id|CDO_LOCK
)paren
id|cdo
op_member_access_from_pointer
id|lock_door
c_func
(paren
id|cdi
comma
l_int|1
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Admittedly, the logic below could be performed in a nicer way. */
r_static
DECL|function|cdrom_release
r_void
id|cdrom_release
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
)paren
(brace
id|kdev_t
id|dev
op_assign
id|ip-&gt;i_rdev
suffix:semicolon
r_struct
id|cdrom_device_info
op_star
id|cdi
op_assign
id|cdrom_find_device
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|cdrom_device_ops
op_star
id|cdo
suffix:semicolon
r_if
c_cond
(paren
id|cdi
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|cdo
op_assign
id|cdi-&gt;ops
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;use_count
op_eq
l_int|1
op_logical_and
multiline_comment|/* last process that closes dev*/
id|cdi-&gt;options
op_amp
id|CDO_LOCK
op_logical_and
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_LOCK
)paren
id|cdo
op_member_access_from_pointer
id|lock_door
c_func
(paren
id|cdi
comma
l_int|0
)paren
suffix:semicolon
id|cdo
op_member_access_from_pointer
id|release
c_func
(paren
id|cdi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;use_count
OG
l_int|0
)paren
id|cdi-&gt;use_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;use_count
op_eq
l_int|0
)paren
(brace
multiline_comment|/* last process that closes dev*/
id|sync_dev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|invalidate_buffers
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;options
op_amp
id|CDO_AUTO_EJECT
op_logical_and
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_OPEN_TRAY
)paren
id|cdo
op_member_access_from_pointer
id|tray_move
c_func
(paren
id|cdi
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* We want to make media_changed accessible to the user through an&n; * ioctl. The main problem now is that we must double-buffer the&n; * low-level implementation, to assure that the VFS and the user both&n; * see a medium change once.&n; */
r_static
DECL|function|media_changed
r_int
id|media_changed
c_func
(paren
r_struct
id|cdrom_device_info
op_star
id|cdi
comma
r_int
id|queue
)paren
(brace
r_int
r_int
id|mask
op_assign
(paren
l_int|1
op_lshift
(paren
id|queue
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_int
id|ret
op_assign
op_logical_neg
op_logical_neg
(paren
id|cdi-&gt;mc_flags
op_amp
id|mask
)paren
suffix:semicolon
multiline_comment|/* changed since last call? */
r_if
c_cond
(paren
id|cdi-&gt;ops
op_member_access_from_pointer
id|media_changed
c_func
(paren
id|cdi
comma
id|CDSL_CURRENT
)paren
)paren
(brace
id|cdi-&gt;mc_flags
op_assign
l_int|0x3
suffix:semicolon
multiline_comment|/* set bit on both queues */
id|ret
op_or_assign
l_int|1
suffix:semicolon
)brace
id|cdi-&gt;mc_flags
op_and_assign
op_complement
id|mask
suffix:semicolon
multiline_comment|/* clear bit */
r_return
id|ret
suffix:semicolon
)brace
r_static
DECL|function|cdrom_media_changed
r_int
id|cdrom_media_changed
c_func
(paren
id|kdev_t
id|dev
)paren
(brace
r_struct
id|cdrom_device_info
op_star
id|cdi
op_assign
id|cdrom_find_device
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdi
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|cdi-&gt;ops-&gt;media_changed
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|media_changed
c_func
(paren
id|cdi
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* Requests to the low-level drivers will /always/ be done in the&n;   following format convention: &n;&n;   CDROM_LBA: all data-related requests.&n;   CDROM_MSF: all audio-related requests. &n;&n;   However, a low-level implementation is allowed to refuse this&n;   request, and return information in its own favorite format.  &n;&n;   It doesn&squot;t make sense /at all/ to ask for a play_audio in LBA&n;   format, or ask for multi-session info in MSF format. However, for&n;   backward compatibility these format requests will be satisfied, but&n;   the requests to the low-level drivers will be sanitized in the more&n;   meaningful format indicated above.&n; */
r_static
DECL|function|sanitize_format
r_void
id|sanitize_format
c_func
(paren
r_union
id|cdrom_addr
op_star
id|addr
comma
id|u_char
op_star
id|curr
comma
id|u_char
id|requested
)paren
(brace
r_if
c_cond
(paren
op_star
id|curr
op_eq
id|requested
)paren
r_return
suffix:semicolon
multiline_comment|/* nothing to be done! */
r_if
c_cond
(paren
id|requested
op_eq
id|CDROM_LBA
)paren
(brace
id|addr-&gt;lba
op_assign
(paren
r_int
)paren
id|addr-&gt;msf.frame
op_plus
l_int|75
op_star
(paren
id|addr-&gt;msf.second
op_minus
l_int|2
op_plus
l_int|60
op_star
id|addr-&gt;msf.minute
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* CDROM_MSF */
r_int
id|lba
op_assign
id|addr-&gt;lba
suffix:semicolon
id|addr-&gt;msf.frame
op_assign
id|lba
op_mod
l_int|75
suffix:semicolon
id|lba
op_div_assign
l_int|75
suffix:semicolon
id|lba
op_add_assign
l_int|2
suffix:semicolon
id|addr-&gt;msf.second
op_assign
id|lba
op_mod
l_int|60
suffix:semicolon
id|addr-&gt;msf.minute
op_assign
id|lba
op_div
l_int|60
suffix:semicolon
)brace
op_star
id|curr
op_assign
id|requested
suffix:semicolon
)brace
multiline_comment|/* All checking and format change makes this code really hard to read!&n; * So let&squot;s make some check and memory move macros.  These macros are&n; * a little inefficient when both used in the same piece of code, as&n; * verify_area is used twice, but who cares, as ioctl() calls&n; * shouldn&squot;t be in inner loops.&n; */
DECL|macro|GETARG
mdefine_line|#define GETARG(type, x) { &bslash;&n;        int ret=verify_area(VERIFY_READ, (void *) arg, sizeof x); &bslash;&n;&t;    if (ret) return ret; &bslash;&n;&t;    copy_from_user(&amp;x, (type *) arg, sizeof x); }
DECL|macro|PUTARG
mdefine_line|#define PUTARG(type, x) { &bslash;&n;&t;    int ret=verify_area(VERIFY_WRITE, (void *) arg, sizeof x); &bslash;&n;&t;    if (ret) return ret; &bslash;&n;&t;    copy_to_user((type *) arg, &amp;x, sizeof x); }
multiline_comment|/* Some of the cdrom ioctls are not implemented here, because these&n; * appear to be either too device-specific, or it is not clear to me&n; * what use they are. These are (number of drivers that support them&n; * in parenthesis): CDROMREADMODE1 (2+ide), CDROMREADMODE2 (2+ide),&n; * CDROMREADAUDIO (2+ide), CDROMREADRAW (2), CDROMREADCOOKED (2),&n; * CDROMSEEK (2), CDROMPLAYBLK (scsi), CDROMREADALL (1). Read-audio,&n; * OK (although i guess the record companies aren&squot;t too happy with&n; * this, most drives therefore refuse to transport audio data).  But&n; * why are there 5 different READs defined? For now, these functions&n; * are left over to the device-specific ioctl routine,&n; * cdo-&gt;dev_ioctl. Note that as a result of this, no&n; * memory-verification is performed for these ioctls.&n; */
r_static
DECL|function|cdrom_ioctl
r_int
id|cdrom_ioctl
c_func
(paren
r_struct
id|inode
op_star
id|ip
comma
r_struct
id|file
op_star
id|fp
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
id|kdev_t
id|dev
op_assign
id|ip-&gt;i_rdev
suffix:semicolon
r_struct
id|cdrom_device_info
op_star
id|cdi
op_assign
id|cdrom_find_device
(paren
id|dev
)paren
suffix:semicolon
r_struct
id|cdrom_device_ops
op_star
id|cdo
suffix:semicolon
r_if
c_cond
(paren
id|cdi
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cdo
op_assign
id|cdi-&gt;ops
suffix:semicolon
multiline_comment|/* the first few commands do not deal with audio capabilities, but&n;           only with routines in cdrom device operations. */
r_switch
c_cond
(paren
id|cmd
)paren
(brace
multiline_comment|/* maybe we should order cases after statistics of use? */
r_case
id|CDROMMULTISESSION
suffix:colon
(brace
r_struct
id|cdrom_multisession
id|ms_info
suffix:semicolon
id|u_char
id|requested_format
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cdo-&gt;capability
op_amp
id|CDC_MULTI_SESSION
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_multisession
comma
id|ms_info
)paren
suffix:semicolon
id|requested_format
op_assign
id|ms_info.addr_format
suffix:semicolon
id|ms_info.addr_format
op_assign
id|CDROM_LBA
suffix:semicolon
id|cdo
op_member_access_from_pointer
id|get_last_session
c_func
(paren
id|cdi
comma
op_amp
id|ms_info
)paren
suffix:semicolon
id|sanitize_format
c_func
(paren
op_amp
id|ms_info.addr
comma
op_amp
id|ms_info.addr_format
comma
id|requested_format
)paren
suffix:semicolon
id|PUTARG
c_func
(paren
r_struct
id|cdrom_multisession
comma
id|ms_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_case
id|CDROMEJECT
suffix:colon
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_OPEN_TRAY
)paren
(brace
r_if
c_cond
(paren
id|cdi-&gt;use_count
op_eq
l_int|1
)paren
r_return
id|cdo
op_member_access_from_pointer
id|tray_move
c_func
(paren
id|cdi
comma
l_int|1
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|CDROMCLOSETRAY
suffix:colon
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_CLOSE_TRAY
)paren
r_return
id|cdo
op_member_access_from_pointer
id|tray_move
c_func
(paren
id|cdi
comma
l_int|0
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|CDROMEJECT_SW
suffix:colon
id|cdi-&gt;options
op_and_assign
op_complement
(paren
id|CDO_AUTO_CLOSE
op_or
id|CDO_AUTO_EJECT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
id|cdi-&gt;options
op_or_assign
id|CDO_AUTO_CLOSE
op_or
id|CDO_AUTO_EJECT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|CDROM_MEDIA_CHANGED
suffix:colon
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_MEDIA_CHANGED
)paren
(brace
r_if
c_cond
(paren
id|arg
op_eq
id|CDSL_CURRENT
)paren
r_return
id|media_changed
c_func
(paren
id|cdi
comma
l_int|1
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
r_int
)paren
id|arg
OL
id|cdi-&gt;capacity
op_logical_and
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_SELECT_DISC
)paren
r_return
id|cdo-&gt;media_changed
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|CDROM_SET_OPTIONS
suffix:colon
id|cdi-&gt;options
op_or_assign
(paren
r_int
)paren
id|arg
suffix:semicolon
r_return
id|cdi-&gt;options
suffix:semicolon
r_case
id|CDROM_CLEAR_OPTIONS
suffix:colon
id|cdi-&gt;options
op_and_assign
op_complement
(paren
r_int
)paren
id|arg
suffix:semicolon
r_return
id|cdi-&gt;options
suffix:semicolon
r_case
id|CDROM_SELECT_SPEED
suffix:colon
r_if
c_cond
(paren
(paren
r_int
)paren
id|arg
op_le
id|cdi-&gt;speed
op_logical_and
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_SELECT_SPEED
)paren
r_return
id|cdo
op_member_access_from_pointer
id|select_speed
c_func
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
r_case
id|CDROM_SELECT_DISC
suffix:colon
r_if
c_cond
(paren
(paren
id|arg
op_eq
id|CDSL_CURRENT
)paren
op_logical_or
(paren
id|arg
op_eq
id|CDSL_NONE
)paren
)paren
r_return
id|cdo
op_member_access_from_pointer
id|select_disc
c_func
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
)paren
id|arg
OL
id|cdi-&gt;capacity
op_logical_and
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_SELECT_DISC
)paren
r_return
id|cdo
op_member_access_from_pointer
id|select_disc
c_func
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* The following function is implemented, although very few audio&n; * discs give Universal Product Code information, which should just be&n; * the Medium Catalog Number on the box.  Note, that the way the code&n; * is written on the CD is /not/ uniform across all discs!&n; */
r_case
id|CDROM_GET_MCN
suffix:colon
(brace
r_struct
id|cdrom_mcn
id|mcn
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cdo-&gt;capability
op_amp
id|CDC_MCN
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdo
op_member_access_from_pointer
id|get_mcn
c_func
(paren
id|cdi
comma
op_amp
id|mcn
)paren
)paren
(brace
id|PUTARG
c_func
(paren
r_struct
id|cdrom_mcn
comma
id|mcn
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|CDROM_DRIVE_STATUS
suffix:colon
r_if
c_cond
(paren
(paren
id|arg
op_eq
id|CDSL_CURRENT
)paren
op_logical_or
(paren
id|arg
op_eq
id|CDSL_NONE
)paren
)paren
r_return
id|cdo
op_member_access_from_pointer
id|drive_status
c_func
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdo-&gt;drive_status
op_eq
l_int|NULL
op_logical_or
op_logical_neg
(paren
id|cdo-&gt;capability
op_amp
op_complement
id|cdi-&gt;mask
op_amp
id|CDC_SELECT_DISC
op_logical_and
(paren
r_int
)paren
id|arg
OL
id|cdi-&gt;capacity
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
id|cdo
op_member_access_from_pointer
id|drive_status
c_func
(paren
id|cdi
comma
id|arg
)paren
suffix:semicolon
r_case
id|CDROM_DISC_STATUS
suffix:colon
r_if
c_cond
(paren
id|cdo-&gt;disc_status
op_eq
l_int|NULL
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_else
r_return
id|cdo
op_member_access_from_pointer
id|disc_status
c_func
(paren
id|cdi
)paren
suffix:semicolon
r_case
id|CDROM_CHANGER_NSLOTS
suffix:colon
r_return
id|cdi-&gt;capacity
suffix:semicolon
multiline_comment|/* The following is not implemented, because there are too many&n; * different data type. We could support /1/ raw mode, that is large&n; * enough to hold everything.&n; */
macro_line|#if 0
r_case
id|CDROMREADMODE1
suffix:colon
(brace
r_struct
id|cdrom_msf
id|msf
suffix:semicolon
r_char
id|buf
(braket
id|CD_FRAMESIZE
)braket
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_msf
comma
id|msf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdo
op_member_access_from_pointer
id|read_audio
c_func
(paren
id|dev
comma
id|cmd
comma
op_amp
id|msf
comma
op_amp
id|buf
comma
id|cdi
)paren
)paren
(brace
id|PUTARG
c_func
(paren
r_char
op_star
comma
id|buf
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* switch */
multiline_comment|/* Now all the audio-ioctls follow, they are all routed through the&n;   same call audio_ioctl(). */
r_if
c_cond
(paren
id|cdo-&gt;capability
op_amp
id|CDC_PLAY_AUDIO
)paren
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|CDROMSUBCHNL
suffix:colon
(brace
r_struct
id|cdrom_subchnl
id|q
suffix:semicolon
id|u_char
id|requested
comma
id|back
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_subchnl
comma
id|q
)paren
suffix:semicolon
id|requested
op_assign
id|q.cdsc_format
suffix:semicolon
id|q.cdsc_format
op_assign
id|CDROM_MSF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|q
)paren
)paren
(brace
id|back
op_assign
id|q.cdsc_format
suffix:semicolon
multiline_comment|/* local copy */
id|sanitize_format
c_func
(paren
op_amp
id|q.cdsc_absaddr
comma
op_amp
id|back
comma
id|requested
)paren
suffix:semicolon
id|sanitize_format
c_func
(paren
op_amp
id|q.cdsc_reladdr
comma
op_amp
id|q.cdsc_format
comma
id|requested
)paren
suffix:semicolon
id|PUTARG
c_func
(paren
r_struct
id|cdrom_subchnl
comma
id|q
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|CDROMREADTOCHDR
suffix:colon
(brace
r_struct
id|cdrom_tochdr
id|header
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_tochdr
comma
id|header
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|header
)paren
)paren
(brace
id|PUTARG
c_func
(paren
r_struct
id|cdrom_tochdr
comma
id|header
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|CDROMREADTOCENTRY
suffix:colon
(brace
r_struct
id|cdrom_tocentry
id|entry
suffix:semicolon
id|u_char
id|requested_format
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_tocentry
comma
id|entry
)paren
suffix:semicolon
id|requested_format
op_assign
id|entry.cdte_format
suffix:semicolon
multiline_comment|/* make interface to low-level uniform */
id|entry.cdte_format
op_assign
id|CDROM_MSF
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|entry
)paren
)paren
)paren
(brace
id|sanitize_format
c_func
(paren
op_amp
id|entry.cdte_addr
comma
op_amp
id|entry.cdte_format
comma
id|requested_format
)paren
suffix:semicolon
id|PUTARG
c_func
(paren
r_struct
id|cdrom_tocentry
comma
id|entry
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|CDROMPLAYMSF
suffix:colon
(brace
r_struct
id|cdrom_msf
id|msf
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_msf
comma
id|msf
)paren
suffix:semicolon
r_return
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|msf
)paren
suffix:semicolon
)brace
r_case
id|CDROMPLAYTRKIND
suffix:colon
(brace
r_struct
id|cdrom_ti
id|track_index
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_ti
comma
id|track_index
)paren
suffix:semicolon
r_return
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|track_index
)paren
suffix:semicolon
)brace
r_case
id|CDROMVOLCTRL
suffix:colon
(brace
r_struct
id|cdrom_volctrl
id|volume
suffix:semicolon
id|GETARG
c_func
(paren
r_struct
id|cdrom_volctrl
comma
id|volume
)paren
suffix:semicolon
r_return
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|volume
)paren
suffix:semicolon
)brace
r_case
id|CDROMVOLREAD
suffix:colon
(brace
r_struct
id|cdrom_volctrl
id|volume
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
op_amp
id|volume
)paren
)paren
(brace
id|PUTARG
c_func
(paren
r_struct
id|cdrom_volctrl
comma
id|volume
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_case
id|CDROMSTART
suffix:colon
r_case
id|CDROMSTOP
suffix:colon
r_case
id|CDROMPAUSE
suffix:colon
r_case
id|CDROMRESUME
suffix:colon
r_return
id|cdo
op_member_access_from_pointer
id|audio_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* switch */
r_if
c_cond
(paren
id|cdo-&gt;dev_ioctl
op_ne
l_int|NULL
)paren
multiline_comment|/* device specific ioctls? */
r_return
id|cdo
op_member_access_from_pointer
id|dev_ioctl
c_func
(paren
id|cdi
comma
id|cmd
comma
id|arg
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Module inserted: &quot;
id|VERSION
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t;printk(KERN_INFO &quot;Module cdrom removed&bslash;n&quot;);&n;&t;*/
)brace
macro_line|#endif
multiline_comment|/*&n; * Local variables:&n; * comment-column: 40&n; * compile-command: &quot;gcc -DMODULE -D__KERNEL__ -I. -I/usr/src/linux-obj/include -Wall -Wstrict-prototypes -O2 -m486 -c cdrom.c -o cdrom.o&quot;&n; * End:&n; */
eof
