multiline_comment|/*&n; * $Id: capi.c,v 1.21 1999/09/10 17:24:18 calle Exp $&n; *&n; * CAPI 2.0 Interface for Linux&n; *&n; * Copyright 1996 by Carsten Paeth (calle@calle.in-berlin.de)&n; *&n; * $Log: capi.c,v $&n; * Revision 1.21  1999/09/10 17:24:18  calle&n; * Changes for proposed standard for CAPI2.0:&n; * - AK148 &quot;Linux Exention&quot;&n; *&n; * Revision 1.20  1999/09/07 09:02:53  calle&n; * SETDATA removed. Now inside the kernel the datapart of DATA_B3_REQ and&n; * DATA_B3_IND is always directly after the CAPI message. The &quot;Data&quot; member&n; * ist never used inside the kernel.&n; *&n; * Revision 1.19  1999/07/09 15:05:42  keil&n; * compat.h is now isdn_compat.h&n; *&n; * Revision 1.18  1999/07/06 07:42:01  calle&n; * - changes in /proc interface&n; * - check and changed calls to [dev_]kfree_skb and [dev_]alloc_skb.&n; *&n; * Revision 1.17  1999/07/01 15:26:30  calle&n; * complete new version (I love it):&n; * + new hardware independed &quot;capi_driver&quot; interface that will make it easy to:&n; *   - support other controllers with CAPI-2.0 (i.e. USB Controller)&n; *   - write a CAPI-2.0 for the passive cards&n; *   - support serial link CAPI-2.0 boxes.&n; * + wrote &quot;capi_driver&quot; for all supported cards.&n; * + &quot;capi_driver&quot; (supported cards) now have to be configured with&n; *   make menuconfig, in the past all supported cards where included&n; *   at once.&n; * + new and better informations in /proc/capi/&n; * + new ioctl to switch trace of capi messages per controller&n; *   using &quot;avmcapictrl trace [contr] on|off|....&quot;&n; * + complete testcircle with all supported cards and also the&n; *   PCMCIA cards (now patch for pcmcia-cs-3.0.13 needed) done.&n; *&n; * Revision 1.16  1999/07/01 08:22:57  keil&n; * compatibility macros now in &lt;linux/isdn_compat.h&gt;&n; *&n; * Revision 1.15  1999/06/21 15:24:11  calle&n; * extend information in /proc.&n; *&n; * Revision 1.14  1999/06/10 16:51:03  calle&n; * Bugfix: open/release of control device was not handled correct.&n; *&n; * Revision 1.13  1998/08/28 04:32:25  calle&n; * Added patch send by Michael.Mueller4@post.rwth-aachen.de, to get AVM B1&n; * driver running with 2.1.118.&n; *&n; * Revision 1.12  1998/05/26 22:39:34  he&n; * sync&squot;ed with 2.1.102 where appropriate (CAPABILITY changes)&n; * concap typo&n; * cleared dev.tbusy in isdn_net BCONN status callback&n; *&n; * Revision 1.11  1998/03/09 17:46:37  he&n; * merged in 2.1.89 changes&n; *&n; * Revision 1.10  1998/02/13 07:09:13  calle&n; * change for 2.1.86 (removing FREE_READ/FREE_WRITE from [dev]_kfree_skb()&n; *&n; * Revision 1.9  1998/01/31 11:14:44  calle&n; * merged changes to 2.0 tree, prepare 2.1.82 to work.&n; *&n; * Revision 1.8  1997/11/04 06:12:08  calle&n; * capi.c: new read/write in file_ops since 2.1.60&n; * capidrv.c: prepared isdnlog interface for d2-trace in newer firmware.&n; * capiutil.c: needs config.h (CONFIG_ISDN_DRV_AVMB1_VERBOSE_REASON)&n; * compat.h: added #define LinuxVersionCode&n; *&n; * Revision 1.7  1997/10/11 10:29:34  calle&n; * llseek() parameters changed in 2.1.56.&n; *&n; * Revision 1.6  1997/10/01 09:21:15  fritz&n; * Removed old compatibility stuff for 2.0.X kernels.&n; * From now on, this code is for 2.1.X ONLY!&n; * Old stuff is still in the separate branch.&n; *&n; * Revision 1.5  1997/08/21 23:11:55  fritz&n; * Added changes for kernels &gt;= 2.1.45&n; *&n; * Revision 1.4  1997/05/27 15:17:50  fritz&n; * Added changes for recent 2.1.x kernels:&n; *   changed return type of isdn_close&n; *   queue_task_* -&gt; queue_task&n; *   clear/set_bit -&gt; test_and_... where apropriate.&n; *   changed type of hard_header_cache parameter.&n; *&n; * Revision 1.3  1997/05/18 09:24:14  calle&n; * added verbose disconnect reason reporting to avmb1.&n; * some fixes in capi20 interface.&n; * changed info messages for B1-PCI&n; *&n; * Revision 1.2  1997/03/05 21:17:59  fritz&n; * Added capi_poll for compiling under 2.1.27&n; *&n; * Revision 1.1  1997/03/04 21:50:29  calle&n; * Frirst version in isdn4linux&n; *&n; * Revision 2.2  1997/02/12 09:31:39  calle&n; * new version&n; *&n; * Revision 1.1  1997/01/31 10:32:20  calle&n; * Initial revision&n; *&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/fs.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/capi.h&gt;
macro_line|#include &lt;linux/kernelcapi.h&gt;
macro_line|#include &quot;capiutil.h&quot;
macro_line|#include &quot;capicmd.h&quot;
macro_line|#include &quot;capidev.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Carsten Paeth (calle@calle.in-berlin.de)&quot;
)paren
suffix:semicolon
multiline_comment|/* -------- driver information -------------------------------------- */
DECL|variable|capi_major
r_int
id|capi_major
op_assign
l_int|68
suffix:semicolon
multiline_comment|/* allocated */
id|MODULE_PARM
c_func
(paren
id|capi_major
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/* -------- global variables ---------------------------------------- */
DECL|variable|capidevs
r_static
r_struct
id|capidev
id|capidevs
(braket
id|CAPI_MAXMINOR
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|capifuncs
r_struct
id|capi_interface
op_star
id|capifuncs
suffix:semicolon
multiline_comment|/* -------- function called by lower level -------------------------- */
DECL|function|capi_signal
r_static
r_void
id|capi_signal
c_func
(paren
id|__u16
id|applid
comma
id|__u32
id|minor
)paren
(brace
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|minor
OG
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_registered
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BUG: capi_signal: illegal minor %d&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
(paren
r_void
)paren
(paren
op_star
id|capifuncs-&gt;capi_get_message
)paren
(paren
id|applid
comma
op_amp
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
id|skb_queue_tail
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
comma
id|skb
)paren
suffix:semicolon
id|wake_up_interruptible
c_func
(paren
op_amp
id|cdev-&gt;recv_wait
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;BUG: capi_signal: no skb&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* -------- file_operations ----------------------------------------- */
DECL|function|capi_llseek
r_static
r_int
r_int
id|capi_llseek
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_int
r_int
id|offset
comma
r_int
id|origin
)paren
(brace
r_return
op_minus
id|ESPIPE
suffix:semicolon
)brace
DECL|function|capi_read
r_static
id|ssize_t
id|capi_read
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_int
id|copied
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minor
op_logical_or
id|minor
OG
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_registered
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|file-&gt;f_flags
op_amp
id|O_NONBLOCK
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|interruptible_sleep_on
c_func
(paren
op_amp
id|cdev-&gt;recv_wait
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
)paren
)paren
op_ne
l_int|0
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|signal_pending
c_func
(paren
id|current
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
op_eq
l_int|0
)paren
r_return
op_minus
id|ERESTARTNOHAND
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb-&gt;len
OG
id|count
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
comma
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EMSGSIZE
suffix:semicolon
)brace
id|retval
op_assign
id|copy_to_user
c_func
(paren
id|buf
comma
id|skb-&gt;data
comma
id|skb-&gt;len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|skb_queue_head
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
comma
id|skb
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|copied
op_assign
id|skb-&gt;len
suffix:semicolon
r_if
c_cond
(paren
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
op_eq
id|CAPI_DATA_B3
op_logical_and
id|CAPIMSG_SUBCOMMAND
c_func
(paren
id|skb-&gt;data
)paren
op_eq
id|CAPI_IND
)paren
id|cdev-&gt;nrecvdatapkt
op_increment
suffix:semicolon
r_else
id|cdev-&gt;nrecvctlpkt
op_increment
suffix:semicolon
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|copied
suffix:semicolon
)brace
DECL|function|capi_write
r_static
id|ssize_t
id|capi_write
c_func
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buf
comma
r_int
id|count
comma
id|loff_t
op_star
id|ppos
)paren
(brace
r_struct
id|inode
op_star
id|inode
op_assign
id|file-&gt;f_dentry-&gt;d_inode
suffix:semicolon
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|__u8
id|cmd
suffix:semicolon
id|__u8
id|subcmd
suffix:semicolon
id|__u16
id|mlen
suffix:semicolon
r_if
c_cond
(paren
id|ppos
op_ne
op_amp
id|file-&gt;f_pos
)paren
r_return
op_minus
id|ESPIPE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minor
op_logical_or
id|minor
OG
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_registered
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|count
comma
id|GFP_USER
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|retval
op_assign
id|copy_from_user
c_func
(paren
id|skb_put
c_func
(paren
id|skb
comma
id|count
)paren
comma
id|buf
comma
id|count
)paren
)paren
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
id|cmd
op_assign
id|CAPIMSG_COMMAND
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|subcmd
op_assign
id|CAPIMSG_SUBCOMMAND
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
id|mlen
op_assign
id|CAPIMSG_LEN
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_eq
id|CAPI_DATA_B3
op_logical_and
id|subcmd
op_eq
id|CAPI_REQ
)paren
(brace
id|__u16
id|dlen
op_assign
id|CAPIMSG_DATALEN
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mlen
op_plus
id|dlen
op_ne
id|count
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|mlen
op_ne
id|count
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
id|CAPIMSG_SETAPPID
c_func
(paren
id|skb-&gt;data
comma
id|cdev-&gt;applid
)paren
suffix:semicolon
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_put_message
)paren
(paren
id|cdev-&gt;applid
comma
id|skb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_eq
id|CAPI_DATA_B3
op_logical_and
id|subcmd
op_eq
id|CAPI_REQ
)paren
id|cdev-&gt;nsentdatapkt
op_increment
suffix:semicolon
r_else
id|cdev-&gt;nsentctlpkt
op_increment
suffix:semicolon
r_return
id|count
suffix:semicolon
)brace
r_static
r_int
r_int
DECL|function|capi_poll
id|capi_poll
c_func
(paren
r_struct
id|file
op_star
id|file
comma
id|poll_table
op_star
id|wait
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &gt;= 0x02012d)
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_dentry-&gt;d_inode-&gt;i_rdev
)paren
suffix:semicolon
macro_line|#else
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|file-&gt;f_inode-&gt;i_rdev
)paren
suffix:semicolon
macro_line|#endif
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|minor
op_logical_or
id|minor
OG
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_registered
)paren
r_return
id|POLLERR
suffix:semicolon
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
macro_line|#if (LINUX_VERSION_CODE &lt; 0x020159) /* 2.1.89 */
DECL|macro|poll_wait
mdefine_line|#define poll_wait(f,wq,w) poll_wait((wq),(w))
macro_line|#endif
id|poll_wait
c_func
(paren
id|file
comma
op_amp
(paren
id|cdev-&gt;recv_wait
)paren
comma
id|wait
)paren
suffix:semicolon
id|mask
op_assign
id|POLLOUT
op_or
id|POLLWRNORM
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|skb_queue_empty
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
)paren
)paren
id|mask
op_or_assign
id|POLLIN
op_or
id|POLLRDNORM
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
DECL|function|capi_ioctl
r_static
r_int
id|capi_ioctl
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
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
id|capi_ioctl_struct
id|data
suffix:semicolon
r_int
id|retval
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_open
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|CAPI_REGISTER
suffix:colon
(brace
r_if
c_cond
(paren
op_logical_neg
id|minor
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|data.rparams
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|capi_register_params
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;is_registered
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_register
)paren
(paren
op_amp
id|data.rparams
comma
op_amp
id|cdev-&gt;applid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
(paren
r_void
)paren
(paren
op_star
id|capifuncs-&gt;capi_set_signal
)paren
(paren
id|cdev-&gt;applid
comma
id|capi_signal
comma
id|minor
)paren
suffix:semicolon
id|cdev-&gt;is_registered
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|CAPI_GET_VERSION
suffix:colon
(brace
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|data.contr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data.contr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_get_version
)paren
(paren
id|data.contr
comma
op_amp
id|data.version
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
op_amp
id|data.version
comma
r_sizeof
(paren
id|data.version
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|CAPI_GET_SERIAL
suffix:colon
(brace
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|data.contr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data.contr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_get_serial
)paren
(paren
id|data.contr
comma
id|data.serial
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
id|data.serial
comma
r_sizeof
(paren
id|data.serial
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|CAPI_GET_PROFILE
suffix:colon
(brace
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|data.contr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data.contr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|data.contr
op_eq
l_int|0
)paren
(brace
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_get_profile
)paren
(paren
id|data.contr
comma
op_amp
id|data.profile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
op_amp
id|data.profile.ncontroller
comma
r_sizeof
(paren
id|data.profile.ncontroller
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_get_profile
)paren
(paren
id|data.contr
comma
op_amp
id|data.profile
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
op_amp
id|data.profile
comma
r_sizeof
(paren
id|data.profile
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|CAPI_GET_MANUFACTURER
suffix:colon
(brace
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|data.contr
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|data.contr
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|cdev-&gt;errcode
op_assign
(paren
op_star
id|capifuncs-&gt;capi_get_manufacturer
)paren
(paren
id|data.contr
comma
id|data.manufacturer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cdev-&gt;errcode
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
id|data.manufacturer
comma
r_sizeof
(paren
id|data.manufacturer
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
r_case
id|CAPI_GET_ERRCODE
suffix:colon
id|data.errcode
op_assign
id|cdev-&gt;errcode
suffix:semicolon
id|cdev-&gt;errcode
op_assign
id|CAPI_NOERROR
suffix:semicolon
r_if
c_cond
(paren
id|arg
)paren
(brace
id|retval
op_assign
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
(paren
r_void
op_star
)paren
op_amp
id|data.errcode
comma
r_sizeof
(paren
id|data.errcode
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|data.errcode
suffix:semicolon
r_case
id|CAPI_INSTALLED
suffix:colon
r_if
c_cond
(paren
(paren
op_star
id|capifuncs-&gt;capi_isinstalled
)paren
(paren
)paren
op_eq
id|CAPI_NOERROR
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
r_case
id|CAPI_MANUFACTURER_CMD
suffix:colon
(brace
r_struct
id|capi_manufacturer_cmd
id|mcmd
suffix:semicolon
r_if
c_cond
(paren
id|minor
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_ADMIN
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|retval
op_assign
id|copy_from_user
c_func
(paren
(paren
r_void
op_star
)paren
op_amp
id|mcmd
comma
(paren
r_void
op_star
)paren
id|arg
comma
r_sizeof
(paren
id|mcmd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
(paren
op_star
id|capifuncs-&gt;capi_manufacturer
)paren
(paren
id|mcmd.cmd
comma
id|mcmd.data
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
DECL|function|capi_open
r_static
r_int
id|capi_open
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
r_int
r_int
id|minor
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
id|minor
op_ge
id|CAPI_MAXMINOR
)paren
r_return
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|minor
)paren
(brace
r_if
c_cond
(paren
id|capidevs
(braket
id|minor
)braket
dot
id|is_open
)paren
r_return
op_minus
id|EEXIST
suffix:semicolon
id|capidevs
(braket
id|minor
)braket
dot
id|is_open
op_assign
l_int|1
suffix:semicolon
id|skb_queue_head_init
c_func
(paren
op_amp
id|capidevs
(braket
id|minor
)braket
dot
id|recv_queue
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
id|capidevs
(braket
id|minor
)braket
dot
id|nopen
op_increment
suffix:semicolon
)brace
r_else
(brace
id|capidevs
(braket
id|minor
)braket
dot
id|is_open
op_increment
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|capi_release
id|capi_release
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
r_int
r_int
id|minor
op_assign
id|MINOR
c_func
(paren
id|inode-&gt;i_rdev
)paren
suffix:semicolon
r_struct
id|capidev
op_star
id|cdev
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|minor
op_ge
id|CAPI_MAXMINOR
op_logical_or
op_logical_neg
id|capidevs
(braket
id|minor
)braket
dot
id|is_open
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capi20: release minor %d ???&bslash;n&quot;
comma
id|minor
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|cdev
op_assign
op_amp
id|capidevs
(braket
id|minor
)braket
suffix:semicolon
r_if
c_cond
(paren
id|minor
)paren
(brace
r_if
c_cond
(paren
id|cdev-&gt;is_registered
)paren
(paren
op_star
id|capifuncs-&gt;capi_release
)paren
(paren
id|cdev-&gt;applid
)paren
suffix:semicolon
id|cdev-&gt;is_registered
op_assign
l_int|0
suffix:semicolon
id|cdev-&gt;applid
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|skb
op_assign
id|skb_dequeue
c_func
(paren
op_amp
id|cdev-&gt;recv_queue
)paren
)paren
op_ne
l_int|0
)paren
(brace
id|kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
)brace
id|cdev-&gt;is_open
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|cdev-&gt;is_open
op_decrement
suffix:semicolon
)brace
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|capi_fops
r_static
r_struct
id|file_operations
id|capi_fops
op_assign
(brace
id|capi_llseek
comma
id|capi_read
comma
id|capi_write
comma
l_int|NULL
comma
multiline_comment|/* capi_readdir */
id|capi_poll
comma
id|capi_ioctl
comma
l_int|NULL
comma
multiline_comment|/* capi_mmap */
id|capi_open
comma
macro_line|#if LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,1,118)
l_int|NULL
comma
multiline_comment|/* capi_flush */
macro_line|#endif
id|capi_release
comma
l_int|NULL
comma
multiline_comment|/* capi_fsync */
l_int|NULL
comma
multiline_comment|/* capi_fasync */
)brace
suffix:semicolon
multiline_comment|/* -------- /proc functions ----------------------------------- */
multiline_comment|/*&n; * /proc/capi/capi20:&n; *  minor opencount nrecvctlpkt nrecvdatapkt nsendctlpkt nsenddatapkt&n; */
DECL|function|proc_capidev_read_proc
r_static
r_int
id|proc_capidev_read_proc
c_func
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|capidev
op_star
id|cp
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|off_t
id|begin
op_assign
l_int|0
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
id|CAPI_MAXMINOR
suffix:semicolon
id|i
op_increment
)paren
(brace
id|cp
op_assign
op_amp
id|capidevs
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|cp-&gt;nopen
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|page
op_plus
id|len
comma
l_string|&quot;%d %lu %lu %lu %lu %lu&bslash;n&quot;
comma
id|i
op_plus
l_int|1
comma
id|cp-&gt;nopen
comma
id|cp-&gt;nrecvctlpkt
comma
id|cp-&gt;nrecvdatapkt
comma
id|cp-&gt;nsentctlpkt
comma
id|cp-&gt;nsentdatapkt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OG
id|off
op_plus
id|count
)paren
r_goto
id|endloop
suffix:semicolon
r_if
c_cond
(paren
id|len
op_plus
id|begin
OL
id|off
)paren
(brace
id|begin
op_add_assign
id|len
suffix:semicolon
id|len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
id|endloop
suffix:colon
r_if
c_cond
(paren
id|i
op_ge
id|CAPI_MAXMINOR
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|off
op_ge
id|len
op_plus
id|begin
)paren
r_return
l_int|0
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
(paren
id|begin
op_minus
id|off
)paren
suffix:semicolon
r_return
(paren
(paren
id|count
OL
id|begin
op_plus
id|len
op_minus
id|off
)paren
ques
c_cond
id|count
suffix:colon
id|begin
op_plus
id|len
op_minus
id|off
)paren
suffix:semicolon
)brace
DECL|struct|procfsentries
r_static
r_struct
id|procfsentries
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|mode
id|mode_t
id|mode
suffix:semicolon
DECL|member|read_proc
r_int
(paren
op_star
id|read_proc
)paren
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
suffix:semicolon
DECL|member|procent
r_struct
id|proc_dir_entry
op_star
id|procent
suffix:semicolon
DECL|variable|procfsentries
)brace
id|procfsentries
(braket
)braket
op_assign
(brace
multiline_comment|/* { &quot;capi&quot;,&t;&t;  S_IFDIR, 0 }, */
(brace
l_string|&quot;capi/capi20&quot;
comma
l_int|0
comma
id|proc_capidev_read_proc
)brace
comma
)brace
suffix:semicolon
DECL|function|proc_init
r_static
r_void
id|proc_init
c_func
(paren
r_void
)paren
(brace
r_int
id|nelem
op_assign
r_sizeof
(paren
id|procfsentries
)paren
op_div
r_sizeof
(paren
id|procfsentries
(braket
l_int|0
)braket
)paren
suffix:semicolon
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
id|nelem
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|procfsentries
op_star
id|p
op_assign
id|procfsentries
op_plus
id|i
suffix:semicolon
id|p-&gt;procent
op_assign
id|create_proc_entry
c_func
(paren
id|p-&gt;name
comma
id|p-&gt;mode
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;procent
)paren
id|p-&gt;procent-&gt;read_proc
op_assign
id|p-&gt;read_proc
suffix:semicolon
)brace
)brace
DECL|function|proc_exit
r_static
r_void
id|proc_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|nelem
op_assign
r_sizeof
(paren
id|procfsentries
)paren
op_div
r_sizeof
(paren
id|procfsentries
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nelem
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_struct
id|procfsentries
op_star
id|p
op_assign
id|procfsentries
op_plus
id|i
suffix:semicolon
r_if
c_cond
(paren
id|p-&gt;procent
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|p-&gt;name
comma
l_int|0
)paren
suffix:semicolon
id|p-&gt;procent
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/* -------- init function and module interface ---------------------- */
macro_line|#ifdef MODULE
DECL|macro|capi_init
mdefine_line|#define&t; capi_init&t;init_module
macro_line|#endif
DECL|variable|cuser
r_static
r_struct
id|capi_interface_user
id|cuser
op_assign
(brace
l_string|&quot;capi20&quot;
comma
l_int|0
comma
)brace
suffix:semicolon
DECL|function|capi_init
r_int
id|capi_init
c_func
(paren
r_void
)paren
(brace
r_int
id|j
suffix:semicolon
id|memset
c_func
(paren
id|capidevs
comma
l_int|0
comma
r_sizeof
(paren
id|capidevs
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|CAPI_MAXMINOR
op_plus
l_int|1
suffix:semicolon
id|j
op_increment
)paren
(brace
id|init_waitqueue_head
c_func
(paren
op_amp
id|capidevs
(braket
id|j
)braket
dot
id|recv_wait
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|register_chrdev
c_func
(paren
id|capi_major
comma
l_string|&quot;capi20&quot;
comma
op_amp
id|capi_fops
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;capi20: unable to get major %d&bslash;n&quot;
comma
id|capi_major
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;capi20: started up with major %d&bslash;n&quot;
comma
id|capi_major
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|capifuncs
op_assign
id|attach_capi_interface
c_func
(paren
op_amp
id|cuser
)paren
)paren
op_eq
l_int|0
)paren
(brace
id|unregister_chrdev
c_func
(paren
id|capi_major
comma
l_string|&quot;capi20&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
(paren
r_void
)paren
id|proc_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
(paren
r_void
)paren
id|proc_exit
c_func
(paren
)paren
suffix:semicolon
id|unregister_chrdev
c_func
(paren
id|capi_major
comma
l_string|&quot;capi20&quot;
)paren
suffix:semicolon
(paren
r_void
)paren
id|detach_capi_interface
c_func
(paren
op_amp
id|cuser
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
