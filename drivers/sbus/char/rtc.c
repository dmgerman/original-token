multiline_comment|/* $Id: rtc.c,v 1.19 2000/02/09 22:33:26 davem Exp $&n; *&n; * Linux/SPARC Real Time Clock Driver&n; * Copyright (C) 1996 Thomas K. Dyas (tdyas@eden.rutgers.edu)&n; *&n; * This is a little driver that lets a user-level program access&n; * the SPARC Mostek real time clock chip. It is no use unless you&n; * use the modified clock utility.&n; *&n; * Get the modified clock utility from:&n; *   ftp://vger.rutgers.edu/pub/linux/Sparc/userland/clock.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/miscdevice.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/poll.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mostek.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rtc.h&gt;
DECL|variable|rtc_busy
r_static
r_int
id|rtc_busy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Retrieve the current date and time from the real time clock. */
DECL|function|get_rtc_time
r_void
id|get_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
r_int
r_int
id|regs
op_assign
id|mstk48t02_regs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|tmp
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
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MSTK_CREG_READ
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|t-&gt;sec
op_assign
id|MSTK_REG_SEC
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;min
op_assign
id|MSTK_REG_MIN
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;hour
op_assign
id|MSTK_REG_HOUR
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;dow
op_assign
id|MSTK_REG_DOW
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;dom
op_assign
id|MSTK_REG_DOM
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;month
op_assign
id|MSTK_REG_MONTH
c_func
(paren
id|regs
)paren
suffix:semicolon
id|t-&gt;year
op_assign
id|MSTK_CVT_YEAR
c_func
(paren
id|MSTK_REG_YEAR
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|MSTK_CREG_READ
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/* Set the current date and time inthe real time clock. */
DECL|function|set_rtc_time
r_void
id|set_rtc_time
c_func
(paren
r_struct
id|rtc_time
op_star
id|t
)paren
(brace
r_int
r_int
id|regs
op_assign
id|mstk48t02_regs
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|u8
id|tmp
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
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_or_assign
id|MSTK_CREG_WRITE
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|MSTK_SET_REG_SEC
c_func
(paren
id|regs
comma
id|t-&gt;sec
)paren
suffix:semicolon
id|MSTK_SET_REG_MIN
c_func
(paren
id|regs
comma
id|t-&gt;min
)paren
suffix:semicolon
id|MSTK_SET_REG_HOUR
c_func
(paren
id|regs
comma
id|t-&gt;hour
)paren
suffix:semicolon
id|MSTK_SET_REG_DOW
c_func
(paren
id|regs
comma
id|t-&gt;dow
)paren
suffix:semicolon
id|MSTK_SET_REG_DOM
c_func
(paren
id|regs
comma
id|t-&gt;dom
)paren
suffix:semicolon
id|MSTK_SET_REG_MONTH
c_func
(paren
id|regs
comma
id|t-&gt;month
)paren
suffix:semicolon
id|MSTK_SET_REG_YEAR
c_func
(paren
id|regs
comma
id|t-&gt;year
op_minus
id|MSTK_YEAR_ZERO
)paren
suffix:semicolon
id|tmp
op_assign
id|mostek_read
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
)paren
suffix:semicolon
id|tmp
op_and_assign
op_complement
id|MSTK_CREG_WRITE
suffix:semicolon
id|mostek_write
c_func
(paren
id|regs
op_plus
id|MOSTEK_CREG
comma
id|tmp
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|rtc_lseek
r_static
r_int
r_int
id|rtc_lseek
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
r_struct
id|rtc_time
id|rtc_tm
suffix:semicolon
r_switch
c_cond
(paren
id|cmd
)paren
(brace
r_case
id|RTCGET
suffix:colon
id|get_rtc_time
c_func
(paren
op_amp
id|rtc_tm
)paren
suffix:semicolon
id|copy_to_user_ret
c_func
(paren
(paren
r_struct
id|rtc_time
op_star
)paren
id|arg
comma
op_amp
id|rtc_tm
comma
r_sizeof
(paren
r_struct
id|rtc_time
)paren
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|RTCSET
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|capable
c_func
(paren
id|CAP_SYS_TIME
)paren
)paren
r_return
op_minus
id|EPERM
suffix:semicolon
id|copy_from_user_ret
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
comma
op_minus
id|EFAULT
)paren
suffix:semicolon
id|set_rtc_time
c_func
(paren
op_amp
id|rtc_tm
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
)brace
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
id|rtc_busy
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|rtc_busy
op_assign
l_int|1
suffix:semicolon
id|MOD_INC_USE_COUNT
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
id|rtc_busy
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|rtc_fops
r_static
r_struct
id|file_operations
id|rtc_fops
op_assign
(brace
id|llseek
suffix:colon
id|rtc_lseek
comma
id|ioctl
suffix:colon
id|rtc_ioctl
comma
id|open
suffix:colon
id|rtc_open
comma
id|release
suffix:colon
id|rtc_release
comma
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
id|EXPORT_NO_SYMBOLS
suffix:semicolon
macro_line|#ifdef MODULE
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
macro_line|#else
r_int
id|__init
id|rtc_sun_init
c_func
(paren
r_void
)paren
macro_line|#endif
(brace
r_int
id|error
suffix:semicolon
r_if
c_cond
(paren
id|mstk48t02_regs
op_eq
l_int|0
)paren
(brace
multiline_comment|/* This diagnostic is a debugging aid... But a useful one. */
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtc: no Mostek in this computer&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|error
op_assign
id|misc_register
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;rtc: unable to get misc minor for Mostek&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|error
suffix:semicolon
)brace
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
id|misc_deregister
c_func
(paren
op_amp
id|rtc_dev
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
