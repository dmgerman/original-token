multiline_comment|/* Driver for USB scsi like devices&n; * &n; * (C) Michael Gee (michael@linuxspecific.com) 1999&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &quot;../scsi/scsi.h&quot;
macro_line|#include &quot;../scsi/hosts.h&quot;
macro_line|#include &quot;../scsi/sd.h&quot;
macro_line|#include &quot;usb.h&quot;
macro_line|#include &quot;usb_scsi.h&quot;
DECL|function|us_show_command
r_void
id|us_show_command
c_func
(paren
id|Scsi_Cmnd
op_star
id|srb
)paren
(brace
r_char
op_star
id|what
op_assign
l_int|NULL
suffix:semicolon
r_switch
c_cond
(paren
id|srb-&gt;cmnd
(braket
l_int|0
)braket
)paren
(brace
r_case
id|TEST_UNIT_READY
suffix:colon
id|what
op_assign
l_string|&quot;TEST_UNIT_READY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REZERO_UNIT
suffix:colon
id|what
op_assign
l_string|&quot;REZERO_UNIT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REQUEST_SENSE
suffix:colon
id|what
op_assign
l_string|&quot;REQUEST_SENSE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|FORMAT_UNIT
suffix:colon
id|what
op_assign
l_string|&quot;FORMAT_UNIT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_BLOCK_LIMITS
suffix:colon
id|what
op_assign
l_string|&quot;READ_BLOCK_LIMITS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REASSIGN_BLOCKS
suffix:colon
id|what
op_assign
l_string|&quot;REASSIGN_BLOCKS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_6
suffix:colon
id|what
op_assign
l_string|&quot;READ_6&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_6
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_6&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEEK_6
suffix:colon
id|what
op_assign
l_string|&quot;SEEK_6&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_REVERSE
suffix:colon
id|what
op_assign
l_string|&quot;READ_REVERSE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_FILEMARKS
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_FILEMARKS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SPACE
suffix:colon
id|what
op_assign
l_string|&quot;SPACE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INQUIRY
suffix:colon
id|what
op_assign
l_string|&quot;INQUIRY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECOVER_BUFFERED_DATA
suffix:colon
id|what
op_assign
l_string|&quot;RECOVER_BUFFERED_DATA&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MODE_SELECT
suffix:colon
id|what
op_assign
l_string|&quot;MODE_SELECT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RESERVE
suffix:colon
id|what
op_assign
l_string|&quot;RESERVE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RELEASE
suffix:colon
id|what
op_assign
l_string|&quot;RELEASE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COPY
suffix:colon
id|what
op_assign
l_string|&quot;COPY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ERASE
suffix:colon
id|what
op_assign
l_string|&quot;ERASE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MODE_SENSE
suffix:colon
id|what
op_assign
l_string|&quot;MODE_SENSE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|START_STOP
suffix:colon
id|what
op_assign
l_string|&quot;START_STOP&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|RECEIVE_DIAGNOSTIC
suffix:colon
id|what
op_assign
l_string|&quot;RECEIVE_DIAGNOSTIC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEND_DIAGNOSTIC
suffix:colon
id|what
op_assign
l_string|&quot;SEND_DIAGNOSTIC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ALLOW_MEDIUM_REMOVAL
suffix:colon
id|what
op_assign
l_string|&quot;ALLOW_MEDIUM_REMOVAL&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_WINDOW
suffix:colon
id|what
op_assign
l_string|&quot;SET_WINDOW&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_CAPACITY
suffix:colon
id|what
op_assign
l_string|&quot;READ_CAPACITY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_10
suffix:colon
id|what
op_assign
l_string|&quot;READ_10&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_10
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_10&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEEK_10
suffix:colon
id|what
op_assign
l_string|&quot;SEEK_10&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_VERIFY
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_VERIFY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|VERIFY
suffix:colon
id|what
op_assign
l_string|&quot;VERIFY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_HIGH
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_HIGH&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_EQUAL
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_EQUAL&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_LOW
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_LOW&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SET_LIMITS
suffix:colon
id|what
op_assign
l_string|&quot;SET_LIMITS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_POSITION
suffix:colon
id|what
op_assign
l_string|&quot;READ_POSITION&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SYNCHRONIZE_CACHE
suffix:colon
id|what
op_assign
l_string|&quot;SYNCHRONIZE_CACHE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LOCK_UNLOCK_CACHE
suffix:colon
id|what
op_assign
l_string|&quot;LOCK_UNLOCK_CACHE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_DEFECT_DATA
suffix:colon
id|what
op_assign
l_string|&quot;READ_DEFECT_DATA&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MEDIUM_SCAN
suffix:colon
id|what
op_assign
l_string|&quot;MEDIUM_SCAN&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COMPARE
suffix:colon
id|what
op_assign
l_string|&quot;COMPARE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|COPY_VERIFY
suffix:colon
id|what
op_assign
l_string|&quot;COPY_VERIFY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_BUFFER
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_BUFFER&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_BUFFER
suffix:colon
id|what
op_assign
l_string|&quot;READ_BUFFER&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|UPDATE_BLOCK
suffix:colon
id|what
op_assign
l_string|&quot;UPDATE_BLOCK&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_LONG
suffix:colon
id|what
op_assign
l_string|&quot;READ_LONG&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_LONG
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_LONG&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|CHANGE_DEFINITION
suffix:colon
id|what
op_assign
l_string|&quot;CHANGE_DEFINITION&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_SAME
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_SAME&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_TOC
suffix:colon
id|what
op_assign
l_string|&quot;READ_TOC&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LOG_SELECT
suffix:colon
id|what
op_assign
l_string|&quot;LOG_SELECT&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|LOG_SENSE
suffix:colon
id|what
op_assign
l_string|&quot;LOG_SENSE&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MODE_SELECT_10
suffix:colon
id|what
op_assign
l_string|&quot;MODE_SELECT_10&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MODE_SENSE_10
suffix:colon
id|what
op_assign
l_string|&quot;MODE_SENSE_10&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|MOVE_MEDIUM
suffix:colon
id|what
op_assign
l_string|&quot;MOVE_MEDIUM&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_12
suffix:colon
id|what
op_assign
l_string|&quot;READ_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_12
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_VERIFY_12
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_VERIFY_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_HIGH_12
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_HIGH_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_EQUAL_12
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_EQUAL_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEARCH_LOW_12
suffix:colon
id|what
op_assign
l_string|&quot;SEARCH_LOW_12&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|READ_ELEMENT_STATUS
suffix:colon
id|what
op_assign
l_string|&quot;READ_ELEMENT_STATUS&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SEND_VOLUME_TAG
suffix:colon
id|what
op_assign
l_string|&quot;SEND_VOLUME_TAG&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|WRITE_LONG_2
suffix:colon
id|what
op_assign
l_string|&quot;WRITE_LONG_2&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_DEBUG
id|USB_SCSI
l_string|&quot;Command %s (%d bytes)&bslash;n&quot;
comma
id|what
comma
id|srb-&gt;cmd_len
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
id|USB_SCSI
l_string|&quot;  %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x&bslash;n&quot;
comma
id|srb-&gt;cmnd
(braket
l_int|0
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|1
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|2
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|3
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|4
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|5
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|6
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|7
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|8
)braket
comma
id|srb-&gt;cmnd
(braket
l_int|9
)braket
)paren
suffix:semicolon
)brace
eof
