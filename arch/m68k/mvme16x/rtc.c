multiline_comment|/*&n; *&t;Real Time Clock interface for Linux on the MVME16x&n; *&n; * Based on the PC driver by Paul Gortmaker.&n; */
DECL|macro|RTC_VERSION
mdefine_line|#define RTC_VERSION&t;&t;&quot;1.00&quot;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;&t;/* For struct rtc_time and ioctls, etc */
macro_line|#include &lt;asm/mvme16xhw.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
multiline_comment|/*&n; *&t;We sponge a minor off of the misc major. No need slurping&n; *&t;up another valuable major dev number for this. If you add&n; *&t;an ioctl, make sure you don&squot;t conflict with SPARC&squot;s RTC&n; *&t;ioctls.&n; */
DECL|macro|BCD2BIN
mdefine_line|#define BCD2BIN(val) (((val)&amp;15) + ((val)&gt;&gt;4)*10)
DECL|macro|BIN2BCD
mdefine_line|#define BIN2BCD(val) ((((val)/10)&lt;&lt;4) + (val)%10)
DECL|variable|days_in_mo
r_static
r_int
r_char
id|days_in_mo
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|31
comma
l_int|28
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|31
comma
l_int|30
comma
l_int|31
comma
l_int|30
comma
l_int|31
)brace
suffix:semicolon
DECL|variable|rtc_status
r_static
r_char
id|rtc_status
op_assign
l_int|0
suffix:semicolon
DECL|function|rtc_ioctl
r_static
r_int
id|rtc_ioctl
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
r_volatile
id|MK48T08ptr_t
id|rtc
op_assign
(paren
id|MK48T08ptr_t
)paren
id|MVME_RTC_BASE
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|rtc_time
id|wtime
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTC_RD_TIME
suffix:colon
multiline_comment|/* Read the time/date from RTC&t;*/
(brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Ensure clock and real-time-mode-register are accessible */
id|rtc-&gt;ctrl
op_assign
id|RTC_READ
suffix:semicolon
id|wtime.tm_sec
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_sec
)paren
suffix:semicolon
id|wtime.tm_min
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_min
)paren
suffix:semicolon
id|wtime.tm_hour
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_hr
)paren
suffix:semicolon
id|wtime.tm_mday
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_dom
)paren
suffix:semicolon
id|wtime.tm_mon
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_mth
)paren
op_minus
l_int|1
suffix:semicolon
id|wtime.tm_year
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_year
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wtime.tm_year
OL
l_int|70
)paren
id|wtime.tm_year
op_add_assign
l_int|100
suffix:semicolon
id|wtime.tm_wday
op_assign
id|BCD2BIN
c_func
(paren
id|rtc-&gt;bcd_dow
)paren
op_minus
l_int|1
suffix:semicolon
id|rtc-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|copy_to_user
c_func
(paren
(paren
r_void
op_star
)paren
id|arg
comma
op_amp
id|wtime
comma
r_sizeof
id|wtime
)paren
ques
c_cond
op_minus
id|EFAULT
suffix:colon
l_int|0
suffix:semicolon
)brace
r_case
id|RTC_SET_TIME
suffix:colon
multiline_comment|/* Set the RTC */
(brace
r_int
r_char
id|leap_yr
suffix:semicolon
r_struct
id|rtc_time
id|rtc_tm
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|suser
c_func
(paren
)paren
)paren
r_return
op_minus
id|EACCES
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|rtc_tm
comma
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|leap_yr
op_assign
(paren
(paren
op_logical_neg
(paren
id|rtc_tm.tm_year
op_mod
l_int|4
)paren
op_logical_and
(paren
id|rtc_tm.tm_year
op_mod
l_int|100
)paren
)paren
op_logical_or
op_logical_neg
(paren
id|rtc_tm.tm_year
op_mod
l_int|400
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtc_tm.tm_mon
OG
l_int|12
)paren
op_logical_or
(paren
id|rtc_tm.tm_mday
op_eq
l_int|0
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|rtc_tm.tm_mday
OG
(paren
id|days_in_mo
(braket
id|rtc_tm.tm_mon
)braket
op_plus
(paren
(paren
id|rtc_tm.tm_mon
op_eq
l_int|2
)paren
op_logical_and
id|leap_yr
)paren
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rtc_tm.tm_hour
op_ge
l_int|24
)paren
op_logical_or
(paren
id|rtc_tm.tm_min
op_ge
l_int|60
)paren
op_logical_or
(paren
id|rtc_tm.tm_sec
op_ge
l_int|60
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|rtc-&gt;ctrl
op_assign
id|RTC_WRITE
suffix:semicolon
id|rtc-&gt;bcd_sec
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_sec
)paren
suffix:semicolon
id|rtc-&gt;bcd_min
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_min
)paren
suffix:semicolon
id|rtc-&gt;bcd_hr
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_hour
)paren
suffix:semicolon
id|rtc-&gt;bcd_dom
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_mday
)paren
suffix:semicolon
id|rtc-&gt;bcd_mth
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_mon
op_plus
l_int|1
)paren
suffix:semicolon
id|rtc-&gt;bcd_year
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_year
op_mod
l_int|100
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rtc_tm.tm_wday
op_ge
l_int|0
)paren
id|rtc-&gt;bcd_dow
op_assign
id|BIN2BCD
c_func
(paren
id|rtc_tm.tm_wday
op_plus
l_int|1
)paren
suffix:semicolon
id|rtc-&gt;ctrl
op_assign
l_int|0
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; *&t;We enforce only one user at a time here with the open/close.&n; *&t;Also clear the previous interrupt data on an open, and clean&n; *&t;up things on a close.&n; */
DECL|function|rtc_open
r_static
r_int
id|rtc_open
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
r_if
c_cond
(paren
id|rtc_status
)paren
(brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|rtc_status
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|rtc_release
r_static
r_int
id|rtc_release
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
id|rtc_status
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;The various file operations we support.&n; */
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
multiline_comment|/* No write */
l_int|NULL
comma
multiline_comment|/* No readdir */
l_int|NULL
comma
id|rtc_ioctl
comma
l_int|NULL
comma
multiline_comment|/* No mmap */
id|rtc_open
comma
id|rtc_release
)brace
suffix:semicolon
DECL|variable|rtc_dev
r_static
r_struct
id|miscdevice
id|rtc_dev
op_assign
(brace
id|RTC_MINOR
comma
l_string|&quot;rtc&quot;
comma
op_amp
id|rtc_fops
)brace
suffix:semicolon
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|rtc_MK48T08_init
c_func
(paren
r_void
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|MACH_IS_MVME16x
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;MK48T08 Real Time Clock Driver v%s&bslash;n&quot;
comma
id|RTC_VERSION
)paren
suffix:semicolon
id|misc_register
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
